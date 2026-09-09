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
*\*\file n32a052_adc.c
*\*\author Nations 
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/


#include "n32a052_adc.h"
#include "n32a052_rcc.h"

static void Delay_8ADC_Colck(uint32_t SysClk, uint32_t adc_clk);


static RCC_ClocksType  RCC_Clocks;
/**
*\*\name    ADC_DeInit.
*\*\fun     Reset the ADC registers.
*\*\return  none
**/
void ADC_DeInit(void)
{
    RCC_EnableAHBPeriphReset(RCC_AHB_PERIPH_ADC);
}

/**
*\*\name    ADC_Init.
*\*\fun     Initializes the ADC according to ADC_initstruct.
*\*\param   ADC_initstruct :
*\*\          - MultiChEn
*\*\            - DISABLE
*\*\            - ENABLE
*\*\          - ContinueConvEn
*\*\            - DISABLE
*\*\            - ENABLE
*\*\          - ExtTrigSelect
*\*\          - ADC_EXT_TRIGCONV_REGULAR_T1_TRGO                
*\*\          - ADC_EXT_TRIGCONV_REGULAR_T1_CC1                
*\*\          - ADC_EXT_TRIGCONV_REGULAR_T1_CC2                
*\*\          - ADC_EXT_TRIGCONV_REGULAR_T1_CC3                
*\*\          - ADC_EXT_TRIGCONV_REGULAR_T2_TRGO               
*\*\          - ADC_EXT_TRIGCONV_REGULAR_T2_CC1                
*\*\          - ADC_EXT_TRIGCONV_REGULAR_T2_CC2   
*\*\          - ADC_EXT_TRIGCONV_REGULAR_T3_TRGO  
*\*\          - ADC_EXT_TRIGCONV_REGULAR_T3_CC1                
*\*\          - ADC_EXT_TRIGCONV_REGULAR_T3_CC2  
*\*\          - ADC_EXT_TRIGCONV_REGULAR_T4_CC1                
*\*\          - ADC_EXT_TRIGCONV_REGULAR_T4_CC4 
*\*\          - ADC_EXT_TRIGCONV_REGULAR_T5_CC1                
*\*\          - ADC_EXT_TRIGCONV_REGULAR_T5_CC4  
*\*\          - ADC_EXT_TRIGCONV_REGULAR_EXT_LINE   
*\*\          - ADC_EXT_TRIGCONV_REGULAR_SWSTRRCH              
*\*\          - DatAlign
*\*\            - ADC_DAT_ALIGN_R
*\*\            - ADC_DAT_ALIGN_L
*\*\          - ChsNumber
*\*\            - ADC_REGULAR_LEN_1
*\*\            - ADC_REGULAR_LEN_2
*\*\            - ADC_REGULAR_LEN_3
*\*\            - ADC_REGULAR_LEN_4
*\*\            - ADC_REGULAR_LEN_5
*\*\return  none
**/
void ADC_Init(ADC_InitType* ADC_initstruct)
{
    __IO  uint32_t tmpreg1 = 0;
    /* Get the ADC CTRL1 value */
    tmpreg1 = ADC->CTRL2;
    /* Clear CTU , ALIGN, LEN, EXTSEL,EXTRTRIG and SCAN bits */
    tmpreg1 &= ~(ADC_CTRL2_EXTRSEL | ADC_CTRL2_LEN | ADC_CTRL2_SCANMD| ADC_CTRL2_CTU | ADC_CTRL2_ALIG | ADC_CTRL2_EXTRTRIG);
    tmpreg1 |= (uint32_t)( ((uint32_t)ADC_initstruct->MultiChEn << 12) | ((uint32_t)ADC_initstruct->ChsNumber) 
                        | ((uint32_t)ADC_initstruct->ContinueConvEn << 1) | ((uint32_t)ADC_initstruct->DatAlign) | ((uint32_t)ADC_initstruct->ExtTrigSelect) );
    /* Write to ADC CTRL2 */
    ADC->CTRL2 = tmpreg1;
    /* Get System Clock and ADC operation clock */ 
    RCC_GetClocksFreqValue(&RCC_Clocks);
}


/**
*\*\name    ADC_InitStruct.
*\*\fun     Fills each ADC_initstruct member with its default value.
*\*\param   ADC_initstruct :
*\*\          - MultiChEn
*\*\          - ContinueConvEn
*\*\          - ExtTrigSelect
*\*\          - DatAlign
*\*\          - ChsNumber
*\*\return  none
**/
void ADC_InitStruct(ADC_InitType* ADC_initstruct)
{
    /* Reset ADC init structure parameters values */
    /* initialize the MultiChEn member */
    ADC_initstruct->MultiChEn      = DISABLE;
    /* Initialize the ContinueConvEn member */
    ADC_initstruct->ContinueConvEn = DISABLE;
    /* Initialize the ExtTrigSelect member */
    ADC_initstruct->ExtTrigSelect  = ADC_EXT_TRIGCONV_REGULAR_T1_TRGO;
    /* Initialize the DatAlign member */
    ADC_initstruct->DatAlign       = ADC_DAT_ALIGN_R;
    /* Initialize the ChsNumber member */
    ADC_initstruct->ChsNumber      = ADC_REGULAR_LEN_1;
}

/**
*\*\name    ADC_Enable.
*\*\fun     Enables or disables ADC peripheral.
*\*\param   Cmd : new state of the ADC peripheral.
*\*\          -ENABLE 
*\*\          -DISABLE
*\*\return  none
**/
void ADC_Enable(FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Set the AD_ON bit to wake up the ADC from power down mode */
         ADC->CTRL2 |= ADC_TURN_ON;
    }
    else
    {
        /* Disable the selected ADC peripheral */
        ADC->CTRL2 &= (~ADC_TURN_ON);
    }
}
/**
*\*\name    ADC_EnableDMA.
*\*\fun     Enables or disables ADC DMA request.
*\*\param   Cmd : new state of the ADC peripheral.
*\*\          -ENABLE 
*\*\          -DISABLE
*\*\return  none
**/
void ADC_EnableDMA(FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected ADC DMA request */
        ADC->CTRL2 |= ADC_DMA_ENABLE;
    }
    else
    {
        /* Disable the selected ADC DMA request */
        ADC->CTRL2 &= (~ADC_DMA_ENABLE);
    }
}


/**
*\*\name    ADC_ConfigInt.
*\*\fun     Config ADC interrupts.
*\*\param   eoc_any :
*\*\          - ADC_SET_INT_TYPE_ENDCA
*\*\          - ADC_SET_INT_TYPE_OTHER
*\*\param   ADC_IT:
*\*\          - ADC_INT_ENDCA     ADC_CTRL3
*\*\          - ADC_INT_ENDC      ADC_CTRL1
*\*\          - ADC_INT_AWD       ADC_CTRL1  
*\*\param   Cmd : new state of the ADC peripheral.
*\*\          -ENABLE 
*\*\          -DISABLE
*\*\return  none
*\*\note    When eoc_any is set to 'ADC_SET_INT_TYPE_ENDCA', ADC_IT can only be configured as 'ADC_INT_ENDCA'.
**/
void ADC_ConfigInt(u8 eoc_any, uint16_t ADC_IT, FunctionalState Cmd)
{
    if(eoc_any == ADC_SET_INT_TYPE_ENDCA)
    {
       /* Set the ADC_CTRL3 ADC_INT_ENDCA bit to enable/disable ADC interrupts */
        if (Cmd != DISABLE)
        {
            ADC->CTRL3 |= ADC_IT;   
        }
        else
        {
             ADC->CTRL3 &= (~ADC_IT);
        }
    }
    else
    {
         /* Set the ADC_CTRL1 ADC_INT_ENDC/ADC_INT_AWD bit to enable/disable ADC interrupts */
        if (Cmd != DISABLE)
        {
            ADC->CTRL1 |= ADC_IT;   
        }
        else
        {
            ADC->CTRL1 &= (~ADC_IT);
        }
    }
}

/**
*\*\name    ADC_EnableSoftwareStartConv.
*\*\fun     Enables or disables software start conversion.
*\*\param   Cmd : new state of the ADC peripheral.
*\*\          -ENABLE 
*\*\          -DISABLE
*\*\return  none:
**/
void ADC_EnableSoftwareStartConv(FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
         /* Enable the ADC external trigger conversion mode for regular channels */
        ADC->CTRL2 |= ADC_EXTRTRIG_SWSTRRCH_ENABLE;
    }
    else
    {
         /* Disable the ADC external trigger conversion mode for regular channels */
        ADC->CTRL2 &= (~ADC_EXTRTRIG_SWSTRRCH_ENABLE);
    }
}    
/**
*\*\name    ADC_GetSoftwareStartConvStatus.
*\*\fun     Get ADC software start conversion status.
*\*\param   none
*\*\return  FlagStatus:
*\*\          - SET
*\*\          - RESET
**/
FlagStatus ADC_GetSoftwareStartConvStatus(void)
{
    FlagStatus bitstatus;

    /* Check the status of SOFT_START bit */
    if ((ADC->CTRL2 & ADC_EXTRTRIG_SWSTRRCH_ENABLE) != (uint32_t)RESET)
    {
        /* SOFT_START bit is set */
        bitstatus = SET;
    }
    else
    {
        /* SOFT_START bit is reset */
        bitstatus = RESET;
    }
    /* Return the SOFT_START bit status */
    return bitstatus;
}     
/**
*\*\name    ADC_ConfigChannelSampleTime.
*\*\fun     Configures ADC channel sample time.
*\*\param   sample_time :
*\*\          - ADC_SAMP_TIME_6CYCLES
*\*\          - ADC_SAMP_TIME_8CYCLES
*\*\          - ADC_SAMP_TIME_12CYCLES
*\*\          - ADC_SAMP_TIME_14CYCLES  
*\*\          - ADC_SAMP_TIME_20CYCLES                
*\*\          - ADC_SAMP_TIME_26CYCLES                   
*\*\          - ADC_SAMP_TIME_30CYCLES                   
*\*\          - ADC_SAMP_TIME_42CYCLES                   
*\*\          - ADC_SAMP_TIME_56CYCLES                   
*\*\          - ADC_SAMP_TIME_72CYCLES                  
*\*\          - ADC_SAMP_TIME_88CYCLES                   
*\*\          - ADC_SAMP_TIME_120CYCLES                  
*\*\          - ADC_SAMP_TIME_182CYCLES                  
*\*\          - ADC_SAMP_TIME_240CYCLES                  
*\*\          - ADC_SAMP_TIME_380CYCLES                 
*\*\          - ADC_SAMP_TIME_760CYCLES                  
*\*\          - ADC_SAMP_TIME_1520CYCLES                 
*\*\          - ADC_SAMP_TIME_3040CYCLES      
*\*\return  none
**/
void ADC_ConfigChannelSampleTime(uint32_t sample_time)
{
    uint32_t temp ;
    temp = ADC->SAMPT;
    temp &= (uint32_t)(ADC_SAMP_TIME_MASK);
    temp |= (uint32_t)(sample_time);
    
    ADC->SAMPT = temp;
}

/**
*\*\name    ADC_EnableExternalTriggerConversion.
*\*\fun     Enables or disables ADC conversion through external trigger.
*\*\param   Cmd : new state of the ADC peripheral.
*\*\          -ENABLE 
*\*\          -DISABLE
*\*\return  none
**/
void ADC_EnableExternalTriggerConversion(FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable ADC regular group channels conversion on external event  */
        ADC->CTRL2 |= ADC_EXTTRIGCONV_REGULAR_ENABLE;
    }
    else
    {
        /* Disables ADC regular group channels conversion on external event */
        ADC->CTRL2 &= (~ADC_EXTTRIGCONV_REGULAR_ENABLE);
    }
}
/**
*\*\name    ADC_GetDat.
*\*\fun     Get ADC regular conversion data.
*\*\return  ADC regular group conversion data.
**/
uint16_t ADC_GetDat(void)
{
    /* Return the conversion value */
    return (uint16_t)ADC->DAT0;
}
/**
*\*\name    ADC_GetGroupConvDat.
*\*\fun     Get ADC regular group conversion data.
*\*\param   number :
*\*\          - 0~4
*\*\return  ADC regular group conversion data.
**/
uint16_t ADC_GetGroupConvDat(uint8_t number)
{
    /* Return the conversion value */
    return (uint16_t)ADC_DATA_REG_READ(ADC->DAT0,number);
}

/**
*\*\name    ADC_ConfigAnalogWatchdogModeChannel.
*\*\fun     Configures ADC analog watchdog single mode or scan mode,
*\*\        and single mode channel operation.
*\*\param   mode :
*\*\          - ADC_ANALOG_WTDG_SINGLE_MODE
*\*\          - ADC_ANALOG_WTDG_SCAN_MODE
*\*\param   channel :
*\*\          - ADC_ANALOG_WTDG_SINGLE_CH0
*\*\          - ADC_ANALOG_WTDG_SINGLE_CH1
*\*\          - ADC_ANALOG_WTDG_SINGLE_CH2
*\*\          - ADC_ANALOG_WTDG_SINGLE_CH3
*\*\          - ADC_ANALOG_WTDG_SINGLE_CH4
*\*\          - ADC_ANALOG_WTDG_SINGLE_CH5
*\*\          - ADC_ANALOG_WTDG_SINGLE_CH6
*\*\          - ADC_ANALOG_WTDG_SINGLE_CH7
*\*\          - ADC_ANALOG_WTDG_SINGLE_CH8
*\*\          - ADC_ANALOG_WTDG_SINGLE_CH9
*\*\          - ADC_ANALOG_WTDG_SINGLE_CH10
*\*\          - ADC_ANALOG_WTDG_SINGLE_CH11
*\*\          - ADC_ANALOG_WTDG_SINGLE_CH12
*\*\          - ADC_ANALOG_WTDG_SINGLE_CH13
*\*\          - ADC_ANALOG_WTDG_SINGLE_CH14
*\*\          - ADC_ANALOG_WTDG_SINGLE_CH15
*\*\          - ADC_ANALOG_WTDG_SINGLE_CH16
*\*\return  none
**/
void ADC_ConfigAnalogWatchdogModeChannel(uint32_t mode, uint8_t channel)
{
    uint32_t temp ;
    temp = ADC->CTRL1;
    
    if(mode == ADC_ANALOG_WTDG_SINGLE_MODE)
    {
        /* ADC analog watchdog on a single channel */
        temp |= ADC_ANALOG_WTDG_SINGLE_MODE;
    }
    else
    {
        /* ADC analog watchdog on all regulor channels */
        temp &= ADC_ANALOG_WTDG_MODE_MASK;
    }
    /* Clear ADC analog watchdog single mode channel */
    temp &= ADC_ANALOG_WTDG_SINGLE_CH_MASK;
    /* Select ADC analog watchdog single mode channel */
    temp |= (uint32_t)channel;
    ADC->CTRL1 = temp;
}

/**
*\*\name    ADC_EnableAnalogWatchdog.
*\*\fun     Enable and disable ADC Analog watchdog.
*\*\param   Cmd : new state of the ADC peripheral.
*\*\          -ENABLE 
*\*\          -DISABLE
*\*\return  none
**/
void ADC_EnableAnalogWatchdog(FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Set the ADC_CTRL1 AWDGERCH bit */
        ADC->CTRL1 |= ADC_ANALOG_WTDG_REGULAR;
    }
    else
    {
        /* Reset the ADC_CTRL1 AWDGERCH bit */
        ADC->CTRL1 &= (~ADC_ANALOG_WTDG_REGULAR);
    }
}

/**
*\*\name    ADC_Analog_Watchdog_HighThresholds_Config.
*\*\fun     Configures the high thresholds of the analog watchdog.
*\*\param   HighThreshold : 12bit high thresholds value(0 ~ 0xFFF)
*\*\param   LowThreshold : 12bit low thresholds value(0 ~ 0xFFF)
*\*\return  none
**/
void ADC_ConfigAnalogWatchdogThresholds(uint16_t HighThreshold, uint16_t LowThreshold)
{
    /* Set the ADC high threshold */
    ADC->WDGHIGH = HighThreshold;
    /* Set the ADC low threshold */
    ADC->WDGLOW = LowThreshold;
}


/**
*\*\name    ADC_GetFlagStatus.
*\*\fun     Get ADC flag Status.
*\*\param   ADC_FLAG :
*\*\          - ADC_FLAG_AWDG
*\*\          - ADC_FLAG_ENDC
*\*\          - ADC_FLAG_ENDCA
*\*\          - ADC_FLAG_STR
*\*\return  SET or RESET
**/
FlagStatus ADC_GetFlagStatus(uint8_t ADC_FLAG)
{
    /* Check the status of ADC flag */
    if ((ADC->STS & ADC_FLAG) != (uint8_t)RESET)
    {
        if(ADC_FLAG == ADC_FLAG_ENDC)
        {
            if((RCC->CFG2 & RCC_CFG2_ADCCLKSEL ) == RCC_ADC_CLKSRC_HSI24M)
            {
                Delay_8ADC_Colck(RCC_Clocks.SysclkFreq,24000000);
            }
            else if((RCC->CFG2 & RCC_CFG2_ADCCLKSEL ) == RCC_ADC_CLKSRC_HCLK)
            {
                Delay_8ADC_Colck(RCC_Clocks.SysclkFreq,RCC_Clocks.AdcHclkFreq);
            }
            else
            {
                Delay_8ADC_Colck(RCC_Clocks.SysclkFreq,RCC_Clocks.AdcPllClkFreq);
            }
        }
        else
        {
            /* no process */
        }
        /* ADC_FLAG is set */
        return SET;
    }
    else
    {
        /* ADC_FLAG is reset */
        return RESET;
    }
}
/**
*\*\name    ADC_GetFlagStatusNew.
*\*\fun     Get ADC flag New Status.
*\*\param   ADC_FLAG :
*\*\          - ADC_FLAG_RDY ADC ready flag
*\*\          - ADC_FLAG_PD_RDY ADC powerdown ready flag
*\*\          - ADC_FLAG_BUF_RDY VREFBUF ready flag
*\*\return  SET or RESET
**/
FlagStatus ADC_GetFlagStatusNew(uint8_t ADC_FLAG_NEW)
{
    FlagStatus bitstatus  ;

    /* Check the status of the specified ADC flag */
    if ((ADC->CTRL3 & ADC_FLAG_NEW) != (uint8_t)RESET)
    {
        /* ADC_FLAG_NEW is set */
        bitstatus = SET;
    }
    else
    {
        /* ADC_FLAG_NEW is reset */
        bitstatus = RESET;
    }
    /* Return the ADC_FLAG_NEW status */
    return bitstatus;
}
/**
*\*\name    ADC_ClearFlag.
*\*\fun     Clear ADC flag Status.
*\*\param   ADC_FLAG :
*\*\          - ADC_FLAG_AWDG
*\*\          - ADC_FLAG_ENDC
*\*\          - ADC_FLAG_ENDCA
*\*\          - ADC_FLAG_STR
*\*\return  none
**/
void ADC_ClearFlag(uint8_t ADC_FLAG)
{
    /* Clear the selected ADC flags */
    ADC->STS = (~(uint32_t)ADC_FLAG);
}

/**
*\*\name    ADC_GetIntStatus.
*\*\fun     Get ADC Interrupt Status.
*\*\param   ADC_IT :
*\*\          - ADC_INT_FLAG_AWDG
*\*\          - ADC_INT_FLAG_ENDC
*\*\          - ADC_INT_FLAG_ENDCA
*\*\return  SET or RESET
**/
INTStatus ADC_GetIntStatus(uint16_t ADC_IT)
{
    FlagStatus bitstatus  ;
    if ((ADC->STS & ADC_IT) != (uint8_t)RESET)
    {
        if(ADC_IT == ADC_INT_FLAG_ENDC)
        {
            if((RCC->CFG2 & RCC_CFG2_ADCCLKSEL ) == RCC_ADC_CLKSRC_HSI24M)
            {
                Delay_8ADC_Colck(RCC_Clocks.SysclkFreq,24000000);
            }
            else if((RCC->CFG2 & RCC_CFG2_ADCCLKSEL ) == RCC_ADC_CLKSRC_HCLK)
            {
                Delay_8ADC_Colck(RCC_Clocks.SysclkFreq,RCC_Clocks.AdcHclkFreq);
            }
            else
            {
                Delay_8ADC_Colck(RCC_Clocks.SysclkFreq,RCC_Clocks.AdcPllClkFreq);
            }
        }
        else
        {
            /* no process */
        }
        /* ADC_INT_FLAG is set */
        bitstatus = SET;
    }
    else
    {
        /* ADC_INT_FLAG is reset */
         bitstatus = RESET;
    }
    return bitstatus;
}
/**
*\*\name    ADC_ClearFlag.
*\*\fun     Clear ADC flag Status.
*\*\param   ADC_IT :
*\*\          - ADC_INT_FLAG_AWDG
*\*\          - ADC_INT_FLAG_ENDC
*\*\          - ADC_INT_FLAG_ENDCA
*\*\return  none
**/
void ADC_ClearIntPendingBit(uint16_t ADC_IT)
{
    /* Clear the selected ADC interrupt pending bits */
    ADC->STS = (~(uint32_t)ADC_IT);
}


/**
*\*\name    ADC_ConfigRegularSequenceSingle.
*\*\fun     Configures ADC channel Single in regular sequence.
*\*\param   channel :
*\*\          - ADC_CH_0
*\*\          - ADC_CH_1
*\*\          - ADC_CH_2
*\*\          - ADC_CH_3
*\*\          - ADC_CH_4
*\*\          - ADC_CH_5
*\*\          - ADC_CH_6
*\*\          - ADC_CH_7
*\*\          - ADC_CH_8
*\*\          - ADC_CH_9
*\*\          - ADC_CH_10
*\*\          - ADC_CH_11
*\*\          - ADC_CH_12
*\*\          - ADC_CH_13
*\*\          - ADC_CH_14
*\*\          - ADC_CH_15
*\*\          - ADC_CH_16
*\*\return  none
**/
void ADC_ConfigRegularSequenceSingle(uint8_t channel)
{
    uint32_t temp  ;
    temp = ADC->DAT0;
    /* ADC regular sequence register configures channelx */
    temp &= ADC_SQR_MASK;
    temp |= ((uint32_t)channel<<ADC_SQR_OFFSET);
    
    ADC->DAT0 = temp;
}

/**
*\*\name    ADC_ConfigRegularSequenceMulti.
*\*\fun     Configures ADC channel Multi in regular sequence.
*\*\param   channel :
*\*\          - ADC_CH_0
*\*\          - ADC_CH_1
*\*\          - ADC_CH_2
*\*\          - ADC_CH_3
*\*\          - ADC_CH_4
*\*\          - ADC_CH_5
*\*\          - ADC_CH_6
*\*\          - ADC_CH_7
*\*\          - ADC_CH_8
*\*\          - ADC_CH_9
*\*\          - ADC_CH_10
*\*\          - ADC_CH_11
*\*\          - ADC_CH_12
*\*\          - ADC_CH_13
*\*\          - ADC_CH_14
*\*\          - ADC_CH_15
*\*\          - ADC_CH_16
*\*\param   number :
*\*\          - ADC_DATA_OFFSET0
*\*\          - ADC_DATA_OFFSET1
*\*\          - ADC_DATA_OFFSET2
*\*\          - ADC_DATA_OFFSET3
*\*\          - ADC_DATA_OFFSET4
*\*\return  none
**/
void ADC_ConfigRegularSequenceMulti(uint8_t channel,uint8_t number)
{
    uint32_t temp  ;
    /* ADC regular sequence register configures channelx */
    if(number == ADC_DATA_OFFSET0)
    {
        temp = ADC->DAT0;
        temp &= ADC_SQR_MASK;
        temp |= ((uint32_t)channel<<ADC_SQR_OFFSET);
        ADC->DAT0 = temp;
    }
    else if(number == ADC_DATA_OFFSET1)
    {
        temp = ADC->DAT1;
        temp &= ADC_SQR_MASK;
        temp|= ((uint32_t)channel<<ADC_SQR_OFFSET);
        ADC->DAT1 = temp;
    } 
    else if(number == ADC_DATA_OFFSET2)
    {
        temp = ADC->DAT2;
        temp &= ADC_SQR_MASK;
        temp |= ((uint32_t)channel<<ADC_SQR_OFFSET);
        ADC->DAT2 = temp;
    } 
    else if(number == ADC_DATA_OFFSET3)
    {
        temp = ADC->DAT3;
        temp &= ADC_SQR_MASK;
        temp |= ((uint32_t)channel<<ADC_SQR_OFFSET);
        ADC->DAT3 = temp;
    } 
    else if(number == ADC_DATA_OFFSET4)
    {
        temp = ADC->DAT4;
        temp &= ADC_SQR_MASK;
        temp |= ((uint32_t)channel<<ADC_SQR_OFFSET);
        ADC->DAT4 = temp;
    }
    else
    {
        /* no process */
    }

}
/**
*\*\name    ADC_EnableInternalInputBuffer.
*\*\fun     Enable and disable ADC internal input buffer.
*\*\param   Cmd : new state of the ADC peripheral.
*\*\          -ENABLE 
*\*\          -DISABLE
*\*\return  none
**/
void ADC_EnableInternalInputBuffer(FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the ADC internal reference voltage */
        ADC->CTRL3 |= ADC_IN_BUFFER_ENABLE;
    }
    else
    {
        /* Disable the ADC internal reference voltage */
        ADC->CTRL3 &= (~ADC_IN_BUFFER_ENABLE);
    }
}


/**
*\*\name    ADC_Temp_Sensor_Enable.
*\*\fun     Enable and disable temperature sensor channel .
*\*\param   Cmd : new state of the ADC peripheral.
*\*\          -ENABLE 
*\*\          -DISABLE
*\*\return  none
**/
void ADC_EnableTempSensor(FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Temperature sensor channel enabled */
        ADC->CTRL2 |= ADC_CTRL2_TEMPEN;
    }
    else
    {
        /* Temperature sensor channel disable */
        ADC->CTRL2 &= (~ADC_CTRL2_TEMPEN);
    }
}

/**
*\*\name    ADC_EnableVREFPAsReferenceVoltag.
*\*\fun     Select VREF+ as ADC reference voltage source or not.
*\*\param   Cmd : new state of the ADC peripheral.
*\*\          -ENABLE 
*\*\          -DISABLE
*\*\return  none
**/
void ADC_EnableVREFPAsReferenceVoltag(FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Select VREF+ as ADC reference voltage source */
        ADC->CTRL1 |= ADC_REF_SEL_VREF;
    }
    else
    {
        /* Select VDDA as ADC reference voltage source */
        ADC->CTRL1 &= (~ADC_REF_SEL_VREF);
    }
}

/**
*\*\name    ADC_Clock_Mode_Config
*\*\fun     Configures the ADCHCLK prescaler.
*\*\param   ADC_clkmode:
*\*\          - ADC_CKMOD_AHB
*\*\          - ADC_CKMOD_PLL
*\*\          - ADC_CKMOD_HSI
*\*\param   RCC_ADCHCLKprescaler:
*\*\          - RCC_ADCHCLK_DIV1 
*\*\          - RCC_ADCHCLK_DIV2 
*\*\          - RCC_ADCHCLK_DIV4 
*\*\          - RCC_ADCHCLK_DIV6 
*\*\          - RCC_ADCHCLK_DIV8 
*\*\          - RCC_ADCHCLK_DIV10 
*\*\          - RCC_ADCHCLK_DIV12 
*\*\          - RCC_ADCHCLK_DIV16 
*\*\          - RCC_ADCHCLK_DIV32

*\*\          - RCC_ADCPLLCLK_DIV1 
*\*\          - RCC_ADCPLLCLK_DIV2 
*\*\          - RCC_ADCPLLCLK_DIV4 
*\*\          - RCC_ADCPLLCLK_DIV6 
*\*\          - RCC_ADCPLLCLK_DIV8
*\*\          - RCC_ADCPLLCLK_DIV10
*\*\          - RCC_ADCPLLCLK_DIV12 
*\*\          - RCC_ADCPLLCLK_DIV16 
*\*\          - RCC_ADCPLLCLK_DIV32 
*\*\          - RCC_ADCPLLCLK_DIV64 
*\*\          - RCC_ADCPLLCLK_DIV128 
*\*\          - RCC_ADCPLLCLK_DIV256 
*\*\return  none
**/
void ADC_ClockModeConfig(ADC_CKMOD ADC_clkmode, uint32_t RCC_ADCHCLKprescaler)
{
    if(ADC_clkmode == ADC_CKMOD_AHB)
    {
        RCC_ConfigADCClksrc(RCC_ADC_CLKSRC_HCLK);
        RCC_ConfigAdcHclk(RCC_ADCHCLKprescaler);
    }
    else if(ADC_clkmode == ADC_CKMOD_PLL)
    {
        RCC_ConfigADCClksrc(RCC_ADC_CLKSRC_PLL);
        RCC_ConfigAdcPllClk(RCC_ADCHCLKprescaler,ENABLE);
    }
    else if(ADC_clkmode == ADC_CKMOD_HSI)
    {
        RCC_ConfigADCClksrc(RCC_ADC_CLKSRC_HSI24M);
    }
    else
    {
        /* no process */
    }
}
/**
*\*\name  Delay_8ADC_Colck.
*\*\fun   Delay 8 ADC_CLK according to the system clock and adc clock.
*\*\param SysClk ,the system clcok frequency.
*\*\param adc_clkk ,the adc operating clcok frequency.
*\*\note: this function is not very precise, if you want to get more precise delay time, please modify this function directly. 
*\*\return  None
 */
static void Delay_8ADC_Colck(uint32_t SysClk, uint32_t adc_clk)
{
    uint16_t Count = 0;
    __IO uint16_t  div = 0;
    div =  (SysClk/adc_clk);
    if(div <= 64)
    {
        div = 1;
    }
    else if(div <= 128)
    {
        div = 25;
    }
    else if(div <= 256)
    {
        div = 70;
    }
    while(Count < div)  
    {
        __NOP();
        Count++;
    }
}

