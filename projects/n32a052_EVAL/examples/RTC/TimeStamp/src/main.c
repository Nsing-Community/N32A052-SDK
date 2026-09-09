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

/** @addtogroup RTC_Calendar
 * @{
 */
RTC_DateType RTC_DateStructure;
RTC_DateType RTC_DateDefault;
RTC_TimeType RTC_TimeStructure;
RTC_TimeType RTC_TimeDefault;
RTC_InitType RTC_InitStructure;

RTC_DateType RTC_TimeStampDateStructure;
RTC_TimeType RTC_TimeStampStructure;

uint32_t SynchPrediv, AsynchPrediv;

ErrorStatus RTC_CLKSourceConfig(uint8_t ClkSrc, uint8_t FirstLastCfg);
ErrorStatus RTC_TimeRegulate(void);
ErrorStatus RTC_DateRegulate(void);
ErrorStatus RTC_AlarmRegulate(uint32_t RTC_Alarm);
void RTC_DateAndTimeDefaultVale(void);
static void RTC_PrescalerConfig(void);

void EXTI_PA1_TimeStamp_Configuration(void);
void RTC_TimeShow(void);
void RTC_DateShow(void);
void RTC_TimeStampShow(void);
void SysTick_Delay_Ms(__IO uint32_t ms);
void EXTI18_TAMPER_IRQn_Configuration(FunctionalState NewState,uint32_t TSEdgeSel);

#define RTC_CLOCK_TRY_COUNT            25

#define RTC_CLK_HSE128          1
#define RTC_CLK_HSI128          2
#define RTC_CLK_LSI             3

#define RTC_CLK_FIRST_CONFIG    0
#define RTC_CLK_LAST_CONFIG     1

/**
*\*\name    main.
*\*\fun     Main program.
*\*\param   none
*\*\return  none
**/
int main(void)
{
    /*!< At this stage the microcontroller clock setting is already configured,
         this is done through SystemInit() function which is called from startup
         file (startup_n32a052_xx.s) before to branch to application main.
         To reconfigure the default setting of SystemInit() function, refer to
         system_n32a052.c file
       */

    /* Initialize USART,TX: PA9 RX: PA10*/
    log_init();
    log_info("RTC Init");
    /* RTC date and time default value*/
    RTC_DateAndTimeDefaultVale();
    /* RTC clock source select 1:HSE/128 2:HSI/128 3:LSI*/
    if(SUCCESS == RTC_CLKSourceConfig(RTC_CLK_LSI, RTC_CLK_FIRST_CONFIG))
    {
        RTC_PrescalerConfig();
        /* RTC date time and alarm regulate*/
        RTC_DateRegulate();
        RTC_TimeRegulate();

        EXTI_PA1_TimeStamp_Configuration();
        EXTI18_TAMPER_IRQn_Configuration(ENABLE,1);
        RTC_ClrFlag(RTC_FLAG_TISF);
        RTC_ClrFlag(RTC_FLAG_TISOVF);
        /* RTC time stamp config and enable */
        RTC_EnableTimeStamp(RTC_TIMESTAMP_EDGE_FALLING, ENABLE);
        RTC_ConfigInt(RTC_INT_TST,ENABLE);
    }
    else
    {
        log_info("\r\n RTC Init Failed\r\n");
    }
    while (1)
    {

        SysTick_Delay_Ms(1000);
    }
}

/**
 * @brief  EXTI PA1 I/O config and use the EXTI interrupt to trigger time stamp.
 */
void EXTI_PA1_TimeStamp_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    GPIO_InitStruct(&GPIO_InitStructure);

    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_AFIO, ENABLE);

    /* Configure PB15 in alternate function mode */
    GPIO_InitStructure.Pin       = GPIO_PIN_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_INPUT;
    GPIO_InitStructure.GPIO_Pull = GPIO_PULL_UP;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);

    EXTI_RTCTimeStampSel(EXTI_TSSEL_LINE1);

    GPIO_ConfigEXTILine(GPIOA_PORT_SOURCE, GPIO_PIN_SOURCE1);
}

/**
 * @brief  Display the current TimeStamp (time and date) on the Hyperterminal.
 */
void RTC_TimeStampShow(void)
{
    /* Get the current TimeStamp */
    RTC_GetTimeStamp(RTC_FORMAT_BIN, &RTC_TimeStampStructure, &RTC_TimeStampDateStructure);
    printf("\n\r //=========TimeStamp Display (Time and Date)============// \n\r");
    printf("\n\r The current time stamp time (Hour-Minute-Second) is :  %0.2d:%0.2d:%0.2d \n\r",
           RTC_TimeStampStructure.Hours,
           RTC_TimeStampStructure.Minutes,
           RTC_TimeStampStructure.Seconds);
    printf("\n\r The current timestamp date (WeekDay-Date-Month) is :  %0.2d-%0.2d-%0.2d\n\r",
           RTC_TimeStampDateStructure.WeekDay,
           RTC_TimeStampDateStructure.Date,
           RTC_TimeStampDateStructure.Month);
}
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
 * @brief  RTC initalize default value.
 */
void RTC_DateAndTimeDefaultVale(void)
{ // Date
    RTC_DateDefault.WeekDay = 3;
    RTC_DateDefault.Date    = 1;
    RTC_DateDefault.Month   = 11;
    RTC_DateDefault.Year    = 23;
    // Time
    RTC_TimeDefault.H12     = RTC_AM_H12;
    RTC_TimeDefault.Hours   = 4;
    RTC_TimeDefault.Minutes = 5;
    RTC_TimeDefault.Seconds = 1;
}

/**
 * @brief  RTC date regulate with the default value.
 */
ErrorStatus RTC_DateRegulate(void)
{
    uint32_t tmp_hh = 0xFF, tmp_mm = 0xFF, tmp_ss = 0xFF;
    log_info("\n\r //=============Date Settings================// \n\r");

    log_info("\n\r Please Set WeekDay (01-07) \n\r");
    tmp_hh = RTC_DateDefault.WeekDay;
    if (tmp_hh == 0xff)
    {
        return ERROR;
    }
    else
    {
        RTC_DateStructure.WeekDay = tmp_hh;
    }
    log_info(": %0.2d\n\r", tmp_hh);

    tmp_hh = 0xFF;
    log_info("\n\r Please Set Date (01-31) \n\r");
    tmp_hh = RTC_DateDefault.Date;
    if (tmp_hh == 0xff)
    {
        return ERROR;
    }
    else
    {
        RTC_DateStructure.Date = tmp_hh;
    }
    log_info(": %0.2d\n\r", tmp_hh);

    log_info("\n\r Please Set Month (01-12)\n\r");
    tmp_mm = RTC_DateDefault.Month;
    if (tmp_mm == 0xff)
    {
        return ERROR;
    }
    else
    {
        RTC_DateStructure.Month = tmp_mm;
    }
    log_info(": %0.2d\n\r", tmp_mm);

    log_info("\n\r Please Set Year (00-99)\n\r");
    tmp_ss = RTC_DateDefault.Year;
    if (tmp_ss == 0xff)
    {
        return ERROR;
    }
    else
    {
        RTC_DateStructure.Year = tmp_ss;
    }
    log_info(": %0.2d\n\r", tmp_ss);

    /* Configure the RTC date register */
    if (RTC_SetDate(RTC_FORMAT_BIN, &RTC_DateStructure) == ERROR)
    {
        log_info("\n\r>> !! RTC Set Date failed. !! <<\n\r");
        return ERROR;
    }
    else
    {
        log_info("\n\r>> !! RTC Set Date success. !! <<\n\r");
        RTC_DateShow();
        return SUCCESS;
    }
}
/**
 * @brief  RTC time regulate with the default value.
 */
ErrorStatus RTC_TimeRegulate(void)
{
    uint32_t tmp_hh = 0xFF, tmp_mm = 0xFF, tmp_ss = 0xFF;
    log_info("\n\r //==============Time Settings=================// \n\r");

    RTC_TimeStructure.H12 = RTC_TimeDefault.H12;

    log_info("\n\r Please Set Hours \n\r");
    tmp_hh = RTC_TimeDefault.Hours;
    if (tmp_hh == 0xff)
    {
        return ERROR;
    }
    else
    {
        RTC_TimeStructure.Hours = tmp_hh;
    }
    log_info(": %0.2d\n\r", tmp_hh);

    log_info("\n\r Please Set Minutes \n\r");
    tmp_mm = RTC_TimeDefault.Minutes;
    if (tmp_mm == 0xff)
    {
        return ERROR;
    }
    else
    {
        RTC_TimeStructure.Minutes = tmp_mm;
    }
    log_info(": %0.2d\n\r", tmp_mm);

    log_info("\n\r Please Set Seconds \n\r");
    tmp_ss = RTC_TimeDefault.Seconds;
    if (tmp_ss == 0xff)
    {
        return ERROR;
    }
    else
    {
        RTC_TimeStructure.Seconds = tmp_ss;
    }
    log_info(": %0.2d\n\r", tmp_ss);

    /* Configure the RTC time register */
    if (RTC_ConfigTime(RTC_FORMAT_BIN, &RTC_TimeStructure) == ERROR)
    {
        log_info("\n\r>> !! RTC Set Time failed. !! <<\n\r");
        return ERROR;
    }
    else
    {
        log_info("\n\r>> !! RTC Set Time success. !! <<\n\r");
        RTC_TimeShow();
        return SUCCESS;
    }
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

void EXTI18_TAMPER_IRQn_Configuration(FunctionalState NewState,uint32_t TSEdgeSel)
{
    //GPIO_InitType GPIO_InitStructure;
    EXTI_InitType EXTI_InitStructure;
    NVIC_InitType NVIC_InitStructure;
    
    EXTI_ClrITPendBit(EXTI_LINE18);
    EXTI_InitStructure.EXTI_Line                          = EXTI_LINE18;
    EXTI_InitStructure.EXTI_Mode                          = EXTI_Mode_Interrupt;
    //EXTI_InitStructure.EXTI_Trigger                       = EXTI_Trigger_Rising; 
    if(TSEdgeSel == 0x01)
        EXTI_InitStructure.EXTI_Trigger   = EXTI_Trigger_Rising;  
    else if(TSEdgeSel == 0x02)
        EXTI_InitStructure.EXTI_Trigger   = EXTI_Trigger_Falling;
    else
        printf("\r\n The TSEdgeSel value is error! \r\n");
    EXTI_InitStructure.EXTI_LineCmd                       = ENABLE;
    EXTI_InitPeripheral(&EXTI_InitStructure);
    
    /* Enable the RTC Alarm Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel                    = RTC_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority  = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                 = NewState;
    NVIC_Init(&NVIC_InitStructure);
}
