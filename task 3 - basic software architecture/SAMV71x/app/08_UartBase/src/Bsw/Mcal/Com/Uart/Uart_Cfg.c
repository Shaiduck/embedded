/*******************************************************************************/
/**
\file       Uart_Cfg.c
\brief      
   \~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   \version       1.0
   \author        
   \description   
   \date          
*/

#include "Uart.h"
#include "Uart_Ctrl.h"   /* Callback functions */

/* Example of 3 configured channels */
const uint8_t UartConfiguredChannels[] = {
  UART_CFG_PHY_CHANNEL4,
  UART_CFG_PHY_CHANNEL0,
  UART_CFG_PHY_CHANNEL2
};

