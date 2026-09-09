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
#include "delay.h"

/** @addtogroup RTC_TAMPER
 * @{
 */
 
RTC_DateType RTC_DateStructure;
RTC_TimeType RTC_TimeStructure;
RTC_InitType RTC_InitStructure;
uint32_t SynchPrediv, AsynchPrediv;

ErrorStatus RTC_CLKSourceConfig(uint8_t ClkSrc, uint8_t FirstLastCfg);
static void RTC_PrescalerConfig(void);
void TAMPER_INT_Configuration(FunctionalState cmd);
void TamperInputIoInit(void);

#define RTC_CLOCK_TRY_COUNT            25
#define RTC_CLK_HSE128          1
#define RTC_CLK_HSI128          2
#define RTC_CLK_LSI             3

#define RTC_CLK_FIRST_CONFIG    0
#define RTC_CLK_LAST_CONFIG     1

/**
 * @brief  Display the current Date on the Hyperterminal.
 */
void RTC_DateShow(void)
{
    /* Get the current Date */
    RTC_GetDate(RTC_FORMAT_BIN, &RTC_DateStructure);
    log_info("\n\r //=========== Current Date Display ==============// \n\r");
    log_info("\n\r The current date (WeekDay-Date-Month-Year) is :  %0.2d-%0.2d-%0.2d-%0.2d \n\r",
             RTC_DateStructure.WeekDay,
             RTC_DateStructure.Date,
             RTC_DateStructure.Month,
             RTC_DateStructure.Year);
}

/**
 * @brief  Display the current time on the Hyperterminal.
 */
void RTC_TimeShow(void)
{
    /* Get the current Time and Date */
    RTC_GetTime(RTC_FORMAT_BIN, &RTC_TimeStructure);
    log_info("\n\r //============ Current Time Display ===============// \n\r");
    log_info("\n\r The current time (Hour-Minute-Second) is :  %0.2d:%0.2d:%0.2d \n\r",
             RTC_TimeStructure.Hours,
             RTC_TimeStructure.Minutes,
             RTC_TimeStructure.Seconds);
    /* Unfreeze the RTC DAT Register */
    (void)RTC->DATE;
}


/**
 * @brief  Main program.
 */
int main(void)
{
    /*!< At this stage the microcontroller clock setting is already configured,
         this is done through SystemInit() function which is called from startup
         file (startup_n32a052_xx.s) before to branch to application main.
         To reconfigure the default setting of SystemInit() function, refer to
         system_n32a052.c file
       */
    /* Initialize USART,TX: PA9*/
    log_init();
    log_info(" RTC Init");
    /* RTC clock source select 1:HSE/128 2:LSE 3:LSI*/
    if(SUCCESS == RTC_CLKSourceConfig(RTC_CLK_LSI, RTC_CLK_FIRST_CONFIG))
    {
        /* RTC prescaler initial value set*/
        RTC_PrescalerConfig();
        /*Tamper GPIO Initialize,PA0*/
        TamperInputIoInit();
        /*Configure Tamper GPIO trigger mode*/
        RTC_TamperTriggerConfig(RTC_TAMPER_2, RTC_TamperTrigger_RisingEdge);
        /*Configure the valib number of scanning times*/
        RTC_TamperFilterConfig(RTC_TamperFilter_Disable);
        /*Configure scanning frequence*/
        RTC_TamperSamplingFreqConfig(RTC_TamperSamplingFreq_RTCCLK_Div256);
        /*Configure precharge duration time*/
        RTC_TamperPinsPrechargeDuration(RTC_TamperPrechargeDuration_1RTCCLK);
        /*Configure tamper interruput,EXTI_LINE18*/
        TAMPER_INT_Configuration(ENABLE);
        /*Enable tamper interruput*/
        RTC_TamperIECmd(RTC_TAMPER2_INT, ENABLE);
        /*Enable tamper */
        RTC_TamperCmd(RTC_TAMPER_2, ENABLE);
    }
    else
    {
        log_info("\r\n RTC Init Failed\r\n");
    }
    while (1)
    {
    }
}

/**
 * @brief  Configure the tamper interruput,EXTI18.
 */
 void TAMPER_INT_Configuration(FunctionalState cmd)
{
    EXTI_InitType EXTI_InitStructure;
    NVIC_InitType NVIC_InitStructure;
    
    EXTI_ClrITPendBit(EXTI_LINE18);
    EXTI_InitStructure.EXTI_Line                          = EXTI_LINE18;
    EXTI_InitStructure.EXTI_Mode                          = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger                       = EXTI_Trigger_Rising; 

    EXTI_InitStructure.EXTI_LineCmd                       = ENABLE;
    EXTI_InitPeripheral(&EXTI_InitStructure);
    
    /* Enable the RTC Alarm Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel                    = RTC_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority  = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                 = cmd;
    NVIC_Init(&NVIC_InitStructure);
}

/**
 * @brief  Configures Tamper Input GPIO.
 */
void TamperInputIoInit(void)
{
    GPIO_InitType GPIO_InitStructure;

    GPIO_InitStruct(&GPIO_InitStructure);

    /* Enable the GPIO Clock */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_AFIO, ENABLE);

    /* Configure the tamper pin */
    GPIO_InitStructure.Pin              = GPIO_PIN_0;
    GPIO_InitStructure.GPIO_Mode        = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Alternate   = GPIO_AF7_RTC;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
}

/**
 * @brief  RTC prescaler config.
 */
static void RTC_PrescalerConfig(void)
{
    /* Configure the RTC data register and RTC prescaler */
    RTC_InitStructure.RTC_AsynchPrediv = AsynchPrediv;
    RTC_InitStructure.RTC_SynchPrediv  = SynchPrediv;
    RTC_InitStructure.RTC_HourFormat   = RTC_24HOUR_FORMAT;

    /* Check on RTC init */
    if (RTC_Init(&RTC_InitStructure) == ERROR)
    {
        log_info("\r\n //******* RTC Prescaler Config failed **********// \r\n");
    }
}

/**
*\*\name    RTC_CLKSource_Config.
*\*\fun     Configure the RTC peripheral by selecting the clock source.
*\*\param   ClkSrc    
*\*\            - RTC_CLK_HSE128    clock source select HSE/128
*\*\            - RTC_CLK_HSI128    clock source select HSI/128
*\*\            - RTC_CLK_LSI       clock source select LSI
*\*\param   FirstLastCfg
*\*\            - RTC_CLK_FIRST_CONFIG
*\*\            - RTC_CLK_LAST_CONFIG
*\*\return  SUCCESS or ERROR
**/
ErrorStatus RTC_CLKSourceConfig(uint8_t ClkSrc, uint8_t FirstLastCfg)
{
    ErrorStatus status=SUCCESS;
    uint16_t ready_count=0;
    
    /* Enable the PWR clock */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_PWR, ENABLE);
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);

    /* Disable RTC clock */
    RCC_EnableRtcClk(DISABLE);

    if (ClkSrc == RTC_CLK_HSE128)
    {
        log_info("\r\n RTC_ClkSrc Is Set HSE128! \r\n");
        if (FirstLastCfg == 0)
        {
            /* Enable HSE */
            RCC_EnableLsi(DISABLE);
            RCC_ConfigHse(RCC_HSE_ENABLE);
            if (RCC_WaitHseStable() == ERROR)
            {
                status = ERROR;
                log_info("\r\n RTC_ClkSrc Set HSE/128 Faile! \r\n");
            }

            RCC_ConfigRtcClk(RCC_RTCCLK_SRC_HSE_DIV128);
        }
        else
        {
            RCC_EnableLsi(DISABLE);
            RCC_ConfigRtcClk(RCC_RTCCLK_SRC_HSE_DIV128);

            /* Enable HSE */
            RCC_ConfigHse(RCC_HSE_ENABLE);

            if (RCC_WaitHseStable() == ERROR)
            {
                status = ERROR;
                log_info("\r\n RTC_ClkSrc Set HSE/128 Faile! \r\n");
            }
        }

        SynchPrediv  = 0x1E8; // 8M/128 = 62.5KHz
        AsynchPrediv = 0x7F;  // value range: 0-7F
    }
    else if (ClkSrc == RTC_CLK_HSI128)
    {
        log_info("\r\n RTC_ClkSrc Is Set HSI128! \r\n");
        if (FirstLastCfg == 0)
        {
            /* Enable HSI */
            RCC_EnableLsi(DISABLE);
            RCC_EnableHsi(ENABLE);
            if (RCC_WaitHsiStable() == ERROR)
            {
                status = ERROR;
                log_info("\r\n RTC_ClkSrc Set HSI/128 Faile! \r\n");
            }

            RCC_ConfigRtcClk(RCC_RTCCLK_SRC_HSI_DIV128);
        }
        else
        {
            RCC_EnableLsi(DISABLE);
            RCC_ConfigRtcClk(RCC_RTCCLK_SRC_HSI_DIV128);

            /* Enable HSI */
            RCC_EnableHsi(ENABLE);

            if (RCC_WaitHsiStable() == ERROR)
            {
                status = ERROR;
                log_info("\r\n RTC_ClkSrc Set HSI/128 Faile! \r\n");
            }
        }

        SynchPrediv  = 0x1E8; // 8M/128 = 62.5KHz
        AsynchPrediv = 0x7F;  // value range: 0-7F
    }
    else if (ClkSrc == RTC_CLK_LSI)
    {
        log_info("\r\n RTC_ClkSrc Is Set LSI! \r\n");
        if (FirstLastCfg == 0)
        {
            /* Enable the LSI OSC */
            RCC_EnableLsi(ENABLE);

            while (RCC_GetFlagStatus(RCC_LSCTRL_FLAG_LSIRDF) == RESET)
            {
                ready_count++;
                SysTick_Delay_Ms(10);
                if(ready_count >= RTC_CLOCK_TRY_COUNT)
                {
                    status = ERROR;
                    log_info("\r\n RTC_ClkSrc Set LSI Faile! \r\n");
                    break;
                }
            }

            RCC_ConfigRtcClk(RCC_RTCCLK_SRC_LSI);
        }
        else
        {
            RCC_ConfigRtcClk(RCC_RTCCLK_SRC_LSI);

            /* Enable the LSI OSC */
            RCC_EnableLsi(ENABLE);

            while (RCC_GetFlagStatus(RCC_LSCTRL_FLAG_LSIRDF) == RESET)
            {
                ready_count++;
                SysTick_Delay_Ms(10);
                if(ready_count >= RTC_CLOCK_TRY_COUNT)
                {
                    status = ERROR;
                    log_info("\r\n RTC_ClkSrc Set LSI Faile! \r\n");
                    break;
                }
            }
        }

        SynchPrediv  = 0xFF; // 32KHz
        AsynchPrediv = 0x7C;  // value range: 0-7F
    }
    else
    {
        log_info("\r\n RTC_ClkSrc Value is error! \r\n");
    }

    /* Enable the RTC Clock */
    RCC_EnableRtcClk(ENABLE);
    RTC_WaitForSynchro();
    /* Unfreeze the RTC DAT Register */
    (void)RTC->DATE;
    return status;
}
