/*******************************************************************************/
/**
\file       SchM_Tasks.h
\brief      Tasks to be assigned to each execution thread of Task scheduler.
   \~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   \version       1.1
   \author        Francisco Martinez
   \description   List of task name updates
   \date          20/Aug/2018
   \~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   \version       1.0
   \author        Abraham Tezmol
   \description   Initial version
   \date          10/Feb/2008
*/

#ifndef SCHM_TASKS
	#define SCHM_TASKS
  
	/** Scheduler function prototypes definitions */

	/* List of tasks to be executed @ 1ms */
	extern void SchM_Task_1ms( void );

	/* List of tasks to be executed @ 2ms, first group */
	extern void SchM_Task_2ms_A( void );

	/* List of tasks to be executed @ 2ms, second group */
	extern void SchM_Task_2ms_B( void );
		
	/* List of tasks to be executed @ 10ms */
	extern void SchM_Task_10ms(  void );

	/* List of tasks to be executed @ 50ms */
	extern void SchM_Task_50ms( void );

	/* List of tasks to be executed @ 100ms */
	extern void SchM_Task_100ms( void );

  /* List of tasks to be executed @ SW0 */
  extern void SchM_Task_SW0( void );

/*============================================================================*/
#endif /* SCHM_TASKS */
