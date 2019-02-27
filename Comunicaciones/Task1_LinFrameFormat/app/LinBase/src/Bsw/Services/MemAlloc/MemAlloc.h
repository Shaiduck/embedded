/*******************************************************************************/
/**
\file       MemAlloc.h
\brief      Memory Allocation Handler
   \~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   \version       1.0
   \author        Francisco Martinez Chavez
   \description   Initial version of Memory Allocation Handler
   \date          31/08/2018
*/

#ifndef MEM_MALLOC_H
#define MEM_MALLOC_H

#include "Std_Types.h"

/* Do not modify */
#define ALLIGNMENT_64BIT (8)
#define ALLIGNMENT_32BIT (4)
#define ALLIGNMENT_16BIT (2)
#define ALLIGNMENT_8BIT  (1)

/* Memory allocation configuration based on target processor architecture 
	Set the value accordinggly:
		#define TARGET_ARCH ALLIGNMENT_64BIT
		#define TARGET_ARCH ALLIGNMENT_32BIT
		#define TARGET_ARCH ALLIGNMENT_16BIT
		#define TARGET_ARCH ALLIGNMENT_8BIT
*/

#define TARGET_ARCH ALLIGNMENT_32BIT

/*
	Function: MemAlloc
		Allocates 
	Param: size 
		Type is uint16_t: max 65535 bytes size
*/
extern void * MemAlloc ( uint16_t size );


#endif