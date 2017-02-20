# $OpenLDAP$
## This work is part of OpenLDAP Software <http://www.openldap.org/>.
##
## Copyright 1998-2016 The OpenLDAP Foundation.
## All rights reserved.
##
## Redistribution and use in source and binary forms, with or without
## modification, are permitted only as authorized by the OpenLDAP
## Public License.
##
## A copy of this license is available in the file LICENSE in the
## top-level directory of the distribution or, alternatively, at
##---------------------------------------------------------------------------
#
# Top-level Makefile template
#

PACKAGE= OpenLDAP
VERSION= 2.4.44
RELEASEDATE= 2016/02/05


SHELL = /bin/sh

top_builddir = ../..

srcdir = .
top_srcdir = ../..

prefix = /usr/local
exec_prefix = ${prefix}
ldap_subdir = /openldap

bindir = ${exec_prefix}/bin
datarootdir = ${prefix}/share
datadir = ${datarootdir}$(ldap_subdir)
includedir = ${prefix}/include
infodir = ${datarootdir}/info
libdir = ${exec_prefix}/lib
libexecdir = ${exec_prefix}/libexec
localstatedir = ${prefix}/var
mandir = ${datarootdir}/man
moduledir = ${exec_prefix}/libexec$(ldap_subdir)
sbindir = ${exec_prefix}/sbin
sharedstatedir = ${prefix}/com
sysconfdir = ${prefix}/etc$(ldap_subdir)
schemadir = $(sysconfdir)/schema

PLAT = UNIX
EXEEXT = 
OBJEXT = o

BUILD_LIBS_DYNAMIC = static

SHTOOL = $(top_srcdir)/build/shtool

INSTALL = $(SHTOOL) install -c
INSTALL_PROGRAM = $(INSTALL)
INSTALL_DATA = $(INSTALL) -m 644
INSTALL_SCRIPT = $(INSTALL)

STRIP = -s

LINT = lint
5LINT = 5lint

MKDEP = $(top_srcdir)/build/mkdep $(MKDEPFLAG) \
	-d "$(srcdir)" -c "$(MKDEP_CC)" -m "$(MKDEP_CFLAGS)"
MKDEP_CC	= cc
MKDEP_CFLAGS = -M

MKVERSION = $(top_srcdir)/build/mkversion -v "$(VERSION)"

LIBTOOL = $(SHELL) $(top_builddir)/libtool
LIBRELEASE = 2.4
LIBVERSION = 12:7:10
LTVERSION = -release $(LIBRELEASE) -version-info $(LIBVERSION)

# libtool --only flag for libraries: platform specific
NT_LTONLY_LIB = # --only-$(BUILD_LIBS_DYNAMIC)
LTONLY_LIB = $(UNIX_LTONLY_LIB)

# libtool --only flag for modules: depends on linkage of module
# The BUILD_MOD macro is defined in each backend Makefile.in file
LTONLY_yes = --tag=disable-shared
LTONLY_mod = --tag=disable-static
LTONLY_MOD = $(LTONLY_$(BUILD_MOD))

# platform-specific libtool flags
NT_LTFLAGS_LIB = -no-undefined -avoid-version -rpath $(libdir)
NT_LTFLAGS_MOD = -no-undefined -avoid-version -rpath $(moduledir)
UNIX_LTFLAGS_LIB = $(LTVERSION) -rpath $(libdir)
UNIX_LTFLAGS_MOD = $(LTVERSION) -rpath $(moduledir)

# libtool flags
LTFLAGS     = $(UNIX_LTFLAGS)
LTFLAGS_LIB = $(UNIX_LTFLAGS_LIB)
LTFLAGS_MOD = $(UNIX_LTFLAGS_MOD)

# LIB_DEFS defined in liblber and libldap Makefile.in files.
# MOD_DEFS defined in backend Makefile.in files.

# platform-specific LINK_LIBS defined in various Makefile.in files.
# LINK_LIBS referenced in library and module link commands.
LINK_LIBS = $(MOD_LIBS) $(UNIX_LINK_LIBS)

LTSTATIC = -static

LTLINK   = $(LIBTOOL) --mode=link \
	$(CC) $(LTSTATIC) $(LT_CFLAGS) $(LDFLAGS) $(LTFLAGS)

LTCOMPILE_LIB = $(LIBTOOL) $(LTONLY_LIB) --mode=compile \
	$(CC) $(LT_CFLAGS) $(LT_CPPFLAGS) $(LIB_DEFS) -c

LTLINK_LIB = $(LIBTOOL) $(LTONLY_LIB) --mode=link \
	$(CC) $(LT_CFLAGS) $(LDFLAGS) $(LTFLAGS_LIB)

LTCOMPILE_MOD = $(LIBTOOL) $(LTONLY_MOD) --mode=compile \
	$(CC) $(LT_CFLAGS) $(LT_CPPFLAGS) $(MOD_DEFS) -c

LTLINK_MOD = $(LIBTOOL) $(LTONLY_MOD) --mode=link \
	$(CC) $(LT_CFLAGS) $(LDFLAGS) $(LTFLAGS_MOD)

LTINSTALL = $(LIBTOOL) --mode=install $(INSTALL) 
LTFINISH = $(LIBTOOL) --mode=finish

# Misc UNIX commands used in build environment
AR = ar
BASENAME = basename
CAT = cat
CHMOD = chmod
DATE = date
ECHO = $(SHTOOL) echo
HOSTNAME = $(SHTOOL) echo -e "%h%d"
LN = $(SHTOOL) mkln
LN_H = $(LN)
LN_S = $(LN) -s
MAKEINFO = ${SHELL} /home/zhangyg/openldap-2.4.44/build/missing --run makeinfo
MKDIR = $(SHTOOL) mkdir -p
MV = $(SHTOOL) move
PWD = pwd
RANLIB = ranlib
RM = rm -f
SED = sed
SUBST = $(SHTOOL) subst

# For manual pages
# MANCOMPRESS=@MANCOMPRESS@
# MANCOMPRESSSUFFIX=@MANCOMPRESSSUFFIX@
MANCOMPRESS=$(CAT)
MANCOMPRESSSUFFIX=

SOELIM=soelim

INCLUDEDIR= $(top_srcdir)/include
LDAP_INCPATH= -I$(LDAP_INCDIR) -I$(INCLUDEDIR)
LDAP_LIBDIR= $(top_builddir)/libraries

LUTIL_LIBS = 
LTHREAD_LIBS =  -pthread

BDB_LIBS =  -ldb-5.1
SLAPD_NDB_LIBS = 

LDAP_LIBLBER_LA = $(LDAP_LIBDIR)/liblber/liblber.la
LDAP_LIBLDAP_LA = $(LDAP_LIBDIR)/libldap/libldap.la
LDAP_LIBLDAP_R_LA = $(LDAP_LIBDIR)/libldap_r/libldap_r.la

LDAP_LIBREWRITE_A = $(LDAP_LIBDIR)/librewrite/librewrite.a
LDAP_LIBLUNICODE_A = $(LDAP_LIBDIR)/liblunicode/liblunicode.a
LDAP_LIBLUTIL_A = $(LDAP_LIBDIR)/liblutil/liblutil.a

LDAP_L = $(LDAP_LIBLUTIL_A) \
	$(LDAP_LIBLDAP_LA) $(LDAP_LIBLBER_LA)
SLAPD_L = $(LDAP_LIBLUNICODE_A) $(LDAP_LIBREWRITE_A) \
	$(LDAP_LIBLUTIL_A) $(LDAP_LIBLDAP_R_LA) $(LDAP_LIBLBER_LA)

WRAP_LIBS = 
# AutoConfig generated 
AC_CC	= cc
AC_CFLAGS = -g -O2
AC_DEFS =  # -DHAVE_CONFIG_H
AC_LDFLAGS = 
AC_LIBS = -lresolv 

KRB4_LIBS = 
KRB5_LIBS = 
KRB_LIBS =  
SASL_LIBS = 
TLS_LIBS = -lssl -lcrypto
AUTH_LIBS = 
SECURITY_LIBS = $(SASL_LIBS) $(KRB_LIBS) $(TLS_LIBS) $(AUTH_LIBS)
ICU_LIBS = 

MODULES_CPPFLAGS = 
MODULES_LDFLAGS = 
MODULES_LIBS = 
SLAPD_PERL_LDFLAGS = 

SLAPD_SQL_LDFLAGS = 
SLAPD_SQL_INCLUDES = 
SLAPD_SQL_LIBS = 

SLAPD_LIBS =  $(BDB_LIBS)      $(ICU_LIBS)

# Our Defaults
CC = $(AC_CC)
DEFS = $(LDAP_INCPATH) $(XINCPATH) $(XDEFS) $(AC_DEFS) $(DEFINES)
CFLAGS = $(AC_CFLAGS) $(DEFS)
LDFLAGS = $(LDAP_LIBPATH) $(AC_LDFLAGS) $(XLDFLAGS)
LIBS = $(XLIBS) $(XXLIBS) $(AC_LIBS) $(XXXLIBS)

LT_CFLAGS = $(AC_CFLAGS)
LT_CPPFLAGS = $(DEFS)

all:		all-common all-local FORCE
install:	install-common install-local FORCE
clean:		clean-common clean-local FORCE
veryclean:	veryclean-common veryclean-local FORCE
depend:		depend-common depend-local FORCE

# empty common rules
all-common:
install-common:
clean-common:
veryclean-common:	clean-common FORCE
depend-common:
lint-common:
lint5-common:

# empty local rules
all-local:
install-local:
clean-local:
veryclean-local:	clean-local FORCE
depend-local:
lint-local:
lint5-local:

veryclean: FORCE
	$(RM) Makefile
	$(RM) -r .libs

Makefile: Makefile.in $(top_srcdir)/build/top.mk

pathtest:
	$(SHTOOL) --version

# empty rule for forcing rules
FORCE:

##---------------------------------------------------------------------------

# Makefile for -llutil
# $OpenLDAP$
## This work is part of OpenLDAP Software <http://www.openldap.org/>.
## 
## Copyright 1998-2016 The OpenLDAP Foundation.
## All rights reserved.
##
## Redistribution and use in source and binary forms, with or without
## modification, are permitted only as authorized by the OpenLDAP
## Public License.
##
## A copy of this license is available in the file LICENSE in the
## top-level directory of the distribution or, alternatively, at
## <http://www.OpenLDAP.org/license.html>.

LIBRARY	= liblutil.a
PROGRAM = testavl

LDAP_INCDIR= ../../include       
LDAP_LIBDIR= ../../libraries

NT_SRCS = ntservice.c
NT_OBJS = ntservice.o slapdmsg.res

UNIX_SRCS = detach.c
UNIX_OBJS = detach.o

XLIBS = $(LIBRARY) $(LDAP_LIBLBER_LA)

SRCS	= base64.c entropy.c sasl.c signal.c hash.c passfile.c \
	md5.c passwd.c sha1.c getpass.c lockf.c utils.c uuid.c sockpair.c \
	avl.c tavl.c \
	testavl.c \
	meter.c \
	 setproctitle.c getpeereid.c $(UNIX_SRCS)

OBJS	= base64.o entropy.o sasl.o signal.o hash.o passfile.o \
	md5.o passwd.o sha1.o getpass.o lockf.o utils.o uuid.o sockpair.o \
	avl.o tavl.o \
	meter.o \
	 ${LIBOBJDIR}setproctitle$U.o ${LIBOBJDIR}getpeereid$U.o $(UNIX_OBJS)

testavl: $(XLIBS) testavl.o
	(LTLINK) -o $@ testavl.o $(LIBS)

testtavl: $(XLIBS) testtavl.o
	(LTLINK) -o $@ testtavl.o $(LIBS)

# These rules are for a Mingw32 build, specifically.
# It's ok for them to be here because the clean rule is harmless, and
# slapdmsg.res won't get built unless it's declared in OBJS.

slapdmsg.bin: FORCE
	@if [ ! -f $@ ]; then cp $(srcdir)/$@ .; fi

slapdmsg.res: slapdmsg.rc slapdmsg.bin
	windres $< -O coff -o $@

clean-local:
	$(RM) *.res

# $OpenLDAP$
## This work is part of OpenLDAP Software <http://www.openldap.org/>.
##
## Copyright 1998-2016 The OpenLDAP Foundation.
## All rights reserved.
##
## Redistribution and use in source and binary forms, with or without
## modification, are permitted only as authorized by the OpenLDAP
## Public License.
##
## A copy of this license is available in the file LICENSE in the
## top-level directory of the distribution or, alternatively, at
## <http://www.OpenLDAP.org/license.html>.
##---------------------------------------------------------------------------
#
# Makefile Template for Libraries
#

all-common: $(LIBRARY) $(PROGRAMS)

version.c: Makefile
	$(RM) $@
	$(MKVERSION) $(LIBRARY) > $@

version.o version.lo: version.c $(OBJS)

install-common: FORCE

lint: lint-local FORCE
	$(LINT) $(DEFS) $(DEFINES) $(SRCS)

lint5: lint5-local FORCE
	$(5LINT) $(DEFS) $(DEFINES) $(SRCS)

#
# In the mingw/cygwin environment, the so and dll files must be
# deleted separately, instead of using the {.so*,*.dll} construct
# that was previously used. It just didn't work.
#
clean-common: 	FORCE
	$(RM) $(LIBRARY) ../$(LIBRARY) $(XLIBRARY) \
		$(PROGRAMS) $(XPROGRAMS) $(XSRCS) $(XXSRCS) \
		*.o *.lo a.out *.exe core version.c .libs/*

depend-common: FORCE
	$(MKDEP) $(DEFS) $(DEFINES) $(SRCS) $(XXSRCS)

lint-local: FORCE
lint5-local: FORCE

Makefile: $(top_srcdir)/build/lib.mk

# $OpenLDAP$
## This work is part of OpenLDAP Software <http://www.openldap.org/>.
##
## Copyright 1998-2016 The OpenLDAP Foundation.
## All rights reserved.
##
## Redistribution and use in source and binary forms, with or without
## modification, are permitted only as authorized by the OpenLDAP
## Public License.
##
## A copy of this license is available in the file LICENSE in the
## top-level directory of the distribution or, alternatively, at
## <http://www.OpenLDAP.org/license.html>.
##---------------------------------------------------------------------------
#
# Makefile Template for Static Libraries
#

$(LIBRARY): version.o
	$(AR) ru $@ $(OBJS) version.o
	@$(RANLIB) $@

Makefile: $(top_srcdir)/build/lib-static.mk
# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.


#
# files: -I../../include -I../../include base64.c entropy.c sasl.c signal.c hash.c passfile.c md5.c passwd.c sha1.c getpass.c lockf.c utils.c uuid.c sockpair.c avl.c tavl.c testavl.c meter.c setproctitle.c getpeereid.c detach.c
# command: cc -M -I.  -I../../include -I../../include base64.c entropy.c sasl.c signal.c hash.c passfile.c md5.c passwd.c sha1.c getpass.c lockf.c utils.c uuid.c sockpair.c avl.c tavl.c testavl.c meter.c setproctitle.c getpeereid.c detach.c
#

base64.o: base64.c
base64.o: ../../include/portable.h
base64.o: /usr/lib/gcc/i686-linux-gnu/4.6/include/stddef.h
base64.o: ../../include/ac/fdset.h
base64.o: /usr/include/i386-linux-gnu/bits/types.h
base64.o: /usr/include/features.h
base64.o: /usr/include/i386-linux-gnu/bits/predefs.h
base64.o: /usr/include/i386-linux-gnu/sys/cdefs.h
base64.o: /usr/include/i386-linux-gnu/bits/wordsize.h
base64.o: /usr/include/i386-linux-gnu/gnu/stubs.h
base64.o: /usr/include/i386-linux-gnu/gnu/stubs-32.h
base64.o: /usr/include/i386-linux-gnu/bits/typesizes.h
base64.o: ../../include/ldap_cdefs.h
base64.o: ../../include/ldap_features.h
base64.o: ../../include/ac/assert.h
base64.o: /usr/include/assert.h
base64.o: ../../include/ac/localize.h
base64.o: ../../include/ac/assert.h
base64.o: ../../include/ac/stdlib.h
base64.o: /usr/include/stdlib.h
base64.o: /usr/include/i386-linux-gnu/bits/waitflags.h
base64.o: /usr/include/i386-linux-gnu/bits/waitstatus.h
base64.o: /usr/include/endian.h
base64.o: /usr/include/i386-linux-gnu/bits/endian.h
base64.o: /usr/include/i386-linux-gnu/bits/byteswap.h
base64.o: /usr/include/i386-linux-gnu/sys/types.h
base64.o: /usr/include/time.h
base64.o: /usr/include/i386-linux-gnu/sys/select.h
base64.o: /usr/include/i386-linux-gnu/bits/select.h
base64.o: /usr/include/i386-linux-gnu/bits/sigset.h
base64.o: /usr/include/i386-linux-gnu/bits/time.h
base64.o: /usr/include/i386-linux-gnu/sys/sysmacros.h
base64.o: /usr/include/i386-linux-gnu/bits/pthreadtypes.h
base64.o: /usr/include/alloca.h
base64.o: /usr/lib/gcc/i686-linux-gnu/4.6/include-fixed/limits.h
base64.o: /usr/lib/gcc/i686-linux-gnu/4.6/include-fixed/syslimits.h
base64.o: /usr/include/limits.h
base64.o: /usr/include/i386-linux-gnu/bits/posix1_lim.h
base64.o: /usr/include/i386-linux-gnu/bits/local_lim.h
base64.o: /usr/include/linux/limits.h
base64.o: /usr/include/i386-linux-gnu/bits/posix2_lim.h
base64.o: ../../include/ac/ctype.h
base64.o: /usr/include/ctype.h
base64.o: /usr/include/xlocale.h
base64.o: ../../include/ac/string.h
base64.o: /usr/include/string.h
base64.o: ../../include/ac/socket.h
base64.o: /usr/include/poll.h
base64.o: /usr/include/i386-linux-gnu/sys/poll.h
base64.o: /usr/include/i386-linux-gnu/bits/poll.h
base64.o: /usr/include/i386-linux-gnu/sys/socket.h
base64.o: /usr/include/i386-linux-gnu/sys/uio.h
base64.o: /usr/include/i386-linux-gnu/bits/uio.h
base64.o: /usr/include/i386-linux-gnu/bits/socket.h
base64.o: /usr/include/i386-linux-gnu/bits/sockaddr.h
base64.o: /usr/include/i386-linux-gnu/asm/socket.h
base64.o: /usr/include/asm-generic/socket.h
base64.o: /usr/include/i386-linux-gnu/asm/sockios.h
base64.o: /usr/include/asm-generic/sockios.h
base64.o: /usr/include/i386-linux-gnu/sys/un.h
base64.o: /usr/include/netinet/in.h
base64.o: /usr/lib/gcc/i686-linux-gnu/4.6/include/stdint.h
base64.o: /usr/include/stdint.h
base64.o: /usr/include/i386-linux-gnu/bits/wchar.h
base64.o: /usr/include/i386-linux-gnu/bits/in.h
base64.o: /usr/include/netinet/tcp.h
base64.o: /usr/include/arpa/inet.h
base64.o: /usr/include/arpa/nameser.h
base64.o: /usr/include/i386-linux-gnu/sys/param.h
base64.o: /usr/include/linux/param.h
base64.o: /usr/include/i386-linux-gnu/asm/param.h
base64.o: /usr/include/asm-generic/param.h
base64.o: /usr/include/i386-linux-gnu/sys/bitypes.h
base64.o: /usr/include/arpa/nameser_compat.h
base64.o: /usr/include/netdb.h
base64.o: /usr/include/rpc/netdb.h
base64.o: /usr/include/i386-linux-gnu/bits/netdb.h
base64.o: /usr/include/resolv.h
base64.o: /usr/include/stdio.h
base64.o: /usr/include/libio.h
base64.o: /usr/include/_G_config.h
base64.o: /usr/include/wchar.h
base64.o: /usr/lib/gcc/i686-linux-gnu/4.6/include/stdarg.h
base64.o: /usr/include/i386-linux-gnu/bits/stdio_lim.h
base64.o: /usr/include/i386-linux-gnu/bits/sys_errlist.h
base64.o: ../../include/lutil.h
base64.o: ../../include/ldap_cdefs.h
base64.o: ../../include/lber_types.h
entropy.o: entropy.c
entropy.o: ../../include/portable.h
entropy.o: /usr/lib/gcc/i686-linux-gnu/4.6/include/stddef.h
entropy.o: ../../include/ac/fdset.h
entropy.o: /usr/include/i386-linux-gnu/bits/types.h
entropy.o: /usr/include/features.h
entropy.o: /usr/include/i386-linux-gnu/bits/predefs.h
entropy.o: /usr/include/i386-linux-gnu/sys/cdefs.h
entropy.o: /usr/include/i386-linux-gnu/bits/wordsize.h
entropy.o: /usr/include/i386-linux-gnu/gnu/stubs.h
entropy.o: /usr/include/i386-linux-gnu/gnu/stubs-32.h
entropy.o: /usr/include/i386-linux-gnu/bits/typesizes.h
entropy.o: ../../include/ldap_cdefs.h
entropy.o: ../../include/ldap_features.h
entropy.o: ../../include/ac/assert.h
entropy.o: /usr/include/assert.h
entropy.o: ../../include/ac/localize.h
entropy.o: ../../include/ac/string.h
entropy.o: /usr/include/string.h
entropy.o: /usr/include/xlocale.h
entropy.o: ../../include/ac/time.h
entropy.o: /usr/include/i386-linux-gnu/sys/time.h
entropy.o: /usr/include/time.h
entropy.o: /usr/include/i386-linux-gnu/bits/time.h
entropy.o: /usr/include/i386-linux-gnu/sys/select.h
entropy.o: /usr/include/i386-linux-gnu/bits/select.h
entropy.o: /usr/include/i386-linux-gnu/bits/sigset.h
entropy.o: ../../include/ac/unistd.h
entropy.o: /usr/include/i386-linux-gnu/sys/types.h
entropy.o: /usr/include/endian.h
entropy.o: /usr/include/i386-linux-gnu/bits/endian.h
entropy.o: /usr/include/i386-linux-gnu/bits/byteswap.h
entropy.o: /usr/include/i386-linux-gnu/sys/sysmacros.h
entropy.o: /usr/include/i386-linux-gnu/bits/pthreadtypes.h
entropy.o: /usr/include/unistd.h
entropy.o: /usr/include/i386-linux-gnu/bits/posix_opt.h
entropy.o: /usr/include/i386-linux-gnu/bits/environments.h
entropy.o: /usr/include/i386-linux-gnu/bits/confname.h
entropy.o: /usr/include/getopt.h
entropy.o: ../../include/lutil_lockf.h
entropy.o: /usr/include/fcntl.h
entropy.o: /usr/include/i386-linux-gnu/bits/fcntl.h
entropy.o: /usr/include/i386-linux-gnu/bits/stat.h
entropy.o: ../../include/lutil.h
entropy.o: ../../include/ldap_cdefs.h
entropy.o: ../../include/lber_types.h
entropy.o: ../../include/lutil_md5.h
sasl.o: sasl.c
sasl.o: ../../include/portable.h
sasl.o: /usr/lib/gcc/i686-linux-gnu/4.6/include/stddef.h
sasl.o: ../../include/ac/fdset.h
sasl.o: /usr/include/i386-linux-gnu/bits/types.h
sasl.o: /usr/include/features.h
sasl.o: /usr/include/i386-linux-gnu/bits/predefs.h
sasl.o: /usr/include/i386-linux-gnu/sys/cdefs.h
sasl.o: /usr/include/i386-linux-gnu/bits/wordsize.h
sasl.o: /usr/include/i386-linux-gnu/gnu/stubs.h
sasl.o: /usr/include/i386-linux-gnu/gnu/stubs-32.h
sasl.o: /usr/include/i386-linux-gnu/bits/typesizes.h
sasl.o: ../../include/ldap_cdefs.h
sasl.o: ../../include/ldap_features.h
sasl.o: ../../include/ac/assert.h
sasl.o: /usr/include/assert.h
sasl.o: ../../include/ac/localize.h
signal.o: signal.c
signal.o: ../../include/portable.h
signal.o: /usr/lib/gcc/i686-linux-gnu/4.6/include/stddef.h
signal.o: ../../include/ac/fdset.h
signal.o: /usr/include/i386-linux-gnu/bits/types.h
signal.o: /usr/include/features.h
signal.o: /usr/include/i386-linux-gnu/bits/predefs.h
signal.o: /usr/include/i386-linux-gnu/sys/cdefs.h
signal.o: /usr/include/i386-linux-gnu/bits/wordsize.h
signal.o: /usr/include/i386-linux-gnu/gnu/stubs.h
signal.o: /usr/include/i386-linux-gnu/gnu/stubs-32.h
signal.o: /usr/include/i386-linux-gnu/bits/typesizes.h
signal.o: ../../include/ldap_cdefs.h
signal.o: ../../include/ldap_features.h
signal.o: ../../include/ac/assert.h
signal.o: /usr/include/assert.h
signal.o: ../../include/ac/localize.h
signal.o: ../../include/ac/string.h
signal.o: /usr/include/string.h
signal.o: /usr/include/xlocale.h
signal.o: ../../include/ac/signal.h
signal.o: /usr/include/signal.h
signal.o: /usr/include/i386-linux-gnu/bits/sigset.h
signal.o: /usr/include/i386-linux-gnu/bits/signum.h
signal.o: /usr/include/time.h
signal.o: /usr/include/i386-linux-gnu/bits/siginfo.h
signal.o: /usr/include/i386-linux-gnu/bits/sigaction.h
signal.o: /usr/include/i386-linux-gnu/bits/sigcontext.h
signal.o: /usr/include/i386-linux-gnu/asm/sigcontext.h
signal.o: /usr/include/linux/types.h
signal.o: /usr/include/i386-linux-gnu/asm/types.h
signal.o: /usr/include/asm-generic/types.h
signal.o: /usr/include/asm-generic/int-ll64.h
signal.o: /usr/include/i386-linux-gnu/asm/bitsperlong.h
signal.o: /usr/include/asm-generic/bitsperlong.h
signal.o: /usr/include/linux/posix_types.h
signal.o: /usr/include/linux/stddef.h
signal.o: /usr/include/i386-linux-gnu/asm/posix_types.h
signal.o: /usr/include/i386-linux-gnu/asm/posix_types_32.h
signal.o: /usr/include/i386-linux-gnu/bits/sigstack.h
signal.o: /usr/include/i386-linux-gnu/sys/ucontext.h
signal.o: /usr/include/i386-linux-gnu/bits/pthreadtypes.h
signal.o: /usr/include/i386-linux-gnu/bits/sigthread.h
hash.o: hash.c
hash.o: ../../include/portable.h
hash.o: /usr/lib/gcc/i686-linux-gnu/4.6/include/stddef.h
hash.o: ../../include/ac/fdset.h
hash.o: /usr/include/i386-linux-gnu/bits/types.h
hash.o: /usr/include/features.h
hash.o: /usr/include/i386-linux-gnu/bits/predefs.h
hash.o: /usr/include/i386-linux-gnu/sys/cdefs.h
hash.o: /usr/include/i386-linux-gnu/bits/wordsize.h
hash.o: /usr/include/i386-linux-gnu/gnu/stubs.h
hash.o: /usr/include/i386-linux-gnu/gnu/stubs-32.h
hash.o: /usr/include/i386-linux-gnu/bits/typesizes.h
hash.o: ../../include/ldap_cdefs.h
hash.o: ../../include/ldap_features.h
hash.o: ../../include/ac/assert.h
hash.o: /usr/include/assert.h
hash.o: ../../include/ac/localize.h
hash.o: ../../include/lutil_hash.h
hash.o: ../../include/lber_types.h
hash.o: ../../include/ldap_cdefs.h
passfile.o: passfile.c
passfile.o: ../../include/portable.h
passfile.o: /usr/lib/gcc/i686-linux-gnu/4.6/include/stddef.h
passfile.o: ../../include/ac/fdset.h
passfile.o: /usr/include/i386-linux-gnu/bits/types.h
passfile.o: /usr/include/features.h
passfile.o: /usr/include/i386-linux-gnu/bits/predefs.h
passfile.o: /usr/include/i386-linux-gnu/sys/cdefs.h
passfile.o: /usr/include/i386-linux-gnu/bits/wordsize.h
passfile.o: /usr/include/i386-linux-gnu/gnu/stubs.h
passfile.o: /usr/include/i386-linux-gnu/gnu/stubs-32.h
passfile.o: /usr/include/i386-linux-gnu/bits/typesizes.h
passfile.o: ../../include/ldap_cdefs.h
passfile.o: ../../include/ldap_features.h
passfile.o: ../../include/ac/assert.h
passfile.o: /usr/include/assert.h
passfile.o: ../../include/ac/localize.h
passfile.o: /usr/include/stdio.h
passfile.o: /usr/include/libio.h
passfile.o: /usr/include/_G_config.h
passfile.o: /usr/include/wchar.h
passfile.o: /usr/lib/gcc/i686-linux-gnu/4.6/include/stdarg.h
passfile.o: /usr/include/i386-linux-gnu/bits/stdio_lim.h
passfile.o: /usr/include/i386-linux-gnu/bits/sys_errlist.h
passfile.o: ../../include/ac/stdlib.h
passfile.o: /usr/include/stdlib.h
passfile.o: /usr/include/i386-linux-gnu/bits/waitflags.h
passfile.o: /usr/include/i386-linux-gnu/bits/waitstatus.h
passfile.o: /usr/include/endian.h
passfile.o: /usr/include/i386-linux-gnu/bits/endian.h
passfile.o: /usr/include/i386-linux-gnu/bits/byteswap.h
passfile.o: /usr/include/i386-linux-gnu/sys/types.h
passfile.o: /usr/include/time.h
passfile.o: /usr/include/i386-linux-gnu/sys/select.h
passfile.o: /usr/include/i386-linux-gnu/bits/select.h
passfile.o: /usr/include/i386-linux-gnu/bits/sigset.h
passfile.o: /usr/include/i386-linux-gnu/bits/time.h
passfile.o: /usr/include/i386-linux-gnu/sys/sysmacros.h
passfile.o: /usr/include/i386-linux-gnu/bits/pthreadtypes.h
passfile.o: /usr/include/alloca.h
passfile.o: /usr/lib/gcc/i686-linux-gnu/4.6/include-fixed/limits.h
passfile.o: /usr/lib/gcc/i686-linux-gnu/4.6/include-fixed/syslimits.h
passfile.o: /usr/include/limits.h
passfile.o: /usr/include/i386-linux-gnu/bits/posix1_lim.h
passfile.o: /usr/include/i386-linux-gnu/bits/local_lim.h
passfile.o: /usr/include/linux/limits.h
passfile.o: /usr/include/i386-linux-gnu/bits/posix2_lim.h
passfile.o: ../../include/ac/ctype.h
passfile.o: /usr/include/ctype.h
passfile.o: /usr/include/xlocale.h
passfile.o: ../../include/ac/string.h
passfile.o: /usr/include/string.h
passfile.o: /usr/include/i386-linux-gnu/sys/stat.h
passfile.o: /usr/include/i386-linux-gnu/bits/stat.h
passfile.o: ../../include/lber.h
passfile.o: ../../include/lber_types.h
passfile.o: ../../include/ldap_cdefs.h
passfile.o: ../../include/lutil.h
md5.o: md5.c
md5.o: ../../include/portable.h
md5.o: /usr/lib/gcc/i686-linux-gnu/4.6/include/stddef.h
md5.o: ../../include/ac/fdset.h
md5.o: /usr/include/i386-linux-gnu/bits/types.h
md5.o: /usr/include/features.h
md5.o: /usr/include/i386-linux-gnu/bits/predefs.h
md5.o: /usr/include/i386-linux-gnu/sys/cdefs.h
md5.o: /usr/include/i386-linux-gnu/bits/wordsize.h
md5.o: /usr/include/i386-linux-gnu/gnu/stubs.h
md5.o: /usr/include/i386-linux-gnu/gnu/stubs-32.h
md5.o: /usr/include/i386-linux-gnu/bits/typesizes.h
md5.o: ../../include/ldap_cdefs.h
md5.o: ../../include/ldap_features.h
md5.o: ../../include/ac/assert.h
md5.o: /usr/include/assert.h
md5.o: ../../include/ac/localize.h
md5.o: ../../include/ac/string.h
md5.o: /usr/include/string.h
md5.o: /usr/include/xlocale.h
md5.o: ../../include/ac/socket.h
md5.o: /usr/include/i386-linux-gnu/sys/types.h
md5.o: /usr/include/time.h
md5.o: /usr/include/endian.h
md5.o: /usr/include/i386-linux-gnu/bits/endian.h
md5.o: /usr/include/i386-linux-gnu/bits/byteswap.h
md5.o: /usr/include/i386-linux-gnu/sys/select.h
md5.o: /usr/include/i386-linux-gnu/bits/select.h
md5.o: /usr/include/i386-linux-gnu/bits/sigset.h
md5.o: /usr/include/i386-linux-gnu/bits/time.h
md5.o: /usr/include/i386-linux-gnu/sys/sysmacros.h
md5.o: /usr/include/i386-linux-gnu/bits/pthreadtypes.h
md5.o: /usr/include/poll.h
md5.o: /usr/include/i386-linux-gnu/sys/poll.h
md5.o: /usr/include/i386-linux-gnu/bits/poll.h
md5.o: /usr/include/i386-linux-gnu/sys/socket.h
md5.o: /usr/include/i386-linux-gnu/sys/uio.h
md5.o: /usr/include/i386-linux-gnu/bits/uio.h
md5.o: /usr/include/i386-linux-gnu/bits/socket.h
md5.o: /usr/include/i386-linux-gnu/bits/sockaddr.h
md5.o: /usr/include/i386-linux-gnu/asm/socket.h
md5.o: /usr/include/asm-generic/socket.h
md5.o: /usr/include/i386-linux-gnu/asm/sockios.h
md5.o: /usr/include/asm-generic/sockios.h
md5.o: /usr/include/i386-linux-gnu/sys/un.h
md5.o: /usr/include/netinet/in.h
md5.o: /usr/lib/gcc/i686-linux-gnu/4.6/include/stdint.h
md5.o: /usr/include/stdint.h
md5.o: /usr/include/i386-linux-gnu/bits/wchar.h
md5.o: /usr/include/i386-linux-gnu/bits/in.h
md5.o: /usr/include/netinet/tcp.h
md5.o: /usr/include/arpa/inet.h
md5.o: /usr/include/arpa/nameser.h
md5.o: /usr/include/i386-linux-gnu/sys/param.h
md5.o: /usr/lib/gcc/i686-linux-gnu/4.6/include-fixed/limits.h
md5.o: /usr/lib/gcc/i686-linux-gnu/4.6/include-fixed/syslimits.h
md5.o: /usr/include/limits.h
md5.o: /usr/include/i386-linux-gnu/bits/posix1_lim.h
md5.o: /usr/include/i386-linux-gnu/bits/local_lim.h
md5.o: /usr/include/linux/limits.h
md5.o: /usr/include/i386-linux-gnu/bits/posix2_lim.h
md5.o: /usr/include/linux/param.h
md5.o: /usr/include/i386-linux-gnu/asm/param.h
md5.o: /usr/include/asm-generic/param.h
md5.o: /usr/include/i386-linux-gnu/sys/bitypes.h
md5.o: /usr/include/arpa/nameser_compat.h
md5.o: /usr/include/netdb.h
md5.o: /usr/include/rpc/netdb.h
md5.o: /usr/include/i386-linux-gnu/bits/netdb.h
md5.o: /usr/include/resolv.h
md5.o: /usr/include/stdio.h
md5.o: /usr/include/libio.h
md5.o: /usr/include/_G_config.h
md5.o: /usr/include/wchar.h
md5.o: /usr/lib/gcc/i686-linux-gnu/4.6/include/stdarg.h
md5.o: /usr/include/i386-linux-gnu/bits/stdio_lim.h
md5.o: /usr/include/i386-linux-gnu/bits/sys_errlist.h
md5.o: ../../include/lutil_md5.h
md5.o: ../../include/lber_types.h
md5.o: ../../include/ldap_cdefs.h
passwd.o: passwd.c
passwd.o: ../../include/portable.h
passwd.o: /usr/lib/gcc/i686-linux-gnu/4.6/include/stddef.h
passwd.o: ../../include/ac/fdset.h
passwd.o: /usr/include/i386-linux-gnu/bits/types.h
passwd.o: /usr/include/features.h
passwd.o: /usr/include/i386-linux-gnu/bits/predefs.h
passwd.o: /usr/include/i386-linux-gnu/sys/cdefs.h
passwd.o: /usr/include/i386-linux-gnu/bits/wordsize.h
passwd.o: /usr/include/i386-linux-gnu/gnu/stubs.h
passwd.o: /usr/include/i386-linux-gnu/gnu/stubs-32.h
passwd.o: /usr/include/i386-linux-gnu/bits/typesizes.h
passwd.o: ../../include/ldap_cdefs.h
passwd.o: ../../include/ldap_features.h
passwd.o: ../../include/ac/assert.h
passwd.o: /usr/include/assert.h
passwd.o: ../../include/ac/localize.h
passwd.o: /usr/include/stdio.h
passwd.o: /usr/include/libio.h
passwd.o: /usr/include/_G_config.h
passwd.o: /usr/include/wchar.h
passwd.o: /usr/lib/gcc/i686-linux-gnu/4.6/include/stdarg.h
passwd.o: /usr/include/i386-linux-gnu/bits/stdio_lim.h
passwd.o: /usr/include/i386-linux-gnu/bits/sys_errlist.h
passwd.o: ../../include/ac/stdlib.h
passwd.o: /usr/include/stdlib.h
passwd.o: /usr/include/i386-linux-gnu/bits/waitflags.h
passwd.o: /usr/include/i386-linux-gnu/bits/waitstatus.h
passwd.o: /usr/include/endian.h
passwd.o: /usr/include/i386-linux-gnu/bits/endian.h
passwd.o: /usr/include/i386-linux-gnu/bits/byteswap.h
passwd.o: /usr/include/i386-linux-gnu/sys/types.h
passwd.o: /usr/include/time.h
passwd.o: /usr/include/i386-linux-gnu/sys/select.h
passwd.o: /usr/include/i386-linux-gnu/bits/select.h
passwd.o: /usr/include/i386-linux-gnu/bits/sigset.h
passwd.o: /usr/include/i386-linux-gnu/bits/time.h
passwd.o: /usr/include/i386-linux-gnu/sys/sysmacros.h
passwd.o: /usr/include/i386-linux-gnu/bits/pthreadtypes.h
passwd.o: /usr/include/alloca.h
passwd.o: /usr/lib/gcc/i686-linux-gnu/4.6/include-fixed/limits.h
passwd.o: /usr/lib/gcc/i686-linux-gnu/4.6/include-fixed/syslimits.h
passwd.o: /usr/include/limits.h
passwd.o: /usr/include/i386-linux-gnu/bits/posix1_lim.h
passwd.o: /usr/include/i386-linux-gnu/bits/local_lim.h
passwd.o: /usr/include/linux/limits.h
passwd.o: /usr/include/i386-linux-gnu/bits/posix2_lim.h
passwd.o: ../../include/ac/string.h
passwd.o: /usr/include/string.h
passwd.o: /usr/include/xlocale.h
passwd.o: ../../include/ac/unistd.h
passwd.o: /usr/include/unistd.h
passwd.o: /usr/include/i386-linux-gnu/bits/posix_opt.h
passwd.o: /usr/include/i386-linux-gnu/bits/environments.h
passwd.o: /usr/include/i386-linux-gnu/bits/confname.h
passwd.o: /usr/include/getopt.h
passwd.o: ../../include/lutil_lockf.h
passwd.o: ../../include/ac/param.h
passwd.o: /usr/include/i386-linux-gnu/sys/param.h
passwd.o: /usr/include/linux/param.h
passwd.o: /usr/include/i386-linux-gnu/asm/param.h
passwd.o: /usr/include/asm-generic/param.h
passwd.o: ../../include/lber.h
passwd.o: ../../include/lber_types.h
passwd.o: ../../include/ldap_cdefs.h
passwd.o: ../../include/ldap_pvt.h
passwd.o: ../../include/lber_pvt.h
passwd.o: ../../include/ldap_pvt_uc.h
passwd.o: ../../include/ac/bytes.h
passwd.o: ../../include/../libraries/liblunicode/ucdata/ucdata.h
passwd.o: ../../include/lutil_md5.h
passwd.o: ../../include/lutil_sha1.h
passwd.o: ../../include/lutil.h
sha1.o: sha1.c
sha1.o: ../../include/portable.h
sha1.o: /usr/lib/gcc/i686-linux-gnu/4.6/include/stddef.h
sha1.o: ../../include/ac/fdset.h
sha1.o: /usr/include/i386-linux-gnu/bits/types.h
sha1.o: /usr/include/features.h
sha1.o: /usr/include/i386-linux-gnu/bits/predefs.h
sha1.o: /usr/include/i386-linux-gnu/sys/cdefs.h
sha1.o: /usr/include/i386-linux-gnu/bits/wordsize.h
sha1.o: /usr/include/i386-linux-gnu/gnu/stubs.h
sha1.o: /usr/include/i386-linux-gnu/gnu/stubs-32.h
sha1.o: /usr/include/i386-linux-gnu/bits/typesizes.h
sha1.o: ../../include/ldap_cdefs.h
sha1.o: ../../include/ldap_features.h
sha1.o: ../../include/ac/assert.h
sha1.o: /usr/include/assert.h
sha1.o: ../../include/ac/localize.h
sha1.o: ../../include/ac/param.h
sha1.o: /usr/include/i386-linux-gnu/sys/param.h
sha1.o: /usr/lib/gcc/i686-linux-gnu/4.6/include-fixed/limits.h
sha1.o: /usr/lib/gcc/i686-linux-gnu/4.6/include-fixed/syslimits.h
sha1.o: /usr/include/limits.h
sha1.o: /usr/include/i386-linux-gnu/bits/posix1_lim.h
sha1.o: /usr/include/i386-linux-gnu/bits/local_lim.h
sha1.o: /usr/include/linux/limits.h
sha1.o: /usr/include/i386-linux-gnu/bits/posix2_lim.h
sha1.o: /usr/include/linux/param.h
sha1.o: /usr/include/i386-linux-gnu/asm/param.h
sha1.o: /usr/include/asm-generic/param.h
sha1.o: /usr/include/i386-linux-gnu/sys/types.h
sha1.o: /usr/include/time.h
sha1.o: /usr/include/endian.h
sha1.o: /usr/include/i386-linux-gnu/bits/endian.h
sha1.o: /usr/include/i386-linux-gnu/bits/byteswap.h
sha1.o: /usr/include/i386-linux-gnu/sys/select.h
sha1.o: /usr/include/i386-linux-gnu/bits/select.h
sha1.o: /usr/include/i386-linux-gnu/bits/sigset.h
sha1.o: /usr/include/i386-linux-gnu/bits/time.h
sha1.o: /usr/include/i386-linux-gnu/sys/sysmacros.h
sha1.o: /usr/include/i386-linux-gnu/bits/pthreadtypes.h
sha1.o: ../../include/ac/unistd.h
sha1.o: /usr/include/unistd.h
sha1.o: /usr/include/i386-linux-gnu/bits/posix_opt.h
sha1.o: /usr/include/i386-linux-gnu/bits/environments.h
sha1.o: /usr/include/i386-linux-gnu/bits/confname.h
sha1.o: /usr/include/getopt.h
sha1.o: ../../include/lutil_lockf.h
sha1.o: ../../include/ac/string.h
sha1.o: /usr/include/string.h
sha1.o: /usr/include/xlocale.h
sha1.o: ../../include/ac/socket.h
sha1.o: /usr/include/poll.h
sha1.o: /usr/include/i386-linux-gnu/sys/poll.h
sha1.o: /usr/include/i386-linux-gnu/bits/poll.h
sha1.o: /usr/include/i386-linux-gnu/sys/socket.h
sha1.o: /usr/include/i386-linux-gnu/sys/uio.h
sha1.o: /usr/include/i386-linux-gnu/bits/uio.h
sha1.o: /usr/include/i386-linux-gnu/bits/socket.h
sha1.o: /usr/include/i386-linux-gnu/bits/sockaddr.h
sha1.o: /usr/include/i386-linux-gnu/asm/socket.h
sha1.o: /usr/include/asm-generic/socket.h
sha1.o: /usr/include/i386-linux-gnu/asm/sockios.h
sha1.o: /usr/include/asm-generic/sockios.h
sha1.o: /usr/include/i386-linux-gnu/sys/un.h
sha1.o: /usr/include/netinet/in.h
sha1.o: /usr/lib/gcc/i686-linux-gnu/4.6/include/stdint.h
sha1.o: /usr/include/stdint.h
sha1.o: /usr/include/i386-linux-gnu/bits/wchar.h
sha1.o: /usr/include/i386-linux-gnu/bits/in.h
sha1.o: /usr/include/netinet/tcp.h
sha1.o: /usr/include/arpa/inet.h
sha1.o: /usr/include/arpa/nameser.h
sha1.o: /usr/include/i386-linux-gnu/sys/bitypes.h
sha1.o: /usr/include/arpa/nameser_compat.h
sha1.o: /usr/include/netdb.h
sha1.o: /usr/include/rpc/netdb.h
sha1.o: /usr/include/i386-linux-gnu/bits/netdb.h
sha1.o: /usr/include/resolv.h
sha1.o: /usr/include/stdio.h
sha1.o: /usr/include/libio.h
sha1.o: /usr/include/_G_config.h
sha1.o: /usr/include/wchar.h
sha1.o: /usr/lib/gcc/i686-linux-gnu/4.6/include/stdarg.h
sha1.o: /usr/include/i386-linux-gnu/bits/stdio_lim.h
sha1.o: /usr/include/i386-linux-gnu/bits/sys_errlist.h
sha1.o: ../../include/ac/bytes.h
sha1.o: ../../include/lutil_sha1.h
sha1.o: ../../include/ldap_cdefs.h
sha1.o: ../../include/ac/stdlib.h
sha1.o: /usr/include/stdlib.h
sha1.o: /usr/include/i386-linux-gnu/bits/waitflags.h
sha1.o: /usr/include/i386-linux-gnu/bits/waitstatus.h
sha1.o: /usr/include/alloca.h
sha1.o: ../../include/ac/errno.h
sha1.o: /usr/include/errno.h
sha1.o: /usr/include/i386-linux-gnu/bits/errno.h
sha1.o: /usr/include/linux/errno.h
sha1.o: /usr/include/i386-linux-gnu/asm/errno.h
sha1.o: /usr/include/asm-generic/errno.h
sha1.o: /usr/include/asm-generic/errno-base.h
sha1.o: /usr/include/i386-linux-gnu/sys/file.h
sha1.o: /usr/include/fcntl.h
sha1.o: /usr/include/i386-linux-gnu/bits/fcntl.h
sha1.o: /usr/include/i386-linux-gnu/bits/stat.h
getpass.o: getpass.c
getpass.o: ../../include/portable.h
getpass.o: /usr/lib/gcc/i686-linux-gnu/4.6/include/stddef.h
getpass.o: ../../include/ac/fdset.h
getpass.o: /usr/include/i386-linux-gnu/bits/types.h
getpass.o: /usr/include/features.h
getpass.o: /usr/include/i386-linux-gnu/bits/predefs.h
getpass.o: /usr/include/i386-linux-gnu/sys/cdefs.h
getpass.o: /usr/include/i386-linux-gnu/bits/wordsize.h
getpass.o: /usr/include/i386-linux-gnu/gnu/stubs.h
getpass.o: /usr/include/i386-linux-gnu/gnu/stubs-32.h
getpass.o: /usr/include/i386-linux-gnu/bits/typesizes.h
getpass.o: ../../include/ldap_cdefs.h
getpass.o: ../../include/ldap_features.h
getpass.o: ../../include/ac/assert.h
getpass.o: /usr/include/assert.h
getpass.o: ../../include/ac/localize.h
getpass.o: /usr/include/stdio.h
getpass.o: /usr/include/libio.h
getpass.o: /usr/include/_G_config.h
getpass.o: /usr/include/wchar.h
getpass.o: /usr/lib/gcc/i686-linux-gnu/4.6/include/stdarg.h
getpass.o: /usr/include/i386-linux-gnu/bits/stdio_lim.h
getpass.o: /usr/include/i386-linux-gnu/bits/sys_errlist.h
getpass.o: ../../include/ac/stdlib.h
getpass.o: /usr/include/stdlib.h
getpass.o: /usr/include/i386-linux-gnu/bits/waitflags.h
getpass.o: /usr/include/i386-linux-gnu/bits/waitstatus.h
getpass.o: /usr/include/endian.h
getpass.o: /usr/include/i386-linux-gnu/bits/endian.h
getpass.o: /usr/include/i386-linux-gnu/bits/byteswap.h
getpass.o: /usr/include/i386-linux-gnu/sys/types.h
getpass.o: /usr/include/time.h
getpass.o: /usr/include/i386-linux-gnu/sys/select.h
getpass.o: /usr/include/i386-linux-gnu/bits/select.h
getpass.o: /usr/include/i386-linux-gnu/bits/sigset.h
getpass.o: /usr/include/i386-linux-gnu/bits/time.h
getpass.o: /usr/include/i386-linux-gnu/sys/sysmacros.h
getpass.o: /usr/include/i386-linux-gnu/bits/pthreadtypes.h
getpass.o: /usr/include/alloca.h
getpass.o: /usr/lib/gcc/i686-linux-gnu/4.6/include-fixed/limits.h
getpass.o: /usr/lib/gcc/i686-linux-gnu/4.6/include-fixed/syslimits.h
getpass.o: /usr/include/limits.h
getpass.o: /usr/include/i386-linux-gnu/bits/posix1_lim.h
getpass.o: /usr/include/i386-linux-gnu/bits/local_lim.h
getpass.o: /usr/include/linux/limits.h
getpass.o: /usr/include/i386-linux-gnu/bits/posix2_lim.h
getpass.o: ../../include/ac/ctype.h
getpass.o: /usr/include/ctype.h
getpass.o: /usr/include/xlocale.h
getpass.o: ../../include/ac/signal.h
getpass.o: /usr/include/signal.h
getpass.o: /usr/include/i386-linux-gnu/bits/signum.h
getpass.o: /usr/include/i386-linux-gnu/bits/siginfo.h
getpass.o: /usr/include/i386-linux-gnu/bits/sigaction.h
getpass.o: /usr/include/i386-linux-gnu/bits/sigcontext.h
getpass.o: /usr/include/i386-linux-gnu/asm/sigcontext.h
getpass.o: /usr/include/linux/types.h
getpass.o: /usr/include/i386-linux-gnu/asm/types.h
getpass.o: /usr/include/asm-generic/types.h
getpass.o: /usr/include/asm-generic/int-ll64.h
getpass.o: /usr/include/i386-linux-gnu/asm/bitsperlong.h
getpass.o: /usr/include/asm-generic/bitsperlong.h
getpass.o: /usr/include/linux/posix_types.h
getpass.o: /usr/include/linux/stddef.h
getpass.o: /usr/include/i386-linux-gnu/asm/posix_types.h
getpass.o: /usr/include/i386-linux-gnu/asm/posix_types_32.h
getpass.o: /usr/include/i386-linux-gnu/bits/sigstack.h
getpass.o: /usr/include/i386-linux-gnu/sys/ucontext.h
getpass.o: /usr/include/i386-linux-gnu/bits/sigthread.h
getpass.o: ../../include/ac/string.h
getpass.o: /usr/include/string.h
getpass.o: ../../include/ac/termios.h
getpass.o: /usr/include/termios.h
getpass.o: /usr/include/i386-linux-gnu/bits/termios.h
getpass.o: /usr/include/i386-linux-gnu/sys/ttydefaults.h
getpass.o: ../../include/ac/time.h
getpass.o: /usr/include/i386-linux-gnu/sys/time.h
getpass.o: ../../include/ac/unistd.h
getpass.o: /usr/include/unistd.h
getpass.o: /usr/include/i386-linux-gnu/bits/posix_opt.h
getpass.o: /usr/include/i386-linux-gnu/bits/environments.h
getpass.o: /usr/include/i386-linux-gnu/bits/confname.h
getpass.o: /usr/include/getopt.h
getpass.o: ../../include/lutil_lockf.h
getpass.o: /usr/include/fcntl.h
getpass.o: /usr/include/i386-linux-gnu/bits/fcntl.h
getpass.o: /usr/include/i386-linux-gnu/bits/stat.h
getpass.o: ../../include/lber.h
getpass.o: ../../include/lber_types.h
getpass.o: ../../include/ldap_cdefs.h
getpass.o: ../../include/ldap.h
getpass.o: ../../include/ldap_features.h
getpass.o: ../../include/ldap_defaults.h
getpass.o: ../../include/ldap_config.h
lockf.o: lockf.c
lockf.o: ../../include/portable.h
lockf.o: /usr/lib/gcc/i686-linux-gnu/4.6/include/stddef.h
lockf.o: ../../include/ac/fdset.h
lockf.o: /usr/include/i386-linux-gnu/bits/types.h
lockf.o: /usr/include/features.h
lockf.o: /usr/include/i386-linux-gnu/bits/predefs.h
lockf.o: /usr/include/i386-linux-gnu/sys/cdefs.h
lockf.o: /usr/include/i386-linux-gnu/bits/wordsize.h
lockf.o: /usr/include/i386-linux-gnu/gnu/stubs.h
lockf.o: /usr/include/i386-linux-gnu/gnu/stubs-32.h
lockf.o: /usr/include/i386-linux-gnu/bits/typesizes.h
lockf.o: ../../include/ldap_cdefs.h
lockf.o: ../../include/ldap_features.h
lockf.o: ../../include/ac/assert.h
lockf.o: /usr/include/assert.h
lockf.o: ../../include/ac/localize.h
lockf.o: /usr/include/stdio.h
lockf.o: /usr/include/libio.h
lockf.o: /usr/include/_G_config.h
lockf.o: /usr/include/wchar.h
lockf.o: /usr/lib/gcc/i686-linux-gnu/4.6/include/stdarg.h
lockf.o: /usr/include/i386-linux-gnu/bits/stdio_lim.h
lockf.o: /usr/include/i386-linux-gnu/bits/sys_errlist.h
lockf.o: ../../include/ac/unistd.h
lockf.o: /usr/include/i386-linux-gnu/sys/types.h
lockf.o: /usr/include/time.h
lockf.o: /usr/include/endian.h
lockf.o: /usr/include/i386-linux-gnu/bits/endian.h
lockf.o: /usr/include/i386-linux-gnu/bits/byteswap.h
lockf.o: /usr/include/i386-linux-gnu/sys/select.h
lockf.o: /usr/include/i386-linux-gnu/bits/select.h
lockf.o: /usr/include/i386-linux-gnu/bits/sigset.h
lockf.o: /usr/include/i386-linux-gnu/bits/time.h
lockf.o: /usr/include/i386-linux-gnu/sys/sysmacros.h
lockf.o: /usr/include/i386-linux-gnu/bits/pthreadtypes.h
lockf.o: /usr/include/unistd.h
lockf.o: /usr/include/i386-linux-gnu/bits/posix_opt.h
lockf.o: /usr/include/i386-linux-gnu/bits/environments.h
lockf.o: /usr/include/i386-linux-gnu/bits/confname.h
lockf.o: /usr/include/getopt.h
lockf.o: ../../include/lutil_lockf.h
utils.o: utils.c
utils.o: ../../include/portable.h
utils.o: /usr/lib/gcc/i686-linux-gnu/4.6/include/stddef.h
utils.o: ../../include/ac/fdset.h
utils.o: /usr/include/i386-linux-gnu/bits/types.h
utils.o: /usr/include/features.h
utils.o: /usr/include/i386-linux-gnu/bits/predefs.h
utils.o: /usr/include/i386-linux-gnu/sys/cdefs.h
utils.o: /usr/include/i386-linux-gnu/bits/wordsize.h
utils.o: /usr/include/i386-linux-gnu/gnu/stubs.h
utils.o: /usr/include/i386-linux-gnu/gnu/stubs-32.h
utils.o: /usr/include/i386-linux-gnu/bits/typesizes.h
utils.o: ../../include/ldap_cdefs.h
utils.o: ../../include/ldap_features.h
utils.o: ../../include/ac/assert.h
utils.o: /usr/include/assert.h
utils.o: ../../include/ac/localize.h
utils.o: /usr/lib/gcc/i686-linux-gnu/4.6/include-fixed/limits.h
utils.o: /usr/lib/gcc/i686-linux-gnu/4.6/include-fixed/syslimits.h
utils.o: /usr/include/limits.h
utils.o: /usr/include/i386-linux-gnu/bits/posix1_lim.h
utils.o: /usr/include/i386-linux-gnu/bits/local_lim.h
utils.o: /usr/include/linux/limits.h
utils.o: /usr/include/i386-linux-gnu/bits/posix2_lim.h
utils.o: /usr/include/stdio.h
utils.o: /usr/include/libio.h
utils.o: /usr/include/_G_config.h
utils.o: /usr/include/wchar.h
utils.o: /usr/lib/gcc/i686-linux-gnu/4.6/include/stdarg.h
utils.o: /usr/include/i386-linux-gnu/bits/stdio_lim.h
utils.o: /usr/include/i386-linux-gnu/bits/sys_errlist.h
utils.o: ../../include/ac/stdlib.h
utils.o: /usr/include/stdlib.h
utils.o: /usr/include/i386-linux-gnu/bits/waitflags.h
utils.o: /usr/include/i386-linux-gnu/bits/waitstatus.h
utils.o: /usr/include/endian.h
utils.o: /usr/include/i386-linux-gnu/bits/endian.h
utils.o: /usr/include/i386-linux-gnu/bits/byteswap.h
utils.o: /usr/include/i386-linux-gnu/sys/types.h
utils.o: /usr/include/time.h
utils.o: /usr/include/i386-linux-gnu/sys/select.h
utils.o: /usr/include/i386-linux-gnu/bits/select.h
utils.o: /usr/include/i386-linux-gnu/bits/sigset.h
utils.o: /usr/include/i386-linux-gnu/bits/time.h
utils.o: /usr/include/i386-linux-gnu/sys/sysmacros.h
utils.o: /usr/include/i386-linux-gnu/bits/pthreadtypes.h
utils.o: /usr/include/alloca.h
utils.o: ../../include/ac/stdarg.h
utils.o: ../../include/ac/string.h
utils.o: /usr/include/string.h
utils.o: /usr/include/xlocale.h
utils.o: ../../include/ac/ctype.h
utils.o: /usr/include/ctype.h
utils.o: ../../include/ac/unistd.h
utils.o: /usr/include/unistd.h
utils.o: /usr/include/i386-linux-gnu/bits/posix_opt.h
utils.o: /usr/include/i386-linux-gnu/bits/environments.h
utils.o: /usr/include/i386-linux-gnu/bits/confname.h
utils.o: /usr/include/getopt.h
utils.o: ../../include/lutil_lockf.h
utils.o: ../../include/ac/time.h
utils.o: /usr/include/i386-linux-gnu/sys/time.h
utils.o: ../../include/ac/errno.h
utils.o: /usr/include/errno.h
utils.o: /usr/include/i386-linux-gnu/bits/errno.h
utils.o: /usr/include/linux/errno.h
utils.o: /usr/include/i386-linux-gnu/asm/errno.h
utils.o: /usr/include/asm-generic/errno.h
utils.o: /usr/include/asm-generic/errno-base.h
utils.o: /usr/include/fcntl.h
utils.o: /usr/include/i386-linux-gnu/bits/fcntl.h
utils.o: /usr/include/i386-linux-gnu/bits/stat.h
utils.o: ../../include/lutil.h
utils.o: ../../include/ldap_cdefs.h
utils.o: ../../include/lber_types.h
utils.o: ../../include/ldap_defaults.h
utils.o: ../../include/ldap_config.h
utils.o: ../../include/ldap_pvt.h
utils.o: ../../include/lber.h
utils.o: ../../include/lber_pvt.h
utils.o: ../../include/ldap_pvt_uc.h
utils.o: ../../include/ac/bytes.h
utils.o: ../../include/../libraries/liblunicode/ucdata/ucdata.h
uuid.o: uuid.c
uuid.o: ../../include/portable.h
uuid.o: /usr/lib/gcc/i686-linux-gnu/4.6/include/stddef.h
uuid.o: ../../include/ac/fdset.h
uuid.o: /usr/include/i386-linux-gnu/bits/types.h
uuid.o: /usr/include/features.h
uuid.o: /usr/include/i386-linux-gnu/bits/predefs.h
uuid.o: /usr/include/i386-linux-gnu/sys/cdefs.h
uuid.o: /usr/include/i386-linux-gnu/bits/wordsize.h
uuid.o: /usr/include/i386-linux-gnu/gnu/stubs.h
uuid.o: /usr/include/i386-linux-gnu/gnu/stubs-32.h
uuid.o: /usr/include/i386-linux-gnu/bits/typesizes.h
uuid.o: ../../include/ldap_cdefs.h
uuid.o: ../../include/ldap_features.h
uuid.o: ../../include/ac/assert.h
uuid.o: /usr/include/assert.h
uuid.o: ../../include/ac/localize.h
uuid.o: /usr/lib/gcc/i686-linux-gnu/4.6/include-fixed/limits.h
uuid.o: /usr/lib/gcc/i686-linux-gnu/4.6/include-fixed/syslimits.h
uuid.o: /usr/include/limits.h
uuid.o: /usr/include/i386-linux-gnu/bits/posix1_lim.h
uuid.o: /usr/include/i386-linux-gnu/bits/local_lim.h
uuid.o: /usr/include/linux/limits.h
uuid.o: /usr/include/i386-linux-gnu/bits/posix2_lim.h
uuid.o: /usr/include/stdio.h
uuid.o: /usr/include/libio.h
uuid.o: /usr/include/_G_config.h
uuid.o: /usr/include/wchar.h
uuid.o: /usr/lib/gcc/i686-linux-gnu/4.6/include/stdarg.h
uuid.o: /usr/include/i386-linux-gnu/bits/stdio_lim.h
uuid.o: /usr/include/i386-linux-gnu/bits/sys_errlist.h
uuid.o: /usr/include/i386-linux-gnu/sys/types.h
uuid.o: /usr/include/time.h
uuid.o: /usr/include/endian.h
uuid.o: /usr/include/i386-linux-gnu/bits/endian.h
uuid.o: /usr/include/i386-linux-gnu/bits/byteswap.h
uuid.o: /usr/include/i386-linux-gnu/sys/select.h
uuid.o: /usr/include/i386-linux-gnu/bits/select.h
uuid.o: /usr/include/i386-linux-gnu/bits/sigset.h
uuid.o: /usr/include/i386-linux-gnu/bits/time.h
uuid.o: /usr/include/i386-linux-gnu/sys/sysmacros.h
uuid.o: /usr/include/i386-linux-gnu/bits/pthreadtypes.h
uuid.o: ../../include/ac/stdlib.h
uuid.o: /usr/include/stdlib.h
uuid.o: /usr/include/i386-linux-gnu/bits/waitflags.h
uuid.o: /usr/include/i386-linux-gnu/bits/waitstatus.h
uuid.o: /usr/include/alloca.h
uuid.o: ../../include/ac/string.h
uuid.o: /usr/include/string.h
uuid.o: /usr/include/xlocale.h
uuid.o: ../../include/ac/socket.h
uuid.o: /usr/include/poll.h
uuid.o: /usr/include/i386-linux-gnu/sys/poll.h
uuid.o: /usr/include/i386-linux-gnu/bits/poll.h
uuid.o: /usr/include/i386-linux-gnu/sys/socket.h
uuid.o: /usr/include/i386-linux-gnu/sys/uio.h
uuid.o: /usr/include/i386-linux-gnu/bits/uio.h
uuid.o: /usr/include/i386-linux-gnu/bits/socket.h
uuid.o: /usr/include/i386-linux-gnu/bits/sockaddr.h
uuid.o: /usr/include/i386-linux-gnu/asm/socket.h
uuid.o: /usr/include/asm-generic/socket.h
uuid.o: /usr/include/i386-linux-gnu/asm/sockios.h
uuid.o: /usr/include/asm-generic/sockios.h
uuid.o: /usr/include/i386-linux-gnu/sys/un.h
uuid.o: /usr/include/netinet/in.h
uuid.o: /usr/lib/gcc/i686-linux-gnu/4.6/include/stdint.h
uuid.o: /usr/include/stdint.h
uuid.o: /usr/include/i386-linux-gnu/bits/wchar.h
uuid.o: /usr/include/i386-linux-gnu/bits/in.h
uuid.o: /usr/include/netinet/tcp.h
uuid.o: /usr/include/arpa/inet.h
uuid.o: /usr/include/arpa/nameser.h
uuid.o: /usr/include/i386-linux-gnu/sys/param.h
uuid.o: /usr/include/linux/param.h
uuid.o: /usr/include/i386-linux-gnu/asm/param.h
uuid.o: /usr/include/asm-generic/param.h
uuid.o: /usr/include/i386-linux-gnu/sys/bitypes.h
uuid.o: /usr/include/arpa/nameser_compat.h
uuid.o: /usr/include/netdb.h
uuid.o: /usr/include/rpc/netdb.h
uuid.o: /usr/include/i386-linux-gnu/bits/netdb.h
uuid.o: /usr/include/resolv.h
uuid.o: ../../include/ac/time.h
uuid.o: /usr/include/i386-linux-gnu/sys/time.h
uuid.o: ../../include/lutil.h
uuid.o: ../../include/ldap_cdefs.h
uuid.o: ../../include/lber_types.h
sockpair.o: sockpair.c
sockpair.o: ../../include/portable.h
sockpair.o: /usr/lib/gcc/i686-linux-gnu/4.6/include/stddef.h
sockpair.o: ../../include/ac/fdset.h
sockpair.o: /usr/include/i386-linux-gnu/bits/types.h
sockpair.o: /usr/include/features.h
sockpair.o: /usr/include/i386-linux-gnu/bits/predefs.h
sockpair.o: /usr/include/i386-linux-gnu/sys/cdefs.h
sockpair.o: /usr/include/i386-linux-gnu/bits/wordsize.h
sockpair.o: /usr/include/i386-linux-gnu/gnu/stubs.h
sockpair.o: /usr/include/i386-linux-gnu/gnu/stubs-32.h
sockpair.o: /usr/include/i386-linux-gnu/bits/typesizes.h
sockpair.o: ../../include/ldap_cdefs.h
sockpair.o: ../../include/ldap_features.h
sockpair.o: ../../include/ac/assert.h
sockpair.o: /usr/include/assert.h
sockpair.o: ../../include/ac/localize.h
sockpair.o: ../../include/ac/socket.h
sockpair.o: /usr/include/i386-linux-gnu/sys/types.h
sockpair.o: /usr/include/time.h
sockpair.o: /usr/include/endian.h
sockpair.o: /usr/include/i386-linux-gnu/bits/endian.h
sockpair.o: /usr/include/i386-linux-gnu/bits/byteswap.h
sockpair.o: /usr/include/i386-linux-gnu/sys/select.h
sockpair.o: /usr/include/i386-linux-gnu/bits/select.h
sockpair.o: /usr/include/i386-linux-gnu/bits/sigset.h
sockpair.o: /usr/include/i386-linux-gnu/bits/time.h
sockpair.o: /usr/include/i386-linux-gnu/sys/sysmacros.h
sockpair.o: /usr/include/i386-linux-gnu/bits/pthreadtypes.h
sockpair.o: /usr/include/poll.h
sockpair.o: /usr/include/i386-linux-gnu/sys/poll.h
sockpair.o: /usr/include/i386-linux-gnu/bits/poll.h
sockpair.o: /usr/include/i386-linux-gnu/sys/socket.h
sockpair.o: /usr/include/i386-linux-gnu/sys/uio.h
sockpair.o: /usr/include/i386-linux-gnu/bits/uio.h
sockpair.o: /usr/include/i386-linux-gnu/bits/socket.h
sockpair.o: /usr/include/i386-linux-gnu/bits/sockaddr.h
sockpair.o: /usr/include/i386-linux-gnu/asm/socket.h
sockpair.o: /usr/include/asm-generic/socket.h
sockpair.o: /usr/include/i386-linux-gnu/asm/sockios.h
sockpair.o: /usr/include/asm-generic/sockios.h
sockpair.o: /usr/include/i386-linux-gnu/sys/un.h
sockpair.o: /usr/include/string.h
sockpair.o: /usr/include/xlocale.h
sockpair.o: /usr/include/netinet/in.h
sockpair.o: /usr/lib/gcc/i686-linux-gnu/4.6/include/stdint.h
sockpair.o: /usr/include/stdint.h
sockpair.o: /usr/include/i386-linux-gnu/bits/wchar.h
sockpair.o: /usr/include/i386-linux-gnu/bits/in.h
sockpair.o: /usr/include/netinet/tcp.h
sockpair.o: /usr/include/arpa/inet.h
sockpair.o: /usr/include/arpa/nameser.h
sockpair.o: /usr/include/i386-linux-gnu/sys/param.h
sockpair.o: /usr/lib/gcc/i686-linux-gnu/4.6/include-fixed/limits.h
sockpair.o: /usr/lib/gcc/i686-linux-gnu/4.6/include-fixed/syslimits.h
sockpair.o: /usr/include/limits.h
sockpair.o: /usr/include/i386-linux-gnu/bits/posix1_lim.h
sockpair.o: /usr/include/i386-linux-gnu/bits/local_lim.h
sockpair.o: /usr/include/linux/limits.h
sockpair.o: /usr/include/i386-linux-gnu/bits/posix2_lim.h
sockpair.o: /usr/include/linux/param.h
sockpair.o: /usr/include/i386-linux-gnu/asm/param.h
sockpair.o: /usr/include/asm-generic/param.h
sockpair.o: /usr/include/i386-linux-gnu/sys/bitypes.h
sockpair.o: /usr/include/arpa/nameser_compat.h
sockpair.o: /usr/include/netdb.h
sockpair.o: /usr/include/rpc/netdb.h
sockpair.o: /usr/include/i386-linux-gnu/bits/netdb.h
sockpair.o: /usr/include/resolv.h
sockpair.o: /usr/include/stdio.h
sockpair.o: /usr/include/libio.h
sockpair.o: /usr/include/_G_config.h
sockpair.o: /usr/include/wchar.h
sockpair.o: /usr/lib/gcc/i686-linux-gnu/4.6/include/stdarg.h
sockpair.o: /usr/include/i386-linux-gnu/bits/stdio_lim.h
sockpair.o: /usr/include/i386-linux-gnu/bits/sys_errlist.h
sockpair.o: ../../include/ac/unistd.h
sockpair.o: /usr/include/unistd.h
sockpair.o: /usr/include/i386-linux-gnu/bits/posix_opt.h
sockpair.o: /usr/include/i386-linux-gnu/bits/environments.h
sockpair.o: /usr/include/i386-linux-gnu/bits/confname.h
sockpair.o: /usr/include/getopt.h
sockpair.o: ../../include/lutil_lockf.h
sockpair.o: ../../include/lutil.h
sockpair.o: ../../include/ldap_cdefs.h
sockpair.o: ../../include/lber_types.h
avl.o: avl.c
avl.o: ../../include/portable.h
avl.o: /usr/lib/gcc/i686-linux-gnu/4.6/include/stddef.h
avl.o: ../../include/ac/fdset.h
avl.o: /usr/include/i386-linux-gnu/bits/types.h
avl.o: /usr/include/features.h
avl.o: /usr/include/i386-linux-gnu/bits/predefs.h
avl.o: /usr/include/i386-linux-gnu/sys/cdefs.h
avl.o: /usr/include/i386-linux-gnu/bits/wordsize.h
avl.o: /usr/include/i386-linux-gnu/gnu/stubs.h
avl.o: /usr/include/i386-linux-gnu/gnu/stubs-32.h
avl.o: /usr/include/i386-linux-gnu/bits/typesizes.h
avl.o: ../../include/ldap_cdefs.h
avl.o: ../../include/ldap_features.h
avl.o: ../../include/ac/assert.h
avl.o: /usr/include/assert.h
avl.o: ../../include/ac/localize.h
avl.o: /usr/lib/gcc/i686-linux-gnu/4.6/include-fixed/limits.h
avl.o: /usr/lib/gcc/i686-linux-gnu/4.6/include-fixed/syslimits.h
avl.o: /usr/include/limits.h
avl.o: /usr/include/i386-linux-gnu/bits/posix1_lim.h
avl.o: /usr/include/i386-linux-gnu/bits/local_lim.h
avl.o: /usr/include/linux/limits.h
avl.o: /usr/include/i386-linux-gnu/bits/posix2_lim.h
avl.o: /usr/include/stdio.h
avl.o: /usr/include/libio.h
avl.o: /usr/include/_G_config.h
avl.o: /usr/include/wchar.h
avl.o: /usr/lib/gcc/i686-linux-gnu/4.6/include/stdarg.h
avl.o: /usr/include/i386-linux-gnu/bits/stdio_lim.h
avl.o: /usr/include/i386-linux-gnu/bits/sys_errlist.h
avl.o: ../../include/ac/stdlib.h
avl.o: /usr/include/stdlib.h
avl.o: /usr/include/i386-linux-gnu/bits/waitflags.h
avl.o: /usr/include/i386-linux-gnu/bits/waitstatus.h
avl.o: /usr/include/endian.h
avl.o: /usr/include/i386-linux-gnu/bits/endian.h
avl.o: /usr/include/i386-linux-gnu/bits/byteswap.h
avl.o: /usr/include/i386-linux-gnu/sys/types.h
avl.o: /usr/include/time.h
avl.o: /usr/include/i386-linux-gnu/sys/select.h
avl.o: /usr/include/i386-linux-gnu/bits/select.h
avl.o: /usr/include/i386-linux-gnu/bits/sigset.h
avl.o: /usr/include/i386-linux-gnu/bits/time.h
avl.o: /usr/include/i386-linux-gnu/sys/sysmacros.h
avl.o: /usr/include/i386-linux-gnu/bits/pthreadtypes.h
avl.o: /usr/include/alloca.h
avl.o: ../../include/lber.h
avl.o: ../../include/lber_types.h
avl.o: ../../include/ldap_cdefs.h
avl.o: /usr/include/string.h
avl.o: /usr/include/xlocale.h
avl.o: ../../include/avl.h
tavl.o: tavl.c
tavl.o: ../../include/portable.h
tavl.o: /usr/lib/gcc/i686-linux-gnu/4.6/include/stddef.h
tavl.o: ../../include/ac/fdset.h
tavl.o: /usr/include/i386-linux-gnu/bits/types.h
tavl.o: /usr/include/features.h
tavl.o: /usr/include/i386-linux-gnu/bits/predefs.h
tavl.o: /usr/include/i386-linux-gnu/sys/cdefs.h
tavl.o: /usr/include/i386-linux-gnu/bits/wordsize.h
tavl.o: /usr/include/i386-linux-gnu/gnu/stubs.h
tavl.o: /usr/include/i386-linux-gnu/gnu/stubs-32.h
tavl.o: /usr/include/i386-linux-gnu/bits/typesizes.h
tavl.o: ../../include/ldap_cdefs.h
tavl.o: ../../include/ldap_features.h
tavl.o: ../../include/ac/assert.h
tavl.o: /usr/include/assert.h
tavl.o: ../../include/ac/localize.h
tavl.o: /usr/lib/gcc/i686-linux-gnu/4.6/include-fixed/limits.h
tavl.o: /usr/lib/gcc/i686-linux-gnu/4.6/include-fixed/syslimits.h
tavl.o: /usr/include/limits.h
tavl.o: /usr/include/i386-linux-gnu/bits/posix1_lim.h
tavl.o: /usr/include/i386-linux-gnu/bits/local_lim.h
tavl.o: /usr/include/linux/limits.h
tavl.o: /usr/include/i386-linux-gnu/bits/posix2_lim.h
tavl.o: /usr/include/stdio.h
tavl.o: /usr/include/libio.h
tavl.o: /usr/include/_G_config.h
tavl.o: /usr/include/wchar.h
tavl.o: /usr/lib/gcc/i686-linux-gnu/4.6/include/stdarg.h
tavl.o: /usr/include/i386-linux-gnu/bits/stdio_lim.h
tavl.o: /usr/include/i386-linux-gnu/bits/sys_errlist.h
tavl.o: ../../include/ac/stdlib.h
tavl.o: /usr/include/stdlib.h
tavl.o: /usr/include/i386-linux-gnu/bits/waitflags.h
tavl.o: /usr/include/i386-linux-gnu/bits/waitstatus.h
tavl.o: /usr/include/endian.h
tavl.o: /usr/include/i386-linux-gnu/bits/endian.h
tavl.o: /usr/include/i386-linux-gnu/bits/byteswap.h
tavl.o: /usr/include/i386-linux-gnu/sys/types.h
tavl.o: /usr/include/time.h
tavl.o: /usr/include/i386-linux-gnu/sys/select.h
tavl.o: /usr/include/i386-linux-gnu/bits/select.h
tavl.o: /usr/include/i386-linux-gnu/bits/sigset.h
tavl.o: /usr/include/i386-linux-gnu/bits/time.h
tavl.o: /usr/include/i386-linux-gnu/sys/sysmacros.h
tavl.o: /usr/include/i386-linux-gnu/bits/pthreadtypes.h
tavl.o: /usr/include/alloca.h
tavl.o: ../../include/lber.h
tavl.o: ../../include/lber_types.h
tavl.o: ../../include/ldap_cdefs.h
tavl.o: /usr/include/string.h
tavl.o: /usr/include/xlocale.h
tavl.o: ../../include/avl.h
testavl.o: testavl.c
testavl.o: ../../include/portable.h
testavl.o: /usr/lib/gcc/i686-linux-gnu/4.6/include/stddef.h
testavl.o: ../../include/ac/fdset.h
testavl.o: /usr/include/i386-linux-gnu/bits/types.h
testavl.o: /usr/include/features.h
testavl.o: /usr/include/i386-linux-gnu/bits/predefs.h
testavl.o: /usr/include/i386-linux-gnu/sys/cdefs.h
testavl.o: /usr/include/i386-linux-gnu/bits/wordsize.h
testavl.o: /usr/include/i386-linux-gnu/gnu/stubs.h
testavl.o: /usr/include/i386-linux-gnu/gnu/stubs-32.h
testavl.o: /usr/include/i386-linux-gnu/bits/typesizes.h
testavl.o: ../../include/ldap_cdefs.h
testavl.o: ../../include/ldap_features.h
testavl.o: ../../include/ac/assert.h
testavl.o: /usr/include/assert.h
testavl.o: ../../include/ac/localize.h
testavl.o: /usr/include/stdio.h
testavl.o: /usr/include/libio.h
testavl.o: /usr/include/_G_config.h
testavl.o: /usr/include/wchar.h
testavl.o: /usr/lib/gcc/i686-linux-gnu/4.6/include/stdarg.h
testavl.o: /usr/include/i386-linux-gnu/bits/stdio_lim.h
testavl.o: /usr/include/i386-linux-gnu/bits/sys_errlist.h
testavl.o: ../../include/ac/stdlib.h
testavl.o: /usr/include/stdlib.h
testavl.o: /usr/include/i386-linux-gnu/bits/waitflags.h
testavl.o: /usr/include/i386-linux-gnu/bits/waitstatus.h
testavl.o: /usr/include/endian.h
testavl.o: /usr/include/i386-linux-gnu/bits/endian.h
testavl.o: /usr/include/i386-linux-gnu/bits/byteswap.h
testavl.o: /usr/include/i386-linux-gnu/sys/types.h
testavl.o: /usr/include/time.h
testavl.o: /usr/include/i386-linux-gnu/sys/select.h
testavl.o: /usr/include/i386-linux-gnu/bits/select.h
testavl.o: /usr/include/i386-linux-gnu/bits/sigset.h
testavl.o: /usr/include/i386-linux-gnu/bits/time.h
testavl.o: /usr/include/i386-linux-gnu/sys/sysmacros.h
testavl.o: /usr/include/i386-linux-gnu/bits/pthreadtypes.h
testavl.o: /usr/include/alloca.h
testavl.o: /usr/lib/gcc/i686-linux-gnu/4.6/include-fixed/limits.h
testavl.o: /usr/lib/gcc/i686-linux-gnu/4.6/include-fixed/syslimits.h
testavl.o: /usr/include/limits.h
testavl.o: /usr/include/i386-linux-gnu/bits/posix1_lim.h
testavl.o: /usr/include/i386-linux-gnu/bits/local_lim.h
testavl.o: /usr/include/linux/limits.h
testavl.o: /usr/include/i386-linux-gnu/bits/posix2_lim.h
testavl.o: ../../include/ac/string.h
testavl.o: /usr/include/string.h
testavl.o: /usr/include/xlocale.h
testavl.o: ../../include/avl.h
testavl.o: ../../include/ldap_cdefs.h
meter.o: meter.c
meter.o: ../../include/portable.h
meter.o: /usr/lib/gcc/i686-linux-gnu/4.6/include/stddef.h
meter.o: ../../include/ac/fdset.h
meter.o: /usr/include/i386-linux-gnu/bits/types.h
meter.o: /usr/include/features.h
meter.o: /usr/include/i386-linux-gnu/bits/predefs.h
meter.o: /usr/include/i386-linux-gnu/sys/cdefs.h
meter.o: /usr/include/i386-linux-gnu/bits/wordsize.h
meter.o: /usr/include/i386-linux-gnu/gnu/stubs.h
meter.o: /usr/include/i386-linux-gnu/gnu/stubs-32.h
meter.o: /usr/include/i386-linux-gnu/bits/typesizes.h
meter.o: ../../include/ldap_cdefs.h
meter.o: ../../include/ldap_features.h
meter.o: ../../include/ac/assert.h
meter.o: /usr/include/assert.h
meter.o: ../../include/ac/localize.h
meter.o: ../../include/lutil_meter.h
meter.o: ../../include/portable.h
meter.o: /usr/lib/gcc/i686-linux-gnu/4.6/include-fixed/limits.h
meter.o: /usr/lib/gcc/i686-linux-gnu/4.6/include-fixed/syslimits.h
meter.o: /usr/include/limits.h
meter.o: /usr/include/i386-linux-gnu/bits/posix1_lim.h
meter.o: /usr/include/i386-linux-gnu/bits/local_lim.h
meter.o: /usr/include/linux/limits.h
meter.o: /usr/include/i386-linux-gnu/bits/posix2_lim.h
meter.o: /usr/include/stdio.h
meter.o: /usr/include/libio.h
meter.o: /usr/include/_G_config.h
meter.o: /usr/include/wchar.h
meter.o: /usr/lib/gcc/i686-linux-gnu/4.6/include/stdarg.h
meter.o: /usr/include/i386-linux-gnu/bits/stdio_lim.h
meter.o: /usr/include/i386-linux-gnu/bits/sys_errlist.h
meter.o: /usr/include/i386-linux-gnu/sys/types.h
meter.o: /usr/include/time.h
meter.o: /usr/include/endian.h
meter.o: /usr/include/i386-linux-gnu/bits/endian.h
meter.o: /usr/include/i386-linux-gnu/bits/byteswap.h
meter.o: /usr/include/i386-linux-gnu/sys/select.h
meter.o: /usr/include/i386-linux-gnu/bits/select.h
meter.o: /usr/include/i386-linux-gnu/bits/sigset.h
meter.o: /usr/include/i386-linux-gnu/bits/time.h
meter.o: /usr/include/i386-linux-gnu/sys/sysmacros.h
meter.o: /usr/include/i386-linux-gnu/bits/pthreadtypes.h
meter.o: ../../include/ac/stdlib.h
meter.o: /usr/include/stdlib.h
meter.o: /usr/include/i386-linux-gnu/bits/waitflags.h
meter.o: /usr/include/i386-linux-gnu/bits/waitstatus.h
meter.o: /usr/include/alloca.h
meter.o: ../../include/ac/time.h
meter.o: /usr/include/i386-linux-gnu/sys/time.h
meter.o: /usr/include/xlocale.h
meter.o: ../../include/ac/assert.h
meter.o: ../../include/ac/string.h
meter.o: /usr/include/string.h
setproctitle.o: setproctitle.c
setproctitle.o: ../../include/portable.h
setproctitle.o: /usr/lib/gcc/i686-linux-gnu/4.6/include/stddef.h
setproctitle.o: ../../include/ac/fdset.h
setproctitle.o: /usr/include/i386-linux-gnu/bits/types.h
setproctitle.o: /usr/include/features.h
setproctitle.o: /usr/include/i386-linux-gnu/bits/predefs.h
setproctitle.o: /usr/include/i386-linux-gnu/sys/cdefs.h
setproctitle.o: /usr/include/i386-linux-gnu/bits/wordsize.h
setproctitle.o: /usr/include/i386-linux-gnu/gnu/stubs.h
setproctitle.o: /usr/include/i386-linux-gnu/gnu/stubs-32.h
setproctitle.o: /usr/include/i386-linux-gnu/bits/typesizes.h
setproctitle.o: ../../include/ldap_cdefs.h
setproctitle.o: ../../include/ldap_features.h
setproctitle.o: ../../include/ac/assert.h
setproctitle.o: /usr/include/assert.h
setproctitle.o: ../../include/ac/localize.h
setproctitle.o: /usr/include/stdio.h
setproctitle.o: /usr/include/libio.h
setproctitle.o: /usr/include/_G_config.h
setproctitle.o: /usr/include/wchar.h
setproctitle.o: /usr/lib/gcc/i686-linux-gnu/4.6/include/stdarg.h
setproctitle.o: /usr/include/i386-linux-gnu/bits/stdio_lim.h
setproctitle.o: /usr/include/i386-linux-gnu/bits/sys_errlist.h
setproctitle.o: ../../include/ac/stdlib.h
setproctitle.o: /usr/include/stdlib.h
setproctitle.o: /usr/include/i386-linux-gnu/bits/waitflags.h
setproctitle.o: /usr/include/i386-linux-gnu/bits/waitstatus.h
setproctitle.o: /usr/include/endian.h
setproctitle.o: /usr/include/i386-linux-gnu/bits/endian.h
setproctitle.o: /usr/include/i386-linux-gnu/bits/byteswap.h
setproctitle.o: /usr/include/i386-linux-gnu/sys/types.h
setproctitle.o: /usr/include/time.h
setproctitle.o: /usr/include/i386-linux-gnu/sys/select.h
setproctitle.o: /usr/include/i386-linux-gnu/bits/select.h
setproctitle.o: /usr/include/i386-linux-gnu/bits/sigset.h
setproctitle.o: /usr/include/i386-linux-gnu/bits/time.h
setproctitle.o: /usr/include/i386-linux-gnu/sys/sysmacros.h
setproctitle.o: /usr/include/i386-linux-gnu/bits/pthreadtypes.h
setproctitle.o: /usr/include/alloca.h
setproctitle.o: /usr/lib/gcc/i686-linux-gnu/4.6/include-fixed/limits.h
setproctitle.o: /usr/lib/gcc/i686-linux-gnu/4.6/include-fixed/syslimits.h
setproctitle.o: /usr/include/limits.h
setproctitle.o: /usr/include/i386-linux-gnu/bits/posix1_lim.h
setproctitle.o: /usr/include/i386-linux-gnu/bits/local_lim.h
setproctitle.o: /usr/include/linux/limits.h
setproctitle.o: /usr/include/i386-linux-gnu/bits/posix2_lim.h
setproctitle.o: ../../include/ac/setproctitle.h
setproctitle.o: ../../include/ac/string.h
setproctitle.o: /usr/include/string.h
setproctitle.o: /usr/include/xlocale.h
setproctitle.o: ../../include/ac/stdarg.h
getpeereid.o: getpeereid.c
getpeereid.o: ../../include/portable.h
getpeereid.o: /usr/lib/gcc/i686-linux-gnu/4.6/include/stddef.h
getpeereid.o: ../../include/ac/fdset.h
getpeereid.o: /usr/include/i386-linux-gnu/bits/types.h
getpeereid.o: /usr/include/features.h
getpeereid.o: /usr/include/i386-linux-gnu/bits/predefs.h
getpeereid.o: /usr/include/i386-linux-gnu/sys/cdefs.h
getpeereid.o: /usr/include/i386-linux-gnu/bits/wordsize.h
getpeereid.o: /usr/include/i386-linux-gnu/gnu/stubs.h
getpeereid.o: /usr/include/i386-linux-gnu/gnu/stubs-32.h
getpeereid.o: /usr/include/i386-linux-gnu/bits/typesizes.h
getpeereid.o: ../../include/ldap_cdefs.h
getpeereid.o: ../../include/ldap_features.h
getpeereid.o: ../../include/ac/assert.h
getpeereid.o: /usr/include/assert.h
getpeereid.o: ../../include/ac/localize.h
getpeereid.o: /usr/include/i386-linux-gnu/sys/types.h
getpeereid.o: /usr/include/time.h
getpeereid.o: /usr/include/endian.h
getpeereid.o: /usr/include/i386-linux-gnu/bits/endian.h
getpeereid.o: /usr/include/i386-linux-gnu/bits/byteswap.h
getpeereid.o: /usr/include/i386-linux-gnu/sys/select.h
getpeereid.o: /usr/include/i386-linux-gnu/bits/select.h
getpeereid.o: /usr/include/i386-linux-gnu/bits/sigset.h
getpeereid.o: /usr/include/i386-linux-gnu/bits/time.h
getpeereid.o: /usr/include/i386-linux-gnu/sys/sysmacros.h
getpeereid.o: /usr/include/i386-linux-gnu/bits/pthreadtypes.h
getpeereid.o: ../../include/ac/unistd.h
getpeereid.o: /usr/include/unistd.h
getpeereid.o: /usr/include/i386-linux-gnu/bits/posix_opt.h
getpeereid.o: /usr/include/i386-linux-gnu/bits/environments.h
getpeereid.o: /usr/include/i386-linux-gnu/bits/confname.h
getpeereid.o: /usr/include/getopt.h
getpeereid.o: ../../include/lutil_lockf.h
getpeereid.o: ../../include/ac/socket.h
getpeereid.o: /usr/include/poll.h
getpeereid.o: /usr/include/i386-linux-gnu/sys/poll.h
getpeereid.o: /usr/include/i386-linux-gnu/bits/poll.h
getpeereid.o: /usr/include/i386-linux-gnu/sys/socket.h
getpeereid.o: /usr/include/i386-linux-gnu/sys/uio.h
getpeereid.o: /usr/include/i386-linux-gnu/bits/uio.h
getpeereid.o: /usr/include/i386-linux-gnu/bits/socket.h
getpeereid.o: /usr/include/i386-linux-gnu/bits/sockaddr.h
getpeereid.o: /usr/include/i386-linux-gnu/asm/socket.h
getpeereid.o: /usr/include/asm-generic/socket.h
getpeereid.o: /usr/include/i386-linux-gnu/asm/sockios.h
getpeereid.o: /usr/include/asm-generic/sockios.h
getpeereid.o: /usr/include/i386-linux-gnu/sys/un.h
getpeereid.o: /usr/include/string.h
getpeereid.o: /usr/include/xlocale.h
getpeereid.o: /usr/include/netinet/in.h
getpeereid.o: /usr/lib/gcc/i686-linux-gnu/4.6/include/stdint.h
getpeereid.o: /usr/include/stdint.h
getpeereid.o: /usr/include/i386-linux-gnu/bits/wchar.h
getpeereid.o: /usr/include/i386-linux-gnu/bits/in.h
getpeereid.o: /usr/include/netinet/tcp.h
getpeereid.o: /usr/include/arpa/inet.h
getpeereid.o: /usr/include/arpa/nameser.h
getpeereid.o: /usr/include/i386-linux-gnu/sys/param.h
getpeereid.o: /usr/lib/gcc/i686-linux-gnu/4.6/include-fixed/limits.h
getpeereid.o: /usr/lib/gcc/i686-linux-gnu/4.6/include-fixed/syslimits.h
getpeereid.o: /usr/include/limits.h
getpeereid.o: /usr/include/i386-linux-gnu/bits/posix1_lim.h
getpeereid.o: /usr/include/i386-linux-gnu/bits/local_lim.h
getpeereid.o: /usr/include/linux/limits.h
getpeereid.o: /usr/include/i386-linux-gnu/bits/posix2_lim.h
getpeereid.o: /usr/include/i386-linux-gnu/bits/xopen_lim.h
getpeereid.o: /usr/include/i386-linux-gnu/bits/stdio_lim.h
getpeereid.o: /usr/include/linux/param.h
getpeereid.o: /usr/include/i386-linux-gnu/asm/param.h
getpeereid.o: /usr/include/asm-generic/param.h
getpeereid.o: /usr/include/i386-linux-gnu/sys/bitypes.h
getpeereid.o: /usr/include/arpa/nameser_compat.h
getpeereid.o: /usr/include/netdb.h
getpeereid.o: /usr/include/rpc/netdb.h
getpeereid.o: /usr/include/i386-linux-gnu/bits/siginfo.h
getpeereid.o: /usr/include/i386-linux-gnu/bits/netdb.h
getpeereid.o: /usr/include/resolv.h
getpeereid.o: /usr/include/stdio.h
getpeereid.o: /usr/include/libio.h
getpeereid.o: /usr/include/_G_config.h
getpeereid.o: /usr/include/wchar.h
getpeereid.o: /usr/lib/gcc/i686-linux-gnu/4.6/include/stdarg.h
getpeereid.o: /usr/include/i386-linux-gnu/bits/sys_errlist.h
getpeereid.o: ../../include/ac/errno.h
getpeereid.o: /usr/include/errno.h
getpeereid.o: /usr/include/i386-linux-gnu/bits/errno.h
getpeereid.o: /usr/include/linux/errno.h
getpeereid.o: /usr/include/i386-linux-gnu/asm/errno.h
getpeereid.o: /usr/include/asm-generic/errno.h
getpeereid.o: /usr/include/asm-generic/errno-base.h
getpeereid.o: /usr/include/stdlib.h
getpeereid.o: /usr/include/i386-linux-gnu/bits/waitflags.h
getpeereid.o: /usr/include/i386-linux-gnu/bits/waitstatus.h
getpeereid.o: /usr/include/alloca.h
detach.o: detach.c
detach.o: ../../include/portable.h
detach.o: /usr/lib/gcc/i686-linux-gnu/4.6/include/stddef.h
detach.o: ../../include/ac/fdset.h
detach.o: /usr/include/i386-linux-gnu/bits/types.h
detach.o: /usr/include/features.h
detach.o: /usr/include/i386-linux-gnu/bits/predefs.h
detach.o: /usr/include/i386-linux-gnu/sys/cdefs.h
detach.o: /usr/include/i386-linux-gnu/bits/wordsize.h
detach.o: /usr/include/i386-linux-gnu/gnu/stubs.h
detach.o: /usr/include/i386-linux-gnu/gnu/stubs-32.h
detach.o: /usr/include/i386-linux-gnu/bits/typesizes.h
detach.o: ../../include/ldap_cdefs.h
detach.o: ../../include/ldap_features.h
detach.o: ../../include/ac/assert.h
detach.o: /usr/include/assert.h
detach.o: ../../include/ac/localize.h
detach.o: /usr/include/stdio.h
detach.o: /usr/include/libio.h
detach.o: /usr/include/_G_config.h
detach.o: /usr/include/wchar.h
detach.o: /usr/lib/gcc/i686-linux-gnu/4.6/include/stdarg.h
detach.o: /usr/include/i386-linux-gnu/bits/stdio_lim.h
detach.o: /usr/include/i386-linux-gnu/bits/sys_errlist.h
detach.o: ../../include/ac/stdlib.h
detach.o: /usr/include/stdlib.h
detach.o: /usr/include/i386-linux-gnu/bits/waitflags.h
detach.o: /usr/include/i386-linux-gnu/bits/waitstatus.h
detach.o: /usr/include/endian.h
detach.o: /usr/include/i386-linux-gnu/bits/endian.h
detach.o: /usr/include/i386-linux-gnu/bits/byteswap.h
detach.o: /usr/include/i386-linux-gnu/sys/types.h
detach.o: /usr/include/time.h
detach.o: /usr/include/i386-linux-gnu/sys/select.h
detach.o: /usr/include/i386-linux-gnu/bits/select.h
detach.o: /usr/include/i386-linux-gnu/bits/sigset.h
detach.o: /usr/include/i386-linux-gnu/bits/time.h
detach.o: /usr/include/i386-linux-gnu/sys/sysmacros.h
detach.o: /usr/include/i386-linux-gnu/bits/pthreadtypes.h
detach.o: /usr/include/alloca.h
detach.o: /usr/lib/gcc/i686-linux-gnu/4.6/include-fixed/limits.h
detach.o: /usr/lib/gcc/i686-linux-gnu/4.6/include-fixed/syslimits.h
detach.o: /usr/include/limits.h
detach.o: /usr/include/i386-linux-gnu/bits/posix1_lim.h
detach.o: /usr/include/i386-linux-gnu/bits/local_lim.h
detach.o: /usr/include/linux/limits.h
detach.o: /usr/include/i386-linux-gnu/bits/posix2_lim.h
detach.o: ../../include/ac/signal.h
detach.o: /usr/include/signal.h
detach.o: /usr/include/i386-linux-gnu/bits/signum.h
detach.o: /usr/include/i386-linux-gnu/bits/siginfo.h
detach.o: /usr/include/i386-linux-gnu/bits/sigaction.h
detach.o: /usr/include/i386-linux-gnu/bits/sigcontext.h
detach.o: /usr/include/i386-linux-gnu/asm/sigcontext.h
detach.o: /usr/include/linux/types.h
detach.o: /usr/include/i386-linux-gnu/asm/types.h
detach.o: /usr/include/asm-generic/types.h
detach.o: /usr/include/asm-generic/int-ll64.h
detach.o: /usr/include/i386-linux-gnu/asm/bitsperlong.h
detach.o: /usr/include/asm-generic/bitsperlong.h
detach.o: /usr/include/linux/posix_types.h
detach.o: /usr/include/linux/stddef.h
detach.o: /usr/include/i386-linux-gnu/asm/posix_types.h
detach.o: /usr/include/i386-linux-gnu/asm/posix_types_32.h
detach.o: /usr/include/i386-linux-gnu/bits/sigstack.h
detach.o: /usr/include/i386-linux-gnu/sys/ucontext.h
detach.o: /usr/include/i386-linux-gnu/bits/sigthread.h
detach.o: ../../include/ac/socket.h
detach.o: /usr/include/poll.h
detach.o: /usr/include/i386-linux-gnu/sys/poll.h
detach.o: /usr/include/i386-linux-gnu/bits/poll.h
detach.o: /usr/include/i386-linux-gnu/sys/socket.h
detach.o: /usr/include/i386-linux-gnu/sys/uio.h
detach.o: /usr/include/i386-linux-gnu/bits/uio.h
detach.o: /usr/include/i386-linux-gnu/bits/socket.h
detach.o: /usr/include/i386-linux-gnu/bits/sockaddr.h
detach.o: /usr/include/i386-linux-gnu/asm/socket.h
detach.o: /usr/include/asm-generic/socket.h
detach.o: /usr/include/i386-linux-gnu/asm/sockios.h
detach.o: /usr/include/asm-generic/sockios.h
detach.o: /usr/include/i386-linux-gnu/sys/un.h
detach.o: /usr/include/string.h
detach.o: /usr/include/xlocale.h
detach.o: /usr/include/netinet/in.h
detach.o: /usr/lib/gcc/i686-linux-gnu/4.6/include/stdint.h
detach.o: /usr/include/stdint.h
detach.o: /usr/include/i386-linux-gnu/bits/wchar.h
detach.o: /usr/include/i386-linux-gnu/bits/in.h
detach.o: /usr/include/netinet/tcp.h
detach.o: /usr/include/arpa/inet.h
detach.o: /usr/include/arpa/nameser.h
detach.o: /usr/include/i386-linux-gnu/sys/param.h
detach.o: /usr/include/linux/param.h
detach.o: /usr/include/i386-linux-gnu/asm/param.h
detach.o: /usr/include/asm-generic/param.h
detach.o: /usr/include/i386-linux-gnu/sys/bitypes.h
detach.o: /usr/include/arpa/nameser_compat.h
detach.o: /usr/include/netdb.h
detach.o: /usr/include/rpc/netdb.h
detach.o: /usr/include/i386-linux-gnu/bits/netdb.h
detach.o: /usr/include/resolv.h
detach.o: ../../include/ac/unistd.h
detach.o: /usr/include/unistd.h
detach.o: /usr/include/i386-linux-gnu/bits/posix_opt.h
detach.o: /usr/include/i386-linux-gnu/bits/environments.h
detach.o: /usr/include/i386-linux-gnu/bits/confname.h
detach.o: /usr/include/getopt.h
detach.o: ../../include/lutil_lockf.h
detach.o: /usr/include/i386-linux-gnu/sys/stat.h
detach.o: /usr/include/i386-linux-gnu/bits/stat.h
detach.o: /usr/include/fcntl.h
detach.o: /usr/include/i386-linux-gnu/bits/fcntl.h
detach.o: /usr/include/i386-linux-gnu/sys/file.h
detach.o: /usr/include/i386-linux-gnu/sys/ioctl.h
detach.o: /usr/include/i386-linux-gnu/bits/ioctls.h
detach.o: /usr/include/i386-linux-gnu/asm/ioctls.h
detach.o: /usr/include/asm-generic/ioctls.h
detach.o: /usr/include/linux/ioctl.h
detach.o: /usr/include/i386-linux-gnu/asm/ioctl.h
detach.o: /usr/include/asm-generic/ioctl.h
detach.o: /usr/include/i386-linux-gnu/bits/ioctl-types.h
detach.o: /usr/include/i386-linux-gnu/sys/ttydefaults.h
detach.o: ../../include/lutil.h
detach.o: ../../include/ldap_cdefs.h
detach.o: ../../include/lber_types.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
