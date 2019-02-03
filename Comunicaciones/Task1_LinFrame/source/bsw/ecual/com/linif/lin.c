#include "lin.h"
#include "uart.h"
#include     "pmc.h"
#include     "board.h"
#include     "pio.h"

void Lin_Init (uint16_t LinBaudrate)
{
	PMC_EnablePeripheral(BASE_ID);
	
	/* Reset & disable receiver and transmitter, disable interrupts */
	// UART_Configure(BASE_UART, (UART_MR_PAR_NO | UART_MR_CHMODE_LOCAL_LOOPBACK), 115200, BOARD_MCK, vfnSerialCtrl_Transfer);
	UART_Configure(BASE_UART, (UART_MR_PAR_NO | UART_MR_CHMODE_LOCAL_LOOPBACK), LinBaudrate, BOARD_MCK);

	/* Clear pending IRQs and Set priority of IRQs */
	NVIC_ClearPendingIRQ(BASE_IRQ);
	NVIC_SetPriority(BASE_IRQ, 1);

	/* Enables the UART to transfer and receive data. */
	UART_SetTransmitterEnabled (BASE_UART , 1);
	UART_SetReceiverEnabled (BASE_UART , 1);

	// UART_EnableIt(BASE_UART, UART_IER_RXRDY);
	/* Enable interrupt  */
	// NVIC_EnableIRQ(BASE_IRQ);	
}

void Lin_SendFrame (uint8_t LinPid);

void Lin_Isr(void);
