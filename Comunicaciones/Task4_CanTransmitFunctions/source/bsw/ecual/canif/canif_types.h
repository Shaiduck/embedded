#ifndef _CANIF_TYPES_
#define _CANIF_TYPES_

#include "mcan.h"
#include "mcan_config.h"

#define MAILBOX_ADDRESS(address) ( 0xFFFC & (address) )

#define CAN_CLK_FREQ_HZ               MCAN_PROG_CLK_FREQ_HZ

#define MCAN0_TSEG1                   ( MCAN0_PROP_SEG + MCAN0_PHASE_SEG1 )
#define MCAN0_TSEG2                   ( MCAN0_PHASE_SEG2 )
#define MCAN0_BRP                     ((uint32_t) (( (float) CAN_CLK_FREQ_HZ / \
									((float)( MCAN0_TSEG1 + MCAN0_TSEG2 + 3 ) *\
									(float) MCAN0_BIT_RATE_BPS )) - 1 ))
#define MCAN0_SJW                     ( MCAN0_SYNC_JUMP - 1 )
#define MCAN0_FTSEG1                  ( MCAN0_FAST_PROP_SEG + MCAN0_FAST_PHASE_SEG1 )
#define MCAN0_FTSEG2                  ( MCAN0_FAST_PHASE_SEG2 )
#define MCAN0_FBRP                    ((uint32_t) (( (float) CAN_CLK_FREQ_HZ / \
									((float)( MCAN0_FTSEG1 + MCAN0_FTSEG2 + 3 ) * \
									(float) MCAN0_FAST_BIT_RATE_BPS )) - 1 ))
#define MCAN0_FSJW                    ( MCAN0_FAST_SYNC_JUMP - 1 )

#define MCAN0_STD_FLTS_WRDS           (MCAN0_NMBR_STD_FLTS)  
									/* 128 max filters */
#define MCAN0_EXT_FLTS_WRDS           (MCAN0_NMBR_EXT_FLTS * 2)  
									/* 64 max filters */
#define MCAN0_RX_FIFO0_WRDS           (MCAN0_NMBR_RX_FIFO0_ELMTS * \
									((MCAN0_RX_FIFO0_ELMT_SZ/4) + 2)) 
									/* 64 elements max */
#define MCAN0_RX_FIFO1_WRDS           (MCAN0_NMBR_RX_FIFO1_ELMTS *\
									((MCAN0_RX_FIFO1_ELMT_SZ/4) + 2))  
									/* 64 elements max */
#define MCAN0_RX_DED_BUFS_WRDS            (MCAN0_NMBR_RX_DED_BUF_ELMTS * \
										((MCAN0_RX_BUF_ELMT_SZ/4) + 2)) 
									/* 64 elements max */
#define MCAN0_TX_EVT_FIFO_WRDS        (MCAN0_NMBR_TX_EVT_FIFO_ELMTS * 2)  
									/* 32 elements max */
#define MCAN0_TX_DED_BUF_WRDS         (MCAN0_NMBR_TX_DED_BUF_ELMTS * \
									((MCAN0_TX_BUF_ELMT_SZ/4) + 2))  
									/* 32 elements max */
#define MCAN0_TX_FIFO_Q_WRDS          (MCAN0_NMBR_TX_FIFO_Q_ELMTS *\
									((MCAN0_TX_BUF_ELMT_SZ/4) + 2))  
									/* 32 elements max */

#define MCAN1_TSEG1                   ( MCAN1_PROP_SEG + MCAN1_PHASE_SEG1 )
#define MCAN1_TSEG2                   ( MCAN1_PHASE_SEG2 )
#define MCAN1_BRP                     ((uint32_t) (( (float) CAN_CLK_FREQ_HZ / \
									((float)( MCAN1_TSEG1 + MCAN1_TSEG2 + 3 ) *\
									(float) MCAN1_BIT_RATE_BPS )) - 1 ))
#define MCAN1_SJW                     ( MCAN1_SYNC_JUMP - 1 )
#define MCAN1_FTSEG1                  ( MCAN1_FAST_PROP_SEG + MCAN1_FAST_PHASE_SEG1 )
#define MCAN1_FTSEG2                  ( MCAN1_FAST_PHASE_SEG2 )
#define MCAN1_FBRP                    ((uint32_t) (( (float) CAN_CLK_FREQ_HZ /\
									((float)( MCAN1_FTSEG1 + MCAN1_FTSEG2 + 3 ) *\
									(float) MCAN1_FAST_BIT_RATE_BPS )) - 1 ))
#define MCAN1_FSJW                    ( MCAN1_FAST_SYNC_JUMP - 1 )

#define MCAN1_STD_FLTS_WRDS           (MCAN1_NMBR_STD_FLTS)  
									/* 128 max filters */
#define MCAN1_EXT_FLTS_WRDS           (MCAN1_NMBR_EXT_FLTS * 2)  
									/* 64 max filters */
#define MCAN1_RX_FIFO0_WRDS           (MCAN1_NMBR_RX_FIFO0_ELMTS * \
									((MCAN1_RX_FIFO0_ELMT_SZ/4) + 2))  
									/* 64 elements max */
#define MCAN1_RX_FIFO1_WRDS           (MCAN1_NMBR_RX_FIFO1_ELMTS *\
									((MCAN1_RX_FIFO1_ELMT_SZ/4) + 2))  
									/* 64 elements max */
#define MCAN1_RX_DED_BUFS_WRDS            (MCAN1_NMBR_RX_DED_BUF_ELMTS * \
									((MCAN1_RX_BUF_ELMT_SZ/4) + 2))  
									/* 64 elements max */
#define MCAN1_TX_EVT_FIFO_WRDS        (MCAN1_NMBR_TX_EVT_FIFO_ELMTS * 2)  
/* 32 elements max */
#define MCAN1_TX_DED_BUF_WRDS         (MCAN1_NMBR_TX_DED_BUF_ELMTS * \
									((MCAN1_TX_BUF_ELMT_SZ/4) + 2))  
									/* 32 elements max */
#define MCAN1_TX_FIFO_Q_WRDS          (MCAN1_NMBR_TX_FIFO_Q_ELMTS * \
									((MCAN1_TX_BUF_ELMT_SZ/4) + 2))  
									/* 32 elements max */

/* validate CAN0 entries */
#if ( MCAN0_TSEG1 > 63 ) 
#error "Invalid CAN0 TSEG1"  
#endif
#if (  MCAN0_TSEG2 > 15 ) 
#error "Invalid CAN0 TSEG2"  
#endif
#if ( MCAN0_SJW > 15 ) 
#error "Invalid CAN0 SJW"  
#endif
#if ( MCAN0_FTSEG1 > 15 ) 
#error "Invalid CAN0 FTSEG1"  
#endif
#if (  MCAN0_FTSEG2 > 7 ) 
#error "Invalid CAN0 FTSEG2"  
#endif
#if ( MCAN0_FSJW > 3 ) 
#error "Invalid CAN0 FSJW"  
#endif

#if ( MCAN0_NMBR_STD_FLTS > 128 ) 
#error "Invalid CAN0 # of Standard Filters"  
#endif
#if ( MCAN0_NMBR_EXT_FLTS > 64 ) 
#error "Invalid CAN0 # of Extended Filters"  
#endif
#if ( MCAN0_NMBR_RX_FIFO0_ELMTS > 64 ) 
#error "Invalid CAN0 # RX FIFO 0 ELEMENTS"  
#endif
#if ( MCAN0_NMBR_RX_FIFO1_ELMTS > 64 ) 
#error "Invalid CAN0 # RX FIFO 0 ELEMENTS"  
#endif
#if ( MCAN0_NMBR_RX_DED_BUF_ELMTS > 64 ) 
#error "Invalid CAN0 # RX BUFFER ELEMENTS"  
#endif
#if ( MCAN0_NMBR_TX_EVT_FIFO_ELMTS > 32 ) 
#error "Invalid CAN0 # TX EVENT FIFO ELEMENTS"  
#endif
#if ( (MCAN0_NMBR_TX_DED_BUF_ELMTS + MCAN0_NMBR_TX_FIFO_Q_ELMTS)  > 32 ) 
#error "Invalid CAN0 # TX BUFFER ELEMENTS"  
#endif

#if   ( 8 == MCAN0_RX_FIFO0_ELMT_SZ )
#define MCAN0_RX_FIFO0_DATA_SIZE  (0u)
#elif ( 12 == MCAN0_RX_FIFO0_ELMT_SZ )
#define MCAN0_RX_FIFO0_DATA_SIZE  (1u)
#elif ( 16 == MCAN0_RX_FIFO0_ELMT_SZ )
#define MCAN0_RX_FIFO0_DATA_SIZE  (2u)
#elif ( 20 == MCAN0_RX_FIFO0_ELMT_SZ )
#define MCAN0_RX_FIFO0_DATA_SIZE  (3u)
#elif ( 24 == MCAN0_RX_FIFO0_ELMT_SZ )
#define MCAN0_RX_FIFO0_DATA_SIZE  (4u)
#elif ( 32 == MCAN0_RX_FIFO0_ELMT_SZ )
#define MCAN0_RX_FIFO0_DATA_SIZE  (5u)
#elif ( 48 == MCAN0_RX_FIFO0_ELMT_SZ )
#define MCAN0_RX_FIFO0_DATA_SIZE  (6u)
#elif ( 64 == MCAN0_RX_FIFO0_ELMT_SZ )
#define MCAN0_RX_FIFO0_DATA_SIZE  (7u)
#else
#error "Invalid CAN0 RX FIFO0 ELEMENT SIZE"
#endif

#if   ( 8 == MCAN0_RX_FIFO1_ELMT_SZ )
#define MCAN0_RX_FIFO1_DATA_SIZE  (0u)
#elif ( 12 == MCAN0_RX_FIFO1_ELMT_SZ )
#define MCAN0_RX_FIFO1_DATA_SIZE  (1u)
#elif ( 16 == MCAN0_RX_FIFO1_ELMT_SZ )
#define MCAN0_RX_FIFO1_DATA_SIZE  (2u)
#elif ( 20 == MCAN0_RX_FIFO1_ELMT_SZ )
#define MCAN0_RX_FIFO1_DATA_SIZE  (3u)
#elif ( 24 == MCAN0_RX_FIFO1_ELMT_SZ )
#define MCAN0_RX_FIFO1_DATA_SIZE  (4u)
#elif ( 32 == MCAN0_RX_FIFO1_ELMT_SZ )
#define MCAN0_RX_FIFO1_DATA_SIZE  (5u)
#elif ( 48 == MCAN0_RX_FIFO1_ELMT_SZ )
#define MCAN0_RX_FIFO1_DATA_SIZE  (6u)
#elif ( 64 == MCAN0_RX_FIFO1_ELMT_SZ )
#define MCAN0_RX_FIFO1_DATA_SIZE  (7u)
#else
#error "Invalid CAN0 RX FIFO1 ELEMENT SIZE"
#endif

#if   ( 8 == MCAN0_RX_BUF_ELMT_SZ )
#define MCAN0_RX_BUF_DATA_SIZE  (0u)
#elif ( 12 == MCAN0_RX_BUF_ELMT_SZ )
#define MCAN0_RX_BUF_DATA_SIZE  (1u)
#elif ( 16 == MCAN0_RX_BUF_ELMT_SZ )
#define MCAN0_RX_BUF_DATA_SIZE  (2u)
#elif ( 20 == MCAN0_RX_BUF_ELMT_SZ )
#define MCAN0_RX_BUF_DATA_SIZE  (3u)
#elif ( 24 == MCAN0_RX_BUF_ELMT_SZ )
#define MCAN0_RX_BUF_DATA_SIZE  (4u)
#elif ( 32 == MCAN0_RX_BUF_ELMT_SZ )
#define MCAN0_RX_BUF_DATA_SIZE  (5u)
#elif ( 48 == MCAN0_RX_BUF_ELMT_SZ )
#define MCAN0_RX_BUF_DATA_SIZE  (6u)
#elif ( 64 == MCAN0_RX_BUF_ELMT_SZ )
#define MCAN0_RX_BUF_DATA_SIZE  (7u)
#else
#error "Invalid CAN0 RX BUFFER ELEMENT SIZE"
#endif

#if   ( 8 == MCAN0_TX_BUF_ELMT_SZ )
#define MCAN0_TX_BUF_DATA_SIZE  (0u)
#elif ( 12 == MCAN0_TX_BUF_ELMT_SZ )
#define MCAN0_TX_BUF_DATA_SIZE  (1u)
#elif ( 16 == MCAN0_TX_BUF_ELMT_SZ )
#define MCAN0_TX_BUF_DATA_SIZE  (2u)
#elif ( 20 == MCAN0_TX_BUF_ELMT_SZ )
#define MCAN0_TX_BUF_DATA_SIZE  (3u)
#elif ( 24 == MCAN0_TX_BUF_ELMT_SZ )
#define MCAN0_TX_BUF_DATA_SIZE  (4u)
#elif ( 32 == MCAN0_TX_BUF_ELMT_SZ )
#define MCAN0_TX_BUF_DATA_SIZE  (5u)
#elif ( 48 == MCAN0_TX_BUF_ELMT_SZ )
#define MCAN0_TX_BUF_DATA_SIZE  (6u)
#elif ( 64 == MCAN0_TX_BUF_ELMT_SZ )
#define MCAN0_TX_BUF_DATA_SIZE  (7u)
#else
#error "Invalid CAN0 TX BUFFER ELEMENT SIZE"
#endif

/* validate CAN1 entries */
#if ( MCAN1_TSEG1 > 63 ) 
#error "Invalid CAN1 TSEG1"  
#endif
#if (  MCAN1_TSEG2 > 15 ) 
#error "Invalid CAN1 TSEG2"  
#endif
#if ( MCAN1_SJW > 15 ) 
#error "Invalid CAN1 SJW"  
#endif
#if ( MCAN1_FTSEG1 > 15 ) 
#error "Invalid CAN1 FTSEG1"  
#endif
#if (  MCAN1_FTSEG2 > 7 ) 
#error "Invalid CAN1 FTSEG2"  
#endif
#if ( MCAN1_FSJW > 3 ) 
#error "Invalid CAN1 FSJW"  
#endif

#if ( MCAN1_NMBR_STD_FLTS > 128 ) 
#error "Invalid CAN1 # of Standard Filters"  
#endif
#if ( MCAN1_NMBR_EXT_FLTS > 64 ) 
#error "Invalid CAN1 # of Extended Filters"  
#endif
#if ( MCAN1_NMBR_RX_FIFO0_ELMTS > 64 ) 
#error "Invalid CAN1 # RX FIFO 0 ELEMENTS"  
#endif
#if ( MCAN1_NMBR_RX_FIFO1_ELMTS > 64 ) 
#error "Invalid CAN1 # RX FIFO 0 ELEMENTS"  
#endif
#if ( MCAN1_NMBR_RX_DED_BUF_ELMTS > 64 ) 
#error "Invalid CAN1 # RX BUFFER ELEMENTS"  
#endif
#if ( MCAN1_NMBR_TX_EVT_FIFO_ELMTS > 32 ) 
#error "Invalid CAN1 # TX EVENT FIFO ELEMENTS"  
#endif
#if ( (MCAN1_NMBR_TX_DED_BUF_ELMTS + MCAN1_NMBR_TX_FIFO_Q_ELMTS)  > 32 ) 
#error "Invalid CAN1 # TX BUFFER ELEMENTS"  
#endif

#if   ( 8 == MCAN1_RX_FIFO0_ELMT_SZ )
#define MCAN1_RX_FIFO0_DATA_SIZE  (0u)
#elif ( 12 == MCAN1_RX_FIFO0_ELMT_SZ )
#define MCAN1_RX_FIFO0_DATA_SIZE  (1u)
#elif ( 16 == MCAN1_RX_FIFO0_ELMT_SZ )
#define MCAN1_RX_FIFO0_DATA_SIZE  (2u)
#elif ( 20 == MCAN1_RX_FIFO0_ELMT_SZ )
#define MCAN1_RX_FIFO0_DATA_SIZE  (3u)
#elif ( 24 == MCAN1_RX_FIFO0_ELMT_SZ )
#define MCAN1_RX_FIFO0_DATA_SIZE  (4u)
#elif ( 32 == MCAN1_RX_FIFO0_ELMT_SZ )
#define MCAN1_RX_FIFO0_DATA_SIZE  (5u)
#elif ( 48 == MCAN1_RX_FIFO0_ELMT_SZ )
#define MCAN1_RX_FIFO0_DATA_SIZE  (6u)
#elif ( 64 == MCAN1_RX_FIFO0_ELMT_SZ )
#define MCAN1_RX_FIFO0_DATA_SIZE  (7u)
#else
#error "Invalid CAN1 RX FIFO0 ELEMENT SIZE"
#endif

#if   ( 8 == MCAN1_RX_FIFO1_ELMT_SZ )
#define MCAN1_RX_FIFO1_DATA_SIZE  (0u)
#elif ( 12 == MCAN1_RX_FIFO1_ELMT_SZ )
#define MCAN1_RX_FIFO1_DATA_SIZE  (1u)
#elif ( 16 == MCAN1_RX_FIFO1_ELMT_SZ )
#define MCAN1_RX_FIFO1_DATA_SIZE  (2u)
#elif ( 20 == MCAN1_RX_FIFO1_ELMT_SZ )
#define MCAN1_RX_FIFO1_DATA_SIZE  (3u)
#elif ( 24 == MCAN1_RX_FIFO1_ELMT_SZ )
#define MCAN1_RX_FIFO1_DATA_SIZE  (4u)
#elif ( 32 == MCAN1_RX_FIFO1_ELMT_SZ )
#define MCAN1_RX_FIFO1_DATA_SIZE  (5u)
#elif ( 48 == MCAN1_RX_FIFO1_ELMT_SZ )
#define MCAN1_RX_FIFO1_DATA_SIZE  (6u)
#elif ( 64 == MCAN1_RX_FIFO1_ELMT_SZ )
#define MCAN1_RX_FIFO1_DATA_SIZE  (7u)
#else
#error "Invalid CAN1 RX FIFO1 ELEMENT SIZE"
#endif

#if   ( 8 == MCAN1_RX_BUF_ELMT_SZ )
#define MCAN1_RX_BUF_DATA_SIZE  (0u)
#elif ( 12 == MCAN1_RX_BUF_ELMT_SZ )
#define MCAN1_RX_BUF_DATA_SIZE  (1u)
#elif ( 16 == MCAN1_RX_BUF_ELMT_SZ )
#define MCAN1_RX_BUF_DATA_SIZE  (2u)
#elif ( 20 == MCAN1_RX_BUF_ELMT_SZ )
#define MCAN1_RX_BUF_DATA_SIZE  (3u)
#elif ( 24 == MCAN1_RX_BUF_ELMT_SZ )
#define MCAN1_RX_BUF_DATA_SIZE  (4u)
#elif ( 32 == MCAN1_RX_BUF_ELMT_SZ )
#define MCAN1_RX_BUF_DATA_SIZE  (5u)
#elif ( 48 == MCAN1_RX_BUF_ELMT_SZ )
#define MCAN1_RX_BUF_DATA_SIZE  (6u)
#elif ( 64 == MCAN1_RX_BUF_ELMT_SZ )
#define MCAN1_RX_BUF_DATA_SIZE  (7u)
#else
#error "Invalid CAN1 RX BUFFER ELEMENT SIZE"
#endif

#if   ( 8 == MCAN1_TX_BUF_ELMT_SZ )
#define MCAN1_TX_BUF_DATA_SIZE  (0u)
#elif ( 12 == MCAN1_TX_BUF_ELMT_SZ )
#define MCAN1_TX_BUF_DATA_SIZE  (1u)
#elif ( 16 == MCAN1_TX_BUF_ELMT_SZ )
#define MCAN1_TX_BUF_DATA_SIZE  (2u)
#elif ( 20 == MCAN1_TX_BUF_ELMT_SZ )
#define MCAN1_TX_BUF_DATA_SIZE  (3u)
#elif ( 24 == MCAN1_TX_BUF_ELMT_SZ )
#define MCAN1_TX_BUF_DATA_SIZE  (4u)
#elif ( 32 == MCAN1_TX_BUF_ELMT_SZ )
#define MCAN1_TX_BUF_DATA_SIZE  (5u)
#elif ( 48 == MCAN1_TX_BUF_ELMT_SZ )
#define MCAN1_TX_BUF_DATA_SIZE  (6u)
#elif ( 64 == MCAN1_TX_BUF_ELMT_SZ )
#define MCAN1_TX_BUF_DATA_SIZE  (7u)
#else
#error "Invalid CAN1 TX BUFFER ELEMENT SIZE"
#endif

#define CAN_11_BIT_ID_MASK                 (0x7FF)
#define CAN_29_BIT_ID_MASK                 (0x1FFFFFFF)
#define ELMT_SIZE_MASK                (0x1F) 
/* max element size is 18 words, fits in 5 bits */

#define BUFFER_XTD_MASK               (0x40000000)
#define BUFFER_EXT_ID_MASK            (0x1FFFFFFF)
#define BUFFER_STD_ID_MASK            (0x1FFC0000)
#define BUFFER_DLC_MASK               (0x000F0000)
#define BUFFER_RXTS_MASK              (0x0000FFFF)

#define STD_FILT_SFT_MASK             (3 << 30)
#define STD_FILT_SFT_RANGE            (0 << 30)
#define STD_FILT_SFT_DUAL             (1 << 30)
#define STD_FILT_SFT_CLASSIC          (2 << 30)
#define STD_FILT_SFEC_MASK            (7 << 27)
#define STD_FILT_SFEC_DISABLE         (0 << 27)
#define STD_FILT_SFEC_FIFO0           (1 << 27)
#define STD_FILT_SFEC_FIFO1           (2 << 27)
#define STD_FILT_SFEC_REJECT          (3 << 27)
#define STD_FILT_SFEC_PRIORITY        (4 << 27)
#define STD_FILT_SFEC_PRIORITY_FIFO0  (5 << 27)
#define STD_FILT_SFEC_PRIORITY_FIFO1  (6 << 27)
#define STD_FILT_SFEC_BUFFER          (7 << 27)
#define STD_FILT_SFID1_MASK           (0x03FF << 16)
#define STD_FILT_SFID2_MASK           (0x3FF << 0)
#define STD_FILT_SFID2_RX_BUFFER      (0 << 9)
#define STD_FILT_SFID2_DEBUG_A        (1 << 9)
#define STD_FILT_SFID2_DEBUG_B        (2 << 9)
#define STD_FILT_SFID2_DEBUG_C        (3 << 9)
#define STD_FILT_SFID2_BUFFER(nmbr)   (nmbr & 0x3F)

#define EXT_FILT_EFEC_MASK            (7 << 29)
#define EXT_FILT_EFEC_DISABLE         (0 << 29)
#define EXT_FILT_EFEC_FIFO0           (1 << 29)
#define EXT_FILT_EFEC_FIFO1           (2 << 29)
#define EXT_FILT_EFEC_REJECT          (3 << 29)
#define EXT_FILT_EFEC_PRIORITY        (4 << 29)
#define EXT_FILT_EFEC_PRIORITY_FIFO0  (5 << 29)
#define EXT_FILT_EFEC_PRIORITY_FIFO1  (6 << 29)
#define EXT_FILT_EFEC_BUFFER          (7 << 29)
#define EXT_FILT_EFID1_MASK           (0x1FFFFFFF)
#define EXT_FILT_EFT_MASK             (3 << 30)
#define EXT_FILT_EFT_RANGE            (0 << 30)
#define EXT_FILT_EFT_DUAL             (1 << 30)
#define EXT_FILT_EFT_CLASSIC          (2 << 30)
#define EXT_FILT_EFT_RANGE_NO_XIDAM   (3 << 30)
#define EXT_FILT_EFID2_MASK           (0x1FFFFFFF)
#define EXT_FILT_EFID2_RX_BUFFER      (0 << 9)
#define EXT_FILT_EFID2_DEBUG_A        (1 << 9)
#define EXT_FILT_EFID2_DEBUG_B        (2 << 9)
#define EXT_FILT_EFID2_DEBUG_C        (3 << 9)
#define EXT_FILT_EFID2_BUFFER(nmbr)   (nmbr & 0x3F)

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