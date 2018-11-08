/****************************************************************************************************/
/**
\file       memory_allocation.c
\brief      Dynamic Memory allocation services.
\author     Abraham Tezmol
\version    1.0
\date       21/09/2013
*/
/****************************************************************************************************/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Dynamic Memory allocation services */
#include    "memory_allocation.h"

/*****************************************************************************************************
* Definition of  VARIABLEs - 
*****************************************************************************************************/


/* Mem alloc status variables */

const tMemAlloc_config * mem_alloc_cnf;

tMemAlloc_status    MemAlloc_Status;

tPagedRAMpages_status PagedRamPages_status[MEM_ALLOC_MAX_RAM_PAGES] = 
{
    {RAM_NULL, (uint8_t *)NULL,(uint8_t *)NULL, 0},
    {RAM_NULL, (uint8_t *)NULL,(uint8_t *)NULL, 0},
    {RAM_NULL, (uint8_t *)NULL,(uint8_t *)NULL, 0},
    {RAM_NULL, (uint8_t *)NULL,(uint8_t *)NULL, 0},
    {RAM_NULL, (uint8_t *)NULL,(uint8_t *)NULL, 0},
    {RAM_NULL, (uint8_t *)NULL,(uint8_t *)NULL, 0},
    {RAM_NULL, (uint8_t *)NULL,(uint8_t *)NULL, 0},
    {RAM_NULL, (uint8_t *)NULL,(uint8_t *)NULL, 0},
    {RAM_NULL, (uint8_t *)NULL,(uint8_t *)NULL, 0},
    {RAM_NULL, (uint8_t *)NULL,(uint8_t *)NULL, 0},
    {RAM_NULL, (uint8_t *)NULL,(uint8_t *)NULL, 0},
    {RAM_NULL, (uint8_t *)NULL,(uint8_t *)NULL, 0},
    {RAM_NULL, (uint8_t *)NULL,(uint8_t *)NULL, 0},
    {RAM_NULL, (uint8_t *)NULL,(uint8_t *)NULL, 0},
    {RAM_NULL, (uint8_t *)NULL,(uint8_t *)NULL, 0},
    {RAM_NULL, (uint8_t *)NULL,(uint8_t *)NULL, 0}
};
/*****************************************************************************************************
* Definition of module wide (CONST-) CONSTANTs 
*****************************************************************************************************/

/*****************************************************************************************************
* Code of module wide private FUNCTIONS
*****************************************************************************************************/


/****************************************************************************************************/
/**
* \brief    memory allocation - Initialization
* \author   Abraham Tezmol
* \param    void
* \return   void
* \todo     
*/
void vfnMemAlloc_Init( const tMemAlloc_config * mem_alloc_config  )
{
    uint8_t   u8pageIndex;
    uint8_t * StartAddress;
    uint8_t * EndAddress;
    
    /* Store pointer to driver configuration */
    mem_alloc_cnf = mem_alloc_config;
    
    MemAlloc_Status.RamPageStatus = &PagedRamPages_status[0];
    
    if (mem_alloc_cnf->u8Number_of_RAM_pages != 0)
    {
        for (u8pageIndex = 0; u8pageIndex < mem_alloc_cnf->u8Number_of_RAM_pages; u8pageIndex++ )
        {
            /* Obtain Start and End Addresses */
            StartAddress =   mem_alloc_cnf->ptr_PagedRAMpages_config[u8pageIndex].ptr_StartAddress;
            EndAddress = mem_alloc_cnf->ptr_PagedRAMpages_config[u8pageIndex].ptr_EndAddress;
            /* Update all relevant entries in status structure */ 
            MemAlloc_Status.RamPageStatus[u8pageIndex].RamPageId = mem_alloc_cnf->ptr_PagedRAMpages_config[u8pageIndex].RamPageId;
            MemAlloc_Status.RamPageStatus[u8pageIndex].ptr_CurrentAddress = StartAddress;
            MemAlloc_Status.RamPageStatus[u8pageIndex].ptr_EndAddress = EndAddress;
            MemAlloc_Status.RamPageStatus[u8pageIndex].u16_FreeBytes = (uint16_t)(EndAddress - StartAddress + 1);
            /* Updated internal variable that keeps track of available pages */
            MemAlloc_Status.u8NumberOfPages++;
            
            /* Erase RAM in order to assure all entries are ready to be used */
            vfnMemAlloc_Erase(StartAddress, MemAlloc_Status.RamPageStatus[u8pageIndex].u16_FreeBytes);
        }
    }
}

/****************************************************************************************************/
/**
* \brief    memory allocation - reserve a buffer and return its address
* \author   Abraham Tezmol
* \param    uint16_t  u16SizeinBytes
* \return   uint8_t * pointer to start of allocated space
* \todo     
*/
uint8_t * MemAlloc_Reserve( uint16_t  u16SizeinBytes)
{
    uint8_t u8pageIndex;
    uint8_t * prtAllocatedBuffer = (uint8_t *)NULL;
    static uint8_t * StartAddress;
    static uint8_t * EndAddress;
    
    for (u8pageIndex = 0; u8pageIndex < MemAlloc_Status.u8NumberOfPages; u8pageIndex++ )
    {
        /* Get start and end address parameters for this RAM page */ 
        StartAddress = MemAlloc_Status.RamPageStatus[u8pageIndex].ptr_CurrentAddress;
        EndAddress = MemAlloc_Status.RamPageStatus[u8pageIndex].ptr_EndAddress;
        /* Apply alginment */
        StartAddress = (uint8_t *)(((uint32_t)(StartAddress)+3) & (uint32_t)MEM_ALLOC_4_BYTE_ALIGN);
        /* Verify if enough memory is free */
        if( (uint16_t)(EndAddress - StartAddress + 1) >= u16SizeinBytes )
        {
            /* Enough memory is available, reserve it and return its start address */
            prtAllocatedBuffer = StartAddress;
            MemAlloc_Status.RamPageStatus[u8pageIndex].ptr_CurrentAddress = StartAddress + u16SizeinBytes;
            MemAlloc_Status.RamPageStatus[u8pageIndex].u16_FreeBytes = (uint16_t)(EndAddress - StartAddress + 1);
            /* Stop searching thorugh pages */
            break;
        }
    }
    
    return(prtAllocatedBuffer);
}

/****************************************************************************************************/
/**
* \brief    memory allocation - reserve a buffer and return its address
* \author   Abraham Tezmol
* \param    tu8ptr_far StartAddress - Start of section to be erased
* \param    uint16_t  u16SizeinBytes - size of section to be erased 
* \return   uint8_t * pointer to start of allocated space
* \todo     
*/
void vfnMemAlloc_Erase( uint8_t * StartAddress , uint16_t  u16SizeinBytes)
{
    uint16_t u16Bytes;
    
    for (u16Bytes = 0; u16Bytes < u16SizeinBytes; u16Bytes++ )
    {
        *StartAddress++ = 0x00;
    }
}

/***************************************************************************************************/
