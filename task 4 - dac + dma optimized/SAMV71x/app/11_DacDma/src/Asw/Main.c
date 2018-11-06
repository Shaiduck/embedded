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
	Wdg_Disable();
	printf( "\n\r-- Scheduler Project %s --\n\r", SOFTPACK_VERSION ) ;
	printf( "-- %s\n\r", BOARD_NAME ) ;
	printf( "-- Compiled: %s %s With %s --\n\r", __DATE__, __TIME__ , COMPILER_NAME);
	/* Configure LEDs */
	printf( "-- Led Control --\n\r" ) ;
	LedCtrl_Configure();
  /* Configure Button */
  printf( "-- Button Control --\n\r" ) ;  
  ButtonCtrl_ConfigureSW0Button();
  /* Enable Floating Point Unit */
  printf( "-- Floating Point Unit --\n\r" ) ;
  Fpu_Enable();
  /************************************************************************************/
  /* Float operations */
  spf_result = spf_int1 - spf_int2;
  spf_result1 = spf_int1 + spf_int2;
  spf_result2 = spf_result  * spf_result1;
  spf_result = spf_int1 * spf_int2;
  spf_result = spf_int1 / spf_int2;
  /* Float to int conversion operations */
  u32_int1 = spf_int1;
	u32_int2 = spf_int2;
		
	s32_int1 = spf_int1;
	s32_int2 = spf_int2;
  /* Int to Float conversion operations */
  spf_result = u32_result;
  spf_result = s32_result;
	/* Integer operations */
	u32_result = u32_int1 - u32_int2;
	u32_result = u32_int1 + u32_int2;
	u32_result = u32_int1 * u32_int2;
	u32_result = u32_int1 / u32_int2;
	s32_result = s32_int1 - s32_int2;
	s32_result = s32_int1 + s32_int2;
	s32_result = s32_int1 * s32_int2;
	s32_result = s32_int1 / s32_int2;  
  /************************************************************************************/
  
      /* Initialize DAC */
    dac_initialization();
    dac_dmaTransfer();
	
  /* Scheduler Inititalization */
	printf( "-- Scheduler Initialization --\n\r" ) ;
	SchM_Init(ScheduleConfig);
	
	/* Should never reach this code */
	for(;;)
    {
		printf( "-- Unexpected Error at Scheduler Initialization --\n\r" ) ;
	}
}
