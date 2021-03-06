# Makefile.in for back-mdb
## $ReOpenLDAP$
## Copyright (c) 2015,2016 Leonid Yuriev <leo@yuriev.ru>.
## Copyright (c) 2015,2016 Peter-Service R&D LLC <http://billing.ru/>.
##
## This file is part of ReOpenLDAP.
##
## ReOpenLDAP is free software; you can redistribute it and/or modify it under
## the terms of the GNU Affero General Public License as published by
## the Free Software Foundation; either version 3 of the License, or
## (at your option) any later version.
##
## ReOpenLDAP is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU Affero General Public License for more details.
##
## You should have received a copy of the GNU Affero General Public License
## along with this program.  If not, see <http://www.gnu.org/licenses/>.
##

pkglib_LTLIBRARIES =
noinst_LTLIBRARIES = libmdbx.la
bin_PROGRAMS = mdbx_stat mdbx_copy mdbx_dump mdbx_load mdbx_chk
back_mdb_la_LDFLAGS = -module
AM_CPPFLAGS = -DSLAPD_IMPORT -I$(srcdir)/.. -I$(top_srcdir)/include

if MDBX_DYNAMIC
pkglib_LTLIBRARIES += back_mdb.la
back_mdb_la_LDFLAGS += -export-dynamic \
	-release $(API_LIB_RELEASE) -version-info $(API_LIB_VERSION)
else
noinst_LTLIBRARIES += back_mdb.la
endif

if BEHIND_CURTIAN
BUILT_SOURCES = banner.c
banner.c: Makefile
	$(MKBANNER) --name backend_mdbx --global 'backend-mdbx' > $@ || $(RM) $@
endif

libmdbx_la_CFLAGS = -DNDEBUG=1 -DMDB_DEBUG=0
libmdbx_la_LIBADD = $(LTHREAD_LIBS)
libmdbx_la_SOURCES = ../../../libraries/libmdbx/mdbx.c

# LY: TODO
EXTRA_DIST = ../../../libraries/libmdbx/barriers.h \
	../../../libraries/libmdbx/CHANGES \
	../../../libraries/libmdbx/COPYRIGHT \
	../../../libraries/libmdbx/LICENSE\
	../../../libraries/libmdbx/lmdb.h \
	../../../libraries/libmdbx/Makefile\
	../../../libraries/libmdbx/mdb.c \
	../../../libraries/libmdbx/mdb_copy.1 \
	../../../libraries/libmdbx/mdb_dump.1 \
	../../../libraries/libmdbx/mdb_load.1 \
	../../../libraries/libmdbx/mdb_stat.1 \
	../../../libraries/libmdbx/mdbx.h \
	../../../libraries/libmdbx/midl.c \
	../../../libraries/libmdbx/midl.h \
	../../../libraries/libmdbx/reopen.h

back_mdb_la_SOURCES = add.c attr.c banner.c bind.c compare.c \
	config.c delete.c dn2entry.c dn2id.c extended.c filterindex.c \
	id2entry.c idl.c index.c init.c key.c modify.c modrdn.c \
	monitor.c nextid.c operational.c search.c tools.c \
	back-mdb.h idl.h proto-mdb.h

back_mdb_la_CFLAGS = -I$(srcdir)/.. -I$(top_srcdir)/libraries/libmdbx
back_mdb_la_LIBADD = libmdbx.la

mdbx_chk_SOURCES = ../../../libraries/libmdbx/mdb_chk.c
mdbx_copy_SOURCES = ../../../libraries/libmdbx/mdb_copy.c
mdbx_dump_SOURCES = ../../../libraries/libmdbx/mdb_dump.c
mdbx_load_SOURCES = ../../../libraries/libmdbx/mdb_load.c
mdbx_stat_SOURCES = ../../../libraries/libmdbx/mdb_stat.c

mdbx_chk_LDADD = libmdbx.la
mdbx_copy_LDADD = libmdbx.la
mdbx_dump_LDADD = libmdbx.la
mdbx_load_LDADD = libmdbx.la
mdbx_stat_LDADD = libmdbx.la
