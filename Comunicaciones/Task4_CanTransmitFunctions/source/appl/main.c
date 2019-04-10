/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "app_scheduler.h"
#include "Tasks.h"
#include "MemAlloc.h" 
#include <stdbool.h>
#include <stdio.h>
#include "mcan.h"
#include "canif.h"
#include "canif_config.h"

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

FuncPtr array_func[]={
	vfnTsk_1ms,
	vfnTsk_2msA,
	vfnTsk_2msB,
	vfnTsk_10ms,
	vfnTsk_50ms,
	vfnTsk_100ms
};

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/**
 *  \brief Configure LEDs
 *
 *  Configures LEDs \#1 and \#2 (cleared by default).
 */
static void _ConfigureLeds( void )
{
	LED_Configure( 0 ) ;
	LED_Configure( 1 ) ;
}

CanIf_MessageConfigType CanTxMsg[] =
{
	{ 0, CAN_TX, { 0x2C1, CAN_STD_ID, CAN_DLC_3, (uint8_t *)0} },
	{ 1, CAN_TX, { 0x2C1, CAN_STD_ID, CAN_DLC_3, (uint8_t *)0} },
	{ 2, CAN_TX, { 0x2C1, CAN_STD_ID, CAN_DLC_3, (uint8_t *)0} },
	{ 3, CAN_TX, { 0x2C1, CAN_STD_ID, CAN_DLC_3, (uint8_t *)0} }
};

CanIf_MsgObjType CanMsgObj =
{
	sizeof(CanTxMsg)/sizeof(CanIf_MessageConfigType),
	CanTxMsg
};

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
	WDT_Disable( WDT ) ;

	/* Output example information */
	printf( "\n\r-- Getting Started Example Workspace Updated!!! %s --\n\r", SOFTPACK_VERSION ) ;
	printf( "-- %s\n\r", BOARD_NAME ) ;
	printf( "-- Compiled: %s %s With %s--\n\r", __DATE__, __TIME__ , COMPILER_NAME);

	/* Enable I and D cache */
	SCB_EnableICache();
  SCB_EnableDCache();

	printf( "Configure LED PIOs.\n\r" ) ;
	_ConfigureLeds() ;
  
  MemAllocInit();
  printf( "\n\r-- Memory Allocation Initialized!!! --\n\r" ) ;
  
    CanIf_Init(1, CanMsgObj);
//   MCAN_Init(&mcan1Config);
  printf( "\n\r-- MCAN driver Initialized!!! --\n\r" ) ;
  
  /*MCAN_InitTxQueue(loc_mcan_Config);
  printf( "\n\r-- MCAN Tx Queue Initialized!!! --\n\r" ) ;*/
  
  MCAN_Enable(&mcan1Config);
  printf( "\n\r-- MCAN Enabled!!! --\n\r" ) ;

  	/* Initialize Task Scheduler */
	vfnScheduler_Init(&array_func[0]);
	/* Start execution of task scheduler */
	vfnScheduler_Start();

	/*-- Loop through all the periodic tasks from Task Scheduler --*/
	for(;;)
	{
		/* Perform all scheduled tasks */
		vfnTask_Scheduler();
	}

}
