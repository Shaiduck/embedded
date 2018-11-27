/*******************************************************************************/
/**
\file       app_tasks.h
\brief      Tasks to be assigned to each execution thread of Task scheduler.
\author     Abraham Tezmol
\version    0.1
\date       10/Feb/2008
*/

#ifndef __APP_TASKS
#define __APP_TASKS

/*-- Includes ----------------------------------------------------------------*/
#include     "compiler.h"
/* LED control definitions */ 
#include     "led_ctrl.h"
/* UART communication */
#include     "serial_ctrl.h"
/** Watchdog control function prototypes definitions */
#include     "wdt_ctrl.h"


/*****************************************************************************************************
* Definition of module wide VARIABLES
*****************************************************************************************************/

/*****************************************************************************************************
* Declaration of module wide TYPES
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of module wide MACROS / #DEFINE-CONSTANTS 
*****************************************************************************************************/

/*****************************************************************************************************
* Declaration of module wide FUNCTIONS
*****************************************************************************************************/

/* List of tasks to be executed @ 1ms */
void TASKS_LIST_1MS( void );

/* List of tasks to be executed @ 2ms, first group */
void TASKS_LIST_2MS_A( void );

/* List of tasks to be executed @ 2ms, second group */
void TASKS_LIST_2MS_B( void );
    
/* List of tasks to be executed @ 10ms */
void TASKS_LIST_10MS(  void );

/* List of tasks to be executed @ 50ms */
void TASKS_LIST_50MS( void );

/* List of tasks to be executed @ 100ms */
void TASKS_LIST_100MS( void );

/*============================================================================*/
#endif /*__APP_TASKS */
