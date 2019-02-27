/****************************************************************************************************/
/**
\file       Uart_Ctrl.c
\brief      MCU abstraction level - Uart control
\author     Francisco Martinez
\version    1.1
\date       25/Sep/2018
*/
/****************************************************************************************************/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/
/** Own headers */
#include "Uart_Ctrl.h"
#include "Uart.h"

/*****************************************************************************************************
* Definition of module wide VARIABLEs 
*****************************************************************************************************/

/****************************************************************************************************
* Declaration of module wide FUNCTIONs 
****************************************************************************************************/

/****************************************************************************************************
* Definition of module wide MACROs / #DEFINE-CONSTANTs 
*****************************************************************************************************/

/****************************************************************************************************
* Declaration of module wide TYPEs 
*****************************************************************************************************/

/****************************************************************************************************
* Definition of module wide (CONST-) CONSTANTs 
*****************************************************************************************************/

uint8_t messageBuff1[] = "La tierra es redonda\n\r";
uint8_t messageBuff2[] = "EMBEDDED SYSTEMS RULES";
uint8_t indx = 0;
uint8_t rxVal = 0;
uint8_t enablestate = true;
uint8_t stateTx = 0;
uint8_t stateBuff = 0;
uint8_t stateBaud = 0;

/****************************************************************************************************
* Code of module wide FUNCTIONS
*****************************************************************************************************/

void UartCtrl_2ms(void)
{
  stateTx = Uart_SendByte(UART2_ctrl, messageBuff1[indx]);
  if (stateTx == 0)
  {
    indx++;
  }

  if (indx >= sizeof(messageBuff1))
  {
    indx = 0;
  }

  rxVal = Uart_GetByte(UART2_ctrl);

  printf("%c", rxVal);
}

void UartCtrl_50ms(void)
{
  //stateBaud=Uart_SetBaudrate (UART4_ctrl,9600);
}

void UartCtrl_100ms(void)
{

  stateBuff = Uart_SendBuffer(UART4_ctrl, &messageBuff2[0], sizeof(messageBuff2));

  if (stateBuff == 0)
  {
    printf("\n\r-Buffer sent-\n\r");
  }
}

void UartCtrl_TriggerEvent(void)
{
  if (enablestate == true)
  {
    enablestate = false;
  }
  else
  {
    enablestate = true;
  }

  Uart_SetRxEnable(UART2_ctrl, enablestate);
  //Uart_EnableInt(UART2_ctrl, UART_CFG_INT_TXRDY | UART_CFG_INT_RXRDY, enablestate);
  /* Example Code, need to be removed */
  /* These function handlers shall be invoked upon interrupt request */
  /* In your solution this trigger can start a buffer transmission */
}

/*******************************************************************************/
