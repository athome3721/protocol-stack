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

#include <arch_helpers.h>
#include <plat_marvell.h>
#include <debug.h>
#include <sys_info.h>
#include <dram_if.h>

/* Notify bootloader on DRAM setup */
void pass_dram_sys_info(struct dram_config *cfg)
{
	set_info(DRAM_BUS_WIDTH, cfg->iface[0].bus[0].bus_width);
	set_info(DRAM_CS0_SIZE, cfg->iface[0].bus[0].size_mb);
	set_info(DRAM_CS0, 1);
	set_info(DRAM_CS1, 0);
	set_info(DRAM_CS2, 0);
	set_info(DRAM_CS3, 0);
}

int ble_plat_dram_setup(void)
{
	int ret;
	struct dram_config *cfg;

	/* Get dram data from platform */
	cfg = (struct dram_config *)plat_get_dram_data();

	/* Kick it in */
	ret = dram_init(cfg);

	/* Pass DRAM information to bootloader */
	pass_dram_sys_info(cfg);

	return ret;
}
