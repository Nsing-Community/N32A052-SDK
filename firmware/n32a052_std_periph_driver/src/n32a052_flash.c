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
*\*\file system_n32a052.c
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/
#include "n32a052_flash.h"


/**
*\*\name    FLASH_SetLatency
*\*\fun     Sets the code latency value.
*\*\param   FLASH_Latency :(The input parameters must be the following values)
*\*\            - FLASH_LATENCY_0    FLASH Zero Latency cycle, 0 < SYCCLK <= 24MHz      
*\*\            - FLASH_LATENCY_1    FLASH One Latency cycle, 24MHz < SYCCLK <= 48MHz
*\*\            - FLASH_LATENCY_2    FLASH Two Latency cycle, 48MHz < SYCCLK <= 64MHz
*\*\return  none
*\*\note    The larger the latency, the longer the flash read operation will take. 
*\*\        If not necessary, it is recommended to use a smaller latency.
**/
void FLASH_SetLatency(uint32_t FLASH_Latency)
{
    uint32_t tmpregister;

    /* Read the AC register */
    tmpregister = FLASH->AC;

    /* Sets the Latency value */
    tmpregister &= (~FLASH_LATENCY_MASK);
    tmpregister |= FLASH_Latency;

    /* Write the AC register */
    FLASH->AC = tmpregister;
}

/**
*\*\name    FLASH_GetLatency
*\*\fun     Get the code latency value.
*\*\param   none
*\*\return  FLASH_LATENCY :(The input parameters must be the following values)
*\*\            - FLASH_LATENCY_0    FLASH Zero Latency cycle, 0 < SYCCLK <= 24MHz      
*\*\            - FLASH_LATENCY_1    FLASH One Latency cycle, 24MHz < SYCCLK <= 48MHz
*\*\            - FLASH_LATENCY_2    FLASH Two Latency cycle, 48MHz < SYCCLK <= 64MHz
**/
uint8_t FLASH_GetLatency(void)
{
    /* Read the AC register */
    return (uint8_t)(FLASH->AC & FLASH_LATENCY_MASK);
}


/**
*\*\name    FLASH_PrefetchBufSet
*\*\fun     Enables or disables the Prefetch Buffer.
*\*\param   FLASH_PrefetchBuf:(The input parameters must be the following values)
*\*\            - FLASH_PrefetchBuf_EN      
*\*\            - FLASH_PrefetchBuf_DIS
*\*\return  none
**/
void FLASH_PrefetchBufSet(uint32_t FLASH_PrefetchBuf)
{
    /* Enable or disable the Prefetch Buffer */
    FLASH->AC &= FLASH_PrefetchBuf_MSK;
    FLASH->AC |= FLASH_PrefetchBuf;
}

/**
*\*\name   FLASH_Unlock
*\*\fun    Unlocks the FLASH Program Erase Controller.
*\*\param  none
*\*\return none
*\*\note   Before operating the FLASH_CTRL register, you need to call the FLASH_Unlock function to unlock the LOCK bit.
**/
void FLASH_Unlock(void)
{
    FLASH->KEY = FLASH_KEY1;
    FLASH->KEY = FLASH_KEY2;
}


/**
*\*\name   FLASH_Lock
*\*\fun    Locks the FLASH Program Erase Controller.
*\*\param  none
*\*\return none
**/
void FLASH_Lock(void)
{
    FLASH->CTRL |= CTRL_Set_LOCK;
}


/**
*\*\name   Flash_GetLockStatus
*\*\fun    Get the Flash lock status.
*\*\param  none
*\*\return FlagStatus :
*\*\            - SET     FLASH is in Lock state
*\*\            - RESET   FLASH is in Unlock state
**/
FlagStatus Flash_GetLockStatus(void)
{
    FlagStatus bit_status;
    if ((FLASH->CTRL & CTRL_Set_LOCK) != (uint32_t)RESET)
    {
        bit_status = SET;
    }
    else
    {
        bit_status =  RESET;
    }
    return bit_status;
}


/**
*\*\name   Option_Bytes_Unlock
*\*\fun    Unlocks the Option_Bytes Program Erase Controller.
*\*\param  none
*\*\return none
**/
void Option_Bytes_Unlock(void)
{
    FLASH->OPTKEY = FLASH_KEY1;
    FLASH->OPTKEY = FLASH_KEY2;
}


/**
*\*\name   Option_Bytes_Lock
*\*\fun    Locks the Option_Bytes Program Erase Controller.
*\*\param  none
*\*\return none
**/
void Option_Bytes_Lock(void)
{
    /* Set the FLASH_CTRL_SET_OPTWE Bit to lock */
    FLASH->CTRL &= (~FLASH_CTRL_SET_OPTWE);
}


/**
*\*\name   OB_GetLockStatus
*\*\fun    Get the Option Bytes lock status.
*\*\param  none
*\*\return FlagStatus :
*\*\            - SET     Option byte is in Unlock state
*\*\            - RESET   Option byte is in Lock state
**/
FlagStatus OB_GetLockStatus(void)
{
    FlagStatus bit_status;
    if ((FLASH->CTRL & FLASH_CTRL_SET_OPTWE) != (uint32_t)RESET)
    {
        bit_status = SET;
    }
    else
    {
        bit_status =  RESET;
    }
    return bit_status;
}


/**
*\*\name   FLASH_EraseOnePage
*\*\fun    Erases a specified main FLASH page.
*\*\param  Page_Address :(The input parameters must be the following values)
*\*\            - main flash, it ranges from 0x08000000 to 0x0801FFFF, it must be a multiple of 0x200
*\*\            - data flash, it ranges from 0x1FFF1000 to 0x1FFF2FFF, it must be a multiple of 0x200
*\*\return FLASH_STS : 
*\*\            - FLASH_BUSY     FLASH is busy
*\*\            - FLASH_ERR_PG   FLASH programming error
*\*\            - FLASH_ERR_WRP  FLASH Write protected error
*\*\            - FLASH_EOP      FLASH End of Operation
*\*\            - FLASH_TIMEOUT  FLASH operation timeout
**/
FLASH_STS FLASH_EraseOnePage(uint32_t Page_Address)
{
    FLASH_STS status;

    /* Clears the FLASH's pending flags */
    FLASH_ClearFlag(FLASH_STS_CLRFLAG);
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOpt(EraseTimeout);

    if (status == FLASH_EOP)
    {
        /* if the previous operation is completed, proceed to erase the page */
        FLASH->CTRL |= CTRL_Set_PER;
        FLASH->ADD = Page_Address;
        FLASH->CTRL |= CTRL_Set_START;

        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOpt(EraseTimeout);

        /* Disable the PER Bit */
        FLASH->CTRL &= CTRL_Reset_PER;
    }

    /* Return the Erase Status */
    return status;
}


/**
*\*\name   FLASH_MassErase
*\*\fun    Erases all main FLASH pages.
*\*\param  none
*\*\return FLASH_STS : 
*\*\            - FLASH_BUSY     FLASH is busy
*\*\            - FLASH_ERR_PG   FLASH programming error
*\*\            - FLASH_ERR_WRP  FLASH Write protected error
*\*\            - FLASH_EOP      FLASH End of Operation
*\*\            - FLASH_TIMEOUT  FLASH operation timeout
**/
FLASH_STS FLASH_MassErase(void)
{
    FLASH_STS status;

    /* Clears the FLASH's pending flags */
    FLASH_ClearFlag(FLASH_STS_CLRFLAG);
    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOpt(EraseTimeout);

    if (status == FLASH_EOP)
    {
        /* if the previous operation is completed, proceed to erase all pages */
        FLASH->CTRL |= CTRL_Set_MER;
        FLASH->CTRL |= CTRL_Set_START;

        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOpt(EraseTimeout);

        /* Disable the MER Bit */
        FLASH->CTRL &= CTRL_Reset_MER;
    }

    /* Return the Erase Status */
    return status;
}


/**
*\*\name   FLASH_ProgramdoubleWord
*\*\fun    Programs two words at a specified address.
*\*\param  address :(The input parameters must be the following values)
*\*\            - main flash, it ranges from 0x08000000 to 0x0801FFFF, it must be a multiple of 0x08
*\*\            - data flash, it ranges from 0x1FFF1000 to 0x1FFF2FFF, it must be a multiple of 0x08
*\*\param  data0 :(The input parameters must be the following values)
*\*\            - It ranges from 0x00000000 to 0xFFFFFFFF
*\*\param  data1 :(The input parameters must be the following values)
*\*\            - It ranges from 0x00000000 to 0xFFFFFFFF
*\*\return FLASH_STS : 
*\*\            - FLASH_BUSY     FLASH is busy
*\*\            - FLASH_ERR_PG   FLASH programming error
*\*\            - FLASH_ERR_WRP  FLASH Write protected error
*\*\            - FLASH_EOP      FLASH End of Operation
*\*\            - FLASH_ERR_ADD  FLASH address error
*\*\            - FLASH_TIMEOUT  FLASH operation timeout
**/
FLASH_STS FLASH_ProgramdoubleWord(uint32_t address, uint32_t data0,uint32_t data1)
{
    FLASH_STS status_value = FLASH_EOP;

    if((address & FLASH_WORD_LENGTH) != (uint32_t)0x00)
    {
        /* The programming address is not a multiple of 8 */
        status_value = FLASH_ERR_ADD;
    }
    else
    {
        /*No process*/
    }

    if(status_value == FLASH_ERR_ADD)
    {
    
    }
    else
    {
        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(ProgramTimeout);
    }

    if (status_value == FLASH_EOP)
    {
        /* if the previous operation is completed, proceed to program the new word */
        FLASH->CTRL |= CTRL_Set_PG;

        *(__IO uint32_t*)address = (uint32_t)data0;
        *(__IO uint32_t*)(address + (uint32_t)0x4) = (uint32_t)data1;
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(ProgramTimeout);

        /* Disable the PG Bit */
        FLASH->CTRL &= CTRL_Reset_PG;
    }
    else
    {
        /*No process*/
    }
    
    /* Return the Program status_value */
    return status_value;
}

/**
*\*\name   FLASH_EraseOB
*\*\fun    Erases the FLASH option bytes.
*\*\param  none
*\*\return FLASH_STS : 
*\*\            - FLASH_BUSY     FLASH is busy
*\*\            - FLASH_ERR_PG   FLASH programming error
*\*\            - FLASH_ERR_WRP  FLASH Write protected error
*\*\            - FLASH_EOP      FLASH End of Operation
*\*\            - FLASH_ERR_RDP2 FLASH is in read protection L2 status
*\*\            - FLASH_TIMEOUT  FLASH operation timeout
**/
FLASH_STS FLASH_EraseOB(void)
{
    FLASH_STS status_value = FLASH_EOP;

    /* Get the actual read protection L2 Option Byte value */
    if (FLASH_GetReadOutProtectionL2STS() != RESET)
    {
        status_value = FLASH_ERR_RDP2;
    }
    else
    {
        /*No process*/
    }
    
    if(status_value == FLASH_ERR_RDP2)
    {
    
    }
    else
    {
        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(EraseTimeout);
    }

    if (status_value == FLASH_EOP)
    {
        Option_Bytes_Unlock();

        /* if the previous operation is completed, proceed to erase the option bytes */
        FLASH->CTRL |= CTRL_Set_OPTER;
        FLASH->CTRL |= CTRL_Set_START;
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(EraseTimeout);

        if (status_value == FLASH_EOP)
        {
            /* Clears the FLASH's pending flags */
            FLASH_ClearFlag(FLASH_STS_CLRFLAG);

            /* if the erase operation is completed, disable the OPTER Bit */
            FLASH->CTRL &= CTRL_Reset_OPTER;
        }
        else
        {
            if (status_value != FLASH_TIMEOUT)
            {
                /* Disable the OPTER Bit */
                FLASH->CTRL &= CTRL_Reset_OPTER;
            }
            else
            {
                /*No process*/
            }
        }
    }
    else
    {
        /*No process*/
    }
    /* Return the erase status_value */
    return status_value;
}


/**
*\*\name   FLASH_ProgramOptionBytes_RDP1
*\*\fun    Programs the Option Byte: RDP1.
*\*\param  option_byte_rpd1 :(The input parameters must be the following values)
*\*\        - FLASH_OB_RDP1_ENABLE   Enable read protection L1
*\*\        - FLASH_OB_RDP1_DISABLE  Disable read protection L1
*\*\return FLASH_STS : 
*\*\        - FLASH_BUSY     FLASH is busy
*\*\        - FLASH_ERR_PG   FLASH programming error
*\*\        - FLASH_ERR_WRP  FLASH Write protected error
*\*\        - FLASH_EOP      FLASH End of Operation
*\*\        - FLASH_ERR_RDP2 FLASH is in read protection L2 status
*\*\        - FLASH_TIMEOUT  FLASH operation timeout
**/
FLASH_STS FLASH_ProgramOptionBytes_RDP1(uint8_t option_byte_rpd1)
{
    FLASH_STS status_value = FLASH_EOP;

    /* Get the actual read protection L2 Option Byte value */
    if (FLASH_GetReadOutProtectionL2STS() != RESET)
    {
        status_value = FLASH_ERR_RDP2;
    }
    else
    {
        /*No process*/
    }
    
    if(status_value == FLASH_ERR_RDP2)
    {
    
    }
    else
    {
        Option_Bytes_Unlock();
      
        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(ProgramTimeout);
    }

    if (status_value == FLASH_EOP)
    {
        /* Enable the Option Bytes Programming operation */
        FLASH->CTRL |= CTRL_Set_OPTPG;
        /* Restore the last read protection Option Byte value */
        OBT->RDP1 = (uint32_t)option_byte_rpd1;
        OBT->RESERVED0 = (uint32_t)FLASH_OB_MASK;
        
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(ProgramTimeout);
        if (status_value != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= CTRL_Reset_OPTPG;
        }
        else
        {
            /*No process*/
        }
    }
    else
    {
        /*No process*/
    }

    /* Return the Option Byte program status_value */
    return status_value;
}


/**
*\*\name   FLASH_ProgramOptionBytes_USER1
*\*\fun    Programs the Option Byte: WDG_SW / RST_STOP / RST_PD / nBOOT0 / nBOOT1 / nSWBOOT0 / BOOT0_CFG.
*\*\param  option_byte_iwdg :(The input parameters must be the following values)
*\*\            - FLASH_OB_IWDG_SOFTWARE Software IWDG selected
*\*\            - FLASH_OB_IWDG_HARDWARE Hardware IWDG selected
*\*\param  option_byte_stop :(The input parameters must be the following values)
*\*\            - FLASH_OB_STOP_NORST No reset generated when entering in STOP
*\*\            - FLASH_OB_STOP_RST Reset generated when entering in STOP
*\*\param  option_byte_PD :(The input parameters must be the following values)
*\*\            - FLASH_OB_PD_NORST No reset generated when entering in PD
*\*\            - FLASH_OB_PD_RST Reset generated when entering in PD
*\*\param   option_byte_nBOOT0 :(The input parameters must be the following values)
*\*\            - FLASH_OB_NBOOT0_SET Set nBOOT0
*\*\            - FLASH_OB_NBOOT0_CLR Clear nBOOT0
*\*\param   option_byte_nBOOT1 :(The input parameters must be the following values)
*\*\            - FLASH_OB_NBOOT1_SET Set nBOOT1
*\*\            - FLASH_OB_NBOOT1_CLR Clear nBOOT1
*\*\param   option_byte_nSWBOOT0 :(The input parameters must be the following values)
*\*\            - FLASH_OB_NSWBOOT0_SET Set nSWBOOT0
*\*\            - FLASH_OB_NSWBOOT0_CLR Clear nSWBOOT0
*\*\param   option_byte_BOOT0_CFG :(The input parameters must be the following values)
*\*\            - FLASH_OB_BOOT0_CFG_HIGH Boot0 high active
*\*\            - FLASH_OB_BOOT0_CFG_LOW  Boot0 low active
*\*\return FLASH_STS : 
*\*\        - FLASH_BUSY     FLASH is busy
*\*\        - FLASH_ERR_PG   FLASH programming error
*\*\        - FLASH_ERR_WRP  FLASH Write protected error
*\*\        - FLASH_EOP      FLASH End of Operation
*\*\        - FLASH_ERR_RDP2 FLASH is in read protection L2 status
*\*\        - FLASH_TIMEOUT  FLASH operation timeout
**/
FLASH_STS FLASH_ProgramOptionBytes_USER1(uint32_t option_byte_iwdg, uint32_t option_byte_stop, uint32_t option_byte_PD, \
                                           uint32_t option_byte_nBOOT0, uint32_t option_byte_nBOOT1, uint32_t option_byte_nSWBOOT0,\
                                           uint32_t option_byte_BOOT0_CFG)
{
    FLASH_STS status_value = FLASH_EOP;

    /* Get the actual read protection L2 Option Byte value */
    if (FLASH_GetReadOutProtectionL2STS() != RESET)
    {
        status_value = FLASH_ERR_RDP2;
    }
    else
    {
        /*No process*/
    }
    
    if(status_value == FLASH_ERR_RDP2)
    {
    
    }
    else
    {
        Option_Bytes_Unlock();
      
        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(ProgramTimeout);
    }

    if (status_value == FLASH_EOP)
    {
        /* Enable the Option Bytes Programming operation */
        FLASH->CTRL |= CTRL_Set_OPTPG;
        /* Restore the last read protection Option Byte value */
        OBT->USER1 = ((uint32_t)(option_byte_iwdg | option_byte_stop | option_byte_PD | \
                                option_byte_nBOOT0 | option_byte_nBOOT1 | option_byte_nSWBOOT0 | \
                                option_byte_BOOT0_CFG));
        OBT->RESERVED1 = (uint32_t)FLASH_OB_MASK;
        
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(ProgramTimeout);
        if (status_value != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= CTRL_Reset_OPTPG;
        }
        else
        {
            /*No process*/
        }
    }
    else
    {
        /*No process*/
    }

    /* Return the Option Byte program status_value */
    return status_value;
}


/**
*\*\name   FLASH_ProgramOptionBytes_USER2
*\*\fun    Programs the Option Byte: LVRLS[3:0] / LVREN / LVRRSTEN / LVRFILEN.
*\*\param  option_byte_LVR_cnt :(The input parameters must be the following values)
*\*\                - 0x00 to 0x0F  LVR gear selection
*\*\param  option_byte_LVR : (The input parameters must be the following values)
*\*\                - FLASH_OB_USER_LVR_ENABLE LVR enable
*\*\                - FLASH_OB_USER_LVR_DISABLE LVR disable
*\*\param  option_byte_LVR_reset : (The input parameters must be the following values)
*\*\                - FLASH_OB_USER_LVRRST_ENABLE  LVR reset enable
*\*\                - FLASH_OB_USER_LVRRST_DISABLE LVR reset disable
*\*\param  option_byte_LVR_filter : (The input parameters must be the following values)
*\*\                - FLASH_OB_USER_LVRFIL_ENABLE LVR filter enable
*\*\                - FLASH_OB_USER_LVRFIL_DISABLE LVR filter disable
*\*\return FLASH_STS : 
*\*\        - FLASH_BUSY     FLASH is busy
*\*\        - FLASH_ERR_PG   FLASH programming error
*\*\        - FLASH_ERR_WRP  FLASH Write protected error
*\*\        - FLASH_EOP      FLASH End of Operation
*\*\        - FLASH_ERR_RDP2 FLASH is in read protection L2 status
*\*\        - FLASH_TIMEOUT  FLASH operation timeout
**/
FLASH_STS FLASH_ProgramOptionBytes_USER2(uint32_t option_byte_LVR_cnt, uint32_t option_byte_LVR, uint32_t option_byte_LVR_reset, \
                                         uint32_t option_byte_LVR_filter)
{
    FLASH_STS status_value = FLASH_EOP;

    /* Get the actual read protection L2 Option Byte value */
    if (FLASH_GetReadOutProtectionL2STS() != RESET)
    {
        status_value = FLASH_ERR_RDP2;
    }
    else
    {
        /*No process*/
    }
    
    if(status_value == FLASH_ERR_RDP2)
    {
    
    }
    else
    {
        Option_Bytes_Unlock();
      
        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(ProgramTimeout);
    }

    if (status_value == FLASH_EOP)
    {
        /* Enable the Option Bytes Programming operation */
        FLASH->CTRL |= CTRL_Set_OPTPG;
        /* Restore the last read protection Option Byte value */
        OBT->USER2 = ((uint32_t)(option_byte_LVR_cnt | option_byte_LVR | option_byte_LVR_reset | \
                                option_byte_LVR_filter ));
        OBT->RESERVED2 = (uint32_t)FLASH_OB_MASK;
        
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(ProgramTimeout);
        if (status_value != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= CTRL_Reset_OPTPG;
        }
        else
        {
            /*No process*/
        }
    }
    else
    {
        /*No process*/
    }

    /* Return the Option Byte program status_value */
    return status_value;
}


/**
*\*\name   FLASH_ProgramOptionBytes_USER3
*\*\fun    Programs the Option Byte: USER3.
*\*\param  option_byte_user3:(The input parameters must be the following values)
*\*\                - 0x00 to 0xFF  LVR filter control count value,30~8192us
*\*\return FLASH_STS : 
*\*\        - FLASH_BUSY     FLASH is busy
*\*\        - FLASH_ERR_PG   FLASH programming error
*\*\        - FLASH_ERR_WRP  FLASH Write protected error
*\*\        - FLASH_EOP      FLASH End of Operation
*\*\        - FLASH_ERR_RDP2 FLASH is in read protection L2 status
*\*\        - FLASH_TIMEOUT  FLASH operation timeout
**/
FLASH_STS FLASH_ProgramOptionBytes_USER3(uint32_t option_byte_user3)
{
    FLASH_STS status_value = FLASH_EOP;

    /* Get the actual read protection L2 Option Byte value */
    if (FLASH_GetReadOutProtectionL2STS() != RESET)
    {
        status_value = FLASH_ERR_RDP2;
    }
    else
    {
        /*No process*/
    }
    
    if(status_value == FLASH_ERR_RDP2)
    {
    
    }
    else
    {
        Option_Bytes_Unlock();
      
        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(ProgramTimeout);
    }

    if (status_value == FLASH_EOP)
    {
        /* Enable the Option Bytes Programming operation */
        FLASH->CTRL |= CTRL_Set_OPTPG;
        /* Restore the last read protection Option Byte value */
        OBT->USER3 = ((uint32_t)option_byte_user3);
        OBT->RESERVED3 = (uint32_t)FLASH_OB_MASK;
        
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(ProgramTimeout);
        if (status_value != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= CTRL_Reset_OPTPG;
        }
        else
        {
            /*No process*/
        }
    }
    else
    {
        /*No process*/
    }

    /* Return the Option Byte program status_value */
    return status_value;
}


/**
*\*\name   FLASH_ProgramOptionBytes_USER4
*\*\fun    Programs the Option Byte: USER4.
*\*\param  option_byte_user4:(The input parameters must be the following values)
*\*\                - 0x00 to 0xFF  PDR/POR filter control count value,30~8192us
*\*\return FLASH_STS : 
*\*\        - FLASH_BUSY     FLASH is busy
*\*\        - FLASH_ERR_PG   FLASH programming error
*\*\        - FLASH_ERR_WRP  FLASH Write protected error
*\*\        - FLASH_EOP      FLASH End of Operation
*\*\        - FLASH_ERR_RDP2 FLASH is in read protection L2 status
*\*\        - FLASH_TIMEOUT  FLASH operation timeout
**/
FLASH_STS FLASH_ProgramOptionBytes_USER4(uint32_t option_byte_user4)
{
    FLASH_STS status_value = FLASH_EOP;

    /* Get the actual read protection L2 Option Byte value */
    if (FLASH_GetReadOutProtectionL2STS() != RESET)
    {
        status_value = FLASH_ERR_RDP2;
    }
    else
    {
        /*No process*/
    }
    
    if(status_value == FLASH_ERR_RDP2)
    {
    
    }
    else
    {
        Option_Bytes_Unlock();
      
        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(ProgramTimeout);
    }

    if (status_value == FLASH_EOP)
    {
        /* Enable the Option Bytes Programming operation */
        FLASH->CTRL |= CTRL_Set_OPTPG;
        /* Restore the last read protection Option Byte value */
        OBT->USER4 = ((uint32_t)option_byte_user4);
        OBT->RESERVED4 = (uint32_t)FLASH_OB_MASK;
        
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(ProgramTimeout);
        if (status_value != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= CTRL_Reset_OPTPG;
        }
        else
        {
            /*No process*/
        }
    }
    else
    {
        /*No process*/
    }

    /* Return the Option Byte program status_value */
    return status_value;
}


/**
*\*\name   FLASH_ProgramOptionBytes_USER5
*\*\fun    Programs the Option Byte: USER5.
*\*\param  option_byte_user5:(The input parameters must be the following values)
*\*\                - 0x00 to 0xFF  FLASH boot start address, 0xff corresponds to 0x8000000, 0x00 corresponds to:0x801FE00, and increment 0x200
*\*\return FLASH_STS : 
*\*\        - FLASH_BUSY     FLASH is busy
*\*\        - FLASH_ERR_PG   FLASH programming error
*\*\        - FLASH_ERR_WRP  FLASH Write protected error
*\*\        - FLASH_EOP      FLASH End of Operation
*\*\        - FLASH_ERR_RDP2 FLASH is in read protection L2 status
*\*\        - FLASH_TIMEOUT  FLASH operation timeout
**/
FLASH_STS FLASH_ProgramOptionBytes_USER5(uint32_t option_byte_user5)
{
    FLASH_STS status_value = FLASH_EOP;

    /* Get the actual read protection L2 Option Byte value */
    if (FLASH_GetReadOutProtectionL2STS() != RESET)
    {
        status_value = FLASH_ERR_RDP2;
    }
    else
    {
        /*No process*/
    }
    
    if(status_value == FLASH_ERR_RDP2)
    {
    
    }
    else
    {
        Option_Bytes_Unlock();
      
        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(ProgramTimeout);
    }

    if (status_value == FLASH_EOP)
    {
        /* Enable the Option Bytes Programming operation */
        FLASH->CTRL |= CTRL_Set_OPTPG;
        /* Restore the last read protection Option Byte value */
        OBT->USER5 = ((uint32_t)option_byte_user5);
        OBT->RESERVED5 = (uint32_t)FLASH_OB_MASK;
        
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(ProgramTimeout);
        if (status_value != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= CTRL_Reset_OPTPG;
        }
        else
        {
            /*No process*/
        }
    }
    else
    {
        /*No process*/
    }

    /* Return the Option Byte program status_value */
    return status_value;
}


/**
*\*\name   FLASH_ProgramOptionBytes_USER6
*\*\fun    Programs the Option Byte: USER6. Serial port pins for boot selection.
*\*\param  option_byte_user6:(The input parameters must be the following values)
*\*\                - 0x00 to 0x03  
*\*\                  0x00:PB10&PB11  0x01:PD10&PD11  0x02: PA2&PA3  0x03: PA9&PA10
*\*\return FLASH_STS : 
*\*\        - FLASH_BUSY     FLASH is busy
*\*\        - FLASH_ERR_PG   FLASH programming error
*\*\        - FLASH_ERR_WRP  FLASH Write protected error
*\*\        - FLASH_EOP      FLASH End of Operation
*\*\        - FLASH_ERR_RDP2 FLASH is in read protection L2 status
*\*\        - FLASH_TIMEOUT  FLASH operation timeout
**/
FLASH_STS FLASH_ProgramOptionBytes_USER6(uint32_t option_byte_user6)
{
    FLASH_STS status_value = FLASH_EOP;

    /* Get the actual read protection L2 Option Byte value */
    if (FLASH_GetReadOutProtectionL2STS() != RESET)
    {
        status_value = FLASH_ERR_RDP2;
    }
    else
    {
        /*No process*/
    }
    
    if(status_value == FLASH_ERR_RDP2)
    {
    
    }
    else
    {
        Option_Bytes_Unlock();
      
        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(ProgramTimeout);
    }

    if (status_value == FLASH_EOP)
    {
        /* Enable the Option Bytes Programming operation */
        FLASH->CTRL |= CTRL_Set_OPTPG;
        /* Restore the last read protection Option Byte value */
        OBT->USER6 = ((uint32_t)option_byte_user6);
        OBT->RESERVED6 = (uint32_t)FLASH_OB_MASK;
        
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(ProgramTimeout);
        if (status_value != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= CTRL_Reset_OPTPG;
        }
        else
        {
            /*No process*/
        }
    }
    else
    {
        /*No process*/
    }

    /* Return the Option Byte program status_value */
    return status_value;
}


/**
*\*\name   FLASH_ProgramOptionBytes_DATA0
*\*\fun    Programs a half word at a specified Option Byte Data0.
*\*\note   This function can be used for N32A052 devices.
*\*\param  option_byte_data0:(The input parameters must be the following values)
*\*\                - 0x00 to 0xFF
*\*\return FLASH_STS: The returned value can be: 
*\*\        - FLASH_BUSY     FLASH is busy
*\*\        - FLASH_ERR_PG   FLASH programming error
*\*\        - FLASH_ERR_WRP  FLASH Write protected error
*\*\        - FLASH_EOP      FLASH End of Operation
*\*\        - FLASH_ERR_RDP2 FLASH is in read protection L2 status
*\*\        - FLASH_TIMEOUT  FLASH operation timeout
**/
FLASH_STS FLASH_ProgramOptionBytes_DATA0(uint32_t option_byte_data0)
{
    FLASH_STS status_value = FLASH_EOP;

    /* Get the actual read protection L2 Option Byte value */
    if (FLASH_GetReadOutProtectionL2STS() != RESET)
    {
        status_value = FLASH_ERR_RDP2;
    }
    else
    {
        /*No process*/
    }
    
    if(status_value == FLASH_ERR_RDP2)
    {
    
    }
    else
    {
        Option_Bytes_Unlock();
      
        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(ProgramTimeout);
    }

    if (status_value == FLASH_EOP)
    {
        /* Enable the Option Bytes Programming operation */
        FLASH->CTRL |= CTRL_Set_OPTPG;
        /* Restore the last read protection Option Byte value */
        OBT->Data0 = ((uint32_t)option_byte_data0);
        OBT->RESERVED7 = (uint32_t)FLASH_OB_MASK;
        
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(ProgramTimeout);
        if (status_value != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= CTRL_Reset_OPTPG;
        }
        else
        {
            /*No process*/
        }
    }
    else
    {
        /*No process*/
    }

    /* Return the Option Byte program status_value */
    return status_value;
}


/**
*\*\name   FLASH_ProgramOptionBytes_DATA1
*\*\fun    Programs a half word at a specified Option Byte Data1.
*\*\note   This function can be used for N32A052 devices.
*\*\param  option_byte_data1:(The input parameters must be the following values)
*\*\                - 0x00 to 0xFF
*\*\return FLASH_STS: The returned value can be: 
*\*\        - FLASH_BUSY     FLASH is busy
*\*\        - FLASH_ERR_PG   FLASH programming error
*\*\        - FLASH_ERR_WRP  FLASH Write protected error
*\*\        - FLASH_EOP      FLASH End of Operation
*\*\        - FLASH_ERR_RDP2 FLASH is in read protection L2 status
*\*\        - FLASH_TIMEOUT  FLASH operation timeout
**/
FLASH_STS FLASH_ProgramOptionBytes_DATA1(uint32_t option_byte_data1)
{
    FLASH_STS status_value = FLASH_EOP;

    /* Get the actual read protection L2 Option Byte value */
    if (FLASH_GetReadOutProtectionL2STS() != RESET)
    {
        status_value = FLASH_ERR_RDP2;
    }
    else
    {
        /*No process*/
    }
    
    if(status_value == FLASH_ERR_RDP2)
    {
    
    }
    else
    {
        Option_Bytes_Unlock();
      
        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(ProgramTimeout);
    }

    if (status_value == FLASH_EOP)
    {
        /* Enable the Option Bytes Programming operation */
        FLASH->CTRL |= CTRL_Set_OPTPG;
        /* Restore the last read protection Option Byte value */
        OBT->Data1 = ((uint32_t)option_byte_data1);
        OBT->RESERVED8 = (uint32_t)FLASH_OB_MASK;
        
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(ProgramTimeout);
        if (status_value != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= CTRL_Reset_OPTPG;
        }
        else
        {
            /*No process*/
        }
    }
    else
    {
        /*No process*/
    }

    /* Return the Option Byte program status_value */
    return status_value;
}


/**
*\*\name   FLASH_EnWriteProtection
*\*\fun    Write protects the desired pages
*\*\param  FLASH_Pages :(The input parameters must be the following values)
*\*\        - FLASH_WRP_Pages0to7      Enable Write protection of page 0 to 7
*\*\        - FLASH_WRP_Pages8to15     Enable Write protection of page 8 to 15
*\*\        - FLASH_WRP_Pages16to23    Enable Write protection of page 16 to 23
*\*\        - FLASH_WRP_Pages24to31    Enable Write protection of page 24 to 31
*\*\        - FLASH_WRP_Pages32to39    Enable Write protection of page 32 to 39
*\*\        - FLASH_WRP_Pages40to47    Enable Write protection of page 40 to 47
*\*\        - FLASH_WRP_Pages48to55    Enable Write protection of page 48 to 55
*\*\        - FLASH_WRP_Pages56to63    Enable Write protection of page 56 to 63
*\*\        - FLASH_WRP_Pages64to71    Enable Write protection of page 64 to 71
*\*\        - FLASH_WRP_Pages72to79    Enable Write protection of page 72 to 79
*\*\        - FLASH_WRP_Pages80to87    Enable Write protection of page 80 to 87
*\*\        - FLASH_WRP_Pages88to95    Enable Write protection of page 88 to 95
*\*\        - FLASH_WRP_Pages96to103   Enable Write protection of page 96 to 103
*\*\        - FLASH_WRP_Pages104to111  Enable Write protection of page 104 to 111
*\*\        - FLASH_WRP_Pages112to119  Enable Write protection of page 112 to 119
*\*\        - FLASH_WRP_Pages120to127  Enable Write protection of page 120 to 127
*\*\        - FLASH_WRP_Pages128to135  Enable Write protection of page 128 to 135
*\*\        - FLASH_WRP_Pages136to143  Enable Write protection of page 136 to 143
*\*\        - FLASH_WRP_Pages144to151  Enable Write protection of page 144 to 151
*\*\        - FLASH_WRP_Pages152to159  Enable Write protection of page 152 to 159
*\*\        - FLASH_WRP_Pages160to167  Enable Write protection of page 160 to 167
*\*\        - FLASH_WRP_Pages168to175  Enable Write protection of page 168 to 175
*\*\        - FLASH_WRP_Pages176to183  Enable Write protection of page 176 to 183
*\*\        - FLASH_WRP_Pages184to191  Enable Write protection of page 184 to 191
*\*\        - FLASH_WRP_Pages192to199  Enable Write protection of page 192 to 199
*\*\        - FLASH_WRP_Pages200to207  Enable Write protection of page 200 to 207
*\*\        - FLASH_WRP_Pages208to215  Enable Write protection of page 208 to 215
*\*\        - FLASH_WRP_Pages216to223  Enable Write protection of page 216 to 223
*\*\        - FLASH_WRP_Pages224to231  Enable Write protection of page 224 to 231
*\*\        - FLASH_WRP_Pages232to239  Enable Write protection of page 232 to 239
*\*\        - FLASH_WRP_Pages240to247  Enable Write protection of page 240 to 247
*\*\        - FLASH_WRP_Pages248to255  Enable Write protection of page 248 to 255
*\*\        - FLASH_WRP_AllPages       Enable Write protection of all Pages
*\*\        - ~FLASH_WRP_AllPages      Disable Write protection of all Pages
*\*\return FLASH_STS : 
*\*\        - FLASH_BUSY     FLASH is busy
*\*\        - FLASH_ERR_PG   FLASH programming error
*\*\        - FLASH_ERR_WRP  FLASH Write protected error
*\*\        - FLASH_EOP      FLASH End of Operation
*\*\        - FLASH_ERR_RDP2 FLASH is in read protection L2 status
*\*\        - FLASH_TIMEOUT  FLASH operation timeout
**/
FLASH_STS FLASH_EnWriteProtection(uint32_t FLASH_Pages)
{
    uint16_t WRP0_Data, WRP1_Data, WRP2_Data, WRP3_Data;

    FLASH_STS status_value = FLASH_EOP;
    
    uint32_t FLASH_Pages_temp;

    /* Get the actual read protection L2 Option Byte value */
    if (FLASH_GetReadOutProtectionL2STS() != RESET)
    {
        status_value = FLASH_ERR_RDP2;
    }
    else
    {
        /*No process*/
    }
    
    FLASH_Pages_temp = (uint32_t)(~FLASH_Pages);
	WRP0_Data   = (uint16_t)( FLASH_Pages_temp & FLASH_WRP0_MSK);
	WRP1_Data   = (uint16_t)((FLASH_Pages_temp & FLASH_WRP1_MSK) >> FLASH_WRP_WRP1_OFFSET);
	WRP2_Data   = (uint16_t)((FLASH_Pages_temp & FLASH_WRP2_MSK) >> FLASH_WRP_WRP2_OFFSET);
	WRP3_Data   = (uint16_t)((FLASH_Pages_temp & FLASH_WRP3_MSK) >> FLASH_WRP_WRP3_OFFSET);
    
    if(status_value == FLASH_ERR_RDP2)
    {
    
    }
    else
    {
		/* Clears the FLASH's pending flags */
		FLASH_ClearFlag(FLASH_STS_CLRFLAG);
		/* Wait for last operation to be completed */
		status_value = FLASH_WaitForLastOpt(ProgramTimeout);
    }

    if (status_value == FLASH_EOP)
    {
        Option_Bytes_Unlock();
        FLASH->CTRL |= CTRL_Set_OPTPG;

        if (WRP0_Data != 0xFF)
        {
            OBT->WRP0 = (uint32_t)WRP0_Data;
            OBT->RESERVED9 = (uint32_t)FLASH_OB_MASK;

            /* Wait for last operation to be completed */
            status_value = FLASH_WaitForLastOpt(ProgramTimeout);
        }
        else
        {
            /*No process*/
        }
        
        
        if ((WRP1_Data != 0xFF) && (status_value == FLASH_EOP))
        {
            OBT->WRP1 = (uint32_t)WRP1_Data;
            OBT->RESERVED10 = (uint32_t)FLASH_OB_MASK;

            /* Wait for last operation to be completed */
            status_value = FLASH_WaitForLastOpt(ProgramTimeout);
        }
        else
        {
            /*No process*/
        }
        
        if ((WRP2_Data != 0xFF) && (status_value == FLASH_EOP))
        {
            OBT->WRP2 = (uint32_t)WRP2_Data;
            OBT->RESERVED11 = (uint32_t)FLASH_OB_MASK;

            /* Wait for last operation to be completed */
            status_value = FLASH_WaitForLastOpt(ProgramTimeout);
        }
        else
        {
            /*No process*/
        }
        
        if ((WRP3_Data != 0xFF) && (status_value == FLASH_EOP))
        {
            OBT->WRP3 = (uint32_t)WRP3_Data;
            OBT->RESERVED12 = (uint32_t)FLASH_OB_MASK;

            /* Wait for last operation to be completed */
            status_value = FLASH_WaitForLastOpt(ProgramTimeout);
        }
        else
        {
            /*No process*/
        }

        if (status_value != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= CTRL_Reset_OPTPG;
        }
        else
        {
            /*No process*/
        }
    }
    else
    {
        /*No process*/
    }
    /* Return the write protection operation Status */
    return status_value;
}

/**
*\*\name   FLASH_ProgramOptionBytes_RDP2
*\*\fun    Programs the Option Byte: RDP2.
*\*\param  option_byte_rpd2 :(The input parameters must be the following values)
*\*\            - FLASH_OB_RDP2_ENABLE   Enable read protection L2
*\*\            - FLASH_OB_RDP2_DISABLE  Disable read protection L2
*\*\return FLASH_STS : 
*\*\        - FLASH_BUSY     FLASH is busy
*\*\        - FLASH_ERR_PG   FLASH programming error
*\*\        - FLASH_ERR_WRP  FLASH Write protected error
*\*\        - FLASH_EOP      FLASH End of Operation
*\*\        - FLASH_ERR_RDP2 FLASH is in read protection L2 status
*\*\        - FLASH_TIMEOUT  FLASH operation timeout
**/
FLASH_STS FLASH_ProgramOptionBytes_RDP2(uint8_t option_byte_rpd2)
{
    FLASH_STS status_value = FLASH_EOP;

    /* Get the actual read protection L2 Option Byte value */
    if (FLASH_GetReadOutProtectionL2STS() != RESET)
    {
        status_value = FLASH_ERR_RDP2;
    }
    else
    {
        /*No process*/
    }
    
    if(status_value == FLASH_ERR_RDP2)
    {
    
    }
    else
    {
        Option_Bytes_Unlock();
      
        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(ProgramTimeout);
    }

    if (status_value == FLASH_EOP)
    {
        /* Enable the Option Bytes Programming operation */
        FLASH->CTRL |= CTRL_Set_OPTPG;
        /* Restore the last read protection Option Byte value */
        OBT->RDP2 = (uint32_t)option_byte_rpd2;
        OBT->RESERVED13 = (uint32_t)FLASH_OB_MASK;
        
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(ProgramTimeout);
        if (status_value != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= CTRL_Reset_OPTPG;
        }
        else
        {
            /*No process*/
        }
    }
    else
    {
        /*No process*/
    }

    /* Return the Option Byte program status_value */
    return status_value;
}

/**
*\*\name   FLASH_ReadOutProtectionL1
*\*\fun    Enables the read out protection.
*\*\param  Cmd:(The input parameters must be the following values)
*\*\            - ENABLE   Enable read protection L1
*\*\            - DISABLE  Disable read protection L1
*\*\return FLASH_STS : 
*\*\        - FLASH_BUSY     FLASH is busy
*\*\        - FLASH_ERR_PG   FLASH programming error
*\*\        - FLASH_ERR_WRP  FLASH Write protected error
*\*\        - FLASH_EOP      FLASH End of Operation
*\*\        - FLASH_ERR_RDP2 FLASH is in read protection L2 status
*\*\        - FLASH_TIMEOUT  FLASH operation timeout
**/
FLASH_STS FLASH_ReadOutProtectionL1(FunctionalState Cmd)
{
    uint32_t user1_iwdg,user1_stop,user1_PD,user1_nBOOT0,user1_nBOOT1,user1_nSWBOOT0,user1_BOOT0_CFG;
    uint32_t user2_LVRcnt,user2_LVR,user2_LVRreset,user2_LVRfilter;    
    uint32_t user3_temp,user4_temp,user5_temp,user6_temp;
    uint32_t data0_temp,data1_temp;
	uint32_t WP_temp;
    FLASH_STS status_value = FLASH_EOP;

    /* Get the actual read protection L2 Option Byte value */
    if (FLASH_GetReadOutProtectionL2STS() != RESET)
    {
        status_value = FLASH_ERR_RDP2;
    }
    else
    {
        /*No process*/
    }
	
    if(FLASH_GetOptionBytes_User1(FLASH_OB_IWDG_SOFTWARE) == SET)
    {
        user1_iwdg = FLASH_OB_IWDG_SOFTWARE;
    }
    else
    {
        user1_iwdg = FLASH_OB_IWDG_HARDWARE;
    }
    
    if(FLASH_GetOptionBytes_User1(FLASH_OB_STOP_NORST) == SET)
    {
        user1_stop = FLASH_OB_STOP_NORST;
    }
    else
    {
        user1_stop = FLASH_OB_STOP_RST;
    }
    
    if(FLASH_GetOptionBytes_User1(FLASH_OB_PD_NORST) == SET)
    {
        user1_PD = FLASH_OB_PD_NORST;
    }
    else
    {
        user1_PD = FLASH_OB_PD_RST;
    }
    
    if(FLASH_GetOptionBytes_User1(FLASH_OB_NBOOT0_SET) == SET)
    {
        user1_nBOOT0 = FLASH_OB_NBOOT0_SET;
    }
    else
    {
        user1_nBOOT0 = FLASH_OB_NBOOT0_CLR;
    }
    
    if(FLASH_GetOptionBytes_User1(FLASH_OB_NBOOT1_SET) == SET)
    {
        user1_nBOOT1 = FLASH_OB_NBOOT1_SET;
    }
    else
    {
        user1_nBOOT1 = FLASH_OB_NBOOT1_CLR;
    }
    
    if(FLASH_GetOptionBytes_User1(FLASH_OB_NSWBOOT0_SET) == SET)
    {
        user1_nSWBOOT0 = FLASH_OB_NSWBOOT0_SET;
    }
    else
    {
        user1_nSWBOOT0 = FLASH_OB_NSWBOOT0_CLR;
    }
    
    if(FLASH_GetOptionBytes_User1(FLASH_OB_BOOT0_CFG_HIGH) == SET)
    {
        user1_BOOT0_CFG = FLASH_OB_BOOT0_CFG_HIGH;
    }
    else
    {
        user1_BOOT0_CFG = FLASH_OB_BOOT0_CFG_LOW;
    }
    
    user2_LVRcnt = FLASH_GetOptionBytes_User2_LVRLS();
    if(FLASH_GetOptionBytes_User2_LVR(FLASH_OB_USER_LVR_DISABLE) == SET)
    {
        user2_LVR = FLASH_OB_USER_LVR_DISABLE;
    }
    else
    {
        user2_LVR = FLASH_OB_USER_LVR_ENABLE;
    }
    
    if(FLASH_GetOptionBytes_User2_LVR(FLASH_OB_USER_LVR_DISABLE) == SET)
    {
        user2_LVR = FLASH_OB_USER_LVR_DISABLE;
    }
    else
    {
        user2_LVR = FLASH_OB_USER_LVR_ENABLE;
    }
    
    if(FLASH_GetOptionBytes_User2_LVR(FLASH_OB_USER_LVRRST_DISABLE) == SET)
    {
        user2_LVRreset = FLASH_OB_USER_LVRRST_DISABLE;
    }
    else
    {
        user2_LVRreset = FLASH_OB_USER_LVRRST_ENABLE;
    }
    
    if(FLASH_GetOptionBytes_User2_LVR(FLASH_OB_USER_LVRFIL_DISABLE) == SET)
    {
        user2_LVRfilter = FLASH_OB_USER_LVRFIL_DISABLE;
    }
    else
    {
        user2_LVRfilter = FLASH_OB_USER_LVRFIL_ENABLE;
    }

    user3_temp = OBT->USER3;
    user4_temp = OBT->USER4;
    user5_temp = OBT->USER5;
    user6_temp = OBT->USER6;
    data0_temp = OBT->Data0;
    data1_temp = OBT->Data1;
    WP_temp    = FLASH_GetWriteProtectionSTS();
    
    if(status_value == FLASH_EOP)
    {
        
        FLASH_Unlock();
        status_value = FLASH_EraseOB();
    }
    else
    {
        /*No process*/
    }
    
    /* USER1 value write back*/
    if(status_value == FLASH_EOP)
    {
        status_value = FLASH_ProgramOptionBytes_USER1(user1_iwdg,user1_stop,user1_PD,user1_nBOOT0,\
												      user1_nBOOT1,user1_nSWBOOT0,user1_BOOT0_CFG);
    }
	else
	{
		/* no process*/
	}
	
	if(status_value == FLASH_EOP)
    {
        status_value = FLASH_ProgramOptionBytes_USER2(user2_LVRcnt,user2_LVR,user2_LVRreset,user2_LVRfilter);
    }
	else
	{
		/* no process*/
	}
    
    if(status_value == FLASH_EOP)
    {
        status_value = FLASH_ProgramOptionBytes_USER3(user3_temp);
    }
	else
	{
		/* no process*/
	}
    
    if(status_value == FLASH_EOP)
    {
        status_value = FLASH_ProgramOptionBytes_USER4(user4_temp);
    }
	else
	{
		/* no process*/
	}
	
    if(status_value == FLASH_EOP)
    {
        status_value = FLASH_ProgramOptionBytes_USER5(user5_temp);
    }
	else
	{
		/* no process*/
	}
    
    if(status_value == FLASH_EOP)
    {
        status_value = FLASH_ProgramOptionBytes_USER6(user6_temp);
    }
	else
	{
		/* no process*/
	}
    
    /* Programs DATA0~DATA1 */
    if(status_value == FLASH_EOP)
    {
        status_value = FLASH_ProgramOptionBytes_DATA0(data0_temp);
    }
	else
	{
		/* no process*/
	}
    
    if(status_value == FLASH_EOP)
    {
        status_value = FLASH_ProgramOptionBytes_DATA1(data1_temp);
    }
	else
	{
		/* no process*/
	}
    
    if(status_value == FLASH_EOP)
    {
        status_value = FLASH_EnWriteProtection(~WP_temp);
    }
	else
	{
		/* no process*/
	}
    
    if(status_value == FLASH_EOP)
    {
        if (Cmd != DISABLE)
        {
            /* Enables the read out protection L1 */
            status_value = FLASH_ProgramOptionBytes_RDP1(FLASH_OB_RDP1_ENABLE);
        }
        else
        {
            /* Disables the read out protection L1 */
            status_value = FLASH_ProgramOptionBytes_RDP1(FLASH_OB_RDP1_DISABLE);
        }    
    }
    else
	{
		/* no process*/
	}
  
    /* Return the protection operation status_value */
    return status_value;
}


/**
*\*\name   FLASH_ReadOutProtectionL2_ENABLE
*\*\fun    Enables the read out protection L2.
*\*\param  none
*\*\return FLASH_STS : 
*\*\        - FLASH_BUSY     FLASH is busy
*\*\        - FLASH_ERR_PG   FLASH programming error
*\*\        - FLASH_ERR_WRP  FLASH Write protected error
*\*\        - FLASH_EOP      FLASH End of Operation
*\*\        - FLASH_ERR_RDP2 FLASH is in read protection L2 status
*\*\        - FLASH_TIMEOUT  FLASH operation timeout
**/
FLASH_STS FLASH_ReadOutProtectionL2_ENABLE(void)
{
    uint32_t user1_iwdg,user1_stop,user1_PD,user1_nBOOT0,user1_nBOOT1,user1_nSWBOOT0,user1_BOOT0_CFG;
    uint32_t user2_LVRcnt,user2_LVR,user2_LVRreset,user2_LVRfilter;    
    uint32_t user3_temp,user4_temp,user5_temp,user6_temp;
    uint32_t data0_temp,data1_temp;
	uint32_t WP_temp;
    FLASH_STS status_value = FLASH_EOP;

    /* Get the actual read protection L2 Option Byte value */
    if (FLASH_GetReadOutProtectionL2STS() != RESET)
    {
        status_value = FLASH_ERR_RDP2;
    }
    else
    {
        /*No process*/
    }
	
    if(FLASH_GetOptionBytes_User1(FLASH_OB_IWDG_SOFTWARE) == SET)
    {
        user1_iwdg = FLASH_OB_IWDG_SOFTWARE;
    }
	else
	{
		user1_iwdg = FLASH_OB_IWDG_HARDWARE;
	}
	
	if(FLASH_GetOptionBytes_User1(FLASH_OB_STOP_NORST) == SET)
    {
        user1_stop = FLASH_OB_STOP_NORST;
    }
	else
	{
		user1_stop = FLASH_OB_STOP_RST;
	}
	
	if(FLASH_GetOptionBytes_User1(FLASH_OB_PD_NORST) == SET)
    {
        user1_PD = FLASH_OB_PD_NORST;
    }
	else
	{
		user1_PD = FLASH_OB_PD_RST;
	}
	
	if(FLASH_GetOptionBytes_User1(FLASH_OB_NBOOT0_SET) == SET)
    {
        user1_nBOOT0 = FLASH_OB_NBOOT0_SET;
    }
	else
	{
		user1_nBOOT0 = FLASH_OB_NBOOT0_CLR;
	}
	
	if(FLASH_GetOptionBytes_User1(FLASH_OB_NBOOT1_SET) == SET)
    {
        user1_nBOOT1 = FLASH_OB_NBOOT1_SET;
    }
	else
	{
		user1_nBOOT1 = FLASH_OB_NBOOT1_CLR;
	}
	
	if(FLASH_GetOptionBytes_User1(FLASH_OB_NSWBOOT0_SET) == SET)
    {
        user1_nSWBOOT0 = FLASH_OB_NSWBOOT0_SET;
    }
	else
	{
		user1_nSWBOOT0 = FLASH_OB_NSWBOOT0_CLR;
	}
	
	if(FLASH_GetOptionBytes_User1(FLASH_OB_BOOT0_CFG_HIGH) == SET)
    {
        user1_BOOT0_CFG = FLASH_OB_BOOT0_CFG_HIGH;
    }
	else
	{
		user1_BOOT0_CFG = FLASH_OB_BOOT0_CFG_LOW;
	}
	
	user2_LVRcnt = FLASH_GetOptionBytes_User2_LVRLS();
	if(FLASH_GetOptionBytes_User2_LVR(FLASH_OB_USER_LVR_DISABLE) == SET)
    {
        user2_LVR = FLASH_OB_USER_LVR_DISABLE;
    }
	else
	{
		user2_LVR = FLASH_OB_USER_LVR_ENABLE;
	}
	
	if(FLASH_GetOptionBytes_User2_LVR(FLASH_OB_USER_LVR_DISABLE) == SET)
    {
        user2_LVR = FLASH_OB_USER_LVR_DISABLE;
    }
	else
	{
		user2_LVR = FLASH_OB_USER_LVR_ENABLE;
	}
	
	if(FLASH_GetOptionBytes_User2_LVR(FLASH_OB_USER_LVRRST_DISABLE) == SET)
    {
        user2_LVRreset = FLASH_OB_USER_LVRRST_DISABLE;
    }
	else
	{
		user2_LVRreset = FLASH_OB_USER_LVRRST_ENABLE;
	}
	
	if(FLASH_GetOptionBytes_User2_LVR(FLASH_OB_USER_LVRFIL_DISABLE) == SET)
    {
        user2_LVRfilter = FLASH_OB_USER_LVRFIL_DISABLE;
    }
	else
	{
		user2_LVRfilter = FLASH_OB_USER_LVRFIL_ENABLE;
	}

    user3_temp = OBT->USER3;
    user4_temp = OBT->USER4;
    user5_temp = OBT->USER5;
    user6_temp = OBT->USER6;
    data0_temp = OBT->Data0;
    data1_temp = OBT->Data1;
	WP_temp    = FLASH_GetWriteProtectionSTS();
    
    if(status_value == FLASH_EOP)
    {
        FLASH_Unlock();
        status_value = FLASH_EraseOB();
    }
    else
    {
        /* no process */
    }
    
    if(FLASH_GetReadOutProtectionSTS() != RESET)
    {
        /* Enables the read out protection L1 */
        status_value = FLASH_ProgramOptionBytes_RDP1(FLASH_OB_RDP1_ENABLE);
    }
    else
    {
        /* Disables the read out protection L1 */
        status_value = FLASH_ProgramOptionBytes_RDP1(FLASH_OB_RDP1_DISABLE);
    }
    
    if(status_value == FLASH_EOP)
    {
        status_value = FLASH_ProgramOptionBytes_USER1(user1_iwdg,user1_stop,user1_PD,user1_nBOOT0,\
												      user1_nBOOT1,user1_nSWBOOT0,user1_BOOT0_CFG);
    }
	else
	{
		/* no process*/
	}
	
	if(status_value == FLASH_EOP)
    {
        status_value = FLASH_ProgramOptionBytes_USER2(user2_LVRcnt,user2_LVR,user2_LVRreset,user2_LVRfilter);
    }
	else
	{
		/* no process*/
	}
    
    if(status_value == FLASH_EOP)
    {
        status_value = FLASH_ProgramOptionBytes_USER3(user3_temp);
    }
	else
	{
		/* no process*/
	}
    
    if(status_value == FLASH_EOP)
    {
        status_value = FLASH_ProgramOptionBytes_USER4(user4_temp);
    }
	else
	{
		/* no process*/
	}
	
    if(status_value == FLASH_EOP)
    {
        status_value = FLASH_ProgramOptionBytes_USER5(user5_temp);
    }
	else
	{
		/* no process*/
	}
    
    if(status_value == FLASH_EOP)
    {
        status_value = FLASH_ProgramOptionBytes_USER6(user6_temp);
    }
	else
	{
		/* no process*/
	}
    
    /* Programs DATA0~DATA1 */
    if(status_value == FLASH_EOP)
    {
        status_value = FLASH_ProgramOptionBytes_DATA0(data0_temp);
    }
	else
	{
		/* no process*/
	}
    
    if(status_value == FLASH_EOP)
    {
        status_value = FLASH_ProgramOptionBytes_DATA1(data1_temp);
    }
	else
	{
		/* no process*/
	}
    
    if(status_value == FLASH_EOP)
    {
        status_value = FLASH_EnWriteProtection(~WP_temp);
    }
	else
	{
		/* no process*/
	}
    
    if(status_value == FLASH_EOP)
    {
        status_value = FLASH_ProgramOptionBytes_RDP2(FLASH_OB_RDP2_ENABLE);
    }
	else
	{
		/* no process*/
	}
    
    /* Return the protection operation status_value */
    return status_value;
}


/**
*\*\name   FLASH_GetOptionBytes_User1
*\*\fun    Returns the FLASH User Option Bytes values.
*\*\param  option_byte_bit: (The input parameters must be the following values)
*\*\            - FLASH_OB_IWDG_SOFTWARE       WDG configuration bit
*\*\            - FLASH_OB_STOP_NORST          STOP configuration bit
*\*\            - FLASH_OB_PD_NORST            PD configuration bit
*\*\            - FLASH_OB_NBOOT0_SET          nBOOT0 configuration bit
*\*\            - FLASH_OB_NBOOT1_SET          nBOOT1 configuration bit
*\*\            - FLASH_OB_NSWBOOT0_SET        nSWBOOT0 configuration bit
*\*\            - FLASH_OB_BOOT0_CFG_HIGH      BOOT0_CFG configuration bit
*\*\return FlagStatus :
*\*\            - SET      Enter this mode without resetting
*\*\            - RESET    Enter this mode reset
**/
FlagStatus FLASH_GetOptionBytes_User1(uint32_t option_byte_bit)
{
    FlagStatus bit_status;
    if(((FLASH->OB >> FLASH_OB_TO_USER_OFFSET) & option_byte_bit) != (uint32_t)RESET)
    {
        bit_status = SET;
    }
    else
    {
        bit_status = RESET;
    }
    return bit_status;
}

/**
*\*\name   FLASH_GetOptionBytes_User2_LVRLS
*\*\fun    Returns the FLASH Option Bytes LVRLS values.
*\*\param  none
*\*\return LVRLS:
*\*\            - 0x00 to 0x0F.
**/
uint32_t FLASH_GetOptionBytes_User2_LVRLS(void)
{
    /* Return the Option Byte User2 LVRLS */
    return (uint32_t)(FLASH->USER & FLASH_USER_LVRLS_MSK);
}


/**
*\*\name   FLASH_GetOptionBytes_User2_LVR
*\*\fun    Returns the FLASH Option Bytes User2 values.
*\*\param  option_byte_bit:(The input parameters must be the following values)
*\*\            - FLASH_OB_USER_LVR_DISABLE
*\*\            - FLASH_OB_USER_LVRRST_DISABLE
*\*\            - FLASH_OB_USER_LVRFIL_DISABLE
*\*\return FlagStatus :
*\*\            - SET
*\*\            - RESET
**/
FlagStatus FLASH_GetOptionBytes_User2_LVR(uint32_t option_byte_bit)
{
    FlagStatus bit_status;
    if((FLASH->USER & option_byte_bit) != (uint32_t)RESET)
    {
        bit_status = SET;
    }
    else
    {
        bit_status = RESET;
    }
    return bit_status;
}


/**
*\*\name   FLASH_GetOptionBytes_User3
*\*\fun    Returns the FLASH Option Bytes LVRCNT values.
*\*\param  none
*\*\return LVRCNT:
*\*\            - 0x00 to 0xFF.
**/
uint32_t FLASH_GetOptionBytes_User3(void)
{
    /* Return the User Option Byte3 */
    return (uint32_t)((FLASH->USER & FLASH_USER_LVRCNT_MSK) >> FLASH_USER3_OFFSET);
}


/**
*\*\name   FLASH_GetOptionBytes_User4
*\*\fun    Returns the FLASH Option Bytes POR_DELAY values.
*\*\param  none
*\*\return POR_DELAY:
*\*\            - 0x00 to 0xFF.
**/
uint32_t FLASH_GetOptionBytes_User4(void)
{
    /* Return the Option Byte User4 */
    return (uint32_t)((FLASH->USER & FLASH_USER_POR_DELAY_MSK) >> FLASH_USER4_OFFSET);
}

/**
*\*\name   FLASH_GetStartAddress
*\*\fun    Returns the FLASH start address Option Bytes Register value.
*\*\param  none
*\*\return option_byte_user5:
*\*\                - 0x00 to 0xFF  FLASH boot start address, 0xff corresponds to 0x8000000, 0x00 corresponds to:0x801FE00, and increment 0x200
**/
uint32_t FLASH_GetStartAddress(void)
{
    /* Return the Option Byte User5 */
    return (uint32_t)(FLASH->START_ADD & FLASH_USER_START_ADD_MSK);
}

/**
*\*\name   FLASH_GetBOOTUartPIN
*\*\fun    Returns the serial communication pins for boot code.
*\*\param  none
*\*\return option_byte_user6:
*\*\                - BOOT_UartPIN_PA9PA10    BOOT uart pins are PA9 and PA10
*\*\                - BOOT_UartPIN_PB10PB11   BOOT uart pins are PB10 and PB11
*\*\                - BOOT_UartPIN_PD10PD11   BOOT uart pins are PD10 and PD11
*\*\                - BOOT_UartPIN_PA2PA3     BOOT uart pins are PA2 and PA3
**/
uint32_t FLASH_GetBOOTUartPIN(void)
{
    /* Return the User Option Byte6 */
    return (uint32_t)((FLASH->OB & FLASH_OB_BOOTSEL_MASK) >> FLASH_OB_BOOTSEL_OFFSET);
}


/**
*\*\name   FLASH_GetOptionBytes_Data0
*\*\fun    Returns the FLASH User Option Bytes values.
*\*\param  none
*\*\return data0:
*\*\            - 0x00 to 0xFF.
**/
uint32_t FLASH_GetOptionBytes_Data0(void)
{
    /* Return the User Option Byte2 */
    return (uint32_t)((FLASH->OB & FLASH_OB_DATA0_MASK) >> FLASH_OB_DATA0_OFFSET);
}

/**
*\*\name   FLASH_GetOptionBytes_Data1
*\*\fun    Returns the FLASH User Option Bytes values.
*\*\param  none
*\*\return data1:
*\*\            - 0x00 to 0xFF.
**/
uint32_t FLASH_GetOptionBytes_Data1(void)
{
    /* Return the User Option Byte2 */
    return (uint32_t)((FLASH->OB & FLASH_OB_DATA1_MASK) >> FLASH_OB_DATA1_OFFSET);
}


/**
*\*\name   FLASH_GetReadOutProtectionSTS
*\*\fun    Checks whether the FLASH Read Out Protection L1 status_value is set or not.
*\*\param  none
*\*\return FlagStatus :
*\*\        - SET    Read protection L1 enable
*\*\        - RESET  Read protection L1 disable
**/
FlagStatus FLASH_GetReadOutProtectionSTS(void)
{
    FlagStatus bit_status;
    if ((FLASH->OB & FLASH_RDPRTL1_MSK) != (uint32_t)RESET)
    {
        bit_status = SET;
    }
    else
    {
        bit_status = RESET;
    }
    return bit_status;
}


/**
*\*\name   FLASH_GetReadOutProtectionL2STS
*\*\fun    Checks whether the FLASH Read Out Protection L2 status_value is set or not.
*\*\param  none
*\*\return FlagStatus :
*\*\        - SET    Read protection L2 enable
*\*\        - RESET  Read protection L2 disable
**/
FlagStatus FLASH_GetReadOutProtectionL2STS(void)
{
    FlagStatus readoutstatus;
    if ((FLASH->OB & FLASH_RDPRTL2_MSK) != (uint32_t)RESET)
    {
        readoutstatus = SET;
    }
    else
    {
        readoutstatus = RESET;
    }
    return readoutstatus;
}

/**
*\*\name   FLASH_GetWriteProtectionSTS
*\*\fun    Returns the FLASH Write Protection Option Bytes Register value.
*\*\param  none
*\*\return The FLASH Write Protection  Option Bytes Register value :
*\*\            - Bit31 - Bit0 write-protects pages (248~255) - page (0~7) 
**/
uint32_t FLASH_GetWriteProtectionSTS(void)
{
    /* Return the Flash write protection Register value */
    return (uint32_t)(FLASH->WRP);
}


/**
*\*\name   FLASH_GetPrefetchBufSTS
*\*\fun    Checks whether the FLASH Prefetch Buffer status_value is set or not.
*\*\param  none
*\*\return FlagStatus :
*\*\        - SET    Flash prefetch buffer enable
*\*\        - RESET  Flash prefetch buffer disable
**/
FlagStatus FLASH_GetPrefetchBufSTS(void)
{
    FlagStatus bitstatus;

    if ((FLASH->AC & FLASH_PRFTBS_MSK) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    /* Return the new state of FLASH Prefetch Buffer Status (SET or RESET) */
    return bitstatus;
}



/**
*\*\name   FLASH_INTConfig
*\*\fun    Enables the specified FLASH interrupts.
*\*\note   This function can be used for N32A052 devices.
*\*\param  Cmd:(The input parameters must be the following values)
*\*\            - ENABLE
*\*\            - DISABLE 
*\*\param  FLASH_INT :
*\*\            - FLASH_INT_ERR      FLASH Error Interrupt
*\*\            - FLASH_INT_EOP      FLASH end of operation Interrupt
*\*\            - FLASH_INT_ECC      ECC Error Interrupt
*\*\return none
**/
void FLASH_INTConfig(uint32_t FLASH_INT, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the interrupt sources */
        FLASH->CTRL |= FLASH_INT;
    }
    else
    {
        /* Disable the interrupt sources */
        FLASH->CTRL &= ~(uint32_t)FLASH_INT;
    }
}


/**
*\*\name   FLASH_GetFlagSTS
*\*\fun    Checks whether the specified FLASH flag is set or not.
*\*\note   This function can be used for N32A052 devices.
*\*\param  FLASH_FLAG :(The input parameters must be the following values)
*\*\        - FLASH_FLAG_BUSY      FLASH Busy flag
*\*\        - FLASH_FLAG_PGERR     FLASH Program error flag
*\*\        - FLASH_FLAG_WRPERR    FLASH Write protected error flag
*\*\        - FLASH_FLAG_EOP       FLASH End of Operation flag
*\*\        - FLASH_FLAG_ECC       FLASH ECC error flag
*\*\return FlagStatus :
*\*\        - SET      Flag status is set
*\*\        - RESET    Flag status is reset
**/
FlagStatus FLASH_GetFlagSTS(uint32_t FLASH_FLAG)
{
    FlagStatus bit_status;
    if ((FLASH->STS & FLASH_FLAG) != (uint32_t)RESET)
    {
        bit_status = SET;
    }
    else
    {
        bit_status = RESET;
    }
    return bit_status;
}


/**
*\*\name   FLASH_GetOBFlagSTS
*\*\fun    Checks whether the specified FLASH flag is set or not.
*\*\param  FLASH_FLAG :(The input parameters must be the following values)
*\*\        - FLASH_FLAG_OBERR FLASH Option Byte error flag
*\*\return FlagStatus :
*\*\        - SET      Flag status is set
*\*\        - RESET    Flag status is reset
**/
FlagStatus FLASH_GetOBFlagSTS(uint32_t FLASH_FLAG)
{
    FlagStatus bit_status;
    if ((FLASH->OB & FLASH_FLAG) != (uint32_t)RESET)
    {
        bit_status = SET;
    }
    else
    {
        bit_status = RESET;
    }
    return bit_status;
}


/**
*\*\name   FLASH_ClearFlag
*\*\fun    Clears the FLASH's status flags.
*\*\note   This function can be used for N32A052 devices.
*\*\param  FLASH_FLAG :(The input parameters must be the following values)
*\*\        - FLASH_FLAG_PGERR     FLASH Program error flag
*\*\        - FLASH_FLAG_WRPERR    FLASH Write protected error flag
*\*\        - FLASH_FLAG_EOP       FLASH End of Operation flag
*\*\        - FLASH_FLAG_ECC       FLASH ECC error flag
*\*\return none
**/
void FLASH_ClearFlag(uint32_t FLASH_FLAG)
{
    /* Clear the flags */
    FLASH->STS = FLASH_FLAG;
}



/**
*\*\name   FLASH_GetSTS
*\*\fun    Returns the FLASH_STS.
*\*\note   This function can be used for N32A052 devices.
*\*\param  none
*\*\return FLASH_STS :
*\*\        - FLASH_BUSY     FLASH is busy
*\*\        - FLASH_ERR_PG   FLASH programming error
*\*\        - FLASH_ERR_WRP  FLASH Write protected error
*\*\        - FLASH_EOP      FLASH End of Operation
**/
FLASH_STS FLASH_GetSTS(void)
{
    FLASH_STS flashstatus;

    if ((FLASH->STS & FLASH_FLAG_BUSY) == FLASH_FLAG_BUSY)
    {
        flashstatus = FLASH_BUSY;
    }
    else
    {
        if ((FLASH->STS & FLASH_FLAG_PGERR) != 0)
        {
            flashstatus = FLASH_ERR_PG;
        }
        else
        {
            if ((FLASH->STS & FLASH_FLAG_WRPERR) != 0)
            {
                flashstatus = FLASH_ERR_WRP;
            }
            else
            {
                flashstatus = FLASH_EOP;
            }
        }
    }

    /* Return the Flash Status */
    return flashstatus;
}


/**
*\*\name   FLASH_WaitForLastOpt
*\*\fun    Waits for a Flash operation to complete or a timeout to occur.
*\*\note   This function can be used for N32A052 devices.
*\*\param  timeout :(The input parameters must be the following values)
*\*\            - EraseTimeout
*\*\            - ProgramTimeout
*\*\return FLASH_STS: The returned value can be: 
*\*\            - FLASH_BUSY     FLASH is busy
*\*\            - FLASH_ERR_PG   FLASH programming error
*\*\            - FLASH_ERR_WRP  FLASH Write protected error
*\*\            - FLASH_EOP      FLASH End of Operation
*\*\            - FLASH_TIMEOUT  FLASH operation timeout
**/
FLASH_STS FLASH_WaitForLastOpt(uint32_t Timeout)
{
    FLASH_STS status;
    uint32_t Timeout_temp;
    Timeout_temp = Timeout;
 
    /* Check for the Flash Status */
    status = FLASH_GetSTS();
    /* Wait for a Flash operation to complete or a TIMEOUT to occur */
    while ((status == FLASH_BUSY) && (Timeout_temp != 0x00))
    {
        status = FLASH_GetSTS();
        Timeout_temp--;
    }
    if (Timeout_temp == 0x00)
    {
        status = FLASH_TIMEOUT;
    }
    /* Return the operation status */
    return status;
}


/**
*\*\name   FLASH_SetVTORAddress
*\*\fun    Set interrupt vector offset address.
*\*\param  VTOR_address :(The input parameters must be the following values)
*\*\            - 0x00000000~0x7FFFFFFF
*\*\param  VTOR_cmd :(The input parameters must be the following values)
*\*\            - FLASH_VTOR_ENABLE
*\*\            - FLASH_VTOR_DISABLE
*\*\return none
**/
void FLASH_SetVTORAddress(uint32_t VTOR_address,uint32_t VTOR_cmd)
{
    /* Set VTOR address */
    FLASH->VTOR = (VTOR_cmd | VTOR_address);
}



