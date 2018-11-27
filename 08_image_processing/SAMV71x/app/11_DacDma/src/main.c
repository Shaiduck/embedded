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
/** Input Image */
#include    "lena_image.h"
/** Image Processing services */
/*#include    "image_processing.h"    */

/*~~~~~~  Local definitions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~  Global variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/* Auxiliary variables */
uint16_t i_index;
uint16_t j_index;

/* Averaging mask */
float AvgMask2x2[2][2] =
{
    0.25, 0.25,   
    0.25, 0.25
};

/* Intermediate scaled up image - temporary pixel calculation */     
uint32_t Filtered2x2scaled __attribute__((section("four_byte_aligment")));
/* Intermediate Mask in integer numbers to accelerate execution */
uint32_t AvgMask2x2scaled[2][2] __attribute__((section("four_byte_aligment")));
/*Output filtered image */     
uint8_t Lena_Image_Filtered[IMAGE_ROWS][IMAGE_COLS] __attribute__((section("four_byte_aligment")));


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
    /* Enable Floating Point Unit */
    vfnFpu_enable();
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
    
    /** Indication for measurement */
    LED_Set(1);
    
    /* Convert to integer and scale up correlation mask in order to avoid loosing resolution */
    for (i_index = 0; i_index < 2; i_index++)
    {
        for (j_index = 0; j_index < 2; j_index++)
        {     /* Mask to be scaled up by a factor of 2^16*/
              AvgMask2x2scaled[i_index][j_index] = (uint32_t)(AvgMask2x2[i_index][j_index] * 0x00010000);
        }
    }
    /* Perform correlation operation */
    for (i_index = 0; i_index < IMAGE_ROWS-1; i_index++)
    {
        for (j_index = 0; j_index < IMAGE_COLS; j_index++)
        {     /* For items on the first column */
            if(j_index == 0)
            {
                Filtered2x2scaled = 
                    (uint32_t)(Lena_Image[i_index][j_index] * AvgMask2x2scaled[0][0]) +
                    (uint32_t)(Lena_Image[i_index+1][j_index] * AvgMask2x2scaled[1][1]);       
            }
            else
            {
                Filtered2x2scaled = 
                    (uint32_t)(Lena_Image[i_index][j_index] * AvgMask2x2scaled[0][0]) +
                    (uint32_t)(Lena_Image[i_index+1][j_index] * AvgMask2x2scaled[1][0]) +
                    (uint32_t)(Lena_Image[i_index+1][j_index-1] * AvgMask2x2scaled[1][1]) + 
                    (uint32_t)(Lena_Image[i_index][j_index-1] * AvgMask2x2scaled[0][1]);
            }
            /* Scale down result */
            Lena_Image_Filtered[i_index][j_index] = (uint8_t)( Filtered2x2scaled >> 16);
        }
    }
    /** End of indication for measurement */
    LED_Clear(1);
    
	/* Once all the basic services have been started, go to infinite loop to serviced activated tasks */
    for(;;)
    {			    
        /** Perform periodically activated tasks */
		vfnTask_Scheduler();
	}
}
