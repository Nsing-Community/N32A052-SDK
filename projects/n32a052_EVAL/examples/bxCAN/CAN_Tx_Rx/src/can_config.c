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
*\*\file can_config.c
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/

#include "can_config.h"

#define CAN_TXDLC_8    ((uint8_t)8)
#define CAN_FILTERNUM0 ((uint8_t)0)

CanTxMessage CAN_TxMessage;
CanRxMessage CAN_RxMessage;


CAN_InitType        CAN_InitStructure;
CAN_FilterInitType  CAN_FilterInitStructure;

/**
*\*\name   CAN_CONFIG
*\*\fun    CAN configure.
*\*\param  none
*\*\return none
**/
void CAN_CONFIG(void)
{
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_CAN,ENABLE);
    
    /* Initializes CAN*/
    CAN_NVIC_Configuration();
    CAN_GPIO_Configuration();
    
    CAN_DeInit(CAN);
    CAN_InitStruct(&CAN_InitStructure);
    /* CAN cell init */
    CAN_InitStructure.TTCM          = DISABLE;
    CAN_InitStructure.ABOM          = DISABLE;
    CAN_InitStructure.AWKUM         = DISABLE;
    CAN_InitStructure.NART          = DISABLE;
    CAN_InitStructure.RFLM          = DISABLE;
    CAN_InitStructure.TXFP          = ENABLE;
    CAN_InitStructure.OperatingMode = CAN_Normal_Mode;
	  /* Baud rate calculation = CAN clock/(BaudRatePrescaler*(TBS1+TBS2+1)) */
    CAN_InitStructure.RSJW          = CAN_RSJW_1tq;
    CAN_InitStructure.TBS1          = CAN_TBS1_8tq;
    CAN_InitStructure.TBS2          = CAN_TBS2_7tq;   
    CAN_InitStructure.BaudRatePrescaler = 4;
    
    /*Initializes the CAN */
    CAN_Init(CAN, &CAN_InitStructure); 
    
    
    /* CAN filter init */
    CAN_FilterInitStructure.Filter_Num            = 0;
    CAN_FilterInitStructure.Filter_Mode           = CAN_Filter_IdMaskMode;
    CAN_FilterInitStructure.Filter_Scale          = CAN_Filter_32bitScale;
    CAN_FilterInitStructure.Filter_HighId         = CAN_STD_ID_LIST_32BIT_H(0x00000400);
    CAN_FilterInitStructure.Filter_LowId          = CAN_STD_ID_LIST_32BIT_L(0x00000400);
    CAN_FilterInitStructure.FilterMask_HighId     = CAN_STD_ID_LIST_32BIT_H(0x00000200);
    CAN_FilterInitStructure.FilterMask_LowId      = CAN_STD_ID_LIST_32BIT_L(0x00000200);
    CAN_FilterInitStructure.Filter_FIFOAssignment = CAN_FIFO0;      //CAN_FIFO1
    CAN_FilterInitStructure.Filter_Act            = ENABLE;
    CAN_InitFilter(&CAN_FilterInitStructure);
    /* IT Configuration for CAN */  
    CAN_INTConfig(CAN, CAN_INT_FMP0, ENABLE);
}


/**
*\*\name   CAN_NVIC_Configuration
*\*\fun    CAN NVIC configure.
*\*\param  none
*\*\return none
**/
void CAN_NVIC_Configuration(void)
{
    NVIC_InitType NVIC_InitStructure;

    NVIC_InitStructure.NVIC_IRQChannel                   = CAN_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority           = 0x0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


/**
*\*\name   CAN_GPIO_Configuration
*\*\fun    CAN GPIO configure.
*\*\param  none
*\*\return none
**/
void CAN_GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    /* Initializes the GPIO */
    GPIO_InitStruct(&GPIO_InitStructure);

    /* Configures CAN IOs */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO | RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_GPIOB, ENABLE);

    /* Configure CAN RX pin */
    GPIO_InitStructure.Pin       = GPIO_PIN_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Pull = GPIO_PULL_UP;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF7_CAN;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
    /* Configure CAN TX pin */
    GPIO_InitStructure.Pin        = GPIO_PIN_3;
    GPIO_InitStructure.GPIO_Mode  = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF4_CAN;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
}


