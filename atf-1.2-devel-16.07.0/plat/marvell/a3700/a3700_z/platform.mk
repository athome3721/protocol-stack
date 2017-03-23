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

PLAT_FAMILY		:= a3700
PLAT_FAMILY_BASE	:= plat/marvell/$(PLAT_FAMILY)
PLAT_SRC_BASE		:= $(PLAT_FAMILY_BASE)/$(PLAT)
PLAT_INCLUDE_BASE	:= include/plat/marvell/$(PLAT_FAMILY)

CALL_DOIMAGE		:= y
# This define is used in BL31 linker script to make sure
# the PSCI code is alligned to 64KB
$(eval $(call add_define,PLAT_MARVELL_7000_Z0))

# GICV3
$(eval $(call add_define,CONFIG_GICV3))

MARVELL_GIC_SOURCES	:=	drivers/arm/gic/common/gic_common.c	\
				drivers/arm/gic/v3/gicv3_main.c		\
				drivers/arm/gic/v3/gicv3_helpers.c	\
				plat/common/plat_gicv3.c

ATF_INCLUDES		:=	-Iinclude/common/tbbr		\
				-Iinclude/drivers

PLAT_INCLUDES		:=	-I$(PLAT_FAMILY_BASE)/$(PLAT)			\
				-I$(PLAT_FAMILY_BASE)/$(PLAT)/include		\
				-I$(PLAT_INCLUDE_BASE)/$(PLAT)/board/common	\
				-I$(PLAT_INCLUDE_BASE)/common			\
				-I$(PLAT_INCLUDE_BASE)/common/aarch64		\
				-I$(PLAT_SRC_BASE)				\
				-Idrivers/marvell/uart				\
				${ATF_INCLUDES}

PLAT_BL_COMMON_SOURCES	:=	$(PLAT_SRC_BASE)/aarch64/a3700_z_common.c	\
				drivers/console/console.S			\
				drivers/marvell/uart/a3700_console.S

BL1_SOURCES		+=	$(PLAT_SRC_BASE)/aarch64/plat_helpers.S	\
				lib/cpus/aarch64/cortex_a53.S

BL31_SOURCES		+=	lib/cpus/aarch64/cortex_a53.S		\
				$(PLAT_SRC_BASE)/aarch64/plat_helpers.S	\
				$(PLAT_SRC_BASE)/aarch64/plat_psci.S	\
				$(PLAT_SRC_BASE)/plat_pm.c		\
				$(PLAT_SRC_BASE)/plat_topology.c	\
				$(PLAT_SRC_BASE)/plat_bl31_setup.c	\
				plat/marvell/common/sys_info.c		\
				plat/marvell/common/marvell_gicv3.c	\
				plat/marvell/common/plat_delay_timer.c	\
				drivers/delay_timer/delay_timer.c	\
				drivers/marvell/i2c/a3700_i2c.c		\
				${MARVELL_GIC_SOURCES}

# Disable the PSCI platform compatibility layer (allows porting from Old Platform APIs
# to the new APIs).
# It is not needed since Marvell platform already used the new platform APIs.
ENABLE_PLAT_COMPAT	:= 	0

include plat/marvell/common/marvell_common.mk
