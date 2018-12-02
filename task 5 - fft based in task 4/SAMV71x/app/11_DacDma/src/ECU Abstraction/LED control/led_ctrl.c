/****************************************************************************************************/
/**
\file       led_ctrl.c
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
#include     "led_ctrl.h"
/** Other modules */
#include     "led.h"
#include     "serial_ctrl.h"
#include     "app_scheduler.h"

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


/*****************************************************************************************************/
/**
* \brief    Configures LED 0 and 1 of SAMV71 board
* \author   Abraham Tezmol
* \param    void
* \return   void
*/
void vfnLedCtrl_Configure( void )
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
void vfnLedCtrl_BlinkingPattern(void)
{
/* Global state machine status for LED flashing control  */
	static uint8_t gu8Index;
	static uint8_t u8ActivationStatus;

    (gu8Index)++;
    
    switch ((gu8Index))
    {
        case  1:
            LED_Set(0);
            LED_Set(1);
			u8ActivationStatus = u8Scheduler_EventActivationHandler(&vfnSerialCtrl_StartTx, TASKS_EVENT_A, 5);
            break;
        case  11:
            LED_Set(0);
            LED_Set(1);
            u8ActivationStatus = u8Scheduler_EventActivationHandler(&vfnSerialCtrl_StartTx, TASKS_EVENT_B, 5);
            break;
        case  3:
            LED_Clear(0);
            LED_Clear(1);
            break;
        case  13:
            LED_Clear(0);
            LED_Clear(1);
            break;
        case 101:
            gu8Index = 0;
            break;
        default:
            break;
    }
}
/*******************************************************************************/