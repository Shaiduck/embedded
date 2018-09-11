#include "Mem_AllocTypes.h"

MemHandlerType MemControl =
{
    .MemStart = (uint8_t*) &_heap_mem_start,
    .MemEnd = (uint8_t*) &_heap_mem_end,
    .CurrAddr = (uint8_t*) &_heap_mem_start,
    .FreeBytes = (uint8_t*) &_heap_mem_end - (uint8_t*) &_heap_mem_start;
};

/*
    Function: Mem_Alloc
    Allocates
    Param: size
    Type is uint16_t: max 65535 bytes size
*/
void * Mem_Alloc(uint16_t size)
{
    uint8_t *returnVal;
    uint32_t currentEndAddress;

    currentEndAddress = (uint32_t)Mem_AllocControl.current_address + size;
    if (currentEndAddress > (uint32_t)Mem_AllocControl.heap_end)
    {
      printf("Unable to alocate. Heap End address exceeded.\n\r");
      returnVal = (void*)0; /* NULL */
    }
    else
    {
      /* Allocated Pointer Address Update */
        returnVal = (void*) Mem_AllocControl.current_address;
      /* 
        Allign current address to:
            8bytes (64bit architecture)*/
       currentEndAddress = (currentEndAddress +(TARGET_ARCH-1)) & TARGET_ARCH_MASK;
            Mem_AllocControl.currentEndAddress = (uint8_t*) currentEndAddress;
        printf("Data allocated. \n\r");
    }
    return(returnVal);
}