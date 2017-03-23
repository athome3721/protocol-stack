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


#define MVEBU_MAX_CPUS_PER_CLUSTER	2

#define MVEBU_PRIMARY_CPU		0x0

/*
 * The counter on A3700 is always fed from reference 25M clock (XTAL).
 * However minimal CPU counter prescaler is 2, so the counter
 * frequency will be divided by 2, the number is 12.5M
 */
#define COUNTER_FREQUENCY		12500000

#define MVEBU_REGS_BASE			0xD0000000

/*******************************************************************************
 * MVEBU memory map related constants
 ******************************************************************************/

/* Aggregate of all devices in the first GB */
#define DEVICE0_BASE			MVEBU_REGS_BASE
#define DEVICE0_SIZE			0x10000000

/*******************************************************************************
 * GIC-500 & interrupt handling related constants
 ******************************************************************************/
/* Base MVEBU compatible GIC memory map */
#define MVEBU_GICD_BASE			0x1D00000
#define MVEBU_GICR_BASE			0x1D40000
#define MVEBU_GICC_BASE			0x1D80000

/*******************************************************************************
 * GPIO registers related constants
 ******************************************************************************/
/* north bridge GPIO register base address */
#define MVEBU_GPIO_NB_REG_BASE			(MVEBU_REGS_BASE + 0x13800)
/* north Bridge GPIO selection regsiter */
#define MVEBU_GPIO_NB_SEL_REG			(MVEBU_GPIO_NB_REG_BASE + 0x30)
/* I2C1 GPIO Enable bit offset */
#define MVEBU_GPIO_TW1_GPIO_EN_OFF		(10)

/*******************************************************************************
 * I2C related constants
 ******************************************************************************/
/* I2C register base address*/
#define MVEBU_I2C_REGS_BASE			(MVEBU_REGS_BASE + 0x11000)

/* CCI-400 */
#define MVEBU_CCI_BASE			(MVEBU_REGS_BASE + 0x8000000)
#define MVEBU_CCI_S3_SNOOP_CTRL_REG	(MVEBU_CCI_BASE + 0x4000)

#endif /* __MVEBU_DEF_H__ */
