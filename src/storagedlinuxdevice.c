/* -*- mode: C; c-file-style: "gnu"; indent-tabs-mode: nil; -*-
 *
 * Copyright (C) 2008 David Zeuthen <zeuthen@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include "config.h"
#include <glib/gi18n-lib.h>

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/cdrom.h>

#include <glib.h>
#include <glib-object.h>

#include "storagedlinuxdevice.h"
#include "storagedprivate.h"
#include "storagedlogging.h"
#include "storagedata.h"
#include "storageddaemonutil.h"

/**
 * SECTION:storagedlinuxdevice
 * @title: StoragedLinuxDevice
 * @short_description: Low-level devices on Linux
 *
 * Types and functions used to record information obtained from the
 * udev database as well as by probing the device.
 */


typedef struct _StoragedLinuxDeviceClass StoragedLinuxDeviceClass;

struct _StoragedLinuxDeviceClass
{
  GObjectClass parent_class;
};


G_DEFINE_TYPE (StoragedLinuxDevice, storaged_linux_device, G_TYPE_OBJECT);

static void
storaged_linux_device_init (StoragedLinuxDevice *device)
{
}

static void
storaged_linux_device_finalize (GObject *object)
{
  StoragedLinuxDevice *device = STORAGED_LINUX_DEVICE (object);

  g_clear_object (&device->udev_device);
  g_free (device->ata_identify_device_data);
  g_free (device->ata_identify_packet_device_data);

  G_OBJECT_CLASS (storaged_linux_device_parent_class)->finalize (object);
}

static void
storaged_linux_device_class_init (StoragedLinuxDeviceClass *klass)
{
  GObjectClass *gobject_class;

  gobject_class = G_OBJECT_CLASS (klass);
  gobject_class->finalize     = storaged_linux_device_finalize;
}

/* ---------------------------------------------------------------------------------------------------- */

static gboolean probe_ata (StoragedLinuxDevice  *device,
                           GCancellable         *cancellable,
                           GError              **error);

/**
 * storaged_linux_device_new_sync:
 * @udev_device: A #GUdevDevice.
 *
 * Creates a new #StoragedLinuxDevice from @udev_device which includes
 * probing the device for more information, if applicable.
 *
 * The calling thread may be blocked for a non-trivial amount of time
 * while the probing is underway.
 *
 * Returns: A #StoragedLinuxDevice.
 */
StoragedLinuxDevice *
storaged_linux_device_new_sync (GUdevDevice *udev_device)
{
  StoragedLinuxDevice *device;
  GError *error = NULL;

  g_return_val_if_fail (G_UDEV_IS_DEVICE (udev_device), NULL);

  device = g_object_new (STORAGED_TYPE_LINUX_DEVICE, NULL);
  device->udev_device = g_object_ref (udev_device);

  /* No point in probing on remove events */
  if (!(g_strcmp0 (g_udev_device_get_action (udev_device), "remove") == 0))
    {
      if (!storaged_linux_device_reprobe_sync (device, NULL, &error))
        goto out;
    }

 out:
  if (error != NULL)
    {
      storaged_error ("Error probing device: %s (%s, %d)",
                    error->message, g_quark_to_string (error->domain), error->code);
      g_clear_error (&error);
    }

  return device;
}

/* ---------------------------------------------------------------------------------------------------- */

/**
 * storaged_linux_device_reprobe_sync:
 * @device: A #StoragedLinuxDevice.
 * @cancellable: (allow-none): A #GCancellable or %NULL.
 * @error: Return location for error or %NULL.
 *
 * Forcibly reprobe information on @device. The calling thread may be
 * blocked for a non-trivial amount of time while the probing is
 * underway.
 *
 * Returns: %TRUE if reprobing succeeded, %FALSE otherwise.
 */
gboolean
storaged_linux_device_reprobe_sync (StoragedLinuxDevice  *device,
                                    GCancellable         *cancellable,
                                    GError              **error)
{
  gboolean ret = FALSE;

  /* Get IDENTIFY DEVICE / IDENTIFY PACKET DEVICE data for ATA devices */
  if (g_strcmp0 (g_udev_device_get_subsystem (device->udev_device), "block") == 0 &&
      g_strcmp0 (g_udev_device_get_devtype (device->udev_device), "disk") == 0 &&
      g_udev_device_get_property_as_boolean (device->udev_device, "ID_ATA"))
    {
      if (!probe_ata (device, cancellable, error))
        goto out;
    }

  ret = TRUE;

 out:
  return ret;
}

/* ---------------------------------------------------------------------------------------------------- */

static gboolean
probe_ata (StoragedLinuxDevice  *device,
           GCancellable         *cancellable,
           GError              **error)
{
  const gchar *device_file;
  gboolean ret = FALSE;
  gint fd = -1;
  StoragedAtaCommandInput input = {0};
  StoragedAtaCommandOutput output = {0};

  device_file = g_udev_device_get_device_file (device->udev_device);
  fd = open (device_file, O_RDONLY|O_NONBLOCK);
  if (fd == -1)
    {
      g_set_error (error, STORAGED_ERROR, STORAGED_ERROR_FAILED,
                   "Error opening device file %s: %m",
                   device_file);
      goto out;
    }


  if (ioctl (fd, CDROM_GET_CAPABILITY, NULL) == -1)
    {
      /* ATA8: 7.16 IDENTIFY DEVICE - ECh, PIO Data-In */
      input.command = 0xec;
      input.count = 1;
      output.buffer = g_new0 (guchar, 512);
      output.buffer_size = 512;
      if (!storaged_ata_send_command_sync (fd,
                                           -1,
                                           STORAGED_ATA_COMMAND_PROTOCOL_DRIVE_TO_HOST,
                                           &input,
                                           &output,
                                           error))
        {
          g_free (output.buffer);
          g_prefix_error (error, "Error sending ATA command IDENTIFY DEVICE to %s: ",
                          device_file);
          goto out;
        }
      g_free (device->ata_identify_device_data);
      device->ata_identify_device_data = output.buffer;
      /* storaged_daemon_util_hexdump_debug (device->ata_identify_device_data, 512); */
    }
  else
    {
      /* ATA8: 7.17 IDENTIFY PACKET DEVICE - A1h, PIO Data-In */
      input.command = 0xa1;
      input.count = 1;
      output.buffer = g_new0 (guchar, 512);
      output.buffer_size = 512;
      if (!storaged_ata_send_command_sync (fd,
                                           -1,
                                           STORAGED_ATA_COMMAND_PROTOCOL_DRIVE_TO_HOST,
                                           &input,
                                           &output,
                                           error))
        {
          g_free (output.buffer);
          g_prefix_error (error, "Error sending ATA command IDENTIFY PACKET DEVICE to %s: ",
                          device_file);
          goto out;
        }
      g_free (device->ata_identify_packet_device_data);
      device->ata_identify_packet_device_data = output.buffer;
      /* storaged_daemon_util_hexdump_debug (device->ata_identify_packet_device_data, 512); */
    }

  ret = TRUE;

 out:
  if (fd != -1)
    {
      if (close (fd) != 0)
        {
          storaged_warning ("Error closing fd %d for device %s: %m",
                          fd, device_file);
        }
    }
  return ret;
}
