#include "lin.h"
#include "uart.h"
#include     "pmc.h"
#include     "board.h"
#include     "pio.h"

void Lin_Isr()
{
	//do something awesome
}

void Lin_Init (uint16_t LinBaudrate)
{
	PMC_EnablePeripheral(BASE_ID);
	
	/* Reset & disable receiver and transmitter, disable interrupts */
	// UART_Configure(BASE_UART, (UART_MR_PAR_NO | UART_MR_CHMODE_LOCAL_LOOPBACK), 115200, BOARD_MCK, vfnSerialCtrl_Transfer);
	linBaudRate = LinBaudRate;
	UART_Configure(BASE_UART, (UART_MR_PAR_NO | UART_MR_CHMODE_LOCAL_LOOPBACK), LinBaudrate, BOARD_MCK);

	/* Clear pending IRQs and Set priority of IRQs */
	NVIC_ClearPendingIRQ(BASE_IRQ);
	NVIC_SetPriority(BASE_IRQ, 1);

	/* Enables the UART to transfer and receive data. */
	UART_SetTransmitterEnabled (BASE_UART , 1);
	UART_SetReceiverEnabled (BASE_UART , 1);

	UART_SetIsr(Lin_Isr);
	UART_EnableIt(BASE_UART, UART_IER_RXRDY);
	UART_EnableIt(BASE_UART, UART_IER_TXRDY);

	/* Enable interrupt  */
	NVIC_EnableIRQ(BASE_IRQ);	
}

void Lin_SendFrame (uint8_t LinPid)
{
	switch(currentState)
	{
		case(IDLE):
		break;
		case (SEND_BREAK):
		break;
		case (SEND_SYNC):
		break;
		case (SEND_PID):
		break;
		case (SEND_RESPONSE):
		break;
	}
}

void Lin_CalculateParity(LinSync* sync)
{
	uint8_t P0;
	uint8_t P1;

	P0 = ((sync->LinID >> 0) & 1) & ((sync->LinID >> 1) & 1) & ((sync->LinID >> 2) & 1) & ((sync->LinID >> 4) & 1);
	P1 = ((sync->LinID >> 1) & 1) & ((sync->LinID >> 3) & 1) & ((sync->LinID >> 4) & 1) & ((sync->LinID >> 5) & 1);
	 
	sync->LinID = ((sync->LinID >> 6 ) & 0) | ((P0 >> 6) & 0);
	sync->LinID = ((sync->LinID >> 7 ) & 0) | ((P1 >> 7) & 0);
}