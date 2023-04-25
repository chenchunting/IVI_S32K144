#include "Cpu.h"
#include "clockMan1.h"
#include "pin_mux.h"
#include "dmaController1.h"
#include "osif.h"
//#include "can_pal0.h"
//#include "lpuart1_uart.h"
#include "init.h"
#include "ledstrip.h"
#include "can_receiver.h"
#include "uart_receiver.h"

#include <string.h>

volatile int exit_code = 0;
#include <stdint.h>
#include <stdbool.h>





void board_init(void)
{
	CLOCK_SYS_Init(g_clockManConfigsArr, CLOCK_MANAGER_CONFIG_CNT, g_clockManCallbacksArr, CLOCK_MANAGER_CALLBACK_CNT);
	CLOCK_SYS_UpdateConfiguration(0U, CLOCK_MANAGER_POLICY_AGREEMENT);
	/*Initialize pins*/
	PINS_DRV_Init(NUM_OF_CONFIGURED_PINS, g_pin_mux_InitConfigArr);
}


/* Definition of the data transfer size */
#define TRANSFER_SIZE 8

/* Initialization of slave buffers */
uint8_t slaveTxBuffer[TRANSFER_SIZE] = { 0x0, 0x1, 0x02, 0x3, 0x4, 0x5, 0x6, 0x7};
uint8_t slaveRxBuffer[TRANSFER_SIZE] = { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};

/*!
 *  @brief I2C Slave Callback
 *
 *  @param [in] instance   I2C instance number
 *  @param [in] slaveEvent Event received on the I2C bus
 *  @param [in] userData   User defined data that is passed to the callback
 *  @return None
 *
 *  @details This function will be called by I2C interrupt handler and it
 *  will assign the buffer for TX or RX events.
 *  If an error event occurs, it will abort the current transfer.
 */
void i2c1_SlaveCallback0(i2c_slave_event_t slaveEvent, void *userData) {
	/* Get instance number from userData */
	uint32_t instance;
	instance = (uint32_t) userData;

	/* Check the event type:
	 *  - set RX or TX buffers depending on the master request type
	 */
	if (slaveEvent == I2C_SLAVE_EVENT_RX_REQ)
		I2C_SlaveSetRxBuffer((uint8_t) instance, slaveRxBuffer, TRANSFER_SIZE);
	if (slaveEvent == I2C_SLAVE_EVENT_TX_REQ)
		I2C_SlaveSetTxBuffer((uint8_t) instance, slaveTxBuffer, TRANSFER_SIZE);
}



int main(void)
{
  /* Write your local variable definition here */

	/* Declaration of the I2C transfer buffer */
	uint8_t masterTxBuffer[TRANSFER_SIZE];
	/* Variable that is used to initialize the buffers */
	uint8_t cnt;
	bool isTransferOk = true;

	/* Variable used for the loop that initializes the data buffer */
	uint16_t i;

	/* Use as callback parameter for slave module the I2C instance number */
	i2c1_SlaveConfig0.callbackParam = (uint32_t *) I2C_OVER_LPI2C0_INSTANCE;

    /* Configure FLEXIO pins routing */
	extension_flexio_for_i2c_t extension;
	extension.sclPin = 4;
	extension.sdaPin = 5;
	i2c2_MasterConfig0.extension = &extension;

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  #ifdef PEX_RTOS_INIT
    PEX_RTOS_INIT();                   /* Initialization of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of Processor Expert internal initialization.                    ***/
   /*Initialize*/
  board_init();
  uart_init();
  ledsrip_spi_init();
  can_init();
  wdg_init();
  pwm_init();
  hx8880_spi_init();



  /*I2C_SlaveInit(I2C_OVER_LPI2C0_INSTANCE, &i2c1_SlaveConfig0);
  I2C_MasterInit(I2C_OVER_FLEXIO0_INSTANCE, &i2c2_MasterConfig0);



  for (i = 0u; i < TRANSFER_SIZE; i++)
  {
      masterTxBuffer[i] = i*2;
  }
  I2C_MasterSendDataBlocking(I2C_OVER_FLEXIO0_INSTANCE, masterTxBuffer, TRANSFER_SIZE, true, 0xFFFF);*/


  while(1)
  {

	  uart();
	  hx8880_spi();
	  pwm_test();
	  LED_strip();

	  dms_test();
	  uart_receive();
	  can_receive();
	  uart_can_uart_test();
  }

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;) {
    if(exit_code != 0) {
      break;
    }
  }
  return exit_code;
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.1 [05.21]
**     for the NXP C55 series of microcontrollers.
**
** ###################################################################
*/
