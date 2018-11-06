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
#include    "Std_Types.h"
/** Task scheduler definitions */
#include    "SchM.h"
/** LED control definitions */ 
#include    "Led_Ctrl.h"
/** Watchdog control function prototypes definitions */
#include    "Wdg.h"
/** Button control operations */
#include    "Button_Ctrl.h"
/** Floating Point Unit */
#include    "Fpu.h"


/*~~~~~~  Local definitions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~  Global variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
float       spf_result;
float       spf_result1;
float       spf_result2;
float       spf_int1 = 256;
float       spf_int2 = 10;
uint32_t    u32_result;
uint32_t    u32_int1;
uint32_t    u32_int2;
int32_t     s32_result;
int32_t     s32_int1;
int32_t     s32_int2;

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
	vfnScheduler_Start();
    
    /* Initialize DAC */
    dac_initialization();
    dac_dmaTransfer();
	
	/* Once all the basic services have been started, go to infinite loop to serviced activated tasks */
	for(;;)
    {
		vfnTask_Scheduler();
	}
}

