/*
 * comm_protocol.c
 *
 */ 

#include <asf.h>
#include "usart.h"
#include "lin_master.h"

#define USART_SERIAL                 USART1
#define USART_SERIAL_ID              ID_USART1
#define USART_SERIAL_BAUDRATE        115200
#define USART_SERIAL_CHAR_LENGTH     US_MR_CHRL_8_BIT
#define USART_SERIAL_PARITY          US_MR_PAR_NO
#define USART_SERIAL_STOP_BIT        US_MR_NBSTOP_1_BIT

#define SCI0_RX_MAX_SIZE    32u
#define SCI0_TX_MAX_SIZE    32u

/* Definition of Analog signal names in ASCII to be published on SCI */
uint8_t ai8AnalogSignalName0[]= "Esta es una prueba\n\r";

const sam_usart_opt_t usart_console_settings = {
  USART_SERIAL_BAUDRATE,
  USART_SERIAL_CHAR_LENGTH,
  USART_SERIAL_PARITY,
  USART_SERIAL_STOP_BIT,
  US_MR_CHMODE_NORMAL
};


/**************************************************************************************************/
/**
* \brief    vfnLinMaster_Init - Initialization of low-level usart resources needed for lin communication
* \author   Francisco Martinez
* \param    void
* \return   void
* \todo
*/

void vfnLinMaster_Init(void)
{
   
	#if SAM4L
	 sysclk_enable_peripheral_clock(USART_SERIAL);
	#else
	 sysclk_enable_peripheral_clock(USART_SERIAL_ID);
	#endif
	usart_init_rs232(USART_SERIAL, &usart_console_settings,	sysclk_get_peripheral_hz());
	usart_enable_tx(USART_SERIAL);
	usart_enable_rx(USART_SERIAL);
}



/*******************************************************************************/
/**
* \brief    Transmit data on usart
* \author   Francisco Martinez
* \param    void
* \return   void
*/
void vfnLinMaster_SendFrame(void)
{

  static uint8_t idx = 0;
  if (usart_is_tx_empty(USART_SERIAL))
  {
	  usart_putchar(USART_SERIAL, ai8AnalogSignalName0[idx] );
	  idx++;
	  if (idx >= sizeof(ai8AnalogSignalName0))
	  {
		idx=0;
	  }
	  
  } 
}
