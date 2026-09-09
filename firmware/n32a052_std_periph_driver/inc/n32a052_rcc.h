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
*\*\file n32a052_rcc.h
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
 */
#ifndef __n32a052_RCC_H
#define __n32a052_RCC_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "n32a052.h"

/** RCC_Exported_Types **/

typedef struct
{
    uint32_t SysclkFreq;    /* returns SYSCLK clock frequency expressed in Hz */
    uint32_t HclkFreq;      /* returns HCLK clock frequency expressed in Hz */
    uint32_t Pclk1Freq;     /* returns PCLK1 clock frequency expressed in Hz */
    uint32_t Pclk2Freq;     /* returns PCLK2 clock frequency expressed in Hz */
    uint32_t AdcPllClkFreq; /* returns ADCPLLCLK clock frequency expressed in Hz */
    uint32_t AdcHclkFreq;   /* returns ADCHCLK clock frequency expressed in Hz */
} RCC_ClocksType;

typedef enum
{
    SYSCLK_SRC_HSI = 0x00,
    SYSCLK_SRC_HSE = 0x04,
    SYSCLK_SRC_PLL = 0x08
} SysclkSource;



#define RCC_HSI_ENABLE     (RCC_CTRL_HSIEN) 
#define RCC_CLKSS_ENABLE   (RCC_CTRL_CLKSSEN)
#define RCC_PLL_ENABLE     (RCC_CTRL_PLLEN)
#define RCC_PLLOUT_ENABLE  (RCC_CTRL_PLLOUTEN)
#define RCC_LSI_ENABLE     (RCC_LSCTRL_LSIEN)
#define RCC_RTC_ENABLE     (RCC_LSCTRL_RTCEN)



/** RCC_Exported_Constants **/

/** Register shift macro definition **/
#define  RCC_CFG_PLLMULFCT_OFFSET    (REG_BIT18_OFFSET)
#define  RCC_CFG_AHBPRES_OFFSET      (REG_BIT4_OFFSET)
#define  RCC_CFG_APB1PRES_OFFSET     (REG_BIT8_OFFSET)
#define  RCC_CFG_APB2PRES_OFFSET     (REG_BIT11_OFFSET)
#define  RCC_CFG2_ADCPLLPRES_OFFSET  (REG_BIT4_OFFSET)
#define  RCC_FLAG_OFFSET             (REG_BIT5_OFFSET)
#define  RCC_CTRL_HSITRIM_OFFSET     (REG_BIT4_OFFSET)
#define  RCC_LSCTRL_LSITRIM_OFFSET   (REG_BIT2_OFFSET)
#define  RCC_APB2PRES_OFFSET         (REG_BIT3_OFFSET)
#define  RCC_CFG3_GCLKMNUM_OFFSET    (REG_BIT16_OFFSET)
#define  RCC_CFG3_GCLKNNUM_OFFSET    (REG_BIT24_OFFSET)

/** RCC R_BIT_MASK **/
#define RCC_REG_BIT_MASK  ((uint32_t)0x00000000)

/** HSE_configuration **/
#define RCC_HSE_DISABLE  (RCC_REG_BIT_MASK)
#define RCC_HSE_ENABLE   (RCC_CTRL_HSEEN)
#define RCC_HSE_BYPASS   (RCC_CTRL_HSEBP)

/** HSE delay configuration **/
#define RCC_HSE_READY_DELAY_MASK   (~RCC_CTRL_HSERDTIM)
#define RCC_HSE_READY_DELAY_0_5ms  (RCC_CTRL_HSERDTIM_0_5MS)
#define RCC_HSE_READY_DELAY_1_0ms  (RCC_CTRL_HSERDTIM_1_0MS)
#define RCC_HSE_READY_DELAY_1_5ms  (RCC_CTRL_HSERDTIM_1_5MS)
#define RCC_HSE_READY_DELAY_2_5ms  (RCC_CTRL_HSERDTIM_2_5MS)

/** Internal High Speed clock trimming **/
#define RCC_HSITRIM_MASK (~RCC_CTRL_HSITRIM)
/** Internal Low Speed clock trimming **/
#define RCC_LSITRIM_MASK (~RCC_LSCTRL_LSITRIM)

/** RAM parity error reset enable **/
#define RCC_RAMPERRRST_ENABLE (RCC_CLKINT_RAMPERRRSTEN)

/** M0 lockup reset enable **/
#define RCC_LKUPRST_ENABLE (RCC_CTRL_LKUPRSTEN)

/** PLL Mask **/
#define RCC_PLL_MASK        (~(RCC_CFG_PLLSRC | RCC_CFG_PLLPRE | RCC_CFG_PLLMULFCT| RCC_CFG_PLLOUTDIV)) 

/** PLL_entry_clock_source **/
#define RCC_PLL_SRC_HSI (RCC_CFG_PLLSRC_HSI)
#define RCC_PLL_SRC_HSE (RCC_CFG_PLLSRC_HSE)

#define RCC_PLL_PRE_1  (RCC_CFG_PLLPREDIV1)
#define RCC_PLL_PRE_2  (RCC_CFG_PLLPREDIV2)
#define RCC_PLL_PRE_3  (RCC_CFG_PLLPREDIV3)
#define RCC_PLL_PRE_4  (RCC_CFG_PLLPREDIV4)

/** PLL_multiplication_factor **/
#define RCC_PLL_MUL_BP  (RCC_CTRL_PLLBP)
#define RCC_PLL_MUL_3   (RCC_CFG_PLLMULFCT3)
#define RCC_PLL_MUL_4   (RCC_CFG_PLLMULFCT4)
#define RCC_PLL_MUL_5   (RCC_CFG_PLLMULFCT5)
#define RCC_PLL_MUL_6   (RCC_CFG_PLLMULFCT6)
#define RCC_PLL_MUL_7   (RCC_CFG_PLLMULFCT7)
#define RCC_PLL_MUL_8   (RCC_CFG_PLLMULFCT8)
#define RCC_PLL_MUL_9   (RCC_CFG_PLLMULFCT9)
#define RCC_PLL_MUL_10  (RCC_CFG_PLLMULFCT10)
#define RCC_PLL_MUL_11  (RCC_CFG_PLLMULFCT11)
#define RCC_PLL_MUL_12  (RCC_CFG_PLLMULFCT12)
#define RCC_PLL_MUL_13  (RCC_CFG_PLLMULFCT13)
#define RCC_PLL_MUL_14  (RCC_CFG_PLLMULFCT14)
#define RCC_PLL_MUL_15  (RCC_CFG_PLLMULFCT15)
#define RCC_PLL_MUL_16  (RCC_CFG_PLLMULFCT16)
#define RCC_PLL_MUL_17  (RCC_CFG_PLLMULFCT17)
#define RCC_PLL_MUL_18  (RCC_CFG_PLLMULFCT18)

#define RCC_PLLOUT_DIV_1  (RCC_CFG_PLLOUTDIV1)
#define RCC_PLLOUT_DIV_2  (RCC_CFG_PLLOUTDIV2)
#define RCC_PLLOUT_DIV_3  (RCC_CFG_PLLOUTDIV3)
#define RCC_PLLOUT_DIV_4  (RCC_CFG_PLLOUTDIV4)

/** System_clock_source **/
#define RCC_SYSCLK_SRC_MASK    (~RCC_CFG_SCLKSW)
#define RCC_SYSCLK_SRC_HSI     (RCC_CFG_SCLKSW_HSI)
#define RCC_SYSCLK_SRC_HSE     (RCC_CFG_SCLKSW_HSE)
#define RCC_SYSCLK_SRC_PLLCLK  (RCC_CFG_SCLKSW_PLL)
#define RCC_SYSCLK_SRC_LSI     (RCC_CFG_SCLKSW_LSI)

/** System_clock_status mask **/
#define RCC_SYSCLK_STS_MASK    (RCC_CFG_SCLKSTS)

/** AHB_clock_source **/
#define RCC_SYSCLK_DIV_MASK (~RCC_CFG_AHBPRES)
#define RCC_SYSCLK_DIV1     (RCC_CFG_AHBPRES_DIV1)
#define RCC_SYSCLK_DIV2     (RCC_CFG_AHBPRES_DIV2)
#define RCC_SYSCLK_DIV4     (RCC_CFG_AHBPRES_DIV4)
#define RCC_SYSCLK_DIV8     (RCC_CFG_AHBPRES_DIV8)
#define RCC_SYSCLK_DIV16    (RCC_CFG_AHBPRES_DIV16)
#define RCC_SYSCLK_DIV64    (RCC_CFG_AHBPRES_DIV64)
#define RCC_SYSCLK_DIV128   (RCC_CFG_AHBPRES_DIV128)
#define RCC_SYSCLK_DIV256   (RCC_CFG_AHBPRES_DIV256)
#define RCC_SYSCLK_DIV512   (RCC_CFG_AHBPRES_DIV512)

/** APB1_APB2_clock_source **/
#define RCC_APB1_DIV_MASK   (~RCC_CFG_APB1PRES)
#define RCC_APB2_DIV_MASK   (~RCC_CFG_APB2PRES)
#define RCC_HCLK_DIV1       (RCC_CFG_APB1PRES_DIV1)
#define RCC_HCLK_DIV2       (RCC_CFG_APB1PRES_DIV2)
#define RCC_HCLK_DIV4       (RCC_CFG_APB1PRES_DIV4)
#define RCC_HCLK_DIV8       (RCC_CFG_APB1PRES_DIV8)
#define RCC_HCLK_DIV16      (RCC_CFG_APB1PRES_DIV16)

/** RCC_CFG2_Config **/
#define RCC_TIM1_CLKSRC_MASK      (~RCC_CFG2_TIM1CLKSEL) 
#define RCC_TIM1_CLKSRC_PCLK      (RCC_CFG2_TIM1CLKSEL_PCLK)
#define RCC_TIM1_CLKSRC_SYSCLK    (RCC_CFG2_TIM1CLKSEL_SYSCLK)

#define RCC_TIM6_CLKSRC_MASK      (~RCC_CFG2_TIM6CLKSEL) 
#define RCC_TIM6_CLKSRC_PCLK      (RCC_CFG2_TIM6CLKSEL_PCLK)
#define RCC_TIM6_CLKSRC_LSI       (RCC_CFG2_TIM6CLKSEL_LSI)

#define RCC_LCD_CLKSRC_MASK       (~RCC_CFG2_LCDCLKSEL) 
#define RCC_LCD_CLKSRC_HSI_DIV8   (RCC_CFG2_LCDCLKSEL_HSI)
#define RCC_LCD_CLKSRC_HSE_DIV16  (RCC_CFG2_LCDCLKSEL_HSE)

#define RCC_ADC1MCLK_SRC_MASK     (~RCC_CFG2_ADC1MSEL)
#define RCC_ADC1MCLK_SRC_HSI      (RCC_CFG2_ADC1MSEL_HSI)
#define RCC_ADC1MCLK_SRC_HSE      (RCC_CFG2_ADC1MSEL_HSE)

#define RCC_ADC1MCLK_DIV_MASK  (~RCC_CFG2_ADC1MPRES)
#define RCC_ADC1MCLK_DIV1      (RCC_CFG2_ADC1MPRES_DIV1)
#define RCC_ADC1MCLK_DIV2      (RCC_CFG2_ADC1MPRES_DIV2)
#define RCC_ADC1MCLK_DIV3      (RCC_CFG2_ADC1MPRES_DIV3)
#define RCC_ADC1MCLK_DIV4      (RCC_CFG2_ADC1MPRES_DIV4)
#define RCC_ADC1MCLK_DIV5      (RCC_CFG2_ADC1MPRES_DIV5)
#define RCC_ADC1MCLK_DIV6      (RCC_CFG2_ADC1MPRES_DIV6)
#define RCC_ADC1MCLK_DIV7      (RCC_CFG2_ADC1MPRES_DIV7)
#define RCC_ADC1MCLK_DIV8      (RCC_CFG2_ADC1MPRES_DIV8)
#define RCC_ADC1MCLK_DIV9      (RCC_CFG2_ADC1MPRES_DIV9)
#define RCC_ADC1MCLK_DIV10     (RCC_CFG2_ADC1MPRES_DIV10)
#define RCC_ADC1MCLK_DIV11     (RCC_CFG2_ADC1MPRES_DIV11)
#define RCC_ADC1MCLK_DIV12     (RCC_CFG2_ADC1MPRES_DIV12)
#define RCC_ADC1MCLK_DIV13     (RCC_CFG2_ADC1MPRES_DIV13)
#define RCC_ADC1MCLK_DIV14     (RCC_CFG2_ADC1MPRES_DIV14)
#define RCC_ADC1MCLK_DIV15     (RCC_CFG2_ADC1MPRES_DIV15)
#define RCC_ADC1MCLK_DIV16     (RCC_CFG2_ADC1MPRES_DIV16)
#define RCC_ADC1MCLK_DIV17     (RCC_CFG2_ADC1MPRES_DIV17)
#define RCC_ADC1MCLK_DIV18     (RCC_CFG2_ADC1MPRES_DIV18)
#define RCC_ADC1MCLK_DIV19     (RCC_CFG2_ADC1MPRES_DIV19)
#define RCC_ADC1MCLK_DIV20     (RCC_CFG2_ADC1MPRES_DIV20)
#define RCC_ADC1MCLK_DIV21     (RCC_CFG2_ADC1MPRES_DIV21)
#define RCC_ADC1MCLK_DIV22     (RCC_CFG2_ADC1MPRES_DIV22)
#define RCC_ADC1MCLK_DIV23     (RCC_CFG2_ADC1MPRES_DIV23)
#define RCC_ADC1MCLK_DIV24     (RCC_CFG2_ADC1MPRES_DIV24)
#define RCC_ADC1MCLK_DIV25     (RCC_CFG2_ADC1MPRES_DIV25)
#define RCC_ADC1MCLK_DIV26     (RCC_CFG2_ADC1MPRES_DIV26)
#define RCC_ADC1MCLK_DIV27     (RCC_CFG2_ADC1MPRES_DIV27)
#define RCC_ADC1MCLK_DIV28     (RCC_CFG2_ADC1MPRES_DIV28)
#define RCC_ADC1MCLK_DIV29     (RCC_CFG2_ADC1MPRES_DIV29)
#define RCC_ADC1MCLK_DIV30     (RCC_CFG2_ADC1MPRES_DIV30)
#define RCC_ADC1MCLK_DIV31     (RCC_CFG2_ADC1MPRES_DIV31)
#define RCC_ADC1MCLK_DIV32     (RCC_CFG2_ADC1MPRES_DIV32)

#define RCC_ADC_CLKSRC_MASK    (~RCC_CFG2_ADCCLKSEL)
#define RCC_ADC_CLKSRC_HSI24M  (RCC_CFG2_ADCCLKSEL_HSI24M )   
#define RCC_ADC_CLKSRC_HCLK    (RCC_CFG2_ADCCLKSEL_HCLK)   
#define RCC_ADC_CLKSRC_PLL     (RCC_CFG2_ADCCLKSEL_PLL )  

#define RCC_ADCPLLCLK_MASK       (~RCC_CFG2_ADCPLLPRES)
#define RCC_ADCPLLCLK_DISABLE    (RCC_CFG2_ADCPLLCLK_DISABLE)
#define RCC_ADCPLLCLK_DIV1       (RCC_CFG2_ADCPLLPRES_DIV1)
#define RCC_ADCPLLCLK_DIV2       (RCC_CFG2_ADCPLLPRES_DIV2)
#define RCC_ADCPLLCLK_DIV4       (RCC_CFG2_ADCPLLPRES_DIV4)
#define RCC_ADCPLLCLK_DIV6       (RCC_CFG2_ADCPLLPRES_DIV6)
#define RCC_ADCPLLCLK_DIV8       (RCC_CFG2_ADCPLLPRES_DIV8)
#define RCC_ADCPLLCLK_DIV10      (RCC_CFG2_ADCPLLPRES_DIV10)
#define RCC_ADCPLLCLK_DIV12      (RCC_CFG2_ADCPLLPRES_DIV12)
#define RCC_ADCPLLCLK_DIV16      (RCC_CFG2_ADCPLLPRES_DIV16)
#define RCC_ADCPLLCLK_DIV32      (RCC_CFG2_ADCPLLPRES_DIV32)
#define RCC_ADCPLLCLK_DIV64      (RCC_CFG2_ADCPLLPRES_DIV64)
#define RCC_ADCPLLCLK_DIV128     (RCC_CFG2_ADCPLLPRES_DIV128)
#define RCC_ADCPLLCLK_DIV256     (RCC_CFG2_ADCPLLPRES_DIV256)
#define RCC_ADCPLLCLK_DIV_OTHERS (RCC_CFG2_ADCPLLPRES_DIV256N)

#define RCC_ADCHCLK_DIV_MASK   (~RCC_CFG2_ADCHPRES)
#define RCC_ADCHCLK_DIV1       (RCC_CFG2_ADCHPRES_DIV1)
#define RCC_ADCHCLK_DIV2       (RCC_CFG2_ADCHPRES_DIV2)
#define RCC_ADCHCLK_DIV4       (RCC_CFG2_ADCHPRES_DIV4)
#define RCC_ADCHCLK_DIV6       (RCC_CFG2_ADCHPRES_DIV6)
#define RCC_ADCHCLK_DIV8       (RCC_CFG2_ADCHPRES_DIV8)
#define RCC_ADCHCLK_DIV10      (RCC_CFG2_ADCHPRES_DIV10)
#define RCC_ADCHCLK_DIV12      (RCC_CFG2_ADCHPRES_DIV12)
#define RCC_ADCHCLK_DIV16      (RCC_CFG2_ADCHPRES_DIV16)
#define RCC_ADCHCLK_DIV32      (RCC_CFG2_ADCHPRES_DIV32)
#define RCC_ADCHCLK_DIV_OTHERS (RCC_CFG2_ADCHPRES_OTHERS)

/** RCC_CFG3_Config **/

#define RCC_LEDCLK_ENABLE       (RCC_CFG3_GCLKEN)
#define RCC_LED_DMAREQ_ENABLE   (RCC_CFG3_GCLKDMAEN)

#define RCC_LEDCLK_SRC_MASK     (~RCC_CFG3_GCLKSEL)
#define RCC_LEDCLK_SRC_HSI      (RCC_CFG3_GCLKSEL_HSI)
#define RCC_LEDCLK_SRC_HSE      (RCC_CFG3_GCLKSEL_HSE)

#define RCC_LEDCLK_DIV_MASK  (~RCC_CFG3_GCLKPRES)
#define RCC_LEDCLK_DISABLE   (RCC_CFG3_GCLKPRES_DISABLE)  
#define RCC_LEDCLK_DIV32     (RCC_CFG3_GCLKPRES_DIV32) 
#define RCC_LEDCLK_DIV40     (RCC_CFG3_GCLKPRES_DIV40) 
#define RCC_LEDCLK_DIV50     (RCC_CFG3_GCLKPRES_DIV50) 
#define RCC_LEDCLK_DIV64     (RCC_CFG3_GCLKPRES_DIV64) 
#define RCC_LEDCLK_DIV80     (RCC_CFG3_GCLKPRES_DIV80)
#define RCC_LEDCLK_DIV160    (RCC_CFG3_GCLKPRES_DIV160)

#define RCC_MIN_GCLKMNUM     (0x1U)
#define RCC_MIN_GCLKNNUM     (0x1U)

#define RCC_GCLKMNUM_MASK  (~RCC_CFG3_GCLKMNUM)
#define RCC_GCLKNNUM_MASK  (~RCC_CFG3_GCLKNNUM)
/** RCC_LSCTRL_Config **/

/** RTC_clock_source **/
#define RCC_RTCCLK_SRC_MASK        (~RCC_LSCTRL_RTCSEL)
#define RCC_RTCCLK_SRC_NONE        (RCC_LSCTRL_RTCSEL_NOCLOCK)
#define RCC_RTCCLK_SRC_LSI         (RCC_LSCTRL_RTCSEL_LSI)
#define RCC_RTCCLK_SRC_HSE_DIV128  (RCC_LSCTRL_RTCSEL_HSE)
#define RCC_RTCCLK_SRC_HSI_DIV128  (RCC_LSCTRL_RTCSEL_HSI)

#define RCC_RTCCLK_RESET           (RCC_LSCTRL_RTCRST)

/** AHB_peripheral **/
#define RCC_AHB_PERIPH_DMA    (RCC_AHBPCLKEN_DMAEN)
#define RCC_AHB_PERIPH_SRAM   (RCC_AHBPCLKEN_SRAMEN)
#define RCC_AHB_PERIPH_FLITF  (RCC_AHBPCLKEN_FLITFEN)
#define RCC_AHB_PERIPH_CRC    (RCC_AHBPCLKEN_CRCEN)
#define RCC_AHB_PERIPH_SAC    (RCC_AHBPCLKEN_SACEN)
#define RCC_AHB_PERIPH_ADC    (RCC_AHBPCLKEN_ADCEN)

/** APB2_peripheral **/
#define RCC_APB2_PERIPH_AFIO     (RCC_APB2PCLKEN_AFIOEN)  
#define RCC_APB2_PERIPH_GPIOA    (RCC_APB2PCLKEN_IOPAEN)  
#define RCC_APB2_PERIPH_GPIOB    (RCC_APB2PCLKEN_IOPBEN)  
#define RCC_APB2_PERIPH_GPIOC    (RCC_APB2PCLKEN_IOPCEN)  
#define RCC_APB2_PERIPH_GPIOD    (RCC_APB2PCLKEN_IOPDEN)  
#define RCC_APB2_PERIPH_SPI1     (RCC_APB2PCLKEN_SPI1EN)  
#define RCC_APB2_PERIPH_SPI2     (RCC_APB2PCLKEN_SPI2EN)  
#define RCC_APB2_PERIPH_SPI3     (RCC_APB2PCLKEN_SPI3EN)  
#define RCC_APB2_PERIPH_TIM1     (RCC_APB2PCLKEN_TIM1EN)  
#define RCC_APB2_PERIPH_TIM2     (RCC_APB2PCLKEN_TIM2EN)  
#define RCC_APB2_PERIPH_UART1    (RCC_APB2PCLKEN_UART1EN)
#define RCC_APB2_PERIPH_UART2    (RCC_APB2PCLKEN_UART2EN)
#define RCC_APB2_PERIPH_TIM3     (RCC_APB2PCLKEN_TIM3EN)  
#define RCC_APB2_PERIPH_TIM4     (RCC_APB2PCLKEN_TIM4EN)  
#define RCC_APB2_PERIPH_TIM5     (RCC_APB2PCLKEN_TIM5EN)  

/** APB1_peripheral **/
#define RCC_APB1_PERIPH_TIM6      (RCC_APB1PCLKEN_TIM6EN)   
#define RCC_APB1_PERIPH_BEEP      (RCC_APB1PCLKEN_BEEPEN)   
#define RCC_APB1_PERIPH_COMP      (RCC_APB1PCLKEN_COMPEN)   
#define RCC_APB1_PERIPH_COMPFILT  (RCC_APB1PCLKEN_COMPFILTEN)
#define RCC_APB1_PERIPH_LCD       (RCC_APB1PCLKEN_LCDEN)   
#define RCC_APB1_PERIPH_WWDG      (RCC_APB1PCLKEN_WWDGEN)  
#define RCC_APB1_PERIPH_UART3     (RCC_APB1PCLKEN_UART3EN)   
#define RCC_APB1_PERIPH_UART4     (RCC_APB1PCLKEN_UART4EN)   
#define RCC_APB1_PERIPH_UART5     (RCC_APB1PCLKEN_UART5EN)   
#define RCC_APB1_PERIPH_I2C1      (RCC_APB1PCLKEN_I2C1EN)   
#define RCC_APB1_PERIPH_I2C2      (RCC_APB1PCLKEN_I2C2EN)   
#define RCC_APB1_PERIPH_CAN       (RCC_APB1PCLKEN_CANEN)   
#define RCC_APB1_PERIPH_DAC       (RCC_APB1PCLKEN_DACEN)   
#define RCC_APB1_PERIPH_PWR       (RCC_APB1PCLKEN_PWREN)   

/** MCO_PLL_prescaler **/
#define RCC_MCO_PLLCLK_DIV_MASK  (~RCC_CFG_MCOPRES)
#define RCC_MCO_PLLCLK_DIV2      (RCC_CFG_MCOPRES_PLLDIV2)
#define RCC_MCO_PLLCLK_DIV3      (RCC_CFG_MCOPRES_PLLDIV3)
#define RCC_MCO_PLLCLK_DIV4      (RCC_CFG_MCOPRES_PLLDIV4)
#define RCC_MCO_PLLCLK_DIV5      (RCC_CFG_MCOPRES_PLLDIV5)
#define RCC_MCO_PLLCLK_DIV6      (RCC_CFG_MCOPRES_PLLDIV6)
#define RCC_MCO_PLLCLK_DIV7      (RCC_CFG_MCOPRES_PLLDIV7)
#define RCC_MCO_PLLCLK_DIV8      (RCC_CFG_MCOPRES_PLLDIV8)
#define RCC_MCO_PLLCLK_DIV9      (RCC_CFG_MCOPRES_PLLDIV9)
#define RCC_MCO_PLLCLK_DIV10     (RCC_CFG_MCOPRES_PLLDIV10)
#define RCC_MCO_PLLCLK_DIV11     (RCC_CFG_MCOPRES_PLLDIV11)
#define RCC_MCO_PLLCLK_DIV12     (RCC_CFG_MCOPRES_PLLDIV12)
#define RCC_MCO_PLLCLK_DIV13     (RCC_CFG_MCOPRES_PLLDIV13)
#define RCC_MCO_PLLCLK_DIV14     (RCC_CFG_MCOPRES_PLLDIV14)
#define RCC_MCO_PLLCLK_DIV15     (RCC_CFG_MCOPRES_PLLDIV15)

/** Clock_source_to_output_on_MCO_pin **/
#define RCC_MCO_MASK          (~RCC_CFG_MCO)
#define RCC_MCO_NOCLK         (RCC_CFG_MCO_NOCLK)
#define RCC_MCO_SYSCLK        (RCC_CFG_MCO_SYSCLK)
#define RCC_MCO_HSI           (RCC_CFG_MCO_HSI)
#define RCC_MCO_HSE           (RCC_CFG_MCO_HSE)
#define RCC_MCO_PLLCLK_PRES   (RCC_CFG_MCO_PLL)
#define RCC_MCO_LSI           (RCC_CFG_MCO_LSI)


/** RCC_Flag **/
#define RCC_FLAG_MASK                 ((uint8_t)0x1F)
#define RCC_CTRL_FLAG_HSIRDF          ((uint8_t)0x21)  
#define RCC_CTRL_FLAG_HSI24MRDF       ((uint8_t)0x22) 
#define RCC_CTRL_FLAG_HSERDF          ((uint8_t)0x31)
#define RCC_CTRL_FLAG_PLLRDF          ((uint8_t)0x39)
#define RCC_LSCTRL_FLAG_LSIRDF        ((uint8_t)0x41)
#define RCC_CTRLSTS_FLAG_RAMPERRRSTF  ((uint8_t)0x61)
#define RCC_CTRLSTS_FLAG_MMURSTF      ((uint8_t)0x62)
#define RCC_CTRLSTS_FLAG_PINRSTF      ((uint8_t)0x63)
#define RCC_CTRLSTS_FLAG_PORRSTF      ((uint8_t)0x64)
#define RCC_CTRLSTS_FLAG_SFTRSTF      ((uint8_t)0x65)
#define RCC_CTRLSTS_FLAG_IWDGRSTF     ((uint8_t)0x66)
#define RCC_CTRLSTS_FLAG_WWDGRSTF     ((uint8_t)0x67)
#define RCC_CTRLSTS_FLAG_LPWRRSTF     ((uint8_t)0x68)
#define RCC_CTRLSTS_FLAG_EMCGBNRSTF   ((uint8_t)0x69)
#define RCC_CTRLSTS_FLAG_EMCGBRSTF    ((uint8_t)0x6A)
#define RCC_CTRLSTS_FLAG_LKUPRSTF     ((uint8_t)0x6B)
#define RCC_CTRLSTS_FLAG_LVRRSTF      ((uint8_t)0x7D)
#define RCC_CFG3_FLAG_LEDCLKDONEF     ((uint8_t)0x82)

/** RCC_Flag **/
#define RCC_REMOVE_RESET_FLAG (RCC_CTRLSTS_RMRSTF)

/** RCC_Interrupt_source **/
/** Interrupts Flag **/
#define RCC_INT_LSIRDIF    (RCC_CLKINT_LSIRDIF )
#define RCC_INT_HSIRDIF    (RCC_CLKINT_HSIRDIF)
#define RCC_INT_HSERDIF    (RCC_CLKINT_HSERDIF)
#define RCC_INT_PLLRDIF    (RCC_CLKINT_PLLRDIF)
#define RCC_INT_RAMPERRIF  (RCC_CLKINT_RAMPERRIF)
#define RCC_INT_CLKSSIF    (RCC_CLKINT_CLKSSIF)

/** Interrupts Clear **/
#define RCC_CLR_LSIRDIF    (RCC_CLKINT_LSIRDICLR)
#define RCC_CLR_HSIRDIF    (RCC_CLKINT_HSIRDICLR)
#define RCC_CLR_HSERDIF    (RCC_CLKINT_HSERDICLR)
#define RCC_CLR_PLLRDIF    (RCC_CLKINT_PLLRDICLR)
#define RCC_CLR_RAMPERRIF  (RCC_CLKINT_RAMPERRICLR)
#define RCC_CLR_CLKSSIF    (RCC_CLKINT_CLKSSICLR)

#define GB3      (RCC_EMCCTRL_GBDET3EN)
#define GB2      (RCC_EMCCTRL_GBDET2EN)
#define GB1      (RCC_EMCCTRL_GBDET1EN)
#define GB0      (RCC_EMCCTRL_GBDET0EN)
#define GBN3     (RCC_EMCCTRL_GBNDET3EN)
#define GBN2     (RCC_EMCCTRL_GBNDET2EN)
#define GBN1     (RCC_EMCCTRL_GBNDET1EN)
#define GBN0     (RCC_EMCCTRL_GBNDET0EN)

void RCC_DeInit(void);
void RCC_ConfigHse(uint32_t RCC_HSE);
ErrorStatus RCC_WaitHseStable(void);
void RCC_SetHseReadyDelay(uint32_t delay_value);
void RCC_EnableClockSecuritySystem(FunctionalState Cmd);
void RCC_SetHsiCalibValue(uint8_t calibration_value);
void RCC_EnableHsi(FunctionalState Cmd);
ErrorStatus RCC_WaitHsiStable(void);
void RCC_ConfigPll(uint32_t PLL_source, uint32_t PLL_multiplication, uint32_t  PLL_prescaler,  uint32_t PLL_outdivider);
void RCC_EnablePll(FunctionalState Cmd);
void RCC_EnablePllClockOut(FunctionalState Cmd);
void RCC_ConfigSysclk(uint32_t sysclk_source);
uint32_t RCC_GetSysclkSrc(void);
void RCC_ConfigHclk(uint32_t sysclk_div);
void RCC_ConfigPclk1(uint32_t hclk_div);
void RCC_ConfigPclk2(uint32_t hclk_div);
void RCC_ConfigInt(uint32_t Interrupt, FunctionalState Cmd);
void RCC_ConfigTim1Clk(uint32_t timer1_clksrc);
void RCC_ConfigTim6Clk(uint32_t timer6_clksrc);
void RCC_ConfigLCDClk(uint32_t lcd_clksrc);
void RCC_ConfigAdc1mClk(uint32_t ADC1M_clksrc, uint32_t ADC1M_prescaler);
void RCC_ConfigADCClksrc(uint32_t adc_clksrc);
void RCC_ConfigAdcPllClk(uint32_t ADC_PLLCLK_prescaler, FunctionalState Cmd);
void RCC_ConfigAdcHclk(uint32_t ADC_hclk_prescaler);
void RCC_EnableLsi(FunctionalState Cmd);
void RCC_SetLsiCalibValue(uint8_t calibration_value);
ErrorStatus RCC_WaitLsiStable(void);
void RCC_ConfigRtcClk(uint32_t rtcclk_source);
void RCC_EnableRtcClk(FunctionalState Cmd);
void RCC_EnableRTCReset(void);
void RCC_EnableLockupReset(FunctionalState Cmd);
void RCC_EnableRAMParityErrorReset(FunctionalState Cmd);
void RCC_EnableLEDClk(FunctionalState Cmd);
void RCC_ConfigLEDClk(uint32_t LED_clksrc, uint32_t LED_prescaler);
void RCC_EnableLEDDMARequest(FunctionalState Cmd);
void RCC_SetLEDLowLevelCycles(uint8_t cycles_value);
void RCC_SetLEDClockCycles(uint8_t cycles_value);
void RCC_ConfigALL_LED_GCLK(FunctionalState Gclk_Cmd, uint32_t LED_clksrc, uint32_t LED_prescaler, \
							FunctionalState GclkDma_Cmd, uint8_t mcycles_value, uint8_t ncycles_value);
void RCC_GetClocksFreqValue(RCC_ClocksType* RCC_clocks);
void RCC_EnableAHBPeriphClk(uint32_t AHB_periph, FunctionalState Cmd);
void RCC_EnableAPB2PeriphClk(uint32_t APB2_periph, FunctionalState Cmd);
void RCC_EnableAPB1PeriphClk(uint32_t APB1_periph, FunctionalState Cmd);
void RCC_EnableAHBPeriphReset(uint32_t AHB_periph);
void RCC_EnableAPB2PeriphReset(uint32_t APB2_periph);
void RCC_EnableAPB1PeriphReset(uint32_t APB1_periph);
void RCC_ConfigMcoClkPre(uint32_t MCO_PLL_prescaler);
void RCC_ConfigMco(uint32_t MCO_source);
FlagStatus RCC_GetFlagStatus(uint8_t RCC_flag);
void RCC_ClearResetFlag(void);
INTStatus RCC_GetIntStatus(uint32_t interrupt_flag);
void RCC_ClrIntPendingBit(uint32_t interrupt_clear);
void RCC_EnableEMCReset(uint32_t EMC_type, FunctionalState Cmd);
void RCC_EnableEMCDetect(uint32_t EMC_type, FunctionalState Cmd);

#ifdef __cplusplus
}
#endif

#endif /* __N32A052_RCC_H__ */


