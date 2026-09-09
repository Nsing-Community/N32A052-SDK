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
*\*\file n32a052_crc.h
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
 */


#ifndef __N32A052_CRC_H_
#define __N32A052_CRC_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "n32a052.h"

/*** CRC Structure Definition Start ***/

/*** CRC Structure Definition End ***/

/*** CRC Macro Definition Start ***/


/** CRC clear the CRC16 check value definition **/
#define CRC_CRC16_VALUE_CLEAR    ((uint32_t)CRC16_CTRL_RESET)
#define CRC_CRC16_VALUE_NO_CLEAR ((uint32_t)CRC16_CTRL_NO_RESET)

/** CRC little-endian and big-endian definition **/
#define CRC_LITTLE_ENDIAN_ENABLE ((uint32_t)CRC16_CTRL_LITTLE) /* Set little-endian */
#define CRC_BIG_ENDIAN_ENABLE    ((uint32_t)CRC16_CTRL_BIG)    /* Set big-endian */

/*** CRC Macro Definition End ***/

/*** CRC Driving Functions Declaration ***/
uint16_t CRC16_CalcCrc(uint8_t data);
uint16_t CRC16_CalcBufCrc(const uint8_t pBuffer[], uint32_t buf_len);
void CRC16_SetCrc(uint8_t data);
uint16_t CRC16_GetCrc(void);
void CRC16_SetLittleEndianFmt(void);
void CRC16_SetBigEndianFmt(void);
void CRC16_SetCleanEnable(void);
void CRC16_SetCleanDisable(void);
void CRC16_SetLRC(uint8_t data);
uint8_t CRC16_GetLRC(void);

#ifdef __cplusplus
}
#endif

#endif /* __N32A052_CRC_H_ */

