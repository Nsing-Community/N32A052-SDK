/**
*     Copyright (c) 2025, Nations Technologies Inc.
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
*\*\file n32a052_dbg.c
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
**/

#include "n32a052_dbg.h"

/**
*\*\name    UCID_Get.
*\*\fun     get unique customer id.
*\*\param   UCIDbuf
*\*\return  none
**/
void GetUCID(uint8_t *UCIDbuf)
{
	uint8_t num;
	
	for (num = 0; num < UCID_LENGTH; num++)
    {
         UCIDbuf[num] = (uint8_t)(*(__IO uint8_t*)(UCID_BASE + num)); 
    }
}


/**
*\*\name    UID_Get.
*\*\fun     get unique device id.
*\*\param   UIDbuf
*\*\return  none
**/
void GetUID(uint8_t *UIDbuf)
{
	uint8_t num;
	
	for (num = 0; num < UID_LENGTH; num ++)
    {
         UIDbuf[num] = (uint8_t)(*(__IO uint8_t*)(UID_BASE + num)); 
    }
}


/**
*\*\name    GetDBGMCU_ID.
*\*\fun     get the DGC_ID number.
*\*\param   none
*\*\return  revision number
**/
void GetDBGMCU_ID(uint8_t *DBGMCU_IDbuf)
{
    uint8_t num;
	
    for (num = 0; num < DBGMCU_ID_LENGTH; num ++)
    {
         DBGMCU_IDbuf[num] = (uint8_t)(*(__IO uint8_t*)(DBGMCU_ID_BASE + num)); 
    }
}
