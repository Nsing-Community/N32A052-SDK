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
#include "delay.h"


/**
*\*\name    main.
*\*\fun     main program.
*\*\param   none
*\*\return  none 
**/
int main(void)
{
    TIM_PWM();    
    /* Init the peripheral */
    BSP_LCD_GLASS_Init(); // Initialize glass LCD.
    
    while (1)   /* Test loop */
    {
        /*Show all char and mark on LCD*/
        BSP_LCD_GLASS_ShowAll();
        SysTick_Delay_Ms(2000);
        
        LCD_Write(LCD_RAM1_COM0, 0x00000000, 0x1);
        LCD_UpdateDisplayRequest();
        SysTick_Delay_Ms(2000);
        
        LCD_Write(LCD_RAM1_COM0, 0x00000000, 0x20);
        LCD_UpdateDisplayRequest();
        SysTick_Delay_Ms(2000);
        
        /*Clear all*/
        BSP_LCD_GLASS_Clear();
        SysTick_Delay_Ms(2000);
    }
}


void TIM_PWM(void)
{
    uint32_t TimerPeriod,Channel2Pulse;
    GPIO_InitType GPIO_InitStructure;
    TIM_TimeBaseInitType TIM_TimeBaseStructure;
    OCInitType TIM_OCInitStructure;

    GPIO_InitStruct(&GPIO_InitStructure);
    /* TIMx, GPIOx and AFIO clocks enable */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_TIM1 | RCC_APB2_PERIPH_GPIOD |  RCC_APB2_PERIPH_AFIO,ENABLE);
    /* GPIOx Configuration: Pin of TIMx */
    GPIO_InitStructure.Pin        = GPIO_PIN_6;
    GPIO_InitStructure.GPIO_Mode  = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Current = GPIO_HIGH_DREIVE;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF2_TIM1;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
    
    GPIO_InitStructure.Pin        = GPIO_PIN_4;
    GPIO_InitStructure.GPIO_Mode  = GPIO_MODE_ANALOG;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
    
    /* Compute the value to be set in AR regiter to generate signal frequency at x Hz */
    TimerPeriod = (SystemCoreClock / 1000 ) - 1;
    /* Compute CCDAT3 value to generate a duty cycle at 25%  for channel 3 and 3N */
    Channel2Pulse = (uint16_t)(((uint32_t)30 * (TimerPeriod - 1)) / 100); 
    
    /* Time Base configuration */
    TIM_InitTimBaseStruct(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.Prescaler     = 0;
    TIM_TimeBaseStructure.CounterMode   = TIM_CNT_MODE_UP;
    TIM_TimeBaseStructure.Period        = TimerPeriod;
    TIM_TimeBaseStructure.ClkDiv        = TIM_CLK_DIV1;
    TIM_TimeBaseStructure.RepetCnt      = 0;
    TIM_InitTimeBase(TIM1, &TIM_TimeBaseStructure);
    
    /* Channel 1, 2 Configuration in PWM mode */
    TIM_InitOcStruct(&TIM_OCInitStructure);
    TIM_OCInitStructure.OCMode       = TIM_OCMODE_PWM1;
    TIM_OCInitStructure.OutputState  = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.Pulse        = Channel2Pulse;
    TIM_OCInitStructure.OCPolarity   = TIM_OC_POLARITY_HIGH;
    TIM_OCInitStructure.OCIdleState  = TIM_OC_IDLE_STATE_SET;
    TIM_InitOc3(TIM1, &TIM_OCInitStructure);
    
    /* TIM1 counter enable */
    TIM_Enable(TIM1, ENABLE);    
    
    /* Main Output Enable */
    TIM_EnableCtrlPwmOutputs(TIM1, ENABLE); 
}

