#include "MemAlloc.h"

/* Private Data */

MemHandlerType MemHandler;

extern uint32_t HEAP_LLD;
extern uint32_t _smyheap;
extern uint32_t _emyheap;


void MemAllocInit ( void )
{
  MemHandler.memStart = (Mem_Uint8PtrType)&HEAP_LLD;   
  MemHandler.memEnd = (Mem_Uint8PtrType)&_emyheap;
  MemHandler.freeBytes = MemHandler.memEnd - MemHandler.memStart; 
  MemHandler.currAddr = MemHandler.memStart;
}


Mem_ReturnType MemAlloc( uint16_t size )
{
   Mem_ReturnType LocMemReturn = (Mem_ReturnType)0;

   if (size < MemHandler.freeBytes)
   {
     LocMemReturn = MemHandler.currAddr;
     MemHandler.currAddr += size;
     if ( ((uint32_t)MemHandler.currAddr % 4) )
     {
       MemHandler.currAddr = (Mem_Uint8PtrType)(((uint32_t)MemHandler.currAddr + 3) & (uint32_t)~3);
     }
     MemHandler.freeBytes = MemHandler.memEnd - MemHandler.currAddr;
   }
   return(LocMemReturn);
}

