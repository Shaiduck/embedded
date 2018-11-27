/****************************************************************************************************/
/**
\file       led_ctrl.h
\brief      MCU abstraction level - LED control
\author     Abraham Tezmol
\version    1.0
\project    Tau 
\date       24/June/2016
*/
/****************************************************************************************************/

#ifndef __SERIAL_CTRL_H        /*prevent duplicated includes*/
#define __SERIAL_CTRL_H

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Core modules */
#include "compiler.h"
#include "Std_Types.h"

/** Used modules */
/*#include "component_uart.h"  */


/*****************************************************************************************************
* Declaration of module wide TYPEs 
*****************************************************************************************************/


/*****************************************************************************************************
* Definition of module wide MACROs / #DEFINE-CONSTANTs 
*****************************************************************************************************/
#define BASE_UART       	UART4
#define BASE_ID         	ID_UART4
#define BASE_IRQ        	UART4_IRQn
/** Pins description corresponding to Rxd,Txd, (UART pins) */
#define UART_PINS        	{PINS_UART4}

#define SERIAL_TX_MAX_SIZE  64
#define SERIAL_RX_MAX_SIZE	64

/*****************************************************************************************************
* Declaration of module wide FUNCTIONS
*****************************************************************************************************/

/** Configures Serial channel 4 on SAMV71 board */
void vfnSerialCtrl_Configure( void );

void vfnSerialCrtl_ClearRx( void );

void vfnSerialCtrl_ClearTx( void );

void vfnSerialCtrl_Init( void );

void vfnSerialCtrl_StartTx( void );

void vfnSerialCtrl_Transfer(void);



/**************************************************************************************************/

#endif /* __SERIAL_CTRL_H */