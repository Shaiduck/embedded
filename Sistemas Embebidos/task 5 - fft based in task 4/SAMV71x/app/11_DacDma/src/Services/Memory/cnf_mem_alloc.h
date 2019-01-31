/****************************************************************************************************/
/**
\file       cnf_mem_alloc.h
\brief      Configuration of Dynamic Memory Allocation function prototypes
\author     Abraham Tezmol
\version    1.0
\date       21/09/2013
*/
/****************************************************************************************************/

#ifndef __CNF_MEM_ALLOC_H        /*prevent duplicated includes*/ 
#define    __CNF_MEM_ALLOC_H    

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

#include "compiler.h"
#include "Std_Types.h"


/*****************************************************************************************************
* Declaration of module wide TYPES
*****************************************************************************************************/

typedef enum
{
    RAM_F0,
    RAM_F1,
    RAM_F2,
    RAM_F3,
    RAM_F4,
    RAM_F5,
    RAM_F6,
    RAM_F7,
    RAM_F8,
    RAM_F9,
    RAM_FA,
    RAM_FB,
    RAM_FC,
    RAM_FD,
    RAM_FE,
    RAM_FF,
    RAM_NULL
}tPagedRAMpages;

typedef struct 
{
    tPagedRAMpages              RamPageId;
    uint8_t  *                  ptr_StartAddress;
    uint8_t  *                  ptr_EndAddress;
}tPagedRAMpages_config;

typedef struct 
{
    uint8_t                         u8Number_of_RAM_pages;
    const tPagedRAMpages_config *   ptr_PagedRAMpages_config;
}tMemAlloc_config;


/*****************************************************************************************************
* Definition of module wide MACROS / #DEFINE-CONSTANTS 
*****************************************************************************************************/

/* Global Dynamic Memory Allocation Configuration Macros  */
#define    MEM_ALLOC_MAX_RAM_PAGES              16

/*****************************************************************************************************
* Declaration of public VARIABLEs / Constants 
*****************************************************************************************************/

extern const tMemAlloc_config  DynamicMemAlloc_config[];

/*****************************************************************************************************
* Declaration of module wide FUNCTIONS
*****************************************************************************************************/


#endif /* __CNF_MEM_ALLOC_H */ 