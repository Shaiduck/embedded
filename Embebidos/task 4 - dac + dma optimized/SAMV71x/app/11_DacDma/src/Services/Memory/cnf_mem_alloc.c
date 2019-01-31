/****************************************************************************************************/
/**
\file       cnf_mem_alloc.c
\brief      Configuration of Dynamic Memory Allocation services
\author     Abraham Tezmol
\version    1.0
\date       21/09/2013
*/
/****************************************************************************************************/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Dynamic Memory allocation configuration definitions */
#include    "cnf_mem_alloc.h"

/*****************************************************************************************************
* Definition of  VARIABLEs - 
*****************************************************************************************************/

/* Dynamic memory allocation configuration for FAR memory */
const tPagedRAMpages_config PagedRamPages_config[] =
{
    {RAM_F0, (uint8_t *)0x20440000, (uint8_t *)0x20440FFF},
    {RAM_F1, (uint8_t *)0x20441000, (uint8_t *)0x20441FFF},
    {RAM_F2, (uint8_t *)0x20442000, (uint8_t *)0x20442FFF},
    {RAM_F3, (uint8_t *)0x20443000, (uint8_t *)0x20443FFF},
    {RAM_F4, (uint8_t *)0x20444000, (uint8_t *)0x20444FFF},
    {RAM_F5, (uint8_t *)0x20445000, (uint8_t *)0x20445FFF},
    {RAM_F6, (uint8_t *)0x20446000, (uint8_t *)0x20446FFF},
    {RAM_F7, (uint8_t *)0x20447000, (uint8_t *)0x20447FFF},
    {RAM_F8, (uint8_t *)0x20448000, (uint8_t *)0x20448FFF},
    {RAM_F9, (uint8_t *)0x20449000, (uint8_t *)0x20449FFF},
    {RAM_FA, (uint8_t *)0x2044A000, (uint8_t *)0x2044AFFF},
    {RAM_FB, (uint8_t *)0x2044B000, (uint8_t *)0x2044BFFF},
    {RAM_FC, (uint8_t *)0x2044C000, (uint8_t *)0x2044CFFF},
    {RAM_FD, (uint8_t *)0x2044D000, (uint8_t *)0x2044DFFF},
    {RAM_FE, (uint8_t *)0x2044E000, (uint8_t *)0x2044EFFF},
    {RAM_FF, (uint8_t *)0x2044F000, (uint8_t *)0x2044FFFF}
};

const tMemAlloc_config  DynamicMemAlloc_config[] =
{
    {
        sizeof(PagedRamPages_config)/sizeof(PagedRamPages_config[0]),    /* number of configured RAM pages */
        &PagedRamPages_config[0]                                         /* RAM pages configuration structure */
    }
};
/*****************************************************************************************************
* Definition of module wide (CONST-) CONSTANTs 
*****************************************************************************************************/

/*****************************************************************************************************
* Code of module wide private FUNCTIONS
*****************************************************************************************************/


/*****************************************************************************************************
* Code of public FUNCTIONS
*****************************************************************************************************/


/***************************************************************************************************/
