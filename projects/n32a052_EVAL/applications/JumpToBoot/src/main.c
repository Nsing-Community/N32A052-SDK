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
 
#include "main.h"
#include "log.h"
#include "n32a052.h"
#include "n32a052_gpio.h"
#include "n32a052_uart.h"
#include "n32a052_rcc.h"
#include "n32a052_iwdg.h"
#include "n32a052_flash.h"

/* Constant for BOOT */
uint32_t BootAddr = 0x1FFF0025,SPAddr = 0x20000660;

/* The pointer of function */
typedef void (*pFunction)(void);


/* Function of how to jump to Boot */
void Jump_To_BOOT(void)
{
    /* Disable all interrupt */
    __disable_irq();
    
    /* Config IWDG */
    IWDG_ReloadKey();
    IWDG_WriteConfig(IWDG_WRITE_DISABLE);
    IWDG_SetPrescalerDiv(IWDG_PRESCALER_DIV256);
       
    /* Config system clock as 64M with HSI and PLL  */
    SetSysClock_HSI_PLL();    

    
    /* Set JumpBoot addr */
    pFunction JumpBoot = (pFunction)BootAddr;
    
    /* Initalize Stack Pointer */
    __set_MSP(SPAddr);
    
    /* Enable interrupt */
    __enable_irq();
    
    /* Jump to BOOT */
    JumpBoot();
}

/* Main program. */
int main(void)
{
    /* Init debug usart */
    log_init();
    /* Init a button */
    IAP_Button_Config();
    
    /* Debug information */
    printf("Jump to Boot demo start with normal state!\r\n");
    printf("If you press S1(PA1),system will jump to BOOT!\r\n\r\n");
    
    /* Wait button to be pressed */
    while(IAP_Button_Read() == SET);
    printf("System jumped to BOOT!\r\n\r\n");
    
    /*Jump to BOOT */
    Jump_To_BOOT();
    
    /* Infinite loop */
    while(1);
}


/* Set system clock as 64M with HSI and PLL. */
void SetSysClock_HSI_PLL(void)
{
    /* It is necessary to initialize the RCC peripheral to the reset state.*/
    RCC_DeInit();
    
    /* Enable HSI   */
    RCC_EnableHsi(ENABLE);
    while (RCC_WaitHsiStable() != SUCCESS)
    {
        /*  If HSI failed to start-up,the clock configuration must be wrong.
            User can add some code here to dela with this problem   */
    }
    
    /* Sets the code latency value */
    FLASH_SetLatency(FLASH_LATENCY_2);
    
    /* AHB prescaler factor set to 1,HCLK = SYSCLK = 64M    */
    RCC_ConfigHclk(RCC_SYSCLK_DIV1);
    /* APB2 prescaler factor set to 1,PCLK2 = HCLK = 64M  */
    RCC_ConfigPclk2(RCC_HCLK_DIV1);
    /* APB1 prescaler factor set to 2,PCLK1 = HCLK/2 = 32M  */
    RCC_ConfigPclk1(RCC_HCLK_DIV2);
    
    /* Config PLL */
    RCC_ConfigPll(RCC_PLL_SRC_HSI,RCC_PLL_MUL_16,RCC_PLL_PRE_2, RCC_PLLOUT_DIV_1);
    
    /* Enable PLL */
    RCC_EnablePll(ENABLE);
     /* Wait till PLL is ready */
    while ((RCC->CTRL & RCC_CTRL_PLLRDF) == 0)
    {
    }
    /* Select PLL as system clock source */
    RCC_ConfigSysclk(RCC_SYSCLK_SRC_PLLCLK);

    /* Wait till PLL is used as system clock source */
    while (RCC_GetSysclkSrc() != RCC_CFG_SCLKSTS_PLL);
}

/* Init a button for test */
void IAP_Button_Config(void)
{  
    GPIO_InitType GPIO_InitStructure;

    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA,ENABLE);

    GPIO_InitStructure.Pin              = GPIO_PIN_1;
    GPIO_InitStructure.GPIO_Slew_Rate   = GPIO_SLEW_RATE_SLOW;
    GPIO_InitStructure.GPIO_Pull        = GPIO_PULL_UP;
    GPIO_InitStructure.GPIO_Mode        = GPIO_MODE_INPUT;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
}

/* Get the state of button */
uint8_t IAP_Button_Read(void)
{
    return GPIO_ReadInputDataBit(GPIOA, GPIO_PIN_1);
}


