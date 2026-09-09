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
*\*\file n32a052_iwdg.h
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/

#ifndef __n32A052_IWDG_H
#define __n32A052_IWDG_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "n32a052.h"   

typedef enum 
{
    IWDG_PVU_FLAG  = IWDG_STS_PVU,
    IWDG_CRVU_FLAG = IWDG_STS_CRVU,
    IWDG_RUNFREF_FLAG = IWDG_STS_RUNFREF,
    IWDG_LPFREF_FLAG = IWDG_STS_LPFREF
}IWDG_STATUS_FLAG;

/** KEY register bit mask **/
#define KEY_ReloadKey                      ((uint16_t)0xAAAA)
#define KEY_EnableKey                      ((uint16_t)0xCCCC)
#define IWDG_FREEZE                        ((uint16_t)0x4567)
#define IWDG_UNFREEZE                      ((uint16_t)0x89AB)

#define IWDG_FREEZE_LPMODE                 ((uint16_t)0xDDDD)

/** PREDIV and RELV register write permission **/
typedef enum 
{
    IWDG_WRITE_ENABLE  = 0x5555,
    IWDG_WRITE_DISABLE = 0x0000
}IWDOG_WRITE_CONFIG;

#define IWDG_PRESCALER_DIV4    ((uint8_t)0x00)
#define IWDG_PRESCALER_DIV8    (IWDG_PREDIV_PD0)
#define IWDG_PRESCALER_DIV16   (IWDG_PREDIV_PD1)
#define IWDG_PRESCALER_DIV32   (IWDG_PREDIV_PD1 | IWDG_PREDIV_PD0)
#define IWDG_PRESCALER_DIV64   (IWDG_PREDIV_PD2)
#define IWDG_PRESCALER_DIV128  (IWDG_PREDIV_PD2 | IWDG_PREDIV_PD0)
#define IWDG_PRESCALER_DIV256  (IWDG_PREDIV_PD2 | IWDG_PREDIV_PD1 | IWDG_PREDIV_PD0)


void IWDG_WriteConfig(IWDOG_WRITE_CONFIG IWDG_WriteAccess);
void IWDG_SetPrescalerDiv(uint8_t IWDG_Prescaler);
void IWDG_CntReload(uint16_t Reload);
void IWDG_ReloadKey(void);
void IWDG_Enable(void);
void IWDG_FreezeRun_Enable(FunctionalState Cmd);
void IWDG_FreezeLP(void);
FlagStatus IWDG_GetStatus(IWDG_STATUS_FLAG IWDG_FLAG);

#ifdef __cplusplus
}
#endif

#endif /* __n32A052_IWDG_H */
