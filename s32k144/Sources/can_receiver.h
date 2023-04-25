

#ifndef CAN_RECEIVER_H_
#define CAN_RECEIVER_H_

#include <stdint.h>
#include <stdbool.h>


typedef enum
{
	can_error_header,
	can_error_length,
	can_error_checksum,
	can_success
} can_reply_status_t;

void can_receive(void);
uint8_t can_checksumValue(uint8_t *buf, int bytecnt);
void can_reply_status(can_reply_status_t status);

#endif /* CAN_RECEIVER_H_ */
