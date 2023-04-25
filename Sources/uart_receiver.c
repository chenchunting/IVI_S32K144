
#include "init.h"
#include "uart_receiver.h"
#include "can_receiver.h"
#include "ledstrip.h"
#include "lpuart1_uart.h"
#include <string.h>




ledstrip_uart_status_t uart_ledsrip_status;

void dms_test(void)
{
	uint8_t i=0,len=8;
	uint8_t uart_recvMsg[UART_TRAN_MAX_LENGTH]={0};
	can_message_t can_tranvMsg_0,can_recvMsg_2;
	uint32_t bytesRemaining;

	for(i=0;i<len;i++)
	{
		UART_ReceiveData(INST_LPUART0_UART, &uart_recvMsg[i], 1UL);
		while(UART_GetReceiveStatus(INST_LPUART0_UART, &bytesRemaining) != STATUS_SUCCESS);
	}

	can_tranvMsg_0.length=len;
	can_tranvMsg_0.id=TX_MSG_ID;
	for(i=0;i<len;i++) can_tranvMsg_0.data[i]=uart_recvMsg[i];
	CAN_Send(INST_CAN_PAL0, TX_MAILBOX, &can_tranvMsg_0);
	WDG_Refresh(INST_WDG_PAL1);
	while(CAN_GetTransferStatus(INST_CAN_PAL0, TX_MAILBOX) == STATUS_BUSY);

	CAN_Receive(INST_CAN_PAL0, RX_MAILBOX, &can_recvMsg_2);
	WDG_Refresh(INST_WDG_PAL1);
	while(CAN_GetTransferStatus(INST_CAN_PAL0, RX_MAILBOX) == STATUS_BUSY);

	UART_SendData(INST_LPUART0_UART, can_recvMsg_2.data, can_recvMsg_2.length);
	WDG_Refresh(INST_WDG_PAL1);
	while(UART_GetTransmitStatus(INST_LPUART0_UART, &bytesRemaining) != STATUS_SUCCESS);

}

void uart_receive(void)
{
	bool received = false,repeat_transmit = false,error_code = false;
	uint32_t bytesRemaining;
	uint8_t i=0,j=0,repeat_transmit_number=0,recvMsg_length=0,length_buff=0,checksum=0,checksum_buff=0;
	uint8_t uart_recvMsg[UART_TRAN_MAX_LENGTH]={0},uart_webMsg[UART_TRAN_MAX_LENGTH]={0};
	can_message_t can_recvMsg_0,can_tranvMsg_0,can_recvMsg_2;
	uint8_t uart_success[] = { 0xAA, 0x04, 0xCC, 0x84 }, len_uart_success = sizeof(uart_success)/sizeof(uart_success[0]);
	uint8_t uart_error_header[] = { 0xAA, 0x04, 0xE0, 0x70 }, len_uart_error_header = sizeof(uart_error_header)/sizeof(uart_error_header[0]);
	uint8_t uart_error_length[] = { 0xAA, 0x04, 0xE1, 0x6F }, len_uart_error_length = sizeof(uart_error_length)/sizeof(uart_error_length[0]);
	uint8_t uart_error_checksum[] = { 0xAA, 0x04, 0xE2, 0x6E }, len_uart_error_checksum = sizeof(uart_error_checksum)/sizeof(uart_error_checksum[0]);


	while(received == false)
	{
		UART_ReceiveData(INST_LPUART0_UART, &uart_recvMsg[i], 1UL);
		while(UART_GetReceiveStatus(INST_LPUART0_UART, &bytesRemaining) != STATUS_SUCCESS);
		i++;
		if(i>=1)if(i == uart_recvMsg[1])	received = true;

		if(i>=UART_TRAN_MAX_LENGTH)// || i<=UART_TRAN_MIN_LENGTH)
		{
			//send error length
			error_code = true;
			uart_ledsrip_status = non_active_ledstrip;
			UART_SendData(INST_LPUART0_UART, uart_error_length, len_uart_error_length);
			WDG_Refresh(INST_WDG_PAL1);
			while(UART_GetTransmitStatus(INST_LPUART0_UART, &bytesRemaining) != STATUS_SUCCESS);
		}
	}

	if(uart_recvMsg[0]==0xAA)//ITE
	{
		recvMsg_length = uart_recvMsg[1];
		checksum = uart_recvMsg[recvMsg_length-1];

		checksum_buff = 0;
		for(i=0;i<recvMsg_length-1;i++) checksum_buff+=uart_recvMsg[i];
		checksum_buff=~checksum_buff-1;

		if(checksum == checksum_buff)
		{
			if(recvMsg_length<=8)
			{
				//send can data
				can_tranvMsg_0.length=recvMsg_length;
				for(i=0;i<recvMsg_length;i++) can_tranvMsg_0.data[i]=uart_recvMsg[i];
				CAN_Send(INST_CAN_PAL0, TX_MAILBOX, &can_tranvMsg_0);
				WDG_Refresh(INST_WDG_PAL1);
				while(CAN_GetTransferStatus(INST_CAN_PAL0, TX_MAILBOX) == STATUS_BUSY);
			}
			else
			{

				//send can data

				length_buff = recvMsg_length-3;
				WDG_Refresh(INST_WDG_PAL1);
				while(repeat_transmit == false)
				{
					if(length_buff>5)
					{
						length_buff = length_buff-5;
						can_tranvMsg_0.data[0]=0xA5;
						can_tranvMsg_0.length = 8;
					}
					else
					{
						can_tranvMsg_0.length = length_buff+3;
						can_tranvMsg_0.data[0]=0xAA;
						repeat_transmit = true;
					}

					can_tranvMsg_0.data[1]=can_tranvMsg_0.length;
					for(i=2;i<can_tranvMsg_0.length-1;i++) can_tranvMsg_0.data[i]=uart_recvMsg[i+5*j];
					checksum_buff=0;
					for(i=0;i<can_tranvMsg_0.length-1;i++) checksum_buff+=can_tranvMsg_0.data[i];
					can_tranvMsg_0.data[can_tranvMsg_0.data[1]-1]=~checksum_buff-1;
					CAN_Send(INST_CAN_PAL0, TX_MAILBOX, &can_tranvMsg_0);
					WDG_Refresh(INST_WDG_PAL1);
					while(CAN_GetTransferStatus(INST_CAN_PAL0, TX_MAILBOX) == STATUS_BUSY);

					//check reply status
					CAN_Receive(INST_CAN_PAL0, RX_MAILBOX, &can_recvMsg_0);
					WDG_Refresh(INST_WDG_PAL1);
					while(CAN_GetTransferStatus(INST_CAN_PAL0, RX_MAILBOX) == STATUS_BUSY);

					if(can_recvMsg_0.data[0] == 0xAA && can_recvMsg_0.data[1] == 0x04 && can_recvMsg_0.data[2] == 0xCC && can_recvMsg_0.data[3] == 0x84)
					{
		#if Return_WebServer_Enable
						//receive can data to web server
						CAN_Receive(INST_CAN_PAL1, RX_MAILBOX, &can_recvMsg_2);
						WDG_Refresh(INST_WDG_PAL1);
						while(CAN_GetTransferStatus(INST_CAN_PAL1, RX_MAILBOX) == STATUS_BUSY)
						//transmit can data to web server
						for(i=2;i<can_recvMsg_2.length-1;i++)uart_webMsg[i+5*j] =can_recvMsg_2.data[i];
						if(can_recvMsg_2.data[0]==0xAA)
						{
							if(j != 0)
							{
								uart_webMsg[0] = 0xAA;
								uart_webMsg[1] = 5*j+can_recvMsg_2.data[1];
								checksum_buff = 0;
								for(i=0;i<uart_webMsg[1]-1;i++) checksum_buff+=uart_webMsg[i];
								uart_webMsg[uart_webMsg[1]-1] = ~checksum_buff-1;
							}
							else
							{
								uart_webMsg[0] = can_recvMsg_2.data[0];
								uart_webMsg[1] = can_recvMsg_2.data[1];
								uart_webMsg[can_recvMsg_2.length-1] = can_recvMsg_2.data[can_recvMsg_2.length-1];
							}
						}
		#endif
					}
					else if(can_recvMsg_0.data[0] == 0xAA && can_recvMsg_0.data[1] == 0x04 && can_recvMsg_0.data[2] == 0xE0 && can_recvMsg_0.data[3] == 0x70)
					{
						error_code = true;
						repeat_transmit = true;
						UART_SendData(INST_LPUART0_UART, uart_error_header, len_uart_error_header);
						WDG_Refresh(INST_WDG_PAL1);
						while(UART_GetTransmitStatus(INST_LPUART0_UART, &bytesRemaining) != STATUS_SUCCESS);
					}
					else if(can_recvMsg_0.data[0] == 0xAA && can_recvMsg_0.data[1] == 0x04 && can_recvMsg_0.data[2] == 0xE1 && can_recvMsg_0.data[3] == 0x6F)
					{
						error_code = true;
						repeat_transmit = true;
						UART_SendData(INST_LPUART0_UART, uart_error_length, len_uart_error_length);
						WDG_Refresh(INST_WDG_PAL1);
						while(UART_GetTransmitStatus(INST_LPUART0_UART, &bytesRemaining) != STATUS_SUCCESS);
					}
					else
					{
						error_code = true;
						repeat_transmit = true;
						UART_SendData(INST_LPUART0_UART, uart_error_checksum, len_uart_error_checksum);
						WDG_Refresh(INST_WDG_PAL1);
						while(UART_GetTransmitStatus(INST_LPUART0_UART, &bytesRemaining) != STATUS_SUCCESS);
					}

					j++;
				}
			}
/*
			//send can data
			can_tranvMsg_0.length=recvMsg_length;
			for(i=0;i<recvMsg_length;i++) can_tranvMsg_0.data[i]=uart_recvMsg[i];
			CAN_Send(INST_CAN_PAL0, TX_MAILBOX, &can_tranvMsg_0);
			WDG_Refresh(INST_WDG_PAL1);
			while(CAN_GetTransferStatus(INST_CAN_PAL0, TX_MAILBOX) == STATUS_BUSY);

	#if Return_WebServer_Enable
			//receive can data to web server
			CAN_Receive(INST_CAN_PAL1, RX_MAILBOX, &can_recvMsg_2);
			WDG_Refresh(INST_WDG_PAL1);
			while(CAN_GetTransferStatus(INST_CAN_PAL1, RX_MAILBOX) == STATUS_BUSY);
	#endif
*/





			//receive can reply status
			CAN_Receive(INST_CAN_PAL0, RX_MAILBOX, &can_recvMsg_0);
			WDG_Refresh(INST_WDG_PAL1);
			while(CAN_GetTransferStatus(INST_CAN_PAL0, RX_MAILBOX) == STATUS_BUSY);

			//check reply status and reply uart status
			if(can_recvMsg_0.data[0] == 0xAA && can_recvMsg_0.data[1] == 0x04 && can_recvMsg_0.data[2] == 0xCC && can_recvMsg_0.data[3] == 0x84)
			{
#if Return_WebServer_Enable
				//transmit can data to web server
				UART_SendData(INST_LPUART0_UART, can_recvMsg_2.data, can_recvMsg_2.data[1]);
#else
				UART_SendData(INST_LPUART0_UART, uart_success, len_uart_success);
#endif
			}
			else if(can_recvMsg_0.data[0] == 0xAA && can_recvMsg_0.data[1] == 0x04 && can_recvMsg_0.data[2] == 0xE0 && can_recvMsg_0.data[3] == 0x70) UART_SendData(INST_LPUART0_UART, uart_error_header, len_uart_error_header);
			else if(can_recvMsg_0.data[0] == 0xAA && can_recvMsg_0.data[1] == 0x04 && can_recvMsg_0.data[2] == 0xE1 && can_recvMsg_0.data[3] == 0x6F) UART_SendData(INST_LPUART0_UART, uart_error_length, len_uart_error_length);
			else UART_SendData(INST_LPUART0_UART, uart_error_checksum, len_uart_error_checksum);
			WDG_Refresh(INST_WDG_PAL1);
			while(UART_GetTransmitStatus(INST_LPUART0_UART, &bytesRemaining) != STATUS_SUCCESS);

		}
		else
		{
			//send error checksum
			uart_ledsrip_status = non_active_ledstrip;
			UART_SendData(INST_LPUART0_UART, uart_error_checksum, len_uart_error_checksum);
			WDG_Refresh(INST_WDG_PAL1);
			while(UART_GetTransmitStatus(INST_LPUART0_UART, &bytesRemaining) != STATUS_SUCCESS);
		}
	}
#if LEDstrip_Enable
	else if(uart_recvMsg[0]==0xA0)
	{
		ledstrip_mode_t select_mode = uart_recvMsg[2];
		ledstrip_color_t select_color = uart_recvMsg[3];

		recvMsg_length = uart_recvMsg[1];
		checksum = uart_recvMsg[recvMsg_length-1];

		for(i=0;i<recvMsg_length-1;i++) checksum_buff+=uart_recvMsg[i];
		checksum_buff=~checksum_buff-1;

		if(checksum == checksum_buff)
		{
			if(select_mode == Mode_Fade_Transition)
			{
				Fade_Transition(select_color);
				//send receive success
				uart_ledsrip_status = active_ledstrip;
				UART_SendData(INST_LPUART0_UART, uart_success, len_uart_success);
				WDG_Refresh(INST_WDG_PAL1);
				while(UART_GetTransmitStatus(INST_LPUART0_UART, &bytesRemaining) != STATUS_SUCCESS);
			}
			else if(select_mode == Mode_Expand_to_Fill)
			{
				Expand_to_Fill();
				//send receive success
				uart_ledsrip_status = active_ledstrip;
				UART_SendData(INST_LPUART0_UART, uart_success, len_uart_success);
				WDG_Refresh(INST_WDG_PAL1);
				while(UART_GetTransmitStatus(INST_LPUART0_UART, &bytesRemaining) != STATUS_SUCCESS);
			}
			else if(select_mode == Mode_Dashed_Expansion)
			{
				Dashed_Expansion();
				//send receive success
				uart_ledsrip_status = active_ledstrip;
				UART_SendData(INST_LPUART0_UART, uart_success, len_uart_success);
				WDG_Refresh(INST_WDG_PAL1);
				while(UART_GetTransmitStatus(INST_LPUART0_UART, &bytesRemaining) != STATUS_SUCCESS);
			}
			else if(select_mode == Mode_Pixel_Light)
			{
				Pixel_Light(select_color);
				//send receive success
				uart_ledsrip_status = active_ledstrip;
				UART_SendData(INST_LPUART0_UART, uart_success, len_uart_success);
				WDG_Refresh(INST_WDG_PAL1);
				while(UART_GetTransmitStatus(INST_LPUART0_UART, &bytesRemaining) != STATUS_SUCCESS);
			}
			else if(select_mode == Mode_News_Ticker)
			{
				News_Ticker(select_color);
				//send receive success
				uart_ledsrip_status = active_ledstrip;
				UART_SendData(INST_LPUART0_UART, uart_success, len_uart_success);
				WDG_Refresh(INST_WDG_PAL1);
				while(UART_GetTransmitStatus(INST_LPUART0_UART, &bytesRemaining) != STATUS_SUCCESS);
			}
			else if(select_mode == Mode_Breathing_Light)
			{
				Breathing_Light(select_color);
				//send receive success
				uart_ledsrip_status = active_ledstrip;
				UART_SendData(INST_LPUART0_UART, uart_success, len_uart_success);
				WDG_Refresh(INST_WDG_PAL1);
				while(UART_GetTransmitStatus(INST_LPUART0_UART, &bytesRemaining) != STATUS_SUCCESS);
			}
		}
		else
		{
			//send error checksum
			uart_ledsrip_status = non_active_ledstrip;
			UART_SendData(INST_LPUART0_UART, uart_error_checksum, len_uart_error_checksum);
			WDG_Refresh(INST_WDG_PAL1);
			while(UART_GetTransmitStatus(INST_LPUART0_UART, &bytesRemaining) != STATUS_SUCCESS);
		}
	}
#endif
	else
	{
		//send error header
		uart_ledsrip_status = non_active_ledstrip;
		UART_SendData(INST_LPUART0_UART, uart_error_header, len_uart_error_header);
		WDG_Refresh(INST_WDG_PAL1);
		while(UART_GetTransmitStatus(INST_LPUART0_UART, &bytesRemaining) != STATUS_SUCCESS);
	}

}
void ledstrip_repeat(void)
{
	if(uart_ledsrip_status == active_ledstrip)
	{
		ledstrip_status_t ledsrip_status_buff;
		ledsrip_status_buff = get_ledsrip_status();

		switch(ledsrip_status_buff.mode)
		{
			case Mode_Fade_Transition:
				break;
			case Mode_Expand_to_Fill:
				break;
			case Mode_Dashed_Expansion:
				Dashed_Expansion();
				break;
			case Mode_Pixel_Light:
				Pixel_Light(ledsrip_status_buff.color);
				break;
			case Mode_News_Ticker:
				News_Ticker(ledsrip_status_buff.color);
				break;
			case Mode_Breathing_Light:
				Breathing_Light(ledsrip_status_buff.color);
				break;
		}
	}
}



