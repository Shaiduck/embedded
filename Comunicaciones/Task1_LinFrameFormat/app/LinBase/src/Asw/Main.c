/****************************************************************************************************/
/**
  \mainpage
  \n 
  \brief        Lin example
  \author       
  \project       
  \version      
  \date         
   
  Program compiled with  WinIDEA Open Build 9.12.256 (54401), tested on Atmel SAMV71 Xplained Ultra
*/
/****************************************************************************************************/

/*~~~~~~  Headers ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/** Main group of includes for board definitions, chip definitions and type definitions */
#include "Std_Types.h"
/** Task scheduler definitions */
#include "SchM.h"
/** LED control definitions */
#include "Led_Ctrl.h"
/** Watchdog control function prototypes definitions */
#include "Wdg.h"
/** Button Control interfaces */
#include "Button_Ctrl.h"
/** Uart interfaces */
#include "Uart.h"
/** Lin interfaces */
#include "Lin.h"

/*~~~~~~  Local definitions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~  Global variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~  Local functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/
/**
 *  \brief getting-started Application entry point.
 *
 *  \return Unused (ANSI-C compatibility).
 */
extern int main(void)
{
	/* Disable watchdog */
	Wdg_Disable();
	printf("\n\r-- Scheduler Project %s --\n\r", SOFTPACK_VERSION);
	printf("-- %s\n\r", BOARD_NAME);
	printf("-- Compiled: %s %s With %s --\n\r", __DATE__, __TIME__, COMPILER_NAME);
	/* Enable I and D cache */
	SCB_EnableICache();
	/* SCB_EnableDCache(); */
	/* Configure LEDs */
	printf("-- Led Control --\n\r");
	LedCtrl_Configure();

	printf("-- Button Control --\n\r");
	ButtonCtrl_ConfigureSW0Button();

	/* Uart Inititalization */
	printf("-- Lin Initialization --\n\r");
	Lin_Init(&LinChannelConfig[0]);

	/* Scheduler Inititalization */
	printf("-- Scheduler Initialization --\n\r");
	SchM_Init(ScheduleConfig);

	/* Should never reach this code */
	for (;;)
	{
		printf("-- Unexpected Error at Scheduler Initialization --\n\r");
	}
}
