

#ifndef UART_RECEIVER_H_
#define UART_RECEIVER_H_

#include <stdint.h>
#include <stdbool.h>

#define	UART_TRAN_MIN_LENGTH	3
#define	UART_TRAN_MAX_LENGTH	20

typedef enum
{
	non_active_ledstrip,
	active_ledstrip
} ledstrip_uart_status_t;



void dms_test(void);
void uart_receive(void);
void ledstrip_repeat(void);
uint8_t uart_checksumValue(uint8_t *buf, int bytecnt);

#endif /* UART_RECEIVER_H_ */
