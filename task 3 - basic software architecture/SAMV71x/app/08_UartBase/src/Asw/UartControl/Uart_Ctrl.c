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
	if (counter < UART_CFG_CHANNELS)
	{
		Uart_EnableInt(counter, UART_CFG_INT_TXRDY, 1);
		counter++;
	}
	else
	{
		counter = 0;
	}
}

void UartCtrl_TriggerEvent( void )
{
/* These function handlers shall be invoked upon interrupt request */
//uart handlers may point to this function
//this function then may start sending information
//the string that will be send is at the beginning of this file
//tasks should be added to scheduler
/* In your solution this trigger can start a buffer transmission */
}

/*******************************************************************************/
