/**
*     Copyright (c) 2022, Nations Technologies Inc.
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
#include "main.h"

TIM_TimeBaseInitType TIM_TimeBaseStructure;
OCInitType TIM_OCInitStructure;
uint16_t SRC_Buffer[3] = {0, 0, 0};
uint16_t TimerPeriod   = 0;


/**
*\*\name    main.
*\*\fun     main program.
*\*\param   none
*\*\return  none 
**/
int main(void)
{
    /* System Clocks Configuration */
    RCC_Configuration();

    /* GPIO Configuration */
    GPIO_Configuration();

    /* DMA Configuration */
    DMA_Configuration();

    /* TIM1 DMA Transfer example -------------------------------------------------
    TIM1CLK = SystemCoreClock, Prescaler = 0, TIM1 counter clock = SystemCoreClock
    SystemCoreClock is set to 48 MHz.

    The objective is to configure TIM1 channel 3 to generate complementary PWM
    signal with a frequency equal to x Hz:
     - TIM1_Period = (SystemCoreClock / x) - 1
    and a variable duty cycle that is changed by the DMA after a specific number of
    Update DMA request.

    The number of this repetitive requests is defined by the TIM1 Repetition counter,
    each 3 Update Requests, the TIM1 Channel 3 Duty Cycle changes to the next new
    value defined by the SRC_Buffer .
    -----------------------------------------------------------------------------*/
    /* Compute the value to be set in AR register to generate signal frequency at x hz */
    TimerPeriod = (SystemCoreClock / 17570) - 1;
    /* Compute CCDAT1 value to generate a duty cycle at 50% */
    SRC_Buffer[0] = (uint16_t)(((uint32_t)5 * (TimerPeriod - 1)) / 10);
    /* Compute CCDAT1 value to generate a duty cycle at 37.5% */
    SRC_Buffer[1] = (uint16_t)(((uint32_t)375 * (TimerPeriod - 1)) / 1000);
    /* Compute CCDAT1 value to generate a duty cycle at 25% */
    SRC_Buffer[2] = (uint16_t)(((uint32_t)25 * (TimerPeriod - 1)) / 100);

    /* TIM1 Peripheral Configuration --------------------------------------------*/
    /* Time Base configuration */
    TIM_InitTimBaseStruct(&TIM_TimeBaseStructure);    
    TIM_TimeBaseStructure.Prescaler     = 0;
    TIM_TimeBaseStructure.CounterMode   = TIM_CNT_MODE_UP;
    TIM_TimeBaseStructure.Period        = TimerPeriod;
    TIM_TimeBaseStructure.ClkDiv        = TIM_CLK_DIV1;
    TIM_TimeBaseStructure.RepetCnt      = 5;

    TIM_InitTimeBase(TIM1, &TIM_TimeBaseStructure);

    /* Channel 3 Configuration in PWM mode */
    TIM_InitOcStruct(&TIM_OCInitStructure);    
    TIM_OCInitStructure.OCMode       = TIM_OCMODE_PWM2;
    TIM_OCInitStructure.OutputState  = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.OutputNState = TIM_OUTPUT_NSTATE_ENABLE;
    TIM_OCInitStructure.Pulse        = SRC_Buffer[0];
    TIM_OCInitStructure.OCPolarity   = TIM_OC_POLARITY_LOW;
    TIM_OCInitStructure.OCNPolarity  = TIM_OCN_POLARITY_LOW;
    TIM_OCInitStructure.OCIdleState  = TIM_OC_IDLE_STATE_SET;
    TIM_OCInitStructure.OCNIdleState = TIM_OC_IDLE_STATE_RESET;

    TIM_InitOc3(TIM1, &TIM_OCInitStructure);

    /* TIM1 Update DMA Request enable */
    TIM_EnableDma(TIM1, TIM_DMA_UPDATE, ENABLE);

    /* TIM1 counter enable */
    TIM_Enable(TIM1, ENABLE);

    /* Main Output Enable */
    TIM_EnableCtrlPwmOutputs(TIM1, ENABLE);
    
    while (1);
}

/**
*\*\name    RCC_Configuration.
*\*\fun     Configures the different system clocks.
*\*\param   none
*\*\return  none 
**/
void RCC_Configuration(void)
{
    /* TIMx, GPIOx and AFIO clocks enable */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_TIM1 | RCC_APB2_PERIPH_GPIOA | 
                            RCC_APB2_PERIPH_AFIO,ENABLE);
    /* DMA clock enable */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_DMA, ENABLE);
}

/**
*\*\name    GPIO_Configuration.
*\*\fun     Configures the GPIO pins.
*\*\param   none
*\*\return  none 
**/
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    GPIO_InitStruct(&GPIO_InitStructure);
    /* GPIOx Configuration: Pin of TIMx */
    GPIO_InitStructure.Pin        = GPIO_PIN_11 ;
    GPIO_InitStructure.GPIO_Mode  = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Slew_Rate = GPIO_SLEW_RATE_SLOW;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF5_TIM1;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);

    /* GPIOx Configuration: Pin of TIMx */
    GPIO_InitStructure.Pin = GPIO_PIN_4;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF3_TIM1;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
    
}

/**
*\*\name    DMA_Configuration.
*\*\fun     Configures the GPIO pins.
*\*\param   none
*\*\return  none 
**/
void DMA_Configuration(void)
{
    DMA_InitType DMA_InitStructure;

    /* DMA Channel5 Config */
    DMA_DeInit(DMA_CH5);
    DMA_StructInit(&DMA_InitStructure);
    DMA_InitStructure.PeriphAddr     = (uint32_t)&TIM1->CCDAT3;
    DMA_InitStructure.MemAddr        = (uint32_t)SRC_Buffer;
    DMA_InitStructure.Direction      = DMA_DIR_PERIPH_DST;
    DMA_InitStructure.BufSize        = 3;
    DMA_InitStructure.PeriphInc      = DMA_PERIPH_INC_DISABLE;
    DMA_InitStructure.DMA_MemoryInc  = DMA_MEM_INC_ENABLE;
    DMA_InitStructure.PeriphDataSize = DMA_PERIPH_DATA_SIZE_HALFWORD;
    DMA_InitStructure.MemDataSize    = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.CircularMode   = DMA_MODE_CIRCULAR;
    DMA_InitStructure.Priority       = DMA_PRIORITY_HIGH;
    DMA_InitStructure.Mem2Mem        = DMA_M2M_DISABLE;

    DMA_Init(DMA_CH5, &DMA_InitStructure);
    DMA_RequestRemap(DMA_REMAP_TIM1_UP, DMA, DMA_CH5, ENABLE);
    /* DMA Channel5 enable */
    DMA_EnableChannel(DMA_CH5, ENABLE);
}

