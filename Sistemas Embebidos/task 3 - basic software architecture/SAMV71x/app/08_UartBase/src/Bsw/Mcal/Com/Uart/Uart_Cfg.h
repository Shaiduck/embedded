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

  #define UART_CFG_CHANNELS  5
  /* channel configuration */
  #define UART_CFG_PHY_CHANNEL0  0
  #define UART_CFG_PHY_CHANNEL1  1
  #define UART_CFG_PHY_CHANNEL2  2
  #define UART_CFG_PHY_CHANNEL3  3
  #define UART_CFG_PHY_CHANNEL4  4
  /* interrupt configuration */
  #define UART_CFG_INT_DISABLED 0
  #define UART_CFG_INT_RXRDY 1
  #define UART_CFG_INT_TXRDY 2
  #define UART_CFG_INT_OVR_ERROR 32
  #define UART_CFG_INT_FRAME_ERROR 64
  #define UART_CFG_INT_PAR_ERROR 128
  #define UART_CFG_INT_TXEMPTY 512
  /* mode configuration */
  #define UART_CFG_MODE_NORMAL 0
  #define UART_CFG_MODE_AUTO 1
  #define UART_CFG_MODE_LOOPBACK 2
  /* parity configuration */
  #define UART_CFG_PARITY_EVEN 0
  #define UART_CFG_PARITY_ODD 1
  #define UART_CFG_PARITY_SPACE 2
  #define UART_CFG_PARITY_MARK 3
  #define UART_CFG_PARITY_NO 4
  /* clock configuration */
  #define UART_CFG_PER_CLK 0
  #define UART_CFG_PMC_CLK 1

  extern const uint8_t UartConfiguredChannels[];

  typedef struct UartConfigType
  {
    uint8_t UartNumberOfChannels;
    uint32_t ClkSrc;
    UartChannelType* UartChannel;
  } UartConfigType;

#endif /* _UART_CFG_H */