/*******************************************************************************/
/**
\file       Uart.h
\brief      
   \~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   \version       1.0
   \author        
   \description   
   \date          
*/

#ifndef _UART_H /*prevent duplicated includes*/
#define _UART_H

/** Standard Types */
#include "Uart_Types.h"
#include "Uart_Cfg.h"

#define UART_MASK_RXRDY 1
#define UART_MASK_TXRDY 2
#define UART_MASK_OVRE 32
#define UART_MASK_FRAME 64
#define UART_MASK_PARE 128
#define UART_MASK_TXEMPTY 512

extern void Uart_EnableInt(uint8_t Channel, uint32_t IntMode, uint8_t Enable);

extern void Uart_Init(const UartConfigType *Config);

extern Std_ReturnType Uart_SetBaudrate(uint8_t Channel, uint32_t Baudrate);

extern void Uart_SetTxEnable(uint8_t Channel, uint8_t Enable);

extern void Uart_SetRxEnable(uint8_t Channel, uint8_t Enable);

extern Std_ReturnType Uart_SendByte(uint8_t Channel, uint8_t Byte);

extern Std_ReturnType Uart_SendBuffer(uint8_t Channel, uint8_t *Buffer, uint16_t Length);

extern uint8_t Uart_GetByte(uint8_t Channel);

extern uint32_t Uart_GetStatus(uint8_t Channel);

/*============================================================================*/
#endif /* _UART_H */