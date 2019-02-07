#include "lin.h"
#include "uart.h"
#include     "pmc.h"
#include     "board.h"
#include     "pio.h"

void Lin_StateHandler()
{
	switch(currentState)
	{
		case(IDLE):
			UART_DisableIt(BASE_UART, UART_IDR_RXRDY);
			UART_DisableIt(BASE_UART, UART_IDR_TXRDY);
		break;
		case (SEND_BREAK):
			UART_EnableIt(BASE_UART, UART_IER_TXRDY);
			/*send break*/
			UART_SendBuffer(BASE_UART, 0x00, 1);
			currentState = SEND_SYNC;
		break;
		case (SEND_SYNC):
			UART_SendBuffer(BASE_UART, 0X55, 1);
			currentState = SEND_PID;
		break;
		case (SEND_PID):
			Lin_CalculateParity(linPid); //will fail. Need to modify
			UART_SendBuffer(BASE_UART, linPid, 1);
			currentState = SEND_RESPONSE;
		break;
		case (SEND_RESPONSE):
		  /* 
			In your project, the number of data will be sent according to the data lenght from the PDU information, therefore a sub-state machine should be considered, or to handle here each byte sent. e.g.
			If ( LinResponseType == MASTER_RESPONSE)
			{
				If (DataSentCtrlCounter < SduDataLength )
				{
					Uart_SendByte(0,SduData[DataSentCtrlCounter]);
					DataSentCtrlCounter++;
					-> Need to calculate Checksum to be sent
				}
				else
				{
					Uart_SendByte(0,LinChecksum);
					DataSentCtrlCounter = 0;
					LinState = IDLE;
				}
			}
		  */
			currentState = IDLE;
		break;
		default:
			//never reached
		break;
	}
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

	/* Enable interrupt  */
	NVIC_EnableIRQ(BASE_IRQ);	
}

void Lin_SendFrame (uint8_t LinPid)
{
	if (currentState == IDLE)
	{
		linPid = LinPid;
	  /*
		To consider in the Lin project. Prepare the data to be handled while the Lin frame is in progress
		in addition to back up the Lin Pid, you will need to back up the ResponseType, Sdu, etc.
		for (uint8_t SduIdx = 0; SduIdx < SduDataLength; SduIdx++)
		{
			SduData[SduIdx] = LinSduPtr[SduIdx]; It is important to backup the Sdu to avoid data corrupted by higher layers. Remember, SduPtr contains a data address whose data is not under our control.
		}
		DataSentCtrlCounter = 0; -> Will handle the data to be sent if a master response, or to store the data in the corresponding order if a slave response
		
	  */
	 	currentState = SEND_BREAK;
		Lin_StateHandler();
	}
	else 
	{
		/*Command not accepted*/
	}
}

void Lin_CalculateParity(LinSync* sync)
{
	uint8_t P0;
	uint8_t P1;

	P0 = ((sync->LinID >> 0) & 1) & ((sync->LinID >> 1) & 1) & ((sync->LinID >> 2) & 1) & ((sync->LinID >> 4) & 1);
	P1 = ((sync->LinID >> 1) & 1) & ((sync->LinID >> 3) & 1) & ((sync->LinID >> 4) & 1) & ((sync->LinID >> 5) & 1);
	
	P1 = ~P1;
	 
	sync->LinID = ((sync->LinID >> 6 ) & 0) | ((P0 >> 6) & 0);
	sync->LinID = ((sync->LinID >> 7 ) & 0) | ((P1 >> 7) & 0);
}

void Lin_Isr(void)
{
	Lin_StateHandler();
}