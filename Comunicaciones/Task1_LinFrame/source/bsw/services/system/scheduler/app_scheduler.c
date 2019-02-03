/*******************************************************************************/
/**
\file       app_scheduler.c
\brief      Multi-thread Task scheduler.
\author     Abraham Tezmol
\version    0.1
\date       09/09/2008
*/

/** Variable types and common definitions */

/** Scheduler function prototypes definitions */
#include "app_scheduler.h"
#include "chip.h"

/* -- Global Variables --------------------------------------------------------*/
uint8_t gu8Scheduler_Status;
uint8_t gu8Scheduler_Counter;
uint8_t gu8Scheduler_Thread_ID;
uint8_t gu8Scheduler_Thread_ID_Backup;
uint8_t u8_10ms_Counter;
uint8_t u8_50ms_Counter;
uint8_t u8_100ms_Counter;

TaskType task_array[NO_OF_TASKS];

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

void Scheduler_Handler(void)
{
	
	/*-- Update scheduler control variable --*/
	gu8Scheduler_Counter++;
	
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	/*  1ms execution thread - used to derive two execution threads:                */
	/*  a) 1ms thread (highest priority tasks)                                      */
	/*  b) 100ms thread (lowest priority tasks)                                     */
	/*  As any other thread on this scheduling scheme,                              */
	/*  all tasks must be executed in <= 500us                                      */
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	if ((gu8Scheduler_Counter & 0x01) == 0x01)
	{
		u8_100ms_Counter++;
		/*-- Allow 100 ms periodic tasks to be executed --*/
		if (u8_100ms_Counter >= 100)
		{
			gu8Scheduler_Thread_ID = TASKS_100_MS;
			u8_100ms_Counter = 0;
			task_array[TASKS_100_MS-1].runTask=1;
			task_array[TASKS_100_MS-1].tickValue = gu8Scheduler_Counter;
		}
		/*-- Allow 1 ms periodic tasks to be executed --*/
		else
		{
			gu8Scheduler_Thread_ID = TASKS_1_MS;
		}
		task_array[TASKS_1_MS-1].runTask=1;
		task_array[TASKS_1_MS-1].tickValue = gu8Scheduler_Counter;
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
		if ((gu8Scheduler_Counter & 0x02) == 0x02)
		{
			u8_50ms_Counter++;
			/*-- Allow 50 ms periodic tasks to be executed --*/
			if (u8_50ms_Counter >= 25)
			{
				gu8Scheduler_Thread_ID = TASKS_50_MS;
				u8_50ms_Counter = 0;
				task_array[TASKS_50_MS-1].runTask=1;
				task_array[TASKS_50_MS-1].tickValue = gu8Scheduler_Counter;
			}
			/*-- Allow 2 ms group A periodic tasks to be executed --*/
			else
			{
				gu8Scheduler_Thread_ID = TASKS_2_MS_A;
			}
			task_array[TASKS_2_MS_A-1].runTask=1;
			task_array[TASKS_2_MS_A-1].tickValue = gu8Scheduler_Counter;
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
			if ((gu8Scheduler_Counter & 0x03) == 0x00)
			{
				u8_10ms_Counter++;
				/*-- Allow 10 ms periodic tasks to be executed --*/
				if (u8_10ms_Counter >= 5)
				{
					gu8Scheduler_Thread_ID = TASKS_10_MS;
					u8_10ms_Counter = 0;
					task_array[TASKS_10_MS-1].runTask=1;
					task_array[TASKS_10_MS-1].tickValue = gu8Scheduler_Counter;
				}
				/*-- Allow 2 ms group B periodic tasks to be executed --*/
				else
				{
					gu8Scheduler_Thread_ID = TASKS_2_MS_B;
				}
				task_array[TASKS_2_MS_B-1].runTask=1;
				task_array[TASKS_2_MS_B-1].tickValue = gu8Scheduler_Counter;
			}
		}
	}
}

/*******************************************************************************/
/**
* \brief    Scheduler - Periodic Interrup Timer Initialization
* \author   Abraham Tezmol
* \param    void
* \return   void
* \todo     
*/
void vfnScheduler_Init(FuncPtr *ParFuncArray)
{   
	uint8_t task_idx;
  /* Init Global and local Task Scheduler variables */
  gu8Scheduler_Counter = 0;   
  gu8Scheduler_Thread_ID = NO_TASK_PENDING;
  u8_10ms_Counter = 0;
  u8_50ms_Counter = 0;
  u8_100ms_Counter = 0;
  gu8Scheduler_Status = TASK_SCHEDULER_INIT;
	for (task_idx = 0; task_idx<NO_OF_TASKS;task_idx++)
	{
		task_array[task_idx].tskFcnPtr = ParFuncArray[task_idx];
	}
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
void vfnScheduler_Start(void)
{
    TimeTick_Configure(Scheduler_Handler);
    gu8Scheduler_Status = TASK_SCHEDULER_RUNNING;
}

/*******************************************************************************/
/**
* \brief    Scheduler Stop - stop execution of Multi-thread Round Robin scheduling scheme.
* \author   Abraham Tezmol
* \param    void
* \return   void
* \todo     
*/
void vfnScheduler_Stop(void)
{  
    /* Update scheduler status accordingly */
    gu8Scheduler_Status = TASK_SCHEDULER_HALTED;
}

/*******************************************************************************/
/**
* \brief    Multi-thread round robin task Scheduler  (non-preemtive)        \n
            It calls the different tasks based on the status of             \n   
            "gu8Scheduler_Thread_ID". This variable is modified by          \n
            ISR "vfnScheduler_PIT_Isr"                                        \n
            List of tasks shall be defined @ "tasks.h" file
* \author   Abraham Tezmol
* \param    void
* \return   void
* \todo     
*/
void vfnTask_Scheduler(void)
{
	uint8_t task_idx;
	
	for (task_idx = 0;task_idx < NO_OF_TASKS; task_idx++)
	{
		if( 1 == task_array[task_idx].runTask )
		{
			task_array[task_idx].runTask = 0;
			if ( NULL != task_array[task_idx].tskFcnPtr )
			{
				task_array[task_idx].tskFcnPtr();
			}
			if ( gu8Scheduler_Counter != task_array[task_idx].tickValue )
			{
				task_array[task_idx].taskOverload = 1;
				gu8Scheduler_Status = TASK_SCHEDULER_OVERLOAD;
			}
			else{
				gu8Scheduler_Status = TASK_SCHEDULER_RUNNING;
			}
		}
	}

}
