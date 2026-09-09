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
 * @version v1.0.1
 *
 * @copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
 */
#include "main.h"
#include "delay.h"


/** @addtogroup n32a052_StdPeriph_Examples
 * @{
 */

/** @addtogroup WWDG_Reset
 * @{
 */

#define LED1_GPIO_PORT      GPIOB                       /* GPIO port */
#define LED1_GPIO_CLK       RCC_AHB_PERIPH_GPIOB        /* GPIO port clock */
#define LED1_GPIO_PIN       GPIO_PIN_0                  /* GPIO connected to the SCL clock line */

#define LED3_GPIO_PORT      GPIOD                       /* GPIO port */
#define LED3_GPIO_CLK       RCC_AHB_PERIPH_GPIOB        /* GPIO port clock */
#define LED3_GPIO_PIN       GPIO_PIN_11                  /* GPIO connected to the SCL clock line */


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
    else
    {
    
    }
    /* Configure the GPIO pin */
    GPIO_InitStruct(&GPIO_InitStructure);
    GPIO_InitStructure.Pin        = Pin;
    GPIO_InitStructure.GPIO_Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitPeripheral(GPIOx, &GPIO_InitStructure);
    // GPIOx->PBSC = Pin;
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
    log_info("--- WWDG demo reset ---\n");
    WWDG_ClrEWINTF();
    LedInit(LED1_GPIO_PORT, LED1_GPIO_PIN);
    LedInit(LED3_GPIO_PORT, LED3_GPIO_PIN);
    LedOff(LED1_GPIO_PORT, LED1_GPIO_PIN);
    LedOff(LED3_GPIO_PORT, LED3_GPIO_PIN);
   
    /* Enable PWR Clock */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_PWR, ENABLE);
    /* Check if the system has resumed from WWDG reset */
    if (RCC_GetFlagStatus(RCC_CTRLSTS_FLAG_WWDGRSTF) != RESET)
    {
        /* WWDGRST flag set */
        /* Turn on LED1 */
        LedOn(LED1_GPIO_PORT, LED1_GPIO_PIN);
        log_info("reset by WWDG\n");
        /* Clear reset flags */
        RCC_ClearResetFlag();
    }
    else
    {
        /* WWDGRST flag is not set */
        /* Turn off LED1 */
        LedOff(LED1_GPIO_PORT, LED1_GPIO_PIN);
    }
    /*
      When the window value is very small, the system is in a frequent reset state,
      at this time, easy to cause the program can not download normally.
      Add a delay of 1 second here to avoid this phenomenon. Of course,
      it can also be downloaded without delay, directly pull the pin of BOOT0 high.
    */
    SysTick_Delay_Ms(1000);
    
    /* WWDG configuration */
    /* Enable WWDG clock */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_WWDG, ENABLE);

    /* WWDG clock counter = 1/((PCLK1(32MHz)/4096)/8) = (~1024 us)  */
    WWDG_SetPrescalerDiv(WWDG_PRESCALER_DIV8);

    /* Set Window value to 80; WWDG counter should be refreshed only when the counter
      is below 80 (and greater than 64) otherwise a reset will be generated */
    WWDG_SetWValue(80);

    /*
      Enable WWDG and set counter value to 127, WWDG timeout = ~1024 us * 64 = 65.536 ms
      In this case the refresh window is: ~1024 us * (127-80) = 48.128 ms < refresh window < ~1024 us * (127-63) = 65.536ms
    */
    WWDG_Enable(127);

    while (1)
    {
        /* Toggle LED2 */
        LedBlink(LED3_GPIO_PORT, LED3_GPIO_PIN);
        SysTick_Delay_Ms(57);
        /* Update WWDG counter */
        WWDG_SetCnt(127);
    }
}

