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



ADC_InitType ADC_InitStructure;
uint32_t ADCConvertedValue[5] = {0};   //note: Low half-word valid, High half-word reserved

void RCC_Configuration(void);
void GPIO_Configuration(void);
void TIM1_Config(void);
void NVIC_Configuration(void);
void DMA_Config(void);


/**
*\*\name    ADC_Initial.
*\*\fun     ADC_Initial program.
*\*\return  none
**/
void ADC_Initial(void)
{
    ADC_InitStruct(&ADC_InitStructure);
    ADC_DeInit();
    /* ADC configuration ------------------------------------------------------*/
    ADC_InitStructure.MultiChEn      = ENABLE;
    ADC_InitStructure.ContinueConvEn = DISABLE;
    ADC_InitStructure.ExtTrigSelect  = ADC_EXT_TRIGCONV_REGULAR_T1_CC1;
    ADC_InitStructure.DatAlign       = ADC_DAT_ALIGN_R;
    ADC_InitStructure.ChsNumber      = ADC_REGULAR_LEN_5;
    ADC_Init(&ADC_InitStructure);

    ADC_ConfigRegularSequenceMulti(ADC_Channel_00_PA0,ADC_DATA_OFFSET0);
    ADC_ConfigRegularSequenceMulti(ADC_Channel_01_PA1,ADC_DATA_OFFSET1);
    ADC_ConfigRegularSequenceMulti(ADC_Channel_02_PA2,ADC_DATA_OFFSET2);
    ADC_ConfigRegularSequenceMulti(ADC_Channel_03_PA3,ADC_DATA_OFFSET3);
    ADC_ConfigRegularSequenceMulti(ADC_Channel_04_PA4,ADC_DATA_OFFSET4);
    /* Configure channel sample time ----------------------*/
    ADC_ConfigChannelSampleTime(ADC_SAMP_TIME_14CYCLES);
    /* Enable ADC DMA */
    ADC_EnableDMA(ENABLE);
    /* Enable ADC */
    ADC_Enable(ENABLE);
    
    /* Check ADC Ready */
    while(ADC_GetFlagStatusNew(ADC_FLAG_RDY) == RESET)
        ;
}


/**
*\*\name    main.
*\*\fun     main program.
*\*\return  none
**/
int main(void)
{
    /* RCC  configuration ------------------------------------------------------*/
    RCC_Configuration();
    
    /* NVIC configuration ------------------------------------------------------*/
    NVIC_Configuration();

    /* GPIO configuration ------------------------------------------------------*/
    GPIO_Configuration();

    /* TIM1 configuration ------------------------------------------------------*/
    TIM1_Config();
    
    /* DMA configuration -------------------------------------------------------*/
    DMA_Config();
    
    /* ADC configuration -------------------------------------------------------*/
    ADC_Initial(); 
    
    /* TIM1 counter enable */
    TIM_Enable(TIM1, ENABLE);    
    
    /* Main Output Enable */
    TIM_EnableCtrlPwmOutputs(TIM1, ENABLE);  

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
    /* RCC_ADCHCLK_DIV1*/
    RCC_ConfigHclk(RCC_SYSCLK_DIV1);
    /* Enable GPIOA and TIM1 clocks */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_TIM1,ENABLE);
    /* Enable ADC and DMA clocks */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_ADC | RCC_AHB_PERIPH_DMA,ENABLE);
    ADC_ClockModeConfig(ADC_CKMOD_AHB,RCC_ADCHCLK_DIV16);
    /* enable ADC 1M clock */
    RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSI,RCC_ADC1MCLK_DIV8);
}

/**
*\*\name    GPIO_Configuration.
*\*\fun     Configures the different GPIO ports.
*\*\return  none
**/
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    GPIO_InitStruct(&GPIO_InitStructure);
    /* Configure PB1 PB2 PB10 PB11 PB12 as analog input -------------------------*/
    GPIO_InitStructure.Pin       = GPIO_PIN_0 | GPIO_PIN_1 |GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_ANALOG;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
}
/**
*\*\name    NVIC_Configuration.
*\*\fun     Configures NVIC and Vector Table base location.
*\*\return  none
**/
void NVIC_Configuration(void)
{
    NVIC_InitType NVIC_InitStructure;

    /* Configure and enable ADC interrupt */
    NVIC_InitStructure.NVIC_IRQChannel                   = DMA_CH1_2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority           = NVIC_PRIORITY_0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}
/**
*\*\name    TIM1_Config.
*\*\fun     Configures TIM1 .
*\*\return  none
**/
void TIM1_Config(void)
{
    TIM_TimeBaseInitType TIM_TimeBaseStructure;
    OCInitType TIM_OCInitStructure;
    
    /* TIM1 Configuration */
    TIM_InitTimBaseStruct(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.Period    = 10000-1;
    TIM_TimeBaseStructure.Prescaler = 64 - 1;
    TIM_TimeBaseStructure.ClkDiv    = 0x0;
    TIM_TimeBaseStructure.CounterMode   = TIM_CNT_MODE_UP;
    TIM_InitTimeBase(TIM1, &TIM_TimeBaseStructure);

    /* Channel 1 Configuration in PWM mode */
    TIM_OCInitStructure.OCMode       = TIM_OCMODE_PWM1;
    TIM_OCInitStructure.OutputState  = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.OutputNState = TIM_OUTPUT_NSTATE_ENABLE;
    TIM_OCInitStructure.Pulse        = 5000;
    TIM_OCInitStructure.OCPolarity   = TIM_OC_POLARITY_HIGH;
    TIM_OCInitStructure.OCNPolarity  = TIM_OCN_POLARITY_HIGH;
    TIM_OCInitStructure.OCIdleState  = TIM_OC_IDLE_STATE_SET;
    TIM_OCInitStructure.OCNIdleState = TIM_OC_IDLE_STATE_RESET;
    TIM_InitOc1(TIM1, &TIM_OCInitStructure);
}
/**
*\*\name    DMA_Config.
*\*\fun     DMA_Initial program.
*\*\return  none
**/
void DMA_Config(void)
{
    DMA_InitType DMA_InitStructure;
    DMA_DeInit(DMA_CH1);
    DMA_StructInit(&DMA_InitStructure);
    DMA_InitStructure.PeriphAddr     = (uint32_t)&ADC->DAT0;  
    DMA_InitStructure.MemAddr        = (uint32_t)ADCConvertedValue;
    DMA_InitStructure.Direction      = DMA_DIR_PERIPH_SRC;
    DMA_InitStructure.BufSize        = 5;
    DMA_InitStructure.PeriphInc      = DMA_PERIPH_INC_ENABLE;
    DMA_InitStructure.DMA_MemoryInc  = DMA_MEM_INC_ENABLE;
    DMA_InitStructure.PeriphDataSize = DMA_PERIPH_DATA_SIZE_WORD;
    DMA_InitStructure.MemDataSize    = DMA_MemoryDataSize_Word;
    DMA_InitStructure.CircularMode   = DMA_MODE_CIRCULAR;
    DMA_InitStructure.Priority       = DMA_PRIORITY_HIGH;
    DMA_InitStructure.Mem2Mem        = DMA_M2M_DISABLE;
    DMA_Init(DMA_CH1, &DMA_InitStructure);
    DMA_RequestRemap(DMA_REMAP_ADC,DMA,DMA_CH1,ENABLE);

    DMA_EnableChannel(DMA_CH1,ENABLE);
}

