/****************************************************************************************************/
/**
\file       	Button_Ctrl.c
\brief      	MCU abstraction level - Push buttons control
\modified by    Angélica Mercado
\version    	1.0
\project    	Scheduler 
\date       	02/Sept/2018
*/
/****************************************************************************************************/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/
/** Own headers */
#include     "Button_Ctrl.h"
/** Other modules */
//#include     "button.h"

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include <stdbool.h>
#include <stdio.h>

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/
 int a =0;
 /**
 *  \brief Process Buttons Events
 */
void ProcessButtonEvt( uint8_t ucButton )
{
	if ( ucButton == 0 ) {
		//bLed0Active = !bLed0Active ;
		//if ( !bLed0Active ) {
			//LED_Clear( 0 );
			a = 0;
		//}
	}
	else
	{
		//bLed1Active = !bLed1Active ;

		/* Enable LED#2 and TC if they were disabled */
		//if ( bLed1Active ) {
			//LED_Set( 1 );
			a = 1;
		}
		/* Disable LED#2 and TC if they were enabled */
		//else{
			//LED_Clear( 1 );
		//	a = 2;
	//	}
//	}
}

/**
 *  \brief Handler for Button 1 rising edge interrupt.
 *
 *  Handle process led1 status change.
 */
void Button1_Handler( void )
{
	// if ( pPin == &pinPB1 ) {
	// 	ProcessButtonEvt( 0 ) ;
	// }
}

/**
 *  \brief Handler for Button 2 falling edge interrupt.
 *
 *  Handle process led2 status change.
 */
void Button2_Handler( void )
{
	// if ( pPin == &pinPB2 ) {
	// 	ProcessButtonEvt( 1 ) ;
	// }
}

/**
 *  \brief Configure the Push-buttons
 *
 *  Configure the PIO as inputs and generate corresponding interrupt when
 *  pressed or released.
 */
void ConfigureButtons( void )
{
	// /* Configure PIO as inputs. */
	// PIO_Configure( &pinPB1, 1 ) ;
	// PIO_Configure( &pinPB2, 1 ) ;

	// /* Adjust PIO denounce filter parameters, uses 10 Hz filter. */
	// PIO_SetDebounceFilter( &pinPB1, 10 ) ;
	// PIO_SetDebounceFilter( &pinPB2, 10 ) ;

	// /* Initialize PIO interrupt handlers, see PIO definition in board.h. */
	// PIO_ConfigureIt( &pinPB1, _Button1_Handler ) ; /* Interrupt on rising edge  */
	// PIO_ConfigureIt( &pinPB2, _Button2_Handler ) ; /* Interrupt on rising edge */

	// /* Enable PIO controller IRQs. */
	// NVIC_EnableIRQ( (IRQn_Type)pinPB1.id ) ;
	// NVIC_EnableIRQ( (IRQn_Type)pinPB2.id ) ;

	// /* Enable PIO line interrupts. */
	// PIO_EnableIt( &pinPB1 ) ;
	// PIO_EnableIt( &pinPB2 ) ;
}

/**
 *  \brief Handler for DBGU input.
 *
 *  Handle process LED1 or LED2 status change.
 */
void DBGU_Handler( void )
{
	// uint8_t key;
	// if ( !DBG_IsRxReady( ) ) return ;
	// key = DBG_GetChar( ) ;
	// switch ( key ) {
	// case '1': case '2':
	// 	ProcessButtonEvt( key - '1' ) ;
	// 	break;
	// }
}
