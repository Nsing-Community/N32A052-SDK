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
*\*\version v1.1.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
 */
#include "n32a052.h"

/* Uncomment the line corresponding to the desired System clock (SYSCLK)
   frequency (after reset the HSI is used as SYSCLK source)

   IMPORTANT NOTE:
   ==============
   1. After each device reset the HSI is used as System clock source.

   2. Please make sure that the selected System clock doesn't exceed your
   device's maximum frequency.

   3. If none of the define below is enabled, the HSI is used as System clock
    source.

   4. The System clock configuration functions provided within this file assume
   that:
        - For Low and High density Value line devices an external 8MHz
          crystal is used to drive the System clock.
        - For Low and High density devices an external 8MHz crystal is
          used to drive the System clock.
        - For Connectivity line devices an external 25MHz crystal is used to
   drive the System clock. If you are using different crystal you have to adapt
   those functions accordingly.
    */

#define SYSCLK_USE_HSI     0
#define SYSCLK_USE_HSE     1
#define SYSCLK_USE_HSI_PLL 2
#define SYSCLK_USE_HSE_PLL 3
#define SYSCLK_USE_LSI     4

#ifndef SYSCLK_FREQ
#define SYSCLK_FREQ 64000000
#endif

/*
* SYSCLK_SRC *
** SYSCLK_USE_HSI     **
** SYSCLK_USE_HSE     **
** SYSCLK_USE_HSI_PLL **
** SYSCLK_USE_HSE_PLL **
** SYSCLK_USE_LSI     **
*/
#ifndef SYSCLK_SRC
#define SYSCLK_SRC SYSCLK_USE_HSI_PLL
#endif

#if SYSCLK_SRC == SYSCLK_USE_HSI

    #ifndef HSI_VALUE
        #error HSI_VALUE must be defined!
    #endif

    #if SYSCLK_FREQ != HSI_VALUE
        #error SYSCL_FREQ must be set to HSI_VALUE
    #endif

#elif SYSCLK_SRC == SYSCLK_USE_HSE

    #ifndef HSE_VALUE
        #error HSE_VALUE must be defined!
    #endif

    #if SYSCLK_FREQ != HSE_VALUE
        #error SYSCL_FREQ must be set to HSE_VALUE
    #endif

#elif SYSCLK_SRC == SYSCLK_USE_HSI_PLL || SYSCLK_SRC == SYSCLK_USE_HSE_PLL
	
		#if SYSCLK_SRC == SYSCLK_USE_HSI_PLL
				#ifndef HSI_VALUE
						#error HSI_VALUE must be defined!
				#endif
				#define PLLSRC_VALUE  HSI_VALUE
		#elif SYSCLK_SRC == SYSCLK_USE_HSE_PLL
				#ifndef HSE_VALUE
				    #error HSE_VALUE must be defined!
				#endif
				#define PLLSRC_VALUE  HSE_VALUE
		#endif 
		
    #if ((SYSCLK_FREQ * 1) >= 48000000) && ((SYSCLK_FREQ * 1) <= 72000000)
        #if ( ((PLLSRC_VALUE / 1) >= 4000000) && ((PLLSRC_VALUE / 1) <= 16000000) && ((PLLSRC_VALUE % 1) == 0) )\
            && ( (((SYSCLK_FREQ * 1) / PLLSRC_VALUE) >= 3) && (((SYSCLK_FREQ * 1) / PLLSRC_VALUE) <= 18) && (((SYSCLK_FREQ * 1) % PLLSRC_VALUE) == 0) )
                #define PLL_MUL    (SYSCLK_FREQ * 1 / PLLSRC_VALUE)
                #define PLL_PRE    0
				#define PLLOUT_DIV 0
                #define SYSCLK_CONFIG_PASS
				#elif ( ((PLLSRC_VALUE / 2) >= 4000000) && ((PLLSRC_VALUE / 2) <= 16000000) && ((PLLSRC_VALUE % 2) == 0) )\
						&& ( (((SYSCLK_FREQ * 2) / PLLSRC_VALUE) >= 3) && (((SYSCLK_FREQ * 2) / PLLSRC_VALUE) <= 18) && (((SYSCLK_FREQ * 2) % PLLSRC_VALUE) == 0) )
								#define PLL_MUL    (SYSCLK_FREQ * 2 / PLLSRC_VALUE)
								#define PLL_PRE    1
								#define PLLOUT_DIV 0
								#define SYSCLK_CONFIG_PASS
				#elif ( ((PLLSRC_VALUE / 3) >= 4000000) && ((PLLSRC_VALUE / 3) <= 16000000) && ((PLLSRC_VALUE % 3) == 0) )\
						&& ( (((SYSCLK_FREQ * 3) / PLLSRC_VALUE) >= 3) && (((SYSCLK_FREQ * 3) / PLLSRC_VALUE) <= 18) && (((SYSCLK_FREQ * 3) % PLLSRC_VALUE) == 0) )
								#define PLL_MUL    (SYSCLK_FREQ * 3 / PLLSRC_VALUE)
								#define PLL_PRE    2
								#define PLLOUT_DIV 0
								#define SYSCLK_CONFIG_PASS
				#elif ( ((PLLSRC_VALUE / 4) >= 4000000) && ((PLLSRC_VALUE / 4) <= 16000000) && ((PLLSRC_VALUE % 4) == 0) )\
						&& ( (((SYSCLK_FREQ * 4) / PLLSRC_VALUE) >= 3) && (((SYSCLK_FREQ * 4) / PLLSRC_VALUE) <= 18) && (((SYSCLK_FREQ * 4) % PLLSRC_VALUE) == 0) )
								#define PLL_MUL    (SYSCLK_FREQ * 4 / PLLSRC_VALUE)
								#define PLL_PRE    3
								#define PLLOUT_DIV 0
								#define SYSCLK_CONFIG_PASS
        #endif
    #endif
    
    #ifndef SYSCLK_CONFIG_PASS
        #if ((SYSCLK_FREQ * 2) >= 48000000) && ((SYSCLK_FREQ * 2) <= 72000000)          
            #if ( ((PLLSRC_VALUE / 1) >= 4000000) && ((PLLSRC_VALUE / 1) <= 16000000) && ((PLLSRC_VALUE % 1) == 0) )\
                && ( (((SYSCLK_FREQ * 2) / PLLSRC_VALUE) >= 3) && (((SYSCLK_FREQ * 2) / PLLSRC_VALUE) <= 18) && (((SYSCLK_FREQ * 2) % PLLSRC_VALUE) == 0) )
                    #define PLL_MUL    (SYSCLK_FREQ * 2 / PLLSRC_VALUE)
                    #define PLL_PRE    0
					#define PLLOUT_DIV 1
                    #define SYSCLK_CONFIG_PASS
						#elif ( ((PLLSRC_VALUE / 2) >= 4000000) && ((PLLSRC_VALUE / 2) <= 16000000) && ((PLLSRC_VALUE % 2) == 0) )\
								&& ( (((SYSCLK_FREQ * 4) / PLLSRC_VALUE) >= 3) && (((SYSCLK_FREQ * 4) / PLLSRC_VALUE) <= 18) && (((SYSCLK_FREQ * 4) % PLLSRC_VALUE) == 0) )
										#define PLL_MUL    (SYSCLK_FREQ * 4 / PLLSRC_VALUE)
										#define PLL_PRE    1
										#define PLLOUT_DIV 1
										#define SYSCLK_CONFIG_PASS
						#elif ( ((PLLSRC_VALUE / 3) >= 4000000) && ((PLLSRC_VALUE / 3) <= 16000000) && ((PLLSRC_VALUE % 3) == 0) )\
								&& ( (((SYSCLK_FREQ * 6) / PLLSRC_VALUE) >= 3) && (((SYSCLK_FREQ * 6) / PLLSRC_VALUE) <= 18) && (((SYSCLK_FREQ * 6) % PLLSRC_VALUE) == 0) )
										#define PLL_MUL    (SYSCLK_FREQ * 6 / PLLSRC_VALUE)
										#define PLL_PRE    2
										#define PLLOUT_DIV 1
										#define SYSCLK_CONFIG_PASS
						#elif ( ((PLLSRC_VALUE / 4) >= 4000000) && ((PLLSRC_VALUE / 4) <= 16000000) && ((PLLSRC_VALUE % 4) == 0) )\
								&& ( (((SYSCLK_FREQ * 8) / PLLSRC_VALUE) >= 3) && (((SYSCLK_FREQ * 8) / PLLSRC_VALUE) <= 18) && (((SYSCLK_FREQ * 8) % PLLSRC_VALUE) == 0) )
										#define PLL_MUL    (SYSCLK_FREQ * 8 / PLLSRC_VALUE)
										#define PLL_PRE    3
										#define PLLOUT_DIV 1
										#define SYSCLK_CONFIG_PASS                          
             #endif
         #endif
     #endif
    
    #ifndef SYSCLK_CONFIG_PASS
        #if ((SYSCLK_FREQ * 3) >= 48000000) && ((SYSCLK_FREQ * 3) <= 72000000)           
            #if ( ((PLLSRC_VALUE / 1) >= 4000000) && ((PLLSRC_VALUE / 1) <= 16000000) && ((PLLSRC_VALUE % 1) == 0) )\
                && ( (((SYSCLK_FREQ * 3) / PLLSRC_VALUE) >= 3) && (((SYSCLK_FREQ * 3) / PLLSRC_VALUE) <= 18) && (((SYSCLK_FREQ * 3) % PLLSRC_VALUE) == 0) )
                    #define PLL_MUL    (SYSCLK_FREQ * 3 / PLLSRC_VALUE)
                    #define PLL_PRE    0
					#define PLLOUT_DIV 2
                    #define SYSCLK_CONFIG_PASS
						#elif ( ((PLLSRC_VALUE / 2) >= 4000000) && ((PLLSRC_VALUE / 2) <= 16000000) && ((PLLSRC_VALUE % 2) == 0) )\
								&& ( (((SYSCLK_FREQ * 6) / PLLSRC_VALUE) >= 3) && (((SYSCLK_FREQ * 6) / PLLSRC_VALUE) <= 18) && (((SYSCLK_FREQ * 6) % PLLSRC_VALUE) == 0) )
										#define PLL_MUL    (SYSCLK_FREQ * 6 / PLLSRC_VALUE)
										#define PLL_PRE    1
										#define PLLOUT_DIV 2
										#define SYSCLK_CONFIG_PASS
						#elif ( ((PLLSRC_VALUE / 3) >= 4000000) && ((PLLSRC_VALUE / 3) <= 16000000) && ((PLLSRC_VALUE % 3) == 0) )\
								&& ( (((SYSCLK_FREQ * 9) / PLLSRC_VALUE) >= 3) && (((SYSCLK_FREQ * 9) / PLLSRC_VALUE) <= 18) && (((SYSCLK_FREQ * 9) % PLLSRC_VALUE) == 0) )
										#define PLL_MUL    (SYSCLK_FREQ * 9 / PLLSRC_VALUE)
										#define PLL_PRE    2
										#define PLLOUT_DIV 2
										#define SYSCLK_CONFIG_PASS
						#elif ( ((PLLSRC_VALUE / 4) >= 4000000) && ((PLLSRC_VALUE / 4) <= 16000000) && ((PLLSRC_VALUE % 4) == 0) )\
								&& ( (((SYSCLK_FREQ * 12) / PLLSRC_VALUE) >= 3) && (((SYSCLK_FREQ * 12) / PLLSRC_VALUE) <= 18) && (((SYSCLK_FREQ * 12) % PLLSRC_VALUE) == 0) )
										#define PLL_MUL    (SYSCLK_FREQ * 12 / PLLSRC_VALUE)
										#define PLL_PRE    3
										#define PLLOUT_DIV 2
										#define SYSCLK_CONFIG_PASS                   
            #endif
         #endif
     #endif
    
   #ifndef SYSCLK_CONFIG_PASS
       #if ((SYSCLK_FREQ * 4) >= 48000000) && ((SYSCLK_FREQ * 4) <= 72000000)            
           #if  (((PLLSRC_VALUE / 1) >= 4000000) && ((PLLSRC_VALUE / 1) <= 16000000) && ((PLLSRC_VALUE % 1) == 0) \
					 && (((SYSCLK_FREQ * 4) / PLLSRC_VALUE) >= 3) && (((SYSCLK_FREQ * 4) / PLLSRC_VALUE) <= 18) && (((SYSCLK_FREQ * 4) % PLLSRC_VALUE) == 0) )
                    #define PLL_MUL    (SYSCLK_FREQ * 4 / PLLSRC_VALUE)
                    #define PLL_PRE    0
					#define PLLOUT_DIV 3
                    #define SYSCLK_CONFIG_PASS
           #elif (((PLLSRC_VALUE / 2) >= 4000000) && ((PLLSRC_VALUE / 2) <= 16000000) && ((PLLSRC_VALUE % 2) == 0)  \
					 && (((SYSCLK_FREQ * 8) / PLLSRC_VALUE) >= 3) && (((SYSCLK_FREQ * 8) / PLLSRC_VALUE) <= 18) && (((SYSCLK_FREQ * 8) % PLLSRC_VALUE) == 0) )
										#define PLL_MUL    (SYSCLK_FREQ * 8 / PLLSRC_VALUE)
										#define PLL_PRE    1
										#define PLLOUT_DIV 3
										#define SYSCLK_CONFIG_PASS
           #elif  (((PLLSRC_VALUE / 3) >= 4000000) && ((PLLSRC_VALUE / 3) <= 16000000) && ((PLLSRC_VALUE % 3) == 0) \
					 && (((SYSCLK_FREQ * 12) / PLLSRC_VALUE) >= 3) && (((SYSCLK_FREQ * 12) / PLLSRC_VALUE) <= 18) && (((SYSCLK_FREQ * 12) % PLLSRC_VALUE) == 0) )
										#define PLL_MUL    (SYSCLK_FREQ * 12 / PLLSRC_VALUE)
										#define PLL_PRE    2
										#define PLLOUT_DIV 3
										#define SYSCLK_CONFIG_PASS
           #elif  (((PLLSRC_VALUE / 4) >= 4000000) && ((PLLSRC_VALUE / 4) <= 16000000) && ((PLLSRC_VALUE % 4) == 0) \
					 && (((SYSCLK_FREQ * 16) / PLLSRC_VALUE) >= 3) && (((SYSCLK_FREQ * 16) / PLLSRC_VALUE) <= 18) && (((SYSCLK_FREQ * 16) % PLLSRC_VALUE) == 0) )
										#define PLL_MUL    (SYSCLK_FREQ * 16 / PLLSRC_VALUE)
										#define PLL_PRE    3
										#define PLLOUT_DIV 3
										#define SYSCLK_CONFIG_PASS                          
           #endif
       #endif
   #endif
     
	 #ifndef SYSCLK_CONFIG_PASS
			 #error Cannot make a PLL multiply factor to SYSCLK_FREQ.
	 #endif
		 

#elif SYSCLK_SRC == SYSCLK_USE_LSI

    #ifndef LSI_VALUE
        #error LSI_VALUE must be defined!
    #endif

    #if SYSCLK_FREQ != LSI_VALUE
        #error SYSCL_FREQ must be set to LSI_VALUE
    #endif

#else
#error wrong value for SYSCLK_SRC
#endif

/* #define VECT_TAB_SRAM */
#define VECT_TAB_OFFSET 0x0 /*!< Vector Table base offset field. This value must be a multiple of 0x200. */

/*******************************************************************************
 *  Clock Definitions
 *******************************************************************************/
uint32_t SystemCoreClock = SYSCLK_FREQ; /*!< System Clock Frequency (Core Clock) */

static void SetSysClock(void);

#ifdef DATA_IN_ExtSRAM
static void SystemInit_ExtMemCtl(void);
#endif /* DATA_IN_ExtSRAM */

/**
*\*\name SystemInit
*\*\fun  Setup the microcontroller system
*\*\         Initialize the Embedded Flash Interface, the PLL and update the
*\*\         SystemCoreClock variable.
*\*\param  none
*\*\return  none
*\*\note   This function should be used only after reset.
 */
void SystemInit(void)
{
    uint32_t temp_value;

    temp_value = PWR->CTRL3;
    /* Clear NRSTCNT[10:0] bits */
    temp_value &= (~(PWR_CTRL3_NRSTCNT));
    /* Set the NRSTCNT[10:0] bits according to filter_value */
    temp_value |= (uint32_t)0x7FF << 16; 
    /* Store the new value */
    PWR->CTRL3 = temp_value;
    /* Enables or disables the NRST pin Filter. */
    PWR->CTRL3 |= PWR_CTRL3_NRSTFILEN;
    /* Reset the RCC clock configuration to the default reset state(for debug purpose) */
    /* Set HSIEN bit */
    RCC->CTRL |= (uint32_t)0x00000001U;

    /* Reset SCLKSW, AHBPRE, APB1PRES, APB2PRES, MCO and MCOPRES bits */
    RCC->CFG &= (uint32_t)0x21FF0000U;

    /* Reset HSEON, CLKSSEN and PLLEN bits */
    RCC->CTRL &= (uint32_t)0xFEF6FFFFU;
  
    /* Reset PLLBP bit */
    RCC->CTRL &= (uint32_t)0xFFBFFFFFU;

    /* Reset PLLMULFCT, PLLPRE, PLLOUTDIV and PLLSRC bits */
    RCC->CFG &= (uint32_t)0xFE00FFFFU;

    /* Reset CFG2 register */
    RCC->CFG2 = 0x00003800U;

    /* Disable all interrupts and clear pending bits  */
    RCC->CLKINT = 0x00BD0000U;

    /* Enable Prefetch Buffer */
    FLASH->AC |= (uint32_t)FLASH_AC_PRFTBFEN;
    
    /* Configure the System clock frequency, HCLK, PCLK2 and PCLK1 prescalers */
    /* Configure the Flash Latency cycles and enable prefetch buffer */
    SetSysClock();
}

/**
*\*\name    RCC_ClrIntPendingBit.
*\*\fun  Update SystemCoreClock variable according to Clock Register Values.
*\*\        The SystemCoreClock variable contains the core clock (HCLK), it can
*\*\        be used by the user application to setup the SysTick timer or configure other parameters.
*\*\param  none
*\*\return  none
*\*\note   Each time the core clock (HCLK) changes, this function must be called
*\*\        to update SystemCoreClock variable value. Otherwise, any configuration based on this variable will be incorrect.
*\*\note   - The system frequency computed by this function is not the real
*\*\          frequency in the chip. It is calculated based on the predefined constant and the selected clock source:
*\*\          - If SYSCLK source is HSI, SystemCoreClock will contain the HSI_VALUE(*)
*\*\          - If SYSCLK source is HSE, SystemCoreClock will contain the HSE_VALUE(**)
*\*\          - If SYSCLK source is PLL, SystemCoreClock will contain the HSE_VALUE(**) or HSI_VALUE(*) multiplied by the PLL factors.
*\*\          - If SYSCLK source is LSI, SystemCoreClock will contain the LSI_VALUE(***)
*\*\        (*) HSI_VALUE is a constant defined in n32a052.h file (default value
*\*\            8 MHz) but the real value may vary depending on the variations
*\*\            in voltage and temperature.
*\*\        (**) HSE_VALUE is a constant defined in n32a052.h file (default value
*\*\             8 MHz, depedning on the product used), user has to
*\*\             ensure that HSE_VALUE is same as the real frequency of the crystal used.
*\*\             Otherwise, this function may have wrong result.
*\*\        (***) LSI_VALUE is a constant defined in n32a052.h file (default value
*\*\            32KHz) but the real value may vary depending on the variations
*\*\            in voltage and temperature.
*\*\        - The result of this function could be not correct when using
*\*\fractional value for HSE crystal.
 */
void SystemCoreClockUpdate(void)
{
    uint32_t tmp, pllmull, pllpre, plloutdiv, pllsource;
    const uint8_t AHBPrescTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};

    /* Get SYSCLK source
     * -------------------------------------------------------*/
    tmp = RCC->CFG & RCC_CFG_SCLKSTS;

    switch (tmp)
    {
        case RCC_CFG_SCLKSTS_HSI: /* HSI used as system clock */
            SystemCoreClock = HSI_VALUE;
            break;
        case RCC_CFG_SCLKSTS_HSE: /* HSE used as system clock */
            SystemCoreClock = HSE_VALUE;
            break;
        case RCC_CFG_SCLKSTS_PLL: /* PLL used as system clock */

            /* Get PLL clock source, PLL Pre-Divider, PLL out div and multiplication factor ----------------------*/
            pllmull   = RCC->CFG & RCC_CFG_PLLMULFCT;
            pllpre    = RCC->CFG & RCC_CFG_PLLPRE;
            plloutdiv = RCC->CFG & RCC_CFG_PLLOUTDIV;
            pllsource = RCC->CFG & RCC_CFG_PLLSRC;
        
            pllmull = (pllmull >> 16) + 3;
        
            if ((pllsource >> 24) == 0x00)
            { 
                /* HSI selected as PLL clock entry */
                SystemCoreClock = HSI_VALUE * pllmull;
            }
            else
            {
                /* HSE selected as PLL clock entry */
                SystemCoreClock = HSE_VALUE * pllmull;
            }
            
            /* PLL Pre-Divider clock */
            pllpre = (pllpre >> 20) + 1;
            SystemCoreClock = SystemCoreClock / pllpre;

            /* PLL Out Div clock */
            plloutdiv = (plloutdiv >> 22) + 1;
            SystemCoreClock = SystemCoreClock / plloutdiv;
            break;
            
        case RCC_CFG_SCLKSTS_LSI: /* LSI used as system clock */
            SystemCoreClock = LSI_VALUE;
            break;

        default:
            SystemCoreClock = HSI_VALUE;
            break;
    }

    /* Compute HCLK clock frequency ----------------*/
    /* Get HCLK prescaler */
    tmp = AHBPrescTable[((RCC->CFG & RCC_CFG_AHBPRES) >> 4)];
    /* HCLK clock frequency */
    SystemCoreClock >>= tmp;
}

/**
*\*\name    HSE_Frequency_Detection
*\*\fun     Used to check if HSE has started vibrating normally.
*\*\param   none
*\*\return  HSE status
 */
uint32_t HSE_Frequency_Detection(void)
{
    uint32_t status = 1U;
    uint32_t tmpccmodx ;
    uint32_t tmpccen , tmp = 0U ;
    uint32_t timeoutcnt = 90000,HSE_FREQ =0U;
    uint8_t i=0U;
    uint32_t HSE_FREQ_TEMP[22];
    uint32_t HSE_valuetemp = 0U;
    uint32_t HSE_valuedown,HSE_valueup;
    
    HSE_valuedown = (HSE_VALUE - HSE_VALUE/10)/1000;
    HSE_valueup = (HSE_VALUE + HSE_VALUE/10)/1000;
    
    RCC->APB2PCLKEN |= RCC_APB2PCLKEN_TIM2EN;
    TIM2->CTRL1 |= 0x00080000;
   
    /*---------Configure the TI4 as Input------------*/
    /* Disable the Channel 4: Reset the CC4E Bit */
    TIM2->CCEN &= (uint32_t)(~((uint32_t)0x00004000U));
    tmpccmodx = TIM2->CCMOD2;
    tmpccen  = TIM2->CCEN;
    /* Select the Input and set the filter */
    tmpccmodx &= (uint32_t)((uint16_t)(~(uint16_t)0x00000300U) & ((uint16_t) ~((uint16_t)0x0000F000U)));
    tmpccmodx |= (uint32_t)(0x00000001 << 8);

    /* Select the Polarity and set the CC4E Bit */
    tmpccen &= (uint32_t)(~((uint32_t)(0x00008000U)));
    tmpccen |= (uint32_t)(tmp | (uint32_t)0x00004000U);

    /* Write to TIM2 CCMOD2 and CCEN registers */
    TIM2->CCMOD2 = tmpccmodx;
    TIM2->CCEN   = tmpccen;
    
    /*---------Sets the TIMx Input Capture 4 prescaler.------------*/
    /* Reset the IC4PSC Bits */
    TIM2->CCMOD2 &= (uint32_t)(~((uint16_t)0x00000C00U));
    
    /* Enable the TIM Counter */
    TIM2->CTRL1 |= (uint32_t)0x00000001U;
    
    while(timeoutcnt)//timeoutcnt>0
    {
        IWDG->KEY = (uint32_t)0xAAAA;
        timeoutcnt--;
        if(TIM2->STS & 0x08)
        {
            TIM2->STS = 0;
            HSE_FREQ_TEMP[i] = TIM2->CCDAT4;
            i++;
            
            if(i>=21)
            {
                HSE_FREQ = 0;
                for(i=1;i<21;i++)
                {
                    if(HSE_FREQ_TEMP[i] > HSE_FREQ_TEMP[i-1])
                    {
                        HSE_FREQ += (HSE_FREQ_TEMP[i] - HSE_FREQ_TEMP[i-1]);
                    }
                    else
                    {
                        HSE_FREQ += (65536 + HSE_FREQ_TEMP[i] - HSE_FREQ_TEMP[i-1]);
                    }
                }
                HSE_valuetemp = 8000*128*20/HSE_FREQ;
                
                if((HSE_valuetemp <= HSE_valueup) && (HSE_valuetemp >= HSE_valuedown))
                {
                    break;
                }
                else
                {
                    i = 0;
                }
            }
        }
    }
    
    if(timeoutcnt==0)
    {
        status = 0U;
    }
    
    /* RESET the TIM2 */
    TIM2->CTRL1 = (uint32_t)0x00000000U;
    RCC->APB2PRST |= RCC_APB2PCLKEN_TIM2EN;
    RCC->APB2PRST &= ~RCC_APB2PCLKEN_TIM2EN;
    RCC->APB2PCLKEN &= ~RCC_APB2PCLKEN_TIM2EN;
    
    return status;
}

/**
*\*\name    HSEPLL_Failed_Detection
*\*\fun     Solution to PLL clock domain anomaly caused by HSE clock abnormality.
*\*\param   none
*\*\return  none
 */
void HSEPLL_Failed_Detection(void)
{
	uint32_t temp_value;
	if((RCC->CTRL & RCC_CTRL_PLLEN) == RCC_CTRL_PLLEN)
	{
		*(uint32_t*)0x4002101C |= 0x10000000U;
		*(uint32_t*)0x4000702C = 0x33000;
		*(uint32_t*)0x4000702C |= 0x10;
		*(uint32_t*)0x40007024 |= 0x10;
		temp_value = *(uint32_t*)0x40007024;
		temp_value &= 0xFFFFFFF3;
		temp_value |= 0x08;
		*(uint32_t*)0x40007024 = temp_value;
		
		temp_value = *(uint32_t*)0x40007028;
		temp_value &= 0xFFFFFFF3;
		temp_value |= 0x0C;
		*(uint32_t*)0x40007028 = temp_value;
		
		temp_value = *(uint32_t*)0x40007000;
		temp_value &= (~0x00000002U);
		*(uint32_t*)0x40007000 = temp_value;
		*(uint32_t*)0xE000ED10 |= 0x00000004U;
		__WFI();
		*(uint32_t*)0xE000ED10 &= (~0x00000004U);
		while(1);
	}
	else
	{
		/* no process */
	}
}

/**
*\*\name  SetSysClock.
*\*\fun   Configures the System clock frequency, HCLK, PCLK2 and PCLK1 prescalers.
*\*\param  none
*\*\return  none
**/
static void SetSysClock(void)
{
    uint32_t rcc_cfg        = 0;
#if ((SYSCLK_SRC == SYSCLK_USE_HSI) || (SYSCLK_SRC == SYSCLK_USE_HSI_PLL))

    uint32_t HSIStatus;
	uint32_t StartUpCounter = 0;
	
#elif ((SYSCLK_SRC == SYSCLK_USE_HSE) || (SYSCLK_SRC == SYSCLK_USE_HSE_PLL))

    uint32_t HSEStatus;
#elif (SYSCLK_SRC == SYSCLK_USE_LSI)

    uint32_t LSIStatus;
	uint32_t StartUpCounter = 0;
#endif
	
	HSEPLL_Failed_Detection();

#if ((SYSCLK_SRC == SYSCLK_USE_HSI) || (SYSCLK_SRC == SYSCLK_USE_HSI_PLL))

    /* Enable HSI */
    RCC->CTRL |= ((uint32_t)RCC_CTRL_HSIEN);

    /* Wait till HSI is ready and if Time out is reached exit */
    do
    {
        HSIStatus = RCC->CTRL & RCC_CTRL_HSIRDF;
        StartUpCounter++;
    } while ((HSIStatus == 0) && (StartUpCounter != HSI_STARTUP_TIMEOUT));

    if((RCC->CTRL & RCC_CTRL_HSIRDF) != RESET)
    {
        HSIStatus = (uint32_t)0x1;
    }
    else
    {
        HSIStatus = (uint32_t)0x0;
    }
    
    if (HSIStatus == 0)
    {
        /* If HSI fails to start-up, the application will have wrong clock
         * configuration. User can add here some code to deal with this error */
        while(1);
    }

#elif ((SYSCLK_SRC == SYSCLK_USE_HSE) || (SYSCLK_SRC == SYSCLK_USE_HSE_PLL))

    /* Enable HSE */
    RCC->CTRL |= (uint32_t)RCC_CTRL_HSEEN;
    
    /* Wait till HSE is ready and if Time out is reached exit */
    HSEStatus = HSE_Frequency_Detection();
    
    if (HSEStatus == 0)
    {
        /* If HSE fails to start-up, the application will have wrong clock
         * configuration. User can add here some code to deal with this error */
        SystemCoreClock = HSI_VALUE;
        return;
    }

#elif (SYSCLK_SRC == SYSCLK_USE_LSI)

    /* Enable LSI */
    RCC->LSCTRL |= ((uint32_t)RCC_LSCTRL_LSIEN);

    /* Wait till LSI is ready and if Time out is reached exit */
    do
    {
        LSIStatus = RCC->LSCTRL & RCC_LSCTRL_LSIRD;
        StartUpCounter++;
    } while ((LSIStatus == 0) && (StartUpCounter != LSI_STARTUP_TIMEOUT));

    if((RCC->LSCTRL & RCC_LSCTRL_LSIRD) != RESET)
    {
        LSIStatus = (uint32_t)0x1;
    }
    else
    {
        LSIStatus = (uint32_t)0x0;
    }
    
    if (LSIStatus == 0)
    {
        /* If LSI fails to start-up, the application will have wrong clock
         * configuration. User can add here some code to deal with this error */
        SystemCoreClock = HSI_VALUE;
        return;
    }

#endif

    /* Flash wait state
        0: SYSCLK <= 24M
        1: SYSCLK <= 48M
        2: SYSCLK <= 64M
     */
    FLASH->AC &= (uint32_t)((uint32_t)~FLASH_AC_LATENCY);
    FLASH->AC |= (uint32_t)((SYSCLK_FREQ - 1) / 24000000);

    /* HCLK = SYSCLK */
    RCC->CFG |= (uint32_t)RCC_CFG_AHBPRES_DIV1;

    /* PCLK2 = HCLK */
    RCC->CFG |= (uint32_t)RCC_CFG_APB2PRES_DIV1;
    

    /* PCLK1 = HCLK/2 */
    RCC->CFG |= (uint32_t)RCC_CFG_APB1PRES_DIV2;
    
    
#if SYSCLK_SRC == SYSCLK_USE_HSI
    /* Select HSI as system clock source */
    RCC->CFG &= (uint32_t)((uint32_t) ~(RCC_CFG_SCLKSW));
    RCC->CFG |= (uint32_t)RCC_CFG_SCLKSW_HSI;

    /* Wait till HSI is used as system clock source */
    while ((RCC->CFG & (uint32_t)RCC_CFG_SCLKSTS) != RCC_CFG_SCLKSTS_HSI)
    {
    }
#elif SYSCLK_SRC == SYSCLK_USE_HSE
    /* Select HSE as system clock source */
    RCC->CFG &= (uint32_t)((uint32_t) ~(RCC_CFG_SCLKSW));
    RCC->CFG |= (uint32_t)RCC_CFG_SCLKSW_HSE;

    /* Wait till HSE is used as system clock source */
    while ((RCC->CFG & (uint32_t)RCC_CFG_SCLKSTS) != RCC_CFG_SCLKSTS_HSE)
    {
    }
#elif SYSCLK_SRC == SYSCLK_USE_HSI_PLL || SYSCLK_SRC == SYSCLK_USE_HSE_PLL
		
    /* clear bits */
    /* Clear PLLOUTDIV PLLPRE bits */
    RCC->CFG &= (~RCC_CFG_PLLOUTDIV);
    
    RCC->CFG &= (uint32_t)((uint32_t) ~(RCC_CFG_PLLSRC | RCC_CFG_PLLPRE | RCC_CFG_PLLMULFCT));

    /* set PLL source */
    rcc_cfg = RCC->CFG;
    rcc_cfg |= ((SYSCLK_SRC == SYSCLK_USE_HSI_PLL) ? RCC_CFG_PLLSRC_HSI : RCC_CFG_PLLSRC_HSE);

    /* set PLL multiply factor */
    rcc_cfg |= (((uint32_t)PLL_MUL - 3) << 16);
    /* set PLL Pre-Divider factor */
    rcc_cfg |= ((uint32_t)PLL_PRE << 20);
    /* set PLL output clock divider factor */
    rcc_cfg |= ((uint32_t)PLLOUT_DIV << 22);

    RCC->CFG = rcc_cfg;

    /* Enable PLL */
    RCC->CTRL |= RCC_CTRL_PLLEN;

    /* Wait till PLL is ready */
    while ((RCC->CTRL & RCC_CTRL_PLLRDF) == 0)
    {
    }

    /* Select PLL as system clock source */
    RCC->CFG &= (uint32_t)((uint32_t) ~(RCC_CFG_SCLKSW));
    RCC->CFG |= (uint32_t)RCC_CFG_SCLKSW_PLL;

    /* Wait till PLL is used as system clock source */
    while ((RCC->CFG & (uint32_t)RCC_CFG_SCLKSTS) != (uint32_t)RCC_CFG_SCLKSTS_PLL)
    {
    }
#elif SYSCLK_SRC == SYSCLK_USE_LSI
    /* Select LSI as system clock source */
    RCC->CFG &= (uint32_t)((uint32_t) ~(RCC_CFG_SCLKSW));
    RCC->CFG |= (uint32_t)RCC_CFG_SCLKSW_LSI;

    /* Wait till LSI is used as system clock source */
    while ((RCC->CFG & (uint32_t)RCC_CFG_SCLKSTS) != RCC_CFG_SCLKSTS_LSI)
    {
    }
#endif
}
