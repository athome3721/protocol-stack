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

/* This driver provides I2C support for armada3700 */

#include <plat_def.h>
#include <debug.h>
#include <mmio.h>
#include <delay_timer.h>
#include <i2c.h>

#ifdef DEBUG_I2C
#define PRINTD(x) printf x
#else
#define PRINTD(x)
#endif

/* Shall the current transfer have a start/stop condition? */
#define I2C_COND_NORMAL		0
#define I2C_COND_START		1
#define I2C_COND_STOP		2

/* Shall the current transfer be ack/nacked or being waited for it? */
#define I2C_ACKNAK_WAITACK	1
#define I2C_ACKNAK_SENDACK	2
#define I2C_ACKNAK_SENDNAK	4

/* Specify who shall transfer the data (master or slave) */
#define I2C_READ		0
#define I2C_WRITE		1

#define I2C_ICR_INIT	(ICR_BEIE | ICR_IRFIE | ICR_ITEIE | ICR_GCD | ICR_SCLE)
#define I2C_ISR_INIT		0x7FF

/* ----- Control register bits ---------------------------------------- */
#define ICR_START	0x1		/* start bit */
#define ICR_STOP	0x2		/* stop bit */
#define ICR_ACKNAK	0x4		/* send ACK(0) or NAK(1) */
#define ICR_TB		0x8		/* transfer byte bit */
#define ICR_MA		0x10		/* master abort */
#define ICR_SCLE	0x20		/* master clock enable, mona SCLEA */
#define ICR_IUE		0x40		/* unit enable */
#define ICR_GCD		0x80		/* general call disable */
#define ICR_ITEIE	0x100		/* enable tx interrupts */
#define ICR_IRFIE	0x200		/* enable rx interrupts, mona: DRFIE */
#define ICR_BEIE	0x400		/* enable bus error ints */
#define ICR_SSDIE	0x800		/* slave STOP detected int enable */
#define ICR_ALDIE	0x1000		/* enable arbitration interrupt */
#define ICR_SADIE	0x2000		/* slave address detected int enable */
#define ICR_UR		0x4000		/* unit reset */
#define ICR_FM		0x8000		/* Fast Mode */

/* ----- Status register bits ----------------------------------------- */
#define ISR_RWM		0x1		/* read/write mode */
#define ISR_ACKNAK	0x2		/* ack/nak status */
#define ISR_UB		0x4		/* unit busy */
#define ISR_IBB		0x8		/* bus busy */
#define ISR_SSD		0x10		/* slave stop detected */
#define ISR_ALD		0x20		/* arbitration loss detected */
#define ISR_ITE		0x40		/* tx buffer empty */
#define ISR_IRF		0x80		/* rx buffer full */
#define ISR_GCAD	0x100		/* general call address detected */
#define ISR_SAD		0x200		/* slave address detected */
#define ISR_BED		0x400		/* bus error no ACK/NAK */

/* All transfers are described by this data structure */
struct i2c_msg {
	uint8_t condition;
	uint8_t acknack;
	uint8_t direction;
	uint8_t data;
};

struct mv_i2c {
	uint32_t ibmr;
	uint32_t idbr;
	uint32_t icr;
	uint32_t isr;
	uint32_t isar;
};

static struct mv_i2c *base;

/*
 * i2c_reset: - reset the host controller
 *
 */
static void i2c_reset(void)
{
	mmio_write_32((uintptr_t)&base->icr, mmio_read_32((uintptr_t)&base->icr) & ~ICR_IUE); /* disable unit */
	mmio_write_32((uintptr_t)&base->icr, mmio_read_32((uintptr_t)&base->icr) | ICR_UR);	  /* reset the unit */
	udelay(100);
	mmio_write_32((uintptr_t)&base->icr, mmio_read_32((uintptr_t)&base->icr) & ~ICR_IUE); /* disable unit */

	/* atf does not support i2c clock setting, i2c clock is enabled by default for a3700 */
	/* i2c is in the standard mode with up to 100 Kbps operation, so here we do nothing for i2c clock enabling */

	mmio_write_32((uintptr_t)&base->icr, I2C_ICR_INIT); /* set control reg values */
	mmio_write_32((uintptr_t)&base->isr, I2C_ISR_INIT); /* set clear interrupt bits */
	mmio_write_32((uintptr_t)&base->icr, mmio_read_32((uintptr_t)&base->icr) | ICR_IUE); /* enable unit */
	udelay(100);
}

/*
 * i2c_isr_set_cleared: - wait until certain bits of the I2C status register
 *	                  are set and cleared
 *
 * @return: 1 in case of success, 0 means timeout (no match within 10 ms).
 */
static int i2c_isr_set_cleared(unsigned long set_mask,
			       unsigned long cleared_mask)
{
	int timeout = 1000, isr;

	do {
		isr = mmio_read_32((uintptr_t)&base->isr);
		udelay(10);
		if (timeout-- < 0)
			return 0;
	} while (((isr & set_mask) != set_mask) ||
		((isr & cleared_mask) != 0));

	return 1;
}

/*
 * i2c_transfer: - Transfer one byte over the i2c bus
 *
 * This function can tranfer a byte over the i2c bus in both directions.
 * It is used by the public API functions.
 *
 * @return:  0: transfer successful
 *          -1: message is empty
 *          -2: transmit timeout
 *          -3: ACK missing
 *          -4: receive timeout
 *          -5: illegal parameters
 *          -6: bus is busy and couldn't be aquired
 */
int i2c_transfer(struct i2c_msg *msg)
{
	int ret;

	if (!msg)
		goto transfer_error_msg_empty;

	switch (msg->direction) {
	case I2C_WRITE:
		/* check if bus is not busy */
		if (!i2c_isr_set_cleared(0, ISR_IBB))
			goto transfer_error_bus_busy;

		/* start transmission */
		mmio_write_32((uintptr_t)&base->icr, mmio_read_32((uintptr_t)&base->icr) & ~ICR_START);
		mmio_write_32((uintptr_t)&base->icr, mmio_read_32((uintptr_t)&base->icr) & ~ICR_STOP);
		mmio_write_32((uintptr_t)&base->idbr, msg->data);
		if (msg->condition == I2C_COND_START)
			mmio_write_32((uintptr_t)&base->icr, mmio_read_32((uintptr_t)&base->icr) | ICR_START);
		if (msg->condition == I2C_COND_STOP)
			mmio_write_32((uintptr_t)&base->icr, mmio_read_32((uintptr_t)&base->icr) | ICR_STOP);
		if (msg->acknack == I2C_ACKNAK_SENDNAK)
			mmio_write_32((uintptr_t)&base->icr, mmio_read_32((uintptr_t)&base->icr) | ICR_ACKNAK);
		if (msg->acknack == I2C_ACKNAK_SENDACK)
			mmio_write_32((uintptr_t)&base->icr, mmio_read_32((uintptr_t)&base->icr) & ~ICR_ACKNAK);
		mmio_write_32((uintptr_t)&base->icr, mmio_read_32((uintptr_t)&base->icr) & ~ICR_ALDIE);
		mmio_write_32((uintptr_t)&base->icr, mmio_read_32((uintptr_t)&base->icr) | ICR_TB);

		/* transmit register empty? */
		if (!i2c_isr_set_cleared(ISR_ITE, 0))
			goto transfer_error_transmit_timeout;

		/* clear 'transmit empty' state */
		mmio_write_32((uintptr_t)&base->isr, mmio_read_32((uintptr_t)&base->isr) | ISR_ITE);

		/* wait for ACK from slave */
		if (msg->acknack == I2C_ACKNAK_WAITACK)
			if (!i2c_isr_set_cleared(0, ISR_ACKNAK))
				goto transfer_error_ack_missing;
		break;

	case I2C_READ:

		/* check if bus is not busy */
		if (!i2c_isr_set_cleared(0, ISR_IBB))
			goto transfer_error_bus_busy;

		/* start receive */
		mmio_write_32((uintptr_t)&base->icr, mmio_read_32((uintptr_t)&base->icr) & ~ICR_START);
		mmio_write_32((uintptr_t)&base->icr, mmio_read_32((uintptr_t)&base->icr) & ~ICR_STOP);
		if (msg->condition == I2C_COND_START)
			mmio_write_32((uintptr_t)&base->icr, mmio_read_32((uintptr_t)&base->icr) | ICR_START);
		if (msg->condition == I2C_COND_STOP)
			mmio_write_32((uintptr_t)&base->icr, mmio_read_32((uintptr_t)&base->icr) | ICR_STOP);
		if (msg->acknack == I2C_ACKNAK_SENDNAK)
			mmio_write_32((uintptr_t)&base->icr, mmio_read_32((uintptr_t)&base->icr) | ICR_ACKNAK);
		if (msg->acknack == I2C_ACKNAK_SENDACK)
			mmio_write_32((uintptr_t)&base->icr, mmio_read_32((uintptr_t)&base->icr) & ~ICR_ACKNAK);
		mmio_write_32((uintptr_t)&base->icr, mmio_read_32((uintptr_t)&base->icr) & ~ICR_ALDIE);
		mmio_write_32((uintptr_t)&base->icr, mmio_read_32((uintptr_t)&base->icr) | ICR_TB);

		/* receive register full? */
		if (!i2c_isr_set_cleared(ISR_IRF, 0))
			goto transfer_error_receive_timeout;

		msg->data = mmio_read_32((uintptr_t)&base->idbr);

		/* clear 'receive empty' state */
		mmio_write_32((uintptr_t)&base->isr, mmio_read_32((uintptr_t)&base->isr) | ISR_IRF);
		break;
	default:
		goto transfer_error_illegal_param;
	}

	return 0;

transfer_error_msg_empty:
		PRINTD(("i2c_transfer: error: 'msg' is empty\n"));
		ret = -1; goto i2c_transfer_finish;

transfer_error_transmit_timeout:
		PRINTD(("i2c_transfer: error: transmit timeout\n"));
		ret = -2; goto i2c_transfer_finish;

transfer_error_ack_missing:
		PRINTD(("i2c_transfer: error: ACK missing\n"));
		ret = -3; goto i2c_transfer_finish;

transfer_error_receive_timeout:
		PRINTD(("i2c_transfer: error: receive timeout\n"));
		ret = -4; goto i2c_transfer_finish;

transfer_error_illegal_param:
		PRINTD(("i2c_transfer: error: illegal parameters\n"));
		ret = -5; goto i2c_transfer_finish;

transfer_error_bus_busy:
		PRINTD(("i2c_transfer: error: bus is busy\n"));
		ret = -6; goto i2c_transfer_finish;

i2c_transfer_finish:
		PRINTD(("i2c_transfer: ISR: 0x%04x\n", mmio_read_32((uintptr_t)&base->isr)));
		i2c_reset();
		return ret;
}

/* ------------------------------------------------------------------------ */
/* API Functions                                                            */
/* ------------------------------------------------------------------------ */
void i2c_init(void)
{
	/* For I2C speed and slave address, now we do not set them since
	 * we just provide the working speed and slave address in plat_def.h
	 * for i2c_init
	 */
	base = (struct mv_i2c *)MVEBU_I2C_REGS_BASE;
}

/*
 * i2c_read: - Read multiple bytes from an i2c device
 *
 * The higher level routines take into account that this function is only
 * called with len < page length of the device (see configuration file)
 *
 * @chip:	address of the chip which is to be read
 * @addr:	i2c data address within the chip
 * @alen:	length of the i2c data address (1..2 bytes)
 * @buffer:	where to write the data
 * @len:	how much byte do we want to read
 * @return:	0 in case of success
 */
int i2c_read(uint8_t chip, uint32_t addr, int alen, uint8_t *buffer, int len)
{
	struct i2c_msg msg;
	uint8_t addr_bytes[3]; /* lowest...highest byte of data address */

	PRINTD(("i2c_read(chip=0x%02x, addr=0x%02x, alen=0x%02x, len=0x%02x)\n", chip, addr, alen, len));

	i2c_reset();

	/* dummy chip address write */
	PRINTD(("i2c_read: dummy chip address write\n"));
	msg.condition = I2C_COND_START;
	msg.acknack   = I2C_ACKNAK_WAITACK;
	msg.direction = I2C_WRITE;
	msg.data = (chip << 1);
	msg.data &= 0xFE;
	if (i2c_transfer(&msg))
		return -1;

	/*
	 * send memory address bytes;
	 * alen defines how much bytes we have to send.
	 */
	/*addr &= ((1 << CONFIG_SYS_EEPROM_PAGE_WRITE_BITS)-1); */
	addr_bytes[0] = (uint8_t)((addr >>  0) & 0x000000FF);
	addr_bytes[1] = (uint8_t)((addr >>  8) & 0x000000FF);
	addr_bytes[2] = (uint8_t)((addr >> 16) & 0x000000FF);

	while (--alen >= 0) {
		PRINTD(("i2c_read: send memory word address byte %1d\n", alen));
		msg.condition = I2C_COND_NORMAL;
		msg.acknack   = I2C_ACKNAK_WAITACK;
		msg.direction = I2C_WRITE;
		msg.data      = addr_bytes[alen];
		if (i2c_transfer(&msg))
			return -1;
	}

	/* start read sequence */
	PRINTD(("i2c_read: start read sequence\n"));
	msg.condition = I2C_COND_START;
	msg.acknack   = I2C_ACKNAK_WAITACK;
	msg.direction = I2C_WRITE;
	msg.data      = (chip << 1);
	msg.data     |= 0x01;
	if (i2c_transfer(&msg))
		return -1;

	/* read bytes; send NACK at last byte */
	while (len--) {
		if (len == 0) {
			msg.condition = I2C_COND_STOP;
			msg.acknack   = I2C_ACKNAK_SENDNAK;
		} else {
			msg.condition = I2C_COND_NORMAL;
			msg.acknack   = I2C_ACKNAK_SENDACK;
		}

		msg.direction = I2C_READ;
		msg.data      = 0x00;
		if (i2c_transfer(&msg))
			return -1;

		*buffer = msg.data;
		PRINTD(("i2c_read: reading byte (0x%08lx)=0x%02x\n",
			(unsigned long)buffer, *buffer));
		buffer++;
	}

	i2c_reset();

	return 0;
}

/*
 * i2c_write: -  Write multiple bytes to an i2c device
 *
 * The higher level routines take into account that this function is only
 * called with len < page length of the device (see configuration file)
 *
 * @chip:	address of the chip which is to be written
 * @addr:	i2c data address within the chip
 * @alen:	length of the i2c data address (1..2 bytes)
 * @buffer:	where to find the data to be written
 * @len:	how much byte do we want to read
 * @return:	0 in case of success
 */
int i2c_write(uint8_t chip, uint32_t addr, int alen, uint8_t *buffer, int len)
{
	struct i2c_msg msg;
	uint8_t addr_bytes[3]; /* lowest...highest byte of data address */

	PRINTD(("i2c_write(chip=0x%02x, addr=0x%02x, alen=0x%02x, len=0x%02x)\n", chip, addr, alen, len));

	i2c_reset();

	/* chip address write */
	PRINTD(("i2c_write: chip address write\n"));
	msg.condition = I2C_COND_START;
	msg.acknack   = I2C_ACKNAK_WAITACK;
	msg.direction = I2C_WRITE;
	msg.data = (chip << 1);
	msg.data &= 0xFE;
	if (i2c_transfer(&msg))
		return -1;

	/*
	 * send memory address bytes;
	 * alen defines how much bytes we have to send.
	 */
	addr_bytes[0] = (uint8_t)((addr >>  0) & 0x000000FF);
	addr_bytes[1] = (uint8_t)((addr >>  8) & 0x000000FF);
	addr_bytes[2] = (uint8_t)((addr >> 16) & 0x000000FF);

	while (--alen >= 0) {
		PRINTD(("i2c_write: send memory word address\n"));
		msg.condition = I2C_COND_NORMAL;
		msg.acknack   = I2C_ACKNAK_WAITACK;
		msg.direction = I2C_WRITE;
		msg.data      = addr_bytes[alen];
		if (i2c_transfer(&msg))
			return -1;
	}

	/* write bytes; send NACK at last byte */
	while (len--) {
		PRINTD(("i2c_write: writing byte (0x%08lx)=0x%02x\n",
			(unsigned long)buffer, *buffer));

		if (len == 0)
			msg.condition = I2C_COND_STOP;
		else
			msg.condition = I2C_COND_NORMAL;

		msg.acknack   = I2C_ACKNAK_WAITACK;
		msg.direction = I2C_WRITE;
		msg.data      = *(buffer++);

		if (i2c_transfer(&msg))
			return -1;
	}

	i2c_reset();

	return 0;
}
