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
#include "n32a052_tim.h"
#include "n32a052_pwr.h"
#include "delay.h"

/** @addtogroup n32a052_StdPeriph_Examples
 * @{
 */

/** @addtogroup
 * @{
 */

/** Define the GPIO port to which the LED is connected **/
#define LED1_GPIO_PORT      GPIOB                       /* GPIO port */
#define LED1_GPIO_CLK       RCC_AHB_PERIPH_GPIOB        /* GPIO port clock */
#define LED1_GPIO_PIN       GPIO_PIN_0                  /* GPIO connected to the SCL clock line */

#define LED3_GPIO_PORT      GPIOD                       /* GPIO port */
#define LED3_GPIO_CLK       RCC_AHB_PERIPH_GPIOC        /* GPIO port clock */
#define LED3_GPIO_PIN       GPIO_PIN_11                  /* GPIO connected to the SCL clock line */


__IO uint32_t LsiFreq = 32000;
extern uint16_t CaptureNumber;

void TIM2_ConfigForLSI(void);

/**
 * @brief  Configures LED GPIO.
 * @param Led Specifies the Led to be configured.
 *   This parameter can be GPIO_PIN_0~GPIO_PIN_15.
 */
void LedInit(GPIO_Module* GPIOx, uint16_t Pin)
{
    GPIO_InitType GPIO_InitStructure;

    /* Enable the GPIO Clock */
    if (GPIOx == GPIOA)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
    }
    else if (GPIOx == GPIOB)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
    }
    else if (GPIOx == GPIOC)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC, ENABLE);
    }
    else if (GPIOx == GPIOD)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOD, ENABLE);
    }

    /* Configure the GPIO pin */
    GPIO_InitStruct(&GPIO_InitStructure);
    GPIO_InitStructure.Pin        = Pin;
    GPIO_InitStructure.GPIO_Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitPeripheral(GPIOx, &GPIO_InitStructure);
}

/**
 * @brief  Turns selected Led on.
 * @param Led Specifies the Led to be set on.
 */
void LedOn(GPIO_Module* GPIOx, uint16_t Pin)
{
    GPIOx->PBSC = Pin;
}
/**
 * @brief  Turns selected Led Off.
 * @param Led Specifies the Led to be set off.
 */
void LedOff(GPIO_Module* GPIOx, uint16_t Pin)
{
    GPIOx->PBC = Pin;
}

/**
 * @brief  Toggles the selected Led.
 * @param Led Specifies the Led to be toggled.
 */
void LedBlink(GPIO_Module* GPIOx, uint16_t Pin)
{
    GPIOx->POD ^= Pin;
}

/**
 * @brief  Main program.
 */
int main(void)
{
    /*!< At this stage the microcontroller clock setting is already configured,
         this is done through SystemInit() function which is called from startup
         file (startup_n32a052.s) before to branch to application main.
         To reconfigure the default setting of SystemInit() function, refer to
         system_n32a052.c file
       */
    log_init();
    log_info("--- IWDG demo reset ---\n");
    LedInit(LED1_GPIO_PORT, LED1_GPIO_PIN);
    LedInit(LED3_GPIO_PORT, LED3_GPIO_PIN);
    LedOff(LED1_GPIO_PORT, LED1_GPIO_PIN);
    LedOff(LED3_GPIO_PORT, LED3_GPIO_PIN);
    
    /* Enable PWR Clock */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_PWR, ENABLE);

    /* Check if the system has resumed from IWDG reset */
    if(RCC_GetFlagStatus(RCC_CTRLSTS_FLAG_IWDGRSTF) != RESET)
    {
        /* IWDGRST flag set */
        /* Turn on LED1 */
        LedOn(LED1_GPIO_PORT, LED1_GPIO_PIN);
        log_info("reset by IWDG\n");
        /* Clear reset flags */
        RCC_ClearResetFlag();
    }
    else
    {
        /* IWDGRST flag is not set */
        /* Turn off LED1 */
        LedOff(LED1_GPIO_PORT, LED1_GPIO_PIN);
    }
    
#ifdef LSI_TIM_MEASURE
    /* Enable the LSI OSC */
    RCC_EnableLsi(ENABLE);

    /* Wait till LSI is ready */
    while (RCC_GetFlagStatus(RCC_LSCTRL_FLAG_LSIRDF) == RESET)
    {
        /* if LSI enable fail, User can add here some code to deal with this error */
    }
    /* TIM Configuration -------------------------------------------------------*/
    TIM2_ConfigForLSI();
    /* Wait until the TIM2 get 3 LSI edges */
    while (CaptureNumber != 3)
    {
    }
    /* Disable TIM2 CC3 Interrupt Request */
    TIM_ConfigInt(TIM2, TIM_INT_CC3, DISABLE);
#endif  /* LSI_TIM_MEASURE */

    /* IWDG timeout equal to 250 ms (the timeout may varies due to LSI frequency
       dispersion) */
    /* Enable write access to IWDG_PR and IWDG_RLR registers */
    IWDG_WriteConfig(IWDG_WRITE_ENABLE);

    /* IWDG counter clock: LSI/32 */
    IWDG_SetPrescalerDiv(IWDG_PRESCALER_DIV32);

    /* Set counter reload value to obtain 250ms IWDG TimeOut.
       Counter Reload Value = 250ms/IWDG counter clock period
                            = 250ms / (LSI/128)
                            = 0.25s / (LsiFreq/32)
                            = LsiFreq/(32 * 4)
                            = LsiFreq/128 */
    log_debug("LsiFreq is: %d\n", LsiFreq);

    IWDG_CntReload(LsiFreq / 128);
    /* Reload IWDG counter */
    IWDG_ReloadKey();

    /* Enable IWDG (the LSI oscillator will be enabled by hardware) */
    IWDG_Enable();

    while(1)
    {
        /* Toggle LED2 */
        LedBlink(LED3_GPIO_PORT, LED3_GPIO_PIN);
        /* Insert 249 ms delay */
        SysTick_Delay_Ms(249);

        /* Reload IWDG counter */
        IWDG_ReloadKey();
    }
}

#ifdef LSI_TIM_MEASURE
/**
 *\*\name   TIM2_ConfigForLSI.
 *\*\fun    Configures TIM2 to measure the LSI oscillator frequency.
 *\*\param  none.
 *\*\return none.
**/
void TIM2_ConfigForLSI(void)
{
    NVIC_InitType NVIC_InitStructure;
    TIM_ICInitType TIM_ICInitStructure;

    /* Enable TIM2 clocks */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_TIM2 | RCC_APB2_PERIPH_AFIO, ENABLE);

    /* Enable the TIM2 Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel          = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority  = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd       = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Configure TIM2 prescaler */    
    TIM_ConfigPrescaler(TIM2, 0, TIM_PSC_RELOAD_MODE_IMMEDIATE);
    
    /* TIM2 configuration: Input Capture mode 
    The LSI oscillator is connected to TIM2 CH3
    The Rising edge is used as active edge,
    The TIM2 CCDAT3 is used to compute the frequency value */
    TIM_ICInitStructure.Channel     = TIM_CH_3;
    TIM_ICInitStructure.ICPolarity  = TIM_IC_POLARITY_RISING;
    TIM_ICInitStructure.ICSelection = TIM_IC_SELECTION_DIRECTTI;
    TIM_ICInitStructure.ICPrescaler = TIM_IC_PSC_DIV8;
    TIM_ICInitStructure.ICFilter    = 0x0;
    TIM_ICInit(TIM2, &TIM_ICInitStructure);
                                       
    TIM2->CTRL1 |= TIM_CTRL1_C3SEL;
    /* TIM2 Counter Enable */
    TIM_Enable(TIM2, ENABLE);

    /* Reset the flags */
    TIM2->STS = 0;

    /* Enable the CC3 Interrupt Request */
    TIM_ConfigInt(TIM2, TIM_INT_CC3, ENABLE);
}
#endif  /* LSI_TIM_MEASURE */


