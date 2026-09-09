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
*\*\file n32a052_uart.c
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/

#include "n32a052_uart.h"
#include "n32a052_rcc.h"

/**
*\*\name    UART_DeInit
*\*\fun     Reset the UARTx registers.
*\*\param   UARTx (The input parameters must be the following values):
*\*\          - UART1
*\*\          - UART2
*\*\          - UART3
*\*\          - UART4
*\*\          - UART5
*\*\return  none
**/
void UART_DeInit(UART_Module* UARTx)
{
    if (UARTx == UART1)
    {
        /* UART1 Reset */
        RCC_EnableAPB2PeriphReset(RCC_APB2_PERIPH_UART1);
    }
    else if (UARTx == UART2)
    {
        /* UART2 Reset */
        RCC_EnableAPB2PeriphReset(RCC_APB2_PERIPH_UART2);
    }
    else if (UARTx == UART3)
    {
        /* UART3 Reset */
        RCC_EnableAPB1PeriphReset(RCC_APB1_PERIPH_UART3);
    }
    else if (UARTx == UART4)
    {
        /* UART4 Reset */
        RCC_EnableAPB1PeriphReset(RCC_APB1_PERIPH_UART4);
    }
    else if (UARTx == UART5)
    {
        /* UART5 Reset */
        RCC_EnableAPB1PeriphReset(RCC_APB1_PERIPH_UART5);
    }
    else
    {
        /* no process */
    }
}

/**
*\*\name    UART_Init
*\*\fun     Initializes the UARTx peripheral according to UART_InitStruct.
*\*\param   UARTx (The input parameters must be the following values):
*\*\          - UART1
*\*\          - UART2
*\*\          - UART3
*\*\          - UART4
*\*\          - UART5
*\*\param   UART_InitStruct (The input parameters must be the following values):
*\*\          - buad_rate :
*\*\            - (((buad_rate) > 0) && ((buad_rate) < 0x003D0900))
*\*\          - WordLength
*\*\            - UART_WL_8B
*\*\            - UART_WL_9B
*\*\          - StopBits
*\*\            - UART_STPB_1
*\*\            - UART_STPB_2
*\*\          - Parity
*\*\            - UART_PE_NO
*\*\            - UART_PE_EVEN
*\*\            - UART_PE_ODD
*\*\          - Mode 
*\*\            - UART_MODE_RX
*\*\            - UART_MODE_TX
*\*\return  none
*\*\note    UART1/2 max baud rate 4000000, UART3/4/5 max baud rate 2000000
**/
void UART_Init(UART_Module* UARTx, UART_InitType* UART_InitStruct)
{
    uint32_t tmpregister, apbclock;
    uint32_t integerdivider;
    uint32_t fractionaldivider;
    uint32_t uartxbase;
	
    RCC_ClocksType RCC_ClocksStatus;

    uartxbase = (uint32_t)UARTx;

    /*---------------------------- UART CTRL2 Configuration -----------------------*/
    tmpregister = UARTx->CTRL2;
    /* Clear STPB[1:0] bits */
    tmpregister &= CTRL2_STPB_CLR_MASK;
    /* Configure the UART Stop Bits ------------*/
    /* Set STOP[13:12] bits according to StopBits value */
    tmpregister |= (uint32_t)UART_InitStruct->StopBits;

    /* Write to UART CTRL2 */
    UARTx->CTRL2 = (uint32_t)tmpregister;

    /*---------------------------- UART CTRL1 Configuration -----------------------*/
    tmpregister = UARTx->CTRL1;
    /* Clear RXEN, TXEN, PSEL, PCEN and WL bits */
    tmpregister &= UART_CTRL1_CLR_MASK;
    /* Configure the UART Word Length, Parity and mode ----------------------- */
    /* Set the WL bits according to WordLength value */
    /* Set PSEL and PCEN bits according to Parity value */
    /* Set RXEN and TXEN bits according to Mode value */
    tmpregister |= (uint32_t)UART_InitStruct->WordLength | UART_InitStruct->Parity | UART_InitStruct->Mode;
    /* Write to UART CTRL1 */
    UARTx->CTRL1 = (uint32_t)tmpregister;

    /*---------------------------- UART BRCF Configuration -----------------------*/
    /* Configure the UART Baud Rate -------------------------------------------*/
    RCC_GetClocksFreqValue(&RCC_ClocksStatus);
    if ((uartxbase == UART1_BASE)||(uartxbase == UART2_BASE))
    {
        apbclock = RCC_ClocksStatus.Pclk2Freq;
    }
    else
    {
        apbclock = RCC_ClocksStatus.Pclk1Freq;
    }

    /* Determine the integer part */
    integerdivider = (((uint32_t)25 * apbclock) / ((uint32_t)4 * (UART_InitStruct->BaudRate)));
    tmpregister = (integerdivider / (uint32_t)100) << (uint32_t)4;

    /* Determine the fractional part */
    fractionaldivider = (((((integerdivider - (100 * (tmpregister >> 4))) * 16) + 50) / 100));

    /*Determine whether the fractional part needs to carried*/
    if((fractionaldivider >> 4) == 1){
        tmpregister = ((integerdivider / 100) + 1) << 4;
    }
    
    /* Implement the fractional part in the register */
    tmpregister |= fractionaldivider & ((uint8_t)0x0F);

    /* Write to UART PBC */
    UARTx->BRCF = (uint32_t)tmpregister;
}

/**
*\*\name    UART_StructInit.
*\*\fun     Fills each UART_InitStruct member with its default value.
*\*\param   UART_InitStruct (The input parameters must be the following values):
*\*\          - BaudRate
*\*\          - WordLength
*\*\          - StopBits
*\*\          - Parity
*\*\          - Mode
*\*\return  none
**/
void UART_StructInit(UART_InitType* UART_InitStruct)
{
    /* UART_InitStruct members default value */
    UART_InitStruct->BaudRate   = (uint32_t)9600;
    UART_InitStruct->WordLength = UART_WL_8B;
    UART_InitStruct->StopBits   = UART_STPB_1;
    UART_InitStruct->Parity     = UART_PE_NO;
    UART_InitStruct->Mode       = UART_MODE_RX | UART_MODE_TX;
}

/**
*\*\name    UART_Enable.
*\*\fun     Enables the specified UART peripheral.
*\*\param   UARTx (The input parameters must be the following values):
*\*\          - UART1
*\*\          - UART2
*\*\          - UART3
*\*\          - UART4
*\*\          - UART5
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void UART_Enable(UART_Module* UARTx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected UART by setting the UE bit in the CTRL1 register */
        UARTx->CTRL1 |= CTRL1_UEN_SET;
    }
    else
    {
        /* Disable the selected UART by clearing the UE bit in the CTRL1 register */
        UARTx->CTRL1 &= CTRL1_UEN_RESET;
    }
}

/**
*\*\name    UART_ConfigInt.
*\*\fun     Enables or disables the specified UART interrupts.
*\*\param   UARTx (The input parameters must be the following values):
*\*\          - UART1
*\*\          - UART2
*\*\          - UART3
*\*\          - UART4
*\*\          - UART5
*\*\param   UART_INT (The input parameters must be the following values):
*\*\          - UART_INT_IDLEF Idle line detection interrupt
*\*\          - UART_INT_RXDNE Receive Data register not empty interrupt
*\*\          - UART_INT_TXDE  Transmit Data Register empty interrupt
*\*\          - UART_INT_TXC   Transmission complete interrupt
*\*\          - UART_INT_PEF   Parity Error interrupt
*\*\          - UART_INT_LINBD LIN Break detection interrupt
*\*\          - UART_INT_ERRF  Error interrupt(Frame error, noise error, overrun error)
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void UART_ConfigInt(UART_Module* UARTx, uint32_t UART_INT, FunctionalState Cmd)
{
    uint32_t uartreg, itpos, itmask;
    uint32_t uartxbase;

    uartxbase = (uint32_t)UARTx;

    /* Get the UART register index */
    uartreg = (uint32_t)((UART_INT & 0xFFU) >> 0x05U);

    /* Get the interrupt position */
    itpos  = UART_INT & UART_INT_MASK;
    itmask = (((uint32_t)0x01) << itpos);

    if (uartreg == UART_CTRL1_OFFSET) /* The IT is in CTRL1 register */
    {
        uartxbase += (uint32_t)0x00;
    }
    else if (uartreg == (uint32_t)UART_CTRL2_OFFSET) /* The IT is in CTRL2 register */
    {
        uartxbase += (uint32_t)0x04;
    }
    else /* The IT is in CTRL3 register */
    {
        uartxbase += (uint32_t)0x08;
    }
    if (Cmd != DISABLE)
    {
        *(__IO uint32_t*)uartxbase |= itmask;
    }
    else
    {
        *(__IO uint32_t*)uartxbase &= ~itmask;
    }
}

/**
*\*\name    UART_EnableDMA.
*\*\fun     Enables or disables the UART's DMA interface.
*\*\param   UARTx (The input parameters must be the following values):
*\*\          - UART1
*\*\          - UART2
*\*\          - UART3
*\*\          - UART4
*\*\          - UART5
*\*\param   UART_DMAReq (The input parameters must be the following values):
*\*\          - UART_DMAREQ_TX
*\*\          - UART_DMAREQ_RX
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void UART_EnableDMA(UART_Module* UARTx, uint32_t UART_DMAReq, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the DMA transfer for selected requests by setting the DMAT and/or
           DADDR bits in the UART CTRL3 register */
        UARTx->CTRL3 |= UART_DMAReq;
    }
    else
    {
        /* Disable the DMA transfer for selected requests by clearing the DMAT and/or
           DADDR bits in the UART CTRL3 register */
        UARTx->CTRL3 &= (uint32_t)(~UART_DMAReq);
    }
}

/**
*\*\name    UART_SetAddr.
*\*\fun     Sets the address of the UART node.
*\*\param   UARTx (The input parameters must be the following values):
*\*\          - UART1
*\*\          - UART2
*\*\          - UART3
*\*\          - UART4
*\*\          - UART5
*\*\param   UART_address :
*\*\          - (((UART_address)>=0x00)&&((UART_address)<=0x0F))
*\*\return  none
**/
void UART_SetAddr(UART_Module* UARTx, uint32_t UART_Addr)
{
    /* Clear the UART address */
    UARTx->CTRL2 &= CTRL2_ADDR_MASK;
    /* Set the UART address node */
    UARTx->CTRL2 |= UART_Addr;
}

/**
*\*\name    UART_ConfigWakeUpMode.
*\*\fun     Selects the UART WakeUp method.
*\*\param   UARTx (The input parameters must be the following values):
*\*\          - UART1
*\*\          - UART2
*\*\          - UART3
*\*\          - UART4
*\*\          - UART5
*\*\param   UART_WakeUpMode (The input parameters must be the following values):
*\*\          - UART_WUM_IDLELINE
*\*\          - UART_WUM_ADDRMASK
*\*\return  none
**/
void UART_ConfigWakeUpMode(UART_Module* UARTx, uint32_t UART_WakeUpMode)
{
    UARTx->CTRL1 &= CTRL1_WUM_MASK;
    UARTx->CTRL1 |= UART_WakeUpMode;
}

/**
*\*\name    UART_Receiver_Wakeup_Enable.
*\*\fun     Enable the UART mute mode.
*\*\param   UARTx (The input parameters must be the following values):
*\*\          - UART1
*\*\          - UART2
*\*\          - UART3
*\*\          - UART4
*\*\          - UART5
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void UART_EnableRcvWakeUp(UART_Module* UARTx, FunctionalState Cmd)
{
    /* Enable the UART mute mode  by setting the RWU bit in the CTRL1 register */
    UARTx->CTRL1 |= CTRL1_RCVWU_SET;
    if (Cmd != DISABLE)
    {
        /* Enable the UART mute mode  by setting the RWU bit in the CTRL1 register */
        UARTx->CTRL1 |= CTRL1_RCVWU_SET;
    }
    else
    {
        /* Disable the UART mute mode by clearing the RWU bit in the CTRL1 register */
        UARTx->CTRL1 &= CTRL1_RCVWU_RESET;
    }
}

/**
*\*\name    UART_ConfigLINBreakDetectLength.
*\*\fun     Sets the UART LIN Break detection length.
*\*\param   UARTx (The input parameters must be the following values):
*\*\          - UART1
*\*\          - UART2
*\*\          - UART3
*\*\          - UART4
*\*\          - UART5
*\*\param   UART_LINBreakDetectLength (The input parameters must be the following values):
*\*\          - UART_LINBDL_10B
*\*\          - UART_LINBDL_11B
*\*\return  none
**/
void UART_ConfigLINBreakDetectLength(UART_Module* UARTx, uint16_t UART_LINBreakDetectLength)
{
    UARTx->CTRL2 &= CTRL2_LINBDL_MASK;
    UARTx->CTRL2 |= UART_LINBreakDetectLength;
}

/**
*\*\name    UART_EnableLIN.
*\*\fun     Enables or disables the UART's LIN mode.
*\*\param   UARTx (The input parameters must be the following values):
*\*\          - UART1
*\*\          - UART2
*\*\          - UART3
*\*\          - UART4
*\*\          - UART5
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void UART_EnableLIN(UART_Module* UARTx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the LIN mode by setting the LINEN bit in the CTRL2 register */
        UARTx->CTRL2 |= CTRL2_LINMEN_SET;
    }
    else
    {
        /* Disable the LIN mode by clearing the LINEN bit in the CTRL2 register */
        UARTx->CTRL2 &= CTRL2_LINMEN_RESET;
    }
}

/**
*\*\name    UART_SendData.
*\*\fun     Transmits single data through the UARTx peripheral.
*\*\param   UARTx (The input parameters must be the following values):
*\*\          - UART1
*\*\          - UART2
*\*\          - UART3
*\*\          - UART4
*\*\          - UART5
*\*\param   Data :
*\*\          - The data to transmit.
*\*\return  none
**/
void UART_SendData(UART_Module* UARTx, uint32_t Data)
{
    /* Transmit Data */
    UARTx->DAT = (Data & 0x000001FFU);
}

/**
*\*\name    UART_ReceiveData.
*\*\fun     Returns the most recent received data by the UARTx peripheral.
*\*\param   UARTx (The input parameters must be the following values):
*\*\          - UART1
*\*\          - UART2
*\*\          - UART3
*\*\          - UART4
*\*\          - UART5
*\*\return  The received data.
**/
uint16_t UART_ReceiveData(UART_Module* UARTx)
{
    /* Receive Data */
    return (uint16_t)(UARTx->DAT & (uint32_t)0x01FF);
}

/**
*\*\name    UART_SendBreak.
*\*\fun     Transmits break characters.
*\*\param   UARTx (The input parameters must be the following values):
*\*\          - UART1
*\*\          - UART2
*\*\          - UART3
*\*\          - UART4
*\*\          - UART5
*\*\return  none
**/
void UART_SendBreak(UART_Module* UARTx)
{
    /* Send break characters */
    UARTx->CTRL1 |= CTRL1_SDBRK_SET;
}

/**
*\*\name    UART_SetPrescaler.
*\*\fun     Sets the system clock prescaler.
*\*\param   UARTx (The input parameters must be the following values):
*\*\          - UART1
*\*\          - UART2
*\*\          - UART3
*\*\          - UART4
*\*\          - UART5
*\*\param   UART_prescaler :
*\*\          - Specifies the prescaler clock.
*\*\return  none
**/
void UART_SetPrescaler(UART_Module* UARTx, uint8_t UART_prescaler)
{
    /* Clear the UART prescaler */
    UARTx->GTP &= GTP_MSB_MASK;
    /* Set the UART prescaler */
    UARTx->GTP |= UART_prescaler;
}

/**
*\*\name    UART_EnableHalfDuplex.
*\*\fun     Enables or disables the UART's Half Duplex communication.
*\*\param   UARTx (The input parameters must be the following values):
*\*\          - UART1
*\*\          - UART2
*\*\          - UART3
*\*\          - UART4
*\*\          - UART5
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void UART_EnableHalfDuplex(UART_Module* UARTx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the Half-Duplex mode by setting the HDMEN bit in the CTRL3 register */
        UARTx->CTRL3 |= CTRL3_HDMEN_SET;
    }
    else
    {
        /* Disable the Half-Duplex mode by clearing the HDMEN bit in the CTRL3 register */
        UARTx->CTRL3 &= CTRL3_HDMEN_RESET;
    }
}

/**
*\*\name    UART_ConfigIrDAMode.
*\*\fun     Configures the UART's IrDA interface.
*\*\param   UARTx (The input parameters must be the following values):
*\*\          - UART1
*\*\          - UART2
*\*\          - UART3
*\*\          - UART4
*\*\          - UART5
*\*\param   UART_IrDAMode (The input parameters must be the following values):
*\*\          - UART_IRDAMODE_LOWPPWER
*\*\          - UART_IRDAMODE_NORMAL
*\*\return  none
**/
void UART_ConfigIrDAMode(UART_Module* UARTx, uint32_t UART_IrDAMode)
{
    UARTx->CTRL3 &= CTRL3_IRDALP_MASK;
    UARTx->CTRL3 |= UART_IrDAMode;
}

/**
*\*\name    UART_EnableIrDA.
*\*\fun     Enables the UART's IrDA interface.
*\*\param   UARTx (The input parameters must be the following values):
*\*\          - UART1
*\*\          - UART2
*\*\          - UART3
*\*\          - UART4
*\*\          - UART5
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void UART_EnableIrDA(UART_Module* UARTx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the IrDA mode by setting the IRDAMEN bit in the CTRL3 register */
        UARTx->CTRL3 |= CTRL3_IRDAMEN_SET;
    }
    else
    {
        /* Disable the IrDA mode by clearing the IRDAMEN bit in the CTRL3 register */
        UARTx->CTRL3 &= CTRL3_IRDAMEN_RESET;
    }
}

/**
*\*\name    UART_GetFlagStatus.
*\*\fun     Checks whether the specified UART flag is set or not.
*\*\param   UARTx (The input parameters must be the following values):
*\*\          - UART1
*\*\          - UART2
*\*\          - UART3
*\*\          - UART4
*\*\          - UART5
*\*\param   UART_FLAG (The input parameters must be the following values):
*\*\          - UART_FLAG_TXDE
*\*\          - UART_FLAG_TXC
*\*\          - UART_FLAG_RXDNE
*\*\          - UART_FLAG_LINBD
*\*\          - UART_FLAG_IDLEF
*\*\          - UART_FLAG_OREF
*\*\          - UART_FLAG_NEF
*\*\          - UART_FLAG_FEF
*\*\          - UART_FLAG_PEF
*\*\return  SET or RESET
**/
FlagStatus UART_GetFlagStatus(UART_Module* UARTx, uint32_t UART_FLAG)
{
    FlagStatus bitstatus;
	
    if ((UARTx->STS & UART_FLAG) != (uint32_t)RESET)
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
*\*\name    UART_ClrFlag.
*\*\fun     Clears the UARTx's pending flags.
*\*\param   UARTx (The input parameters must be the following values):
*\*\          - UART1
*\*\          - UART2
*\*\          - UART3
*\*\          - UART4
*\*\          - UART5
*\*\param   UART_FLAG (The input parameters must be the following values):
*\*\          - UART_FLAG_TXC
*\*\          - UART_FLAG_RXDNE
*\*\          - UART_FLAG_LINBD
*\*\return  none
*\*\note
*\*\          - PE (Parity error), FE (Framing error), NE (Noise error), ORE (OverRun
*\*\            error) and IDLE (Idle line detected) flags are cleared by software
*\*\            sequence: a read operation to UART_STS register (UART_GetFlagStatus())
*\*\            followed by a read operation to UART_DAT register (UART_ReceiveData()).
*\*\          - RXNE flag can be also cleared by a read to the UART_DAT register
*\*\            (UART_ReceiveData()).
*\*\          - TC flag can be also cleared by software sequence: a read operation to
*\*\            UART_STS register (UART_GetFlagStatus()) followed by a write operation
*\*\            to UART_DAT register (UART_SendData()).
*\*\          - TXE flag is cleared only by a write to the UART_DAT register
*\*\            (UART_SendData()).
**/
void UART_ClrFlag(UART_Module* UARTx, uint32_t UART_FLAG)
{
    UARTx->STS = (~UART_FLAG)&UART_STS_RESERVED_MASK;
}

/**
*\*\name    UART_GetIntStatus.
*\*\fun     Checks whether the specified UART interrupt has occurred or not.
*\*\param   UARTx (The input parameters must be the following values):
*\*\          - UART1
*\*\          - UART2
*\*\          - UART3
*\*\          - UART4
*\*\          - UART5
*\*\param   UART_INT (The input parameters must be the following values):
*\*\          - UART_INT_IDLEF
*\*\          - UART_INT_TXDE
*\*\          - UART_INT_TXC
*\*\          - UART_INT_RXDNE
*\*\          - UART_INT_LINBD
*\*\          - UART_INT_PEF
*\*\          - UART_INT_OREF
*\*\          - UART_INT_NEF
*\*\          - UART_INT_FEF
*\*\return  SET or RESET
**/
INTStatus UART_GetIntStatus(UART_Module* UARTx, uint32_t UART_INT)
{
    uint32_t bitpos, itmask, uartreg;
    INTStatus bitstatus;

    /* Get the UART register index */
    uartreg = (uint32_t)((UART_INT & 0xFFU) >> UART_INTREG_OFFSET);
    /* Get the interrupt position */
    itmask = UART_INT & (uint32_t)UART_INT_MASK;
    itmask = UART_REGBIT0_OFFSET << itmask;

    if (uartreg == UART_CTRL1_OFFSET) /* The IT  is in CTRL1 register */
    {
        itmask &= UARTx->CTRL1;
    }
    else if (uartreg == UART_CTRL2_OFFSET) /* The IT  is in CTRL2 register */
    {
        itmask &= UARTx->CTRL2;
    }
    else /* The IT  is in CTRL3 register */
    {
        itmask &= UARTx->CTRL3;
    }

    bitpos = UART_INT >> UART_INTSTS_OFFSET;
    bitpos = UART_REGBIT0_OFFSET << bitpos;
    bitpos &= UARTx->STS;
    if ((itmask != (uint32_t)RESET) && (bitpos != (uint32_t)RESET))
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
*\*\name    UART_ClrIntPendingBit.
*\*\fun     Clears the UARTx's interrupt Status.
*\*\param   UARTx (The input parameters must be the following values):
*\*\          - UART1
*\*\          - UART2
*\*\          - UART3
*\*\          - UART4
*\*\          - UART5
*\*\param   UART_INT (The input parameters must be the following values):
*\*\          - UART_INT_TXC
*\*\          - UART_INT_RXDNE
*\*\          - UART_INT_LINBD
*\*\return  none
**/
void UART_ClrIntPendingBit(UART_Module* UARTx, uint32_t UART_INT)
{
    uint32_t bitpos, itmask;

    bitpos = UART_INT >> UART_INTSTS_OFFSET;
    itmask = UART_REGBIT0_OFFSET << bitpos;
    UARTx->STS = (uint32_t)(~itmask);
}


