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
 * @file n32a052x_it.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
 */
#include "n32a052_it.h"
#include "n32a052_tim.h"
#include "n32a052_rcc.h"

/** @addtogroup N32A052X_StdPeriph_Template
 * @{
 */

uint16_t IC1ReadValue1 = 0, IC1ReadValue2 = 0;
uint16_t CaptureNumber = 0;
uint32_t Capture       = 0;
extern uint32_t LsiFreq;

/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
 * @brief  This function handles NMI exception.
 */
void NMI_Handler(void)
{
}

/**
 * @brief  This function handles Hard Fault exception.
 */
void HardFault_Handler(void)
{
    /* Go to infinite loop when Hard Fault exception occurs */
    while (1)
    {
    }
}


/**
 * @brief  This function handles SVCall exception.
 */
void SVC_Handler(void)
{
}

/**
 * @brief  This function handles PendSV_Handler exception.
 */
void PendSV_Handler(void)
{
}

/**
 * @brief  This function handles SysTick Handler.
 */
void SysTick_Handler(void)
{
}


/******************************************************************************/
/*                 N32A052X Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_N32A052x.s).                                            */
/******************************************************************************/

/**
*\*\name    TIM2_IRQHandler.
*\*\fun     This function handles TIM2 global interrupt request.
*\*\param   none
*\*\return  none 
**/
void TIM2_IRQHandler(void)
{
    RCC_ClocksType clks;
    if(TIM_GetIntStatus(TIM2, TIM_INT_CC3) != RESET)
    {
        if (CaptureNumber == 0)
        {
            /* Get the Input Capture value */
            IC1ReadValue1 = TIM_GetCap3(TIM2);
        }
        else if (CaptureNumber == 2)
        {
            /* Get the Input Capture value */
            IC1ReadValue2 = TIM_GetCap3(TIM2);

            /* Capture computation */
            if (IC1ReadValue2 > IC1ReadValue1)
            {
                Capture = (IC1ReadValue2 - IC1ReadValue1);
            }
            else
            {
                Capture = ((0xFFFF - IC1ReadValue1) + IC1ReadValue2);
            }
            RCC_GetClocksFreqValue(&clks);
            /* Frequency computation */
            LsiFreq = (uint32_t)clks.Pclk1Freq / Capture;
            LsiFreq *= 32;

        }
        CaptureNumber++;
        /* Clear TIM2 Capture compare interrupt pending bit */
        TIM_ClrIntPendingBit(TIM2, TIM_INT_CC3);
    }
}

