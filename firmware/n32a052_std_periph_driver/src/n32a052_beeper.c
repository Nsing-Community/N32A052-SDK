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
*\*\file n32a052_beeper.c
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/

#include "n32a052_beeper.h"
#include "n32a052_rcc.h"
 
/**
*\*\name    BEEPER_DeInit.
*\*\fun     Reset the BEEPER register to it's default reset values.
*\*\param   none.
*\*\return  none. 
**/
void BEEPER_DeInit(void)
{
    /* Reset BEEPER */
    RCC_EnableAPB1PeriphReset(RCC_APB1_PERIPH_BEEP);
}

/**
*\*\name    BEEPER_FreqSelect.
*\*\fun     Beeper output frequency selection.
*\*\param   freq_selection:     select beeper output frequency
              -BEEPER_FREQ_131HZ
              -BEEPER_FREQ_147HZ
              -BEEPER_FREQ_165HZ
              -BEEPER_FREQ_175HZ
              -BEEPER_FREQ_196HZ
              -BEEPER_FREQ_220HZ
              -BEEPER_FREQ_247HZ
              -BEEPER_FREQ_262HZ
              -BEEPER_FREQ_294HZ
              -BEEPER_FREQ_330HZ
              -BEEPER_FREQ_349HZ
              -BEEPER_FREQ_392HZ
              -BEEPER_FREQ_440HZ
              -BEEPER_FREQ_494HZ
              -BEEPER_FREQ_524HZ
              -BEEPER_FREQ_588HZ
              -BEEPER_FREQ_660HZ
              -BEEPER_FREQ_698HZ
              -BEEPER_FREQ_784HZ
              -BEEPER_FREQ_880HZ
              -BEEPER_FREQ_988HZ
              -BEEPER_FREQ_1KHZ
              -BEEPER_FREQ_2KHZ
              -BEEPER_FREQ_4KHZ
              -BEEPER_FREQ_8KHZ
*\*\return  none. 
**/
void BEEPER_FreqSelect(uint32_t freq_selection)
{
      BEEPER->CTRL &= BEEPER_FREQ_SEL_MASK;
      BEEPER->CTRL |= (freq_selection << SHIFT_BEEPER);
}

/**
*\*\name    BEEPER_Enable.
*\*\fun     Enables or disables the BEEPER peripheral
*\*\param   Cmd: 
*\*\          -ENABLE   enable beeper 
*\*\          -DISABLE  disable beeper
*\*\return  none. 
**/
void BEEPER_Enable(FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        BEEPER->CTRL |= BEEPER_ENABLE;
    }
    else
    {
        BEEPER->CTRL &= BEEPER_DISABLE;
    }
}

