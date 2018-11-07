/*******************************************************************************/
/**
\file       wdt_ctrl.c
\brief      Watchdog timer control.
\author     Abraham Tezmol
\version    0.1
\date       29/06/2016
*/

/** Variable types and common definitions */
#include "system_samv71.h"

/** Watchdog control function prototypes definitions */
#include "wdt_ctrl.h"

/* -- Global Variables --------------------------------------------------------*/


/*******************************************************************************/
/**
* \brief    Watchdog Timer Control - Initialization
* \author   Abraham Tezmol
* \param    uint32_t Watchdog timeout period in milliseconds
* \return   void
* \todo     
*/
void vfnWdtCtrl_Init(uint32_t Wdt_Period)
{   
    uint32_t dwPeriod;
    
    /* Init Global and local Task Scheduler variables */
    dwPeriod = WDT_GetPeriod(Wdt_Period);

	WDT_Enable(WDT, WDT_MR_WDFIEN | WDT_MR_WDDBGHLT| WDT_MR_WDIDLEHLT | (dwPeriod << 16) | dwPeriod);
	NVIC_DisableIRQ(WDT_IRQn);
	NVIC_ClearPendingIRQ(WDT_IRQn);
	NVIC_SetPriority(WDT_IRQn, 0);
	NVIC_EnableIRQ(WDT_IRQn);
}

/*******************************************************************************/
/**
* \brief    Watchdog Timer Control - Restart
* \author   Abraham Tezmol
* \param    void
* \return   void
* \todo     
*/
void vfnWdtCtrl_Restart( void )
{
	WDT_Restart(WDT);
}
void vfnWdtCtrl_Disable( void )
{
	WDT_Disable(WDT) ;
}
