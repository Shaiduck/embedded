/*******************************************************************************/
/**
\file       Uart_Types.h
\brief      
   \~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   \version       1.0
   \author        
   \description   
   \date          
*/

#ifndef UART_TYPES
#define UART_TYPES

  /** Standard Types */
  #include "Std_Types.h"
  
  /* UartStatusType example */
  typedef struct
  {
    uint8_t ChannelId;
    uint8_t Counter;
    uint8_t TriggerCounter;
  }UartStatusType;

  typedef enum UartErrorType
  {
    UART_ERROR_OVERRUN = 0,
    UART_ERROR_FRAMING = 1,
    UART_ERROR_PARITY = 2
  } UartErrorType;

  typedef enum UartMaskDefinitions
  {
    UART_MASK_RXRDY = 1,
    UART_MASK_TXRDY = 2,
    UART_MASK_OVRE = 32,
    UART_MASK_FRAME = 64,
    UART_MASK_PARE = 128,
    UART_MASK_TXEMPTY = 512
  } UartMaskDefinitions;

  typedef void (*UartNotificationType)(void);

  typedef void (*UartErrorNotification)(UartErrorType Error);
  

/*============================================================================*/
#endif /* UART_TYPES */
