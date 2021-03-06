
NULL =

SUBDIRS = man

DOC_DIR = $(top_srcdir)/doc

# The name of the module.
DOC_MODULE=storaged

# The top-level SGML file.
DOC_MAIN_SGML_FILE=$(DOC_MODULE)-docs.xml

# Extra options to supply to gtkdoc-scan
SCAN_OPTIONS=

# Types
STORAGED_TYPES=$(DOC_MODULE).types

# Sections
STORAGED_SECTIONS=$(DOC_MODULE)-sections.txt

# The directory containing the source code. Relative to $(srcdir)
DOC_SOURCE_DIR = $(top_srcdir)

HFILE_GLOB =                                                                   \
	$(top_srcdir)/storaged/*.h                                             \
	$(top_srcdir)/src/*.h                                                  \
	$(top_srcdir)/modules/*.h

CFILE_GLOB =                                                                   \
	$(top_srcdir)/storaged/*.c                                             \
	$(top_srcdir)/src/*.c                                                  \
	$(top_srcdir)/modules/*.c

# Headers to ignore
IGNORE_HFILES=                                                                 \
	config.h                                                               \
	$(NULL)

# CFLAGS and LDFLAGS for compiling scan program. Only needed
# if $(DOC_MODULE).types is non-empty.
AM_CPPFLAGS =                                                                  \
	-I$(srcdir)                                                            \
	-I$(top_srcdir)                                                        \
	-I$(top_builddir)                                                      \
	$(GLIB_CFLAGS)                                                         \
	$(GIO_CFLAGS)                                                          \
	$(NULL)

GTKDOC_LIBS =                                                                  \
	$(GLIB_LIBS)                                                           \
	$(GIO_LIBS)                                                            \
	$(top_builddir)/storaged/libstoraged.la                                \
	$(top_builddir)/src/libstoraged-daemon.la                              \
	$(NULL)

# Extra options to supply to gtkdoc-mkdb
MKDB_OPTIONS = --output-format=xml --sgml-mode --name-space=storaged

# Images to copy into HTML directory
HTML_IMAGES =                                                                  \
	$(NULL)

content_files =                                                                \
	$(NULL)

expand_content_files =                                                         \
	$(NULL)

extra_files =                                                                  \
	$(NULL)

# ------------------------------------------------------------------------------

all-local: $(DOC_MAIN_SGML_FILE)

# storaged-docs.xml, storaged-sections.txt storaged.types
$(DOC_MAIN_SGML_FILE): $(DOC_MAIN_SGML_FILE).in $(STORAGED_SECTIONS).in $(STORAGED_TYPES).in
	$(AM_V_at) rm -f $(DOC_MAIN_SGML_FILE) $(STORAGED_SECTIONS) $(STORAGED_TYPES) && \
	cp $(DOC_MAIN_SGML_FILE).in $(builddir)/$(DOC_MAIN_SGML_FILE) && \
	cp $(STORAGED_SECTIONS).in $(builddir)/$(STORAGED_SECTIONS) && \
	cp $(STORAGED_TYPES).in $(builddir)/$(STORAGED_TYPES)
if HAVE_LVM2
	$(AM_V_at) $(SED) -i -f $(DOC_DIR)/$(DOC_MAIN_SGML_FILE).lvm2.sed $(builddir)/$(DOC_MAIN_SGML_FILE)
	$(AM_V_at) $(SED) -i -f $(DOC_DIR)/$(STORAGED_SECTIONS).lvm2.sed $(builddir)/$(STORAGED_SECTIONS)
	$(AM_V_at) $(SED) -i -f $(DOC_DIR)/$(STORAGED_TYPES).lvm2.sed $(builddir)/$(STORAGED_TYPES)
else
	$(AM_V_at) $(SED) -i "/<\!-- LVM2_GENERATED_SECTIONS -->/d" $(builddir)/$(STORAGED_SECTIONS)
	$(AM_V_at) $(SED) -i "/\# LVM2_TYPES/d" $(builddir)/$(STORAGED_TYPES)
endif # HAVE_LVM2
if HAVE_LSM
	$(AM_V_at) $(SED) -i -f $(DOC_DIR)/$(DOC_MAIN_SGML_FILE).lsm.sed $(builddir)/$(DOC_MAIN_SGML_FILE)
	$(AM_V_at) $(SED) -i -f $(DOC_DIR)/$(STORAGED_SECTIONS).lsm.sed $(builddir)/$(STORAGED_SECTIONS)
	$(AM_V_at) $(SED) -i -f $(DOC_DIR)/$(STORAGED_TYPES).lsm.sed $(builddir)/$(STORAGED_TYPES)
else
	$(AM_V_at) $(SED) -i "/<\!-- LSM_GENERATED_SECTIONS -->/d" $(builddir)/$(STORAGED_SECTIONS)
	$(AM_V_at) $(SED) -i "/\# LSM_TYPES/d" $(builddir)/$(STORAGED_TYPES)
endif # HAVE_LSM
if HAVE_ISCSI
	$(AM_V_at) $(SED) -i -f $(DOC_DIR)/$(DOC_MAIN_SGML_FILE).iscsi.sed $(builddir)/$(DOC_MAIN_SGML_FILE)
	$(AM_V_at) $(SED) -i -f $(DOC_DIR)/$(STORAGED_SECTIONS).iscsi.sed $(builddir)/$(STORAGED_SECTIONS)
	$(AM_V_at) $(SED) -i -f $(DOC_DIR)/$(STORAGED_TYPES).iscsi.sed $(builddir)/$(STORAGED_TYPES)
else
	$(AM_V_at) $(SED) -i "/<\!-- ISCSI_GENERATED_SECTIONS -->/d" $(builddir)/$(STORAGED_SECTIONS)
	$(AM_V_at) $(SED) -i "/\# ISCSI_TYPES/d" $(builddir)/$(STORAGED_TYPES)
endif # HAVE_ISCSI
if HAVE_BTRFS
	$(AM_V_at) $(SED) -i -f $(DOC_DIR)/$(DOC_MAIN_SGML_FILE).btrfs.sed $(builddir)/$(DOC_MAIN_SGML_FILE)
	$(AM_V_at) $(SED) -i -f $(DOC_DIR)/$(STORAGED_SECTIONS).btrfs.sed $(builddir)/$(STORAGED_SECTIONS)
	$(AM_V_at) $(SED) -i -f $(DOC_DIR)/$(STORAGED_TYPES).btrfs.sed $(builddir)/$(STORAGED_TYPES)
else
	$(AM_V_at) $(SED) -i "/<\!-- BTRFS_GENERATED_SECTIONS -->/d" $(builddir)/$(STORAGED_SECTIONS)
	$(AM_V_at) $(SED) -i "/\# BTRFS_TYPES/d" $(builddir)/$(STORAGED_TYPES)
endif # HAVE_BTRFS
if HAVE_ZRAM
	$(AM_V_at) $(SED) -i -f $(DOC_DIR)/$(DOC_MAIN_SGML_FILE).zram.sed $(builddir)/$(DOC_MAIN_SGML_FILE)
	$(AM_V_at) $(SED) -i -f $(DOC_DIR)/$(STORAGED_SECTIONS).zram.sed $(builddir)/$(STORAGED_SECTIONS)
	$(AM_V_at) $(SED) -i -f $(DOC_DIR)/$(STORAGED_TYPES).zram.sed $(builddir)/$(STORAGED_TYPES)
else
	$(AM_V_at) $(SED) -i "/<\!-- ZRAM_GENERATED_SECTIONS -->/d" $(builddir)/$(STORAGED_SECTIONS)
	$(AM_V_at) $(SED) -i "/\# ZRAM_TYPES/d" $(builddir)/$(STORAGED_TYPES)
endif # HAVE_ZRAM
if HAVE_BCACHE
	$(AM_V_at) $(SED) -i -f $(DOC_DIR)/$(DOC_MAIN_SGML_FILE).bcache.sed $(builddir)/$(DOC_MAIN_SGML_FILE)
	$(AM_V_at) $(SED) -i -f $(DOC_DIR)/$(STORAGED_SECTIONS).bcache.sed $(builddir)/$(STORAGED_SECTIONS)
	$(AM_V_at) $(SED) -i -f $(DOC_DIR)/$(STORAGED_TYPES).bcache.sed $(builddir)/$(STORAGED_TYPES)
else
	$(AM_V_at) $(SED) -i "/<\!-- BCACHE_GENERATED_SECTIONS -->/d" $(builddir)/$(STORAGED_SECTIONS)
	$(AM_V_at) $(SED) -i "/\# BCACHE_TYPES/d" $(builddir)/$(STORAGED_TYPES)
endif # HAVE_BCACHE

# GTKDOC for LVM2
if HAVE_LVM2
DOC_SOURCE_DIR += $(top_srcdir)/modules/lvm2
HFILE_GLOB += $(top_srcdir)/modules/lvm2/*.h
CFILE_GLOB += $(top_srcdir)/modules/lvm2/*.c
AM_CPPFLAGS += -I$(top_srcdir)/modules/lvm2
GTKDOC_LIBS += $(top_builddir)/modules/lvm2/libstoraged_lvm2.la
endif # HAVE_LVM2

# GTKDOC for ISCSI
if HAVE_ISCSI
DOC_SOURCE_DIR += $(top_srcdir)/modules/iscsi
HFILE_GLOB += $(top_srcdir)/modules/iscsi/*.h
CFILE_GLOB += $(top_srcdir)/modules/iscsi/*.c
AM_CPPFLAGS += -I$(top_srcdir)/modules/iscsi
GTKDOC_LIBS += $(top_builddir)/modules/iscsi/libstoraged_iscsi.la
endif # HAVE_ISCSI

# GTKDOC for BTRFS
if HAVE_BTRFS
DOC_SOURCE_DIR += $(top_srcdir)/modules/btrfs
HFILE_GLOB += $(top_srcdir)/modules/btrfs/*.h
CFILE_GLOB += $(top_srcdir)/modules/btrfs/*.c
AM_CPPFLAGS += -I$(top_srcdir)/modules/btrfs
GTKDOC_LIBS += $(top_builddir)/modules/btrfs/libstoraged_btrfs.la
endif # HAVE_BTRFS

# GTKDOC for ZRAM
if HAVE_ZRAM
DOC_SOURCE_DIR += $(top_srcdir)/modules/zram
HFILE_GLOB += $(top_srcdir)/modules/zram/*.h
CFILE_GLOB += $(top_srcdir)/modules/zram/*.c
AM_CPPFLAGS += -I$(top_srcdir)/modules/zram
GTKDOC_LIBS += $(top_builddir)/modules/zram/libstoraged_zram.la
endif # HAVE_ZRAM

# GTKDOC for LSM
if HAVE_LSM
DOC_SOURCE_DIR += $(top_srcdir)/modules/lsm
HFILE_GLOB += $(top_srcdir)/modules/lsm/*.h
CFILE_GLOB += $(top_srcdir)/modules/lsm/*.c
AM_CPPFLAGS += -I$(top_srcdir)/modules/lsm
GTKDOC_LIBS += $(top_builddir)/modules/lsm/libstoraged_lsm.la
endif # HAVE_LSM

# GTKDOC for BCACHE
if HAVE_BCACHE
DOC_SOURCE_DIR += $(top_srcdir)/modules/bcache
HFILE_GLOB += $(top_srcdir)/modules/bcache/*.h
CFILE_GLOB += $(top_srcdir)/modules/bcache/*.c
AM_CPPFLAGS += -I$(top_srcdir)/modules/bcache
GTKDOC_LIBS += $(top_builddir)/modules/bcache/libstoraged_bcache.la
endif # HAVE_BCACHE

# ------------------------------------------------------------------------------

include $(top_srcdir)/gtk-doc.make

EXTRA_DIST +=                                                                  \
	$(DOC_MAIN_SGML_FILE).in.in                                            \
	$(DOC_MAIN_SGML_FILE).in                                               \
        $(DOC_MAIN_SGML_FILE).bcache.dbus.in                                   \
        $(DOC_MAIN_SGML_FILE).bcache.generated.in                              \
        $(DOC_MAIN_SGML_FILE).bcache.sed                                       \
	$(DOC_MAIN_SGML_FILE).btrfs.dbus.in                                    \
	$(DOC_MAIN_SGML_FILE).btrfs.generated.in                               \
	$(DOC_MAIN_SGML_FILE).btrfs.sed                                        \
	$(DOC_MAIN_SGML_FILE).iscsi.dbus.in                                    \
	$(DOC_MAIN_SGML_FILE).iscsi.generated.in                               \
	$(DOC_MAIN_SGML_FILE).iscsi.sed                                        \
	$(DOC_MAIN_SGML_FILE).lsm.dbus.in                                      \
	$(DOC_MAIN_SGML_FILE).lsm.generated.in                                 \
	$(DOC_MAIN_SGML_FILE).lsm.sed                                          \
	$(DOC_MAIN_SGML_FILE).lvm2.dbus.in                                     \
	$(DOC_MAIN_SGML_FILE).lvm2.generated.in                                \
	$(DOC_MAIN_SGML_FILE).lvm2.sed                                         \
	$(DOC_MAIN_SGML_FILE).zram.dbus.in                                     \
	$(DOC_MAIN_SGML_FILE).zram.generated.in                                \
	$(DOC_MAIN_SGML_FILE).zram.block_devices.in                            \
	$(DOC_MAIN_SGML_FILE).zram.sed                                         \
	$(STORAGED_TYPES).in.in                                                \
	$(STORAGED_TYPES).in                                                   \
        $(STORAGED_TYPES).bcache.in                                            \
        $(STORAGED_TYPES).bcache.sed                                           \
	$(STORAGED_TYPES).btrfs.in                                             \
	$(STORAGED_TYPES).btrfs.sed                                            \
	$(STORAGED_TYPES).iscsi.in                                             \
	$(STORAGED_TYPES).iscsi.sed                                            \
	$(STORAGED_TYPES).lsm.in                                               \
	$(STORAGED_TYPES).lsm.sed                                              \
	$(STORAGED_TYPES).lvm2.in                                              \
	$(STORAGED_TYPES).lvm2.sed                                             \
	$(STORAGED_TYPES).zram.in                                              \
	$(STORAGED_TYPES).zram.sed                                             \
	$(STORAGED_SECTIONS).in.in                                             \
	$(STORAGED_SECTIONS).in                                                \
        $(STORAGED_SECTIONS).bcache.sections.in                                \
        $(STORAGED_SECTIONS).bcache.sed                                        \
	$(STORAGED_SECTIONS).btrfs.sections.in                                 \
	$(STORAGED_SECTIONS).btrfs.sed                                         \
	$(STORAGED_SECTIONS).iscsi.sections.in                                 \
	$(STORAGED_SECTIONS).iscsi.sed                                         \
	$(STORAGED_SECTIONS).lsm.sections.in                                   \
	$(STORAGED_SECTIONS).lsm.sed                                           \
	$(STORAGED_SECTIONS).lvm2.sections.in                                  \
	$(STORAGED_SECTIONS).lvm2.sed                                          \
	$(STORAGED_SECTIONS).zram.sections.in                                  \
	$(STORAGED_SECTIONS).zram.sed                                          \
	$(STORAGED_SECTIONS).lsm.sections.in                                   \
	version.xml.in                                                         \
	TODO-ISCSI

CLEANFILES +=                                                                  \
	$(DOC_MAIN_SGML_FILE)                                                  \
	$(STORAGED_SECTIONS)                                                   \
	$(STORAGED_TYPES)                                                      \
	$(DOC_MODULE)-decl-list.txt                                            \
	$(DOC_MODULE)-decl.txt                                                 \
	$(DOC_MODULE)-overrides.txt                                            \
	$(DOC_MODULE)-undeclared.txt                                           \
	$(DOC_MODULE)-undocumented.txt                                         \
	$(DOC_MODULE)-overrides.txt                                            \
	$(DOC_MODULE)-unused.txt                                               \
	$(DOC_MODULE).args                                                     \
	$(DOC_MODULE).hierarchy                                                \
	$(DOC_MODULE).interfaces                                               \
	$(DOC_MODULE).prerequisites                                            \
	$(DOC_MODULE).signals                                                  \
	*.stamp                                                                \
	-rf xml html tmpl                                                      \
	$(NULL)
