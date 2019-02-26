/**
 * \file
 *
 * \brief Universal Synchronous Asynchronous Receiver Transmitter (USART) driver
 * for SAM.
 *
 * Copyright (c) 2011-2015 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#include "usart.h"

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

/**
 * \defgroup sam_drivers_usart_group Universal Synchronous Asynchronous
 * Receiver Transmitter (USART)
 *
 * The Universal Synchronous Asynchronous Receiver Transceiver (USART)
 * provides one full duplex universal synchronous asynchronous serial link.
 * Data frame format is widely programmable (data length, parity, number of
 * stop bits) to support a maximum of standards. The receiver implements
 * parity error, framing error and overrun error detection. The receiver
 * time-out enables handling variable-length frames and the transmitter
 * timeguard facilitates communications with slow remote devices. Multidrop
 * communications are also supported through address bit handling in reception
 * and transmission. The driver supports the following modes:
 * RS232, RS485, SPI, IrDA, ISO7816, MODEM, Hardware handshaking and LIN.
 *
 * @{
 */

/* The write protect key value. */
#ifndef US_WPMR_WPKEY_PASSWD
#define US_WPMR_WPKEY_PASSWD    US_WPMR_WPKEY(0x555341U)
#endif

#ifndef US_WPMR_WPKEY_PASSWD
#  define US_WPMR_WPKEY_PASSWD US_WPMR_WPKEY(US_WPKEY_VALUE)
#endif

/* The CD value scope programmed in MR register. */
#define MIN_CD_VALUE                  0x01
#define MIN_CD_VALUE_SPI              0x04
#define MAX_CD_VALUE                  US_BRGR_CD_Msk

/* The receiver sampling divide of baudrate clock. */
#define HIGH_FRQ_SAMPLE_DIV           16
#define LOW_FRQ_SAMPLE_DIV            8

/* Max transmitter timeguard. */
#define MAX_TRAN_GUARD_TIME           US_TTGR_TG_Msk

/* The non-existent parity error number. */
#define USART_PARITY_ERROR            5

/* ISO7816 protocol type. */
#define ISO7816_T_0                   0
#define ISO7816_T_1                   1

/**
 * \brief Calculate a clock divider(CD) and a fractional part (FP) for the
 * USART asynchronous modes to generate a baudrate as close as possible to
 * the baudrate set point.
 *
 * \note Baud rate calculation: Baudrate = ul_mck/(Over * (CD + FP/8))
 * (Over being 16 or 8). The maximal oversampling is selected if it allows to
 * generate a baudrate close to the set point.
 *
 * \param p_usart Pointer to a USART instance.
 * \param baudrate Baud rate set point.
 * \param ul_mck USART module input clock frequency.
 *
 * \retval 0 Baud rate is successfully initialized.
 * \retval 1 Baud rate set point is out of range for the given input clock
 * frequency.
 */
uint32_t usart_set_async_baudrate(Usart *p_usart,
		uint32_t baudrate, uint32_t ul_mck)
{
	uint32_t over;
	uint32_t cd_fp;
	uint32_t cd;
	uint32_t fp;

	/* Calculate the receiver sampling divide of baudrate clock. */
	if (ul_mck >= HIGH_FRQ_SAMPLE_DIV * baudrate) {
		over = HIGH_FRQ_SAMPLE_DIV;
	} else {
		over = LOW_FRQ_SAMPLE_DIV;
	}

	/* Calculate clock divider according to the fraction calculated formula. */
	cd_fp = (8 * ul_mck + (over * baudrate) / 2) / (over * baudrate);
	cd = cd_fp >> 3;
	fp = cd_fp & 0x07;
	if (cd < MIN_CD_VALUE || cd > MAX_CD_VALUE) {
		return 1;
	}

	/* Configure the OVER bit in MR register. */
	if (over == 8) {
		p_usart->US_MR |= US_MR_OVER;
	}

	/* Configure the baudrate generate register. */
	p_usart->US_BRGR = (cd << US_BRGR_CD_Pos) | (fp << US_BRGR_FP_Pos);

	return 0;
}


/**
 * \brief Reset the USART and disable TX and RX.
 *
 * \param p_usart Pointer to a USART instance.
 */
void usart_reset(Usart *p_usart)
{
	/* Disable the Write Protect. */
	usart_disable_writeprotect(p_usart);

	/* Reset registers that could cause unpredictable behavior after reset. */
	p_usart->US_MR = 0;
	p_usart->US_RTOR = 0;
	p_usart->US_TTGR = 0;

	/* Disable TX and RX. */
	usart_reset_tx(p_usart);
	usart_reset_rx(p_usart);
	/* Reset status bits. */
	usart_reset_status(p_usart);
	/* Turn off RTS */
	usart_drive_RTS_pin_high(p_usart);
}

/**
 * \brief Configure USART to work in RS232 mode.
 *
 * \note By default, the transmitter and receiver aren't enabled.
 *
 * \param p_usart Pointer to a USART instance.
 * \param p_usart_opt Pointer to sam_usart_opt_t instance.
 * \param ul_mck USART module input clock frequency.
 *
 * \retval 0 on success.
 * \retval 1 on failure.
 */
uint32_t usart_init_rs232(Usart *p_usart,
		const sam_usart_opt_t *p_usart_opt, uint32_t ul_mck)
{
	static uint32_t ul_reg_val;

	/* Reset the USART and shut down TX and RX. */
	usart_reset(p_usart);

	ul_reg_val = 0;
	/* Check whether the input values are legal. */
	if (!p_usart_opt || usart_set_async_baudrate(p_usart,
			p_usart_opt->baudrate, ul_mck)) {
		return 1;
	}

	/* Configure the USART option. */
	ul_reg_val |= p_usart_opt->char_length | p_usart_opt->parity_type |
			p_usart_opt->channel_mode | p_usart_opt->stop_bits;

	/* Configure the USART mode as normal mode. */
	ul_reg_val |= US_MR_USART_MODE_NORMAL;

	p_usart->US_MR |= ul_reg_val;

	return 0;
}



/**
 * \brief Enable USART transmitter.
 *
 * \param p_usart Pointer to a USART instance.
 */
void usart_enable_tx(Usart *p_usart)
{
	p_usart->US_CR = US_CR_TXEN;
}

/**
 * \brief Disable USART transmitter.
 *
 * \param p_usart Pointer to a USART instance.
 */
void usart_disable_tx(Usart *p_usart)
{
	p_usart->US_CR = US_CR_TXDIS;
}

/**
 * \brief Immediately stop and disable USART transmitter.
 *
 * \param p_usart Pointer to a USART instance.
 */
void usart_reset_tx(Usart *p_usart)
{
	/* Reset transmitter */
	p_usart->US_CR = US_CR_RSTTX | US_CR_TXDIS;
}

/**
 * \brief Configure the transmit timeguard register.
 *
 * \param p_usart Pointer to a USART instance.
 * \param timeguard The value of transmit timeguard.
 */
void usart_set_tx_timeguard(Usart *p_usart, uint32_t timeguard)
{
	p_usart->US_TTGR = timeguard;
}

/**
 * \brief Enable USART receiver.
 *
 * \param p_usart Pointer to a USART instance.
 */
void usart_enable_rx(Usart *p_usart)
{
	p_usart->US_CR = US_CR_RXEN;
}

/**
 * \brief Disable USART receiver.
 *
 * \param p_usart Pointer to a USART instance.
 */
void usart_disable_rx(Usart *p_usart)
{
	p_usart->US_CR = US_CR_RXDIS;
}

/**
 * \brief Immediately stop and disable USART receiver.
 *
 * \param p_usart Pointer to a USART instance.
 */
void usart_reset_rx(Usart *p_usart)
{
	/* Reset Receiver */
	p_usart->US_CR = US_CR_RSTRX | US_CR_RXDIS;
}

/**
 * \brief Configure the receive timeout register.
 *
 * \param p_usart Pointer to a USART instance.
 * \param timeout The value of receive timeout.
 */
void usart_set_rx_timeout(Usart *p_usart, uint32_t timeout)
{
	p_usart->US_RTOR = timeout;
}

/**
 * \brief Enable USART interrupts.
 *
 * \param p_usart Pointer to a USART peripheral.
 * \param ul_sources Interrupt sources bit map.
 */
void usart_enable_interrupt(Usart *p_usart, uint32_t ul_sources)
{
	p_usart->US_IER = ul_sources;
}

/**
 * \brief Disable USART interrupts.
 *
 * \param p_usart Pointer to a USART peripheral.
 * \param ul_sources Interrupt sources bit map.
 */
void usart_disable_interrupt(Usart *p_usart, uint32_t ul_sources)
{
	p_usart->US_IDR = ul_sources;
}

/**
 * \brief Read USART interrupt mask.
 *
 * \param p_usart Pointer to a USART peripheral.
 *
 * \return The interrupt mask value.
 */
uint32_t usart_get_interrupt_mask(Usart *p_usart)
{
	return p_usart->US_IMR;
}

/**
 * \brief Get current status.
 *
 * \param p_usart Pointer to a USART instance.
 *
 * \return The current USART status.
 */
uint32_t usart_get_status(Usart *p_usart)
{
	return p_usart->US_CSR;
}

/**
 * \brief Reset status bits (PARE, OVER, MANERR, UNRE and PXBRK in US_CSR).
 *
 * \param p_usart Pointer to a USART instance.
 */
void usart_reset_status(Usart *p_usart)
{
	p_usart->US_CR = US_CR_RSTSTA;
}

/**
 * \brief Start transmission of a break.
 *
 * \param p_usart Pointer to a USART instance.
 */
void usart_start_tx_break(Usart *p_usart)
{
	p_usart->US_CR = US_CR_STTBRK;
}

/**
 * \brief Stop transmission of a break.
 *
 * \param p_usart Pointer to a USART instance.
 */
void usart_stop_tx_break(Usart *p_usart)
{
	p_usart->US_CR = US_CR_STPBRK;
}

/**
 * \brief Start waiting for a character before clocking the timeout count.
 * Reset the status bit TIMEOUT in US_CSR.
 *
 * \param p_usart Pointer to a USART instance.
 */
void usart_start_rx_timeout(Usart *p_usart)
{
	p_usart->US_CR = US_CR_STTTO;
}

/**
 * \brief Restart the receive timeout.
 *
 * \param p_usart Pointer to a USART instance.
 */
void usart_restart_rx_timeout(Usart *p_usart)
{
	p_usart->US_CR = US_CR_RETTO;
}

/*
 * \brief Drive the pin RTS to 0.
 *
 * \param p_usart Pointer to a USART instance.
 */
void usart_drive_RTS_pin_low(Usart *p_usart)
{
	p_usart->US_CR = US_CR_RTSEN;
}
/**
 * \brief Drive the pin RTS to 1.
 *
 * \param p_usart Pointer to a USART instance.
 */
void usart_drive_RTS_pin_high(Usart *p_usart)
{
	p_usart->US_CR = US_CR_RTSDIS;
}

/**
 * \brief Check if Transmit is Ready.
 * Check if data have been loaded in USART_THR and are waiting to be loaded
 * into the Transmit Shift Register (TSR).
 *
 * \param p_usart Pointer to a USART instance.
 *
 * \retval 1 No data is in the Transmit Holding Register.
 * \retval 0 There is data in the Transmit Holding Register.
 */
uint32_t usart_is_tx_ready(Usart *p_usart)
{
	return (p_usart->US_CSR & US_CSR_TXRDY) > 0;
}

/**
 * \brief Check if Transmit Holding Register is empty.
 * Check if the last data written in USART_THR have been loaded in TSR and the
 * last data loaded in TSR have been transmitted.
 *
 * \param p_usart Pointer to a USART instance.
 *
 * \retval 1 Transmitter is empty.
 * \retval 0 Transmitter is not empty.
 */
uint32_t usart_is_tx_empty(Usart *p_usart)
{
	return (p_usart->US_CSR & US_CSR_TXEMPTY) > 0;
}

/**
 * \brief Check if the received data are ready.
 * Check if Data have been received and loaded into USART_RHR.
 *
 * \param p_usart Pointer to a USART instance.
 *
 * \retval 1 Some data has been received.
 * \retval 0 No data has been received.
 */
uint32_t usart_is_rx_ready(Usart *p_usart)
{
	return (p_usart->US_CSR & US_CSR_RXRDY) > 0;
}

/**
 * \brief Write to USART Transmit Holding Register.
 *
 * \note Before writing user should check if tx is ready (or empty).
 *
 * \param p_usart Pointer to a USART instance.
 * \param c Data to be sent.
 *
 * \retval 0 on success.
 * \retval 1 on failure.
 */
uint32_t usart_write(Usart *p_usart, uint32_t c)
{
	if (!(p_usart->US_CSR & US_CSR_TXRDY)) {
		return 1;
	}

	p_usart->US_THR = US_THR_TXCHR(c);
	return 0;
}

/**
 * \brief Write to USART Transmit Holding Register.
 *
 * \note Before writing user should check if tx is ready (or empty).
 *
 * \param p_usart Pointer to a USART instance.
 * \param c Data to be sent.
 *
 * \retval 0 on success.
 * \retval 1 on failure.
 */
uint32_t usart_putchar(Usart *p_usart, uint32_t c)
{
	while (!(p_usart->US_CSR & US_CSR_TXRDY)) {
	}

	p_usart->US_THR = US_THR_TXCHR(c);

	return 0;
}

/**
 * \brief Write one-line string through USART.
 *
 * \param p_usart Pointer to a USART instance.
 * \param string Pointer to one-line string to be sent.
 */
void usart_write_line(Usart *p_usart, const char *string)
{
	while (*string != '\0') {
		usart_putchar(p_usart, *string++);
	}
}

/**
 * \brief Read from USART Receive Holding Register.
 *
 * \note Before reading user should check if rx is ready.
 *
 * \param p_usart Pointer to a USART instance.
 * \param c Pointer where the one-byte received data will be stored.
 *
 * \retval 0 on success.
 * \retval 1 if no data is available or errors.
 */
uint32_t usart_read(Usart *p_usart, uint32_t *c)
{
	if (!(p_usart->US_CSR & US_CSR_RXRDY)) {
		return 1;
	}

	/* Read character */
	*c = p_usart->US_RHR & US_RHR_RXCHR_Msk;

	return 0;
}

/**
 * \brief Read from USART Receive Holding Register.
 * Before reading user should check if rx is ready.
 *
 * \param p_usart Pointer to a USART instance.
 * \param c Pointer where the one-byte received data will be stored.
 *
 * \retval 0 Data has been received.
 * \retval 1 on failure.
 */
uint32_t usart_getchar(Usart *p_usart, uint32_t *c)
{
	/* Wait until it's not empty or timeout has reached. */
	while (!(p_usart->US_CSR & US_CSR_RXRDY)) {
	}

	/* Read character */
	*c = p_usart->US_RHR & US_RHR_RXCHR_Msk;

	return 0;
}

/**
 * \brief Enable write protect of USART registers.
 *
 * \param p_usart Pointer to a USART instance.
 */
void usart_enable_writeprotect(Usart *p_usart)
{
	p_usart->US_WPMR = US_WPMR_WPEN | US_WPMR_WPKEY_PASSWD;
}

/**
 * \brief Disable write protect of USART registers.
 *
 * \param p_usart Pointer to a USART instance.
 */
void usart_disable_writeprotect(Usart *p_usart)
{
	p_usart->US_WPMR = US_WPMR_WPKEY_PASSWD;
}

/**
 * \brief Get write protect status.
 *
 * \param p_usart Pointer to a USART instance.
 *
 * \return 0 if no write protect violation occurred, or 16-bit write protect
 * violation source.
 */
uint32_t usart_get_writeprotect_status(Usart *p_usart)
{
	uint32_t reg_value;

	reg_value = p_usart->US_WPSR;
	if (reg_value & US_WPSR_WPVS) {
		return (reg_value & US_WPSR_WPVSRC_Msk) >> US_WPSR_WPVSRC_Pos;
	} else {
		return 0;
	}
}
//@}

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond
