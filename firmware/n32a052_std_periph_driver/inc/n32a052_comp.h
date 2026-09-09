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
*\*\file n32a052_comp.h
*\*\author Nations 
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/


#ifndef __N32A052_COMP_H
#define __N32A052_COMP_H

#ifdef __cplusplus
 extern "C" {
#endif

#include <stddef.h>
#include "n32a052.h"
#include <stdbool.h> 


typedef enum
{
    COMP1 = 0,
    COMP2 = 1,
    COMP3 = 2,
    COMP4 = 3,
} COMPX;

/** COMP init structure definition **/
typedef struct
{
    /* ctrl define */   
    uint32_t Blking;             /* Specifies which timer can control the comp output blanking with its capture event */
    uint32_t Hyst;               /* Specifies the comp hysteresis level with low/medium/high level */
    uint32_t PolRev;             /* Specifies the comp output polarity */
    uint32_t OutSel;             /* Specifies which timer input that can be connecte to the comp output */
    uint32_t InpSel;             /* Specifies the comp inpsel */
    uint32_t InmSel;             /* Specifies the comp inmsel */
    FunctionalState En;          /* enable or disable the comp */

    /* filter define */
    uint8_t SampWindow;          /* Initializes comp sampwindow value ~5bit */
    uint8_t Threshold;           /* ~5bit ,need > SampWindow/2 */
    FunctionalState FilterEn;    /* enable or disable the comp filter */

    /* filter prescale */
    uint16_t ClkPsc;             /* Initializes comp clkpsc value ~5bit */
}COMP_InitType;


/** COMP hysteresis definition **/
typedef enum
{
    COMP_CTRL_HYST_NO   = (0x00000000U),
    COMP_CTRL_HYST_LOW  = (COMP1_CTRL_HYST_0),
    COMP_CTRL_HYST_MID  = (COMP1_CTRL_HYST_1),
    COMP_CTRL_HYST_HIGH = ((COMP1_CTRL_HYST_1 | COMP1_CTRL_HYST_0)),
}COMP_CTRL_HYST;

/** COMP blanking definition **/
typedef enum
{
    COMP_CTRL_BLKING_NO       = ((uint32_t)0x00000000U),
    COMP_CTRL_BLKING_TIM1_OC5 = (COMP1_CTRL_BLKING_0),
}COMP_CTRL_BLKING;

/** COMP blanking mask definition **/
#define COMP_BLANKING_MASK                ((uint32_t)(~COMP1_CTRL_BLKING))

/** COMP hysteresis mask definition **/
#define COMP_HYST_MASK                    ((uint32_t)(~COMP1_CTRL_HYST))

/** COMP Out mask definition **/
#define COMP_CTRL_OUT_MASK                ((uint32_t)COMP1_CTRL_OUT)
#define COMP_CTRL_FILT_OUT_MASK           ((uint32_t)COMP1_CTRL_FILP_OUT)

/** COMP output polarity definition **/
#define COMP_OUTPOL_MASK                  ((uint32_t)(~COMP1_CTRL_POL))
#define COMP_OUTPOL_REV                   ((uint32_t)COMP1_CTRL_POL)
#define COMP_OUTPOL_NREV                  ((uint32_t)0x00000000U)

/** COMP non inverting input definition **/
#define COMP_INPSEL_MASK                  ((uint32_t)(~COMP1_CTRL_INPSEL))
#define COMP_INPSEL_RES                   ((uint32_t)0x00000000U) 
 /** COMP1 inp sel **/  
#define COMP1_INPSEL_PA2                  ((uint32_t)0x00000000U)
#define COMP1_INPSEL_PA3                  ((uint32_t)COMP1_CTRL_INPSEL_0)
#define COMP1_INPSEL_VREF_VC1             ((uint32_t)COMP1_CTRL_INPSEL_1)
#define COMP1_INPSEL_PB1                  ((uint32_t)(COMP1_CTRL_INPSEL_1 | COMP1_CTRL_INPSEL_0))

 /** COMP2 inp sel **/  
#define COMP2_INPSEL_PB1                  ((uint32_t)0x00000000U)
#define COMP2_INPSEL_PA6                  ((uint32_t)COMP2_CTRL_INPSEL_0)
#define COMP2_INPSEL_PB10                 ((uint32_t)COMP2_CTRL_INPSEL_1)
#define COMP2_INPSEL_PA5                  ((uint32_t)(COMP2_CTRL_INPSEL_1 | COMP2_CTRL_INPSEL_0))
#define COMP2_INPSEL_VREF_VC2             ((uint32_t)COMP2_CTRL_INPSEL_2)

 /** COMP3 inp sel **/  
#define COMP3_INPSEL_PA10                 ((uint32_t)0x00000000U)
#define COMP3_INPSEL_DAC_OUT_PB13         ((uint32_t)COMP3_CTRL_INPSEL_0)
#define COMP2_INPSEL_VREF_VC1             ((uint32_t)COMP3_CTRL_INPSEL_1)
#define COMP3_INPSEL_PD7                  ((uint32_t)(COMP3_CTRL_INPSEL_1 | COMP3_CTRL_INPSEL_0))

 /** COMP4 inp sel **/  
#define COMP4_INPSEL_PD7                  ((uint32_t)0x00000000U)
#define COMP4_INPSEL_PA12                 ((uint32_t)COMP4_CTRL_INPSEL_0)
#define COMP4_INPSEL_PD5                  ((uint32_t)COMP4_CTRL_INPSEL_1)
#define COMP4_INPSEL_VREF_VC2             ((uint32_t)(COMP4_CTRL_INPSEL_1 | COMP4_CTRL_INPSEL_0))

/** COMP1 inverting input definition **/
#define COMP_INMSEL_MASK                  ((uint32_t)(~COMP1_CTRL_INMSEL))
#define COMP_INMSEL_RES                   ((uint32_t)0x00000000U)
/** COMP1 inm sel **/
#define COMP1_INMSEL_PA5                  ((uint32_t)0x00000000U)
#define COMP1_INMSEL_PB0                  ((uint32_t)COMP1_CTRL_INMSEL_0)
#define COMP1_INMSEL_PA2                  ((uint32_t)COMP1_CTRL_INMSEL_1)
#define COMP1_INMSEL_VREF_VC1             ((uint32_t)(COMP1_CTRL_INMSEL_1 | COMP1_CTRL_INMSEL_0))
#define COMP1_INMSEL_DAC_OUT_PB13         ((uint32_t)COMP1_CTRL_INMSEL_2)

/** COMP2 inm sel **/
#define COMP2_INMSEL_PA3                  ((uint32_t)0x00000000U)
#define COMP2_INMSEL_PB2                  ((uint32_t)COMP2_CTRL_INMSEL_0)
#define COMP2_INMSEL_PA4                  ((uint32_t)COMP2_CTRL_INMSEL_1)
#define COMP2_INMSEL_DAC_OUT_PB13         ((uint32_t)(COMP2_CTRL_INMSEL_1 | COMP2_CTRL_INMSEL_0))

/** COMP3 inm sel **/
#define COMP3_INMSEL_PA9                  ((uint32_t)0x00000000)
#define COMP3_INMSEL_PD6                  ((uint32_t)COMP3_CTRL_INMSEL_0)
#define COMP3_INMSEL_VREF_VC1             ((uint32_t)COMP3_CTRL_INMSEL_1)
#define COMP3_INMSEL_DAC_OUT_PB13         ((uint32_t)(COMP3_CTRL_INMSEL_1 | COMP3_CTRL_INMSEL_0))

/** COMP4 inm sel **/
#define COMP4_INMSEL_PA11                 ((uint32_t)0x00000000)
#define COMP4_INMSEL_PD4                  ((uint32_t)COMP4_CTRL_INMSEL_0)
#define COMP4_INMSEL_VREF_VC2             ((uint32_t)COMP4_CTRL_INMSEL_1)
#define COMP4_INMSEL_DAC_OUT_PB13         ((uint32_t)(COMP4_CTRL_INMSEL_1 | COMP4_CTRL_INMSEL_0))

/** COMP output connection definition **/
#define COMP_OUTSEL_MASK                  ((uint32_t)(~COMP1_CTRL_OUTSEL))
#define COMP_OUTSEL_RES                   ((uint32_t)0x00000000U)
/** comp1 out trig **/
#define COMP1_OUTSEL_TIM1_OCREFCLEAR      ((uint32_t)0x00000000U)
#define COMP1_OUTSEL_TIM1_BKIN            ((uint32_t)0x00000100U)
#define COMP1_OUTSEL_TIM1_IC1             ((uint32_t)0x00000200U)
#define COMP1_OUTSEL_TIM2_IC1             ((uint32_t)0x00000300U)
#define COMP1_OUTSEL_TIM2_IC4             ((uint32_t)0x00000400U)
#define COMP1_OUTSEL_TIM2_OCREFCLEAR      ((uint32_t)0x00000500U)
#define COMP1_OUTSEL_TIM3_IC1             ((uint32_t)0x00000600U)
#define COMP1_OUTSEL_TIM3_IC4             ((uint32_t)0x00000700U)
#define COMP1_OUTSEL_TIM3_OCREFCLEAR      ((uint32_t)0x00000800U)
#define COMP1_OUTSEL_TIM4_IC1             ((uint32_t)0x00000900U)
#define COMP1_OUTSEL_TIM4_IC4             ((uint32_t)0x00000A00U)
#define COMP1_OUTSEL_TIM4_OCREFCLEAR      ((uint32_t)0x00000B00U)
#define COMP1_OUTSEL_TIM5_IC1             ((uint32_t)0x00000C00U)
#define COMP1_OUTSEL_TIM5_IC4             ((uint32_t)0x00000D00U)
#define COMP1_OUTSEL_TIM5_OCREFCLEAR      ((uint32_t)0x00000E00U)

/** comp2 out trig **/
#define COMP2_OUTSEL_TIM1_OCREFCLEAR      ((uint32_t)0x00000000U)
#define COMP2_OUTSEL_TIM1_BKIN            ((uint32_t)0x00000100U)
#define COMP2_OUTSEL_TIM1_IC1             ((uint32_t)0x00000200U)
#define COMP2_OUTSEL_TIM2_IC2             ((uint32_t)0x00000300U)
#define COMP2_OUTSEL_TIM2_IC3             ((uint32_t)0x00000400U)
#define COMP2_OUTSEL_TIM2_OCREFCLEAR      ((uint32_t)0x00000500U)
#define COMP2_OUTSEL_TIM3_IC2             ((uint32_t)0x00000600U)
#define COMP2_OUTSEL_TIM3_IC3             ((uint32_t)0x00000700U)
#define COMP2_OUTSEL_TIM3_OCREFCLEAR      ((uint32_t)0x00000800U)
#define COMP2_OUTSEL_TIM4_IC2             ((uint32_t)0x00000900U)
#define COMP2_OUTSEL_TIM4_IC3             ((uint32_t)0x00000A00U)
#define COMP2_OUTSEL_TIM4_OCREFCLEAR      ((uint32_t)0x00000B00U)
#define COMP2_OUTSEL_TIM5_IC2             ((uint32_t)0x00000C00U)
#define COMP2_OUTSEL_TIM5_IC3             ((uint32_t)0x00000D00U)
#define COMP2_OUTSEL_TIM5_OCREFCLEAR      ((uint32_t)0x00000E00U)

/** comp3 out trig **/
#define COMP3_OUTSEL_TIM1_OCREFCLEAR      ((uint32_t)0x00000000U)
#define COMP3_OUTSEL_TIM1_BKIN            ((uint32_t)0x00000100U)
#define COMP3_OUTSEL_TIM1_IC1             ((uint32_t)0x00000200U)
#define COMP3_OUTSEL_TIM2_IC1             ((uint32_t)0x00000300U)
#define COMP3_OUTSEL_TIM2_IC2             ((uint32_t)0x00000400U)
#define COMP3_OUTSEL_TIM2_OCREFCLEAR      ((uint32_t)0x00000500U)
#define COMP3_OUTSEL_TIM3_IC1             ((uint32_t)0x00000600U)
#define COMP3_OUTSEL_TIM3_IC2             ((uint32_t)0x00000700U)
#define COMP3_OUTSEL_TIM3_OCREFCLEAR      ((uint32_t)0x00000800U)
#define COMP3_OUTSEL_TIM4_IC1             ((uint32_t)0x00000900U)
#define COMP3_OUTSEL_TIM4_IC2             ((uint32_t)0x00000A00U)
#define COMP3_OUTSEL_TIM4_OCREFCLEAR      ((uint32_t)0x00000B00U)
#define COMP3_OUTSEL_TIM5_IC1             ((uint32_t)0x00000C00U)
#define COMP3_OUTSEL_TIM5_IC2             ((uint32_t)0x00000D00U)
#define COMP3_OUTSEL_TIM5_OCREFCLEAR      ((uint32_t)0x00000E00U)

/** comp4 out trig **/
#define COMP4_OUTSEL_TIM1_OCREFCLEAR      ((uint32_t)0x00000000U)
#define COMP4_OUTSEL_TIM1_BKIN            ((uint32_t)0x00000100U)
#define COMP4_OUTSEL_TIM1_IC1             ((uint32_t)0x00000200U)
#define COMP4_OUTSEL_TIM2_IC3             ((uint32_t)0x00000300U)
#define COMP4_OUTSEL_TIM2_IC4             ((uint32_t)0x00000400U)
#define COMP4_OUTSEL_TIM2_OCREFCLEAR      ((uint32_t)0x00000500U)
#define COMP4_OUTSEL_TIM3_IC3             ((uint32_t)0x00000600U)
#define COMP4_OUTSEL_TIM3_IC4             ((uint32_t)0x00000700U)
#define COMP4_OUTSEL_TIM3_OCREFCLEAR      ((uint32_t)0x00000800U)
#define COMP4_OUTSEL_TIM4_IC3             ((uint32_t)0x00000900U)
#define COMP4_OUTSEL_TIM4_IC4             ((uint32_t)0x00000A00U)
#define COMP4_OUTSEL_TIM4_OCREFCLEAR      ((uint32_t)0x00000B00U)
#define COMP4_OUTSEL_TIM5_IC3             ((uint32_t)0x00000C00U)
#define COMP4_OUTSEL_TIM5_IC4             ((uint32_t)0x00000D00U)
#define COMP4_OUTSEL_TIM5_OCREFCLEAR      ((uint32_t)0x00000E00U)

/** COMP switch definition **/
#define COMP_ENABLE                       ((uint32_t)COMP1_CTRL_EN)

/** COMP filter definition **/
#define COMP_FILTER_SAMPW_MASK            ((uint16_t)(~COMP1_FILC_SAMPW)) /* Low filter sample window size. Number of samples to monitor is SAMPWIN+1. */
#define COMP_FILTER_THRESHOLD_MASK        ((uint16_t)(~COMP1_FILC_THRESH)) /* For proper operation, the value of THRESHOLD must be greater than SAMPWIN / 2. */
#define COMP_FILTER_FILEN_MASK            ((uint16_t)(~COMP1_FILC_FILEN)) /* Filter enable mask. */

#define COMP_FILTER_ENABLE                ((uint16_t)COMP1_FILC_FILEN) /* Filter enable. */

/** COMP filter prescale definition **/
#define COMP_FILTER_CLKPSC_MASK           ((uint16_t)(~COMP1_FILP_CLKPSC)) /* Low filter sample clock prescale mask*/

/** COMP lock definition**/
#define COMP_LOCK_MSK                     ((uint16_t)(~COMP_LOCK)) /* COMP Lock bit */
#define COMP1_LOCK                        ((uint16_t)COMP_LOCK_CMP1LK) /* COMP1 Lock bit */
#define COMP2_LOCK                        ((uint16_t)COMP_LOCK_CMP2LK) /* COMP2 Lock bit */
#define COMP3_LOCK                        ((uint16_t)COMP_LOCK_CMP3LK) /* COMP3 Lock bit */
#define COMP4_LOCK                        ((uint16_t)COMP_LOCK_CMP4LK) /* COMP4 Lock bit */

/** COMP interrupt enable definition **/
#define COMP_INTEN_MSK                    ((uint16_t)(~COMP_INTEN))      
#define COMP1_INTEN                       ((uint16_t)COMP_INTEN_CMP1IEN) /* This bit control Interrput enable of COMP1. */ 
#define COMP2_INTEN                       ((uint16_t)COMP_INTEN_CMP2IEN) /* This bit control Interrput enable of COMP2. */ 
#define COMP3_INTEN                       ((uint16_t)COMP_INTEN_CMP3IEN) /* This bit control Interrput enable of COMP3. */ 
#define COMP4_INTEN                       ((uint16_t)COMP_INTEN_CMP4IEN) /* This bit control Interrput enable of COMP4. */ 

/** COMP interrupt status definition **/
#define COMP_INTSTS_CMP1IS                (COMP_INTSTS_COMP1IS) /* COMP1 Int Status bit */
#define COMP_INTSTS_CMP2IS                (COMP_INTSTS_COMP2IS) /* COMP2 Int Status bit */
#define COMP_INTSTS_CMP3IS                (COMP_INTSTS_COMP3IS) /* COMP3 Int Status bit */
#define COMP_INTSTS_CMP4IS                (COMP_INTSTS_COMP4IS) /* COMP4 Int Status bit */


/** COMP output status definition**/
#define COMP_OUT_MASK                     ((uint32_t)(~COMP1_CTRL_OUT)) 
#define COMP_OUT                          ((uint32_t)COMP1_CTRL_OUT) 

/** COMP non inverting input definition **/
typedef enum {
  //comp1 inp sel
  COMP1_CTRL_INPSEL_PA2         = (COMP1_INPSEL_PA2),
  COMP1_CTRL_INPSEL_PA3         = (COMP1_INPSEL_PA3),
  COMP1_CTRL_INPSEL_VREF_VC1    = (COMP1_INPSEL_VREF_VC1),
  COMP1_CTRL_INPSEL_PB1         = (COMP1_INPSEL_PB1),
  //comp2 inp sel
  COMP2_CTRL_INPSEL_PB1         = (COMP2_INPSEL_PB1),
  COMP2_CTRL_INPSEL_PA6         = (COMP2_INPSEL_PA6),
  COMP2_CTRL_INPSEL_PB10        = (COMP2_INPSEL_PB10),
  COMP2_CTRL_INPSEL_PA5         = (COMP2_INPSEL_PA5),
  COMP2_CTRL_INPSEL_VREF_VC2    = (COMP2_INPSEL_VREF_VC2),
  //comp3 inp sel
  COMP3_CTRL_INPSEL_PA10        = (COMP3_INPSEL_PA10),
  COMP3_CTRL_INPSEL_DAC_OUT_PB13 = (COMP3_INPSEL_DAC_OUT_PB13),
  COMP3_CTRL_INPSEL_VREF_VC1    = (COMP2_INPSEL_VREF_VC1),
  COMP3_CTRL_INPSEL_PD7         = (COMP3_INPSEL_PD7),
  //comp4 inp sel
  COMP4_CTRL_INPSEL_PD7         = (COMP4_INPSEL_PD7),
  COMP4_CTRL_INPSEL_PA12        = (COMP4_INPSEL_PA12),
  COMP4_CTRL_INPSEL_PD5         = (COMP4_INPSEL_PD5),
  COMP4_CTRL_INPSEL_VREF_VC2    = (COMP4_INPSEL_VREF_VC2),
}COMP_CTRL_INPSEL;

/** COMP inverting input definition **/
typedef enum {
  //comp1 inm sel
  COMP1_CTRL_INMSEL_PA5         = (COMP1_INMSEL_PA5),
  COMP1_CTRL_INMSEL_PB0         = (COMP1_INMSEL_PB0),
  COMP1_CTRL_INMSEL_PA2         = (COMP1_INMSEL_PA2),
  COMP1_CTRL_INMSEL_VREF_VC1    = (COMP1_INMSEL_VREF_VC1),
  COMP1_CTRL_INMSEL_DAC_OUT_PB13 = (COMP1_INMSEL_DAC_OUT_PB13),
  //comp2 inm sel
  COMP2_CTRL_INMSEL_PA3         = (COMP2_INMSEL_PA3),
  COMP2_CTRL_INMSEL_PB2         = (COMP2_INMSEL_PB2),
  COMP2_CTRL_INMSEL_PA4         = (COMP2_INMSEL_PA4),
  COMP2_CTRL_INMSEL_DAC_OUT_PB13 = (COMP2_INMSEL_DAC_OUT_PB13),
  //comp3 inm sel
  COMP3_CTRL_INMSEL_PA9         = (COMP3_INMSEL_PA9),
  COMP3_CTRL_INMSEL_PD6         = (COMP3_INMSEL_PD6),
  COMP3_CTRL_INMSEL_VREF_VC1    = (COMP3_INMSEL_VREF_VC1),
  COMP3_CTRL_INMSEL_DAC_OUT_PB13 = (COMP3_INMSEL_DAC_OUT_PB13),
  //comp4 inm sel
  COMP4_CTRL_INMSEL_PA11        = (COMP4_INMSEL_PA11),
  COMP4_CTRL_INMSEL_PD4         = (COMP4_INMSEL_PD4),
  COMP4_CTRL_INMSEL_VREF_VC2    = (COMP4_INMSEL_VREF_VC2),
  COMP4_CTRL_INMSEL_DAC_OUT_PB13 = (COMP4_INMSEL_DAC_OUT_PB13),
}COMP_CTRL_INMSEL;

/** COMP output connection definition **/
typedef enum {
    // comp1 out trig
    COMP1_CTRL_OUTSEL_T1_OCREFCLEAR     = (COMP1_OUTSEL_TIM1_OCREFCLEAR),
    COMP1_CTRL_OUTSEL_T1_BKIN           = (COMP1_OUTSEL_TIM1_BKIN),
    COMP1_CTRL_OUTSEL_T1_IC1            = (COMP1_OUTSEL_TIM1_IC1),
    COMP1_CTRL_OUTSEL_T2_IC1            = (COMP1_OUTSEL_TIM2_IC1),
    COMP1_CTRL_OUTSEL_T2_IC4            = (COMP1_OUTSEL_TIM2_IC4),
    COMP1_CTRL_OUTSEL_T2_OCREFCLEAR     = (COMP1_OUTSEL_TIM2_OCREFCLEAR),
    COMP1_CTRL_OUTSEL_T3_IC1            = (COMP1_OUTSEL_TIM3_IC1),
    COMP1_CTRL_OUTSEL_T3_IC4            = (COMP1_OUTSEL_TIM3_IC4),
    COMP1_CTRL_OUTSEL_T3_OCREFCLEAR     = (COMP1_OUTSEL_TIM3_OCREFCLEAR),
    COMP1_CTRL_OUTSEL_T4_IC1            = (COMP1_OUTSEL_TIM4_IC1),
    COMP1_CTRL_OUTSEL_T4_IC4            = (COMP1_OUTSEL_TIM4_IC4),
    COMP1_CTRL_OUTSEL_T4_OCREFCLEAR     = (COMP1_OUTSEL_TIM4_OCREFCLEAR),
    COMP1_CTRL_OUTSEL_T5_IC1            = (COMP1_OUTSEL_TIM5_IC1),
    COMP1_CTRL_OUTSEL_T5_IC4            = (COMP1_OUTSEL_TIM5_IC4),
    COMP1_CTRL_OUTSEL_T5_OCREFCLEAR     = (COMP1_OUTSEL_TIM5_OCREFCLEAR),
    // comp2 out trig
    COMP2_CTRL_OUTSEL_T1_OCREFCLEAR     = (COMP2_OUTSEL_TIM1_OCREFCLEAR),
    COMP2_CTRL_OUTSEL_T1_BKIN           = (COMP2_OUTSEL_TIM1_BKIN),
    COMP2_CTRL_OUTSEL_T1_IC1            = (COMP2_OUTSEL_TIM1_IC1),
    COMP2_CTRL_OUTSEL_T2_IC2            = (COMP2_OUTSEL_TIM2_IC2),
    COMP2_CTRL_OUTSEL_T2_IC3            = (COMP2_OUTSEL_TIM2_IC3),
    COMP2_CTRL_OUTSEL_T2_OCREFCLEAR     = (COMP2_OUTSEL_TIM2_OCREFCLEAR),
    COMP2_CTRL_OUTSEL_T3_IC2            = (COMP2_OUTSEL_TIM3_IC2),
    COMP2_CTRL_OUTSEL_T3_IC3            = (COMP2_OUTSEL_TIM3_IC3),
    COMP2_CTRL_OUTSEL_T3_OCREFCLEAR     = (COMP2_OUTSEL_TIM3_OCREFCLEAR),
    COMP2_CTRL_OUTSEL_T4_IC2            = (COMP2_OUTSEL_TIM4_IC2),
    COMP2_CTRL_OUTSEL_T4_IC3            = (COMP2_OUTSEL_TIM4_IC3),
    COMP2_CTRL_OUTSEL_T4_OCREFCLEAR     = (COMP2_OUTSEL_TIM4_OCREFCLEAR),
    COMP2_CTRL_OUTSEL_T5_IC2            = (COMP2_OUTSEL_TIM5_IC2),
    COMP2_CTRL_OUTSEL_T5_IC3            = (COMP2_OUTSEL_TIM5_IC3),
    COMP2_CTRL_OUTSEL_T5_OCREFCLEAR     = (COMP2_OUTSEL_TIM5_OCREFCLEAR),
    // comp3 out trig
    COMP3_CTRL_OUTSEL_T1_OCREFCLEAR     = (COMP3_OUTSEL_TIM1_OCREFCLEAR),
    COMP3_CTRL_OUTSEL_T1_BKIN           = (COMP3_OUTSEL_TIM1_BKIN),
    COMP3_CTRL_OUTSEL_T1_IC1            = (COMP3_OUTSEL_TIM1_IC1),
    COMP3_CTRL_OUTSEL_T2_IC1            = (COMP3_OUTSEL_TIM2_IC1),
    COMP3_CTRL_OUTSEL_T2_IC2            = (COMP3_OUTSEL_TIM2_IC2),
    COMP3_CTRL_OUTSEL_T2_OCREFCLEAR     = (COMP3_OUTSEL_TIM2_OCREFCLEAR),
    COMP3_CTRL_OUTSEL_T3_IC1            = (COMP3_OUTSEL_TIM3_IC1),
    COMP3_CTRL_OUTSEL_T3_IC2            = (COMP3_OUTSEL_TIM3_IC2),
    COMP3_CTRL_OUTSEL_T3_OCREFCLEAR     = (COMP3_OUTSEL_TIM3_OCREFCLEAR),
    COMP3_CTRL_OUTSEL_T4_IC1            = (COMP3_OUTSEL_TIM4_IC1),
    COMP3_CTRL_OUTSEL_T4_IC2            = (COMP3_OUTSEL_TIM4_IC2),
    COMP3_CTRL_OUTSEL_T4_OCREFCLEAR     = (COMP3_OUTSEL_TIM4_OCREFCLEAR),
    COMP3_CTRL_OUTSEL_T5_IC1            = (COMP3_OUTSEL_TIM5_IC1),
    COMP3_CTRL_OUTSEL_T5_IC2            = (COMP3_OUTSEL_TIM5_IC2),
    COMP3_CTRL_OUTSEL_T5_OCREFCLEAR     = (COMP3_OUTSEL_TIM5_OCREFCLEAR),
    // comp4 out trig
    COMP4_CTRL_OUTSEL_T1_OCREFCLEAR     = (COMP4_OUTSEL_TIM1_OCREFCLEAR),
    COMP4_CTRL_OUTSEL_T1_BKIN           = (COMP4_OUTSEL_TIM1_BKIN),
    COMP4_CTRL_OUTSEL_T1_IC1            = (COMP4_OUTSEL_TIM1_IC1),
    COMP4_CTRL_OUTSEL_T2_IC3            = (COMP4_OUTSEL_TIM2_IC3),
    COMP4_CTRL_OUTSEL_T2_IC4            = (COMP4_OUTSEL_TIM2_IC4),
    COMP4_CTRL_OUTSEL_T2_OCREFCLEAR     = (COMP4_OUTSEL_TIM2_OCREFCLEAR),
    COMP4_CTRL_OUTSEL_T3_IC3            = (COMP4_OUTSEL_TIM3_IC3),
    COMP4_CTRL_OUTSEL_T3_IC4            = (COMP4_OUTSEL_TIM3_IC4),
    COMP4_CTRL_OUTSEL_T3_OCREFCLEAR     = (COMP4_OUTSEL_TIM3_OCREFCLEAR),
    COMP4_CTRL_OUTSEL_T4_IC3            = (COMP4_OUTSEL_TIM4_IC3),
    COMP4_CTRL_OUTSEL_T4_IC4            = (COMP4_OUTSEL_TIM4_IC4),
    COMP4_CTRL_OUTSEL_T4_OCREFCLEAR     = (COMP4_OUTSEL_TIM4_OCREFCLEAR),
    COMP4_CTRL_OUTSEL_T5_IC3            = (COMP4_OUTSEL_TIM5_IC3),
    COMP4_CTRL_OUTSEL_T5_IC4            = (COMP4_OUTSEL_TIM5_IC4),
    COMP4_CTRL_OUTSEL_T5_OCREFCLEAR     = (COMP4_OUTSEL_TIM5_OCREFCLEAR),
}COMP_CTRL_OUTTRIG;

/** COMP Driving Functions Declaration **/
void COMP_DeInit(void);

void COMP_Init(COMPX COMPx, COMP_InitType* COMP_InitStruct);
void COMP_StructInit(COMP_InitType* COMP_initstruct);
void COMP_SetFilterControl(COMPX COMPx, uint8_t FilEn, uint8_t TheresNum, uint8_t SampPW);
void COMP_SetFilterPrescaler(COMPX COMPx, uint16_t FilPreVal);
void COMP_SetBlanking(COMPX COMPx , COMP_CTRL_BLKING BLK);
void COMP_SetHyst(COMPX COMPx , COMP_CTRL_HYST HYST);
void COMP_OutputPolarityConfig(COMPX COMPx, uint32_t POL);
void COMP_SetInpSel(COMPX COMPx, COMP_CTRL_INPSEL VpSel);
void COMP_SetInmSel(COMPX COMPx, COMP_CTRL_INMSEL VmSel);
void COMP_SetOutTrig(COMPX COMPx, COMP_CTRL_OUTTRIG OutTrig);

void COMP_Enable(COMPX COMPx , FunctionalState Cmd);

void COMP_SetIntEn(uint32_t IntEn, FunctionalState Cmd);
FlagStatus COMP_GetIntStsOneComp(COMPX COMPx);
void COMP_IntStatusClear(uint32_t intsts);

FlagStatus COMP_GetOutStatus(COMPX COMPx);
FlagStatus COMP_GetFilterOutStatus(COMPX COMPx);

void COMP_SetLock(uint32_t Lock);
void COMP_CMPXorOut(uint32_t COMP_XoOsel, FunctionalState Cmd);
void COMP_OutTimEn(uint32_t CompxOut, FunctionalState Cmd);
void COMP_SetRefScl(uint8_t Vv2Trim, bool Vv2En, uint8_t Vv1Trim, bool Vv1En);

#ifdef __cplusplus
}
#endif

#endif /* __N32A052_COMP_H */

