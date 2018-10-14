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


/*****************************************************************************************************
* Defines - 
*****************************************************************************************************/

#define UART_CHANNEL_UNDEF (255)

#define UART_CH0  (0) 
#define UART_CH1  (1)
#define UART_CH2  (2)
#define UART_CH3  (3)
#define UART_CH4  (4)

/*****************************************************************************************************
* Definition of  VARIABLEs - 
*****************************************************************************************************/

/* Uart Status Structure Example */
UartStatusType *UartStatus;

/*****************************************************************************************************
* Definition of module wide (CONST-) CONSTANTs 
*****************************************************************************************************/
/* Array of Uart Register Base Address */
static const Uart * UartRegAddr[]={ UART0, UART1, UART2, UART3, UART4 };

const UartConfigType* currentConfig;


/*****************************************************************************************************
* Code of module wide Private FUNCTIONS
*****************************************************************************************************/

uint8_t Uart_GetLogChannel(uint8_t PhyChannel)
{
	uint8_t LogicalChannel = UART_CHANNEL_UNDEF; 
	uint8_t LocChIdx = 0; /* LocChIdx represent the logical channel */
	/* UART_CFG_CHANNELS represents the number of configured channels from configuration structure */
	do
	{
		if (UartStatus[LocChIdx].ChannelId == PhyChannel)
		{
			LogicalChannel = LocChIdx; 
		}
		LocChIdx++;
	}while( (UartStatus[LocChIdx-1].ChannelId != PhyChannel) && (LocChIdx < UART_CFG_CHANNELS) );
	return (LogicalChannel);
}

/*****************************************************************************************************
* Code of module wide Public FUNCTIONS
*****************************************************************************************************/

// void Uart_Init(  const uint8_t * ChannelConfigure )
// {
// 	const Uart * LocUartReg;
// 	uint8_t LocChIdx = 0; /* LocChIdx represent the logical channel */

// 	/* Memory allocation for all Channel Status example */
// 	/* UART_CFG_CHANNELS represents the number of configured channels from configuration structure */
// 	UartStatus = (UartStatusType*) MemAlloc( sizeof(UartStatusType) * UART_CFG_CHANNELS  );  

// 	for (LocChIdx = 0; LocChIdx < UART_CFG_CHANNELS; LocChIdx++)
// 	{
// 		/* Point to register address based of physical channel */
// 		LocUartReg = UartRegAddr[ChannelConfigure[LocChIdx]];
// 		/* Access to register for the configured channel with LocUartReg */
// 		/* Access to channel status structure with LocChIdx */
// 		UartStatus[LocChIdx].ChannelId = ChannelConfigure[LocChIdx];    
// 	}
// }

void Uart_Init(const UartConfigType* Config)
{
	currentConfig = Config;
	Uart* LocUartReg;
	uint8_t LocChIdx = 0;

	UartStatus = (UartStatusType*)MemAlloc(sizeof(UartStatusType) * Config->UartNumberOfChannels);

	for (LocChIdx = 0; LocChIdx < Config->UartNumberOfChannels; LocChIdx++)
	{
		LocUartReg = (Uart*)UartRegAddr[Config->UartChannel[LocChIdx].ChannelId];

		UartStatus[LocChIdx].ChannelId = Config->UartChannel[LocChIdx].ChannelId;

		LocUartReg->UART_CR = UART_CR_RSTRX | UART_CR_RSTTX
		| UART_CR_RXDIS | UART_CR_TXDIS | UART_CR_RSTSTA;

		LocUartReg->UART_IDR = 0xFFFFFFFF;

		/* Configure mode*/
		LocUartReg->UART_MR = Config->UartChannel[LocChIdx].Mode;

		if (Uart_SetBaudRate(LocChIdx, Config->UartChannel[LocChIdx].Baudrate == E_OK))
		{
			//nice
			LocUartReg->UART_CR = UART_CR_TXEN | UART_CR_RXEN;
		}
		else
		{
			printf("can't init UART\n");
		}
	}
	//initializes the UART module
}

Std_ReturnType Uart_SetBaudRate(uint8_t Channel, uint32_t Baudrate)
{
	Std_ReturnType result = E_NOT_OK;
	Uart* LocUartReg;
	
	LocUartReg = (Uart*)UartRegAddr[UartStatus[Channel].ChannelId];

	/* Configure baudrate*/
	if (LocUartReg != NULL)
	{
		LocUartReg->UART_BRGR = (currentConfig->ClkSrc / Baudrate) / 16;
		result = E_OK;
	}	
	else
	{
		result = E_NOT_OK;
	}
	//Sets the requested baudrate to the addressed UART channel

	return result;
}

void Uart_SetTxEnable(uint8_t Channel, uint32_t Enable)
{
	//ENables or disables the transmitter of the UART module
	Uart* LocUartReg;

	LocUartReg = (Uart*)UartRegAddr[UartStatus[Channel].ChannelId];

	if (Enable == 1) {
		LocUartReg->UART_CR = UART_CR_TXEN;
	} else if (Enable == 0) {
		LocUartReg->UART_CR = UART_CR_TXDIS;
	}
}

void Uart_SetRxEnable(uint8_t Channel, uint32_t Enable)
{
	//Enables or disables the receiver of the UART module
	Uart* LocUartReg;

	LocUartReg = (Uart*)UartRegAddr[UartStatus[Channel].ChannelId];

	if (Enable == 1) {
		LocUartReg->UART_CR = UART_CR_RXEN;
	} else if (Enable == 0) {
		LocUartReg->UART_CR = UART_CR_RXDIS;
	}
}

Std_ReturnType Uart_SendByte(uint8_t Channel, uint8_t Byte)
{
	Std_ReturnType result = E_NOT_OK;
	//Sends one packet of data through the specified UART module
	Uart* LocUartReg;

	LocUartReg = (Uart*)UartRegAddr[UartStatus[Channel].ChannelId];
	if (LocUartReg != NULL)
	{
		LocUartReg->UART_THR = Byte;

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

	LocUartReg = (Uart*)UartRegAddr[UartStatus[Channel].ChannelId];

	//this blocks the execution
	while (!LocUartReg->UART_SR & UART_SR_RXRDY);
	return LocUartReg->UART_RHR;
}

uint32_t Uart_GetStatus(uint8_t Channel)
{
	//reads and returns the current status of the addressed UART module
	Uart* LocUartReg;

	LocUartReg = (Uart*)UartRegAddr[UartStatus[Channel].ChannelId];
	return LocUartReg->UART_SR;
}

void Uart_EnableInt(uint8_t Channel, uint32_t IntMode, uint8_t Enable)
{
	Uart* LocUartReg;

	LocUartReg = (Uart*)UartRegAddr[UartStatus[Channel].ChannelId];
	LocUartReg->UART_IER = currentConfig->UartChannel[Channel].Mode;
}

void Uart_Send(uint8_t Channel)
{
	const Uart * LocUartReg = UartRegAddr[UartStatus[Channel].ChannelId];
	/* Example Code */
	UartStatus[Channel].Counter++;
}


/*****************************************************************************************************
* Code of module wide Interrupt Handler FUNCTIONS
*****************************************************************************************************/

void Uart_Isr( uint8_t Channel )
{
  const Uart * LocUartReg = UartRegAddr[Channel];
  uint8_t LocUartLogicChannel = Uart_GetLogChannel(Channel);
  
  /* Example Code */
  /* UART_CFG_CHANNELS represents the number of configured channels from configuration structure */
  if (LocUartLogicChannel<UART_CFG_CHANNELS)
    UartStatus[LocUartLogicChannel].TriggerCounter++;
}


void UART0_Handler(void)
{
	Uart_Isr(UART_CH0);
}


void UART1_Handler(void)
{
	Uart_Isr(UART_CH1);
}


void UART2_Handler(void)
{
	Uart_Isr(UART_CH2);
}


void UART3_Handler(void)
{
	Uart_Isr(UART_CH3);
}


void UART4_Handler(void)
{
	Uart_Isr(UART_CH4);
}