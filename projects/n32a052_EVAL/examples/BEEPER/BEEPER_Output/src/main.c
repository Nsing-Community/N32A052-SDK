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

/**
 *  BEEPER_Output
 */

/**
 * @brief  Main program.
 */
int main(void)
{
    /* log Init */
    log_init();
    log_info("BEEPER Output Test Start\r\n");
    /* BEEPER Output */
    SysTick_Delay_Ms(3000);
    /* Enable BEEPER Clock */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_BEEP, ENABLE);

		
    /* Config BEEPER output GPIO */
    BEEPER_GPIO_Config();

    /* Init BEEPER */
    BEEPER_FreqSelect(BEEPER_FREQ_1KHZ);

    /* Enable BEEPER and Select the mode*/
    BEEPER_Enable(ENABLE);

    log_info("BEEPER Output Test End\r\n");

    while (1)
    {
    }
}

/**
 * @brief  BEEPER_GPIO_Config.
 */
void BEEPER_GPIO_Config(void)
{
    GPIO_InitType GPIO_InitStructure;

    GPIO_InitStruct(&GPIO_InitStructure);
    
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);

    /* BEEPER out */
    GPIO_InitStructure.Pin             = GPIO_PIN_13;
    GPIO_InitStructure.GPIO_Mode       = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Alternate  = GPIO_AF7_BEEPER;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
}
