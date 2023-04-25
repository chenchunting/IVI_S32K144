
#include "init.h"
#include "uart_receiver.h"
#include "can_receiver.h"
#include "ledstrip.h"
#include "lpuart1_uart.h"
#include <string.h>


can_message_t can_tranvMsg_2;
uint8_t uart_recvMsg[UART_TRAN_MAX_LENGTH]={0};
void uart(void)
{
	uint32_t bytesRemaining;
	uint8_t uart_test_number1[]={0xAA,0x04,0xCC,0x84};
	uint8_t i;
	bool received = false;


	/*while(received == false)
	{
		UART_ReceiveData(INST_LPUART0_UART, &uart_recvMsg[i], 1UL);
		while(UART_GetReceiveStatus(INST_LPUART0_UART, &bytesRemaining) != STATUS_SUCCESS);
		i++;
		if(i>=1)if(i == uart_recvMsg[1])	received = true;
	}*/

	UART_SendData(INST_LPUART0_UART, uart_test_number1, 4);
	while(UART_GetTransmitStatus(INST_LPUART0_UART, &bytesRemaining) != STATUS_SUCCESS);
	OSIF_TimeDelay(500);
}

void hx8880_spi(void)
{
	uint32_t bytesRemaining;
	uint8_t i,uart_test_number1[8]={0};
	uint8_t m_send[]={0x10,0x2,0x3,0x4,0x5,0x6,0x7,0x8},m_receive[8]={0};
	uint8_t s_send[]={0x9,0x08,0x07,0x06,0x5,0x4,0x3,0x2},s_receive[8]={0};

	LPSPI_DRV_MasterTransfer(SEND1, m_send,m_receive, 8U);
	OSIF_TimeDelay(20);
	LPSPI_DRV_SlaveTransfer(SEND, s_send,s_receive, 8U);
	OSIF_TimeDelay(20);

	for(i=0;i<8;i++)uart_test_number1[i]=s_receive[i];
	UART_SendData(INST_LPUART0_UART, uart_test_number1, 8);
	while(UART_GetTransmitStatus(INST_LPUART0_UART, &bytesRemaining) != STATUS_SUCCESS);
	for(i=0;i<8;i++)uart_test_number1[i]=m_receive[i];
	UART_SendData(INST_LPUART0_UART, uart_test_number1, 8);
	while(UART_GetTransmitStatus(INST_LPUART0_UART, &bytesRemaining) != STATUS_SUCCESS);
}

void pwm_test(void)
{
	FTM_DRV_UpdatePwmChannel(INST_FLEXTIMER_PWM1, 1U, FTM_PWM_UPDATE_IN_DUTY_CYCLE, 0x6000, 0U, true);
	OSIF_TimeDelay(500);
	FTM_DRV_UpdatePwmChannel(INST_FLEXTIMER_PWM1, 1U, FTM_PWM_UPDATE_IN_DUTY_CYCLE, 0x2000, 0U, true);
	OSIF_TimeDelay(500);
}

void write_pin(void)
{
	PINS_DRV_WritePin(PTD,  15U, 0u);
	PINS_DRV_SetPins(PTD, (1 << 15U) | (1 << 16U));
}

void LED_strip(void)
{
	Expand_to_Fill();
	Dashed_Expansion();
	Pixel_Light(3);
	News_Ticker(4);
	Breathing_Light(5);
	Fade_Transition(6);
}
void can_reply_status2(can_reply_status_t status)
{
	switch(status)
	{
	case can_error_header:
		can_tranvMsg_2.length=4;
		can_tranvMsg_2.data[0]=0xAA;
		can_tranvMsg_2.data[1]=0x04;
		can_tranvMsg_2.data[2]=0xE0;
		can_tranvMsg_2.data[3]=0x70;
		break;
	case can_error_length:
		can_tranvMsg_2.length=4;
		can_tranvMsg_2.data[0]=0xAA;
		can_tranvMsg_2.data[1]=0x04;
		can_tranvMsg_2.data[2]=0xE1;
		can_tranvMsg_2.data[3]=0x6F;
		break;
	case can_error_checksum:
		can_tranvMsg_2.length=4;
		can_tranvMsg_2.data[0]=0xAA;
		can_tranvMsg_2.data[1]=0x04;
		can_tranvMsg_2.data[2]=0xE2;
		can_tranvMsg_2.data[3]=0x6E;
		break;
	case can_success:
		can_tranvMsg_2.length=4;
		can_tranvMsg_2.data[0]=0xAA;
		can_tranvMsg_2.data[1]=0x04;
		can_tranvMsg_2.data[2]=0xCC;
		can_tranvMsg_2.data[3]=0x84;
		break;
	}
}

void uart_can_uart_test(void)
{
	bool received = false,repeat_transmit = false;
	uint32_t bytesRemaining;
	uint8_t i=0,j=0,recvMsg_length=0,length_buff=0,checksum=0,checksum_buff=0;
	uint8_t uart_recvMsg[UART_TRAN_MAX_LENGTH]={0},uart_tranMsg[UART_TRAN_MAX_LENGTH]={0},uart_reply_recvMsg[UART_TRAN_MAX_LENGTH]={0};;
	can_message_t can_tranvMsg_0;
	uint8_t uart_success[] = { 0xAA, 0x04, 0xCC, 0x84 }, len_uart_success = sizeof(uart_success)/sizeof(uart_success[0]);
	uint8_t uart_error_header[] = { 0xAA, 0x04, 0xE0, 0x70 }, len_uart_error_header = sizeof(uart_error_header)/sizeof(uart_error_header[0]);
	uint8_t uart_error_length[] = { 0xAA, 0x04, 0xE1, 0x6F }, len_uart_error_length = sizeof(uart_error_length)/sizeof(uart_error_length[0]);
	uint8_t uart_error_checksum[] = { 0xAA, 0x04, 0xE2, 0x6E }, len_uart_error_checksum = sizeof(uart_error_checksum)/sizeof(uart_error_checksum[0]);


	while(received == false)
	{
		UART_ReceiveData(INST_LPUART1_UART, &uart_recvMsg[i], 1UL);
		while(UART_GetReceiveStatus(INST_LPUART1_UART, &bytesRemaining) != STATUS_SUCCESS);
		i++;
		if(i>=1)if(i == uart_recvMsg[1])	received = true;

		if(i>=UART_TRAN_MAX_LENGTH)// || i<=UART_TRAN_MIN_LENGTH)
		{
			//send error length
			UART_SendData(INST_LPUART1_UART, uart_error_length, len_uart_error_length);
			while(UART_GetTransmitStatus(INST_LPUART1_UART, &bytesRemaining) != STATUS_SUCCESS);
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
				while(CAN_GetTransferStatus(INST_CAN_PAL0, TX_MAILBOX) == STATUS_BUSY);
				for(i=0;i<can_tranvMsg_0.length;i++) uart_tranMsg[i]=can_tranvMsg_0.data[i];
			}
			else
			{

				//send can data

				length_buff = recvMsg_length-3;
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
					while(CAN_GetTransferStatus(INST_CAN_PAL0, TX_MAILBOX) == STATUS_BUSY);



					recvMsg_length = can_tranvMsg_0.data[1];
					checksum = can_tranvMsg_0.data[recvMsg_length-1];

					checksum_buff = 0;
					for(i=0;i<recvMsg_length-1;i++) checksum_buff+=can_tranvMsg_0.data[i];
					checksum_buff=~checksum_buff-1;

					if(checksum == checksum_buff)
					{
						for(i=2;i<can_tranvMsg_0.length-1;i++)uart_tranMsg[i+5*j] =can_tranvMsg_0.data[i];
						if(can_tranvMsg_0.data[0]==0xAA)
						{
							if(j != 0)
							{
								uart_tranMsg[0] = 0xAA;
								uart_tranMsg[1] = 5*j+can_tranvMsg_0.data[1];
								checksum_buff = 0;
								for(i=0;i<uart_tranMsg[1]-1;i++) checksum_buff+=uart_tranMsg[i];
								uart_tranMsg[uart_tranMsg[1]-1] = ~checksum_buff-1;
							}
							else
							{
								uart_tranMsg[0] = can_tranvMsg_0.data[0];
								uart_tranMsg[1] = can_tranvMsg_0.data[1];
								uart_tranMsg[can_tranvMsg_0.length-1] = can_tranvMsg_0.data[can_tranvMsg_0.length-1];
							}
						}
					}
					else
					{
					//send error checksum
						can_reply_status2(can_error_checksum);
						CAN_Send(INST_CAN_PAL0, TX_MAILBOX, &can_tranvMsg_2);
						while(CAN_GetTransferStatus(INST_CAN_PAL0, TX_MAILBOX) == STATUS_BUSY);
					}


					j++;
				}
			}


			//send uart data
			UART_SendData(INST_LPUART0_UART, uart_tranMsg, uart_tranMsg[1]);
			while(UART_GetTransmitStatus(INST_LPUART0_UART, &bytesRemaining) != STATUS_SUCCESS);

			//receive uart reply status
			for(i=0;i<4;i++)
			{
				UART_ReceiveData(INST_LPUART0_UART, &uart_reply_recvMsg[i], 1UL);
				while(UART_GetReceiveStatus(INST_LPUART0_UART, &bytesRemaining) != STATUS_SUCCESS);
			}

			//check reply status and reply can status
			if(uart_reply_recvMsg[0] == 0xAA)
			{
				if(uart_reply_recvMsg[1] == 0x04)
				{
					if(uart_reply_recvMsg[2] == 0xCC && uart_reply_recvMsg[3] == 0x84) can_reply_status2(can_success);
					else if(uart_reply_recvMsg[2] == 0xE0 && uart_reply_recvMsg[3] == 0x70) can_reply_status2(can_error_header);
					else if(uart_reply_recvMsg[2] == 0xE1 && uart_reply_recvMsg[3] == 0x6F) can_reply_status2(can_error_length);
					else can_reply_status2(can_error_checksum);
					CAN_Send(INST_CAN_PAL0, TX_MAILBOX, &can_tranvMsg_2);
					while(CAN_GetTransferStatus(INST_CAN_PAL0, TX_MAILBOX) == STATUS_BUSY);
				}
			}



			//check reply status and reply uart status
			if(can_tranvMsg_2.data[0] == 0xAA)
			{
				if(can_tranvMsg_2.data[1] == 0x04)
				{
					if(can_tranvMsg_2.data[2] == 0xCC && can_tranvMsg_2.data[3] == 0x84)
					{
						UART_SendData(INST_LPUART1_UART, uart_success, len_uart_success);

					}
					else if(can_tranvMsg_2.data[2] == 0xE0 && can_tranvMsg_2.data[3] == 0x70) UART_SendData(INST_LPUART1_UART, uart_error_header, len_uart_error_header);
					else if(can_tranvMsg_2.data[2] == 0xE1 && can_tranvMsg_2.data[3] == 0x6F) UART_SendData(INST_LPUART1_UART, uart_error_length, len_uart_error_length);
					else UART_SendData(INST_LPUART1_UART, uart_error_checksum, len_uart_error_checksum);
					while(UART_GetTransmitStatus(INST_LPUART1_UART, &bytesRemaining) != STATUS_SUCCESS);
				}
			}
		}
		else
		{
			//send error checksum
			UART_SendData(INST_LPUART1_UART, uart_error_checksum, len_uart_error_checksum);
			while(UART_GetTransmitStatus(INST_LPUART0_UART, &bytesRemaining) != STATUS_SUCCESS);
		}
	}

	else
	{
		//send error header
		UART_SendData(INST_LPUART1_UART, uart_error_header, len_uart_error_header);
		while(UART_GetTransmitStatus(INST_LPUART0_UART, &bytesRemaining) != STATUS_SUCCESS);
	}

}



