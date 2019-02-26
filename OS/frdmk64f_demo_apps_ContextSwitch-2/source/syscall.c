#include "asm.h"

void syscall(void)
{
	//__asm ("NOP \n");
	__asm ("SVC 0 \n");
	//__asm ("NOP \n");
	__asm ("BX LR \n");
}
