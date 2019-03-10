#ifndef __MEMALLOC_TYPES
#define __MEMALLOC_TYPES

#include "chip.h"

/* Type Definitions  **/
typedef	void	   *		Mem_ReturnType;
typedef	uint8_t	 *		Mem_Uint8PtrType;
typedef	uint16_t			Mem_SizeType;

typedef struct{	
  Mem_Uint8PtrType	memStart;
  Mem_Uint8PtrType	memEnd;
  Mem_Uint8PtrType	currAddr;
  uint32_t	freeBytes;
}MemHandlerType;

#endif