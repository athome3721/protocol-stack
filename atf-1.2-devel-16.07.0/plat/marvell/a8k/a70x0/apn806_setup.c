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
#include <apn806_setup.h>
#include <rfu.h>
#include <ccu.h>
#include <mmio.h>
#include <cache_llc.h>
#include <debug.h>

#define SMMU_sACR				(MVEBU_SMMU_BASE + 0x10)
#define SMMU_sACR_PG_64K			(1 << 16)

#define CCU_GSPMU_CR				(MVEBU_CCU_BASE + 0x3F0)
#define GSPMU_CPU_CONTROL			(0x1 << 0)

#define CCU_HTC_CR				(MVEBU_CCU_BASE + 0x200)
#define CCU_SET_POC_OFFSET			5

#define CCU_LTC_CR				(MVEBU_CCU_BASE + 0x300)
#define CCU_CLEAN_INV_WRITE_OFFSET		8

/* MCI indirect access definitions */
#define MCI_MAX_UNIT_ID				2
#define MCIX4_REG_START_ADDRESS_REG(unit_id)	(MVEBU_REGS_BASE + 0x6F4218 + (unit_id * 0x20))
#define MCI_REMAP_OFF_SHIFT			8

/* MCI indirect access definitions */
#define MCI_WRITE_READ_DATA_REG(mci_index)	MVEBU_MCI_REG_BASE_REMAP(mci_index)
#define MCI_ACCESS_CMD_REG(mci_index)		(MVEBU_MCI_REG_BASE_REMAP(mci_index) + 0x4)

#define MCI_CTRL_STATUS_REG_NUM			5
#define MCI_CTRL_STATUS_REG_PHY_READY		(1 << 12)
#define MCI_CTRL_STATUS_REG_PHY_READY_RESERVERD	(1 << 15)
#define MCI_CTRL_STATUS_REG_PHY_CID_VIO_OFFSET	24
#define MCI_CTRL_STATUS_REG_PHY_CID_VIO_MASK	(0xF << MCI_CTRL_STATUS_REG_PHY_CID_VIO_OFFSET)
/* Expected successful Link result, including reserved bit */
#define MCI_CTRL_PHY_READY			(MCI_CTRL_STATUS_REG_PHY_READY | \
						 MCI_CTRL_STATUS_REG_PHY_READY_RESERVERD | \
						 MCI_CTRL_STATUS_REG_PHY_CID_VIO_MASK)

#define MCI_PHY_PWM3_REG_NUM			7
#define PWM3_LINK_ERROR_OFFSET			8	/* [11:8] : LINK_ERROR */
#define PWM3_LINK_ERROR_MASK			(0xF << PWM3_LINK_ERROR_OFFSET)
#define PWM4_NUM_OF_LANES_OFFSET		20	/* [20:22] : AUTO_NUMBER_OF_LANES */
#define PWM4_NUM_OF_LANES_MASK			(0x7 << PWM4_NUM_OF_LANES_OFFSET)
#define PWM4_LINK_SPEED_MASK			0x7	/* [3:0] AUTO_SPEED */


#define MCI_INDIRECT_CTRL_READ_EN		0x1 /* BIT1 */
#define MCI_INDIRECT_CTRL_LOCAL_PKT		(1 << 5) /* BIT5: Local destination packet */
#define MCI_INDIRECT_CTRL_REG_CHIPID_OFST	16
#define MCI_INDIRECT_REG_CTRL_ADDR(reg_num)	((reg_num << MCI_INDIRECT_CTRL_REG_CHIPID_OFST) | \
						  MCI_INDIRECT_CTRL_LOCAL_PKT | MCI_INDIRECT_CTRL_READ_EN)

#define MCI_INDIRECT_CTRL_PHY_ACCESS_EN		(0xC0  << MCI_INDIRECT_CTRL_REG_CHIPID_OFST) /* PHY access domain */

#define MCI_PHY_CTRL_ADDR			((MCI_PHY_PWM3_REG_NUM << MCI_INDIRECT_CTRL_REG_CHIPID_OFST) \
						  | MCI_INDIRECT_CTRL_LOCAL_PKT)

#define MCI_PHY_CTRL_MCI_MINOR			0x6 /* BITS [3:0] */
#define MCI_PHY_CTRL_MCI_MAJOR_OFFSET		4
#define MCI_PHY_CTRL_MCI_MAJOR			(1 << MCI_PHY_CTRL_MCI_MAJOR_OFFSET)
#define MCI_PHY_CTRL_MCI_PHY_MODE_OFFSET	24
#define MCI_PHY_CTRL_MCI_PHY_MODE_HOST		(1 << MCI_PHY_CTRL_MCI_PHY_MODE_OFFSET)
#define MCI_PHY_CTRL_MCI_PHY_REG_IF_MODE_OFFSET	25
#define MCI_PHY_CTRL_MCI_PHY_REG_IF_MODE	(1 << MCI_PHY_CTRL_MCI_PHY_REG_IF_MODE_OFFSET)
#define MCI_PHY_CTRL_ENABLE_PHY_ACCESS		(MCI_PHY_CTRL_MCI_PHY_MODE_HOST | \
						MCI_PHY_CTRL_MCI_PHY_REG_IF_MODE | \
						MCI_PHY_CTRL_MCI_MAJOR | MCI_PHY_CTRL_MCI_MINOR)

enum mci_register_type {
	MCI_REG_TYPE_PHY = 0,
	MCI_REG_TYPE_CTRL,
};


/* MCIx indirect access register are based by default at 0xf4000000/0xf6000000
 * to avoid conflict of internal registers of units connected via MCIx, which
 * can be based on the same address (i.e CP1 base is also 0xf4000000),
 * the following routines remaps the MCIx indirect bases to another domain */
void mci_remap_indirect_access_base(void)
{
	uint32_t i;

	for (i = 0; i < MCI_MAX_UNIT_ID; ++i)
		mmio_write_32(MCIX4_REG_START_ADDRESS_REG(i), MVEBU_MCI_REG_BASE_REMAP(i) >> MCI_REMAP_OFF_SHIFT);
}

/* Routine to enable access to PHY registers over MCI0 indirect read/write*/
void mci_enable_phy_regs_access(int mci_index)
{
	/* Enable PHY local access (reg 7 bit 25) */
	mmio_write_32(MCI_WRITE_READ_DATA_REG(mci_index), MCI_PHY_CTRL_ENABLE_PHY_ACCESS);
	mmio_write_32(MCI_ACCESS_CMD_REG(mci_index), MCI_PHY_CTRL_ADDR);
}

/* read mci0 PHY/CTRL registers via indirect access */
uint32_t mci_indirect_read(int reg_num, enum mci_register_type reg_type, int mci_index)
{
	uint32_t indirect_reg_address = 0;

	/* Access to PHY registers requires special configuration */
	if (reg_type == MCI_REG_TYPE_PHY)
		indirect_reg_address |= MCI_INDIRECT_CTRL_PHY_ACCESS_EN;

	indirect_reg_address |= MCI_INDIRECT_REG_CTRL_ADDR(reg_num);

	mmio_write_32(MCI_ACCESS_CMD_REG(mci_index), indirect_reg_address);
	return mmio_read_32(MCI_WRITE_READ_DATA_REG(mci_index));
}

int mci_test_link(int mci_index)
{
	uint32_t ctrl_status, phy_status, link_error, lane_count;
	uint32_t link_result[5] = {1, 2, 4, 8, 16}; /* link speed and lane count */

	NOTICE("MCI0 link status.. ");
	mci_enable_phy_regs_access(mci_index);	/* enable PHY domain read/write access */

	/* MCI Controller link status*/
	ctrl_status = mci_indirect_read(MCI_CTRL_STATUS_REG_NUM, MCI_REG_TYPE_CTRL, mci_index);

	/* MCI PHY link status: PWM Control #3*/
	phy_status = mci_indirect_read(MCI_PHY_PWM3_REG_NUM, MCI_REG_TYPE_PHY, mci_index);

	if (ctrl_status != MCI_CTRL_PHY_READY) {
		printf(" link failed (MCI status: 0x%x, PWM_CTRL #3 = 0x%x)\n", ctrl_status, phy_status);
		return 0;
	}

	printf("Link UP:");
	link_error = (phy_status & PWM3_LINK_ERROR_MASK) >> PWM3_LINK_ERROR_OFFSET;
	if (link_error)
		ERROR("\n\tlink Error #%d: (MCI status: 0%x):", link_error, ctrl_status);

	lane_count = (phy_status & PWM4_NUM_OF_LANES_MASK) >> PWM4_NUM_OF_LANES_OFFSET;
	printf(" %d lanes ", link_result[lane_count]);
	printf("@ %d Gbps", link_result[(phy_status & PWM4_LINK_SPEED_MASK)]);
	printf(" (PWM_CTRL #3 = 0x%x)\n", phy_status);

	return 1;
}

void setup_smmu(void)
{
	uint32_t reg;

	/* Set the SMMU page size to 64 KB */
	reg = mmio_read_32(SMMU_sACR);
	reg |= SMMU_sACR_PG_64K;
	mmio_write_32(SMMU_sACR, reg);
}

void init_aurora2(void)
{
	uint32_t reg;

	/* Enable GSPMU control by CPU */
	reg = mmio_read_32(CCU_GSPMU_CR);
	reg |= GSPMU_CPU_CONTROL;
	mmio_write_32(CCU_GSPMU_CR, reg);

#if !LLC_DISABLE
#ifdef PLAT_MARVELL_APN_806_Z
	/* Enable LLC in non-exclusive mode */
	llc_enable(0);
#else
	/* Enable LLC in exclusive mode */
	llc_enable(1);
#endif /* AP806-Z1 */
#endif

	/* Set point of coherency to DDR.
	   This is required by units which have
	   SW cache coherency */
	reg = mmio_read_32(CCU_HTC_CR);
	reg |= (0x1 << CCU_SET_POC_OFFSET);
	mmio_write_32(CCU_HTC_CR, reg);

	/* cache line clean & invalidate instead of
	** cache line invalidate only - to avoid system hang
	** due to memory coherency issue */
	reg = mmio_read_32(CCU_LTC_CR);
	reg |= (0x1 << CCU_CLEAN_INV_WRITE_OFFSET);
	mmio_write_32(CCU_LTC_CR, reg);
}

void apn806_init(void)
{
	/* Setup Aurora2. */
	init_aurora2();

	/* configure MCI mapping */
	mci_remap_indirect_access_base();

	/* configure RFU windows */
	init_rfu();

	/* configure CCU windows */
	init_ccu();

	/* configure the SMMU */
	setup_smmu();
}
