/*******************************************************************************/
/**
\file       SchM.c
\brief      Multi-thread Task scheduler.
   \~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   \version       1.1
   \author        Francisco Martinez
   \description   Scheduler updates
   \date          20/Aug/2018
   \~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   \version       1.0
   \author        Abraham Tezmol
   \description   Initial version
   \date          09/Sep/2008
*/

/** Standard Types */
#include "Std_Types.h"
/** Scheduler function prototypes definitions */
#include "SchM.h"
/** Scheduler Type definitions */
#include "SchM_Types.h"
/** Tasks definition */
#include "SchM_Tasks.h"

#include "SchM_TaskCtrlType.h"

/*****************************************************************************************************
* Definition of module wide (CONST-) CONSTANTs 
*****************************************************************************************************/
/* Global Task Scheduler Status definitions */

#define    SCHM_TASK_SCHEDULER_BASE_FREQ		 2000u
#define    SCHM_TASK_SCH_MAX_NUMBER_TIME_TASKS   0x06u

#define    SCHM_TASK_SCHEDULER_INIT              0x00u
#define    SCHM_TASK_SCHEDULER_RUNNING           0x01u
#define    SCHM_TASK_SCHEDULER_OVERLOAD_1MS      0x02u
#define    SCHM_TASK_SCHEDULER_OVERLOAD_2MS_A    0x03u
#define    SCHM_TASK_SCHEDULER_OVERLOAD_2MS_B    0x04u
#define    SCHM_TASK_SCHEDULER_HALTED            0xAAu

/*****************************************************************************************************
* Definition of  VARIABLEs - 
*****************************************************************************************************/

/* Global pointer used to invoke callback function upon Timer event*/
SchM_CallbackType pfctnSysTick = (SchM_CallbackType)NULL;


uint8_t SchM_Status;
uint8_t SchM_Counter;

SchMTasksIdType SchM_Task_ID_Activated;
SchMTasksIdType SchM_Task_ID_Running;
SchMTasksIdType SchM_Task_ID_Backup;
SchMTasksIdType SchM_Task_ID_Interrupting;

uint8_t SchM_10ms_Counter;
uint8_t SchM_50ms_Counter;
uint8_t SchM_100ms_Counter;

SchMTaskCtrlType taskController[SCHM_NUMBER_OF_TASKS];

/*****************************************************************************************************
* Code of module wide private FUNCTIONS
*****************************************************************************************************/
/*******************************************************************************/
/**
* \brief    Periodic Interrupt Timer Service routine.                            \n
            This interrupt is the core of the task scheduler.                   \n
            It is executed every 500us                                          \n
            It defines 3 basic threads from which other 3 threads are derived:  \n
            a) 1ms thread (basic) ->  100ms thread (derived)                    \n
            b) 2ms A thread (basic)-> 50ms thread (derived)                     \n
            c) 2ms B thread (basic)-> 10ms thread (derived)                     \n
            It partitions core execution time into time slices (500us each one).\n 
            This arrangement assures core will have equal task loading across time.\n   
            For more information on how time slice is assigned to each thread,  \n
            refer to file "S12X Task Scheduler Layout.xls"
* \author   Abraham Tezmol
* \param    void
* \return   void
* \todo
*/

void SchM_Callback(void)
{
    /*-- Update scheduler control variable --*/
    SchM_Counter++;

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*  1ms execution thread - used to derive two execution threads:                */
    /*  a) 1ms thread (highest priority tasks)                                      */
    /*  b) 100ms thread (lowest priority tasks)                                     */
    /*  As any other thread on this scheduling scheme,                              */
    /*  all tasks must be executed in <= 500us                                      */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    if( ( SchM_Counter & 0x01u ) == 0x01u )
    {
        SchM_100ms_Counter++;
        /*-- Allow 100 ms periodic tasks to be executed --*/
        if( SchM_100ms_Counter >= 100u )
        {
            /* Indicate that Task is Ready to be executed */ 
            SchM_Task_ID_Activated = TASKS_100_MS;
            SchM_100ms_Counter       = 0u;
        }
        /*-- Allow 1 ms periodic tasks to be executed --*/
        else
        {
            SchM_Task_ID_Activated = TASKS_1_MS;
        }
    }
    else
    {
        /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        /*  2ms execution thread - used to derive two execution threads:                */
        /*  a) 2ms group A thread (high priority tasks)                                 */
        /*  b) 50ms thread (second lowest priority tasks)                               */
        /*  As any other thread on this scheduling scheme,                              */
        /*  all tasks must be executed in <= 500us                                      */
        /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        if( ( SchM_Counter & 0x02u ) == 0x02u )
        {
            SchM_50ms_Counter++;
            /*-- Allow 50 ms periodic tasks to be executed --*/
            if( SchM_50ms_Counter >= 25u )
            {
                SchM_Task_ID_Activated = TASKS_50_MS;
                SchM_50ms_Counter        = 0u;
            }
            /*-- Allow 2 ms group A periodic tasks to be executed --*/
            else
            {
                SchM_Task_ID_Activated = TASKS_2_MS_A;
            }
        }
        else
        {
            /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            /*  2ms execution thread - used to derive two execution threads:                */
            /*  a) 2ms group B thread (high priority tasks)                                 */
            /*  b) 10ms thread (medium priority tasks)                                      */
            /*  As any other thread on this scheduling scheme,                              */
            /*  all tasks must be executed in <= 500us                                      */
            /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            if( ( SchM_Counter & 0x03u ) == 0x00u )
            {
                SchM_10ms_Counter++;
                /*-- Allow 10 ms periodic tasks to be executed --*/
                if( SchM_10ms_Counter >= 5u )
                {
                    SchM_Task_ID_Activated = TASKS_10_MS;
                    SchM_10ms_Counter        = 0u;
                }
                /*-- Allow 2 ms group B periodic tasks to be executed --*/
                else
                {
                    SchM_Task_ID_Activated = TASKS_2_MS_B;
                }
            }
        }
    }
}

/****************************************************************************************************/
/**
* \brief    SysTick - Initialization
* \author   Abraham Tezmol
* \param    int32_t base_freq	--> Requested SysTick interrupt frequency
* \param    SchM_CallbackType sysTick_handler	--> Callback function to handle SysTick ISR.
* \return   uint8_t --> 0 - Successful configuration of SysTick IRQ and SysTick Timer, 1 - Invalid configuration
* \todo
*/

uint8_t SysTick_init(uint32_t base_freq, SchM_CallbackType sysTick_handler)
{
	pfctnSysTick = sysTick_handler;
	return SysTick_Config(SystemCoreClock / base_freq);
}

/*******************************************************************************/
/**
* \brief    Scheduler Start - Once time base is armed, start execution of   \n
            Multi-thread Round Robin scheduling scheme.                     \n
            This function requires prior execution of "vfnScheduler_Init"
* \author   Abraham Tezmol
* \param    void
* \return   void
* \todo     
*/

void SchM_Start(void)
{
	if (SysTick_init(SCHM_TASK_SCHEDULER_BASE_FREQ, SchM_Callback)) 
	{
		while (1);
		printf( "-- SysTick Initialization Failed --\n\r" ) ;
	}
	SchM_Status = SCHM_TASK_SCHEDULER_RUNNING;
	printf( "-- Scheduler Running --\n\r" ) ;
	/* Once all the basic services have been started, go to infinite loop to serviced activated tasks */
	while(1)
    {
		//SchM_Scheduler();
        SchM_SchedulePoint();
	}
}

/*******************************************************************************/
/**
* \brief    Multi-thread round robin task Scheduler  (non-preemtive)        \n
            It calls the different tasks based on the status of             \n   
            List of tasks shall be defined @ "tasks.h" file
* \author   Abraham Tezmol
* \param    void
* \return   void
* \todo     
*/

void SchM_Scheduler(void)
{
    //interruptions have bigger priority.
    if (SchM_Task_ID_Activated == TASKS_INTERRUPT)
    {
        SchM_Task_ID_Running = TASKS_INTERRUPT;
        taskController[TASKS_INTERRUPT].taskFcnPtr();
        SchM_Task_ID_Running = TASK_NULL;
    } else // if not an interruption
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*  1ms execution thread - used to derive two execution threads:                */
    /*  a) 1ms thread (high priority tasks)                                         */
    /*  b) 100ms thread (lowest priority tasks)                                     */
    /*  As any other thread on this scheduler, all tasks must be executed in <=500us*/
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    if( ( SchM_Task_ID_Activated == TASKS_1_MS )
         || ( SchM_Task_ID_Activated == TASKS_100_MS ) )
    {
        /* Make a copy of scheduled task ID */
        SchM_Task_ID_Backup = SchM_Task_ID_Activated;
        
        SchM_Task_ID_Running = TASKS_1_MS;
        taskController[TASKS_1_MS].taskFcnPtr();
        SchM_Task_ID_Running = TASK_NULL;
        if( SchM_Task_ID_Activated == TASKS_100_MS )
        {
            SchM_Task_ID_Running = TASKS_100_MS;
            taskController[TASKS_100_MS].taskFcnPtr();
            SchM_Task_ID_Running = TASK_NULL;
        }
        /* Verify that thread execution took less than 500 us */
        if( SchM_Task_ID_Backup == SchM_Task_ID_Activated )
        {
             /* In case execution of all thread took less than 500us */
            SchM_Task_ID_Activated = TASK_NULL;
        }
        else
        {
            SchM_Status = SCHM_TASK_SCHEDULER_OVERLOAD_1MS;
        }
    }
    else
    {
        /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        /*  2ms execution thread - used to derive two execution threads:                */
        /*  a) 2ms group A thread (high priority tasks)                                 */
        /*  b) 50ms thread (second lowest priority tasks)                               */
        /*  As any other thread on this scheduler, all tasks must be executed in <=500us*/
        /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        if( ( SchM_Task_ID_Activated == TASKS_2_MS_A )
             || ( SchM_Task_ID_Activated == TASKS_50_MS ) )
        {
            /* Make a copy of scheduled task ID */
            SchM_Task_ID_Backup = SchM_Task_ID_Activated;
            SchM_Task_ID_Running = TASKS_2_MS_A;
            taskController[TASKS_2_MS_A].taskFcnPtr();
            SchM_Task_ID_Running = TASK_NULL;
            if( SchM_Task_ID_Activated == TASKS_50_MS )
            {
                SchM_Task_ID_Running = TASKS_50_MS;
                taskController[TASKS_50_MS].taskFcnPtr();
                SchM_Task_ID_Running = TASK_NULL;
            }
            /* Verify that thread execution took less than 500 us */
            if( SchM_Task_ID_Backup == SchM_Task_ID_Activated )
            {
                 /* In case execution of all thread took less than 500us */
                SchM_Task_ID_Activated = TASK_NULL;
            }
            else
            {
                SchM_Status = SCHM_TASK_SCHEDULER_OVERLOAD_2MS_A;
            }
        }
        else
        {
            /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            /*  2ms execution thread - used to derive two execution threads:                */
            /*  a) 2ms group B thread (high priority tasks)                                 */
            /*  b) 10ms thread (medium priority tasks)                                      */
            /*  As any other thread on this scheduler, all tasks must be executed in <=500us*/
            /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            if( ( SchM_Task_ID_Activated == TASKS_2_MS_B )
                 || ( SchM_Task_ID_Activated == TASKS_10_MS ) )
            {
                /* Make a copy of scheduled task ID */
                SchM_Task_ID_Backup = SchM_Task_ID_Activated;
                SchM_Task_ID_Running = TASKS_2_MS_B;
                taskController[TASKS_2_MS_B].taskFcnPtr();
                SchM_Task_ID_Running = TASK_NULL;
                if( SchM_Task_ID_Activated == TASKS_10_MS )
                {
                    SchM_Task_ID_Running = TASKS_10_MS;
                    taskController[TASKS_10_MS].taskFcnPtr();
                    SchM_Task_ID_Running = TASK_NULL;
                }
                 /* Verify that thread execution took less than 500 us */
                if( SchM_Task_ID_Backup == SchM_Task_ID_Activated )
                {
                    /* In case execution of all thread took less than 500us */
                    SchM_Task_ID_Activated = TASK_NULL;
                }
                else
                {
                    SchM_Status = SCHM_TASK_SCHEDULER_OVERLOAD_2MS_B;
                }
            }
        }
    }        
}

/*****************************************************************************************************
* Code of public FUNCTIONS
*****************************************************************************************************/

/****************************************************************************************************/
/**
* \brief    Scheduler - Initialization
* \author   Abraham Tezmol
* \param    void
* \return   void
* \todo     
*/
void SchM_Init(SchMTaskType* taskArray)
{    
    /* Init Global and local Task Scheduler variables */
    SchM_Counter   = 0u;
    SchM_Task_ID_Activated = TASK_NULL;
    SchM_Task_ID_Running = TASK_NULL;
    SchM_Task_ID_Backup = TASK_NULL;
    SchM_10ms_Counter        = 0u;
    SchM_50ms_Counter        = 0u;
    SchM_100ms_Counter       = 0u;
    SchM_Status    = SCHM_TASK_SCHEDULER_INIT;

    //init task controller    
    uint8_t i;
    //less than 6, since those are the number of functions already defined.
    for ( i = 0; i < 6; i++)
    {
        taskController[i].taskFcnPtr = taskArray[i].taskFcnPtr;
        taskController[i].taskId = taskArray[i].taskId;
        taskController[i].taskPriority = taskArray[i].taskPriority;
        taskController[i].taskOverload = 0;
        taskController[i].taskState = STATE_SUSPENDED;
        taskController[i].tickValue = 0;
    }

	/* Start scheduler */
	SchM_Start();
    
}

/*******************************************************************************/
/**
* \brief    Scheduler Stop - stop execution of Multi-thread Round Robin scheduling scheme.
* \author   Abraham Tezmol
* \param    void
* \return   void
* \todo     
*/
void SchM_Stop(void)
{  
    /* Update scheduler status accordingly */
    SchM_Status = SCHM_TASK_SCHEDULER_HALTED;
}

/***************************************************************************************************/

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
		(*pfctnSysTick)();
	}
}


/**
 * This should force the execution of a new task if it seems fit.
 * maybe one or two tasks could be lost.
 * TODO: Check if it works
 */
void SchM_SchedulePoint(void)
{
    //Allows activated higher priority tasks to run
    if (SchM_Task_ID_Running > SchM_Task_ID_Activated)
    {
        SchM_Task_ID_Backup = SchM_Task_ID_Running;
        SchM_Task_ID_Running = SchM_Task_ID_Activated;
        if (SchM_Task_ID_Running != TASK_NULL)
        {
            taskController[SchM_Task_ID_Running].taskFcnPtr();
        }
        SchM_Task_ID_Running = TASK_NULL;
        SchM_Task_ID_Backup = TASK_NULL;
    }
}

/**
 * supports task activation
 * this calls the schedule point and force a reevalution
 * TODO: Test and maybe improve
 */
void SchM_ActivateTask(SchMTasksIdType TaskId)
{
    taskController[TaskId].taskFcnPtr();
}

/**
 * THIS IS A PLACEHOLDER SO THAT IT COMPILES
 * It should be the handler for the button
 * TODO: Expand
 */
void TC9_Handler(void)
{
    SchM_ActivateTask(TASKS_INTERRUPT);
}