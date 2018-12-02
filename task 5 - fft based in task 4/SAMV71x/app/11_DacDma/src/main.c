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
/** Floating Point Unit */
#include "Fpu.h"
#include "dac.h"
#include "ecg_data.h"

/*~~~~~~  Local definitions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#define TEST_LENGTH_SAMPLES 2048

/*~~~~~~  Global variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/** Auxiliary input buffer to accomodate data as FFT function expects it */
float fft_inputData[TEST_LENGTH_SAMPLES];
/** Output magnitude data */
float fft_signalPower[TEST_LENGTH_SAMPLES / 2];
/** Auxiliary output variable that holds the frequency bin with the highest level of signal power */
uint32_t u32fft_maxPowerIndex;
/** Auxiliary output variable that holds the maximum level of signal power */
float fft_maxPower;
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
	uint16_t u16index;
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
	Fpu_Enable();

	/*Prepare data for FFT operation */
	for (u16index = 0; u16index < (TEST_LENGTH_SAMPLES / 2); u16index++)
	{
		printf("fft_inputData[2 * %i] = ecg_resampled[%i] = %i  \n", u16index, u16index, ecg_resampled[u16index]);
		fft_inputData[(2 * u16index)] = ecg_resampled[u16index];
		printf("fft_inputData[2 * %i + 1] = 0\n", u16index);
		fft_inputData[(2 * u16index) + 1] = 0;
	}
	/** Perform FFT on the input signal */
	fft(fft_inputData, fft_signalPower, TEST_LENGTH_SAMPLES / 2, &u32fft_maxPowerIndex, &fft_maxPower);

	/* Publish through emulated Serial the byte that was previously sent through the regular Serial channel */
	printf("%5d  %5.4f \r\n", u32fft_maxPowerIndex, fft_maxPower);
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
