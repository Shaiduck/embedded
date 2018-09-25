#ifndef MEM_ALLOCTYPES        /*prevent duplicated includes*/ 
#define MEM_ALLOCTYPES    


#include "Std_Types.h"

typedef void* MemReturnType;
typedef uint16_t MemSizeType;

extern uint32_t _heap_mem_start;
extern uint32_t _heap_mem_end;
extern uint32_t _heap_mem_size;


typedef struct MemHandlerType
{
    uint8_t* MemStart;
    uint8_t* MemEnd;
    uint8_t* CurrAddr;
    uint32_t FreeBytes;
} MemHandlerType;

#endif  /* STD_TYPES_H */ 