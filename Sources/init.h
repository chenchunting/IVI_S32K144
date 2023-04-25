

#ifndef INIT_H_
#define INIT_H_

#define Enable	1
#define Disable	0

#define LEDstrip_Enable 		Enable
#define Return_WebServer_Enable Disable
#define Web_Server_Enable 		Disable
#define CAN_FD_Enable 			Disable

#define TX_MAILBOX  (1UL)
#define TX_MSG_ID   0x601//(1UL)
#define RX_MAILBOX 	(0UL)
#define RX_MSG_ID  	0x602//(2UL)


void uart_init(void);
void can_init(void);
void ledsrip_spi_init(void);
void wdg_init(void);
void pwm_init(void);
void hx8880_spi_init(void);


#endif /* INIT_H_ */
