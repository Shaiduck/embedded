/*******************************************************************************/
/**
\file       SchM_Types.h
\brief      Scheduler Type Definitions.
   \~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   \version       1.0
   \author        Francisco Martinez
   \description   Initial version of Task Type Definitios
   \date          20/08/2018
*/

#ifndef SCHM_TYPES
#define SCHM_TYPES

	/** Standard Types */
	#include "Std_Types.h"
	
	#define SCHM_NUMBER_OF_TASKS                    7

	typedef  void  ( * SchM_CallbackType )( void );

	/* Task Scheduler Tasks IDs definitions */
	typedef enum  
	{   
		TASKS_1_MS = 0,
		TASKS_2_MS_A = 1,
		TASKS_2_MS_B = 2,
		TASKS_10_MS = 3,
		TASKS_50_MS = 4,
		TASKS_100_MS = 5,
		TASKS_INTERRUPT = 6,
		TASK_NULL,
	}SchMTasksIdType;

		/* Task Scheduler Tasks IDs definitions */
	typedef enum  
	{
        STATE_SUSPENDED,
        STATE_READY,
        STATE_RUNNING
	}SchMTaskStateType;

	/* Task Scheduler Tasks IDs definitions */
	typedef struct SchMTaskType  
	{
        SchM_CallbackType taskFcnPtr;
        SchMTasksIdType taskId;
        uint8_t taskPriority;
	}SchMTaskType;


/*============================================================================*/
#endif /* SCHM_TYPES */
