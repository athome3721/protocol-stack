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
#include <amb_adec.h>
#include <iob.h>
#include <icu.h>
#include <mmio.h>

/*
 * AXI Configuration.
 */

 /* Used for Units of CP-110 (e.g. USB device, USB Host, and etc) */
#define MVEBU_AXI_ATTR_BASE(cp_index)		(MVEBU_CP_REGS_BASE(cp_index) + 0x441300)
#define MVEBU_AXI_ATTR_REG(cp_index, index)	(MVEBU_AXI_ATTR_BASE(cp_index) + 0x4 * index)
#define MVEBU_AXI_ATTR_ARCACHE_OFFSET		4
#define MVEBU_AXI_ATTR_ARCACHE_MASK		(0xF << MVEBU_AXI_ATTR_ARCACHE_OFFSET)
#define MVEBU_AXI_ATTR_ARDOMAIN_OFFSET		12
#define MVEBU_AXI_ATTR_ARDOMAIN_MASK		(0x3 << MVEBU_AXI_ATTR_ARDOMAIN_OFFSET)
#define MVEBU_AXI_ATTR_AWCACHE_OFFSET		20
#define MVEBU_AXI_ATTR_AWCACHE_MASK		(0xF << MVEBU_AXI_ATTR_AWCACHE_OFFSET)
#define MVEBU_AXI_ATTR_AWDOMAIN_OFFSET		28
#define MVEBU_AXI_ATTR_AWDOMAIN_MASK		(0x3 << MVEBU_AXI_ATTR_AWDOMAIN_OFFSET)

/* AXI Protection bits */
#define MVEBU_AXI_PROT_BASE(cp_index)		(MVEBU_CP_REGS_BASE(cp_index) + 0x441200)
#define MVEBU_AXI_PROT_REG(cp_index, index)	((index <= 6) ? (MVEBU_AXI_PROT_BASE(cp_index) + 0x4 * index) : \
						(MVEBU_AXI_PROT_BASE(cp_index) + 0x20 + 0x4 * (index - 7)))
#define MVEBU_AXI_PROT_REGS_NUM			(9)

/* AXI to MBUS bridge registers */
#define MVEBU_AMB_IP_BRIDGE_WIN_REG(cp_index, win)	(MVEBU_AMB_IP_BASE(cp_index) + (win * 0x8))
#define MVEBU_AMB_IP_BRIDGE_WIN_EN_OFFSET		0
#define MVEBU_AMB_IP_BRIDGE_WIN_EN_MASK			(0x1 << MVEBU_AMB_IP_BRIDGE_WIN_EN_OFFSET)
#define MVEBU_AMB_IP_BRIDGE_WIN_SIZE_OFFSET		16
#define MVEBU_AMB_IP_BRIDGE_WIN_SIZE_MASK		(0xffff << MVEBU_AMB_IP_BRIDGE_WIN_SIZE_OFFSET)

enum axi_attr {
	AXI_ADUNIT_ATTR = 0,
	AXI_COMUNIT_ATTR,
	AXI_EIP197_ATTR,
	AXI_USB3D_ATTR,
	AXI_USB3H0_ATTR,
	AXI_USB3H1_ATTR,
	AXI_SATA0_ATTR,
	AXI_SATA1_ATTR,
	AXI_DAP_ATTR,
	AXI_DFX_ATTR,
	AXI_DBG_TRC_ATTR = 12,
	AXI_SDIO_ATTR,
	AXI_MSS_ATTR,
	AXI_MAX_ATTR,
};

/* Most stream IDS are configured centrally in the CP-110 RFU
 * but some are configured inside the unit registers
 */
#define RFU_STREAM_ID_BASE	(0x450000)
#define AUDIO_STREAM_ID_REG	(RFU_STREAM_ID_BASE + 0x0)
#define TDM_STREAM_ID_REG	(RFU_STREAM_ID_BASE + 0x4)
#define USB3D_STREAM_ID_REG	(RFU_STREAM_ID_BASE + 0x8)
#define USB3H_0_STREAM_ID_REG	(RFU_STREAM_ID_BASE + 0xC)
#define USB3H_1_STREAM_ID_REG	(RFU_STREAM_ID_BASE + 0x10)
#define SATA_0_STREAM_ID_REG	(RFU_STREAM_ID_BASE + 0x14)
#define SATA_1_STREAM_ID_REG	(RFU_STREAM_ID_BASE + 0x18)
#define DBG_TRC_STREAM_ID_REG	(RFU_STREAM_ID_BASE + 0x24)
#define SDIO_STREAM_ID_REG	(RFU_STREAM_ID_BASE + 0x28)
#define DAP_STREAM_ID_REG	(RFU_STREAM_ID_BASE + 0x2C)

#define CP_DMA_0_STREAM_ID_REG  (0x6B0010)
#define CP_DMA_1_STREAM_ID_REG  (0x6D0010)

/* We allocate IDs 0-127 for PCI since
 * SR-IOV devices can generate many functions
 * that need a unique Stream-ID.
 */
#define MAX_PCIE_STREAM_ID	(0x80)

uintptr_t stream_id_reg[] = {
	AUDIO_STREAM_ID_REG,
	TDM_STREAM_ID_REG,
	USB3D_STREAM_ID_REG,
	USB3H_0_STREAM_ID_REG,
	USB3H_1_STREAM_ID_REG,
	SATA_0_STREAM_ID_REG,
	SATA_1_STREAM_ID_REG,
	DBG_TRC_STREAM_ID_REG,
	SDIO_STREAM_ID_REG,
	DAP_STREAM_ID_REG,
	CP_DMA_0_STREAM_ID_REG,
	CP_DMA_1_STREAM_ID_REG,
	0
};

/* Set a unique stream id for all DMA capable devices */
void cp110_stream_id_init(uintptr_t cp110_base)
{
	int i = 0;
	uint32_t stream_id = MAX_PCIE_STREAM_ID;

	while (stream_id_reg[i]) {
		/* SATA port 0/1 are in the same SATA unit, and they should use
		** the same STREAM ID number */
		if (stream_id_reg[i] == SATA_0_STREAM_ID_REG)
			mmio_write_32(cp110_base + stream_id_reg[i++], stream_id);
		else
			mmio_write_32(cp110_base + stream_id_reg[i++], stream_id++);
	}
}

void cp110_axi_attr_init(int cp_index)
{
	uint32_t index, data;

	/* Initialize AXI attributes for Armada-7040 SoC */
	/* Releveant for 7040 SoC (and not AP-806 Stand alone) */

	/* Go over the AXI attributes and set Ax-Cache and Ax-Domain */
	for (index = 0; index < AXI_MAX_ATTR; index++) {
		switch (index) {
		/* DFX and MSS unit works with no coherent only -
		   there's no option to configure the Ax-Cache and Ax-Domain */
		case AXI_DFX_ATTR:
		case AXI_MSS_ATTR:
			continue;
		default:
			/* Set Ax-Cache as cacheable, no allocate, modifiable, bufferable
			 The values are different because Read & Write definition
			 is different in Ax-Cache */
			data = mmio_read_32(MVEBU_AXI_ATTR_REG(cp_index, index));
			data &= ~MVEBU_AXI_ATTR_ARCACHE_MASK;
			data |= 0xB << MVEBU_AXI_ATTR_ARCACHE_OFFSET;
			data &= ~MVEBU_AXI_ATTR_AWCACHE_MASK;
			data |= 0x7 << MVEBU_AXI_ATTR_AWCACHE_OFFSET;
			/* Set Ax-Domain as Outer domain */
			data &= ~MVEBU_AXI_ATTR_ARDOMAIN_MASK;
			data |= 0x2 << MVEBU_AXI_ATTR_ARDOMAIN_OFFSET;
			data &= ~MVEBU_AXI_ATTR_AWDOMAIN_MASK;
			data |= 0x2 << MVEBU_AXI_ATTR_AWDOMAIN_OFFSET;
			mmio_write_32(MVEBU_AXI_ATTR_REG(cp_index, index), data);
		}
	}

	/* Set all IO's AXI attribute to non-secure access. */
	for (index = 0; index < MVEBU_AXI_PROT_REGS_NUM; index++)
		mmio_write_32(MVEBU_AXI_PROT_REG(cp_index, index), 0x3);

	return;
}

void amb_bridge_init(int cp_index)
{
	uint32_t reg;

	/* Open AMB bridge Window to Access COMPHY/MDIO registers */
	reg = mmio_read_32(MVEBU_AMB_IP_BRIDGE_WIN_REG(cp_index, 0));
	reg &= ~(MVEBU_AMB_IP_BRIDGE_WIN_SIZE_MASK | MVEBU_AMB_IP_BRIDGE_WIN_EN_MASK);
	reg |= (0x7ff << MVEBU_AMB_IP_BRIDGE_WIN_SIZE_OFFSET | 0x1 << MVEBU_AMB_IP_BRIDGE_WIN_EN_OFFSET);
	mmio_write_32(MVEBU_AMB_IP_BRIDGE_WIN_REG(cp_index, 0), reg);
}

void cp110_init(int cp_index)
{
	/* configure AXI-MBUS windows for CP0*/
	init_amb_adec(cp_index);

	/* configure IOB windows for CP0*/
	init_iob(cp_index);

	/* configure axi for CP0*/
	cp110_axi_attr_init(cp_index);

	/* configure icu for CP0 */
#ifdef PLAT_MARVELL_APN_806_Z
	icu_init(MVEBU_CP_REGS_BASE(0), 64, 0);
#else
	/* ICU - Interrupt Consolidation unit
	 * CP0: interrupt 0..63 mapped to ID 64..127 in AP
	 * CP1: interrupt 64..127 mapped to ID 288..351 in AP */
	icu_init(MVEBU_CP_REGS_BASE(cp_index), 0, cp_index * 64);
#endif /* PLAT_MARVELL_APN_806_Z */

	/* configure stream id for CP0 */
	cp110_stream_id_init(MVEBU_CP_REGS_BASE(cp_index));

	/* Open AMB bridge for comphy for CP0 & CP1*/
	amb_bridge_init(cp_index);
}
