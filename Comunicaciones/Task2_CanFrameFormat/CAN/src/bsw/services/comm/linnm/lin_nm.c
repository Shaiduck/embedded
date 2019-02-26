/*
 * Lin Network Manager
 *
 */ 

#include "lin_nm.h"
#include "lin_master.h"


/*******************************************************************************/
/**
* \brief    LIN Network Manager Periodic Task
* \author   Francisco Martinez
* \param    void
* \return   void
*/
void vfnLinNM_1ms(void)
{
	vfnLinMaster_SendFrame();  
}
