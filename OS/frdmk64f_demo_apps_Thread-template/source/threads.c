#include "threads.h"
#include "main.h"

void PendSV_Handler( void ) __attribute__ (( naked ));

#define THREAD_PSP	0xFFFFFFFD

/* Thread Control Block */
typedef struct {
	void *stack;
	void *orig_stack;
	uint8_t in_use;
} tcb_t;

static tcb_t tasks[MAX_TASKS];
static int lastTask;
static int first = 1;

/* FIXME: Without naked attribute, GCC will corrupt r7 which is used for stack
 * pointer. If so, after restoring the tasks' context, we will get wrong stack
 * pointer.
 */
void PendSV_Handler( void )
{
	/* Save the old task's context */
	asm volatile("MRS   R0, PSP\n"
	             "STMDB R0!, {R4,R5,R6,R7,R8,R9,R10,R11, LR}\n");
	/* To get the task pointer address from result r0 */
	asm volatile("MOV   %0, R0\n" : "=r" (tasks[lastTask].stack));

	/* Find a new task to run */
	while (1) {
		lastTask++;
		if (lastTask == MAX_TASKS)
			lastTask = 0;
		if (tasks[lastTask].in_use) {
			/* Move the task's stack pointer address into r0 */
			asm volatile("MOV R0, %0\n" : : "r" (tasks[lastTask].stack));
			/* Restore the new task's context and jump to the task */
			asm volatile("LDMIA R0!, {R4,R5,R6,R7,R8,R9,R10,R11, LR}\n"
			             "MSR PSP, R0\n"
			             "BX LR\n");
		}
	}
}


void SysTick_Handler(void)
{
	SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
}

void thread_start()
{
	lastTask = 0;

	/* Save kernel context */
	asm volatile("MRS IP, PSR\n"
	             "PUSH {R4,R5,R6,R7,R8,R9,R10,R11, IP, LR}\n");

	/* To bridge the variable in C and the register in ASM,
	 * move the task's stack pointer address into r0.
	 * http://www.ethernut.de/en/documents/arm-inline-asm.html
	 */
	asm volatile("MOV R0, %0\n" : : "r" (tasks[lastTask].stack));
	
	/* Load user task's context and jump to the task */
	asm volatile("MSR PSP, R0\n"
	             "MOV R0, #2\n"
	             "MSR CONTROL, R0\n"
	             "ISB\n"
	             "POP {R4,R5,R6,R7,R8,R9,R10,R11, LR}\n"
	             "POP {R0}\n"
	             "BX LR\n");
}

int thread_create(void (*run)(void *), void *userdata)
{
	/* Find a free thing */
	int threadId = 0;
	uint32_t *stack;

	for (threadId = 0; threadId < MAX_TASKS; threadId++) {
		if (tasks[threadId].in_use == 0)
			break;
	}

	if (threadId == MAX_TASKS)
		return -1;

	/* Create the stack */
	stack = (uint32_t *) malloc(STACK_SIZE * sizeof(uint32_t));
	tasks[threadId].orig_stack = stack;
	if (stack == 0)
		return -1;

	stack += STACK_SIZE - 32; /* End of stack, minus what we are about to push */
	if (first) {
		stack[8] =  (unsigned int) run;
		stack[9] =  (unsigned int) userdata;
		first = 0;
	} else {
		stack[8] =  (unsigned int) THREAD_PSP;
		stack[9] =  (unsigned int) userdata;
		stack[14] = (unsigned) &thread_self_terminal;
		stack[15] = (unsigned int) run;
		stack[16] = (unsigned int) 0x01000000; /* PSR Thumb bit */
	}

	/* Construct the control block */
	tasks[threadId].stack = stack;
	tasks[threadId].in_use = 1;

	return threadId;
}

void thread_kill(int thread_id)
{
	tasks[thread_id].in_use = 0;

	/* Free the stack */
	free(tasks[thread_id].orig_stack);
}

void thread_self_terminal()
{
	/* This will kill the stack.
	 * For now, disable context switches to save ourselves.
	 */
	asm volatile("CPSID   I\n");
	thread_kill(lastTask);
	asm volatile("CPSIE   I\n");

	/* And now wait for death to kick in */
	while (1);
}
