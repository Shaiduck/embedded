#include "canif.h"
#include "mcan.h"

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

void CanIf_InitMessage(uint8_t CanChannelId, CanIf_MsgObjType CanIfMsgConfig)
{

}

void CanIf_GetConfiguration(uint8_t CanChannelId, MCan_ConfigType* MCan_Config)
{

    //CanIf_InitMessage(CanChannelId, &CanIfMsgConfig);
}

void CanIf_Init(uint8_t CanChannelId, CanIf_MsgObjType CanIfMsgConfig)
{
    MCan_ConfigType mcan1Config;
    CanIf_GetConfiguration(CanChannelId, &mcan1Config);
    MCAN_Init(&mcan1Config);


}