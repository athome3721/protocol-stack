# $Id: Makefile.in,v 1.45 2010/08/16 03:15:23 dtucker Exp $

sysconfdir=${prefix}/etc
piddir=/var/run
srcdir=.
top_srcdir=..


CC=/home/zhangyg/software/marvell-gcc-5.2.1-16.02.0/marvell-gcc-5.2.1-16.02.0/armv8/le/aarch64v8-marvell-linux-gnu-5.2.1_i686_20151110/bin/aarch64-linux-gnu-gcc
LD=/home/zhangyg/software/marvell-gcc-5.2.1-16.02.0/marvell-gcc-5.2.1-16.02.0/armv8/le/aarch64v8-marvell-linux-gnu-5.2.1_i686_20151110/bin/aarch64-linux-gnu-gcc
CFLAGS=-g -O2 -Wall -Wpointer-arith -Wuninitialized -fno-builtin-memset -fstack-protector-all 
CPPFLAGS=-I. -I.. -I$(srcdir) -I$(srcdir)/.. -I/home/zhangyg/ssh/openssl-1.0.1u/include -I/home/zhangyg/ssh/zlib-1.2.8  -DHAVE_CONFIG_H
LIBS=-lcrypto -ldl -lutil -lz -lnsl  -lcrypt -lresolv
AR=/home/zhangyg/software/marvell-gcc-5.2.1-16.02.0/marvell-gcc-5.2.1-16.02.0/armv8/le/aarch64v8-marvell-linux-gnu-5.2.1_i686_20151110/bin/aarch64-linux-gnu-gcc-ar
RANLIB=ranlib
INSTALL=/usr/bin/install -c
LDFLAGS=-L. -L/home/zhangyg/ssh/openssl-1.0.1u -L/home/zhangyg/ssh/zlib-1.2.8  -fstack-protector-all

OPENBSD=base64.o basename.o bindresvport.o daemon.o dirname.o fmt_scaled.o getcwd.o getgrouplist.o getopt.o getrrsetbyname.o glob.o inet_aton.o inet_ntoa.o inet_ntop.o mktemp.o pwcache.o readpassphrase.o realpath.o rresvport.o setenv.o setproctitle.o sha2.o sigact.o strlcat.o strlcpy.o strmode.o strptime.o strsep.o strtonum.o strtoll.o strtoul.o vis.o

COMPAT=bsd-arc4random.o bsd-asprintf.o bsd-closefrom.o bsd-cray.o bsd-cygwin_util.o bsd-getpeereid.o bsd-misc.o bsd-nextstep.o bsd-openpty.o bsd-poll.o bsd-snprintf.o bsd-statvfs.o bsd-waitpid.o fake-rfc2553.o openssl-compat.o xmmap.o xcrypt.o

PORTS=port-aix.o port-irix.o port-linux.o port-solaris.o port-tun.o port-uw.o

.c.o:
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $<

all: libopenbsd-compat.a

$(COMPAT): ../config.h
$(OPENBSD): ../config.h
$(PORTS): ../config.h

libopenbsd-compat.a:  $(COMPAT) $(OPENBSD) $(PORTS)
	$(AR) rv $@ $(COMPAT) $(OPENBSD) $(PORTS)
	$(RANLIB) $@

clean:
	rm -f *.o *.a core 

distclean: clean
	rm -f Makefile *~
