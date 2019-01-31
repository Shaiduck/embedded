/*******************************************************************************/
/**
\file       wdt_ctrl.h
\brief      Watchdog timer control function prototypes
\author     Abraham Tezmol
\version    0.1
\date       29/06/2016
*/

#ifndef WDT_CTRL_H        /*prevent duplicated includes*/
#define WDT_CTRL_H

/*-- Includes ----------------------------------------------------------------*/

#include "compiler.h"
#include "Std_Types.h"

/*-- Types Definitions -------------------------------------------------------*/

/*-- Defines -----------------------------------------------------------------*/

/** Watchdog period, in ms */
#define WDT_PERIOD           250

/*-- Function Prototypes -----------------------------------------------------*/

/**  Watchdog Timer Control - Initialization */
void vfnWdtCtrl_Init(uint32_t Wdt_Period);
/**  Watchdog Timer Control - Restart */
void vfnWdtCtrl_Restart( void );
void vfnWdtCtrl_Disable( void );

/*******************************************************************************/

#endif /* WDT_CTRL_H */