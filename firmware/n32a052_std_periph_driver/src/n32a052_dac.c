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
*\*\file n32a052_dac.c
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/

#include "n32a052_dac.h"
#include "n32a052_rcc.h"

/** DMA Private Defines **/

/* DAC register bit mask definition*/
#define DAC_TEN_MASK   ((uint32_t)0xFFFFFFF7)
#define DAC_BEN_MASK   ((uint32_t)0xFFFFFFFB)

/** DMA Driving Functions Declaration **/

/**
*\*\name    DAC_DeInit.
*\*\fun     Deinitializes the DAC peripheral registers to their default reset values.
*\*\param   none
*\*\return  none
**/
void DAC_DeInit(void)
{
    /* DAC DeInit */
    RCC_EnableAPB1PeriphReset(RCC_APB1_PERIPH_DAC);
}

/**
*\*\name    DAC_Init.
*\*\fun     Initializes the DAC peripheral according to the specified parameters in the
*\*\        DAC_InitParam.
*\*\param   DAC_Init (The input parameters must be the following values):
*\*\          - TriggerSelect
*\*\            - DAC_TRIGGER_NONE
*\*\            - DAC_TRIGGER_TIM1_TRGO
*\*\            - DAC_TRIGGER_TIM2_TRGO
*\*\            - DAC_TRIGGER_TIM3_TRGO
*\*\            - DAC_TRIGGER_TIM4_TRGO
*\*\            - DAC_TRIGGER_TIM5_TRGO
*\*\            - DAC_TRIGGER_EXT_LINE9
*\*\            - DAC_TRIGGER_SOFTWARE
*\*\          - WaveGeneration
*\*\            - DAC_WAVEGEN_NONE
*\*\            - DAC_WAVEGEN_NOISE
*\*\            - DAC_WAVEGEN_TRIANGLE
*\*\          - LfsrUnMaskTriAmp
*\*\            - DAC_LFSR_UNMASK_BIT0
*\*\            - DAC_LFSR_UNMASK_BIT1_0
*\*\            - DAC_LFSR_UNMASK_BIT2_0
*\*\            - DAC_LFSR_UNMASK_BIT3_0
*\*\            - DAC_LFSR_UNMASK_BIT4_0
*\*\            - DAC_LFSR_UNMASK_BIT5_0
*\*\            - DAC_LFSR_UNMASK_BIT6_0
*\*\            - DAC_LFSR_UNMASK_BIT7_0
*\*\            - DAC_LFSR_UNMASK_BIT8_0
*\*\            - DAC_LFSR_UNMASK_BIT9_0
*\*\            - DAC_LFSR_UNMASK_BIT10_0
*\*\            - DAC_LFSR_UNMASK_BIT11_0
*\*\            - DAC_TRIANGLE_AMP_1
*\*\            - DAC_TRIANGLE_AMP_3
*\*\            - DAC_TRIANGLE_AMP_7
*\*\            - DAC_TRIANGLE_AMP_15
*\*\            - DAC_TRIANGLE_AMP_31
*\*\            - DAC_TRIANGLE_AMP_63
*\*\            - DAC_TRIANGLE_AMP_127
*\*\            - DAC_TRIANGLE_AMP_255
*\*\            - DAC_TRIANGLE_AMP_511
*\*\            - DAC_TRIANGLE_AMP_1023
*\*\            - DAC_TRIANGLE_AMP_2047
*\*\            - DAC_TRIANGLE_AMP_4095
*\*\          - OutputBuffer
*\*\            - DAC_OUTPUT_BUF_ENABLE
*\*\            - DAC_OUTPUT_BUF_DISABLE
*\*\          - OutputHighDriver
*\*\            - DAC_OUTPUT_HIGH_DRIVER_ENABLE
*\*\            - DAC_OUTPUT_HIGH_DRIVER_DISABLE
*\*\return  none
**/
void DAC_Init(DAC_InitType* DAC_InitStruct)
{
    uint32_t tmpreg1,tmpreg2;
    /*---------------------------- DAC CTRL Configuration --------------------------*/
    /* Get the DAC CTRL value */
    tmpreg1 = DAC->CTRL;
    /* Clear BOFFx, TENx, TSELx, WAVEx and MAMPx bits */
    tmpreg1 &= ~(DAC_CTRL_MASEL| DAC_CTRL_WEN | DAC_CTRL_TSEL | DAC_CTRL_TEN |DAC_CTRL_BEN |DAC_CTRL_BDASEL);
    /* Configure for the selected DAC : buffer output, high driver output trigger, wave generation,
       mask/amplitude for wave generation */
    /* Set TSELx and TENx bits according to TriggerSelect value */
    /* Set WAVEx bits according to WaveGeneration value */
    /* Set MAMPx bits according to LfsrUnMaskTriAmp value */
    /* Set BOFFx bit according to OutputBuffer value */
    /* Set BDASEL bit according to OutputHighDriver value */
    tmpreg2 = (DAC_InitStruct->TriggerSelect | DAC_InitStruct->WaveGeneration | DAC_InitStruct->LfsrUnMaskTriAmp
               | DAC_InitStruct->OutputBuffer | DAC_InitStruct->OutputHighDriver);
    /* Calculate CTRL register value depending on DAC_ */
    tmpreg1 |= tmpreg2 ;
    /* Write to DAC CTRL */
    DAC->CTRL = tmpreg1;
}

/**
*\*\name    DAC_InitStruct.
*\*\fun     Initializes the structure parameter of type DAC_InitType used to
*\*\        initialize DAC. This function is usually called before initializing
*\*\        a parameter of type DAC_InitType.
*\*\param   DAC_InitStruct :
*\*\          - Pointer to the DAC_InitType structure which will be initialized.
*\*\return  none
**/
void DAC_InitStruct(DAC_InitType* DAC_InitStruct)
{
    /* Initialize the TriggerSelect member */
    DAC_InitStruct->TriggerSelect = DAC_TRIGGER_NONE;
    /* Initialize the WaveGeneration member */
    DAC_InitStruct->WaveGeneration = DAC_WAVEGEN_NONE;
    /* Initialize the LfsrUnMaskTriAmp member */
    DAC_InitStruct->LfsrUnMaskTriAmp = DAC_LFSR_UNMASK_BIT0;
    /* Initialize the OutputBuffer member */
    DAC_InitStruct->OutputBuffer = DAC_OUTPUT_BUF_ENABLE;
    /* Initialize the OutputHighDriver member */
    DAC_InitStruct->OutputHighDriver = DAC_OUTPUT_HIGH_DRIVER_DISABLE;
}

/**
*\*\name    DAC_TriggerConfig.
*\*\fun     Configure the trigger source of DAC: TRGO of timer 1/2/3/4/6, EXTI LINE 9,
*\*\        software trigger.
*\*\param   Trigger (The input parameters must be the following values):
*\*\          - DAC_TRIGGER_NONE
*\*\          - DAC_TRIGGER_TIM1_TRGO
*\*\          - DAC_TRIGGER_TIM2_TRGO
*\*\          - DAC_TRIGGER_TIM3_TRGO
*\*\          - DAC_TRIGGER_TIM4_TRGO
*\*\          - DAC_TRIGGER_TIM6_TRGO
*\*\          - DAC_TRIGGER_EXT_LINE9
*\*\          - DAC_TRIGGER_SOFTWARE
*\*\return  none
*\*\note    The trigger function of DAC is also enabled while configuring the trigger source.
**/
void DAC_TriggerConfig(uint32_t Trigger)
{
    uint32_t temp_value;
    /* Get the DAC CTRL value */
    temp_value = DAC->CTRL;
    /* Clear TEN, TSEL bits */
    temp_value &= (DAC_TRIGGER_MASK);
    /* Set TEN, TSEL bits */
    temp_value |= Trigger;
    /* Update DAC_CTRL register */
    DAC->CTRL = temp_value;
}

/**
*\*\name    DAC_WaveGenerationConfig.
*\*\fun     Configured to generate noise, triangular waves, or no waveform generation.
*\*\param   WaveGeneration (The input parameters must be the following values):
*\*\          - DAC_WAVEGEN_NONE
*\*\          - DAC_WAVEGEN_NOISE
*\*\          - DAC_WAVEGEN_TRIANGLE
*\*\return  none
**/
void DAC_WaveGenerationConfig(uint32_t WaveGeneration)
{
    uint32_t temp_value;
    /* Get the DAC CTRL value */
    temp_value = DAC->CTRL;
    /* Clear WEN[1:0] bits */
    temp_value &= (DAC_WAVEGEN_MASK);
    /* Set WEN[1:0] bits */
    temp_value |= WaveGeneration;
    /* Update DAC_CTRL register */
    DAC->CTRL = temp_value;
}

/**
*\*\name    DAC_LFSRUnmaskTriangleAmplitudeConfig.
*\*\fun     Configure not to mask the LFSR bit[x:0], or configure the delta wave assignment.
*\*\param   unmaskBit_amplitude (The input parameters must be the following values):
*\*\          - DAC_LFSR_UNMASK_BIT0
*\*\          - DAC_LFSR_UNMASK_BIT1_0
*\*\          - DAC_LFSR_UNMASK_BIT2_0
*\*\          - DAC_LFSR_UNMASK_BIT3_0
*\*\          - DAC_LFSR_UNMASK_BIT4_0
*\*\          - DAC_LFSR_UNMASK_BIT5_0
*\*\          - DAC_LFSR_UNMASK_BIT6_0
*\*\          - DAC_LFSR_UNMASK_BIT7_0
*\*\          - DAC_LFSR_UNMASK_BIT8_0
*\*\          - DAC_LFSR_UNMASK_BIT9_0
*\*\          - DAC_LFSR_UNMASK_BIT10_0
*\*\          - DAC_LFSR_UNMASK_BIT11_0
*\*\          - DAC_TRIANGLE_AMP_1
*\*\          - DAC_TRIANGLE_AMP_3
*\*\          - DAC_TRIANGLE_AMP_7
*\*\          - DAC_TRIANGLE_AMP_15
*\*\          - DAC_TRIANGLE_AMP_31
*\*\          - DAC_TRIANGLE_AMP_63
*\*\          - DAC_TRIANGLE_AMP_127
*\*\          - DAC_TRIANGLE_AMP_255
*\*\          - DAC_TRIANGLE_AMP_511
*\*\          - DAC_TRIANGLE_AMP_1023
*\*\          - DAC_TRIANGLE_AMP_2047
*\*\          - DAC_TRIANGLE_AMP_4095
*\*\return  none
**/
void DAC_LFSRUnmaskTriangleAmplitudeConfig(uint32_t unmaskBit_amplitude)
{
    uint32_t temp_value;
    /* Get the DAC CTRL value */
    temp_value = DAC->CTRL;
    /* Clear MASEL[3:0] bits */
    temp_value &= (DAC_MASEL_MASK);
    /* Set MASEL[3:0] bits */
    temp_value |= unmaskBit_amplitude;
    /* Update DAC_CTRL register */
    DAC->CTRL = temp_value;
}

/**
*\*\name    DAC_OutputBufferConfig.
*\*\fun     Enables or disables the output buffer function.
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE     
*\*\return  none
**/
void DAC_OutputBufferConfig(FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the output buffer */
        DAC->CTRL |= (DAC_OUTPUT_BUF_ENABLE);
    }
    else
    {
        /* Disable the output buffer */
        DAC->CTRL &= (~DAC_OUTPUT_BUF_ENABLE);
    }
}

/**
*\*\name    DAC_HighDriverOutput.
*\*\fun     Enables or disables the output high driver ability function.
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE     
*\*\return  none
**/
void DAC_HighDriverOutput(FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the output high driver ability */
        DAC->CTRL |= DAC_OUTPUT_HIGH_DRIVER_ENABLE;
    }
    else
    {
        /* Disable the output high driver ability */
        DAC->CTRL &= (~DAC_OUTPUT_HIGH_DRIVER_ENABLE);
    }
}

/**
*\*\name    DAC_Enable.
*\*\fun     Enables or disables the DAC. 
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE     
*\*\return  none
**/
void DAC_Enable(FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the DAC  */
        DAC->CTRL |= (DAC_ENABLE);
    }
    else
    {
        /* Disable the DAC  */
        DAC->CTRL &= (~DAC_ENABLE);
    }
}


/**
*\*\name    DAC_DmaEnable.
*\*\fun     Enables or disables the DAC  DMA mode. 
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE     
*\*\return  none
**/
void DAC_DmaEnable(FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the DAC  DMA mode */
        DAC->CTRL |= DAC_DMA_ENABLE;
    }
    else
    {
        /* Disable the DAC  DMA mode */
        DAC->CTRL &= (~DAC_DMA_ENABLE);
    }
}

/**
*\*\name    DAC_SoftTrgEnable.
*\*\fun     Enables or disables the software trigger function of the DAC.
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE     
*\*\return  none
**/
void DAC_SoftTrgEnable(FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable software trigger for the DAC  */
        DAC->SOTTR |= DAC_SW_TRIGGER_ENABLE;
    }
    else
    {
        /* Disable software trigger for the DAC  */
        DAC->SOTTR &= (~DAC_SW_TRIGGER_ENABLE);
    }
}

/**
*\*\name    DAC_SetChData.
*\*\fun     Set the specified data holding register value for DAC .
*\*\param   DAC_Align (The input parameters must be the following values):
*\*\          - DAC_ALIGN_R_8BIT
*\*\          - DAC_ALIGN_L_12BIT
*\*\          - DAC_ALIGN_R_12BIT
*\*\param   Data :
*\*\          - 0 - 0xFFF
*\*\return  none
**/
void DAC_SetChData(uint32_t DAC_Align, uint16_t Data)
{
    if(DAC_Align == DAC_ALIGN_R_8BIT)
    {
        /* Set the DAC_DH8RA register */
        DAC->DH8RA = Data;
    }
    else if (DAC_Align == DAC_ALIGN_L_12BIT)
    {
        /* Set the DAC_DH12LA register */
        DAC->DH12LA = Data;
    }
    else if (DAC_Align == DAC_ALIGN_R_12BIT)
    {
        /* Set the DAC_DH12RA register */
        DAC->DH12RA = Data;
    }
    else
    {
        /* no process */
    }
}

/**
*\*\name    DAC_GetOutputDataVal.
*\*\fun     Get the last data output value of the selected DAC .
*\*\param   none
*\*\return  Returns the DAC output data value.
**/
uint16_t DAC_GetOutputDataVal(void)
{
    /* Returns the DAC  data output register value */
    return ((uint16_t)(DAC->DATO));
}

