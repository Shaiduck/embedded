#include "asm.h"

void SVC_Handler( void ) __attribute__ (( naked ));

void SVC_Handler(void)
{
	/* save user state */
	__asm("MRS     R0, PSP \n");
	__asm("STMDB   R0!, {R4, R5, R6, R7, R8, R9, R10, R11, LR} \n");

	/* load kernel state */
	__asm("POP     {R4, R5, R6, R7, R8, R9, R10, R11, IP, LR}  \n");
	__asm("MSR     PSR_NZCVQ, IP \n");

	__asm("BX      LR \n");
}

unsigned int * activate(unsigned int *stack)
{
	/* save kernel state */
	__asm ("MRS    IP, PSR \n");          //ip and/or IP - Intra procedure call scratch register. This is a synonym for R12.
	__asm ("PUSH   {R4, R5, R6, R7, R8, R9, R10, R11, IP, LR} \n");

	/* load user state */
	__asm ("LDMIA  R0!, {R4, R5, R6, R7, R8, R9, R10, R11, LR} \n");
	__asm ("MSR    PSP, R0 \n");

	/* check the situation and determine the transition */
	__asm ("MOV    R0, #0xFFFFFFFD \n");
	__asm ("CMP    LR, R0 \n");          // LR - 0xFFFFFFFD

	/* if "LR" does not point to exception return, then switch to process stack */
	__asm ("ITTT   NE \n");              // "NE" - Not equal - Z flag is cleared
	__asm ("MOVNE  R0, #2 \n");
	// __asm ("MOVNE  R0, #3 \n");
	__asm ("MSRNE  CONTROL, R0 \n");
	__asm ("ISBNE \n");

	/* jump to user task */
	__asm ("BX     LR \n");

	return 0;
}
