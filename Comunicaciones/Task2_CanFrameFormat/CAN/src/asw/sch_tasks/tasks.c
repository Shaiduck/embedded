/*
 * tasks.c
 *
 * Created: 6/10/2016 7:40:22 PM
 *  Author: Francisco Martinez
 */ 

#include <asf.h>
#include "tasks.h"
#include "lin_nm.h"
#include "mcanif.h"

void vfnTsk_1ms(void)
{
  //ioport_toggle_pin_level(LED1_GPIO);
  /*vfnLinNM_1ms();  */
}

void vfnTsk_2msA(void)
{
  // ioport_toggle_pin_level(LED1_GPIO);
  mcan_main();
}

void vfnTsk_2msB(void)
{
  // ioport_toggle_pin_level(LED1_GPIO);
}

void vfnTsk_10ms(void)
{
  // ioport_toggle_pin_level(LED1_GPIO);
}

void vfnTsk_50ms(void)
{
  // ioport_toggle_pin_level(LED1_GPIO);
}

void vfnTsk_100ms(void)
{
	static uint8_t counter = 0;
	counter++;
	if ( 5 == counter)
	{
		ioport_toggle_pin_level(LED1_GPIO);
		counter = 0;	
	}
}