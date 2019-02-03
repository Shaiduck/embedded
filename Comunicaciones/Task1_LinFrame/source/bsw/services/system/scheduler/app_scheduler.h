/*******************************************************************************/
/**
\file       app_scheduler.h
\brief      Task scheduler function prototypes
\author     Abraham Tezmol
\version    0.1
\date       09/09/2008
*/

#ifndef APP_SCHEDULER_H        /*prevent duplicated includes*/
#define APP_SCHEDULER_H

/*-- Includes ----------------------------------------------------------------*/
#include <stdint.h>
/*-- Types Definitions -------------------------------------------------------*/

/*-- Defines -----------------------------------------------------------------*/

/* Task Scheduler state machine status definitions */
#define NO_TASK_PENDING     0x00u
#define TASKS_1_MS          0x01u
#define TASKS_2_MS_A        0x02u
#define TASKS_2_MS_B        0x03u
#define TASKS_10_MS         0x04u
#define TASKS_50_MS         0x05u
#define TASKS_100_MS        0x06u

/* Global Task Scheduler Status definitions */
#define TASK_SCHEDULER_INIT             0x00u   
#define TASK_SCHEDULER_RUNNING          0x01u
#define TASK_SCHEDULER_OVERLOAD_1MS     0x02u
#define TASK_SCHEDULER_OVERLOAD_2MS_A   0x03u
#define TASK_SCHEDULER_OVERLOAD_2MS_B   0x04u
#define TASK_SCHEDULER_HALTED           0xAAu

#define NO_OF_TASKS						(0x06u)
#define TASK_SCHEDULER_OVERLOAD			(0x55u)

typedef void (*FuncPtr)(void);

typedef struct  
{
	uint8_t runTask, tickValue, taskOverload;
	FuncPtr tskFcnPtr;
}TaskType;

/*-- Macros ------------------------------------------------------------------*/


/*-- Function Prototypes -----------------------------------------------------*/

/** Sheduler Initalization (arming) */
void vfnScheduler_Init(FuncPtr *ParFuncArray);

/** Scheduler kick-off function */
void vfnScheduler_Start(void);

/** Scheduler stop function */
void vfnScheduler_Stop(void);

/** Multi-thread round robin task scheduler */
void vfnTask_Scheduler(void);

/*******************************************************************************/

#endif /* APP_SCHEDULER_H */