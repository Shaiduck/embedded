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
	static uint8_t counter = 0;

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

void UartCtrl_TriggerEvent( void )
{
	static uint8_t enabled = 1;
	static uint8_t counter = 0;


	if (counter < UART_CFG_CHANNELS)
	{
		if (enabled == 1)
		{
			printf("Trying to enable UART");
		}
		else 
		{
			printf("Trying to disable UART");
		}
		Uart_EnableInt(counter, UART_CFG_INT_TXRDY, enabled);
		counter++;
	}
	else if (counter == UART_CFG_CHANNELS)
	{
		if (enabled == 0)
		{
			enabled = 1;
		}
		else
		{
			enabled = 0;
		}
		counter = 0;
	}
}

/*******************************************************************************/
