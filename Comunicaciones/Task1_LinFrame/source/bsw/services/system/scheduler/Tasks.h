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

/*-- Variables -------------------------------------------------------*/

/*-- Defines -----------------------------------------------------------------*/

/*-- Macros ------------------------------------------------------------------*/


extern void vfnTsk_1ms(void);
extern void vfnTsk_2msA(void);
extern void vfnTsk_2msB(void);
extern void vfnTsk_10ms(void);
extern void vfnTsk_50ms(void);
extern void vfnTsk_100ms(void);


/*============================================================================*/
#endif /*__APP_TASKS */
