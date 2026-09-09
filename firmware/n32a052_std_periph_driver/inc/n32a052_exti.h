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

/***
*\*\file n32a052_exti.h
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
***/

#ifndef __N32A052_EXTI_H
#define __N32A052_EXTI_H

#ifdef __cplusplus
 extern "C" {
#endif
	 
#include "n32a052.h"
	 
/*** EXTI Structure Definition Start ***/

/** EXTI Init Structure definition **/
typedef struct
{
    uint32_t EXTI_Line;   /* < Specifies the EXTI lines to be enabled or disabled */

    uint8_t EXTI_Mode;    /* < Specifies the mode for the EXTI lines */

    uint8_t EXTI_Trigger; /* < Specifies the trigger signal active edge for the EXTI lines */
    
    FunctionalState EXTI_LineCmd;  /* Specifies the new state of the selected EXTI lines. */
} EXTI_InitType;

/** EXTI mode enumeration **/
typedef enum
{
    EXTI_Mode_Event      = 0x00U,
    EXTI_Mode_Interrupt  = 0x04U
} EXTI_ModeType;

/** EXTI Trigger enumeration **/
typedef enum
{   
    EXTI_Trigger_Falling         = 0x08U,
    EXTI_Trigger_Rising          = 0x0CU,
    EXTI_Trigger_Rising_Falling  = 0x10U
} EXTI_TriggerType;

/*** EXTI Structure Definition End ***/


/*** EXTI Macro Definition Start ***/

#define EXTI_IMASK_MASK  ((uint32_t)0x001FFFFFU)
#define EXTI_EMASK_MASK  ((uint32_t)0x001FFFFFU)
#define EXTI_RT_CFG_MASK ((uint32_t)0x001FFFFFU)
#define EXTI_FT_CFG_MASK ((uint32_t)0x001FFFFFU)
#define EXTI_PEND_MASK   ((uint32_t)0x001FFFFFU)


/** EXTI_TSSEL_Line **/
#define EXTI_TSSEL_LINE_MASK ((uint32_t)0x00000U)
#define EXTI_TSSEL_LINE0     ((uint32_t)0x00000U) /** External interrupt line 0 **/
#define EXTI_TSSEL_LINE1     ((uint32_t)0x00001U) /** External interrupt line 1 **/
#define EXTI_TSSEL_LINE2     ((uint32_t)0x00002U) /** External interrupt line 2 **/
#define EXTI_TSSEL_LINE3     ((uint32_t)0x00003U) /** External interrupt line 3 **/
#define EXTI_TSSEL_LINE4     ((uint32_t)0x00004U) /** External interrupt line 4 **/
#define EXTI_TSSEL_LINE5     ((uint32_t)0x00005U) /** External interrupt line 5 **/
#define EXTI_TSSEL_LINE6     ((uint32_t)0x00006U) /** External interrupt line 6 **/
#define EXTI_TSSEL_LINE7     ((uint32_t)0x00007U) /** External interrupt line 7 **/
#define EXTI_TSSEL_LINE8     ((uint32_t)0x00008U) /** External interrupt line 8 **/
#define EXTI_TSSEL_LINE9     ((uint32_t)0x00009U) /** External interrupt line 9 **/
#define EXTI_TSSEL_LINE10    ((uint32_t)0x0000AU) /** External interrupt line 10 **/
#define EXTI_TSSEL_LINE11    ((uint32_t)0x0000BU) /** External interrupt line 11 **/
#define EXTI_TSSEL_LINE12    ((uint32_t)0x0000CU) /** External interrupt line 12 **/
#define EXTI_TSSEL_LINE13    ((uint32_t)0x0000DU) /** External interrupt line 13 **/
#define EXTI_TSSEL_LINE14    ((uint32_t)0x0000EU) /** External interrupt line 14 **/
#define EXTI_TSSEL_LINE15    ((uint32_t)0x0000FU) /** External interrupt line 15 **/

/** EXTI_Lines **/
#define EXTI_LINENONE ((uint32_t)0x00000U) /** No interrupt selected **/
#define EXTI_LINE0    ((uint32_t)0x00001U)   /** External interrupt line 0 **/
#define EXTI_LINE1    ((uint32_t)0x00002U)   /** External interrupt line 1 **/
#define EXTI_LINE2    ((uint32_t)0x00004U)   /** External interrupt line 2 **/
#define EXTI_LINE3    ((uint32_t)0x00008U)   /** External interrupt line 3 **/
#define EXTI_LINE4    ((uint32_t)0x00010U)   /** External interrupt line 4 **/
#define EXTI_LINE5    ((uint32_t)0x00020U)   /** External interrupt line 5 **/
#define EXTI_LINE6    ((uint32_t)0x00040U)   /** External interrupt line 6 **/
#define EXTI_LINE7    ((uint32_t)0x00080U)   /** External interrupt line 7 **/
#define EXTI_LINE8    ((uint32_t)0x00100U)   /** External interrupt line 8 **/
#define EXTI_LINE9    ((uint32_t)0x00200U)   /** External interrupt line 9 **/
#define EXTI_LINE10   ((uint32_t)0x00400U)   /** External interrupt line 10 **/
#define EXTI_LINE11   ((uint32_t)0x00800U)   /** External interrupt line 11 **/
#define EXTI_LINE12   ((uint32_t)0x01000U)   /** External interrupt line 12 **/
#define EXTI_LINE13   ((uint32_t)0x02000U)   /** External interrupt line 13 **/
#define EXTI_LINE14   ((uint32_t)0x04000U)   /** External interrupt line 14 **/
#define EXTI_LINE15   ((uint32_t)0x08000U)   /** External interrupt line 15 **/
#define EXTI_LINE16   ((uint32_t)0x10000U)   /** External interrupt line 16 Connected to the PVD Output **/
#define EXTI_LINE17   ((uint32_t)0x20000U)   /** External interrupt line 17 Connected to the USB Device/USB OTG FS Wakeup from suspend event **/
#define EXTI_LINE18   ((uint32_t)0x40000U)   /** External interrupt line 18 Connected to the RTC Alarm event **/
#define EXTI_LINE19   ((uint32_t)0x80000U)   /** External interrupt line 19 Connected to the RTC Time stamp event **/
#define EXTI_LINE20   ((uint32_t)0x100000U)  /** External interrupt line 20 Connected to the RTC Wakeup event */

/** EXTI_Mode definition**/
#define EXTI_MODE_INT   (0x00U)
#define EXTI_MODE_EVENT (0x04U)

/** EXTI Trigger enumeration **/
#define EXTI_TRIGGER_RISING         (0x08U)
#define EXTI_TRIGGER_FALLING        (0x0CU)
#define EXTI_TRIGGER_RISING_FALLING (0x10U)


/*** EXTI Macro Definition End ***/

/** EXTI Driving Functions Declaration **/
void EXTI_DeInit(void);
void EXTI_InitPeripheral(const EXTI_InitType* EXTI_InitStruct);
void EXTI_InitStruct(EXTI_InitType* EXTI_StructInit);
void EXTI_TriggerSWInt(uint32_t EXTI_Line);
FlagStatus EXTI_GetStatusFlag(uint32_t EXTI_Line);
void EXTI_ClrStatusFlag(uint32_t EXTI_Line);
INTStatus EXTI_GetITStatus(uint32_t EXTI_Line);
void EXTI_ClrITPendBit(uint32_t EXTI_Line);
void EXTI_RTCTimeStampSel(uint32_t EXTI_TSSEL_Line);


#ifdef __cplusplus
}
#endif

#endif /* __N32A052_EXTI_H__ */

