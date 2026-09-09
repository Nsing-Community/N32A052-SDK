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
*\*\file n32a052_lcd.h
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
***/

#ifndef __N32A052_LCD_H__
#define __N32A052_LCD_H__
 
#ifdef __cplusplus
 extern "C" {
#endif
 
#include "n32a052.h"

/*** EXTI Structure Definition Start ***/


typedef enum {
    LCD_ERROR_OK        = 0x00U,     /* No error */
    LCD_ERROR_FCRSF     = 0x01U,     /* Synchro flag error */
    LCD_ERROR_UDR       = 0x02U,     /* Update display request flag error */
    LCD_ERROR_UDD       = 0x03U,     /* Update display done flag error */
    LCD_ERROR_ENSTS     = 0x04U,     /* LCD enabled status flag error */
    LCD_ERROR_RDY       = 0x05U,     /* LCD VLCD ready flag error */
    LCD_ERROR_PARAM     = 0x06U,     /* LCD function parameter error */
    LCD_ERROR_CLK       = 0x07U,     /* LCD clock source fail error */
}LCD_ErrorTypeDef;

/** LCD normal timeout **/
#define LCD_TIME_OUT    (0x01000000)

/** LCD_Clock_Source **/
#define LCD_CLK_SRC_HSI_DIV8            (RCC_CTRL_HSIEN)   /* HSI */
#define LCD_CLK_SRC_HSE_DIV16           (RCC_CTRL_HSEEN)   /* HSE */
#define LCD_CLK_SRC_HSE_BYPASS_DIV16    (RCC_CTRL_HSEBP)   /* HSE bypass */

/** LCD_RAMRegister **/
#define LCD_RAM1_COM0   (0x00000000U)
#define LCD_RAM2_COM0   (0x00000001U)
#define LCD_RAM1_COM1   (0x00000002U)
#define LCD_RAM2_COM1   (0x00000003U)
#define LCD_RAM1_COM2   (0x00000004U)
#define LCD_RAM2_COM2   (0x00000005U)
#define LCD_RAM1_COM3   (0x00000006U)
#define LCD_RAM2_COM3   (0x00000007U)
#define LCD_RAM1_COM4   (0x00000008U)
#define LCD_RAM2_COM4   (0x00000009U)
#define LCD_RAM1_COM5   (0x0000000AU)
#define LCD_RAM2_COM5   (0x0000000BU)
#define LCD_RAM1_COM6   (0x0000000CU)
#define LCD_RAM2_COM6   (0x0000000DU)
#define LCD_RAM1_COM7   (0x0000000EU)
#define LCD_RAM2_COM7   (0x0000000FU)
#define LCD_RAM_SEG_DATA_RAM1   (0xFFFFFFFFU)
#define LCD_RAM_SEG_DATA_RAM2   (0x0000001FU)

/** LCD driving strength control define **/
#define LCD_DRIVESTRENGTH_MASK          ((uint32_t)(~LCD_CTRL_DSC))

/** LCD highDrive buffer define **/
#define LCD_HIGHDRIVEBUFFER_DISABLE     ((uint32_t)0x00000000U)         /* High drive buffer disabled */
#define LCD_HIGHDRIVEBUFFER_ENABLE      ((uint32_t)LCD_CTRL_BUFEN)     /* High drive buffer enabled  */

/** LCD duty mode define **/
#define LCD_DUTY_MASK                   ((uint32_t)(~LCD_CTRL_DUTY))
#define LCD_DUTY_STATIC                 ((uint32_t)0x00000000U)          /* 0x00000000U  Static duty */
#define LCD_DUTY_1_2                    ((uint32_t)0x00000004U)          /* 0x00000004U  1/2 duty    */
#define LCD_DUTY_1_3                    ((uint32_t)0x00000008U)          /* 0x00000008U  1/3 duty    */
#define LCD_DUTY_1_4                    ((uint32_t)0x0000000CU)          /* 0x0000000CU  1/4 duty    */
#define LCD_DUTY_1_8                    ((uint32_t)0x00000010U)          /* 0x00000010U  1/8 duty    */

/** LCD bias define **/
#define LCD_BIAS_MASK                   ((uint32_t)(~LCD_CTRL_BIAS))
#define LCD_BIAS_1_2                    ((uint32_t)0x00000000U)          /* 0x00000000U   1/2 bias   */
#define LCD_BIAS_1_3                    ((uint32_t)0x00000020U)          /* 0x00000020U   1/3 bias   */
#define LCD_BIAS_1_4                    ((uint32_t)0x00000040U)          /* 0x00000040U   1/4 bias   */

/** LCD voltage_source  **/
#define LCD_VOLTAGESOURCE_DISABLE      ((uint32_t)0x00000000U)         /* LCD driver contrast control disable  */      
#define LCD_VOLTAGESOURCE_ENABLE      ((uint32_t)LCD_CTRL_VSEL)       /* LCD driver contrast control enable  */

/** LCD enable  **/
#define LCD_OFF                         ((uint32_t)(~LCD_CTRL_EN))     /* LCD controler disable  */
#define LCD_ON                          ((uint32_t)LCD_CTRL_EN)        /* LCD controler enable  */

/** LCD 16-bit prescaler define **/
#define LCD_PRESCALER_MASK              ((uint32_t)(~LCD_FCTRL_PRES))  /* LCD_FCTRL PRES[3:0] bit Mask */
#define LCD_PRESCALER_1                 ((uint32_t)0x00000000U)        /* 0x00000000U  CLKPS = LCDCLK        */
#define LCD_PRESCALER_2                 ((uint32_t)0x00800000U)        /* 0x00800000U  CLKPS = LCDCLK/2      */
#define LCD_PRESCALER_4                 ((uint32_t)0x01000000U)        /* 0x01000000U  CLKPS = LCDCLK/4      */
#define LCD_PRESCALER_8                 ((uint32_t)0x01800000U)        /* 0x01800000U  CLKPS = LCDCLK/8      */
#define LCD_PRESCALER_16                ((uint32_t)0x02000000U)        /* 0x02000000U  CLKPS = LCDCLK/16     */
#define LCD_PRESCALER_32                ((uint32_t)0x02800000U)        /* 0x02800000U  CLKPS = LCDCLK/32     */
#define LCD_PRESCALER_64                ((uint32_t)0x03000000U)        /* 0x03000000U  CLKPS = LCDCLK/64     */
#define LCD_PRESCALER_128               ((uint32_t)0x03800000U)        /* 0x03800000U  CLKPS = LCDCLK/128    */
#define LCD_PRESCALER_256               ((uint32_t)0x04000000U)        /* 0x04000000U  CLKPS = LCDCLK/256    */
#define LCD_PRESCALER_512               ((uint32_t)0x04800000U)        /* 0x04800000U  CLKPS = LCDCLK/512    */
#define LCD_PRESCALER_1024              ((uint32_t)0x05000000U)        /* 0x05000000U  CLKPS = LCDCLK/1024   */
#define LCD_PRESCALER_2048              ((uint32_t)0x05800000U)        /* 0x05800000U  CLKPS = LCDCLK/2048   */
#define LCD_PRESCALER_4096              ((uint32_t)0x06000000U)        /* 0x06000000U  CLKPS = LCDCLK/4096   */
#define LCD_PRESCALER_8192              ((uint32_t)0x06800000U)        /* 0x06800000U  CLKPS = LCDCLK/8192   */
#define LCD_PRESCALER_16384             ((uint32_t)0x07000000U)        /* 0x07000000U  CLKPS = LCDCLK/16384  */
#define LCD_PRESCALER_32768             ((uint32_t)0x07800000U)        /* 0x07800000U  CLKPS = LCDCLK/32768  */

/** LCD clock divider define **/
#define LCD_DIV_MASK                    ((uint32_t)(~LCD_FCTRL_DIV))   /* LCD_FCTRL DIV[3:0] bit Mask */
#define LCD_DIV_16                      ((uint32_t)0x00000000U)        /* 0x00000000U  CLKDIV = CLKPS/(16) */
#define LCD_DIV_17                      ((uint32_t)0x00080000U)        /* 0x00080000U  CLKDIV = CLKPS/(17) */
#define LCD_DIV_18                      ((uint32_t)0x00100000U)        /* 0x00100000U  CLKDIV = CLKPS/(18) */
#define LCD_DIV_19                      ((uint32_t)0x00180000U)        /* 0x00180000U  CLKDIV = CLKPS/(19) */
#define LCD_DIV_20                      ((uint32_t)0x00200000U)        /* 0x00200000U  CLKDIV = CLKPS/(20) */
#define LCD_DIV_21                      ((uint32_t)0x00280000U)        /* 0x00280000U  CLKDIV = CLKPS/(21) */
#define LCD_DIV_22                      ((uint32_t)0x00300000U)        /* 0x00300000U  CLKDIV = CLKPS/(22) */
#define LCD_DIV_23                      ((uint32_t)0x00380000U)        /* 0x00380000U  CLKDIV = CLKPS/(23) */
#define LCD_DIV_24                      ((uint32_t)0x00400000U)        /* 0x00400000U  CLKDIV = CLKPS/(24) */
#define LCD_DIV_25                      ((uint32_t)0x00480000U)        /* 0x00480000U  CLKDIV = CLKPS/(25) */
#define LCD_DIV_26                      ((uint32_t)0x00500000U)        /* 0x00500000U  CLKDIV = CLKPS/(26) */
#define LCD_DIV_27                      ((uint32_t)0x00580000U)        /* 0x00580000U  CLKDIV = CLKPS/(27) */
#define LCD_DIV_28                      ((uint32_t)0x00600000U)        /* 0x00600000U  CLKDIV = CLKPS/(28) */
#define LCD_DIV_29                      ((uint32_t)0x00680000U)        /* 0x00680000U  CLKDIV = CLKPS/(29) */
#define LCD_DIV_30                      ((uint32_t)0x00700000U)        /* 0x00700000U  CLKDIV = CLKPS/(30) */
#define LCD_DIV_31                      ((uint32_t)0x00780000U)        /* 0x00780000U  CLKDIV = CLKPS/(31) */

/** LCD_Blink_Mode define **/
#define LCD_BLINKMODE_MASK              ((uint32_t)(~LCD_FCTRL_BLINK))  /* LCD_FCTRL BLINK[1:0] bit Mask */
#define LCD_BLINKMODE_OFF               ((uint32_t)0x00000000U)         /* Blink disable  */
#define LCD_BLINKMODE_SEG0_COM0         ((uint32_t)0x00020000U)         /* 0x00020000U Blink enabled on SEG[0], COM[0] (1 pixel)          */
#define LCD_BLINKMODE_SEG0_ALLCOM       ((uint32_t)0x00040000U)         /* 0x00040000U Blink enabled on SEG[0], all COM (up to 8 pixels according to the programmed duty)          */
#define LCD_BLINKMODE_ALLSEG_ALLCOM     ((uint32_t)0x00060000U)         /* 0x00060000U Blink enabled on all SEG and all COM (all pixels)  */

/** LCD_Blink_Frequency define **/
#define LCD_BLINKFREQ_MASK              ((uint32_t)(~LCD_FCTRL_BLINKF)) /* LCD_FCTRL BLINKF[2:0] bit Mask */
#define LCD_BLINKFREQ_DIV_8             ((uint32_t)0x00000000U)         /* 0x00000000U The Blink frequency = fck_div/8    */
#define LCD_BLINKFREQ_DIV_16            ((uint32_t)0x00004000U)         /* 0x00004000U The Blink frequency = fck_div/16   */
#define LCD_BLINKFREQ_DIV_32            ((uint32_t)0x00008000U)         /* 0x00008000U The Blink frequency = fck_div/32   */
#define LCD_BLINKFREQ_DIV_64            ((uint32_t)0x0000C000U)         /* 0x0000C000U The Blink frequency = fck_div/64   */
#define LCD_BLINKFREQ_DIV_128           ((uint32_t)0x00010000U)         /* 0x00010000U The Blink frequency = fck_div/128  */
#define LCD_BLINKFREQ_DIV_256           ((uint32_t)0x00014000U)         /* 0x00014000U The Blink frequency = fck_div/256  */
#define LCD_BLINKFREQ_DIV_512           ((uint32_t)0x00018000U)         /* 0x00018000U The Blink frequency = fck_div/512  */
#define LCD_BLINKFREQ_DIV_1024          ((uint32_t)0x0001C000U)         /* 0x0001C000U The Blink frequency = fck_div/1024 */

/** LCD Contrast control define **/
#define LCD_CONTRASTLEVEL_MASK          ((uint32_t)(~LCD_FCTRL_CONTRAST))  /* LCD_FCTRL DEAD[2:0] bit Mask */
#define LCD_CONTRASTLEVEL_0             ((uint32_t)0x00000000U)   /* Maximum Voltage = VDD*1.0    */
#define LCD_CONTRASTLEVEL_1             ((uint32_t)0x00000400U)   /* 0x00000400U  Maximum Voltage = VDD*0.97    */
#define LCD_CONTRASTLEVEL_2             ((uint32_t)0x00000800U)   /* 0x00000800U  Maximum Voltage = VDD*0.94    */
#define LCD_CONTRASTLEVEL_3             ((uint32_t)0x00000C00U)   /* 0x00000C00U  Maximum Voltage = VDD*0.90    */
#define LCD_CONTRASTLEVEL_4             ((uint32_t)0x00001000U)   /* 0x00001000U  Maximum Voltage = VDD*0.87    */
#define LCD_CONTRASTLEVEL_5             ((uint32_t)0x00001400U)   /* 0x00001400U  Maximum Voltage = VDD*0.84    */
#define LCD_CONTRASTLEVEL_6             ((uint32_t)0x00001800U)   /* 0x00001800U  Maximum Voltage = VDD*0.80    */
#define LCD_CONTRASTLEVEL_7             ((uint32_t)0x00001C00U)   /* 0x00001C00U  Maximum Voltage = VDD*0.77    */
#define LCD_CONTRASTLEVEL_8             ((uint32_t)0x00002000U)   /* 0x00002000U  Maximum Voltage = VDD*0.74    */
#define LCD_CONTRASTLEVEL_9             ((uint32_t)0x00002400U)   /* 0x00002400U  Maximum Voltage = VDD*0.70    */
#define LCD_CONTRASTLEVEL_10            ((uint32_t)0x00002800U)   /* 0x00002800U  Maximum Voltage = VDD*0.67    */
#define LCD_CONTRASTLEVEL_11            ((uint32_t)0x00002C00U)   /* 0x00002C00U  Maximum Voltage = VDD*0.64    */
#define LCD_CONTRASTLEVEL_12            ((uint32_t)0x00003000U)   /* 0x00003000U  Maximum Voltage = VDD*0.61    */
#define LCD_CONTRASTLEVEL_13            ((uint32_t)0x00003400U)   /* 0x00002C00U  Maximum Voltage = VDD*0.58    */
#define LCD_CONTRASTLEVEL_14            ((uint32_t)0x00003800U)   /* 0x00002800U  Maximum Voltage = VDD*0.54    */
#define LCD_CONTRASTLEVEL_15            ((uint32_t)0x00003C00U)   /* 0x00003C00U  Maximum Voltage = VDD*0.50    */

/** LCD Dead time duration define **/
#define LCD_DEADTIME_MASK               ((uint32_t)(~LCD_FCTRL_DEAD))  /* LCD_FCTRL DEAD[2:0] bit Mask */
#define LCD_DEADTIME_0                  ((uint32_t)0x00000000U)        /* No dead Time      */
#define LCD_DEADTIME_1                  ((uint32_t)0x00000080U)        /* 0x00000080U 1 Phase between different couple of Frame   */
#define LCD_DEADTIME_2                  ((uint32_t)0x00000100U)        /* 0x00000100U 2 Phase between different couple of Frame   */
#define LCD_DEADTIME_3                  ((uint32_t)0x00000180U)        /* 0x00000180U 3 Phase between different couple of Frame */
#define LCD_DEADTIME_4                  ((uint32_t)0x00000200U)        /* 0x00000200U 4 Phase between different couple of Frame  */
#define LCD_DEADTIME_5                  ((uint32_t)0x00000280U)        /* 0x00000280U 5 Phase between different couple of Frame  */
#define LCD_DEADTIME_6                  ((uint32_t)0x00000300U)        /* 0x00000300U 6 Phase between different couple of Frame   */
#define LCD_DEADTIME_7                  ((uint32_t)0x00000380U)        /* 0x00000380U 7 Phase between different couple of Frame */

/** LCD Pulseon duration define **/
#define LCD_PULSEONDURATION_MASK        ((uint32_t)(~LCD_FCTRL_PULSEON))/* LCD_FCTRL PON[2:0] bit Mask */
#define LCD_PULSEONDURATION_0           ((uint32_t)0x00000000U)         /* 0x00000010U Pulse ON duration = 0 pulse  */
#define LCD_PULSEONDURATION_1           ((uint32_t)0x00000010U)         /* 0x00000010U Pulse ON duration = 1/CK_PS  */
#define LCD_PULSEONDURATION_2           ((uint32_t)0x00000020U)         /* 0x00000020U Pulse ON duration = 2/CK_PS  */
#define LCD_PULSEONDURATION_3           ((uint32_t)0x00000030U)         /* 0x00000030U Pulse ON duration = 3/CK_PS  */
#define LCD_PULSEONDURATION_4           ((uint32_t)0x00000040U)         /* 0x00000040U Pulse ON duration = 4/CK_PS  */
#define LCD_PULSEONDURATION_5           ((uint32_t)0x00000050U)         /* 0x00000050U Pulse ON duration = 5/CK_PS  */
#define LCD_PULSEONDURATION_6           ((uint32_t)0x00000060U)         /* 0x00000060U Pulse ON duration = 6/CK_PS  */
#define LCD_PULSEONDURATION_7           ((uint32_t)0x00000070U)         /* 0x00000070U Pulse ON duration = 7/CK_PS  */

/** Update display done interrupt define **/
#define LCD_IT_UDD                ((uint32_t)LCD_FCTRL_UDDIE)     /* Update display done interrupt enabled  */

/** Start of frame interrupt define **/
#define LCD_IT_SOF                ((uint32_t)LCD_FCTRL_SOFIE)     /* Start of frame interrupt enabled  */

/** High drive define **/
#define LCD_HIGHDRIVE_DISABLE           ((uint32_t)0x00000000U)   /* High drive disabled */
#define LCD_HIGHDRIVE_ENABLE            ((uint32_t)LCD_FCTRL_HDEN)      /* High drive enabled  */


/** LCD flags definition **/
#define LCD_FLAG_FCRSF                  ((uint32_t)LCD_STS_FCRSF)       /* LCD Frame Control Synchronization flag  */
#define LCD_FLAG_RDY                    ((uint32_t)LCD_STS_RDY)         /* Ready flag  */
#define LCD_FLAG_UDD                    ((uint32_t)LCD_STS_UDD)         /* Update display done  */
#define LCD_FLAG_UDR                    ((uint32_t)LCD_STS_UDR)         /* Update display request  */
#define LCD_FLAG_SOF                    ((uint32_t)LCD_STS_SOF)         /* Start of frame status  */
#define LCD_FLAG_ENSTS                  ((uint32_t)LCD_STS_ENSTS)       /* LCD controller status  */

/** LCD flags clear definition **/
#define LCD_FLAG_UDD_CLEAR                  ((uint32_t)LCD_CLR_UDDCLR)      /* Start of frame status  */
#define LCD_FLAG_SOF_CLEAR                  ((uint32_t)LCD_CLR_SOFCLR)      /* LCD controller status  */


/**  LCD_Interrupt definition **/
#define LCD_INT_FLAG_UDD                (LCD_FLAG_UDD)                  /* Update display done interrupt flag*/
#define LCD_INT_FLAG_SOFIE              (LCD_FLAG_ENSOF)                /* Start of frame interrupt flag */



/** LCD Init structure definition **/

typedef struct
{
  uint32_t  Prescaler;          /* Configures the LCD Prescaler. */
  uint32_t  Divider;            /* Configures the LCD Divider. */
  uint32_t  Duty;               /* Configures the LCD Duty. */
  uint32_t  Bias;               /* Configures the LCD Bias. */
  uint32_t  VoltageSource;      /* Selects the LCD Voltage source. */
  uint32_t  Contrast;           /* Configures the LCD Contrast. */
  uint32_t  DeadTime;           /* Configures the LCD Dead Time. */
  uint32_t  PulseOnDuration;    /* Configures the LCD Pulse On Duration. */
  uint32_t  HighDrive;          /* Enable or disable the permanent high driver. */
  uint32_t  HighDriveBuffer;    /* Enable or disable the high driver buffer. */
  uint32_t  BlinkMode;          /* Configures the LCD Blink Mode. */
  uint32_t  BlinkFreq;          /* Configures the LCD Blink frequency. */
}LCD_InitType;


/** EXTI Driving Functions Declaration **/
void LCD_DeInit(void);
void LCD_Enable(void);
void LCD_Disable(void);
void LCD_HIGHDRIVE_BUF_ENABLE(void);
void LCD_HIGHDRIVE_BUF_DISABLE(void);
void LCD_VLCD_SELECT_ENABLE(void);
void LCD_VLCD_SELECT_DISABLE(void);
void LCD_High_Drive_Enable(void);
void LCD_High_Drive_Disable(void);
void LCD_PRESCALER_CONFIG(uint32_t pres);
void LCD_DIVIDER_CONFIG(uint32_t div);
void LCD_BLINK_CONFIG(uint32_t freq);
void LCD_Blink_Mode_Config(uint32_t blink_mode);
void LCD_CONTRAST_CONFIG(uint32_t contrast);
void LCD_DEADTIME_CONFIG(uint32_t deadtime);
void LCD_PULSEONDURATION_CONFIG(uint32_t pluse_type);
FlagStatus LCD_GetFlagSTS(uint32_t lcd_flag);
void LCD_RamClear(void);
void LCD_Update_Request(void);
LCD_ErrorTypeDef LCD_WaitForSynchro(void);
LCD_ErrorTypeDef LCD_Init(LCD_InitType *LCD_InitStructure);
void LCD_ENABLE_IT(uint32_t lcd_interrupt);
void LCD_DISABLE_IT(uint32_t lcd_interrupt);
FlagStatus LCD_GET_IT_SOURCE(uint32_t lcd_interrupt);
void LCD_Clear_Flag(uint32_t lcd_flag);
LCD_ErrorTypeDef LCD_UpdateDisplayRequest(void);
LCD_ErrorTypeDef LCD_Write(uint32_t RAMRegisterIndex,uint32_t RAMRegisterMask,uint32_t RAMData);
LCD_ErrorTypeDef LCD_SetBit(uint32_t RAMRegisterIndex,uint32_t RAMData);
LCD_ErrorTypeDef LCD_ClearBit(uint32_t RAMRegisterIndex,uint32_t RAMData);
LCD_ErrorTypeDef LCD_ClockConfig(uint32_t LCD_ClkSource);

#ifdef __cplusplus
 }
#endif
 
#endif /* __N32A052_LCD_H__ */


