/*******************************************************************************/
/**
\file       Lin_Types.h
\brief      
   \~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   \version       1.1
   \author        
   \description   
   \date          
*/

#ifndef LIN_TYPES
#define LIN_TYPES

/** Standard Types */
#include "Std_Types.h"
#include "Uart_Types.h"

typedef uint8_t LinFramePidType;

typedef enum
{
  LIN_ENHANCED_CS,
  LIN_CLASSIC_CS,
} LinFrameCsModelType;

typedef enum
{
  LIN_MASTER_RESPONSE,
  LIN_SLAVE_RESPONSE,
} LinFrameResponseType;

typedef uint8_t LinFrameDlType;

typedef struct
{
  LinFramePidType Pid;
  LinFrameCsModelType Cs;
  LinFrameResponseType Drc;
  LinFrameDlType Dl;
  uint8_t *SduPtr;
} LinPduType;

/*============================================================================*/
#endif /* LIN_TYPES */