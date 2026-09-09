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


TIM_TimeBaseInitType TIM_TimeBaseStructure;
OCInitType TIM_OCInitStructure;
TIM_BDTRInitType TIM_BDTRInitStructure;
uint16_t TimerPeriod   = 0;
uint16_t Channel1Pulse = 0,Channel2Pulse = 0,Channel3Pulse = 0;

void RCC_Configuration(void);
void GPIO_Configuration(void);
void COMP_Configuratoin(void);
void TIM_Intial(TIM_Module* TIMx);
void ChangeVmVp(void);
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

    /* TIM1 configuration -------------------------------------------------------*/
    TIM_Intial(TIM1);
    
    /* COMP configuration -------------------------------------------------------*/
    COMP_Configuratoin();
    
    while (1)
    {
        ChangeVmVp();
    }
}
/**
*\*\name    ChangeVmVp.
*\*\fun     Self Generate Puls ,by skip line connect to vp and vm if need.
*\*\return  none
**/
void ChangeVmVp(void)
{
    GPIO_SetBits(GPIOB, GPIO_PIN_3);
    GPIO_ResetBits(GPIOB, GPIO_PIN_4);
    {
        uint32_t i = 0;
        while (i++ < 10000)
            ;
    }
    GPIO_ResetBits(GPIOB, GPIO_PIN_3);
    GPIO_SetBits(GPIOB, GPIO_PIN_4);
    {
        uint32_t i = 0;
        while (i++ < 10000)
            ;
    }
}

/**
*\*\name    RCC_Configuration.
*\*\fun     Configures the different system clocks.
*\*\return  none
**/
void RCC_Configuration(void)
{
    /* Enable GPIOA,GPIOB,GPIOC,TIM1 clocks */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_GPIOB |RCC_APB2_PERIPH_GPIOC | RCC_APB2_PERIPH_TIM1 | RCC_APB2_PERIPH_AFIO,ENABLE);
    /* Enable COMP clocks */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_COMP | RCC_APB1_PERIPH_COMPFILT,ENABLE);
}

/**
*\*\name    GPIO_Configuration.
*\*\fun     Configures the different GPIO ports.
*\*\return  none
**/
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    /*COMP INP, INM*/ 
    GPIO_InitStruct(&GPIO_InitStructure);
    GPIO_InitStructure.Pin       = GPIO_PIN_3 | GPIO_PIN_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_ANALOG;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
    /*OUT*/
    GPIO_InitStructure.Pin       = GPIO_PIN_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF8_COMP1;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
    
    /*PC10 PC15 as analog*/ 
    GPIO_InitStruct(&GPIO_InitStructure);
    GPIO_InitStructure.Pin       = GPIO_PIN_10 | GPIO_PIN_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_ANALOG;
    GPIO_InitPeripheral(GPIOC, &GPIO_InitStructure);
    
    /*PA6 */ 
    GPIO_InitStruct(&GPIO_InitStructure);
    GPIO_InitStructure.Pin       = GPIO_PIN_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_ANALOG;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
    
    /*PB1,P2 as connect to INP,INM by external skip line*/
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pin       = GPIO_PIN_3|GPIO_PIN_4;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
    
    /*PA4,PA6 PA11 as TIM1_CH1\CH2\CH3 output  */
    GPIO_InitStructure.Pin       = GPIO_PIN_4 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF2_TIM1;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
    
    GPIO_InitStructure.Pin       = GPIO_PIN_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF1_TIM1;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
    
    GPIO_InitStructure.Pin       = GPIO_PIN_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF5_TIM1;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
}

/**
*\*\name    COMP_Configuratoin.
*\*\fun     Configures the comp module.
*\*\return  none
**/
void COMP_Configuratoin(void)
{
    COMP_InitType COMP_Initial;

    /*Initial comp*/
    COMP_StructInit(&COMP_Initial);
    COMP_Initial.InpSel     = COMP1_INPSEL_PA3;
    COMP_Initial.InmSel     = COMP1_INMSEL_PA2;
    COMP_Initial.SampWindow = 18;       //(0~31)
    COMP_Initial.Threshold  = 12;       //Thresh should be greater than half of SampWindow and should be less than SampWindow at the same time.
    COMP_Initial.Blking     = COMP_CTRL_BLKING_NO;
    COMP_Initial.Hyst       = COMP_CTRL_HYST_NO;
    COMP_Init(COMP1, &COMP_Initial);

    /*trig initial as tim1 break*/
    COMP_SetOutTrig(COMP1, COMP1_CTRL_OUTSEL_T1_BKIN);
    
    COMP_OutTimEn(CMP1_TIM_EN,ENABLE);
    /*enable comp1*/
    COMP_Enable(COMP1,ENABLE);
}

/**
*\*\name    TIM_Intial.
*\*\fun     Configures timx program.
*\*\return  none
**/
void TIM_Intial(TIM_Module* TIMx)
{  
    /* 
    TIMx Configuration to:

    1/ Generate 3 complementary PWM signals with 3 different duty cycles:
    TIMxCLK is fixed to SystemCoreClock, the TIMx Prescaler is equal to 0 so the
    TIMx counter clock used is SystemCoreClock.

    The objective is to generate PWM signal at x Hz:
    - TIMx_Period = (SystemCoreClock / x) - 1

    The Three Duty cycles are computed as the following description:

    The channel 1 duty cycle is set to 50% .
    The channel 2 duty cycle is set to 25% .
    The channel 3 duty cycle is set to 12.5% .
    The Timer pulse is calculated as follows:
      - ChannelxPulse = DutyCycle * (TIMx_Period - 1) / 100

    2/ Insert a dead time equal to 11/SystemCoreClock ns
    3/ Configure the break feature, active at High level, and using the automatic
     output enable feature
    4/ Use the Locking parameters level1.
    */
    
    /* Compute the value to be set in AR register to generate signal frequency at x hz */
    TimerPeriod = (SystemCoreClock / 17570) - 1;
    /* Compute CCDAT1 value to generate a duty cycle at 50% for channel 1 */
    Channel1Pulse = (uint16_t)(((uint32_t)5 * (TimerPeriod - 1)) / 10);
    /* Compute CCDAT2 value to generate a duty cycle at 25%  for channel 2 */
    Channel2Pulse = (uint16_t)(((uint32_t)25 * (TimerPeriod - 1)) / 100);
    /* Compute CCDAT3 value to generate a duty cycle at 12.5%  for channel 3 */
    Channel3Pulse = (uint16_t)(((uint32_t)125 * (TimerPeriod - 1)) / 1000);   

    /* Time Base configuration */
    TIM_InitTimBaseStruct(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.Prescaler = 0;
    TIM_TimeBaseStructure.CounterMode   = TIM_CNT_MODE_UP;
    TIM_TimeBaseStructure.Period    = TimerPeriod;
    TIM_TimeBaseStructure.ClkDiv    = TIM_CLK_DIV1;
    TIM_TimeBaseStructure.RepetCnt  = 0;

    TIM_InitTimeBase(TIMx, &TIM_TimeBaseStructure);

    /* Channel 1, 2,3 Configuration in PWM mode */
    TIM_InitOcStruct(&TIM_OCInitStructure);    
    TIM_OCInitStructure.OCMode       = TIM_OCMODE_PWM2;
    TIM_OCInitStructure.OutputState  = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.OutputNState = TIM_OUTPUT_NSTATE_ENABLE;
    TIM_OCInitStructure.Pulse        = Channel1Pulse;
    TIM_OCInitStructure.OCPolarity   = TIM_OC_POLARITY_LOW;
    TIM_OCInitStructure.OCNPolarity  = TIM_OCN_POLARITY_LOW;
    TIM_OCInitStructure.OCIdleState  = TIM_OC_IDLE_STATE_SET;
    TIM_OCInitStructure.OCNIdleState = TIM_OCN_IDLE_STATE_RESET;
    TIM_InitOc1(TIMx, &TIM_OCInitStructure);
    
    TIM_OCInitStructure.Pulse = Channel2Pulse;
    TIM_InitOc2(TIMx, &TIM_OCInitStructure);

    TIM_OCInitStructure.Pulse = Channel3Pulse;
    TIM_InitOc3(TIMx, &TIM_OCInitStructure);

    /* TIMx break */
    TIM_InitBkdtStruct(&TIM_BDTRInitStructure);
    TIM_BDTRInitStructure.OSSRState       = TIM_OSSR_STATE_ENABLE;
    TIM_BDTRInitStructure.OSSIState       = TIM_OSSI_STATE_ENABLE;
    TIM_BDTRInitStructure.LOCKLevel       = TIM_LOCK_LEVEL_OFF;
    TIM_BDTRInitStructure.DeadTime        = 11;
    TIM_BDTRInitStructure.Break           = TIM_BREAK_IN_ENABLE;
    TIM_BDTRInitStructure.BreakPolarity   = TIM_BREAK_POLARITY_HIGH;
    TIM_BDTRInitStructure.AutomaticOutput = TIM_AUTO_OUTPUT_ENABLE;
    TIM_BDTRInitStructure.IOMBreak      = TIM_BREAK_PVD_DISABLE;
    TIM_BDTRInitStructure.LOCKUPBreak   = TIM_BREAK_PVD_DISABLE;
    TIM_BDTRInitStructure.PVDBreak      = TIM_BREAK_PVD_DISABLE;
    TIM_BDTRInitStructure.COMPBreak     = TIM_BREAK_COMP_ENABLE ;
    TIM_ConfigBkdt(TIMx, &TIM_BDTRInitStructure);

    /* TIMx counter enable */
    TIM_Enable(TIMx,ENABLE);

    /* TIMx Main Output Enable */
    TIM_EnableCtrlPwmOutputs(TIMx,ENABLE);
}

