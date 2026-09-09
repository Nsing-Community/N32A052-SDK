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
*\*\file n32a052_wwdg.h
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/


#ifndef __N32A052_WWDG_H__
#define __N32A052_WWDG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32a052.h"


#define WWDG_PRESCALER_DIV1             ((uint32_t)0x00000000)
#define WWDG_PRESCALER_DIV2             ((uint32_t)WWDG_CFG_TIMERB0)
#define WWDG_PRESCALER_DIV4             ((uint32_t)WWDG_CFG_TIMERB1)
#define WWDG_PRESCALER_DIV8             ((uint32_t)(WWDG_CFG_TIMERB1 | WWDG_CFG_TIMERB0))

/** EWINT bit **/
#define EARLY_WAKEUP_INT                (WWDG_CFG_EWINT)
#define EARLY_WAKEUP_FLAG               (WWDG_STS_EWINTF)

/** CTRL register bit mask **/
#define CTRL_ACTB_SET                   ((uint32_t)WWDG_CTRL_ACTB)

/* CFG register bit mask **/
#define CFG_TIMERB_MASK                 ((uint32_t)0xFFFF3FFFU)
#define CFG_W_MASK                      ((uint32_t)0xFFFFC000U)
#define BIT_MASK                        ((uint16_t)0x3FFF)


void WWDG_DeInit(void);
void WWDG_SetPrescalerDiv(uint32_t WWDG_Prescaler);
void WWDG_SetWValue(uint16_t WindowValue);
void WWDG_EnableInt(void);
void WWDG_SetCnt(uint16_t Counter);
void WWDG_Enable(uint16_t Counter);
FlagStatus WWDG_GetEWINTF(void);
void WWDG_ClrEWINTF(void);

#ifdef __cplusplus
}
#endif

#endif /* __N32A052_WWDG_H__ */

