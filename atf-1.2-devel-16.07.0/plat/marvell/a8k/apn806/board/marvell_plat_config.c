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

#include <plat_config.h>
#include <plat_def.h>


/*******************************************************************************
 * RFU Configuration
 ******************************************************************************/
struct rfu_win rfu_memory_map[] = {
	{0x0,	0xfe000000,	0x0,	0x1f00000,	PCIE_PORT_TID}, /* PCIe window 31Mb for PCIe port*/
	{0x0,	0xffe00000,	0x0,	0x100000,	PCIE_REGS_TID}, /* PCI-REG window 64Kb for PCIe-reg*/
	{0x0,	0xf9100000,	0x0,	0x100000,	MCIPHY_TID},	/* MCI window  1Mb for PHY-reg*/
};

uintptr_t marvell_get_rfu_reg_offs(void)
{
	return MVEBU_RFU_BASE;
}

int marvell_get_rfu_memory_map(struct rfu_win **win, uint32_t *size)
{
	*win = rfu_memory_map;
	*size = sizeof(rfu_memory_map)/sizeof(struct rfu_win);

	return 0;
}

/*******************************************************************************
 * IOB Configuration
 ******************************************************************************/
#define MARVELL_IOB_MAX_WIN	16

struct iob_win iob_memory_map[] = {
	{0x0,	0xf7000000,	0x0,	0x1000000,	PEX1_TID}, /* PEX1_X1 window */
	{0x0,	0xf8000000,	0x0,	0x1000000,	PEX2_TID}, /* PEX2_X1 window */
	{0x0,	0xf6000000,	0x0,	0x1000000,	PEX0_TID}, /* PEX0_X4 window */
};

uintptr_t marvell_get_iob_reg_offs(int cp_index)
{
	return MVEBU_IOB_BASE(0);
}

int marvell_get_iob_max_win(void)
{
	return MARVELL_IOB_MAX_WIN;
}

int marvell_get_iob_memory_map(struct iob_win **win, uint32_t *size, int cp_index)
{
	*win = iob_memory_map;
	*size = sizeof(iob_memory_map)/sizeof(struct iob_win);

	return 0;
}

/*******************************************************************************
 * CCU Configuration
 ******************************************************************************/
#define MARVELL_CCU_MAX_WIN	8

struct ccu_win ccu_memory_map[] = {
	{0x0,	0xf2000000,	0x0,	0xe000000,	IO_0_TID}, /* IO window */
};

uintptr_t marvell_get_ccu_reg_offs(void)
{
	return MVEBU_CCU_BASE;
}

int marvell_get_ccu_max_win(void)
{
	return MARVELL_CCU_MAX_WIN;
}

int marvell_get_ccu_memory_map(struct ccu_win **win, uint32_t *size)
{
	*win = ccu_memory_map;
	*size = sizeof(ccu_memory_map)/sizeof(struct ccu_win);

	return 0;
}
