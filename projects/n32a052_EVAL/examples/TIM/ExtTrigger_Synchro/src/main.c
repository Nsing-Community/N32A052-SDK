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
TIM_ICInitType TIM_ICInitStructure;

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
    
    /* 
    Timers synchronisation in cascade mode with an external trigger 
    1/TIM1 is configured as Master Timer:
     - Toggle Mode is used
     - The TIM1 Enable event is used as Trigger Output

    2/TIM1 is configured as Slave Timer for an external Trigger connected
     to TIM1 TI2 pin (TIM1 CH2 configured as input pin):
     - The TIM1 TI2FP2 is used as Trigger Input
     - Rising edge is used to start and stop the TIM1: Gated Mode.

    3/TIM3 is slave for TIM1 and Master for TIM4,
     - Toggle Mode is used
     - The ITR1(TIM1) is used as input trigger
     - Gated mode is used, so start and stop of slave counter
       are controlled by the Master trigger output signal(TIM1 enable event).
     - The TIM3 enable event is used as Trigger Output.

    4/TIM4 is slave for TIM3,
     - Toggle Mode is used
     - The ITR2(TIM3) is used as input trigger
     - Gated mode is used, so start and stop of slave counter
       are controlled by the Master trigger output signal(TIM3 enable event).

    The starts and stops of the TIM1 counters are controlled by the
    external trigger.
    The TIM3 starts and stops are controlled by the TIM1, and the TIM4
    starts and stops are controlled by the TIM3.
    */
    
    /* Time base configuration */
    TIM_InitTimBaseStruct(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.Period    = 73;
    TIM_TimeBaseStructure.Prescaler = 2;
    TIM_TimeBaseStructure.ClkDiv    = TIM_CLK_DIV1;
    TIM_TimeBaseStructure.CounterMode   = TIM_CNT_MODE_UP;

    TIM_InitTimeBase(TIM1, &TIM_TimeBaseStructure);

    TIM_TimeBaseStructure.Period = 73;
    TIM_InitTimeBase(TIM3, &TIM_TimeBaseStructure);

    TIM_TimeBaseStructure.Period = 73;
    TIM_InitTimeBase(TIM4, &TIM_TimeBaseStructure);

    /* Master Configuration in Toggle Mode */
    TIM_InitOcStruct(&TIM_OCInitStructure);
    TIM_OCInitStructure.OCMode      = TIM_OCMODE_TOGGLE;
    TIM_OCInitStructure.OutputState = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.Pulse       = 64;
    TIM_OCInitStructure.OCPolarity  = TIM_OC_POLARITY_HIGH;

    TIM_InitOc1(TIM1, &TIM_OCInitStructure);
    
    /* TIM1 Input Capture Configuration */
    TIM_InitIcStruct(&TIM_ICInitStructure);
    TIM_ICInitStructure.Channel     = TIM_CH_2;
    TIM_ICInitStructure.ICPolarity  = TIM_IC_POLARITY_RISING;
    TIM_ICInitStructure.ICSelection = TIM_IC_SELECTION_DIRECTTI;
    TIM_ICInitStructure.ICPrescaler = TIM_IC_PSC_DIV1;
    TIM_ICInitStructure.ICFilter    = 0;

    TIM_ICInit(TIM1, &TIM_ICInitStructure);    
    
    /* TIM1 Input trigger configuration: External Trigger connected to TI2 */
    TIM_SelectInputTrig(TIM1, TIM_TRIG_SEL_TI2FP2);
    TIM_SelectSlaveMode(TIM1, TIM_SLAVE_MODE_GATED);

    /* Select the Master Slave Mode */
    TIM_SelectMasterSlaveMode(TIM1, TIM_MASTER_SLAVE_MODE_ENABLE);

    /* Master Mode selection: TIM1 */
    TIM_SelectOutputTrig(TIM1, TIM_TRGO_SRC_ENABLE);

    /* Slaves Configuration: Toggle Mode */
    TIM_OCInitStructure.OCMode      = TIM_OCMODE_TOGGLE;
    TIM_OCInitStructure.OutputState = TIM_OUTPUT_STATE_ENABLE;

    TIM_InitOc1(TIM3, &TIM_OCInitStructure);

    TIM_InitOc1(TIM4, &TIM_OCInitStructure);

    /* Slave Mode selection: TIM3 */
    TIM_SelectInputTrig(TIM3, TIM_TRIG_SEL_IN_TR0);
    TIM_SelectSlaveMode(TIM3, TIM_SLAVE_MODE_GATED);

    /* Select the Master Slave Mode */
    TIM_SelectMasterSlaveMode(TIM3, TIM_MASTER_SLAVE_MODE_ENABLE);

    /* Master Mode selection: TIM3 */
    TIM_SelectOutputTrig(TIM3, TIM_TRGO_SRC_ENABLE);

    /* Slave Mode selection: TIM4 */
    TIM_SelectInputTrig(TIM4, TIM_TRIG_SEL_IN_TR2);
    TIM_SelectSlaveMode(TIM4, TIM_SLAVE_MODE_GATED);

    /* TIM1 Main Output Enable */
    TIM_EnableCtrlPwmOutputs(TIM1, ENABLE);

    /* TIM enable counter */
    TIM_Enable(TIM1, ENABLE);
    TIM_Enable(TIM3, ENABLE);
    TIM_Enable(TIM4, ENABLE);   


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
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_TIM1 | RCC_APB2_PERIPH_TIM3 | 
                            RCC_APB2_PERIPH_TIM4 |  RCC_APB2_PERIPH_GPIOA | 
                            RCC_APB2_PERIPH_GPIOC | RCC_APB2_PERIPH_AFIO,ENABLE);
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
    GPIO_InitStructure.Pin        = GPIO_PIN_9;
    GPIO_InitStructure.GPIO_Mode  = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Slew_Rate = GPIO_SLEW_RATE_SLOW;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF2_TIM1;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
    
    /* GPIOx Configuration: Pin of TIMx */
    GPIO_InitStructure.Pin        = GPIO_PIN_6;
    GPIO_InitStructure.GPIO_Mode  = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Slew_Rate = GPIO_SLEW_RATE_SLOW;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF2_TIM1;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);    
    
    /* GPIOx Configuration: Pin of TIMx */
    GPIO_InitStructure.Pin        = GPIO_PIN_6;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF2_TIM3;
    GPIO_InitPeripheral(GPIOC, &GPIO_InitStructure);
    
    /* GPIOx Configuration: Pin of TIMx */
    GPIO_InitStructure.Pin        = GPIO_PIN_10;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF3_TIM4;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
    
}


