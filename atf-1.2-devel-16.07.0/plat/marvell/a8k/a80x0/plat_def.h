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

#ifndef __MVEBU_DEF_H__
#define __MVEBU_DEF_H__

#include <arm_def.h>


#define MVEBU_PRIMARY_CPU		0x0
#define CP_COUNT			2	/* A80x0 has both CP0 & CP1 */

#if PALLADIUM
#define COUNTER_FREQUENCY		48000
#else
#define COUNTER_FREQUENCY		25000000
#endif

#define MVEBU_REGS_BASE			0xF0000000
#define MVEBU_CP_REGS_BASE(cp_index)	(0xF2000000 + cp_index * 0x2000000)
#define MVEBU_RFU_BASE			(MVEBU_REGS_BASE + 0x6F0000)
#define MVEBU_CCU_BASE			(MVEBU_REGS_BASE + 0x4000)
#define MVEBU_LLC_BASE			(MVEBU_REGS_BASE + 0x8000)
#define MVEBU_IOB_BASE(cp_index)	(MVEBU_CP_REGS_BASE(cp_index) + 0x190000)
#define MVEBU_DRAM_MAC_BASE		(MVEBU_REGS_BASE + 0x20000)
#define MVEBU_DRAM_PHY_BASE		(MVEBU_REGS_BASE + 0x20000)
#define MVEBU_AMB_IP_BASE(cp_index)	(MVEBU_CP_REGS_BASE(cp_index) + 0x13ff00)
#define MVEBU_AMB_ADEC_BASE(cp_index)	(MVEBU_CP_REGS_BASE(cp_index) + 0x70ff00)
#define MVEBU_SMMU_BASE			(MVEBU_REGS_BASE + 0x100000)
#define MVEBU_CP_MPP_REGS(cp_index, n)	(MVEBU_CP_REGS_BASE(cp_index) + 0x440000 + ((n) << 2))

#define MVEBU_MCI_REG_BASE_REMAP(index) (0xFB000000 + (index * 0x2000000))

/*******************************************************************************
 * MVEBU memory map related constants
 ******************************************************************************/

/* Aggregate of all devices in the first GB */
#define DEVICE0_BASE			MVEBU_REGS_BASE
#define DEVICE0_SIZE			0x10000000

/*******************************************************************************
 * GIC-400 & interrupt handling related constants
 ******************************************************************************/
/* Base MVEBU compatible GIC memory map */
#define MVEBU_GICD_BASE			0x210000
#define MVEBU_GICC_BASE			0x220000

#endif /* __MVEBU_DEF_H__ */

