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
*\*\file n32a052_adc.h
*\*\author Nations 
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/


#ifndef __N32A052_ADC_H__
#define __N32A052_ADC_H__

#ifdef __cplusplus
extern "C" {
#endif
	
#include "n32a052.h"

/** ADC init structure definition **/
typedef struct
{
    FunctionalState MultiChEn;      /* Specifies whether the conversion is performed in
                                       Scan (multichannels) or Single (one channel) mode */

    FunctionalState ContinueConvEn; /* Specifies whether the conversion is performed in
                                       Continuous or Single mode */

    uint32_t ExtTrigSelect;         /* Defines the external trigger used to start the analog
                                       to digital conversion of regular channels */

    uint32_t DatAlign;              /* Specifies whether the ADC data alignment is left or right */

    uint32_t ChsNumber;             /* Specifies the number of ADC channels that will be converted
                                       using the sequencer for regular channel group */
} ADC_InitType;

/** ADC clock mode define **/
typedef enum
{
    ADC_CKMOD_AHB = 0,
    ADC_CKMOD_PLL = 1,
    ADC_CKMOD_HSI = 2,
}ADC_CKMOD;

/** ADC external trigger sources for regular channels conversion define **/
#define ADC_EXT_TRIGCONV_REGULAR_MASK        ((uint32_t)(~(ADC_CTRL2_EXTRSEL|ADC_CTRL2_EXTRTRIG))) /* ADC_CTRL2 EXTRSEL[3:0] bits Mask */
#define ADC_EXT_TRIGCONV_REGULAR_T1_TRGO     ((uint32_t)(0x00000000U|ADC_CTRL2_EXTRTRIG)) 
#define ADC_EXT_TRIGCONV_REGULAR_T1_CC1      ((uint32_t)(0x00000008U|ADC_CTRL2_EXTRTRIG)) 
#define ADC_EXT_TRIGCONV_REGULAR_T1_CC2      ((uint32_t)(0x00000010U|ADC_CTRL2_EXTRTRIG))
#define ADC_EXT_TRIGCONV_REGULAR_T1_CC3      ((uint32_t)(0x00000018U|ADC_CTRL2_EXTRTRIG)) 
#define ADC_EXT_TRIGCONV_REGULAR_T2_TRGO     ((uint32_t)(0x00000020U|ADC_CTRL2_EXTRTRIG)) 
#define ADC_EXT_TRIGCONV_REGULAR_T2_CC1      ((uint32_t)(0x00000028U|ADC_CTRL2_EXTRTRIG)) 
#define ADC_EXT_TRIGCONV_REGULAR_T2_CC2      ((uint32_t)(0x00000030U|ADC_CTRL2_EXTRTRIG)) 
#define ADC_EXT_TRIGCONV_REGULAR_T3_TRGO     ((uint32_t)(0x00000038U|ADC_CTRL2_EXTRTRIG)) 
#define ADC_EXT_TRIGCONV_REGULAR_T3_CC1      ((uint32_t)(0x00000040U|ADC_CTRL2_EXTRTRIG)) 
#define ADC_EXT_TRIGCONV_REGULAR_T3_CC2      ((uint32_t)(0x00000048U|ADC_CTRL2_EXTRTRIG))
#define ADC_EXT_TRIGCONV_REGULAR_T4_CC1      ((uint32_t)(0x00000050U|ADC_CTRL2_EXTRTRIG))
#define ADC_EXT_TRIGCONV_REGULAR_T4_CC4      ((uint32_t)(0x00000058U|ADC_CTRL2_EXTRTRIG))
#define ADC_EXT_TRIGCONV_REGULAR_T5_CC1      ((uint32_t)(0x00000060U|ADC_CTRL2_EXTRTRIG))
#define ADC_EXT_TRIGCONV_REGULAR_T5_CC4      ((uint32_t)(0x00000068U|ADC_CTRL2_EXTRTRIG))
#define ADC_EXT_TRIGCONV_REGULAR_EXT_LINE    ((uint32_t)(0x00000070U|ADC_CTRL2_EXTRTRIG)) 
#define ADC_EXT_TRIGCONV_REGULAR_SWSTRRCH    ((uint32_t)0x00000078U) 

/** ADC data alignment define **/
#define ADC_DAT_ALIGN_R                      ((uint32_t)0x00000000U)        /* ADC_CTRL2 ALIG bits */
#define ADC_DAT_ALIGN_L                      ((uint32_t)ADC_CTRL2_ALIG)

/** ADC DMA mode define **/
#define ADC_DMA_ENABLE                       ((uint32_t)ADC_CTRL2_ENDMA)   /* ADC_CTRL2 DMA bits Mask */

/** ADC regular channel sequence length define **/
#define ADC_REGULAR_LEN_MSAK                 ((uint32_t)(~ADC_CTRL2_LEN)) /* ADC_CTRL2 LEN[2:0] bits Mask */
#define ADC_REGULAR_LEN_1                    ((uint32_t)0x00000000U)
#define ADC_REGULAR_LEN_2                    ((uint32_t)0x00000200U)
#define ADC_REGULAR_LEN_3                    ((uint32_t)0x00000400U)
#define ADC_REGULAR_LEN_4                    ((uint32_t)0x00000600U)
#define ADC_REGULAR_LEN_5                    ((uint32_t)0x00000800U)

/** ADC channels define **/
#define ADC_SQR_MASK                         ((uint32_t)~(ADC_DAT0_SEQ0))
#define ADC_SQR_OFFSET                       ((uint32_t)0x10U)
#define ADC_CH_0                             ((uint8_t)0x00U)
#define ADC_CH_1                             ((uint8_t)0x01U)
#define ADC_CH_2                             ((uint8_t)0x02U)
#define ADC_CH_3                             ((uint8_t)0x03U)
#define ADC_CH_4                             ((uint8_t)0x04U)
#define ADC_CH_5                             ((uint8_t)0x05U)
#define ADC_CH_6                             ((uint8_t)0x06U)
#define ADC_CH_7                             ((uint8_t)0x07U)
#define ADC_CH_8                             ((uint8_t)0x08U)
#define ADC_CH_9                             ((uint8_t)0x09U)
#define ADC_CH_10                            ((uint8_t)0x0AU)
#define ADC_CH_11                            ((uint8_t)0x0BU)
#define ADC_CH_12                            ((uint8_t)0x0CU)
#define ADC_CH_13                            ((uint8_t)0x0DU)
#define ADC_CH_14                            ((uint8_t)0x0EU)
#define ADC_CH_15                            ((uint8_t)0x0FU)
#define ADC_CH_16                            ((uint8_t)0x10U)
#define ADC_CH_TS                            ((uint8_t)ADC_CH_15)
#define ADC_CH_VREFINT                       ((uint8_t)ADC_CH_16)

#define ADC_Channel_00_PA0                   ((uint8_t)0x00U)
#define ADC_Channel_01_PA1                   ((uint8_t)0x01U)
#define ADC_Channel_02_PA2                   ((uint8_t)0x02U)
#define ADC_Channel_03_PA3                   ((uint8_t)0x03U)
#define ADC_Channel_04_PA4                   ((uint8_t)0x04U)
#define ADC_Channel_05_PA5                   ((uint8_t)0x05U)
#define ADC_Channel_06_PA6                   ((uint8_t)0x06U)
#define ADC_Channel_07_PA7                   ((uint8_t)0x07U)
#define ADC_Channel_08_PB0                   ((uint8_t)0x08U)
#define ADC_Channel_09_PB1                   ((uint8_t)0x09U)
#define ADC_Channel_10_PB2                   ((uint8_t)0x0AU)
#define ADC_Channel_11_PB10                  ((uint8_t)0x0BU)
#define ADC_Channel_12_PB11                  ((uint8_t)0x0CU)
#define ADC_Channel_13_PB12                  ((uint8_t)0x0DU)
#define ADC_Channel_14_PB3                   ((uint8_t)0x0EU)
#define ADC_Channel_15_TS                    ((uint8_t)0x0FU)
#define ADC_Channel_16_VREFINT               ((uint8_t)0x10U)
/** ADC converter operation define **/
#define ADC_TURN_ON                          ((uint32_t)ADC_CTRL2_ON)    /* A/D Converter ON / OFF */

/** ADC interrupts define **/
#define ADC_INT_ENDC                         ((uint32_t)ADC_CTRL1_ENDCIEN)   /* Interrupt enable for EOC */
#define ADC_INT_AWD                          ((uint32_t)ADC_CTRL1_AWDGIEN)   /* Analog Watchdog interrupt enable */
#define ADC_INT_ENDCA                        ((uint32_t)ADC_CTRL3_ENDCAIEN)  /* Interrupt enable for any EOC */
#define ADC_SET_INT_TYPE_ENDCA               ((uint8_t) 0x01)  /* Interrupt enable for any EOCA */
#define ADC_SET_INT_TYPE_OTHER               ((uint8_t) 0x00)  /* Interrupt enable for other */

/** ADC external triagger conversion definition **/ 
#define ADC_EXTTRIGCONV_REGULAR_ENABLE       ((uint32_t)ADC_CTRL2_EXTRTRIG)
/** ADC software triagger start conversion definition **/ 
#define ADC_EXTRTRIG_SWSTRRCH_ENABLE         ((uint32_t)(ADC_CTRL2_SWSTRRCH | ADC_CTRL2_EXTRTRIG))


/** ADC sampling time define **/
#define ADC_SAMP_TIME_MASK                   ((uint32_t)~ADC_SAMPT_SAMP)
#define ADC_SAMP_TIME_6CYCLES                ((uint32_t)0x00000000U)
#define ADC_SAMP_TIME_8CYCLES                ((uint32_t)0x00000001U)
#define ADC_SAMP_TIME_12CYCLES               ((uint32_t)0x00000002U)
#define ADC_SAMP_TIME_14CYCLES               ((uint32_t)0x00000003U)
#define ADC_SAMP_TIME_20CYCLES               ((uint32_t)0x00000004U)
#define ADC_SAMP_TIME_26CYCLES               ((uint32_t)0x00000005U)
#define ADC_SAMP_TIME_30CYCLES               ((uint32_t)0x00000006U)
#define ADC_SAMP_TIME_42CYCLES               ((uint32_t)0x00000007U)
#define ADC_SAMP_TIME_56CYCLES               ((uint32_t)0x00000008U)
#define ADC_SAMP_TIME_72CYCLES               ((uint32_t)0x00000009U)
#define ADC_SAMP_TIME_88CYCLES               ((uint32_t)0x0000000AU)
#define ADC_SAMP_TIME_120CYCLES              ((uint32_t)0x0000000BU)
#define ADC_SAMP_TIME_182CYCLES              ((uint32_t)0x0000000CU)
#define ADC_SAMP_TIME_240CYCLES              ((uint32_t)0x0000000DU)
#define ADC_SAMP_TIME_380CYCLES              ((uint32_t)0x0000000EU)
#define ADC_SAMP_TIME_760CYCLES              ((uint32_t)0x0000000FU)
#define ADC_SAMP_TIME_1520CYCLES             ((uint32_t)0x00000010U)
#define ADC_SAMP_TIME_3040CYCLES             ((uint32_t)0x00000011U)

/** ADC analog watchdog mode define **/
#define ADC_ANALOG_WTDG_MODE_MASK            ((uint32_t)(~ADC_CTRL1_AWDGSGLEN))
#define ADC_ANALOG_WTDG_SINGLE_MODE          ((uint32_t)ADC_CTRL1_AWDGSGLEN)/* Enable the watchdog on a single channel in scan mode */
#define ADC_ANALOG_WTDG_SCAN_MODE            ((uint32_t)0x00000000U)


/** ADC analog watchdog single mode channel define**/
#define ADC_ANALOG_WTDG_SINGLE_CH_MASK       ((uint32_t)(~ADC_CTRL1_AWDGCH))/* AWDG_CH[4:0] bits (Analog watchdog channel select bits) */
#define ADC_ANALOG_WTDG_SINGLE_CH0           ((uint8_t)0x00000000U)
#define ADC_ANALOG_WTDG_SINGLE_CH1           ((uint8_t)0x00000001U)
#define ADC_ANALOG_WTDG_SINGLE_CH2           ((uint8_t)0x00000002U)
#define ADC_ANALOG_WTDG_SINGLE_CH3           ((uint8_t)0x00000003U)
#define ADC_ANALOG_WTDG_SINGLE_CH4           ((uint8_t)0x00000004U)
#define ADC_ANALOG_WTDG_SINGLE_CH5           ((uint8_t)0x00000005U)
#define ADC_ANALOG_WTDG_SINGLE_CH6           ((uint8_t)0x00000006U)
#define ADC_ANALOG_WTDG_SINGLE_CH7           ((uint8_t)0x00000007U)
#define ADC_ANALOG_WTDG_SINGLE_CH8           ((uint8_t)0x00000008U)
#define ADC_ANALOG_WTDG_SINGLE_CH9           ((uint8_t)0x00000009U)
#define ADC_ANALOG_WTDG_SINGLE_CH10          ((uint8_t)0x0000000AU)
#define ADC_ANALOG_WTDG_SINGLE_CH11          ((uint8_t)0x0000000BU)
#define ADC_ANALOG_WTDG_SINGLE_CH12          ((uint8_t)0x0000000CU)
#define ADC_ANALOG_WTDG_SINGLE_CH13          ((uint8_t)0x0000000DU)
#define ADC_ANALOG_WTDG_SINGLE_CH14          ((uint8_t)0x0000000EU)
#define ADC_ANALOG_WTDG_SINGLE_CH15          ((uint8_t)0x0000000FU)
#define ADC_ANALOG_WTDG_SINGLE_CH16          ((uint8_t)0x00000010U)
/** ADC ADC Analog watchdog on regular channels define **/
#define ADC_ANALOG_WTDG_REGULAR              ((uint32_t)ADC_CTRL1_AWDGERCH)    /* ADC_CTRL1 AWDGERCH bit */

/** ADC flags definition **/
#define ADC_INT_FLAG_AWDG                    ((uint8_t)ADC_STS_AWDG)
#define ADC_INT_FLAG_ENDC                    ((uint8_t)ADC_STS_ENDC)
#define ADC_INT_FLAG_ENDCA                   ((uint8_t)ADC_STS_ENDCA)

#define ADC_FLAG_AWDG                        ((uint8_t)ADC_STS_AWDG)
#define ADC_FLAG_ENDC                        ((uint8_t)ADC_STS_ENDC)
#define ADC_FLAG_STR                         ((uint8_t)ADC_STS_STR)
#define ADC_FLAG_ENDCA                       ((uint8_t)ADC_STS_ENDCA)
/** ADC flags ex definition **/
#define ADC_FLAG_BUF_RDY                     ((uint8_t)0x04U)
#define ADC_FLAG_RDY                         ((uint8_t)ADC_CTRL3_RDY)
#define ADC_FLAG_PD_RDY                      ((uint8_t)ADC_CTRL3_PDRDY)

/** ADC regular data register define **/
#define ADC_DATA_OFFSET0                      ((uint8_t)0x00U)
#define ADC_DATA_OFFSET1                      ((uint8_t)0X01U)
#define ADC_DATA_OFFSET2                      ((uint8_t)0X02U)
#define ADC_DATA_OFFSET3                      ((uint8_t)0X03U)
#define ADC_DATA_OFFSET4                      ((uint8_t)0X04U)

/** ADC internal input buffer  definition **/ 
#define ADC_IN_BUFFER_ENABLE                  ((uint32_t)ADC_CTRL3_VREFEN)    /*ADC internal input buffer enable.*/

/** ADC Reference source select  definition **/ 
#define ADC_REF_SEL_VREF                      ((uint32_t)(ADC_CTRL1_REFSEL))

/* ADC data registers read define */
#define ADC_DATA_REG_READ(data, num)          (*(uint32_t*)((uint32_t)&data + 4*num))


/** ADC Driving Functions Declaration **/
void ADC_DeInit(void);

void ADC_Init(ADC_InitType* ADC_initstruct);
void ADC_InitStruct(ADC_InitType* ADC_initstruct);

void ADC_Enable(FunctionalState Cmd);
void ADC_EnableDMA(FunctionalState Cmd);
void ADC_ConfigInt(u8 eoc_any, uint16_t ADC_IT, FunctionalState Cmd);

void ADC_EnableSoftwareStartConv(FunctionalState Cmd);
FlagStatus ADC_GetSoftwareStartConvStatus(void);

void ADC_ConfigChannelSampleTime(uint32_t sample_time);
void ADC_EnableExternalTriggerConversion(FunctionalState Cmd);

uint16_t ADC_GetDat(void);
uint16_t ADC_GetGroupConvDat(uint8_t number);

void ADC_ConfigAnalogWatchdogModeChannel(uint32_t mode, uint8_t channel);
void ADC_EnableAnalogWatchdog(FunctionalState Cmd);
void ADC_ConfigAnalogWatchdogThresholds(uint16_t HighThreshold, uint16_t LowThreshold);

FlagStatus ADC_GetFlagStatus(uint8_t ADC_FLAG);
FlagStatus ADC_GetFlagStatusNew(uint8_t ADC_FLAG_NEW);
void ADC_ClearFlag(uint8_t ADC_FLAG);
INTStatus ADC_GetIntStatus(uint16_t ADC_IT);
void ADC_ClearIntPendingBit(uint16_t ADC_IT);

void ADC_ConfigRegularSequenceSingle(uint8_t channel);
void ADC_ConfigRegularSequenceMulti(uint8_t channel,uint8_t number);

void ADC_EnableInternalInputBuffer(FunctionalState Cmd);
void ADC_EnableTempSensor(FunctionalState Cmd);
void ADC_EnableVREFPAsReferenceVoltag(FunctionalState Cmd);
void ADC_ClockModeConfig(ADC_CKMOD ADC_clkmode, uint32_t RCC_ADCHCLKprescaler);
#ifdef __cplusplus
}
#endif

#endif /*__N32A052_ADC_H__ */

