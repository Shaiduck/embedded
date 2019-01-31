/****************************************************************************************************/
/**
\file       Button_Ctrl.c
\brief      MCU abstraction level - Button control
\author     Francisco Martinez
\version    1.0
\date       2/Sep/2018
*/
/****************************************************************************************************/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/
/** Own headers */
#include  "Button_Ctrl.h"
#include	"SchM.h"


/*****************************************************************************************************
* Definition of module wide VARIABLEs 
*****************************************************************************************************/

/****************************************************************************************************
* Declaration of module wide FUNCTIONs 
****************************************************************************************************/

/****************************************************************************************************
* Definition of module wide MACROs / #DEFINE-CONSTANTs 
*****************************************************************************************************/
/** Pin definition: Pin type definition is located at pio.h file */
/* 
  typedef struct _Pin
  {
  	uint32_t mask;     PIO_PA9                                      -> Bitmask indicating which pin(s) to configure.
  	Pio    *pio;       PIOA                                         -> Pointer to the PIO controller which has the pin(s).
  	uint8_t id;        ID_PIOA                                      -> Peripheral ID of the PIO controller which has the pin(s).
  	uint8_t type;      PIO_INPUT                                    -> Pin Type
  	uint8_t attribute; PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_RISE_EDGE -> Pin attribute
  } Pin ;
*/
#include "Std_Types.h"
#define PIN_SW0 \
		{PIO_PA9, PIOA, ID_PIOA, PIO_INPUT, PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_RISE_EDGE}
/****************************************************************************************************
* Declaration of module wide TYPEs 
*****************************************************************************************************/

/****************************************************************************************************
* Definition of module wide (CONST-) CONSTANTs 
*****************************************************************************************************/
/** SW0 Pin Definition, used to configure the Pin and Pin Interrupt, see ConfigureSW0Button function  */
static const Pin PinSW0 = PIN_SW0;

/****************************************************************************************************
* Code of module wide FUNCTIONS
*****************************************************************************************************/


/**
 *  \brief Handler for Button 1 rising edge interrupt.
 *
 *  Handle process led status change.
 */
static void SW0_Handler( const Pin* pPin )
{
	if ( pPin == &PinSW0 ) {
		SchM_ActivateTask(TASK_SW0);
	}
}

/**
 *  \brief Configure the SW0 Push-button
 *
 *  Configure the PIO as inputs and generate corresponding interrupt when
 *  pressed or released.
 */

void ButtonCtrl_ConfigureSW0Button( void )
{
	/* Configure PinSW0 as input. */
	PIO_Configure( &PinSW0, 1 ) ;

	/* Adjust PinSW0 denounce filter parameters, uses 10 Hz filter. */
	PIO_SetDebounceFilter( &PinSW0, 10 ) ;

	/* Initialize PinSW0 interrupt handler */
	PIO_ConfigureIt( &PinSW0, SW0_Handler ) ; /* Interrupt on rising edge, SW0_Handler as callback function */

	/* Enable PinSW0 controller IRQs. */
	NVIC_EnableIRQ( (IRQn_Type)PinSW0.id ) ;

	/* Enable PinSW0 line interrupts. */
	PIO_EnableIt( &PinSW0 ) ;
}

/*******************************************************************************/
