#ifndef __MEMALLOC
#define __MEMALLOC

#include "MemAlloc_Types.h"

void MemAllocInit ( void );
Mem_ReturnType MemAlloc( uint16_t size );

#endif