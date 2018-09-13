#include "Mem_AllocTypes.h"
#include "Mem_Alloc.h"

MemHandlerType MemControl =
{
    .MemStart = (uint8_t*)&_heap_mem_start,
    .MemEnd = (uint8_t*)&_heap_mem_end,
    .CurrAddr = (uint8_t*)&_heap_mem_start,
    .FreeBytes = 0,
};

/*
    Function: Mem_Alloc
    Allocates
    Param: size
    Type is uint16_t: max 65535 bytes size
*/
void* memalloc(uint16_t size)
{
    MemControl.FreeBytes = _heap_mem_size;
    
    uint8_t *returnVal;
    uint32_t currentEndAddress;

    currentEndAddress = (uint32_t)MemControl.CurrAddr + (uint32_t)size;
    
    if (currentEndAddress > (uint32_t)MemControl.MemEnd)
    {
        printf("Unable to alocate. Heap End address exceeded.\n\r");
        returnVal = (void*)0; /* NULL */
    }
    else
    {
        /* Allocated Pointer Address Update */
        returnVal = (void*) MemControl.CurrAddr;
        /* 
            Allign current address to:
                8bytes (64bit architecture) -> #define TARGET_ARCH ALLIGNMENT_64BIT
                4bytes (32bit architecture) -> #define TARGET_ARCH ALLIGNMENT_32BIT
                2bytes (16bit architecture) -> #define TARGET_ARCH ALLIGNMENT_16BIT 
        */
        currentEndAddress = (currentEndAddress + (TARGET_ARCH - 1)) & TARGET_ARCH_MASK;
        MemControl.CurrAddr = (uint8_t*)currentEndAddress;
        printf("Data allocated.\n\r");
    }

    return returnVal;
}