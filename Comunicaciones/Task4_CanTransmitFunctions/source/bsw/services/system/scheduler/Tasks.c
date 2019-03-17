/*
 * Tasks.c
 *
 * Created: 6/21/2016 7:25:43 PM
 *  Author: Francisco Martinez
 */

#include "Tasks.h"
#include "led.h"
#include "mcan.h"

// uint8_t *buffer0;
// uint8_t buffernumber0 = 0;
// uint32_t CanId0 = 0x1A0;
// MCan_IdType CanIdType0 = CAN_STD_ID;
// MCan_DlcType CanDlc0 = CAN_DLC_3;

// uint8_t Buff0Ctr = 0xFF;
// uint8_t Buff1Ctr = 0x80;
// uint8_t Buff2Ctr = 0x00;

uint8_t u8100ms_Ctr = 0;
uint8_t u8100ms_Ctr2 = 0;

void vfnTsk_1ms(void)
{
	static int message = 0;
	static int canId = 0;
	
	if (message >= 3)
	{
		if (canId == 0)
		{
			canId++;
		}
		else
		{
			canId = 0;
		}
		message = 0;
	}

	CanIf_Transmit(canId, message);
	message++;
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

void vfnTsk_100ms(void)
{
	static uint8_t keep = 0x80;

	u8100ms_Ctr++;
	u8100ms_Ctr2++;
	CanIf_IncreaseBuffer(2);
	if (5 <= u8100ms_Ctr)
	{
		u8100ms_Ctr = 0;
		LED_Toggle(0);
	}
	if (10 <= u8100ms_Ctr2)
	{
		u8100ms_Ctr2 = 0;
		CanIf_ResetBuffer(2);
		CanIf_IncreaseBuffer(1);
	}
	if (60 <= keep)
	{
		CanIf_IncreaseBuffer(0);
		CanIf_ResetBuffer(1);
		keep = 0;
	}
}
