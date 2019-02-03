#ifndef _LIN_
#define _LIN_

// - This function will configure the lower layer UART driver
// - Baudrate will as per LinBaudrate parameter
// - Interrupts shall be configured for each data byte to be transmitted or received
// - This function shall provide to the lower layer a function callback (Lin_Isr) to be invoked at any of the RX or TX UART interrupts
void Lin_Init (uint16_t LinBaudrate);

// - This function will send a predefined header as per the LIN protocol with the rate define in the Lin_Init function.
// - This function shall be asynchronous, i.e. it will trigger the "send command" and will continue its operation without waiting for the header to be completely sent over the bus.
// - The header shall be composed in order of:
//    - 1. Break = (from 10 to 13 bit times) ideally >= 13 bit time
//    - 2. Synch = 0x55
//    - 3. ID = LinPid
void Lin_SendFrame (uint8_t LinPid);

// - UART TX/RX interrupts:
//    - will invoke this function
//    - will serve as input transitions to manage the LIN state machine (transitions and actions)
void Lin_Isr(void);

typedef enum
{
    IDLE,
    SEND_BREAK,
    SEND_SYNC,
    SEND_PID,
    SEND_RESPONSE
} LinStateType;

#endif /* #ifndef LIN_H */
