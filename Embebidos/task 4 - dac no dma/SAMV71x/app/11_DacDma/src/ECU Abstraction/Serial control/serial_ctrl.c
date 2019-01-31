/****************************************************************************************************/
/**
\file       serial_ctrl.c
\brief      MCU abstraction level - Serial UART control
\author     Abraham Tezmol
\version    1.0
\project    Tau 
\date       21/June/2016
*/
/****************************************************************************************************/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/
/** Own headers */
#include     "serial_ctrl.h"

/** Other modules */
#include     "uartdrv.h"
#include     "pmc.h"
#include     "board.h"
#include     "pio.h"

/****************************************************************************************************
* Definition of module wide MACROs / #DEFINE-CONSTANTs 
*****************************************************************************************************/


/*****************************************************************************************************
* Definition of module wide VARIABLEs 
*****************************************************************************************************/

uint8_t 		u8SerialCtrl_TxData[] =
{"The Atmel� | SMART� SAM V71 Xplained Ultra evaluation kit is ideal for evaluating and prototyping with the Atmel SAM V71, SAM V70, SAM S70 and SAM E70 ARM� Cortex�-M7 based microcontrollers\n\r\n\rExample by Abraham Tezmol\n\r\n\r"};
uint8_t 		u8SerialCtrl_RxData[SERIAL_RX_MAX_SIZE];
uint8_t  * 		pu8SerialCtrl_RxDataPtr;
uint8_t  * 		pu8SerialCtrl_ReadRxDataPtr;
uint8_t  *		pu8SerialCtrl_ReadTxDataPtr;
uint16_t  		u16SerialCtrl_RxLength;
uint16_t 		u16SerialCtrl_TxLength;

/****************************************************************************************************
* Declaration of module wide FUNCTIONs 
****************************************************************************************************/

/****************************************************************************************************
* Declaration of module wide TYPEs 
*****************************************************************************************************/

/****************************************************************************************************
* Definition of module wide (CONST-) CONSTANTs 
*****************************************************************************************************/

/****************************************************************************************************
* Code of module wide FUNCTIONS
*****************************************************************************************************/


/*****************************************************************************************************/
/**
* \brief    Configures Serial channel 4 on SAMV71 board
* \author   Abraham Tezmol
* \param    void
* \return   void
*/
void vfnSerialCtrl_Configure( void )
{
	PMC_EnablePeripheral(BASE_ID);
	
	/* Reset & disable receiver and transmitter, disable interrupts */
	// UART_Configure(BASE_UART, (UART_MR_PAR_NO | UART_MR_CHMODE_LOCAL_LOOPBACK), 115200, BOARD_MCK, vfnSerialCtrl_Transfer);
	UART_Configure(BASE_UART, (UART_MR_PAR_NO | UART_MR_CHMODE_LOCAL_LOOPBACK), 115200, BOARD_MCK);

	/* Clear pending IRQs and Set priority of IRQs */
	NVIC_ClearPendingIRQ(BASE_IRQ);
	NVIC_SetPriority(BASE_IRQ, 1);

	/* Enables the UART to transfer and receive data. */
	UART_SetTransmitterEnabled (BASE_UART , 1);
	UART_SetReceiverEnabled (BASE_UART , 1);

	UART_EnableIt(BASE_UART, UART_IER_RXRDY);
	/* Enable interrupt  */
	NVIC_EnableIRQ(BASE_IRQ);	
}

/******************************************************************************************************************/
/**
* \brief    Discard any incomming data on UART receive buffer
* \author   Abraham Tezmol
* \param    void
* \return   void
*/
void vfnSerialCrtl_ClearRx( void )
{
    /* Reset auxiliary variables for input buffer management */
    pu8SerialCtrl_RxDataPtr      = &u8SerialCtrl_RxData[0];
    pu8SerialCtrl_ReadRxDataPtr  = pu8SerialCtrl_RxDataPtr;
    u16SerialCtrl_RxLength        = 0u;
}

/******************************************************************************************************************/
/**
* \brief    Discard any queued data on UART transmit buffer
* \author   Abraham Tezmol
* \param    void
* \return   void
*/
void vfnSerialCtrl_ClearTx( void )
{
    /* inhibit interrupt-driven Tx scheme */
    UART_DisableIt(BASE_UART, UART_IER_TXRDY); 
      
    /* Reset auxiliary variables for output buffer management */
    pu8SerialCtrl_ReadTxDataPtr = &u8SerialCtrl_TxData[0];
    u16SerialCtrl_TxLength       = 0u;

}

/******************************************************************************************************************/
/**
* \brief    Initialize UART communication on Serial channel 4 of SAMV71 board
* \author   Abraham Tezmol
* \param    void
* \return   void
*/
void vfnSerialCtrl_Init( void )
{
    vfnSerialCtrl_Configure();
    vfnSerialCrtl_ClearRx();
    vfnSerialCtrl_ClearTx();
}

/******************************************************************************************************************/
/**
* \brief    Start serial communication through Serial channel 4 on SAMV71 board
* \author   Abraham Tezmol
* \param    void
* \return   void
*/
void vfnSerialCtrl_StartTx( void )
{
    pu8SerialCtrl_ReadTxDataPtr = &u8SerialCtrl_TxData[0];
    u16SerialCtrl_TxLength = sizeof(u8SerialCtrl_TxData);
    UART_EnableIt(BASE_UART, UART_IER_TXRDY );
}


/******************************************************************************************************************/
/**
* \brief    Start serial communication - transfer one byte at a time
* \author   Abraham Tezmol
* \param    void
* \return   void
*/
void vfnSerialCtrl_Transfer(void)
{		
	if (u16SerialCtrl_TxLength > 0)
	{
		/*Send out one byte at a time */
		// UART_PutCharAsynch(BASE_UART, *pu8SerialCtrl_ReadTxDataPtr);
		UART_PutChar(BASE_UART, *pu8SerialCtrl_ReadTxDataPtr);
		/* point to next element */
		pu8SerialCtrl_ReadTxDataPtr++;
		/* update number of pending bytes to transfer */
		u16SerialCtrl_TxLength--;
	}
	else
	{
		/* inhibit interrupt-driven Tx scheme */
    	UART_DisableIt(BASE_UART, UART_IER_TXRDY);
	}
}
