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

#define BufferSize 32

SPI_InitType SPI_InitStructure;
uint16_t SPI1_Buffer_Tx[BufferSize] = {0x0102, 0x0304, 0x0506, 0x0708, 0x090A, 0x0B0C, 0x0D0E, 0x0F10,
                                       0x1112, 0x1314, 0x1516, 0x1718, 0x191A, 0x1B1C, 0x1D1E, 0x1F20,
                                       0x2122, 0x2324, 0x2526, 0x2728, 0x292A, 0x2B2C, 0x2D2E, 0x2F30,
                                       0x3132, 0x3334, 0x3536, 0x3738, 0x393A, 0x3B3C, 0x3D3E, 0x3F40};
uint16_t SPI2_Buffer_Tx[BufferSize] = {0x5152, 0x5354, 0x5556, 0x5758, 0x595A, 0x5B5C, 0x5D5E, 0x5F60,
                                       0x6162, 0x6364, 0x6566, 0x6768, 0x696A, 0x6B6C, 0x6D6E, 0x6F70,
                                       0x7172, 0x7374, 0x7576, 0x7778, 0x797A, 0x7B7C, 0x7D7E, 0x7F80,
                                       0x8182, 0x8384, 0x8586, 0x8788, 0x898A, 0x8B8C, 0x8D8E, 0x8F90};
uint16_t SPI1_Buffer_Rx[BufferSize], SPI2_Buffer_Rx[BufferSize];
uint32_t TxIdx = 0, RxIdx = 0;
__IO uint16_t CRC1Value = 0, CRC2Value = 0;
volatile TestStatus TransferStatus1 = FAILED, TransferStatus2 = FAILED;

void RCC_Configuration(void);
void GPIO_Configuration(void);
TestStatus Buffercmp(uint16_t* pBuffer1, uint16_t* pBuffer2, uint16_t BufferLength);

/**
*\*\name    main.
*\*\fun     main program.
*\*\param   none
*\*\return  none 
**/
int main(void)
{
    uint32_t SPI1_CRCTX,SPI1_CRCRX,SPI2_CRCTX,SPI2_CRCRX;
    /* At this stage the microcontroller clock setting is already configured,
        this is done through SystemInit() function which is called from startup
        file (startup_n32a052.s) before to branch to application main.
        To reconfigure the default setting of SystemInit() function, refer to
        system_n32a052.c file */

    /* System clocks configuration */
    RCC_Configuration();
    log_init();
    
    log_info(" This is SPI CRC demo! \r\n");
    /* GPIO configuration */
    GPIO_Configuration();

    /* SPI1 configuration */
    SPI_InitStruct(&SPI_InitStructure);
    SPI_InitStructure.DataDirection = SPI_DIR_DOUBLELINE_FULLDUPLEX;
    SPI_InitStructure.SpiMode       = SPI_MODE_MASTER;
    SPI_InitStructure.DataLen       = SPI_DATA_SIZE_16BITS;
    SPI_InitStructure.CLKPOL        = SPI_CLKPOL_LOW;
    SPI_InitStructure.CLKPHA        = SPI_CLKPHA_SECOND_EDGE;
    SPI_InitStructure.NSS           = SPI_NSS_SOFT;
    SPI_InitStructure.BaudRatePres  = SPI_BR_PRESCALER_16;
    SPI_InitStructure.FirstBit      = SPI_FB_MSB;
    SPI_InitStructure.CRCPoly       = 7;
    SPI_Init(SPI1, &SPI_InitStructure);

    /* SPI2 configuration */
    SPI_InitStructure.SpiMode = SPI_MODE_SLAVE;
    SPI_Init(SPI2, &SPI_InitStructure);

    /* Enable SPI1 CRC calculation */
    SPI_EnableCalculateCrc(SPI1, ENABLE);
    /* Enable SPI2 CRC calculation */
    SPI_EnableCalculateCrc(SPI2, ENABLE);

    /* Enable SPI1 */
    SPI_Enable(SPI1, ENABLE);
    /* Enable SPI2 */
    SPI_Enable(SPI2, ENABLE);

    /* Transfer procedure */
    while (TxIdx < BufferSize - 1)
    {
        /* Wait for SPI1 Tx buffer empty */
        while (SPI_GetStatus(SPI1, SPI_TE_FLAG) == RESET)
            ;
        /* Send SPI2 data */
        SPI_TransmitData(SPI2, SPI2_Buffer_Tx[TxIdx]);
        /* Send SPI1 data */
        SPI_TransmitData(SPI1, SPI1_Buffer_Tx[TxIdx++]);
        /* Wait for SPI2 data reception */
        while (SPI_GetStatus(SPI2, SPI_RNE_FLAG) == RESET)
            ;
        /* Read SPI2 received data */
        SPI2_Buffer_Rx[RxIdx] = SPI_ReceiveData(SPI2);
        /* Wait for SPI1 data reception */
        while (SPI_GetStatus(SPI1, SPI_RNE_FLAG) == RESET)
            ;
        /* Read SPI1 received data */
        SPI1_Buffer_Rx[RxIdx++] = SPI_ReceiveData(SPI1);
    }

    /* Wait for SPI1 Tx buffer empty */
    while (SPI_GetStatus(SPI1, SPI_TE_FLAG) == RESET)
        ;
    /* Wait for SPI2 Tx buffer empty */
    while (SPI_GetStatus(SPI2, SPI_TE_FLAG) == RESET)
        ;

    /* Send last SPI2_Buffer_Tx data */
    SPI_TransmitData(SPI2, SPI2_Buffer_Tx[TxIdx]);
    /* Enable SPI2 CRC transmission */
    SPI_TransmitCrcNext(SPI2);
    /* Send last SPI1_Buffer_Tx data */
    SPI_TransmitData(SPI1, SPI1_Buffer_Tx[TxIdx]);
    /* Enable SPI1 CRC transmission */
    SPI_TransmitCrcNext(SPI1);

    /* Wait for SPI1 last data reception */
    while (SPI_GetStatus(SPI1, SPI_RNE_FLAG) == RESET)
        ;
    /* Read SPI1 last received data */
    SPI1_Buffer_Rx[RxIdx] = SPI_ReceiveData(SPI1);
    /* Read SPI2 last received data */
    SPI2_Buffer_Rx[RxIdx] = SPI_ReceiveData(SPI2);

    /* Wait for SPI2 data reception: CRC transmitted by SPI1 */
    while (SPI_GetStatus(SPI2, SPI_RNE_FLAG) == RESET)
        ;
    /* Wait for SPI1 data reception: CRC transmitted by SPI2 */
    while (SPI_GetStatus(SPI1, SPI_RNE_FLAG) == RESET)
        ;
    

    /* Check the received data with the send ones */
    TransferStatus1 = Buffercmp(SPI2_Buffer_Rx, SPI1_Buffer_Tx, BufferSize);
    TransferStatus2 = Buffercmp(SPI1_Buffer_Rx, SPI2_Buffer_Tx, BufferSize);
    /* TransferStatus1, TransferStatus2 = PASSED, if the data transmitted and received
       are correct */
    /* TransferStatus1, TransferStatus2 = FAILED, if the data transmitted and received
       are different */

    /* Test on the SPI1 CRC Error flag */
    if ((SPI_GetStatus(SPI1, SPI_CRCERR_FLAG)) == SET)
    {
        TransferStatus2 = FAILED;
    }

    /* Test on the SPI2 CRC Error flag */
    if ((SPI_GetStatus(SPI2, SPI_CRCERR_FLAG)) == SET)
    {
        TransferStatus1 = FAILED;
    }
    
    if(TransferStatus1 != FAILED)
    {
        log_info("SPI communication is normal! \r\n");
    }
    else
    {
        log_info("SPI communication exception! \r\n");
    }

    /* Read SPI1 received CRC value */
    CRC1Value = SPI_ReceiveData(SPI1);
    /* Read SPI2 received CRC value */
    CRC2Value = SPI_ReceiveData(SPI2);
    
    /* Get SPI1&SPI2 CRC value */
    SPI1_CRCTX = SPI_GetCRCDat(SPI1,SPI_CRC_TX);
    SPI1_CRCRX = SPI_GetCRCDat(SPI1,SPI_CRC_RX);
    SPI2_CRCTX = SPI_GetCRCDat(SPI2,SPI_CRC_TX);
    SPI2_CRCRX = SPI_GetCRCDat(SPI2,SPI_CRC_RX);
    
    if((CRC1Value == SPI1_CRCRX) && (SPI1_CRCRX == SPI2_CRCTX))
    {
        log_info("SPI1 CRC is OK! \r\n");
    }
    else
    {
        log_info("SPI1 CRC is Fail! \r\n");
    }
    
    if((CRC2Value == SPI2_CRCRX) && (SPI2_CRCRX == SPI1_CRCTX))
    {
        log_info("SPI2 CRC is OK! \r\n");
    }
    else
    {
        log_info("SPI2 CRC is Fail! \r\n");
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
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_SPI1 | RCC_APB2_PERIPH_SPI2, ENABLE);
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
TestStatus Buffercmp(uint16_t* pBuffer1, uint16_t* pBuffer2, uint16_t BufferLength)
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

