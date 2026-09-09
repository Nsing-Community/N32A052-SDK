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
*\*\file n32a052_iwdg.c
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/
#include "n32a052_iwdg.h"


/**
*\*\name    IWDG_WriteConfig.
*\*\fun     Enables or disables write protection to IWDG_PREDIV and IWDG_RELV registers.
*\*\param   IWDG_WriteAccess
*\*\        - IWDG_WRITE_ENABLE
*\*\        - IWDG_WRITE_DISABLE
*\*\return  none
**/
void IWDG_WriteConfig(IWDOG_WRITE_CONFIG IWDG_WriteAccess)
{
    /* Check the parameters */
    IWDG->KEY = (uint32_t)IWDG_WriteAccess;
}

/**
*\*\name    IWDG_SetPrescalerDiv.
*\*\fun     IWDG_Prescaler specifies the IWDG prescaler value.
*\*\param   IWDG_Prescaler :
*\*\          - IWDG_PRESCALER_DIV4 
*\*\          - IWDG_PRESCALER_DIV8
*\*\          - IWDG_PRESCALER_DIV16
*\*\          - IWDG_PRESCALER_DIV32
*\*\          - IWDG_PRESCALER_DIV64
*\*\          - IWDG_PRESCALER_DIV128
*\*\          - IWDG_PRESCALER_DIV256
*\*\return  none
**/
void IWDG_SetPrescalerDiv(uint8_t IWDG_Prescaler)
{
    IWDG->PREDIV = IWDG_Prescaler;
}


/**
*\*\name    IWDG_CntReload.
*\*\fun     Sets IWDG reload value.
*\*\param   Reload :
*\*\          -0x000 ~ 0xFFF
*\*\return  none
**/
void IWDG_CntReload(uint16_t Reload)
{
    IWDG->RELV = Reload;
}


/**
*\*\name    IWDG_ReloadKey.
*\*\fun     Reload IWDG counter with value defined in IWDG_RELV register.
*\*\param   none
*\*\return  none
**/
void IWDG_ReloadKey(void)
{
    IWDG->KEY = KEY_ReloadKey;
}


/**
*\*\name    IWDG_Enable.
*\*\fun     Start watch dog counter.
*\*\param   none
*\*\return  none
**/
void IWDG_Enable(void)
{
    IWDG->KEY = KEY_EnableKey;
}

/**
*\*\name    IWDG_FreezeRun_Enable.
*\*\fun     Freeze or unfreeze IWDG while IWDG is running in run mode.
 *\*\param  Cmd :
 *\*\          - ENABLE
 *\*\          - DISABLE
*\*\return  none
**/
void IWDG_FreezeRun_Enable(FunctionalState Cmd)
{
    if(Cmd == ENABLE)
    {
        IWDG->KEY = IWDG_FREEZE;
    }
    else
    {
        IWDG->KEY = IWDG_UNFREEZE;
    }
    
}

/**
*\*\name    IWDG_FreezeLP.
*\*\fun     Freeze or unfreeze IWDG after mcu enter low power mode.
*\*\param   none
*\*\return  none
**/
void IWDG_FreezeLP(void)
{
    IWDG->FREEZE = IWDG_FREEZE_LPMODE;
}

/**
*\*\name    IWDG_GetStatus.
*\*\fun     Checks whether the specified IWDG flag is set or not.
*\*\param   IWDG_FLAG :
*\*\          - IWDG_PVU_FLAG
*\*\          - IWDG_CRVU_FLAG
*\*\          - IWDG_RUNFREF_FLAG
*\*\          - IWDG_LPFREF_FLAG
*\*\return  FlagStatus :
*\*\          - RESET
*\*\          - SET
**/
FlagStatus IWDG_GetStatus(IWDG_STATUS_FLAG IWDG_FLAG)
{
    FlagStatus bitstatus = RESET;

    if ((IWDG->STS & IWDG_FLAG) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    /* Return the flag status */
    return bitstatus;
}
