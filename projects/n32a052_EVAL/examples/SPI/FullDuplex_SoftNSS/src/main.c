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

#define BufferSize 32

SPI_InitType SPI_InitStructure;
uint8_t SPIy_Buffer_Tx[BufferSize] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
                                      0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16,
                                      0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20};
uint8_t SPIz_Buffer_Tx[BufferSize] = {0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B,
                                      0x5C, 0x5D, 0x5E, 0x5F, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
                                      0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70};
uint8_t SPIy_Buffer_Rx[BufferSize], SPIz_Buffer_Rx[BufferSize];
__IO uint8_t TxIdx = 0, RxIdx = 0, k = 0;
volatile TestStatus TransferStatus1 = FAILED, TransferStatus2 = FAILED;
volatile TestStatus TransferStatus3 = FAILED, TransferStatus4 = FAILED;

void RCC_Configuration(void);
void GPIO_Configuration(void);
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);

/**
*\*\name    main.
*\*\fun     main program.
*\*\param   none
*\*\return  none 
**/
int main(void)
{
    /* At this stage the microcontroller clock setting is already configured,
       this is done through SystemInit() function which is called from startup
       file (startup_n32a052.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_n32a052.c file */

    /* System clocks configuration */
    RCC_Configuration();

    log_init();
    
    log_info(" This is FullDuplex_SoftNSS demo!\r\n");
    /* GPIO configuration */
    GPIO_Configuration();

    /* SPIy configuration */
    SPI_InitStruct(&SPI_InitStructure);
    SPI_InitStructure.DataDirection = SPI_DIR_DOUBLELINE_FULLDUPLEX;
    SPI_InitStructure.SpiMode       = SPI_MODE_MASTER;
    SPI_InitStructure.DataLen       = SPI_DATA_SIZE_8BITS;
    SPI_InitStructure.CLKPOL        = SPI_CLKPOL_LOW;
    SPI_InitStructure.CLKPHA        = SPI_CLKPHA_SECOND_EDGE;
    SPI_InitStructure.NSS           = SPI_NSS_SOFT;
    SPI_InitStructure.BaudRatePres  = SPI_BR_PRESCALER_8;
    SPI_InitStructure.FirstBit      = SPI_FB_LSB;
    SPI_InitStructure.CRCPoly       = 7;
    SPI_Init(SPIy, &SPI_InitStructure);

    /* SPIz configuration */
    SPI_InitStructure.SpiMode       = SPI_MODE_SLAVE;
    SPI_Init(SPIz, &SPI_InitStructure);

    /* Enable SPIy */
    SPI_Enable(SPIy, ENABLE);
    /* Enable SPIz */
    SPI_Enable(SPIz, ENABLE);

    /* Transfer procedure */
    while (TxIdx < BufferSize)
    {
        /* Wait for SPIy Tx buffer empty */
        while (SPI_GetStatus(SPIy, SPI_TE_FLAG) == RESET)
            ;
        /* Send SPIz data */
        SPI_TransmitData(SPIz, SPIz_Buffer_Tx[TxIdx]);
        /* Send SPIy data */
        SPI_TransmitData(SPIy, SPIy_Buffer_Tx[TxIdx++]);
        /* Wait for SPIz data reception */
        while (SPI_GetStatus(SPIz, SPI_RNE_FLAG) == RESET)
            ;
        /* Read SPIz received data */
        SPIz_Buffer_Rx[RxIdx] = SPI_ReceiveData(SPIz);
        /* Wait for SPIy data reception */
        while (SPI_GetStatus(SPIy, SPI_RNE_FLAG) == RESET)
            ;
        /* Read SPIy received data */
        SPIy_Buffer_Rx[RxIdx++] = SPI_ReceiveData(SPIy);
    }

    /* Check the correctness of written dada */
    TransferStatus1 = Buffercmp(SPIz_Buffer_Rx, SPIy_Buffer_Tx, BufferSize);
    TransferStatus2 = Buffercmp(SPIy_Buffer_Rx, SPIz_Buffer_Tx, BufferSize);
    
    /* TransferStatus1, TransferStatus2 = PASSED, if the transmitted and received data
       are equal */
    /* TransferStatus1, TransferStatus2 = FAILED, if the transmitted and received data
       are different */
    if((TransferStatus1 == PASSED) && (TransferStatus2 == PASSED))
    {
        log_info("SPI1 master SPI2 slave TEST passed!\r\n");
    }
    else
    {
        log_info("SPI1 master SPI2 slave TEST Failed!\r\n");
    }
    

    /* SPIy Re-configuration */
    SPI_InitStructure.SpiMode = SPI_MODE_SLAVE;
    SPI_Init(SPIy, &SPI_InitStructure);

    /* SPIz Re-configuration */
    SPI_InitStructure.SpiMode = SPI_MODE_MASTER;
    SPI_Init(SPIz, &SPI_InitStructure);

    /* Reset TxIdx, RxIdx indexes and receive tables values */
    TxIdx = 0;
    RxIdx = 0;
    for (k = 0; k < BufferSize; k++)
        SPIz_Buffer_Rx[k] = 0;
    for (k = 0; k < BufferSize; k++)
        SPIy_Buffer_Rx[k] = 0;

    /* Transfer procedure */
    while (TxIdx < BufferSize)
    {
        /* Wait for SPIz Tx buffer empty */
        while (SPI_GetStatus(SPIz, SPI_TE_FLAG) == RESET)
            ;
        /* Send SPIy data */
        SPI_TransmitData(SPIy, SPIy_Buffer_Tx[TxIdx]);
        /* Send SPIz data */
        SPI_TransmitData(SPIz, SPIz_Buffer_Tx[TxIdx++]);
        /* Wait for SPIy data reception */
        while (SPI_GetStatus(SPIy, SPI_RNE_FLAG) == RESET)
            ;
        /* Read SPIy received data */
        SPIy_Buffer_Rx[RxIdx] = SPI_ReceiveData(SPIy);
        /* Wait for SPIz data reception */
        while (SPI_GetStatus(SPIz, SPI_RNE_FLAG) == RESET)
            ;
        /* Read SPIz received data */
        SPIz_Buffer_Rx[RxIdx++] = SPI_ReceiveData(SPIz);
    }

    /* Check the correctness of written dada */
    TransferStatus3 = Buffercmp(SPIz_Buffer_Rx, SPIy_Buffer_Tx, BufferSize);
    TransferStatus4 = Buffercmp(SPIy_Buffer_Rx, SPIz_Buffer_Tx, BufferSize);
    /* TransferStatus3, TransferStatus4 = PASSED, if the transmitted and received data
       are equal */
    /* TransferStatus3, TransferStatus4 = FAILED, if the transmitted and received data
       are different */
    if((TransferStatus3 == PASSED) && (TransferStatus4 == PASSED))
    {
        log_info("SPI2 master SPI1 slave TEST passed!\r\n");
    }
    else
    {
        log_info("SPI2 master SPI1 slave TEST Failed!\r\n");
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
    /* Enable peripheral clocks --------------------------------------------------*/
    /* GPIOA, AFIO clock enable */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB | RCC_APB2_PERIPH_GPIOC | RCC_APB2_PERIPH_GPIOD | RCC_APB2_PERIPH_AFIO, ENABLE);

    /* SPI1 Periph clock enable */
    RCC_EnableAPB2PeriphClk(SPIy_CLK | SPIz_CLK, ENABLE);
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
    /* Configure SPI_MASTER pins: SCK */
    GPIO_InitStructure.Pin        = GPIO_PIN_12;
    GPIO_InitStructure.GPIO_Slew_Rate = GPIO_SLEW_RATE_FAST;
    GPIO_InitStructure.GPIO_Mode  = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Pull  = GPIO_PULL_DOWN;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF0_SPI1;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
    /* Configure SPI_MASTER pins: MISO */
    GPIO_InitStructure.Pin        = GPIO_PIN_5;
    GPIO_InitStructure.GPIO_Mode  = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Pull  = GPIO_NO_PULL;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF5_SPI1;
    GPIO_InitPeripheral(GPIOD, &GPIO_InitStructure);
    /* Configure SPI_MASTER pins:  MOSI */
    GPIO_InitStructure.Pin       = GPIO_PIN_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF0_SPI1;
    GPIO_InitStructure.GPIO_Pull = GPIO_NO_PULL;
    GPIO_InitPeripheral(GPIOD, &GPIO_InitStructure);
    
    /* Configure SPI_SLAVE pins: SCK */
    GPIO_InitStructure.Pin       = GPIO_PIN_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF1_SPI2;
    GPIO_InitStructure.GPIO_Pull = GPIO_NO_PULL;
    GPIO_InitPeripheral(GPIOC, &GPIO_InitStructure);
    /* Configure SPI_SLAVE pins: MISO */
    GPIO_InitStructure.Pin       = GPIO_PIN_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF1_SPI2;
    GPIO_InitStructure.GPIO_Pull = GPIO_NO_PULL;
    GPIO_InitPeripheral(GPIOC, &GPIO_InitStructure);
    /* Configure SPI_SLAVE pins: MOSI  */
    GPIO_InitStructure.Pin       = GPIO_PIN_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF4_SPI2;
    GPIO_InitStructure.GPIO_Pull = GPIO_NO_PULL;
    GPIO_InitPeripheral(GPIOC, &GPIO_InitStructure);
}


/**
*\*\name    Buffercmp.
*\*\fun     Compares two buffers.
*\*\param   pBuffer1
*\*\param   pBuffer2
*\*\param   BufferLength
*\*\return  FAILED or PASSED
**/
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength)
{
    while (BufferLength--)
    {
        if (*pBuffer1 != *pBuffer2)
        {
            return FAILED;
        }

        pBuffer1++;
        pBuffer2++;
    }

    return PASSED;
}
