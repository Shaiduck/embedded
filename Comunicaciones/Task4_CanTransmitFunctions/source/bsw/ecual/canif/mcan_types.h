#ifndef _CANIF_TYPES_
#define _CANIF_TYPES_

#include "mcan.h"

typedef enum
{
    CAN_TX = 0,
    CAN_RX = 1,
} MCan_DirType;

typedef struct
{
    uint32_t CanId;
    MCan_IdType CanIdType;
    MCan_DlcType CanDlc;
    uint8_t* CanSdu;
} CanIf_PduType;

typedef struct 
{
    uint8_t CanMsgIdNumber;
    MCan_DirType MCanDir;
    CanIf_PduType CanPdu;
}CanIf_MessageConfigType;

typedef struct 
{
    uint8_t CanNumberOfMsgs;
    CanIf_MessageConfigType *CanIfMessageConfig;
}CanIf_MsgObjType;


#endif