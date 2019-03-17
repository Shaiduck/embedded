#include "canif.h"

static uint32_t can0MsgRam[MCAN0_STD_FLTS_WRDS + 
						   MCAN0_EXT_FLTS_WRDS + 
						   MCAN0_RX_FIFO0_WRDS + 
						   MCAN0_RX_FIFO1_WRDS + 
						   MCAN0_RX_DED_BUFS_WRDS + 
						   MCAN0_TX_EVT_FIFO_WRDS + 
						   MCAN0_TX_DED_BUF_WRDS + 
						   MCAN0_TX_FIFO_Q_WRDS];

static uint32_t can1MsgRam[MCAN1_STD_FLTS_WRDS + 
						   MCAN1_EXT_FLTS_WRDS + 
						   MCAN1_RX_FIFO0_WRDS + 
						   MCAN1_RX_FIFO1_WRDS + 
						   MCAN1_RX_DED_BUFS_WRDS + 
						   MCAN1_TX_EVT_FIFO_WRDS + 
						   MCAN1_TX_DED_BUF_WRDS + 
						   MCAN1_TX_FIFO_Q_WRDS];

Mcan		* pMCan[2] = {MCAN0, MCAN1};
uint32_t	bitTiming[2] = {MCAN_BTP_BRP(MCAN0_BRP) | MCAN_BTP_TSEG1(MCAN0_TSEG1) | MCAN_BTP_TSEG2(MCAN0_TSEG2) | MCAN_BTP_SJW(MCAN0_SJW),
                            MCAN_BTP_BRP(MCAN1_BRP) | MCAN_BTP_TSEG1(MCAN1_TSEG1) | MCAN_BTP_TSEG2(MCAN1_TSEG2) | MCAN_BTP_SJW(MCAN1_SJW)};
uint32_t	fastBitTiming[2] = {MCAN_FBTP_FBRP(MCAN0_FBRP) | MCAN_FBTP_FTSEG1(MCAN0_FTSEG1) | MCAN_FBTP_FTSEG2(MCAN0_FTSEG2) | MCAN_FBTP_FSJW(MCAN0_FSJW),
                                MCAN_FBTP_FBRP(MCAN1_FBRP) | MCAN_FBTP_FTSEG1(MCAN1_FTSEG1) | MCAN_FBTP_FTSEG2(MCAN1_FTSEG2) | MCAN_FBTP_FSJW(MCAN1_FSJW)};
uint32_t	nmbrStdFilts[2] = {MCAN0_NMBR_STD_FLTS, MCAN1_NMBR_STD_FLTS};
uint32_t	nmbrExtFilts[2] = {MCAN0_NMBR_EXT_FLTS, MCAN1_NMBR_EXT_FLTS};  
uint32_t	nmbrFifo0Elmts[2] = {MCAN0_NMBR_RX_FIFO0_ELMTS, MCAN1_NMBR_RX_FIFO0_ELMTS};
uint32_t	nmbrFifo1Elmts[2] = {MCAN0_NMBR_RX_FIFO1_ELMTS, MCAN1_NMBR_RX_FIFO1_ELMTS};
uint32_t	nmbrRxDedBufElmts[2] = {MCAN0_NMBR_RX_DED_BUF_ELMTS, MCAN1_NMBR_RX_DED_BUF_ELMTS};
uint32_t	nmbrTxEvtFifoElmts[2] = {MCAN0_NMBR_TX_EVT_FIFO_ELMTS, MCAN1_NMBR_TX_EVT_FIFO_ELMTS};
uint32_t	nmbrTxDedBufElmts[2] = {MCAN0_NMBR_TX_DED_BUF_ELMTS, MCAN1_NMBR_TX_DED_BUF_ELMTS};
uint32_t	nmbrTxFifoQElmts[2] = {MCAN0_NMBR_TX_FIFO_Q_ELMTS, MCAN1_NMBR_TX_FIFO_Q_ELMTS};
uint32_t	rxFifo0ElmtSize[2] = {(MCAN0_RX_FIFO0_DATA_SIZE << 29) | ((MCAN0_RX_FIFO0_ELMT_SZ/4)+2), 
                                    (MCAN1_RX_FIFO0_DATA_SIZE << 29) | ((MCAN1_RX_FIFO0_ELMT_SZ/4)+2)};
uint32_t	rxFifo1ElmtSize[2] = {(MCAN1_RX_FIFO1_DATA_SIZE << 29) | ((MCAN1_RX_FIFO1_ELMT_SZ/4)+2), 
                                    (MCAN0_RX_FIFO1_DATA_SIZE << 29) | ((MCAN0_RX_FIFO1_ELMT_SZ/4)+2)};
uint32_t	rxBufElmtSize[2] = {(MCAN1_RX_BUF_DATA_SIZE << 29) | ((MCAN1_RX_BUF_ELMT_SZ/4)+2), 
                                (MCAN0_RX_BUF_DATA_SIZE << 29) | ((MCAN0_RX_BUF_ELMT_SZ/4)+2)};
uint32_t    txBufElmtSize[2] = {(MCAN0_TX_BUF_DATA_SIZE << 29) | ((MCAN0_TX_BUF_ELMT_SZ/4)+2), 
                                (MCAN1_TX_BUF_DATA_SIZE << 29) | ((MCAN1_TX_BUF_ELMT_SZ/4)+2)};

uint8_t *buffer;
uint8_t buffernumber = 0;
uint8_t Buff0Ctr = 0xFF;
uint8_t Buff1Ctr = 0x80;
uint8_t Buff2Ctr = 0x00;

CanIf_MsgObjType msgCopy;

void CanIf_GetConfiguration(uint8_t CanChannelId, MCan_ConfigType* MCan_Config)
{
	MCan_Config-> pMCan = pMCan[CanChannelId];
	MCan_Config->bitTiming = bitTiming[CanChannelId];

	MCan_Config->fastBitTiming =  fastBitTiming[CanChannelId];
	MCan_Config->nmbrStdFilts =  nmbrStdFilts[CanChannelId];
	MCan_Config->nmbrExtFilts =  nmbrExtFilts[CanChannelId];
	MCan_Config->nmbrFifo0Elmts =  nmbrFifo0Elmts[CanChannelId];
	MCan_Config->nmbrFifo1Elmts =  nmbrFifo1Elmts[CanChannelId];
	MCan_Config->nmbrRxDedBufElmts =  nmbrRxDedBufElmts[CanChannelId];
	MCan_Config->nmbrTxEvtFifoElmts =  nmbrTxEvtFifoElmts[CanChannelId];
	MCan_Config->nmbrTxDedBufElmts =  nmbrTxDedBufElmts[CanChannelId];
	MCan_Config->nmbrTxFifoQElmts  =  nmbrTxFifoQElmts[CanChannelId];
	MCan_Config->rxFifo0ElmtSize =  rxFifo0ElmtSize[CanChannelId];
	MCan_Config->rxFifo1ElmtSize =  rxFifo1ElmtSize[CanChannelId];
	MCan_Config->rxBufElmtSize =  rxBufElmtSize[CanChannelId];
	MCan_Config->txBufElmtSize =  txBufElmtSize[CanChannelId];
	
	switch (CanChannelId)
	{
		case 0:
			MCan_Config->msgRam.pStdFilts = &can0MsgRam[0];
			MCan_Config->msgRam.pExtFilts = &can0MsgRam[MCAN0_STD_FLTS_WRDS];
			MCan_Config->msgRam.pRxFifo0 = &can0MsgRam[MCAN0_STD_FLTS_WRDS + MCAN0_EXT_FLTS_WRDS];
			MCan_Config->msgRam.pRxFifo1 = &can0MsgRam[MCAN0_STD_FLTS_WRDS + MCAN0_EXT_FLTS_WRDS + MCAN0_RX_FIFO0_WRDS];
			MCan_Config->msgRam.pRxDedBuf = &can0MsgRam[MCAN0_STD_FLTS_WRDS + MCAN0_EXT_FLTS_WRDS + MCAN0_RX_FIFO0_WRDS + MCAN0_RX_FIFO1_WRDS];
			MCan_Config->msgRam.pTxEvtFifo = &can0MsgRam[MCAN0_STD_FLTS_WRDS + MCAN0_EXT_FLTS_WRDS + MCAN0_RX_FIFO0_WRDS + MCAN0_RX_FIFO1_WRDS + MCAN0_RX_DED_BUFS_WRDS];
			MCan_Config->msgRam.pTxDedBuf = &can0MsgRam[MCAN0_STD_FLTS_WRDS + MCAN0_EXT_FLTS_WRDS + MCAN0_RX_FIFO0_WRDS + MCAN0_RX_FIFO1_WRDS + MCAN0_RX_DED_BUFS_WRDS + MCAN0_TX_EVT_FIFO_WRDS];
			MCan_Config->msgRam.pTxFifoQ = &can0MsgRam[MCAN0_STD_FLTS_WRDS + MCAN0_EXT_FLTS_WRDS + MCAN0_RX_FIFO0_WRDS + MCAN0_RX_FIFO1_WRDS + MCAN0_RX_DED_BUFS_WRDS + MCAN0_TX_EVT_FIFO_WRDS + MCAN0_TX_DED_BUF_WRDS];
			break;
		case 1:
			MCan_Config->msgRam.pStdFilts = &can1MsgRam[0];
			MCan_Config->msgRam.pExtFilts = &can1MsgRam[MCAN1_STD_FLTS_WRDS];
			MCan_Config->msgRam.pRxFifo0 = &can1MsgRam[MCAN1_STD_FLTS_WRDS + MCAN1_EXT_FLTS_WRDS];
			MCan_Config->msgRam.pRxFifo1 = &can1MsgRam[MCAN1_STD_FLTS_WRDS + MCAN1_EXT_FLTS_WRDS + MCAN1_RX_FIFO0_WRDS];
			MCan_Config->msgRam.pRxDedBuf = &can1MsgRam[MCAN1_STD_FLTS_WRDS + MCAN1_EXT_FLTS_WRDS + MCAN1_RX_FIFO0_WRDS + MCAN1_RX_FIFO1_WRDS];
			MCan_Config->msgRam.pTxEvtFifo = &can1MsgRam[MCAN1_STD_FLTS_WRDS + MCAN1_EXT_FLTS_WRDS + MCAN1_RX_FIFO0_WRDS + MCAN1_RX_FIFO1_WRDS + MCAN1_RX_DED_BUFS_WRDS];
			MCan_Config->msgRam.pTxDedBuf = &can1MsgRam[MCAN1_STD_FLTS_WRDS + MCAN1_EXT_FLTS_WRDS + MCAN1_RX_FIFO0_WRDS + MCAN1_RX_FIFO1_WRDS + MCAN1_RX_DED_BUFS_WRDS + MCAN1_TX_EVT_FIFO_WRDS];
			MCan_Config->msgRam.pTxFifoQ = &can1MsgRam[MCAN1_STD_FLTS_WRDS + MCAN1_EXT_FLTS_WRDS + MCAN1_RX_FIFO0_WRDS + MCAN1_RX_FIFO1_WRDS + MCAN1_RX_DED_BUFS_WRDS + MCAN1_TX_EVT_FIFO_WRDS + MCAN1_TX_DED_BUF_WRDS];
			break;
	}
}

void CanIf_Init(uint8_t CanChannelId, CanIf_MsgObjType CanIfMsgConfig)
{
    MCan_ConfigType ifCanConfig;
    CanIf_GetConfiguration(CanChannelId, &ifCanConfig);
    MCAN_Init(&ifCanConfig);
	//MCAN_InitTxQueue(loc_mcan_Config);
	MCAN_Enable(&mcan1Config);
	msgCopy = CanIfMsgConfig;
}

void CanIf_Transmit(uint8_t CanChannelId, uint8_t MsgId)
{
	static uint8_t ifCanBuffInit[] = {0, 0, 0, 0};
    MCan_ConfigType ifCanConfig;
    CanIf_GetConfiguration(CanChannelId, &ifCanConfig);

	if(ifCanBuffInit[MsgId] == 0)
	{
		ifCanBuffInit[MsgId] = 1;
		// buffer = MCAN_ConfigTxDedBuffer( &ifCanConfig, buffernumber, CanTxMsg[MsgId].CanPdu.CanId, CanTxMsg[MsgId].CanPdu.CanIdType, CanTxMsg[MsgId].CanPdu.CanDlc);
		buffer = MCAN_ConfigTxDedBuffer( &ifCanConfig, buffernumber, msgCopy.CanIfMessageConfig[MsgId].CanPdu.CanId,
																	msgCopy.CanIfMessageConfig[MsgId].CanPdu.CanIdType, 
																	msgCopy.CanIfMessageConfig[MsgId].CanPdu.CanDlc);
	}
	else
	{
		buffer[0] = Buff0Ctr;
		buffer[1] = Buff1Ctr;
		buffer[2] = Buff2Ctr;
    	MCAN_SendTxDedBuffer( &mcan1Config, buffernumber );
	}
}

void CanIf_IncreaseBuffer(uint8_t bufferNum)
{
	switch (bufferNum)
	{
		case 0:
			Buff0Ctr++;
		break;
		case 1:
			Buff1Ctr++;
		break;
		case 2:
			Buff2Ctr++;
		break;
	}
}

void CanIf_ResetBuffer(uint8_t bufferNum)
{
	switch (bufferNum)
	{
		case 0:
			Buff0Ctr = 0;
		break;
		case 1:
			Buff1Ctr = 0;
		break;
		case 2:
			Buff2Ctr = 0;
		break;
	}

}