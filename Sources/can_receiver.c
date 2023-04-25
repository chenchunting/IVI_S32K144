
#include "init.h"
#include "can_receiver.h"
#include "uart_receiver.h"
#include "can_pal1.h"
#include "ledstrip.h"
#include "lpuart1_uart.h"


can_message_t can_recvMsg_1,can_tranvMsg_1;

void can_receive(void)
{
	bool repeat_receive = false;
	uint32_t bytesRemaining;
	uint8_t i=0,j=0,recvMsg_length=0,checksum=0,checksum_buff=0;
	uint8_t uart_reply_recvMsg[UART_TRAN_MAX_LENGTH]={0};
	uint8_t uart_tranMsg[UART_TRAN_MAX_LENGTH]={0};

#if CAN_FD_Enable
	CAN_Receive(INST_CAN_PAL0, RX_MAILBOX, &can_recvMsg_1);
	WDG_Refresh(INST_WDG_PAL1);
	while(CAN_GetTransferStatus(INST_CAN_PAL0, RX_MAILBOX) == STATUS_BUSY);

	if(can_recvMsg_1.id == RX_MSG_ID)
	{
		if(can_recvMsg_1.data[0]==0xAA)//ITE
		{
			recvMsg_length = can_recvMsg_1.data[1];
			checksum = can_recvMsg_1.data[recvMsg_length-1];

			for(i=0;i<recvMsg_length-1;i++) checksum_buff+=can_recvMsg_1.data[i];
			checksum_buff=~checksum_buff-1;

			if(checksum == checksum_buff)
			{
				//send uart data
				UART_SendData(INST_LPUART0_UART, can_recvMsg_1.data, recvMsg_length);
				WDG_Refresh(INST_WDG_PAL1);
				while(UART_GetTransmitStatus(INST_LPUART0_UART, &bytesRemaining) != STATUS_SUCCESS);

				//receive uart reply status
				for(i=0;i<4;i++)
				{
					UART_ReceiveData(INST_LPUART0_UART, &uart_reply_recvMsg[i], 1UL);
					WDG_Refresh(INST_WDG_PAL1);
					while(UART_GetReceiveStatus(INST_LPUART0_UART, &bytesRemaining) != STATUS_SUCCESS);
				}

				//check reply status and reply can status
				if(uart_reply_recvMsg[0] == 0xAA && uart_reply_recvMsg[1] == 0x04 && uart_reply_recvMsg[2] == 0xCC && uart_reply_recvMsg[3] == 0x84) can_reply_status(can_success);
				else if(uart_reply_recvMsg[0] == 0xAA && uart_reply_recvMsg[1] == 0x04 && uart_reply_recvMsg[2] == 0xE0 && uart_reply_recvMsg[3] == 0x70) can_reply_status(can_error_header);
				else if(uart_reply_recvMsg[0] == 0xAA && uart_reply_recvMsg[1] == 0x04 && uart_reply_recvMsg[2] == 0xE1 && uart_reply_recvMsg[3] == 0x6F) can_reply_status(can_error_length);
				else can_reply_status(can_error_checksum);
				CAN_Send(INST_CAN_PAL0, TX_MAILBOX, &can_tranvMsg_1);
				WDG_Refresh(INST_WDG_PAL1);
				while(CAN_GetTransferStatus(INST_CAN_PAL0, TX_MAILBOX) == STATUS_BUSY);


			}
			else
			{
				//send error checksum
				can_reply_status(can_error_checksum);
				CAN_Send(INST_CAN_PAL0, TX_MAILBOX, &can_tranvMsg_1);
				WDG_Refresh(INST_WDG_PAL1);
				while(CAN_GetTransferStatus(INST_CAN_PAL0, TX_MAILBOX) == STATUS_BUSY);
			}
		}
		else
		{
			//send error header
			can_reply_status(can_error_header);
			CAN_Send(INST_CAN_PAL0, TX_MAILBOX, &can_tranvMsg_1);
			WDG_Refresh(INST_WDG_PAL1);
			while(CAN_GetTransferStatus(INST_CAN_PAL0, TX_MAILBOX) == STATUS_BUSY);
		}
	}
#else
	WDG_Refresh(INST_WDG_PAL1);
	while(repeat_receive == false)
	{
		CAN_Receive(INST_CAN_PAL0, RX_MAILBOX, &can_recvMsg_1);
		WDG_Refresh(INST_WDG_PAL1);
		while(CAN_GetTransferStatus(INST_CAN_PAL0, RX_MAILBOX) == STATUS_BUSY);

		if(can_recvMsg_1.id == RX_MSG_ID)
		{
			if(can_recvMsg_1.data[0]==0xAA || can_recvMsg_1.data[0]==0xA5)//ITE
			{

				recvMsg_length = can_recvMsg_1.data[1];
				checksum = can_recvMsg_1.data[recvMsg_length-1];

				checksum_buff = 0;
				for(i=0;i<recvMsg_length-1;i++) checksum_buff+=can_recvMsg_1.data[i];
				checksum_buff=~checksum_buff-1;

				if(checksum == checksum_buff)
				{
					for(i=2;i<can_recvMsg_1.length-1;i++)uart_tranMsg[i+5*j] =can_recvMsg_1.data[i];
					if(can_recvMsg_1.data[0]==0xAA)
					{
						if(j != 0)
						{
							uart_tranMsg[0] = 0xAA;
							uart_tranMsg[1] = 5*j+can_recvMsg_1.data[1];
							checksum_buff = 0;
							for(i=0;i<uart_tranMsg[1]-1;i++) checksum_buff+=uart_tranMsg[i];
							uart_tranMsg[uart_tranMsg[1]-1] = ~checksum_buff-1;
							can_reply_status(can_success);
							CAN_Send(INST_CAN_PAL0, TX_MAILBOX, &can_tranvMsg_1);
							WDG_Refresh(INST_WDG_PAL1);
							while(CAN_GetTransferStatus(INST_CAN_PAL0, TX_MAILBOX) == STATUS_BUSY);
						}
						else
						{
							uart_tranMsg[0] = can_recvMsg_1.data[0];
							uart_tranMsg[1] = can_recvMsg_1.data[1];
							uart_tranMsg[can_recvMsg_1.length-1] = can_recvMsg_1.data[can_recvMsg_1.length-1];
						}
						repeat_receive = true;
					}
					if(can_recvMsg_1.data[0]==0xA5)
					{
						can_reply_status(can_success);
						CAN_Send(INST_CAN_PAL0, TX_MAILBOX, &can_tranvMsg_1);
						WDG_Refresh(INST_WDG_PAL1);
						while(CAN_GetTransferStatus(INST_CAN_PAL0, TX_MAILBOX) == STATUS_BUSY);
					}
					j++;
				}
				else
				{
					//send error checksum
					can_reply_status(can_error_checksum);
					CAN_Send(INST_CAN_PAL0, TX_MAILBOX, &can_tranvMsg_1);
					WDG_Refresh(INST_WDG_PAL1);
					while(CAN_GetTransferStatus(INST_CAN_PAL0, TX_MAILBOX) == STATUS_BUSY);
					repeat_receive = true;
				}
			}
			else
			{
				//send error header
				can_reply_status(can_error_header);
				CAN_Send(INST_CAN_PAL0, TX_MAILBOX, &can_tranvMsg_1);
				WDG_Refresh(INST_WDG_PAL1);
				while(CAN_GetTransferStatus(INST_CAN_PAL0, TX_MAILBOX) == STATUS_BUSY);
				repeat_receive = true;
			}

		}
	}


	//send uart data
	UART_SendData(INST_LPUART0_UART, uart_tranMsg, uart_tranMsg[1]);
	WDG_Refresh(INST_WDG_PAL1);
	while(UART_GetTransmitStatus(INST_LPUART0_UART, &bytesRemaining) != STATUS_SUCCESS);

	//receive uart reply status
	for(i=0;i<4;i++)
	{
		UART_ReceiveData(INST_LPUART0_UART, &uart_reply_recvMsg[i], 1UL);
		WDG_Refresh(INST_WDG_PAL1);
		while(UART_GetReceiveStatus(INST_LPUART0_UART, &bytesRemaining) != STATUS_SUCCESS);
	}

	//check reply status and reply can status
	if(uart_reply_recvMsg[0] == 0xAA && uart_reply_recvMsg[1] == 0x04 && uart_reply_recvMsg[2] == 0xCC && uart_reply_recvMsg[3] == 0x84) can_reply_status(can_success);
	else if(uart_reply_recvMsg[0] == 0xAA && uart_reply_recvMsg[1] == 0x04 && uart_reply_recvMsg[2] == 0xE0 && uart_reply_recvMsg[3] == 0x70) can_reply_status(can_error_header);
	else if(uart_reply_recvMsg[0] == 0xAA && uart_reply_recvMsg[1] == 0x04 && uart_reply_recvMsg[2] == 0xE1 && uart_reply_recvMsg[3] == 0x6F) can_reply_status(can_error_length);
	else can_reply_status(can_error_checksum);
	CAN_Send(INST_CAN_PAL0, TX_MAILBOX, &can_tranvMsg_1);
	WDG_Refresh(INST_WDG_PAL1);
	while(CAN_GetTransferStatus(INST_CAN_PAL0, TX_MAILBOX) == STATUS_BUSY);

#endif
}

void can_reply_status(can_reply_status_t status)
{
	switch(status)
	{
	case can_error_header:
		can_tranvMsg_1.length=4;
		can_tranvMsg_1.data[0]=0xAA;
		can_tranvMsg_1.data[1]=0x04;
		can_tranvMsg_1.data[2]=0xE0;
		can_tranvMsg_1.data[3]=0x70;
		break;
	case can_error_length:
		can_tranvMsg_1.length=4;
		can_tranvMsg_1.data[0]=0xAA;
		can_tranvMsg_1.data[1]=0x04;
		can_tranvMsg_1.data[2]=0xE1;
		can_tranvMsg_1.data[3]=0x6F;
		break;
	case can_error_checksum:
		can_tranvMsg_1.length=4;
		can_tranvMsg_1.data[0]=0xAA;
		can_tranvMsg_1.data[1]=0x04;
		can_tranvMsg_1.data[2]=0xE2;
		can_tranvMsg_1.data[3]=0x6E;
		break;
	case can_success:
		can_tranvMsg_1.length=4;
		can_tranvMsg_1.data[0]=0xAA;
		can_tranvMsg_1.data[1]=0x04;
		can_tranvMsg_1.data[2]=0xCC;
		can_tranvMsg_1.data[3]=0x84;
		break;
	}
}



