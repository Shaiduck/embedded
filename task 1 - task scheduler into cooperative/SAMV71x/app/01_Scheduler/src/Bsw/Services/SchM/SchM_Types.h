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
		TASKS_1_MS = 100,
		TASKS_2_MS_A = 50,
		TASKS_2_MS_B = 50,
		TASKS_10_MS = 10,
		TASKS_50_MS = 2,
		TASKS_100_MS = 1,
		TASK_SW0 = 200,
		TASK_NULL = 0,
	}SchMTasksIdType;

		/* Task Scheduler Tasks IDs definitions */
	typedef enum  
	{
        STATE_SUSPENDED,
        STATE_READY,
        STATE_RUNNING,
	}SchMTaskStateType;

	/* Task Scheduler Tasks IDs definitions */
	typedef struct SchMTaskType  
	{
        uint8_t taskPriority;
        SchMTasksIdType taskId;
        SchM_CallbackType taskFcnPtr;
	}SchMTaskType;


/*============================================================================*/
#endif /* SCHM_TYPES */
