/****************************************************************************************************/
/**
\file       SchM_Tasks.c
\brief      List of Tasks
   \~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   \version       1.1
   \author        Francisco Martinez
   \description   List of task name updates
   \date          20/08/2018
   \~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   \version       1.0
   \author        Abraham Tezmol
   \description   Multi-thread Task scheduler - list of tasks.   
   \date          07/09/2013
*/
/****************************************************************************************************/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Scheduler function prototypes definitions */
#include    "SchM_Tasks.h"
/* LED control definitions */ 
#include    "Led_Ctrl.h"

/*****************************************************************************************************
* Definition of  VARIABLEs - 
*****************************************************************************************************/


/*****************************************************************************************************
* Definition of module wide (CONST-) CONSTANTs 
*****************************************************************************************************/

/*****************************************************************************************************
* Code of module wide FUNCTIONS
*****************************************************************************************************/

/* List of tasks to be executed @ 1ms */
void SchM_Task_1ms( void )
{

}

/* List of tasks to be executed @ 2ms, first group */
void SchM_Task_2ms_A(void)
{
	
}

/* List of tasks to be executed @ 2ms, second group */
void SchM_Task_2ms_B( void )
{
	
}
    
/* List of tasks to be executed @ 10ms */
void SchM_Task_10ms( void )
{
    LedCtrl_BlinkingPattern();
}

/* List of tasks to be executed @ 50ms */
void SchM_Task_50ms( void )
{
	
}

/* List of tasks to be executed @ 100ms */
void SchM_Task_100ms( void )
{ 
    
}
