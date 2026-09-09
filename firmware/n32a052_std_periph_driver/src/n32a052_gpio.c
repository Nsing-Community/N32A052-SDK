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
*\*\file n32a052_gpio.c
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/

#include "n32a052_gpio.h"
#include "n32a052_rcc.h"

#define GPIO_MODE                       ((uint32_t)0x00000003)
#define EXTI_MODE                       ((uint32_t)0x10000000)
#define GPIO_MODE_IT                    ((uint32_t)0x00010000)
#define GPIO_MODE_EVT                   ((uint32_t)0x00020000)
#define RISING_EDGE                     ((uint32_t)0x00100000) 
#define FALLING_EDGE                    ((uint32_t)0x00200000)
#define GPIO_OUTPUT_TYPE                ((uint32_t)0x00000010)


/**
 *\*\name   GPIO_DeInit.
 *\*\fun    Reset the GPIOx peripheral registers to their default reset values.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\return none
 */
void GPIO_DeInit(GPIO_Module* GPIOx)
{
    if (GPIOx == GPIOA)
    {
        RCC_EnableAPB2PeriphReset(RCC_APB2_PERIPH_GPIOA);
    }
    else if (GPIOx == GPIOB)
    {
        RCC_EnableAPB2PeriphReset(RCC_APB2_PERIPH_GPIOB);
    }
    else if (GPIOx == GPIOC)
    {
        RCC_EnableAPB2PeriphReset(RCC_APB2_PERIPH_GPIOC);
    }
    else if (GPIOx == GPIOD)
    {
        RCC_EnableAPB2PeriphReset(RCC_APB2_PERIPH_GPIOD);
    }
    else
    {
        /* NOP process */
    }
}

/**
 *\*\name   GPIO_DeInitPin.
 *\*\fun    Deinitializes the GPIOx peripheral registers to their default reset values.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\param  Pin :
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\          - GPIO_PIN_ALL
 *\*\return none
 */
void GPIO_DeInitPin(GPIO_Module* GPIOx, uint32_t Pin)
{
    uint32_t pos = 0x00U, currentpin;
    uint32_t tmpregister; 

    while((Pin >> pos) != 0)
    {
        /* Get the IO position */
        currentpin = (Pin) & ((uint32_t)1U << pos);

        if(currentpin > 0)
        {
            /*------------------------- GPIO Mode Configuration --------------------*/
            /* Configure IO Direction in Analog Mode */
            GPIOx->PMODE |= (GPIO_PMODE0 << (pos * 2U));

            /* Configure the default value IO Output Type */
            GPIOx->POTYPE &= ~(GPIO_POTYPE_POT0 << pos);

            /* Deactivate the Pull-up and Pull-down resistor for the current IO */
            GPIOx->PUPD &= ~(GPIO_PUPD0 << (pos * 2U));
            
            /* Configure the default value IO Output */
            GPIOx->POD &= ~(GPIO_POD_POD0 << pos);
            
            /* Configure the default value for IO Speed */
            GPIOx->SR |= ((uint32_t)GPIO_SR_SR0 << pos);

            /* Configure the default value for IO Driver */
            GPIOx->DS &= ~(GPIO_DS_DS0 << pos);

             /* Configure the default Alternate Function in current IO */ 
            if((pos & (uint8_t)0x08) > 0)
            {
                if((GPIOx == GPIOA) && ((pos == 13) || (pos == 14)))
                {
                    /* Configure IO Direction in Alternate Mode */
                    GPIOx->PMODE &= ~(GPIO_PMODE0_3 << (pos * 2U));
                    GPIOx->PMODE |= (GPIO_AF_MODE << (pos * 2U));

                    if(pos==13)
                    {
                        /* Deactivate the Pull-up and Pull-down resistor for the current IO */
                        GPIOx->PUPD |= (GPIO_PU_MODE << (pos * 2U));
                    }
                    else
                    {
                        /* Deactivate the Pull-up and Pull-down resistor for the current IO */
                        GPIOx->PUPD |= (GPIO_PD_MODE << (pos * 2U));
                    }

                    GPIOx->AFH &= ~((0x0FUL) << ((pos & 0x07U) * 4U)); 
                }
                else
                {
                    GPIOx->AFH |= ((0x0FUL) << ((pos & 0x07U) * 4U));
                } 
            }
            else
            {
                GPIOx->AFL |= ((0x0FUL) << ((pos & 0x07U) * 4U));
            }

            /*------------------------- EXTI Mode Configuration --------------------*/
            /* Clear the External Interrupt or Event for the current IO */
            tmpregister = AFIO->EXTI_CFG[pos >> 2U];
            tmpregister &= ((0x0FUL) << ((pos & 0x03U) * 4U));
            if(tmpregister == ((uint32_t)GPIO_GET_INDEX(GPIOx) << ((pos & 0x03U) * 4U)))
            {
                AFIO->EXTI_CFG[pos >> 2U] &= ~((0x0FUL) << ((pos & 0x03U) * 4U));

                /* Clear EXTI line configuration */
                EXTI->IMASK &= ~((uint32_t)currentpin);
                EXTI->EMASK &= ~((uint32_t)currentpin);

                /* Clear Rising Falling edge configuration */
                EXTI->RT_CFG &= ~((uint32_t)currentpin);
                EXTI->FT_CFG &= ~((uint32_t)currentpin);
            }
        } 
        pos++;
    }
}

/**
 *\*\name   GPIO_AFIOInitDefault.
 *\*\fun    Reset the AFIO peripheral registers to their default reset values.
 *\*\param  none
 *\*\return none
 */
void GPIO_AFIOInitDefault(void)
{
    RCC_EnableAPB2PeriphReset(RCC_APB2_PERIPH_AFIO);
}


/**
 *\*\name   GPIO_InitPeripheral.
 *\*\fun    Initialize the GPIOx peripheral with the value of the GPIO_InitStruct structure.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\param  GPIO_InitStructure :
 *\*\            - pin
 *\*\               - GPIO_PIN_0
 *\*\               - GPIO_PIN_1
 *\*\               - GPIO_PIN_2
 *\*\               - GPIO_PIN_3
 *\*\               - GPIO_PIN_4
 *\*\               - GPIO_PIN_5
 *\*\               - GPIO_PIN_6
 *\*\               - GPIO_PIN_7
 *\*\               - GPIO_PIN_8
 *\*\               - GPIO_PIN_9
 *\*\               - GPIO_PIN_10
 *\*\               - GPIO_PIN_11
 *\*\               - GPIO_PIN_12
 *\*\               - GPIO_PIN_13
 *\*\               - GPIO_PIN_14
 *\*\               - GPIO_PIN_15
 *\*\               - GPIO_PIN_ALL
 *\*\            - GPIO_Mode
 *\*\               - GPIO_MODE_INPUT
 *\*\               - GPIO_MODE_OUTPUT_PP
 *\*\               - GPIO_MODE_OUTPUT_OD
 *\*\               - GPIO_MODE_AF_PP
 *\*\               - GPIO_MODE_AF_OD
 *\*\               - GPIO_MODE_ANALOG
 *\*\            - GPIO_Pull
 *\*\               - GPIO_NO_PULL
 *\*\               - GPIO_PULL_UP
 *\*\               - GPIO_PULL_DOWN
 *\*\            - GPIO_Slew_Rate
 *\*\               - GPIO_SLEW_RATE_FAST
 *\*\               - GPIO_SLEW_RATE_SLOW
 *\*\            - GPIO_Current
 *\*\               - GPIO_HIGH_DREIVE
 *\*\               - GPIO_LOW_DREIVE
 *\*\            - GPIO_Alternate
 *\*\               - GPIO_AF0_SWDIO        SWDIO Alternate Function mapping
 *\*\               - GPIO_AF0_SWCLK        SWCLK Alternate Function mapping
 *\*\               - GPIO_AF0_TIM1         TIM1 Alternate Function mapping 
 *\*\               - GPIO_AF0_TIM3         TIM3 Alternate Function mapping 
 *\*\               - GPIO_AF0_SPI1         SPI1 Alternate Function mapping 
 *\*\               - GPIO_AF0_SPI2         SPI2 Alternate Function mapping 
 *\*\               - GPIO_AF0_SPI3         SPI3 Alternate Function mapping 
 *\*\               - GPIO_AF0_RCI1         RCI1 Alternate Function mapping 
 *\*\               - GPIO_AF0_I2C2         I2C2 Alternate Function mapping 
 *\*\               - GPIO_AF1_TIM1         TIM1 Alternate Function mapping
 *\*\               - GPIO_AF1_TIM2         TIM2 Alternate Function mapping
 *\*\               - GPIO_AF1_TIM3         TIM3 Alternate Function mapping
 *\*\               - GPIO_AF1_TIM4         TIM4 Alternate Function mapping
 *\*\               - GPIO_AF1_TIM5         TIM5 Alternate Function mapping
 *\*\               - GPIO_AF1_I2C1         I2C1 Alternate Function mapping
 *\*\               - GPIO_AF1_SPI1         SPI1 Alternate Function mapping
 *\*\               - GPIO_AF1_SPI2         SPI2 Alternate Function mapping
 *\*\               - GPIO_AF1_RCI2         RCI2 Alternate Function mapping
 *\*\               - GPIO_AF2_UART1        UART1 Alternate Function mapping    
 *\*\               - GPIO_AF2_UART2        UART2 Alternate Function mapping    
 *\*\               - GPIO_AF2_TIM1         TIM1 Alternate Function mapping     
 *\*\               - GPIO_AF2_TIM2         TIM2 Alternate Function mapping     
 *\*\               - GPIO_AF2_TIM3         TIM3 Alternate Function mapping     
 *\*\               - GPIO_AF2_TIM4         TIM4 Alternate Function mapping     
 *\*\               - GPIO_AF2_TIM5         TIM5 Alternate Function mapping     
 *\*\               - GPIO_AF2_I2C2         I2C2 Alternate Function mapping     
 *\*\               - GPIO_AF2_RCI2         RCI2 Alternate Function mapping     
 *\*\               - GPIO_AF3_EVENTOUT     EVENTOUT Alternate Function mapping 
 *\*\               - GPIO_AF3_TIM1         TIM1 Alternate Function mapping     
 *\*\               - GPIO_AF3_TIM4         TIM4 Alternate Function mapping     
 *\*\               - GPIO_AF3_TIM5         TIM5 Alternate Function mapping     
 *\*\               - GPIO_AF3_SPI3         SPI3 Alternate Function mapping     
 *\*\               - GPIO_AF3_I2C2         I2C2 Alternate Function mapping     
 *\*\               - GPIO_AF3_RTC          RTC  Alternate Function mapping     
 *\*\               - GPIO_AF3_UART2        UART2 Alternate Function mapping    
 *\*\               - GPIO_AF4_TIM1         TIM1 Alternate Function mapping      
 *\*\               - GPIO_AF4_TIM2         TIM2 Alternate Function mapping     
 *\*\               - GPIO_AF4_TIM3         TIM3 Alternate Function mapping     
 *\*\               - GPIO_AF4_TIM4         TIM4 Alternate Function mapping     
 *\*\               - GPIO_AF4_TIM5         TIM5 Alternate Function mapping     
 *\*\               - GPIO_AF4_SPI2         SPI2 Alternate Function mapping     
 *\*\               - GPIO_AF4_SPI3         SPI3 Alternate Function mapping     
 *\*\               - GPIO_AF4_UART1        UART1 Alternate Function mapping    
 *\*\               - GPIO_AF4_UART2        UART2 Alternate Function mapping    
 *\*\               - GPIO_AF4_UART3        UART3 Alternate Function mapping    
 *\*\               - GPIO_AF4_UART4        UART4 Alternate Function mapping    
 *\*\               - GPIO_AF4_UART5        UART5 Alternate Function mapping    
 *\*\               - GPIO_AF4_I2C2         I2C2 Alternate Function mapping     
 *\*\               - GPIO_AF4_CAN          CAN  Alternate Function mapping     
 *\*\               - GPIO_AF4_COMP4        COMP4 Alternate Function mapping    
 *\*\               - GPIO_AF4_RTC          RTC Alternate Function mapping      
 *\*\               - GPIO_AF4_EVENTOUT     EVENTOUT Alternate Function mapping 
 *\*\               - GPIO_AF5_UART1        UART1 Alternate Function mapping    
 *\*\               - GPIO_AF5_UART3        UART3 Alternate Function mapping    
 *\*\               - GPIO_AF5_UART4        UART4 Alternate Function mapping    
 *\*\               - GPIO_AF5_UART5        UART5 Alternate Function mapping    
 *\*\               - GPIO_AF5_TIM1         TIM1 Alternate Function mapping     
 *\*\               - GPIO_AF5_TIM5         TIM5 Alternate Function mapping     
 *\*\               - GPIO_AF5_SPI1         SPI1 Alternate Function mapping     
 *\*\               - GPIO_AF5_SPI2         SPI2 Alternate Function mapping     
 *\*\               - GPIO_AF5_SPI3         SPI3 Alternate Function mapping     
 *\*\               - GPIO_AF5_RCI1         RCI1 Alternate Function mapping     
 *\*\               - GPIO_AF5_COMP1        COMP1 Alternate Function mapping    
 *\*\               - GPIO_AF5_COMP3        COMP3 Alternate Function mapping    
 *\*\               - GPIO_AF5_COMP4        COMP4 Alternate Function mapping    
 *\*\               - GPIO_AF5_I2C2         I2C2  Alternate Function mapping    
 *\*\               - GPIO_AF6_I2C2         I2C2 Alternate Function mapping     
 *\*\               - GPIO_AF6_I2C1         I2C1 Alternate Function mapping     
 *\*\               - GPIO_AF6_UART2        UART2 Alternate Function mapping    
 *\*\               - GPIO_AF6_UART3        UART3 Alternate Function mapping    
 *\*\               - GPIO_AF6_UART5        UART5 Alternate Function mapping    
 *\*\               - GPIO_AF6_MCO          MCO Alternate Function mapping      
 *\*\               - GPIO_AF6_SPI3         SPI3  Alternate Function mapping    
 *\*\               - GPIO_AF6_COMP2        COMP2 Alternate Function mapping    
 *\*\               - GPIO_AF6_RCI1         RCI1 Alternate Function mapping     
 *\*\               - GPIO_AF6_BEEPER       BEEPER Alternate Function mapping   
 *\*\               - GPIO_AF7_BEEPER       BEEPER Alternate Function mapping   
 *\*\               - GPIO_AF7_I2C1         I2C1 Alternate Function mapping     
 *\*\               - GPIO_AF7_I2C2         I2C2 Alternate Function mapping     
 *\*\               - GPIO_AF7_UART4        UART4 Alternate Function mapping    
 *\*\               - GPIO_AF7_RTC          RTC  Alternate Function mapping     
 *\*\               - GPIO_AF7_CAN          CAN  Alternate Function mapping     
 *\*\               - GPIO_AF7_TIM1         TIM1 Alternate Function mapping     
 *\*\               - GPIO_AF7_RCI2         RCI2 Alternate Function mapping     
 *\*\               - GPIO_AF8_SPI3         SPI3 Alternate Function mapping     
 *\*\               - GPIO_AF8_I2C1         I2C1 Alternate Function mapping     
 *\*\               - GPIO_AF8_RCI2         RCI2 Alternate Function mapping     
 *\*\               - GPIO_AF8_UART4        UART4 Alternate Function mapping    
 *\*\               - GPIO_AF8_UART5        UART5 Alternate Function mapping    
 *\*\               - GPIO_AF8_CAN          CAN   Alternate Function mapping    
 *\*\               - GPIO_AF8_COMP1        COMP1 Alternate Function mapping    
 *\*\               - GPIO_AF8_COMP3        COMP3 Alternate Function mapping    
 *\*\               - GPIO_AF8_COMP4        COMP4 Alternate Function mapping    
 *\*\               - GPIO_AF9_COMP2        COMP2 Alternate Function mapping    
 *\*\               - GPIO_AF9_COMP3        COMP3 Alternate Function mapping    
 *\*\               - GPIO_AF9_RCI2         RCI2 Alternate Function mapping     
 *\*\               - GPIO_AF10_RCI2        RCI2 Alternate Function mapping    
 *\*\               - GPIO_NO_AF            NO alternate Function mapping
 *\*\return none
 */
void GPIO_InitPeripheral(GPIO_Module* GPIOx, GPIO_InitType * GPIO_InitStruct)
{
    uint32_t pos = 0x00U, currentpin;
    uint32_t tmpregister; 

    while(((GPIO_InitStruct->Pin) >> pos) != 0)
    {
        /* Get the IO position */
        currentpin = (GPIO_InitStruct->Pin) & ((uint32_t)1U << pos);

        if(currentpin > 0)
        {
            /*--------------------- GPIO Mode Configuration ------------------------*/
            /* In case of Alternate function mode selection */
            if((GPIO_InitStruct->GPIO_Mode == GPIO_MODE_AF_PP) || (GPIO_InitStruct->GPIO_Mode == GPIO_MODE_AF_OD) || ((GPIO_InitStruct->GPIO_Mode == GPIO_MODE_ANALOG) && (GPIO_InitStruct->GPIO_Alternate != GPIO_NO_AF)))
            {
                /* Configure Alternate function mapped with the current IO */
                if((pos & (uint8_t)0x08) > 0)
                {
                    tmpregister = GPIOx->AFH;
                    tmpregister &= ~((uint32_t)0xF << ((uint32_t)(pos & (uint32_t)0x07) * 4U));
                    tmpregister |= ((uint32_t)(GPIO_InitStruct->GPIO_Alternate) << ((uint32_t)(pos & (uint32_t)0x07) * 4U)) ;
                    GPIOx->AFH = tmpregister;
                }
                else
                {
                    tmpregister = GPIOx->AFL;
                    tmpregister &= ~((uint32_t)0xF << ((uint32_t)(pos & (uint32_t)0x07) * 4U)) ;
                    tmpregister |= ((uint32_t)(GPIO_InitStruct->GPIO_Alternate) << ((uint32_t)(pos & (uint32_t)0x07) * 4U)) ;
                    GPIOx->AFL = tmpregister;
                }
            }

            /* In case of Output or Alternate function mode selection */
            if ((GPIO_InitStruct->GPIO_Mode == GPIO_MODE_OUTPUT_PP) || (GPIO_InitStruct->GPIO_Mode == GPIO_MODE_OUTPUT_OD)
                 ||(GPIO_InitStruct->GPIO_Mode == GPIO_MODE_AF_PP) || (GPIO_InitStruct->GPIO_Mode == GPIO_MODE_AF_OD))
            {
                /* Configure the IO Output Type */
                tmpregister = GPIOx->POTYPE;
                tmpregister &= ~(GPIO_POTYPE_POT0 << pos);
                tmpregister |= (((GPIO_InitStruct->GPIO_Mode >> 4U) & 0x01U) << pos);
                GPIOx->POTYPE = tmpregister;
            }

            /*---------------------------- GPIO Mode Configuration -----------------------*/
            /* Configure IO Direction mode (Input, Output, Alternate or Analog) */
            tmpregister = GPIOx->PMODE;
            tmpregister &= ~(GPIO_PMODE0 << (pos * 2U));
            tmpregister |= (((GPIO_InitStruct->GPIO_Mode & 0x03U) << (pos * 2U)));
            GPIOx->PMODE = tmpregister;

            /* Configure pull-down mode */
            tmpregister = GPIOx->PUPD;
            tmpregister &= ~(GPIO_PUPD0 << (pos * 2U));
            tmpregister |= (GPIO_InitStruct->GPIO_Pull << (pos * 2U));
            GPIOx->PUPD = tmpregister;

            /* Configure slew rate */
            tmpregister = GPIOx->SR;
            tmpregister &= ~(GPIO_SR_SR0 << pos);
            tmpregister |= (GPIO_InitStruct->GPIO_Slew_Rate << pos);
            GPIOx->SR = tmpregister;

            /* Configure driver current */
            tmpregister = GPIOx->DS;
            tmpregister &= ~(GPIO_DS_DS0 << pos);
            tmpregister |= (GPIO_InitStruct->GPIO_Current << pos);
            GPIOx->DS = tmpregister;
        }
        pos++;      
    }
}


/**
 *\*\name   GPIO_InitStruct.
 *\*\fun    Assign default values to each GPIO_InitStruct member.
 *\*\param  GPIO_InitStructure :
 *\*\           pointer to GPIO_InitType structure.
 *\*\return none
 */
void GPIO_InitStruct(GPIO_InitType* GPIO_InitStructer)
{
    /* Reset GPIO structure member */
    GPIO_InitStructer->Pin            = GPIO_PIN_ALL;
    GPIO_InitStructer->GPIO_Slew_Rate = GPIO_SLEW_RATE_FAST;
    GPIO_InitStructer->GPIO_Mode      = GPIO_MODE_INPUT;
    GPIO_InitStructer->GPIO_Alternate = GPIO_NO_AF;
    GPIO_InitStructer->GPIO_Pull      = GPIO_NO_PULL;
    GPIO_InitStructer->GPIO_Current   = GPIO_LOW_DREIVE;
}

/**
 *\*\name   GPIO_ReadInputDataBit.
 *\*\fun    Get the pin status on the specified input port.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\param  Pin :
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\return the pin state on the input port.
 */
uint8_t GPIO_ReadInputDataBit(GPIO_Module* GPIOx, uint16_t Pin)
{
    uint8_t bitstatus;

    if ((GPIOx->PID & Pin) != (uint32_t)Bit_RESET)
    {
        bitstatus = (uint8_t)Bit_SET;
    }
    else
    {
        bitstatus = (uint8_t)Bit_RESET;
    }
    return bitstatus;
}

/**
 *\*\name   GPIO_ReadInputData.
 *\*\fun    Get the input data on the designated GPIO port.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\return the data value on the GPIO input port.
 */
uint16_t GPIO_ReadInputData(GPIO_Module* GPIOx)
{
    return ((uint16_t)GPIOx->PID);
}


/**
 *\*\name   GPIO_ReadOutputDataBit.
 *\*\fun    Get the pin status on the specified output port.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\param  Pin :
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\return the pin state on the output port.
 */
uint8_t GPIO_ReadOutputDataBit(GPIO_Module* GPIOx, uint16_t Pin)
{
    uint8_t bitstatus;

    if ((GPIOx->POD & Pin) != (uint32_t)Bit_RESET)
    {
        bitstatus = (uint8_t)Bit_SET;
    }
    else
    {
        bitstatus = (uint8_t)Bit_RESET;
    }
    return bitstatus;
}


/**
 *\*\name   GPIO_ReadOutputData.
 *\*\fun    Get the output data on the designated GPIO port.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\return the data value on the GPIO output port.
 */
uint16_t GPIO_ReadOutputData(GPIO_Module* GPIOx)
{
    return ((uint16_t)GPIOx->POD);
}


/**
 *\*\name   GPIO_SetBits.
 *\*\fun    Sets the selected data port bits.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\param  Pin :
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\return none
 */
void GPIO_SetBits(GPIO_Module* GPIOx, uint16_t Pin)
{
    GPIOx->PBSC = Pin;
}

/**
 *\*\name   GPIO_ResetBits.
 *\*\fun    Reset the selected data port bits.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\param  Pin :
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\return none
 */
void GPIO_ResetBits(GPIO_Module* GPIOx, uint16_t Pin)
{
    GPIOx->PBC = Pin;
}

/**
 *\*\name   GPIO_WriteBit.
 *\*\fun    Reset the selected data port bits.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\param  Pin :
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
  *\*\param  BitCmd :
 *\*\          - Bit_RESET
 *\*\          - Bit_SET
 *\*\return none
 */
void GPIO_WriteBit(GPIO_Module* GPIOx, uint16_t Pin, Bit_OperateType BitCmd)
{
    if (BitCmd != Bit_RESET)
    {
        GPIOx->PBSC = Pin;
    }
    else
    {
        GPIOx->PBC = Pin;
    }
}

/**
 *\*\name   GPIO_Write.
 *\*\fun    Write data on the designated GPIO data port.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\param  data_value :
 *\*\          the value to be written to the port output data register.
 *\*\          - 0~0xFFFF
 *\*\return none
 */
void GPIO_Write(GPIO_Module* GPIOx, uint16_t data_value)
{
    GPIOx->POD = data_value;
}

/**
 *\*\name   GPIO_TogglePin.
 *\*\fun    Toggle the specified port pin level.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\param  Pin :
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\return none
 */
void GPIO_TogglePin(GPIO_Module *GPIOx, uint16_t Pin)
{
    GPIOx->POD ^= Pin;
}


/**
 *\*\name   GPIO_ConfigPinLock.
 *\*\fun    GPIO port lock register configuration.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\param  Pin :
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\return none
 */
void GPIO_ConfigPinLock(GPIO_Module* GPIOx, uint16_t Pin)
{
    uint32_t tmp = 0x00010000;

    tmp |= Pin;
    /* Set LCKK bit */
    GPIOx->PLOCK = tmp;
    /* Reset LCKK bit */
    GPIOx->PLOCK = Pin;
    /* Set LCKK bit */
    GPIOx->PLOCK = tmp;
    /* Read LCKK bit*/
    GPIOx->PLOCK;
    /* Read LCKK bit*/
    GPIOx->PLOCK;
}


/**
 *\*\name   GPIO_ConfigEXTILine.
 *\*\fun    Selects the GPIO pin used as EXTI Line. A single EXTI line can only be configured with a single pin.
 *\*\param  PortSource :
 *\*\          - GPIOA_PORT_SOURCE
 *\*\          - GPIOB_PORT_SOURCE
 *\*\          - GPIOC_PORT_SOURCE
 *\*\          - GPIOD_PORT_SOURCE
 *\*\param  PinSource :
 *\*\          - GPIO_PIN_SOURCE0
 *\*\          - GPIO_PIN_SOURCE1
 *\*\          - GPIO_PIN_SOURCE2
 *\*\          - GPIO_PIN_SOURCE3
 *\*\          - GPIO_PIN_SOURCE4
 *\*\          - GPIO_PIN_SOURCE5
 *\*\          - GPIO_PIN_SOURCE6
 *\*\          - GPIO_PIN_SOURCE7
 *\*\          - GPIO_PIN_SOURCE8
 *\*\          - GPIO_PIN_SOURCE9
 *\*\          - GPIO_PIN_SOURCE10
 *\*\          - GPIO_PIN_SOURCE11
 *\*\          - GPIO_PIN_SOURCE12
 *\*\          - GPIO_PIN_SOURCE13
 *\*\          - GPIO_PIN_SOURCE14
 *\*\          - GPIO_PIN_SOURCE15
 *\*\return none
 */
void GPIO_ConfigEXTILine(uint8_t PortSource, uint8_t PinSource)
{
    uint32_t port = (uint32_t)1<<(PortSource);

    AFIO->EXTI_CFG[(PinSource >> 0x02)] |= (port << ((PinSource & 0x03U) * 4U));
}

/**
 *\*\name   GPIO_ClearEXTILine.
 *\*\fun    Clear the GPIO pin used as EXTI Line.
 *\*\param  PinSource :
 *\*\          - GPIO_PIN_SOURCE0
 *\*\          - GPIO_PIN_SOURCE1
 *\*\          - GPIO_PIN_SOURCE2
 *\*\          - GPIO_PIN_SOURCE3
 *\*\          - GPIO_PIN_SOURCE4
 *\*\          - GPIO_PIN_SOURCE5
 *\*\          - GPIO_PIN_SOURCE6
 *\*\          - GPIO_PIN_SOURCE7
 *\*\          - GPIO_PIN_SOURCE8
 *\*\          - GPIO_PIN_SOURCE9
 *\*\          - GPIO_PIN_SOURCE10
 *\*\          - GPIO_PIN_SOURCE11
 *\*\          - GPIO_PIN_SOURCE12
 *\*\          - GPIO_PIN_SOURCE13
 *\*\          - GPIO_PIN_SOURCE14
 *\*\          - GPIO_PIN_SOURCE15
 *\*\return none
 */
void GPIO_ClearEXTILine( uint8_t PinSource)
{
    AFIO->EXTI_CFG[(PinSource >> 0x02)] &= ~(0x0FUL << ((PinSource & 0x03U) * 4U));
}

/**
 *\*\name   GPIO_ConfigPinRemap.
 *\*\fun    Pin remapping configuration.
 *\*\param  PortSource :
 *\*\          - GPIOA_PORT_SOURCE
 *\*\          - GPIOB_PORT_SOURCE
 *\*\          - GPIOC_PORT_SOURCE
 *\*\          - GPIOD_PORT_SOURCE
 *\*\param  PinSource :
 *\*\          - GPIO_PIN_SOURCE0
 *\*\          - GPIO_PIN_SOURCE1
 *\*\          - GPIO_PIN_SOURCE2
 *\*\          - GPIO_PIN_SOURCE3
 *\*\          - GPIO_PIN_SOURCE4
 *\*\          - GPIO_PIN_SOURCE5
 *\*\          - GPIO_PIN_SOURCE6
 *\*\          - GPIO_PIN_SOURCE7
 *\*\          - GPIO_PIN_SOURCE8
 *\*\          - GPIO_PIN_SOURCE9
 *\*\          - GPIO_PIN_SOURCE10
 *\*\          - GPIO_PIN_SOURCE11
 *\*\          - GPIO_PIN_SOURCE12
 *\*\          - GPIO_PIN_SOURCE13
 *\*\          - GPIO_PIN_SOURCE14
 *\*\          - GPIO_PIN_SOURCE15
 *\*\param  AlternateFunction :
 *\*\          - GPIO_AF0_SWDIO        SWDIO Alternate Function mapping
 *\*\          - GPIO_AF0_SWCLK        SWCLK Alternate Function mapping
 *\*\          - GPIO_AF0_TIM1         TIM1 Alternate Function mapping 
 *\*\          - GPIO_AF0_TIM3         TIM3 Alternate Function mapping 
 *\*\          - GPIO_AF0_SPI1         SPI1 Alternate Function mapping 
 *\*\          - GPIO_AF0_SPI2         SPI2 Alternate Function mapping 
 *\*\          - GPIO_AF0_SPI3         SPI3 Alternate Function mapping 
 *\*\          - GPIO_AF0_RCI1         RCI1 Alternate Function mapping 
 *\*\          - GPIO_AF0_I2C2         I2C2 Alternate Function mapping 
 *\*\          - GPIO_AF1_TIM1         TIM1 Alternate Function mapping
 *\*\          - GPIO_AF1_TIM2         TIM2 Alternate Function mapping
 *\*\          - GPIO_AF1_TIM3         TIM3 Alternate Function mapping
 *\*\          - GPIO_AF1_TIM4         TIM4 Alternate Function mapping
 *\*\          - GPIO_AF1_TIM5         TIM5 Alternate Function mapping
 *\*\          - GPIO_AF1_I2C1         I2C1 Alternate Function mapping
 *\*\          - GPIO_AF1_SPI1         SPI1 Alternate Function mapping
 *\*\          - GPIO_AF1_SPI2         SPI2 Alternate Function mapping
 *\*\          - GPIO_AF1_RCI2         RCI2 Alternate Function mapping
 *\*\          - GPIO_AF2_UART1        UART1 Alternate Function mapping    
 *\*\          - GPIO_AF2_UART2        UART2 Alternate Function mapping    
 *\*\          - GPIO_AF2_TIM1         TIM1 Alternate Function mapping     
 *\*\          - GPIO_AF2_TIM2         TIM2 Alternate Function mapping     
 *\*\          - GPIO_AF2_TIM3         TIM3 Alternate Function mapping     
 *\*\          - GPIO_AF2_TIM4         TIM4 Alternate Function mapping     
 *\*\          - GPIO_AF2_TIM5         TIM5 Alternate Function mapping     
 *\*\          - GPIO_AF2_I2C2         I2C2 Alternate Function mapping     
 *\*\          - GPIO_AF2_RCI2         RCI2 Alternate Function mapping     
 *\*\          - GPIO_AF3_EVENTOUT     EVENTOUT Alternate Function mapping 
 *\*\          - GPIO_AF3_TIM1         TIM1 Alternate Function mapping     
 *\*\          - GPIO_AF3_TIM4         TIM4 Alternate Function mapping     
 *\*\          - GPIO_AF3_TIM5         TIM5 Alternate Function mapping     
 *\*\          - GPIO_AF3_SPI3         SPI3 Alternate Function mapping     
 *\*\          - GPIO_AF3_I2C2         I2C2 Alternate Function mapping     
 *\*\          - GPIO_AF3_RTC          RTC  Alternate Function mapping     
 *\*\          - GPIO_AF3_UART2        UART2 Alternate Function mapping    
 *\*\          - GPIO_AF4_TIM1         TIM1 Alternate Function mapping      
 *\*\          - GPIO_AF4_TIM2         TIM2 Alternate Function mapping     
 *\*\          - GPIO_AF4_TIM3         TIM3 Alternate Function mapping     
 *\*\          - GPIO_AF4_TIM4         TIM4 Alternate Function mapping     
 *\*\          - GPIO_AF4_TIM5         TIM5 Alternate Function mapping     
 *\*\          - GPIO_AF4_SPI2         SPI2 Alternate Function mapping     
 *\*\          - GPIO_AF4_SPI3         SPI3 Alternate Function mapping     
 *\*\          - GPIO_AF4_UART1        UART1 Alternate Function mapping    
 *\*\          - GPIO_AF4_UART2        UART2 Alternate Function mapping    
 *\*\          - GPIO_AF4_UART3        UART3 Alternate Function mapping    
 *\*\          - GPIO_AF4_UART4        UART4 Alternate Function mapping    
 *\*\          - GPIO_AF4_UART5        UART5 Alternate Function mapping    
 *\*\          - GPIO_AF4_I2C2         I2C2 Alternate Function mapping     
 *\*\          - GPIO_AF4_CAN          CAN  Alternate Function mapping     
 *\*\          - GPIO_AF4_COMP4        COMP4 Alternate Function mapping    
 *\*\          - GPIO_AF4_RTC          RTC Alternate Function mapping      
 *\*\          - GPIO_AF4_EVENTOUT     EVENTOUT Alternate Function mapping 
 *\*\          - GPIO_AF5_UART1        UART1 Alternate Function mapping    
 *\*\          - GPIO_AF5_UART3        UART3 Alternate Function mapping    
 *\*\          - GPIO_AF5_UART4        UART4 Alternate Function mapping    
 *\*\          - GPIO_AF5_UART5        UART5 Alternate Function mapping    
 *\*\          - GPIO_AF5_TIM1         TIM1 Alternate Function mapping     
 *\*\          - GPIO_AF5_TIM5         TIM5 Alternate Function mapping     
 *\*\          - GPIO_AF5_SPI1         SPI1 Alternate Function mapping     
 *\*\          - GPIO_AF5_SPI2         SPI2 Alternate Function mapping     
 *\*\          - GPIO_AF5_SPI3         SPI3 Alternate Function mapping     
 *\*\          - GPIO_AF5_RCI1         RCI1 Alternate Function mapping     
 *\*\          - GPIO_AF5_COMP1        COMP1 Alternate Function mapping    
 *\*\          - GPIO_AF5_COMP3        COMP3 Alternate Function mapping    
 *\*\          - GPIO_AF5_COMP4        COMP4 Alternate Function mapping    
 *\*\          - GPIO_AF5_I2C2         I2C2  Alternate Function mapping    
 *\*\          - GPIO_AF6_I2C2         I2C2 Alternate Function mapping     
 *\*\          - GPIO_AF6_I2C1         I2C1 Alternate Function mapping     
 *\*\          - GPIO_AF6_UART2        UART2 Alternate Function mapping    
 *\*\          - GPIO_AF6_UART3        UART3 Alternate Function mapping    
 *\*\          - GPIO_AF6_UART5        UART5 Alternate Function mapping    
 *\*\          - GPIO_AF6_MCO          MCO Alternate Function mapping      
 *\*\          - GPIO_AF6_SPI3         SPI3  Alternate Function mapping    
 *\*\          - GPIO_AF6_COMP2        COMP2 Alternate Function mapping    
 *\*\          - GPIO_AF6_RCI1         RCI1 Alternate Function mapping     
 *\*\          - GPIO_AF6_BEEPER       BEEPER Alternate Function mapping   
 *\*\          - GPIO_AF7_BEEPER       BEEPER Alternate Function mapping   
 *\*\          - GPIO_AF7_I2C1         I2C1 Alternate Function mapping     
 *\*\          - GPIO_AF7_I2C2         I2C2 Alternate Function mapping     
 *\*\          - GPIO_AF7_UART4        UART4 Alternate Function mapping    
 *\*\          - GPIO_AF7_RTC          RTC  Alternate Function mapping     
 *\*\          - GPIO_AF7_CAN          CAN  Alternate Function mapping     
 *\*\          - GPIO_AF7_TIM1         TIM1 Alternate Function mapping     
 *\*\          - GPIO_AF7_RCI2         RCI2 Alternate Function mapping     
 *\*\          - GPIO_AF8_SPI3         SPI3 Alternate Function mapping     
 *\*\          - GPIO_AF8_I2C1         I2C1 Alternate Function mapping     
 *\*\          - GPIO_AF8_RCI2         RCI2 Alternate Function mapping     
 *\*\          - GPIO_AF8_UART4        UART4 Alternate Function mapping    
 *\*\          - GPIO_AF8_UART5        UART5 Alternate Function mapping    
 *\*\          - GPIO_AF8_CAN          CAN   Alternate Function mapping    
 *\*\          - GPIO_AF8_COMP1        COMP1 Alternate Function mapping    
 *\*\          - GPIO_AF8_COMP3        COMP3 Alternate Function mapping    
 *\*\          - GPIO_AF8_COMP4        COMP4 Alternate Function mapping    
 *\*\          - GPIO_AF9_COMP2        COMP2 Alternate Function mapping    
 *\*\          - GPIO_AF9_COMP3        COMP3 Alternate Function mapping    
 *\*\          - GPIO_AF9_RCI2         RCI2 Alternate Function mapping     
 *\*\          - GPIO_AF10_RCI2        RCI2 Alternate Function mapping    
 *\*\          - GPIO_NO_AF            NO alternate Function mapping
 *\*\return none
 */
void GPIO_ConfigPinRemap(uint8_t PortSource, uint8_t PinSource, uint32_t AlternateFunction)
{
    uint8_t temp_value; 
    uint32_t tmpregister;
    GPIO_Module *GPIOx;

    /*Get Peripheral point*/
    GPIOx = GPIO_GET_PERIPH(PortSource);
    /**/
     if((PinSource & (uint8_t)0x08) > 0)
    {
        temp_value = (PinSource & (uint8_t)0x07);
        /*Read GPIO_AFH register*/
        tmpregister  = GPIOx->AFH;
        /*Reset corresponding bits*/
        tmpregister &=~((uint32_t)0x0F <<(temp_value*4U));
        /*Set corresponding bits*/
        tmpregister |= ((uint32_t)(AlternateFunction) << (temp_value * 4U));
        /*Write to the GPIO_AFH register*/
        GPIOx->AFH = tmpregister;
    }
    else
    {
        temp_value = (PinSource & (uint8_t)0x07);
        /*Read GPIO_AFL register*/
        tmpregister  = GPIOx->AFL;
        /*Reset corresponding bits*/
        tmpregister &=~((uint32_t)0x0F <<(temp_value*4U));
        /*Set corresponding bits*/
        tmpregister |= ((uint32_t)(AlternateFunction) << (temp_value * 4U));
        /*Write to the GPIO_AFL register*/
        GPIOx->AFL = tmpregister;
    }
}

/**
 *\*\name   AFIO_ConfigADCExternalTrigRemap.
 *\*\fun    Configurate ADC external trigger.
 *\*\param  ADC_trigger : 
 *\*\          specifies the external trigger line be configured.
 *\*\          - AFIO_ADC_TRIG_EXTI_0
 *\*\          - AFIO_ADC_TRIG_EXTI_1
 *\*\          - AFIO_ADC_TRIG_EXTI_2
 *\*\          - AFIO_ADC_TRIG_EXTI_3
 *\*\          - AFIO_ADC_TRIG_EXTI_4
 *\*\          - AFIO_ADC_TRIG_EXTI_5
 *\*\          - AFIO_ADC_TRIG_EXTI_6
 *\*\          - AFIO_ADC_TRIG_EXTI_7
 *\*\          - AFIO_ADC_TRIG_EXTI_8
 *\*\          - AFIO_ADC_TRIG_EXTI_9
 *\*\          - AFIO_ADC_TRIG_EXTI_10
 *\*\          - AFIO_ADC_TRIG_EXTI_11
 *\*\          - AFIO_ADC_TRIG_EXTI_12
 *\*\          - AFIO_ADC_TRIG_EXTI_13
 *\*\          - AFIO_ADC_TRIG_EXTI_14
 *\*\          - AFIO_ADC_TRIG_EXTI_15
 *\*\return none
 */
void AFIO_ConfigADCExternalTrigRemap(AFIO_ADC_Trig_RemapType ADC_trigger)
{
    uint32_t tmpregister;
    uint32_t temp_value = (uint32_t)ADC_trigger;

    tmpregister = AFIO->CFG;
    
    /* clear AFIO_CFG register ETRR bit */
    tmpregister &= (~(AFIO_RMP_CFG_EXTI_ETRR));

    /* select which external line is connected*/
    tmpregister |= (temp_value << 11U);
    
    AFIO->CFG = tmpregister;
}


/**
 *\*\name   AFIO_ConfigSPINSSMode.
 *\*\fun    Selects the alternate function SPIx NSS mode.
 *\*\param  AFIO_SPIx_NSS : 
 *\*\          choose which SPI configuration.
 *\*\          - AFIO_SPI1_NSS
 *\*\          - AFIO_SPI2_NSS
 *\*\          - AFIO_SPI3_NSS
 *\*\param  SpiNssMode : 
 *\*\          specifies the SPI_NSS mode to be configured.
 *\*\          - AFIO_SPI_NSS_HIGH_IMPEDANCE
 *\*\          - AFIO_SPI_NSS_High_LEVEL
 *\*\return none
 */
void AFIO_ConfigSPINSSMode(uint32_t AFIO_SPIx_NSS, uint32_t SpiNssMode)
{
    uint32_t tmpregister;

    tmpregister = AFIO->CFG;
    if(SpiNssMode != AFIO_SPI_NSS_HIGH_IMPEDANCE)
    {
        tmpregister |= AFIO_SPIx_NSS;
    }
    else 
    {
        tmpregister &= ~AFIO_SPIx_NSS;
    }
    AFIO->CFG = tmpregister;
}

/**
 *\*\name   AFIO_ConfigIOFlitNum.
 *\*\fun    Configure IO filter number in APB clock.
 *\*\param  Flit_Num : 
 *\*\        - 0~31
 *\*\return none
 */
void AFIO_ConfigIOFlitNum(uint8_t Flit_Num)
{
    uint32_t temp_value;

    temp_value = AFIO->CFG;
    
    temp_value &= ~AFIO_RMP_CFG_IOFLITCFG;

    AFIO->CFG = (temp_value | Flit_Num);
}

/**
 *\*\name   AFIO_DIGEFTEnable.
 *\*\fun    Enables or disable digital EFT of port pins.
 *\*\param  PortSource :
 *\*\          - GPIOA_PORT_SOURCE
 *\*\          - GPIOB_PORT_SOURCE
 *\*\          - GPIOC_PORT_SOURCE
 *\*\          - GPIOD_PORT_SOURCE
 *\*\param  Pin :
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\          - GPIO_PIN_ALL
 *\*\param  Cmd :
 *\*\          - ENABLE
 *\*\          - DISABLE
 *\*\return none
 */
void AFIO_DIGEFTEnable(uint8_t PortSource, uint16_t Pin, FunctionalState Cmd)
{
    uint32_t pin = (uint32_t)Pin;

    if(PortSource < GPIOC_PORT_SOURCE)
    {
        if(Cmd == ENABLE)
        {
            AFIO->DIGEFT_CFG1 |= (pin<<(PortSource*16));
        }
        else
        {
            AFIO->DIGEFT_CFG1 &= ~(pin<<(PortSource*16));
        }
    }
    else
    {
        if(Cmd == ENABLE)
        {
            AFIO->DIGEFT_CFG2 |= (pin << ((PortSource & (uint8_t)0x01)*16));
        }
            
        else
        {
            AFIO->DIGEFT_CFG2 &= (pin << ((PortSource & (uint8_t)0x01)*16));
        }
    }
}
