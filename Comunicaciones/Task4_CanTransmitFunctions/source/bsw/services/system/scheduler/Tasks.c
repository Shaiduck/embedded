/*
 * Tasks.c
 *
 * Created: 6/21/2016 7:25:43 PM
 *  Author: Francisco Martinez
 */

#include "Tasks.h"
#include "led.h"
#include "mcan.h"
#include "canif.h"

// uint8_t *buffer0;
// uint8_t buffernumber0 = 0;
// uint32_t CanId0 = 0x1A0;
// MCan_IdType CanIdType0 = CAN_STD_ID;
// MCan_DlcType CanDlc0 = CAN_DLC_3;

uint8_t Buff0Ctr = 0xFF;
uint8_t Buff1Ctr = 0x80;
uint8_t Buff2Ctr = 0x00;

uint8_t u8100ms_Ctr = 0;
uint8_t u8100ms_Ctr2 = 0;

uint8_t *bufferTest;
uint8_t *buffer0;
uint8_t *buffer1;
uint8_t *buffer2;
uint8_t *buffer3;
uint16_t conta;
uint16_t divi;

uint8_t MsgTest[] = {0xFF, 0x80, 0x00};
uint8_t Msg0[] = {0x08, 0x00, 0x80}; // High Beams
uint8_t Msg1[] = {0x04, 0x00, 0x80}; // Optical Horn
uint8_t Msg2[] = {0x01, 0x00, 0x80}; // Left Blinker
uint8_t Msg3[] = {0x02, 0x00, 0x80}; // Righ Blinker

void fill_Buffer(uint8_t *buff, uint8_t sizemsg, uint8_t *msg);

void vfnTsk_1ms(void)
{
    /*
  static uint8_t McanBuff0Init = 0;
  
  if (0 == McanBuff0Init)
  {
    McanBuff0Init = 1;
    //buffer0 = MCAN_ConfigTxDedBuffer( &mcan1Config, buffernumber0, CanId0, CanIdType0, CanDlc0 );
  }
  else if (1 == McanBuff0Init)
  {
    McanBuff0Init = 2;
    //buffer1 = MCAN_ConfigTxDedBuffer( &mcan1Config, buffernumber1, CanId1, CanIdType0, CanDlc0 );
  } 
  else
  {
    buffer0[0] = Buff0Ctr;
    buffer0[1] = Buff1Ctr;
    buffer0[2] = Buff2Ctr;
    
    MCAN_SendTxDedBuffer( &mcan1Config, buffernumber0 );
    
    buffer1[0] = msg1[0];
    buffer1[1] = msg1[1];
    buffer1[2] = msg1[2];
    MCAN_SendTxDedBuffer( &mcan1Config, buffernumber1 );
  }
  */
}
void vfnTsk_2msA(void)
{
}

void vfnTsk_2msB(void)
{
}

void vfnTsk_10ms(void)
{
    static uint8_t u8500ms_Ctr = 0;

    u8500ms_Ctr++;

    if (25 <= u8500ms_Ctr)
    {
        u8500ms_Ctr = 0;
        LED_Toggle(1);
    }
}

void vfnTsk_50ms(void)
{
}

// void vfnTsk_100ms(void)
// {

// 		u8100ms_Ctr++;
//     u8100ms_Ctr2++;
// 		Buff2Ctr++;
// 		if (5 <= u8100ms_Ctr)
// 		{
// 			u8100ms_Ctr = 0;
// 			LED_Toggle( 0 );
// 		}
//     if (10 <= u8100ms_Ctr2)
// 		{
// 			u8100ms_Ctr2 = 0;
//       Buff2Ctr=0;
// 			Buff1Ctr++;
// 		}
//     if (60 <= Buff1Ctr)
//     {
//       Buff0Ctr++;
//       Buff1Ctr = 0;
//     }
// }
void vfnTsk_100ms(void)
{

    conta++;
    divi = conta / 100;

    static uint8_t McanBuff0Init = 0;

    if (0 == McanBuff0Init)
    {
        McanBuff0Init = 1;
        fill_Buffer(bufferTest, sizeof(MsgTest), &MsgTest[0]);

        fill_Buffer(buffer0, sizeof(Msg0), &Msg0[0]);
        fill_Buffer(buffer1, sizeof(Msg1), &Msg1[0]);
        fill_Buffer(buffer2, sizeof(Msg2), &Msg2[0]);
        fill_Buffer(buffer3, sizeof(Msg3), &Msg3[0]);
    }
    else
    {

        CanIf_Transmit(CAN_CHANNEL_1, TEST_MSG);
        // switch (divi)
        // {
        // case 0:
        //     CanIf_Transmit(CAN_CHANNEL_1, HIGH_BEAMS);
        //     break;

        // case 1:
        //     CanIf_Transmit(CAN_CHANNEL_1, OPTICAL_HORN);
        //     break;

        // case 2:
        //     CanIf_Transmit(CAN_CHANNEL_1, RIGHT_BLINKER);

        //     break;

        // case 3:
        //     CanIf_Transmit(CAN_CHANNEL_1, LEFT_BLINKER);
        //     break;
        // default:
        //     conta = 0;
        //     break;
        // }
    }

    u8100ms_Ctr++;
    u8100ms_Ctr2++;
    Buff2Ctr++;
    if (5 <= u8100ms_Ctr)
    {
        u8100ms_Ctr = 0;
        LED_Toggle(0);
    }
    if (10 <= u8100ms_Ctr2)
    {
        u8100ms_Ctr2 = 0;
        Buff2Ctr = 0;
        Buff1Ctr++;
    }
    if (60 <= Buff1Ctr)
    {
        Buff0Ctr++;
        Buff1Ctr = 0;
    }
}

void fill_Buffer(uint8_t *buff, uint8_t sizemsg, uint8_t *msg)
{
    uint8_t lub_index;
    for (lub_index = 0; lub_index < sizemsg; lub_index++)
    {
        buff[lub_index] = msg[lub_index];
    }
}
