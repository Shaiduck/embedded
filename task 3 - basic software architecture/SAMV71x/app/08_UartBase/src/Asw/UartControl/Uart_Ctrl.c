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

/*****************************************************************************************************
* Definition of module wide VARIABLEs 
*****************************************************************************************************/
uint8_t 		u8SerialCtrl_TxData[] = {"The Atmel_ | SMART_ SAM V71 Xplained Ultra evaluation kit is ideal for evaluating and prototyping with the Atmel SAM V71, SAM V70, SAM S70 and SAM E70 ARM_ Cortex_-M7 based microcontrollers\n\r\n\rExample by Abraham Tezmol\n\r\n\r"};

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
// need to add task
// probably one that enables the interrupt for sending info via uart but different channel
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
