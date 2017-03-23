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
#include <dram_if.h>

struct dram_config dram_cfg = {
	.iface_mask	= 0x1,
	.printf		= printf,

	/* Interface configuration */
	.iface[0] = {
		.mac_base = (void *)MVEBU_DRAM_MAC_BASE,
		.phy_base = (void *)MVEBU_DRAM_PHY_BASE,
		.ecc_enabled	= 0,
		.cs_count	= 1,
		.freq_mhz	= 800,

		/* Bus configuration */
		.bus[0] = {
			.bus_width = 64,
			.size_mb   = 0x1000,
		},
	},
};

/* This function may modify the default DRAM parameters
 * based on information recieved from SPD or bootloader
 * configuration located on non volatile storage */
int update_dram_info(struct dram_config *cfg)
{
	NOTICE("Gathering DRAM information\n");
	return 0;
}

void *plat_get_dram_data(void)
{
	/* Update DRAM for dynamic platforms */
	update_dram_info(&dram_cfg);

	return &dram_cfg;
}
