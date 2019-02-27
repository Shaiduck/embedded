/*******************************************************************************/
/**
\file       Uart_Cfg.h
\brief      
   \~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   \version       1.1
   \author        
   \description   
   \date          
*/
#ifndef _UART_CFG_H
#define _UART_CFG_H

#define UART_CFG_PHYCH_UART0 0
#define UART_CFG_PHYCH_UART1 1
#define UART_CFG_PHYCH_UART2 2
#define UART_CFG_PHYCH_UART3 3
#define UART_CFG_PHYCH_UART4 4

#define UART_CFG_INT_DISABLED 0
#define UART_CFG_INT_RXRDY 1
#define UART_CFG_INT_TXRDY 2
#define UART_CFG_INT_OVR_ERROR 32
#define UART_CFG_INT_FRAME_ERROR 64
#define UART_CFG_INT_PAR_ERROR 128
#define UART_CFG_INT_TXEMPTY 512

#define UART_CFG_MODE_NORMAL 0
#define UART_CFG_MODE_AUTO 1
#define UART_CFG_MODE_LOOPBACK 2

#define UART_CFG_PARITY_EVEN 0
#define UART_CFG_PARITY_ODD 1
#define UART_CFG_PARITY_SPACE 2
#define UART_CFG_PARITY_MARK 3
#define UART_CFG_PARITY_NO 4

#define UART_CFG_PER_CLK 0
#define UART_CFG_PMC_CLK 1

extern const uint8_t UartConfiguredChannels[];

typedef struct
{
  uint8_t ChannelId;
  uint32_t IsrEn;
  uint8_t Mode;
  uint8_t Parity;
  uint32_t Baudrate;
  UartNotification TxNotification;
  UartNotification RxNotification;
  UartErrorNotification ErrorNotification;
} UartChannelType;

typedef struct
{
  uint8_t UartNumberOfChannels;
  uint8_t ClkSrc;
  UartChannelType *UartChannel;
} UartConfigType;

extern UartConfigType UartCfg[];

#endif /* _UART_CFG_H */