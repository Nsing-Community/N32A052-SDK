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
*\*\file n32a052_i2c.c
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/
#include "n32a052_rcc.h"
#include "n32a052_i2c.h"


/** I2C Private Defines **/

/** I2C Driving Functions Declaration **/

/**
*\*\name    I2C_DeInit.
*\*\fun     Reset the I2Cx registers.
*\*\param   I2Cx (The input parameters must be the following values):
*\*\          - I2C1
*\*\          - I2C2
*\*\return  none
**/
void I2C_DeInit(I2C_Module* I2Cx)
{
  
    if (I2Cx == I2C1)
    {
        /* I2C1 Reset */
        RCC_EnableAPB1PeriphReset(RCC_APB1_PERIPH_I2C1);
    }
    else
    {
        /* I2C2 Reset */
        RCC_EnableAPB1PeriphReset(RCC_APB1_PERIPH_I2C2);
    }
}


/**
*\*\name    I2C_Clock_Speed_Config.
*\*\fun     Initializes the clock speed.
*\*\param   I2Cx (The input parameters must be the following values):
*\*\          - I2C1
*\*\          - I2C2
*\*\param   clk_speed (The input parameters must be the following values)
*\*\          - between 1 to 1000000
*\*\param   duty_cycle (The input parameters must be the following values):
*\*\          - I2C_FMDUTYCYCLE_16_9
*\*\          - I2C_FMDUTYCYCLE_2
*\*\return  The  parameter only be set when I2C is turned off (EN = 0)
**/
static void I2C_Clock_Speed_Config(I2C_Module* I2Cx, uint32_t clk_speed, uint16_t duty_cycle)
{
    uint16_t temp_value, freq_value, speed_value, trise_value;
    uint32_t ctrl_value, pclk_value, clk_speedtmp;
    RCC_ClocksType rcc_clocks;

    /* Get APB1 frequency value */
    RCC_GetClocksFreqValue(&rcc_clocks);

    /** I2Cx CTRL2 config **/
    /* Get the I2Cx CTRL2 value */
    ctrl_value = I2Cx->CTRL2;
    /* Clear frequency FREQ[6:0] bits */
    ctrl_value &= I2C_CLKFREQ_RESET;
    /* Get APB1 frequency value */
    pclk_value = rcc_clocks.Pclk1Freq;  
    /* Set frequency bits depending on APB1 pclk value */
    freq_value = (uint16_t)(pclk_value / 1000000);
	if (freq_value > APB1_FREQ_MAX_VALUE) 
    {
        freq_value = APB1_FREQ_MAX_VALUE;
    }
	/* Write to I2Cx CTRL2 */
    ctrl_value |= freq_value;
    I2Cx->CTRL2 = ctrl_value;
   
    /** I2Cx CLKCTRL and TMRISE config **/
    /* Disable the selected I2C peripheral to configure TMRISE */
    I2Cx->CTRL1 &= I2C_EN_RESET;  
    /* Get the I2Cx TMRISE value */
    trise_value = I2Cx->TMRISE;    
    /* Clear TMRISE[5:0] bits */
    trise_value &= (~I2C_TMRISE_MASK);
    /* Reset temp_value */
    /* Clear CLKCTRL:FSMODE, DUTY and CLKCTRL[11:0] bits */
    temp_value = 0;
    
    /*If the ClkSpeed does not exceed 100KHz, mode(FSMODE[bit15]) is standard, duty is fixed at 1:1,ignore DUTY[bit14] */
    /* Configure speed in SM(standard mode) */
    if (clk_speed <= CLK_SPEED_100K)
    {  
        /* Ensure clk_speed is not zero to avoid division by zero */
        if (clk_speed == 0)
        {
            /* Default 5khz */
            clk_speedtmp = 5000; 
        }
        else
        {
            clk_speedtmp = clk_speed; 
        }
        /* Standard mode speed calculate: Tlow/Thigh = 1 */
        speed_value = (uint16_t)(pclk_value / (clk_speedtmp * 2)); 
        /* Test if CLKCTRL value is under 0x4*/
        if (speed_value < SM_CLKCTRL_LOW_LIMIT)
        {
            /* Set minimum allowed value */
            speed_value = SM_CLKCTRL_LOW_LIMIT;
        }
        /* Set speed value for standard mode */
        temp_value |= speed_value;   
        /* Set Maximum Rise Time for standard mode */
        trise_value |= ((freq_value + 1) & I2C_TMRISE_MASK);         
    }
    /*If ClkSpeed exceeds 100KHz, mode(FSMODE[bit15]) is fast, DUTY[bit14] can be configured as 2:1 or 16:9 */
    /* Configure speed in FM(fast mode) */
    else 
    {
        if (duty_cycle != I2C_FMDUTYCYCLE_16_9)
        {
            /* Fast mode speed calculate: Tlow/Thigh = 2 */
            speed_value = (uint16_t)(pclk_value / (clk_speed * 3));
        }
        else /*duty_cycle == I2C_FMDUTYCYCLE_16_9*/
        {
            /* Fast mode speed calculate: Tlow/Thigh = 16/9 */
            speed_value = (uint16_t)(pclk_value / (clk_speed * 25));
            /* Set DUTY bit */
            speed_value |= I2C_FMDUTYCYCLE_16_9;
        }

        /* Test if CLKCTRL value is under 0x1*/
        if ((speed_value & I2C_CLKCTRL_SET) < FM_CLKCTRL_LOW_LIMIT)
        {
            /* Set minimum allowed value */
            speed_value |= (uint16_t)FM_CLKCTRL_LOW_LIMIT;
        }
        /* Set speed value and set F/S bit for fast mode */
        temp_value |= (uint16_t)(speed_value | I2C_FSMODE_SET);
        
        /* Set Maximum Rise Time for fast mode */
        /* if APB1 frequency is 32MHz,period = 1/32*1000ns,so trise_value = period/TRISE+1=32*TRISE/1000+1,See the manual for details*/
        if(clk_speed <= CLK_SPEED_400K)   /* 100KHz~400KHz */ 
        {
            trise_value |= (((uint16_t)(((freq_value * (uint16_t)FM_TRISE_400K) / (uint16_t)1000) + (uint16_t)1)) & I2C_TMRISE_MASK);
        }
        else  /* 400KHz~1MHz */ 
        {
            trise_value |= (((uint16_t)(((freq_value * (uint16_t)FM_TRISE_1M) / (uint16_t)1000) + (uint16_t)1)) & I2C_TMRISE_MASK);
        }
    }
    /* Write to I2Cx TMRISE */
    I2Cx->TMRISE = trise_value;
    /* Write to I2Cx CLKCTRL */
    I2Cx->CLKCTRL = temp_value; 
    /* Enable the selected I2C peripheral */
    I2Cx->CTRL1 |= I2C_EN_SET;
}

/**
*\*\name    I2C_Bus_Mode_Config.
*\*\fun     Initializes the bus mode.
*\*\param   I2Cx (The input parameters must be the following values):
*\*\          - I2C1
*\*\          - I2C2
*\*\param   mode (The input parameters must be the following values)
*\*\          - I2C_BUSMODE_I2C
*\*\          - I2C_BUSMODE_SMBDEVICE
*\*\          - I2C_BUSMODE_SMBHOST
*\*\return  none
**/
static void I2C_Bus_Mode_Config(I2C_Module* I2Cx, uint32_t mode)
{
    uint32_t temp_value;

    /* Get the I2Cx CTRL1 value */
    temp_value = I2Cx->CTRL1;
    /* Clear SMBTYPE and SMBUS bits */
    temp_value &= I2C_BUSMODE_CLR_MASK;
    /* Set SMBTYPE and SMBUS bits according to mode value */
    temp_value |= mode;
    /* Set I2Cx CTRL1 */
    I2Cx->CTRL1 = temp_value;
}

/**
*\*\name    I2C_Acknowledgement_Config.
*\*\fun     Initializes the acknowledgement.
*\*\param   I2Cx (The input parameters must be the following values) :
*\*\          - I2C1
*\*\          - I2C2
*\*\param   ack (The input parameters must be the following values)
*\*\          - I2C_ACKEN
*\*\          - I2C_ACKDIS
*\*\return  none
**/
static void I2C_Acknowledgement_Config(I2C_Module* I2Cx, uint32_t ack)
{
    uint32_t temp_value;

    /* Get the I2Cx CTRL1 value */
    temp_value = I2Cx->CTRL1;
    /* Clear ACKEN bits */
    temp_value &= I2C_ACKEN_CLR_MASK;
    /* Set ACKEN bits according to ack value */
    temp_value |= ack;
    /* Set I2Cx CTRL1 */
    I2Cx->CTRL1 = temp_value;
}

/**
*\*\name    I2C_Address_Mode_Config.
*\*\fun     Initializes addressing mode.
*\*\param   I2Cx (The input parameters must be the following values):
*\*\          - I2C1
*\*\          - I2C2
*\*\param   mode(The input parameters must be the following values)
*\*\          - I2C_ADDR_MODE_7BIT
*\*\          - I2C_ADDR_MODE_10BIT
*\*\return  none
**/
static void I2C_Address_Mode_Config(I2C_Module* I2Cx, uint16_t mode)
{
    uint16_t temp_value;

    /* Get the I2Cx OADDR1 value */
    temp_value = I2Cx->OADDR1;
    /* Clear ADDRMODE bits */
    temp_value &= I2C_ADDRMODE_CLR_MASK;
    /* Set ACKEN bits according to mode value, and set bit14 */
    temp_value |= mode;
    /* Set I2Cx OADDR1 */
    I2Cx->OADDR1 = temp_value;
}

/**
*\*\name    I2C_Own_Address1_Config.
*\*\fun     Initializes the own address.
*\*\param   I2Cx (The input parameters must be the following values):
*\*\          - I2C1
*\*\          - I2C2
*\*\param   addr1 (The input parameters must be the following values)  
*\*\          - 0 to 0xFF
*\*\return  none
**/
static void I2C_Own_Address1_Config(I2C_Module* I2Cx, uint16_t addr1)
{
    uint16_t temp_value;

    /* Get the I2Cx OADDR1 value */
    temp_value = I2Cx->OADDR1;
    /* Clear ADDRMODE bits */
    temp_value &= I2C_OADDR_CLR_MASK;
    /* Set ACKEN bits according to mode value */
    temp_value |= addr1;
    /* Set I2Cx OADDR1 */
    I2Cx->OADDR1 = temp_value;

}

/**
*\*\name    I2C_Init.
*\*\fun     Initializes the I2Cx peripheral according to the specified
*\*\        parameters in the I2C_InitParam
*\*\param   I2Cx (The input parameters must be the following values):
*\*\          - I2C1
*\*\          - I2C2
*\*\param   I2C_InitParam (The input parameters must be the following values):
*\*\          - ClkSpeed(common speed:100000(100KHz) - 400000(400KHz) - 1000000(1MHz)):
*\*\            - between 1 to 1000000 
*\*\          - BusMode:
*\*\            - I2C_BUSMODE_I2C
*\*\            - I2C_BUSMODE_SMBDEVICE
*\*\            - I2C_BUSMODE_SMBHOST
*\*\          - FmDutyCycle(If the ClkSpeed does not exceed 100KHz,duty is fixed at 1:1,
*\*\                      otherwise it can be configured as 2:1 or 16:9):
*\*\            - I2C_FMDUTYCYCLE_16_9
*\*\            - I2C_FMDUTYCYCLE_2
*\*\          - OwnAddr1:
*\*\            - between 0 to 0xFF 
*\*\          - AckEnable:
*\*\            - I2C_ACKEN
*\*\            - I2C_ACKDIS
*\*\          - AddrMode:
*\*\            - I2C_ADDR_MODE_7BIT
*\*\            - I2C_ADDR_MODE_10BIT
*\*\return  none
**/
void I2C_Init(I2C_Module* I2Cx, I2C_InitType* I2C_InitParam)
{
    I2C_Clock_Speed_Config(I2Cx, I2C_InitParam->ClkSpeed, I2C_InitParam->FmDutyCycle);
    I2C_Bus_Mode_Config(I2Cx, I2C_InitParam->BusMode);
    I2C_Acknowledgement_Config(I2Cx, I2C_InitParam->AckEnable);
    I2C_Address_Mode_Config(I2Cx, I2C_InitParam->AddrMode);
    I2C_Own_Address1_Config(I2Cx, I2C_InitParam->OwnAddr1);
}

/**
*\*\name    I2C_Initializes_Structure.
*\*\fun     Fills each I2C_InitStruct member with its default value.
*\*\param   (The input parameters must be the following values):
*\*\          - ClkSpeed
*\*\          - BusMode
*\*\          - FmDutyCycle
*\*\          - OwnAddr1
*\*\          - AckEnable
*\*\          - AddrMode
*\*\return  none
**/
void I2C_InitStruct(I2C_InitType* I2C_StructInit)
{
    /*Reset I2C init structure parameters values */
    /* initialize the ClkSpeed member */
    I2C_StructInit->ClkSpeed    = 5000;
    /* Initialize the FmDutyCycle member */
    I2C_StructInit->FmDutyCycle = I2C_FMDUTYCYCLE_2;
    /* Initialize the BusMode member */
    I2C_StructInit->BusMode     = I2C_BUSMODE_I2C;
    /* Initialize the AckEnable member */
    I2C_StructInit->AckEnable   = I2C_ACKDIS;
    /* Initialize the AddrMode member */
    I2C_StructInit->AddrMode    = I2C_ADDR_MODE_7BIT;
    /* Initialize the OwnAddr1 member */
    I2C_StructInit->OwnAddr1    = 0;
}

/**
*\*\name    I2C_Enable.
*\*\fun     Enables or disables the specified I2C peripheral.
*\*\param   I2Cx (The input parameters must be the following values):
*\*\          - I2C1
*\*\          - I2C2
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE  
*\*\return  none
**/
void I2C_Enable(I2C_Module* I2Cx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected I2C peripheral */
        I2Cx->CTRL1 |= I2C_EN_SET;  
    }
    else
    {
        /* Disable the selected I2C peripheral */
        I2Cx->CTRL1 &= I2C_EN_RESET;   
    }
}


/**
*\*\name    I2C_GenerateStart.
*\*\fun     Enable or disables Generate a START condition.
*\*\param   I2Cx (The input parameters must be the following values):
*\*\          - I2C1
*\*\          - I2C2
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\return  none
**/
void I2C_GenerateStart(I2C_Module* I2Cx, FunctionalState Cmd)
{   
    if (Cmd != DISABLE)
    {
        /* Generate a START condition */
        I2Cx->CTRL1 |= I2C_START_SET;
    }
    else
    {
        /* Disable the START condition generation */
        I2Cx->CTRL1 &= I2C_START_RESET;
    }
}


/**
*\*\name    I2C_GenerateStop.
*\*\fun     Enable  or disables Generate a STOP condition.
*\*\param   I2Cx (The input parameters must be the following values):
*\*\          - I2C1
*\*\          - I2C2
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\return  none
**/
void I2C_GenerateStop(I2C_Module* I2Cx, FunctionalState Cmd)
{   
    if (Cmd != DISABLE)
    {
        /* Generate a STOP condition */
        I2Cx->CTRL1 |= I2C_STOP_SET;
    }
    else
    {
        /* Disable the STOP condition generation */
        I2Cx->CTRL1 &= I2C_STOP_RESET;
    }
}

/**
*\*\name    I2C_ConfigAck.
*\*\fun     Enable  or disables the acknowledgement.
*\*\param   I2Cx (The input parameters must be the following values):
*\*\          - I2C1
*\*\          - I2C2
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\return  none
**/
void I2C_ConfigAck(I2C_Module* I2Cx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the acknowledgement */
        I2Cx->CTRL1 |= I2C_ACK_SET;
    }
    else
    {
        /* Disable the acknowledgement */
        I2Cx->CTRL1 &= I2C_ACK_RESET;
    }
}


/**
*\*\name    I2C_SendAddr7bit.
*\*\fun     Transmits the address byte to select the slave device.
*\*\param   I2Cx (The input parameters must be the following values):
*\*\          - I2C1
*\*\          - I2C2
*\*\param   address (The input parameters must be the following values)
*\*\        - 0 to 0xFF 
*\*\param   mode (The input parameters must be the following values):
*\*\          - I2C_DIRECTION_SEND    Transmitter mode
*\*\          - I2C_DIRECTION_RECV    Receiver mode
*\*\return  none
**/
void I2C_SendAddr7bit(I2C_Module* I2Cx, uint8_t address, uint8_t mode)
{
    uint8_t temp_value;
    /* Test on the direction to set/reset the read/write bit */
    if (mode == I2C_DIRECTION_RECV)
    {
        /* Set the address bit0 for read */
        temp_value = (uint8_t)(address | I2C_ADDR0_SET);
    }
    else
    {
        /* Reset the address bit0 for write */
        temp_value = (uint8_t)(address & I2C_ADDR0_RESET);
    }
    /* Send the address */
    I2Cx->DAT = temp_value;
}

/**
*\*\name    I2C_ConfigOwnAddr2.
*\*\fun     Set the specified I2C own address2.
*\*\param   I2Cx (The input parameters must be the following values):
*\*\          - I2C1
*\*\          - I2C2
*\*\param   address(The input parameters must be the following values)
*\*\          - - 0 to 0xFF
*\*\return  none
**/
void I2C_ConfigOwnAddr2(I2C_Module* I2Cx, uint8_t address)
{
    uint16_t temp_value;

    /* Get the old register value */
    temp_value = I2Cx->OADDR2;

    /* Reset I2Cx Own address2 bit [7:1] */
    temp_value &= I2C_ADDR2_RESET;

    /* Set I2Cx Own address2 */
    temp_value |= (uint16_t)((uint16_t)address & I2C_ADDR2_SET);

    /* Store the new register value */
    I2Cx->OADDR2 = temp_value;
}

/**
*\*\name    I2C_EnableDualAddr.
*\*\fun     Enables or disables the specified I2C dual addressing mode.
*\*\param   I2Cx (The input parameters must be the following values):
*\*\          - I2C1
*\*\          - I2C2
\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\return  none
**/
void I2C_EnableDualAddr(I2C_Module* I2Cx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable dual addressing mode */
        I2Cx->OADDR2 |= I2C_DUALEN_SET;
    }
    else
    {
        /* Disable dual addressing mode */
        I2Cx->OADDR2 &= I2C_DUALEN_RESET;
    }
}


/**
*\*\name    I2C_EnableGeneralCall.
*\*\fun     Enables or disables the specified I2C general call feature.
*\*\param   I2Cx (The input parameters must be the following values):
*\*\          - I2C1
*\*\          - I2C2
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\return  none
**/
void I2C_EnableGeneralCall(I2C_Module* I2Cx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable generall call */
        I2Cx->CTRL1 |= I2C_GCEN_SET;
    }
    else
    {
        /* Disable generall call */
        I2Cx->CTRL1 &= I2C_GCEN_RESET;
    }
}



/**
*\*\name    I2C_ConfigInt.
*\*\fun     Enables the specified I2C interrupts.
*\*\param   I2Cx (The input parameters must be the following values):
*\*\          - I2C1
*\*\          - I2C2
*\*\param   I2C_IT (The input parameters must be the following values):
*\*\          - I2C_INT_BUF      Buffer interrupt mask
*\*\          - I2C_INT_EVENT    Event interrupt mask
*\*\          - I2C_INT_ERR      Error interrupt mask
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\return  none
**/
void I2C_ConfigInt(I2C_Module* I2Cx, uint32_t I2C_IT, FunctionalState Cmd)
{
    
    if (Cmd != DISABLE)
    {
        /* Enable the selected I2C interrupts */
        I2Cx->CTRL2 |= I2C_IT;
    }
    else
    {
        /* Disable the selected I2C interrupts */
        I2Cx->CTRL2 &= (~I2C_IT);
    }
}


/**
*\*\name    I2C_SendData.
*\*\fun     Sends a data byte through the I2Cx peripheral.
*\*\param   I2Cx (The input parameters must be the following values):
*\*\          - I2C1
*\*\          - I2C2
*\*\param   data: 0x00~0xFF
*\*\return  none
**/
void I2C_SendData(I2C_Module* I2Cx, uint8_t data)
{
    /* Write in the DAT register the data to be sent */
    I2Cx->DAT = data;
}

/**
*\*\name    I2C_RecvData.
*\*\fun     Returns the most recent received data by the I2Cx peripheral.
*\*\param   I2Cx (The input parameters must be the following values):
*\*\          - I2C1
*\*\          - I2C2
*\*\return  The value of the received data
**/
uint8_t I2C_RecvData(I2C_Module* I2Cx)
{
    /* Return the data in the DAT register */
    return (uint8_t)I2Cx->DAT;
}

/**
*\*\name    I2C_EnableDMA.
*\*\fun     Enables or disables I2C DMA transfer.
*\*\param   I2Cx (The input parameters must be the following values):
*\*\          - I2C1
*\*\          - I2C2
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\return  none
**/
void I2C_EnableDMA(I2C_Module* I2Cx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Set the I2C_CTRL2 DMAEN bit to enable DMA transfer */
        I2Cx->CTRL2 |= I2C_DMAEN_SET;
    }
    else
    {
        /* Clean the I2C_CTRL2 DMAEN bit to disable DMA transfer */
        I2Cx->CTRL2 &= I2C_DMAEN_RESET;
    }
    
}


/**
*\*\name    I2C_EnableDmaLastSend.
*\*\fun     Enables  or disables I2C DMA last transfer.
*\*\param   I2Cx (The input parameters must be the following values):
*\*\          - I2C1
*\*\          - I2C2
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\return  none
*\*\note    This bit is used in the master receiving mode, so that a NACK can be generated when
*\*\        data is received for the last time.
**/
void I2C_EnableDmaLastSend(I2C_Module* I2Cx, FunctionalState Cmd)
{   
    if (Cmd != DISABLE)
    {
        /* Next DMA transfer is the last transfer */
        I2Cx->CTRL2 |= I2C_DMALAST_SET;
    }
    else
    {
        /* Next DMA transfer is not the last transfer */
        I2Cx->CTRL2 &= I2C_DMALAST_RESET;
    }
    
}

/**
*\*\name    I2C_EnableSoftwareReset.
*\*\fun     Enables or disables the specified I2C software reset.
*\*\param   I2Cx (The input parameters must be the following values):
*\*\          - I2C1
*\*\          - I2C2
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\return  none
*\*\note    This bit can be used when the I2C_STS2.BUSY bit is set to 1 and no stop condition is detected
*\*\        on the bus.
**/
void I2C_EnableSoftwareReset(I2C_Module* I2Cx, FunctionalState Cmd)
{
    if (Cmd != DISABLE) 
    {
        /* Peripheral under reset */
        I2Cx->CTRL1 |= I2C_SWRESET_SET;
    }
    else
    {
       /* Peripheral not under reset */
        I2Cx->CTRL1 &= I2C_SWRESET_RESET;
    }
    
}

/**
*\*\name    I2C_ConfigNackLocation.
*\*\fun     Selects the specified I2C NACK position in master receiver mode.
*\*\        This function is useful in I2C Master Receiver mode when the number
*\*\        of data to be received is equal to 2. In this case, this function
*\*\        should be called (with parameter I2C_NACK_POS_NEXT) before data
*\*\        reception starts,as described in the 2-byte reception procedure
*\*\        recommended in User Manual in Section: Master receiver.
*\*\param   I2Cx (The input parameters must be the following values):
*\*\          - I2C1
*\*\          - I2C2
*\*\param   position (The input parameters must be the following values):
*\*\          - I2C_NACK_POS_NEXT       Indicates that the next byte will be the last received byte.
*\*\          - I2C_NACK_POS_CURRENT    Indicates that the current byte is the last received byte.
*\*\return  none
*\*\note    ACKPOS bit can only be used in 2-byte receiving configuration and must be configured before
*\*\        receiving data.
*\*\        For the second byte of NACK, the I2C_CTRL1.ACKEN bit must be cleared after the
*\*\        I2C_STS1.ADDRF bit is cleared.
*\*\        To detect the PEC of the second byte, the I2C_CTRL1.PEC bit must be set after the ACKPOS bit is
*\*\        configured and when the ADDR event is extended.
**/

void I2C_ConfigNackLocation(I2C_Module* I2Cx, uint32_t position)
{
    if (position == I2C_NACK_POS_NEXT)
    {
        /* Next byte in shift register is the last received byte */
        I2Cx->CTRL1 |= I2C_NACK_POS_NEXT;
    }
    else
    {
        /* Current byte in shift register is the last received byte */
        I2Cx->CTRL1 &= I2C_NACK_POS_CURRENT;
    }
}

/**
*\*\name    I2C_ConfigPecLocation.
*\*\fun     Selects the specified I2C PEC position.
*\*\param   I2Cx (The input parameters must be the following values):
*\*\          - I2C1
*\*\          - I2C2
*\*\param   position (The input parameters must be the following values):
*\*\          - I2C_PEC_POS_NEXT       Indicates that the next byte will be the last received byte or the next byte is PEC.
*\*\          - I2C_PEC_POS_CURRENT    Indicates that the current byte is the last received byte or the current byte is PEC.
*\*\return  none
*\*\note   This function configures the same bit (ACKPOS) as I2C_ConfigNackLocation()
*\*\       but is intended to be used in SMBUS mode while I2C_ConfigNackLocation()
*\*\       is intended to used in I2C mode.
**/

void I2C_ConfigPecLocation(I2C_Module* I2Cx, uint32_t position)
{
    if (position == I2C_PEC_POS_NEXT)
    {
        /* Next byte in shift register is the last received byte */
        I2Cx->CTRL1 |= I2C_PEC_POS_NEXT;
    }
    else
    {
        /* Current byte in shift register is the last received byte */
        I2Cx->CTRL1 &= I2C_PEC_POS_CURRENT;
    }
}

/**
*\*\name    I2C_ConfigSmbusAlert.
*\*\fun     Set the SMBus Alert pin high or low for the specified I2C.
*\*\param   I2Cx (The input parameters must be the following values):
*\*\          - I2C1
*\*\          - I2C2
*\*\param   polarity (The input parameters must be the following values):
*\*\          - I2C_SMBALERT_LOW     SMBAlert pin driven low
*\*\          - I2C_SMBALERT_HIGH    SMBAlert pin driven high
*\*\return  none
**/
void I2C_ConfigSmbusAlert(I2C_Module* I2Cx, uint32_t polarity)
{
    if (polarity == I2C_SMBALERT_LOW)
    {
        /* Drive the SMBusAlert pin Low */
        I2Cx->CTRL1 |= I2C_SMBALERT_LOW;
    }
    else
    {
        /* Drive the SMBusAlert pin High  */
        I2Cx->CTRL1 &= I2C_SMBALERT_HIGH;
    }
}

/**
*\*\name    I2C_SendPEC.
*\*\fun     Enables or disables the specified I2C PEC transfer.
*\*\param   I2Cx (The input parameters must be the following values):
*\*\          - I2C1
*\*\          - I2C2
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\return  none
*\*\note    When arbitration is lost, the calculation of PEC is invalid.
**/
void I2C_SendPEC(I2C_Module* I2Cx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected I2C PEC transmission */
        I2Cx->CTRL1 |= I2C_PEC_SET;
    }
    else
    {
        /* Disable the selected I2C PEC transmission */
        I2Cx->CTRL1 &= I2C_PEC_RESET;
    }
    
}

/**
*\*\name    I2C_ComputePec.
*\*\fun     Enables or disables the PEC value calculation of the transferred bytes.
*\*\param   I2Cx (The input parameters must be the following values):
*\*\          - I2C1
*\*\          - I2C2
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\return  none
**/
void I2C_ComputePec(I2C_Module* I2Cx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected I2C PEC calculation */
        I2Cx->CTRL1 |= I2C_PECEN_SET;
    }
    else
    {
        /* Disable the selected I2C PEC calculation */
        I2Cx->CTRL1 &= I2C_PECEN_RESET;
    }
    
}

/**
*\*\name    I2C_GetPec.
*\*\fun     Get the PEC value for the specified I2C.
*\*\param   I2Cx (The input parameters must be the following values):
*\*\          - I2C1
*\*\          - I2C2
*\*\return  The PEC value
**/
uint8_t I2C_GetPec(I2C_Module* I2Cx)
{
    /* Return the selected I2C PEC value */
    return (uint8_t)(I2Cx->STS2 >> 8);
}

/**
*\*\name    I2C_EnableArp.
*\*\fun     Enables or disables the specified I2C Address Resolution Protocol(ARP).
*\*\param   I2Cx (The input parameters must be the following values):
*\*\          - I2C1
*\*\          - I2C2
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\return  none
**/
void I2C_EnableArp(I2C_Module* I2Cx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected I2C ARP */
        I2Cx->CTRL1 |= I2C_ARPEN_SET; 
    }
    else
    {
        /* Disable the selected I2C ARP */
        I2Cx->CTRL1 &= I2C_ARPEN_RESET;
    }
    
}

/**
*\*\name    I2C_EnableExtendClk.
*\*\fun     Enables or disables the specified I2C clock extending.
*\*\param   I2Cx (The input parameters must be the following values):
*\*\          - I2C1
*\*\          - I2C2
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\return  none
**/
void I2C_EnableExtendClk(I2C_Module* I2Cx, FunctionalState Cmd)
{
    if (Cmd == DISABLE)
    {
        /* Disable the selected I2C Clock extending */
        I2Cx->CTRL1 |= I2C_NOEXTEND_SET;
        
    }
    else
    {
        /* Enable the selected I2C Clock extending */
        I2Cx->CTRL1 &= I2C_NOEXTEND_RESET; 
    }
    
}

/**
*\*\name    I2C_SetSDADigitalFilterWidth.
*\*\fun     SDA digital filter width selection.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\param   width :
*\*\          - 0x00            Disable the digital filter.
*\*\          - 0x01 ~ 0x0F     The numbers of pclk cycles.
*\*\return  none
**/
void I2C_SetSDADigitalFilterWidth(I2C_Module* I2Cx, uint8_t width)
{
    uint16_t temp_value;

    temp_value = I2Cx->GFLTRCTRL;
    /* Clear SDADFW[3:0] bits */
    temp_value &= I2C_SDADFW_MASK;
    /* Set SDADFW[3:0] bits according to width value */
    temp_value |= (uint16_t)width ;
    /* Store the new value */
    I2Cx->GFLTRCTRL = temp_value;

}

/**
*\*\name    I2C_SetSCLDigitalFilterWidth.
*\*\fun     SCL digital filter width selection.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\param   width :
*\*\          - 0x00            Disable the digital filter.
*\*\          - 0x01 ~ 0x0F     The numbers of pclk cycles.
*\*\return  none
**/
void I2C_SetSCLDigitalFilterWidth(I2C_Module* I2Cx, uint8_t width)
{
    uint16_t temp_value;

    temp_value = I2Cx->GFLTRCTRL;
    /* Clear SCLDFW[3:0] bits */
    temp_value &= I2C_SCLDFW_MASK;
    /* Set SCLDFW[3:0] bits according to width value */
    temp_value |= ((uint16_t)width << 4);
    /* Store the new value */
    I2Cx->GFLTRCTRL = temp_value;

}

/**
*\*\name    I2C_SetSDAAnalogFilterWidth.
*\*\fun     SDA analog filter width selection.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\param   width :
*\*\        - I2C_ANALOG_FILTER_WIDTH_5NS
*\*\        - I2C_ANALOG_FILTER_WIDTH_15NS
*\*\        - I2C_ANALOG_FILTER_WIDTH_25NS
*\*\        - I2C_ANALOG_FILTER_WIDTH_35NS
*\*\return  none
**/
void I2C_SetSDAAnalogFilterWidth(I2C_Module* I2Cx, uint16_t width)
{
    uint16_t temp_value;

    temp_value = I2Cx->GFLTRCTRL;
    /* Clear SDAAFW[1:0] bits */
    temp_value &= I2C_SDAAFW_MASK;
    /* Set SDAAFW[1:0] bits according to width value */
    temp_value |= width;
    /* Store the new value */
    I2Cx->GFLTRCTRL = temp_value;

}

/**
*\*\name    I2C_EnableSDAAnalogFilter.
*\*\fun     Enables or disables the SDA analog filter.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\return  none
**/
void I2C_EnableSDAAnalogFilter(I2C_Module* I2Cx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the SDA analog filter */
        I2Cx->GFLTRCTRL &= I2C_SDAAFENN_RESET;
    }
    else
    {
         /* Disable the SDA analog filter */
        I2Cx->GFLTRCTRL |= I2C_SDAAFENN_SET;
    }
    
}

/**
*\*\name    I2C_SetSCLAnalogFilterWidth.
*\*\fun     SCL analog filter width selection.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\param   width :
*\*\        - I2C_ANALOG_FILTER_WIDTH_5NS
*\*\        - I2C_ANALOG_FILTER_WIDTH_15NS
*\*\        - I2C_ANALOG_FILTER_WIDTH_25NS
*\*\        - I2C_ANALOG_FILTER_WIDTH_35NS
*\*\return  none
**/
void I2C_SetSCLAnalogFilterWidth(I2C_Module* I2Cx, uint16_t width)
{
    uint16_t temp_value;

    temp_value = I2Cx->GFLTRCTRL;
    /* Clear SCLAFW[1:0] bits */
    temp_value &= I2C_SCLAFW_MASK;
    /* Set SCLAFW[1:0] bits according to width value */
    temp_value |= (width << 4);
    /* Store the new value */
    I2Cx->GFLTRCTRL = temp_value;

}

/**
*\*\name    I2C_EnableSCLAnalogFilter.
*\*\fun     Enables or disables the SCL analog filter.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\return  none
**/
void I2C_EnableSCLAnalogFilter(I2C_Module* I2Cx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the SCL analog filter */
        I2Cx->GFLTRCTRL &= I2C_SCLAFENN_RESET;
    }
    else
    {
        /* Disable the SCL analog filter */
        I2Cx->GFLTRCTRL |= I2C_SCLAFENN_SET;
    }
    
}

/**
*\*\name    I2C_CheckEvent.
*\*\fun     Checks whether the last I2Cx Event is equal to the one passed as parameter.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\param   I2C_event :
*\*\          - I2C_EVT_SLAVE_SEND_ADDR_MATCHED                     EV1
*\*\          - I2C_EVT_SLAVE_RECV_ADDR_MATCHED                     EV1
*\*\          - I2C_EVT_SLAVE_SEND_ADDR2_MATCHED                    EV1
*\*\          - I2C_EVT_SLAVE_RECV_ADDR2_MATCHED                    EV1
*\*\          - I2C_EVT_SLAVE_GCALLADDR_MATCHED                     EV1
*\*\          - I2C_EVT_SLAVE_DATA_RECVD                            EV2
*\*\          - (I2C_EVT_SLAVE_DATA_RECVD | I2C_FLAG_DUALFLAG)      EV2
*\*\          - (I2C_EVT_SLAVE_DATA_RECVD | I2C_FLAG_GCALLADDR)     EV2
*\*\          - I2C_EVT_SLAVE_DATA_SENDED                           EV3
*\*\          - (I2C_EVT_SLAVE_DATA_SENDED | I2C_FLAG_DUALFLAG)     EV3
*\*\          - (I2C_EVT_SLAVE_DATA_SENDED | I2C_FLAG_GCALLADDR)    EV3
*\*\          - I2C_EVT_SLAVE_ACK_MISS                              EV3_2
*\*\          - I2C_EVT_SLAVE_STOP_RECVD                            EV4
*\*\          - I2C_EVT_MASTER_MODE_FLAG                            EV5
*\*\          - I2C_EVT_MASTER_TXMODE_FLAG                          EV6
*\*\          - I2C_EVT_MASTER_RXMODE_FLAG                          EV6
*\*\          - I2C_EVT_MASTER_DATA_RECVD_FLAG                      EV7
*\*\          - I2C_EVT_MASTER_DATA_SENDING                         EV8
*\*\          - I2C_EVT_MASTER_DATA_SENDED                          EV8_2
*\*\          - I2C_EVT_MASTER_MODE_ADDRESS10_FLAG                  EV9
*\*\return  SUCCESS or ERROR
*\*\note    If an error occurs (that is, an error flag is set in addition to the flags parameter entered), the function may still return SUCCESS.
*\*\        In this case, you can use error interrupts to handle error events.
**/
ErrorStatus I2C_CheckEvent(I2C_Module* I2Cx, uint32_t I2C_event)
{
    uint32_t temp_value;
    uint32_t flag1, flag2;
    ErrorStatus bitstatus;

    /* Read the I2Cx status register */
    flag1 = I2Cx->STS1;
    flag1 = flag1&((uint32_t)0xFFFF);
    flag2 = I2Cx->STS2;
    flag2 = (flag2&((uint32_t)0xFFFF)) << RCC_FLAG_STS2_OFFSET;

    /* Get the last event value from I2C status register */
    temp_value = (flag1 | flag2) & I2C_FLAG_MASK;

    /* Check whether the last event contains the I2C_event */
    if ((temp_value & I2C_event) == I2C_event)
    {
        /* Return SUCCESS: last event is equal to I2C_event */
        bitstatus = SUCCESS;
    }
    else
    {
        /* Return ERROR: last event is different from I2C_event */
        bitstatus = ERROR;
    }
    return bitstatus;
}

/**
*\*\name    I2C_GetLastEvent.
*\*\fun     Returns the last I2Cx Event.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\return  The last event
*\*\note    Users can define their own events.
*\*\        If the user decides to check only the general communication flags (ignore error flags), 
*\*\        when an error occurs, you can use error interrupts to handle error events.
**/
uint32_t I2C_GetLastEvent(I2C_Module* I2Cx)
{
    uint32_t flag1, flag2;

    /* Read the I2Cx status register */   
    flag1 = I2Cx->STS1;
    flag1 = flag1&((uint32_t)0xFFFF);
    flag2 = I2Cx->STS2;
    flag2 = (flag2&((uint32_t)0xFFFF)) << RCC_FLAG_STS2_OFFSET;

    /* Return the last event value from I2C status register */
    return (flag1 | flag2) & I2C_FLAG_MASK;
}

/**
*\*\name    I2C_GetFlag.
*\*\fun     Checks whether the specified I2C flag is set or not.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\param   I2C_flag :
*\*\          - I2C_FLAG_DUALFLAG     Dual flag (Slave mode)
*\*\          - I2C_FLAG_SMBHADDR     SMBus host header (Slave mode)
*\*\          - I2C_FLAG_SMBDADDR     SMBus default header (Slave mode)
*\*\          - I2C_FLAG_GCALLADDR    General call header flag (Slave mode)
*\*\          - I2C_FLAG_TRF          Transmitter/Receiver flag
*\*\          - I2C_FLAG_BUSY         Bus busy flag
*\*\          - I2C_FLAG_MSMODE       Master/Slave flag
*\*\          - I2C_FLAG_SMBALERT     SMBus Alert flag
*\*\          - I2C_FLAG_PECERR       PEC error in reception flag
*\*\          - I2C_FLAG_OVERRUN      Overrun/Underrun flag (Slave mode)
*\*\          - I2C_FLAG_ACKFAIL      Acknowledge failure flag
*\*\          - I2C_FLAG_ARLOST       Arbitration lost flag (Master mode)
*\*\          - I2C_FLAG_BUSERR       Bus error flag
*\*\          - I2C_FLAG_TXDATE       Data register empty flag (Transmitter)
*\*\          - I2C_FLAG_RXDATNE      Data register not empty (Receiver) flag
*\*\          - I2C_FLAG_STOPF        Stop detection flag (Slave mode)
*\*\          - I2C_FLAG_ADDR10F      10-bit header sent flag (Master mode)
*\*\          - I2C_FLAG_BYTEF        Byte transfer finished flag
*\*\          - I2C_FLAG_ADDRF        Address sent flag (Master mode) 
*\*\                                  Address matched flag (Slave mode)
*\*\          - I2C_FLAG_STARTBF      Start bit flag (Master mode)
*\*\return  SET or RESET
*\*\note    When this function is called, the status register is accessed, so other flags may be cleared.
*\*\        You can call I2C_GetFlag() in I2Cx_ER_IRQHandler() to determine which error occurred.
**/
FlagStatus I2C_GetFlag(I2C_Module* I2Cx, uint32_t I2C_flag)
{
    uint32_t temp_value, temp_value1;
    FlagStatus bitstatus;

    /* Read flag register index */
    temp_value = I2C_flag >> RCC_FLAG_GET_OFFSET;

    /* Get bit[23:0] of the flag */
    temp_value1 = (I2C_flag & I2C_FLAG_MASK);

    if (temp_value == 0)
    {
        /* Flag in I2Cx STS2 Register */
        temp_value1 = (uint32_t)(temp_value1 >> RCC_FLAG_STS2_OFFSET);
        /* Get the I2Cx STS2 register address */
		if ((I2Cx->STS2 & temp_value1) == (uint32_t)RESET)
        {
            /* I2C_flag is reset */
            bitstatus = RESET;
        }
        else
        {
            /* I2C_flag is set */
            bitstatus = SET;
        }
    }
    else
    {
        /* Get the I2Cx STS1 register address */
        if ((I2Cx->STS1 & temp_value1) == (uint32_t)RESET)
        {
            /* I2C_flag is reset */
            bitstatus = RESET;
        }
        else
        {
            /* I2C_flag is set */
            bitstatus = SET;
        }
    }
    return bitstatus;
}

/**
*\*\name    I2C_ClrFlag.
*\*\fun     Clears the I2Cx's flags.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\param   I2C_flag :
*\*\          - I2C_FLAG_SMBALERT    SMBus Alert flag
*\*\          - I2C_FLAG_PECERR      PEC error in reception flag
*\*\          - I2C_FLAG_OVERRUN     Overrun/Underrun flag (Slave mode)
*\*\          - I2C_FLAG_ACKFAIL     Acknowledge failure flag
*\*\          - I2C_FLAG_ARLOST      Arbitration lost flag (Master mode)
*\*\          - I2C_FLAG_BUSERR      Bus error flag
*\*\note    Software can read this bit or clear it by writing' 0', and writing' 1' has no effect on this bit.
*\*\        The other flag bits are cleared in the following sequence:
*\*\        - STOPF (STOP detection) is cleared by software sequence: a read operation
*\*\          to I2C_STS1 register followed by a write operation to I2C_CTRL1 register (I2C_ON()
*\*\          to re-enable the I2C peripheral).
*\*\        - ADDR10F (10-bit header sent) is cleared by software sequence: a read
*\*\          operation to I2C_STS1 followed by writing the second byte of the address in DAT register.        
*\*\        - BYTEF (Byte Transfer Finished) is cleared by software sequence: a read
*\*\          operation to I2C_STS1 register followed by a read/write to I2C_DAT register.
*\*\        - ADDRF (Address sent) is cleared by software sequence: a read operation to
*\*\          I2C_STS1 register followed by a read operation to I2C_STS2 register.
*\*\        - STARTBF (Start Bit) is cleared software sequence: a read operation to I2C_STS1
*\*\          register followed by a write operation to I2C_DAT register.
*\*\return  none
**/
void I2C_ClrFlag(I2C_Module* I2Cx, uint32_t I2C_flag)
{
    uint32_t temp_value;

    /* Get the I2C flag position */
    temp_value = I2C_flag & I2C_FLAG_MASK;
    /* Clear the selected I2C flag */
    I2Cx->STS1 = (~temp_value)&I2C_STS1_RESERVED_MASK;
}

/**
*\*\name    I2C_GetIntStatus.
*\*\fun     Checks whether the specified I2C interrupt has occurred or not.
*\*\param   I2Cx (The input parameters must be the following values):
*\*\          - I2C1
*\*\          - I2C2
*\*\param   Interrupt (The input parameters must be the following values):
*\*\          - I2C_INT_SMBALERT    SMBus Alert flag
*\*\          - I2C_INT_PECERR      PEC error in reception flag
*\*\          - I2C_INT_OVERRUN     Overrun/Underrun flag (Slave mode)
*\*\          - I2C_INT_ACKFAIL     Acknowledge failure flag
*\*\          - I2C_INT_ARLOST      Arbitration lost flag (Master mode)
*\*\          - I2C_INT_BUSERR      Bus error flag
*\*\          - I2C_INT_TXDATE      Data register empty flag (Transmitter)
*\*\          - I2C_INT_RXDATNE     Data register not empty (Receiver) flag
*\*\          - I2C_INT_STOPF       Stop detection flag (Slave mode)
*\*\          - I2C_INT_ADDR10F     10-bit header sent flag (Master mode)
*\*\          - I2C_INT_BYTEF       Byte transfer finished flag
*\*\          - I2C_INT_ADDRF       Address sent flag (Master mode) 
*\*\                                Address matched flag (Slave mode)
*\*\          - I2C_INT_STARTBF     Start bit flag (Master mode)
*\*\return  SET or RESET
*\*\note    You can call I2C_GetIntStatus() in I2Cx_ER_IRQHandler() to determine which error occurred.
**/
INTStatus I2C_GetIntStatus(I2C_Module* I2Cx, uint32_t Interrupt)
{
    uint32_t temp_value, temp_value1;
    INTStatus bitstatus;

    /* Check if the interrupt source is enabled or not */
    temp_value = (uint32_t)(((Interrupt & I2C_INTEN_MASK) >> 16) & (I2Cx->CTRL2));

    /* Get bit[23:0] of the flag */
    temp_value1 = (Interrupt & I2C_FLAG_MASK);

    /* Check the status of the specified I2C flag */
    if (((I2Cx->STS1 & temp_value1) != (uint32_t)RESET) && (temp_value != 0u))
    {
        /* Interrupt is set */
        bitstatus = SET;
    }
    else
    {
        /* Interrupt is reset */
        bitstatus = RESET;
    }
    return bitstatus;
}

/**
*\*\name    I2C_ClrIntPendingBit.
*\*\fun     Clears the I2Cx's interrupt statu bits.
*\*\param   I2Cx (The input parameters must be the following values):
*\*\          - I2C1
*\*\          - I2C2
*\*\param   Interrupt (The input parameters must be the following values):
*\*\          - I2C_INT_SMBALERT    SMBus Alert flag
*\*\          - I2C_INT_PECERR      PEC error in reception flag
*\*\          - I2C_INT_OVERRUN     Overrun/Underrun flag (Slave mode)
*\*\          - I2C_INT_ACKFAIL     Acknowledge failure flag
*\*\          - I2C_INT_ARLOST      Arbitration lost flag (Master mode)
*\*\          - I2C_INT_BUSERR      Bus error flag
*\*\return  none
*\*\note    Software can read this bit or clear it by writing' 0', and writing' 1' has no effect on this bit.
*\*\        The other flag bits are cleared in the following sequence:
*\*\        - STOPF (STOP detection) is cleared by software sequence: a read operation
*\*\          to I2C_STS1 register followed by a write operation to I2C_CTRL1 register (I2C_ON()
*\*\          to re-enable the I2C peripheral).
*\*\        - ADDR10F (10-bit header sent) is cleared by software sequence: a read
*\*\          operation to I2C_STS1 followed by writing the second byte of the address in DAT register.        
*\*\        - BYTEF (Byte Transfer Finished) is cleared by software sequence: a read
*\*\          operation to I2C_STS1 register followed by a read/write to I2C_DAT register.
*\*\        - ADDRF (Address sent) is cleared by software sequence: a read operation to
*\*\          I2C_STS1 register followed by a read operation to I2C_STS2 register.
*\*\        - STARTBF (Start Bit) is cleared software sequence: a read operation to I2C_STS1
*\*\          register followed by a write operation to I2C_DAT register.
**/
void I2C_ClrIntPendingBit(I2C_Module* I2Cx, uint32_t Interrupt)
{
    uint32_t temp_value;

    /* Get the I2C flag position */
    temp_value = Interrupt & I2C_FLAG_MASK;
    /* Clear the selected I2C flag */
    I2Cx->STS1 = (~temp_value)&I2C_STS1_RESERVED_MASK;
}

/**
*\*\name    I2C_EnableByteNum.
*\*\fun     Enables or disables the specified I2C peripheral ByteNum function.
*\*\param   I2Cx :
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\return  none
**/
void I2C_EnableByteNum(I2C_Module* I2Cx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected I2C peripheral ByteNum function*/
        I2Cx->BYTENUM |= I2C_BYTENUMEN_SET;
    }
    else
    {
        /* Disable the selected I2C peripheral ByteNum function*/
        I2Cx->BYTENUM &= I2C_BYTENUMEN_RESET;
    }
    
}

/**
*\*\name    I2C_SetMasterReceivedDataBytesNum.
*\*\fun     Set the number of data bytes that will be received by master receiver of I2C peripheral.
*\*\param   I2Cx :
*\*\          - I2C
*\*\param   Number_Of_bytes(the number of data bytes) :
*\*\          - 0x0~0x3FFF
*\*\return  none
**/
void I2C_SetMasterReceivedDataBytesNum(I2C_Module* I2Cx, uint16_t Number_Of_bytes)
{
    uint16_t temp_value;

    temp_value = I2Cx->BYTENUM;
    /* Clear BYTENUM[13:0] bits */
    temp_value &= I2C_BYTENUM_MASK;
    /* Set BYTENUM[13:0] bits according to Number_Of_bytes value */
    temp_value |= Number_Of_bytes;
    /* Store the new value */
    I2Cx->BYTENUM = temp_value;
}

/**
*\*\name    I2C_SetByteNumLastStartStop.
*\*\fun     Configure the last status after master have finished sending the required data bytes.
*\*\param   I2Cx :
*\*\          - I2C
*\*\param   LastStatus :
*\*\          - I2C_BYTENUM_LAST_STOP
*\*\ 		  - I2C_BYTENUM_LAST_START
*\*\return  none
**/
void I2C_SetByteNumLastStartStop(I2C_Module* I2Cx, uint16_t LastStatus)
{
	if (LastStatus == I2C_BYTENUM_LAST_START)
    {
        /* Next byte in shift register is PEC */
        I2Cx->BYTENUM |= I2C_BYTENUM_LAST_START;
    }
    else
    {
        /* Current byte in shift register is PEC */
        I2Cx->BYTENUM &= I2C_BYTENUM_LAST_STOP;
    }
}

/**
*\*\name    I2C_SetTimeoutLowLimit.
*\*\fun     timeout low threshold selection.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\param   limit:
*\*\          - I2C_TIMEOUT_LOWLIMIT_25MS 
*\*\ 		  - I2C_TIMEOUT_LOWLIMIT_100MS
*\*\ 		  - I2C_TIMEOUT_LOWLIMIT_1S   
*\*\ 		  - I2C_TIMEOUT_LOWLIMIT_4S   
*\*\return  none
**/
void I2C_SetTimeoutLowLimit(I2C_Module* I2Cx, uint32_t limit)
{
    uint32_t temp_value;

    temp_value = I2Cx->CTRL1;
    /* Clear LTOSEL[1:0] bits */
    temp_value &= I2C_LTOSEL_MASK;
    /* Set LTOSEL[1:0] bits according to limit value */
    temp_value |= limit;
    /* Store the new value */
    I2Cx->CTRL1 = temp_value;
}

/**
*\*\name    I2C_SetTimeoutHighLimit.
*\*\fun     timeout high threshold selection.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\param   limit:
*\*\          - I2C_TIMEOUT_HIGHLIMIT_256US
*\*\ 		  - I2C_TIMEOUT_HIGHLIMIT_512US
*\*\ 		  - I2C_TIMEOUT_HIGHLIMIT_1MS  
*\*\ 		  - I2C_TIMEOUT_HIGHLIMIT_128US
*\*\return  none
**/
void I2C_SetTimeoutHighLimit(I2C_Module* I2Cx, uint32_t limit)
{
    uint32_t temp_value;

    temp_value = I2Cx->CTRL1;
    /* Clear HTOSEL[1:0] bits */
    temp_value &= I2C_HTOSEL_MASK;
    /* Set HTOSEL[1:0] bits according to limit value */
    temp_value |= limit;
    /* Store the new value */
    I2Cx->CTRL1 = temp_value;
}

/**
*\*\name    I2C_ConfigTimeoutInt.
*\*\fun     Enables the specified I2C timeout interrupts.
*\*\param   I2Cx (The input parameters must be the following values):
*\*\          - I2C1
*\*\          - I2C2
*\*\param   I2C_IT (The input parameters must be the following values):
*\*\          - I2C_TIMEOUT_INT_SCLLOW     SCL low timeout error interrupt 
*\*\          - I2C_TIMEOUT_INT_SCLHIGH    SCL high timeout error interrupt 
*\*\          - I2C_TIMEOUT_INT_SDALOW     SDA low timeout error interrupt 
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\return  none
**/
void I2C_ConfigTimeoutInt(I2C_Module* I2Cx, uint32_t I2C_IT, FunctionalState Cmd)
{
    
    if (Cmd != DISABLE)
    {
        /* Enable the selected I2C timeout interrupts */
        I2Cx->CTRL2 |= I2C_IT;
    }
    else
    {
        /* Disable the selected I2C timeout interrupts */
        I2Cx->CTRL2 &= (~I2C_IT);
    }
}

/**
*\*\name    I2C_EnableTimeout.
*\*\fun     Enables the specified I2C timeout detection function .
*\*\param   I2Cx (The input parameters must be the following values):
*\*\          - I2C1
*\*\          - I2C2
*\*\param   timeout_type (The input parameters must be the following values):
*\*\          - I2C_TIMEOUT_LOW     low timeout function enable 
*\*\          - I2C_TIMEOUT_HIGH    high timeout function enable
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\note    This function can be disabled in I2C mode when an timeout error is not required.
*\*\return  none
**/
void I2C_EnableTimeoutDetect(I2C_Module* I2Cx, uint32_t timeout_type, FunctionalState Cmd)
{
    
    if (Cmd != DISABLE)
    {
        /* Enable the selected I2C interrupts */
        I2Cx->CTRL2 |= timeout_type;
    }
    else
    {
        /* Disable the selected I2C interrupts */
        I2Cx->CTRL2 &= (~timeout_type);
    }
}

/**
*\*\name    I2C_GetTimeoutFlag.
*\*\fun     Checks whether the specified I2C timeout flag is set or not.
*\*\param   I2Cx (The input parameters must be the following values):
*\*\          - I2C1
*\*\          - I2C2
*\*\param   I2C_flag (The input parameters must be the following values):
*\*\          - I2C_TIMEOUT_FLAG_SCLLOW     SCL low timeout flag
*\*\          - I2C_TIMEOUT_FLAG_SCLHIGH    SCL high timeout flag
*\*\          - I2C_TIMEOUT_FLAG_SDALOW     SDA low timeout flag
*\*\return  SET or RESET
**/
FlagStatus I2C_GetTimeoutFlag(I2C_Module* I2Cx, uint32_t I2C_flag)
{
    FlagStatus bitstatus;
	
    if ((I2Cx->STS1 & I2C_flag) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    return bitstatus;
}

/**
*\*\name    I2C_ClrTimeoutFlag.
*\*\fun     Clears the I2Cx's pending flags.
*\*\param   I2Cx (The input parameters must be the following values):
*\*\          - I2C1
*\*\          - I2C2
*\*\param   I2C_flag (The input parameters must be the following values):
*\*\          - I2C_TIMEOUT_FLAG_SCLLOW     SCL low timeout flag
*\*\          - I2C_TIMEOUT_FLAG_SCLHIGH    SCL high timeout flag
*\*\          - I2C_TIMEOUT_FLAG_SDALOW     SDA low timeout flag
*\*\return  none
**/
void I2C_ClrTimeoutFlag(I2C_Module* I2Cx, uint32_t I2C_flag)
{
    /* Clear the selected I2C flag */
    I2Cx->STS1 = (~I2C_flag)&I2C_STS1_RESERVED_MASK;
}

