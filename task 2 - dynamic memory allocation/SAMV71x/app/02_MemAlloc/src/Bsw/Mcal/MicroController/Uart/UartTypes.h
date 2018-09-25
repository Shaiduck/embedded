#ifndef UARTTYPES_H        /*prevent duplicated includes*/
#define UARTTYPES_H

typedef enum UartErrorType
{
    UART_ERROR_OVERRUN = 0,
    UART_REROR_FRAMING = 1,
    UART_ERROR_PARITY = 2,
} UartErrorType;

typedef enum UartMaskDefitions
{
    UART_MASK_RXRDY     =    1,
    UART_MASK_TXRDY     =    2,
    UART_MASK_OVRE      =    32,
    UART_MASK_FRAME     =    64,
    UART_MASK_PARE      =    128,
    UART_MASK_TXEMPTY   =    512,
} UartMaskDefinitions;
#endif
