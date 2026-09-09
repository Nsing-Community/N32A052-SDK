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
*\*\file n32a052_comp.c
*\*\author Nations 
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/
 
#include "n32a052_comp.h"
#include "n32a052_rcc.h"

#define COMP_FILTCR_MASK        ((uint32_t)0x000007FFU)
/**
*\*\name    COMP_Reset.
*\*\fun     Reset the COMP registers.
*\*\return  none
**/
void COMP_DeInit(void)
{
    RCC_EnableAPB1PeriphReset(RCC_APB1_PERIPH_COMP);
}

/**
*\*\name    COMP_Init.
*\*\fun     Initializes the COMP peripheral according to the specified parameters in the COMP_InitStruct
*\*\param   COMP_initstruct :
*\*\param   Blking :
*\*\          - COMP_CTRL_BLKING_NO
*\*\          - COMP_CTRL_BLKING_TIM1_OC5
*\*\param   Hyst :
*\*\          - COMP_CTRL_HYST_NO   
*\*\          - COMP_CTRL_HYST_LOW  
*\*\          - COMP_CTRL_HYST_MID     
*\*\          - COMP_CTRL_HYST_HIGH 
*\*\param   PolRev :
*\*\          - COMP_OUTPOL_REV   
*\*\          - COMP_OUTPOL_NREV
*\*\param   InpSel :
*\*\          - COMP1
*\*\            - COMP1_CTRL_INPSEL_PA2                   
*\*\            - COMP1_CTRL_INPSEL_PA3                   
*\*\            - COMP1_CTRL_INPSEL_VREF_VC1                   
*\*\            - COMP1_CTRL_INPSEL_PB1                  
*\*\          - COMP2
*\*\            - COMP2_CTRL_INPSEL_PB1                   
*\*\            - COMP2_CTRL_INPSEL_PA6                   
*\*\            - COMP2_CTRL_INPSEL_PB10                   
*\*\            - COMP2_CTRL_INPSEL_PA5                                     
*\*\            - COMP2_CTRL_INPSEL_VREF_VC2                   
*\*\          - COMP3
*\*\            - COMP3_CTRL_INPSEL_PA10                   
*\*\            - COMP3_CTRL_INPSEL_DAC_OUT_PB13                   
*\*\            - COMP3_CTRL_INPSEL_VREF_VC1                   
*\*\            - COMP3_CTRL_INPSEL_PD7                 
*\*\          - COMP4
*\*\            - COMP4_CTRL_INPSEL_PD7                   
*\*\            - COMP4_CTRL_INPSEL_PA12                   
*\*\            - COMP4_CTRL_INPSEL_PD5                   
*\*\            - COMP4_CTRL_INPSEL_VREF_VC2  
*\*\param   InmSel :
*\*\          - COMP1
*\*\            - COMP1_CTRL_INMSEL_PA5                   
*\*\            - COMP1_CTRL_INMSEL_PB0         
*\*\            - COMP1_CTRL_INMSEL_PA2                   
*\*\            - COMP1_CTRL_INMSEL_VREF_VC1                    
*\*\            - COMP1_CTRL_INMSEL_DAC_OUT_PB13                  
*\*\          - COMP2
*\*\            - COMP2_CTRL_INMSEL_PA3     
*\*\            - COMP2_CTRL_INMSEL_PB2      
*\*\            - COMP2_CTRL_INMSEL_PA4                   
*\*\            - COMP2_CTRL_INMSEL_DAC_OUT_PB13      
*\*\          - COMP3
*\*\            - COMP3_CTRL_INMSEL_PA9     
*\*\            - COMP3_CTRL_INMSEL_PD6      
*\*\            - COMP3_CTRL_INMSEL_VREF_VC1                   
*\*\            - COMP3_CTRL_INMSEL_DAC_OUT_PB13    
*\*\          - COMP4
*\*\            - COMP4_CTRL_INMSEL_PA11     
*\*\            - COMP4_CTRL_INMSEL_PD4      
*\*\            - COMP4_CTRL_INMSEL_VREF_VC2                   
*\*\            - COMP4_CTRL_INMSEL_DAC_OUT_PB13
*\*\param   OutSel :
*\*\          - COMP1
*\*\            - COMP1_CTRL_OUTSEL_T1_OCREFCLEAR
*\*\            - COMP1_CTRL_OUTSEL_T1_BKIN                
*\*\            - COMP1_CTRL_OUTSEL_T1_IC1  
*\*\            - COMP1_CTRL_OUTSEL_T2_IC1        
*\*\            - COMP1_CTRL_OUTSEL_T2_IC4              
*\*\            - COMP1_CTRL_OUTSEL_T2_OCREFCLEAR                                 
*\*\            - COMP1_CTRL_OUTSEL_T3_IC1  
*\*\            - COMP1_CTRL_OUTSEL_T3_IC4  
*\*\            - COMP1_CTRL_OUTSEL_T3_OCREFCLEAR  
*\*\            - COMP1_CTRL_OUTSEL_T4_IC1  
*\*\            - COMP1_CTRL_OUTSEL_T4_IC4  
*\*\            - COMP1_CTRL_OUTSEL_T4_OCREFCLEAR  
*\*\            - COMP1_CTRL_OUTSEL_T5_IC1  
*\*\            - COMP1_CTRL_OUTSEL_T5_IC4  
*\*\            - COMP1_CTRL_OUTSEL_T5_OCREFCLEAR  
*\*\          - COMP2
*\*\            - COMP2_CTRL_OUTSEL_T1_OCREFCLEAR
*\*\            - COMP2_CTRL_OUTSEL_T1_BKIN                
*\*\            - COMP2_CTRL_OUTSEL_T1_IC1  
*\*\            - COMP2_CTRL_OUTSEL_T2_IC1        
*\*\            - COMP2_CTRL_OUTSEL_T2_IC2             
*\*\            - COMP2_CTRL_OUTSEL_T2_OCREFCLEAR                                 
*\*\            - COMP2_CTRL_OUTSEL_T3_IC1  
*\*\            - COMP2_CTRL_OUTSEL_T3_IC2  
*\*\            - COMP2_CTRL_OUTSEL_T3_OCREFCLEAR  
*\*\            - COMP2_CTRL_OUTSEL_T4_IC1  
*\*\            - COMP2_CTRL_OUTSEL_T4_IC2  
*\*\            - COMP2_CTRL_OUTSEL_T4_OCREFCLEAR  
*\*\            - COMP2_CTRL_OUTSEL_T5_IC1  
*\*\            - COMP2_CTRL_OUTSEL_T5_IC2  
*\*\            - COMP2_CTRL_OUTSEL_T5_OCREFCLEAR  
*\*\          - COMP3
*\*\            - COMP3_CTRL_OUTSEL_T1_OCREFCLEAR
*\*\            - COMP3_CTRL_OUTSEL_T1_BKIN                
*\*\            - COMP3_CTRL_OUTSEL_T1_IC1  
*\*\            - COMP3_CTRL_OUTSEL_T2_IC1        
*\*\            - COMP3_CTRL_OUTSEL_T2_IC2             
*\*\            - COMP3_CTRL_OUTSEL_T2_OCREFCLEAR                                 
*\*\            - COMP3_CTRL_OUTSEL_T3_IC1  
*\*\            - COMP3_CTRL_OUTSEL_T3_IC2  
*\*\            - COMP3_CTRL_OUTSEL_T3_OCREFCLEAR  
*\*\            - COMP3_CTRL_OUTSEL_T4_IC1  
*\*\            - COMP3_CTRL_OUTSEL_T4_IC2  
*\*\            - COMP3_CTRL_OUTSEL_T4_OCREFCLEAR  
*\*\            - COMP3_CTRL_OUTSEL_T5_IC1  
*\*\            - COMP3_CTRL_OUTSEL_T5_IC2  
*\*\            - COMP3_CTRL_OUTSEL_T5_OCREFCLEAR  
*\*\          - COMP4
*\*\            - COMP4_CTRL_OUTSEL_T1_OCREFCLEAR
*\*\            - COMP4_CTRL_OUTSEL_T1_BKIN                
*\*\            - COMP4_CTRL_OUTSEL_T1_IC1  
*\*\            - COMP4_CTRL_OUTSEL_T2_IC3        
*\*\            - COMP4_CTRL_OUTSEL_T2_IC4              
*\*\            - COMP4_CTRL_OUTSEL_T2_OCREFCLEAR                                 
*\*\            - COMP4_CTRL_OUTSEL_T3_IC3  
*\*\            - COMP4_CTRL_OUTSEL_T3_IC4  
*\*\            - COMP4_CTRL_OUTSEL_T3_OCREFCLEAR  
*\*\            - COMP4_CTRL_OUTSEL_T4_IC3  
*\*\            - COMP4_CTRL_OUTSEL_T4_IC4  
*\*\            - COMP4_CTRL_OUTSEL_T4_OCREFCLEAR  
*\*\            - COMP4_CTRL_OUTSEL_T5_IC3  
*\*\            - COMP4_CTRL_OUTSEL_T5_IC4  
*\*\            - COMP4_CTRL_OUTSEL_T5_OCREFCLEAR  
*\*\param   ClkPsc:
*\*\          Value can be set from 0 to 65535.
*\*\param   FilterEn:
*\*\          - ENABLE 
*\*\          - DISABLE
*\*\param   Threshold:
*\*\          - this value must be greater than SAMPW / 2 .
*\*\param   SampWindow:
*\*\          - from 0 to 31.
*\*\param   En
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void COMP_Init(COMPX COMPx, COMP_InitType* COMP_InitStruct)
{
    COMP_SingleType *pCS ;
    __IO uint32_t tmpreg1 = 0;
    if(COMPx == COMP1)
    {
        pCS = (COMP_SingleType*)&COMP->COMP1;
    }
    else if(COMPx == COMP2)
    {
        pCS = (COMP_SingleType*)&COMP->COMP2;
    }
    else if(COMPx == COMP3)
    {
        pCS = (COMP_SingleType*)&COMP->COMP3;
    }
    else if(COMPx == COMP4)
    {
        pCS = (COMP_SingleType*)&COMP->COMP4;
    }
    else
    {
        pCS = NULL;
    }

    if(pCS == NULL)
    {
        return ;
    }

    // filter
    tmpreg1 = pCS->FILC;
    tmpreg1 &= COMP_FILTCR_MASK;
    tmpreg1 |= ((uint32_t)COMP_InitStruct->SampWindow << 6)|((uint32_t)COMP_InitStruct->Threshold << 1)|((uint32_t)COMP_InitStruct->FilterEn);
    pCS->FILC = tmpreg1;
    // filter psc
    pCS->FILP = COMP_InitStruct->ClkPsc;

    // ctrl
    tmpreg1 = pCS->CTRL;
    tmpreg1 &= (COMP_BLANKING_MASK & COMP_HYST_MASK &COMP_INPSEL_MASK& COMP_INMSEL_MASK& COMP_OUTSEL_MASK);
    tmpreg1 |= ((COMP_InitStruct->Blking) | (COMP_InitStruct->Hyst)  | (COMP_InitStruct->InpSel) |
                (COMP_InitStruct->InmSel) | (COMP_InitStruct->OutSel) );
    /*COMP out pol select*/
    if(COMP_InitStruct->PolRev != DISABLE)
    {
        tmpreg1 |= (COMP_OUTPOL_REV);
    }
    else
    {
        tmpreg1 &= (~COMP_OUTPOL_REV);
    }
    /*COMP enable or disable select*/
    if(COMP_InitStruct->En != DISABLE)
    {
        tmpreg1 |= COMP_ENABLE;
    }
    else
    {
        tmpreg1 &= (~COMP_ENABLE);
    }

    pCS->CTRL = tmpreg1;
}
/**
*\*\name    COMP_StructInit.
*\*\fun     Fills all COMP_initstruct member with default value.
*\*\param   COMP_initstruct :
*\*\          - Blking
*\*\          - Hyst
*\*\          - PolRev
*\*\          - OutSel
*\*\          - InpSel
*\*\          - InmSel
*\*\          - FilterEn
*\*\          - ClkPsc
*\*\          - SampWindow
*\*\          - Threshold
*\*\          - En
*\*\return  none
**/
void COMP_StructInit(COMP_InitType* COMP_initstruct)
{
    /* Reset COMP init structure parameters values */ 
    /* Initialize the Blking */
    COMP_initstruct->Blking            = (uint32_t)COMP_CTRL_BLKING_NO;
    /* Initialize the Hyst */
    COMP_initstruct->Hyst              = (uint32_t)COMP_CTRL_HYST_NO;
    /* Initialize the PolRev */
    COMP_initstruct->PolRev            = COMP_OUTPOL_NREV;
    /* Initialize the OutSel */
    COMP_initstruct->OutSel            = COMP_OUTSEL_RES;
    /* Initialize the InpSel */
    COMP_initstruct->InpSel            = COMP_INPSEL_RES;
    /* Initialize the InmSel */
    COMP_initstruct->InmSel            = COMP_INMSEL_RES;
    /* Initialize the FilterEn */
    COMP_initstruct->FilterEn          = DISABLE;
    /* Initialize the ClkPsc */
    COMP_initstruct->ClkPsc            = 0;
    /* Initialize the SampWindow */
    COMP_initstruct->SampWindow        = 0;
    /* Initialize the Threshold */
    COMP_initstruct->Threshold         = 0;
    /* Initialize the En */
    COMP_initstruct->En                = DISABLE;
}

/**
*\*\name    COMP_SetFilterControl.
*\*\fun     Configure the COMP filter value. 
*\*\param   COMPx:
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\          - COMP4
*\*\param   FilEn:
*\*\          - ENABLE.
*\*\          - DISABLE.
*\*\param   TheresNum:
*\*\          - this value must be greater than SAMPW / 2 .
*\*\param   SampPW:
*\*\          - from 0 to 31.
*\*\return  none
**/
void COMP_SetFilterControl(COMPX COMPx, uint8_t FilEn, uint8_t TheresNum, uint8_t SampPW)
{
    if(COMPx == COMP1)
    {
        /* Clear COMP_FILC SAMPW[4:0],THRESH[4:0] Filt_EN bits */
        COMP->COMP1.FILC &= COMP_FILTCR_MASK;
        /* Set COMP_FILC SAMPW[4:0],THRESH[4:0] Filt_EN bits bits */
        COMP->COMP1.FILC = (((uint32_t)SampPW << 6)|((uint32_t)TheresNum << 1)|((uint32_t)FilEn));
    }
    else if(COMPx == COMP2)
    {
        /* Clear COMP_FILC SAMPW[4:0],THRESH[4:0] Filt_EN bits */
        COMP->COMP2.FILC &= COMP_FILTCR_MASK;
        /* Set COMP_FILC SAMPW[4:0],THRESH[4:0] Filt_EN bits bits */
        COMP->COMP2.FILC = (((uint32_t)SampPW << 6)|((uint32_t)TheresNum << 1)|((uint32_t)FilEn));
    }
    else if(COMPx == COMP3)
    {
        /* Clear COMP_FILC SAMPW[4:0],THRESH[4:0] Filt_EN bits */
        COMP->COMP3.FILC &= COMP_FILTCR_MASK;
        /* Set COMP_FILC SAMPW[4:0],THRESH[4:0] Filt_EN bits bits */
        COMP->COMP3.FILC = (((uint32_t)SampPW << 6)|((uint32_t)TheresNum << 1)|((uint32_t)FilEn));
    }
    else 
    {
        /* Clear COMP_FILC SAMPW[4:0],THRESH[4:0] Filt_EN bits */
        COMP->COMP4.FILC &= COMP_FILTCR_MASK;
        /* Set COMP_FILC SAMPW[4:0],THRESH[4:0] Filt_EN bits bits */
        COMP->COMP4.FILC = (((uint32_t)SampPW << 6)|((uint32_t)TheresNum << 1)|((uint32_t)FilEn));
    }
}

/**
*\*\name    COMP_Filter_Clock_Prescale_Config.
*\*\fun     Configure The COMP low filter prescale.
*\*\param   COMPx:
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\          - COMP4
*\*\param   FilPreVal:
*\*\        Value can be set from 0 to 65535.
*\*\return  none
**/
void COMP_SetFilterPrescaler(COMPX COMPx, uint16_t FilPreVal)
{
    if(COMPx == COMP1)
    {
        /* Clear COMP_FILP CLKPSC[15:0] bits */
        COMP->COMP1.FILP &= COMP_FILTER_CLKPSC_MASK;
        /* Set COMP_FILP CLKPSC[15:0] bits */
        COMP->COMP1.FILP |= FilPreVal;
    }
    else if(COMPx == COMP2)
    {
        /* Clear COMP_FILP CLKPSC[15:0] bits */
        COMP->COMP2.FILP &= COMP_FILTER_CLKPSC_MASK;
        /* Set COMP_FILP CLKPSC[15:0] bits */
        COMP->COMP2.FILP |= FilPreVal;
    }
    else if(COMPx == COMP3)
    {
        /* Clear COMP_FILP CLKPSC[15:0] bits */
        COMP->COMP3.FILP &= COMP_FILTER_CLKPSC_MASK;
        /* Set COMP_FILP CLKPSC[15:0] bits */
        COMP->COMP3.FILP |= FilPreVal;
    }
    else 
    {
        /* Clear COMP_FILP CLKPSC[15:0] bits */
        COMP->COMP4.FILP &= COMP_FILTER_CLKPSC_MASK;
        /* Set COMP_FILP CLKPSC[15:0] bits */
        COMP->COMP4.FILP |= FilPreVal;
    }
}

/**
*\*\name    COMP_SetBlanking.
*\*\fun     Configure the COMP blanking source. 
*\*\param   COMPx:
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\          - COMP4
*\*\param   blking_mode :
*\*\          - COMP_CTRL_BLKING_NO
*\*\          - COMP_CTRL_BLKING_TIM1_OC5
*\*\return  none
**/
void COMP_SetBlanking(COMPX COMPx, COMP_CTRL_BLKING BLK)
{
    if(COMPx == COMP1)
    {
        /* Clear COMP1_CTRL BLKING bit */
        COMP->COMP1.CTRL &= COMP_BLANKING_MASK;
        /* Set COMP1_CTRL BLKING bit */
        COMP->COMP1.CTRL |= (uint32_t)BLK;
    }
    else if(COMPx == COMP2)
    {
        /* Clear COMP2_CTRL BLKING bit */
        COMP->COMP2.CTRL &= COMP_BLANKING_MASK;
        /* Set COMP2_CTRL BLKING bit */
        COMP->COMP2.CTRL |= (uint32_t)BLK;
    }
    else if(COMPx == COMP3)
    {
        /* Clear COMP3_CTRL BLKING bit */
        COMP->COMP3.CTRL &= COMP_BLANKING_MASK;
        /* Set COMP3_CTRL BLKING bit */
        COMP->COMP3.CTRL |= (uint32_t)BLK;
    }
    else 
    {
        /* Clear COMP4_CTRL BLKING bit */
        COMP->COMP4.CTRL &= COMP_BLANKING_MASK;
        /* Set COMP4_CTRL BLKING bit */
        COMP->COMP4.CTRL |= (uint32_t)BLK;
    }
}

/**
*\*\name    COMP_SetHyst.
*\*\fun     Configure COMP hysteresis level.
*\*\param   COMPx:
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\          - COMP4
*\*\param   HYST :
*\*\          - COMP_CTRL_HYST_NO   
*\*\          - COMP_CTRL_HYST_LOW  
*\*\          - COMP_CTRL_HYST_MID     
*\*\          - COMP_CTRL_HYST_HIGH 
*\*\return  none
**/
void COMP_SetHyst(COMPX COMPx, COMP_CTRL_HYST HYST)
{
    if(COMPx == COMP1)
    {
        /* Clear COMP1_CTRL HYST[1:0] bits */
        COMP->COMP1.CTRL &= COMP_HYST_MASK;
        /* Set COMP1_CTRL HYST[1:0] bits */
        COMP->COMP1.CTRL |= (uint32_t)HYST;
    }
    else if(COMPx == COMP2)
    {
        /* Clear COMP2_CTRL HYST[1:0] bits */
        COMP->COMP2.CTRL &= COMP_HYST_MASK;
        /* Set COMP2_CTRL HYST[1:0] bits */
        COMP->COMP2.CTRL |= (uint32_t)HYST;
    }
    else if(COMPx == COMP3)
    {
        /* Clear COMP3_CTRL HYST[1:0] bits */
        COMP->COMP3.CTRL &= COMP_HYST_MASK;
        /* Set COMP3_CTRL HYST[1:0] bits */
        COMP->COMP3.CTRL |= (uint32_t)HYST;
    }
    else 
    {
        /* Clear COMP4_CTRL HYST[1:0] bits */
        COMP->COMP4.CTRL &= COMP_HYST_MASK;
        /* Set COMP4_CTRL HYST[1:0] bits */
        COMP->COMP4.CTRL |= (uint32_t)HYST;
    }
}

/**
*\*\name    COMP_OutputPolarityConfig.
*\*\fun     Configures COMP output signal polarity overturn or not.
*\*\param   COMPx:
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\          - COMP4
*\*\param   POL :
*\*\          - COMP_OUTPOL_REV   
*\*\          - COMP_OUTPOL_NREV   
*\*\return  none
**/
void COMP_OutputPolarityConfig(COMPX COMPx, uint32_t POL)
{
    if(COMPx == COMP1)
    {
        /* Clear COMP1_CTRL POL bits */
        COMP->COMP1.CTRL &= COMP_OUTPOL_MASK;
        /* Set COMP1_CTRL POL bits */
        COMP->COMP1.CTRL |= POL;
    }
    else if(COMPx == COMP2)
    {
        /* Clear COMP2_CTRL POL bits */
        COMP->COMP2.CTRL &= COMP_OUTPOL_MASK;
        /* Set COMP2_CTRL POL bits */
        COMP->COMP2.CTRL |= POL;
    }
    else if(COMPx == COMP3)
    {
        /* Clear COMP3_CTRL POL bits */
        COMP->COMP3.CTRL &= COMP_OUTPOL_MASK;
        /* Set COMP3_CTRL POL bits */
        COMP->COMP3.CTRL |= POL;
    }
    else 
    {
        /* Clear COMP4_CTRL POL bits */
        COMP->COMP4.CTRL &= COMP_OUTPOL_MASK;
        /* Set COMP4_CTRL POL bits */
        COMP->COMP4.CTRL |= POL;
    }
}

/**
*\*\name    COMP_SetInpSel.
*\*\fun     Configures COMP inpsel input selection.
*\*\param   COMPx:
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\          - COMP4
*\*\param   vpsel :
*\*\          - COMP1
*\*\            - COMP1_CTRL_INPSEL_PA2                   
*\*\            - COMP1_CTRL_INPSEL_PA3                   
*\*\            - COMP1_CTRL_INPSEL_VREF_VC1                   
*\*\            - COMP1_CTRL_INPSEL_PB1                  
*\*\          - COMP2
*\*\            - COMP2_CTRL_INPSEL_PB1                   
*\*\            - COMP2_CTRL_INPSEL_PA6                   
*\*\            - COMP2_CTRL_INPSEL_PB10                   
*\*\            - COMP2_CTRL_INPSEL_PA5                                     
*\*\            - COMP2_CTRL_INPSEL_VREF_VC2                   
*\*\          - COMP3
*\*\            - COMP3_CTRL_INPSEL_PA10                   
*\*\            - COMP3_CTRL_INPSEL_DAC_OUT_PB13                   
*\*\            - COMP3_CTRL_INPSEL_VREF_VC1                   
*\*\            - COMP3_CTRL_INPSEL_PD7                 
*\*\          - COMP4
*\*\            - COMP4_CTRL_INPSEL_PD7                   
*\*\            - COMP4_CTRL_INPSEL_PA12                   
*\*\            - COMP4_CTRL_INPSEL_PD5                   
*\*\            - COMP4_CTRL_INPSEL_VREF_VC2                 
*\*\return  none
**/
void COMP_SetInpSel(COMPX COMPx, COMP_CTRL_INPSEL VpSel)
{
    if(COMPx == COMP1)
    {
        /* Clear COMP1_CTRL INPSEL bit */
        COMP->COMP1.CTRL &= COMP_INPSEL_MASK;
        /* Set COMP1_CTRL INPSEL bit */
        COMP->COMP1.CTRL |= (uint32_t)VpSel;
    }
    else if(COMPx == COMP2)
    {
        /* Clear COMP2_CTRL INPSEL bit */
        COMP->COMP2.CTRL &= COMP_INPSEL_MASK;
        /* Set COMP2_CTRL INPSEL bit */
        COMP->COMP2.CTRL |= (uint32_t)VpSel;
    }
    else if(COMPx == COMP3)
    {
        /* Clear COMP3_CTRL INPSEL bit */
        COMP->COMP3.CTRL &= COMP_INPSEL_MASK;
        /* Set COMP3_CTRL INPSEL bit */
        COMP->COMP3.CTRL |= (uint32_t)VpSel;
    }
    else 
    {
        /* Clear COMP4_CTRL INPSEL bit */
        COMP->COMP4.CTRL &= COMP_INPSEL_MASK;
        /* Set COMP4_CTRL INPSEL bit */
        COMP->COMP4.CTRL |= (uint32_t)VpSel;
    }
}

/**
*\*\name    COMP_SetInmSel.
*\*\fun     Configures COMP inmsel input selection..
*\*\param   COMPx:
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\          - COMP4
*\*\param   VmSel :
*\*\          - COMP1
*\*\            - COMP1_CTRL_INMSEL_PA5                   
*\*\            - COMP1_CTRL_INMSEL_PB0         
*\*\            - COMP1_CTRL_INMSEL_PA2                   
*\*\            - COMP1_CTRL_INMSEL_VREF_VC1                    
*\*\            - COMP1_CTRL_INMSEL_DAC_OUT_PB13                  
*\*\          - COMP2
*\*\            - COMP2_CTRL_INMSEL_PA3     
*\*\            - COMP2_CTRL_INMSEL_PB2      
*\*\            - COMP2_CTRL_INMSEL_PA4                   
*\*\            - COMP2_CTRL_INMSEL_DAC_OUT_PB13      
*\*\          - COMP3
*\*\            - COMP3_CTRL_INMSEL_PA9     
*\*\            - COMP3_CTRL_INMSEL_PD6      
*\*\            - COMP3_CTRL_INMSEL_VREF_VC1                   
*\*\            - COMP3_CTRL_INMSEL_DAC_OUT_PB13     
*\*\          - COMP4
*\*\            - COMP4_CTRL_INMSEL_PA11     
*\*\            - COMP4_CTRL_INMSEL_PD4      
*\*\            - COMP4_CTRL_INMSEL_VREF_VC2                   
*\*\            - COMP4_CTRL_INMSEL_DAC_OUT_PB13
*\*\return  none
**/
void COMP_SetInmSel(COMPX COMPx, COMP_CTRL_INMSEL VmSel)
{
    if(COMPx == COMP1)
    {
        /* Clear COMP1_CTRL INMSEL bit */
        COMP->COMP1.CTRL &= COMP_INMSEL_MASK;
        /* Set COMP1_CTRL INMSEL bit */
        COMP->COMP1.CTRL |= (uint32_t)VmSel;
    }
    else if(COMPx == COMP2)
    {
        /* Clear COMP2_CTRL INMSEL bit */
        COMP->COMP2.CTRL &= COMP_INMSEL_MASK;
        /* Set COMP2_CTRL INMSEL bit */
        COMP->COMP2.CTRL |= (uint32_t)VmSel;
    }
    else if(COMPx == COMP3)
    {
        /* Clear COMP3_CTRL INMSEL bit */
        COMP->COMP3.CTRL &= COMP_INMSEL_MASK;
        /* Set COMP3_CTRL INMSEL bit */
        COMP->COMP3.CTRL |= (uint32_t)VmSel;
    }
    else 
    {
        /* Clear COMP4_CTRL INMSEL bit */
        COMP->COMP4.CTRL &= COMP_INMSEL_MASK;
        /* Set COMP4_CTRL INMSEL bit */
        COMP->COMP4.CTRL |= (uint32_t)VmSel;
    }
}

/**
*\*\name    COMP_SetOutTrig.
*\*\fun     Configures which Timer input must be connected with the comparator output.
*\*\param   COMPx:
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\          - COMP4
*\*\param   OutTrig :
*\*\          - COMP1
*\*\            - COMP1_CTRL_OUTSEL_T1_OCREFCLEAR
*\*\            - COMP1_CTRL_OUTSEL_T1_BKIN                
*\*\            - COMP1_CTRL_OUTSEL_T1_IC1  
*\*\            - COMP1_CTRL_OUTSEL_T2_IC1        
*\*\            - COMP1_CTRL_OUTSEL_T2_IC4              
*\*\            - COMP1_CTRL_OUTSEL_T2_OCREFCLEAR                                 
*\*\            - COMP1_CTRL_OUTSEL_T3_IC1  
*\*\            - COMP1_CTRL_OUTSEL_T3_IC4  
*\*\            - COMP1_CTRL_OUTSEL_T3_OCREFCLEAR  
*\*\            - COMP1_CTRL_OUTSEL_T4_IC1  
*\*\            - COMP1_CTRL_OUTSEL_T4_IC4  
*\*\            - COMP1_CTRL_OUTSEL_T4_OCREFCLEAR  
*\*\            - COMP1_CTRL_OUTSEL_T5_IC1  
*\*\            - COMP1_CTRL_OUTSEL_T5_IC4  
*\*\            - COMP1_CTRL_OUTSEL_T5_OCREFCLEAR  
*\*\          - COMP2
*\*\            - COMP2_CTRL_OUTSEL_T1_OCREFCLEAR
*\*\            - COMP2_CTRL_OUTSEL_T1_BKIN                
*\*\            - COMP2_CTRL_OUTSEL_T1_IC1  
*\*\            - COMP2_CTRL_OUTSEL_T2_IC1        
*\*\            - COMP2_CTRL_OUTSEL_T2_IC2             
*\*\            - COMP2_CTRL_OUTSEL_T2_OCREFCLEAR                                 
*\*\            - COMP2_CTRL_OUTSEL_T3_IC1  
*\*\            - COMP2_CTRL_OUTSEL_T3_IC2  
*\*\            - COMP2_CTRL_OUTSEL_T3_OCREFCLEAR  
*\*\            - COMP2_CTRL_OUTSEL_T4_IC1  
*\*\            - COMP2_CTRL_OUTSEL_T4_IC2  
*\*\            - COMP2_CTRL_OUTSEL_T4_OCREFCLEAR  
*\*\            - COMP2_CTRL_OUTSEL_T5_IC1  
*\*\            - COMP2_CTRL_OUTSEL_T5_IC2  
*\*\            - COMP2_CTRL_OUTSEL_T5_OCREFCLEAR  
*\*\          - COMP3
*\*\            - COMP3_CTRL_OUTSEL_T1_OCREFCLEAR
*\*\            - COMP3_CTRL_OUTSEL_T1_BKIN                
*\*\            - COMP3_CTRL_OUTSEL_T1_IC1  
*\*\            - COMP3_CTRL_OUTSEL_T2_IC1        
*\*\            - COMP3_CTRL_OUTSEL_T2_IC2             
*\*\            - COMP3_CTRL_OUTSEL_T2_OCREFCLEAR                                 
*\*\            - COMP3_CTRL_OUTSEL_T3_IC1  
*\*\            - COMP3_CTRL_OUTSEL_T3_IC2  
*\*\            - COMP3_CTRL_OUTSEL_T3_OCREFCLEAR  
*\*\            - COMP3_CTRL_OUTSEL_T4_IC1  
*\*\            - COMP3_CTRL_OUTSEL_T4_IC2  
*\*\            - COMP3_CTRL_OUTSEL_T4_OCREFCLEAR  
*\*\            - COMP3_CTRL_OUTSEL_T5_IC1  
*\*\            - COMP3_CTRL_OUTSEL_T5_IC2  
*\*\            - COMP3_CTRL_OUTSEL_T5_OCREFCLEAR  
*\*\          - COMP4
*\*\            - COMP4_CTRL_OUTSEL_T1_OCREFCLEAR
*\*\            - COMP4_CTRL_OUTSEL_T1_BKIN                
*\*\            - COMP4_CTRL_OUTSEL_T1_IC1  
*\*\            - COMP4_CTRL_OUTSEL_T2_IC3        
*\*\            - COMP4_CTRL_OUTSEL_T2_IC4              
*\*\            - COMP4_CTRL_OUTSEL_T2_OCREFCLEAR                                 
*\*\            - COMP4_CTRL_OUTSEL_T3_IC3  
*\*\            - COMP4_CTRL_OUTSEL_T3_IC4  
*\*\            - COMP4_CTRL_OUTSEL_T3_OCREFCLEAR  
*\*\            - COMP4_CTRL_OUTSEL_T4_IC3  
*\*\            - COMP4_CTRL_OUTSEL_T4_IC4  
*\*\            - COMP4_CTRL_OUTSEL_T4_OCREFCLEAR  
*\*\            - COMP4_CTRL_OUTSEL_T5_IC3  
*\*\            - COMP4_CTRL_OUTSEL_T5_IC4  
*\*\            - COMP4_CTRL_OUTSEL_T5_OCREFCLEAR 
*\*\return  none  
**/
void COMP_SetOutTrig(COMPX COMPx, COMP_CTRL_OUTTRIG OutTrig)
{
    if(COMPx == COMP1)
    {
        /* Clear COMP1_CTRL OUTSEL[3:0] bits */
        COMP->COMP1.CTRL &= COMP_OUTSEL_MASK;
        /* Set COMP1_CTRL OUTSEL[3:0] bits */ 
        COMP->COMP1.CTRL |= (uint32_t)OutTrig;
    }
    else if(COMPx == COMP2)
    {
        /* Clear COMP2_CTRL OUTSEL[3:0] bits */
        COMP->COMP2.CTRL &= COMP_OUTSEL_MASK;
        /* Set COMP2_CTRL OUTSEL[3:0] bits */ 
        COMP->COMP2.CTRL |= (uint32_t)OutTrig;
    }
    else if(COMPx == COMP3)
    {
        /* Clear COMP3_CTRL OUTSEL[3:0] bits */
        COMP->COMP3.CTRL &= COMP_OUTSEL_MASK;
        /* Set COMP3_CTRL OUTSEL[3:0] bits */ 
        COMP->COMP3.CTRL |= (uint32_t)OutTrig;
    }
    else 
    {
        /* Clear COMP4_CTRL OUTSEL[3:0] bits */
        COMP->COMP4.CTRL &= COMP_OUTSEL_MASK;
        /* Set COMP4_CTRL OUTSEL[3:0] bits */ 
        COMP->COMP4.CTRL |= (uint32_t)OutTrig;
    }
}

/**
*\*\name    COMP_Enable.
*\*\fun     Enable Oor disable COMP peripheral.
*\*\param   COMPx:
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\          - COMP4
*\*\param   Cmd new state of the COMP peripheral.
*\*\          -ENABLE 
*\*\          -DISABLE
*\*\return  none
**/
void COMP_Enable(COMPX COMPx , FunctionalState Cmd)
{
    if(COMPx == COMP1)
    {
        /* Set or reset the COMP1_CTRL EN bit */
        if(Cmd != DISABLE)
        {
            COMP->COMP1.CTRL |= COMP_ENABLE;
        }
        else
        {
            COMP->COMP1.CTRL &= (~COMP_ENABLE);
        }
    }
    else if(COMPx == COMP2)
    {
        /* Set or reset the COMP2_CTRL EN bit */
        if(Cmd != DISABLE)
        {
            COMP->COMP2.CTRL |= COMP_ENABLE;
        }
        else
        {
            COMP->COMP2.CTRL &= (~COMP_ENABLE);
        }
    }
    else if(COMPx == COMP3)
    {
        /* Set or reset the COMP3_CTRL EN bit */
        if(Cmd != DISABLE)
        {
            COMP->COMP3.CTRL |= COMP_ENABLE;
        }
        else
        {
            COMP->COMP3.CTRL &= (~COMP_ENABLE);
        }
    }
    else if(COMPx == COMP4)
    {
        /* Set or reset the COMP4_CTRL EN bit  */
        if(Cmd != DISABLE)
        {
            COMP->COMP4.CTRL |= COMP_ENABLE;
        }
        else
        {
            COMP->COMP4.CTRL &= (~COMP_ENABLE);
        }
    }
    else
    {
        /*no process*/
    }
}

/**
*\*\name    COMP_SetIntEn.
*\*\fun     Enable or disable COMP interrupt .
*\*\param   IntEn :
*\*\          - COMP1_INTEN
*\*\          - COMP2_INTEN
*\*\          - COMP3_INTEN
*\*\          - COMP4_INTEN
*\*\param   Cmd new state of the COMP peripheral.
*\*\          -ENABLE 
*\*\          -DISABLE
*\*\return  none
**/
void COMP_SetIntEn(uint32_t IntEn, FunctionalState Cmd)
{
    if(Cmd != DISABLE)
    {
        COMP->INTEN |= IntEn ;
    }
    else
    {
        COMP->INTEN &= (~IntEn) ;
    }
}

/**
*\*\name    COMP_GetIntStsOneComp.
*\*\fun     Get COMPx interrupt flag .
*\*\param   COMPx:
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\          - COMP4
*\*\return  FlagStatus:
*\*\          - SET
*\*\          - RESET
**/
FlagStatus COMP_GetIntStsOneComp(COMPX COMPx)
{
    return ((COMP->INTSTS &((uint32_t)0x01U << COMPx )) != 0) ? SET: RESET;
}

/**
*\*\name    COMP_GetOutStatus.
*\*\fun     Get COMP result Status before filtering .
*\*\param   COMPx:
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\          - COMP4
*\*\return  FlagStatus:
*\*\          - SET
*\*\          - RESET
**/
FlagStatus COMP_GetOutStatus(COMPX COMPx)
{
	FlagStatus status ;
    if(COMPx == COMP1)
	{
		status =((COMP->COMP1.CTRL & COMP_CTRL_OUT_MASK) == COMP_CTRL_OUT_MASK) ? SET : RESET;
	}
    else if(COMPx == COMP2)
	{
		status =((COMP->COMP2.CTRL & COMP_CTRL_OUT_MASK) == COMP_CTRL_OUT_MASK) ? SET : RESET;
	}
    else if(COMPx == COMP3)
	{
		status =((COMP->COMP3.CTRL & COMP_CTRL_OUT_MASK) == COMP_CTRL_OUT_MASK) ? SET : RESET;
	}
    else if(COMPx == COMP4)
	{
		status =((COMP->COMP4.CTRL & COMP_CTRL_OUT_MASK)==COMP_CTRL_OUT_MASK) ? SET : RESET;
	}
	else
	{
		status = RESET;
	}
	return status;
}

/**
*\*\name    COMP_GetFilterOutStatus.
*\*\fun     Get COMP result Status after filtering .
*\*\param   COMPx:
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\          - COMP4
*\*\return  FlagStatus:
*\*\          - SET
*\*\          - RESET
**/
FlagStatus COMP_GetFilterOutStatus(COMPX COMPx)
{
	FlagStatus status ;
    if(COMPx == COMP1)
	{
		status =((COMP->COMP1.CTRL & COMP_CTRL_FILT_OUT_MASK) == COMP_CTRL_FILT_OUT_MASK) ? SET : RESET;
	}
    else if(COMPx == COMP2)
	{
		status =((COMP->COMP2.CTRL & COMP_CTRL_FILT_OUT_MASK)== COMP_CTRL_FILT_OUT_MASK) ? SET : RESET;
	}
    else if(COMPx == COMP3)
	{
		status =((COMP->COMP3.CTRL & COMP_CTRL_FILT_OUT_MASK)== COMP_CTRL_FILT_OUT_MASK) ? SET : RESET;
	}
    else if(COMPx == COMP4)
	{
		status =((COMP->COMP4.CTRL & COMP_CTRL_FILT_OUT_MASK) == COMP_CTRL_FILT_OUT_MASK) ? SET : RESET;
	}
	else
	{
		status = RESET;
	}
	return status;
}

/**
*\*\name    COMP_IntStatusClear.
*\*\fun     Clear COMP interrupt flag.
*\*\param   intsts:
*\*\          - COMP_INTSTS_CMP1IS
*\*\          - COMP_INTSTS_CMP2IS
*\*\          - COMP_INTSTS_CMP3IS
*\*\          - COMP_INTSTS_CMP4IS
*\*\return  none
**/
void COMP_IntStatusClear(uint32_t intsts)
{
    COMP->INTSTS &= ~intsts;
}

/**
*\*\name    COMP_SetIntEn.
*\*\fun     Enable COMP Lock .
*\*\param   IntEn :
*\*\          - COMP1_LOCK
*\*\          - COMP2_LOCK
*\*\          - COMP3_LOCK
*\*\          - COMP4_LOCK
*\*\return  none
**/
void COMP_SetLock(uint32_t Lock)
{
    COMP->LOCK |= Lock ;
}


/**
*\*\name    COMP_CMPXorOut.
*\*\fun     Enable or disable COMP xor output .
*\*\param   COMP_XoOsel :
*\*\          - COMP2_OSEL_CMP2XO
*\*\          - COMP4_OSEL_CMP4XO
*\*\param   Cmd new state of the COMP peripheral.
*\*\          -ENABLE 
*\*\          -DISABLE
*\*\return  none
**/
void COMP_CMPXorOut(uint32_t COMP_XoOsel, FunctionalState Cmd)
{
    if(Cmd != DISABLE)
    {
        COMP->OSEL |= COMP_XoOsel ;
    }
    else
    {
        COMP->OSEL &= (~COMP_XoOsel) ;
    }
}

/**
*\*\name    COMP_SetRefScl.
*\*\fun     Set Reference Volatge Scale of Vv1 and Vv2 .
*\*\param   Vv2Trim :
*\*\          - this data range of 0-63 
*\*\param   Vv2En :
*\*\          - false
*\*\          - true  
*\*\param   Vv1Trim :
*\*\          - this data range of 0-63 
*\*\param   Vv1En :
*\*\          - false
*\*\          - true  
*\*\return  none
**/
void COMP_SetRefScl(uint8_t Vv2Trim, bool Vv2En, uint8_t Vv1Trim, bool Vv1En)
{
    __IO uint32_t tmp = 0;

    tmp |=  ((((uint32_t )Vv1Trim) << 1) | (uint32_t )(Vv1En ? 0x01 : 0));
    tmp |=  ((((uint32_t )Vv2Trim) << 8) | ((uint32_t )(Vv2En ? 0x01 : 0)<<7));

    COMP->VREFSCAL = tmp;
}

/**
*\*\name    COMP_OutTimEn.
*\*\fun     Enable the connection of the comparator's output to TIM .
*\*\param   CompxOut :
*\*\          - CMP1_TIM_EN
*\*\          - CMP2_TIM_EN
*\*\          - CMP3_TIM_EN
*\*\          - CMP4_TIM_EN
*\*\param   Cmd new state of the COMP peripheral.
*\*\          -ENABLE 
*\*\          -DISABLE
*\*\return  none
**/
void COMP_OutTimEn(uint32_t CompxOut, FunctionalState Cmd)
{
    if(Cmd != DISABLE)
    {
        COMP->TIM_OSEL |= CompxOut ;
    }
    else
    {
        COMP->TIM_OSEL &= (~CompxOut) ;
    }
}
