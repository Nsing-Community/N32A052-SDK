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
*\*\copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
**/
#include <stdio.h>
#include "main.h"
#include "bsp_Tim_38K.h"

#define TxBufferSize1 (countof(TxBuffer1))

#define countof(a) (sizeof(a) / sizeof(*(a)))

UART_InitType UART_InitStructure;
uint8_t TxBuffer1[]                = "UART IrDA Example: Board1_UARTy -> Board2_UARTz using TXE and RXNE Flags";
uint8_t RxBuffer1[TxBufferSize1] = {0};
__IO uint8_t NbrOfDataToRead1 = TxBufferSize1;
__IO uint8_t TxCounter             = 0;
__IO uint8_t RxCounter             = 0;
volatile TestStatus TransferStatus = FAILED;

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
    
    /* GPIO PC2 Output 38KHz Clock */
    ADVANCE_TIM_Init();

    /* UARTy and UARTz configuration */
    UART_StructInit(&UART_InitStructure);
    UART_InitStructure.BaudRate   = 600;
    UART_InitStructure.WordLength = UART_WL_8B;
    UART_InitStructure.StopBits   = UART_STPB_1;
    UART_InitStructure.Parity     = UART_PE_NO;
    UART_InitStructure.Mode       = UART_MODE_TX;
    UART_Init(UARTy, &UART_InitStructure);
    UART_InitStructure.Mode       = UART_MODE_RX;
    UART_Init(UARTz, &UART_InitStructure);

    /* Enable UARTz Receive and Transmit interrupts */
    UART_ConfigInt(UARTz, UART_INT_RXDNE, ENABLE);
    
    /* Set the UARTy and UARTz prescaler */
    UART_SetPrescaler(UARTy, 210);
    UART_SetPrescaler(UARTz, 210);
    /* Configure the UARTy IrDA mode */
    UART_ConfigIrDAMode(UARTy, UART_IRDAMODE_LOWPPWER);
    UART_ConfigIrDAMode(UARTz, UART_IRDAMODE_LOWPPWER);
    
    /* Enable the UARTy and UARTz IrDA mode */
    UART_EnableIrDA(UARTy,ENABLE);
    UART_EnableIrDA(UARTz,ENABLE);

    /* Enable the UARTy and UARTz */
    UART_Enable(UARTy, ENABLE);
    UART_Enable(UARTz, ENABLE);

    while (TxCounter < TxBufferSize1)
    {
				while (UART_GetFlagStatus(UARTy, UART_FLAG_TXC) == RESET)
        {
        }
        /* Send one byte from Board1_UARTy to Board2_UARTz */
        UART_SendData(UARTy, TxBuffer1[TxCounter++]);
        /* Loop until Board1_UARTy DAT register is empty */
        
    }
    while (RxCounter < TxBufferSize1)
    {
    }
    /* Check the received data with the send ones */
    /* TransferStatus = PASSED, if the data transmitted from UARTy and
       received by UARTz are the same */
    /* TransferStatus = FAILED, if the data transmitted from UARTy and
       received by UARTz are different */
    TransferStatus = Buffercmp(TxBuffer1, RxBuffer1, TxBufferSize1);

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
    /* Enable GPIO clock */
    RCC_EnableAPB2PeriphClk(UARTy_GPIO_CLK | UARTz_GPIO_CLK, ENABLE);
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO,ENABLE);
    /* Enable UARTy and UARTz Clock */
    UARTy_APBxClkCmd(UARTy_CLK, ENABLE);
    UARTz_APBxClkCmd(UARTz_CLK, ENABLE);
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
   
    /* Configure UARTy Tx as alternate function push-pull */
    GPIO_InitStructure.Pin            = UARTy_TxPin;     
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Alternate = UARTy_Tx_GPIO_AF;
    GPIO_InitPeripheral(UARTy_GPIO, &GPIO_InitStructure);

    /* Configure UARTz Tx as alternate function push-pull */
    GPIO_InitStructure.Pin            = UARTz_TxPin;
    GPIO_InitStructure.GPIO_Alternate = UARTz_Tx_GPIO_AF;
    GPIO_InitPeripheral(UARTz_GPIO, &GPIO_InitStructure); 

    /* Configure UARTx Rx as alternate function push-pull */
    GPIO_InitStructure.Pin            = UARTy_RxPin;
    GPIO_InitStructure.GPIO_Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Alternate = UARTy_Rx_GPIO_AF;
    GPIO_InitPeripheral(UARTy_GPIO, &GPIO_InitStructure);    

    /* Configure UARTz Rx as alternate function push-pull */
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
    NVIC_InitStructure.NVIC_IRQChannel         = UARTz_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = NVIC_PRIORITY_0;
    NVIC_InitStructure.NVIC_IRQChannelCmd      = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
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


