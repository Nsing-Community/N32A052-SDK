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
*\*\file n32a052_pwr.h
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/

#ifndef __N32A052_PWR_H__
#define __N32A052_PWR_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32a052.h"

/*** PWR Structure Definition Start ***/	

/** PWR sleep status enmu definition **/
typedef enum
{
    PWR_SLEEP_NOW = 0,
    PWR_SLEEP_ON_EXIT = 1,
} PWR_SLEEPONEXIT_STATUS; 

/** PWR wakeup PINx enmu definition **/
typedef enum
{
    WKUP_PIN1 = 0x0100,
    WKUP_PIN2 = 0x0200,
} WAKEUP_PINX;

/** PWR wakeup PIN polarity enmu definition **/
typedef enum
{
    WKUP_POL_DOWN = 0x00,
    WKUP_POL_RISE = 0x01,
} WAKEUP_PIN_POL;

/*** PWR Structure Definition End ***/

/*** PWR Macro Definition Start ***/

/** PWR register bit mask definition **/
#define PWR_CTRL_PLS_MASK        (~(PWR_CTRL_PLS))
#define PWR_CTRL_PDSTP_MASK      (~(PWR_CTRL_PDSTP))
#define PWR_CTRL_PDRS_MASK       (~(PWR_CTRL_PDRS))
#define PWR_CTRL_PVDCNT_MASK     (~(PWR_CTRL_PVDCNT))
#define PWR_REG_BIT_MASK         ((uint32_t)0x00000000)

/** PWR CTRL2 register bit mask definition **/
#define PWR_CTRL2_LVRLS_MASK     (~(PWR_CTRL2_LVRLS))
#define PWR_CTRL2_LVRCNT_MASK    (~(PWR_CTRL2_LVRCNT))

/** PWR CTRLSTS register bit mask definition **/
#define PWR_CTRLSTS_WKUPPOL_MASK (~(PWR_CTRLSTS_WKUPPOL))

/** PWR CTRL3 register bit mask definition **/
#define PWR_CTRL3_NRSTCNT_MASK    (~(PWR_CTRL3_NRSTCNT))

/** PWR CTRL5 register bit mask definition **/
#define PWR_CTRL5_STPMRSEL_MASK  (~(PWR_CTRL5_STPMRSEL))

/** PWR PVD enable definition **/
#define PWR_PVD_ENABLE             (PWR_CTRL_PVDEN)

/** PWR PVD interrupt enable definition **/
#define PWR_PVD_INT_ENABLE         (PWR_CTRL_PVDITEN)

/** PWR PVD Filter enable definition **/
#define PWR_PVD_FIL_ENABLE         (PWR_CTRL_PVDFILEN)

/** PWR IWDR reset enable definition **/
#define PWR_IWDGRST_ENABLE         (PWR_CTRL_IWDGRSTEN)

/** PWR LVR enable definition **/
#define PWR_LVR_ENABLE             (PWR_CTRL2_LVREN)

/** PWR LVR reset enable definition **/
#define PWR_LVR_RST_ENABLE         (PWR_CTRL2_LVRRSTEN)

/** PWR LVR Filter enable definition **/
#define PWR_LVR_FIL_ENABLE         (PWR_CTRL2_LVRFILEN)

/** PWR clear WKUPF definition **/
#define PWR_CLEAR_WKUPF            (PWR_CTRL_CLRWKUPF)

/** PWR PVD output Flag definition **/
#define PWR_PVDO_FLAG              (0x20000000 | PWR_CTRLSTS_PVDO)

/** PWR PD Flag definition **/
#define PWR_DBGPD_FLAG             (0x20000000 | PWR_CTRLSTS_DBGPDF)

/** PWR PA2/PA0 wakeup Flag definition **/
#define PWR_DBGPD_WKUP_FLAG        (0x20000000 | PWR_CTRLSTS_WKUPF)

/** PWR LVR output Flag definition **/
#define PWR_LVRO_FLAG              (0x40000000 | PWR_CTRL2_LVRO)

/** PWR LVR output Flag definition **/
#define PWR_RUN_FLAG               (0x60000000 | PWR_CTRL4_RUNF)

/** PWR FLASH enters deep standby definition **/
#define PWR_FLASH_DS_ENABLE        (PWR_CTRL4_STBFLH)

/** PWR FLASH for fast wakeup definition **/
#define PWR_FLASH_FW_ENABLE        (PWR_CTRL4_FLHWKUP)

/** PWR PD mode definition **/
#define PWR_PD_MODE                (PWR_CTRL_PDSTP)

/** PWR control PDR select signal definition **/
#define PWR_CONTROL_PDR_SEL        (PWR_CTRL3_PDRSEL)

/** PWR control NRST filter definition **/
#define PWR_NRST_FIL_ENABLE        (PWR_CTRL3_NRSTFILEN)

/** PWR enable VDDD output voltage select definition **/
#define PWR_VDDD_OUTPUT_SEL_EN     (PWR_CTRL6_STPMREN)

/** PWR PVD threshold level definition **/
#define PWR_PVD_LEVEL_2V0 ((uint32_t)(PWR_CTRL_PLS_0))    /* 2.0v PWR_CTRL bit[8:5]:0001 */
#define PWR_PVD_LEVEL_2V2 ((uint32_t)(PWR_CTRL_PLS_1))    /* 2.2v PWR_CTRL bit[8:5]:0010 */
#define PWR_PVD_LEVEL_2V4 ((uint32_t)(PWR_CTRL_PLS_0 \
                                    | PWR_CTRL_PLS_1))    /* 2.4v PWR_CTRL bit[8:5]:0011 */
#define PWR_PVD_LEVEL_2V6 ((uint32_t)(PWR_CTRL_PLS_2))    /* 2.6v PWR_CTRL bit[8:5]:0100 */
#define PWR_PVD_LEVEL_2V8 ((uint32_t)(PWR_CTRL_PLS_0 \
                                    | PWR_CTRL_PLS_2))    /* 2.8v PWR_CTRL bit[8:5]:0101 */
#define PWR_PVD_LEVEL_3V0 ((uint32_t)(PWR_CTRL_PLS_1 \
                                    | PWR_CTRL_PLS_2))    /* 3.0v PWR_CTRL bit[8:5]:0110 */
#define PWR_PVD_LEVEL_3V2 ((uint32_t)(PWR_CTRL_PLS_0 \
                                    | PWR_CTRL_PLS_1 \
                                    | PWR_CTRL_PLS_2))    /* 3.2v PWR_CTRL bit[8:5]:0111 */
#define PWR_PVD_LEVEL_3V4 ((uint32_t)(PWR_CTRL_PLS_3))    /* 3.4v PWR_CTRL bit[8:5]:1000 */
#define PWR_PVD_LEVEL_3V6 ((uint32_t)(PWR_CTRL_PLS_0 \
                                    | PWR_CTRL_PLS_3))    /* 3.6v PWR_CTRL bit[8:5]:1001 */
#define PWR_PVD_LEVEL_3V8 ((uint32_t)(PWR_CTRL_PLS_1 \
                                    | PWR_CTRL_PLS_3))    /* 3.8v PWR_CTRL bit[8:5]:1010 */
#define PWR_PVD_LEVEL_4V0 ((uint32_t)(PWR_CTRL_PLS_0 \
                                    | PWR_CTRL_PLS_1 \
                                    | PWR_CTRL_PLS_3))    /* 4.0v PWR_CTRL bit[8:5]:1011 */
#define PWR_PVD_LEVEL_4V2 ((uint32_t)(PWR_CTRL_PLS_2 \
                                    | PWR_CTRL_PLS_3))    /* 4.2v PWR_CTRL bit[8:5]:1100 */
#define PWR_PVD_LEVEL_4V4 ((uint32_t)(PWR_CTRL_PLS_0 \
                                    | PWR_CTRL_PLS_2 \
                                    | PWR_CTRL_PLS_3))    /* 4.4v PWR_CTRL bit[8:5]:1101 */
#define PWR_PVD_LEVEL_4V6 ((uint32_t)(PWR_CTRL_PLS_1 \
                                    | PWR_CTRL_PLS_2 \
                                    | PWR_CTRL_PLS_3))    /* 4.6v PWR_CTRL bit[8:5]:1110 */
#define PWR_PVD_LEVEL_4V8 ((uint32_t)(PWR_CTRL_PLS_0 \
                                    | PWR_CTRL_PLS_1 \
                                    | PWR_CTRL_PLS_2 \
                                    | PWR_CTRL_PLS_3))    /* 4.8v PWR_CTRL bit[8:5]:1111 */	 

/** PWR LVR threshold level definition **/
#define PWR_LVR_LEVEL_2V0 ((uint32_t)(PWR_CTRL2_LVRLS_0)) /* 2.0v PWR_CTRL2 bit[14:11]:0001 */
#define PWR_LVR_LEVEL_2V2 ((uint32_t)(PWR_CTRL2_LVRLS_1)) /* 2.2v PWR_CTRL2 bit[14:11]:0010 */
#define PWR_LVR_LEVEL_2V4 ((uint32_t)(PWR_CTRL2_LVRLS_0 \
                                    | PWR_CTRL2_LVRLS_1)) /* 2.4v PWR_CTRL2 bit[14:11]:0011 */
#define PWR_LVR_LEVEL_2V6 ((uint32_t)(PWR_CTRL2_LVRLS_2)) /* 2.6v PWR_CTRL2 bit[14:11]:0100 */
#define PWR_LVR_LEVEL_2V8 ((uint32_t)(PWR_CTRL2_LVRLS_0 \
                                    | PWR_CTRL2_LVRLS_2)) /* 2.8v PWR_CTRL2 bit[14:11]:0101 */
#define PWR_LVR_LEVEL_3V0 ((uint32_t)(PWR_CTRL2_LVRLS_1 \
                                    | PWR_CTRL2_LVRLS_2)) /* 3.0v PWR_CTRL2 bit[14:11]:0110 */
#define PWR_LVR_LEVEL_3V2 ((uint32_t)(PWR_CTRL2_LVRLS_0 \
                                    | PWR_CTRL2_LVRLS_1 \
                                    | PWR_CTRL2_LVRLS_2)) /* 3.2v PWR_CTRL2 bit[14:11]:0111 */
#define PWR_LVR_LEVEL_3V4 ((uint32_t)(PWR_CTRL2_LVRLS_3)) /* 3.4v PWR_CTRL2 bit[14:11]:1000 */
#define PWR_LVR_LEVEL_3V6 ((uint32_t)(PWR_CTRL2_LVRLS_0 \
                                    | PWR_CTRL2_LVRLS_3)) /* 3.6v PWR_CTRL2 bit[14:11]:1001 */
#define PWR_LVR_LEVEL_3V8 ((uint32_t)(PWR_CTRL2_LVRLS_1 \
                                    | PWR_CTRL2_LVRLS_3)) /* 3.8v PWR_CTRL2 bit[14:11]:1010 */
#define PWR_LVR_LEVEL_4V0 ((uint32_t)(PWR_CTRL2_LVRLS_0 \
                                    | PWR_CTRL2_LVRLS_1 \
                                    | PWR_CTRL2_LVRLS_3)) /* 4.0v PWR_CTRL2 bit[14:11]:1011 */
#define PWR_LVR_LEVEL_4V2 ((uint32_t)(PWR_CTRL2_LVRLS_2 \
                                    | PWR_CTRL2_LVRLS_3)) /* 4.2v PWR_CTRL2 bit[14:11]:1100 */
#define PWR_LVR_LEVEL_4V4 ((uint32_t)(PWR_CTRL2_LVRLS_0 \
                                    | PWR_CTRL2_LVRLS_2 \
                                    | PWR_CTRL2_LVRLS_3)) /* 4.4v PWR_CTRL2 bit[14:11]:1101 */
#define PWR_LVR_LEVEL_4V6 ((uint32_t)(PWR_CTRL2_LVRLS_1 \
                                    | PWR_CTRL2_LVRLS_2 \
                                    | PWR_CTRL2_LVRLS_3)) /* 4.6v PWR_CTRL2 bit[14:11]:1110 */
#define PWR_LVR_LEVEL_4V8 ((uint32_t)(PWR_CTRL2_LVRLS_0 \
                                    | PWR_CTRL2_LVRLS_1 \
                                    | PWR_CTRL2_LVRLS_2 \
                                    | PWR_CTRL2_LVRLS_3)) /* 4.8v PWR_CTRL2 bit[14:11]:1111 */

/** PWR PDR trigger level definition **/
#define PWR_PDR_LEVEL_1V0 ((uint32_t)(PWR_CTRL_PDRS_1))   /* 1.0v PWR_CTRL bit[10:9]:10 */
#define PWR_PDR_LEVEL_1V2 ((uint32_t)(PWR_CTRL_PDRS_0 \
                                    | PWR_CTRL_PDRS_1))   /* 0.2v PWR_CTRL bit[10:9]:11 */

/** PWR VDDD output voltage definition **/
#define PWR_VDDD_OUTPUT_1V5 ((uint32_t)(PWR_CTRL5_STPMRSEL_0)) /* 1.5v PWR_CTRL5 bit[3:2]:01 */
#define PWR_VDDD_OUTPUT_1V2 ((uint32_t)(PWR_CTRL5_STPMRSEL_0 \
                                      | PWR_CTRL5_STPMRSEL_1)) /* 0.2v PWR_CTRL5 bit[3:2]:11 */

/** PWR SLEEP mode entry definition **/
#define PWR_SLEEPENTRY_WFI ((uint8_t)0x01) /* enter SLEEP mode with WFI instruction */
#define PWR_SLEEPENTRY_WFE ((uint8_t)0x02) /* enter SLEEP mode with WFE instruction */	 

/** PWR STOP mode entry definition **/
#define PWR_STOPENTRY_WFI  ((uint8_t)0x01) /* enter STOP mode with WFI instruction */
#define PWR_STOPENTRY_WFE  ((uint8_t)0x02) /* enter STOP mode with WFE instruction */

/** PWR PD mode entry definition **/
#define PWR_PDENTRY_WFI    ((uint8_t)0x01) /* enter PD mode with WFI instruction */
#define PWR_PDENTRY_WFE    ((uint8_t)0x02) /* enter PD mode with WFE instruction */

/** PWR DBG_CTRL definition **/
#define PWR_DBG_SLEEP (DBG_CTRL_SLEEP)
#define PWR_DBG_STOP  (DBG_CTRL_STOP)
#define PWR_DBG_PD    (DBG_CTRL_PD)
#define PWR_DBG_IWDG  (DBG_CTRL_IWDGSTP)
#define PWR_DBG_WWDG  (DBG_CTRL_WWDGSTP)
#define PWR_DBG_TIM1  (DBG_CTRL_TIM1STP)
#define PWR_DBG_TIM3  (DBG_CTRL_TIM3STP)
#define PWR_DBG_CAN   (DBG_CTRL_CANSTP)
#define PWR_DBG_I2C1  (DBG_CTRL_I2C1TIMOUT)
#define PWR_DBG_I2C2  (DBG_CTRL_I2C2TIMOUT)
#define PWR_DBG_TIM6  (DBG_CTRL_TIM6STP)
#define PWR_DBG_TIM5  (DBG_CTRL_TIM5STP)
#define PWR_DBG_TIM4  (DBG_CTRL_TIM4STP)
#define PWR_DBG_TIM2  (DBG_CTRL_TIM2STP)

/** PWR registers write protection keys definition **/
#define PWR_CTRL2_KEYS      ((uint32_t)0xA5000000U)
#define PWR_CTRL2_KEYS_MASK (~PWR_CTRL2_LVRKEY)
#define PWR_CTRL4_KEYS      ((uint32_t)0x01753603U)

/** PWR bit shift number definition **/
#define PWR_BIT_SHIFT_2  ((uint32_t)REG_BIT2_OFFSET)
#define PWR_BIT_SHIFT_11 ((uint32_t)REG_BIT11_OFFSET)

/*** PWR Macro Definition End ***/

/*** PWR Driving Functions Declaration ***/
void PWR_DeInit(void);
void PWR_PvdEnable(FunctionalState Cmd);
void PWR_PVDIntEnable(FunctionalState Cmd);
void PWR_PVDFilterWidthSet(uint8_t filter_value);
void PWR_PVDFilterEnable(FunctionalState Cmd);
void PWR_PVDLevelConfig(uint32_t level);
void PWR_LVREnable(FunctionalState Cmd);
void PWR_LVRResetEnable(FunctionalState Cmd);
void PWR_LVRFilterWidthSet(uint8_t filter_value);
void PWR_LVRFilterEnable(FunctionalState Cmd);
void PWR_LVRLevelConfig(uint32_t level);
void PWR_NRSTFilterWidthSet(uint16_t filter_value);
void PWR_NRSTFilterEnable(FunctionalState Cmd);
void PWR_WakeUpPinEnable(WAKEUP_PINX pin, FunctionalState Cmd);
void PWR_WakeUpPinPolarity(WAKEUP_PIN_POL polarity);
void PWR_EnterSLEEPMode(PWR_SLEEPONEXIT_STATUS status, uint8_t enter_mode);
void PWR_EnterSTOPMode(uint8_t enter_mode);
void PWR_EnterPDMode(uint8_t enter_mode);
void PWR_PDRTriggerLevelConfig(uint32_t level);
void PWR_VDDDOutputConfig(uint32_t voltage_output);
void PWR_CTRL2WriteProtectionEnable(void);
void PWR_CTRL4WriteProtectionEnable(void);
FlagStatus PWR_GetFlagStatus(uint32_t flag);
void PWR_ClearFlag(uint32_t flag);
void DBG_ConfigPeriph(uint32_t DBG_Periph, FunctionalState Cmd);
void PWR_EnableIWDGReset(FunctionalState Cmd);
void PWR_EnableFlashDeepStandby(FunctionalState Cmd);
void PWR_EnableFlashFastWakeup(FunctionalState Cmd);
#ifdef __cplusplus
}
#endif

#endif /* __N32A052_PWR_H__ */

