/*******************************************************************************/
/**
\file       SchM_Cfg.h
\brief      Scheduler Configuration Header.
   \~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   \version       1.0
   \author        Francisco Martinez
   \description   Initial version of Scheduler Configuration
   \date          17/09/2018
*/
#ifndef _SCHM_CFG_H
#define _SCHM_CFG_H

	#include "Std_Types.h"

	typedef  void  ( * SchMCallbackType )( void );

	/* Task Scheduler Tasks IDs definitions */
	typedef enum  
	{   
		TASK_1MS,
		TASK_2MSA,
		TASK_2MSB,
		TASK_10MS,
		TASK_50MS,
		TASK_100MS,
        TASK_SW0,
		TASK_BKG,
	}SchMTaskIdType;
	
	typedef struct
	{
		uint8_t           TaskPriority;
		SchMTaskIdType    TaskId;
		SchMCallbackType TaskFcnPtr;
	}SchMTaskType;
	
	typedef struct
	{
		uint8_t NoOfTasks;
		SchMTaskType * TaskCfg;
	}SchMCfgType;

    extern SchMCfgType ScheduleConfig[];

#endif /* _SCHM_CFG_H */