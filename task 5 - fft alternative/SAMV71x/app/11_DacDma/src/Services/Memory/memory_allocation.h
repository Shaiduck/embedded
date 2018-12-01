/****************************************************************************************************/
/**
\file       memory_allocation.h
\brief      Dynamic Memory allocation services.
\author     Abraham Tezmol
\version    1.0
\date       21/09/2013
*/
/****************************************************************************************************/

#ifndef __MEMORY_ALLOCATION_H        /*prevent duplicated includes*/ 
#define    __MEMORY_ALLOCATION_H    

/*****************************************************************************************************
* Include files
*****************************************************************************************************/


#include "compiler.h"
#include "Std_Types.h"

/** Dynamic Memory allocation configuration definitions */
#include    "cnf_mem_alloc.h"

/*****************************************************************************************************
* Declaration of module wide TYPES
*****************************************************************************************************/

/* Data type definitions */
typedef struct 
{
    tPagedRAMpages         RamPageId;
    uint8_t *                   ptr_CurrentAddress;
    uint8_t *                   ptr_EndAddress;
    uint16_t                    u16_FreeBytes;
}tPagedRAMpages_status;

typedef struct 
{      
    tPagedRAMpages_status *     RamPageStatus;
    uint8_t                     u8NumberOfPages;
}tMemAlloc_status;
/*****************************************************************************************************
* Definition of module wide MACROS / #DEFINE-CONSTANTS 
*****************************************************************************************************/

#define MEM_ALLOC_1_BYTE_ALIGN				0xFFFFFFFF
#define MEM_ALLOC_2_BYTE_ALIGN				0xFFFFFFFE
#define MEM_ALLOC_4_BYTE_ALIGN				0xFFFFFFFC

/*****************************************************************************************************
* Declaration of module wide VARIABLEs
*****************************************************************************************************/

/*****************************************************************************************************
* Declaration of module wide FUNCTIONS
*****************************************************************************************************/
/** Dynamic Memory Allocation Initialization */
void vfnMemAlloc_Init( const tMemAlloc_config * mem_alloc_config  );
/** Dynamic Memory Allocation - Actual allocation mechanism */
uint8_t * MemAlloc_Reserve( uint16_t  u16SizeinBytes );
/** Dynamic Memory Allocation - RAM Erase mechanism */
void vfnMemAlloc_Erase( uint8_t * StartAddress , uint16_t  u16SizeinBytes);

#endif /* __MEMORY_ALLOCATION_H */ 