/*******************************************************************************/
/**
\file       Uart_Cfg.c
\brief      
   \~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   \version       1.1
   \author        
   \description   
   \date          
*/

#include "Uart.h"

void RxNotification(void)
{
  printf("\n\r-RxRdy-\n\r");
}

void TxNotification(void)
{
  printf("\n\r-TxRdy-\n\r");
}

void ErrorNotification2(UartErrorType Error)
{
  printf("\n\r-ErrorCH2No:%d-\n\r", Error);
}

void ErrorNotification4(UartErrorType Error)
{
  printf("\n\r-ErrorCH4No:%d-\n\r", Error);
}

UartChannelType UartChannelConfig[] = {
    {
        UART_CFG_PHYCH_UART4,
        UART_CFG_INT_OVR_ERROR,
        UART_CFG_MODE_LOOPBACK,
        UART_CFG_PARITY_NO,
        115200,
        NULL,
        NULL,
        NULL
        //ErrorNotification4
    },
    {UART_CFG_PHYCH_UART2,
     UART_CFG_INT_TXRDY | UART_CFG_INT_RXRDY | UART_CFG_INT_OVR_ERROR,
     UART_CFG_MODE_LOOPBACK,
     UART_CFG_PARITY_NO,
     115200,
     TxNotification,
     RxNotification,
     ErrorNotification2}

};

UartConfigType UartCfg[] = {
    {sizeof(UartChannelConfig) / sizeof(UartChannelType), //number of channels
     UART_CFG_PER_CLK,
     &UartChannelConfig[0]}

};
