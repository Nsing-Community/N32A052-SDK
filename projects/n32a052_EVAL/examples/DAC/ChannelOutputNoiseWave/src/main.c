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



void RCC_Configuration(void);
void GPIO_Configuration(void);
void DAC_Config(void);
void Delay(__IO uint32_t nCount);

/**
*\*\name    main.
*\*\fun     main program.
*\*\return  none
**/
int main(void)
{
    /* System clocks configuration ---------------------------------------------*/
    RCC_Configuration();

    /* GPIO configuration ------------------------------------------------------*/
    GPIO_Configuration();

    /* DAC configuration -------------------------------------------------------*/
    DAC_Config(); 

    while (1)
    {
        /* Start DAC  conversion by software */
        DAC_SoftTrgEnable(ENABLE);
        Delay(0x3FF);
    }
}

/**
*\*\name    RCC_Configuration.
*\*\fun     Configures the different system clocks.
*\*\return  none
**/
void RCC_Configuration(void)
{
    /* Enable GPIOB clocks */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB,ENABLE);
    /* Enable DAC clocks */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_DAC,ENABLE);
}

/**
*\*\name    GPIO_Configuration.
*\*\fun     Configures the different GPIO ports.
*\*\return  none
**/
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    /* Once the DAC  is enabled, the corresponding GPIO pin is automatically
    connected to the DAC converter. In order to avoid parasitic consumption,
    the GPIO pin should be configured in analog */
    GPIO_InitStruct(&GPIO_InitStructure);
    GPIO_InitStructure.Pin       = GPIO_PIN_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_ANALOG;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
}

/**
*\*\name    DAC_Config.
*\*\fun     Configures the DAC config.
*\*\return  none
**/

void DAC_Config(void)
{
    DAC_InitType DAC_InitStructure;

    /* DAC Configuration */
    DAC_InitStructure.TriggerSelect    = DAC_TRIGGER_SOFTWARE;
    DAC_InitStructure.WaveGeneration   = DAC_WAVEGEN_NOISE;
    DAC_InitStructure.LfsrUnMaskTriAmp = DAC_LFSR_UNMASK_BIT0;
    DAC_InitStructure.OutputBuffer     = DAC_OUTPUT_BUF_ENABLE;
    DAC_InitStructure.OutputHighDriver = DAC_OUTPUT_HIGH_DRIVER_DISABLE;
    DAC_Init(&DAC_InitStructure);
    
    /* Set DAC  DHR12R register */
    DAC_SetChData(DAC_ALIGN_R_12BIT, 4094);
    /* Enable DAC: Once the DAC  is enabled, PB13 is
    automatically connected to the DAC converter. */
    DAC_Enable(ENABLE);


}
/**
*\*\name    Delay.
*\*\fun     Delay for a while.
*\*\return  none
**/
void Delay(__IO uint32_t nCount)
{
    for(; nCount != 0; nCount--);
}

