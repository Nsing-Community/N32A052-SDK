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
*\*\file n32a052_pwr.c
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/
#include "n32a052_rcc.h"
#include "n32a052_pwr.h"

/** PWR Private Defines **/


/** PWR Driving Functions Declaration **/

/**
*\*\name    PWR_DeInit.
*\*\fun     Deinitializes the PWR peripheral registers to their default reset values.
*\*\param   none
*\*\return  none
**/
void PWR_DeInit(void)
{
    RCC_EnableAPB1PeriphReset(RCC_APB1_PERIPH_PWR);
}

/**
*\*\name    PWR_PvdEnable.
*\*\fun     Enables or disables the Power Voltage Detector(PVD).
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\return  none
**/
void PWR_PvdEnable(FunctionalState Cmd)
{
    if(Cmd == ENABLE)
    {
        PWR->CTRL |= PWR_PVD_ENABLE;
    }
    else
    {
        PWR->CTRL &= (~PWR_PVD_ENABLE);
    }
}


/**
*\*\name    PWR_PVDIntEnable.
*\*\fun     Enables or disables the Power Voltage Detector Interrupt.
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\return  none
**/
void PWR_PVDIntEnable(FunctionalState Cmd)
{
    if(Cmd == ENABLE)
    {
        PWR->CTRL |= PWR_PVD_INT_ENABLE;
    }
    else
    {
        PWR->CTRL &= (~PWR_PVD_INT_ENABLE);
    }
    
}

/**
*\*\name    PWR_PVDFilterWidthSet.
*\*\fun     Adjusting the PVD Filter Control Count value.
*\*\param   filter_value(Filter Width = (1/fLSI) * filter_value):
*\*\        -0 ~ 0xFF
*\*\return  none
**/ 
void PWR_PVDFilterWidthSet(uint8_t filter_value) 
{
    uint32_t temp_value;

    temp_value = PWR->CTRL;
    /* Clear PVDCNT[7:0] bits */
    temp_value &= PWR_CTRL_PVDCNT_MASK;
    /* Set the PVDCNT[7:0] bits according to filter_value */
    temp_value |= (uint32_t)filter_value << 16; 
    /* Store the new value */
    PWR->CTRL = temp_value;
}

/**
*\*\name    PWR_PVDFilterEnable.
*\*\fun     Enables or disables the Power Voltage Detector Filter.
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\return  none
**/
void PWR_PVDFilterEnable(FunctionalState Cmd)
{
    if(Cmd == ENABLE)
    {
        PWR->CTRL |= PWR_PVD_FIL_ENABLE;
    }
    else
    {
        PWR->CTRL &= (~PWR_PVD_FIL_ENABLE);
    }
    
}

/**
*\*\name    PWR_PVDLevelConfig.
*\*\fun     Configures the voltage threshold detected by the Power Voltage Detector(PVD).
*\*\param   level (The input parameters must be the following values):
*\*\          - PWR_PVD_LEVEL_2V0
*\*\          - PWR_PVD_LEVEL_2V2
*\*\          - PWR_PVD_LEVEL_2V4
*\*\          - PWR_PVD_LEVEL_2V6
*\*\          - PWR_PVD_LEVEL_2V8
*\*\          - PWR_PVD_LEVEL_3V0
*\*\          - PWR_PVD_LEVEL_3V2
*\*\          - PWR_PVD_LEVEL_3V4
*\*\          - PWR_PVD_LEVEL_3V6
*\*\          - PWR_PVD_LEVEL_3V8
*\*\          - PWR_PVD_LEVEL_4V0
*\*\          - PWR_PVD_LEVEL_4V2
*\*\          - PWR_PVD_LEVEL_4V4
*\*\          - PWR_PVD_LEVEL_4V6
*\*\          - PWR_PVD_LEVEL_4V8
*\*\return  none
**/
void PWR_PVDLevelConfig(uint32_t level)
{
    uint32_t temp_value;
    
    temp_value = PWR->CTRL;
    /* Clear PLS[8:5] bits bit */
    temp_value &= PWR_CTRL_PLS_MASK;
    /* Set PLS[8:5] bits according to level value */
    temp_value |= level;
    /* Store the new value */
    PWR->CTRL = temp_value;
}

/**
*\*\name    PWR_LVREnable.
*\*\fun     Enables or disables the Low Voltage Detector(LVR).
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\return  none
*\*\note    Needs to be unlocked first by PWR_CTRL2WriteProtectionEnable 
**/
void PWR_LVREnable(FunctionalState Cmd)
{
    if(Cmd == ENABLE)
    {
        PWR->CTRL2 |= PWR_LVR_ENABLE;
    }
    else
    {
        PWR->CTRL2 &= (~PWR_LVR_ENABLE);
    }
    
}

/**
*\*\name    PWR_LVRResetEnable.
*\*\fun     Enables or disables the Low Voltage Detector reset.
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\return  none
*\*\note    Needs to be unlocked first by PWR_CTRL2WriteProtectionEnable 
**/
void PWR_LVRResetEnable(FunctionalState Cmd)
{
    if(Cmd == ENABLE)
    {
        PWR->CTRL2 |= PWR_LVR_RST_ENABLE;
    }
    else
    {
        PWR->CTRL2 &= (~PWR_LVR_RST_ENABLE);
    }
    
}

/**
*\*\name    PWR_LVRFilterWidthSet.
*\*\fun     Adjusting the LVR Filter Control Count value.
*\*\param   filter_value(Filter Width = (1/fLSI) * filter_value):
*\*\        -0 ~ 0xFF
*\*\return  none
*\*\note    Needs to be unlocked first by PWR_CTRL2WriteProtectionEnable 
**/ 
void PWR_LVRFilterWidthSet(uint8_t filter_value) 
{
    uint32_t temp_value;

    temp_value = PWR->CTRL2;
    /* Clear LVRCNT[7:0] bits */
    temp_value &= PWR_CTRL2_LVRCNT_MASK;
    /* Set the LVRCNT[7:0] bits according to filter_value */
    temp_value |= (uint32_t)filter_value; 
    /* Store the new value */
    PWR->CTRL2 = temp_value;
}

/**
*\*\name    PWR_LVRFilterEnable.
*\*\fun     Enables or disables the Low Voltage Detector Filter.
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\return  none
*\*\note    Needs to be unlocked first by PWR_CTRL2WriteProtectionEnable 
**/
void PWR_LVRFilterEnable(FunctionalState Cmd)
{
    if(Cmd == ENABLE)
    {
        PWR->CTRL2 |= PWR_LVR_FIL_ENABLE;
    }
    else
    {
        PWR->CTRL2 &= (~PWR_LVR_FIL_ENABLE);
    }
    
}

/**
*\*\name    PWR_LVRLevelConfig.
*\*\fun     Configures the voltage threshold detected by the Low Voltage Detector(LVR).
*\*\param   level (The input parameters must be the following values):
*\*\          - PWR_LVR_LEVEL_2V0 
*\*\          - PWR_LVR_LEVEL_2V2
*\*\          - PWR_LVR_LEVEL_2V4
*\*\          - PWR_LVR_LEVEL_2V6
*\*\          - PWR_LVR_LEVEL_2V8
*\*\          - PWR_LVR_LEVEL_3V0
*\*\          - PWR_LVR_LEVEL_3V2
*\*\          - PWR_LVR_LEVEL_3V4
*\*\          - PWR_LVR_LEVEL_3V6
*\*\          - PWR_LVR_LEVEL_3V8
*\*\          - PWR_LVR_LEVEL_4V0
*\*\          - PWR_LVR_LEVEL_4V2
*\*\          - PWR_LVR_LEVEL_4V4
*\*\          - PWR_LVR_LEVEL_4V6
*\*\          - PWR_LVR_LEVEL_4V8
*\*\return  none
*\*\note    Needs to be unlocked first by PWR_CTRL2WriteProtectionEnable 
**/
void PWR_LVRLevelConfig(uint32_t level)
{
    uint32_t temp_value;
    
    temp_value = PWR->CTRL2;
    /* Clear LVRS[14:11] bits*/
    temp_value &= PWR_CTRL2_LVRLS_MASK;
    /* Set LVRS[14:11] bits according to level value */
    temp_value |= level;
    /* Store the new value */
    PWR->CTRL2 = temp_value;
}


/**
*\*\name    PWR_NRSTFilterWidthSet.
*\*\fun     Adjusting the NRST Filter Control Count value.
*\*\param   filter_value(Filter Width = (1/fSYSCLK) * filter_value):
*\*\        -0 ~ 0x7FF
*\*\return  none
**/ 
void PWR_NRSTFilterWidthSet(uint16_t filter_value) 
{
    uint32_t temp_value;

    temp_value = PWR->CTRL3;
    /* Clear NRSTCNT[10:0] bits */
    temp_value &= PWR_CTRL3_NRSTCNT_MASK;
    /* Set the NRSTCNT[10:0] bits according to filter_value */
    temp_value |= (uint32_t)filter_value << 16; 
    /* Store the new value */
    PWR->CTRL3 = temp_value;
}

/**
*\*\name    PWR_NRSTFilterEnable.
*\*\fun     Enables or disables the NRST pin Filter.
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\return  none
**/
void PWR_NRSTFilterEnable(FunctionalState Cmd)
{
    if(Cmd == ENABLE)
    {
        PWR->CTRL3 |= PWR_NRST_FIL_ENABLE;
    }
    else
    {
        PWR->CTRL3 &= (~PWR_NRST_FIL_ENABLE);
    }
    
}


/**
*\*\name    PWR_WakeUpPinEnable.
*\*\fun     Enables the Wakeup Pin functionality.
*\*\param   pin (The input parameters must be the following values):
*\*\          - WKUP_PIN1   WKUP0(PA0)
*\*\          - WKUP_PIN2   WKUP1(PA2)
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\return  none
**/
void PWR_WakeUpPinEnable(WAKEUP_PINX pin, FunctionalState Cmd)
{
    uint32_t temp_value;
    
    temp_value = PWR->CTRLSTS;
    if(Cmd == ENABLE)
    {
        /* Set WKUP1EN or WKUP0EN bit */
        temp_value |= (uint32_t)pin;
    }
    else
    {
        /* Clear WKUP1EN or WKUP0EN bit*/
        temp_value &= (~(uint32_t)pin);
    }
    /* Store the new value */
    PWR->CTRLSTS = temp_value;
}

/**
*\*\name    PWR_WakeUpPinPolarity.
*\*\fun     Disables the WakeUp Pin functionality.
*\*\param   polarity (The input parameters must be the following values):
*\*\          - WKUP_POL_RISE
*\*\          - WKUP_POL_DOWN
*\*\return  none
**/
void PWR_WakeUpPinPolarity(WAKEUP_PIN_POL polarity)
{
    uint32_t temp_value;

    temp_value = PWR->CTRLSTS;
    /* Clear WKUPPOL bit*/
    temp_value &= (PWR_CTRLSTS_WKUPPOL_MASK);
    /* Set WKUPPOL bit */
    temp_value |= ((uint32_t)polarity << PWR_BIT_SHIFT_11);
    /* Store the new value */
    PWR->CTRLSTS = temp_value;
}

/**
*\*\name    PWR_EnterSLEEPMode.
*\*\fun     Enters SLEEP mode.
*\*\param   status (The input parameters must be the following values):
*\*\          - PWR_SLEEP_ON_EXIT
*\*\          - PWR_SLEEP_NOW
*\*\param   enter_mode (The input parameters must be the following values):
*\*\          - PWR_SLEEPENTRY_WFI enter SLEEP mode with WFI instruction
*\*\          - PWR_SLEEPENTRY_WFE enter SLEEP mode with WFE instruction
*\*\return  none
**/
void PWR_EnterSLEEPMode(PWR_SLEEPONEXIT_STATUS status, uint8_t enter_mode)
{
    /* CLEAR SLEEPDEEP bit of Cortex System Control Register */
    SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPDEEP);
    
    /* Select SLEEPONEXIT mode entry */
    if (status == PWR_SLEEP_ON_EXIT)
    {
        /* the MCU enters Sleep mode as soon as it exits the lowest priority INTSTS */
        SCB->SCR |= SCB_SCR_SLEEPONEXIT;
    }
    else 
    {
        /* Sleep-now */
        SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPONEXIT);
    }

    /* Select SLEEP mode entry */
    if (enter_mode == PWR_SLEEPENTRY_WFI)
    {
        /* Request Wait For Interrupt */
        __WFI();
    }
    else
    {
        /* Request Wait For Event */
        __SEV();
        __WFE();
        __WFE();
    }
}

/**
*\*\name    PWR_EnterSTOPMode.
*\*\fun     Enters STOP mode.
*\*\param   enter_mode (The input parameters must be the following values):
*\*\          - PWR_STOPENTRY_WFI (enter STOP mode with WFI instruction)
*\*\          - PWR_STOPENTRY_WFE (enter STOP mode with WFE instruction)
*\*\return  none
**/
void PWR_EnterSTOPMode(uint8_t enter_mode)
{
    uint32_t temp_value;
    
    temp_value = PWR->CTRL;
    /* Clear PDSTP bits */
    temp_value &= PWR_CTRL_PDSTP_MASK;
    /* Store the new value */
    PWR->CTRL = temp_value;
    /* Set SLEEPDEEP bit of Cortex System Control Register */
    SCB->SCR |= SCB_SCR_SLEEPDEEP;

    /* Select STOP mode entry */
    if (enter_mode == PWR_STOPENTRY_WFI)
    {
        /* Request Wait For Interrupt */
        __WFI();
    }
    else
    {
        /* Request Wait For Event */
        __SEV();
        __WFE();
        __WFE();
    }
    /* Reset SLEEPDEEP bit of Cortex System Control Register */
    SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPDEEP);
}

/**
*\*\name    PWR_EnterPDMode.
*\*\fun     Enters PD mode.
*\*\param   enter_mode (The input parameters must be the following values):
*\*\          - PWR_PDENTRY_WFI (enter PD mode with WFI instruction)
*\*\          - PWR_PDENTRY_WFE (enter PD mode with WFE instruction)
*\*\return  none
**/
void PWR_EnterPDMode(uint8_t enter_mode)
{
    /* Clear Wake-up flag */
    PWR->CTRL |= PWR_CLEAR_WKUPF;
    /* Clear PDS bits */
    PWR->CTRL &= PWR_CTRL_PDSTP_MASK;
    /* Select PD mode */
    PWR->CTRL |= PWR_PD_MODE;
    /* Set SLEEPDEEP bit of Cortex System Control Register */
    SCB->SCR |= SCB_SCR_SLEEPDEEP;
    /* This option is used to ensure that store operations are completed */
#if defined(__CC_ARM)
    __force_stores();
#endif
    /* Select PD mode entry */
    if (enter_mode == PWR_PDENTRY_WFI)
    {
        /* Request Wait For Interrupt */
        __WFI();
    }
    else
    {
        /* Request Wait For Event */
        __SEV();
        __WFE();
        __WFE();
    }
}

/**
*\*\name    PWR_PDRTriggerLevelConfig.
*\*\fun     VDDD PDR trigger level configuration in STOP mode.
*\*\param   level (The input parameters must be the following values):
*\*\          - PWR_PDR_LEVEL_1V0
*\*\          - PWR_PDR_LEVEL_1V2
*\*\return  none
**/
void PWR_PDRTriggerLevelConfig(uint32_t level)
{
    uint32_t temp_value;
    
    /* Enable PDR select signal is controlled by the PWR */
    PWR->CTRL3 |= PWR_CONTROL_PDR_SEL;

    temp_value = PWR->CTRL;
    /* Clear PDRS[10:9] bits*/
    temp_value &= PWR_CTRL_PDRS_MASK;
    /* Set PDRS[10:9] bits according to level value */
    temp_value |= level;
    /* Store the new value */
    PWR->CTRL = temp_value;
}

/**
*\*\name    PWR_VDDDOutputConfig.
*\*\fun     After the chip enters STOP mode, configure the output voltage of VDDD.
*\*\param   voltage_output (The input parameters must be the following values):
*\*\          - PWR_VDDD_OUTPUT_1V5
*\*\          - PWR_VDDD_OUTPUT_1V2
*\*\return  none
*\*\note    When configuring PWR_VDDD_OUTPUT_1V2, you must first call
*\*\        PWR_PDRTriggerLevelConfig() function with the parameter PWR_PDR_LEVEL_1V0,
*\*\        When configuring PWR_VDDD_OUTPUT_1V5, you must first call
*\*\        PWR_PDRTriggerLevelConfig() function with the parameter PWR_PDR_LEVEL_1V2.
**/
void PWR_VDDDOutputConfig(uint32_t voltage_output)
{
    uint32_t temp_value;
    
    /* Enable VDDD output voltage select */
    PWR->CTRL6 |= PWR_VDDD_OUTPUT_SEL_EN;

    temp_value = PWR->CTRL5;
    /* Clear STPMRSEL[3:2] bits*/
    temp_value &= PWR_CTRL5_STPMRSEL_MASK;
    /* Set STPMRSEL[3:2] bits according to level value */
    temp_value |= voltage_output;
    /* Store the new value */
    PWR->CTRL5 = temp_value;
}


/**
*\*\name    PWR_CTRL2WriteProtectionEnable.
*\*\fun     Enable the PWR_CTRL2 registers write protection.
*\*\param   none
*\*\return  none
*\*\note    This register has write protection.Before writing PWR_CTRL2, PWR_CTRL2WriteProtectionEnable()
*\*\        function must be called, and then write real value to PWR_CTRL2
**/
void PWR_CTRL2WriteProtectionEnable(void) 
{
    uint32_t temp_value;

    temp_value = PWR->CTRL2;
    
    /* Clear LVRKEY bits*/
    temp_value &= PWR_CTRL2_KEYS_MASK;
    /* Set LVRKEY bits*/
    temp_value |= PWR_CTRL2_KEYS;
    /* Store the new value */
    PWR->CTRL2 = temp_value;
}

/**
*\*\name    PWR_CTRL4WriteProtectionEnable.
*\*\fun     Enable the PWR_CTRL4 registers write protection.
*\*\param   none
*\*\return  none
*\*\note    This register has write protection.Before writing PWR_CTRL4, PWR_CTRL4WriteProtectionEnable()
*\*\        function must be called, and then write real value to PWR_CTRL4
**/
void PWR_CTRL4WriteProtectionEnable(void) 
{
    /* Enable the write protection for PWR_CTRL4 registers */
    PWR->CTRL4 = PWR_CTRL4_KEYS;
}

/**
*\*\name    PWR_GetFlagStatus.
*\*\fun     Checks whether the specified PWR flag is set or not.
*\*\param   flag (The input parameters must be the following values):
*\*\          - PWR_DBGPD_WKUP_FLAG    Wakeup DBGPD mode flag
*\*\          - PWR_DBGPD_FLAG         Input DBGPD mode flag
*\*\          - PWR_PVDO_FLAG          PVD Output flag 
*\*\          - PWR_LVRO_FLAG          LVR Output flag  
*\*\          - PWR_RUN_FLAG           RUN mode flag
*\*\return  SET or RESET.
**/
FlagStatus PWR_GetFlagStatus(uint32_t flag)
{
    uint32_t temp_value;
    uint32_t reg_value;
    FlagStatus bitstatus;

    /* Get the RCC register index */
    temp_value = flag >> 29;
    switch(temp_value)
    {
        case 1: /* The flag to check is in CTRLSTS register */
            reg_value = PWR->CTRLSTS;
            break;
        case 2: /* The flag to check is in CTRL2 register */
           reg_value = PWR->CTRL2;
           break;
        default:/* The flag to check is in CTRL4 register */
           reg_value = PWR->CTRL4;
           break;
    }
  
    /* Check the status of the PWR flag */
    if ((reg_value & (flag & (uint32_t)0xFFFF)) == (uint32_t)RESET)
    {
        /* PWR Flag is reset */
        bitstatus = RESET;
    }
    else
    {
        /* PWR Flag is set */
        bitstatus = SET;
    }
    return bitstatus;
   
}

/**
*\*\name    PWR_ClearFlag.
*\*\fun     Clears the PWR's pending flags.
*\*\param   flag (The input parameters must be the following values):
*\*\          - PWR_DBGPD_WKUP_FLAG    Wakeup DBGPD mode flag
*\*\          - PWR_DBGPD_FLAG         Input DBGPD mode flag
*\*\return  none
**/
void PWR_ClearFlag(uint32_t flag)
{
    PWR->CTRL |= (flag << PWR_BIT_SHIFT_2);
}

/**
*\*\name    DBG_ConfigPeriph.
*\*\fun     Configures the specified peripheral run when the MCU under Debug mode.
*\*\param   DBG_Periph (The input parameters must be the following values):
*\*\          - PWR_DBG_SLEEP   Keep debugger connection during SLEEP mode
*\*\          - PWR_DBG_STOP    Keep debugger connection during STOP mode
*\*\          - PWR_DBG_PD      Keep debugger connection during PD mode
*\*\          - PWR_DBG_IWDG    IWDG stopped when Core is halted
*\*\          - PWR_DBG_WWDG    WWDG stopped when Core is halted
*\*\          - PWR_DBG_TIM1    TIM1 counter stopped when Core is halted
*\*\          - PWR_DBG_TIM3    TIM3 counter stopped when Core is halted
*\*\          - PWR_DBG_CAN     CAN stopped when Core is halted
*\*\          - PWR_DBG_I2C1    I2C1 SMBUS timeout mode stopped stopped when Core is halted
*\*\          - PWR_DBG_I2C2    I2C2 SMBUS timeout mode stopped stopped when Core is halted
*\*\          - PWR_DBG_TIM6    TIM6 counter stopped when Core is halted
*\*\          - PWR_DBG_TIM5    TIM5 counter stopped when Core is halted
*\*\          - PWR_DBG_TIM4    TIM4 counter stopped when Core is halted
*\*\          - PWR_DBG_TIM2    TIM2 counter stopped when Core is halted
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\return  none
**/
void DBG_ConfigPeriph(uint32_t DBG_Periph, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        PWR->DBG_CTRL |= DBG_Periph;
    }
    else
    {
        PWR->DBG_CTRL &= (~DBG_Periph);
    }
    
}

/**
*\*\name    PWR_EnableIWDGReset.
*\*\fun     Configure whether to generate a reset request when the IWDG counter reaches 0.
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE   
*\*\return  none. 
**/
void PWR_EnableIWDGReset(FunctionalState Cmd)
{ 
   if(Cmd == ENABLE)
   {
       /* Set IWDGRSTEN bit */
       PWR->CTRL |= PWR_IWDGRST_ENABLE;
   }
   else
   {
       /* Reset IWDGRSTEN bit */
       PWR->CTRL &= (~PWR_IWDGRST_ENABLE);
   }
    
}

/**
*\*\name    PWR_EnableFlashDeepStandby.
*\*\fun     Configure whether or not FLASH enters deep standby mode.
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\return  none.  
*\*\note    Needs to be unlocked first by PWR_CTRL4WriteProtectionEnable  
**/
void PWR_EnableFlashDeepStandby(FunctionalState Cmd)
{ 
   if(Cmd == ENABLE)
   {
       /* Set STBFLH bit */
       PWR->CTRL4 |= PWR_FLASH_DS_ENABLE;
   }
   else
   {
       /* Reset STBFLH bit */
       PWR->CTRL4 &= (~PWR_FLASH_DS_ENABLE);
   }
    
}

/**
*\*\name    PWR_EnableFlashFastWakeup.
*\*\fun     Configure FLASH for fast wakeup or not.
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE
*\*\return  none.   
*\*\note    Needs to be unlocked first by PWR_CTRL4WriteProtectionEnable 
**/
void PWR_EnableFlashFastWakeup(FunctionalState Cmd)
{ 
   if(Cmd == ENABLE)
   {
       /* Set STBFLH bit */
       PWR->CTRL4 |= PWR_FLASH_FW_ENABLE;
   }
   else
   {
       /* Reset STBFLH bit */
       PWR->CTRL4 &= (~PWR_FLASH_FW_ENABLE);
   }
    
}

