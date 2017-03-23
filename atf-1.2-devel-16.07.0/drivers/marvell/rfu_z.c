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

#include <plat_def.h>
#include <debug.h>
#include <mmio.h>
#include <mvebu.h>
#include <rfu.h>
#include <plat_config.h>

#if LOG_LEVEL >= LOG_LEVEL_INFO
#define DEBUG_ADDR_MAP
#endif

/* common defines */
#define WIN_ENABLE_BIT			(0x1)
/* Physical address of the base of the window = {Addr[19:0],20`h0} */
#define ADDRESS_SHIFT			(20 - 4)
#define ADDRESS_MASK			(0xFFFFFFF0)
#define RFU_WIN_ALIGNMENT_1M		(0x100000)
#define RFU_WIN_ALIGNMENT_64K		(0x10000)

uintptr_t rfu_base;


static void rfu_win_check(struct rfu_win *win, uint32_t win_num)
{
	uint64_t base_addr, win_size;
	uint32_t alignment_value = RFU_WIN_ALIGNMENT_1M;

	/* for RFU The base is always 1M aligned */
	/* check if address is aligned to 1M */
	base_addr = ((uint64_t)win->base_addr_high << 32) + win->base_addr_low;
	if (IS_NOT_ALIGN(base_addr, RFU_WIN_ALIGNMENT_1M)) {
		base_addr = ALIGN_UP(base_addr, RFU_WIN_ALIGNMENT_1M);
		ERROR("Window %d: base address unaligned to 0x%x\n", win_num, RFU_WIN_ALIGNMENT_1M);
		printf("Align up the base address to 0x%lx\n", base_addr);
		win->base_addr_high = (uint32_t)(base_addr >> 32);
		win->base_addr_low = (uint32_t)(base_addr);
	}

	/* targets that have AHR must have size aligned to 1M.
	   targets with no AHR (pcie-reg, bootrom) have a fixed size of 64k */
	if (win->target_id == BOOTROM_TID || win->target_id == PCIE_REGS_TID)
		alignment_value = RFU_WIN_ALIGNMENT_64K;

	/* size parameter validity check */
	win_size = ((uint64_t)win->win_size_high << 32) + win->win_size_low;
	if (IS_NOT_ALIGN(win_size, alignment_value)) {
		win_size = ALIGN_UP(win_size, alignment_value);
		ERROR("Window %d: window size unaligned to 0x%x\n", win_num, alignment_value);
		printf("Aligning size to 0x%lx\n", win_size);
		win->win_size_high = (uint32_t)(win_size >> 32);
		win->win_size_low = (uint32_t)(win_size);
	}
}

static uintptr_t rfu_alr_offset_get(uint32_t trgt_id)
{
	uint32_t rfu_alr_offset[RFU_MAX_TID] = {0x0, 0x10, 0x20, 0x208, 0x210, 0x218};

	if (trgt_id < 0 || trgt_id > RFU_MAX_TID) {
		ERROR("target ID is wrong");
		return rfu_base;
	}
	return rfu_base + rfu_alr_offset[trgt_id];
}

static uintptr_t rfu_ahr_offset_get(uint32_t trgt_id)
{
	uint32_t rfu_ahr_offset[RFU_MAX_TID] = {0x0, 0x18, 0x28, 0x0, 0x214, 0x21c};

	if (trgt_id < 0 || trgt_id > RFU_MAX_TID) {
		ERROR("target ID is wrong");
		return rfu_base;
	}
	return rfu_base + rfu_ahr_offset[trgt_id];
}

static void rfu_enable_win(struct rfu_win *win, uint32_t trgt_id)
{
	uint32_t alr, ahr;
	uint64_t start_addr, end_addr;

	start_addr = ((uint64_t)win->base_addr_high << 32) + win->base_addr_low;
	end_addr = (start_addr + (((uint64_t)win->win_size_high << 32) + win->win_size_low) - 1);

	/* there's no ahr for bootrom and pcie-regs windows */
	if (trgt_id != BOOTROM_TID && trgt_id != PCIE_REGS_TID) {
		ahr = (uint32_t)((end_addr >> ADDRESS_SHIFT) & ADDRESS_MASK);
		mmio_write_32(rfu_ahr_offset_get(trgt_id), ahr);
	}

	alr = (uint32_t)((start_addr >> ADDRESS_SHIFT) & ADDRESS_MASK);
	if (trgt_id != PCIE_REGS_TID)
		alr |= WIN_ENABLE_BIT;
	mmio_write_32(rfu_alr_offset_get(trgt_id), alr);
}

#ifdef DEBUG_ADDR_MAP
static void dump_rfu(void)
{
	uint32_t trgt_id;
	uint32_t alr, ahr;
	uint64_t start, end;
	char *rfu_target_name[RFU_MAX_TID] = {"BootRoom ", "STM      ", "SPI      ",
					"PCIe-reg ", "MCI-Port ", "PCIe-Port"};

	/* Dump all RFU windows */
	printf("bank  target     start              end\n");
	printf("----------------------------------------------------\n");
	for (trgt_id = 0; trgt_id < RFU_MAX_TID; trgt_id++) {
		alr = mmio_read_32(rfu_alr_offset_get(trgt_id));
		if (alr & WIN_ENABLE_BIT) {
			alr &= ~WIN_ENABLE_BIT;
			if (trgt_id == BOOTROM_TID || trgt_id == PCIE_REGS_TID)
				ahr = alr;
			else
				ahr = mmio_read_32(rfu_ahr_offset_get(trgt_id));
			start = ((uint64_t)alr << ADDRESS_SHIFT);
			end = (((uint64_t)ahr + 0x10) << ADDRESS_SHIFT);
			printf("rfu   %s  0x%016lx 0x%016lx\n", rfu_target_name[trgt_id], start, end);
		}
	}
	printf("rfu   PIDI-port  - all other IO transactions\n");

	return;
}
#endif

int init_rfu(void)
{
	struct rfu_win *win;
	uint32_t win_id, win_reg, trgt_id;
	uint32_t win_count;

	INFO("Initializing RFU Address decoding\n");

	/* Get the base address of the address decoding MBUS */
	rfu_base = marvell_get_rfu_reg_offs();

	/* Get the array of the windows and its size */
	marvell_get_rfu_memory_map(&win, &win_count);
	if (win_count <= 0) {
		INFO("no windows configurations found\n");
		return 0;
	}

	/* disable all RFU windows */
	for (trgt_id = 0; trgt_id < RFU_MAX_TID; trgt_id++) {
		win_reg = mmio_read_32(rfu_alr_offset_get(trgt_id));
		win_reg &= ~WIN_ENABLE_BIT;
		mmio_write_32(rfu_alr_offset_get(trgt_id), win_reg);
	}

	for (win_id = 0; win_id < win_count; win_id++, win++) {
		rfu_win_check(win, win_id);
		rfu_enable_win(win, win->target_id);
	}

#ifdef DEBUG_ADDR_MAP
	dump_rfu();
#endif

	INFO("Done RFU Address decoding Initializing\n");

	return 0;
}
