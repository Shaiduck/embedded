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
#include    "ecg_data.h"

/*~~~~~~  Local definitions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#define TEST_LENGTH_SAMPLES 2048

/*~~~~~~  Global variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/** Auxiliary input buffer to accomodate data as FFT function expects it */
float       fft_inputData[TEST_LENGTH_SAMPLES];
/** Output magnitude data */
float       fft_signalPower[TEST_LENGTH_SAMPLES/2];
/** Auxiliary output variable that holds the frequency bin with the highest level of signal power */
uint32_t    u32fft_maxPowerIndex;
/** Auxiliary output variable that holds the maximum level of signal power */
float       fft_maxPower;
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

	/*Prepare data for FFT operation */
	for (u16index = 0; u16index < (TEST_LENGTH_SAMPLES/2); u16index++)
	{
	    fft_inputData[(2*u16index)] = ecg_resampled[u16index];
	    fft_inputData[(2*u16index) + 1] = 0;
	}
	/** Perform FFT on the input signal */
	fft(fft_inputData, fft_signalPower, TEST_LENGTH_SAMPLES/2, &u32fft_maxPowerIndex, &fft_maxPower);
        
	/* Publish through emulated Serial the byte that was previously sent through the regular Serial channel */
	printf("%5d  %5.4f \r\n", u32fft_maxPowerIndex, fft_maxPower);
		
	/** Perform periodically activated tasks */
	vfnTask_Scheduler();
  
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
