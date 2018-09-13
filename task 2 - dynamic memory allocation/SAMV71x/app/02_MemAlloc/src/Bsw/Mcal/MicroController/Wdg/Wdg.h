/*******************************************************************************/
/**
\file       Wdg.h
\brief      Watchdog Driver function prototypes
\author     Abraham Tezmol
\version    0.1
\date       29/06/2016
*/

#ifndef WDG_H        /*prevent duplicated includes*/
#define WDG_H

/*-- Includes ----------------------------------------------------------------*/

#include "Std_Types.h"

/*-- Types Definitions -------------------------------------------------------*/

/*-- Defines -----------------------------------------------------------------*/

/** Watchdog period, in ms */
#define WDG_PERIOD           250

/*-- Function Prototypes -----------------------------------------------------*/

/**  Watchdog Timer Control - Initialization */
void Wdg_Init(uint32_t Wdg_Period);
/**  Watchdog Timer Control - Restart */
void Wdg_Restart( void );
/**  Watchdog Timer Control - Disable */
void Wdg_Disable( void );

/*******************************************************************************/

#endif /* WDG_H */