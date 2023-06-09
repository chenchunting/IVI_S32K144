/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : i2c2.h
**     Project     : s32k144
**     Processor   : S32K144_100
**     Component   : i2c_pal
**     Version     : Component SDK_S32K14x_09, Driver 01.00, CPU db: 3.00.000
**     Repository  : SDK_S32K14x_09
**     Compiler    : GNU C Compiler
**     Date/Time   : 2023-04-18, 16:56, # CodeGen: 14
**     Contents    :
**         I2C_MasterInit                - status_t I2C_MasterInit(i2c_instance_t instance,i2c_master_t * config);
**         I2C_MasterSendData            - status_t I2C_MasterSendData(i2c_instance_t instance,void * txBuffer,void *...
**         I2C_MasterReceiveData         - status_t I2C_MasterReceiveData(i2c_instance_t instance, uint8_t * txBuffer,...
**         I2C_MasterReceiveDataBlocking - status_t I2C_MasterReceiveDataBlocking(i2c_instance_t instance, uint8_t *...
**         I2C_MasterSetSlaveAddress     - status_t I2C_MasterSetSlaveAddress(i2c_instance_t instance,const uint16_t...
**         I2C_MasterGetTransferStatus   - status_t I2C_MasterGetTransferStatus(i2c_instance_t instance,uint32_t *...
**         I2C_MasterSetBaudRate         - status_t I2C_MasterSetBaudRate(i2c_instance_t instance, i2c_master_t *config,...
**         I2C_MasterGetBaudRate         - status_t I2C_MasterGetBaudRate(i2c_instance_t instance, uint32_t *baudRate);
**         I2C_MasterAbortTransfer       - status_t I2C_MasterAbortTransfer(i2c_instance_t instance);
**         I2C_MasterDeinit              - status_t I2C_MasterDeinit(i2c_instance_t instance);
**         I2C_GetDefaultMasterConfig    - status_t I2C_GetDefaultMasterConfig(i2c_master_t *config);
**         I2C_GetDefaultSlaveConfig     - status_t I2C_GetDefaultSlaveConfig(i2c_slave_t * config);
**         I2C_SlaveInit                 - status_t I2C_SlaveInit(i2c_instance_t instance, i2c_slave_t *config);
**         I2C_SlaveSendData             - status_t I2C_SlaveSendData(i2c_instance_t instance, const uint8_t *txBuff,...
**         I2C_SlaveSendDataBlocking     - status_t I2C_SlaveSendDataBlocking(i2c_instance_t instance, const uint8_t...
**         I2C_SlaveReceiveData          - status_t I2C_SlaveReceiveData(i2c_instance_t instance, const uint8_t *rxBuff,...
**         I2C_SlaveReceiveDataBlocking  - status_t I2C_SlaveReceiveDataBlocking(i2c_instance_t instance, const uint8_t...
**         I2C_SlaveSetRxBuffer          - status_t I2C_SlaveSetRxBuffer(uint32_t instance,uint8_t * rxBuff,uint32_t...
**         I2C_SlaveSetTxBuffer          - status_t I2C_SlaveSetTxBuffer(uint32_t instance,uint8_t * txBuff,uint32_t...
**         I2C_SlaveDeinit               - status_t I2C_SlaveDeinit(i2c_instance_t instance);
**         I2C_SlaveGetTransferStatus    - status_t I2C_SlaveGetTransferStatus(i2c_instance_t instance,uint32_t *...
**         I2C_SlaveAbortTransfer        - status_t I2C_SlaveAbortTransfer(i2c_instance_t instance);
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
** @file i2c2.h
** @version 01.00
*/
/*!
**  @addtogroup i2c2_module i2c2 module documentation
**  @{
*/
#ifndef i2c2_H
#define i2c2_H

/* MODULE i2c2. */
/* Include inherited beans */
#include "clockMan1.h"
#include "dmaController1.h"
#include "Cpu.h"
/*! @brief Master module configurations */
extern i2c_master_t i2c2_MasterConfig0;
/*! @brief Slave module configurations */
/*! @brief Define external callbacks for slave devices */
/*! @brief Define external callbacks for master devices */


#endif
/* ifndef __i2c2_H */
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

