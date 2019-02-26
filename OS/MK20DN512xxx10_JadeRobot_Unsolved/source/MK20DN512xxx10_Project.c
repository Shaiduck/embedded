/*
 * Copyright (c) 2017, NXP Semiconductor, Inc.
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
 
/**
 * @file    MK20DN512xxx10_Project.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK20D10.h"
#include "fsl_debug_console.h"
#include "fsl_gpio.h"
#include "fsl_port.h"

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define BOARD_SW_GPIO_PORTB  GPIOB
#define BOARD_SW_GPIOB_PORT  PORTB
#define BOARD_SW_GPIOB_PIN10 10u
#define BOARD_SW_GPIOB_PIN11 11u
#define BOARD_SW_GPIOB_PIN18 18u
#define BOARD_SW_IRQ_PORTB   PORTB_IRQn

#define BOARD_LED_GPIO_PORTC  GPIOC
#define BOARD_LED_GPIOC_PIN11 11U
#define BOARD_LED_GPIOC_PIN12 12U
#define BOARD_LED_GPIOC_PIN13 13U
#define BOARD_LED_GPIOC_PIN14 14U
#define BOARD_LED_GPIOC_PIN15 15U
#define BOARD_LED_GPIOC_PIN16 16U
#define BOARD_LED_GPIOC_PIN17 17U

#define BOARD_LED_GPIO_PORTD GPIOD
#define BOARD_LED_GPIOD_PIN4 4U
#define BOARD_LED_GPIOD_PIN5 5U

#define BOARD_SW_GPIO_PORTD  GPIOD
#define BOARD_SW_GPIOD_PORT  PORTD
#define BOARD_SW_GPIOD_PIN3  3u
#define BOARD_SW_GPIOD_PIN6  6u
#define BOARD_SW_IRQ_PORTD   PORTD_IRQn

#define BOARD_LED_GPIO_PORTE GPIOE
#define BOARD_LED_GPIOE_PIN3 3U
#define BOARD_LED_GPIOE_PIN4 4U
#define BOARD_LED_GPIOE_PIN5 5U

/* Task priorities. */
#define clt_task_PRIORITY          (configMAX_PRIORITIES)
#define moveForward_task_PRIORITY  (configMAX_PRIORITIES)
#define moveBackward_task_PRIORITY (configMAX_PRIORITIES)
#define moveLeft_task_PRIORITY     (configMAX_PRIORITIES)
#define moveRight_task_PRIORITY    (configMAX_PRIORITIES)
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void clt_task(void *pvParameters);
static void forward_task(void *pvParameters);
static void backward_task(void *pvParameters);
static void left_task(void *pvParameters);
static void right_task(void *pvParameters);

static void moveLeft(char ticks);
static void moveRight(char ticks);
static void moveForward(char ticks);
static void moveBackward(char ticks);

#define MAX_CMD_LENGTH 2

/*!
 * @brief Interrupt service function of switch.
 *
 */
void PORTB_IRQHandler(void)
{
	uint32_t irqpin = 0;

    if (irqpin & (1<<10)) //Left switch
    {
	    /* Clear external interrupt flag. */
        GPIO_ClearPinsInterruptFlags(BOARD_SW_GPIO_PORTB, 1U << BOARD_SW_GPIOB_PIN10);
    }

    if (irqpin & (1<<11)) //Backward switch
    {
        /* Clear external interrupt flag. */
        GPIO_ClearPinsInterruptFlags(BOARD_SW_GPIO_PORTB, 1U << BOARD_SW_GPIOB_PIN11);
    }

    if (irqpin & (1<<18)) //Enter switch
    {
        /* Clear external interrupt flag. */
        GPIO_ClearPinsInterruptFlags(BOARD_SW_GPIO_PORTB, 1U << BOARD_SW_GPIOB_PIN18);
    }

}

/*!
 * @brief Interrupt service function of switch.
 *
 */
void PORTD_IRQHandler(void)
{
	uint32_t irqpin = 0;

	irqpin = GPIO_GetPinsInterruptFlags(BOARD_SW_GPIO_PORTD);

    if (irqpin & (1<<3)) //Right switch
    {
        /* Clear external interrupt flag. */
        GPIO_ClearPinsInterruptFlags(BOARD_SW_GPIO_PORTD, 1U << BOARD_SW_GPIOD_PIN3);

    }

    if (irqpin & (1<<6)) //Forward switch
    {
        /* Clear external interrupt flag. */
        GPIO_ClearPinsInterruptFlags(BOARD_SW_GPIO_PORTD, 1U << BOARD_SW_GPIOD_PIN6);

    }

}

void myGPIOinit(void)
{
	int result = 0;

    /* Define the init structure for the output LED pin*/
    gpio_pin_config_t led_config = {
        kGPIO_DigitalOutput, 0,
    };

    /* Define the init structure for the input switch pin */
    gpio_pin_config_t sw_config = {
        kGPIO_DigitalInput, 0,
    };

    /* Init output LED GPIO. */
    GPIO_PinInit(BOARD_LED_GPIO_PORTE, BOARD_LED_GPIOE_PIN3, &led_config);
    GPIO_PinInit(BOARD_LED_GPIO_PORTC, BOARD_LED_GPIOC_PIN11, &led_config);
    GPIO_PinInit(BOARD_LED_GPIO_PORTC, BOARD_LED_GPIOC_PIN12, &led_config);
    GPIO_PinInit(BOARD_LED_GPIO_PORTC, BOARD_LED_GPIOC_PIN13, &led_config);
    GPIO_PinInit(BOARD_LED_GPIO_PORTC, BOARD_LED_GPIOC_PIN14, &led_config);
    GPIO_PinInit(BOARD_LED_GPIO_PORTC, BOARD_LED_GPIOC_PIN15, &led_config);
    GPIO_PinInit(BOARD_LED_GPIO_PORTC, BOARD_LED_GPIOC_PIN16, &led_config);
    GPIO_PinInit(BOARD_LED_GPIO_PORTC, BOARD_LED_GPIOC_PIN17, &led_config);

    GPIO_PinInit(BOARD_LED_GPIO_PORTE, BOARD_LED_GPIOE_PIN4, &led_config);
    GPIO_PinInit(BOARD_LED_GPIO_PORTE, BOARD_LED_GPIOE_PIN5, &led_config);
    GPIO_PinInit(BOARD_LED_GPIO_PORTD, BOARD_LED_GPIOD_PIN4, &led_config);
    GPIO_PinInit(BOARD_LED_GPIO_PORTD, BOARD_LED_GPIOD_PIN5, &led_config);

    /* Init input switch ENTER GPIO. */
    PORT_SetPinInterruptConfig(BOARD_SW_GPIOB_PORT, BOARD_SW_GPIOB_PIN18, kPORT_InterruptFallingEdge);
    EnableIRQ(BOARD_SW_IRQ_PORTB);
    GPIO_PinInit(BOARD_SW_GPIO_PORTB, BOARD_SW_GPIOB_PIN18, &sw_config);

    /* Init input switch BACKWARD GPIO. */
    PORT_SetPinInterruptConfig(BOARD_SW_GPIOB_PORT, BOARD_SW_GPIOB_PIN11, kPORT_InterruptFallingEdge);
    EnableIRQ(BOARD_SW_IRQ_PORTB);
    GPIO_PinInit(BOARD_SW_GPIO_PORTB, BOARD_SW_GPIOB_PIN11, &sw_config);

    /* Init input switch LEFT GPIO. */
    PORT_SetPinInterruptConfig(BOARD_SW_GPIOB_PORT, BOARD_SW_GPIOB_PIN10, kPORT_InterruptFallingEdge);
    EnableIRQ(BOARD_SW_IRQ_PORTB);
    GPIO_PinInit(BOARD_SW_GPIO_PORTB, BOARD_SW_GPIOB_PIN10, &sw_config);

   /* Init input switch RIGHT GPIO. */
    PORT_SetPinInterruptConfig(BOARD_SW_GPIOD_PORT, BOARD_SW_GPIOD_PIN3, kPORT_InterruptFallingEdge);
    EnableIRQ(BOARD_SW_IRQ_PORTD);
    GPIO_PinInit(BOARD_SW_GPIO_PORTD, BOARD_SW_GPIOD_PIN3, &sw_config);

    /* Init input switch Forward GPIO. */
    PORT_SetPinInterruptConfig(BOARD_SW_GPIOD_PORT, BOARD_SW_GPIOD_PIN6, kPORT_InterruptFallingEdge);
    EnableIRQ(BOARD_SW_IRQ_PORTD);
    GPIO_PinInit(BOARD_SW_GPIO_PORTD, BOARD_SW_GPIOD_PIN6, &sw_config);

    //Set PORTB Interrupt level to 3, configMAX_SYSCALL_INTERRUPT_PRIORITY priority is 2.
    result = NVIC_GetPriority(88);
	NVIC_SetPriority(88,3);        //PORTB vector is 88
	result = NVIC_GetPriority(88);

    //Set PORTD Interrupt level to 3, configMAX_SYSCALL_INTERRUPT_PRIORITY priority is 2.
    result = NVIC_GetPriority(90);
	NVIC_SetPriority(90,3);        //PORTD vector is 90
	result = NVIC_GetPriority(90);
}

void delay(uint32_t x)
{
    volatile uint32_t i = 0;

    x= x*10000;

    for (i = 0; i < x; ++i)
    {
        __asm("NOP"); /* delay */
    }
}

/*
 * @brief   Application entry point.
 */
int main(void) {
	int result = 0;

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

    myGPIOinit();

#define TEST
#ifdef TEST
	//MOVE Forward
	moveForward(100);

	//MOVE Backward
	moveBackward(100);
#endif


    vTaskStartScheduler();
    for (;;)
        ;

    return 0 ;
}

/*!
 * @brief Task responsible for printing of "Hello world." message.
 */
static void clt_task(void *pvParameters)
{
    char cmd[MAX_CMD_LENGTH + 1];

}

/*!
 * @brief Task responsible for move jRobot Left during 10 ticks.
 */
static void left_task(void *pvParameters)
{
	//MOVE left
	moveLeft(100);
}

/*!
 * @brief Task responsible for move jRobot Right during 10 ticks.
 */
static void right_task(void *pvParameters)
{
	//MOVE right
	moveRight(100);
}

/*!
 * @brief Task responsible for move jRobot Forward during 10 ticks.
 */
static void forward_task(void *pvParameters)
{
	//MOVE Forward
	moveForward(100);
}

/*!
 * @brief Task responsible for move jRobot backward during 10 ticks.
 */
static void backward_task(void *pvParameters)
{
	//MOVE Backward
	moveBackward(100);
}

/*!
 * @brief Function responsible for move jRobot left.
 */
static void moveLeft(char ticks)
{

	//LEDs for Move Left ON
	GPIO_TogglePinsOutput(BOARD_LED_GPIO_PORTC, 1u << BOARD_LED_GPIOC_PIN13); //left

	//MOVE left
	GPIO_TogglePinsOutput(BOARD_LED_GPIO_PORTE, 1u << BOARD_LED_GPIOE_PIN4); //GPIOE_PDOR |= 0x10;  //PTE4 - LEFT_MTR_DIR
	GPIO_TogglePinsOutput(BOARD_LED_GPIO_PORTE, 1u << BOARD_LED_GPIOD_PIN5); //GPIOE_PDOR |= 0x20;  //PTE5 - RIGHT_MTR_DIR

	delay(ticks); //should be 100 ticks

	//STOP
	GPIO_TogglePinsOutput(BOARD_LED_GPIO_PORTE, 1u << BOARD_LED_GPIOE_PIN4); //GPIOE_PDOR &= ~0x10; //PTE4 - LEFT_MTR_DIR
	GPIO_TogglePinsOutput(BOARD_LED_GPIO_PORTE, 1u << BOARD_LED_GPIOD_PIN5); //GPIOE_PDOR &= ~0x20  //PTE5 - RIGHT_MTR_DIR

	//LEDs for Move left OFF
	GPIO_TogglePinsOutput(BOARD_LED_GPIO_PORTC, 1u << BOARD_LED_GPIOC_PIN13); //left

}

/*!
 * @brief Function responsible for move jRobot right
 */
static void moveRight(char ticks)
{

	//LEDs for Move right ON
	GPIO_TogglePinsOutput(BOARD_LED_GPIO_PORTC, 1u << BOARD_LED_GPIOC_PIN12); //right

	//MOVE right
	GPIO_TogglePinsOutput(BOARD_LED_GPIO_PORTD, 1u << BOARD_LED_GPIOE_PIN4); //GPIOD_PDOR |= 0x10;  //PTD4 - LEFT_MTR_SPD
	GPIO_TogglePinsOutput(BOARD_LED_GPIO_PORTD, 1u << BOARD_LED_GPIOD_PIN5); //GPIOD_PDOR |= 0x20;  //PTD5 - RIGHT_MTR_SPD

	delay(ticks); //should be 100 ticks

	//STOP
	GPIO_TogglePinsOutput(BOARD_LED_GPIO_PORTD, 1u << BOARD_LED_GPIOE_PIN4); //GPIOD_PDOR &= ~0x10; //PTD4 - LEFT_MTR_SPD
	GPIO_TogglePinsOutput(BOARD_LED_GPIO_PORTD, 1u << BOARD_LED_GPIOD_PIN5); //GPIOD_PDOR &= ~0x20  //PTD5 - RIGHT_MTR_SPD

	//LEDs for Move right OFF
	GPIO_TogglePinsOutput(BOARD_LED_GPIO_PORTC, 1u << BOARD_LED_GPIOC_PIN12); //right

}

/*!
 * @brief Function responsible for move jRobot forward
 */
static void moveForward(char ticks)
{
	//LEDs for Move forward ON
	GPIO_TogglePinsOutput(BOARD_LED_GPIO_PORTC, 1u << BOARD_LED_GPIOC_PIN14); //front
	GPIO_TogglePinsOutput(BOARD_LED_GPIO_PORTC, 1u << BOARD_LED_GPIOC_PIN15); //front

	//MOVE Forward
	GPIO_TogglePinsOutput(BOARD_LED_GPIO_PORTE, 1u << BOARD_LED_GPIOE_PIN4); //GPIOE_PDOR |= 0x10;  //PTE4 - LEFT_MTR_DIR
	GPIO_TogglePinsOutput(BOARD_LED_GPIO_PORTD, 1u << BOARD_LED_GPIOD_PIN5); //GPIOD_PDOR |= 0x20;  //PTD5 - RIGHT_MTR_SPD

	delay(ticks); //should be 100 ticks

	//STOP
	GPIO_TogglePinsOutput(BOARD_LED_GPIO_PORTE, 1u << BOARD_LED_GPIOE_PIN4); //GPIOE_PDOR &= ~0x10; //PTE4 - LEFT_MTR_DIR
	GPIO_TogglePinsOutput(BOARD_LED_GPIO_PORTD, 1u << BOARD_LED_GPIOD_PIN5); //GPIOD_PDOR &= ~0x20  //PTD5 - RIGHT_MTR_SPD

	//LEDs for Move forward OFF
	GPIO_TogglePinsOutput(BOARD_LED_GPIO_PORTC, 1u << BOARD_LED_GPIOC_PIN14); //front
	GPIO_TogglePinsOutput(BOARD_LED_GPIO_PORTC, 1u << BOARD_LED_GPIOC_PIN15); //front
}

/*!
 * @brief Function responsible for move jRobot backwards
 */
static void moveBackward(char ticks)
{

	//LEDs for Move backward ON
	GPIO_TogglePinsOutput(BOARD_LED_GPIO_PORTE, 1u << BOARD_LED_GPIOE_PIN3);  //back
	GPIO_TogglePinsOutput(BOARD_LED_GPIO_PORTC, 1u << BOARD_LED_GPIOC_PIN11); //back

	//MOVE backward
	GPIO_TogglePinsOutput(BOARD_LED_GPIO_PORTD, 1u << BOARD_LED_GPIOE_PIN4); //GPIOE_PDOR |= 0x10;  //PTE4 - LEFT_MTR_DIR
	GPIO_TogglePinsOutput(BOARD_LED_GPIO_PORTE, 1u << BOARD_LED_GPIOD_PIN5); //GPIOD_PDOR |= 0x20;  //PTD5 - RIGHT_MTR_SPD

	delay(ticks); //should be 100 ticks

	//STOP
	GPIO_TogglePinsOutput(BOARD_LED_GPIO_PORTD, 1u << BOARD_LED_GPIOE_PIN4); //GPIOE_PDOR &= ~0x10; //PTE4 - LEFT_MTR_DIR
	GPIO_TogglePinsOutput(BOARD_LED_GPIO_PORTE, 1u << BOARD_LED_GPIOD_PIN5); //GPIOD_PDOR &= ~0x20  //PTD5 - RIGHT_MTR_SPD

	//LEDs for Move backward OFF
	GPIO_TogglePinsOutput(BOARD_LED_GPIO_PORTE, 1u << BOARD_LED_GPIOE_PIN3);  //back
	GPIO_TogglePinsOutput(BOARD_LED_GPIO_PORTC, 1u << BOARD_LED_GPIOC_PIN11); //back

}
