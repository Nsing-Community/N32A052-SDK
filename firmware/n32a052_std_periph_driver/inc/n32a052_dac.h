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
*\*\file n32a052_dac.h
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/

#ifndef __N32A052_DAC_H__
#define __N32A052_DAC_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "n32a052.h"

/*** DAC Structure Definition Start ***/

/** DAC Init structure definition **/
typedef struct
{
    uint32_t TriggerSelect;       /* Specifies the external trigger for the selected DAC  */

    uint32_t WaveGeneration;      /* Specifies whether DAC  noise waves or triangle waves
                                     are generated, or whether no wave is generated */

    uint32_t LfsrUnMaskTriAmp;    /* Specifies the LFSR mask for noise wave generation or the maximum
                                     amplitude triangle generation for the DAC  */

    uint32_t OutputBuffer;        /* Specifies whether the DAC  output buffer is enabled or disabled */

    uint32_t OutputHighDriver;    /* Specifies whether the DAC  output high driver ability is enabled or disabled */
} DAC_InitType;

/** DAC align mode enmu definition **/
typedef enum
{
    DAC_ALIGN_R_8BIT  = 0,
    DAC_ALIGN_L_12BIT = 1,
    DAC_ALIGN_R_12BIT = 2,
} DAC_ALIGN_MODE; 

/*** DAC Structure Definition End ***/


/*** DAC Macro Definition Start ***/

/** DAC register bit field mask definition **/
#define DAC_REG_BIT_FIELD_MASK          ((uint32_t)0x00000000)

/** DAC trigger selection definition **/
#define DAC_TRIGGER_MASK      ((uint32_t)(~(DAC_CTRL_TSEL | DAC_CTRL_TEN)) )
#define DAC_TRIGGER_NONE      ((uint32_t)(DAC_REG_BIT_FIELD_MASK)) /* Conversion is automatic once the DAC_DHRxxxx register 
                                                                      has been loaded, and not by external trigger */
#define DAC_TRIGGER_TIM1_TRGO ((uint32_t)(DAC_CTRL_TEN))           /* TIM1 TRGO selected as external conversion trigger */
#define DAC_TRIGGER_TIM2_TRGO ((uint32_t)(DAC_CTRL_TEN    \
                                        | DAC_CTRL_TSEL_0))        /* TIM2 TRGO selected as external conversion trigger */
#define DAC_TRIGGER_TIM3_TRGO ((uint32_t)(DAC_CTRL_TEN    \
                                        | DAC_CTRL_TSEL_1))        /* TIM3 TRGO selected as external conversion trigger */
#define DAC_TRIGGER_TIM4_TRGO ((uint32_t)(DAC_CTRL_TEN    \
                                        | DAC_CTRL_TSEL_0 \
                                        | DAC_CTRL_TSEL_1))        /* TIM4 TRGO selected as external conversion trigger */
#define DAC_TRIGGER_TIM6_TRGO ((uint32_t)(DAC_CTRL_TEN    \
                                        | DAC_CTRL_TSEL_2))        /* TIM6 TRGO selected as external conversion trigger */
#define DAC_TRIGGER_EXT_LINE9 ((uint32_t)(DAC_CTRL_TEN    \
                                        | DAC_CTRL_TSEL_0 \
                                        | DAC_CTRL_TSEL_2))        /* EXTI Line9 event selected as external conversion trigger */
#define DAC_TRIGGER_SOFTWARE  ((uint32_t)(DAC_CTRL_TEN    \
                                        | DAC_CTRL_TSEL_1 \
                                        | DAC_CTRL_TSEL_2))        /* Conversion started by software trigger for DAC  */

/** DAC wave generation definition **/
#define DAC_WAVEGEN_MASK      ((uint32_t)(~DAC_CTRL_WEN))
#define DAC_WAVEGEN_NONE      ((uint32_t)0x00000000)
#define DAC_WAVEGEN_NOISE     ((uint32_t)(DAC_CTRL_WEN_0))
#define DAC_WAVEGEN_TRIANGLE  ((uint32_t)(DAC_CTRL_WEN_1))

/** DAC LFSR unmask Triangle Amplitude definition **/
#define DAC_MASEL_MASK     ((uint32_t)(~DAC_CTRL_MASEL)) 

#define DAC_LFSR_UNMASK_BIT0     ((uint32_t)0x00000000) /* Unmask DAC  LFSR bit0 for noise wave generation */
#define DAC_LFSR_UNMASK_BIT1_0   ((uint32_t)(DAC_CTRL_MASEL_0)) /* Unmask DAC  LFSR bit[1:0] for noise wave generation */
#define DAC_LFSR_UNMASK_BIT2_0   ((uint32_t)(DAC_CTRL_MASEL_1)) /* Unmask DAC  LFSR bit[2:0] for noise wave generation */
#define DAC_LFSR_UNMASK_BIT3_0   ((uint32_t)(DAC_CTRL_MASEL_0 \
                                           | DAC_CTRL_MASEL_1)) /* Unmask DAC  LFSR bit[3:0] for noise wave generation */
#define DAC_LFSR_UNMASK_BIT4_0   ((uint32_t)(DAC_CTRL_MASEL_2)) /* Unmask DAC  LFSR bit[4:0] for noise wave generation */
#define DAC_LFSR_UNMASK_BIT5_0   ((uint32_t)(DAC_CTRL_MASEL_0 \
                                           | DAC_CTRL_MASEL_2)) /* Unmask DAC  LFSR bit[5:0] for noise wave generation */
#define DAC_LFSR_UNMASK_BIT6_0   ((uint32_t)(DAC_CTRL_MASEL_1 \
                                           | DAC_CTRL_MASEL_2)) /* Unmask DAC  LFSR bit[6:0] for noise wave generation */
#define DAC_LFSR_UNMASK_BIT7_0   ((uint32_t)(DAC_CTRL_MASEL_0 \
                                           | DAC_CTRL_MASEL_1 \
                                           | DAC_CTRL_MASEL_2)) /* Unmask DAC  LFSR bit[7:0] for noise wave generation */
#define DAC_LFSR_UNMASK_BIT8_0   ((uint32_t)(DAC_CTRL_MASEL_3)) /* Unmask DAC  LFSR bit[8:0] for noise wave generation */
#define DAC_LFSR_UNMASK_BIT9_0   ((uint32_t)(DAC_CTRL_MASEL_0 \
                                           | DAC_CTRL_MASEL_3)) /* Unmask DAC  LFSR bit[9:0] for noise wave generation */
#define DAC_LFSR_UNMASK_BIT10_0  ((uint32_t)(DAC_CTRL_MASEL_1 \
                                           | DAC_CTRL_MASEL_3)) /* Unmask DAC  LFSR bit[10:0] for noise wave generation */
#define DAC_LFSR_UNMASK_BIT11_0  ((uint32_t)(DAC_CTRL_MASEL_0 \
                                           | DAC_CTRL_MASEL_1 \
                                           | DAC_CTRL_MASEL_3)) /* Unmask DAC  LFSR bit[11:0] for noise wave generation */

#define DAC_TRIANGLE_AMP_1       ((uint32_t)0x00000000)         /* Select max triangle amplitude of 1 */
#define DAC_TRIANGLE_AMP_3       ((uint32_t)(DAC_CTRL_MASEL_0)) /* Select max triangle amplitude of 3 */
#define DAC_TRIANGLE_AMP_7       ((uint32_t)(DAC_CTRL_MASEL_1)) /* Select max triangle amplitude of 7 */
#define DAC_TRIANGLE_AMP_15      ((uint32_t)(DAC_CTRL_MASEL_0 \
                                           | DAC_CTRL_MASEL_1)) /* Select max triangle amplitude of 15 */
#define DAC_TRIANGLE_AMP_31      ((uint32_t)(DAC_CTRL_MASEL_2)) /* Select max triangle amplitude of 31 */
#define DAC_TRIANGLE_AMP_63      ((uint32_t)(DAC_CTRL_MASEL_0 \
                                           | DAC_CTRL_MASEL_2)) /* Select max triangle amplitude of 63 */
#define DAC_TRIANGLE_AMP_127     ((uint32_t)(DAC_CTRL_MASEL_1 \
                                           | DAC_CTRL_MASEL_2)) /* Select max triangle amplitude of 127 */
#define DAC_TRIANGLE_AMP_255     ((uint32_t)(DAC_CTRL_MASEL_0 \
                                           | DAC_CTRL_MASEL_1 \
                                           | DAC_CTRL_MASEL_2)) /* Select max triangle amplitude of 255 */
#define DAC_TRIANGLE_AMP_511     ((uint32_t)(DAC_CTRL_MASEL_3)) /* Select max triangle amplitude of 511 */
#define DAC_TRIANGLE_AMP_1023    ((uint32_t)(DAC_CTRL_MASEL_0 \
                                           | DAC_CTRL_MASEL_3)) /* Select max triangle amplitude of 1023 */
#define DAC_TRIANGLE_AMP_2047    ((uint32_t)(DAC_CTRL_MASEL_1 \
                                           | DAC_CTRL_MASEL_3)) /* Select max triangle amplitude of 2047 */
#define DAC_TRIANGLE_AMP_4095    ((uint32_t)(DAC_CTRL_MASEL_0 \
                                           | DAC_CTRL_MASEL_1 \
                                           | DAC_CTRL_MASEL_3)) /* Select max triangle amplitude of 4095 */

/** DAC output buffer definition **/
#define DAC_OUTPUT_BUF_ENABLE  ((uint32_t)DAC_CTRL_BEN)
#define DAC_OUTPUT_BUF_DISABLE ((uint32_t)0x00000000)

/** DAC output high driver definition **/
#define DAC_OUTPUT_HIGH_DRIVER_ENABLE  ((uint32_t)DAC_CTRL_BDASEL)
#define DAC_OUTPUT_HIGH_DRIVER_DISABLE ((uint32_t)0x00000000)

/** DAC Enable/Disable definition **/
#define DAC_ENABLE  ((uint32_t)(DAC_CTRL_CHEN))
#define DAC_DISABLE ((uint32_t)0x00000000)

/** DAC Enable/Disable definition **/
#define DAC_DMA_ENABLE  ((uint32_t)(DAC_CTRL_DMAEN))
#define DAC_DMA_DISABLE ((uint32_t)0x00000000)

/** DAC Enable/Disable software trigger definition **/
#define DAC_SW_TRIGGER_ENABLE  ((uint32_t)(DAC_SOTTR_SWTREN))
#define DAC_SW_TRIGGER_DISABLE ((uint32_t)0x00000000)

/*** DAC Macro Definition End ***/

/*** DAC Driving Functions Declaration ***/
void DAC_DeInit(void);
void DAC_TriggerConfig(uint32_t Trigger);
void DAC_WaveGenerationConfig(uint32_t WaveGeneration);
void DAC_LFSRUnmaskTriangleAmplitudeConfig(uint32_t unmaskBit_amplitude);
void DAC_OutputBufferConfig(FunctionalState Cmd);
void DAC_HighDriverOutput(FunctionalState Cmd);
void DAC_Init(DAC_InitType* DAC_InitStruct);
void DAC_InitStruct(DAC_InitType* DAC_InitStruct);
void DAC_Enable(FunctionalState Cmd);
void DAC_DmaEnable(FunctionalState Cmd);
void DAC_SoftTrgEnable(FunctionalState Cmd);
void DAC_SetChData(uint32_t DAC_Align, uint16_t Data);
uint16_t DAC_GetOutputDataVal(void);

#ifdef __cplusplus
}
#endif

#endif /* __N32A052_DAC_H__ */


