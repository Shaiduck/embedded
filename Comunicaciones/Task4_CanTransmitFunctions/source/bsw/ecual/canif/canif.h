#ifndef _CANIF_
#define _CANIF_

#include "canif_types.h"

/**
 *    1) This function shall initialize the Can channel according to CanChannelId parameter.
 *    2) Additionally, the function shall configure the CAN TX Messages as per the message configuration structure shown below.
 * */
void CanIf_Init(uint8_t CanChannelId, CanIf_MsgObjType CanIfMsgConfig);

/**
 *    1) This function shall transmit the Can Message according to MsgId on the CAN Bus as per the CanChannelId parameter.
 * */
void CanIf_Transmit(uint8_t CanChannelId, uint8_t MsgId);

void CanIf_Test();

#endif