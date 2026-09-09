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

#define TxBufferSize1 (countof(TxBuffer1) - 1)
#define TxBufferSize2 (countof(TxBuffer2) - 1)

#define countof(a) (sizeof(a) / sizeof(*(a)))

UART_InitType UART_InitStructure;
uint8_t TxBuffer1[] = "UART DMA Interrupt: UARTy -> UARTz using DMA Tx and Rx Flag";
uint8_t TxBuffer2[] = "UART DMA Interrupt: UARTz -> UARTy using DMA Tx and Rx Interrupt";
uint8_t RxBuffer1[TxBufferSize2];
uint8_t RxBuffer2[TxBufferSize1];
uint8_t NbrOfDataToRead             = TxBufferSize1;
uint32_t indexFlag                  = 0;
volatile TestStatus TransferStatus1 = FAILED, TransferStatus2 = FAILED;

/**
*\*\name    main.
*\*\fun     Main program.
*\*\param   none
*\*\return  none
**/
int main(void)
{
    /* System Clocks Configuration */
    RCC_Configuration();

    /* NVIC configuration */
    NVIC_Configuration();

    /* Configure the GPIO ports */
    GPIO_Configuration();

    /* Configure the DMA */
    DMA_Configuration();

    /* UARTy and UARTz configuration */
    UART_StructInit(&UART_InitStructure);
    UART_InitStructure.BaudRate            = 115200;
    UART_InitStructure.WordLength          = UART_WL_8B;
    UART_InitStructure.StopBits            = UART_STPB_1;
    UART_InitStructure.Parity              = UART_PE_NO;
    UART_InitStructure.Mode                = UART_MODE_RX | UART_MODE_TX;

    /* Configure UARTy and UARTz */
    UART_Init(UARTy, &UART_InitStructure);
    UART_Init(UARTz, &UART_InitStructure);

    /* Enable UARTy DMA Rx and TX request */
    UART_EnableDMA(UARTy, UART_DMAREQ_RX | UART_DMAREQ_TX,ENABLE);
    /* Enable UARTz DMA Rx and TX request */
    UART_EnableDMA(UARTz, UART_DMAREQ_RX | UART_DMAREQ_TX,ENABLE);

    /* Enable the UARTz Receive Interrupt */
    UART_ConfigInt(UARTz, UART_INT_RXDNE,ENABLE);

    /* Enable UARTy TX DMA Channel */
    DMA_EnableChannel(UARTy_Tx_DMA_Channel,ENABLE);
    /* Enable UARTz TX DMA Channel */
    DMA_EnableChannel(UARTz_Tx_DMA_Channel,ENABLE);

    /* Enable the UARTy and UARTz */
    UART_Enable(UARTy, ENABLE);
    UART_Enable(UARTz, ENABLE);

    /* Receive the TxBuffer2 */
    while (indexFlag < TxBufferSize2)
    {
        while (UART_GetFlagStatus(UARTy, UART_FLAG_RXDNE) == RESET)
        {
            /* Overflow data loss */
            if(UART_GetFlagStatus(UARTy, UART_FLAG_OREF) != RESET)
            {
                UARTy->DAT;
            }
        }
        RxBuffer1[indexFlag++] = UART_ReceiveData(UARTy);
    }

    /* Wait until UARTy TX DMA Channel  Transfer Complete */
    while (DMA_GetFlagStatus(UARTy_Tx_DMA_FLAG,DMA) == RESET)
    {
    }
    /* Wait until UARTz TX DMA Channel Transfer Complete */
    while (DMA_GetFlagStatus(UARTz_Tx_DMA_FLAG,DMA) == RESET)
    {
    }

    /* Check the received data with the send ones */
    TransferStatus1 = Buffercmp(TxBuffer2, RxBuffer1, TxBufferSize2);
    /* TransferStatus1 = PASSED, if the data transmitted from UARTz and
       received by UARTy are the same */
    /* TransferStatus1 = FAILED, if the data transmitted from UARTz and
       received by UARTy are different */
    TransferStatus2 = Buffercmp(TxBuffer1, RxBuffer2, TxBufferSize1);
    /* TransferStatus2 = PASSED, if the data transmitted from UARTy and
       received by UARTz are the same */
    /* TransferStatus2 = FAILED, if the data transmitted from UARTy and
       received by UARTz are different */

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
    /* DMA clock enable */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_DMA,ENABLE);
    /* Enable GPIO clock */
    RCC_EnableAPB2PeriphClk(UARTy_GPIO_CLK | UARTz_GPIO_CLK,ENABLE);
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO,ENABLE);
    /* Enable UARTy and UARTz Clock */
    UARTy_APBxClkCmd(UARTy_CLK,ENABLE);
    UARTz_APBxClkCmd(UARTz_CLK,ENABLE);
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

    /* Initialize GPIO_InitStructure */
    GPIO_InitStruct(&GPIO_InitStructure);
    
    /* Configure UARTy Tx as alternate function push-pull and pull-up */
    GPIO_InitStructure.Pin            = UARTy_TxPin;  
    GPIO_InitStructure.GPIO_Pull      = GPIO_PULL_UP;
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Alternate = UARTy_Tx_GPIO_AF;
    GPIO_InitPeripheral(UARTy_GPIO, &GPIO_InitStructure);

    /* Configure UARTz Tx as alternate function push-pull and pull-up */
    GPIO_InitStructure.Pin            = UARTz_TxPin;
    GPIO_InitStructure.GPIO_Alternate = UARTz_Tx_GPIO_AF;
    GPIO_InitPeripheral(UARTz_GPIO, &GPIO_InitStructure); 

    /* Configure UARTx Rx as alternate function push-pull and pull-up */
    GPIO_InitStructure.Pin            = UARTy_RxPin;
    GPIO_InitStructure.GPIO_Alternate = UARTy_Rx_GPIO_AF;
    GPIO_InitPeripheral(UARTy_GPIO, &GPIO_InitStructure);    

    /* Configure UARTz Rx as alternate function push-pull and pull-up */
    GPIO_InitStructure.Pin            = UARTz_RxPin;
    GPIO_InitStructure.GPIO_Alternate = UARTz_Rx_GPIO_AF;
    GPIO_InitPeripheral(UARTz_GPIO, &GPIO_InitStructure);    
}


/**
*\*\name    NVIC_Configuration.
*\*\fun     Configures the nested vectored interrupt controller.
*\*\param   none
*\*\return  none
**/
void NVIC_Configuration(void)
{
    NVIC_InitType NVIC_InitStructure;

    /* Enable the UARTz Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel                   = UARTz_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority           = NVIC_PRIORITY_0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


/**
*\*\name    DMA_Configuration.
*\*\fun     Configures the DMA.
*\*\param   none
*\*\return  none
**/
void DMA_Configuration(void)
{
    DMA_InitType DMA_InitStructure;

    /* UARTy_Tx_DMA_Channel (triggered by UARTy Tx event) Config */
    DMA_DeInit(UARTy_Tx_DMA_Channel);
    DMA_StructInit(&DMA_InitStructure);
    DMA_InitStructure.PeriphAddr     = UARTy_DAT_Base;
    DMA_InitStructure.MemAddr        = (uint32_t)TxBuffer1;
    DMA_InitStructure.Direction      = DMA_DIR_PERIPH_DST;
    DMA_InitStructure.BufSize        = TxBufferSize1;
    DMA_InitStructure.PeriphInc      = DMA_PERIPH_INC_DISABLE;
    DMA_InitStructure.DMA_MemoryInc  = DMA_MEM_INC_ENABLE;
    DMA_InitStructure.PeriphDataSize = DMA_PERIPH_DATA_SIZE_BYTE;
    DMA_InitStructure.MemDataSize    = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.CircularMode   = DMA_MODE_NORMAL;
    DMA_InitStructure.Priority       = DMA_PRIORITY_VERY_HIGH;
    DMA_InitStructure.Mem2Mem        = DMA_M2M_DISABLE;
    DMA_Init(UARTy_Tx_DMA_Channel, &DMA_InitStructure);
    DMA_RequestRemap(UARTy_Tx_DMA_REMAP,DMA,UARTy_Tx_DMA_Channel,ENABLE);

    /* UARTz_Tx_DMA_Channel (triggered by UARTz Tx event) Config */
    DMA_DeInit(UARTz_Tx_DMA_Channel);
    DMA_InitStructure.PeriphAddr = UARTz_DAT_Base;
    DMA_InitStructure.MemAddr    = (uint32_t)TxBuffer2;
    DMA_InitStructure.Direction  = DMA_DIR_PERIPH_DST;
    DMA_InitStructure.BufSize    = TxBufferSize2;
    DMA_Init(UARTz_Tx_DMA_Channel, &DMA_InitStructure);
    DMA_RequestRemap(UARTz_Tx_DMA_REMAP,DMA,UARTz_Tx_DMA_Channel,ENABLE);
}


/**
*\*\name    Buffercmp.
*\*\fun     Compares two buffers.
*\*\param   pBuffer1
*\*\param   pBuffer2
*\*\param   BufferLength
*\*\return  PASSED or FAILED
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

