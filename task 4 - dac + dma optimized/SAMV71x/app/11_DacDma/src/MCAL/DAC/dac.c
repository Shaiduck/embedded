/****************************************************************************************************/
/**
\file       dac.c
\brief      MCAL abstraction level - Digital to Analog Converter Controller configuration and interrupt handling.
\author     Abraham Tezmol
\version    1.0
\project    Tau 
\date       26/September/2016
*/
/****************************************************************************************************/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/
/** dac function prototypes and definitions */
#include "dac.h"
#include "dac_dma.h"
#include "xdmad.h"
/** Power Management Controller */
#include "pmc.h"
/** MCU-derivative specific definitions */
#include "samv71.h"
/** ECG sample data */
#include "ecg_data.h"

/*****************************************************************************************************
* Definition of module wide MACROs / #DEFINE-CONSTANTs 
*****************************************************************************************************/
/** SAMPLES per cycle*/
#define SAMPLES         1024
#define TEST_CHANNEL    5

/*****************************************************************************************************
* Definition of  VARIABLEs - 
*****************************************************************************************************/
/** */
uint32_t dacBuffer[SAMPLES];

/** Global DMA driver for all transfer */
sXdmad dmad;
/** Global DAC DMA instance */
 DacDma Dacd;
/** DAC command instance */
DacCmd DacCommand;
/*****************************************************************************************************
* Definition of module wide (CONST-) CONSTANTs 
*****************************************************************************************************/

/*****************************************************************************************************
* Code of module wide FUNCTIONS
*****************************************************************************************************/

/****************************************************************************************************/
/**
* \brief    SysTick - Initialization
* \author   Abraham Tezmol
* \param    int32_t base_freq	--> Requested SysTick interrupt frequency
* \param    tPtr_to_function sysTick_handler	--> Callback function to handle SysTick ISR.
* \return   int8_t --> 0 - Successful configuration of SysTick IRQ and SysTick Timer, 1 - Invalid configuration
* \todo
*/
void dac_initialization(void)
{
	uint32_t i;
	/* Enable Digital to Analog Converter Controller */
	PMC_EnablePeripheral(ID_DACC);
	/* Command a Soft-reset onto Digital to Analog Converter Controller */
	DACC_SoftReset(DACC);
	/* Enable Invidivual channels */
	DACC_EnableChannel(DACC, 0);
	DACC_EnableChannel(DACC, 1);
	/* Copy samples onto DAC Buffer -- to review usefullness later */
	for (i = 0; i < SAMPLES; i++)
	{
		dacBuffer[i] = ecg_resampled_integer[i] << 1;
	}
	
	/* Configure trigger mode of the Digital to Analog Converter Controller:
	Mode = 0 --> Disabling Trigger mode --> Free-running or Max speed mode on the status of DACC_MR.MAXSx
	Mode = 1 --> Trigger mode enabled 
	 */
	DACC_CfgTrigger(DACC, 0);
}

/**
 *  \brief Configure DAC DMA and start DMA transfer.
* \param    void
* \return   void
* \todo
*/
void dac_dmaTransfer(void)
{
	DacCommand.dacChannel = DACC_CHANNEL_0;
	DacCommand.TxSize = SAMPLES;
	DacCommand.pTxBuff = (uint8_t *)dacBuffer;
	DacCommand.loopback = 1;
	DacCommand.callback = dac_callback;
	Dac_ConfigureDma(&Dacd, DACC, ID_DACC, &dmad);
	Dac_SendData(&Dacd, &DacCommand);
}

void dac_callback(uint8_t arg1, void* arg2)
{
	//do something
}
