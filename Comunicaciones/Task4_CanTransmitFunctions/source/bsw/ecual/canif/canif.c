/**
 *  \file
 *  Implement the System Timer.
 */

/*----------------------------------------------------------------------------
 *         Headers
 *----------------------------------------------------------------------------*/

#include "canif.h"
#include "mcan_types.h"

/*----------------------------------------------------------------------------
 *         Local variables
 *----------------------------------------------------------------------------*/

uint8_t buffernumber0 = 0;
uint8_t buffernumber1 = 1;
uint8_t buffernumber2 = 2;
uint8_t buffernumber3 = 3;


typedef enum
{
  channel0,
  channel1
}CanIf_channelId;

/*----------------------------------------------------------------------------
 *         Functions
 *----------------------------------------------------------------------------*/

/* CAN Initialization:
This function shall initialize the Can channel according to CanChannelId parameter.
Additionally, the function shall configure the CAN TX Messages as per the message configuration structure shown below.*/
void CanIf_Init(uint8_t CanChannelId, CanIf_MsgObjType CanIfMsgConfig)
{
  MCan_ConfigType lub_mcanConfig = {0u};
  
  if( CanChannelId == channel0 )
  {
    lub_mcanConfig = mcan0Config;
  }
  else if( CanChannelId == channel1 )
  {
    lub_mcanConfig = mcan1Config;
  }
  
	MCAN_Init( &lub_mcanConfig );
  
  MCAN_Enable( &lub_mcanConfig );
  
  buffer0 = MCAN_ConfigTxDedBuffer( &mcan1Config, buffernumber0, CanIfMsgConfig.CanIfMessageConfig[0].CanPdu.CanId, CanIfMsgConfig.CanIfMessageConfig[0].CanPdu.CanIdType, CanIfMsgConfig.CanIfMessageConfig[0].CanPdu.CanDlc );
  buffer1 = MCAN_ConfigTxDedBuffer( &mcan1Config, buffernumber1, CanIfMsgConfig.CanIfMessageConfig[1].CanPdu.CanId, CanIfMsgConfig.CanIfMessageConfig[1].CanPdu.CanIdType, CanIfMsgConfig.CanIfMessageConfig[1].CanPdu.CanDlc );
  buffer2 = MCAN_ConfigTxDedBuffer( &mcan1Config, buffernumber2, CanIfMsgConfig.CanIfMessageConfig[2].CanPdu.CanId, CanIfMsgConfig.CanIfMessageConfig[2].CanPdu.CanIdType, CanIfMsgConfig.CanIfMessageConfig[2].CanPdu.CanDlc );
  buffer3 = MCAN_ConfigTxDedBuffer( &mcan1Config, buffernumber3, CanIfMsgConfig.CanIfMessageConfig[3].CanPdu.CanId, CanIfMsgConfig.CanIfMessageConfig[3].CanPdu.CanIdType, CanIfMsgConfig.CanIfMessageConfig[3].CanPdu.CanDlc );
}

/* CAN Transmission: 
This function shall transmit the Can Message according to MsgId on the CAN Bus as per the CanChannelId parameter.*/
void CanIf_Transmit(uint8_t CanChannelId, uint8_t MsgId)
{
  MCan_ConfigType lub_mcanConfig = {0u};
  
  if( CanChannelId == channel0 )
  {
    lub_mcanConfig = mcan0Config;
  }
  else if( CanChannelId == channel1 )
  {
    lub_mcanConfig = mcan1Config;
  }
  
  MCAN_SendTxDedBuffer( &lub_mcanConfig, MsgId );
}
