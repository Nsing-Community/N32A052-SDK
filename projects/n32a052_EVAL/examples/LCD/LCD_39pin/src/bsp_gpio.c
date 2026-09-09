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
*\*\file bsp_gpio.c
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/

#include "bsp_gpio.h"

void LCD_GPIO_Init(void)
{
    GPIO_InitType  gpioinitstruct;

    /* Enable LCD GPIO Clocks */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA|RCC_APB2_PERIPH_GPIOB|RCC_APB2_PERIPH_GPIOC|RCC_APB2_PERIPH_GPIOD, ENABLE);
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
    
    /*Init GPIO init struct*/
    GPIO_InitStruct(&gpioinitstruct);

    /* AF7 */
    /////* PB0: SEG0   PD0:SEG6   */////
    gpioinitstruct.Pin    =   GPIO_PIN_0 ;
    gpioinitstruct.GPIO_Mode      = GPIO_MODE_ANALOG;
    gpioinitstruct.GPIO_Pull      = GPIO_NO_PULL;
    gpioinitstruct.GPIO_Current   = GPIO_HIGH_DREIVE;
    gpioinitstruct.GPIO_Alternate = GPIO_AF7_LCD;
    GPIO_InitPeripheral(GPIOB, &gpioinitstruct);
    
    gpioinitstruct.Pin    =   GPIO_PIN_0;
    GPIO_InitPeripheral(GPIOD, &gpioinitstruct);
     
    /* AF8 : */
    /*  PA14: SEG7  PA13: SEG8
        PC5: SEG23  PC6: SEG24   PC7: SEG25   */
//    gpioinitstruct.Pin    = GPIO_PIN_13 | GPIO_PIN_14;
//    gpioinitstruct.GPIO_Alternate = GPIO_AF8_LCD;
//    GPIO_InitPeripheral(GPIOA, &gpioinitstruct);
    
    gpioinitstruct.Pin    =   GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
    gpioinitstruct.GPIO_Alternate = GPIO_AF8_LCD;
    GPIO_InitPeripheral(GPIOC, &gpioinitstruct);
    
    /* AF9 : */
    /*  PB4: SEG13  PB8:SEG16  PB12: SEG5    */
    gpioinitstruct.Pin    =   GPIO_PIN_4 |GPIO_PIN_8 | GPIO_PIN_12 ;
    gpioinitstruct.GPIO_Alternate = GPIO_AF9_LCD;
    GPIO_InitPeripheral(GPIOB, &gpioinitstruct);
    
    /* Port D*/
    /*  PD4:COM0   PD5:COM1  PD8:COM4  PD11:COM7 */
    gpioinitstruct.Pin    =   GPIO_PIN_4 | GPIO_PIN_5; 
    gpioinitstruct.GPIO_Alternate = GPIO_AF9_LCD;
    GPIO_InitPeripheral(GPIOD, &gpioinitstruct);
    
    gpioinitstruct.Pin    =   GPIO_PIN_8 | GPIO_PIN_11; 
    gpioinitstruct.GPIO_Alternate = GPIO_AF8_LCD;
    GPIO_InitPeripheral(GPIOD, &gpioinitstruct);

}


