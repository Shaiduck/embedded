/*
 * The Clear BSD License
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted (subject to the limitations in the disclaimer below) provided
 * that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS LICENSE.
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

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "board.h"

#include "pin_mux.h"
#include "clock_config.h"

#include "asm.h"


/*******************************************************************************
 * Definitions
 ******************************************************************************/
void usertask(void);
#define HANDLER_MSP	0xFFFFFFF1
#define THREAD_MSP	0xFFFFFFF9
#define THREAD_PSP	0xFFFFFFFD
/* Size of our user task stacks in words */
#define STACK_SIZE 256

/* Number of user task */
#define TASK_LIMIT 2

/* Initialization of process stack
 * r4, r5, r6, r7, r8, r9, r10, r11, lr */
unsigned int usertask_stack[256] = {0};
unsigned int *usertask_stack_start = usertask_stack + 256 - 16;

void usertask(void)
{
	PRINTF("usertask: 1st call of usertask!\n\r");
	PRINTF("usertask: Now, return to kernel mode\n\r");
	syscall();
	PRINTF("usertask: 2nd call of usertask!\n\r");
	PRINTF("usertask: Now, return to kernel mode\n\r");
	syscall();
	while (1)
		/* wait */ ;
}

void task1_func(void)
{
	PRINTF("task1: Created!\n");
	PRINTF("task1: Now, return to kernel mode\n");
	syscall();
	while (1) {
		PRINTF("task1: Executed!\n");
		PRINTF("task1: Now, return to kernel mode\n");
		syscall(); /* return to kernel mode */
	}
}

void task2_func(void)
{
	PRINTF("task2: Created!\n");
	PRINTF("task2: Now, return to kernel mode\n");
	syscall();
	while (1) {
		PRINTF("task2: Executed!\n");
		PRINTF("task2: Now, return to kernel mode\n");
		syscall(); /* return to kernel mode */
	}
}

unsigned int *create_task(unsigned int *stack, void (*start)(void))
{
	// stack += STACK_SIZE - 17; /* End of stack, minus what we are about to push */
	// stack[8] = (unsigned int) THREAD_PSP;
	// stack[15] = (unsigned int) start;
	// stack[16] = (unsigned int) 0x01000000; /* PSR Thumb bit */
	stack[8] = (unsigned int) start;
	stack = activate(stack);

	return stack;
}
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Main function
 */
int main(void)
{
	unsigned int user_stacks[TASK_LIMIT][STACK_SIZE];
	unsigned int *usertasks[TASK_LIMIT];
	size_t task_count = 0;
	size_t current_task;

	// usertask_stack_start[8] = (unsigned int) &usertask;

    /* Init board hardware. */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    // PRINTF("OS: Starting...\n\r");
    // PRINTF("OS: Calling the usertask (1st time)\n\r");

    // usertask_stack_start = activate(usertask_stack_start);
	// // usertask_stack_start = activate(task1_func);
	// PRINTF("OS: Return to the OS mode !\n\r");
	// PRINTF("OS: Calling the usertask (2nd time)\n\r");

	// usertask_stack_start = activate(usertask_stack_start);
	// // usertask_stack_start = activate(task2_func);
	// PRINTF("OS: Return to the OS mode !\n\r");
	// PRINTF("OS: Going to infinite loop...\n\r");

	// while (1)
	// 	/* We can't exit, there is nowhere to go */ ;
	// return 0;

	PRINTF("OS: Starting...\n");
	PRINTF("OS: First create task 1\n");
	usertasks[0] = create_task(user_stacks[0]+256-16, &task1_func);
	task_count += 1;
	PRINTF("OS: Back to OS, create task 2\n");
	usertasks[1] = create_task(user_stacks[1]+256-16, &task2_func);
	task_count += 1;

	PRINTF("\nOS: Start multitasking, back to OS till task yield!\n");
	current_task = 0;

	while (1) {
		PRINTF("OS: Activate next task\n");
		usertasks[current_task] = activate(usertasks[current_task]);
		PRINTF("OS: Back to OS\n");

		current_task = current_task == (task_count - 1) ? 0 : current_task + 1;
	}

	return 0;

}
