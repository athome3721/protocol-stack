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
#include <plat_marvell.h>
#include <plat_private.h>
#include <sys_info.h>
#include <mmio.h>
#include <i2c.h>

/*******************************************************************************
 * EEPROM for boot mode
 ******************************************************************************/
#define BOOT_MODE_I2C_CHIP			0x4c
#define BOOT_MODE_I2C_ADDR			0
#define BOOT_MODE_I2C_ADDR_LEN			1

/* BOOT MODE */
enum boot_mode_ids {
	BOOT_MODE_AUTO_SCAN = 0,
	BOOT_MODE_SPI,
	BOOT_MODE_EMMC,
	BOOT_MODE_EMMC_ALTERNATE,
	BOOT_MODE_SATA,
	BOOT_MODE_NAND,
	BOOT_MODE_UART,
	BOOT_MODE_MAX,
};

/* This function passes hard coded DRAM in ATF to sys info */
static void pass_dram_sys_info(void)
{
	/* Pass DRAM size value, so that u-boot could get it later
	 * Convert dram_size value from bits unit to MB unit by right-shift 20 bits
	 * Uboot code expects MB unit not bit unit for Armada3700
	 * Only single ddr chip-set is supported for Armada3700
	 */
	set_info(DRAM_CS0_SIZE, MARVELL_DRAM1_SIZE >> 20);
}

/* This routine does MPP initialization */
static void marvell_bl31_mpp_init(void)
{
	uint32_t reg_val;

	/* Enable I2C1 MPP */
	reg_val = mmio_read_32(MVEBU_GPIO_NB_SEL_REG);
	reg_val = reg_val & (~(1 << MVEBU_GPIO_TW1_GPIO_EN_OFF));
	mmio_write_32(MVEBU_GPIO_NB_SEL_REG, reg_val);
}

static void marvell_boot_mode_set(uint8_t boot_mode)
{
	i2c_write(BOOT_MODE_I2C_CHIP, BOOT_MODE_I2C_ADDR, BOOT_MODE_I2C_ADDR_LEN, &boot_mode, sizeof(boot_mode));
}

static void marvell_boot_mode_get(uint8_t *boot_mode)
{
	i2c_read(BOOT_MODE_I2C_CHIP, BOOT_MODE_I2C_ADDR, BOOT_MODE_I2C_ADDR_LEN, boot_mode, sizeof(*boot_mode));
}

/* Armada3700-Z chip doesn't support escape string to enter the uart mode.
 * So that the u-boot cannot be recovered via uart on a boot failure. For Marvell
 * board, it supports to switch the boot_src by modifying the sample at reset
 * value in PCA9560.
 *
 * 1. in atf bl31, boot mode from SatR device will be read, kept
 *    the original value, I2C mem will be written to boot from UART, so if
 *    atf/u-boot crashed, board stays in boot from UART mode.
 * 2. in the last stage of u-boot, boot mode will be written back to
 *    oringal value.
 */
static void marvell_boot_mode_switch(void)
{
	uint8_t boot_mode;

	/* get boot mode */
	marvell_boot_mode_get(&boot_mode);

	/* Pass BOOT_MODE from atf to u-boot */
	set_info(BOOT_MODE, boot_mode);

	/* switch to uart mode in modes other than uart */
	if (BOOT_MODE_UART != boot_mode)
		marvell_boot_mode_set(BOOT_MODE_UART);
}

void misc_init_cci400(void)
{
	/*
	   CCI-400 enable snoop and dvm on S3 port.
	   For details see the <CoreLink CCI-400 Cache Coherent Interconnect> document.
	   bit[0] - Enable issuing of snoop requests from this slave interface.
	   bit[1] - Enable issuing of DVM message requests from this slave interface
	   bit[29:2] - Reserved
	   bit[30] - Slave interface supports snoops
	   bit[31] - Slave interface supports DVM messages
	 */
	mmio_write_32(MVEBU_CCI_S3_SNOOP_CTRL_REG, 0xC0000003);
}

/* This function overruns the same function in marvell_bl31_setup.c */
void bl31_plat_arch_setup(void)
{
	marvell_bl31_plat_arch_setup();

	/* MPP init */
	marvell_bl31_mpp_init();

	/* initiliaze the timer for delay functionality */
	plat_delay_timer_init();

	/* i2c initialization */
	i2c_init();

	/* save current boot mode and switch to UART boot mode */
	marvell_boot_mode_switch();

	/* Pass DRAM size value so that u-boot could get it later */
	pass_dram_sys_info();

	/* initialiaze the cci400 */
	misc_init_cci400();
}
