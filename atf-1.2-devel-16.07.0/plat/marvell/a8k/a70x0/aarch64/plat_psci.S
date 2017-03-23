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
/*
 * Copyright (C) 2013 - ARM Ltd
 * Author: Marc Zyngier <marc.zyngier@arm.com>
 *
 * Based on code by Carl van Schaik <carl@ok-labs.com>.
 *
 * Copyright (C) 2015 Marvell International Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 2 of the License, or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * ***************************************************************************
*/

#include <plat_def.h>
#include <asm/macro.h>

#define MVEBU_CCU_HTC_ASET_REG	0x4264
#define MVEBU_PRIVATE_UID_REG	0x30
#define MVEBU_IO_AFFINITY		0xF00
#define MVEBU_RFU_GLOBL_SW_RST	0x84
#define ARM_PSCI_RET_SUCCESS	0

#define MVEBU_CCU_RVBAR(i)	(0x640 + (i * 4))

.pushsection ._secure.text, "ax"

/*******************************************************************************
 * A8K cpu entry.
 * This function implements WA of entry point alignment.
 * A8K jump address (in SMP mode) must be alogned to 65KB. Since Linux jump
 * address is not aliogned, this function is used and it will set the jump
 * address which was passed to the CPU on SMC
 ******************************************************************************/
.global _armada8k_cpu_entry
_armada8k_cpu_entry:
	/* get current CPU */
	mrs 	x2, MPIDR_EL1   	/* get current CPU - Use affinity level 1 */
	asr 	x2, x2, #8
	and 	x2, x2, #0xff

	/* set CPU private UID */
	mov	x0, #(MVEBU_REGS_BASE)
	add	x3, x0, #(MVEBU_PRIVATE_UID_REG)
	add     x1, x2, #0x4
	str 	w1, [x3]

	bl	enable_affinity

	isb

	/*
	 * Could be EL3/EL2/EL1, Initial State:
	 * Little Endian, MMU Disabled, i/dCache Disabled
	 */
	/* Update vectors table address (which was obtained from Master) */
	adr	x0, _vectors
	ldr	x0, [x0]

	switch_el x1, 3f, 2f, 1f
3:	msr	vbar_el3, x0
	mrs	x0, scr_el3
	orr	x0, x0, #0xf			/* SCR_EL3.NS|IRQ|FIQ|EA */
	msr	scr_el3, x0
	msr	cptr_el3, xzr			/* Enable FP/SIMD */
	ldr	x0, =COUNTER_FREQUENCY
	msr	cntfrq_el0, x0			/* Initialize CNTFRQ */
	b	0f
2:	msr	vbar_el2, x0
	mov	x0, #0x33ff
	msr	cptr_el2, x0			/* Enable FP/SIMD */
	b	0f
1:	msr	vbar_el1, x0
	mov	x0, #3 << 20
	msr	cpacr_el1, x0			/* Enable FP/SIMD */
0:


	bl	psci_build_stack

	bl	l2_setup

	bl	gicv2_pcpu_distif_init

	bl	gicv2_cpuif_enable

	bl	armv8_switch_to_el2
#ifdef CONFIG_ARMV8_SWITCH_TO_EL1
	bl	armv8_switch_to_el1
#endif

	/* Get linux start address - we use RVBARR for CPU's 2-3 as a WA. */
	mrs 	x2, MPIDR_EL1   	/* get current CPU - Use affinity level 1 */
	and	x5, x2, #0x3

	mov	x0, #(MVEBU_REGS_BASE)
	mov	x2, #(MVEBU_CCU_RVBAR(2))
	add	x2, x2, x5, lsl #2
	orr     x2, x2, x0
	ldr     w0, [x2]

	br	x0

/*******************************************************************************
 * This function saves Linux entry point which was passed by the SMC.
 * It is required since ATF PSCI flow passed only the target CPU to CPU on
 * routine. Therefore, the jump address should be saved before.
 *
 * Parameters:
 * 		x0 = entry point
 ******************************************************************************/
.global psci_save_cpu_entrypoint
psci_save_cpu_entrypoint:
	adr	x2, _target_pc
	str	x0, [x2]
	ret

.global enable_affinity
enable_affinity:

	/* get current CPU */
	mrs 	x2, MPIDR_EL1   	/* get current CPU - Use affinity level 1 */
	asr 	x2, x2, #8
	and 	x2, x2, #0xff

	/* Activate Affinity between current CPU */
	mov	x0, #(MVEBU_REGS_BASE)
	mov     x3, #(MVEBU_CCU_HTC_ASET_REG)
	orr     x0, x3, x0
	mov	x3, #0x1
	lsl     x1, x3, x2
	orr	x1, x1, #(MVEBU_IO_AFFINITY)
	str     w1, [x0]

	/* Activate Affinity in CA-57 configuration
	 * Enable the SMPEN bit in CPUECTLR_EL1 */
	mrs x0, S3_1_c15_c2_1
	orr x0, x0, #0x40
	msr S3_1_c15_c2_1, x0
	ret

l2_setup:
	stp     x29, x30, [sp,#-16]!
	bl llc_is_exclusive
	cmp w0, #1
	bne 1f
        mrs x5, s3_1_c15_c0_0 /* L2 Aux Ctrl */
        orr x5, x5, #(1 << 14) /* Enable UniqueClean evictions with data */
        msr s3_1_c15_c0_0, x5 /* L2 Aux Ctrl */
1:
	ldp     x29, x30, [sp],#16
        ret

.globl	psci_arch_init
psci_arch_init:
	add	x29, x30, 0 /* keep return address */
	bl	enable_affinity
	bl	l2_setup
	ret	x29

psci_build_stack:

	mrs     x5, SCR_EL3
	bic	x5, x5, #1	/* Secure mode */
	msr	SCR_EL3, x5
	isb

	mrs 	x4, MPIDR_EL1	/* get current CPU - Use affinity level 1 */
	asr 	x4, x4, #8
	and 	x4, x4, #0xff

	mov	x5, #400		/* 1kB of stack per CPU */
	mul	x4, x4, x5

	adr	x5, text_end		/* end of text */
	add	x5, x5, #0x2000		/* Skip two pages */
	lsr	x5, x5, #12		/* Align to start of page */
	lsl	x5, x5, #12
	sub	sp, x5, x4		/* here's our stack! */

	ret

.globl	psci_0_2_system_reset
psci_0_2_system_reset:
	mov	x0, #(MVEBU_RFU_BASE)
	add	x3, x0, #(MVEBU_RFU_GLOBL_SW_RST)
	mov	w0, #0
	str	w0, [x3]
	ret

/* x0 = target CPU */
.globl	psci_0_2_cpu_on_64
psci_0_2_cpu_on_64:
	mov 	x1, x0

	dsb     sy

	/* read vbar from master CPU and save it
	   for later use when the slave CPUs are awaken */
	mrs	x3, vbar_el1		/* Obtain vectors table address (for EL1) from Master */
	adr	x2, _vectors
	str	x3, [x2]		/* Store vectors table address for slaves */

	/* get cpu number - use CPU ID */
	and 	x5, x1, #0x3

	/* get cluster number - use affinity level 1 */
	asr 	x1, x1, #8
	and 	x1, x1, #0xff

	/* set CPU private UID */
	mov	x0, #(MVEBU_REGS_BASE)
	add	x3, x0, #(MVEBU_PRIVATE_UID_REG)
	add     x2, x1, #0x4
	str 	w2, [x3]

	/* set the cpu start address */
	mov	x2, #(MVEBU_CCU_RVBAR(0))
	add	x2, x2, x5, lsl #2
	add	x3, x0, x2

	/* CPU reset vector address - must be aligned to 0x10000
	   first instruction - jump to _armada8k_cpu_entry */
	adr     x2, _armada8k_cpu_entry
	lsr	x2, x2, #16	/* align to 0x10000 */
	str 	w2, [x3]

	/* Save the Linux out of reset address to unused register.
	** We used the RVBAR for CPU's 2-3 to store the Linux return address
	** for CPUs 0 & 1. */
	adr	x1, _target_pc
	ldr	x1, [x1]
	mov	x2, #(MVEBU_CCU_RVBAR(2))
	add	x2, x2, x5, lsl #2
	add	x3, x0, x2
	str     w1, [x3]

	/* get the cpu out of reset */
	mov	x2, #0x650
	add	x2, x2, x5, lsl #2
	add	x3, x0, x2
	movz 	x2, #0x1, LSL #16
	add	x2, x2, #0x1
	str 	w2, [x3]

	/* return success */
	mov	x0, #ARM_PSCI_RET_SUCCESS	/* Return PSCI_RET_SUCCESS */
	ret

	/* 64 bit alignment for elements accessed as data */
	.align 4
_target_pc:
	.quad 0x0

_vectors:
	.quad 0x0

text_end:
	.popsection
