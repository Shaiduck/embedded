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

#ifndef USART_H_INCLUDED
#define USART_H_INCLUDED

#include "compiler.h"

/**
 * \defgroup group_sam_drivers_usart Universal Synchronous Asynchronous Receiver
 * Transmitter (USART).
 *
 * See \ref sam_usart_quickstart.
 *
 * This is a low-level driver implementation for the SAM Universal
 * Synchronous/Asynchronous Receiver/Transmitter.
 *
 * @{
 */

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

/* Input parameters when initializing RS232 and similar modes. */
typedef struct {
	/* Set baud rate of the USART (unused in slave modes). */
	uint32_t baudrate;

	/*
	 * Number of bits, which should be one of the following: US_MR_CHRL_5_BIT,
	 * US_MR_CHRL_6_BIT, US_MR_CHRL_7_BIT, US_MR_CHRL_8_BIT or
	 * US_MR_MODE9.
	 */
	uint32_t char_length;

	/*
	 * Parity type, which should be one of the following: US_MR_PAR_EVEN,
	 * US_MR_PAR_ODD, US_MR_PAR_SPACE, US_MR_PAR_MARK, US_MR_PAR_NO
	 * or US_MR_PAR_MULTIDROP.
	 */
	uint32_t parity_type;

	/*
	 * Number of stop bits between two characters: US_MR_NBSTOP_1_BIT,
	 * US_MR_NBSTOP_1_5_BIT, US_MR_NBSTOP_2_BIT.
	 * \note US_MR_NBSTOP_1_5_BIT is supported in asynchronous modes only.
	 */
	uint32_t stop_bits;

	/*
	 * Run the channel in test mode, which should be one of following:
	 * US_MR_CHMODE_NORMAL, US_MR_CHMODE_AUTOMATIC,
	 * US_MR_CHMODE_LOCAL_LOOPBACK, US_MR_CHMODE_REMOTE_LOOPBACK.
	 */
	uint32_t channel_mode;

	/* Filter of IrDA mode, useless in other modes. */
	uint32_t irda_filter;
} sam_usart_opt_t;


void usart_reset(Usart *p_usart);
uint32_t usart_set_async_baudrate(Usart *p_usart,
		uint32_t baudrate, uint32_t ul_mck);
uint32_t usart_init_rs232(Usart *p_usart,
		const sam_usart_opt_t *p_usart_opt, uint32_t ul_mck);
void usart_enable_tx(Usart *p_usart);
void usart_disable_tx(Usart *p_usart);
void usart_reset_tx(Usart *p_usart);
void usart_set_tx_timeguard(Usart *p_usart, uint32_t timeguard);
void usart_enable_rx(Usart *p_usart);
void usart_disable_rx(Usart *p_usart);
void usart_reset_rx(Usart *p_usart);
void usart_set_rx_timeout(Usart *p_usart, uint32_t timeout);
void usart_enable_interrupt(Usart *p_usart, uint32_t ul_sources);
void usart_disable_interrupt(Usart *p_usart, uint32_t ul_sources);
uint32_t usart_get_interrupt_mask(Usart *p_usart);
uint32_t usart_get_status(Usart *p_usart);
void usart_reset_status(Usart *p_usart);
void usart_start_tx_break(Usart *p_usart);
void usart_stop_tx_break(Usart *p_usart);
void usart_start_rx_timeout(Usart *p_usart);
void usart_restart_rx_timeout(Usart *p_usart);
void usart_drive_RTS_pin_low(Usart *p_usart);
void usart_drive_RTS_pin_high(Usart *p_usart);
uint32_t usart_is_tx_ready(Usart *p_usart);
uint32_t usart_is_tx_empty(Usart *p_usart);
uint32_t usart_is_rx_ready(Usart *p_usart);
uint32_t usart_write(Usart *p_usart, uint32_t c);
uint32_t usart_putchar(Usart *p_usart, uint32_t c);
void usart_write_line(Usart *p_usart, const char *string);
uint32_t usart_read(Usart *p_usart, uint32_t *c);
uint32_t usart_getchar(Usart *p_usart, uint32_t *c);
#if (SAM3XA || SAM3U)
uint32_t *usart_get_tx_access(Usart *p_usart);
uint32_t *usart_get_rx_access(Usart *p_usart);
#endif
void usart_enable_writeprotect(Usart *p_usart);
void usart_disable_writeprotect(Usart *p_usart);
uint32_t usart_get_writeprotect_status(Usart *p_usart);

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond

//! @}

#endif /* USART_H_INCLUDED */
