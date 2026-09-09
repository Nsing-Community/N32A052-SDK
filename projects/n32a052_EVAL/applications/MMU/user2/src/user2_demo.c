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
*\*\file user2_demo.c
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/

#include "user2_demo.h"
#include "user2_led_demo.h"
#include <stdio.h>
#include "main.h"

uint32_t test_data __attribute__((at(0x20002A00)));
void Test_User2(void) __attribute__((section(".ARM.__at_0x08016000")));

void Test_ProgramFlashWord(uint32_t Address, uint32_t Data)
{  
    /* Unlocks the FLASH Program Erase Controller */
    FLASH_Unlock();

    /* Erase */
    if (FLASH_EOP != FLASH_EraseOnePage(Address))
    {
        while(1)
        {
            printf("Flash EraseOnePage Error. Please Deal With This Error Promptly\r\n");
        }
    }

    /* Program */
    if (FLASH_EOP != FLASH_ProgramdoubleWord(Address, Data,Data))
    {
        while(1)
        {
            printf("Flash ProgramWord Error. Please Deal With This Error Promptly\r\n");
        }
    }       

    /* Locks the FLASH Program Erase Controller */
    FLASH_Lock();

    /* Check */
    if (Data != (*(__IO uint32_t *)(Address)))
    {
        printf("Flash Program Test Failed\r\n");
        
    }   
}


void Test_InitData(void)
{
    test_data = 0x01234567;
}

void Test_User2(void)
{
    uint32_t flash_write_data = 0x76543210;
    Test_InitData();
    /* USART Configuration */
    // log_init(); 
    /* Output a message on Hyperterminal using printf function */
    printf("\n\rHello! Here is USER2 Example!\n\r");

    /* LED2 Blinks */
    Test_LedBlink(LED2_PORT, LED2_PIN);
    
    /* Program USER2 FLASH */
    Test_ProgramFlashWord(0x08017800, flash_write_data);
    
    /* Read USER2 FLASH */
    printf("USER2 Get USER2 FLASH *0x08017800 = 0x%X\r\n", *(__IO uint32_t*)(0x08017800));
    
    /* Read USER2 FLASH */
    printf("USER2 Get USER2 SRAM *0x20002A00 = 0x%X\r\n", *(__IO uint32_t*)(0x20002A00));
}

