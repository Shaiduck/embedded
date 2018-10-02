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
  extern void Uart_Init( const uint8_t * ChannelConfigure );
  /* Uart Send Fucntion */
  extern void Uart_Send(uint8_t Channel);

  /* Example Code - Need to be removed */
  extern void UART0_Handler(void);
  extern void UART1_Handler(void);
  extern void UART2_Handler(void);
  extern void UART3_Handler(void);
  extern void UART4_Handler(void);

/*============================================================================*/
#endif /* _UART_H */