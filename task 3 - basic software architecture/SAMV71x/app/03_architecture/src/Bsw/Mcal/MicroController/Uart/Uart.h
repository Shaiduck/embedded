#ifndef UART_H        /*prevent duplicated includes*/
#define UART_H

#include <Std_Types.h>

//placeholder
typedef int UartConfigType;

//todo: modify parameters
void Uart_init(UartConfigType);
Std_ReturnType Uart_SetBaudRate(uint8_t x, uint32_t y);
void Uart_SetTxEnable(uint8_t x, uint32_t y);
void Uart_SetRxEnable(uint8_t x, uint32_t y);

Std_ReturnType Uart_SendByte(uint8_t x, uint8_t y);
Std_ReturnType Uart_SendBuffer(uint8_t x, uint8_t* y);
void Uart_GetByte(uint8_t x, uint8_t y);

void Uart_EnableInt(uint8_t x, uint32_t y, uint8_t z);
void Uart_GetStatus(uint8_t x, uint32_t* y);

void UART0_Handler();
void UART1_Handler();
void UART2_Handler();
void UART3_Handler();
void UART4_Handler();

#endif