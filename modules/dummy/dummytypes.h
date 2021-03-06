/* -*- mode: C; c-file-style: "gnu"; indent-tabs-mode: nil; -*-
 *
 * Copyright (C) 2014 Tomas Bzatek <tbzatek@redhat.com>
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

#ifndef __DUMMY_TYPES_H__
#define __DUMMY_TYPES_H__

#include <gio/gio.h>
#include <polkit/polkit.h>
#include <storaged/storaged.h>
#include <gudev/gudev.h>

#include <sys/types.h>

#define DUMMY_MODULE_NAME "dummy"

struct _DummyLinuxBlock;
typedef struct _DummyLinuxBlock DummyLinuxBlock;

struct _DummyLinuxDrive;
typedef struct _DummyLinuxDrive DummyLinuxDrive;

struct _DummyLoopObject;
typedef struct _DummyLoopObject DummyLoopObject;

struct _DummyLinuxLoop;
typedef struct _DummyLinuxLoop DummyLinuxLoop;

struct _DummyLinuxManager;
typedef struct _DummyLinuxManager DummyLinuxManager;

#endif /* __DUMMY_TYPES_H__ */
