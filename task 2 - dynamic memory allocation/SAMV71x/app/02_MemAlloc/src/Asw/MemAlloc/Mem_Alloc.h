#ifndef MEM_ALLOC_H
#define MEM_ALLOC_H

#include <Std_Types.h>

/* Do not modify */
#define ALLIGNMENT_64BIT (8)
#define ALLIGNMENT_32BIT (4)
#define ALLIGNMENT_16BIT (2)
#define ALLIGNMENT_8BIT  (1)

#define TARGET_ARCH       ALLIGNMENT_32BIT

#if TARGET_ARCH == ALLIGNMENT_64BIT
	#define TARGET_ARCH_MASK (0xFFFFFFFFFFFFFFF0)
#elif TARGET_ARCH == ALLIGNMENT_32BIT
	#define TARGET_ARCH_MASK (0xFFFFFFFC)
#elif TARGET_ARCH == ALLIGNMENT_16BIT
	#define TARGET_ARCH_MASK (0xFFFE)
#elif TARGET_ARCH == ALLIGNMENT_8BIT
	#define TARGET_ARCH_MASK (0xFF)     
#endif

/* 
	Fuction: memalloc
		Allocates
	Param: size
		Type is uint16_t: max 65535 bytes size
*/

extern void *memalloc(uint16_t size);

#endif