
#ifndef CANIF_H
#define CANIF_H

/*----------------------------------------------------------------------------
 *         Headers
 *----------------------------------------------------------------------------*/

#include "mcan_types.h"
#include "mcan.h"

/*----------------------------------------------------------------------------
 *         Definitions
 *----------------------------------------------------------------------------*/

#define CAN_CHANNEL_1 1u

#define HIGH_BEAMS    0u
#define OPTICAL_HORN  1u
#define LEFT_BLINKER  2u
#define RIGHT_BLINKER 3u
#define TEST_MSG      4u


/*----------------------------------------------------------------------------
 *         Global functions
 *----------------------------------------------------------------------------*/

void CanIf_Init(uint8_t CanChannelId, CanIf_MsgObjType CanIfMsgConfig);
void CanIf_Transmit(uint8_t CanChannelId, uint8_t MsgId);

extern uint8_t *buffer0;
extern uint8_t *buffer1;
extern uint8_t *buffer2;
extern uint8_t *buffer3;

#endif /* _TIMETICK_ */
