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
#include "n32a052_uart.h"
#include <stdio.h>
/** Flash_Program **/

#define FLASH_PAGE_SIZE        ((uint16_t)0x200)
#define FLASH_WRITE_START_ADDR ((uint32_t)0x08008000)
#define FLASH_WRITE_END_ADDR   ((uint32_t)0x08010000)

/** Main program. **/
int main(void)
{
    uint32_t Value_temp;
    /* USART Init */
    log_init();
#ifdef BOOT0_START
    log_info("\nboot start in Flash 0x8000000 area !\r\n");
#endif
#ifdef BOOT1_START
    FLASH_SetVTORAddress(0x08010000,FLASH_VTOR_ENABLE);
    log_info("\nboot start in Flash 0x8010000 area !\r\n");
#endif
    
    while (1)
    {
        /* Loop until UART1 DAT register is not empty */
        while (UART_GetFlagStatus(UART1, UART_FLAG_RXDNE) == RESET)
        {
        }

        Value_temp = UART_ReceiveData(UART1);
        
        /* Received reset command from host computer */
#ifdef BOOT0_START
        if(Value_temp == 0x55)
#endif
#ifdef BOOT1_START
        if(Value_temp == 0xAA)
#endif        
        {
            FLASH_Unlock();
            FLASH_EraseOB();
            FLASH_ProgramOptionBytes_RDP1(FLASH_OB_RDP1_DISABLE);
#ifdef BOOT0_START
            /* Configure the FLASH boot address to 0x8010000 */
            FLASH_ProgramOptionBytes_USER5(0x7F);
#endif            
            log_info("System reset !\r\n");
            NVIC_SystemReset();
        }
    }
}

