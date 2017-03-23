#/bin/bash
export CROSS_CM3=/usr/bin/arm-linux-gnueabi-

export CROSS_COMPILE=/home/zhangyg/software/marvell-gcc-5.2.1-16.02.0/marvell-gcc-5.2.1-16.02.0/armv8/le/aarch64v8-marvell-linux-gnu-5.2.1_i686_20151110/bin/aarch64-linux-gnu-

export BL33=/home/zhangyg/software/UBoot/u-boot-160902/u-boot-2015.01-devel-16.09.2/u-boot.bin

make
sleep 6;
cd /home/zhangyg/software/ATF/atf-1.2-devel-16.07.0
make DEBUG=1 USE_COHERENT_MEM=0 LOG_LEVEL=20 PLAT=a3700_z all fip
sleep 4;
cd /home/zhangyg/software/ATF/atf-1.2-devel-16.07.0
cp build/a3700_z/debug/uart-images/*.bin /mnt/hgfs/BaiduYunDownload/debug/build/
cp build/a3700_z/debug/flash-image.bin /mnt/hgfs/BaiduYunDownload/debug/build/
