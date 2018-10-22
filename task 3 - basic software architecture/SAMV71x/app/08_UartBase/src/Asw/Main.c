/****************************************************************************************************/
/**
  \mainpage
  \n 
  \brief        Main application (main module)
  \author       Abraham Tezmol Otero, M.S.E.E
  \project      Tau 
  \version      1.0
  \date         12/Jun/2016
   
  Program compiled with  WinIDEA Open Build 9.12.256 (54401), tested on Atmel SAMV71 Xplained Ultra
*/
/****************************************************************************************************/


/*~~~~~~  Headers ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/** Main group of includes for board definitions, chip definitions and type definitions */
#include    "Std_Types.h"
/** Task scheduler definitions */
#include    "SchM.h"
/** LED control definitions */ 
#include    "Led_Ctrl.h"
/** Watchdog control function prototypes definitions */
#include    "Wdg.h"
/** Button Control interfaces */
#include    "Button_Ctrl.h"
/** Uart interfaces */
#include    "Uart.h"


/*~~~~~~  Local definitions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~  Global variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
UartConfigType Config;

/*~~~~~~  Local functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void TxNotification()
{
	printf("Uart: Ready to text\n");
}

void RxNotification()
{
	printf("Uart: Ready to read\n");
}

void ErrorNotification(UartErrorType Error)
{
	switch (Error)
	{
		case UART_ERROR_OVERRUN:
			printf("Uart Error Overrun\n");
			break;
		case UART_ERROR_FRAMING:
			printf("Uart Error Framing\n");
			break;
		case UART_ERROR_PARITY:
			printf("Uart Error Parity\n");
			break;
		default:
			printf("error: this ain't it, chief\n");
	}
}

void configurationInit()
{
	Config.UartNumberOfChannels = 1;
	Config.ClkSrc = 0;
	Config.UartChannel = (UartChannelType*)MemAlloc(sizeof(UartChannelType*)*(Config.UartNumberOfChannels));
	Config.UartChannel->ChannelId = 0;
	Config.UartChannel->IsrEn = UART_CFG_INT_TXRDY;
	Config.UartChannel->Mode = UART_CFG_MODE_NORMAL;
	Config.UartChannel->Parity = UART_CFG_PARITY_NO;
	Config.UartChannel->Baudrate = 115200;
	Config.UartChannel->ErrorNotification = ErrorNotification;
	Config.UartChannel->RxNotification = RxNotification;
	Config.UartChannel->TxNotification = TxNotification;
}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/
/**
 *  \brief getting-started Application entry point.
 *
 *  \return Unused (ANSI-C compatibility).
 */
extern int main( void )
{
	/* Disable watchdog */
	Wdg_Disable();
	printf( "\n\r-- Scheduler Project %s --\n\r", SOFTPACK_VERSION ) ;
	printf( "-- %s\n\r", BOARD_NAME ) ;
	printf( "-- Compiled: %s %s With %s --\n\r", __DATE__, __TIME__ , COMPILER_NAME);
	/* Enable I and D cache */
	SCB_EnableICache();
	/* SCB_EnableDCache(); */
	/* Configure LEDs */
	printf( "-- Led Control --\n\r" ) ;
	LedCtrl_Configure();
  
    printf( "-- Button Control --\n\r" ) ;  
    ButtonCtrl_ConfigureSW0Button();
  
    /* Uart Inititalization */
    printf( "-- Uart Initialization --\n\r" ) ;
    //Uart_Init(&UartConfiguredChannels[0]);
	configurationInit();
	Uart_Init(&Config);
	
	/* Scheduler Inititalization */
	printf( "-- Scheduler Initialization --\n\r" ) ;
	SchM_Init(ScheduleConfig);
	
	/* Should never reach this code */
	for(;;)
    {
		printf( "-- Unexpected Error at Scheduler Initialization --\n\r" ) ;
	}
}