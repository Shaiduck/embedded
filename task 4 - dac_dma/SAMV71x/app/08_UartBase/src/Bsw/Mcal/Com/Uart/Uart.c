/*******************************************************************************/
/**
\file       
\brief      
   \~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   \version       1.0
   \author        
   \description   
   \date          
*/

/** Scheduler function prototypes definitions */
#include "Uart.h"
#include "MemAlloc.h"
#include "uartdrv.h"
#include "pmc.h"
/*****************************************************************************************************
* Defines - 
*****************************************************************************************************/

#define UART_CHANNEL_UNDEF (255)

#define UART_CH0  3 
#define UART_CH1  4
#define UART_CH2  0
#define UART_CH3  2
#define UART_CH4  1

#define CHANNEL0 0
#define CHANNEL1 1
#define CHANNEL2 2
#define CHANNEL3 3
#define CHANNEL4 4


/*****************************************************************************************************
* Definition of  VARIABLEs - 
*****************************************************************************************************/

/* Uart Status Structure Example */
UartStatusType *UartStatus;

/*****************************************************************************************************
* Definition of module wide (CONST-) CONSTANTs 
*****************************************************************************************************/
/* Array of Uart Register Base Address */
static const uint8_t PhysicalIds[] = {UART_CH0, UART_CH1, UART_CH2, UART_CH3, UART_CH4};

static const Uart * UartRegAddr[]={ UART2, UART4, UART3, UART0, UART1 };

static const uint32_t UartIDs[] = { ID_UART2, ID_UART4, ID_UART3, ID_UART0, ID_UART1 };

static const uint8_t IRQn[]={ UART2_IRQn, UART4_IRQn, UART3_IRQn, 0, 0};

uint8_t  *		pu8SerialCtrl_ReadTxDataPtr;
uint8_t 		u8SerialCtrl_TxData[] = {"holii"};
uint16_t u16SerialCtrl_TxLength;

uint8_t uartEnabled = 0;
/*****************************************************************************************************
* Code of module wide Private FUNCTIONS
*****************************************************************************************************/

uint8_t Uart_GetLogChannel(uint8_t PhyChannel)
{

	uint8_t LogicalChannel = UART_CHANNEL_UNDEF; 
	uint8_t LocChIdx = 100; /* LocChIdx represent the logical channel */

	/* UART_CFG_CHANNELS represents the number of configured channels from configuration structure */
	for (LocChIdx = 0; LocChIdx < UART_CFG_CHANNELS; LocChIdx++)
	{
		if (PhysicalIds[LocChIdx] == PhyChannel)
		{
			LogicalChannel = LocChIdx; 
			break;
		}
	}
	return (LogicalChannel);
}

/*****************************************************************************************************
* Code of module wide Public FUNCTIONS
*****************************************************************************************************/
void Uart_Init(const UartConfigType* Config)
{
	//initializes the UART module
	Uart* LocUartReg;
	uint32_t Parity = 0;
	uint32_t Mode = 0;
	uint32_t Baudrate = 0;
	uint32_t ClockSource = 0;
	uint32_t Interrupt = 0;
	uint8_t LocChIdx = 0;
	uint8_t physicalUART = 100;

	UartStatus = (UartStatusType*)MemAlloc(sizeof(UartStatusType) * Config->UartNumberOfChannels);

	for (LocChIdx = 0; LocChIdx < Config->UartNumberOfChannels; LocChIdx++)
	{

		physicalUART = Uart_GetLogChannel(Config->UartChannel[LocChIdx].ChannelId);
		if (physicalUART == 100)
		{
			return;
		}


		LocUartReg = (Uart*)UartRegAddr[physicalUART];
		UartStatus[LocChIdx].ChannelId = Config->UartChannel[LocChIdx].ChannelId;
		UartStatus[LocChIdx].UartChannel = &(Config->UartChannel[LocChIdx]);

		PMC_EnablePeripheral(UartIDs[LocChIdx]);

		switch(Config->UartChannel[LocChIdx].Parity)
		{
			case (UART_CFG_PARITY_NO):
				Parity = UART_MR_PAR_NO;
				break;
			case (UART_CFG_PARITY_EVEN):
				Parity = UART_MR_PAR_EVEN;
				break;
			case (UART_CFG_PARITY_MARK):
				Parity = UART_MR_PAR_MARK;
				break;
			case (UART_CFG_PARITY_ODD):
				Parity = UART_MR_PAR_ODD;
				break;
			case (UART_CFG_PARITY_SPACE):
				Parity = UART_MR_PAR_SPACE;
				break;
		}

		switch(Config->UartChannel[LocChIdx].Mode)
		{
			case (UART_CFG_MODE_AUTO):
				Mode = UART_MR_CHMODE_AUTOMATIC;
				break;
			case (UART_CFG_MODE_NORMAL):
				Mode = UART_MR_CHMODE_NORMAL;
				break;
			case (UART_CFG_MODE_LOOPBACK):
				Mode = UART_MR_CHMODE_LOCAL_LOOPBACK;
				break;
		}

		Baudrate = Config->UartChannel[LocChIdx].Baudrate;
		if (Config->ClkSrc == 0)
		{
			ClockSource = BOARD_MCK;
		}
		else
		{
			ClockSource = Config->ClkSrc;
		}

		UART_Configure(LocUartReg, (Parity | Mode), Baudrate, ClockSource);

		NVIC_ClearPendingIRQ(IRQn[physicalUART]);
		NVIC_SetPriority(IRQn[physicalUART], 1);

		Interrupt = Config->UartChannel[LocChIdx].IsrEn;

		UART_SetTransmitterEnabled(LocUartReg, Interrupt);
		UART_SetReceiverEnabled(LocUartReg, Interrupt);
		
		UART_EnableIt(LocUartReg, Interrupt);
		// NVIC_EnableIRQ(IRQn[physicalUART]);

	}
}

Std_ReturnType Uart_SetBaudRate(uint8_t Channel, uint32_t Baudrate)
{
	//Sets the requested baudrate to the addressed UART channel
	Std_ReturnType result = E_NOT_OK;
	Uart* LocUartReg;
	uint8_t physicalUART = 100;

	physicalUART = Uart_GetLogChannel(UartStatus[Channel].UartChannel->ChannelId);
	if (physicalUART == 100)
	{
		return E_NOT_OK;
	}


	LocUartReg = (Uart*)UartRegAddr[physicalUART];

	/* Configure baudrate*/
	if (LocUartReg != NULL)
	{
		uint32_t Baudrate = UartStatus[Channel].UartChannel->Baudrate;
		uint32_t SrcClk = UartStatus[Channel].SrcClk;

		UART_SetBaudrate(LocUartReg, Baudrate, SrcClk);
		result = E_OK;
	}	
	else
	{
		result = E_NOT_OK;
	}

	return result;
}

void Uart_SetTxEnable(uint8_t Channel, uint32_t Enable)
{
	//ENables or disables the transmitter of the UART module
	Uart* LocUartReg;
	uint8_t physicalUART = 100;

	physicalUART = Uart_GetLogChannel(UartStatus[Channel].UartChannel->ChannelId);

	LocUartReg = (Uart*)UartRegAddr[physicalUART];
	if (physicalUART == 100)
	{
		return;
	}


	if (Enable == 1) 
	{
		printf("Enabling TX\n");
	} else if (Enable == 0) 
	{
		printf("Disabling TX\n");
	}
	
	UART_SetTransmitterEnabled(LocUartReg, Enable);
}

void Uart_SetRxEnable(uint8_t Channel, uint32_t Enable)
{
	//Enables or disables the receiver of the UART module
	Uart* LocUartReg;
	uint8_t physicalUART = 100;

	physicalUART = Uart_GetLogChannel(UartStatus[Channel].UartChannel->ChannelId);
	if (physicalUART == 100)
	{
		return;
	}


	LocUartReg = (Uart*)UartRegAddr[physicalUART];

	if (Enable == 1) {
		printf("Enabling RX\n");
	} else if (Enable == 0) {
		printf("Enabling RX\n");
	}
	UART_SetReceiverEnabled(LocUartReg, Enable);
}

Std_ReturnType Uart_SendByte(uint8_t Channel, uint8_t Byte)
{
	Std_ReturnType result = E_NOT_OK;
	//Sends one packet of data through the specified UART module
	Uart* LocUartReg;
	uint8_t physicalUART = 100;

	physicalUART = Uart_GetLogChannel(UartStatus[Channel].UartChannel->ChannelId);
	if (physicalUART == 100)
	{
		return E_NOT_OK;
	}

	LocUartReg = (Uart*)UartRegAddr[physicalUART];

	if (LocUartReg != NULL)
	{
		UART_PutChar(LocUartReg, Byte);
		UartStatus[Channel].Counter++;
		result = E_OK;
	}
	else
	{
		result = E_NOT_OK;
	}
	return result;
}

Std_ReturnType Uart_SendBuffer(uint8_t Channel, uint8_t* Buffer, uint16_t Length)
{
	//sends a packet of data through the specified UART channel
	uint8_t *Data = Buffer;
	uint32_t Len = 0;
	Std_ReturnType result = E_NOT_OK;

	for(Len = 0; Len < Length; Len++ ) {
		result = Uart_SendByte(Channel, *Data);
		Data++;
		if (result != E_OK)
			break;
	}
	return result;
}

uint8_t Uart_GetByte(uint8_t Channel)
{
	//reads and returns a character from the UART module
	Uart* LocUartReg;
	uint8_t physicalUART = 100;

	physicalUART = Uart_GetLogChannel(UartStatus[Channel].UartChannel->ChannelId);
	if (physicalUART == 100)
	{
		return E_NOT_OK;
	}

	LocUartReg = (Uart*)UartRegAddr[physicalUART];

	//this blocks the execution
	while (!LocUartReg->UART_SR & UART_SR_RXRDY);
	return LocUartReg->UART_RHR;
}

uint32_t Uart_GetStatus(uint8_t Channel)
{
	//reads and returns the current status of the addressed UART module
	Uart* LocUartReg;
	uint8_t physicalUART = 100;
	physicalUART = Uart_GetLogChannel(UartStatus[Channel].UartChannel->ChannelId);

	if (physicalUART == 100)
	{
		return E_NOT_OK;
	}

	LocUartReg = (Uart*)UartRegAddr[physicalUART];

	return (UART_GetChar(LocUartReg));
}

void Uart_EnableInt(uint8_t Channel, uint32_t IntMode, uint8_t Enable)
{
	Uart* LocUartReg;
	uint8_t physicalUART = 100;

	physicalUART = Uart_GetLogChannel(UartStatus[Channel].UartChannel->ChannelId);

	if (physicalUART == 100)
	{
		return;
	}

	LocUartReg = (Uart*)UartRegAddr[physicalUART];
	
	uint32_t interrupt;

	if (Enable == 1)
	{
		if (IntMode == UART_CFG_INT_RXRDY)
		{
			interrupt = UART_IER_RXRDY;
		}
		else if (IntMode == UART_CFG_INT_TXRDY)
		{
			interrupt = UART_IER_TXRDY;
		}
		
		UART_EnableIt(LocUartReg, interrupt);
		NVIC_EnableIRQ(IRQn[physicalUART]);

	}
	else if (Enable == 0)
	{
		if (IntMode == UART_CFG_INT_RXRDY)
		{
			interrupt = UART_IDR_RXRDY;
		}
		else if (IntMode == UART_CFG_INT_TXRDY)
		{
			interrupt = UART_IDR_TXRDY;
		}
		UART_DisableIt(LocUartReg, interrupt);
		NVIC_DisableIRQ(IRQn[physicalUART]);
	}
	
	uartEnabled = Enable;

}

void Uart_Send(uint8_t Channel)
{
	pu8SerialCtrl_ReadTxDataPtr = &u8SerialCtrl_TxData[0];
    u16SerialCtrl_TxLength = sizeof(u8SerialCtrl_TxData);
	Uart_SendBuffer(Channel, pu8SerialCtrl_ReadTxDataPtr, u16SerialCtrl_TxLength);
}


/*****************************************************************************************************
* Code of module wide Interrupt Handler FUNCTIONS
*****************************************************************************************************/

void Uart_Isr( uint8_t Channel )
{
	uint8_t position = 100;
	uint8_t index = 0;
	for (index = 0; index < UART_CFG_CHANNELS; index++)
	{
		if (UartStatus[index].UartChannel != NULL)
		{
			if (Channel == UartStatus[index].UartChannel->ChannelId)
			{
				position = index;
				break;
			}
		}
	}

	if (position == 100)
	{
		return;
	}

	printf("interruption in channel #%u\n", UartStatus[index].UartChannel->ChannelId);

	uint8_t Interrupt = UartStatus[position].UartChannel->IsrEn;
	switch (Interrupt)
	{
		case (UART_CFG_INT_TXRDY):
		{
			if (UartStatus[position].UartChannel->TxNotification != NULL)
			{
				UartStatus[position].UartChannel->TxNotification();
			}
		}
			break;
		case (UART_CFG_INT_RXRDY):
		{
			if (UartStatus[position].UartChannel->RxNotification != NULL)
			{
				UartStatus[position].UartChannel->RxNotification();
			}
		}
			break;
		case (UART_CFG_INT_OVR_ERROR):
		{
			if (UartStatus[position].UartChannel->ErrorNotification != NULL)
			{
				UartStatus[position].UartChannel->ErrorNotification(UART_ERROR_OVERRUN);
			}
		}
			break;
		case (UART_CFG_INT_FRAME_ERROR):
		{
			if (UartStatus[position].UartChannel->ErrorNotification != NULL)
			{
				UartStatus[position].UartChannel->ErrorNotification(UART_ERROR_FRAMING);
			}
		}
			break;
		case (UART_CFG_INT_PAR_ERROR):
		{
			if (UartStatus[position].UartChannel->ErrorNotification != NULL)
			{
				UartStatus[position].UartChannel->ErrorNotification(UART_ERROR_PARITY);
			}
		}
			break;
	}
	UartStatus[position].TriggerCounter++;
}

uint8_t Uart_IsEnabled()
{
	return uartEnabled;
}

void UART0_Handler(void)
{
	Uart_Isr(CHANNEL0);
}


void UART1_Handler(void)
{
	Uart_Isr(CHANNEL1);
}


void UART2_Handler(void)
{
	Uart_Isr(CHANNEL2);
}


void UART3_Handler(void)
{
	Uart_Isr(CHANNEL3);
}


void UART4_Handler(void)
{
	Uart_Isr(CHANNEL4);
}
