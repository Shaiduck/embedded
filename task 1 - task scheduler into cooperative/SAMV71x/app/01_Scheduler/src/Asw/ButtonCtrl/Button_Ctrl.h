/****************************************************************************************************/
/**
\file       	Button_Ctrl.h
\brief      	MCU abstraction level - Push buttons control
\modified by    Angélica Mercado
\version    	1.0
\project    	Scheduler 
\date       	02/Sept/2018
*/
/****************************************************************************************************/

#ifndef __BUTTONS_CTRL_H        /*prevent duplicated includes*/
#define __BUTTONS_CTRL_H

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

/** Configures LED 0 and 1 of SAMV71 board */
//void LedCtrl_Configure( void );

/** Turn a combination of 2 LEDs with a unique blinking pattern */
//void LedCtrl_BlinkingPattern(void);

void ProcessButtonEvt( uint8_t ucButton );
void Button1_Handler( void );
void Button2_Handler( void );
void ConfigureButtons( void );
void DBGU_Handler( void );

/**************************************************************************************************/

#endif /* __BUTTONS_CTRL_H */