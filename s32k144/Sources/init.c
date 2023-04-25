
#include "init.h"
#include "can_pal1.h"
#include "Send.h"
#include "Send1.h"

void uart_init(void)
{

	UART_Init(INST_LPUART0_UART, &lpuart0_uart_Config0);
	UART_Init(INST_LPUART1_UART, &lpuart1_uart_Config0);
}

void can_init(void)
{
    CAN_Init(INST_CAN_PAL0, &can_pal0_Config0);
    CAN_Init(INST_CAN_PAL1, &can_pal1_Config0);


    can_buff_config_t buffCfg =  {
        .enableFD = false,//true,
        .enableBRS = true,
        .fdPadding = 0U,
        .idType = CAN_MSG_ID_STD,
        .isRemote = false
    };

    /* Configure RX buffer with index RX_MAILBOX */
    CAN_ConfigRxBuff(INST_CAN_PAL0, RX_MAILBOX, &buffCfg, RX_MSG_ID);
    CAN_ConfigTxBuff(INST_CAN_PAL0, TX_MAILBOX, &buffCfg);
    CAN_ConfigRxBuff(INST_CAN_PAL1, RX_MAILBOX, &buffCfg, RX_MSG_ID);
    CAN_ConfigTxBuff(INST_CAN_PAL1, TX_MAILBOX, &buffCfg);
}

void ledsrip_spi_init(void)
{
	EDMA_DRV_Init(&dmaController1_State, &dmaController1_InitConfig0, edmaChnStateArray, edmaChnConfigArray, EDMA_CONFIGURED_CHANNELS_COUNT);
	LPSPI_DRV_MasterInit(SEND, &SendState, &Send_MasterConfig0);
}

void wdg_init(void)
{
	WDG_Init(INST_WDG_PAL1, &wdg_pal1_Config0);
}

void pwm_init(void)
{
	ftm_state_t ftmStateStruct;
	FTM_DRV_Init(INST_FLEXTIMER_PWM1, &flexTimer_pwm1_InitConfig, &ftmStateStruct);
	FTM_DRV_InitPwm(INST_FLEXTIMER_PWM1, &flexTimer_pwm1_PwmConfig);

}

void hx8880_spi_init(void)
{
	LPSPI_DRV_MasterInit(SEND1, &Send1State, &Send1_MasterConfig0);
	//LPSPI_DRV_SlaveInit(SEND, &SendState, &Send_SlaveConfig0);//test
}
