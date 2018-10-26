/****************************************************************************************************/
/**
\file       Uart_Ctrl.c
\brief      MCU abstraction level - Uart control
\author     Francisco Martinez
\version    1.0
\date       25/Sep/2018
*/
/****************************************************************************************************/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/
/** Own headers */
#include  "Uart_Ctrl.h"
#include "Uart.h"

/*****************************************************************************************************
* Definition of module wide VARIABLEs 
*****************************************************************************************************/
uint8_t counter = 0;
uint8_t enabled = 0;
/****************************************************************************************************
* Declaration of module wide FUNCTIONs 
****************************************************************************************************/

/****************************************************************************************************
* Definition of module wide MACROs / #DEFINE-CONSTANTs 
*****************************************************************************************************/

/****************************************************************************************************
* Declaration of module wide TYPEs 
*****************************************************************************************************/

/****************************************************************************************************
* Definition of module wide (CONST-) CONSTANTs 
*****************************************************************************************************/


/****************************************************************************************************
* Code of module wide FUNCTIONS
*****************************************************************************************************/

void UartCtrl_2ms( void )
{
// need to add task
// probably one that enables the interrupt for sending info via uart
// remember to disable interrupt once inside so that the transmission can be completed
//without interruptions
}

void UartCtrl_50ms( void )
{
// need to add task
// probably one that enables the interrupt for sending info via uart but different channel
}

void UartCtrl_100ms( void )
{
	if (enabled != 0)
	{
		if (counter < UART_CFG_CHANNELS)
		{
			Uart_Send(counter);
			counter++;
		}
		else
		{
			counter = 0;
		}
	}
}

void UartCtrl_TriggerEvent( void )
{
	if (enabled == 0)
	{
		enabled = 1;
		Uart_EnableInt(0, UART_CFG_INT_TXRDY, enabled);
		Uart_EnableInt(1, UART_CFG_INT_TXRDY, enabled);
		printf("UART Enabled");
	}
	else 
	{
		enabled = 0;
		Uart_EnableInt(0, UART_CFG_INT_TXRDY, enabled);
		Uart_EnableInt(1, UART_CFG_INT_TXRDY, enabled);
		printf("UART Disabled");
	}
}

/*******************************************************************************/
