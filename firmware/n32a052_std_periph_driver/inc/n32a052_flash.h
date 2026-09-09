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
*\*\file n32a052_flash.h
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/
#ifndef __N32A052_FLASH_H
#define __N32A052_FLASH_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "n32a052.h" 

/** FLASH Status **/
typedef enum
{ 
    FLASH_BUSY = 1,
    FLASH_ERR_PG,
    FLASH_ERR_WRP,
    FLASH_EOP,
    FLASH_ERR_RDP2,
    FLASH_ERR_ADD,
    FLASH_TIMEOUT
}FLASH_STS;

/** Flash Access Control Register bits **/
#define FLASH_PRFTBS_MSK                  ((uint32_t)FLASH_AC_PRFTBFSTS)
/** Prefetch_Buffer_Enable_Disable **/
#define FLASH_PrefetchBuf_EN              ((uint32_t)FLASH_AC_PRFTBFEN)            /* FLASH Prefetch Buffer Enable */
#define FLASH_PrefetchBuf_DIS             ((uint32_t)0x00000000)                   /* FLASH Prefetch Buffer Disable */
#define FLASH_PrefetchBuf_MSK             (~((uint32_t)FLASH_AC_PRFTBFEN))         /* FLASH Prefetch Buffer Disable */

/** Flash_Latency **/
#define FLASH_LATENCY_0     ((uint32_t)FLASH_AC_LATENCY_0) /* FLASH Zero Latency cycle */
#define FLASH_LATENCY_1     ((uint32_t)FLASH_AC_LATENCY_1) /* FLASH One Latency cycle */
#define FLASH_LATENCY_2     ((uint32_t)FLASH_AC_LATENCY_2) /* FLASH Two Latency cycle */
#define FLASH_LATENCY_MASK  ((uint32_t)FLASH_AC_LATENCY)

/** FLASH Keys **/
#define FLASH_KEY1   ((uint32_t)0x45670123U)
#define FLASH_KEY2   ((uint32_t)0xCDEF89ABU)

/** Flash Control Register bits **/
#define CTRL_Set_PG             ((uint32_t)FLASH_CTRL_PG)
#define CTRL_Reset_PG           (~((uint32_t)FLASH_CTRL_PG))
#define CTRL_Set_PER            ((uint32_t)FLASH_CTRL_PER)
#define CTRL_Reset_PER          (~((uint32_t)FLASH_CTRL_PER))
#define CTRL_Set_MER            ((uint32_t)FLASH_CTRL_MER)
#define CTRL_Reset_MER          (~((uint32_t)FLASH_CTRL_MER))
#define CTRL_Set_OPTPG          ((uint32_t)FLASH_CTRL_OPTPG)
#define CTRL_Reset_OPTPG        (~((uint32_t)FLASH_CTRL_OPTPG))
#define CTRL_Set_OPTER          ((uint32_t)FLASH_CTRL_OPTER)
#define CTRL_Reset_OPTER        (~((uint32_t)FLASH_CTRL_OPTER))
#define CTRL_Set_START          ((uint32_t)FLASH_CTRL_START)
#define CTRL_Set_LOCK           ((uint32_t)FLASH_CTRL_LOCK)
#define FLASH_CTRL_SET_OPTWE    ((uint32_t)FLASH_CTRL_OPTWE)

/** Option byte **/
#define L1_RDP_Key              ((uint32_t)0xFFFF00A5U)  
#define FLASH_L2_RDP_KEY        ((uint32_t)0xFFFF33CCU)
#define FLASH_OB_DATA0_MASK     (FLASH_OB_DATA0)
#define FLASH_OB_DATA1_MASK     (FLASH_OB_DATA1)
#define FLASH_OB_BOOTSEL_MASK   (FLASH_OB_BOOT_SEL)

/** FLASH Mask **/
#define FLASH_RDPRTL1_MSK           ((uint32_t)FLASH_OB_RDPRT1)
#define FLASH_RDPRTL2_MSK           ((uint32_t)FLASH_OB_RDPRT2)
#define FLASH_OB_USER_MSK           ((uint32_t)FLASH_OB_USER)

/** Option_Bytes_BOOTSEL **/
#define BOOT_UartPIN_PA9PA10            ((uint32_t)0x00000003U) /* BOOT uart pins are PA9 and PA10 */
#define BOOT_UartPIN_PB10PB11           ((uint32_t)0x00000000U) /* BOOT uart pins are PB10 and PB11 */
#define BOOT_UartPIN_PD10PD11           ((uint32_t)0x00000001U) /* BOOT uart pins are PD10 and PD11 */
#define BOOT_UartPIN_PA2PA3             ((uint32_t)0x00000002U) /* BOOT uart pins are PA2 and PA3 */

/** Option_Bytes_RDPx **/
#define FLASH_OB_RDP1_ENABLE            ((uint8_t)0x00U) /* Enable RDP1 */
#define FLASH_OB_RDP1_DISABLE           ((uint8_t)0xA5U) /* DISABLE RDP1 */

#define FLASH_OB_RDP2_ENABLE            ((uint8_t)0xCCU) /* Enable RDP2 */
#define FLASH_OB_RDP2_DISABLE           ((uint8_t)0x00U) /* Disable RDP2 */

/** Option_Bytes_IWatchdog **/
#define FLASH_OB_IWDG_SOFTWARE          ((uint32_t)0x0001U) /* Software IWDG selected */
#define FLASH_OB_IWDG_HARDWARE          ((uint32_t)0x0000U) /* Hardware IWDG selected */

/** Option_Bytes_nRST_STOP **/
#define FLASH_OB_STOP_NORST             ((uint32_t)0x0002U) /* No reset generated when entering in STOP */
#define FLASH_OB_STOP_RST               ((uint32_t)0x0000U) /* Reset generated when entering in STOP */

/** Option_Bytes_nRST_PD **/
#define FLASH_OB_PD_NORST               ((uint32_t)0x0004U) /* No reset generated when entering in PD */
#define FLASH_OB_PD_RST                 ((uint32_t)0x0000U) /* Reset generated when entering in PD */

#define FLASH_OB_NBOOT0_SET             ((uint32_t)0x0008U) /* Set nBOOT0 */
#define FLASH_OB_NBOOT0_CLR             ((uint32_t)0x0000U) /* Clear nBOOT0 */

#define FLASH_OB_NBOOT1_SET             ((uint32_t)0x0010U) /* Set nBOOT1 */
#define FLASH_OB_NBOOT1_CLR             ((uint32_t)0x0000U) /* Clear nBOOT1 */

#define FLASH_OB_NSWBOOT0_SET           ((uint32_t)0x0020U) /* Set nSWBOOT0 */
#define FLASH_OB_NSWBOOT0_CLR           ((uint32_t)0x0000U) /* Clear nSWBOOT0 */

#define FLASH_OB_BOOT0_CFG_HIGH         ((uint32_t)0x0040U) /* Boot0 high active */
#define FLASH_OB_BOOT0_CFG_LOW          ((uint32_t)0x0000U) /* Boot0 low active */

/** Option_Bytes_USER_LVREN **/
#define FLASH_OB_USER_LVR_ENABLE        ((uint32_t)0x0000U) /* LVR enable */
#define FLASH_OB_USER_LVR_DISABLE       ((uint32_t)0x0010U) /* LVR disable */

/** Option_Bytes_USER_LVRRST **/
#define FLASH_OB_USER_LVRRST_ENABLE     ((uint32_t)0x0000U) /* LVR reset enable */
#define FLASH_OB_USER_LVRRST_DISABLE    ((uint32_t)0x0020U) /* LVR reset disable */

/** Option_Bytes_USER_LVRFIL **/
#define FLASH_OB_USER_LVRFIL_ENABLE     ((uint32_t)0x0000U) /* LVR filter enable */
#define FLASH_OB_USER_LVRFIL_DISABLE    ((uint32_t)0x0040U) /* LVR filter disable */

/** Option Bytes MASK **/
#define FLASH_OB_MASK                   ((uint32_t)0xFFFFFFFFU)

/** FLASH USER Mask **/
#define FLASH_USER_LVRCNT_MSK           ((uint32_t)FLASH_USER_LVRCNT)
#define FLASH_USER_LVRLS_MSK            ((uint32_t)FLASH_USER_LVRLS)
#define FLASH_USER_POR_DELAY_MSK        ((uint32_t)FLASH_USER_POR_DELAY)
#define FLASH_USER_START_ADD_MSK        ((uint32_t)FLASH_START_ADD_MASK)


#define FLASH_USER_RPD_OFFSET           (REG_BIT16_OFFSET)

#define FLASH_DATA0_DATA1_OFFSET        (REG_BIT16_OFFSET)
#define FLASH_USER2_USER3_OFFSET        (REG_BIT16_OFFSET)
#define FLASH_OB_DATA0_OFFSET           (REG_BIT10_OFFSET)
#define FLASH_OB_DATA1_OFFSET           (REG_BIT18_OFFSET)
#define FLASH_OB_BOOTSEL_OFFSET         (REG_BIT26_OFFSET)


/** Delay definition **/
#define EraseTimeout   ((uint32_t)0x000B0000U)
#define ProgramTimeout ((uint32_t)0x00002000U)	 

#define FLASH_WORD_LENGTH   ((uint32_t)0x00000007U)


/**  FLASH_Interrupts **/
#define FLASH_INT_ECC      ((uint32_t)FLASH_CTRL_ECERRITE) /* End of FLASH Operation Interrupt source */
#define FLASH_INT_ERR      ((uint32_t)FLASH_CTRL_ERRITE) /* PGERR WRPERR ERROR error interrupt source */
#define FLASH_INT_EOP      ((uint32_t)FLASH_CTRL_EOPITE) /* End of FLASH Operation Interrupt source */

/** FLASH_Flags **/
#define FLASH_FLAG_BUSY     ((uint32_t)FLASH_STS_BUSY) /* FLASH Busy flag */
#define FLASH_FLAG_ECC      ((uint32_t)FLASH_STS_ECCERR) /* FLASH ECC error flag */
#define FLASH_FLAG_PGERR    ((uint32_t)FLASH_STS_PGERR) /* FLASH Program error flag */
#define FLASH_FLAG_WRPERR   ((uint32_t)FLASH_STS_WRPERR) /* FLASH Write protected error flag */
#define FLASH_FLAG_EOP      ((uint32_t)FLASH_STS_EOP) /* FLASH End of Operation flag */
#define FLASH_FLAG_OBERR    ((uint32_t)FLASH_OB_OBERR) /* Option Byte Error flag */

/** FLASH_STS_CLRFLAG **/
#define FLASH_STS_CLRFLAG   (FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR | FLASH_FLAG_EOP | FLASH_FLAG_ECC)


/** FLASH_VTOR_CLRFLAG **/
#define FLASH_VTOR_ENABLE   ((uint32_t)FLASH_VTOR_EN) /* FLASH Vtor enable */
#define FLASH_VTOR_DISABLE  ((uint32_t)0x00000000U) /* FLASH Vtor disable */

/** Option byte offset **/
#define FLASH_OB_TO_USER_OFFSET     (REG_BIT2_OFFSET)
#define FLASH_USER3_OFFSET          (REG_BIT8_OFFSET)
#define FLASH_USER4_OFFSET              (REG_BIT16_OFFSET)

/** FLASH Mask **/
#define FLASH_WRP_WRP1_OFFSET       (REG_BIT8_OFFSET)
#define FLASH_WRP_WRP2_OFFSET       (REG_BIT16_OFFSET)
#define FLASH_WRP_WRP3_OFFSET       (REG_BIT24_OFFSET)         
#define FLASH_WRP0_MSK              (FLASH_WRP0_WRP0)
#define FLASH_WRP1_MSK              (FLASH_WRP1_WRP1 << FLASH_WRP_WRP1_OFFSET)
#define FLASH_WRP2_MSK              (FLASH_WRP2_WRP2 << FLASH_WRP_WRP2_OFFSET)
#define FLASH_WRP3_MSK              (FLASH_WRP3_WRP3 << FLASH_WRP_WRP3_OFFSET)



#define FLASH_WRP_Pages0to7      ((uint32_t)FLASH_WRP_WRPT_0) /* N32A052 devices: Write protection of page 0 to 7 */
#define FLASH_WRP_Pages8to15     ((uint32_t)FLASH_WRP_WRPT_1) /* N32A052 devices: Write protection of page 8 to 15 */
#define FLASH_WRP_Pages16to23    ((uint32_t)FLASH_WRP_WRPT_2) /* N32A052 devices: Write protection of page 16 to 23 */
#define FLASH_WRP_Pages24to31    ((uint32_t)FLASH_WRP_WRPT_3) /* N32A052 devices: Write protection of page 24 to 31 */
#define FLASH_WRP_Pages32to39    ((uint32_t)FLASH_WRP_WRPT_4) /* N32A052 devices: Write protection of page 32 to 39 */
#define FLASH_WRP_Pages40to47    ((uint32_t)FLASH_WRP_WRPT_5) /* N32A052 devices: Write protection of page 40 to 47 */
#define FLASH_WRP_Pages48to55    ((uint32_t)FLASH_WRP_WRPT_6) /* N32A052 devices: Write protection of page 48 to 55 */
#define FLASH_WRP_Pages56to63    ((uint32_t)FLASH_WRP_WRPT_7) /* N32A052 devices: Write protection of page 56 to 63 */
#define FLASH_WRP_Pages64to71    ((uint32_t)FLASH_WRP_WRPT_8) /* N32A052 devices: Write protection of page 64 to 71 */
#define FLASH_WRP_Pages72to79    ((uint32_t)FLASH_WRP_WRPT_9) /* N32A052 devices: Write protection of page 72 to 79 */
#define FLASH_WRP_Pages80to87    ((uint32_t)FLASH_WRP_WRPT_10) /* N32A052 devices: Write protection of page 80 to 87 */
#define FLASH_WRP_Pages88to95    ((uint32_t)FLASH_WRP_WRPT_11) /* N32A052 devices: Write protection of page 88 to 95 */
#define FLASH_WRP_Pages96to103   ((uint32_t)FLASH_WRP_WRPT_12) /* N32A052 devices: Write protection of page 96 to 103 */
#define FLASH_WRP_Pages104to111  ((uint32_t)FLASH_WRP_WRPT_13) /* N32A052 devices: Write protection of page 104 to 111 */
#define FLASH_WRP_Pages112to119  ((uint32_t)FLASH_WRP_WRPT_14) /* N32A052 devices: Write protection of page 112 to 119 */
#define FLASH_WRP_Pages120to127  ((uint32_t)FLASH_WRP_WRPT_15) /* N32A052 devices: Write protection of page 120 to 127 */
#define FLASH_WRP_Pages128to135  ((uint32_t)FLASH_WRP_WRPT_16) /* N32A052 devices: Write protection of page 128 to 135 */
#define FLASH_WRP_Pages136to143  ((uint32_t)FLASH_WRP_WRPT_17) /* N32A052 devices: Write protection of page 136 to 143 */
#define FLASH_WRP_Pages144to151  ((uint32_t)FLASH_WRP_WRPT_18) /* N32A052 devices: Write protection of page 144 to 151 */
#define FLASH_WRP_Pages152to159  ((uint32_t)FLASH_WRP_WRPT_19) /* N32A052 devices: Write protection of page 152 to 159 */
#define FLASH_WRP_Pages160to167  ((uint32_t)FLASH_WRP_WRPT_20) /* N32A052 devices: Write protection of page 160 to 167 */
#define FLASH_WRP_Pages168to175  ((uint32_t)FLASH_WRP_WRPT_21) /* N32A052 devices: Write protection of page 168 to 175 */
#define FLASH_WRP_Pages176to183  ((uint32_t)FLASH_WRP_WRPT_22) /* N32A052 devices: Write protection of page 176 to 183 */
#define FLASH_WRP_Pages184to191  ((uint32_t)FLASH_WRP_WRPT_23) /* N32A052 devices: Write protection of page 184 to 191 */
#define FLASH_WRP_Pages192to199  ((uint32_t)FLASH_WRP_WRPT_24) /* N32A052 devices: Write protection of page 192 to 199 */
#define FLASH_WRP_Pages200to207  ((uint32_t)FLASH_WRP_WRPT_25) /* N32A052 devices: Write protection of page 200 to 207 */
#define FLASH_WRP_Pages208to215  ((uint32_t)FLASH_WRP_WRPT_26) /* N32A052 devices: Write protection of page 208 to 215 */
#define FLASH_WRP_Pages216to223  ((uint32_t)FLASH_WRP_WRPT_27) /* N32A052 devices: Write protection of page 216 to 223 */
#define FLASH_WRP_Pages224to231  ((uint32_t)FLASH_WRP_WRPT_28) /* N32A052 devices: Write protection of page 224 to 231 */
#define FLASH_WRP_Pages232to239  ((uint32_t)FLASH_WRP_WRPT_29) /* N32A052 devices: Write protection of page 232 to 239 */
#define FLASH_WRP_Pages240to247  ((uint32_t)FLASH_WRP_WRPT_30) /* N32A052 devices: Write protection of page 240 to 247 */
#define FLASH_WRP_Pages248to255  ((uint32_t)FLASH_WRP_WRPT_31) /* N32A052 devices: Write protection of page 248 to 255 */
#define FLASH_WRP_AllPages       ((uint32_t)0xFFFFFFFF)        /* Write protection of all Pages */


/* Functions used for N32A052 devices */
void FLASH_SetLatency(uint32_t FLASH_Latency);
uint8_t FLASH_GetLatency(void);
void FLASH_PrefetchBufSet(uint32_t FLASH_PrefetchBuf);
void FLASH_Unlock(void);
void FLASH_Lock(void);
FlagStatus Flash_GetLockStatus(void);
void Option_Bytes_Unlock(void);
void Option_Bytes_Lock(void);
FlagStatus OB_GetLockStatus(void);
FLASH_STS FLASH_EraseOnePage(uint32_t Page_Address);
FLASH_STS FLASH_MassErase(void);
FLASH_STS FLASH_ProgramdoubleWord(uint32_t address, uint32_t data0,uint32_t data1);
FLASH_STS FLASH_EraseOB(void);
FLASH_STS FLASH_ProgramOptionBytes_RDP1(uint8_t option_byte_rpd1);
FLASH_STS FLASH_ProgramOptionBytes_USER1(uint32_t option_byte_iwdg, uint32_t option_byte_stop, uint32_t option_byte_PD, \
                                           uint32_t option_byte_nBOOT0, uint32_t option_byte_nBOOT1, uint32_t option_byte_nSWBOOT0,\
                                           uint32_t option_byte_BOOT0_CFG);
FLASH_STS FLASH_ProgramOptionBytes_USER2(uint32_t option_byte_LVR_cnt, uint32_t option_byte_LVR, uint32_t option_byte_LVR_reset, \
                                         uint32_t option_byte_LVR_filter);
FLASH_STS FLASH_ProgramOptionBytes_USER3(uint32_t option_byte_user3);
FLASH_STS FLASH_ProgramOptionBytes_USER4(uint32_t option_byte_user4);
FLASH_STS FLASH_ProgramOptionBytes_USER5(uint32_t option_byte_user5);
FLASH_STS FLASH_ProgramOptionBytes_USER6(uint32_t option_byte_user6);
FLASH_STS FLASH_ProgramOptionBytes_DATA0(uint32_t option_byte_data0);
FLASH_STS FLASH_ProgramOptionBytes_DATA1(uint32_t option_byte_data1);
FLASH_STS FLASH_EnWriteProtection(uint32_t FLASH_Pages);
FLASH_STS FLASH_ProgramOptionBytes_RDP2(uint8_t option_byte_rpd2);
FLASH_STS FLASH_ReadOutProtectionL1(FunctionalState Cmd);
FLASH_STS FLASH_ReadOutProtectionL2_ENABLE(void);
FlagStatus FLASH_GetOptionBytes_User1(uint32_t option_byte_bit);
uint32_t FLASH_GetOptionBytes_User2_LVRLS(void);
FlagStatus FLASH_GetOptionBytes_User2_LVR(uint32_t option_byte_bit);
uint32_t FLASH_GetOptionBytes_User3(void);
uint32_t FLASH_GetOptionBytes_User4(void);
uint32_t FLASH_GetStartAddress(void);
uint32_t FLASH_GetBOOTUartPIN(void);
uint32_t FLASH_GetOptionBytes_Data0(void);
uint32_t FLASH_GetOptionBytes_Data1(void);
FlagStatus FLASH_GetReadOutProtectionSTS(void);
FlagStatus FLASH_GetReadOutProtectionL2STS(void);
uint32_t FLASH_GetWriteProtectionSTS(void);
FlagStatus FLASH_GetPrefetchBufSTS(void);
void FLASH_INTConfig(uint32_t FLASH_INT, FunctionalState Cmd);
FlagStatus FLASH_GetFlagSTS(uint32_t FLASH_FLAG);
FlagStatus FLASH_GetOBFlagSTS(uint32_t FLASH_FLAG);
void FLASH_ClearFlag(uint32_t FLASH_FLAG);
FLASH_STS FLASH_GetSTS(void);
FLASH_STS FLASH_WaitForLastOpt(uint32_t Timeout);
void FLASH_SetVTORAddress(uint32_t VTOR_address,uint32_t VTOR_cmd);


#ifdef __cplusplus
}
#endif

#endif /* __N32A052_FLASH_H */

