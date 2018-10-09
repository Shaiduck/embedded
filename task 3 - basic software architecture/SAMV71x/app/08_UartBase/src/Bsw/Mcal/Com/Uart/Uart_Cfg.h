/*******************************************************************************/
/**
\file       Uart_Cfg.h
\brief      
   \~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   \version       1.0
   \author        
   \description   
   \date          
*/
#ifndef _UART_CFG_H
#define _UART_CFG_H

  #include "Std_Types.h"

  #define UART_CFG_CHANNELS (3)

  #define UART_CFG_CHANNEL0  (0)
  #define UART_CFG_CHANNEL1  (1)
  #define UART_CFG_CHANNEL2  (2)
  #define UART_CFG_CHANNEL3  (3)
  #define UART_CFG_CHANNEL4  (4)

  #define UART_CFG_INT_DISABLED = 0;
  #define UART_CFG_INT_RXRDY = 1;
  #define UART_CFG_INT_TXRDY = 2;
  #define UART_CFG_INT_OVR_ERROR = 32;
  #define UART_CFG_INT_FRAME_ERROR = 64;
  #define UART_CFG_INT_PAR_ERROR = 128;
  #define UART_CFG_INT_TXEMPTY = 512;

  extern const uint8_t UartConfiguredChannels[];

  


#endif /* _UART_CFG_H */