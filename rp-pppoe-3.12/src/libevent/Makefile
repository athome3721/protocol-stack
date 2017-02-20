# Generated automatically from Makefile.in by configure.
# $Id$
#
# Makefile for event-handling library
#
# Copyright 2002 Roaring Penguin Software Inc.
#
# This software may be distributed according to the terms of the GNU
# General Public License, version 2 or (at your option) any later version.
# LIC: GPL

OBJS=event.o event_tcp.o hash.o event_sig.o
SRCS=$(OBJS:.o=.c)
HDRS=event.h event_tcp.h eventpriv.h hash.h
CFLAGS=-g -O2 -fno-strict-aliasing -Wall -Wstrict-prototypes -I.. $(DEFINES)
AR=ar

all: libevent.a

libevent.a: $(OBJS)
	rm -f libevent.a
	$(AR) -cq libevent.a $(OBJS)
	ranlib libevent.a

event.o: event.c $(HDRS)
	/home/zhangyg/software/marvell-gcc-5.2.1-16.02.0/marvell-gcc-5.2.1-16.02.0/armv8/le/aarch64v8-marvell-linux-gnu-5.2.1_i686_20151110/bin/aarch64-linux-gnu-gcc $(CFLAGS) -c -o $@ $<

hash.o: hash.c $(HDRS)
	/home/zhangyg/software/marvell-gcc-5.2.1-16.02.0/marvell-gcc-5.2.1-16.02.0/armv8/le/aarch64v8-marvell-linux-gnu-5.2.1_i686_20151110/bin/aarch64-linux-gnu-gcc $(CFLAGS) -c -o $@ $<

event_sig.o: event_sig.c $(HDRS)
	/home/zhangyg/software/marvell-gcc-5.2.1-16.02.0/marvell-gcc-5.2.1-16.02.0/armv8/le/aarch64v8-marvell-linux-gnu-5.2.1_i686_20151110/bin/aarch64-linux-gnu-gcc $(CFLAGS) -c -o $@ $<

event_tcp.o: event_tcp.c $(HDRS)
	/home/zhangyg/software/marvell-gcc-5.2.1-16.02.0/marvell-gcc-5.2.1-16.02.0/armv8/le/aarch64v8-marvell-linux-gnu-5.2.1_i686_20151110/bin/aarch64-linux-gnu-gcc $(CFLAGS) -c -o $@ $<

clean: FORCE
	rm -f *.a *.o *~

FORCE:

.phony: FORCE
