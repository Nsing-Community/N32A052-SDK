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
*\*\file n32a052_lcd.c
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/
#include "n32a052_rcc.h"
#include "n32a052_lcd.h"


/** lCD Driving Functions Declaration **/

/**
*\*\name    LCD_DeInit.
*\*\fun     Reset the LCD registers.
*\*\return  none
**/
void LCD_DeInit(void)
{
    RCC_EnableAPB1PeriphReset(RCC_APB1_PERIPH_LCD);
}


/**
*\*\name    LCD_Enable.
*\*\fun     LCD turn on.
*\*\return  none
**/
void LCD_Enable(void)
{
    /* Set LCD_CTRL EN bit */
    LCD->CTRL |= LCD_ON;
}
/**
*\*\name    LCD_Disable.
*\*\fun     LCD turn off.
*\*\return  none
**/
void LCD_Disable(void)
{
    /* Reset LCD_CTRL EN bit */
    LCD->CTRL &= LCD_OFF;
}

/**
*\*\name    LCD_HIGHDRIVE_BUF_ENABLE.
*\*\fun     Enable the LCD voltage output buffer.
*\*\return  none
**/
void LCD_HIGHDRIVE_BUF_ENABLE(void)
{
    /* Set LCD_CTRL EN bit */
    LCD->CTRL |= LCD_CTRL_BUFEN;
}
/**
*\*\name    LCD_HIGHDRIVE_BUF_DISABLE.
*\*\fun     Disable the LCD voltage output buffer.
*\*\return  none
**/
void LCD_HIGHDRIVE_BUF_DISABLE(void)
{
    /* Reset LCD_CTRL EN bit */
    LCD->CTRL &= (~LCD_CTRL_BUFEN);
}

/**
*\*\name    LCD_VLCD_SELECT_ENABLE.
*\*\fun     Enable contrast control VLCD adjustable.
*\*\return  none
**/
void LCD_VLCD_SELECT_ENABLE(void)
{
    /* Set LCD_CTRL EN bit */
    LCD->CTRL |= LCD_CTRL_VSEL;
}
/**
*\*\name    LCD_VLCD_SELECT_DISABLE.
*\*\fun     Disable contrast control VLCD adjustable.
*\*\return  none
**/
void LCD_VLCD_SELECT_DISABLE(void)
{
    /* Reset LCD_CTRL EN bit */
    LCD->CTRL &= (~LCD_CTRL_VSEL);
}

/**
*\*\name    LCD_High_Drive_Enable.
*\*\fun     Enable the LCD High drive output.
*\*\return  none
**/
void LCD_High_Drive_Enable(void)
{
    /* Set LCD_FCTRL HDEN Bit */
    LCD->FCTRL |= LCD_FCTRL_HDEN;
}

/**
*\*\name    LCD_High_Drive_Disable.
*\*\fun     Disable the LCD High drive output.
*\*\return  none
**/
void LCD_High_Drive_Disable(void)
{
    /* Clear LCD_FCTRL HDEN Bit */
    LCD->FCTRL &= (~LCD_FCTRL_HDEN);
}

/**
*\*\name    LCD_PRESCALER_CONFIG.
*\*\fun     LCD clock prescaler congfiguration.
*\*\param   freq :
*\*\          - LCD_PRESCALER_1
*\*\          - LCD_PRESCALER_2
*\*\          - LCD_PRESCALER_4 
*\*\          - LCD_PRESCALER_8
*\*\          - LCD_PRESCALER_16 
*\*\          - LCD_PRESCALER_32 
*\*\          - LCD_PRESCALER_64 
*\*\          - LCD_PRESCALER_128 
*\*\          - LCD_PRESCALER_256 
*\*\          - LCD_PRESCALER_512 
*\*\          - LCD_PRESCALER_1024 
*\*\          - LCD_PRESCALER_2048 
*\*\          - LCD_PRESCALER_4096 
*\*\          - LCD_PRESCALER_8192 
*\*\          - LCD_PRESCALER_16384 
*\*\          - LCD_PRESCALER_32768
*\*\return  none
**/
void LCD_PRESCALER_CONFIG(uint32_t pres)
{
    uint32_t tmp = LCD->FCTRL;
    /* Clear LCD_FCTRL PRES[3:0] */
    tmp &= LCD_PRESCALER_MASK;
    /* Set LCD_FCTRL PRES[3:0] */
    tmp |= pres;
    LCD->FCTRL = tmp;
}


/**
*\*\name    LCD_DIVIDER_CONFIG.
*\*\fun     LCD clock divider congfiguration.
*\*\param   div :
*\*\          - LCD_DIV_16
*\*\          - LCD_DIV_17 
*\*\          - LCD_DIV_18
*\*\          - LCD_DIV_19 
*\*\          - LCD_DIV_20 
*\*\          - LCD_DIV_21 
*\*\          - LCD_DIV_22 
*\*\          - LCD_DIV_23 
*\*\          - LCD_DIV_24 
*\*\          - LCD_DIV_25 
*\*\          - LCD_DIV_26 
*\*\          - LCD_DIV_27 
*\*\          - LCD_DIV_28 
*\*\          - LCD_DIV_29 
*\*\          - LCD_DIV_30 
*\*\          - LCD_DIV_31 
*\*\return  none
**/
void LCD_DIVIDER_CONFIG(uint32_t div)
{
    uint32_t tmp = LCD->FCTRL;
    /* Clear LCD_FCTRL DIV[3:0] */
    tmp &= LCD_DIV_MASK;
    /* Set LCD_FCTRL DIV[3:0] */
    tmp |= div;
    LCD->FCTRL = tmp;
}

/**
*\*\name    LCD_BLINK_CONFIG.
*\*\fun     LCD blink frequency congfiguration.
*\*\param   freq :
*\*\          - LCD_BLINKFREQ_DIV_8
*\*\          - LCD_BLINKFREQ_DIV_16 
*\*\          - LCD_BLINKFREQ_DIV_32
*\*\          - LCD_BLINKFREQ_DIV_64 
*\*\          - LCD_BLINKFREQ_DIV_128 
*\*\          - LCD_BLINKFREQ_DIV_256 
*\*\          - LCD_BLINKFREQ_DIV_512 
*\*\          - LCD_BLINKFREQ_DIV_1024 
*\*\return  none
**/
void LCD_BLINK_CONFIG(uint32_t freq)
{
    uint32_t tmp = LCD->FCTRL;
    /* Clear LCD_FCTRL BLINKF[2:0] */
    tmp &= LCD_BLINKFREQ_MASK;
    /* Set LCD_FCTRL BLINKF[2:0] */
    tmp |= freq;
    LCD->FCTRL = tmp;
}

/**
*\*\name    LCD_Blink_Mode_Config.
*\*\fun     LCD Blink mode congfiguration.
*\*\param   blink_mode :
*\*\          - LCD_BLINKMODE_OFF
*\*\          - LCD_BLINKMODE_SEG0_COM0 
*\*\          - LCD_BLINKMODE_SEG0_ALLCOM
*\*\          - LCD_BLINKMODE_ALLSEG_ALLCOM 
*\*\return  none
**/
void LCD_Blink_Mode_Config(uint32_t blink_mode)
{
    uint32_t tmp = LCD->FCTRL;
    /* Clear LCD_FCTRL BLINK[1:0] */
    tmp &= LCD_BLINKMODE_MASK;
    /* Set LCD_FCTRL BLINK[1:0] */
    tmp |= blink_mode;
    LCD->FCTRL = tmp;
}


/**
*\*\name    LCD_Contrast_Config.
*\*\fun     Contrast control congfiguration.
*\*\param   contrast :
*\*\          - LCD_CONTRASTLEVEL_0
*\*\          - LCD_CONTRASTLEVEL_1 
*\*\          - LCD_CONTRASTLEVEL_2
*\*\          - LCD_CONTRASTLEVEL_3 
*\*\          - LCD_CONTRASTLEVEL_4
*\*\          - LCD_CONTRASTLEVEL_5
*\*\          - LCD_CONTRASTLEVEL_6 
*\*\          - LCD_CONTRASTLEVEL_7 
*\*\          - LCD_CONTRASTLEVEL_8
*\*\          - LCD_CONTRASTLEVEL_9 
*\*\          - LCD_CONTRASTLEVEL_10
*\*\          - LCD_CONTRASTLEVEL_11 
*\*\          - LCD_CONTRASTLEVEL_12
*\*\          - LCD_CONTRASTLEVEL_13
*\*\          - LCD_CONTRASTLEVEL_14 
*\*\          - LCD_CONTRASTLEVEL_15 
*\*\return  none
**/
void LCD_CONTRAST_CONFIG(uint32_t contrast)
{
    uint32_t tmp = LCD->FCTRL;
    /* Clear LCD_FCTRL LCD_CONTRAST[3:0] */
    tmp &= LCD_CONTRASTLEVEL_MASK;
    /* Set LCD_FCTRL LCD_CONTRAST[3:0] */
    tmp |= contrast;
    LCD->FCTRL = tmp;
}

/**
*\*\name    LCD_DEADTIME_CONFIG.
*\*\fun     LCD Dead_Time congfiguration.
*\*\param   deadtime :
*\*\          - LCD_DEADTIME_0
*\*\          - LCD_DEADTIME_1 
*\*\          - LCD_DEADTIME_2
*\*\          - LCD_DEADTIME_3 
*\*\          - LCD_DEADTIME_4
*\*\          - LCD_DEADTIME_5
*\*\          - LCD_DEADTIME_6 
*\*\          - LCD_DEADTIME_7 
*\*\return  none
**/
void LCD_DEADTIME_CONFIG(uint32_t deadtime)
{
    uint32_t tmp = LCD->FCTRL;
    /* Clear LCD_FCTRL DEAD[2:0] */
    tmp &= LCD_DEADTIME_MASK;
    /* Set LCD_FCTRL DEAD[2:0] */
    tmp |= deadtime;
    LCD->FCTRL = tmp;
}

/**
*\*\name    LCD_PULSEONDURATION_CONFIG.
*\*\fun     LCD Pluse_On_Duration congfiguration.
*\*\param   pluse_type :
*\*\          - LCD_PULSEONDURATION_0
*\*\          - LCD_PULSEONDURATION_1 
*\*\          - LCD_PULSEONDURATION_2
*\*\          - LCD_PULSEONDURATION_3 
*\*\          - LCD_PULSEONDURATION_4 
*\*\          - LCD_PULSEONDURATION_5
*\*\          - LCD_PULSEONDURATION_6 
*\*\          - LCD_PULSEONDURATION_7 
*\*\return  none
**/
void LCD_PULSEONDURATION_CONFIG(uint32_t pluse_type)
{
    uint32_t tmp = LCD->FCTRL;
    /* Clear LCD_FCTRL PULSEON[2:0] */
    tmp &= LCD_PULSEONDURATION_MASK;
    /* Set LCD_FCTRL PULSEON[2:0] */
    tmp |= pluse_type;
    LCD->FCTRL = tmp;
}


/**
*\*\name    LCD_GetFlagSTS.
*\*\fun     Get LCD flag Status.
*\*\param   lcd_flag :
*\*\          - LCD_FLAG_FCRSF
*\*\          - LCD_FLAG_RDY
*\*\          - LCD_FLAG_UDD
*\*\          - LCD_FLAG_UDR
*\*\          - LCD_FLAG_SOF
*\*\          - LCD_FLAG_ENSTS
*\*\return  SET or RESET
**/
FlagStatus LCD_GetFlagSTS(uint32_t lcd_flag)
{
    FlagStatus bit_status;
    /* Check the status of LCD flag */
    if ((LCD->STS & lcd_flag) != (uint8_t)RESET)
    {
        bit_status = SET;
    }
    else
    {
        bit_status = RESET;
    }
    return bit_status;
}

/**
*\*\name    LCD_RamClear.
*\*\fun     Clear LCD ram register.
*\*\return  none
**/
void LCD_RamClear(void)
{
    uint32_t counter;

    /*Clear lcd ram register*/
    for(counter = LCD_RAM1_COM0; counter <= LCD_RAM2_COM7; counter++)
    {
        LCD->RAM_COM[counter] = 0x0U;
    }
}


/**
*\*\name    LCD_Update_Request.
*\*\fun     Display request LCD update.
*\*\return  none
**/
void LCD_Update_Request(void)
{
    /* set LCD_STS UDR bit*/
    LCD->STS |= LCD_FLAG_UDR;
}

/**
*\*\name    LCD_Wait_For_Synchro.
*\*\fun     Wait until the LCD FCTRL register is synchronized in the LCDCLK domain.
*\*\        This function must be called after any write operation to LCD_FCTRL register.
*\*\return  LCD_ErrorTypeDef
*\*\          - LCD_ERROR_FCRSF : synchronization  timeout
*\*\          - LCD_ERROR_OK    : synchronization  success
**/
LCD_ErrorTypeDef LCD_WaitForSynchro(void)
{
    LCD_ErrorTypeDef status_value = LCD_ERROR_OK;
    uint32_t timeout;

    /* Loop until FCRSF flag is set */
    timeout = 0;
    while(RESET == (LCD_GetFlagSTS(LCD_FLAG_FCRSF)))
    {
        timeout++;
        if(timeout >= LCD_TIME_OUT)
        {
            status_value = LCD_ERROR_FCRSF;
            break;
        }
    }
    return status_value;
}

/**
*\*\name    LCD_Init.
*\*\fun     Initialize the LCD peripheral according to the specified parameters in the LCD_InitStruct.
*\*\param   LCD_InitStructure(The input parameters must be the following values) :
*\*\          - Bias
*\*\            - LCD_BIAS_1_2              
*\*\            - LCD_BIAS_1_3            
*\*\            - LCD_BIAS_1_4   
*\*\          - BlinkFreq
*\*\            - LCD_BLINKFREQ_DIV_8  
*\*\            - LCD_BLINKFREQ_DIV_16
*\*\            - LCD_BLINKFREQ_DIV_32  
*\*\            - LCD_BLINKFREQ_DIV_64
*\*\            - LCD_BLINKFREQ_DIV_128  
*\*\            - LCD_BLINKFREQ_DIV_256
*\*\            - LCD_BLINKFREQ_DIV_512  
*\*\            - LCD_BLINKFREQ_DIV_1024
*\*\          - BlinkMode
*\*\            - LCD_BLINKMODE_OFF        
*\*\            - LCD_BLINKMODE_SEG0_COM0       
*\*\            - LCD_BLINKMODE_SEG0_ALLCOM
*\*\            - LCD_BLINKMODE_ALLSEG_ALLCOM
*\*\          - Contrast:
*\*\            - LCD_CONTRASTLEVEL_0
*\*\            - LCD_CONTRASTLEVEL_1 
*\*\            - LCD_CONTRASTLEVEL_2
*\*\            - LCD_CONTRASTLEVEL_3 
*\*\            - LCD_CONTRASTLEVEL_4
*\*\            - LCD_CONTRASTLEVEL_5 
*\*\            - LCD_CONTRASTLEVEL_6
*\*\            - LCD_CONTRASTLEVEL_7
*\*\            - LCD_CONTRASTLEVEL_8
*\*\            - LCD_CONTRASTLEVEL_9 
*\*\            - LCD_CONTRASTLEVEL_10
*\*\            - LCD_CONTRASTLEVEL_11
*\*\            - LCD_CONTRASTLEVEL_12
*\*\            - LCD_CONTRASTLEVEL_13 
*\*\            - LCD_CONTRASTLEVEL_14
*\*\            - LCD_CONTRASTLEVEL_15
*\*\          - DeadTime:
*\*\            - LCD_DEADTIME_0
*\*\            - LCD_DEADTIME_1 
*\*\            - LCD_DEADTIME_2
*\*\            - LCD_DEADTIME_3 
*\*\            - LCD_DEADTIME_4
*\*\            - LCD_DEADTIME_5 
*\*\            - LCD_DEADTIME_6
*\*\            - LCD_DEADTIME_7
*\*\          - Divider:
*\*\            - LCD_DIV_16
*\*\            - LCD_DIV_17 
*\*\            - LCD_DIV_18
*\*\            - LCD_DIV_19 
*\*\            - LCD_DIV_20
*\*\            - LCD_DIV_21 
*\*\            - LCD_DIV_22
*\*\            - LCD_DIV_23
*\*\            - LCD_DIV_24
*\*\            - LCD_DIV_25 
*\*\            - LCD_DIV_26
*\*\            - LCD_DIV_27
*\*\            - LCD_DIV_28
*\*\            - LCD_DIV_29 
*\*\            - LCD_DIV_30
*\*\            - LCD_DIV_31
*\*\          - Duty:
*\*\            - LCD_DUTY_STATIC
*\*\            - LCD_DUTY_1_2 
*\*\            - LCD_DUTY_1_3
*\*\            - LCD_DUTY_1_4 
*\*\            - LCD_DUTY_1_8
*\*\          - HighDrive:
*\*\            - LCD_HIGHDRIVE_DISABLE
*\*\            - LCD_HIGHDRIVE_ENABLE 
*\*\          - HighDriveBuffer:
*\*\            - LCD_HIGHDRIVEBUFFER_DISABLE
*\*\            - LCD_HIGHDRIVEBUFFER_ENABLE
*\*\          - Prescaler:
*\*\            - LCD_PRESCALER_1
*\*\            - LCD_PRESCALER_2 
*\*\            - LCD_PRESCALER_4
*\*\            - LCD_PRESCALER_8 
*\*\            - LCD_PRESCALER_16
*\*\            - LCD_PRESCALER_32 
*\*\            - LCD_PRESCALER_64
*\*\            - LCD_PRESCALER_128
*\*\            - LCD_PRESCALER_256
*\*\            - LCD_PRESCALER_512 
*\*\            - LCD_PRESCALER_1024
*\*\            - LCD_PRESCALER_2048
*\*\            - LCD_PRESCALER_4096
*\*\            - LCD_PRESCALER_8192 
*\*\            - LCD_PRESCALER_16384
*\*\            - LCD_PRESCALER_32768
*\*\          - PulseOnDuration:
*\*\            - LCD_PULSEONDURATION_0
*\*\            - LCD_PULSEONDURATION_1 
*\*\            - LCD_PULSEONDURATION_2
*\*\            - LCD_PULSEONDURATION_3 
*\*\            - LCD_PULSEONDURATION_4
*\*\            - LCD_PULSEONDURATION_5 
*\*\            - LCD_PULSEONDURATION_6
*\*\            - LCD_PULSEONDURATION_7
*\*\          - VoltageSource:
*\*\            - LCD_VOLTAGESOURCE_DISABLE
*\*\            - LCD_VOLTAGESOURCE_ENABLE
*\*\return  none
**/
LCD_ErrorTypeDef LCD_Init(LCD_InitType *LCD_InitStructure)
{
    uint32_t tmp, timeout;
    LCD_ErrorTypeDef status_value = LCD_ERROR_OK;
    /*Disable LCD controller*/
    LCD_Disable();
    
    /* set the bits of LCD_CTRL register with corresonding parameters */
    tmp = 0;
    tmp |= LCD_InitStructure->HighDriveBuffer;
    tmp |= LCD_InitStructure->Bias;
    tmp |= LCD_InitStructure->Duty;
    tmp |= LCD_InitStructure->VoltageSource;
    LCD->CTRL = tmp;

    /*If High driver enable, PulseOnDuration must be LCD_PulseOnDuration_1*/
    if(LCD_InitStructure->HighDrive == LCD_HIGHDRIVE_ENABLE)
    {
        LCD_InitStructure->PulseOnDuration = LCD_PULSEONDURATION_1;
    }

    /* set the bits of LCD_FCTRL register with corresonding parameters */
    tmp = 0;
    tmp |= LCD_InitStructure->Prescaler;
    tmp |= LCD_InitStructure->Divider;
    tmp |= LCD_InitStructure->BlinkMode;
    tmp |= LCD_InitStructure->BlinkFreq;
    tmp |= LCD_InitStructure->Contrast;
    tmp |= LCD_InitStructure->DeadTime;
    tmp |= LCD_InitStructure->HighDrive;
    tmp |= LCD_InitStructure->PulseOnDuration;
    LCD->FCTRL = tmp;

    /*Clear LCD display ram, and set the update request flag*/
    LCD_RamClear();
    LCD_Update_Request();
    
    /*Enable LCD controller*/
    LCD_Enable();

    /*Check the LCD ENSTS status*/
    timeout = 0;
    while(RESET == (LCD_GetFlagSTS(LCD_FLAG_ENSTS)))
    {
        timeout++;
        if(timeout >= LCD_TIME_OUT)
        {
            status_value = LCD_ERROR_ENSTS;
            break;
        }
        else
        {
            /* no process */
        }
    }

    if(status_value == LCD_ERROR_OK)
    {
        /*Wait VLCD stable*/
        timeout = 0;
        while(RESET == (LCD_GetFlagSTS(LCD_FLAG_RDY)))
        {
            timeout++;
            if(timeout >= LCD_TIME_OUT)
            {
                status_value = LCD_ERROR_RDY;
                break;
            }
            else
            {
                /* no process */
            }
        }
    }
    else
    {
        /* no process */
    }

    if(status_value == LCD_ERROR_OK)
    {
        status_value = LCD_WaitForSynchro();
    }
    else
    {
        /* no process */
    }
    
    return status_value;
}



/**
*\*\name    LCD_ENABLE_IT.
*\*\fun     Enable LCD interrupts.
*\*\param   lcd_interrupt :
*\*\          - LCD_IT_UDD    
*\*\          - LCD_IT_SOF      
*\*\return  none
**/
void LCD_ENABLE_IT(uint32_t lcd_interrupt)
{
    /* Set the LCD_FCTRL LCD_UDDIE_ENABLE/LCD_SOFIE_ENABLE bit to enable LCD interrupts */
    LCD->FCTRL |= lcd_interrupt;
}

/**
*\*\name    LCD_DISABLE_IT.
*\*\fun     Disable LCD interrupts.
*\*\param   lcd_interrupt :
*\*\          - LCD_IT_UDD    
*\*\          - LCD_IT_SOF      
*\*\return  none
**/
void LCD_DISABLE_IT(uint32_t lcd_interrupt)
{
    /* Clear the LCD_FCTRL LCD_UDDIE_DISABLE/LCD_SOFIE_DISABLE bit to enable LCD interrupts */
    LCD->FCTRL &= (~lcd_interrupt);
}


/**
*\*\name    LCD_GET_IT_SOURCE.
*\*\fun     Get LCD  interrupt flag Status.
*\*\param   lcd_interrupt :
*\*\          - LCD_IT_UDD
*\*\          - LCD_IT_SOF
*\*\return  SET or RESET
**/
FlagStatus LCD_GET_IT_SOURCE(uint32_t lcd_interrupt)
{
    FlagStatus bit_status;
    /* Check the status of LCD flag */
    if ((LCD->FCTRL & lcd_interrupt) != (uint8_t)RESET)
    {
        /* LCD_FLAG is set */
        bit_status = SET;
    }
    else
    {
        /* LCD_FLAG is reset */
        bit_status = RESET;
    }
    return bit_status;
}

/**
*\*\name    LCD_Clear_Flag.
*\*\fun     Clear lcd flag Status.
*\*\param   lcd_flag :
*\*\          - LCD_FLAG_UDD_CLEAR
*\*\          - LCD_FLAG_SOF_CLEAR
*\*\return  none
**/
void LCD_Clear_Flag(uint32_t lcd_flag)
{
    uint32_t timeout;
    /* Clear the selected LCD flag Status */
    LCD->CLR = lcd_flag; 
    /* Wait update complete */
    timeout = 0;
    while(SET == (LCD_GetFlagSTS(LCD_FLAG_UDD)))
    {
        timeout++;
        if(timeout >= LCD_TIME_OUT)
        {
            break;
        }
        else
        {
            /* no process */
        }
    }
    
    /*Clear UDDCLR bit*/
    LCD->CLR &= (~LCD_CLR_UDDCLR);
}

/**
*\*\name    LCD_UpdateDisplayRequest.
*\*\fun     LCD Display update request,and get the request status.
*\*\return  LCD_ErrorTypeDef
*\*\          - LCD_ERROR_UDD : update timeout
*\*\          - LCD_ERROR_OK  : update success
**/
LCD_ErrorTypeDef LCD_UpdateDisplayRequest(void)
{
    uint32_t timeout;
    LCD_ErrorTypeDef status_value = LCD_ERROR_OK;

    /*Clear UDD flag*/
    LCD_Clear_Flag(LCD_FLAG_UDD_CLEAR);
    
    /* set update display request bit*/
    LCD_Update_Request();

    /* Wait update complete */
    timeout = 0;
    while(RESET == (LCD_GetFlagSTS(LCD_FLAG_UDD)))
    {
        timeout++;
        if(timeout >= LCD_TIME_OUT)
        {
            status_value = LCD_ERROR_UDD;
            break;
        }
        else
        {
            /* no process */
        }
    }
    
    return status_value;
}

/**
*\*\name    LCD_Write.
*\*\fun     write to the lcd ram register.
*\*\param   RAMRegisterIndex :
*\*\          - LCD_RAM1_COM0
*\*\          - LCD_RAM2_COM0
*\*\          - LCD_RAM1_COM1
*\*\          - LCD_RAM2_COM1
*\*\          - LCD_RAM1_COM2
*\*\          - LCD_RAM2_COM2
*\*\          - LCD_RAM1_COM3
*\*\          - LCD_RAM2_COM3
*\*\          - LCD_RAM1_COM4
*\*\          - LCD_RAM2_COM4
*\*\          - LCD_RAM1_COM5
*\*\          - LCD_RAM2_COM5
*\*\          - LCD_RAM1_COM6
*\*\          - LCD_RAM2_COM6
*\*\          - LCD_RAM1_COM7
*\*\          - LCD_RAM2_COM7
*\*\param   RAMRegisterMask :
*\*\          - 0x00000000U~0xFFFFFFFFU  A bit of 1 indicates that this bit retains its original value.
*\*\param   RAMData :
*\*\          - 0x00000000 ~ 0xFFFFFFFF
*\*\return  LCD_ErrorTypeDef
*\*\          - LCD_ERROR_PARAM : LCD function parameter error
*\*\          - LCD_ERROR_UDR   : Update display request flag error
*\*\          - LCD_ERROR_OK    : update success
**/
LCD_ErrorTypeDef LCD_Write(uint32_t RAMRegisterIndex,uint32_t RAMRegisterMask,uint32_t RAMData)
{   
    uint32_t timeout;
    LCD_ErrorTypeDef status_value = LCD_ERROR_OK;

    if(RAMRegisterIndex > LCD_RAM2_COM7) 
    {
        status_value = LCD_ERROR_PARAM;
    }
    
    if(status_value == LCD_ERROR_OK)
    {
        /* Wait VLCD request flag  clear */
        timeout = 0;
        while(LCD_GetFlagSTS(LCD_FLAG_UDR) == SET)
        {
            timeout++;
            if(timeout >= LCD_TIME_OUT)
            {
                status_value = LCD_ERROR_UDR;
                break;
            }
        }
    }
    else
    {
    
    }

    if(status_value == LCD_ERROR_OK)
    {
        /* Write lcd RAMData */
        MODIFY_REG(LCD->RAM_COM[RAMRegisterIndex], ~(RAMRegisterMask), RAMData &(~(RAMRegisterMask)));
    }
    else
    {
    
    }

    return status_value;
}

/**
*\*\name    LCD_SetBit.
*\*\fun     Set some bits of lcd ram register.
*\*\param   RAMRegisterIndex :
*\*\          - LCD_RAM1_COM0
*\*\          - LCD_RAM2_COM0
*\*\          - LCD_RAM1_COM1
*\*\          - LCD_RAM2_COM1
*\*\          - LCD_RAM1_COM2
*\*\          - LCD_RAM2_COM2
*\*\          - LCD_RAM1_COM3
*\*\          - LCD_RAM2_COM3
*\*\          - LCD_RAM1_COM4
*\*\          - LCD_RAM2_COM4
*\*\          - LCD_RAM1_COM5
*\*\          - LCD_RAM2_COM5
*\*\          - LCD_RAM1_COM6
*\*\          - LCD_RAM2_COM6
*\*\          - LCD_RAM1_COM7
*\*\          - LCD_RAM2_COM7
*\*\param   RAMData :
*\*\          - 0x00000000 ~ 0xFFFFFFFF
*\*\return  LCD_ErrorTypeDef
*\*\          - LCD_ERROR_PARAM : LCD function parameter error
*\*\          - LCD_ERROR_UDR   : Update display request flag error
*\*\          - LCD_ERROR_OK    : update success
**/
LCD_ErrorTypeDef LCD_SetBit(uint32_t RAMRegisterIndex,uint32_t RAMData)
{
    uint32_t timeout;
    LCD_ErrorTypeDef status_value = LCD_ERROR_OK;
    
    if(RAMRegisterIndex > LCD_RAM2_COM7) 
    {
        status_value = LCD_ERROR_PARAM;
    }

    if(status_value == LCD_ERROR_OK)
    {
        /* Wait VLCD request flag  clear */
        timeout = 0;
        while(LCD_GetFlagSTS(LCD_FLAG_UDR) == SET)
        {
            timeout++;
            if(timeout >= LCD_TIME_OUT)
            {
                status_value = LCD_ERROR_UDR;
                break;
            }
        }
    }
    else
    {
    
    }

    if(status_value == LCD_ERROR_OK)
    {
        /* Write lcd RAMData */
        SET_BIT(LCD->RAM_COM[RAMRegisterIndex], RAMData);
    }
    else
    {
    
    }
    
    return status_value;
}

/**
*\*\name    LCD_ClearBit.
*\*\fun     Clear some bits of lcd ram register.
*\*\param   RAMRegisterIndex :
*\*\          - LCD_RAM1_COM0
*\*\          - LCD_RAM2_COM0
*\*\          - LCD_RAM1_COM1
*\*\          - LCD_RAM2_COM1
*\*\          - LCD_RAM1_COM2
*\*\          - LCD_RAM2_COM2
*\*\          - LCD_RAM1_COM3
*\*\          - LCD_RAM2_COM3
*\*\          - LCD_RAM1_COM4
*\*\          - LCD_RAM2_COM4
*\*\          - LCD_RAM1_COM5
*\*\          - LCD_RAM2_COM5
*\*\          - LCD_RAM1_COM6
*\*\          - LCD_RAM2_COM6
*\*\          - LCD_RAM1_COM7
*\*\          - LCD_RAM2_COM7
*\*\param   RAMData :
*\*\          - 0x00000000 ~ 0xFFFFFFFF
*\*\return  LCD_ErrorTypeDef
*\*\          - LCD_ERROR_PARAM : LCD function parameter error
*\*\          - LCD_ERROR_UDR   : Update display request flag error
*\*\          - LCD_ERROR_OK    : update success
**/
LCD_ErrorTypeDef LCD_ClearBit(uint32_t RAMRegisterIndex,uint32_t RAMData)
{
    uint32_t timeout;
    LCD_ErrorTypeDef status_value = LCD_ERROR_OK;
    
    if(RAMRegisterIndex > LCD_RAM2_COM7)
    {
        status_value = LCD_ERROR_PARAM;
    }

    if(status_value == LCD_ERROR_OK)
    {
        /* Wait VLCD request flag  clear */
        timeout = 0;
        while(LCD_GetFlagSTS(LCD_FLAG_UDR) == SET)
        {
            timeout++;
            if(timeout >= LCD_TIME_OUT)
            {
                status_value = LCD_ERROR_UDR;
                break;
            }
        }
    }

    if(status_value == LCD_ERROR_OK)
    {
        /* Write lcd RAMData */
        CLEAR_BIT(LCD->RAM_COM[RAMRegisterIndex], RAMData);
    }
    else
    {
    
    }
    
    return status_value;
}


/**
*\*\name    LCD_ClockConfig.
*\*\fun     Clear some bits of lcd ram register.
*\*\param   LCD_ClkSource :
*\*\          - LCD_CLK_SRC_HSI_DIV8:              LCD clock source is HSI_8M/8
*\*\          - LCD_CLK_SRC_HSE_DIV16:             LCD clock source is HSE/16
*\*\          - LCD_CLK_SRC_HSE_BYPASS_DIV16       LCD clock source is HSE_BYPASS/16
*\*\return  LCD_ErrorTypeDef
*\*\          - LCD_ERROR_CLK                LCD clock source fail error
*\*\          - LCD_ERROR_PARAM              LCD function parameter error
*\*\          - LCD_ERROR_OK                 update success
**/
LCD_ErrorTypeDef LCD_ClockConfig(uint32_t LCD_ClkSource)
{
    LCD_ErrorTypeDef status_value = LCD_ERROR_OK;
    if(LCD_CLK_SRC_HSI_DIV8==LCD_ClkSource)
    {
        if(RCC_GetFlagStatus(RCC_CTRL_FLAG_HSIRDF)==RESET)
        {
            RCC_EnableHsi(ENABLE);
            if(RCC_WaitHsiStable()!=SUCCESS)
            {
                status_value = LCD_ERROR_CLK;
            }
        }
    }
    else if(LCD_CLK_SRC_HSE_DIV16==LCD_ClkSource)
    {
        if(RCC_GetFlagStatus(RCC_CTRL_FLAG_HSERDF)==RESET)
        {
            RCC_ConfigHse(RCC_HSE_ENABLE);
            if(RCC_WaitHseStable()!=SUCCESS)
            {
                status_value = LCD_ERROR_CLK;
            }
        }
    }
	else if(LCD_CLK_SRC_HSE_BYPASS_DIV16 == LCD_ClkSource)
    {
        if(RCC_GetFlagStatus(RCC_CTRL_FLAG_HSERDF)==RESET)
        {
            RCC_ConfigHse(RCC_HSE_BYPASS);
            if(RCC_WaitHseStable()!=SUCCESS)
            {
                status_value = LCD_ERROR_CLK;
            }
        }
    }
    else
    {
        status_value = LCD_ERROR_PARAM;
    }

    if(LCD_CLK_SRC_HSI_DIV8==LCD_ClkSource)
    {
        /*set HSI as LCD clock source*/
        RCC_ConfigLCDClk(RCC_LCD_CLKSRC_HSI_DIV8);
    }
    else
    {
        /*set HSE as LCD clock source*/
        RCC_ConfigLCDClk(RCC_LCD_CLKSRC_HSE_DIV16);
    }

    /*Enable LCD clk*/
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_LCD,ENABLE);

    return status_value;
}


