/*******************************************************************************/
/**
\file       Uart_Types.h
\brief      
   \~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   \version       1.1
   \author        
   \description   
   \date          
*/

#ifndef UART_TYPES
#define UART_TYPES

/** Standard Types */
#include "Std_Types.h"

typedef enum
{
  UART_ERROR_OVERRUN,
  UART_ERROR_FRAMING,
  UART_ERROR_PARITY,
} UartErrorType;

typedef void (*UartNotification)(void);
typedef void (*UartErrorNotification)(UartErrorType Error);

/* UartStatusType example */
typedef struct
{
  uint8_t ChannelId;
  uint8_t Counter;
  uint8_t TriggerCounter;
  UartNotification tx_callback;
  UartNotification rx_callback;
  UartErrorNotification error_callback;
} UartStatusType;

/*============================================================================*/
#endif /* UART_TYPES */