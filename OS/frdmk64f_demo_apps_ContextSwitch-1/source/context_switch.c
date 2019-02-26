#include "asm.h"

void activate(unsigned int *stack)
{
	/* save kernel state */
	__asm ("MRS   IP, PSR \n"); //ip and/or IP - Intra Procedure call scratch register. This is a synonym for R12.
	__asm ("PUSH  {R4, R5, R6, R7, R8, R9, R10, R11, IP, LR} \n");

	/* switch to process stack */
	__asm ("MSR   PSP, R0 \n");
	__asm ("MOV   R0, #2 \n");
	__asm ("MSR   CONTROL, R0 \n");

	/* load user state */
	__asm ("POP   {R4, R5, R6, R7, R8, R9, R10, R11, LR} \n");

	/* jump to user task */
	__asm ("BX    LR \n");
}
