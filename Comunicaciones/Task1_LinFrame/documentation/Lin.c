
void Lin_StateHandler( void ){
	switch(LinState){
		case SEND_IDLE:
		  /* Ensure ISR's used are disabled */
		  /* Enabling-Disabling Rx and Tx interrupts has to be handled accordingly */
		  Uart_EnableInt(0,CFG_INT_RXRDY,0);
		  Uart_EnableInt(0,CFG_INT_TXRDY,0);
		  break;
		case SEND_BREAK:
		  Uart_SendByte(0,0x00);
		  Uart_EnableInt(0,CFG_INT_TXRDY,1);
		  LinState = SEND_SYNC;
		  break;
		case SEND_SYNC:
		  Uart_SendByte(0,0x55);
		  LinState = SEND_PID;
		  break;
		case SEND_PID:
		  /* For the Lin project, you might need to calculate the PID */
		  Uart_SendByte(0,PduLinPid);
		  LinState = SEND_RESPONSE;
		  /*
			For the project you need to consider if you will wait for a response or will send a response, there fore LinState should be changed accordingly. 
			e.g. LinState = SEND_RESPONSE or LinState = GET_RESPONSE (additional state to handle RX from slaves)
			If GET_RESPONSE then Tx interrupts should be disabled, and Rx interrupts enabled. Both isr's should call Lin_Isr();
		  */
		  break;   
		case SEND_RESPONSE:
		  
		  /* 
			In your project, the number of data will be sent according to the data lenght from the PDU information, therefore a sub-state machine should be considered, or to handle here each byte sent. e.g.
			If ( LinResponseType == MASTER_RESPONSE)
			{
				If (DataSentCtrlCounter < SduDataLength )
				{
					Uart_SendByte(0,SduData[DataSentCtrlCounter]);
					DataSentCtrlCounter++;
					-> Need to calculate Checksum to be sent
				}
				else
				{
					Uart_SendByte(0,LinChecksum);
					DataSentCtrlCounter = 0;
					LinState = IDLE;
				}
			}
		  */
		  break; 
		default: /* Should not be reached */
		  break;
  }          
}

void Lin_SendFrame(uint8_t PduLinPid){
  
  if( LinState == IDLE){
	  PduLinPid = LinPid;
	  /*
		To consider in the Lin project. Prepare the data to be handled while the Lin frame is in progress
		in addition to back up the Lin Pid, you will need to back up the ResponseType, Sdu, etc.
		for (uint8_t SduIdx = 0; SduIdx < SduDataLength; SduIdx++)
		{
			SduData[SduIdx] = LinSduPtr[SduIdx]; It is important to backup the Sdu to avoid data corrupted by higher layers. Remember, SduPtr contains a data address whose data is not under our control.
		}
		DataSentCtrlCounter = 0; -> Will handle the data to be sent if a master response, or to store the data in the corresponding order if a slave response
		
	  */
	  LinState = SEND_BREAK;
	  Lin_StateHandler();
  }
  else{
    /*Command not accepted*/
  }
      
}

void Lin_Isr(void){
  Lin_StateHandler();    
}