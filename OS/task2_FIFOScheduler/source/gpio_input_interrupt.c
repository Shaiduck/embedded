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

#include "generic_list.h"
#include<stdio.h>
#include<stdlib.h>

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

typedef struct Node
{
    function_pointer_int callback;
	struct Node *next;
}node;
 
node *front=NULL,*rear=NULL,*temp;
 
void create(function_pointer_int cb);
void del();
void display();
 
void create(function_pointer_int cb)
{
	node *newnode;
	newnode=(node*)malloc(sizeof(node));
    newnode->callback = cb;
	newnode->next=NULL;
	if(rear==NULL)
	front=rear=newnode;
	else
	{
		rear->next=newnode;
		rear=newnode;
	}
	
	rear->next=front;
}
 
void del()
{
	temp=front;
	if(front==NULL)
		PRINTF("\nUnderflow :");
	else
	{
		if(front==rear)
		{
			front=rear=NULL;
		}
		else
		{
			front=front->next;
			rear->next=front;
		}
 
	temp->next=NULL;
	free(temp);
	}
}
 
void display()
{
	temp=front;
	if(front==NULL)
		PRINTF("\r\n Empty \r\n ");
	else
	{
		PRINTF("\n");

		temp->callback(0);

		for(int i = 1;temp!=rear;temp=temp->next, i++)
        {
            temp->callback(i);
        }
        PRINTF("\r\n finished display \r\n");
			//printf("\n%d address=%u next=%u\t",temp->info,temp,temp->next);
			//printf("\n%d address=%u next=%u\t",temp->info,temp,temp->next);
	}
}
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

volatile int pendingAdds = 0;
volatile int pendingDeletions = 0;

list_t linkedList;


void sm_StateA(int param);
void sm_StateB(int param);
void sm_StateC(int param);
void sm_StateD(int param);
void sm_StateE(int param);
void sm_StateF(int param);

void sm_StateSuspended(int param);
void sm_StateAdd(int param);
void sm_StateDelete(int param);

void testCallback(int taskNumber);

typedef enum
{
    STATE_SUSPENDED,
    STATE_ADD,
    STATE_DELETE,
    NUM_STATES
}StateType;

typedef struct
{
    StateType state;
    void (*func) (int);
}StateMachineType;

StateMachineType StateMachine[] = 
{
    {STATE_SUSPENDED, sm_StateSuspended},
    {STATE_ADD, sm_StateAdd},
    {STATE_DELETE, sm_StateDelete},
};

StateType sm_State = STATE_SUSPENDED;

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Interrupt service fuction of switch.
 *
 * This function toggles the LED
 */
void testCallback(int taskNumber)
{
	int task = taskNumber +1;
    PRINTF("\r\nThis is the task number %i and it will last %i seconds\r\n", task, task);
    SysTick_DelayTicks(task * 1000U);
}

void sm_StateSuspended(int param)
{
    if (param == 2)
    {
        sm_State = STATE_ADD;
        PRINTF("\r\n initializing\r\n");
    } else if (param == 3)
    {
        sm_State = STATE_DELETE;
        PRINTF("\r\n initializing\r\n");
    }

}

void sm_StateAdd(int param)
{

    if (pendingAdds > 0)
    {
        for (int i = 0; i < pendingAdds; i++)
        {
            PRINTF("\r\n adding task\r\n");
            create(testCallback);
            // list_t newLinkedList;
            // LIST_Init(&newLinkedList, 0, testCallback);
            // LIST_AddTail(&linkedList, LIST_GetHead(&newLinkedList));
        }
        pendingAdds = 0;
    }
    if (param == 2)
    {
        PRINTF("\r\n already in state add\r\n");
    } else if (param == 3)
    {
        sm_State = STATE_DELETE;
    }
}

void sm_StateDelete(int param)
{
    if (pendingDeletions > 0)
    {
        for (int i = 0; i < pendingDeletions; i++)
        {
            // LIST_RemoveHead(&linkedList);
            PRINTF("\r\n deleting task\r\n");
            del();
        }
        pendingDeletions = 0;
    }
    if (param == 2)
    {
        sm_State = STATE_ADD;
    } else if (param == 3)
    {
        PRINTF("\r\n already in state delete\r\n");
    }
}

void BOARD_SW_IRQ_HANDLER(void)
{
    /* Clear external interrupt flag. */
    GPIO_PortClearInterruptFlags(BOARD_SW_GPIO, 1U << BOARD_SW_GPIO_PIN);
    /* Change state of button. */
    g_ButtonPress = true;


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

    while (1)
    {
        if (g_ButtonPress)
        {
            PRINTF(" %s is pressed \r\n", BOARD_SW_NAME);
            /* Toggle LED. */
            GPIO_PortToggle(BOARD_LED_GPIO, 1U << BOARD_LED_GPIO_PIN);
            
            pendingAdds++;

            /* call state machine */
            (*StateMachine[sm_State].func)(2);

            /* Reset state of button. */
            g_ButtonPress = false;
        }
        else if (g_ButtonPress_2)
        {
            PRINTF(" %s is pressed \r\n", BOARD_SW_NAME_2);
            /* Toggle LED. */
            GPIO_PortToggle(BOARD_LED_GPIO_2, 1U << BOARD_LED_GPIO_PIN_2);
            
            pendingDeletions++;

            /* call state machine */
            (*StateMachine[sm_State].func)(3);

            /* Reset state of button. */
            g_ButtonPress_2 = false;
        }
        else
        {
            (*StateMachine[sm_State].func)(0);
        }
        
        display();
    }
}
