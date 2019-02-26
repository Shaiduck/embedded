/*
 * comm_protocol.h
 *
 */ 


#ifndef __LIN_MASTER_H
#define __LIN_MASTER_H


/*-- Includes ----------------------------------------------------------------*/

/** Core modules */

/** Used modules */



/*-- Defines -----------------------------------------------------------------*/


/*-- Macros ------------------------------------------------------------------*/


/*-- Function Prototypes -----------------------------------------------------*/

/** Lin initialization function */
void vfnLinMaster_Init(void);

/** Lin Send Frame  */
void vfnLinMaster_SendFrame(void);

#endif /* __LIN_MASTER_H */