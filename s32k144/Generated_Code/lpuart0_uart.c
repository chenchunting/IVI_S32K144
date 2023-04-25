/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : lpuart0_uart.c
**     Project     : s32k144
**     Processor   : S32K144_100
**     Component   : uart_pal
**     Version     : Component SDK_S32K14x_09, Driver 01.00, CPU db: 3.00.000
**     Repository  : SDK_S32K14x_09
**     Compiler    : GNU C Compiler
**     Date/Time   : 2023-04-18, 14:13, # CodeGen: 10
**
**     Copyright 1997 - 2015 Freescale Semiconductor, Inc.
**     Copyright 2016-2017 NXP
**     All Rights Reserved.
**     
**     THIS SOFTWARE IS PROVIDED BY NXP "AS IS" AND ANY EXPRESSED OR
**     IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
**     OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
**     IN NO EVENT SHALL NXP OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
**     INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
**     SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
**     HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
**     STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
**     IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
**     THE POSSIBILITY OF SUCH DAMAGE.
** ###################################################################*/
/*!
** @file lpuart0_uart.c
** @version 01.00
*/
/*!
**  @addtogroup lpuart0_uart_module lpuart0_uart module documentation
**  @{
*/
#include "lpuart0_uart.h"

/* Serial User Configurations */
uart_user_config_t lpuart0_uart_Config0 = {
    .baudRate         = 115200,
    .bitCount         = UART_8_BITS_PER_CHAR,
    .parityMode       = UART_PARITY_DISABLED,
    .stopBitCount     = UART_ONE_STOP_BIT,
    .transferType     = UART_USING_INTERRUPTS,
    .rxDMAChannel     = 0U,
    .txDMAChannel     = 0U,
    .rxCallback       = NULL,
    .rxCallbackParam  = NULL,
    .txCallback       = NULL,
    .txCallbackParam  = NULL,
    .extension        = NULL
};

/* END lpuart0_uart. */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.1 [05.21]
**     for the Freescale S32K series of microcontrollers.
**
** ###################################################################
*/
