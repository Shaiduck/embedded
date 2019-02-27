/*******************************************************************************/
/**
\file       Uart_Cfg.h
\brief      
   \~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   \version       1.1
   \author        
   \description   
   \date          
*/
#ifndef _LIN_CFG_H
#define _LIN_CFG_H

#include "Lin.h"

#define CHANNEL_LIN1 1
#define CHANNEL_LIN2 2
#define CHANNEL_LIN3 3
#define CHANNEL_LIN4 4
#define CHANNEL_LIN5 5
#define BAUDRATE_9600 9600
#define BAUDRATE_115200 115200

typedef struct
{
  uint8_t LinChannelId;
  uint32_t LinChannelBaudrate;
} LinChannelType;

typedef struct
{
  uint8_t LinNumberOfChannels;
  LinChannelType *LinChannel;
} LinConfigType;

extern LinConfigType LinChannelConfig[];

#endif /* _LIN_CFG_H */