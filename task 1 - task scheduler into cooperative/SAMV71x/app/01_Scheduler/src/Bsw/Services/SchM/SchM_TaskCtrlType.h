/*******************************************************************************/
/**
\file       SchM_TaskType.h
\brief      
   \~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   \version       1.0
   \author        
   \description   
   \date          
*/

#ifndef SCHM_TASKTYPE
#define SCHM_TTASKYPE

	/** Standard Types */
	#include "Std_Types.h"

		/* Task Scheduler Tasks IDs definitions */
	typedef struct SchMTaskCtrlType
	{
        uint8_t runTask;
        SchM_CallbackType taskFcnPtr;
        SchMTasksIdType taskId;
        uint8_t taskOverload;
        uint8_t taskPriority;
        SchMTaskStateType taskState;
        uint8_t tickValue;
	}SchMTaskCtrlType;

/*============================================================================*/
#endif /*  */
