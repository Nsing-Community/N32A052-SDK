/*****************************************************************************
 * Copyright (c) 2023, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file main.c
 * @author Nations 
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
 */
#include "main.h"
#include "n32a052_rcc.h"
#include "n32a052_adc.h"


ADC_InitType ADC_InitStructure;
__IO uint16_t ADCConvertedValue;

void RCC_Configuration(void);
void GPIO_Configuration(void);
uint16_t Get_Data(void);

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
    ADC_InitStructure.MultiChEn      = DISABLE;
    ADC_InitStructure.ContinueConvEn = ENABLE;
    ADC_InitStructure.ExtTrigSelect  = ADC_EXT_TRIGCONV_REGULAR_SWSTRRCH;
    ADC_InitStructure.DatAlign       = ADC_DAT_ALIGN_R;
    ADC_InitStructure.ChsNumber      = ADC_REGULAR_LEN_1;
    ADC_Init(&ADC_InitStructure);
    
    /* ADC enable Vrefint  */
    ADC_EnableInternalInputBuffer(ENABLE);
    /*ADC_ConfigRegularSequenceSingle  ADC_CH_VREFINT */
    ADC_ConfigRegularSequenceSingle(ADC_CH_VREFINT);
    /* Configure channel sample time ----------------------*/
    ADC_ConfigChannelSampleTime(ADC_SAMP_TIME_380CYCLES);
    
    /* Enable ADC */
    ADC_Enable(ENABLE);
    /* Check ADC Ready */
    while(ADC_GetFlagStatusNew(ADC_FLAG_RDY) == RESET)
        ;
    /*wait ADC Vrefint is ready to use*/
    while(!ADC_GetFlagStatusNew(ADC_FLAG_BUF_RDY))
        ;
    /* Start ADC Software Conversion */
    ADC_EnableSoftwareStartConv(ENABLE);
}


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

    /* ADC configuration ------------------------------------------------------*/
    ADC_Initial(); 

    while (1)
    {
        ADCConvertedValue = Get_Data();
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
    /* Enable GPIOA clocks */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA,ENABLE);
    /* Enable ADC clocks */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_ADC,ENABLE);
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
    /* Configure PA0,PA1 as analog input -------------------------*/
    GPIO_InitStructure.Pin       = GPIO_PIN_0 | GPIO_PIN_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_ANALOG;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
}

/**
*\*\name    Get_Data.
*\*\fun     Get ADC conversion results.
*\*\return  ADC conversion results
**/
uint16_t Get_Data(void)
{

    uint16_t data = 0;

    /* wait end of conversion flag-------------------------*/
    while(ADC_GetFlagStatus(ADC_FLAG_ENDCA)==0){
    }
    ADC_ClearFlag(ADC_FLAG_ENDCA);
    ADC_ClearFlag(ADC_FLAG_STR);
    data= ADC_GetDat();
    return data;
}
