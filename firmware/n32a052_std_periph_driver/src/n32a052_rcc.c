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
*\*\file n32a052_rcc.c
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
 */
#include "n32a052_rcc.h"


/** RCC Private Defines **/


/** RCC Driving Functions Declaration **/ 

/**
*\*\name    RCC_DeInit.
*\*\fun     Reset the RCC registers.
*\*\param   none 
*\*\return  none 
**/
void RCC_DeInit(void)
{
     /* Set HSIEN bit */
    RCC->CTRL |= (uint32_t)0x00000001U;

    /* Reset SCLKSW, AHBPRE, APB1PRES, APB2PRES, MCO and MCOPRES bits */
    RCC->CFG &= (uint32_t)0x21FF0000U;

    /* Reset HSEEN, CLKSSEN and PLLEN bits */
    RCC->CTRL &= (uint32_t)0xFEF6FFFFU;

    /* Reset PLLBPbit */
    RCC->CTRL &= (uint32_t)0xFFBFFFFFU;
  
    /* Reset PLLMULFCT, PLLPRE, PLLOUTDIV and PLLSRC bits */
    RCC->CFG &= (uint32_t)0xFE00FFFFU;

    /* Reset CFG2 register */
    RCC->CFG2 = 0x00003800U;

    /* Disable all interrupts and clear pending bits  */
    RCC->CLKINT = 0x00BD0000U;
}


/**
*\*\name    RCC_ConfigHse.
*\*\fun     Configures the External High Speed oscillator (HSE).
*\*\param   RCC_HSE :
*\*\          - RCC_HSE_DISABLE    HSE oscillator OFF 
*\*\          - RCC_HSE_ENABLE     HSE oscillator ON
*\*\          - RCC_HSE_BYPASS     HSE oscillator bypassed with external clock
*\*\return  none:
*\*\note    HSE can not be stopped if it is used directly or through the PLL as system clock
**/
void RCC_ConfigHse(uint32_t RCC_HSE)
{
    uint32_t temp_value;
    
    temp_value = RCC->CTRL;
    /* Reset HSEEN bit */
    temp_value &= (~RCC_HSE_ENABLE);
    /* Reset HSEBP bit */
    temp_value &= (~RCC_HSE_BYPASS);
    /* Configure HSE (RC_HSE_DISABLE is already covered by the code section above) */
    if(RCC_HSE == RCC_HSE_ENABLE)
    {
        /* Set HSEEN bit */
        temp_value |= RCC_HSE_ENABLE;
    }   
    else if (RCC_HSE == RCC_HSE_BYPASS)
    {
        /* Set HSEBP and HSEEN bits */
        temp_value |= RCC_HSE_BYPASS | RCC_HSE_ENABLE;
    }
    else
    {
        /* No process */
    }

    RCC->CTRL = temp_value;

}
 
/**
*\*\name    RCC_WaitHseStable.
*\*\fun     Waits for HSE start-up.
*\*\param   none
*\*\return  ErrorStatus:
 *\*\         - SUCCESS    HSE oscillator is stable and ready to use
 *\*\         - ERROR      HSE oscillator not yet ready
**/
ErrorStatus RCC_WaitHseStable(void)
{
    __IO uint32_t counter_value = 0;
    uint32_t timeout_value;  
    FlagStatus status_value;
	RCC_ClocksType sysclk_value;
    ErrorStatus bitstatus;

	RCC_GetClocksFreqValue(&sysclk_value);
	timeout_value = (HSE_STARTUP_TIMEOUT/((uint32_t)64000000/sysclk_value.SysclkFreq));
	
    /* Wait till HSE is ready and if Time out is reached exit */
    do
    {
        status_value = RCC_GetFlagStatus(RCC_CTRL_FLAG_HSERDF);
        counter_value++;
    } while ((counter_value != timeout_value) && (status_value == RESET));
    
    if (RCC_GetFlagStatus(RCC_CTRL_FLAG_HSERDF) != RESET)
    {
        bitstatus = SUCCESS;
    }
    else
    {
        bitstatus = ERROR;
    }
    return bitstatus;
}

/**
*\*\name    RCC_SetHseReadyDelay.
*\*\fun     Configures the External High Speed oscillator (HSE).
*\*\param   RCC_HSE:
*\*\          - RCC_HSE_READY_DELAY_0_5ms   HSE Clock ready delay 0.5ms  
*\*\          - RCC_HSE_READY_DELAY_1_0ms   HSE Clock ready delay 1.0ms   
*\*\          - RCC_HSE_READY_DELAY_1_5ms   HSE Clock ready delay 1.5ms
*\*\          - RCC_HSE_READY_DELAY_2_5ms   HSE Clock ready delay 2.5ms
*\*\note    
**/
void RCC_SetHseReadyDelay(uint32_t delay_value)
{
    uint32_t temp_value;

    temp_value = RCC->CTRL;
    /* Clear HSERDTIM[1:0] bits */
    temp_value &= RCC_HSE_READY_DELAY_MASK;
    /* Set the HSITRIM[1:0] bits  */
    temp_value |= delay_value; 
    /* Store the new value */
    RCC->CTRL = temp_value;

}
 
/**
*\*\name    RCC_EnableClockSecuritySystem.
*\*\fun     Enables the HSE Clock Security System.
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE     
*\*\return  none. 
**/
void RCC_EnableClockSecuritySystem(FunctionalState Cmd)
{
     if (Cmd != DISABLE)
    {
        RCC->CTRL |= RCC_CLKSS_ENABLE;
    }
    else
    {
        RCC->CTRL &= (~RCC_CLKSS_ENABLE);
    }
}


/**
*\*\name    RCC_SetHsiCalibValue.
*\*\fun     Adjusts the Internal High Speed oscillator (HSI) calibration value.
*\*\param   calibration_value(the calibration trimming value):
*\*\        This parameter must be a number between 0 and 0x0F
*\*\return  none
**/ 
void RCC_SetHsiCalibValue(uint8_t calibration_value) 
{
    uint32_t temp_value;

    temp_value = RCC->CTRL;
    /* Clear HSITRIM[3:0] bits */
    temp_value &= RCC_HSITRIM_MASK;
    /* Set the HSITRIM[3:0] bits according to HSICalibrationValue value */
    temp_value |= (uint32_t)calibration_value << RCC_CTRL_HSITRIM_OFFSET; 
    /* Store the new value */
    RCC->CTRL = temp_value;
}

/**
*\*\name    RCC_EnableHsi.
*\*\fun     Enables the Internal High Speed oscillator (HSI).
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE  
*\*\return  none
*\*\note   HSI can not be stopped if it is used directly or through the PLL as system clock.
**/ 
void RCC_EnableHsi(FunctionalState Cmd)
{
    if(Cmd == ENABLE)
   {
       /* Set HSIEN bit */
       RCC->CTRL |= RCC_HSI_ENABLE;
   }
   else
   {
       /* Reset HSIEN bit */
       RCC->CTRL &= (~RCC_HSI_ENABLE);
   }
}
 
/**
*\*\name    RCC_WaitHsiStable.
*\*\fun     Waits for HSI start-up.
*\*\param   none
*\*\return  ErrorStatus:
 *\*\         - SUCCESS    HSI oscillator is stable and ready to use
 *\*\         - ERROR      HSI oscillator not yet ready
**/
ErrorStatus RCC_WaitHsiStable(void)
{
    __IO uint32_t counter_value = 0;
    uint32_t timeout_value;  
    FlagStatus status_value;
	RCC_ClocksType sysclk_value;
    ErrorStatus bitstatus;

	RCC_GetClocksFreqValue(&sysclk_value);
	timeout_value = (HSI_STARTUP_TIMEOUT/((uint32_t)64000000/sysclk_value.SysclkFreq));

    /* Wait till HSI is ready and if Time out is reached exit */
    do
    {
        status_value = RCC_GetFlagStatus(RCC_CTRL_FLAG_HSIRDF);
        counter_value++;
    } while ((counter_value != timeout_value) && (status_value == RESET));
    
    if (RCC_GetFlagStatus(RCC_CTRL_FLAG_HSIRDF) != RESET)
    {
        bitstatus = SUCCESS;
    }
    else
    {
        bitstatus = ERROR;
    }
    return bitstatus;
}

/**
*\*\name    RCC_ConfigPll.
*\*\fun     Configures the PLL clock source and multiplication factor.
*\*\param   PLL_source(PLL entry clock source):
*\*\   		  - RCC_PLL_SRC_HSI    HSI oscillator clock selected as PLL clock entry
*\*\   		  - RCC_PLL_SRC_HSE    HSE oscillator clock selected as PLL clock entry
*\*\param   PLL_multiplication(PLL multiplication factor):
*\*\	      - RCC_PLL_MUL_BP 
*\*\	      - RCC_PLL_MUL_3  
*\*\	      - RCC_PLL_MUL_4  
*\*\	      - RCC_PLL_MUL_5  
*\*\	      - RCC_PLL_MUL_6  
*\*\	      - RCC_PLL_MUL_7  
*\*\	      - RCC_PLL_MUL_8  
*\*\	      - RCC_PLL_MUL_9  
*\*\	      - RCC_PLL_MUL_10 
*\*\	      - RCC_PLL_MUL_11 
*\*\	      - RCC_PLL_MUL_12 
*\*\	      - RCC_PLL_MUL_13 
*\*\	      - RCC_PLL_MUL_14 
*\*\	      - RCC_PLL_MUL_15
*\*\	      - RCC_PLL_MUL_16
*\*\	      - RCC_PLL_MUL_17
*\*\	      - RCC_PLL_MUL_18
*\*\param   PLL_prescaler(PLL Pre-Divider):
*\*\	      - RCC_PLL_PRE_1 
*\*\	      - RCC_PLL_PRE_2
*\*\	      - RCC_PLL_PRE_3 
*\*\	      - RCC_PLL_PRE_4 
*\*\param   PLL_outdivider(PLL Out divider):
*\*\	      - RCC_PLLOUT_DIV_1 
*\*\	      - RCC_PLLOUT_DIV_2
*\*\	      - RCC_PLLOUT_DIV_3 
*\*\	      - RCC_PLLOUT_DIV_4 
*\*\return  none
*\*\note    This function must be used only when the PLL is disabled. 
**/
void RCC_ConfigPll(uint32_t PLL_source, uint32_t PLL_multiplication, uint32_t  PLL_prescaler,  uint32_t PLL_outdivider)
{
    uint32_t temp_value1;  
    
    temp_value1 = RCC->CFG;
    /* Clear PLLSRC, PLLPRE, PLLOUTDIV and PLLMUL[3:0] bits */
    temp_value1 &= RCC_PLL_MASK;
    /* Set PLLSRC, PLLPRE, PLLOUTDIV  bits */
    temp_value1 |= (PLL_source | PLL_prescaler | PLL_outdivider);

    /* Set the PLL configuration bits */
    if(PLL_multiplication == RCC_PLL_MUL_BP)
    {
        /*Set PLLBP, Fout = Fin/N */ 
        RCC->CTRL |= RCC_PLL_MUL_BP;
    }
    else
    {
        /*Disable PLLBP */ 
        RCC->CTRL &= (~RCC_PLL_MUL_BP);
        /*Set PLLMUL[3:0], Fout = Fin*M/N */ 
        temp_value1 |= (PLL_multiplication);
        
    }
    /* Store the new value */
    RCC->CFG  = temp_value1;
}

/**
*\*\name    RCC_EnablePll.
*\*\fun     Enables the PLL.
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\return  none
**/ 
void RCC_EnablePll(FunctionalState Cmd)
{
    if(Cmd == ENABLE)
   {
       /* Set PLLEN bit */
       RCC->CTRL |= RCC_PLL_ENABLE;
   }
   else
   {
       /* Reset PLLEN bit */
       RCC->CTRL &= (~RCC_PLL_ENABLE);
   }
}


/**
*\*\name    RCC_EnablePllClockOut.
*\*\fun     Enables the PLL out.
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\return  none
**/ 
void RCC_EnablePllClockOut(FunctionalState Cmd)
{
    if(Cmd == ENABLE)
   {
       /* Set PLLOUTEN bit */
       RCC->CTRL |= RCC_PLLOUT_ENABLE;
   }
   else
   {
       /* Reset PLLOUTEN bit */
       RCC->CTRL &= (~RCC_PLLOUT_ENABLE);
   }
}

/**
*\*\name    RCC_ConfigSysclk.
*\*\fun     Configures the system clock (SYSCLK).
*\*\param   sysclk_source(clock source used as system clock):
*\*\	     - RCC_SYSCLK_SRC_HSI       HSI selected as system clock
*\*\	     - RCC_SYSCLK_SRC_HSE       HSE selected as system clock
*\*\	     - RCC_SYSCLK_SRC_PLLCLK    PLL selected as system clock
*\*\	     - RCC_SYSCLK_SRC_LSI       LSI selected as system clock
*\*\return  none
**/
void RCC_ConfigSysclk(uint32_t sysclk_source)
{
    uint32_t temp_value;
    
    temp_value = RCC->CFG;
    /* Clear SCLKSW[2:0] bits */
    temp_value &= RCC_SYSCLK_SRC_MASK;
    /* Set SCLKSW[2:0] bits according to sysclk_source value */
    temp_value |= sysclk_source;
    /* Store the new value */
    RCC->CFG = temp_value;
}

/**
*\*\name    RCC_GetSysclkSrc.
*\*\fun     Returns the clock source used as system clock.
*\*\param   none
*\*\return  (The clock source used as system clock):
*\*\         - RCC_CFG_SCLKSTS_HSI    HSI used as system clock  
*\*\         - RCC_CFG_SCLKSTS_HSE    HSE used as system clock
*\*\         - RCC_CFG_SCLKSTS_PLL    PLL used as system clock
*\*\         - RCC_CFG_SCLKSTS_LSI    LSI used as system clock

**/
uint32_t RCC_GetSysclkSrc(void)  
{  
    return ((uint32_t)(RCC->CFG & RCC_SYSCLK_STS_MASK));
}

/**
*\*\name    RCC_ConfigHclk.
*\*\fun     Configures the AHB clock (HCLK).
*\*\param   sysclk_div(AHB clock is derived from the system clock (SYSCLK)):
*\*\         - RCC_SYSCLK_DIV1      AHB clock = SYSCLK
*\*\         - RCC_SYSCLK_DIV2      AHB clock = SYSCLK/2
*\*\         - RCC_SYSCLK_DIV4      AHB clock = SYSCLK/4
*\*\         - RCC_SYSCLK_DIV8      AHB clock = SYSCLK/8
*\*\         - RCC_SYSCLK_DIV16     AHB clock = SYSCLK/16
*\*\         - RCC_SYSCLK_DIV64     AHB clock = SYSCLK/64
*\*\         - RCC_SYSCLK_DIV128    AHB clock = SYSCLK/128
*\*\         - RCC_SYSCLK_DIV256    AHB clock = SYSCLK/256
*\*\         - RCC_SYSCLK_DIV512    AHB clock = SYSCLK/512
*\*\return  none
**/
void RCC_ConfigHclk(uint32_t sysclk_div)
{
    uint32_t temp_value;
    temp_value = RCC->CFG;
    /* Clear AHBPRES[3:0] bits */
    temp_value &= RCC_SYSCLK_DIV_MASK;
    /* Set AHBPRES[3:0] bits according to rcc_sysclk value */
    temp_value |= sysclk_div;
    /* Store the new value */
    RCC->CFG = temp_value;
}

/**
*\*\name    RCC_ConfigPclk1.
*\*\fun     Configures the Low Speed APB clock (PCLK1).
*\*\param   hclk_div(APB1 clock is derived from the AHB clock (HCLK)):
*\*\         - RCC_HCLK_DIV1     APB1 clock = HCLK
*\*\         - RCC_HCLK_DIV2     APB1 clock = HCLK/2
*\*\         - RCC_HCLK_DIV4     APB1 clock = HCLK/4
*\*\         - RCC_HCLK_DIV8     APB1 clock = HCLK/8
*\*\         - RCC_HCLK_DIV16    APB1 clock = HCLK/16
*\*\return  none
**/
void RCC_ConfigPclk1(uint32_t hclk_div)
{
    uint32_t temp_value;
    
    temp_value = RCC->CFG;
    /* Clear APB1PRES[2:0] bits */
    temp_value &= RCC_APB1_DIV_MASK;
    /* Set APB1PRES[2:0] bits according to hclk_div value */
    temp_value |= hclk_div;
    /* Store the new value */
    RCC->CFG = temp_value;
}

/**
*\*\name    RCC_ConfigPclk2.
*\*\fun     Configures the High Speed APB clock (PCLK2).
*\*\param   hclk_div(APB2 clock is derived from the AHB clock (HCLK)):
*\*\         - RCC_HCLK_DIV1     APB2 clock = HCLK
*\*\         - RCC_HCLK_DIV2     APB2 clock = HCLK/2
*\*\         - RCC_HCLK_DIV4     APB2 clock = HCLK/4
*\*\         - RCC_HCLK_DIV8     APB2 clock = HCLK/8
*\*\         - RCC_HCLK_DIV16    APB2 clock = HCLK/16
*\*\return  none
**/
void RCC_ConfigPclk2(uint32_t hclk_div)
{
    uint32_t temp_value;
    
    temp_value = RCC->CFG;
    /* Clear APB2PRES[2:0] bits */
    temp_value &= RCC_APB2_DIV_MASK;
    /* Set APB2PRES[2:0] bits according to hclk_div value */
    temp_value |= hclk_div << RCC_APB2PRES_OFFSET; 
    /* Store the new value */
    RCC->CFG = temp_value;
}

/**
*\*\name    RCC_ConfigInt.
*\*\fun     Enables the specified RCC interrupts.
*\*\param   Interrupt(the RCC interrupt sources to be enabled):
*\*\         - RCC_INT_LSIRDIF    LSI ready interrupt
*\*\         - RCC_INT_HSIRDIF    HSI ready interrupt
*\*\         - RCC_INT_HSERDIF    HSE ready interrupt
*\*\         - RCC_INT_PLLRDIF    PLL ready interrupt
*\*\         - RCC_INT_RAMPERRIF  RAM parity error interrupt 
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\return  none
**/
void RCC_ConfigInt(uint32_t Interrupt, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->CLKINT |= (((uint32_t)Interrupt) << 8);
    }
    else
    {
        RCC->CLKINT &= (~(((uint32_t)Interrupt) << 8));
    }
}

/**
*\*\name    RCC_ConfigTim1Clk.
*\*\fun     Configures the TIM1 clock source(TIM1CLK).
*\*\param   timer1_clksrc(TIM1 clock source):
*\*\         - RCC_TIM1_CLKSRC_PCLK 
*\*\         - RCC_TIM1_CLKSRC_SYSCLK
*\*\return  none
**/
void RCC_ConfigTim1Clk(uint32_t timer1_clksrc)  
{
    uint32_t temp_value;

    temp_value = RCC->CFG2;
    /* Clear TIMCLK_SEL bits */
    temp_value &= RCC_TIM1_CLKSRC_MASK;
    /* Set TIMCLK_SEL bits according to timer1_clksrc value */
    temp_value |= timer1_clksrc;

    /* Store the new value */
    RCC->CFG2 = temp_value;
}

/**
*\*\name    RCC_ConfigTim6Clk.
*\*\fun     Configures the TIM6 clock source(TIM6CLK).
*\*\param   timer6_clksrc(TIM6 clock source):
*\*\        - RCC_TIM6_CLKSRC_PCLK 
*\*\        - RCC_TIM6_CLKSRC_LSI 
*\*\return  none
**/
void RCC_ConfigTim6Clk(uint32_t timer6_clksrc)  
{
    uint32_t temp_value;

    temp_value = RCC->CFG2;
    /* Clear TIMCLK_SEL bits */
    temp_value &= RCC_TIM6_CLKSRC_MASK;
    /* Set TIMCLK_SEL bits according to timer6_clksrc value */
    temp_value |= timer6_clksrc;

    /* Store the new value */
    RCC->CFG2 = temp_value;
}

/**
*\*\name    RCC_ConfigLCDClk_.
*\*\fun     Configures the LCD clock source(LCDCLK).
*\*\param   lcd_clksrc(LCD clock source):
*\*\         - RCC_LCD_CLKSRC_HSI_DIV8    HSI clock divided 8 selected 
*\*\         - RCC_LCD_CLKSRC_HSE_DIV16   HSE clock divided 16 selected 
*\*\return  none
**/
void RCC_ConfigLCDClk(uint32_t lcd_clksrc)  
{
    uint32_t temp_value;

    temp_value = RCC->CFG2;
    /* Clear TIMCLK_SEL bits */
    temp_value &= RCC_LCD_CLKSRC_MASK;
    /* Set TIMCLK_SEL bits according to lcd_clksrc value */
    temp_value |= lcd_clksrc;

    /* Store the new value */
    RCC->CFG2 = temp_value;
}


/**
*\*\name    RCC_ConfigAdc1mClk.
*\*\fun     Configures the ADCx 1M clock (ADC1MCLK).
*\*\param   ADC1M_clksrc(ADC1M clock source):
*\*\         - RCC_ADC1MCLK_SRC_HSI
*\*\         - RCC_ADC1MCLK_SRC_HSE
*\*\param   ADC1M_prescaler(ADC1M clock prescaler):
*\*\         - RCC_ADC1MCLK_DIV1 
*\*\         - RCC_ADC1MCLK_DIV2 
*\*\         - RCC_ADC1MCLK_DIV3 
*\*\         - RCC_ADC1MCLK_DIV4 
*\*\         - RCC_ADC1MCLK_DIV5 
*\*\         - RCC_ADC1MCLK_DIV6 
*\*\         - RCC_ADC1MCLK_DIV7 
*\*\         - RCC_ADC1MCLK_DIV8 
*\*\         - RCC_ADC1MCLK_DIV9 
*\*\         - RCC_ADC1MCLK_DIV10
*\*\         - RCC_ADC1MCLK_DIV11
*\*\         - RCC_ADC1MCLK_DIV12
*\*\         - RCC_ADC1MCLK_DIV13
*\*\         - RCC_ADC1MCLK_DIV14
*\*\         - RCC_ADC1MCLK_DIV15
*\*\         - RCC_ADC1MCLK_DIV16
*\*\         - RCC_ADC1MCLK_DIV17
*\*\         - RCC_ADC1MCLK_DIV18
*\*\         - RCC_ADC1MCLK_DIV19
*\*\         - RCC_ADC1MCLK_DIV20
*\*\         - RCC_ADC1MCLK_DIV21
*\*\         - RCC_ADC1MCLK_DIV22
*\*\         - RCC_ADC1MCLK_DIV23
*\*\         - RCC_ADC1MCLK_DIV24
*\*\         - RCC_ADC1MCLK_DIV25
*\*\         - RCC_ADC1MCLK_DIV26
*\*\         - RCC_ADC1MCLK_DIV27
*\*\         - RCC_ADC1MCLK_DIV28
*\*\         - RCC_ADC1MCLK_DIV29
*\*\         - RCC_ADC1MCLK_DIV30
*\*\         - RCC_ADC1MCLK_DIV31
*\*\         - RCC_ADC1MCLK_DIV32
*\*\return  none
**/
void RCC_ConfigAdc1mClk(uint32_t ADC1M_clksrc, uint32_t ADC1M_prescaler)
{
    uint32_t temp_value;

    temp_value = RCC->CFG2;
    /* Clear ADC1MSEL and ADC1MPRE[4:0] bits */
    temp_value &= RCC_ADC1MCLK_SRC_MASK;
    temp_value &= RCC_ADC1MCLK_DIV_MASK;
    /* Set ADC1MSEL bits according to ADC1M_clksrc value */
    temp_value |= ADC1M_clksrc;
    /* Set ADC1MPRE[4:0] bits according to ADC1M_prescaler value */
    temp_value |= ADC1M_prescaler;

    /* Store the new value */
    RCC->CFG2 = temp_value;
}

/**
*\*\name    RCC_ConfigADCClksrc.
*\*\fun     Configures the ADC clock source(ADCCLK).
*\*\param   adc_clksrc(ADC clock source):
*\*\         - RCC_ADC_CLKSRC_HSI24M 
*\*\         - RCC_ADC_CLKSRC_PLL
*\*\         - RCC_ADC_CLKSRC_HCLK 
*\*\return  none
**/
void RCC_ConfigADCClksrc(uint32_t adc_clksrc)  
{
    uint32_t temp_value;

    temp_value = RCC->CFG2;
    /* Clear TIMCLK_SEL bits */
    temp_value &= RCC_ADC_CLKSRC_MASK;
    /* Set TIMCLK_SEL bits according to adc_clksrc value */
    temp_value |= adc_clksrc;

    /* Store the new value */
    RCC->CFG2 = temp_value;
}

/**
*\*\name    RCC_ConfigAdcPllClk.
*\*\fun     Configures the ADCPLLCLK prescaler, and enable ADCPLLCLK.
*\*\param   ADC_PLLCLK_prescaler(ADCPLLCLK prescaler):
*\*\         - RCC_ADCPLLCLK_DIV1       ADCPLLCLKPRES[4:0] = 10000, Pll Clock Divided By 1
*\*\         - RCC_ADCPLLCLK_DIV2       ADCPLLCLKPRES[4:0] = 10001, Pll Clock Divided By 2
*\*\         - RCC_ADCPLLCLK_DIV4       ADCPLLCLKPRES[4:0] = 10010, Pll Clock Divided By 4
*\*\         - RCC_ADCPLLCLK_DIV6       ADCPLLCLKPRES[4:0] = 10011, Pll Clock Divided By 6
*\*\         - RCC_ADCPLLCLK_DIV8       ADCPLLCLKPRES[4:0] = 10100, Pll Clock Divided By 8
*\*\         - RCC_ADCPLLCLK_DIV10      ADCPLLCLKPRES[4:0] = 10101, Pll Clock Divided By 10
*\*\         - RCC_ADCPLLCLK_DIV12      ADCPLLCLKPRES[4:0] = 10110, Pll Clock Divided By 12
*\*\         - RCC_ADCPLLCLK_DIV16      ADCPLLCLKPRES[4:0] = 10111, Pll Clock Divided By 16
*\*\         - RCC_ADCPLLCLK_DIV32      ADCPLLCLKPRES[4:0] = 11000, Pll Clock Divided By 32
*\*\         - RCC_ADCPLLCLK_DIV64      ADCPLLCLKPRES[4:0] = 11001, Pll Clock Divided By 64
*\*\         - RCC_ADCPLLCLK_DIV128     ADCPLLCLKPRES[4:0] = 11010, Pll Clock Divided By 128
*\*\         - RCC_ADCPLLCLK_DIV256     ADCPLLCLKPRES[4:0] = 11011, Pll Clock Divided By 256
*\*\         - RCC_ADCPLLCLK_DIV_OTHERS ADCPLLCLKPRES[4:0] = others, Pll Clock Divided By 256
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\return  none
**/
void RCC_ConfigAdcPllClk(uint32_t ADC_PLLCLK_prescaler, FunctionalState Cmd)
{
    uint32_t temp_value;

    temp_value = RCC->CFG2;
    /* Clear ADCPLLPRES[4:0] bits */
    temp_value &= RCC_ADCPLLCLK_MASK;

    if (Cmd != DISABLE)
    {
        temp_value |= ADC_PLLCLK_prescaler;
    }
    else
    {
        temp_value &= RCC_ADCPLLCLK_DISABLE;
    }

    /* Store the new value */
    RCC->CFG2 = temp_value;
}


/**
*\*\name    RCC_ConfigAdcHclk.
*\*\fun     Configures the ADCHCLK prescaler.
*\*\param   ADC_hclk_prescaler(ADCHCLK prescaler):
*\*\         - RCC_ADCHCLK_DIV1        ADCHCLKPRE[3:0] = 0000, HCLK Clock Divided By 1
*\*\         - RCC_ADCHCLK_DIV2        ADCHCLKPRE[3:0] = 0001, HCLK Clock Divided By 2
*\*\         - RCC_ADCHCLK_DIV4        ADCHCLKPRE[3:0] = 0010, HCLK Clock Divided By 4
*\*\         - RCC_ADCHCLK_DIV6        ADCHCLKPRE[3:0] = 0011, HCLK Clock Divided By 6
*\*\         - RCC_ADCHCLK_DIV8        ADCHCLKPRE[3:0] = 0100, HCLK Clock Divided By 8
*\*\         - RCC_ADCHCLK_DIV10       ADCHCLKPRE[3:0] = 0101, HCLK Clock Divided By 10
*\*\         - RCC_ADCHCLK_DIV12       ADCHCLKPRE[3:0] = 0110, HCLK Clock Divided By 12
*\*\         - RCC_ADCHCLK_DIV16       ADCHCLKPRE[3:0] = 0111, HCLK Clock Divided By 16
*\*\         - RCC_ADCHCLK_DIV32       ADCHCLKPRE[3:0] = 1000, HCLK Clock Divided By 32
*\*\         - RCC_ADCHCLK_DIV_OTHERS  ADCHCLKPRE[3:0] = others, HCLK Clock Divided By 32
*\*\return  none
**/
void RCC_ConfigAdcHclk(uint32_t ADC_hclk_prescaler)
{
    uint32_t temp_value;

    temp_value = RCC->CFG2;
    /* Clear ADCHPRE[3:0] bits */
    temp_value &= RCC_ADCHCLK_DIV_MASK;
    /* Set ADCHPRE[3:0] bits according to ADC_hclk_prescaler value */
    temp_value |= ADC_hclk_prescaler;

    /* Store the new value */
    RCC->CFG2 = temp_value;
}


/**
*\*\name    RCC_EnableLsi.
*\*\fun     Enables the Internal Low Speed oscillator (LSI).
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\return  none
**/
void RCC_EnableLsi(FunctionalState Cmd)
{
    if(Cmd == ENABLE)
    {
        /* Set LSIEN bit */
        RCC->LSCTRL |= RCC_LSI_ENABLE;
    }
    else
    {
        /* Reset PLLEN bit */
        RCC->LSCTRL &= (~RCC_LSI_ENABLE);
    }
     
}

/**
*\*\name    RCC_SetLsiCalibValue.
*\*\fun     Adjusts the Internal Low Speed oscillator (LSI) calibration value.
*\*\param   calibration_value(the calibration trimming value):
*\*\        This parameter must be a number between 0 and 0x1F
*\*\return  none
**/
void RCC_SetLsiCalibValue(uint8_t calibration_value)
{
    uint32_t temp_value;

    temp_value = RCC->LSCTRL;
    /* Clear LSITRIM[4:0] bits */
    temp_value &= RCC_LSITRIM_MASK;
    /* Set the LSITRIM[4:0] bits according to LSICalibrationValue value */
    temp_value |= (uint32_t)calibration_value << RCC_LSCTRL_LSITRIM_OFFSET;
    /* Store the new value */
    RCC->LSCTRL = temp_value;
}


/**
*\*\name    RCC_WaitLsiStable.
*\*\fun     Waits for LSI start-up.
*\*\param   none
*\*\return  ErrorStatus:
 *\*\         - SUCCESS    LSI oscillator is stable and ready to use
 *\*\         - ERROR      LSI oscillator not yet ready
**/
ErrorStatus RCC_WaitLsiStable(void)
{
    __IO uint32_t counter_value = 0;
    uint32_t timeout_value;   
    FlagStatus status_value;
	RCC_ClocksType sysclk_value;
    ErrorStatus bitstatus;

	RCC_GetClocksFreqValue(&sysclk_value);
	timeout_value = (LSI_STARTUP_TIMEOUT/((uint32_t)64000000/sysclk_value.SysclkFreq));

    /* Wait till LSI is ready and if Time out is reached exit */
    do
    {
        status_value = RCC_GetFlagStatus(RCC_LSCTRL_FLAG_LSIRDF);
        counter_value++;
    } while ((counter_value != timeout_value) && (status_value == RESET));
    
    if (RCC_GetFlagStatus(RCC_LSCTRL_FLAG_LSIRDF) != RESET)
    {
        bitstatus = SUCCESS;
    }
    else
    {
        bitstatus = ERROR;
    }
    return bitstatus;
}

/**
*\*\name    RCC_ConfigRtcClk.
*\*\fun     Configures the RTC clock (RTCCLK).
*\*\param   rtcclk_source(the RTC clock source):
*\*\         - RCC_RTCCLK_SRC_NONE          No clock selected as RTC clock
*\*\         - RCC_RTCCLK_SRC_LSI           LSI selected as RTC clock
*\*\         - RCC_RTCCLK_SRC_HSE_DIV128    HSE clock divided by 128 selected as RTC clock
*\*\         - RCC_RTCCLK_SRC_HSI_DIV128    HSI clock divided by 128 selected as RTC clock
*\*\return  none
*\*\note    Once the RTC clock is selected it can't be changed unless the Backup domain is reset.
**/
void RCC_ConfigRtcClk(uint32_t rtcclk_source)
{
    uint32_t temp_value;

    temp_value = RCC->LSCTRL;

    /* Clear the RTC clock source */
    temp_value &= RCC_RTCCLK_SRC_MASK;
    /* Select the RTC clock source */
    temp_value |= rtcclk_source;

    RCC->LSCTRL = temp_value;
}

/**
*\*\name    RCC_EnableRtcClk.
*\*\fun     Enables the RTC clock.
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\return  none
*\*\note    This function must be used only after the RTC clock was selected 
*\*\        using the RCC_Config_Rtc_Clock function.
**/
void RCC_EnableRtcClk(FunctionalState Cmd)
{
    if(Cmd == ENABLE)
    {
        RCC->LSCTRL |= RCC_RTC_ENABLE;
    }
    else
    {
        RCC->LSCTRL &= (~RCC_RTC_ENABLE);
    }
}

/**
*\*\name    RCC_EnableRTCReset.
*\*\fun     Reset RTC .
*\*\param   none  
*\*\return  none. 
**/
void RCC_EnableRTCReset(void)
{ 
    RCC->LSCTRL |= (RCC_RTCCLK_RESET);
    RCC->LSCTRL &= (~RCC_RTCCLK_RESET);
}

/**
*\*\name    RCC_EnableLockupReset.
*\*\fun     Reset can be generated when M0 core lock up.
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE   
*\*\return  none. 
**/
void RCC_EnableLockupReset(FunctionalState Cmd)
{ 
   if(Cmd == ENABLE)
   {
       /* Set LKUPRST bit */
       RCC->CTRL |= RCC_LKUPRST_ENABLE;
   }
   else
   {
       /* Reset LKUPRST bit */
       RCC->CTRL &= (~RCC_LKUPRST_ENABLE);
   }
    
}

/**
*\*\name    RCC_EnableRAMParityErrorReset.
*\*\fun     Reset can be generated when RAM parity error.
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE   
*\*\return  none. 
**/
void RCC_EnableRAMParityErrorReset(FunctionalState Cmd)
{ 
   if(Cmd == ENABLE)
   {
       /* Set RAMPERRRST bit */
       RCC->CLKINT |= RCC_RAMPERRRST_ENABLE;
   }
   else
   {
       /* Reset RAMPERRRST bit */
       RCC->CLKINT &= (~RCC_RAMPERRRST_ENABLE);
   }
    
}

/**
*\*\name    RCC_EnableLEDClk.
*\*\fun     LED clock enable.
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\return  none. 
**/
void RCC_EnableLEDClk(FunctionalState Cmd)
{ 
   if(Cmd == ENABLE)
   {
       /* Set LEDCLK bit */
       RCC->CFG3 |= RCC_LEDCLK_ENABLE;
   }
   else
   {
       /* Reset LEDCLK bit */
       RCC->CFG3 &= (~RCC_LEDCLK_ENABLE);
   }   
}

/**
*\*\name    RCC_ConfigLEDClk.
*\*\fun     Configures the LED clock (LEDCLK).
*\*\param   LED_clksrc(LED clock source):
*\*\         - RCC_LEDCLK_SRC_HSI    HSI clock selected 
*\*\         - RCC_LEDCLK_SRC_HSE    HSE clock selected 
*\*\param   LED_prescaler(LED clock prescaler):
*\*\         - RCC_LEDCLK_DISABLE 
*\*\         - RCC_LEDCLK_DIV32
*\*\         - RCC_LEDCLK_DIV40
*\*\         - RCC_LEDCLK_DIV50
*\*\         - RCC_LEDCLK_DIV64
*\*\         - RCC_LEDCLK_DIV80
*\*\         - RCC_LEDCLK_DIV160
*\*\return  none
**/
void RCC_ConfigLEDClk(uint32_t LED_clksrc, uint32_t LED_prescaler)
{
    uint32_t temp_value;

    temp_value = RCC->CFG3;
    /* Clear LEDSEL and LEDPRE[3:0] bits */
    temp_value &= RCC_LEDCLK_SRC_MASK;
    temp_value &= RCC_LEDCLK_DIV_MASK;
    /* Set LEDSEL bits according to LED_clksrc value */
    temp_value |= LED_clksrc;
    /* Set LEDPRE[3:0] bits according to LED_prescaler value */
    temp_value |= LED_prescaler;

    /* Store the new value */
    RCC->CFG3 = temp_value;
}

/**
*\*\name    RCC_EnableLEDDMARequest.
*\*\fun     LED DMA Request enable.
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE  
*\*\return  none. 
**/
void RCC_EnableLEDDMARequest(FunctionalState Cmd)
{ 
   if(Cmd == ENABLE)
   {
       /* Set DMAREQ bit */
       RCC->CFG3 |= RCC_LED_DMAREQ_ENABLE;
   }
   else
   {
       /* Reset DMAREQ bit */
       RCC->CFG3 &= (~RCC_LED_DMAREQ_ENABLE);
   }
}

/**
*\*\name    RCC_SetLEDLowLevelCycles.
*\*\fun     Number of low level cycles in one time period.
*\*\param   cycles_value:
*\*\        This parameter must be a number between 2 and 0xFF
*\*\return  none
**/ 
void RCC_SetLEDLowLevelCycles(uint8_t cycles_value) 
{
    uint32_t temp_value;

    temp_value = RCC->CFG3;
    /* Clear GCLKMNUM[7:0] bits */
    temp_value &= RCC_GCLKMNUM_MASK;
    if(cycles_value < RCC_MIN_GCLKMNUM )
    {
        cycles_value = RCC_MIN_GCLKMNUM;
    }
    /* Set the GCLKMNUM[7:0] bits */
    temp_value |= ((uint32_t)cycles_value << RCC_CFG3_GCLKMNUM_OFFSET); 
    /* Store the new value */
    RCC->CFG3 = temp_value;
}

/**
*\*\name    RCC_SetLEDClockCycles.
*\*\fun     Number of clock cycles in one time period.
*\*\param   cycles_value:
*\*\        This parameter must be fiexed at 130.
*\*\return  none
**/ 
void RCC_SetLEDClockCycles(uint8_t cycles_value) 
{
    uint32_t temp_value;

    temp_value = RCC->CFG3;
    /* Clear GCLKNNUM[7:0] bits */
    temp_value &= RCC_GCLKNNUM_MASK;
    /* Set the GCLKNNUM[7:0] bits */
    temp_value |= ((uint32_t)cycles_value << RCC_CFG3_GCLKNNUM_OFFSET); 
    /* Store the new value */
    RCC->CFG3 = temp_value;
}

/**
*\*\name    RCC_ConfigALL_LED_GCLK.
*\*\fun     Configures GCLKEN GCLKSEL GCLKDMAEN GCLKPRE[3:0] GCLKMNUM[7:0] GCLKNNUM[7:0].
*\*\param   Gclk_Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\param   LED_clksrc(LED clock source):
*\*\         - RCC_LEDCLK_SRC_HSI    HSI clock selected 
*\*\         - RCC_LEDCLK_SRC_HSE    HSE clock selected 
*\*\param   LED_prescaler(LED clock prescaler):
*\*\         - RCC_LEDCLK_DISABLE 
*\*\         - RCC_LEDCLK_DIV32
*\*\         - RCC_LEDCLK_DIV40
*\*\         - RCC_LEDCLK_DIV50
*\*\         - RCC_LEDCLK_DIV64
*\*\         - RCC_LEDCLK_DIV80
*\*\         - RCC_LEDCLK_DIV160
*\*\param   GclkDma_Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\param   mcycles_value:
*\*\        This parameter must be a number between 1 and 0xFF
*\*\param   ncycles_value:
*\*\        This parameter must be a number between 1 and 0xFF
*\*\return  none
**/ 
void RCC_ConfigALL_LED_GCLK(FunctionalState Gclk_Cmd, uint32_t LED_clksrc, uint32_t LED_prescaler, \
                            FunctionalState GclkDma_Cmd, uint8_t mcycles_value, uint8_t ncycles_value)
{
    uint32_t temp_value;

    temp_value = RCC->CFG3;

    /* Clear LEDSEL and LEDPRE[3:0] bits */
    temp_value &= RCC_LEDCLK_SRC_MASK;
    temp_value &= RCC_LEDCLK_DIV_MASK;
    /* Clear GCLKMNUM[7:0] bits */
    temp_value &= RCC_GCLKMNUM_MASK;
    /* Clear GCLKNNUM[7:0] bits */
    temp_value &= RCC_GCLKNNUM_MASK;

    /* Set GCLKEN value */
    if(Gclk_Cmd == ENABLE)
    {
        /* Set LEDCLK bit */
        temp_value |= RCC_LEDCLK_ENABLE;
    }
    else
    {
        /* Reset LEDCLK bit */
        temp_value &= (~RCC_LEDCLK_ENABLE);
    }

    /* Set LEDSEL bits according to LED_clksrc value */
    temp_value |= LED_clksrc;
    /* Set LEDPRE[3:0] bits according to LED_prescaler value */
    temp_value |= LED_prescaler;

    /* Set GCLKDMAEN value */
    if(GclkDma_Cmd == ENABLE)
    {
        /* Set DMAREQ bit */
        temp_value |= RCC_LED_DMAREQ_ENABLE;
    }
    else
    {
        /* Reset DMAREQ bit */
        temp_value &= (~RCC_LED_DMAREQ_ENABLE);
    }

    /* GCLKMNUM[7:0] value >= 1 */
    if(mcycles_value < RCC_MIN_GCLKMNUM )
    {
        mcycles_value = RCC_MIN_GCLKMNUM;
    }
    /* Set the GCLKMNUM[7:0] bits */
    temp_value |= ((uint32_t)mcycles_value << RCC_CFG3_GCLKMNUM_OFFSET); 

    /* GCLKNNUM[7:0] value >= 1 */
    if(ncycles_value < RCC_MIN_GCLKNNUM )
    {
        ncycles_value = RCC_MIN_GCLKNNUM;
    }
    /* Set the GCLKNNUM[7:0] bits */
    temp_value |= ((uint32_t)ncycles_value << RCC_CFG3_GCLKNNUM_OFFSET); 

    /* Store the new value */
    RCC->CFG3 = temp_value;
}


/**
*\*\name    RCC_GetClocksFreqValue.
*\*\fun     Returns the frequencies of different on chip clocks.
*\*\param   RCC_clocks pointer to a RCC_ClocksType structure which will hold
*\*\        the clocks frequencies.
*\*\return  none
*\*\note    The result of this function could be not correct when using
*\*\        fractional value for HSE crystal.  
**/
void RCC_GetClocksFreqValue(RCC_ClocksType* RCC_clocks)
{
    uint32_t temp, pllclk, pllmull, pllpre, plloutdiv, pllsource, presc;
    const uint8_t ApbAhbPresTable[16]     = {0, 0, 0, 0, 1, 2, 3, 4, 1, 2, 3, 4, 6, 7, 8, 9};
    const uint8_t AdcHclkPresTable[16]    = {1, 2, 4, 6, 8, 10, 12, 16, 32, 32, 32, 32, 32, 32, 32, 32};
    const uint16_t AdcPllClkPresTable[16] = {1, 2, 4, 6, 8, 10, 12, 16, 32, 64, 128, 256, 256, 256, 256, 256};
    
    /* Get PLL clock source, PLL Pre-Divider, PLL out div and multiplication factor ----------------------*/
    pllmull   = RCC->CFG & RCC_CFG_PLLMULFCT;
    pllpre    = RCC->CFG & RCC_CFG_PLLPRE;
    plloutdiv = RCC->CFG & RCC_CFG_PLLOUTDIV;
    pllsource = RCC->CFG & RCC_CFG_PLLSRC;

    pllmull = (pllmull >> 16) + 3;

    if ((pllsource >> 24) == 0x00)
    { 
        /* HSI selected as PLL clock entry */
        pllclk = HSI_VALUE * pllmull;
    }
    else
    {
        /* HSE selected as PLL clock entry */
        pllclk = HSE_VALUE * pllmull;
    }
    
    /* PLL Pre-Divider clock */
    pllpre = (pllpre >> 20) + 1;
    pllclk = pllclk / pllpre;

    /* PLL Out Div clock */
    plloutdiv = (plloutdiv >> 22) + 1;
    pllclk = pllclk / plloutdiv;

    /* Get SYSCLK source -------------------------------------------------------*/
    temp = RCC->CFG & RCC_CFG_SCLKSTS;

    switch (temp)
    {
        case RCC_CFG_SCLKSTS_HSI: /* HSI used as system clock */
            RCC_clocks->SysclkFreq = HSI_VALUE;
            break;
        case RCC_CFG_SCLKSTS_HSE: /* HSE used as system clock */
            RCC_clocks->SysclkFreq = HSE_VALUE;
            break;
        case RCC_CFG_SCLKSTS_PLL: /* PLL used as system clock */
            RCC_clocks->SysclkFreq = pllclk;
            break;
        case RCC_CFG_SCLKSTS_LSI: /* LSI used as system clock */
            RCC_clocks->SysclkFreq = LSI_VALUE;
            break;

        default:
            RCC_clocks->SysclkFreq = HSI_VALUE;
            break;
    }

    /* Compute HCLK, PCLK1, PCLK2 and ADCCLK clocks frequencies ----------------*/
    /* Get HCLK prescaler */
    temp   = RCC->CFG & RCC_CFG_AHBPRES;
    temp   = temp >> 4;
    if(temp < 0x8)
    {
        temp = 0;
    }
    presc = ApbAhbPresTable[temp];
    /* HCLK clock frequency */
    RCC_clocks->HclkFreq = RCC_clocks->SysclkFreq >> presc;
    /* Get PCLK1 prescaler */
    temp   = RCC->CFG & RCC_CFG_APB1PRES;
    temp   = temp >> 8;
    presc = ApbAhbPresTable[temp];
    /* PCLK1 clock frequency */
    RCC_clocks->Pclk1Freq = RCC_clocks->HclkFreq >> presc;
    /* Get PCLK2 prescaler */
    temp   = RCC->CFG & RCC_CFG_APB2PRES;
    temp   = temp >> 11;
    presc = ApbAhbPresTable[temp];
    /* PCLK2 clock frequency */
    RCC_clocks->Pclk2Freq = RCC_clocks->HclkFreq >> presc;

    /* Get ADCHCLK prescaler */
    temp   = RCC->CFG2 & RCC_CFG2_ADCHPRES;
    presc = AdcHclkPresTable[temp];
    /* ADCHCLK clock frequency */
    RCC_clocks->AdcHclkFreq = RCC_clocks->HclkFreq / presc;
    /* Get ADCPLLCLK prescaler */
    temp   = RCC->CFG2 & RCC_CFG2_ADCPLLPRES;
    temp   = temp >> 4;
    presc = AdcPllClkPresTable[(temp & (uint32_t)0xF)]; // ignore BIT5
    /* ADCPLLCLK clock frequency */
    RCC_clocks->AdcPllClkFreq = pllclk / presc;
}

/**
*\*\name    RCC_EnableAHBPeriphClk.
*\*\fun     Enables the AHB peripheral clock.
*\*\param   AHB_periph (AHB peripheral to gates its clock):
*\*\        - RCC_AHB_PERIPH_DMA  
*\*\        - RCC_AHB_PERIPH_SRAM 
*\*\        - RCC_AHB_PERIPH_FLITF
*\*\        - RCC_AHB_PERIPH_CRC  
*\*\        - RCC_AHB_PERIPH_SAC  
*\*\        - RCC_AHB_PERIPH_ADC
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE    
*\*\return  none
**/
void RCC_EnableAHBPeriphClk(uint32_t AHB_periph, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->AHBPCLKEN |= AHB_periph;
    }
    else
    {
        RCC->AHBPCLKEN &= ~AHB_periph;
    }
    
}

/**
*\*\name    RCC_EnableAPB2PeriphClk.
*\*\fun     Enables the High Speed APB (APB2) peripheral clock.
*\*\param   APB2_periph (APB2 peripheral to gates its clock):
*\*\        - RCC_APB2_PERIPH_AFIO 
*\*\        - RCC_APB2_PERIPH_GPIOA 
*\*\        - RCC_APB2_PERIPH_GPIOB 
*\*\        - RCC_APB2_PERIPH_GPIOC 
*\*\        - RCC_APB2_PERIPH_GPIOD 
*\*\        - RCC_APB2_PERIPH_SPI1 
*\*\        - RCC_APB2_PERIPH_SPI2 
*\*\        - RCC_APB2_PERIPH_SPI3 
*\*\        - RCC_APB2_PERIPH_TIM1 
*\*\        - RCC_APB2_PERIPH_TIM2 
*\*\        - RCC_APB2_PERIPH_UART1
*\*\        - RCC_APB2_PERIPH_UART2
*\*\        - RCC_APB2_PERIPH_TIM3 
*\*\        - RCC_APB2_PERIPH_TIM4 
*\*\        - RCC_APB2_PERIPH_TIM5 
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\return none. 
**/
void RCC_EnableAPB2PeriphClk(uint32_t APB2_periph, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->APB2PCLKEN |= APB2_periph;
    }
    else
    {
        RCC->APB2PCLKEN &= ~APB2_periph;
    }
    
}


/**
*\*\name    RCC_EnableAPB1PeriphClk.
*\*\fun     Enables the High Speed APB (APB1) peripheral clock.
*\*\param   APB1_periph (APB1 peripheral to gates its clock):
*\*\        - RCC_APB1_PERIPH_TIM6    
*\*\        - RCC_APB1_PERIPH_BEEP    
*\*\        - RCC_APB1_PERIPH_COMP    
*\*\        - RCC_APB1_PERIPH_COMPFILT
*\*\        - RCC_APB1_PERIPH_LCD     
*\*\        - RCC_APB1_PERIPH_WWDG   
*\*\        - RCC_APB1_PERIPH_UART3   
*\*\        - RCC_APB1_PERIPH_UART4   
*\*\        - RCC_APB1_PERIPH_UART5   
*\*\        - RCC_APB1_PERIPH_I2C1    
*\*\        - RCC_APB1_PERIPH_I2C2    
*\*\        - RCC_APB1_PERIPH_CAN     
*\*\        - RCC_APB1_PERIPH_DAC     
*\*\        - RCC_APB1_PERIPH_PWR  
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE       
*\*\return none. 
**/
void RCC_EnableAPB1PeriphClk(uint32_t APB1_periph, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->APB1PCLKEN |= APB1_periph;
    }
    else
    {
        RCC->APB1PCLKEN &= ~APB1_periph;
    }
    
}

/**
*\*\name    RCC_EnableAHBPeriphReset.
*\*\fun     AHB peripheral reset.
*\*\param   AHB_periph specifies the AHB peripheral to reset.    
*\*\        - RCC_AHB_PERIPH_SAC  
*\*\        - RCC_AHB_PERIPH_ADC 
*\*\return none.
**/
void RCC_EnableAHBPeriphReset(uint32_t AHB_periph)
{
    RCC->AHBPRST |= AHB_periph;
    RCC->AHBPRST &= ~AHB_periph;
}

/**
*\*\name    RCC_EnableAPB2PeriphReset.
*\*\fun     High Speed APB (APB2) peripheral reset.
*\*\param   APB2_periph specifies the APB2 peripheral to reset.
*\*\        - RCC_APB2_PERIPH_AFIO 
*\*\        - RCC_APB2_PERIPH_GPIOA 
*\*\        - RCC_APB2_PERIPH_GPIOB 
*\*\        - RCC_APB2_PERIPH_GPIOC 
*\*\        - RCC_APB2_PERIPH_GPIOD 
*\*\        - RCC_APB2_PERIPH_SPI1 
*\*\        - RCC_APB2_PERIPH_SPI2 
*\*\        - RCC_APB2_PERIPH_SPI3 
*\*\        - RCC_APB2_PERIPH_TIM1 
*\*\        - RCC_APB2_PERIPH_TIM2 
*\*\        - RCC_APB2_PERIPH_UART1
*\*\        - RCC_APB2_PERIPH_UART2
*\*\        - RCC_APB2_PERIPH_TIM3 
*\*\        - RCC_APB2_PERIPH_TIM4 
*\*\        - RCC_APB2_PERIPH_TIM5   
*\*\return none.
**/
void RCC_EnableAPB2PeriphReset(uint32_t APB2_periph)
{
    RCC->APB2PRST |= APB2_periph;
    RCC->APB2PRST &= ~APB2_periph;
}

/**
*\*\name    RCC_EnableAPB1PeriphReset.
*\*\fun     Low Speed APB (APB1) peripheral reset.
*\*\param   APB1_periph specifies the APB1 peripheral to reset.
*\*\        - RCC_APB1_PERIPH_TIM6    
*\*\        - RCC_APB1_PERIPH_BEEP    
*\*\        - RCC_APB1_PERIPH_COMP 
*\*\        - RCC_APB1_PERIPH_LCD     
*\*\        - RCC_APB1_PERIPH_WWDG   
*\*\        - RCC_APB1_PERIPH_UART3   
*\*\        - RCC_APB1_PERIPH_UART4   
*\*\        - RCC_APB1_PERIPH_UART5   
*\*\        - RCC_APB1_PERIPH_I2C1    
*\*\        - RCC_APB1_PERIPH_I2C2    
*\*\        - RCC_APB1_PERIPH_CAN     
*\*\        - RCC_APB1_PERIPH_DAC     
*\*\        - RCC_APB1_PERIPH_PWR       
*\*\return none. 
**/
void RCC_EnableAPB1PeriphReset(uint32_t APB1_periph)
{
    RCC->APB1PRST |= APB1_periph;
    RCC->APB1PRST &= ~APB1_periph;
}

/**
*\*\name   RCC_ConfigMcoClkPre.
*\*\fun    Configures the MCO PLL clock prescaler.
*\*\param  MCO_PLL_prescaler(MCO PLL clock prescaler): 
*\*\        - RCC_MCO_PLLCLK_DIV2 
*\*\        - RCC_MCO_PLLCLK_DIV3 
*\*\        - RCC_MCO_PLLCLK_DIV4 
*\*\        - RCC_MCO_PLLCLK_DIV5 
*\*\        - RCC_MCO_PLLCLK_DIV6 
*\*\        - RCC_MCO_PLLCLK_DIV7 
*\*\        - RCC_MCO_PLLCLK_DIV8 
*\*\        - RCC_MCO_PLLCLK_DIV9 
*\*\        - RCC_MCO_PLLCLK_DIV10
*\*\        - RCC_MCO_PLLCLK_DIV11
*\*\        - RCC_MCO_PLLCLK_DIV12
*\*\        - RCC_MCO_PLLCLK_DIV13
*\*\        - RCC_MCO_PLLCLK_DIV14
*\*\        - RCC_MCO_PLLCLK_DIV15 
*\*\return  none. 
**/
void RCC_ConfigMcoClkPre(uint32_t MCO_PLL_prescaler)
{
    uint32_t temp_value;

    temp_value = RCC->CFG;
    /* Clear MCOPRE[3:0] bits */
    temp_value &= RCC_MCO_PLLCLK_DIV_MASK;
    /* Set MCOPRE[3:0] bits according to MCO_PLL_prescaler value */
    temp_value |= MCO_PLL_prescaler;

    /* Store the new value */
    RCC->CFG = temp_value;
}

/**
*\*\name   RCC_ConfigMco.
*\*\fun    Selects the clock source to output on MCO pin.
*\*\param  MCO_source(clock source to output): 
*\*\     - RCC_MCO_NOCLK      
*\*\     - RCC_MCO_SYSCLK     
*\*\     - RCC_MCO_HSI        
*\*\     - RCC_MCO_HSE       
*\*\     - RCC_MCO_PLLCLK_PRES     
*\*\     - RCC_MCO_LSI    
*\*\return  none. 
**/
void RCC_ConfigMco(uint32_t MCO_source)
{
    uint32_t temp_value;

    temp_value = RCC->CFG;
    /* Clear MCO[2:0] bits */
    temp_value &= RCC_MCO_MASK;
    /* Set MCO[2:0] bits according to MCO_source value */
    temp_value |= MCO_source;

    /* Store the new value */
    RCC->CFG = temp_value;
}

/**
*\*\name    RCC_GetFlagStatus.
*\*\fun     Checks whether the specified RCC flag is set or not.
*\*\param   RCC_flag:
*\*\	      - RCC_CTRL_FLAG_HSIRDF           HSI oscillator clock ready
*\*\	      - RCC_CTRL_FLAG_HSI24MRDF        HSI oscillator clock ready
*\*\          - RCC_CTRL_FLAG_HSERDF           HSE oscillator clock ready
*\*\	      - RCC_CTRL_FLAG_PLLRDF           PLL clock ready
*\*\	      - RCC_LSCTRL_FLAG_LSIRDF         LSI oscillator clock ready
*\*\	      - RCC_CTRLSTS_FLAG_RAMPERRRSTF   RAM parity error reset
*\*\	      - RCC_CTRLSTS_FLAG_MMURSTF       Mmu reset flag
*\*\	      - RCC_CTRLSTS_FLAG_PINRSTF       Pin reset
*\*\	      - RCC_CTRLSTS_FLAG_PORRSTF       POR/PDR reset
*\*\	      - RCC_CTRLSTS_FLAG_SFTRSTF       Software reset
*\*\	      - RCC_CTRLSTS_FLAG_IWDGRSTF      Independent Watchdog reset
*\*\	      - RCC_CTRLSTS_FLAG_WWDGRSTF      Window Watchdog reset
*\*\	      - RCC_CTRLSTS_FLAG_LPWRRSTF      Low Power reset
*\*\	      - RCC_CTRLSTS_FLAG_EMCGBNRSTF    EMCGBN reset
*\*\	      - RCC_CTRLSTS_FLAG_EMCGBRSTF     EMCGB reset
*\*\	      - RCC_CTRLSTS_FLAG_LKUPRSTF      M0 lock up reset
*\*\	      - RCC_CTRLSTS_FLAG_LVRRSTF       LVR reset
*\*\	      - RCC_CFG3_FLAG_LEDCLKDONEF      LED GCLK output Output the full number
*\*\return  FlagStatus:    
*\*\      	  - SET 
*\*\  	      - RESET
**/
FlagStatus RCC_GetFlagStatus(uint8_t RCC_flag)
{
    uint32_t temp_value;
    uint32_t reg_value;
    FlagStatus bitstatus;

    /* Get the RCC register index */
    temp_value = (uint32_t)RCC_flag >> RCC_FLAG_OFFSET;
    switch(temp_value)
    {
        case 1: /* The flag to check is in CTRL register */
            reg_value = RCC->CTRL;
            break;
        case 2: /* The flag to check is in LSCTRL register */
           reg_value = RCC->LSCTRL;
           break;
        case 3:/* The flag to check is in CTRLSTS register */
            reg_value = RCC->CTRLSTS;
            break;
        default:/* The flag to check is in CFG3 register */
            reg_value = RCC->CFG3;
            break;
    }

    /* Get the flag position */
    temp_value = (uint32_t)RCC_flag & RCC_FLAG_MASK;
    if ((reg_value & ((uint32_t)1 << temp_value)) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    return bitstatus;
}

/**
*\*\name    RCC_ClearResetFlag.
*\*\fun     Clears the RCC reset flags.
*\*\param   none
*\*\return  none
*\*\note  Clear the following flags:
*\*\	      - RCC_CTRLSTS_FLAG_RAMPERRRSTF   RAM parity error reset
*\*\	      - RCC_CTRLSTS_FLAG_MMURSTF       Mmu reset flag
*\*\	      - RCC_CTRLSTS_FLAG_PINRSTF       Pin reset
*\*\	      - RCC_CTRLSTS_FLAG_PORRSTF       POR/PDR reset
*\*\	      - RCC_CTRLSTS_FLAG_SFTRSTF       Software reset
*\*\	      - RCC_CTRLSTS_FLAG_IWDGRSTF      Independent Watchdog reset
*\*\	      - RCC_CTRLSTS_FLAG_WWDGRSTF      Window Watchdog reset
*\*\	      - RCC_CTRLSTS_FLAG_LPWRRSTF      Low Power reset
*\*\	      - RCC_CTRLSTS_FLAG_EMCGBNRSTF    EMCGBN reset
*\*\	      - RCC_CTRLSTS_FLAG_EMCGBRSTF     EMCGB reset
*\*\	      - RCC_CTRLSTS_FLAG_LKUPRSTF      M0 lock up reset
*\*\	      - RCC_CTRLSTS_FLAG_LVRRSTF       LVR reset
**/
void RCC_ClearResetFlag(void)
{
    /* Set RMRSTF bit to clear the reset flags */
    RCC->CTRLSTS |= RCC_REMOVE_RESET_FLAG;
    /* RMRSTF bit should be reset */
    RCC->CTRLSTS &= ~RCC_REMOVE_RESET_FLAG;
}

/**
*\*\name    RCC_GetIntStatus.
*\*\fun     Checks whether the specified RCC interrupt has occurred or not.
*\*\param   interrupt_flag(RCC interrupt source to check):
*\*\         - RCC_INT_LSIRDIF    LSI ready interrupt
*\*\         - RCC_INT_HSIRDIF    HSI ready interrupt
*\*\         - RCC_INT_HSERDIF    HSE ready interrupt
*\*\         - RCC_INT_PLLRDIF    PLL ready interrupt
*\*\         - RCC_INT_RAMPERRIF  RAM Parity Error Interrupt 
*\*\         - RCC_INT_CLKSSIF    Clock Security System interrupt in HSE
*\*\return  The new state of RccInt 
*\*\         - SET
*\*\         - RESET
**/
INTStatus RCC_GetIntStatus(uint32_t interrupt_flag)
{
    INTStatus bitstatus;
    /* Check the status of the specified RCC interrupt */
    if ((RCC->CLKINT & interrupt_flag) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    return bitstatus;
}

/**
*\*\name    RCC_ClrIntPendingBit.
*\*\fun     Clears the RCC's interrupt pending bits.
*\*\param   interrupt_clear(interrupt pending bit to clear):
*\*\         - RCC_CLR_LSIRDIF    LSI ready interrupt
*\*\         - RCC_CLR_HSIRDIF    HSI ready interrupt
*\*\         - RCC_CLR_HSERDIF    HSE ready interrupt
*\*\         - RCC_CLR_PLLRDIF    PLL ready interrupt
*\*\         - RCC_CLR_RAMPERRIF  RAM Parity Error Interrupt 
*\*\         - RCC_CLR_CLKSSIF    Clock Security System interrupt in HSE
*\*\return  none
**/
void RCC_ClrIntPendingBit(uint32_t interrupt_clear)
{
    /* Software set this bit to clear INT flag. */
    RCC->CLKINT |= interrupt_clear;
}

/**
*\*\name    RCC_EnableEMCReset.
*\*\fun     Configure whether to generate a reset request when an EMC error occurs.
*\*\param   EMC_type:
*\*\          - GB3
*\*\          - GB2
*\*\          - GB1
*\*\          - GB0
*\*\          - GBN3
*\*\          - GBN2
*\*\          - GBN1
*\*\          - GBN0
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE   
*\*\return  none. 
**/
void RCC_EnableEMCReset(uint32_t EMC_type, FunctionalState Cmd)
{ 
   if (Cmd != DISABLE)
    {
        RCC->EMCCTRL |= (EMC_type<<12);
    }
    else
    {
        RCC->EMCCTRL &= (~(EMC_type<<12));
    }   
}

/**
*\*\name    RCC_EnableEMCDetect.
*\*\fun     Configure whether to enable EMC detection.
*\*\param   EMC_type:
*\*\          - GB3
*\*\          - GB2
*\*\          - GB1
*\*\          - GB0
*\*\          - GBN3
*\*\          - GBN2
*\*\          - GBN1
*\*\          - GBN0
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE   
*\*\return  none. 
**/
void RCC_EnableEMCDetect(uint32_t EMC_type, FunctionalState Cmd)
{ 
   if (Cmd != DISABLE)
    {
        RCC->EMCCTRL |= EMC_type;
    }
    else
    {
        RCC->EMCCTRL &= ~EMC_type;
    }   
}

