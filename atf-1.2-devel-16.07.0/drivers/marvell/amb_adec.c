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
#include <plat_config.h>

#if LOG_LEVEL >= LOG_LEVEL_INFO
#define DEBUG_ADDR_MAP
#endif

/* common defines */
#define WIN_ENABLE_BIT			(0x1)

#define AMB_WIN_CR_OFFSET(win)		(amb_base + 0x0 + (0x8 * win))
#define AMB_ATTR_OFFSET			8
#define AMB_ATTR_MASK			0xFF

#define AMB_WIN_BASE_OFFSET(win)	(amb_base + 0x4 + (0x8 * win))
#define AMB_BASE_OFFSET			16

uintptr_t amb_base;

static void amb_enable_win(struct amb_win *win, uint32_t win_num)
{
	uint32_t ctrl, base;

	ctrl = (win->attribute << AMB_ATTR_OFFSET) | WIN_ENABLE_BIT;
	base = win->base_addr << AMB_BASE_OFFSET;

	mmio_write_32(AMB_WIN_BASE_OFFSET(win_num), base);
	mmio_write_32(AMB_WIN_CR_OFFSET(win_num), ctrl);
}

#ifdef DEBUG_ADDR_MAP
static void dump_amb_adec(void)
{
	uint32_t ctrl, base, win_id, attr;

	/* Dump all AMB windows */
	printf("bank  attribute     base\n");
	printf("------------------------------\n");
	for (win_id = 0; win_id < AMB_MAX_WIN_ID; win_id++) {
		ctrl = mmio_read_32(AMB_WIN_CR_OFFSET(win_id));
		if (ctrl & WIN_ENABLE_BIT) {
			base = mmio_read_32(AMB_WIN_BASE_OFFSET(win_id));
			attr = (ctrl >> AMB_ATTR_OFFSET) & AMB_ATTR_MASK;
			printf("amb   0x%04x        0x%08x\n", attr, base);
		}
	}

	return;
}
#endif

int init_amb_adec(int cp_index)
{
	struct amb_win *win;
	uint32_t win_id, win_reg;
	uint32_t win_count;

	INFO("Initializing AXI to MBus Bridge Address decoding\n");

	/* Get the base address of the AMB address decoding */
	amb_base = marvell_get_amb_reg_offs(cp_index);

	/* Get the array of the windows and its size */
	marvell_get_amb_memory_map(&win, &win_count);
	if (win_count <= 0)
		INFO("no windows configurations found\n");

	if (win_count > AMB_MAX_WIN_ID) {
		INFO("number of windows is bigger than %d\n", AMB_MAX_WIN_ID);
		return 0;
	}

	/* disable all AMB windows */
	for (win_id = 0; win_id < AMB_MAX_WIN_ID; win_id++) {
		win_reg = mmio_read_32(AMB_WIN_CR_OFFSET(win_id));
		win_reg &= ~WIN_ENABLE_BIT;
		mmio_write_32(AMB_WIN_CR_OFFSET(win_id), win_reg);
	}

	/* enable relevant windows */
	for (win_id = 0; win_id < win_count; win_id++, win++)
		amb_enable_win(win, win_id);

#ifdef DEBUG_ADDR_MAP
	dump_amb_adec();
#endif

	INFO("Done AXI to MBus Bridge Address decoding Initializing\n");

	return 0;
}
