/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>

/** Scheduler function prototypes definitions */
#include "scheduler.h"
#include "tasks.h"
/** Communication Protocol Functions */
#include "lin_master.h"
#include "mcanif.h"

FuncPtr	TasksFunc[]={
    vfnTsk_1ms,
    vfnTsk_2msA,
    vfnTsk_2msB,
    vfnTsk_10ms,
    vfnTsk_50ms,
    vfnTsk_100ms
 };


int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	sysclk_init();
	board_init();
	configure_mcan();

	/* Insert application code here, after the board has been initialized. */
	
  
	vfnLinMaster_Init();
  
	/* Initialize Task Scheduler */
	vfnScheduler_Init(TasksFunc);
	/* Start execution of task scheduler */
	vfnScheduler_Start();

	/*-- Loop through all the periodic tasks from Task Scheduler --*/
	for(;;)
	{
		/* Perform all scheduled tasks */
		vfnTask_Scheduler();
	}
}
