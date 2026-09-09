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
void DAC_ChannelConfig(void);
void TIM4_Config(void);

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

    /* TIM4 configuration -------------------------------------------------------*/
    TIM4_Config();

    /* DAC configuration -------------------------------------------------------*/
    DAC_ChannelConfig(); 

    /* TIM4 enable counter */
    TIM_Enable(TIM4, ENABLE);
    while (1)
    {
    }
}

/**
*\*\name    RCC_Configuration.
*\*\fun     Configures the different system clocks.
*\*\return  none
**/
void RCC_Configuration(void)
{
    /* Enable GPIOB TIM4 clocks */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB|RCC_APB2_PERIPH_TIM4,ENABLE);
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

    /* Once the DAC channel is enabled, the corresponding GPIO pin is automatically
       connected to the DAC converter. In order to avoid parasitic consumption,
       the GPIO pin should be configured in analog */
    GPIO_InitStruct(&GPIO_InitStructure);
    GPIO_InitStructure.Pin       = GPIO_PIN_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_ANALOG;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
}

/**
*\*\name    DAC_ChannelConfig.
*\*\fun     Configures the DAC config.
*\*\return  none
**/

void DAC_ChannelConfig(void)
{
    DAC_InitType DAC_InitStructure;

    /* DAC channel1 Configuration */
    DAC_InitStructure.TriggerSelect    = DAC_TRIGGER_TIM4_TRGO;
    DAC_InitStructure.WaveGeneration   = DAC_WAVEGEN_TRIANGLE;
    DAC_InitStructure.LfsrUnMaskTriAmp = DAC_TRIANGLE_AMP_2047;
    DAC_InitStructure.OutputBuffer     = DAC_OUTPUT_BUF_ENABLE;
    DAC_InitStructure.OutputHighDriver = DAC_OUTPUT_HIGH_DRIVER_DISABLE;
    DAC_Init(&DAC_InitStructure);

    /* Enable DAC Channel1: Once the DAC channel is enabled, PB13 is
       automatically connected to the DAC converter. */
    DAC_Enable(ENABLE);

    /* Set DAC Channel1 DHR12L register */
    DAC_SetChData(DAC_ALIGN_R_12BIT, 0x000);
}
/**
*\*\name    TIM4_Config.
*\*\fun     Configures TIM4 .
*\*\return  none
**/
void TIM4_Config(void)
{
    TIM_TimeBaseInitType TIM_TimeBaseStructure;
    
    /* TIM4 Configuration */
    TIM_InitTimBaseStruct(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.Period    = 0xF;
    TIM_TimeBaseStructure.Prescaler = 0xF;
    TIM_TimeBaseStructure.ClkDiv    = 0x0;
    TIM_TimeBaseStructure.CounterMode  = TIM_CNT_MODE_UP;
    TIM_InitTimeBase(TIM4, &TIM_TimeBaseStructure);

    /* TIM4 TRGO selection */
    TIM_SelectOutputTrig(TIM4, TIM_TRGO_SRC_UPDATE);
}

