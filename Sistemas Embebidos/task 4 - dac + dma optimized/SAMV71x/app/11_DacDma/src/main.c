/****************************************************************************************************/
/**
  \mainpage
  \n 
  \brief        Main application (main module)
  \author       Abraham Tezmol Otero, M.S.E.E
  \project      Tau 
  \version      1.0
  \date         12/Jun/2016
   
  Program compiled with  WinIDEA Open Build 9.12.256 (54401), tested on Atmel SAMV71 Xplained Ultra
*/
/****************************************************************************************************/


/*~~~~~~  Headers ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/** Main group of includes for board definitions, chip definitions and type definitions */
#include    "board.h"
#include "tc.h"
#include <stdbool.h>
#include <stdio.h>
/** Task scheduler definitions */
#include    "app_scheduler.h"
/** LED control definitions */ 
#include    "led_ctrl.h"
/** UART communication */
#include    "serial_ctrl.h"
/** Watchdog control function prototypes definitions */
#include    "wdt_ctrl.h"
/** Dynamic Memory allocation services */
#include    "memory_allocation.h"
#include "dac.h"

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
extern int main( void )
{
	
	/* Disable watchdog */
	vfnWdtCtrl_Disable();

	Tc customTc;
	customTc.TC_BCR = TC_BCR_SYNC; /**< \brief (Tc Offset: 0xC0) Block Control Register */
	customTc.TC_BMR = TC_BMR_TC0XC0S_TCLK0; /**< \brief (Tc Offset: 0xC4) Block Mode Register */
	customTc.TC_QIER = TC_QIER_IDX;/**< \brief (Tc Offset: 0xC8) QDEC Interrupt Enable Register */
	customTc.TC_QIDR = TC_QIDR_IDX;/**< \brief (Tc Offset: 0xCC) QDEC Interrupt Disable Register */
	//customTc.TC_QIMR = TC_QIMR_IDX;/**< \brief (Tc Offset: 0xD0) QDEC Interrupt Mask Register */
	//customTc.TC_QISR = TC_QISR_IDX;/**< \brief (Tc Offset: 0xD4) QDEC Interrupt Status Register */
	customTc.TC_FMR = TC_FMR_ENCF0;/**< \brief (Tc Offset: 0xD8) Fault Mode Register */
	//customTc.Reserved1;
	//customTc.TC_WPMR;/**< \brief (Tc Offset: 0xE4) Write Protection Mode Register */
	//customTc.TC_CHANNEL[0] /**< \brief (Tc Offset: 0x0) channel = 0 .. 2 */

	TC_Configure(&customTc, 0, TC_CMR_WAVE);
	TC_Start(&customTc, 0);

	/* Enable I and D cache */
	SCB_EnableICache();
	SCB_EnableDCache(); 
	/* Dynamic Memory Allocation initialization */
	vfnMemAlloc_Init(&DynamicMemAlloc_config[0]);
	/* Configure LEDs */
	vfnLedCtrl_Configure(); 
	/* Initialize UART communicaiton */
	vfnSerialCtrl_Init();
	/* Configure Non-preemtive scheduler */
	vfnScheduler_Init();
	/* Start scheduler */
	dac_initialization();
	// vfnScheduler_Start(dac_dmaTransfer);
	vfnScheduler_Start(NULL);
	dac_dmaTransfer();
	/* Once all the basic services have been started, go to infinite loop to serviced activated tasks */
	for(;;)
    {
		vfnTask_Scheduler();
	}
}
