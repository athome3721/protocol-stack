#
# ***************************************************************************
# Copyright (C) 2016 Marvell International Ltd.
# ***************************************************************************
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# Redistributions of source code must retain the above copyright notice, this
# list of conditions and the following disclaimer.
#
# Redistributions in binary form must reproduce the above copyright notice,
# this list of conditions and the following disclaimer in the documentation
# and/or other materials provided with the distribution.
#
# Neither the name of Marvell nor the names of its contributors may be used
# to endorse or promote products derived from this software without specific
# prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
# OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#

# Use a70x0 platform sources since a80x0 uses the same code
PLAT_SRC		:= a70x0
PLAT_SOC		?= $(PLAT)
PLAT_FAMILY		:= a8k
PLAT_FAMILY_BASE	:= plat/marvell/$(PLAT_FAMILY)
PLAT_SRC_BASE		:= $(PLAT_FAMILY_BASE)/$(PLAT_SRC)
PLAT_INCLUDE_BASE	:= include/plat/marvell/$(PLAT_FAMILY)
MARVELL_DRV_BASE	:= drivers/marvell

CALL_DOIMAGE		:= y
# This define is used in BL31 linker script to make sure
# the PSCI code is alligned to 64KB
$(eval $(call add_define,PLAT_MARVELL_7040_RZ1))

MARVELL_GIC_SOURCES	:=	drivers/arm/gic/common/gic_common.c	\
				drivers/arm/gic/v2/gicv2_main.c				\
				drivers/arm/gic/v2/gicv2_helpers.c			\
				plat/common/plat_gicv2.c

ATF_INCLUDES		:=	-Iinclude/common/tbbr

PLAT_INCLUDES		:=	-I$(PLAT_FAMILY_BASE)/$(PLAT_SOC)		\
				-I$(PLAT_FAMILY_BASE)/$(PLAT_SRC)/include	\
				-I$(PLAT_INCLUDE_BASE)/$(PLAT_SRC)/board/common	\
				-I$(PLAT_INCLUDE_BASE)/$(PLAT_SRC)/board	\
				-I$(PLAT_INCLUDE_BASE)/common			\
				-I$(PLAT_INCLUDE_BASE)/common/aarch64		\
				-I$(PLAT_SRC_BASE)				\
				-Iinclude/drivers/marvell			\
				${ATF_INCLUDES}

PLAT_BL_COMMON_SOURCES	:=	$(PLAT_SRC_BASE)/aarch64/a7040_rz_common.c	\
				drivers/console/console.S			\
				drivers/ti/uart/16550_console.S

BLE_PORTING_SOURCES	:=	$(PLAT_FAMILY_BASE)/$(PLAT_SOC)/board/dram_port.c

BLE_SOURCES		:=	plat/marvell/common/sys_info.c			\
				plat/marvell/common/dram_setup.c		\
				$(BLE_PORTING_SOURCES)

BL1_SOURCES		+=	$(PLAT_SRC_BASE)/aarch64/plat_helpers.S	\
				lib/cpus/aarch64/cortex_a72.S

ifeq (${PALLADIUM}, 1)
BL1_SOURCES		+=	$(PLAT_SRC_BASE)/plat_bl1_setup.c
endif

MARVELL_DRV		:= 	$(MARVELL_DRV_BASE)/rfu.c	\
				$(MARVELL_DRV_BASE)/iob.c	\
				$(MARVELL_DRV_BASE)/ccu.c	\
				$(MARVELL_DRV_BASE)/icu.c	\
				$(MARVELL_DRV_BASE)/amb_adec.c	\
				$(MARVELL_DRV_BASE)/cache_llc.c


BL31_PORTING_SOURCES	:=	$(PLAT_FAMILY_BASE)/$(PLAT_SOC)/board/marvell_plat_config.c

BL31_SOURCES		+=	lib/cpus/aarch64/cortex_a72.S				\
				$(PLAT_SRC_BASE)/aarch64/plat_helpers.S			\
				$(PLAT_SRC_BASE)/aarch64/plat_psci.S			\
				$(PLAT_SRC_BASE)/plat_pm.c				\
				$(PLAT_SRC_BASE)/plat_topology.c			\
				$(PLAT_SRC_BASE)/plat_bl31_setup.c			\
				$(PLAT_SRC_BASE)/apn806_setup.c				\
				$(PLAT_SRC_BASE)/cp110_setup.c				\
				plat/marvell/common/marvell_gicv2.c			\
				${BL31_PORTING_SOURCES}					\
				${MARVELL_DRV}						\
				${MARVELL_GIC_SOURCES}

# Disable the PSCI platform compatibility layer (allows porting from Old Platform APIs
# to the new APIs).
# It is not needed since Marvell platform already used the new platform APIs.
ENABLE_PLAT_COMPAT	:= 	0

include plat/marvell/common/marvell_common.mk
