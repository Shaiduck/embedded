/*
 * Copyright 2017-2018 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v4.0
* BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********/

/**
 * @file    pin_mux.c
 * @brief   Board pins file.
 */
 
/* This is a template for board specific configuration created by MCUXpresso IDE Project Wizard.*/

#include "pin_mux.h"
#include "fsl_common.h"
#include "fsl_port.h"

#define PIN3_IDX                       3u   /*!< Pin number for pin 3 in a port */
#define PIN4_IDX                       4u   /*!< Pin number for pin 4 in a port */
#define PIN5_IDX                       5u   /*!< Pin number for pin 5 in a port */
#define PIN6_IDX                       6u   /*!< Pin number for pin 6 in a port */
#define PIN10_IDX                     10u   /*!< Pin number for pin 10 in a port */
#define PIN11_IDX                     11u   /*!< Pin number for pin 11 in a port */
#define PIN12_IDX                     12u   /*!< Pin number for pin 12 in a port */
#define PIN13_IDX                     13u   /*!< Pin number for pin 13 in a port */
#define PIN14_IDX                     14u   /*!< Pin number for pin 14 in a port */
#define PIN15_IDX                     15u   /*!< Pin number for pin 15 in a port */
#define PIN16_IDX                     16u   /*!< Pin number for pin 16 in a port */
#define PIN17_IDX                     17u   /*!< Pin number for pin 17 in a port */
#define PIN18_IDX                     18u   /*!< Pin number for pin 18 in a port */

/**
 * @brief Set up and initialize all required blocks and functions related to the board hardware.
 */
void BOARD_InitBootPins(void) {
	/* The user initialization should be placed here */
	  CLOCK_EnableClock(kCLOCK_PortB);                           /* Port B Clock Gate Control: Clock enabled */
	  CLOCK_EnableClock(kCLOCK_PortC);                           /* Port C Clock Gate Control: Clock enabled */
	  CLOCK_EnableClock(kCLOCK_PortD);                           /* Port D Clock Gate Control: Clock enabled */
	  CLOCK_EnableClock(kCLOCK_PortE);                           /* Port E Clock Gate Control: Clock enabled */

	  //USER_ENTER switch
	  const port_pin_config_t portb18_config = {
	    kPORT_PullUp,                                            /* Internal pull-up resistor is enabled */
	    kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
	    kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
	    kPORT_OpenDrainDisable,                                  /* Open drain is disabled */
	    kPORT_LowDriveStrength,                                  /* Low drive strength is configured */
	    kPORT_MuxAsGpio,                                         /* Pin is configured as PTB18 */
	    kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
	  };
	  PORT_SetPinConfig(PORTB, PIN18_IDX, &portb18_config);      /* PORTB18 is configured as PTB18 */ //USER_ENTER

	  //USER_UP switch
	  const port_pin_config_t portb11_config = {
	    kPORT_PullUp,                                            /* Internal pull-up resistor is enabled */
	    kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
	    kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
	    kPORT_OpenDrainDisable,                                  /* Open drain is disabled */
	    kPORT_LowDriveStrength,                                  /* Low drive strength is configured */
	    kPORT_MuxAsGpio,                                         /* Pin is configured as PTB11 */
	    kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
	  };
	  PORT_SetPinConfig(PORTB, PIN11_IDX, &portb11_config);      /* PORTB11 is configured as PTB11 */ //USER_UP //Backward

	  //USER_RIGHT switch
	  const port_pin_config_t portb10_config = {
	    kPORT_PullUp,                                            /* Internal pull-up resistor is enabled */
	    kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
	    kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
	    kPORT_OpenDrainDisable,                                  /* Open drain is disabled */
	    kPORT_LowDriveStrength,                                  /* Low drive strength is configured */
	    kPORT_MuxAsGpio,                                         /* Pin is configured as PTB10 */
	    kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
	  };
	  PORT_SetPinConfig(PORTB, PIN10_IDX, &portb10_config);      /* PORTB10 is configured as PTB10 */ //USER_RIGHT //Left

	  //USER_LEFT switch
	  const port_pin_config_t portd3_config = {
	    kPORT_PullUp,                                            /* Internal pull-up resistor is enabled */
	    kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
	    kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
	    kPORT_OpenDrainDisable,                                  /* Open drain is disabled */
	    kPORT_LowDriveStrength,                                  /* Low drive strength is configured */
	    kPORT_MuxAsGpio,                                         /* Pin is configured as PTD3 */
	    kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
	  };
	  PORT_SetPinConfig(PORTD, PIN3_IDX, &portd3_config);      /* PORTD3 is configured as PTD3 */ //USER_LEFT //Right

	  //USER_DOWN switch
	  const port_pin_config_t portd6_config = {
	    kPORT_PullUp,                                            /* Internal pull-up resistor is enabled */
	    kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
	    kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
	    kPORT_OpenDrainDisable,                                  /* Open drain is disabled */
	    kPORT_LowDriveStrength,                                  /* Low drive strength is configured */
	    kPORT_MuxAsGpio,                                         /* Pin is configured as PTD6 */
	    kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
	  };
	  PORT_SetPinConfig(PORTD, PIN6_IDX, &portd6_config);      /* PORTD6 is configured as PTD6 */ //USER_DOWN //Forward

	  PORT_SetPinMux(PORTC, PIN11_IDX, 1);                       /* PORTC11 is configured as PTC11 */
	  PORT_SetPinMux(PORTC, PIN12_IDX, 1);                       /* PORTC12 is configured as PTC12 */
	  PORT_SetPinMux(PORTC, PIN13_IDX, 1);                       /* PORTC13 is configured as PTC13 */
	  PORT_SetPinMux(PORTC, PIN14_IDX, 1);                       /* PORTC14 is configured as PTC14 */
	  PORT_SetPinMux(PORTC, PIN15_IDX, 1);                       /* PORTC15 is configured as PTC15 */
	  PORT_SetPinMux(PORTC, PIN16_IDX, 1);                       /* PORTC16 is configured as PTC16 */
	  PORT_SetPinMux(PORTC, PIN17_IDX, 1);                       /* PORTC17 is configured as PTC17 */

	  PORT_SetPinMux(PORTD, PIN4_IDX, 1);                        /* PORTD4  is configured as PTD4 */
	  PORT_SetPinMux(PORTD, PIN5_IDX, 1);                        /* PORTD5  is configured as PTD5 */

	  PORT_SetPinMux(PORTE, PIN3_IDX, 1);                        /* PORTE3  is configured as PTE3 */
	  PORT_SetPinMux(PORTE, PIN4_IDX, 1);                        /* PORTE4  is configured as PTE4 */
	  PORT_SetPinMux(PORTE, PIN5_IDX, 1);                        /* PORTE5  is configured as PTE5 */	
}
