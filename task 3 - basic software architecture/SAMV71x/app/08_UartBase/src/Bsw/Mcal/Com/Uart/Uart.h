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

#ifndef _UART_H        /*prevent duplicated includes*/
	#define _UART_H

	/** Standard Types */
	#include "Std_Types.h"
  #include "Uart_Types.h"
	#include "Uart_Cfg.h"

  /* Uart Initialization Fucntion */
  //extern void Uart_Init( const uint8_t * ChannelConfigure );
  /* Uart Send Fucntion */
  //extern void Uart_Send(uint8_t Channel);

  extern Std_ReturnType Uart_SetBaudRate(uint8_t Channel, uint32_t Baudrate);

  extern void Uart_SetTxEnable(uint8_t Channel, uint32_t Enable);

  extern void Uart_SetRxEnable(uint8_t Channel, uint32_t Enable);

  extern Std_ReturnType Uart_SendByte(uint8_t Channel, uint8_t Byte);

  extern Std_ReturnType Uart_SendBuffer(uint8_t Channel, uint8_t* Buffer, uint16_t Length);

  extern uint8_t Uart_GetByte(uint8_t Channel);

  extern uint32_t Uart_GetStatus(uint8_t Channel);

  extern void Uart_EnableInt(uint8_t Channel, uint32_t IntMode, uint8_t Enable);

  
  #define UART_MASK_RXRDY 1
  #define UART_MASK_TXRDY 2
  #define UART_MASK_OVRE 32
  #define UART_MASK_FRAME 64
  #define UART_MASK_PARE 128
  #define UART_MASK_TXEMPTY 512


  /* Example Code - Need to be removed */
  extern void UART0_Handler(void);
  extern void UART1_Handler(void);
  extern void UART2_Handler(void);
  extern void UART3_Handler(void);
  extern void UART4_Handler(void);

/*============================================================================*/
#endif /* _UART_H */