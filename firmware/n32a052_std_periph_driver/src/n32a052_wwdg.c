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
*\*\file n32a052_wwdg.c
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/

#include "n32a052_wwdg.h"
#include "n32a052_rcc.h"

/**
*\*\name    WWDG_DeInit.
*\*\fun     Resets the WWDG peripheral registers to their default reset values.
*\*\return  none
**/
void WWDG_DeInit(void)
{
    RCC_EnableAPB1PeriphReset(RCC_APB1_PERIPH_WWDG);
}

/**
*\*\name    WWDG_SetPrescalerDiv.
*\*\fun     Set the WWDOG Prescaler Division Value.
*\*\param   WWDG_Prescaler : 
*\*\          - WWDG_PRESCALER_DIV1   WWDG Counter Clock (PCLK1 / 4096) / 1
*\*\          - WWDG_PRESCALER_DIV2   WWDG Counter Clock (PCLK1 / 4096) / 2
*\*\          - WWDG_PRESCALER_DIV4   WWDG Counter Clock (PCLK1 / 4096) / 4
*\*\          - WWDG_PRESCALER_DIV8   WWDG Counter Clock (PCLK1 / 4096) / 8
*\*\return  none
**/
void WWDG_SetPrescalerDiv(uint32_t WWDG_Prescaler)
{
    uint32_t tmpregister;

    /* Clear TIMERB[1:0] bits */
    tmpregister = WWDG->CFG & CFG_TIMERB_MASK;
    /* Set TIMERB[1:0] bits according to WWDG_Prescaler value */
    tmpregister |= WWDG_Prescaler;
    /* Store the new value */
    WWDG->CFG = tmpregister;
}

/**
*\*\name    WWDG_SetWValue.
*\*\fun     Set the WWDOG Window Value.
*\*\param   WindowValue : WWDOG Window Value
*\*\          The value range of this parameter :
*\*\          - 0x0040 ~ 0x3FFF
*\*\return  none
**/
void WWDG_SetWValue(uint16_t WindowValue)
{
    __IO uint32_t tmpregister = 0;

    /* Clear W[13:0] bits */
    tmpregister = WWDG->CFG & CFG_W_MASK;

    /* Set W[13:0] bits according to WindowValue value */
    tmpregister |= WindowValue & (uint32_t)BIT_MASK;

    /* Store the new value */
    WWDG->CFG = tmpregister;
}

/**
*\*\name    WWDG_EnableInt.
*\*\fun     Enable WWDG Early Wakeup interrupt(EWINT).
*\*\return  none
**/
void WWDG_EnableInt(void)
{
    WWDG->CFG |= EARLY_WAKEUP_INT;
}

/**
*\*\name    WWDG_SetCnt.
*\*\fun     Set the WWDOG Counter Value.
*\*\param   Counter : WWDOG Counter value
*\*\          The value range of this parameter :
*\*\          - 0x40 ~ 0x3FFF
*\*\return  none 
**/
void WWDG_SetCnt(uint16_t Counter)
{
    /* Write to T[13:0] bits to configure the counter value, no need to do
       a read-modify-write; writing a 0 to WDGA bit does nothing */
    WWDG->CTRL = (uint32_t)(Counter & BIT_MASK);
}

/**
*\*\name    WWDG_Enable.
*\*\fun     Set the WWDOG Counter Value and Enable WWDOG .
*\*\param   Counter : WWDOG Counter value
*\*\          The value range of this parameter :
*\*\          - 0x40 ~ 0x3FFF
*\*\return  none
**/
void WWDG_Enable(uint16_t Counter)
{
    WWDG->CTRL = CTRL_ACTB_SET | Counter;
}

/**
*\*\name    WWDG_GetEWINTF.
*\*\fun     Get WWDOG Early Wake-up Interrupt Flag.
*\*\param   none
*\*\return  SET or RESET
**/
FlagStatus WWDG_GetEWINTF(void)
{
    return (FlagStatus)(WWDG->STS & (uint32_t)EARLY_WAKEUP_FLAG);
}

/**
*\*\name    WWDG_ClrEWINTF.
*\*\fun     Clear WWDOG Early Wake-up Interrupt Flag.
*\*\return  none
**/
void WWDG_ClrEWINTF(void)
{
    WWDG->STS = (uint32_t)~EARLY_WAKEUP_FLAG;
}
