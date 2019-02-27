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

#define UART_CH0 (0)
#define UART_CH1 (1)
#define UART_CH2 (2)
#define UART_CH3 (3)
#define UART_CH4 (4)

/*****************************************************************************************************
* Definition of  VARIABLEs - 
*****************************************************************************************************/

/* Uart Status Structure Example */
UartStatusType *UartStatus;
uint8_t NumberOfChannels;

uint32_t intBUglob = 0;

/*****************************************************************************************************
* Definition of module wide (CONST-) CONSTANTs 
*****************************************************************************************************/
/* Array of Uart Register Base Address */

static Uart *UartRegAddr[] = {UART0, UART1, UART2, UART3, UART4};
static uint8_t UartIRQS[] = {UART0_IRQn, UART1_IRQn, UART2_IRQn, UART3_IRQn, UART4_IRQn};
static uint8_t PeriID[] = {ID_UART0, ID_UART1, ID_UART2, ID_UART3, ID_UART4};

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
  } while ((UartStatus[LocChIdx - 1].ChannelId != PhyChannel) && (LocChIdx < NumberOfChannels));
  return (LogicalChannel);
}

/*****************************************************************************************************
* Code of module wide Public FUNCTIONS
*****************************************************************************************************/

/**
 * \brief Initialize the UART module. Configures different UART peripheral 
 * 	with the specified parameters provideb by the parameter Config
 *
 *  \param Config  Pointer to the UART peripheral structures of configuration.
 */

void Uart_Init(const UartConfigType *Config)
{
  Uart *LocUartReg;
  uint8_t LocChIdx = 0; /* LocChIdx represent the logical channel */
  uint8_t PhyChIdx = 0; /* PhyCHIdx represent the Physical channel */

  NumberOfChannels = Config->UartNumberOfChannels;

  /* Memory allocation for all Channel Status example */
  /* UART_CFG_CHANNELS represents the number of configured channels from configuration structure */
  UartStatus = (UartStatusType *)MemAlloc(sizeof(UartStatusType) * NumberOfChannels);

  for (LocChIdx = 0; LocChIdx < NumberOfChannels; LocChIdx++)
  {
    /* Reference to the physical channel with PhyChIdx */
    PhyChIdx = Config->UartChannel[LocChIdx].ChannelId;

    /* Point to register address based of physical channel */
    LocUartReg = UartRegAddr[PhyChIdx];

    /* Access to register for the configured channel with LocUartReg */
    /* Access to channel status structure with LocChIdx */
    UartStatus[LocChIdx].ChannelId = PhyChIdx;

    UartStatus[LocChIdx].tx_callback = Config->UartChannel[LocChIdx].TxNotification;
    UartStatus[LocChIdx].rx_callback = Config->UartChannel[LocChIdx].RxNotification;
    UartStatus[LocChIdx].error_callback = Config->UartChannel[LocChIdx].ErrorNotification;

    /* Enable the peripheral clock in the PMC*/
    PMC_EnablePeripheral(PeriID[PhyChIdx]);

    /* Reset and disable receiver & transmitter*/
    LocUartReg->UART_CR = UART_CR_RSTRX | UART_CR_RSTTX | UART_CR_RXDIS | UART_CR_TXDIS | UART_CR_RSTSTA;

    LocUartReg->UART_IDR = 0xFFFFFFFF;

    /* Configure mode*/
    LocUartReg->UART_MR = UART_MR_PAR(Config->UartChannel[LocChIdx].Parity) | ((Config->ClkSrc) << 12) | UART_MR_CHMODE(Config->UartChannel[LocChIdx].Mode);

    /* Configure baudrate*/
    LocUartReg->UART_BRGR = (BOARD_MCK / Config->UartChannel[LocChIdx].Baudrate) / 16;

    LocUartReg->UART_CR = UART_CR_TXEN | UART_CR_RXEN;

    /* Clear pending IRQs and Set priority of IRQs */
    NVIC_ClearPendingIRQ(UartIRQS[PhyChIdx]);
    //NVIC_SetPriority(UartIRQS[PhyChIdx], 1);

    /* Enables the UART to transfer and receive data. */
    Uart_EnableInt(PhyChIdx, Config->UartChannel[LocChIdx].IsrEn, true);
  }
}

/**
 * \brief Sets the requested baudrate to the addressed UART channel
 *
 *  \param Channel  UART channel to be addressed.
 *  \param Baudrate  Baudrate to configure.
 *  \return E_OK: Command successfuly executed.
 */

Std_ReturnType Uart_SetBaudrate(uint8_t Channel, uint32_t Baudrate)
{
  uint8_t retVal = E_NOT_OK;
  uint32_t IntBU = 0;

  UartRegAddr[Channel]->UART_CR = UART_CR_RXDIS | UART_CR_TXDIS;

  /* Look for Tx and Rx to be disabled */
  if (!(UartRegAddr[Channel]->UART_SR & UART_SR_RXRDY) && !(UartRegAddr[Channel]->UART_SR & UART_SR_TXEMPTY))
  {
    IntBU = UartRegAddr[Channel]->UART_IMR; /* Enabled interrupts Backup */

    UartRegAddr[Channel]->UART_IDR = 0xFFFFFFFF;

    UartRegAddr[Channel]->UART_BRGR = (BOARD_MCK / Baudrate) / 16;

    UartRegAddr[Channel]->UART_CR = UART_CR_TXEN | UART_CR_RXEN;

    UartRegAddr[Channel]->UART_IER = IntBU;

    retVal = E_OK;
  }
  else
  {
    retVal = E_NOT_OK;
  }
  return retVal;
}

/**
 * \brief Enables or disables the transmitter of the UART module
 *
 *  \param Channel  UART Channel to be addressed.
 *  \param Enable  Enable/Disable information. 0: Disable 1: Enable
 */

void Uart_SetTxEnable(uint8_t Channel, uint8_t Enable)
{
  if (Enable)
  {
    UartRegAddr[Channel]->UART_CR = UART_CR_TXEN;
  }
  else
  {
    UartRegAddr[Channel]->UART_CR = UART_CR_TXDIS;
  }
}

/**
 * \brief Enables or disables the receiver of the UART module
 *
 *  \param Channel  UART Channel to be addressed.
 *  \param Enable  Enable/Disable information. 0: Disable 1: Enable
 */

void Uart_SetRxEnable(uint8_t Channel, uint8_t Enable)
{
  if (Enable)
  {
    UartRegAddr[Channel]->UART_CR = UART_CR_RXEN;
  }
  else
  {
    UartRegAddr[Channel]->UART_CR = UART_CR_RXDIS;
  }
}

/**
 * \brief Sends one packet of data through the specified UART module
 *
 *  \param Channel  UART channel to be addressed.
 *  \param Byte  Data to be sent over the UART bus.
 *  \return E_OK: Command successfuly executed.
 */

Std_ReturnType Uart_SendByte(uint8_t Channel, uint8_t Byte)
{

  uint8_t retVal = E_NOT_OK;

  NVIC_EnableIRQ(UartIRQS[Channel]);

  if (!(UartRegAddr[Channel]->UART_SR & UART_SR_RXRDY) && !(UartRegAddr[Channel]->UART_SR & UART_SR_TXEMPTY))
  //  if( !( UartRegAddr[Channel]->UART_SR & UART_SR_TXEMPTY ) )
  {
    retVal = E_NOT_OK;
  }
  else
  {
    UartRegAddr[Channel]->UART_THR = Byte;
    UartStatus[Uart_GetLogChannel(Channel)].Counter++;
    retVal = E_OK;
  }
  return retVal;
}

/**
 * \brief Sends a packet of data through the specified UART channel
 *
 *  \param Channel  UART channel to be addressed.
 *  \param Buffer  Pointer to the start address of the buffer to be sent over the UART bus.
 *  \param Lenght  Size of the buffer to sent.
 *  \return E_OK: Command successfuly executed.
 */

Std_ReturnType Uart_SendBuffer(uint8_t Channel, uint8_t *Buffer, uint16_t Length)
{
  uint8_t retVal = E_NOT_OK;
  uint8_t *pData = Buffer;
  uint8_t sentData = 0;
  static uint32_t Len = 0;

  if (Len == 0)
  {
    while (Len < Length)
    {
      sentData = Uart_SendByte(Channel, *pData);

      if (sentData == E_OK)
      {
        pData++;
        Len++;
      }
    }
    Len = 0;
    retVal = E_OK;
  }
  else
  {
    retVal = E_NOT_OK;
  }
  return retVal;
}

/**
 * \brief Reads and returns a character from the UART module
 *
 *  \param Channel  UART channel to be addressed.
 *  \return Data received from the UART bus.
 */

uint8_t Uart_GetByte(uint8_t Channel)
{
  return UartRegAddr[Channel]->UART_RHR;
}

/**
 * \brief Reads and returns the current status of the addressed UART module
 *
 *  \param Channel  UART channel to be addressed.
 *  \return Current status of the addressed UART module.
 */

uint32_t Uart_GetStatus(uint8_t Channel)
{
  return UartRegAddr[Channel]->UART_SR;
}

/**
 * \brief Enable/disable The UART module interrupts
 *
 *  \param Channel  UART channel to be addressed.
 *  \param IntMode  Interrupt Mode information.
 *  \param Enable  Enable/Disable information. 0: Disable 1: Enable.
 */

void Uart_EnableInt(uint8_t Channel, uint32_t IntMode, uint8_t Enable)
{
  if (Enable)
  {
    UartRegAddr[Channel]->UART_IER = IntMode;
    intBUglob = IntMode;
  }
  else
  {
    UartRegAddr[Channel]->UART_IDR = IntMode;
  }
}

/*****************************************************************************************************
* Code of module wide Interrupt Handler FUNCTIONS
*****************************************************************************************************/

void Uart_Isr(uint8_t Channel)
{
  const Uart *LocUartReg = UartRegAddr[Channel];
  uint8_t LocUartLogicChannel = Uart_GetLogChannel(Channel);

  uint32_t statusRegister = UartRegAddr[Channel]->UART_IMR & UartRegAddr[Channel]->UART_SR;

  if ((statusRegister & UART_MASK_RXRDY) /*&& (UartStatus[LocUartLogicChannel].rx_callback != NULL)*/)
  {
    UartStatus[LocUartLogicChannel].rx_callback();
  }
  if ((statusRegister & UART_MASK_TXRDY) /*&& (UartStatus[LocUartLogicChannel].tx_callback != NULL)*/)
  {
    UartStatus[LocUartLogicChannel].tx_callback();
  }
  if ((statusRegister & UART_MASK_OVRE) /*&& (UartStatus[LocUartLogicChannel].error_callback != NULL)*/)
  {
    UartStatus[LocUartLogicChannel].error_callback(UART_ERROR_OVERRUN);
  }
  if ((statusRegister & UART_MASK_FRAME) /*&& (UartStatus[LocUartLogicChannel].error_callback != NULL)*/)
  {
    UartStatus[LocUartLogicChannel].error_callback(UART_ERROR_FRAMING);
  }
  if ((statusRegister & UART_MASK_PARE) /*&& (UartStatus[LocUartLogicChannel].error_callback != NULL)*/)
  {
    UartStatus[LocUartLogicChannel].error_callback(UART_ERROR_PARITY);
  }

  /* Example Code */
  /* UART_CFG_CHANNELS represents the number of configured channels from configuration structure */
  if (LocUartLogicChannel < NumberOfChannels)
    UartStatus[LocUartLogicChannel].TriggerCounter++;

  // NVIC_DisableIRQ(UartIRQS[Channel]);
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