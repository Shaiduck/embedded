/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_debug_console.h"
#include "fsl_port.h"
#include "fsl_gpio.h"
#include "fsl_common.h"
#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
#include<stdlib.h>
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define BOARD_LED_GPIO BOARD_LED_RED_GPIO
#define BOARD_LED_GPIO_PIN BOARD_LED_RED_GPIO_PIN

#define BOARD_SW_GPIO BOARD_SW3_GPIO
#define BOARD_SW_PORT BOARD_SW3_PORT
#define BOARD_SW_GPIO_PIN BOARD_SW3_GPIO_PIN
#define BOARD_SW_IRQ BOARD_SW3_IRQ
#define BOARD_SW_IRQ_HANDLER BOARD_SW3_IRQ_HANDLER
#define BOARD_SW_NAME BOARD_SW3_NAME


#define BOARD_LED_GPIO_2 BOARD_LED_BLUE_GPIO
#define BOARD_LED_GPIO_PIN_2 BOARD_LED_BLUE_GPIO_PIN

#define BOARD_SW_GPIO_2 BOARD_SW2_GPIO
#define BOARD_SW_PORT_2 BOARD_SW2_PORT
#define BOARD_SW_GPIO_PIN_2 BOARD_SW2_GPIO_PIN
#define BOARD_SW_IRQ_2 BOARD_SW2_IRQ
#define BOARD_SW_IRQ_HANDLER_2 BOARD_SW2_IRQ_HANDLER
#define BOARD_SW_NAME_2 BOARD_SW2_NAME
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* Whether the SW button is pressed */
volatile bool g_ButtonPress = false;
volatile bool g_ButtonPress_2 = false;

volatile int deletionPending = 0;
volatile int creationPending = 0;
#define MAX_TASKS  6
void sm_StateSuspended(int param);
void sm_StateCreate(int param);
void sm_StateDelete(int param);
void sm_StateE(int param);
void sm_StateF(int param);

typedef enum
{
    STATE_SUSPENDED,
    STATE_CREATE,
    STATE_DELETE,
    NUM_STATES
}StateType;

typedef void (*function_pointer) (int);
typedef struct
{
    StateType state;
    function_pointer state_callback;
}StateMachineType;

typedef struct
{
    int numberOfTasks;
    function_pointer function_array[MAX_TASKS];
}SchedulerType;

SchedulerType scheduler;
StateMachineType StateMachine[] = 
{
    {STATE_SUSPENDED, sm_StateSuspended},
    {STATE_CREATE, sm_StateCreate},
    {STATE_DELETE, sm_StateDelete},
};

StateType sm_State = STATE_SUSPENDED;

volatile uint32_t g_systickCounter;
void SysTick_Handler(void)
{
    if (g_systickCounter != 0U)
    { 
        g_systickCounter--;
    }
}
void SysTick_DelayTicks(uint32_t n)
{
    g_systickCounter = n;
    while(g_systickCounter != 0U)
    {
    }
}


/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Interrupt service fuction of switch.
 *
 * This function toggles the LED
 */
void scheduler_task(int taskNumber)
{
	int task = taskNumber +1;
    PRINTF("\r\nThis is the task number %i and it will last %i seconds\r\n", task, task*5);
    SysTick_DelayTicks(task * 5000U);
}

void scheduler_function()
{
    int taskAtEnter = scheduler.numberOfTasks;
    for (int index = 0; index < taskAtEnter; index++)
    {
        (*scheduler.function_array[index])(index);
        scheduler.function_array[index] = NULL;
        scheduler.numberOfTasks--;
    }
    if (taskAtEnter != scheduler.numberOfTasks)
    {
        PRINTF("\r\nNo more tasks\r\n");
    }
}

void sm_StateSuspended(int param)
{
    if (param == 2)
    {
        sm_State = STATE_CREATE;
    } else if (param == 3)
    {
        sm_State = STATE_CREATE;
    }
}
void sm_StateCreate(int param)
{
    if (param == 2)
    {
        PRINTF("\r\nLet's create a task\r\n");
        for (int index = 0; index < creationPending; index++)
        {
            if (scheduler.numberOfTasks+1 < MAX_TASKS)
            {
                scheduler.function_array[scheduler.numberOfTasks] = scheduler_task;
                scheduler.numberOfTasks++;
            }
            else
            {
                PRINTF("\r\nMax number of tasks reached\r\n");
            }
        }
        creationPending = 0;
    } else if (param == 3)
    {
        sm_State = STATE_DELETE;
    }
}
void sm_StateDelete(int param)
{
    if (param == 2)
    {
        sm_State = STATE_CREATE;
    } else if (param == 3)
    {
        PRINTF("\r\nLet's delete a task\r\n");
        for (int index = 0; index < deletionPending; index++)
        {
            if (scheduler.numberOfTasks-1 >= 0)
            {
                scheduler.function_array[scheduler.numberOfTasks] = NULL;
                scheduler.numberOfTasks--;
            }
            else
            {
                PRINTF("\r\nNo Tasks to Delete\r\n");
            }
        }
        deletionPending = 0;
    }
}

void BOARD_SW_IRQ_HANDLER(void)
{
    /* Clear external interrupt flag. */
    GPIO_PortClearInterruptFlags(BOARD_SW_GPIO, 1U << BOARD_SW_GPIO_PIN);
    /* Change state of button. */
    g_ButtonPress = true;
    creationPending++;



/* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F Store immediate overlapping
  exception return operation might vector to incorrect interrupt */
#if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
#endif
}

void BOARD_SW_IRQ_HANDLER_2(void)
{
    /* Clear external interrupt flag. */
    GPIO_PortClearInterruptFlags(BOARD_SW_GPIO_2, 1U << BOARD_SW_GPIO_PIN_2);
    /* Change state of button. */
    g_ButtonPress_2 = true;
    deletionPending++;
/* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F Store immediate overlapping
  exception return operation might vector to incorrect interrupt */
#if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
#endif
}

/*!
 * @brief Main function
 */
int main(void)
{
    /* Define the init structure for the input switch pin */
    gpio_pin_config_t sw_config = {
        kGPIO_DigitalInput, 0,
    };

    /* Define the init structure for the output LED pin */
    gpio_pin_config_t led_config = {
        kGPIO_DigitalOutput, 0,
    };

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    /* Print a note to terminal. */
    PRINTF("\r\n GPIO Driver example\r\n");
    PRINTF("\r\n Press %s to turn on/off a LED \r\n", BOARD_SW_NAME);

/* Init input switch GPIO. */
#if (defined(FSL_FEATURE_PORT_HAS_NO_INTERRUPT) && FSL_FEATURE_PORT_HAS_NO_INTERRUPT)
    GPIO_SetPinInterruptConfig(BOARD_SW_GPIO_2, BOARD_SW_GPIO_PIN_2, kGPIO_InterruptFallingEdge);
    GPIO_SetPinInterruptConfig(BOARD_SW_GPIO, BOARD_SW_GPIO_PIN, kGPIO_InterruptFallingEdge);
#else
    PORT_SetPinInterruptConfig(BOARD_SW_PORT, BOARD_SW_GPIO_PIN, kPORT_InterruptFallingEdge);
    PORT_SetPinInterruptConfig(BOARD_SW_PORT_2, BOARD_SW_GPIO_PIN_2, kPORT_InterruptFallingEdge);
#endif
    EnableIRQ(BOARD_SW_IRQ);
    EnableIRQ(BOARD_SW_IRQ_2);
    GPIO_PinInit(BOARD_SW_GPIO, BOARD_SW_GPIO_PIN, &sw_config);
    GPIO_PinInit(BOARD_SW_GPIO_2, BOARD_SW_GPIO_PIN_2, &sw_config);

    /* Init output LED GPIO. */
    GPIO_PinInit(BOARD_LED_GPIO, BOARD_LED_GPIO_PIN, &led_config);
    GPIO_PinInit(BOARD_LED_GPIO_2, BOARD_LED_GPIO_PIN_2, &led_config);

    if(SysTick_Config(SystemCoreClock / 1000U))
    {
        while(1)
        {
        }
    }


    scheduler.numberOfTasks = 0;
    while (1)
    {
        if (g_ButtonPress)
        {
            PRINTF("\r\n %s is pressed \r\n", BOARD_SW_NAME);
            /* Toggle LED. */
            GPIO_PortToggle(BOARD_LED_GPIO, 1U << BOARD_LED_GPIO_PIN);

            /* call state machine */
            (*StateMachine[sm_State].state_callback)(2);

            /* Reset state of button. */
            g_ButtonPress = false;
        }
        else if (g_ButtonPress_2)
        {
            PRINTF("\r\n %s is pressed \r\n", BOARD_SW_NAME_2);
            /* Toggle LED. */
            GPIO_PortToggle(BOARD_LED_GPIO_2, 1U << BOARD_LED_GPIO_PIN_2);
            
            /* call state machine */
            (*StateMachine[sm_State].state_callback)(3);

            /* Reset state of button. */
            g_ButtonPress_2 = false;
        }
        scheduler_function();
    }
}
