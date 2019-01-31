/*******************************************************************************/
/**
\file       app_scheduler.h
\brief      Task scheduler function prototypes
\author     Abraham Tezmol
\version    1.1
\date       07/09/2013
*/

#ifndef APP_SCHEDULER_H        /*prevent duplicated includes*/
#define APP_SCHEDULER_H

/*-- Includes ----------------------------------------------------------------*/

#include "compiler.h"
#include "Std_Types.h"

/*****************************************************************************************************
* Declaration of module wide TYPES
*****************************************************************************************************/
typedef enum
{
    SUSPENDED,
    READY,
    RUNNING
}tTaskStates;

/* Task Scheduler Tasks IDs definitions */
typedef enum  
{   
    TASKS_1_MS,
    TASKS_2_MS_A,
    TASKS_2_MS_B,
    TASKS_10_MS,
    TASKS_50_MS,
    TASKS_100_MS,
    TASKS_EVENT_A,
    TASKS_EVENT_B,
    TASKS_EVENT_C,
    TASKS_EVENT_D,
    TASKS_EVENT_E,
    TASKS_EVENT_F,
    TASK_NULL,
}tSchedulerTasks_ID;

typedef struct 
{
    tSchedulerTasks_ID     TaskId;
    tPtr_to_function       ptrTask;
    tTaskStates            enTaskState;
    uint8_t                u8Priority;
    
}tSchedulingTask;

/*****************************************************************************************************
* Definition of module wide MACROS / #DEFINE-CONSTANTS 
*****************************************************************************************************/



/* Global Task Scheduler Status definitions */
#define    TASK_SCHEDULER_INIT              0x00u
#define    TASK_SCHEDULER_RUNNING           0x01u
#define    TASK_SCHEDULER_OVERLOAD_1MS      0x02u
#define    TASK_SCHEDULER_OVERLOAD_2MS_A    0x03u
#define    TASK_SCHEDULER_OVERLOAD_2MS_B    0x04u
#define    TASK_SCHEDULER_HALTED            0xAAu

#define    TASK_SCH_MAX_NUMBER_TIME_TASKS   0x06u
#define    TASK_SCH_MAX_NUMBER_EVENT_TASKS  0x05u

#define    TASK_SCHEDULER_BASE_FREQ		    2000
/*****************************************************************************************************
* Definition of module wide VARIABLEs
*****************************************************************************************************/
extern tSchedulingTask TimeTriggeredTasks[TASK_SCH_MAX_NUMBER_TIME_TASKS];

/*****************************************************************************************************
* Declaration of module wide FUNCTIONS
*****************************************************************************************************/

/** Scheduler Initalization (arming) */
void vfnScheduler_Init(void);

/** Scheduler kick-off function */
void vfnScheduler_Start(void);

/** Scheduler stop function */
void vfnScheduler_Stop(void);

/** Cooperative Scheduler - Event Activation Handler */
uint8_t u8Scheduler_EventActivationHandler(tPtr_to_function ptrTask, tSchedulerTasks_ID TaskId, uint8_t priority);

/** Cooperative Scheduler - Schedule Point */
void vfnSchedulepoint( void );

/** Multi-thread round robin task scheduler */
void vfnTask_Scheduler(void);

void vfnScheduler_Callback( void  );
/*******************************************************************************/

#endif /* APP_SCHEDULER_H */