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
 * @file main.c
 * @author Nations 
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
 */
#include "main.h"
#include "log.h"
#include "delay.h"

/*xx mv per degree Celsius  by datasheet define*/
#define AVG_SLOPE  0.0039f

#define  TS_VALUE_ADDR   (0x1FFFF930U)

//#define VDDA_5V    1

#ifdef  VDDA_5V
#define  VREF_VALUE      (4.39)    //this value need be configured by the actual voltage reference. 
#define  VTS_CODE_ADDR   (0x1FFFF9D8U)
#else
#define  VREF_VALUE      (3.3)
#define  VTS_CODE_ADDR   (0x1FFFF928U)

#endif

ADC_InitType ADC_InitStructure;
DMA_InitType DMA_InitStructure;
__IO uint16_t ADCConvertedValue = 0;
__IO float TempValue;

void RCC_Configuration(void);
float TempCal(uint16_t TempAdVal);

/**
*\*\name    ADC_Initial.
*\*\fun     ADC_Initial program.
*\*\return  none
**/
void ADC_Initial(void)
{

    /* DMA channel1 configuration ----------------------------------------------*/
    DMA_DeInit(DMA_CH1);
    DMA_InitStructure.PeriphAddr     = (uint32_t)&ADC->DAT0;
    DMA_InitStructure.MemAddr        = (uint32_t)&ADCConvertedValue;
    DMA_InitStructure.Direction      = DMA_DIR_PERIPH_SRC;
    DMA_InitStructure.BufSize        = 500;
    DMA_InitStructure.PeriphInc      = DMA_PERIPH_INC_DISABLE;
    DMA_InitStructure.DMA_MemoryInc  = DMA_MEM_INC_DISABLE;
    DMA_InitStructure.PeriphDataSize = DMA_PERIPH_DATA_SIZE_HALFWORD;
    DMA_InitStructure.MemDataSize    = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.CircularMode   = DMA_MODE_CIRCULAR;
    DMA_InitStructure.Priority       = DMA_PRIORITY_HIGH;
    DMA_InitStructure.Mem2Mem        = DMA_M2M_DISABLE;
    DMA_Init(DMA_CH1, &DMA_InitStructure);
    DMA_RequestRemap(DMA_REMAP_ADC, DMA, DMA_CH1, ENABLE);
    
    /* Enable DMA channel1 */
    DMA_EnableChannel(DMA_CH1, ENABLE);
    
    ADC_InitStruct(&ADC_InitStructure);
    ADC_DeInit();
    /* ADC configuration ------------------------------------------------------*/
    ADC_InitStructure.MultiChEn      = DISABLE;
    ADC_InitStructure.ContinueConvEn = ENABLE;
    ADC_InitStructure.ExtTrigSelect  = ADC_EXT_TRIGCONV_REGULAR_SWSTRRCH;
    ADC_InitStructure.DatAlign       = ADC_DAT_ALIGN_R;
    ADC_InitStructure.ChsNumber      = ADC_REGULAR_LEN_1;
    ADC_Init(&ADC_InitStructure);
        
    /* Enable ADC DMA */
    ADC_EnableDMA(ENABLE);
        
    /* ADC enable temper sensor  */
    ADC_EnableTempSensor(ENABLE);
    /*ADC_Regular_Sequence_Single_Config  ADC_CH_TS */
    ADC_ConfigRegularSequenceSingle(ADC_CH_TS);
    /* Configure channel sample time ----------------------*/
    ADC_ConfigChannelSampleTime(ADC_SAMP_TIME_380CYCLES);

    /* Enable ADC */
    ADC_Enable(ENABLE);
    /* Check ADC Ready */
    while(ADC_GetFlagStatusNew(ADC_FLAG_RDY) == RESET)
        ;
    /* Start ADC Software Conversion */
    ADC_EnableSoftwareStartConv(ENABLE);
    
}


/**
*\*\name    main.
*\*\fun     main program.
*\*\return  none
**/
int main(void)
{
    /* System clocks configuration ---------------------------------------------*/
    RCC_Configuration();
    /* log configuration -------------------------------------------------------*/
    log_init();

    /* ADC configuration -------------------------------------------------------*/
    ADC_Initial();
        
    /* Check ADC Conversion complete */
    while(ADC_GetFlagStatus(ADC_FLAG_ENDCA) == RESET)
        ;

    while (1)
    {
        SysTick_Delay_Ms(100);
        TempValue = TempCal(ADCConvertedValue);
        printf("\r\n Temperature = %.3f C\r\n",TempValue); 
    }
}

/**
*\*\name    RCC_Configuration.
*\*\fun     Configures the different system clocks.
*\*\return  none
**/
void RCC_Configuration(void)
{
    /* RCC_ADCHCLK_DIV1*/
    RCC_ConfigHclk(RCC_SYSCLK_DIV1);
    /* Enable GPIOA clocks */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA,ENABLE);
    /* Enable ADC, DMA clocks */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_ADC | RCC_AHB_PERIPH_DMA,ENABLE);
    ADC_ClockModeConfig(ADC_CKMOD_AHB,RCC_ADCHCLK_DIV16);
    /* enable ADC 1M clock */
    RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSI,RCC_ADC1MCLK_DIV8);
}



/**
*\*\name    TempCal.
*\*\fun     Calclate temp use float result.
*\*\return  ADC conversion float results
**/
float TempCal(uint16_t TempAdVal)
{
    float Temperate,tempValue,VTS,T_value;
    uint32_t TSValue;
    /* Voltage value of temperature sensor */
    tempValue=TempAdVal*(VREF_VALUE/4095);
    TSValue= (*(uint32_t*)(VTS_CODE_ADDR)) & 0xFFFF;
    #ifdef  VDDA_5V
    VTS = TSValue*(5.0/4095);
    #else
    VTS = TSValue*(3.3/4095);
    #endif
    T_value  = (uint16_t)(*(uint32_t *)TS_VALUE_ADDR);
    if(T_value == 0xFFFF)
    {
       T_value = 25000; 
    }
    else
    {
       /* no process */
    }
    /* Get the temperature inside the chip */
    Temperate= (VTS-tempValue)/AVG_SLOPE + T_value/1000.0f;
    return Temperate;
}


