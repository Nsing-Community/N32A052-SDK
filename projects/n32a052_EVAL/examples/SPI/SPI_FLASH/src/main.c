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
#include <string.h>


#define FLASH_WriteAddress  0x100000
#define FLASH_ReadAddress   FLASH_WriteAddress
#define FLASH_SectorToErase FLASH_WriteAddress

#define LED1 GPIO_PIN_4
#define LED2 GPIO_PIN_5

#define sFLASH_ID sFLASH_GD25Q16_ID
//#define sFLASH_ID sFLASH_516AUGLA1_ID

#define BufferSize (countof(Tx_Buffer) - 1)

#define countof(a) (sizeof(a) / sizeof(*(a)))

uint8_t Tx_Buffer[] = "N32A052 SPI Firmware Library Example: communication with an GD25Q16 SPI FLASH";
uint8_t Rx_Buffer[BufferSize];
__IO uint8_t Index                  = 0x0;
volatile TestStatus TransferStatus1 = FAILED, TransferStatus2 = PASSED;
__IO uint32_t FlashID = 0;

TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);

/**
*\*\name    main.
*\*\fun     main program.
*\*\param   none
*\*\return  none 
**/
int main(void)
{
    /* At this stage the microcontroller clock setting is already configured,
        this is done through SystemInit() function which is called from startup
        file (startup_n32a052.s) before to branch to application main.
        To reconfigure the default setting of SystemInit() function, refer to
        system_n32a052.c file */

    log_init();
    
    log_info(" This is SPI FLASH demo! \r\n");
    
    /* Initialize the SPI FLASH driver */
    sFLASH_Init();
    
    /* Get SPI Flash ID */
    FlashID = sFLASH_ReadID();

    /* Check the SPI Flash ID */
    if (FlashID == sFLASH_ID)
    {
        /* Perform a write in the Flash followed by a read of the written data */
        /* Erase SPI FLASH Sector to write on */
        sFLASH_EraseSector(FLASH_SectorToErase);

        /* Write Tx_Buffer data to SPI FLASH memory */
        sFLASH_WriteBuffer(Tx_Buffer, FLASH_WriteAddress, BufferSize);

        /* Read data from SPI FLASH memory */
        sFLASH_ReadBuffer(Rx_Buffer, FLASH_ReadAddress, BufferSize);

        /* Check the correctness of written dada */
        TransferStatus1 = Buffercmp(Tx_Buffer, Rx_Buffer, BufferSize);
        /* TransferStatus1 = PASSED, if the transmitted and received data by SPI1
           are the same */
        /* TransferStatus1 = FAILED, if the transmitted and received data by SPI1
           are different */

        /* Perform an erase in the Flash followed by a read of the written data */
        /* Erase SPI FLASH Sector to write on */
        sFLASH_EraseSector(FLASH_SectorToErase);

        /* Read data from SPI FLASH memory */
        sFLASH_ReadBuffer(Rx_Buffer, FLASH_ReadAddress, BufferSize);

        /* Check the correctness of erasing operation dada */
        for (Index = 0; Index < BufferSize; Index++)
        {
            if (Rx_Buffer[Index] != 0xFF)
            {
                TransferStatus2 = FAILED;
            }
        }
        /* TransferStatus2 = PASSED, if the specified sector part is erased */
        /* TransferStatus2 = FAILED, if the specified sector part is not well erased */
    }
    else
    {

    }
    
    if(TransferStatus1 == PASSED)
    {
        log_info("SPI FLASH read write OK! \r\n");
    }
    else
    {
        log_info("SPI FLASH read write Fail! \r\n");
    }
    
    if(TransferStatus2 == PASSED)
    {
        log_info("SPI FLASH read erase OK! \r\n");
    }
    else
    {
        log_info("SPI FLASH read erase Fail! \r\n");
    }
    
    while (1)
    {
    }
}


/**
*\*\name    Buffercmp.
*\*\fun     Compares two buffers.
*\*\param   pBuffer1, pBuffer2: buffers to be compared.
*\*\return  PASSED: pBuffer1 identical to pBuffer2
*\*\        FAILED: pBuffer1 differs from pBuffer2 
**/
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength)
{
    while (BufferLength--)
    {
        if (*pBuffer1 != *pBuffer2)
        {
            return FAILED;
        }

        pBuffer1++;
        pBuffer2++;
    }

    return PASSED;
}

