/*******************************************************************************/
/**
\file       Wdg.c
\brief      Watchdog Driver.
\author     Abraham Tezmol
\version    0.1
\date       29/06/2016
*/

/** Standard Types */
#include "Std_Types.h"
/** Watchdog control function prototypes definitions */
#include "Wdg.h"

/* -- Global Variables --------------------------------------------------------*/


/*******************************************************************************/
/**
* \brief    Watchdog Driver - Initialization
* \author   Abraham Tezmol
* \param    uint32_t Watchdog timeout period in milliseconds
* \return   void
* \todo     
*/
void Wdg_Init(uint32_t Wdg_Period)
{   
    uint32_t dwPeriod;
    
    /* Init Global and local Task Scheduler variables */
    dwPeriod = WDT_GetPeriod(Wdg_Period);

	WDT_Enable(WDT, WDT_MR_WDFIEN | WDT_MR_WDDBGHLT| WDT_MR_WDIDLEHLT | (dwPeriod << 16) | dwPeriod);
	NVIC_DisableIRQ(WDT_IRQn);
	NVIC_ClearPendingIRQ(WDT_IRQn);
	NVIC_SetPriority(WDT_IRQn, 0);
	NVIC_EnableIRQ(WDT_IRQn);

	//HOLII
}

/*******************************************************************************/
/**
* \brief    Watchdog Timer Control - Restart
* \author   Abraham Tezmol
* \param    void
* \return   void
* \todo     
*/
void Wdg_Restart( void )
{
	WDT_Restart(WDT);
}

/*******************************************************************************/
/**
* \brief    Watchdog Timer Control - Disable
* \author   Abraham Tezmol
* \param    void
* \return   void
* \todo     
*/
void Wdg_Disable( void )
{
	WDT_Disable(WDT) ;
}
