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
        uint8_t tickCounter;
        uint8_t taskRunning;
        uint8_t taskOverload;
        SchMTaskStateType taskState;

		SchMTaskType* taskInfo;
	}SchMTaskCtrlType;

/*============================================================================*/
#endif /*  */
