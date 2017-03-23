/*
* ***************************************************************************
* Copyright (C) 2016 Marvell International Ltd.
* ***************************************************************************
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* Redistributions of source code must retain the above copyright notice, this
* list of conditions and the following disclaimer.
*
* Redistributions in binary form must reproduce the above copyright notice,
* this list of conditions and the following disclaimer in the documentation
* and/or other materials provided with the distribution.
*
* Neither the name of Marvell nor the names of its contributors may be used
* to endorse or promote products derived from this software without specific
* prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
* OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
***************************************************************************
*/

#ifndef __PLATFORM_DEF_H__
#define __PLATFORM_DEF_H__

#include <board_marvell_def.h>
#include <plat_def.h>
#ifndef __ASSEMBLY__
#include <stdio.h>
#endif /* __ASSEMBLY__ */

/*
 * Most platform porting definitions provided by included headers
 */

/*
 * DRAM Memory layout:
		+-----------------------+
		:			:
		:	Linux		:
0x04X00000 --->	+-----------------------+
		|	BL3-3(u-boot)	|>>>>>>>}>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
		|-----------------------|	}						|
		|	BL3-[0,1, 2]	|	}---------------------------------------->	|
		|-----------------------|	}					||	|
		|	BL2		|	}->FIP (loaded by BootROM to DRAM)	||	|
		|-----------------------|	}					||	|
		|	FIP_TOC		|	}					||	|
0x04120000 --->	|-----------------------|						||	|
		|	BL1 (RO)	|						||	|
0x04100000 --->	+-----------------------+						||	|
		:			:						||	|
		: Trusted SRAM section	:						\/	|
0x04040000 --->	+-----------------------+	Replaced by BL2		+----------------+	|
		|	BL1 (RW)	|	<<<<<<<<<<<<<<<<<<	| BL3-1 NOBITS	 |	|
0x04037000 --->	|-----------------------|	<<<<<<<<<<<<<<<<<<	|----------------|	|
		|			|	<<<<<<<<<<<<<<<<<<	| BL3-1 PROGBITS |	|
0x04023000 --->	|-----------------------|				+----------------+	|
		|	BL2		|
		|-----------------------|
		|			|
0x04001000 --->	|-----------------------|
		|	Shared		|
0x04000000 --->	+-----------------------+
		:			:
		:	Linux		:
		:			:
		|-----------------------|
		|			|	U-Boot(BL3-3) Loaded by BL2			|
		|	U-Boot		|	<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
0x00000000 --->	+-----------------------+

Trusted SRAM section 0x4000000..0x4200000:
----------------------------------------
 * SRAM_BASE		= 0x4001000
 * BL2_BASE			= 0x4006000
 * BL2_LIMIT		= BL31_BASE
 * BL31_BASE		= 0x4023000 = (64MB + 256KB - 0x1D000)
 * BL31_PROGBITS_LIMIT	= BL1_RW_BASE
 * BL1_RW_BASE		= 0x4037000 = (64MB + 256KB - 0x9000)
 * BL1_RW_LIMIT		= BL31_LIMIT = 0x4040000
 *
 *
 * PLAT_MARVELL_FIP_BASE	= 0x4120000
 */

/* since BL33 is loaded by BL2 (and validated by BL31) to DRAM offset 0,
   it is allowed to load/copy images to 'NULL' pointers */
#if defined(IMAGE_BL2) || defined(IMAGE_BL31)
#define PLAT_ALLOW_ZERO_ADDR_COPY
#endif

#define PLAT_MARVELL_SRAM_BASE	0xFFE1C048
#define PLAT_MARVELL_SRAM_END	0xFFE3C000

#define PLAT_MARVELL_ATF_BASE			0x4000000
#define PLAT_MARVELL_ATF_LOAD_ADDR		(PLAT_MARVELL_ATF_BASE + 0x100000)

#define PLAT_MARVELL_FIP_BASE			(PLAT_MARVELL_ATF_LOAD_ADDR + 0x20000)
#define PLAT_MARVELL_FIP_MAX_SIZE		0x4000000

#ifdef PLAT_MARVELL_APN_806_Z
#define PLAT_MARVELL_CLUSTER_COUNT		4
#define PLAT_MARVELL_CLUSTER_CORE_COUNT		1
#else
#define PLAT_MARVELL_CLUSTER_COUNT		2
#define PLAT_MARVELL_CLUSTER_CORE_COUNT		2
#endif

#define PLAT_MARVELL_CORE_COUNT			(PLAT_MARVELL_CLUSTER_COUNT * PLAT_MARVELL_CLUSTER_CORE_COUNT)

#define PLAT_MARVELL_TRUSTED_ROM_BASE	PLAT_MARVELL_ATF_LOAD_ADDR	/* DRAM[2MB..66MB] is used as Trusted ROM */
#define PLAT_MARVELL_TRUSTED_ROM_SIZE	0x04000000	/* 64 MB TODO: reduce this to minimum needed according
								to fip image size*/

#define PLAT_MARVELL_TRUSTED_DRAM_BASE	0x06000000	/* TODO: update SCP (Secure PayLoad) Trusted DRAM actual
								BASE & size */
#define PLAT_MARVELL_TRUSTED_DRAM_SIZE	0x02000000	/* 32 MB */

/* GIC related definitions */
#define PLAT_MARVELL_GICD_BASE			(MVEBU_REGS_BASE + MVEBU_GICD_BASE)
#define PLAT_MARVELL_GICC_BASE			(MVEBU_REGS_BASE + MVEBU_GICC_BASE)

#define PLAT_MARVELL_G0_IRQS			MARVELL_G1S_IRQS
#define PLAT_MARVELL_G1S_IRQS			MARVELL_G0_IRQS

#define PLAT_MARVELL_SHARED_RAM_CACHED	1

/*
 * Load address of BL3-3 for this platform port
 */
#if PALLADIUM
#define PLAT_MARVELL_NS_IMAGE_OFFSET	0x1000
#else
#define PLAT_MARVELL_NS_IMAGE_OFFSET	0x0
#endif

/* System Reference Clock*/
#define PLAT_REF_CLK_IN_HZ				COUNTER_FREQUENCY

/*
 * PL011 related constants
 */
#define PLAT_MARVELL_BOOT_UART_BASE			(MVEBU_REGS_BASE + 0x512000)
#if PALLADIUM
#define PLAT_MARVELL_BOOT_UART_CLK_IN_HZ		384000
#else
#define PLAT_MARVELL_BOOT_UART_CLK_IN_HZ		200000000
#endif

#define PLAT_MARVELL_CRASH_UART_BASE			PLAT_MARVELL_BOOT_UART_BASE
#define PLAT_MARVELL_CRASH_UART_CLK_IN_HZ		PLAT_MARVELL_BOOT_UART_CLK_IN_HZ

#define PLAT_MARVELL_BL31_RUN_UART_BASE			PLAT_MARVELL_BOOT_UART_BASE
#define PLAT_MARVELL_BL31_RUN_UART_CLK_IN_HZ	PLAT_MARVELL_BOOT_UART_CLK_IN_HZ

/* Required platform porting definitions */
#define PLAT_MAX_PWR_LVL				MPIDR_AFFLVL1

/* System timer related constants */
#define PLAT_MARVELL_NSTIMER_FRAME_ID		1


#endif /* __PLATFORM_DEF_H__ */
