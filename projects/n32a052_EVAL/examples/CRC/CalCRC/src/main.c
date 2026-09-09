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
 * @file main.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
 */
#include "main.h"

/** @addtogroup N32A052_StdPeriph_Examples
 * @{
 */

/** @addtogroup CRC_Calculation
 * @{
 */

#define CRC_DFE_POLY 0x8005


static const uint8_t Buffer[8] = {0x7e, 0x11, 0x36, 0x4e, 0x55, 0x0a, 0xf1, 0x1a};

__IO uint32_t CRCValue   = 0;
__IO uint16_t CRC16Value = 0;

void Delay(__IO uint32_t nCount);

uint8_t ReverseBits(uint8_t bufin)
{
    uint8_t bufout = 0;
    uint8_t j      = 0;
    for (j = 0; j < 4; j++)
    {
        bufout |= (bufin & (0x01 << j)) << (7 - 2 * j);
        bufout |= (bufin & (0x10 << (j))) >> (2 * j + 1);
    }
    return bufout;
}
uint16_t GetCRC16_Software(uint8_t* buf, uint32_t len, uint16_t initcrc)
{
    uint16_t crc16 = initcrc;
    uint8_t i = 0, j = 0;

    for (i = 0; i < len; i++)
    {
        crc16 ^= (uint16_t)(buf[i] << 8);
        for (j = 0; j < 8; j++)
        {
            if ((crc16 & 0x8000) > 0)
            {
                crc16 = (uint16_t)((crc16 << 1) ^ CRC_DFE_POLY);
            }
            else
            {
                crc16 <<= 1;
            }
        }
    }
    return crc16;
}


/**
 * @brief  Main program.
 */
int main(void)
{
    /*!< At this stage the microcontroller clock setting is already configured,
         this is done through SystemInit() function which is called from startup
         file (startup_n32a052.s) before to branch to application main.
         To reconfigure the default setting of SystemInit() function, refer to
         system_n32a052.c file
       */
    
    /* Enable CRC clock */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_CRC, ENABLE);

    /* Compute the 16bit CRC of an array */
    CRC16Value = CRC16_CalcBufCrc((uint8_t*)Buffer, 8);
    
    /* Compute the 16bit CRC of an array by software*/
    CRCValue = GetCRC16_Software((uint8_t*)Buffer, 8, 0x00);

    while (1)
    {
    }
}

/**
 * @brief  Inserts a delay time.
 * @param nCount specifies the delay time length.
 */
void Delay(__IO uint32_t nCount)
{
    for (; nCount != 0; nCount--)
        ;
}

