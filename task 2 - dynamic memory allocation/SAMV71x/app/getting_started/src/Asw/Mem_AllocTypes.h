#ifndef MEM_ALLOCTYPES        /*prevent duplicated includes*/ 
#define MEM_ALLOCTYPES    


#include "Std_Types.h"

typedef uint8_t* MemReturnType;
typedef uint16_t MemSizeType;

extern uint8_t _heap_mem_start;
extern uint8_t _heap_mem_end;

typedef struct MemHandlerType
{
    uint8_t* MemStart;
    uint8_t* MemEnd;
    uint8_t* CurrAddr;
    const uint8_t* FreeBytes;
} MemHandlerType;

#endif  /* STD_TYPES_H */ 