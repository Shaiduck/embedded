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
#include "board.h"
#include "tc.h"
#include <stdbool.h>
#include <stdio.h>
/** Task scheduler definitions */
#include "app_scheduler.h"
/** LED control definitions */
#include "led_ctrl.h"
/** UART communication */
#include "serial_ctrl.h"
/** Watchdog control function prototypes definitions */
#include "wdt_ctrl.h"
/** Dynamic Memory allocation services */
#include "memory_allocation.h"
/** Floating Point Unit */
#include "Fpu.h"
#include "dac.h"
#include "ecg_data.h"

#include "afec.h"
#include "afe_dma.h"


/*~~~~~~  Local definitions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#define TEST_LENGTH_SAMPLES 2048
#define SAMPLES 1024	//SIZE
#define AFE_CLK 2200000 // SAMP_PER
#define TEST_CHANNEL 5

uint16_t __attribute__((section(".my_heap"))) ADC_BUFF[SAMPLES];

/*~~~~~~  Global variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/** Auxiliary input buffer to accomodate data as FFT function expects it */
float fft_inputData[TEST_LENGTH_SAMPLES];
/** Output magnitude data */
float fft_signalPower[TEST_LENGTH_SAMPLES / 2];
/** Auxiliary output variable that holds the frequency bin with the highest level of signal power */
uint32_t u32fft_maxPowerIndex;
/** Auxiliary output variable that holds the maximum level of signal power */
float fft_maxPower;


/** Global AFE DMA instance */
static AfeDma Afed;
/** AFE command instance */
static AfeCmd AfeCommand;

/** Global DMA driver for all transfer */
static sXdmad dmad;

static uint8_t isDACEnabled = 0;
static uint8_t isADCEnabled = 0;

static uint32_t afeChannel = 0;

typedef struct
{
	uint32_t Sample_Period; //SAMP_PER
	uint32_t Sample_Size;   //SIZE
	uint32_t *BUFF_ADDR;	//&ADC_BUFF[0]
} ConfigStruct;

ConfigStruct configuration;

/*~~~~~~  Local functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**
 *  \brief Callback function for AFE interrupt
 *
 */
static void _afe_Callback(int dummy, void *pArg)
{
	uint32_t i;
	uint32_t ch;
	uint32_t voltage;
	dummy = dummy;
	pArg = pArg;
	printf("\n\rCH  AFE   Voltage(mV) \n\r");
	for (i = 0; i < SAMPLES; i++)
	{
		ch = (configuration.BUFF_ADDR[i] & AFEC_LCDR_CHNB_Msk) >> AFEC_LCDR_CHNB_Pos;
		voltage = ((configuration.BUFF_ADDR[i] & 0xFFFF) - 0x200) * 1650 / 2047;
		printf("%02u  %04x  %04u\n\r", (unsigned int)ch,
			   (unsigned int)(configuration.BUFF_ADDR[i] & 0xFFFF), (unsigned int)voltage);
	}
}

void initializeAfe()
{
	AFEC_Initialize(AFEC0, ID_AFEC0);
	AFEC_SetModeReg(AFEC0,
					AFEC_MR_FREERUN_ON
					//AFEC_MR_FREERUN_OFF
						// | AFEC_EMR_RES_NO_AVERAGE
						| AFEC_MR_TRANSFER(1)
						// | (1 << AFEC_MR_TRANSFER_Pos)
						// | (2 << AFEC_MR_TRACKTIM_Pos)
						| AFEC_MR_TRACKTIM(2) | AFEC_MR_ONE
						// | AFEC_MR_SETTLING_AST3
						| AFEC_MR_STARTUP_SUT64);
	AFEC_SetClock(AFEC0, AFE_CLK, BOARD_MCK);
	AFEC_EnableChannel(AFEC0, TEST_CHANNEL);
	AFEC_SetAnalogOffset(AFEC0, TEST_CHANNEL, 0x200);
	AFEC_SetAnalogControl(AFEC0, AFEC_ACR_IBCTL(1) | AFEC_ACR_PGA0_ON |
									 AFEC_ACR_PGA1_ON);

	AFEC_SetExtModeReg(AFEC0,
					   0
						   // | AFEC_EMR_RES_NO_AVERAGE
						   | AFEC_EMR_RES(256) | AFEC_EMR_TAG | AFEC_EMR_STM);

	// AFEC_SetTrigger(AFEC0, AFEC_MR_TRGSEL_AFEC_TRIG6);
}

void transferAfe()
{
	AfeCommand.RxSize = configuration.Sample_Size;
	AfeCommand.pRxBuff = configuration.BUFF_ADDR;
	AfeCommand.callback = (AfeCallback)_afe_Callback;
	Afe_ConfigureDma(&Afed, AFEC0, ID_AFEC0, &dmad);
	isADCEnabled = 1;
	afeChannel = Afe_SendData(&Afed, &AfeCommand);

}

void SET_AFEC_SAMPLING(uint16_t SAMP_PER, uint16_t *BUFF_ADDR, uint16_t SIZE)
{
	configuration.Sample_Period = (uint32_t)SAMP_PER;
	configuration.Sample_Size = SIZE;
	configuration.BUFF_ADDR = (uint32_t *)BUFF_ADDR;
}
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
	vfnWdtCtrl_Disable();
	/* Enable I and D cache */
	SCB_EnableICache();
	SCB_EnableDCache();
	/* Dynamic Memory Allocation initialization */
	// vfnMemAlloc_Init(&DynamicMemAlloc_config[0]);
	/* Configure LEDs */
	vfnLedCtrl_Configure();
	/* Initialize UART communicaiton */
	vfnSerialCtrl_Init();
	/* Configure Non-preemtive scheduler */
	vfnScheduler_Init();
	/* Start scheduler */
	vfnScheduler_Start(NULL);

	SET_AFEC_SAMPLING((uint16_t)AFE_CLK, ADC_BUFF, SAMPLES);
	initializeAfe();
	transferAfe();
	/* Once all the basic services have been started, go to infinite loop to serviced activated tasks */
	for (;;)
	{
		vfnTask_Scheduler();
	}
}

void XDMAC_Handler(void)
{
		isADCEnabled = 0;
		PMC_DisablePeripheral(ID_AFEC0);
			/*  Reset the controller */
		AFEC0->AFEC_CR = AFEC_CR_SWRST;

		/* Reset Mode Register */
		AFEC0->AFEC_MR = 0;
		AFEC_DisableChannel(AFEC0, TEST_CHANNEL);
		NVIC_ClearPendingIRQ(XDMAC_IRQn);
		NVIC_SetPriority(XDMAC_IRQn, 1);
		NVIC_DisableIRQ(XDMAC_IRQn);

		XDMAD_StopTransfer(&dmad, afeChannel);
		XDMAD_FreeChannel(&dmad, afeChannel);

		printf("We're finished collecting samples\n");
		/*Prepare data for FFT operation */
		Fpu_Enable();
		uint16_t u16index = 0;
		/*Prepare data for FFT operation */
		for (u16index = 0; u16index < (TEST_LENGTH_SAMPLES / 2); u16index++)
		{
			fft_inputData[(2 * u16index)] = ADC_BUFF[u16index];
			fft_inputData[(2 * u16index) + 1] = 0;
		}
		/** Perform FFT on the input signal */
		fft(fft_inputData, fft_signalPower, TEST_LENGTH_SAMPLES / 2, &u32fft_maxPowerIndex, &fft_maxPower);

		/* Publish through emulated Serial the byte that was previously sent through the regular Serial channel */
		printf("%5d  %5.4f \r\n", u32fft_maxPowerIndex, fft_maxPower);

}