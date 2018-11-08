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
#define SAMPLES         27778

/*****************************************************************************************************
* Definition of  VARIABLEs - 
*****************************************************************************************************/
/** */
const uint16_t *ptrDacData;
uint16_t u8DataSamples = 0;

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
	
	/* Configure trigger mode of the Digital to Analog Converter Controller:
	Mode = 0 --> Disabling Trigger mode --> Free-running or Max speed mode on the status of DACC_MR.MAXSx
	Mode = 1 --> Trigger mode enabled 
	 */
	DACC_CfgTrigger(DACC, DACC_TRIGR_TRGEN0_DIS | DACC_TRIGR_TRGEN1_DIS);
    /* Clear DACC_MR.MAXSx to enable Free running mode for both channels DAC0 and DAC1 */
    DACC_CfgModeReg(DACC, DACC_MR_MAXS0_TRIG_EVENT | DACC_MR_MAXS1_TRIG_EVENT) ; 
    
    /*Initialize data */
    ptrDacData = &ecg_resampled_integer[0];
}

/**
 *  \brief Configure DAC DMA and start DMA transfer.
* \param    void
* \return   void
* \todo
*/
void dac_dataTransfer(void)
{
   if ((DACC->DACC_ISR & DACC_ISR_TXRDY0) == DACC_ISR_TXRDY0)
    {
        DACC->DACC_CDR[0] = *ptrDacData << 1;
    }
    if ((DACC->DACC_ISR & DACC_ISR_TXRDY1) == DACC_ISR_TXRDY1)
    {
        DACC->DACC_CDR[1] = *ptrDacData << 1;
    }
    /* Point to next element in data array */
    ptrDacData++;    
    u8DataSamples++;
    if ( u8DataSamples >= SAMPLES)
    {
        /*Initialize data */
        ptrDacData = (uint16_t *)&ecg_resampled_integer[0];
        u8DataSamples = 0;
    }
    
}
