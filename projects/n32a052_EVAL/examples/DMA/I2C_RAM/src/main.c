/**
*     Copyright (c) 2023, Nations Technologies Inc.
* 
*     All rights reserved.
*
*     This software is the exclusive property of Nations Technologies Inc. (Hereinafter 
* referred to as NATIONS). This software, and the product of NATIONS described herein 
* (Hereinafter referred to as the Product) are owned by NATIONS under the laws and treaties
* of the People's Republic of China and other applicable jurisdictions worldwide.
*
*     NATIONS does not grant any license under its patents, copyrights, trademarks, or other 
* intellectual property rights. Names and brands of third party may be mentioned or referred 
* thereto (if any) for identification purposes only.
*
*     NATIONS reserves the right to make changes, corrections, enhancements, modifications, and 
* improvements to this software at any time without notice. Please contact NATIONS and obtain 
* the latest version of this software before placing orders.

*     Although NATIONS has attempted to provide accurate and reliable information, NATIONS assumes 
* no responsibility for the accuracy and reliability of this software.
* 
*     It is the responsibility of the user of this software to properly design, program, and test 
* the functionality and safety of any application made of this information and any resulting product. 
* In no event shall NATIONS be liable for any direct, indirect, incidental, special,exemplary, or 
* consequential damages arising in any way out of the use of this software or the Product.
*
*     NATIONS Products are neither intended nor warranted for usage in systems or equipment, any
* malfunction or failure of which may cause loss of human life, bodily injury or severe property 
* damage. Such applications are deemed, "Insecure Usage".
*
*     All Insecure Usage shall be made at user's risk. User shall indemnify NATIONS and hold NATIONS 
* harmless from and against all claims, costs, damages, and other liabilities, arising from or related 
* to any customer's Insecure Usage.

*     Any express or implied warranty with regard to this software or the Product, including,but not 
* limited to, the warranties of merchantability, fitness for a particular purpose and non-infringement
* are disclaimed to the fullest extent permitted by law.

*     Unless otherwise explicitly permitted by NATIONS, anyone may not duplicate, modify, transcribe
* or otherwise distribute this software for any purposes, in whole or in part.
*
*     NATIONS products and technologies shall not be used for or incorporated into any products or systems
* whose manufacture, use, or sale is prohibited under any applicable domestic or foreign laws or regulations. 
* User shall comply with any applicable export control laws and regulations promulgated and administered by 
* the governments of any countries asserting jurisdiction over the parties or transactions.
**/

/**
*\*\file main.c
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/
#include "main.h"
#include "log.h"

#include <string.h>

I2C_InitType I2C_InitStructure;
DMA_InitType DMA_InitStructure;
uint8_t I2C1_Tx_Buffer[BUFFER_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8};
uint8_t I2C2_Rx_Buffer[BUFFER_SIZE];
uint8_t Tx_Idx = 0, Rx_Idx = 0;
void RCC_Configuration(void);
void GPIO_Configuration(void);


/**
*\*\name    main.
*\*\fun     main program.
*\*\param   none
*\*\return  none 
**/
int main(void)
{
    log_init();

    log_info("\n this is a DMA I2C to RAM Demo.\n");
    
    /* System Clocks Configuration */
    RCC_Configuration();
    
    /* Configure the GPIO ports */
    GPIO_Configuration();
    
    /* DMA channel5 configuration */
    DMA_DeInit(DMA_CH5);
    DMA_StructInit(&DMA_InitStructure);
    DMA_InitStructure.PeriphAddr     = (uint32_t)&I2C2->DAT;
    DMA_InitStructure.MemAddr        = (uint32_t)I2C2_Rx_Buffer;
    DMA_InitStructure.Direction      = DMA_DIR_PERIPH_SRC;
    DMA_InitStructure.BufSize        = BUFFER_SIZE;
    DMA_InitStructure.PeriphInc      = DMA_PERIPH_INC_DISABLE;
    DMA_InitStructure.DMA_MemoryInc  = DMA_MEM_INC_ENABLE;
    DMA_InitStructure.PeriphDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.MemDataSize    = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.CircularMode   = DMA_MODE_NORMAL;
    DMA_InitStructure.Priority       = DMA_PRIORITY_VERY_HIGH;
    DMA_InitStructure.Mem2Mem        = DMA_M2M_DISABLE;
    DMA_Init(DMA_CH5, &DMA_InitStructure);
    DMA_RequestRemap(DMA_REMAP_I2C2_RX,DMA,DMA_CH5,ENABLE);
    /* DMA channel1 configuration */
    DMA_DeInit(DMA_CH1);
    DMA_InitStructure.PeriphAddr = (uint32_t)&I2C1->DAT;
    DMA_InitStructure.MemAddr    = (uint32_t)I2C1_Tx_Buffer;
    DMA_InitStructure.Direction  = DMA_DIR_PERIPH_DST;
    DMA_InitStructure.Priority   = DMA_PRIORITY_HIGH;
    DMA_Init(DMA_CH1, &DMA_InitStructure);
    DMA_RequestRemap(DMA_REMAP_I2C1_TX,DMA,DMA_CH1,ENABLE);

    I2C_DeInit(I2C1);
    I2C_EnableTimeoutDetect(I2C1, I2C_TIMEOUT_LOW, DISABLE);
    I2C_EnableTimeoutDetect(I2C2, I2C_TIMEOUT_LOW, DISABLE);

    /* I2C1 configuration */
    I2C_InitStruct(&I2C_InitStructure);
    I2C_InitStructure.BusMode     = I2C_BUSMODE_I2C;
    I2C_InitStructure.FmDutyCycle = I2C_FMDUTYCYCLE_2;
    I2C_InitStructure.OwnAddr1    = I2C1_SLAVE_ADDRESS7;
    I2C_InitStructure.AckEnable   = I2C_ACKEN;
    I2C_InitStructure.AddrMode    = I2C_ADDR_MODE_7BIT;
    I2C_InitStructure.ClkSpeed    = I2C_CLK_SPEED;
    I2C_Init(I2C1, &I2C_InitStructure);
    /* I2C2 configuration */
    I2C_InitStructure.OwnAddr1 = I2C2_SLAVE_ADDRESS7;
    I2C_Init(I2C2, &I2C_InitStructure);
    
    /* Enable I2C1 and I2C2 */
    I2C_Enable(I2C1, ENABLE);
    I2C_Enable(I2C2, ENABLE);

    /** Transmission Phase **/
    /* Send I2C1 START condition */
    I2C_GenerateStart(I2C1, ENABLE);
    /* Test on I2C1 EV5 and clear it */
    while (!I2C_CheckEvent(I2C1, I2C_EVT_MASTER_MODE_FLAG))
        ;
    /* Send I2C2 slave Address for write */
    I2C_SendAddr7bit(I2C1, I2C2_SLAVE_ADDRESS7, I2C_DIRECTION_SEND)
        ;
    /* Test on I2C2 EV1 and clear it */
    while (!I2C_CheckEvent(I2C2, I2C_EVT_SLAVE_RECV_ADDR_MATCHED))
        ;
    /* Test on I2C1 EV6 and clear it */
    while (!I2C_CheckEvent(I2C1, I2C_EVT_MASTER_TXMODE_FLAG))
        ;

    /* Enable I2C2 DMA */
    I2C_EnableDMA(I2C2, ENABLE);
    /* Enable I2C1 DMA */
    I2C_EnableDMA(I2C1, ENABLE);

    /* Enable DMA Channel5 */
    DMA_EnableChannel(DMA_CH5, ENABLE);
    /* Enable DMA Channel1 */
    DMA_EnableChannel(DMA_CH1, ENABLE);

    /* DMA Channel5 transfer complete test */
    while (!DMA_GetFlagStatus(DMA_FLAG_TC5, DMA))
        ;
    /* DMA Channel1 transfer complete test */
    while (!DMA_GetFlagStatus(DMA_FLAG_TC1, DMA))
        ;

    /* Send I2C1 STOP Condition */
    I2C_GenerateStop(I2C1, ENABLE);
    /* Test on I2C2 EV4 */
    while (!I2C_CheckEvent(I2C2, I2C_EVT_SLAVE_STOP_RECVD))
        ;
    /* Clear I2C2 STOPF flag: read operation to I2C_STS1 followed by a
    write operation to I2C_CTRL1 */
    (void)(I2C_GetFlag(I2C2, I2C_FLAG_STOPF));
    I2C_Enable(I2C2, ENABLE);
    
    /* Check if the transmitted and received data are equal */
    if (memcmp(I2C1_Tx_Buffer, I2C2_Rx_Buffer, BUFFER_SIZE) == 0)
    {
        log_info("DMA I2C to RAM passed\n");
    }
    else
    {
        log_error("DMA I2C to RAM failed\n");
    }

    while (1)
    {
    }
}

/**
*\*\name    RCC_Configuration.
*\*\fun     Configures the different system clocks.
*\*\param   none
*\*\return  none 
**/
void RCC_Configuration(void)
{
    /* Enable DMA clock */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_DMA, ENABLE);
    /* Enable GPIO clock */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_GPIOD | RCC_APB2_PERIPH_AFIO, ENABLE);
    /* Enable I2C1 and I2C2 clock */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_I2C1 | RCC_APB1_PERIPH_I2C2, ENABLE);
}


/**
*\*\name    GPIO_Configuration.
*\*\fun     Configures the different GPIO ports.
*\*\param   none
*\*\return  none 
**/
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    GPIO_InitStruct(&GPIO_InitStructure);
    /* Configure I2C1 pins: SCL and SDA */
    GPIO_InitStructure.Pin        = GPIO_PIN_4 | GPIO_PIN_3;
    GPIO_InitStructure.GPIO_Slew_Rate = GPIO_SLEW_RATE_FAST;
    GPIO_InitStructure.GPIO_Mode  = GPIO_MODE_AF_OD;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF6_I2C1;
    GPIO_InitStructure.GPIO_Pull = GPIO_PULL_UP;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);

    /* Configure I2C2 pins: SCL and SDA */
    GPIO_InitStructure.Pin = GPIO_PIN_12 | GPIO_PIN_13;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF7_I2C2;
    GPIO_InitPeripheral(GPIOD, &GPIO_InitStructure);
}

