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
*\*\file n32a052_it.c
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/

#include "n32a052_it.h"
#include "main.h"

uint16_t capture = 0;
extern __IO uint16_t CCR1_Val;
extern __IO uint16_t CCR2_Val;
extern __IO uint16_t CCR3_Val;
extern __IO uint16_t CCR4_Val;

/** Cortex-M0 Processor Exceptions Handlers **/

/**
*\*\name    NMI_Handler.
*\*\fun     This function handles NMI exception.
*\*\param   none
*\*\return  none 
**/
void NMI_Handler(void)
{
}

/**
*\*\name    HardFault_Handler.
*\*\fun     This function handles Hard Fault exception.
*\*\param   none
*\*\return  none 
**/
void HardFault_Handler(void)
{
    /* Go to infinite loop when Hard Fault exception occurs */
    while (1)
    {
    }
}


/**
*\*\name    SVC_Handler.
*\*\fun     This function handles SVCall exception.
*\*\param   none
*\*\return  none 
**/
void SVC_Handler(void)
{
}

/**
*\*\name    PendSV_Handler.
*\*\fun     This function handles PendSV_Handler exception.
*\*\param   none
*\*\return  none 
**/
void PendSV_Handler(void)
{
}

/**
*\*\name    SysTick_Handler.
*\*\fun     This function handles SysTick Handler.
*\*\param   none
*\*\return  none 
**/
void SysTick_Handler(void)
{
}

/**
*\*\name    TIM3_IRQHandler.
*\*\fun     This function handles TIMx interrupts.
*\*\param   none
*\*\return  none 
**/
void TIM3_IRQHandler(void)
{
    /* TIM3_CH1 toggling */
    if (TIM_GetIntStatus(TIM3, TIM_INT_CC1) != RESET)
    {
        TIM_ClrIntPendingBit(TIM3, TIM_INT_CC1);
        capture = TIM_GetCap1(TIM3);
        TIM_SetCmp1(TIM3, capture + CCR1_Val);
    }

    /* TIM3_CH2 toggling */
    if (TIM_GetIntStatus(TIM3, TIM_INT_CC2) != RESET)
    {
        TIM_ClrIntPendingBit(TIM3, TIM_INT_CC2);
        capture = TIM_GetCap2(TIM3);
        TIM_SetCmp2(TIM3, capture + CCR2_Val);
    }

    /* TIM3_CH3 toggling */
    if (TIM_GetIntStatus(TIM3, TIM_INT_CC3) != RESET)
    {
        TIM_ClrIntPendingBit(TIM3, TIM_INT_CC3);
        capture = TIM_GetCap3(TIM3);
        TIM_SetCmp3(TIM3, capture + CCR3_Val);
    }

    /* TIM3_CH4 toggling */
    if (TIM_GetIntStatus(TIM3, TIM_INT_CC4) != RESET)
    {
        TIM_ClrIntPendingBit(TIM3, TIM_INT_CC4);
        capture = TIM_GetCap4(TIM3);
        TIM_SetCmp4(TIM3, capture + CCR4_Val);
    }
}

/* N32A052 Peripherals Interrupt Handlers, interrupt handler's name please refer to the startup file (startup_n32a052.s). */

