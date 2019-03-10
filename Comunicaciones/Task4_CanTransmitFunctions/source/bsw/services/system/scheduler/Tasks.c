/*
 * Tasks.c
 *
 * Created: 6/21/2016 7:25:43 PM
 *  Author: Francisco Martinez
 */ 

#include "Tasks.h"
#include "led.h"
#include "mcan.h"

uint8_t *buffer0;
uint8_t buffernumber0 = 0;
uint32_t CanId0 = 0x1A0;
MCan_IdType CanIdType0 = CAN_STD_ID;
MCan_DlcType CanDlc0 = CAN_DLC_3;

uint8_t Buff0Ctr = 0xFF;
uint8_t Buff1Ctr = 0x80;
uint8_t Buff2Ctr = 0x00;

uint8_t u8100ms_Ctr=0;
uint8_t u8100ms_Ctr2=0;


void vfnTsk_1ms(void)
{
  static uint8_t McanBuff0Init = 0;
  
  if (0 == McanBuff0Init)
  {
    McanBuff0Init = 1;
    buffer0 = MCAN_ConfigTxDedBuffer( &mcan1Config, buffernumber0, CanId0, CanIdType0, CanDlc0 );
  }
  else
  {
    buffer0[0] = Buff0Ctr;
    buffer0[1] = Buff1Ctr;
    buffer0[2] = Buff2Ctr;
    MCAN_SendTxDedBuffer( &mcan1Config, buffernumber0 );
  }
}

void vfnTsk_2msA(void)
{
	
}

void vfnTsk_2msB(void)
{
	
}

void vfnTsk_10ms(void)
{
		static uint8_t u8500ms_Ctr=0;
		
		u8500ms_Ctr++;
		
		if (25 <= u8500ms_Ctr)
		{
			u8500ms_Ctr = 0;
			LED_Toggle( 1 );
		}   
}

void vfnTsk_50ms(void)
{

}

void vfnTsk_100ms(void)
{
  			
		u8100ms_Ctr++;
    u8100ms_Ctr2++;
		Buff2Ctr++;
		if (5 <= u8100ms_Ctr)
		{
			u8100ms_Ctr = 0;
			LED_Toggle( 0 );
		}
    if (10 <= u8100ms_Ctr2)
		{
			u8100ms_Ctr2 = 0;
      Buff2Ctr=0;
			Buff1Ctr++;
		}
    if (60 <= Buff1Ctr)
    {
      Buff0Ctr++;
      Buff1Ctr = 0;
    }
}

