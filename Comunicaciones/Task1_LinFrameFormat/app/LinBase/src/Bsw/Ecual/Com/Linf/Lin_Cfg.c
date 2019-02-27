/*******************************************************************************/
/**
\file       Lin_Cfg.c
\brief      
   \~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   \version       1.1
   \author        
   \description   
   \date          
*/

#include "Lin.h"

LinChannelType LinCh[] = {
    {
        CHANNEL_LIN4,
        BAUDRATE_115200,
    },
    {
        CHANNEL_LIN2,
        BAUDRATE_115200,
    },
};

LinConfigType LinChannelConfig[] = {
    sizeof(LinCh) / sizeof(LinChannelType), //number of channels
    &LinCh[0],
};