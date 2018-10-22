/****************************************************************************************************/
/**
\file       Uart_Ctrl.h
\brief      MCU abstraction level - Uart control
\author     Francisco Martinez
\version    1.0
\date       25/Sep/2018
*/
/****************************************************************************************************/

#ifndef __UART_CTRL_H        /*prevent duplicated includes*/
#define __UART_CTRL_H

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Standard Types */
#include "Std_Types.h"

/** Used modules */

/*****************************************************************************************************
* Declaration of module wide TYPEs 
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of module wide MACROs / #DEFINE-CONSTANTs 
*****************************************************************************************************/


/*****************************************************************************************************
* Declaration of module wide FUNCTIONS
*****************************************************************************************************/

/** Uart Control Exported Functions */
extern void UartCtrl_2ms( void );
extern void UartCtrl_50ms( void );
extern void UartCtrl_100ms( void );
extern void UartCtrl_TriggerEvent( void );


/**************************************************************************************************/

#endif /* __UART_CTRL_H */