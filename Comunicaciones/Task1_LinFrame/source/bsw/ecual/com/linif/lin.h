#ifndef _LIN_
#define _LIN_

#define BASE_UART       	UART4
#define BASE_ID         	ID_UART4
#define BASE_IRQ        	UART4_IRQn
/** Pins description corresponding to Rxd,Txd, (UART pins) */
#define UART_PINS        	{PINS_UART4}

#define SERIAL_TX_MAX_SIZE  64
#define SERIAL_RX_MAX_SIZE	64

//    The sequence shall be as follows (since no response shall be provided for this task)

//    IDLE -> SEND_BREAK -> SEND_SYNC -> SEND_PID -> IDLE

//    IDLE: No activity
//    SEND_BREAK: Send break process is about to start or in progress
//    SEND_SYNC: Send sync process is about to start or in progress
//    SEND_PID: Send pid process is about to start or in progress

//    Note: Lin_SendFrame will start the state machine by changing the state to SEND_BREAK as long as there is no a frame transmission/reception in progress.
typedef enum
{
    IDLE,
    SEND_BREAK,
    SEND_SYNC,
    SEND_PID,
    SEND_RESPONSE
} LinStateType;

typedef struct 
{
    uint16_t LinBreak;
    uint8_t LinByte;
    uint8_t LinID;
} LinSync;

typedef struct
{
    uint8_t LinMessage;
    uint8_t LinChecksum;
} LinMessage;

typedef struct 
{
    LinSync synch;
    LinMessage message
} LinFrame;

uint16_t linBaudRate = 0;

LinStateType currentState = IDLE;


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
#endif /* #ifndef LIN_H */
