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
*\*\file main.c
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/

#include "n32a052_it.h"
#include "log.h"

GPIO_InitType GPIO_InitStructure;
RCC_ClocksType RCC_ClockFreq;
ErrorStatus HSEStartUpStatus;
ErrorStatus HSIStartUpStatus;
ErrorStatus LSIStartUpStatus;

void NVIC_Configuration(void);
ErrorStatus SetSysClockToHSI(void);
ErrorStatus SetSysClockToHSE(void);
ErrorStatus SetSysClockToPLL(uint32_t freq, uint8_t src);
ErrorStatus SetSysClock_LSI(void);

/**
*\*\name    PrintfClockInfo.
*\*\fun     Printf clock information.
*\*\param   none
*\*\return  none 
**/
void PrintfClockInfo(const char* msg)
{
    log_init(); // should reinit after sysclk changed
    log_info("\n--------------------------------\n");
    log_info("%s:\n", msg);
    RCC_GetClocksFreqValue(&RCC_ClockFreq);
    log_info("SYSCLK: %d\n", RCC_ClockFreq.SysclkFreq);
    log_info("HCLK: %d\n", RCC_ClockFreq.HclkFreq);
    log_info("PCLK1: %d\n", RCC_ClockFreq.Pclk1Freq);
    log_info("PCLK2: %d", RCC_ClockFreq.Pclk2Freq);
}

int main(void)
{

    PrintfClockInfo("After reset");
	
/*** Select one of the following configuration methods ***/
#if SYSCLK_SOURCE_SELECT == SYSCLK_SOURCE_HSI
  /* Method 1  */	
    if(SetSysClockToHSI() == ERROR)
    {
        log_info("Clock configuration failure!\n");
    }
    else
    {
        PrintfClockInfo("HSI, 8MHz");
    }
#elif SYSCLK_SOURCE_SELECT == SYSCLK_SOURCE_HSE 
  /* Method 2  */		
    if(SetSysClockToHSE() == ERROR)
    {
        log_info("Clock configuration failure!\n");
    }
    else
    {
        PrintfClockInfo("HSE, 8MHz");
    }
#elif SYSCLK_SOURCE_SELECT == SYSCLK_SOURCE_LSI 
	/* Method 3  */	
    if(SetSysClock_LSI() == ERROR)
    {
        log_info("Clock configuration failure!\n");
    }
    else
    {
        //Printing is only possible when system clock is LSI and the baud rate is configured to 1200
    }
#elif SYSCLK_SOURCE_SELECT == SYSCLK_SOURCE_HSE_PLL 
  /* Method 4  */	
    if(SetSysClockToPLL(32000000, SYSCLK_SOURCE_HSE) == ERROR)
    {
        log_info("Clock configuration failure!\n");
    }
    else
    {
        PrintfClockInfo("HSE->PLL, 32M");
    }
#elif SYSCLK_SOURCE_SELECT == SYSCLK_SOURCE_HSI_PLL 		
  /* Method 5  */	
    if(SetSysClockToPLL(48000000, SYSCLK_SOURCE_HSI) == ERROR)
    {
        log_info("Clock configuration failure!\n");
    }
    else
    {
        PrintfClockInfo("HSI->PLL, 48M");
    }
#endif
    /* Enable Clock Security System(CSS): this will generate an NMI exception
       when HSE clock fails */
    RCC_EnableClockSecuritySystem(ENABLE);

    /* NVIC configuration
     * ------------------------------------------------------*/
    NVIC_Configuration();

    /* Output HSE clock on MCO pin
     * ---------------------------------------------*/
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);

    GPIO_InitStruct(&GPIO_InitStructure);
    GPIO_InitStructure.Pin             = GPIO_PIN_3;
    GPIO_InitStructure.GPIO_Mode       = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Alternate  = GPIO_AF6_MCO;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);

    RCC_ConfigMcoClkPre(RCC_MCO_PLLCLK_DIV8);
   /*** Select the corresponding MCO clock source ***/
    RCC_ConfigMco(RCC_MCO_PLLCLK_PRES);
    
    while (1);
}

/**
*\*\name    SetSysClockToHSI.
*\*\fun     Selects HSI as System clock source and configure HCLK, PCLK2
*\*\         and PCLK1 prescalers.
*\*\param   none
*\*\return  none 
**/
ErrorStatus SetSysClockToHSI(void)
{
    uint32_t timeout_value = 0xFFFFFFFF; 
    RCC_DeInit();

    RCC_EnableHsi(ENABLE);

    /* Wait till HSI is ready */
    HSIStartUpStatus = RCC_WaitHsiStable();

    if (HSIStartUpStatus == SUCCESS)
    {
        /* Enable Prefetch Buffer */
        FLASH_PrefetchBufSet(FLASH_PrefetchBuf_EN);

        /* Flash 0 wait state */
        FLASH_SetLatency(FLASH_LATENCY_0);

        /* HCLK = SYSCLK */
        RCC_ConfigHclk(RCC_SYSCLK_DIV1);

        /* PCLK2 = HCLK */
        RCC_ConfigPclk2(RCC_HCLK_DIV1);

        /* PCLK1 = HCLK */
        RCC_ConfigPclk1(RCC_HCLK_DIV1);

        /* Select HSI as system clock source */
        RCC_ConfigSysclk(RCC_SYSCLK_SRC_HSI);
           
        /* Wait till HSI is used as system clock source */
        while (RCC_GetSysclkSrc() != RCC_CFG_SCLKSTS_HSI)
        {
            if ((timeout_value--) == 0)
            {
                return ERROR;
            }
        }
    }
    else
    {
        /* If HSI fails to start-up, the application will have wrong clock
           configuration. User can add here some code to deal with this error */
        return ERROR;
    }
    return SUCCESS;
}

/**
*\*\name    SetSysClockToHSE.
*\*\fun     Selects HSE as System clock source and configure HCLK, PCLK2
*\*\          and PCLK1 prescalers.
*\*\param   none
*\*\return  none 
**/
ErrorStatus SetSysClockToHSE(void)
{
    uint32_t timeout_value = 0xFFFFFFFF; 
    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration
     * -----------------------------*/
    /* RCC system reset(for debug purpose) */
    RCC_DeInit();

    /* Enable HSE */
    RCC_ConfigHse(RCC_HSE_ENABLE);

    /* Wait till HSE is ready */
    HSEStartUpStatus = RCC_WaitHseStable();

    if (HSEStartUpStatus == SUCCESS)
    {
        /* Enable Prefetch Buffer */
        FLASH_PrefetchBufSet(FLASH_PrefetchBuf_EN);

        if (HSE_Value <= 18000000)
        {
            /* Flash 0 wait state */
            FLASH_SetLatency(FLASH_LATENCY_0);
        }
        else
        {
            /* Flash 1 wait state */
            FLASH_SetLatency(FLASH_LATENCY_1);
        }

        /* HCLK = SYSCLK */
        RCC_ConfigHclk(RCC_SYSCLK_DIV1);

        /* PCLK2 = HCLK */
        RCC_ConfigPclk2(RCC_HCLK_DIV1);

        /* PCLK1 = HCLK */
        RCC_ConfigPclk1(RCC_HCLK_DIV1);

        /* Select HSE as system clock source */
        RCC_ConfigSysclk(RCC_SYSCLK_SRC_HSE);
       
        /* Wait till HSE is used as system clock source */
        while (RCC_GetSysclkSrc() != RCC_CFG_SCLKSTS_HSE)
        {
            if ((timeout_value--) == 0)
            {
                return ERROR;
            }
        }
    }
    else
    {
        /* If HSE fails to start-up, the application will have wrong clock
           configuration. User can add here some code to deal with this error */
        return ERROR;
    }
    return SUCCESS;
}

/**
*\*\name    SetSysClockToPLL.
*\*\fun     Selects PLL clock as System clock source and configure HCLK, PCLK2
*\*\         and PCLK1 prescalers.
**\*\param   freq
*\*\         - 32000000      
*\*\         - 48000000    
*\*\param   src
*\*\         - SYSCLK_SOURCE_HSI      
*\*\         - SYSCLK_SOURCE_HSE  
*\*\return  none 
*\*\note FIN/N must be set in 4MHz to 16MHz.
*\*\     FIN/N*M must be set in 48MHz to 72MHz
**/
ErrorStatus SetSysClockToPLL(uint32_t freq, uint8_t src)
{
    uint32_t timeout_value = 0xFFFFFFFF; 
    uint32_t pllmul;
    uint32_t plldiv = RCC_PLLOUT_DIV_1;
    uint32_t latency;
    uint32_t pclk1div, pclk2div;

    if ((src == SYSCLK_SOURCE_HSE)&&(HSE_VALUE != 8000000))
    {
        /* HSE_VALUE == 8000000 is needed in this project! */
        return ERROR;
    }

    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration
     * -----------------------------*/
    /* RCC system reset(for debug purpose) */
    RCC_DeInit();

    if (src == SYSCLK_SOURCE_HSI) 
    {
        /* Enable HSI */
        RCC_EnableHsi(ENABLE);

        /* Wait till HSI is ready */
        HSIStartUpStatus = RCC_WaitHsiStable();

        if (HSIStartUpStatus != SUCCESS)
        {
            /* If HSI fails to start-up, the application will have wrong clock
               configuration. User can add here some code to deal with this
               error */
            return ERROR;
        }

    }
    else if (src == SYSCLK_SOURCE_HSE) 
    {
        /* Enable HSE */
        RCC_ConfigHse(RCC_HSE_ENABLE);

        /* Wait till HSE is ready */
        HSEStartUpStatus = RCC_WaitHseStable();

        if (HSEStartUpStatus != SUCCESS)
        {
            /* If HSE fails to start-up, the application will have wrong clock
               configuration. User can add here some code to deal with this
               error */
            return ERROR;
        }

    }

    switch (freq)
    {
        case 32000000:
            latency  = FLASH_LATENCY_1;
            pllmul = RCC_PLL_MUL_16;
            pclk1div = RCC_HCLK_DIV2;
            pclk2div = RCC_HCLK_DIV1;
            plldiv = RCC_PLLOUT_DIV_2;
            break;
        case 48000000:
            latency  = FLASH_LATENCY_2;
		    pllmul = RCC_PLL_MUL_12;
            pclk1div = RCC_HCLK_DIV2;
            pclk2div = RCC_HCLK_DIV1;
		    plldiv = RCC_PLLOUT_DIV_1;
            break;
        default:
            while (1);
    }

    FLASH_SetLatency(latency);

    /* HCLK = SYSCLK */
    RCC_ConfigHclk(RCC_SYSCLK_DIV1);

    /* PCLK2 = HCLK */
    RCC_ConfigPclk2(pclk2div);

    /* PCLK1 = HCLK */
    RCC_ConfigPclk1(pclk1div);
    if(src == SYSCLK_SOURCE_HSE)
    {
        RCC_ConfigPll(RCC_PLL_SRC_HSE,pllmul, RCC_PLL_PRE_2, plldiv);
    }
    else
    {
        RCC_ConfigPll(RCC_PLL_SRC_HSI,pllmul, RCC_PLL_PRE_2, plldiv);
    }

    /* Enable PLL */
    RCC_EnablePll(ENABLE);

    /* Wait till PLL is ready */
   // while (RCC_GetFlagStatus(RCC_CTRL_FLAG_PLLRDF) == RESET);
     /* Wait till PLL is ready */
    while ((RCC->CTRL & RCC_CTRL_PLLRDF) == 0)
    {
        if ((timeout_value--) == 0)
        {
            return ERROR;
        }
    }
    /* Select PLL as system clock source */
    RCC_ConfigSysclk(RCC_SYSCLK_SRC_PLLCLK);

    /* Wait till PLL is used as system clock source */
    timeout_value = 0xFFFFFFFF;
    while (RCC_GetSysclkSrc() != RCC_CFG_SCLKSTS_PLL)
    {
        if ((timeout_value--) == 0)
        {
            return ERROR;
        }
    }
    return SUCCESS;
}

/**
*\*\name    SetSysClock_LSI.
*\*\fun     Selects LSI as System clock source and configure HCLK, PCLK2
*\*\         and PCLK1 prescalers.
*\*\param   none
*\*\return  none 
**/
ErrorStatus SetSysClock_LSI(void)
{
    uint32_t timeout_value = 0xFFFFFFFF; 
    RCC_DeInit();
    
    RCC_EnableLsi(ENABLE);
    /* Wait till LSI is ready */
    LSIStartUpStatus = RCC_WaitLsiStable();
    
    if (LSIStartUpStatus == SUCCESS)
    {
        /*** set systems clock ***/
        /* HCLK = SYSCLK */
        RCC_ConfigHclk(RCC_SYSCLK_DIV1);

        /* PCLK2 = HCLK */
        RCC_ConfigPclk2(RCC_HCLK_DIV1);

        /* PCLK1 = HCLK */
        RCC_ConfigPclk1(RCC_HCLK_DIV1);
    
        FLASH_SetLatency(FLASH_LATENCY_0);
        
        RCC_ConfigSysclk(RCC_SYSCLK_SRC_LSI);
        while (RCC_GetSysclkSrc() != RCC_CFG_SCLKSTS_LSI)
        {
            if ((timeout_value--) == 0)
            {
                return ERROR;
            }
        }
    }
    else
    {
        /* If LSI fails to start-up, the application will have wrong clock
           configuration. User can add here some code to deal with this error */
        return ERROR;
    }
    return SUCCESS;

}


void NVIC_Configuration(void)
{
    NVIC_InitType NVIC_InitStructure;

    /* Enable and configure RCC global IRQ channel */
    NVIC_InitStructure.NVIC_IRQChannel                   = RCC_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority           = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}



