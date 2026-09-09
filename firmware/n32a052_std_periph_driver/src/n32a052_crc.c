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
*\*\file n32a052_crc.c
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
 */

#include "n32a052_crc.h"

/** CRC Private Defines **/


/** CRC Driving Functions Declaration **/

/**
*\*\name    CRC16_CalcCrc.
*\*\fun     Computes the 16-bit CRC of a given data word(8-bit).
*\*\param   data :
*\*\          - data word(8-bit) to compute its CRC
*\*\return  16-bit CRC
**/
uint16_t CRC16_CalcCrc(uint8_t data)
{
    /* Write data to the CRC16DAT register */
    CRC->CRC16DAT = data;
    /* Returns the computed CRC16 result */
    return (CRC->CRC16D);
}

/**
*\*\name    CRC16_CalcBufCrc.
*\*\fun     Computes the 16-bit CRC of a given buffer of data word(8-bit).
*\*\param   pBuffer :
*\*\          - pointer to the buffer containing the data to be computed
*\*\param   buf_len :
*\*\          - length of the buffer to be computed
*\*\return  16-bit CRC
**/
uint16_t CRC16_CalcBufCrc(const uint8_t pBuffer[], uint32_t buf_len)
{
    uint32_t index = 0;

    CRC->CRC16D = 0x00;
    for (index = 0; index < buf_len; index++)
    {
        /* Write data to the CRC16DAT register */
        CRC->CRC16DAT = pBuffer[index];
    }
    /* Returns the computed CRC16 result */
    return (CRC->CRC16D);
}

/**
*\*\name    CRC16_SetCrc.
*\*\fun     write a 8-bit data in the 16-bit CRC Data register.
*\*\param   data :
*\*\          - 8-bit data value to be writed in the 16-bit CRC Data register
*\*\return  none
**/
void CRC16_SetCrc(uint8_t data)
{
    /* Writes 8-bit data to the CRC16DAT register */
    CRC->CRC16DAT = data;
}

/**
*\*\name    CRC16_GetCrc.
*\*\fun     Returns the current CRC value.
*\*\param   none
*\*\return  16-bit CRC
**/
uint16_t CRC16_GetCrc(void)
{
    /* Returns the CRC16 calculation result */
    return (CRC->CRC16D);
}

/**
*\*\name    CRC16_SetLittleEndianFmt.
*\*\fun     Set the calculate data to little endian format.
*\*\param   none
*\*\return  none
**/
void CRC16_SetLittleEndianFmt(void)
{
    CRC->CRC16CTRL |= CRC_LITTLE_ENDIAN_ENABLE;
}

/**
*\*\name    CRC16_SetBigEndianFmt.
*\*\fun     Set the calculate data to big endian format.
*\*\param   none
*\*\return  none
**/
void CRC16_SetBigEndianFmt(void)
{
    CRC->CRC16CTRL &= CRC_BIG_ENDIAN_ENABLE;
}

/**
*\*\name    CRC16_SetCleanEnable.
*\*\fun     Clean CRC16 value.
*\*\param   none
*\*\return  none
**/
void CRC16_SetCleanEnable(void)
{
    CRC->CRC16CTRL |= CRC_CRC16_VALUE_CLEAR;
}

/**
*\*\name    CRC16_SetCleanDisable.
*\*\fun     Not clean CRC16 value.
*\*\param   none
*\*\return  none
**/
void CRC16_SetCleanDisable(void)
{
    CRC->CRC16CTRL &= CRC_CRC16_VALUE_NO_CLEAR;
}

/**
*\*\name    CRC16_SetLRC.
*\*\fun     Write LRC initial value.
*\*\param   data :
*\*\          - 8-bit data
*\*\return  none
**/
void CRC16_SetLRC(uint8_t data)
{
    /* Write LRC to verify the initial value */
    CRC->LRC = data;
}

/**
*\*\name    CRC16_GetLRC.
*\*\fun     Returns the current LRC value.
*\*\param   none
*\*\return  8-bit LRC
**/
uint8_t CRC16_GetLRC(void)
{
    /* Returns the LRC check value */
    return (CRC->LRC);
}


