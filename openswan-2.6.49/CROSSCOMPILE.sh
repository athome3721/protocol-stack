#!/bin/sh
#
# cross compile example
#


#export PREFIX=/volquad/arm-4.0.2
export PREFIX=/home/zhangyg/software/marvell-gcc-5.2.1-16.02.0/marvell-gcc-5.2.1-16.02.0/armv8/le/aarch64v8-marvell-linux-gnu-5.2.1_i686_20151110
export DESTDIR=/tmp/openswan.arm

export ARCH=arm
export CC=$PREFIX/bin/aarch64-linux-gnu-gcc
export GCC=$PREFIX/bin/aarch64-linux-gnu-gcc
export LD=$PREFIX/bin/aarch64-linux-gnu-ld
export RANLIB=$PREFIX/bin/aarch64-linux-gnu-ranlib
export AR=$PREFIX/bin/aarch64-linux-gnu-ar
export AS=$PREFIX/bin/aarch64-linux-gnu-as
export STRIP=$PREFIX/bin/aarch64-linux-gnu-strip
export LD_LIBRARY_PATH=$PREFIX/aarch64-linux-gnu/libc/usr/lib/
export PATH=$PATH:$PREFIX/bin
export USERCOMPILE="-Wl,-elf2flt -DCOMPILER_HAS_NO_PRINTF_LIKE -O3 -g ${PORTDEFINE} -I$PREFIX/aarch64-linux-gnu/libc/usr/include -L$LD_LIBRARY_PATH -DGCC_LINT -DLEAK_DETECTIVE -Dlinux -D__linux__"
export WERROR=' ' 

#now you can run:
# make programs
#and binaries will appear in OBJ.linux.$ARCH/
#and run:
# make install
#and the install will go into $DESTDIR/

# note: the arm_tools I had failed to compile PRINTF_LIKE(x), so the code
# for that was  ifdef'ed with #ifndef COMPILER_HAS_NO_PRINTF_LIKE statements.
# Add -DCOMPILER_HAS_NO_PRINTF_LIKE to enable the workaround.

# EXECUTABLE FILE FORMAT
#
# Some uClibc/busybox combinations use different executable files formats from
# ELF. This is configured during Linux kernel build. One common format is
# the BLFT file format. Do not manually convert ELF binaries to BLTF using
# elf2flt as that will create invalid binaries. Instead add -Wl,-elf2flt to
# your flags (CFLAGS / LDFLAGS / USERCOMPILE)
