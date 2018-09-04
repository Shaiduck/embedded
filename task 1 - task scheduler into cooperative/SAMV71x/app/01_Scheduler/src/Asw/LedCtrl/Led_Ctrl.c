/****************************************************************************************************/
/**
\file       Led_Ctrl.c
\brief      MCU abstraction level - LED control
\author     Abraham Tezmol
\version    1.0
\project    Tau 
\date       24/June/2016
*/
/****************************************************************************************************/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/
/** Own headers */
#include     "Led_Ctrl.h"
/** Other modules */
#include     "led.h"

/*****************************************************************************************************
* Definition of module wide VARIABLEs 
*****************************************************************************************************/
bool LED_enabled = false;
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


/*****************************************************************************************************/
/**
* \brief    Configures LED 0 and 1 of SAMV71 board
* \author   Abraham Tezmol
* \param    void
* \return   void
*/
void LedCtrl_Configure( void )
{
	LED_Configure( 0 ) ;
	LED_Configure( 1 ) ;
}

/*****************************************************************************************************/
/**
* \brief    Turn a combination of 2 LEDs with a unique blinking pattern.
			Call this function periodically @ 10ms to operate
* \author   Abraham Tezmol
* \param    void
* \return   void
*/
void LedCtrl_BlinkingPattern(void)
{
/* Global state machine status for LED flashing control  */
	static uint8_t LocPatternIndex;

    LocPatternIndex++;
    
    switch ((LocPatternIndex))
    {
        case  1:
            LED_Set(STD_OFF);
            LED_Set(STD_ON);
            break;
        case  11:
            LED_Set(STD_OFF);
            LED_Set(STD_ON);
            break;
        case  3:
            LED_Clear(STD_OFF);
            LED_Clear(STD_ON);
            break;
        case  13:
            LED_Clear(STD_OFF);
            LED_Clear(STD_ON);
            break;
        case 101:
            LocPatternIndex = 0;
            break;
        default:
            break;
    }
}
/*******************************************************************************/