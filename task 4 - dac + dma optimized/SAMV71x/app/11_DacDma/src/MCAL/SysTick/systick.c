/****************************************************************************************************/
/**
\file       systick.c
\brief      MCAL abstraction level - SysTick configuration and interrupt handling.
\author     Abraham Tezmol
\version    1.0
\date       10/July/2016
*/
/****************************************************************************************************/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/
/** Systick function prototypes and definitions */
#include "systick.h"
/** Core-specific prototypes and definitions */
#include "core_cm7.h"
/** Definitions of System Clock Frequency (Core Clock) */
#include "system_samv71.h"

/*****************************************************************************************************
* Definition of  VARIABLEs - 
*****************************************************************************************************/
/* Global pointer used to invoke callback function upon Timer event*/
tPtr_to_function pfctnSysTick = (tPtr_to_function)NULL;

/*****************************************************************************************************
* Definition of module wide (CONST-) CONSTANTs 
*****************************************************************************************************/

/*****************************************************************************************************
* Code of module wide FUNCTIONS
*****************************************************************************************************/

/****************************************************************************************************/
/**
* \brief    SysTick - Initialization
* \author   Abraham Tezmol
* \param    int32_t base_freq	--> Requested SysTick interrupt frequency
* \param    tPtr_to_function sysTick_handler	--> Callback function to handle SysTick ISR.
* \return   int8_t --> 0 - Successful configuration of SysTick IRQ and SysTick Timer, 1 - Invalid configuration
* \todo
*/
int8_t sysTick_init(int32_t base_freq, tPtr_to_function sysTick_handler)
{
	pfctnSysTick = sysTick_handler;
	return SysTick_Config(SystemCoreClock / base_freq);
}

/****************************************************************************************************/
/**
* \brief    SysTick - interrupt handling
* \author   Abraham Tezmol
* \param    void
* \return   void
* \todo
*/
/* SysTick interrupt handler */
void SysTick_Handler(void)
{
	if (pfctnSysTick)
	{
		__disable_irq();
		(*pfctnSysTick)();
    	__enable_irq();
	}
}
