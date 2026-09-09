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
*\*\file n32a052.h
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/
#ifndef __N32A052_H__
#define __N32A052_H__

#ifdef __cplusplus
extern "C" {
#endif


/***  N32A052_Library_Basic ***/

#if !defined HSE_VALUE
#define HSE_VALUE (8000000U) /* Value of the External oscillator in Hz */
#endif

#define HSI_VALUE   (8000000U) /* Value of the Internal oscillator in Hz*/
#define HSI_24M     (24000000U)   

#define LSI_VALUE (32000) /* Value of the Internal Low Speed oscillator in Hz*/


/** In the following line adjust the External High Speed oscillator (HSE) Startup
   Timeout value **/
#define HSE_STARTUP_TIMEOUT ((uint16_t)0x1000U)  /* SYSCLK= 64M Time out for HSE start up */
#define HSI_STARTUP_TIMEOUT ((uint16_t)0x0300U)  /* SYSCLK= 64M Time out for HSI start up */
#define LSI_STARTUP_TIMEOUT ((uint16_t)0x0300U)  /* SYSCLK= 64M Time out for LSI start up */

/** n32a052 Standard Peripheral Library version number **/
#define __n32a052_STDPERIPH_VERSION_MAIN   (0x01U) /* [31:24] main version */
#define __n32a052_STDPERIPH_VERSION_SUB1   (0x00U) /* [23:16] sub1 version */
#define __n32a052_STDPERIPH_VERSION_SUB2   (0x00U) /* [15:8]  sub2 version */
#define __n32a052_STDPERIPH_VERSION_RC     (0x00U) /* [7:0]  release candidate */
#define __n32a052_STDPERIPH_VERSION        ( (__n32a052_STDPERIPH_VERSION_MAIN << 24U)\
                                           |(__n32a052_STDPERIPH_VERSION_SUB1 << 16U)\
                                           |(__n32a052_STDPERIPH_VERSION_SUB2 << 8U)\
                                           |(__n32a052_STDPERIPH_VERSION_RC))

/** Configuration of the Cortex-M0 Processor and Core Peripherals **/
#define __NVIC_PRIO_BITS          2U /* N32A052 uses 2 Bits for the Priority Levels    */
#define __Vendor_SysTickConfig    0U /* Set to 1 if different SysTick Config is used */

/*** N32A052 Interrupt Number Definition ***/

typedef enum IRQn
{
    /** Cortex-M0 Processor Exceptions Numbers **/
    NonMaskableInt_IRQn         = -14,    /* 2 Non Maskable Interrupt                                */
    HardFault_IRQn              = -13,    /* 3 Cortex-M0 Hard Fault Interrupt                        */
    SVC_IRQn                    = -5,     /* 11 Cortex-M0 SV Call Interrupt                          */
    PendSV_IRQn                 = -2,     /* 14 Cortex-M0 Pend SV Interrupt                          */
    SysTick_IRQn                = -1,     /* 15 Cortex-M0 System Tick Interrupt                      */

    /** N32A052 specific Interrupt Numbers  **/
    WWDG_IRQn                   = 0,      /* Window WatchDog Interrupt                               */
    PVD_IRQn                    = 1,      /* PVD through EXTI Line 16 detect Interrupt               */
    RTC_IRQn                    = 2,      /* PVD through EXTI Line 17/18/19 detect Interrupt         */
    MMU_RAMC_ERR_IRQn           = 3,      /* MMU&RAM global Interrupt                                */
    FLASH_IRQn                  = 4,      /* FLASH Interrupt                                         */
    RCC_IRQn                    = 5,      /* RCC global Interrupt                                    */
    EXTI0_1_IRQn                = 6,      /* EXTI Line 0 and 1 Interrupts                            */
    EXTI2_3_IRQn                = 7,      /* EXTI Line 2 and 3 Interrupts                            */
    EXTI4_15_IRQn               = 8,      /* EXTI Line 4 to 15 Interrupts                            */
    SAC_IRQn                    = 9,      /* SAC global Interrupt                                    */
    DMA_CH1_2_IRQn              = 10,     /* DMA Channel 1/2 global Interrupt                        */
    DMA_CH3_4_5_IRQn            = 11,     /* DMA Channel 3/4/5 global Interrupt                      */
    TIM4_IRQn                   = 12,     /* TIM4 global Interrupt                                   */
    TIM1_BRK_UP_TRG_COM_IRQn    = 13,     /* TIM1 Break, Update, Trigger and Commutation Interrupts  */
    TIM1_CC_IRQn                = 14,     /* TIM1 Capture Compare Interrupt                          */
    CAN_IRQn                    = 15,     /* CAN global Interrupt                                    */
    TIM3_IRQn                   = 16,     /* TIM3 global Interrupt                                   */
    UART3_4_IRQn                = 17,     /* UART3/4 global Interrupt                                */
    TIM5_IRQn                   = 18,     /* TIM5 global Interrupt                                   */
    TIM6_IRQn                   = 19,     /* TIM6 through EXTI Line 20 Interrupt                     */
    TIM2_IRQn                   = 20,     /* TIM2 global Interrupt                                   */
    ADC_IRQn                    = 21,     /* ADC global Interrupt                                    */
    SPI2_IRQn                   = 22,     /* SPI2 global Interrupt                                   */
    I2C1_IRQn                   = 23,     /* I2C1 global Interrupt                                   */
    I2C2_IRQn                   = 24,     /* I2C2 global Interrupt                                   */
    SPI1_IRQn                   = 25,     /* SPI1 global Interrupt                                   */
    UART1_IRQn                  = 26,     /* UART1 Interrupt                                         */
    SPI3_IRQn                   = 27,     /* SPI3 global Interrupt                                   */
    UART5_IRQn                  = 28,     /* UART5 global Interrupt                                  */
    LCD_IRQn                    = 29,     /* LCD global Interrupt                                    */
    UART2_IRQn                  = 30,     /* UART2 global Interrupt                                  */
    COMP1_2_3_4_IRQn            = 31      /* COMP1/2/3/4 Interrupt                                   */
} IRQn_Type;

#include "core_cm0.h"
#include "system_n32a052.h"
#include <stdint.h>
#include <stdbool.h>

/* n32a052 Standard Peripheral Library old types (maintained for legacy purpose) */
typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;

typedef const int32_t sc32;  /* Read Only */
typedef const int16_t sc16;  /* Read Only */
typedef const int8_t sc8;    /* Read Only */

typedef __IO int32_t  vs32;
typedef __IO int16_t  vs16;
typedef __IO int8_t   vs8;

typedef __I int32_t vsc32;  /* Read Only */
typedef __I int16_t vsc16;  /* Read Only */
typedef __I int8_t vsc8;   /* Read Only */

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef const uint32_t uc32;  /* Read Only */
typedef const uint16_t uc16;  /* Read Only */
typedef const uint8_t uc8;   /* Read Only */

typedef __IO uint32_t  vu32;
typedef __IO uint16_t vu16;
typedef __IO uint8_t  vu8;

typedef __I uint32_t vuc32;  /* Read Only */
typedef __I uint16_t vuc16;  /* Read Only */
typedef __I uint8_t vuc8;   /* Read Only */

typedef enum {RESET = 0, SET = !RESET} FlagStatus, INTStatus;

typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;

typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;

/* n32a052 Standard Peripheral Library old definitions (maintained for legacy purpose) */
#define HSEStartUp_TimeOut   HSE_STARTUP_TIMEOUT
#define HSE_Value            HSE_VALUE
#define HSI_Value            HSI_VALUE

/*** Analog to Digital Converter ***/
typedef struct
{
    __IO uint32_t STS;     	//0x00
    __IO uint32_t CTRL1;   	//0x04
    __IO uint32_t CTRL2;	//0x08
    __IO uint32_t CTRL3;	//0x0C
    __IO uint32_t SAMPT;	//0x10
    __IO uint32_t WDGHIGH;	//0x14
    __IO uint32_t WDGLOW;	//0x18
    __IO uint32_t DAT0;		//0x1C
    __IO uint32_t DAT1;		//0x20	
    __IO uint32_t DAT2;		//0x24
    __IO uint32_t DAT3;		//0x28
    __IO uint32_t DAT4;		//0x2C
} ADC_Module;


/*** CRC calculation unit ***/
typedef struct
{
    __IO uint32_t RESERVED0;	// 0x00	
    __IO uint32_t RESERVED1;	// 0x04
    __IO uint32_t RESERVED2;	// 0x08
    __IO uint32_t CRC16CTRL;	// 0x0C
    __IO uint8_t  CRC16DAT;		// 0x10
    uint8_t RESERVED3;			// 0x11
    uint16_t RESERVED4;			// 0x12
    __IO uint16_t CRC16D;		// 0x14
    uint16_t RESERVED5;			// 0x16
    __IO uint8_t LRC;			// 0x18
    uint8_t RESERVED6;			// 0x19
    uint16_t RESERVED7;			// 0x1A
} CRC_Module;



/***  External Interrupt/Event Controller ***/

typedef struct
{
   __IO uint32_t EMASK;   //0x00
   __IO uint32_t IMASK;   //0x04 
   __IO uint32_t FT_CFG;  //0x08
   __IO uint32_t RT_CFG;  //0x0C
   __IO uint32_t PEND;    //0x10
   __IO uint32_t SWIE;    //0x14
   __IO uint32_t TS_SEL;  //0x18
} EXTI_Module;

/*** FLASH Registers ***/

typedef struct
{
    __IO uint32_t AC;			//0x00
    __IO uint32_t KEY;			//0x04
    __IO uint32_t OPTKEY;		//0x08
    __IO uint32_t STS;			//0x0C
    __IO uint32_t CTRL;			//0x10
    __IO uint32_t ADD;			//0x14
    __IO uint32_t RESERVED0;	
    __IO uint32_t OB;			//0x1C
    __IO uint32_t WRP;			//0x20
    __IO uint32_t ECC;			//0x24
    __IO uint32_t RESERVED[8];
    __IO uint32_t USER;			//0x48
    __IO uint32_t START_ADD;	//0x4C
    __IO uint32_t VTOR;			//0x50
} FLASH_Module;

/*** Option Bytes Registers ***/

typedef struct
{
    __IO uint32_t RDP1;		//0x00
    uint32_t RESERVED0;
    __IO uint32_t USER1;	//0x08
    uint32_t RESERVED1;
    __IO uint32_t USER2;	//0x10
    uint32_t RESERVED2;
    __IO uint32_t USER3;	//0x18
    uint32_t RESERVED3;
    __IO uint32_t USER4;	//0x20
    uint32_t RESERVED4;
    __IO uint32_t USER5;	//0x28
    uint32_t RESERVED5;
    __IO uint32_t USER6;	//0x30
    uint32_t RESERVED6;
    __IO uint32_t Data0;	//0x38
    uint32_t RESERVED7;
    __IO uint32_t Data1;	//0x40
    uint32_t RESERVED8;
    __IO uint32_t WRP0;		//0x48
    uint32_t RESERVED9;
    __IO uint32_t WRP1;		//0x50
    uint32_t RESERVED10;
    __IO uint32_t WRP2;		//0x58
    uint32_t RESERVED11;
    __IO uint32_t WRP3;		//0x60
    uint32_t RESERVED12;
    __IO uint32_t RDP2;		//0x68
    uint32_t RESERVED13;
} OB_Module;

/** General Purpose I/O **/

typedef struct
{
    __IO uint32_t PMODE;	// 0x00
    __IO uint32_t POTYPE;	// 0x04
    __IO uint32_t SR;		// 0x08
    __IO uint32_t PUPD;		// 0x0C
    __IO uint32_t PID;		// 0x10
    __IO uint32_t POD;		// 0x14
    __IO uint32_t PBSC;		// 0x18
    __IO uint32_t PLOCK;	// 0x1C
    __IO uint32_t AFL;		// 0x20
    __IO uint32_t AFH;		// 0x24
    __IO uint32_t PBC;		// 0x28
    __IO uint32_t DS;		// 0x2C
} GPIO_Module;

/** Alternate Function I/O **/

typedef struct
{
    __IO uint32_t CFG;			// 0x00
	__IO uint32_t RESERVED0;	// 0x04
    __IO uint32_t EXTI_CFG[4];	// 0x08
    __IO uint32_t DIGEFT_CFG1;	// 0x18
    __IO uint32_t DIGEFT_CFG2;	// 0x1C
} AFIO_Module;



/***  Inter Integrated Circuit Interface ***/

typedef struct
{
  __IO uint32_t CTRL1;    //0x00
  __IO uint32_t CTRL2;    //0x04
  __IO uint16_t OADDR1;   //0x08
  uint16_t  RESERVED2;
  __IO uint16_t OADDR2;   //0x0C
  uint16_t  RESERVED3;
  __IO uint16_t DAT;      //0x10
  uint16_t  RESERVED4;
  __IO uint32_t STS1;     //0x14
  __IO uint32_t STS2;     //0x18
  __IO uint16_t CLKCTRL;  //0x1C
  uint16_t  RESERVED7;
  __IO uint16_t TMRISE;   //0x20
  uint16_t  RESERVED8;
  __IO uint16_t BYTENUM;  //0x24
  uint16_t  RESERVED9;
  __IO uint16_t GFLTRCTRL;//0x28
  uint16_t  RESERVED10;
} I2C_Module;


/***  Beeper  ***/

typedef struct
{
  __IO uint32_t CTRL;	// 0x00
} BEEPER_Module;


/*** Independent watchdog ***/

typedef struct
{
  __IO uint32_t KEY;		// 0x00
  __IO uint32_t PREDIV;		// 0x04
  __IO uint32_t RELV;		// 0x08
  __IO uint32_t STS;		// 0x0C
  __IO uint32_t FREEZE;		// 0x10
} IWDG_Module;

/*** Power Control ***/
typedef struct
{
    __IO uint32_t CTRL;      //0x00
    __IO uint32_t CTRLSTS;   //0x04
    __IO uint32_t CTRL2;     //0x08
    uint32_t      RESERVED0;
    uint32_t      RESERVED1;
    __IO uint32_t CTRL3;     //0x14
    uint32_t      RESERVED2;
    uint32_t      RESERVED3;
    __IO uint32_t CTRL4;     //0x20
    __IO uint32_t CTRL5;     //0x24
    __IO uint32_t CTRL6;     //0x28
    uint32_t      RESERVED4;
    __IO uint32_t DBG_CTRL;  //0x30
} PWR_Module;

/*** Reset and Clock Control ***/

typedef struct
{
    __IO uint32_t CTRL;       //0x00
    __IO uint32_t CFG;        //0x04
    __IO uint32_t CLKINT;     //0x08
    __IO uint32_t APB2PRST;   //0x0C
    __IO uint32_t APB1PRST;   //0x10
    __IO uint32_t AHBPCLKEN;  //0x14
    __IO uint32_t APB2PCLKEN; //0x18
    __IO uint32_t APB1PCLKEN; //0x1C
    __IO uint32_t LSCTRL;     //0x20
    __IO uint32_t CTRLSTS;    //0x24
    __IO uint32_t AHBPRST;    //0x28
    __IO uint32_t CFG2;       //0x2C
    __IO uint32_t CFG3;       //0x30
    __IO uint32_t EMCCTRL;    //0x34
} RCC_Module;


/*** COMP_Single ***/
typedef struct
{
    __IO uint32_t CTRL;
    __IO uint32_t FILC;
    __IO uint32_t FILP;
    uint32_t RESERVED;
} COMP_SingleType;

/*** compare ***/

typedef struct
{
    __IO uint32_t res0[4];	//0x00
    COMP_SingleType COMP1;	//0x10
    COMP_SingleType COMP2;	//0x20
    COMP_SingleType COMP3;	//0x30
    COMP_SingleType COMP4;	//0x40
    __IO uint32_t res1[8];	
    __IO uint32_t OSEL;		//0x70
    __IO uint32_t res2[4];
    __IO uint32_t LOCK;		//0x84
    __IO uint32_t res3;		//0x88
    __IO uint32_t INTEN;	//0x8C
    __IO uint32_t INTSTS;	//0x90
    __IO uint32_t VREFSCAL;	//0x94
    __IO uint32_t TIM_OSEL; //0x98
} COMP_Module;



/*** Serial Peripheral Interface ***/
typedef struct
{
    __IO uint32_t CTRL1;   // 0x00
    __IO uint32_t CTRL2;   // 0x04
    __IO uint32_t STS;     // 0x08
    __IO uint32_t DAT;     // 0x0C
    __IO uint32_t CRCTDAT; // 0x10
    __IO uint32_t CRCRDAT; // 0x14
    __IO uint32_t CRCPOLY; // 0x18
    __IO uint32_t RESERVED0[7]; // 0x1C
    __IO uint32_t CTRL3;   // 0x38
} SPI_Module;


/*** TIM ***/

typedef struct
{
    __IO uint32_t CTRL1;  // 0x00
    __IO uint32_t CTRL2;  // 0x04
    __IO uint32_t STS;    // 0x08
    __IO uint32_t EVTGEN; // 0x0C
    __IO uint32_t SMCTRL; // 0x10
    __IO uint32_t DINTEN; // 0x14
    __IO uint32_t CCMOD1; // 0x18
    __IO uint32_t CCMOD2; // 0x1C
    __IO uint32_t CCMOD3; // 0x20
    __IO uint32_t CCEN;   // 0x24
    __IO uint32_t CCDAT1; // 0x28
    __IO uint32_t CCDAT2; // 0x2C
    __IO uint32_t CCDAT3; // 0x30
    __IO uint32_t CCDAT4; // 0x34
    __IO uint32_t CCDAT5; // 0x38
    __IO uint32_t CCDAT6; // 0x3C
    __IO uint32_t PSC;    // 0x40
    __IO uint32_t AR;     // 0x44
    __IO uint32_t CNT;    // 0x48
    __IO uint32_t REPCNT; // 0x4C
    __IO uint32_t BKDT;   // 0x50
    __IO uint32_t CCDAT7; // 0x54
    __IO uint32_t CCDAT8; // 0x58
    __IO uint32_t CCDAT9; // 0x5C
    __IO uint32_t BKFR;   // 0x60
    __IO uint32_t C1FILT; // 0x64
    __IO uint32_t C2FILT; // 0x68
    __IO uint32_t C3FILT; // 0x6C
    __IO uint32_t C4FILT; // 0x70
    __IO uint32_t FILTO;  // 0x74
    __IO uint32_t INSEL;  // 0x78
    uint32_t  RESERVED0;  // 0x7C
    uint32_t  RESERVED1;  // 0x80
    uint32_t  RESERVED2;  // 0x84
    uint32_t  RESERVED3;  // 0x88
    uint32_t  RESERVED4;  // 0x9C
    uint32_t  RESERVED5;  // 0x90
    __IO uint32_t DCTRL;  // 0x94
    __IO uint32_t DADDR;  // 0x98
} TIM_Module;



/*** Universal Asynchronous Receiver Transmitter ***/
typedef struct
{
    __IO uint32_t CTRL1;  // 0x00
    __IO uint32_t CTRL2;  // 0x04
    __IO uint32_t CTRL3;  // 0x08
    __IO uint32_t STS;    // 0x0C
    __IO uint32_t DAT;    // 0x10
    __IO uint32_t BRCF;   // 0x14
    __IO uint32_t GTP;    // 0x18
} UART_Module;


/*** Controller Area Network TxMailBox ***/

typedef struct
{
    __IO uint32_t TMI;  //0x180, 0x190, 0x1A0
    __IO uint32_t TMDT;	//0x184, 0x194, 0x1A4
    __IO uint32_t TMDL;	//0x188, 0x198, 0x1A8
    __IO uint32_t TMDH;	//0x18c, 0x19c, 0x1ac
} CAN_TxMailBox_Param;

/*** Controller Area Network FIFOMailBox ***/

typedef struct
{
    __IO uint32_t RMI;	//0x1B0, 0x1C0
    __IO uint32_t RMDT;	//0x1B4, 0x1C4
    __IO uint32_t RMDL;	//0x1B8, 0x1C8
    __IO uint32_t RMDH;	//0x1BC, 0x1CC
} CAN_FIFOMailBox_Param;

/*** Controller Area Network FilterRegister ***/

typedef struct
{
    __IO uint32_t FR1;		//0x240h
    __IO uint32_t FR2;		//0x31C
} CAN_FilterRegister_Param;

/*** Controller Area Network ***/

typedef struct
{
    __IO uint32_t MCTRL;	//0x00
    __IO uint32_t MSTS;		//0x04
    __IO uint32_t TSTS;		//0x08
    __IO uint32_t RFF0;		//0x0C
    __IO uint32_t RFF1;		//0x10
    __IO uint32_t INTE;		//0x14
    __IO uint32_t ESTS;		//0x18
    __IO uint32_t BTIM;		//0x1C
    uint32_t RESERVED0[88];
    CAN_TxMailBox_Param sTxMailBox[3];
    CAN_FIFOMailBox_Param sFIFOMailBox[2];
    uint32_t RESERVED1[12];
    __IO uint32_t FMC;		//0x200
    __IO uint32_t FM1;		//0x204
    uint32_t RESERVED2;
    __IO uint32_t FS1;		//0x20C
    uint32_t RESERVED3;
    __IO uint32_t FFA1;		//0x214
    uint32_t RESERVED4;
    __IO uint32_t FA1;		//0x21C
    uint32_t RESERVED5[8];
    CAN_FilterRegister_Param sFilterRegister[14];
} CAN_Module;


/*** Real-Time Clock ***/

/**  Real-Time Clock **/

typedef struct
{
    __IO uint32_t INITSTS;  // 0x00
    __IO uint32_t CTRL;     // 0x04
    __IO uint32_t TSH;    	// 0x08  
    __IO uint32_t DATE;   	// 0x0C  
    __IO uint32_t WRP; 		// 0x10    
    __IO uint32_t SCTRL; 	// 0x14   
    __IO uint32_t SUBS;		// 0x18
    __IO uint32_t TST;		// 0x1C
    __IO uint32_t ALARMA;	// 0x20 
    __IO uint32_t PRE;		// 0x24
    __IO uint32_t ALARMB;	// 0x28
    __IO uint32_t WKUPT;	// 0x2C
    __IO uint32_t TMPCFG; 	// 0x30
    __IO uint32_t ALRMASS;	// 0x34
    __IO uint32_t OPT;		// 0x38
    __IO uint32_t ALRMBSS;	// 0x3C
    __IO uint32_t CALIB;	// 0x40
    __IO uint32_t TSSS;		// 0x44
    __IO uint32_t TSD;		// 0x48
} RTC_Module;

/*** Window WATCHDOG ***/

typedef struct
{
    __IO uint32_t CTRL;		// 0x00
    __IO uint32_t CFG;		// 0x04
    __IO uint32_t STS;		// 0x08
} WWDG_Module;

/*** DMA Controller ***/
typedef struct
{
    __IO uint32_t CHCFG;		//0x08+20 * (x-1)
    __IO uint32_t TXNUM;		//0x0c+20 * (x-1)
    __IO uint32_t PADDR;		//0x10+20 * (x-1)
    __IO uint32_t MADDR;		//0x14+20 * (x-1)
    __IO uint32_t CHSEL;		//0x18+20 * (x-1)
} DMA_ChannelType;

typedef struct
{
    __IO uint32_t INTSTS;					//0x00
    __IO uint32_t INTCLR;					//0x04
    __IO DMA_ChannelType DMA_Channel[5];
} DMA_Module;


/*** DAC ***/
typedef struct
{
    __IO uint32_t CTRL;		//0x00
    __IO uint32_t SOTTR;	//0x04
    __IO uint32_t DATO;		//0x08
    __IO uint32_t DH8RA;	//0x0C	
    __IO uint32_t DH12LA;	//0x10
    __IO uint32_t DH12RA;	//0x14
} DAC_Module;

/*** LCD ***/
typedef struct
{
    __IO uint32_t CTRL; 		//0x00   
    __IO uint32_t FCTRL;  	//0x04  
    __IO uint32_t STS;      //0x08
    __IO uint32_t CLR;  		//0x0C 
    uint32_t RESERVED;     
    __IO uint32_t RAM_COM[16];     //0x14 + x*4
} LCD_Module;

/*** SAC ***/
typedef struct
{
    uint32_t RESERVED;     
} SAC_Module;


/*** Peripheral memory map ***/

#define FLASH_BASE            ((uint32_t)0x08000000U) /* FLASH base address in the alias region */
#define SRAM_BASE             ((uint32_t)0x20000000U) /* SRAM base address in the alias region */
#define PERIPH_BASE           ((uint32_t)0x40000000U) /* Peripheral base address in the alias region */

#define UCID_BASE             ((uint32_t)0x1FFFF8D0U) /* UCID Address : 0x1FFF_F8D0 */
#define UCID_LENGTH           ((uint32_t)0x10U)       /* UCID Length  : 16 Bytes */
#define UID_BASE              ((uint32_t)0x1FFFF910U) /* UID Address  : 0x1FFF_F910 */
#define UID_LENGTH            ((uint32_t)0x0CU)       /* UID Length   : 12 Bytes */
#define DBGMCU_ID_BASE        ((uint32_t)0x1FFFF920U) /* DBGMCU_ID Address :0x1FFF_F920 */
#define DBGMCU_ID_LENGTH      ((uint8_t)0x04U)         /* DBGMCU_ID Length : 4 Bytes */


/** Peripheral memory map **/
#define APB1PERIPH_BASE       (PERIPH_BASE)
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x10000U)
#define AHBPERIPH_BASE        (PERIPH_BASE + 0x20000U)

/** APB1 **/
#define BEEPER_BASE           (APB1PERIPH_BASE + 0x0000U)
#define UART3_BASE            (APB1PERIPH_BASE + 0x0400U)
#define UART4_BASE            (APB1PERIPH_BASE + 0x0800U)
#define UART5_BASE            (APB1PERIPH_BASE + 0x0C00U)
#define TIM6_BASE             (APB1PERIPH_BASE + 0x1000U)
#define CAN_BASE              (APB1PERIPH_BASE + 0x1C00U)
#define DAC_BASE              (APB1PERIPH_BASE + 0x2000U)
#define COMP_BASE             (APB1PERIPH_BASE + 0x2400U)
#define RTC_BASE              (APB1PERIPH_BASE + 0x2800U)
#define WWDG_BASE             (APB1PERIPH_BASE + 0x2C00U)
#define IWDG_BASE             (APB1PERIPH_BASE + 0x3000U)
#define LCD_BASE              (APB1PERIPH_BASE + 0x3C00U)
#define I2C1_BASE             (APB1PERIPH_BASE + 0x5400U)
#define I2C2_BASE             (APB1PERIPH_BASE + 0x5800U)
#define PWR_BASE              (APB1PERIPH_BASE + 0x7000U)

/** APB2 **/
#define AFIO_BASE             (APB2PERIPH_BASE + 0x0000U)
#define EXTI_BASE             (APB2PERIPH_BASE + 0x0400U)
#define GPIOA_BASE            (APB2PERIPH_BASE + 0x0800U)
#define GPIOB_BASE            (APB2PERIPH_BASE + 0x0C00U)
#define GPIOC_BASE            (APB2PERIPH_BASE + 0x1000U)
#define GPIOD_BASE            (APB2PERIPH_BASE + 0x1C00U)
#define SPI1_BASE             (APB2PERIPH_BASE + 0x2000U)
#define TIM4_BASE             (APB2PERIPH_BASE + 0x2400U)
#define TIM5_BASE             (APB2PERIPH_BASE + 0x2800U)
#define TIM1_BASE             (APB2PERIPH_BASE + 0x2C00U)
#define TIM3_BASE             (APB2PERIPH_BASE + 0x3000U)
#define TIM2_BASE             (APB2PERIPH_BASE + 0x3400U)
#define UART1_BASE            (APB2PERIPH_BASE + 0x3800U)
#define UART2_BASE            (APB2PERIPH_BASE + 0x3C00U)
#define SPI3_BASE             (APB2PERIPH_BASE + 0x4000U)
#define SPI2_BASE             (APB2PERIPH_BASE + 0x4400U)


/** AHB **/
#define DMA_BASE              (AHBPERIPH_BASE + 0x0000U)
#define DMA_CH1_BASE          (AHBPERIPH_BASE + 0x0008U)
#define DMA_CH2_BASE          (AHBPERIPH_BASE + 0x001CU)
#define DMA_CH3_BASE          (AHBPERIPH_BASE + 0x0030U)
#define DMA_CH4_BASE          (AHBPERIPH_BASE + 0x0044U)
#define DMA_CH5_BASE          (AHBPERIPH_BASE + 0x0058U)
#define ADC_BASE              (AHBPERIPH_BASE + 0x0800U)
#define RCC_BASE              (AHBPERIPH_BASE + 0x1000U)
#define FLASH_R_BASE          (AHBPERIPH_BASE + 0x2000U) /* Flash registers base address */
#define OB_BASE               ((uint32_t)0x1FFFFC00U)    /* Flash Option Bytes base address */
#define CRC_BASE              (AHBPERIPH_BASE + 0x3000U)
#define SAC_BASE              (AHBPERIPH_BASE + 0x4000U)
#define SAC_SRAM512B_BASE     (AHBPERIPH_BASE + 0x4400U)

/** Peripheral_declaration **/
#define BEEPER              ((BEEPER_Module *) BEEPER_BASE)
#define UART3               ((UART_Module *) UART3_BASE)
#define UART4               ((UART_Module *) UART4_BASE)
#define UART5               ((UART_Module *) UART5_BASE)
#define TIM6                ((TIM_Module *) TIM6_BASE)
#define CAN                 ((CAN_Module *) CAN_BASE)
#define DAC                 ((DAC_Module *) DAC_BASE)
#define COMP                ((COMP_Module *) COMP_BASE)
#define RTC                 ((RTC_Module *) RTC_BASE)
#define WWDG                ((WWDG_Module *) WWDG_BASE)
#define IWDG                ((IWDG_Module *) IWDG_BASE)
#define LCD                 ((LCD_Module *) LCD_BASE)
#define I2C1                ((I2C_Module *) I2C1_BASE)
#define I2C2                ((I2C_Module *) I2C2_BASE)
#define PWR                 ((PWR_Module *) PWR_BASE)

#define AFIO                ((AFIO_Module *) AFIO_BASE)
#define EXTI                ((EXTI_Module *) EXTI_BASE)
#define GPIOA               ((GPIO_Module *) GPIOA_BASE)
#define GPIOB               ((GPIO_Module *) GPIOB_BASE)
#define GPIOC               ((GPIO_Module *) GPIOC_BASE)
#define GPIOD               ((GPIO_Module *) GPIOD_BASE)
#define SPI1                ((SPI_Module *) SPI1_BASE)
#define TIM4                ((TIM_Module *) TIM4_BASE)
#define TIM5                ((TIM_Module *) TIM5_BASE)
#define TIM1                ((TIM_Module *) TIM1_BASE)
#define TIM3                ((TIM_Module *) TIM3_BASE)
#define TIM2                ((TIM_Module *) TIM2_BASE)
#define UART1               ((UART_Module *) UART1_BASE)
#define UART2               ((UART_Module *) UART2_BASE)
#define SPI3                ((SPI_Module *) SPI3_BASE)
#define SPI2                ((SPI_Module *) SPI2_BASE)

#define DMA                 ((DMA_Module *)DMA_BASE)
#define DMA_CH1             ((DMA_ChannelType*)DMA_CH1_BASE)
#define DMA_CH2             ((DMA_ChannelType*)DMA_CH2_BASE)
#define DMA_CH3             ((DMA_ChannelType*)DMA_CH3_BASE)
#define DMA_CH4             ((DMA_ChannelType*)DMA_CH4_BASE)
#define DMA_CH5             ((DMA_ChannelType*)DMA_CH5_BASE)
#define ADC                 ((ADC_Module *) ADC_BASE)
#define RCC                 ((RCC_Module *) RCC_BASE)
#define FLASH               ((FLASH_Module *) FLASH_R_BASE)
#define OBT                 ((OB_Module *) OB_BASE)
#define CRC                 ((CRC_Module *) CRC_BASE)
#define SAC                 ((SAC_Module *) SAC_BASE)


/***  Peripheral Registers_Bits_Definition   ***/

/*** CRC calculation unit ***/
/** Bit definition for CRC_CRC16CTRL register **/
#define CRC16_CTRL_ENDHL    ((uint8_t)0x02U)
#define CRC16_CTRL_LITTLE   ((uint8_t)0x02U)
#define CRC16_CTRL_BIG      ((uint8_t)0xFDU)

#define CRC16_CTRL_CLR      ((uint8_t)0x04U) 
#define CRC16_CTRL_RESET    ((uint8_t)0x04U)
#define CRC16_CTRL_NO_RESET ((uint8_t)0xFBU)

/** Bit definition for CRC_CRC16DAT register **/
#define CRC16_CRC16DAT      ((uint8_t)0xFFU)

/** Bit definition for CRC_CRC16D register **/
#define CRC16_CRC16D        ((uint16_t)0xFFFFU)


/*** Power Control ***/
/** Bit definition for PWR_CTRL register **/
#define PWR_CTRL_IWDGRSTEN ((uint32_t)0x00000001U) /* IWDG reset request causes a system reset */
#define PWR_CTRL_PDSTP     ((uint32_t)0x00000002U) /* 0: CPU output DEEPSLEEP is 1, and the chip enters STOP mode, */
                                                                      /* 1: CPU output DEEPSLEEP is 1, and the chip enters PD mode */
#define PWR_CTRL_CLRWKUPF  ((uint32_t)0x00000004U) /* Clear Wakeup Flag */
#define PWR_CTRL_CLRDBGPDF ((uint32_t)0x00000008U) /* Clear DBGPDF flag */
#define PWR_CTRL_PVDEN     ((uint32_t)0x00000010U) /* PVD Enables control */

#define PWR_CTRL_PLS       ((uint32_t)0x000001E0U) /* PLS[3:0] bits (PVD Level Selection) */
#define PWR_CTRL_PLS_0     ((uint32_t)0x00000020U) /* Bit 0 */
#define PWR_CTRL_PLS_1     ((uint32_t)0x00000040U) /* Bit 1 */
#define PWR_CTRL_PLS_2     ((uint32_t)0x00000080U) /* Bit 2 */
#define PWR_CTRL_PLS_3     ((uint32_t)0x00000100U) /* Bit 3 */

#define PWR_CTRL_PDRS      ((uint32_t)0x00000600U) /* PDRS[2:0] bits (VDDD PDR trigger level in STOP mode) */
#define PWR_CTRL_PDRS_0    ((uint32_t)0x00000200U) /* Bit 0 */
#define PWR_CTRL_PDRS_1    ((uint32_t)0x00000400U) /* Bit 1 */

#define PWR_CTRL_NRSTPOL   ((uint32_t)0x00000800U) /* NRST polarity selection */

#define PWR_CTRL_PVDCNT    ((uint32_t)0x00FF0000) /* PVD count */
#define PWR_CTRL_PVDFILEN  ((uint32_t)0x01000000) /* Enable PVD filter */
#define PWR_CTRL_PVDITEN   ((uint32_t)0x02000000) /* Enable PVD interrupt */

/** Bit definition for PWR_CTRLSTS register **/
#define PWR_CTRLSTS_WKUPF   ((uint32_t)0x00000001U) /* Wakeup Flag */
#define PWR_CTRLSTS_DBGPDF  ((uint32_t)0x00000002U) /* DBGPDF Flag */
#define PWR_CTRLSTS_PVDO    ((uint32_t)0x00000004U) /* PVD Output */
#define PWR_CTRLSTS_WKUP0EN ((uint32_t)0x00000100U) /* Enable WKUP pin PA0 */
#define PWR_CTRLSTS_WKUP1EN ((uint32_t)0x00000200U) /* Enable WKUP pin PA2 */
#define PWR_CTRLSTS_WKUPPOL ((uint32_t)0x00000800U) /* Polarity of WKUP pin PA0/PA2,0:Falling edge,1:Rising edge */

/** Bit definition for PWR_CTRL2 register **/
#define PWR_CTRL2_LVRCNT   ((uint32_t)0x000000FFU) /* LVR filter control counts */
#define PWR_CTRL2_LVRFILEN ((uint32_t)0x00000100U) /* Enable LVR filter */
#define PWR_CTRL2_LVRRSTEN ((uint32_t)0x00000200U) /* Enable LVR reset */
#define PWR_CTRL2_LVREN    ((uint32_t)0x00000400U) /* Enable LVR */

#define PWR_CTRL2_LVRLS    ((uint32_t)0x00007800U) /* LVRLS[3:0] bits (LVR Level Selection) */
#define PWR_CTRL2_LVRLS_0  ((uint32_t)0x00000800U) /* Bit 0 */
#define PWR_CTRL2_LVRLS_1  ((uint32_t)0x00001000U) /* Bit 1 */
#define PWR_CTRL2_LVRLS_2  ((uint32_t)0x00002000U) /* Bit 2 */
#define PWR_CTRL2_LVRLS_3  ((uint32_t)0x00004000U) /* Bit 3 */

#define PWR_CTRL2_LVRO     ((uint32_t)0x00008000U) /* LVR Output */

#define PWR_CTRL2_LVRKEY   ((uint32_t)0xFF000000U) /* LVR key */

/** Bit definition for PWR_CTRL3 register **/
#define PWR_CTRL3_LSIEN      ((uint32_t)0x00000080U) /* Control PWR Enables the LSI */
#define PWR_CTRL3_PDRSEL     ((uint32_t)0x00000200U) /* VDDD PDR select signal is controlled by PWR */
#define PWR_CTRL3_NRSTCNT    ((uint32_t)0x07FF0000U) /* NRST filter control counts */
#define PWR_CTRL3_NRSTFILEN  ((uint32_t)0x08000000U) /* Enable NRST filter */

/** Bit definition for PWR_CTRL4 register **/
#define PWR_CTRL4_FLHWKUP ((uint32_t)0x00000001U) /* Flash quick Wake up */
#define PWR_CTRL4_STBFLH  ((uint32_t)0x00000002U) /* Flash Deep standby mode */
#define PWR_CTRL4_RUNF    ((uint32_t)0x00000004U) /* System in RUN mode */

/** Bit definition for PWR_CTRL5 register **/
#define PWR_CTRL5_STPMRSEL   ((uint32_t)0x0000000CU) /* STPMRSEL[1:0] bits (After enter STOP mode, VDDD output voltage select) */
#define PWR_CTRL5_STPMRSEL_0 ((uint32_t)0x00000004U) /* Bit 0 */
#define PWR_CTRL5_STPMRSEL_1 ((uint32_t)0x00000008U) /* Bit 1 */

/** Bit definition for PWR_CTRL6 register **/
#define PWR_CTRL6_STPMREN   ((uint32_t)0x0000000CU) /* STPMREN[1:0] bits (After enter STOP mode, Enable VDDD output voltage select) */
#define PWR_CTRL6_STPMREN_0 ((uint32_t)0x00000004U) /* Bit 0 */
#define PWR_CTRL6_STPMREN_1 ((uint32_t)0x00000008U) /* Bit 1 */

/** Bit definition for DBG_CTRL register **/
#define DBG_CTRL_SLEEP      ((uint32_t)0x00000001U) /* Debug SLEEP mode control */
#define DBG_CTRL_STOP       ((uint32_t)0x00000002U) /* Debug STOP mode control */
#define DBG_CTRL_PD         ((uint32_t)0x00000004U) /* Debug PD mode control */
#define DBG_CTRL_IWDGSTP    ((uint32_t)0x00000100U) /* Debug IWDG mode control */
#define DBG_CTRL_WWDGSTP    ((uint32_t)0x00000200U) /* Debug WWDG mode control */
#define DBG_CTRL_TIM1STP    ((uint32_t)0x00000400U) /* Debug TIM1 mode control */
#define DBG_CTRL_TIM3STP    ((uint32_t)0x00001000U) /* Debug TIM3 mode control */
#define DBG_CTRL_CANSTP     ((uint32_t)0x00004000U) /* Debug CAN mode control */
#define DBG_CTRL_I2C1TIMOUT ((uint32_t)0x00008000U) /* Debug I2C1TIMOUT mode control */
#define DBG_CTRL_I2C2TIMOUT ((uint32_t)0x00010000U) /* Debug I2C2TIMOUT mode control */
#define DBG_CTRL_TIM5STP    ((uint32_t)0x00020000U) /* Debug TIM5 mode control */
#define DBG_CTRL_TIM6STP    ((uint32_t)0x00040000U) /* Debug TIM6 mode control */
#define DBG_CTRL_TIM4STP    ((uint32_t)0x00080000U) /* Debug TIM4 mode control */
#define DBG_CTRL_TIM2STP    ((uint32_t)0x00100000U) /* Debug TIM2 mode control */


/*** Reset and Clock Control ***/

/** Bit definition for RCC_CTRL register **/

#define  RCC_CTRL_HSIEN      ((uint32_t)0x00000001U) /* Internal High Speed clock enable */
#define  RCC_CTRL_HSIRDF     ((uint32_t)0x00000002U) /* Internal High Speed 8M clock ready flag */
#define  RCC_CTRL_HSI24MRDF  ((uint32_t)0x00000004U) /* Internal High Speed 24M clock ready flag */
#define  RCC_CTRL_HSITRIM    ((uint32_t)0x000000F0U) /* Internal High Speed clock trimming */
#define  RCC_CTRL_HSEEN      ((uint32_t)0x00010000U) /* External High Speed clock enable */
#define  RCC_CTRL_HSERDF     ((uint32_t)0x00020000U) /* External High Speed clock ready flag */
#define  RCC_CTRL_HSEBP      ((uint32_t)0x00040000U) /* External High Speed clock bypass */
#define  RCC_CTRL_CLKSSEN    ((uint32_t)0x00080000U) /* Clock Security System enable */  

#define  RCC_CTRL_HSERDTIM         ((uint32_t)0x00300000U) /* External High Speed clock ready delay time */  
#define  RCC_CTRL_HSERDTIM_0_5MS   ((uint32_t)0x00000000U) /*  HSE Clock ready delay 0.5ms */  
#define  RCC_CTRL_HSERDTIM_1_0MS   ((uint32_t)0x00100000U) /*  HSE Clock ready delay 1.0ms */  
#define  RCC_CTRL_HSERDTIM_1_5MS   ((uint32_t)0x00200000U) /*  HSE Clock ready delay 1.5ms */  
#define  RCC_CTRL_HSERDTIM_2_5MS   ((uint32_t)0x00300000U) /*  HSE Clock ready delay 2.5ms */  

#define  RCC_CTRL_PLLBP      ((uint32_t)0x00400000U) /* PLL clock bypass */
#define  RCC_CTRL_PLLOUTEN   ((uint32_t)0x00800000U)    /* PLL clock out enable */
#define  RCC_CTRL_PLLEN      ((uint32_t)0x01000000U) /* PLL clock enable */
#define  RCC_CTRL_PLLRDF     ((uint32_t)0x02000000U) /* PLL clock ready flag */  
#define  RCC_CTRL_LKUPRSTEN  ((uint32_t)0x04000000U) /* M0 core lock up reset enabled */    


/** Bit definition for RCC_CFG register **/

/** SCLKSW configuration **/
#define RCC_CFG_SCLKSW      ((uint32_t)0x00000007U) /* SCLKSW[2:0] bits (System clock Switch) */
#define RCC_CFG_SCLKSW_0    ((uint32_t)0x00000001U) /* Bit 0 */
#define RCC_CFG_SCLKSW_1    ((uint32_t)0x00000002U) /* Bit 1 */
#define RCC_CFG_SCLKSW_2    ((uint32_t)0x00000004U) /* Bit 2 */

#define RCC_CFG_SCLKSW_HSI  ((uint32_t)0x00000000U) /* HSI selected as system clock */
#define RCC_CFG_SCLKSW_HSE  ((uint32_t)0x00000001U) /* HSE selected as system clock */
#define RCC_CFG_SCLKSW_PLL  ((uint32_t)0x00000002U) /* PLL selected as system clock */
#define RCC_CFG_SCLKSW_LSI  ((uint32_t)0x00000003U) /* LSI selected as system clock */

/* SCLKSTS configuration */
#define RCC_CFG_SCLKSTS     ((uint32_t)0x0000C008U) /* SCLKSTS[2:0] bits (System Clock Switch Status) */
#define RCC_CFG_SCLKSTS_0   ((uint32_t)0x00000008U) /* Bit 0 */
#define RCC_CFG_SCLKSTS_1   ((uint32_t)0x00004000U) /* Bit 1 */
#define RCC_CFG_SCLKSTS_2   ((uint32_t)0x00008000U) /* Bit 1 */

#define RCC_CFG_SCLKSTS_HSI ((uint32_t)0x00000000U) /* HSI oscillator used as system clock */
#define RCC_CFG_SCLKSTS_HSE ((uint32_t)0x00000008U) /* HSE oscillator used as system clock */
#define RCC_CFG_SCLKSTS_PLL ((uint32_t)0x00004000U) /* PLL used as system clock */
#define RCC_CFG_SCLKSTS_LSI ((uint32_t)0x00004008U) /* LSI oscillator used as system clock */

/** AHBPRES configuration */
#define RCC_CFG_AHBPRES     ((uint32_t)0x000000F0U) /* AHBPRES[3:0] bits (AHB prescaler) */
#define RCC_CFG_AHBPRES_0   ((uint32_t)0x00000010U) /* Bit 0 */
#define RCC_CFG_AHBPRES_1   ((uint32_t)0x00000020U) /* Bit 1 */
#define RCC_CFG_AHBPRES_2   ((uint32_t)0x00000040U) /* Bit 2 */
#define RCC_CFG_AHBPRES_3   ((uint32_t)0x00000080U) /* Bit 3 */

#define RCC_CFG_AHBPRES_DIV1    ((uint32_t)0x00000000U) /* SYSCLK not divided */
#define RCC_CFG_AHBPRES_DIV2    ((uint32_t)0x00000080U) /* SYSCLK divided by 2 */
#define RCC_CFG_AHBPRES_DIV4    ((uint32_t)0x00000090U) /* SYSCLK divided by 4 */
#define RCC_CFG_AHBPRES_DIV8    ((uint32_t)0x000000A0U) /* SYSCLK divided by 8 */
#define RCC_CFG_AHBPRES_DIV16   ((uint32_t)0x000000B0U) /* SYSCLK divided by 16 */
#define RCC_CFG_AHBPRES_DIV64   ((uint32_t)0x000000C0U) /* SYSCLK divided by 64 */
#define RCC_CFG_AHBPRES_DIV128  ((uint32_t)0x000000D0U) /* SYSCLK divided by 128 */
#define RCC_CFG_AHBPRES_DIV256  ((uint32_t)0x000000E0U) /* SYSCLK divided by 256 */
#define RCC_CFG_AHBPRES_DIV512  ((uint32_t)0x000000F0U) /* SYSCLK divided by 512 */

/** APB1PRES configuration */
#define RCC_CFG_APB1PRES    ((uint32_t)0x00000700U) /* APB1PRES[2:0] bits (APB1 prescaler) */
#define RCC_CFG_APB1PRES_0  ((uint32_t)0x00000100U) /* Bit 0 */
#define RCC_CFG_APB1PRES_1  ((uint32_t)0x00000200U) /* Bit 1 */
#define RCC_CFG_APB1PRES_2  ((uint32_t)0x00000400U) /* Bit 2 */

#define RCC_CFG_APB1PRES_DIV1   ((uint32_t)0x00000000U) /* HCLK not divided */
#define RCC_CFG_APB1PRES_DIV2   ((uint32_t)0x00000400U) /* HCLK divided by 2 */
#define RCC_CFG_APB1PRES_DIV4   ((uint32_t)0x00000500U) /* HCLK divided by 4 */
#define RCC_CFG_APB1PRES_DIV8   ((uint32_t)0x00000600U) /* HCLK divided by 8 */
#define RCC_CFG_APB1PRES_DIV16  ((uint32_t)0x00000700U) /* HCLK divided by 16 */

/** APB2PRES configuration **/
#define RCC_CFG_APB2PRES    ((uint32_t)0x00003800U) /* APB2PRES[2:0] bits (APB2 prescaler) */
#define RCC_CFG_APB2PRES_0  ((uint32_t)0x00000800U) /* Bit 0 */
#define RCC_CFG_APB2PRES_1  ((uint32_t)0x00001000U) /* Bit 1 */
#define RCC_CFG_APB2PRES_2  ((uint32_t)0x00002000U) /* Bit 2 */

#define RCC_CFG_APB2PRES_DIV1  ((uint32_t)0x00000000U) /* HCLK not divided */
#define RCC_CFG_APB2PRES_DIV2  ((uint32_t)0x00002000U) /* HCLK divided by 2 */
#define RCC_CFG_APB2PRES_DIV4  ((uint32_t)0x00002800U) /* HCLK divided by 4 */
#define RCC_CFG_APB2PRES_DIV8  ((uint32_t)0x00003000U) /* HCLK divided by 8 */
#define RCC_CFG_APB2PRES_DIV16 ((uint32_t)0x00003800U) /* HCLK divided by 16 */

/* PLLMUL configuration */
#define RCC_CFG_PLLMULFCT   ((uint32_t)0x000F0000U) /* PLLMUL[3:0] bits (PLL multiplication factor) */
#define RCC_CFG_PLLMULFCT_0 ((uint32_t)0x00010000U) /* Bit 0 */
#define RCC_CFG_PLLMULFCT_1 ((uint32_t)0x00020000U) /* Bit 1 */
#define RCC_CFG_PLLMULFCT_2 ((uint32_t)0x00040000U) /* Bit 2 */
#define RCC_CFG_PLLMULFCT_3 ((uint32_t)0x00080000U) /* Bit 3 */

#define RCC_CFG_PLLMULFCT3  ((uint32_t)0x00000000U) /* PLL input clock*3 */
#define RCC_CFG_PLLMULFCT4  ((uint32_t)0x00010000U) /* PLL input clock*4 */
#define RCC_CFG_PLLMULFCT5  ((uint32_t)0x00020000U) /* PLL input clock*5 */
#define RCC_CFG_PLLMULFCT6  ((uint32_t)0x00030000U) /* PLL input clock*6 */
#define RCC_CFG_PLLMULFCT7  ((uint32_t)0x00040000U) /* PLL input clock*7 */
#define RCC_CFG_PLLMULFCT8  ((uint32_t)0x00050000U) /* PLL input clock*8 */
#define RCC_CFG_PLLMULFCT9  ((uint32_t)0x00060000U) /* PLL input clock*9 */
#define RCC_CFG_PLLMULFCT10 ((uint32_t)0x00070000U) /* PLL input clock*10 */
#define RCC_CFG_PLLMULFCT11 ((uint32_t)0x00080000U) /* PLL input clock*11 */
#define RCC_CFG_PLLMULFCT12 ((uint32_t)0x00090000U) /* PLL input clock*12 */
#define RCC_CFG_PLLMULFCT13 ((uint32_t)0x000A0000U) /* PLL input clock*13 */
#define RCC_CFG_PLLMULFCT14 ((uint32_t)0x000B0000U) /* PLL input clock*14 */
#define RCC_CFG_PLLMULFCT15 ((uint32_t)0x000C0000U) /* PLL input clock*15 */
#define RCC_CFG_PLLMULFCT16 ((uint32_t)0x000D0000U) /* PLL input clock*16 */
#define RCC_CFG_PLLMULFCT17 ((uint32_t)0x000E0000U) /* PLL input clock*17 */
#define RCC_CFG_PLLMULFCT18 ((uint32_t)0x000F0000U) /* PLL input clock*18 */

/* PLLPRE configuration */
#define RCC_CFG_PLLPRE      ((uint32_t)0x00300000U) /* PLL prescaler */
#define RCC_CFG_PLLPRE_0    ((uint32_t)0x00100000U) /* Bit 0 */
#define RCC_CFG_PLLPRE_1    ((uint32_t)0x00200000U) /* Bit 1 */

#define RCC_CFG_PLLPREDIV1   ((uint32_t)0x00000000U)/* PLL clock is divided by 1 */
#define RCC_CFG_PLLPREDIV2   ((uint32_t)0x00100000U)/* PLL clock is divided by 2 */
#define RCC_CFG_PLLPREDIV3   ((uint32_t)0x00200000U)/* PLL clock is divided by 3 */
#define RCC_CFG_PLLPREDIV4   ((uint32_t)0x00300000U)/* PLL clock is divided by 4 */

/* PLLOUTDIV configuration */
#define RCC_CFG_PLLOUTDIV   ((uint32_t)0x00C00000U) /* PLL Out Clock Divid */
#define RCC_CFG_PLLOUTDIV_0 ((uint32_t)0x00400000U) /* Bit 0 */
#define RCC_CFG_PLLOUTDIV_1 ((uint32_t)0x00800000U) /* Bit 1 */

#define RCC_CFG_PLLOUTDIV1     ((uint32_t)0x00000000U) /* PLL Out clock is divided by 1 */
#define RCC_CFG_PLLOUTDIV2  ((uint32_t)0x00400000U) /* PLL Out clock is divided by 2 */
#define RCC_CFG_PLLOUTDIV3  ((uint32_t)0x00800000U) /* PLL Out clock is divided by 3 */
#define RCC_CFG_PLLOUTDIV4  ((uint32_t)0x00C00000U) /* PLL Out clock is divided by 4 */

/* PLLSRC configuration */
#define RCC_CFG_PLLSRC         ((uint32_t)0x01000000U) /* PLL entry clock source */

#define RCC_CFG_PLLSRC_HSI   ((uint32_t)0x00000000U) /* HSI clock selected as PLL entry clock source */
#define RCC_CFG_PLLSRC_HSE   ((uint32_t)0x01000000U) /* HSE clock selected as PLL entry clock source */

/* MCO configuration */
#define RCC_CFG_MCO      ((uint32_t)0x0E000000U) /* MCO[2:0] bits (Microcontroller Clock Output) */
#define RCC_CFG_MCO_0    ((uint32_t)0x02000000U) /* Bit 0 */
#define RCC_CFG_MCO_1    ((uint32_t)0x04000000U) /* Bit 1 */
#define RCC_CFG_MCO_2    ((uint32_t)0x08000000U) /* Bit 2 */

#define  RCC_CFG_MCO_NOCLK      ((uint32_t)0x00000000U) /* No clock */ 
#define  RCC_CFG_MCO_LSI        ((uint32_t)0x02000000U) /* LSI clock selected as MCO source */
#define  RCC_CFG_MCO_SYSCLK     ((uint32_t)0x04000000U) /* System clock selected as MCO source */ 
#define  RCC_CFG_MCO_HSI        ((uint32_t)0x06000000U) /* HSI clock selected as MCO source */
#define  RCC_CFG_MCO_HSE        ((uint32_t)0x08000000U) /* HSE clock selected as MCO source  */ 
#define  RCC_CFG_MCO_PLL        ((uint32_t)0x0A000000U) /* PLL clock divided selected as MCO source */

/* MCOPRE configuration */
#define RCC_CFG_MCOPRES    ((uint32_t)0xF0000000U)/* MCOPRE[3:0] bits ( PLL prescaler set and cleared by software to generate MCOPRE clock.) */
#define RCC_CFG_MCOPRES_0  ((uint32_t)0x10000000U) /* Bit 0 */
#define RCC_CFG_MCOPRES_1  ((uint32_t)0x20000000U) /* Bit 1 */
#define RCC_CFG_MCOPRES_2  ((uint32_t)0x40000000U) /* Bit 2 */
#define RCC_CFG_MCOPRES_3  ((uint32_t)0x80000000U) /* Bit 3 */

#define RCC_CFG_MCOPRES_PLLDIV2  ((uint32_t)0x20000000U) /* PLL clock is divided by 2 */
#define RCC_CFG_MCOPRES_PLLDIV3  ((uint32_t)0x30000000U) /* PLL clock is divided by 3 */
#define RCC_CFG_MCOPRES_PLLDIV4  ((uint32_t)0x40000000U) /* PLL clock is divided by 4 */
#define RCC_CFG_MCOPRES_PLLDIV5  ((uint32_t)0x50000000U) /* PLL clock is divided by 5 */
#define RCC_CFG_MCOPRES_PLLDIV6  ((uint32_t)0x60000000U) /* PLL clock is divided by 6 */
#define RCC_CFG_MCOPRES_PLLDIV7  ((uint32_t)0x70000000U) /* PLL clock is divided by 7 */
#define RCC_CFG_MCOPRES_PLLDIV8  ((uint32_t)0x80000000U) /* PLL clock is divided by 8 */
#define RCC_CFG_MCOPRES_PLLDIV9  ((uint32_t)0x90000000U) /* PLL clock is divided by 9 */
#define RCC_CFG_MCOPRES_PLLDIV10 ((uint32_t)0xA0000000U) /* PLL clock is divided by 10 */
#define RCC_CFG_MCOPRES_PLLDIV11 ((uint32_t)0xB0000000U) /* PLL clock is divided by 11 */
#define RCC_CFG_MCOPRES_PLLDIV12 ((uint32_t)0xC0000000U) /* PLL clock is divided by 12 */
#define RCC_CFG_MCOPRES_PLLDIV13 ((uint32_t)0xD0000000U) /* PLL clock is divided by 13 */
#define RCC_CFG_MCOPRES_PLLDIV14 ((uint32_t)0xE0000000U) /* PLL clock is divided by 14 */
#define RCC_CFG_MCOPRES_PLLDIV15 ((uint32_t)0xF0000000U) /* PLL clock is divided by 15 */

/** Bit definition for RCC_CLKINT register **/

#define RCC_CLKINT_LSIRDIF     ((uint32_t)0x00000001U) /* LSI Ready Interrupt Flag */
#define RCC_CLKINT_HSIRDIF     ((uint32_t)0x00000004U) /* HSI Ready Interrupt Flag */
#define RCC_CLKINT_HSERDIF     ((uint32_t)0x00000008U) /* HSE Ready Interrupt Flag */
#define RCC_CLKINT_PLLRDIF     ((uint32_t)0x00000010U) /* PLL Ready Interrupt Flag */
#define RCC_CLKINT_RAMPERRIF   ((uint32_t)0x00000020U) /* RAM Parity Error Interrupt Flag */
#define RCC_CLKINT_CLKSSIF     ((uint32_t)0x00000080U) /* HSE Clock Security System Interrupt Flag */

#define RCC_CLKINT_LSIRDIEN      ((uint32_t)0x00000100U) /* LSI Ready Interrupt Enable */
#define RCC_CLKINT_HSIRDIEN      ((uint32_t)0x00000400U) /* HSI Ready Interrupt Enable */
#define RCC_CLKINT_HSERDIEN      ((uint32_t)0x00000800U) /* HSE Ready Interrupt Enable */
#define RCC_CLKINT_PLLRDIEN      ((uint32_t)0x00001000U) /* PLL Ready Interrupt Enable */
#define RCC_CLKINT_RAMPERRIEN    ((uint32_t)0x00002000U) /* RAM Parity Error Interrupt Enable */
#define RCC_CLKINT_RAMPERRRSTEN  ((uint32_t)0x00004000U) /* RAM Parity Error Reset Enable */

#define RCC_CLKINT_LSIRDICLR   ((uint32_t)0x00010000U) /* LSI Ready Interrupt Clear */
#define RCC_CLKINT_HSIRDICLR   ((uint32_t)0x00040000U) /* HSI Ready Interrupt Clear */
#define RCC_CLKINT_HSERDICLR   ((uint32_t)0x00080000U) /* HSE Ready Interrupt Clear */
#define RCC_CLKINT_PLLRDICLR   ((uint32_t)0x00100000U) /* PLL Ready Interrupt Clear */
#define RCC_CLKINT_RAMPERRICLR ((uint32_t)0x00200000U) /* RAM Parity Error Interrupt Clear */
#define RCC_CLKINT_CLKSSICLR   ((uint32_t)0x00800000U) /* HSE Clock Security System Interrupt Clear */

/** Bit definition for RCC_APB2PRST register **/

#define RCC_APB2PRST_AFIORST   ((uint32_t)0x00000001U) /* Alternate Function I/O reset */
#define RCC_APB2PRST_IOPARST   ((uint32_t)0x00000004U) /* I/O port A clock reset */
#define RCC_APB2PRST_IOPBRST   ((uint32_t)0x00000008U) /* I/O port B clock reset */
#define RCC_APB2PRST_IOPCRST   ((uint32_t)0x00000010U) /* I/O port C clock reset */
#define RCC_APB2PRST_IOPDRST   ((uint32_t)0x00000020U) /* I/O port D clock reset */
#define RCC_APB2PRST_SPI1RST   ((uint32_t)0x00000200U) /* SPI 1 reset */
#define RCC_APB2PRST_SPI2RST   ((uint32_t)0x00000400U) /* SPI 2 reset */
#define RCC_APB2PRST_SPI3RST   ((uint32_t)0x00000800U) /* SPI 3 reset */
#define RCC_APB2PRST_TIM1RST   ((uint32_t)0x00001000U) /* Timer 1 reset */
#define RCC_APB2PRST_TIM2RST   ((uint32_t)0x00002000U) /* Timer 2 reset */
#define RCC_APB2PRST_UART1RST  ((uint32_t)0x00004000U) /* UART 1 reset */
#define RCC_APB2PRST_UART2RST  ((uint32_t)0x00008000U) /* UART 4 reset */
#define RCC_APB2PRST_TIM3RST   ((uint32_t)0x00010000U) /* Timer 3 reset */
#define RCC_APB2PRST_TIM4RST   ((uint32_t)0x00020000U) /* Timer 4 reset */
#define RCC_APB2PRST_TIM5RST   ((uint32_t)0x00040000U) /* Timer 5 reset */

/** Bit definition for RCC_APB1PRST register **/

#define RCC_APB1PRST_TIM6RST   ((uint32_t)0x00000010U) /* Timer 6 reset */
#define RCC_APB1PRST_BEEPRST   ((uint32_t)0x00000020U) /* Beeper reset */
#define RCC_APB1PRST_COMPRST   ((uint32_t)0x00000100U) /* COMP reset */
#define RCC_APB1PRST_LCDRST    ((uint32_t)0x00000400U) /* LCD reset */
#define RCC_APB1PRST_WWDGRST   ((uint32_t)0x00000800U) /* Window Watchdog reset */
#define RCC_APB1PRST_UART3RST  ((uint32_t)0x00040000U) /* UART 3 reset */
#define RCC_APB1PRST_UART4RST  ((uint32_t)0x00080000U) /* UART 4 reset */
#define RCC_APB1PRST_UART5RST  ((uint32_t)0x00100000U) /* UART 5 reset */
#define RCC_APB1PRST_I2C1RST   ((uint32_t)0x00200000U) /* I2C 1 reset */
#define RCC_APB1PRST_I2C2RST   ((uint32_t)0x00400000U) /* I2C 2 reset */
#define RCC_APB1PRST_CANRST    ((uint32_t)0x04000000U) /* CAN reset */
#define RCC_APB1PRST_DACRST    ((uint32_t)0x08000000U) /* DAC reset */
#define RCC_APB1PRST_PWRRST    ((uint32_t)0x10000000U) /* Power interface reset */

/** Bit definition for RCC_AHBPCLKEN register **/

#define RCC_AHBPCLKEN_DMAEN    ((uint32_t)0x00000001U) /* DMA clock enable */
#define RCC_AHBPCLKEN_SRAMEN   ((uint32_t)0x00000004U) /* SRAM interface clock enable */
#define RCC_AHBPCLKEN_FLITFEN  ((uint32_t)0x00000010U) /* FLITF clock enable */
#define RCC_AHBPCLKEN_CRCEN    ((uint32_t)0x00000040U) /* CRC clock enable */
#define RCC_AHBPCLKEN_SACEN    ((uint32_t)0x00000800U) /* SAC clock enable */
#define RCC_AHBPCLKEN_ADCEN    ((uint32_t)0x00001000U) /* ADC clock enable */

/** Bit definition for RCC_APB2PCLKEN register **/

#define RCC_APB2PCLKEN_AFIOEN   ((uint32_t)0x00000001U) /* Alternate Function I/O enable */
#define RCC_APB2PCLKEN_IOPAEN   ((uint32_t)0x00000004U) /* I/O port A clock enable */
#define RCC_APB2PCLKEN_IOPBEN   ((uint32_t)0x00000008U) /* I/O port B clock enable */
#define RCC_APB2PCLKEN_IOPCEN   ((uint32_t)0x00000010U) /* I/O port C clock enable */
#define RCC_APB2PCLKEN_IOPDEN   ((uint32_t)0x00000020U) /* I/O port D clock enable */
#define RCC_APB2PCLKEN_SPI1EN   ((uint32_t)0x00000200U) /* SPI 1 enable */
#define RCC_APB2PCLKEN_SPI2EN   ((uint32_t)0x00000400U) /* SPI 2 enable */
#define RCC_APB2PCLKEN_SPI3EN   ((uint32_t)0x00000800U) /* SPI 3 enable */
#define RCC_APB2PCLKEN_TIM1EN   ((uint32_t)0x00001000U) /* Timer 1 enable */
#define RCC_APB2PCLKEN_TIM2EN   ((uint32_t)0x00002000U) /* Timer 2 enable */
#define RCC_APB2PCLKEN_UART1EN  ((uint32_t)0x00004000U) /* UART 1 enable */
#define RCC_APB2PCLKEN_UART2EN  ((uint32_t)0x00008000U) /* UART 4 enable */
#define RCC_APB2PCLKEN_TIM3EN   ((uint32_t)0x00010000U) /* Timer 3 enable */
#define RCC_APB2PCLKEN_TIM4EN   ((uint32_t)0x00020000U) /* Timer 4 enable */
#define RCC_APB2PCLKEN_TIM5EN   ((uint32_t)0x00040000U) /* Timer 5 enable */

/** Bit definition for RCC_APB1PCLKEN register **/

#define RCC_APB1PCLKEN_TIM6EN      ((uint32_t)0x00000010U) /* Timer 6 enable */
#define RCC_APB1PCLKEN_BEEPEN      ((uint32_t)0x00000020U) /* Beeper enable */
#define RCC_APB1PCLKEN_COMPEN      ((uint32_t)0x00000100U) /* COMP enable */
#define RCC_APB1PCLKEN_COMPFILTEN  ((uint32_t)0x00000200U) /* COMP Filter enable */
#define RCC_APB1PCLKEN_LCDEN       ((uint32_t)0x00000400U) /* LCD enable */
#define RCC_APB1PCLKEN_WWDGEN      ((uint32_t)0x00000800U) /* Window Watchdog enable */
#define RCC_APB1PCLKEN_UART3EN     ((uint32_t)0x00040000U) /* UART 3 enable */
#define RCC_APB1PCLKEN_UART4EN     ((uint32_t)0x00080000U) /* UART 4 enable */
#define RCC_APB1PCLKEN_UART5EN     ((uint32_t)0x00100000U) /* UART 5 enable */
#define RCC_APB1PCLKEN_I2C1EN      ((uint32_t)0x00200000U) /* I2C 1 enable */
#define RCC_APB1PCLKEN_I2C2EN      ((uint32_t)0x00400000U) /* I2C 2 enable */
#define RCC_APB1PCLKEN_CANEN       ((uint32_t)0x04000000U) /* CAN enable */
#define RCC_APB1PCLKEN_DACEN       ((uint32_t)0x08000000U) /* DAC enable */
#define RCC_APB1PCLKEN_PWREN       ((uint32_t)0x10000000U) /* Power interface enable */

/** Bit definition for RCC_LSCTRL register **/

#define RCC_LSCTRL_LSIEN    ((uint32_t)0x00000001U) /* Internal Low Speed oscillator enable */
#define RCC_LSCTRL_LSIRD    ((uint32_t)0x00000002U) /* Internal Low Speed oscillator Ready */
#define RCC_LSCTRL_LSITRIM  ((uint32_t)0x0000007CU) /* Internal Low Speed oscillator trimming */

#define RCC_LSCTRL_RTCSEL   ((uint32_t)0x00001800U) /* RTCSEL[1:0] bits (RTC clock source selection) */
#define RCC_LSCTRL_RTCSEL_0 ((uint32_t)0x00000800U) /* Bit 0 */
#define RCC_LSCTRL_RTCSEL_1 ((uint32_t)0x00001000U) /* Bit 1 */

/** RTC congiguration **/
#define RCC_LSCTRL_RTCSEL_NOCLOCK ((uint32_t)0x00000000U) /* No clock */
#define RCC_LSCTRL_RTCSEL_LSI     ((uint32_t)0x00000800U) /* LSI oscillator clock used as RTC clock */
#define RCC_LSCTRL_RTCSEL_HSE     ((uint32_t)0x00001000U) /* HSE oscillator clock divided by 128 used as RTC clock */
#define RCC_LSCTRL_RTCSEL_HSI     ((uint32_t)0x00001800U) /* HSI oscillator clock divided by 128 used as RTC clock */

#define RCC_LSCTRL_RTCEN          ((uint32_t)0x00002000U) /* RTC clock enable */
#define RCC_LSCTRL_RTCRST         ((uint32_t)0x00004000U) /* RTC clock reset  */

/** Bit definition for RCC_CTRLSTS register **/

#define RCC_CTRLSTS_RMRSTF       ((uint32_t)0x00000001U) /* Remove all reset flag */
#define RCC_CTRLSTS_RAMPERRRSTF  ((uint32_t)0x00000002U) /* RAM parity error reset flag */
#define RCC_CTRLSTS_MMURSTF      ((uint32_t)0x00000004U) /* MMU reset flag */
#define RCC_CTRLSTS_PINRSTF      ((uint32_t)0x00000008U) /* PIN reset flag */
#define RCC_CTRLSTS_PORRSTF      ((uint32_t)0x00000010U) /* POR reset flag */
#define RCC_CTRLSTS_SFTRSTF      ((uint32_t)0x00000020U) /* Software Reset flag */
#define RCC_CTRLSTS_IWDGRSTF     ((uint32_t)0x00000040U) /* Independent Watchdog reset flag */
#define RCC_CTRLSTS_WWDGRSTF     ((uint32_t)0x00000080U) /* Window watchdog reset flag */
#define RCC_CTRLSTS_LPWRRSTF     ((uint32_t)0x00000100U) /* Low-Power reset flag */
#define RCC_CTRLSTS_EMCGBNRSTF   ((uint32_t)0x00000200U) /* EMCGBN reset flag */
#define RCC_CTRLSTS_EMCGBRSTF    ((uint32_t)0x00000400U) /* EMCGB reset flag */
#define RCC_CTRLSTS_LKUPRSTF     ((uint32_t)0x00000800U) /* M0 core lock up reset flag */
#define RCC_CTRLSTS_LVRRSTF      ((uint32_t)0x20000000U) /* LVR reset flag */

/** Bit definition for RCC_AHBPRST register **/

#define RCC_AHBPRST_SACRST    ((uint32_t)0x00000800U) /* SAC clock reset */
#define RCC_AHBPRST_ADCRST    ((uint32_t)0x00001000U) /* ADC clock reset */

/** Bit definition for RCC_CFG2 register **/
/** ADCHPRE configuration **/
#define RCC_CFG2_ADCHPRES   ((uint32_t)0x0000000FU) /* ADCHPRE[3:0] bits */
#define RCC_CFG2_ADCHPRES_0 ((uint32_t)0x00000001U) /* Bit 0 */
#define RCC_CFG2_ADCHPRES_1 ((uint32_t)0x00000002U) /* Bit 1 */
#define RCC_CFG2_ADCHPRES_2 ((uint32_t)0x00000004U) /* Bit 2 */
#define RCC_CFG2_ADCHPRES_3 ((uint32_t)0x00000008U) /* Bit 3 */

#define RCC_CFG2_ADCHPRES_DIV1   ((uint32_t)0x00000000U) /* HCLK clock divided by 1 */
#define RCC_CFG2_ADCHPRES_DIV2   ((uint32_t)0x00000001U) /* HCLK clock divided by 2 */
#define RCC_CFG2_ADCHPRES_DIV4   ((uint32_t)0x00000002U) /* HCLK clock divided by 4 */
#define RCC_CFG2_ADCHPRES_DIV6   ((uint32_t)0x00000003U) /* HCLK clock divided by 6 */
#define RCC_CFG2_ADCHPRES_DIV8   ((uint32_t)0x00000004U) /* HCLK clock divided by 8 */
#define RCC_CFG2_ADCHPRES_DIV10  ((uint32_t)0x00000005U) /* HCLK clock divided by 10 */
#define RCC_CFG2_ADCHPRES_DIV12  ((uint32_t)0x00000006U) /* HCLK clock divided by 12 */
#define RCC_CFG2_ADCHPRES_DIV16  ((uint32_t)0x00000007U) /* HCLK clock divided by 16 */
#define RCC_CFG2_ADCHPRES_DIV32  ((uint32_t)0x00000008U) /* HCLK clock divided by 32 */
#define RCC_CFG2_ADCHPRES_OTHERS ((uint32_t)0x00000008U) /* HCLK clock divided by 32 */

/** ADCPLLPRES configuration **/
#define RCC_CFG2_ADCPLLPRES   ((uint32_t)0x000001F0U) /* ADCPLLPRES[4:0] bits */
#define RCC_CFG2_ADCPLLPRES_0 ((uint32_t)0x00000010U) /* Bit 0 */
#define RCC_CFG2_ADCPLLPRES_1 ((uint32_t)0x00000020U) /* Bit 1 */
#define RCC_CFG2_ADCPLLPRES_2 ((uint32_t)0x00000040U) /* Bit 2 */
#define RCC_CFG2_ADCPLLPRES_3 ((uint32_t)0x00000080U) /* Bit 3 */
#define RCC_CFG2_ADCPLLPRES_4 ((uint32_t)0x00000100U) /* Bit 4 */

#define RCC_CFG2_ADCPLLCLK_DISABLE  ((uint32_t)0xFFFFFEFFU) /* ADC PLL clock Disable */
#define RCC_CFG2_ADCPLLPRES_DIV1    ((uint32_t)0x00000100U) /* PLL clock divided by 1 */
#define RCC_CFG2_ADCPLLPRES_DIV2    ((uint32_t)0x00000110U) /* PLL clock divided by 2 */
#define RCC_CFG2_ADCPLLPRES_DIV4    ((uint32_t)0x00000120U) /* PLL clock divided by 4 */
#define RCC_CFG2_ADCPLLPRES_DIV6    ((uint32_t)0x00000130U) /* PLL clock divided by 6 */
#define RCC_CFG2_ADCPLLPRES_DIV8    ((uint32_t)0x00000140U) /* PLL clock divided by 8 */
#define RCC_CFG2_ADCPLLPRES_DIV10   ((uint32_t)0x00000150U) /* PLL clock divided by 10 */
#define RCC_CFG2_ADCPLLPRES_DIV12   ((uint32_t)0x00000160U) /* PLL clock divided by 12 */
#define RCC_CFG2_ADCPLLPRES_DIV16   ((uint32_t)0x00000170U) /* PLL clock divided by 16 */
#define RCC_CFG2_ADCPLLPRES_DIV32   ((uint32_t)0x00000180U) /* PLL clock divided by 32 */
#define RCC_CFG2_ADCPLLPRES_DIV64   ((uint32_t)0x00000190U) /* PLL clock divided by 64 */
#define RCC_CFG2_ADCPLLPRES_DIV128  ((uint32_t)0x000001A0U) /* PLL clock divided by 128 */
#define RCC_CFG2_ADCPLLPRES_DIV256  ((uint32_t)0x000001B0U) /* PLL clock divided by 256 */
#define RCC_CFG2_ADCPLLPRES_DIV256N ((uint32_t)0x000001C0U) /* PLL clock divided by 256 */


/** ADC1MSEL configuration **/
#define RCC_CFG2_ADC1MSEL     ((uint32_t)0x00000400U) /* ADC1M clock source select */

#define RCC_CFG2_ADC1MSEL_HSI ((uint32_t)0x00000000U) /* HSI clock selected as ADC1M input clock */
#define RCC_CFG2_ADC1MSEL_HSE ((uint32_t)0x00000400U) /* HSE clock selected as ADC1M input clock */

/** ADC1MPRE configuration **/
#define RCC_CFG2_ADC1MPRES   ((uint32_t)0x0000F800U) /* ADC1MPRE[4:0] bits */
#define RCC_CFG2_ADC1MPRES_0 ((uint32_t)0x00000800U) /* Bit 0 */
#define RCC_CFG2_ADC1MPRES_1 ((uint32_t)0x00001000U) /* Bit 1 */
#define RCC_CFG2_ADC1MPRES_2 ((uint32_t)0x00002000U) /* Bit 2 */
#define RCC_CFG2_ADC1MPRES_3 ((uint32_t)0x00004000U) /* Bit 3 */
#define RCC_CFG2_ADC1MPRES_4 ((uint32_t)0x00008000U) /* Bit 4 */

#define RCC_CFG2_ADC1MPRES_DIV1  ((uint32_t)0x00000000U) /* ADC1M source clock is divided by 1 */
#define RCC_CFG2_ADC1MPRES_DIV2  ((uint32_t)0x00000800U) /* ADC1M source clock is divided by 2 */
#define RCC_CFG2_ADC1MPRES_DIV3  ((uint32_t)0x00001000U) /* ADC1M source clock is divided by 3 */
#define RCC_CFG2_ADC1MPRES_DIV4  ((uint32_t)0x00001800U) /* ADC1M source clock is divided by 4 */
#define RCC_CFG2_ADC1MPRES_DIV5  ((uint32_t)0x00002000U) /* ADC1M source clock is divided by 5 */
#define RCC_CFG2_ADC1MPRES_DIV6  ((uint32_t)0x00002800U) /* ADC1M source clock is divided by 6 */
#define RCC_CFG2_ADC1MPRES_DIV7  ((uint32_t)0x00003000U) /* ADC1M source clock is divided by 7 */
#define RCC_CFG2_ADC1MPRES_DIV8  ((uint32_t)0x00003800U) /* ADC1M source clock is divided by 8 */
#define RCC_CFG2_ADC1MPRES_DIV9  ((uint32_t)0x00004000U) /* ADC1M source clock is divided by 9 */
#define RCC_CFG2_ADC1MPRES_DIV10 ((uint32_t)0x00004800U) /* ADC1M source clock is divided by 10 */
#define RCC_CFG2_ADC1MPRES_DIV11 ((uint32_t)0x00005000U) /* ADC1M source clock is divided by 11 */
#define RCC_CFG2_ADC1MPRES_DIV12 ((uint32_t)0x00005800U) /* ADC1M source clock is divided by 12 */
#define RCC_CFG2_ADC1MPRES_DIV13 ((uint32_t)0x00006000U) /* ADC1M source clock is divided by 13 */
#define RCC_CFG2_ADC1MPRES_DIV14 ((uint32_t)0x00006800U) /* ADC1M source clock is divided by 14 */
#define RCC_CFG2_ADC1MPRES_DIV15 ((uint32_t)0x00007000U) /* ADC1M source clock is divided by 15 */
#define RCC_CFG2_ADC1MPRES_DIV16 ((uint32_t)0x00007800U) /* ADC1M source clock is divided by 16 */
#define RCC_CFG2_ADC1MPRES_DIV17 ((uint32_t)0x00008000U) /* ADC1M source clock is divided by 17 */
#define RCC_CFG2_ADC1MPRES_DIV18 ((uint32_t)0x00008800U) /* ADC1M source clock is divided by 18 */
#define RCC_CFG2_ADC1MPRES_DIV19 ((uint32_t)0x00009000U) /* ADC1M source clock is divided by 19 */
#define RCC_CFG2_ADC1MPRES_DIV20 ((uint32_t)0x00009800U) /* ADC1M source clock is divided by 20 */
#define RCC_CFG2_ADC1MPRES_DIV21 ((uint32_t)0x0000A000U) /* ADC1M source clock is divided by 21 */
#define RCC_CFG2_ADC1MPRES_DIV22 ((uint32_t)0x0000A800U) /* ADC1M source clock is divided by 22 */
#define RCC_CFG2_ADC1MPRES_DIV23 ((uint32_t)0x0000B000U) /* ADC1M source clock is divided by 23 */
#define RCC_CFG2_ADC1MPRES_DIV24 ((uint32_t)0x0000B800U) /* ADC1M source clock is divided by 24 */
#define RCC_CFG2_ADC1MPRES_DIV25 ((uint32_t)0x0000C000U) /* ADC1M source clock is divided by 25 */
#define RCC_CFG2_ADC1MPRES_DIV26 ((uint32_t)0x0000C800U) /* ADC1M source clock is divided by 26 */
#define RCC_CFG2_ADC1MPRES_DIV27 ((uint32_t)0x0000D000U) /* ADC1M source clock is divided by 27 */
#define RCC_CFG2_ADC1MPRES_DIV28 ((uint32_t)0x0000D800U) /* ADC1M source clock is divided by 28 */
#define RCC_CFG2_ADC1MPRES_DIV29 ((uint32_t)0x0000E000U) /* ADC1M source clock is divided by 29 */
#define RCC_CFG2_ADC1MPRES_DIV30 ((uint32_t)0x0000E800U) /* ADC1M source clock is divided by 30 */
#define RCC_CFG2_ADC1MPRES_DIV31 ((uint32_t)0x0000F000U) /* ADC1M source clock is divided by 31 */
#define RCC_CFG2_ADC1MPRES_DIV32 ((uint32_t)0x0000F800U) /* ADC1M source clock is divided by 32 */


/** ADCCLKSEL configuration **/
#define RCC_CFG2_ADCCLKSEL   ((uint32_t)0x06000000U) /* ADCCLKSEL[1:0] bits */

#define RCC_CFG2_ADCCLKSEL_0   ((uint32_t)0x02000000U) /* Bit 0 */
#define RCC_CFG2_ADCCLKSEL_1   ((uint32_t)0x04000000U) /* Bit 1 */

#define RCC_CFG2_ADCCLKSEL_HSI24M   ((uint32_t)0x00000000U) /* HSI 24M clock selected as ADC clock */
#define RCC_CFG2_ADCCLKSEL_PLL      ((uint32_t)0x02000000U) /* PLL clock selected as ADC clock */
#define RCC_CFG2_ADCCLKSEL_HCLK     ((uint32_t)0x04000000U) /* HCLK clock selected as ADC clock */


/** LCDCLKSEL configuration **/
#define RCC_CFG2_LCDCLKSEL   ((uint32_t)0x08000000U) /* LCDCLKSEL[1:0] bits */

#define RCC_CFG2_LCDCLKSEL_HSI   ((uint32_t)0x00000000U) /* HSI clock divided 8 selected as LCD clock */
#define RCC_CFG2_LCDCLKSEL_HSE   ((uint32_t)0x08000000U) /* HSE clock divided 16 selected as LCD clock */

/** TIM6CLKSEL configuration **/
#define RCC_CFG2_TIM6CLKSEL   ((uint32_t)0x40000000U) /* TIM6CLKSEL bits */

#define RCC_CFG2_TIM6CLKSEL_PCLK  ((uint32_t)0x00000000U) /* PCLK clock selected as TIM6 clock */
#define RCC_CFG2_TIM6CLKSEL_LSI   ((uint32_t)0x40000000U) /* LSI clock selected as TIM6 clock */

/** TIM1CLKSEL configuration **/
#define RCC_CFG2_TIM1CLKSEL         ((uint32_t)0x80000000U) /* Timer1 clock source select */

#define RCC_CFG2_TIM1CLKSEL_PCLK    ((uint32_t)0x00000000U) /* Timer1 clock selected as PCLK */
#define RCC_CFG2_TIM1CLKSEL_SYSCLK  ((uint32_t)0x80000000U) /* Timer1 clock selected as sysclk clock */

/** Bit definition for RCC_CFG3 register **/

#define RCC_CFG3_GCLKEN        ((uint32_t)0x00000001U) /* LED GCLK clock enable */
/** GCLKSEL configuration **/
#define RCC_CFG3_GCLKSEL       ((uint32_t)0x00000002U) /* LED GCLK source select */

#define RCC_CFG3_GCLKSEL_HSI   ((uint32_t)0x00000000U) /* HSI clock selected as LED GCLK clock */
#define RCC_CFG3_GCLKSEL_HSE   ((uint32_t)0x00000002U) /* HSE clock selected as LED GCLK clock  */

#define RCC_CFG3_GCLKDONEF       ((uint32_t)0x00000004U) /* LED GCLK output lasts one cycle flag  */
#define RCC_CFG3_GCLKDMAEN       ((uint32_t)0x00000008U) /* LED GCLK dma req output enable */
/** GCLKPRES configuration **/
#define RCC_CFG3_GCLKPRES      ((uint32_t)0x00000F00U) /* LED GCLK prescaler */
#define RCC_CFG3_GCLKPRES_0    ((uint32_t)0x00000100U) /* Bit 0 */
#define RCC_CFG3_GCLKPRES_1    ((uint32_t)0x00000200U) /* Bit 1 */
#define RCC_CFG3_GCLKPRES_2    ((uint32_t)0x00000400U) /* Bit 2 */
#define RCC_CFG3_GCLKPRES_3    ((uint32_t)0x00000800U) /* Bit 3 */

#define RCC_CFG3_GCLKPRES_DISABLE  ((uint32_t)0x00000000U) /* LED source clock is disable */
#define RCC_CFG3_GCLKPRES_DIV32    ((uint32_t)0x00000800U) /* LED source clock is divided by 32 */
#define RCC_CFG3_GCLKPRES_DIV40    ((uint32_t)0x00000900U) /* LED source clock is divided by 40 */
#define RCC_CFG3_GCLKPRES_DIV50    ((uint32_t)0x00000A00U) /* LED source clock is divided by 50 */
#define RCC_CFG3_GCLKPRES_DIV64    ((uint32_t)0x00000B00U) /* LED source clock is divided by 64 */
#define RCC_CFG3_GCLKPRES_DIV80    ((uint32_t)0x00000C00U) /* LED source clock is divided by 80 */
#define RCC_CFG3_GCLKPRES_DIV160   ((uint32_t)0x00000D00U) /* LED source clock is divided by 160 */

#define RCC_CFG3_GCLKMNUM        ((uint32_t)0x00FF0000U) /* Number of low level cycles in one time period */
#define RCC_CFG3_GCLKNNUM        ((uint32_t)0xFF000000U) /* Number of clock cycles in one time period */

/**  Bit definition for RCC_EMCCTRL register  **/

#define RCC_EMCCTRL_GBNDET0EN ((uint32_t)0x00000010U) /* GBN0 Detect Enable */
#define RCC_EMCCTRL_GBNDET1EN ((uint32_t)0x00000020U) /* GBN1 Detect Enable */
#define RCC_EMCCTRL_GBNDET2EN ((uint32_t)0x00000040U) /* GBN2 Detect Enable */
#define RCC_EMCCTRL_GBNDET3EN ((uint32_t)0x00000080U) /* GBN3 Detect Enable */
#define RCC_EMCCTRL_GBDET0EN  ((uint32_t)0x00000100U) /* GB0 Detect Enable */
#define RCC_EMCCTRL_GBDET1EN  ((uint32_t)0x00000200U) /* GB1 Detect Enable */
#define RCC_EMCCTRL_GBDET2EN  ((uint32_t)0x00000400U) /* GB2 Detect Enable */
#define RCC_EMCCTRL_GBDET3EN  ((uint32_t)0x00000800U) /* GB3 Detect Enable */

#define RCC_EMCCTRL_GBN0RST   ((uint32_t)0x00010000U) /* GBN0 Reset */
#define RCC_EMCCTRL_GBN1RST   ((uint32_t)0x00020000U) /* GBN1 Reset */
#define RCC_EMCCTRL_GBN2RST   ((uint32_t)0x00040000U) /* GBN2 Reset */
#define RCC_EMCCTRL_GBN3RST   ((uint32_t)0x00080000U) /* GBN3 Reset */
#define RCC_EMCCTRL_GB0RST    ((uint32_t)0x00100000U) /* GB0 Reset */
#define RCC_EMCCTRL_GB1RST    ((uint32_t)0x00200000U) /* GB1 Reset */
#define RCC_EMCCTRL_GB2RST    ((uint32_t)0x00400000U) /* GB2 Reset */
#define RCC_EMCCTRL_GB3RST    ((uint32_t)0x00800000U) /* GB3 Reset */


/*** General Purpose and Alternate Function I/O ***/

/** Bit definition for GPIO_PMODE register **/
#define GPIO_PMODE0_Pos            (0)                                   
#define GPIO_PMODE0_Msk            (0x3 << GPIO_PMODE0_Pos)         /* 0x00000003 */ 
#define GPIO_PMODE0                        GPIO_PMODE0_Msk          /* 0x00000003 */
#define GPIO_PMODE0_0              (0x0 << GPIO_PMODE0_Pos)         /* 0x00000000 */
#define GPIO_PMODE0_1              (0x1 << GPIO_PMODE0_Pos)         /* 0x00000001 */
#define GPIO_PMODE0_2              (0x2 << GPIO_PMODE0_Pos)         /* 0x00000002 */
#define GPIO_PMODE0_3              (0x3 << GPIO_PMODE0_Pos)         /* 0x00000003 */

#define GPIO_PMODE1_Pos            (2)                                   
#define GPIO_PMODE1_Msk            (0x3 << GPIO_PMODE1_Pos)         /* 0x0000000C */
#define GPIO_PMODE1                        GPIO_PMODE1_Msk          /* 0x0000000C */
#define GPIO_PMODE1_0              (0x0 << GPIO_PMODE1_Pos)         /* 0x00000000 */
#define GPIO_PMODE1_1              (0x1 << GPIO_PMODE1_Pos)         /* 0x00000004 */
#define GPIO_PMODE1_2              (0x2 << GPIO_PMODE1_Pos)         /* 0x00000008 */
#define GPIO_PMODE1_3              (0x3 << GPIO_PMODE1_Pos)         /* 0x0000000C */

#define GPIO_PMODE2_Pos            (4)                                   
#define GPIO_PMODE2_Msk            (0x3 << GPIO_PMODE2_Pos)         /* 0x00000030 */               
#define GPIO_PMODE2                        GPIO_PMODE2_Msk          /* 0x00000030 */
#define GPIO_PMODE2_0              (0x0 << GPIO_PMODE2_Pos)         /* 0x00000000 */
#define GPIO_PMODE2_1              (0x1 << GPIO_PMODE2_Pos)         /* 0x00000010 */
#define GPIO_PMODE2_2              (0x2 << GPIO_PMODE2_Pos)         /* 0x00000020 */
#define GPIO_PMODE2_3              (0x3 << GPIO_PMODE2_Pos)         /* 0x00000030 */

#define GPIO_PMODE3_Pos            (6)                                   
#define GPIO_PMODE3_Msk            (0x3 << GPIO_PMODE3_Pos)         /* 0x000000C0 */
#define GPIO_PMODE3                        GPIO_PMODE3_Msk          /* 0x000000C0 */
#define GPIO_PMODE3_0              (0x0 << GPIO_PMODE3_Pos)         /* 0x00000000 */
#define GPIO_PMODE3_1              (0x1 << GPIO_PMODE3_Pos)         /* 0x00000040 */
#define GPIO_PMODE3_2              (0x2 << GPIO_PMODE3_Pos)         /* 0x00000080 */
#define GPIO_PMODE3_3              (0x3 << GPIO_PMODE3_Pos)         /* 0x000000C0 */

#define GPIO_PMODE4_Pos            (8)                                   
#define GPIO_PMODE4_Msk            (0x3 << GPIO_PMODE4_Pos)         /* 0x00000300 */ 
#define GPIO_PMODE4                        GPIO_PMODE4_Msk          /* 0x00000300 */
#define GPIO_PMODE4_0              (0x0 << GPIO_PMODE4_Pos)         /* 0x00000000 */
#define GPIO_PMODE4_1              (0x1 << GPIO_PMODE4_Pos)         /* 0x00000100 */
#define GPIO_PMODE4_2              (0x2 << GPIO_PMODE4_Pos)         /* 0x00000100 */
#define GPIO_PMODE4_3              (0x3 << GPIO_PMODE4_Pos)         /* 0x00000300 */

#define GPIO_PMODE5_Pos            (10)                                   
#define GPIO_PMODE5_Msk            (0x3 << GPIO_PMODE5_Pos)         /* 0x00000C00 */
#define GPIO_PMODE5                        GPIO_PMODE5_Msk          /* 0x00000C00 */
#define GPIO_PMODE5_0              (0x0 << GPIO_PMODE5_Pos)         /* 0x00000000 */
#define GPIO_PMODE5_1              (0x1 << GPIO_PMODE5_Pos)         /* 0x00000400 */
#define GPIO_PMODE5_2              (0x2 << GPIO_PMODE5_Pos)         /* 0x00000800 */
#define GPIO_PMODE5_3              (0x3 << GPIO_PMODE5_Pos)         /* 0x00000C00 */

#define GPIO_PMODE6_Pos            (12)                                   
#define GPIO_PMODE6_Msk            (0x3 << GPIO_PMODE6_Pos)         /* 0x00003000 */      
#define GPIO_PMODE6                        GPIO_PMODE6_Msk          /* 0x00003000 */
#define GPIO_PMODE6_0              (0x0 << GPIO_PMODE6_Pos)         /* 0x00000000 */
#define GPIO_PMODE6_1              (0x1 << GPIO_PMODE6_Pos)         /* 0x00001000 */
#define GPIO_PMODE6_2              (0x2 << GPIO_PMODE6_Pos)         /* 0x00002000 */
#define GPIO_PMODE6_3              (0x3 << GPIO_PMODE6_Pos)         /* 0x00003000 */

#define GPIO_PMODE7_Pos            (14)                                   
#define GPIO_PMODE7_Msk            (0x3 << GPIO_PMODE7_Pos)         /* 0x0000C000 */
#define GPIO_PMODE7                        GPIO_PMODE7_Msk          /* 0x0000C000 */
#define GPIO_PMODE7_0              (0x0 << GPIO_PMODE7_Pos)         /* 0x00000000 */
#define GPIO_PMODE7_1              (0x1 << GPIO_PMODE7_Pos)         /* 0x00004000 */
#define GPIO_PMODE7_2              (0x2 << GPIO_PMODE7_Pos)         /* 0x00008000 */
#define GPIO_PMODE7_3              (0x3 << GPIO_PMODE7_Pos)         /* 0x0000C000 */

#define GPIO_PMODE8_Pos            (16)                                   
#define GPIO_PMODE8_Msk            (0x3 << GPIO_PMODE8_Pos)         /* 0x00030000 */
#define GPIO_PMODE8                        GPIO_PMODE8_Msk          /* 0x00030000 */
#define GPIO_PMODE8_0              (0x0 << GPIO_PMODE8_Pos)         /* 0x00000000 */
#define GPIO_PMODE8_1              (0x1 << GPIO_PMODE8_Pos)         /* 0x00010000 */
#define GPIO_PMODE8_2              (0x2 << GPIO_PMODE8_Pos)         /* 0x00020000 */
#define GPIO_PMODE8_3              (0x3 << GPIO_PMODE8_Pos)         /* 0x00030000 */

#define GPIO_PMODE9_Pos            (18)                                   
#define GPIO_PMODE9_Msk            (0x3 << GPIO_PMODE9_Pos)         /* 0x000C0000 */
#define GPIO_PMODE9                        GPIO_PMODE9_Msk          /* 0x000C0000 */
#define GPIO_PMODE9_0              (0x0 << GPIO_PMODE9_Pos)         /* 0x00000000 */
#define GPIO_PMODE9_1              (0x1 << GPIO_PMODE9_Pos)         /* 0x00040000 */
#define GPIO_PMODE9_2              (0x2 << GPIO_PMODE9_Pos)         /* 0x00080000 */
#define GPIO_PMODE9_3              (0x3 << GPIO_PMODE9_Pos)         /* 0x000C0000 */

#define GPIO_PMODE10_Pos           (20)                                   
#define GPIO_PMODE10_Msk           (0x3 << GPIO_PMODE10_Pos)         /* 0x00300000 */ 
#define GPIO_PMODE10                       GPIO_PMODE10_Msk          /* 0x00300000 */
#define GPIO_PMODE10_0             (0x0 << GPIO_PMODE10_Pos)         /* 0x00000000 */
#define GPIO_PMODE10_1             (0x1 << GPIO_PMODE10_Pos)         /* 0x00100000 */
#define GPIO_PMODE10_2             (0x2 << GPIO_PMODE10_Pos)         /* 0x00200000 */
#define GPIO_PMODE10_3             (0x3 << GPIO_PMODE10_Pos)         /* 0x00300000 */

#define GPIO_PMODE11_Pos           (22)                                   
#define GPIO_PMODE11_Msk           (0x3 << GPIO_PMODE11_Pos)         /* 0x00C00000 */ 
#define GPIO_PMODE11                       GPIO_PMODE11_Msk          /* 0x00C00000 */
#define GPIO_PMODE11_0             (0x0 << GPIO_PMODE11_Pos)         /* 0x00000000 */
#define GPIO_PMODE11_1             (0x1 << GPIO_PMODE11_Pos)         /* 0x00400000 */
#define GPIO_PMODE11_2             (0x2 << GPIO_PMODE11_Pos)         /* 0x00800000 */
#define GPIO_PMODE11_3             (0x3 << GPIO_PMODE11_Pos)         /* 0x00C00000 */

#define GPIO_PMODE12_Pos           (24)                                   
#define GPIO_PMODE12_Msk           (0x3 << GPIO_PMODE12_Pos)         /* 0x03000000 */
#define GPIO_PMODE12                       GPIO_PMODE12_Msk          /* 0x03000000 */
#define GPIO_PMODE12_0             (0x0 << GPIO_PMODE12_Pos)         /* 0x00000000 */
#define GPIO_PMODE12_1             (0x1 << GPIO_PMODE12_Pos)         /* 0x01000000 */
#define GPIO_PMODE12_2             (0x2 << GPIO_PMODE12_Pos)         /* 0x02000000 */
#define GPIO_PMODE12_3             (0x3 << GPIO_PMODE12_Pos)         /* 0x03000000 */

#define GPIO_PMODE13_Pos           (26)                                   
#define GPIO_PMODE13_Msk           (0x3 << GPIO_PMODE13_Pos)         /* 0x0C000000 */
#define GPIO_PMODE13                       GPIO_PMODE13_Msk          /* 0x0C000000 */
#define GPIO_PMODE13_0             (0x0 << GPIO_PMODE13_Pos)         /* 0x00000000 */
#define GPIO_PMODE13_1             (0x1 << GPIO_PMODE13_Pos)         /* 0x04000000 */
#define GPIO_PMODE13_2             (0x2 << GPIO_PMODE13_Pos)         /* 0x08000000 */
#define GPIO_PMODE13_3             (0x3 << GPIO_PMODE13_Pos)         /* 0x0C000000 */

#define GPIO_PMODE14_Pos           (28)                                   
#define GPIO_PMODE14_Msk           (0x3 << GPIO_PMODE14_Pos)         /* 0x30000000 */
#define GPIO_PMODE14                       GPIO_PMODE14_Msk          /* 0x30000000 */
#define GPIO_PMODE14_0             (0x0 << GPIO_PMODE14_Pos)         /* 0x00000000 */
#define GPIO_PMODE14_1             (0x1 << GPIO_PMODE14_Pos)         /* 0x10000000 */
#define GPIO_PMODE14_2             (0x2 << GPIO_PMODE14_Pos)         /* 0x20000000 */
#define GPIO_PMODE14_3             (0x3 << GPIO_PMODE14_Pos)         /* 0x30000000 */

#define GPIO_PMODE15_Pos           (30)                                   
#define GPIO_PMODE15_Msk           (0x3 << GPIO_PMODE15_Pos)         /* 0xC0000000 */
#define GPIO_PMODE15                       GPIO_PMODE15_Msk          /* 0xC0000000 */
#define GPIO_PMODE15_0             (0x0 << GPIO_PMODE15_Pos)         /* 0x00000000 */
#define GPIO_PMODE15_1             (0x1 << GPIO_PMODE15_Pos)         /* 0x40000000 */
#define GPIO_PMODE15_2             (0x2 << GPIO_PMODE15_Pos)         /* 0x80000000 */
#define GPIO_PMODE15_3             (0x3 << GPIO_PMODE15_Pos)         /* 0xC0000000 */

/** Bit definition for GPIO_POTYPE register **/
#define GPIO_POTYPE_POT0           ((uint16_t)0x0001U) 
#define GPIO_POTYPE_POT1           ((uint16_t)0x0002U) 
#define GPIO_POTYPE_POT2           ((uint16_t)0x0004U) 
#define GPIO_POTYPE_POT3           ((uint16_t)0x0008U) 
#define GPIO_POTYPE_POT4           ((uint16_t)0x0010U) 
#define GPIO_POTYPE_POT5           ((uint16_t)0x0020U) 
#define GPIO_POTYPE_POT6           ((uint16_t)0x0040U) 
#define GPIO_POTYPE_POT7           ((uint16_t)0x0080U) 
#define GPIO_POTYPE_POT8           ((uint16_t)0x0100U) 
#define GPIO_POTYPE_POT9           ((uint16_t)0x0200U) 
#define GPIO_POTYPE_POT10          ((uint16_t)0x0400U) 
#define GPIO_POTYPE_POT11          ((uint16_t)0x0800U) 
#define GPIO_POTYPE_POT12          ((uint16_t)0x1000U) 
#define GPIO_POTYPE_POT13          ((uint16_t)0x2000U) 
#define GPIO_POTYPE_POT14          ((uint16_t)0x4000U) 
#define GPIO_POTYPE_POT15          ((uint16_t)0x8000U) 

/** Bit definition for GPIO_SR register **/
#define GPIO_SR_SR0                ((uint16_t)0x0001U) /* Port x Slew Rate bit 0  */
#define GPIO_SR_SR1                ((uint16_t)0x0002U) /* Port x Slew Rate bit 1  */
#define GPIO_SR_SR2                ((uint16_t)0x0004U) /* Port x Slew Rate bit 2  */
#define GPIO_SR_SR3                ((uint16_t)0x0008U) /* Port x Slew Rate bit 3  */
#define GPIO_SR_SR4                ((uint16_t)0x0010U) /* Port x Slew Rate bit 4  */
#define GPIO_SR_SR5                ((uint16_t)0x0020U) /* Port x Slew Rate bit 5  */
#define GPIO_SR_SR6                ((uint16_t)0x0040U) /* Port x Slew Rate bit 6  */
#define GPIO_SR_SR7                ((uint16_t)0x0080U) /* Port x Slew Rate bit 7  */
#define GPIO_SR_SR8                ((uint16_t)0x0100U) /* Port x Slew Rate bit 8  */
#define GPIO_SR_SR9                ((uint16_t)0x0200U) /* Port x Slew Rate bit 9  */
#define GPIO_SR_SR10               ((uint16_t)0x0400U) /* Port x Slew Rate bit 10 */
#define GPIO_SR_SR11               ((uint16_t)0x0800U) /* Port x Slew Rate bit 11 */
#define GPIO_SR_SR12               ((uint16_t)0x1000U) /* Port x Slew Rate bit 12 */
#define GPIO_SR_SR13               ((uint16_t)0x2000U) /* Port x Slew Rate bit 13 */
#define GPIO_SR_SR14               ((uint16_t)0x4000U) /* Port x Slew Rate bit 14 */
#define GPIO_SR_SR15               ((uint16_t)0x8000U) /* Port x Slew Rate bit 15 */

/** Bit definition for GPIO_PUPD register **/
#define GPIO_PUPD0_Pos             (0)                                   
#define GPIO_PUPD0_Msk             (0x3 << GPIO_PUPD0_Pos)         /* 0x00000003 */
#define GPIO_PUPD0                         GPIO_PUPD0_Msk          /* 0x00000003 */     
#define GPIO_PUPD0_0               (0x0 << GPIO_PUPD0_Pos)         /* 0x00000000 */
#define GPIO_PUPD0_1               (0x1 << GPIO_PUPD0_Pos)         /* 0x00000001 */
#define GPIO_PUPD0_2               (0x2 << GPIO_PUPD0_Pos)         /* 0x00000002 */

#define GPIO_PUPD1_Pos             (2)                                   
#define GPIO_PUPD1_Msk             (0x3 << GPIO_PUPD1_Pos)         /* 0x0000000C */
#define GPIO_PUPD1                         GPIO_PUPD1_Msk          /* 0x0000000C */     
#define GPIO_PUPD1_0               (0x0 << GPIO_PUPD1_Pos)         /* 0x00000000 */
#define GPIO_PUPD1_1               (0x1 << GPIO_PUPD1_Pos)         /* 0x00000004 */
#define GPIO_PUPD1_2               (0x2 << GPIO_PUPD1_Pos)         /* 0x00000008 */

#define GPIO_PUPD2_Pos             (4)                                   
#define GPIO_PUPD2_Msk             (0x3 << GPIO_PUPD2_Pos)         /* 0x00000030 */
#define GPIO_PUPD2                         GPIO_PUPD2_Msk          /* 0x00000030 */       
#define GPIO_PUPD2_0               (0x0 << GPIO_PUPD2_Pos)         /* 0x00000000 */
#define GPIO_PUPD2_1               (0x1 << GPIO_PUPD2_Pos)         /* 0x00000010 */
#define GPIO_PUPD2_2               (0x2 << GPIO_PUPD2_Pos)         /* 0x00000020 */

#define GPIO_PUPD3_Pos             (6)                                   
#define GPIO_PUPD3_Msk             (0x3 << GPIO_PUPD3_Pos)         /* 0x000000C0 */
#define GPIO_PUPD3                         GPIO_PUPD3_Msk          /* 0x000000C0 */        
#define GPIO_PUPD3_0               (0x0 << GPIO_PUPD3_Pos)         /* 0x00000000 */
#define GPIO_PUPD3_1               (0x1 << GPIO_PUPD3_Pos)         /* 0x00000040 */
#define GPIO_PUPD3_2               (0x2 << GPIO_PUPD3_Pos)         /* 0x00000080 */

#define GPIO_PUPD4_Pos             (8)                                   
#define GPIO_PUPD4_Msk             (0x3 << GPIO_PUPD4_Pos)         /* 0x00000300 */
#define GPIO_PUPD4                         GPIO_PUPD4_Msk          /* 0x00000300 */         
#define GPIO_PUPD4_0               (0x0 << GPIO_PUPD4_Pos)         /* 0x00000000 */
#define GPIO_PUPD4_1               (0x1 << GPIO_PUPD4_Pos)         /* 0x00000100 */
#define GPIO_PUPD4_2               (0x2 << GPIO_PUPD4_Pos)         /* 0x00000200 */

#define GPIO_PUPD5_Pos             (10)                                   
#define GPIO_PUPD5_Msk             (0x3 << GPIO_PUPD5_Pos)         /* 0x00000C00 */
#define GPIO_PUPD5                         GPIO_PUPD5_Msk          /* 0x00000C00 */         
#define GPIO_PUPD5_0               (0x0 << GPIO_PUPD5_Pos)         /* 0x00000000 */
#define GPIO_PUPD5_1               (0x1 << GPIO_PUPD5_Pos)         /* 0x00000400 */
#define GPIO_PUPD5_2               (0x2 << GPIO_PUPD5_Pos)         /* 0x00000800 */

#define GPIO_PUPD6_Pos             (12)                                   
#define GPIO_PUPD6_Msk             (0x3 << GPIO_PUPD6_Pos)         /* 0x00003000 */
#define GPIO_PUPD6                         GPIO_PUPD6_Msk          /* 0x00003000 */         
#define GPIO_PUPD6_0               (0x0 << GPIO_PUPD6_Pos)         /* 0x00000000 */
#define GPIO_PUPD6_1               (0x1 << GPIO_PUPD6_Pos)         /* 0x00001000 */
#define GPIO_PUPD6_2               (0x2 << GPIO_PUPD6_Pos)         /* 0x00002000 */

#define GPIO_PUPD7_Pos             (14)                                   
#define GPIO_PUPD7_Msk             (0x3 << GPIO_PUPD7_Pos)         /* 0x0000C000 */
#define GPIO_PUPD7                         GPIO_PUPD7_Msk          /* 0x0000C000 */         
#define GPIO_PUPD7_0               (0x0 << GPIO_PUPD7_Pos)         /* 0x00000000 */
#define GPIO_PUPD7_1               (0x1 << GPIO_PUPD7_Pos)         /* 0x00004000 */
#define GPIO_PUPD7_2               (0x2 << GPIO_PUPD7_Pos)         /* 0x00008000 */

#define GPIO_PUPD8_Pos             (16)                                   
#define GPIO_PUPD8_Msk             (0x3 << GPIO_PUPD8_Pos)         /* 0x00030000 */
#define GPIO_PUPD8                         GPIO_PUPD8_Msk          /* 0x00030000 */         
#define GPIO_PUPD8_0               (0x0 << GPIO_PUPD8_Pos)         /* 0x00000000 */
#define GPIO_PUPD8_1               (0x1 << GPIO_PUPD8_Pos)         /* 0x00010000 */
#define GPIO_PUPD8_2               (0x2 << GPIO_PUPD8_Pos)         /* 0x00020000 */

#define GPIO_PUPD9_Pos             (18)                                   
#define GPIO_PUPD9_Msk             (0x3 << GPIO_PUPD9_Pos)         /* 0x000C0000 */
#define GPIO_PUPD9                         GPIO_PUPD9_Msk          /* 0x000C0000 */         
#define GPIO_PUPD9_0               (0x0 << GPIO_PUPD9_Pos)         /* 0x00000000 */
#define GPIO_PUPD9_1               (0x1 << GPIO_PUPD9_Pos)         /* 0x00040000 */
#define GPIO_PUPD9_2               (0x2 << GPIO_PUPD9_Pos)         /* 0x00080000 */

#define GPIO_PUPD10_Pos            (20)                                   
#define GPIO_PUPD10_Msk            (0x3 << GPIO_PUPD10_Pos)        /* 0x00300000 */
#define GPIO_PUPD10                        GPIO_PUPD10_Msk         /* 0x00300000 */         
#define GPIO_PUPD10_0              (0x0 << GPIO_PUPD10_Pos)        /* 0x00000000 */
#define GPIO_PUPD10_1              (0x1 << GPIO_PUPD10_Pos)        /* 0x00100000 */
#define GPIO_PUPD10_2              (0x2 << GPIO_PUPD10_Pos)        /* 0x00200000 */

#define GPIO_PUPD11_Pos            (22)                                   
#define GPIO_PUPD11_Msk            (0x3 << GPIO_PUPD11_Pos)        /* 0x00C00000 */
#define GPIO_PUPD11                        GPIO_PUPD11_Msk         /* 0x00C00000 */         
#define GPIO_PUPD11_0              (0x0 << GPIO_PUPD11_Pos)        /* 0x00000000 */
#define GPIO_PUPD11_1              (0x1 << GPIO_PUPD11_Pos)        /* 0x00400000 */
#define GPIO_PUPD11_2              (0x2 << GPIO_PUPD11_Pos)        /* 0x00800000 */

#define GPIO_PUPD12_Pos            (24)                                   
#define GPIO_PUPD12_Msk            (0x3 << GPIO_PUPD12_Pos)        /* 0x03000000 */
#define GPIO_PUPD12                        GPIO_PUPD12_Msk         /* 0x03000000 */         
#define GPIO_PUPD12_0              (0x0 << GPIO_PUPD12_Pos)        /* 0x00000000 */
#define GPIO_PUPD12_1              (0x1 << GPIO_PUPD12_Pos)        /* 0x01000000 */
#define GPIO_PUPD12_2              (0x2 << GPIO_PUPD12_Pos)        /* 0x02000000 */

#define GPIO_PUPD13_Pos            (26)                                   
#define GPIO_PUPD13_Msk            (0x3 << GPIO_PUPD13_Pos)         /* 0x0C000000 */
#define GPIO_PUPD13                        GPIO_PUPD13_Msk          /* 0x0C000000 */         
#define GPIO_PUPD13_0              (0x0 << GPIO_PUPD13_Pos)         /* 0x00000000 */
#define GPIO_PUPD13_1              (0x1 << GPIO_PUPD13_Pos)         /* 0x04000000 */
#define GPIO_PUPD13_2              (0x2 << GPIO_PUPD13_Pos)         /* 0x08000000 */

#define GPIO_PUPD14_Pos            (28)                                   
#define GPIO_PUPD14_Msk            (0x3 << GPIO_PUPD14_Pos)         /* 0x30000000 */
#define GPIO_PUPD14                        GPIO_PUPD14_Msk          /* 0x30000000 */ 
#define GPIO_PUPD14_0              (0x0 << GPIO_PUPD14_Pos)         /* 0x00000000 */
#define GPIO_PUPD14_1              (0x1 << GPIO_PUPD14_Pos)         /* 0x10000000 */
#define GPIO_PUPD14_2              (0x2 << GPIO_PUPD14_Pos)         /* 0x30000000 */

#define GPIO_PUPD15_Pos            (30)                                   
#define GPIO_PUPD15_Msk            (0x3 << GPIO_PUPD15_Pos)         /* 0xC0000000 */
#define GPIO_PUPD15                        GPIO_PUPD15_Msk          /* 0xC0000000 */         
#define GPIO_PUPD15_0              (0x0 << GPIO_PUPD15_Pos)         /* 0x00000000 */
#define GPIO_PUPD15_1              (0x1 << GPIO_PUPD15_Pos)         /* 0x40000000 */
#define GPIO_PUPD15_2              (0x2 << GPIO_PUPD15_Pos)         /* 0x80000000 */

/** Bit definition for GPIO_PID register **/
#define GPIO_PID_PID0              ((uint16_t)0x0001U) /* Port input data, bit 0  */
#define GPIO_PID_PID1              ((uint16_t)0x0002U) /* Port input data, bit 1  */
#define GPIO_PID_PID2              ((uint16_t)0x0004U) /* Port input data, bit 2  */
#define GPIO_PID_PID3              ((uint16_t)0x0008U) /* Port input data, bit 3  */
#define GPIO_PID_PID4              ((uint16_t)0x0010U) /* Port input data, bit 4  */
#define GPIO_PID_PID5              ((uint16_t)0x0020U) /* Port input data, bit 5  */
#define GPIO_PID_PID6              ((uint16_t)0x0040U) /* Port input data, bit 6  */
#define GPIO_PID_PID7              ((uint16_t)0x0080U) /* Port input data, bit 7  */
#define GPIO_PID_PID8              ((uint16_t)0x0100U) /* Port input data, bit 8  */
#define GPIO_PID_PID9              ((uint16_t)0x0200U) /* Port input data, bit 9  */
#define GPIO_PID_PID10             ((uint16_t)0x0400U) /* Port input data, bit 10 */
#define GPIO_PID_PID11             ((uint16_t)0x0800U) /* Port input data, bit 11 */
#define GPIO_PID_PID12             ((uint16_t)0x1000U) /* Port input data, bit 12 */
#define GPIO_PID_PID13             ((uint16_t)0x2000U) /* Port input data, bit 13 */
#define GPIO_PID_PID14             ((uint16_t)0x4000U) /* Port input data, bit 14 */
#define GPIO_PID_PID15             ((uint16_t)0x8000U) /* Port input data, bit 15 */

/** Bit definition for GPIO_POD register **/
#define GPIO_POD_POD0              ((uint16_t)0x0001U) /* Port output data, bit 0  */
#define GPIO_POD_POD1              ((uint16_t)0x0002U) /* Port output data, bit 1  */
#define GPIO_POD_POD2              ((uint16_t)0x0004U) /* Port output data, bit 2  */
#define GPIO_POD_POD3              ((uint16_t)0x0008U) /* Port output data, bit 3  */
#define GPIO_POD_POD4              ((uint16_t)0x0010U) /* Port output data, bit 4  */
#define GPIO_POD_POD5              ((uint16_t)0x0020U) /* Port output data, bit 5  */
#define GPIO_POD_POD6              ((uint16_t)0x0040U) /* Port output data, bit 6  */
#define GPIO_POD_POD7              ((uint16_t)0x0080U) /* Port output data, bit 7  */
#define GPIO_POD_POD8              ((uint16_t)0x0100U) /* Port output data, bit 8  */
#define GPIO_POD_POD9              ((uint16_t)0x0200U) /* Port output data, bit 9  */
#define GPIO_POD_POD10             ((uint16_t)0x0400U) /* Port output data, bit 10 */
#define GPIO_POD_POD11             ((uint16_t)0x0800U) /* Port output data, bit 11 */
#define GPIO_POD_POD12             ((uint16_t)0x1000U) /* Port output data, bit 12 */
#define GPIO_POD_POD13             ((uint16_t)0x2000U) /* Port output data, bit 13 */
#define GPIO_POD_POD14             ((uint16_t)0x4000U) /* Port output data, bit 14 */
#define GPIO_POD_POD15             ((uint16_t)0x8000U) /* Port output data, bit 15 */

/** Bit definition for GPIO_PBSC register **/
#define GPIO_PBSC_PBS0             ((uint32_t)0x00000001U) /* Port x Set bit 0  */
#define GPIO_PBSC_PBS1             ((uint32_t)0x00000002U) /* Port x Set bit 1  */
#define GPIO_PBSC_PBS2             ((uint32_t)0x00000004U) /* Port x Set bit 2  */
#define GPIO_PBSC_PBS3             ((uint32_t)0x00000008U) /* Port x Set bit 3  */
#define GPIO_PBSC_PBS4             ((uint32_t)0x00000010U) /* Port x Set bit 4  */
#define GPIO_PBSC_PBS5             ((uint32_t)0x00000020U) /* Port x Set bit 5  */
#define GPIO_PBSC_PBS6             ((uint32_t)0x00000040U) /* Port x Set bit 6  */
#define GPIO_PBSC_PBS7             ((uint32_t)0x00000080U) /* Port x Set bit 7  */
#define GPIO_PBSC_PBS8             ((uint32_t)0x00000100U) /* Port x Set bit 8  */
#define GPIO_PBSC_PBS9             ((uint32_t)0x00000200U) /* Port x Set bit 9  */
#define GPIO_PBSC_PBS10            ((uint32_t)0x00000400U) /* Port x Set bit 10 */
#define GPIO_PBSC_PBS11            ((uint32_t)0x00000800U) /* Port x Set bit 11 */
#define GPIO_PBSC_PBS12            ((uint32_t)0x00001000U) /* Port x Set bit 12 */
#define GPIO_PBSC_PBS13            ((uint32_t)0x00002000U) /* Port x Set bit 13 */
#define GPIO_PBSC_PBS14            ((uint32_t)0x00004000U) /* Port x Set bit 14 */
#define GPIO_PBSC_PBS15            ((uint32_t)0x00008000U) /* Port x Set bit 15 */

#define GPIO_PBSC_PBC0             ((uint32_t)0x00010000U) /* Port x Reset bit 0  */
#define GPIO_PBSC_PBC1             ((uint32_t)0x00020000U) /* Port x Reset bit 1  */
#define GPIO_PBSC_PBC2             ((uint32_t)0x00040000U) /* Port x Reset bit 2  */
#define GPIO_PBSC_PBC3             ((uint32_t)0x00080000U) /* Port x Reset bit 3  */
#define GPIO_PBSC_PBC4             ((uint32_t)0x00100000U) /* Port x Reset bit 4  */
#define GPIO_PBSC_PBC5             ((uint32_t)0x00200000U) /* Port x Reset bit 5  */
#define GPIO_PBSC_PBC6             ((uint32_t)0x00400000U) /* Port x Reset bit 6  */
#define GPIO_PBSC_PBC7             ((uint32_t)0x00800000U) /* Port x Reset bit 7  */
#define GPIO_PBSC_PBC8             ((uint32_t)0x01000000U) /* Port x Reset bit 8  */
#define GPIO_PBSC_PBC9             ((uint32_t)0x02000000U) /* Port x Reset bit 9  */
#define GPIO_PBSC_PBC10            ((uint32_t)0x04000000U) /* Port x Reset bit 10 */
#define GPIO_PBSC_PBC11            ((uint32_t)0x08000000U) /* Port x Reset bit 11 */
#define GPIO_PBSC_PBC12            ((uint32_t)0x10000000U) /* Port x Reset bit 12 */
#define GPIO_PBSC_PBC13            ((uint32_t)0x20000000U) /* Port x Reset bit 13 */
#define GPIO_PBSC_PBC14            ((uint32_t)0x40000000U) /* Port x Reset bit 14 */
#define GPIO_PBSC_PBC15            ((uint32_t)0x80000000U) /* Port x Reset bit 15 */

/**  Bit definition for GPIO_PLOCK register **/
#define GPIO_PLOCK_PLOCK0          ((uint32_t)0x00000001U) /* Port x Lock bit 0  */
#define GPIO_PLOCK_PLOCK1          ((uint32_t)0x00000002U) /* Port x Lock bit 1  */
#define GPIO_PLOCK_PLOCK2          ((uint32_t)0x00000004U) /* Port x Lock bit 2  */
#define GPIO_PLOCK_PLOCK3          ((uint32_t)0x00000008U) /* Port x Lock bit 3  */
#define GPIO_PLOCK_PLOCK4          ((uint32_t)0x00000010U) /* Port x Lock bit 4  */
#define GPIO_PLOCK_PLOCK5          ((uint32_t)0x00000020U) /* Port x Lock bit 5  */
#define GPIO_PLOCK_PLOCK6          ((uint32_t)0x00000040U) /* Port x Lock bit 6  */
#define GPIO_PLOCK_PLOCK7          ((uint32_t)0x00000080U) /* Port x Lock bit 7  */
#define GPIO_PLOCK_PLOCK8          ((uint32_t)0x00000100U) /* Port x Lock bit 8  */
#define GPIO_PLOCK_PLOCK9          ((uint32_t)0x00000200U) /* Port x Lock bit 9  */
#define GPIO_PLOCK_PLOCK10         ((uint32_t)0x00000400U) /* Port x Lock bit 10 */
#define GPIO_PLOCK_PLOCK11         ((uint32_t)0x00000800U) /* Port x Lock bit 11 */
#define GPIO_PLOCK_PLOCK12         ((uint32_t)0x00001000U) /* Port x Lock bit 12 */
#define GPIO_PLOCK_PLOCK13         ((uint32_t)0x00002000U) /* Port x Lock bit 13 */
#define GPIO_PLOCK_PLOCK14         ((uint32_t)0x00004000U) /* Port x Lock bit 14 */
#define GPIO_PLOCK_PLOCK15         ((uint32_t)0x00008000U) /* Port x Lock bit 15 */
#define GPIO_PLOCK_PLOCKK          ((uint32_t)0x00010000U) /* Lock key */

/** Bit definition for GPIO_AFL register **/
#define GPIO_AFL_AFSEL0            ((uint32_t)0x0000000FU) /* Port x AFL bit (0..3) */
#define GPIO_AFL_AFSEL1            ((uint32_t)0x000000F0U) /* Port x AFL bit (4..7) */
#define GPIO_AFL_AFSEL2            ((uint32_t)0x00000F00U) /* Port x AFL bit (8..11) */
#define GPIO_AFL_AFSEL3            ((uint32_t)0x0000F000U) /* Port x AFL bit (12..15) */
#define GPIO_AFL_AFSEL4            ((uint32_t)0x000F0000U) /* Port x AFL bit (16..19) */
#define GPIO_AFL_AFSEL5            ((uint32_t)0x00F00000U) /* Port x AFL bit (20..23) */
#define GPIO_AFL_AFSEL6            ((uint32_t)0x0F000000U) /* Port x AFL bit (24..27) */
#define GPIO_AFL_AFSEL7            ((uint32_t)0xF0000000U) /* Port x AFL bit (27..31) */

/** Bit definition for GPIO_AFH register **/
#define GPIO_AFH_AFSEL8            ((uint32_t)0x0000000FU) /* Port x AFH bit (0..3) */
#define GPIO_AFH_AFSEL9            ((uint32_t)0x000000F0U) /* Port x AFH bit (4..7) */
#define GPIO_AFH_AFSEL10           ((uint32_t)0x00000F00U) /* Port x AFH bit (8..11) */
#define GPIO_AFH_AFSEL11           ((uint32_t)0x0000F000U) /* Port x AFH bit (12..15) */
#define GPIO_AFH_AFSEL12           ((uint32_t)0x000F0000U) /* Port x AFH bit (16..19) */
#define GPIO_AFH_AFSEL13           ((uint32_t)0x00F00000U) /* Port x AFH bit (20..23) */
#define GPIO_AFH_AFSEL14           ((uint32_t)0x0F000000U) /* Port x AFH bit (24..27) */
#define GPIO_AFH_AFSEL15           ((uint32_t)0xF0000000U) /* Port x AFH bit (27..31) */

/** Bit definition for GPIO_PBC register **/
#define GPIO_PBC_PBC0              ((uint16_t)0x0001U) /* Port x Reset bit 0  */
#define GPIO_PBC_PBC1              ((uint16_t)0x0002U) /* Port x Reset bit 1  */
#define GPIO_PBC_PBC2              ((uint16_t)0x0004U) /* Port x Reset bit 2  */
#define GPIO_PBC_PBC3              ((uint16_t)0x0008U) /* Port x Reset bit 3  */
#define GPIO_PBC_PBC4              ((uint16_t)0x0010U) /* Port x Reset bit 4  */
#define GPIO_PBC_PBC5              ((uint16_t)0x0020U) /* Port x Reset bit 5  */
#define GPIO_PBC_PBC6              ((uint16_t)0x0040U) /* Port x Reset bit 6  */
#define GPIO_PBC_PBC7              ((uint16_t)0x0080U) /* Port x Reset bit 7  */
#define GPIO_PBC_PBC8              ((uint16_t)0x0100U) /* Port x Reset bit 8  */
#define GPIO_PBC_PBC9              ((uint16_t)0x0200U) /* Port x Reset bit 9  */
#define GPIO_PBC_PBC10             ((uint16_t)0x0400U) /* Port x Reset bit 10 */
#define GPIO_PBC_PBC11             ((uint16_t)0x0800U) /* Port x Reset bit 11 */
#define GPIO_PBC_PBC12             ((uint16_t)0x1000U) /* Port x Reset bit 12 */
#define GPIO_PBC_PBC13             ((uint16_t)0x2000U) /* Port x Reset bit 13 */
#define GPIO_PBC_PBC14             ((uint16_t)0x4000U) /* Port x Reset bit 14 */
#define GPIO_PBC_PBC15             ((uint16_t)0x8000U) /* Port x Reset bit 15 */

/** Bit definition for GPIO_DS register **/
#define GPIO_DS_DS0                ((uint16_t)0x0001U) /* Port x Reset bit 0  */
#define GPIO_DS_DS1                ((uint16_t)0x0002U) /* Port x Reset bit 1  */
#define GPIO_DS_DS2                ((uint16_t)0x0004U) /* Port x Reset bit 2  */
#define GPIO_DS_DS3                ((uint16_t)0x0008U) /* Port x Reset bit 3  */
#define GPIO_DS_DS4                ((uint16_t)0x0010U) /* Port x Reset bit 4  */
#define GPIO_DS_DS5                ((uint16_t)0x0020U) /* Port x Reset bit 5  */
#define GPIO_DS_DS6                ((uint16_t)0x0040U) /* Port x Reset bit 6  */
#define GPIO_DS_DS7                ((uint16_t)0x0080U) /* Port x Reset bit 7  */
#define GPIO_DS_DS8                ((uint16_t)0x0100U) /* Port x Reset bit 8  */
#define GPIO_DS_DS9                ((uint16_t)0x0200U) /* Port x Reset bit 9  */
#define GPIO_DS_DS10               ((uint16_t)0x0400U) /* Port x Reset bit 10 */
#define GPIO_DS_DS11               ((uint16_t)0x0800U) /* Port x Reset bit 11 */
#define GPIO_DS_DS12               ((uint16_t)0x1000U) /* Port x Reset bit 12 */
#define GPIO_DS_DS13               ((uint16_t)0x2000U) /* Port x Reset bit 13 */
#define GPIO_DS_DS14               ((uint16_t)0x4000U) /* Port x Reset bit 14 */
#define GPIO_DS_DS15               ((uint16_t)0x8000U) /* Port x Reset bit 15 */

/** Bit definition for AFIO register **/

/** Bit definition for AFIO_RMP_CFG register **/
#define AFIO_RMP_CFG_IOFLITCFG     ((uint32_t)0x0000001FU)  /* Filter stage control bit (0..4) */
#define AFIO_RMP_CFG_EXTI_ETRR     ((uint32_t)0x00007800U)  /* Selects the EXTI line through which the ETRGREG is remapped */
#define AFIO_RMP_CFG_SPI1_NSS      ((uint32_t)0x00200000U)  /* NSS mode of SPI1 */
#define AFIO_RMP_CFG_SPI2_NSS      ((uint32_t)0x00400000U)  /* NSS mode of SPI2 */
#define AFIO_RMP_CFG_SPI3_NSS      ((uint32_t)0x00800000U)  /* NSS mode of SPI3 */
#define AFIO_RMP_CFG_TIM3CH2       ((uint32_t)0x10000000U)  /* TIM3_CH2 REMAP SLECTION */

/** Bit definition for AFIO_EXTI_CFG1 register **/
#define AFIO_EXTI_CFG1_EXTI0       ((uint32_t)0x0000003FU)  /* EXTI 0 configuration */
#define AFIO_EXTI_CFG1_EXTI1       ((uint32_t)0x00003F00U)  /* EXTI 1 configuration */
#define AFIO_EXTI_CFG1_EXTI2       ((uint32_t)0x003F0000U)  /* EXTI 2 configuration */
#define AFIO_EXTI_CFG1_EXTI3       ((uint32_t)0x3F000000U)  /* EXTI 3 configuration */

/** Bit definition for AFIO_EXTI_CFG1 register **/
#define AFIO_EXTI_CFG1_EXTI0_PA0   ((uint32_t)0x00000001U) /* PA[0] pin */
#define AFIO_EXTI_CFG1_EXTI0_PB0   ((uint32_t)0x00000002U) /* PB[0] pin */
#define AFIO_EXTI_CFG1_EXTI0_PC0   ((uint32_t)0x00000004U) /* PC[0] pin */
#define AFIO_EXTI_CFG1_EXTI0_PD0   ((uint32_t)0x00000008U) /* PD[0] pin */

#define AFIO_EXTI_CFG1_EXTI1_PA1   ((uint32_t)0x00000010U) /* PA[1] pin */
#define AFIO_EXTI_CFG1_EXTI1_PB1   ((uint32_t)0x00000020U) /* PB[1] pin */
#define AFIO_EXTI_CFG1_EXTI1_PC1   ((uint32_t)0x00000040U) /* PC[1] pin */
#define AFIO_EXTI_CFG1_EXTI1_PD1   ((uint32_t)0x00000080U) /* PD[1] pin */

#define AFIO_EXTI_CFG1_EXTI2_PA2   ((uint32_t)0x00000100U) /* PA[2] pin */
#define AFIO_EXTI_CFG1_EXTI2_PB2   ((uint32_t)0x00000200U) /* PB[2] pin */
#define AFIO_EXTI_CFG1_EXTI2_PC2   ((uint32_t)0x00000400U) /* PC[2] pin */
#define AFIO_EXTI_CFG1_EXTI2_PD2   ((uint32_t)0x00000800U) /* PD[2] pin */

#define AFIO_EXTI_CFG1_EXTI3_PA3   ((uint32_t)0x0C001000U) /* PA[3] pin */
#define AFIO_EXTI_CFG1_EXTI3_PB3   ((uint32_t)0x0D002000U) /* PB[3] pin */
#define AFIO_EXTI_CFG1_EXTI3_PC3   ((uint32_t)0x00004000U) /* PC[3] pin */
#define AFIO_EXTI_CFG1_EXTI3_PD3   ((uint32_t)0x00008000U) /* PD[3] pin */

/** Bit definition for AFIO_EXTI_CFG2 register **/
#define AFIO_EXTI_CFG2_EXTI4       ((uint32_t)0x0000003FU)  /* EXTI 4 configuration */
#define AFIO_EXTI_CFG2_EXTI5       ((uint32_t)0x00003F00U)  /* EXTI 5 configuration */
#define AFIO_EXTI_CFG2_EXTI6       ((uint32_t)0x003F0000U)  /* EXTI 6 configuration */
#define AFIO_EXTI_CFG2_EXTI7       ((uint32_t)0x3F000000U)  /* EXTI 7 configuration */

/** Bit definition for AFIO_EXTI_CFG2 register **/
#define AFIO_EXTI_CFG2_EXTI4_PA4   ((uint32_t)0x00000001U) /* PA[4] pin */
#define AFIO_EXTI_CFG2_EXTI4_PB4   ((uint32_t)0x00000002U) /* PB[4] pin */
#define AFIO_EXTI_CFG2_EXTI4_PC4   ((uint32_t)0x00000004U) /* PC[4] pin */
#define AFIO_EXTI_CFG2_EXTI4_PD4   ((uint32_t)0x00000008U) /* PD[4] pin */

#define AFIO_EXTI_CFG2_EXTI5_PA5   ((uint32_t)0x00000010U) /* PA[5] pin */
#define AFIO_EXTI_CFG2_EXTI5_PB5   ((uint32_t)0x00000020U) /* PB[5] pin */
#define AFIO_EXTI_CFG2_EXTI5_PC5   ((uint32_t)0x00000040U) /* PC[5] pin */
#define AFIO_EXTI_CFG2_EXTI5_PD5   ((uint32_t)0x00000080U) /* PD[5] pin */

#define AFIO_EXTI_CFG2_EXTI6_PA6   ((uint32_t)0x00000100U) /* PA[6] pin */
#define AFIO_EXTI_CFG2_EXTI6_PB6   ((uint32_t)0x00000200U) /* PB[6] pin */
#define AFIO_EXTI_CFG2_EXTI6_PC6   ((uint32_t)0x00000400U) /* PC[6] pin */
#define AFIO_EXTI_CFG2_EXTI6_PD6   ((uint32_t)0x00000800U) /* PD[6] pin */

#define AFIO_EXTI_CFG2_EXTI7_PA7   ((uint32_t)0x00001000U) /* PA[7] pin */
#define AFIO_EXTI_CFG2_EXTI7_PB7   ((uint32_t)0x00002000U) /* PB[7] pin */
#define AFIO_EXTI_CFG2_EXTI7_PC7   ((uint32_t)0x00004000U) /* PC[7] pin */
#define AFIO_EXTI_CFG2_EXTI7_PD7   ((uint32_t)0x00008000U) /* PD[7] pin */

/** Bit definition for AFIO_EXTI_CFG3 register **/
#define AFIO_EXTI_CFG2_EXTI8       ((uint32_t)0x0000003FU)  /* EXTI 8 configuration */
#define AFIO_EXTI_CFG2_EXTI9       ((uint32_t)0x00003F00U)  /* EXTI 9 configuration */
#define AFIO_EXTI_CFG2_EXTI10      ((uint32_t)0x003F0000U)  /* EXTI 10 configuration */
#define AFIO_EXTI_CFG2_EXTI11      ((uint32_t)0x3F000000U)  /* EXTI 11 configuration */

/** Bit definition for AFIO_EXTI_CFG3 register **/
#define AFIO_EXTI_CFG3_EXTI8_PA8   ((uint32_t)0x00000001U) /* PA[8] pin */
#define AFIO_EXTI_CFG3_EXTI8_PB8   ((uint32_t)0x00000002U) /* PB[8] pin */
#define AFIO_EXTI_CFG3_EXTI8_PC8   ((uint32_t)0x00000004U) /* PC[8] pin */
#define AFIO_EXTI_CFG3_EXTI8_PD8   ((uint32_t)0x00000008U) /* PD[8] pin */

#define AFIO_EXTI_CFG3_EXTI9_PA9   ((uint32_t)0x00000010U) /* PA[9] pin */
#define AFIO_EXTI_CFG3_EXTI9_PB9   ((uint32_t)0x00000020U) /* PB[9] pin */
#define AFIO_EXTI_CFG3_EXTI9_PC9   ((uint32_t)0x00000040U) /* PC[9] pin */
#define AFIO_EXTI_CFG3_EXTI9_PD9   ((uint32_t)0x00000080U) /* PD[9] pin */

#define AFIO_EXTI_CFG3_EXTI10_PA10 ((uint32_t)0x00000100U) /* PA[10] pin */
#define AFIO_EXTI_CFG3_EXTI10_PB10 ((uint32_t)0x00000200U) /* PB[10] pin */
#define AFIO_EXTI_CFG3_EXTI10_PC10 ((uint32_t)0x00000400U) /* PC[10] pin */
#define AFIO_EXTI_CFG3_EXTI10_PD10 ((uint32_t)0x00000800U) /* PD[10] pin */

#define AFIO_EXTI_CFG3_EXTI11_PA11 ((uint32_t)0x00001000U) /* PA[11] pin */
#define AFIO_EXTI_CFG3_EXTI11_PB11 ((uint32_t)0x00002000U) /* PB[11] pin */
#define AFIO_EXTI_CFG3_EXTI11_PC11 ((uint32_t)0x00004000U) /* PC[11] pin */
#define AFIO_EXTI_CFG3_EXTI11_PD11 ((uint32_t)0x00008000U) /* PD[11] pin */

/** Bit definition for AFIO_EXTI_CFG4 register **/
#define AFIO_EXTI_CFG2_EXTI12      ((uint32_t)0x0000003FU)  /* EXTI 12 configuration */
#define AFIO_EXTI_CFG2_EXTI13      ((uint32_t)0x00003F00U)  /* EXTI 13 configuration */
#define AFIO_EXTI_CFG2_EXTI14      ((uint32_t)0x003F0000U)  /* EXTI 14 configuration */
#define AFIO_EXTI_CFG2_EXTI15      ((uint32_t)0x3F000000U)  /* EXTI 15 configuration */

/** Bit definition for AFIO_EXTI_CFG4 register **/
#define AFIO_EXTI_CFG4_EXTI12_PA12   ((uint32_t)0x00000001U) /* PA[12] pin */
#define AFIO_EXTI_CFG4_EXTI12_PB12   ((uint32_t)0x00000002U) /* PB[12] pin */
#define AFIO_EXTI_CFG4_EXTI12_PC12   ((uint32_t)0x00000004U) /* PC[12] pin */
#define AFIO_EXTI_CFG4_EXTI12_PD12   ((uint32_t)0x00000008U) /* PD[12] pin */

#define AFIO_EXTI_CFG4_EXTI13_PA13   ((uint32_t)0x00000010U) /* PA[13] pin */
#define AFIO_EXTI_CFG4_EXTI13_PB13   ((uint32_t)0x00000020U) /* PB[13] pin */
#define AFIO_EXTI_CFG4_EXTI13_PC13   ((uint32_t)0x00000040U) /* PC[13] pin */
#define AFIO_EXTI_CFG4_EXTI13_PD13   ((uint32_t)0x00000080U) /* PD[13] pin */

#define AFIO_EXTI_CFG4_EXTI14_PA14   ((uint32_t)0x00000100U) /* PA[14] pin */
#define AFIO_EXTI_CFG4_EXTI14_PB14   ((uint32_t)0x00000200U) /* PB[14] pin */
#define AFIO_EXTI_CFG4_EXTI14_PC14   ((uint32_t)0x00000400U) /* PC[14] pin */
#define AFIO_EXTI_CFG4_EXTI14_PD14   ((uint32_t)0x00000800U) /* PD[14] pin */

#define AFIO_EXTI_CFG4_EXTI15_PA15   ((uint32_t)0x00001000U) /* PA[15] pin */
#define AFIO_EXTI_CFG4_EXTI15_PB15   ((uint32_t)0x00002000U) /* PB[15] pin */
#define AFIO_EXTI_CFG4_EXTI15_PC15   ((uint32_t)0x00004000U) /* PC[15] pin */
#define AFIO_EXTI_CFG4_EXTI15_PD15   ((uint32_t)0x00008000U) /* PD[15] pin */

/** Bit definition for AFIO_DIGEFT_CFG1 register **/
#define AFIO_DIGEFT_CFG1_PA0DIGEFTEN  ((uint32_t)0x00000001U) /* PA[0]  DIGEFT IE */
#define AFIO_DIGEFT_CFG1_PA1DIGEFTEN  ((uint32_t)0x00000002U) /* PA[1]  DIGEFT IE */
#define AFIO_DIGEFT_CFG1_PA2DIGEFTEN  ((uint32_t)0x00000004U) /* PA[2]  DIGEFT IE */
#define AFIO_DIGEFT_CFG1_PA3DIGEFTEN  ((uint32_t)0x00000008U) /* PA[3]  DIGEFT IE */
#define AFIO_DIGEFT_CFG1_PA4DIGEFTEN  ((uint32_t)0x00000010U) /* PA[4]  DIGEFT IE */
#define AFIO_DIGEFT_CFG1_PA5DIGEFTEN  ((uint32_t)0x00000020U) /* PA[5]  DIGEFT IE */
#define AFIO_DIGEFT_CFG1_PA6DIGEFTEN  ((uint32_t)0x00000040U) /* PA[6]  DIGEFT IE */
#define AFIO_DIGEFT_CFG1_PA7DIGEFTEN  ((uint32_t)0x00000080U) /* PA[7]  DIGEFT IE */
#define AFIO_DIGEFT_CFG1_PA8DIGEFTEN  ((uint32_t)0x00000100U) /* PA[8]  DIGEFT IE */
#define AFIO_DIGEFT_CFG1_PA9DIGEFTEN  ((uint32_t)0x00000200U) /* PA[9]  DIGEFT IE */
#define AFIO_DIGEFT_CFG1_PA10DIGEFTEN ((uint32_t)0x00000400U) /* PA[10] DIGEFT IE */
#define AFIO_DIGEFT_CFG1_PA11DIGEFTEN ((uint32_t)0x00000800U) /* PA[11] DIGEFT IE */
#define AFIO_DIGEFT_CFG1_PA12DIGEFTEN ((uint32_t)0x00001000U) /* PA[12] DIGEFT IE */
#define AFIO_DIGEFT_CFG1_PA13DIGEFTEN ((uint32_t)0x00002000U) /* PA[13] DIGEFT IE */
#define AFIO_DIGEFT_CFG1_PA14DIGEFTEN ((uint32_t)0x00004000U) /* PA[14] DIGEFT IE */
#define AFIO_DIGEFT_CFG1_PA15DIGEFTEN ((uint32_t)0x00008000U) /* PA[15] DIGEFT IE */
#define AFIO_DIGEFT_CFG1_PB0DIGEFTEN  ((uint32_t)0x00010000U) /* PB[0]  DIGEFT IE */
#define AFIO_DIGEFT_CFG1_PB1DIGEFTEN  ((uint32_t)0x00020000U) /* PB[1]  DIGEFT IE */
#define AFIO_DIGEFT_CFG1_PB2DIGEFTEN  ((uint32_t)0x00040000U) /* PB[2]  DIGEFT IE */
#define AFIO_DIGEFT_CFG1_PB3DIGEFTEN  ((uint32_t)0x00080000U) /* PB[3]  DIGEFT IE */
#define AFIO_DIGEFT_CFG1_PB4DIGEFTEN  ((uint32_t)0x00100000U) /* PB[4]  DIGEFT IE */
#define AFIO_DIGEFT_CFG1_PB5DIGEFTEN  ((uint32_t)0x00200000U) /* PB[5]  DIGEFT IE */
#define AFIO_DIGEFT_CFG1_PB6DIGEFTEN  ((uint32_t)0x00400000U) /* PB[6]  DIGEFT IE */
#define AFIO_DIGEFT_CFG1_PB7DIGEFTEN  ((uint32_t)0x00800000U) /* PB[7]  DIGEFT IE */
#define AFIO_DIGEFT_CFG1_PB8DIGEFTEN  ((uint32_t)0x01000000U) /* PB[8]  DIGEFT IE */
#define AFIO_DIGEFT_CFG1_PB9DIGEFTEN  ((uint32_t)0x02000000U) /* PB[9]  DIGEFT IE */
#define AFIO_DIGEFT_CFG1_PB10DIGEFTEN ((uint32_t)0x04000000U) /* PB[10] DIGEFT IE */
#define AFIO_DIGEFT_CFG1_PB11DIGEFTEN ((uint32_t)0x08000000U) /* PB[11] DIGEFT IE */
#define AFIO_DIGEFT_CFG1_PB12DIGEFTEN ((uint32_t)0x10000000U) /* PB[12] DIGEFT IE */
#define AFIO_DIGEFT_CFG1_PB13DIGEFTEN ((uint32_t)0x20000000U) /* PB[13] DIGEFT IE */
#define AFIO_DIGEFT_CFG1_PB14DIGEFTEN ((uint32_t)0x40000000U) /* PB[14] DIGEFT IE */
#define AFIO_DIGEFT_CFG1_PB15DIGEFTEN ((uint32_t)0x80000000U) /* PB[15] DIGEFT IE */

/** Bit definition for AFIO_DIGEFT_CFG2 register **/
#define AFIO_DIGEFT_CFG2_PC0DIGEFTEN  ((uint32_t)0x00000001U) /* PC[0]  DIGEFT IE */
#define AFIO_DIGEFT_CFG2_PC1DIGEFTEN  ((uint32_t)0x00000002U) /* PC[1]  DIGEFT IE */
#define AFIO_DIGEFT_CFG2_PC2DIGEFTEN  ((uint32_t)0x00000004U) /* PC[2]  DIGEFT IE */
#define AFIO_DIGEFT_CFG2_PC3DIGEFTEN  ((uint32_t)0x00000008U) /* PC[3]  DIGEFT IE */
#define AFIO_DIGEFT_CFG2_PC4DIGEFTEN  ((uint32_t)0x00000010U) /* PC[4]  DIGEFT IE */
#define AFIO_DIGEFT_CFG2_PC5DIGEFTEN  ((uint32_t)0x00000020U) /* PC[5]  DIGEFT IE */
#define AFIO_DIGEFT_CFG2_PC6DIGEFTEN  ((uint32_t)0x00000040U) /* PC[6]  DIGEFT IE */
#define AFIO_DIGEFT_CFG2_PC7DIGEFTEN  ((uint32_t)0x00000080U) /* PC[7]  DIGEFT IE */
#define AFIO_DIGEFT_CFG2_PC8DIGEFTEN  ((uint32_t)0x00000100U) /* PC[8]  DIGEFT IE */
#define AFIO_DIGEFT_CFG2_PC9DIGEFTEN  ((uint32_t)0x00000200U) /* PC[9]  DIGEFT IE */
#define AFIO_DIGEFT_CFG2_PC10DIGEFTEN ((uint32_t)0x00000400U) /* PC[10] DIGEFT IE */
#define AFIO_DIGEFT_CFG2_PC11DIGEFTEN ((uint32_t)0x00000800U) /* PC[11] DIGEFT IE */
#define AFIO_DIGEFT_CFG2_PC12DIGEFTEN ((uint32_t)0x00001000U) /* PC[12] DIGEFT IE */
#define AFIO_DIGEFT_CFG2_PC13DIGEFTEN ((uint32_t)0x00002000U) /* PC[13] DIGEFT IE */
#define AFIO_DIGEFT_CFG2_PC14DIGEFTEN ((uint32_t)0x00004000U) /* PC[14] DIGEFT IE */
#define AFIO_DIGEFT_CFG2_PC15DIGEFTEN ((uint32_t)0x00008000U) /* PC[15] DIGEFT IE */
#define AFIO_DIGEFT_CFG2_PD0DIGEFTEN  ((uint32_t)0x00010000U) /* PD[0]  DIGEFT IE */
#define AFIO_DIGEFT_CFG2_PD1DIGEFTEN  ((uint32_t)0x00020000U) /* PD[1]  DIGEFT IE */
#define AFIO_DIGEFT_CFG2_PD2DIGEFTEN  ((uint32_t)0x00040000U) /* PD[2]  DIGEFT IE */
#define AFIO_DIGEFT_CFG2_PD3DIGEFTEN  ((uint32_t)0x00080000U) /* PD[3]  DIGEFT IE */
#define AFIO_DIGEFT_CFG2_PD4DIGEFTEN  ((uint32_t)0x00100000U) /* PD[4]  DIGEFT IE */
#define AFIO_DIGEFT_CFG2_PD5DIGEFTEN  ((uint32_t)0x00200000U) /* PD[5]  DIGEFT IE */
#define AFIO_DIGEFT_CFG2_PD6DIGEFTEN  ((uint32_t)0x00400000U) /* PD[6]  DIGEFT IE */
#define AFIO_DIGEFT_CFG2_PD7DIGEFTEN  ((uint32_t)0x00800000U) /* PD[7]  DIGEFT IE */
#define AFIO_DIGEFT_CFG2_PD8DIGEFTEN  ((uint32_t)0x01000000U) /* PD[8]  DIGEFT IE */
#define AFIO_DIGEFT_CFG2_PD9DIGEFTEN  ((uint32_t)0x02000000U) /* PD[9]  DIGEFT IE */
#define AFIO_DIGEFT_CFG2_PD10DIGEFTEN ((uint32_t)0x04000000U) /* PD[10] DIGEFT IE */
#define AFIO_DIGEFT_CFG2_PD11DIGEFTEN ((uint32_t)0x08000000U) /* PD[11] DIGEFT IE */z
#define AFIO_DIGEFT_CFG2_PD12DIGEFTEN ((uint32_t)0x10000000U) /* PD[12] DIGEFT IE */
#define AFIO_DIGEFT_CFG2_PD13DIGEFTEN ((uint32_t)0x20000000U) /* PD[13] DIGEFT IE */
#define AFIO_DIGEFT_CFG2_PD14DIGEFTEN ((uint32_t)0x40000000U) /* PD[14] DIGEFT IE */
#define AFIO_DIGEFT_CFG2_PD15DIGEFTEN ((uint32_t)0x80000000U) /* PD[15] DIGEFT IE */


/*** SystemTick ***/

/** Bit definition for SysTick_CTRL register **/
#define SysTick_CTRL_ENABLE    ((uint32_t)0x00000001U) /* Counter enable */
#define SysTick_CTRL_TICKINT   ((uint32_t)0x00000002U) /* Counting down to 0 pends the SysTick handler */
#define SysTick_CTRL_CLKSOURCE ((uint32_t)0x00000004U) /* Clock source */
#define SysTick_CTRL_COUNTFLAG ((uint32_t)0x00010000U) /* Count Flag */

/** Bit definition for SysTick_LOAD register **/
#define SysTick_LOAD_RELOAD ((uint32_t)0x00FFFFFFU) /* Value to load into the SysTick Current Value Register when the counter reaches 0 */
/** Bit definition for SysTick_VAL register **/
#define SysTick_VAL_CURRENT ((uint32_t)0x00FFFFFFU) /* Current value at the time the register is accessed */

/** Bit definition for SysTick_CALIB register **/
#define SysTick_CALIB_TENMS ((uint32_t)0x00FFFFFFU) /* Reload value to use for 10ms timing */
#define SysTick_CALIB_SKEW  ((uint32_t)0x40000000U) /* Calibration value is not exactly 10 ms */
#define SysTick_CALIB_NOREF ((uint32_t)0x80000000U) /* The reference clock is not provided */


/*** Nested Vectored Interrupt Controller ***/

/** Bit definition for NVIC_ISER register **/
#define NVIC_ISER_SETENA    ((uint32_t)0xFFFFFFFFU) /* Interrupt set enable bits */
#define NVIC_ISER_SETENA_0  ((uint32_t)0x00000001U) /* bit 0 */
#define NVIC_ISER_SETENA_1  ((uint32_t)0x00000002U) /* bit 1 */
#define NVIC_ISER_SETENA_2  ((uint32_t)0x00000004U) /* bit 2 */
#define NVIC_ISER_SETENA_3  ((uint32_t)0x00000008U) /* bit 3 */
#define NVIC_ISER_SETENA_4  ((uint32_t)0x00000010U) /* bit 4 */
#define NVIC_ISER_SETENA_5  ((uint32_t)0x00000020U) /* bit 5 */
#define NVIC_ISER_SETENA_6  ((uint32_t)0x00000040U) /* bit 6 */
#define NVIC_ISER_SETENA_7  ((uint32_t)0x00000080U) /* bit 7 */
#define NVIC_ISER_SETENA_8  ((uint32_t)0x00000100U) /* bit 8 */
#define NVIC_ISER_SETENA_9  ((uint32_t)0x00000200U) /* bit 9 */
#define NVIC_ISER_SETENA_10 ((uint32_t)0x00000400U) /* bit 10 */
#define NVIC_ISER_SETENA_11 ((uint32_t)0x00000800U) /* bit 11 */
#define NVIC_ISER_SETENA_12 ((uint32_t)0x00001000U) /* bit 12 */
#define NVIC_ISER_SETENA_13 ((uint32_t)0x00002000U) /* bit 13 */
#define NVIC_ISER_SETENA_14 ((uint32_t)0x00004000U) /* bit 14 */
#define NVIC_ISER_SETENA_15 ((uint32_t)0x00008000U) /* bit 15 */
#define NVIC_ISER_SETENA_16 ((uint32_t)0x00010000U) /* bit 16 */
#define NVIC_ISER_SETENA_17 ((uint32_t)0x00020000U) /* bit 17 */
#define NVIC_ISER_SETENA_18 ((uint32_t)0x00040000U) /* bit 18 */
#define NVIC_ISER_SETENA_19 ((uint32_t)0x00080000U) /* bit 19 */
#define NVIC_ISER_SETENA_20 ((uint32_t)0x00100000U) /* bit 20 */
#define NVIC_ISER_SETENA_21 ((uint32_t)0x00200000U) /* bit 21 */
#define NVIC_ISER_SETENA_22 ((uint32_t)0x00400000U) /* bit 22 */
#define NVIC_ISER_SETENA_23 ((uint32_t)0x00800000U) /* bit 23 */
#define NVIC_ISER_SETENA_24 ((uint32_t)0x01000000U) /* bit 24 */
#define NVIC_ISER_SETENA_25 ((uint32_t)0x02000000U) /* bit 25 */
#define NVIC_ISER_SETENA_26 ((uint32_t)0x04000000U) /* bit 26 */
#define NVIC_ISER_SETENA_27 ((uint32_t)0x08000000U) /* bit 27 */
#define NVIC_ISER_SETENA_28 ((uint32_t)0x10000000U) /* bit 28 */
#define NVIC_ISER_SETENA_29 ((uint32_t)0x20000000U) /* bit 29 */
#define NVIC_ISER_SETENA_30 ((uint32_t)0x40000000U) /* bit 30 */
#define NVIC_ISER_SETENA_31 ((uint32_t)0x80000000U) /* bit 31 */

/** Bit definition for NVIC_ICER register ***/
#define NVIC_ICER_CLRENA    ((uint32_t)0xFFFFFFFFU) /* Interrupt clear-enable bits */
#define NVIC_ICER_CLRENA_0  ((uint32_t)0x00000001U) /* bit 0 */
#define NVIC_ICER_CLRENA_1  ((uint32_t)0x00000002U) /* bit 1 */
#define NVIC_ICER_CLRENA_2  ((uint32_t)0x00000004U) /* bit 2 */
#define NVIC_ICER_CLRENA_3  ((uint32_t)0x00000008U) /* bit 3 */
#define NVIC_ICER_CLRENA_4  ((uint32_t)0x00000010U) /* bit 4 */
#define NVIC_ICER_CLRENA_5  ((uint32_t)0x00000020U) /* bit 5 */
#define NVIC_ICER_CLRENA_6  ((uint32_t)0x00000040U) /* bit 6 */
#define NVIC_ICER_CLRENA_7  ((uint32_t)0x00000080U) /* bit 7 */
#define NVIC_ICER_CLRENA_8  ((uint32_t)0x00000100U) /* bit 8 */
#define NVIC_ICER_CLRENA_9  ((uint32_t)0x00000200U) /* bit 9 */
#define NVIC_ICER_CLRENA_10 ((uint32_t)0x00000400U) /* bit 10 */
#define NVIC_ICER_CLRENA_11 ((uint32_t)0x00000800U) /* bit 11 */
#define NVIC_ICER_CLRENA_12 ((uint32_t)0x00001000U) /* bit 12 */
#define NVIC_ICER_CLRENA_13 ((uint32_t)0x00002000U) /* bit 13 */
#define NVIC_ICER_CLRENA_14 ((uint32_t)0x00004000U) /* bit 14 */
#define NVIC_ICER_CLRENA_15 ((uint32_t)0x00008000U) /* bit 15 */
#define NVIC_ICER_CLRENA_16 ((uint32_t)0x00010000U) /* bit 16 */
#define NVIC_ICER_CLRENA_17 ((uint32_t)0x00020000U) /* bit 17 */
#define NVIC_ICER_CLRENA_18 ((uint32_t)0x00040000U) /* bit 18 */
#define NVIC_ICER_CLRENA_19 ((uint32_t)0x00080000U) /* bit 19 */
#define NVIC_ICER_CLRENA_20 ((uint32_t)0x00100000U) /* bit 20 */
#define NVIC_ICER_CLRENA_21 ((uint32_t)0x00200000U) /* bit 21 */
#define NVIC_ICER_CLRENA_22 ((uint32_t)0x00400000U) /* bit 22 */
#define NVIC_ICER_CLRENA_23 ((uint32_t)0x00800000U) /* bit 23 */
#define NVIC_ICER_CLRENA_24 ((uint32_t)0x01000000U) /* bit 24 */
#define NVIC_ICER_CLRENA_25 ((uint32_t)0x02000000U) /* bit 25 */
#define NVIC_ICER_CLRENA_26 ((uint32_t)0x04000000U) /* bit 26 */
#define NVIC_ICER_CLRENA_27 ((uint32_t)0x08000000U) /* bit 27 */
#define NVIC_ICER_CLRENA_28 ((uint32_t)0x10000000U) /* bit 28 */
#define NVIC_ICER_CLRENA_29 ((uint32_t)0x20000000U) /* bit 29 */
#define NVIC_ICER_CLRENA_30 ((uint32_t)0x40000000U) /* bit 30 */
#define NVIC_ICER_CLRENA_31 ((uint32_t)0x80000000U) /* bit 31 */

/** Bit definition for NVIC_ISPR register **/
#define NVIC_ISPR_SETPEND    ((uint32_t)0xFFFFFFFFU) /* Interrupt set-pending bits */
#define NVIC_ISPR_SETPEND_0  ((uint32_t)0x00000001U) /* bit 0 */
#define NVIC_ISPR_SETPEND_1  ((uint32_t)0x00000002U) /* bit 1 */
#define NVIC_ISPR_SETPEND_2  ((uint32_t)0x00000004U) /* bit 2 */
#define NVIC_ISPR_SETPEND_3  ((uint32_t)0x00000008U) /* bit 3 */
#define NVIC_ISPR_SETPEND_4  ((uint32_t)0x00000010U) /* bit 4 */
#define NVIC_ISPR_SETPEND_5  ((uint32_t)0x00000020U) /* bit 5 */
#define NVIC_ISPR_SETPEND_6  ((uint32_t)0x00000040U) /* bit 6 */
#define NVIC_ISPR_SETPEND_7  ((uint32_t)0x00000080U) /* bit 7 */
#define NVIC_ISPR_SETPEND_8  ((uint32_t)0x00000100U) /* bit 8 */
#define NVIC_ISPR_SETPEND_9  ((uint32_t)0x00000200U) /* bit 9 */
#define NVIC_ISPR_SETPEND_10 ((uint32_t)0x00000400U) /* bit 10 */
#define NVIC_ISPR_SETPEND_11 ((uint32_t)0x00000800U) /* bit 11 */
#define NVIC_ISPR_SETPEND_12 ((uint32_t)0x00001000U) /* bit 12 */
#define NVIC_ISPR_SETPEND_13 ((uint32_t)0x00002000U) /* bit 13 */
#define NVIC_ISPR_SETPEND_14 ((uint32_t)0x00004000U) /* bit 14 */
#define NVIC_ISPR_SETPEND_15 ((uint32_t)0x00008000U) /* bit 15 */
#define NVIC_ISPR_SETPEND_16 ((uint32_t)0x00010000U) /* bit 16 */
#define NVIC_ISPR_SETPEND_17 ((uint32_t)0x00020000U) /* bit 17 */
#define NVIC_ISPR_SETPEND_18 ((uint32_t)0x00040000U) /* bit 18 */
#define NVIC_ISPR_SETPEND_19 ((uint32_t)0x00080000U) /* bit 19 */
#define NVIC_ISPR_SETPEND_20 ((uint32_t)0x00100000U) /* bit 20 */
#define NVIC_ISPR_SETPEND_21 ((uint32_t)0x00200000U) /* bit 21 */
#define NVIC_ISPR_SETPEND_22 ((uint32_t)0x00400000U) /* bit 22 */
#define NVIC_ISPR_SETPEND_23 ((uint32_t)0x00800000U) /* bit 23 */
#define NVIC_ISPR_SETPEND_24 ((uint32_t)0x01000000U) /* bit 24 */
#define NVIC_ISPR_SETPEND_25 ((uint32_t)0x02000000U) /* bit 25 */
#define NVIC_ISPR_SETPEND_26 ((uint32_t)0x04000000U) /* bit 26 */
#define NVIC_ISPR_SETPEND_27 ((uint32_t)0x08000000U) /* bit 27 */
#define NVIC_ISPR_SETPEND_28 ((uint32_t)0x10000000U) /* bit 28 */
#define NVIC_ISPR_SETPEND_29 ((uint32_t)0x20000000U) /* bit 29 */
#define NVIC_ISPR_SETPEND_30 ((uint32_t)0x40000000U) /* bit 30 */
#define NVIC_ISPR_SETPEND_31 ((uint32_t)0x80000000U) /* bit 31 */

/** Bit definition for NVIC_ICPR register **/
#define NVIC_ICPR_CLRPEND    ((uint32_t)0xFFFFFFFFU) /* Interrupt clear-pending bits */
#define NVIC_ICPR_CLRPEND_0  ((uint32_t)0x00000001U) /* bit 0 */
#define NVIC_ICPR_CLRPEND_1  ((uint32_t)0x00000002U) /* bit 1 */
#define NVIC_ICPR_CLRPEND_2  ((uint32_t)0x00000004U) /* bit 2 */
#define NVIC_ICPR_CLRPEND_3  ((uint32_t)0x00000008U) /* bit 3 */
#define NVIC_ICPR_CLRPEND_4  ((uint32_t)0x00000010U) /* bit 4 */
#define NVIC_ICPR_CLRPEND_5  ((uint32_t)0x00000020U) /* bit 5 */
#define NVIC_ICPR_CLRPEND_6  ((uint32_t)0x00000040U) /* bit 6 */
#define NVIC_ICPR_CLRPEND_7  ((uint32_t)0x00000080U) /* bit 7 */
#define NVIC_ICPR_CLRPEND_8  ((uint32_t)0x00000100U) /* bit 8 */
#define NVIC_ICPR_CLRPEND_9  ((uint32_t)0x00000200U) /* bit 9 */
#define NVIC_ICPR_CLRPEND_10 ((uint32_t)0x00000400U) /* bit 10 */
#define NVIC_ICPR_CLRPEND_11 ((uint32_t)0x00000800U) /* bit 11 */
#define NVIC_ICPR_CLRPEND_12 ((uint32_t)0x00001000U) /* bit 12 */
#define NVIC_ICPR_CLRPEND_13 ((uint32_t)0x00002000U) /* bit 13 */
#define NVIC_ICPR_CLRPEND_14 ((uint32_t)0x00004000U) /* bit 14 */
#define NVIC_ICPR_CLRPEND_15 ((uint32_t)0x00008000U) /* bit 15 */
#define NVIC_ICPR_CLRPEND_16 ((uint32_t)0x00010000U) /* bit 16 */
#define NVIC_ICPR_CLRPEND_17 ((uint32_t)0x00020000U) /* bit 17 */
#define NVIC_ICPR_CLRPEND_18 ((uint32_t)0x00040000U) /* bit 18 */
#define NVIC_ICPR_CLRPEND_19 ((uint32_t)0x00080000U) /* bit 19 */
#define NVIC_ICPR_CLRPEND_20 ((uint32_t)0x00100000U) /* bit 20 */
#define NVIC_ICPR_CLRPEND_21 ((uint32_t)0x00200000U) /* bit 21 */
#define NVIC_ICPR_CLRPEND_22 ((uint32_t)0x00400000U) /* bit 22 */
#define NVIC_ICPR_CLRPEND_23 ((uint32_t)0x00800000U) /* bit 23 */
#define NVIC_ICPR_CLRPEND_24 ((uint32_t)0x01000000U) /* bit 24 */
#define NVIC_ICPR_CLRPEND_25 ((uint32_t)0x02000000U) /* bit 25 */
#define NVIC_ICPR_CLRPEND_26 ((uint32_t)0x04000000U) /* bit 26 */
#define NVIC_ICPR_CLRPEND_27 ((uint32_t)0x08000000U) /* bit 27 */
#define NVIC_ICPR_CLRPEND_28 ((uint32_t)0x10000000U) /* bit 28 */
#define NVIC_ICPR_CLRPEND_29 ((uint32_t)0x20000000U) /* bit 29 */
#define NVIC_ICPR_CLRPEND_30 ((uint32_t)0x40000000U) /* bit 30 */
#define NVIC_ICPR_CLRPEND_31 ((uint32_t)0x80000000U) /* bit 31 */

/** Bit definition for NVIC_PRI0 register **/
#define NVIC_IPR0_PRI_0 ((uint32_t)0x000000FFU) /* Priority of interrupt 0 */
#define NVIC_IPR0_PRI_1 ((uint32_t)0x0000FF00U) /* Priority of interrupt 1 */
#define NVIC_IPR0_PRI_2 ((uint32_t)0x00FF0000U) /* Priority of interrupt 2 */
#define NVIC_IPR0_PRI_3 ((uint32_t)0xFF000000U) /* Priority of interrupt 3 */

/** Bit definition for NVIC_PRI1 register **/
#define NVIC_IPR1_PRI_4 ((uint32_t)0x000000FFU) /* Priority of interrupt 4 */
#define NVIC_IPR1_PRI_5 ((uint32_t)0x0000FF00U) /* Priority of interrupt 5 */
#define NVIC_IPR1_PRI_6 ((uint32_t)0x00FF0000U) /* Priority of interrupt 6 */
#define NVIC_IPR1_PRI_7 ((uint32_t)0xFF000000U) /* Priority of interrupt 7 */

/** Bit definition for NVIC_PRI2 register **/
#define NVIC_IPR2_PRI_8  ((uint32_t)0x000000FFU) /* Priority of interrupt 8 */
#define NVIC_IPR2_PRI_9  ((uint32_t)0x0000FF00U) /* Priority of interrupt 9 */
#define NVIC_IPR2_PRI_10 ((uint32_t)0x00FF0000U) /* Priority of interrupt 10 */
#define NVIC_IPR2_PRI_11 ((uint32_t)0xFF000000U) /* Priority of interrupt 11 */

/** Bit definition for NVIC_PRI3 register **/
#define NVIC_IPR3_PRI_12 ((uint32_t)0x000000FFU) /* Priority of interrupt 12 */
#define NVIC_IPR3_PRI_13 ((uint32_t)0x0000FF00U) /* Priority of interrupt 13 */
#define NVIC_IPR3_PRI_14 ((uint32_t)0x00FF0000U) /* Priority of interrupt 14 */
#define NVIC_IPR3_PRI_15 ((uint32_t)0xFF000000U) /* Priority of interrupt 15 */

/** Bit definition for NVIC_PRI4 register **/
#define NVIC_IPR4_PRI_16 ((uint32_t)0x000000FFU) /* Priority of interrupt 16 */
#define NVIC_IPR4_PRI_17 ((uint32_t)0x0000FF00U) /* Priority of interrupt 17 */
#define NVIC_IPR4_PRI_18 ((uint32_t)0x00FF0000U) /* Priority of interrupt 18 */
#define NVIC_IPR4_PRI_19 ((uint32_t)0xFF000000U) /* Priority of interrupt 19 */

/** Bit definition for NVIC_PRI5 register **/
#define NVIC_IPR5_PRI_20 ((uint32_t)0x000000FFU) /* Priority of interrupt 20 */
#define NVIC_IPR5_PRI_21 ((uint32_t)0x0000FF00U) /* Priority of interrupt 21 */
#define NVIC_IPR5_PRI_22 ((uint32_t)0x00FF0000U) /* Priority of interrupt 22 */
#define NVIC_IPR5_PRI_23 ((uint32_t)0xFF000000U) /* Priority of interrupt 23 */

/** Bit definition for NVIC_PRI6 register **/
#define NVIC_IPR6_PRI_24 ((uint32_t)0x000000FFU) /* Priority of interrupt 24 */
#define NVIC_IPR6_PRI_25 ((uint32_t)0x0000FF00U) /* Priority of interrupt 25 */
#define NVIC_IPR6_PRI_26 ((uint32_t)0x00FF0000U) /* Priority of interrupt 26 */
#define NVIC_IPR6_PRI_27 ((uint32_t)0xFF000000U) /* Priority of interrupt 27 */

/** Bit definition for NVIC_PRI7 register **/
#define NVIC_IPR7_PRI_28 ((uint32_t)0x000000FFU) /* Priority of interrupt 28 */
#define NVIC_IPR7_PRI_29 ((uint32_t)0x0000FF00U) /* Priority of interrupt 29 */
#define NVIC_IPR7_PRI_30 ((uint32_t)0x00FF0000U) /* Priority of interrupt 30 */
#define NVIC_IPR7_PRI_31 ((uint32_t)0xFF000000U) /* Priority of interrupt 31 */

/** Bit definition for SCB_CPUID register **/
#define SCB_CPUID_REVISION    ((uint32_t)0x0000000FU) /* Implementation defined revision number */
#define SCB_CPUID_PARTNO      ((uint32_t)0x0000FFF0U) /* Number of processor within family */
#define SCB_CPUID_Constant    ((uint32_t)0x000F0000U) /* Reads as 0x0F */
#define SCB_CPUID_VARIANT     ((uint32_t)0x00F00000U) /* Implementation defined variant number */
#define SCB_CPUID_IMPLEMENTER ((uint32_t)0xFF000000U) /* Implementer code. ARM is 0x41 */

/** Bit definition for SCB_ICSR register **/
#define SCB_ICSR_VECTACTIVE  ((uint32_t)0x000001FFU) /* Active INTSTS number field */
#define SCB_ICSR_RETTOBASE   ((uint32_t)0x00000800U) /* All active exceptions minus the IPSR_current_exception yields the empty set */
#define SCB_ICSR_VECTPENDING ((uint32_t)0x003FF000U) /* Pending INTSTS number field */
#define SCB_ICSR_ISRPENDING  ((uint32_t)0x00400000U) /* Interrupt pending flag */
#define SCB_ICSR_ISRPREEMPT  ((uint32_t)0x00800000U) /* It indicates that a pending interrupt becomes active in the next running cycle */
#define SCB_ICSR_PENDSTCLR   ((uint32_t)0x02000000U) /* Clear pending SysTick bit */
#define SCB_ICSR_PENDSTSET   ((uint32_t)0x04000000U) /* Set pending SysTick bit */
#define SCB_ICSR_PENDSVCLR   ((uint32_t)0x08000000U) /* Clear pending pendSV bit */
#define SCB_ICSR_PENDSVSET   ((uint32_t)0x10000000U) /* Set pending pendSV bit */
#define SCB_ICSR_NMIPENDSET  ((uint32_t)0x80000000U) /* Set pending NMI bit */

/** Bit definition for SCB_AIRCR register **/
#define SCB_AIRCR_VECTCLRACTIVE ((uint32_t)0x00000002U) /* Clear active vector bit */
#define SCB_AIRCR_SYSRESETREQ   ((uint32_t)0x00000004U) /* Requests chip control logic to generate a reset */
#define SCB_AIRCR_ENDIANESS     ((uint32_t)0x00008000U) /* Data endianness bit */
#define SCB_AIRCR_VECTKEYSTAT   ((uint32_t)0xFFFF0000U) /* Reads as 0xFA05 (VECTKEYSTAT) */
#define SCB_AIRCR_VECTKEY       ((uint32_t)0x05FA0000U) /* Register access key */

/** Bit definition for SCB_SCR register **/
#define SCB_SCR_SLEEPONEXIT ((uint8_t)0x02U) /* Sleep on exit bit */
#define SCB_SCR_SLEEPDEEP   ((uint8_t)0x04U) /* Sleep deep bit */
#define SCB_SCR_SEVONPEND   ((uint8_t)0x10U) /* Wake up from WFE */

/** Bit definition for SCB_CCR register **/
#define SCB_CCR_UNALIGN_TRP ((uint16_t)0x0008U) /* Trap for unaligned access */
#define SCB_CCR_STKALIGN    ((uint16_t)0x0200U) /* On exception entry, the SP used prior to the exception is adjusted to be 8-byte aligned */

/** Bit definition for SCB_SHPR register **/
#define SCB_SHPR_PRI_N    ((uint32_t)0x000000FFU) /* Priority of system handler 4,8, and 12. Mem Manage, reserved and Debug Monitor */
#define SCB_SHPR_PRI_N1   ((uint32_t)0x0000FF00U) /* Priority of system handler 5,9, and 13. Bus Fault, reserved and reserved */
#define SCB_SHPR_PRI_N2   ((uint32_t)0x00FF0000U) /* Priority of system handler 6,10, and 14. Usage Fault, reserved and PendSV */
#define SCB_SHPR_PRI_N3   ((uint32_t)0xFF000000U) /* Priority of system handler 7,11, and 15. Reserved, SVCall and SysTick */

/** Bit definition for SCB_SHCSR register **/
#define SCB_SHCSR_SVCALLPENDED   ((uint32_t)0x00008000U) /* SVCall is pended */

/** Bit definition for SCB_DFSR register **/
#define SCB_DFSR_HALTED   ((uint8_t)0x01U) /* Halt request flag */
#define SCB_DFSR_BKPT     ((uint8_t)0x02U) /* BKPT flag */
#define SCB_DFSR_DWTTRAP  ((uint8_t)0x04U) /* Data Watchpoint and Trace (DWT) flag */
#define SCB_DFSR_VCATCH   ((uint8_t)0x08U) /* Vector catch flag */
#define SCB_DFSR_EXTERNAL ((uint8_t)0x10U) /* External debug request flag */

/** Bit definition for SCB_afsr register **/
#define SCB_AFSR_IMPDEF ((uint32_t)0xFFFFFFFFU) /* Implementation defined */



/*** External Interrupt/Event Controller ***/

/** Bit definition for EXTI_EMASK register **/
#define EXTI_EMASK_EMASK0        ((uint32_t)0x00000001U) /* Event Mask on line 0 */
#define EXTI_EMASK_EMASK1        ((uint32_t)0x00000002U) /* Event Mask on line 1 */
#define EXTI_EMASK_EMASK2        ((uint32_t)0x00000004U) /* Event Mask on line 2 */
#define EXTI_EMASK_EMASK3        ((uint32_t)0x00000008U) /* Event Mask on line 3 */
#define EXTI_EMASK_EMASK4        ((uint32_t)0x00000010U) /* Event Mask on line 4 */
#define EXTI_EMASK_EMASK5        ((uint32_t)0x00000020U) /* Event Mask on line 5 */
#define EXTI_EMASK_EMASK6        ((uint32_t)0x00000040U) /* Event Mask on line 6 */
#define EXTI_EMASK_EMASK7        ((uint32_t)0x00000080U) /* Event Mask on line 7 */
#define EXTI_EMASK_EMASK8        ((uint32_t)0x00000100U) /* Event Mask on line 8 */
#define EXTI_EMASK_EMASK9        ((uint32_t)0x00000200U) /* Event Mask on line 9 */
#define EXTI_EMASK_EMASK10       ((uint32_t)0x00000400U) /* Event Mask on line 10 */
#define EXTI_EMASK_EMASK11       ((uint32_t)0x00000800U) /* Event Mask on line 11 */
#define EXTI_EMASK_EMASK12       ((uint32_t)0x00001000U) /* Event Mask on line 12 */
#define EXTI_EMASK_EMASK13       ((uint32_t)0x00002000U) /* Event Mask on line 13 */
#define EXTI_EMASK_EMASK14       ((uint32_t)0x00004000U) /* Event Mask on line 14 */
#define EXTI_EMASK_EMASK15       ((uint32_t)0x00008000U) /* Event Mask on line 15 */
#define EXTI_EMASK_EMASK16       ((uint32_t)0x00010000U) /* Event Mask on line 16 */
#define EXTI_EMASK_EMASK17       ((uint32_t)0x00020000U) /* Event Mask on line 17 */
#define EXTI_EMASK_EMASK18       ((uint32_t)0x00040000U) /* Event Mask on line 18 */
#define EXTI_EMASK_EMASK19       ((uint32_t)0x00080000U) /* Event Mask on line 19 */
#define EXTI_EMASK_EMASK20       ((uint32_t)0x00100000U) /* Event Mask on line 20 */

/** Bit definition for EXTI_IMASK register **/
#define EXTI_IMASK_IMASK0        ((uint32_t)0x00000001U) /* Interrupt Mask on line 0 */
#define EXTI_IMASK_IMASK1        ((uint32_t)0x00000002U) /* Interrupt Mask on line 1 */
#define EXTI_IMASK_IMASK2        ((uint32_t)0x00000004U) /* Interrupt Mask on line 2 */
#define EXTI_IMASK_IMASK3        ((uint32_t)0x00000008U) /* Interrupt Mask on line 3 */
#define EXTI_IMASK_IMASK4        ((uint32_t)0x00000010U) /* Interrupt Mask on line 4 */
#define EXTI_IMASK_IMASK5        ((uint32_t)0x00000020U) /* Interrupt Mask on line 5 */
#define EXTI_IMASK_IMASK6        ((uint32_t)0x00000040U) /* Interrupt Mask on line 6 */
#define EXTI_IMASK_IMASK7        ((uint32_t)0x00000080U) /* Interrupt Mask on line 7 */
#define EXTI_IMASK_IMASK8        ((uint32_t)0x00000100U) /* Interrupt Mask on line 8 */
#define EXTI_IMASK_IMASK9        ((uint32_t)0x00000200U) /* Interrupt Mask on line 9 */
#define EXTI_IMASK_IMASK10       ((uint32_t)0x00000400U) /* Interrupt Mask on line 10 */
#define EXTI_IMASK_IMASK11       ((uint32_t)0x00000800U) /* Interrupt Mask on line 11 */
#define EXTI_IMASK_IMASK12       ((uint32_t)0x00001000U) /* Interrupt Mask on line 12 */
#define EXTI_IMASK_IMASK13       ((uint32_t)0x00002000U) /* Interrupt Mask on line 13 */
#define EXTI_IMASK_IMASK14       ((uint32_t)0x00004000U) /* Interrupt Mask on line 14 */
#define EXTI_IMASK_IMASK15       ((uint32_t)0x00008000U) /* Interrupt Mask on line 15 */
#define EXTI_IMASK_IMASK16       ((uint32_t)0x00010000U) /* Interrupt Mask on line 16 */
#define EXTI_IMASK_IMASK17       ((uint32_t)0x00020000U) /* Interrupt Mask on line 17 */
#define EXTI_IMASK_IMASK18       ((uint32_t)0x00040000U) /* Interrupt Mask on line 18 */
#define EXTI_IMASK_IMASK19       ((uint32_t)0x00080000U) /* Interrupt Mask on line 19 */
#define EXTI_IMASK_IMASK20       ((uint32_t)0x00100000U) /* Interrupt Mask on line 20 */

/** Bit definition for EXTI_FT_CFG register **/
#define EXTI_FT_CFG_FT_CFG0        ((uint32_t)0x00000001U) /* Falling trigger event configuration bit of line 0 */
#define EXTI_FT_CFG_FT_CFG1        ((uint32_t)0x00000002U) /* Falling trigger event configuration bit of line 1 */
#define EXTI_FT_CFG_FT_CFG2        ((uint32_t)0x00000004U) /* Falling trigger event configuration bit of line 2 */
#define EXTI_FT_CFG_FT_CFG3        ((uint32_t)0x00000008U) /* Falling trigger event configuration bit of line 3 */
#define EXTI_FT_CFG_FT_CFG4        ((uint32_t)0x00000010U) /* Falling trigger event configuration bit of line 4 */
#define EXTI_FT_CFG_FT_CFG5        ((uint32_t)0x00000020U) /* Falling trigger event configuration bit of line 5 */
#define EXTI_FT_CFG_FT_CFG6        ((uint32_t)0x00000040U) /* Falling trigger event configuration bit of line 6 */
#define EXTI_FT_CFG_FT_CFG7        ((uint32_t)0x00000080U) /* Falling trigger event configuration bit of line 7 */
#define EXTI_FT_CFG_FT_CFG8        ((uint32_t)0x00000100U) /* Falling trigger event configuration bit of line 8 */
#define EXTI_FT_CFG_FT_CFG9        ((uint32_t)0x00000200U) /* Falling trigger event configuration bit of line 9 */
#define EXTI_FT_CFG_FT_CFG10       ((uint32_t)0x00000400U) /* Falling trigger event configuration bit of line 10 */
#define EXTI_FT_CFG_FT_CFG11       ((uint32_t)0x00000800U) /* Falling trigger event configuration bit of line 11 */
#define EXTI_FT_CFG_FT_CFG12       ((uint32_t)0x00001000U) /* Falling trigger event configuration bit of line 12 */
#define EXTI_FT_CFG_FT_CFG13       ((uint32_t)0x00002000U) /* Falling trigger event configuration bit of line 13 */
#define EXTI_FT_CFG_FT_CFG14       ((uint32_t)0x00004000U) /* Falling trigger event configuration bit of line 14 */
#define EXTI_FT_CFG_FT_CFG15       ((uint32_t)0x00008000U) /* Falling trigger event configuration bit of line 15 */
#define EXTI_FT_CFG_FT_CFG16       ((uint32_t)0x00010000U) /* Falling trigger event configuration bit of line 16 */
#define EXTI_FT_CFG_FT_CFG17       ((uint32_t)0x00020000U) /* Falling trigger event configuration bit of line 17 */
#define EXTI_FT_CFG_FT_CFG18       ((uint32_t)0x00040000U) /* Falling trigger event configuration bit of line 18 */
#define EXTI_FT_CFG_FT_CFG19       ((uint32_t)0x00080000U) /* Falling trigger event configuration bit of line 19 */
#define EXTI_FT_CFG_FT_CFG20       ((uint32_t)0x00100000U) /* Falling trigger event configuration bit of line 20 */

/** Bit definition for EXTI_RT_CFG register **/
#define EXTI_RT_CFG_RT_CFG0        ((uint32_t)0x00000001U) /* Rising trigger event configuration bit of line 0 */
#define EXTI_RT_CFG_RT_CFG1        ((uint32_t)0x00000002U) /* Rising trigger event configuration bit of line 1 */
#define EXTI_RT_CFG_RT_CFG2        ((uint32_t)0x00000004U) /* Rising trigger event configuration bit of line 2 */
#define EXTI_RT_CFG_RT_CFG3        ((uint32_t)0x00000008U) /* Rising trigger event configuration bit of line 3 */
#define EXTI_RT_CFG_RT_CFG4        ((uint32_t)0x00000010U) /* Rising trigger event configuration bit of line 4 */
#define EXTI_RT_CFG_RT_CFG5        ((uint32_t)0x00000020U) /* Rising trigger event configuration bit of line 5 */
#define EXTI_RT_CFG_RT_CFG6        ((uint32_t)0x00000040U) /* Rising trigger event configuration bit of line 6 */
#define EXTI_RT_CFG_RT_CFG7        ((uint32_t)0x00000080U) /* Rising trigger event configuration bit of line 7 */
#define EXTI_RT_CFG_RT_CFG8        ((uint32_t)0x00000100U) /* Rising trigger event configuration bit of line 8 */
#define EXTI_RT_CFG_RT_CFG9        ((uint32_t)0x00000200U) /* Rising trigger event configuration bit of line 9 */
#define EXTI_RT_CFG_RT_CFG10       ((uint32_t)0x00000400U) /* Rising trigger event configuration bit of line 10 */
#define EXTI_RT_CFG_RT_CFG11       ((uint32_t)0x00000800U) /* Rising trigger event configuration bit of line 11 */
#define EXTI_RT_CFG_RT_CFG12       ((uint32_t)0x00001000U) /* Rising trigger event configuration bit of line 12 */
#define EXTI_RT_CFG_RT_CFG13       ((uint32_t)0x00002000U) /* Rising trigger event configuration bit of line 13 */
#define EXTI_RT_CFG_RT_CFG14       ((uint32_t)0x00004000U) /* Rising trigger event configuration bit of line 14 */
#define EXTI_RT_CFG_RT_CFG15       ((uint32_t)0x00008000U) /* Rising trigger event configuration bit of line 15 */
#define EXTI_RT_CFG_RT_CFG16       ((uint32_t)0x00010000U) /* Rising trigger event configuration bit of line 16 */
#define EXTI_RT_CFG_RT_CFG17       ((uint32_t)0x00020000U) /* Rising trigger event configuration bit of line 17 */
#define EXTI_RT_CFG_RT_CFG18       ((uint32_t)0x00040000U) /* Rising trigger event configuration bit of line 18 */
#define EXTI_RT_CFG_RT_CFG19       ((uint32_t)0x00080000U) /* Rising trigger event configuration bit of line 19 */
#define EXTI_RT_CFG_RT_CFG20       ((uint32_t)0x00100000U) /* Rising trigger event configuration bit of line 20 */

/** Bit definition for EXTI_PEND register **/
#define EXTI_PEND_PEND0        ((uint32_t)0x00000001U) /* Pending bit for line 0 */
#define EXTI_PEND_PEND1        ((uint32_t)0x00000002U) /* Pending bit for line 1 */
#define EXTI_PEND_PEND2        ((uint32_t)0x00000004U) /* Pending bit for line 2 */
#define EXTI_PEND_PEND3        ((uint32_t)0x00000008U) /* Pending bit for line 3 */
#define EXTI_PEND_PEND4        ((uint32_t)0x00000010U) /* Pending bit for line 4 */
#define EXTI_PEND_PEND5        ((uint32_t)0x00000020U) /* Pending bit for line 5 */
#define EXTI_PEND_PEND6        ((uint32_t)0x00000040U) /* Pending bit for line 6 */
#define EXTI_PEND_PEND7        ((uint32_t)0x00000080U) /* Pending bit for line 7 */
#define EXTI_PEND_PEND8        ((uint32_t)0x00000100U) /* Pending bit for line 8 */
#define EXTI_PEND_PEND9        ((uint32_t)0x00000200U) /* Pending bit for line 9 */
#define EXTI_PEND_PEND10       ((uint32_t)0x00000400U) /* Pending bit for line 10 */
#define EXTI_PEND_PEND11       ((uint32_t)0x00000800U) /* Pending bit for line 11 */
#define EXTI_PEND_PEND12       ((uint32_t)0x00001000U) /* Pending bit for line 12 */
#define EXTI_PEND_PEND13       ((uint32_t)0x00002000U) /* Pending bit for line 13 */
#define EXTI_PEND_PEND14       ((uint32_t)0x00004000U) /* Pending bit for line 14 */
#define EXTI_PEND_PEND15       ((uint32_t)0x00008000U) /* Pending bit for line 15 */
#define EXTI_PEND_PEND16       ((uint32_t)0x00010000U) /* Pending bit for line 16 */
#define EXTI_PEND_PEND17       ((uint32_t)0x00020000U) /* Pending bit for line 17 */
#define EXTI_PEND_PEND18       ((uint32_t)0x00040000U) /* Pending bit for line 18 */
#define EXTI_PEND_PEND19       ((uint32_t)0x00080000U) /* Pending bit for line 19 */
#define EXTI_PEND_PEND20       ((uint32_t)0x00100000U) /* Pending bit for line 20 */

/** Bit definition for EXTI_SWIE register **/
#define EXTI_SWIE_SWIE0        ((uint32_t)0x00000001U) /* Software Interrupt on line 0 */
#define EXTI_SWIE_SWIE1        ((uint32_t)0x00000002U) /* Software Interrupt on line 1 */
#define EXTI_SWIE_SWIE2        ((uint32_t)0x00000004U) /* Software Interrupt on line 2 */
#define EXTI_SWIE_SWIE3        ((uint32_t)0x00000008U) /* Software Interrupt on line 3 */
#define EXTI_SWIE_SWIE4        ((uint32_t)0x00000010U) /* Software Interrupt on line 4 */
#define EXTI_SWIE_SWIE5        ((uint32_t)0x00000020U) /* Software Interrupt on line 5 */
#define EXTI_SWIE_SWIE6        ((uint32_t)0x00000040U) /* Software Interrupt on line 6 */
#define EXTI_SWIE_SWIE7        ((uint32_t)0x00000080U) /* Software Interrupt on line 7 */
#define EXTI_SWIE_SWIE8        ((uint32_t)0x00000100U) /* Software Interrupt on line 8 */
#define EXTI_SWIE_SWIE9        ((uint32_t)0x00000200U) /* Software Interrupt on line 9 */
#define EXTI_SWIE_SWIE10       ((uint32_t)0x00000400U) /* Software Interrupt on line 10 */
#define EXTI_SWIE_SWIE11       ((uint32_t)0x00000800U) /* Software Interrupt on line 11 */
#define EXTI_SWIE_SWIE12       ((uint32_t)0x00001000U) /* Software Interrupt on line 12 */
#define EXTI_SWIE_SWIE13       ((uint32_t)0x00002000U) /* Software Interrupt on line 13 */
#define EXTI_SWIE_SWIE14       ((uint32_t)0x00004000U) /* Software Interrupt on line 14 */
#define EXTI_SWIE_SWIE15       ((uint32_t)0x00008000U) /* Software Interrupt on line 15 */
#define EXTI_SWIE_SWIE16       ((uint32_t)0x00010000U) /* Software Interrupt on line 16 */
#define EXTI_SWIE_SWIE17       ((uint32_t)0x00020000U) /* Software Interrupt on line 17 */
#define EXTI_SWIE_SWIE18       ((uint32_t)0x00040000U) /* Software Interrupt on line 18 */
#define EXTI_SWIE_SWIE19       ((uint32_t)0x00080000U) /* Software Interrupt on line 19 */
#define EXTI_SWIE_SWIE20       ((uint32_t)0x00100000U) /* Software Interrupt on line 20 */

/** Bit definition for EXTI_TS_SEL register **/
#define EXTI_TSSEL_MASK        ((uint32_t)0x0000000FU) /* Select external interrupt input as the trigger source for timestamp events */


/*** DMA Controller ***/

/** Bit definition for DMA_INTSTS register **/
#define DMA_INTSTS_GLBF1 ((uint32_t)0x00000001U) /* Channel 1 Global interrupt flag */
#define DMA_INTSTS_TXCF1 ((uint32_t)0x00000002U) /* Channel 1 Transfer Complete flag */
#define DMA_INTSTS_HTXF1 ((uint32_t)0x00000004U) /* Channel 1 Half Transfer flag */
#define DMA_INTSTS_ERRF1 ((uint32_t)0x00000008U) /* Channel 1 Transfer Error flag */
#define DMA_INTSTS_GLBF2 ((uint32_t)0x00000010U) /* Channel 2 Global interrupt flag */
#define DMA_INTSTS_TXCF2 ((uint32_t)0x00000020U) /* Channel 2 Transfer Complete flag */
#define DMA_INTSTS_HTXF2 ((uint32_t)0x00000040U) /* Channel 2 Half Transfer flag */
#define DMA_INTSTS_ERRF2 ((uint32_t)0x00000080U) /* Channel 2 Transfer Error flag */
#define DMA_INTSTS_GLBF3 ((uint32_t)0x00000100U) /* Channel 3 Global interrupt flag */
#define DMA_INTSTS_TXCF3 ((uint32_t)0x00000200U) /* Channel 3 Transfer Complete flag */
#define DMA_INTSTS_HTXF3 ((uint32_t)0x00000400U) /* Channel 3 Half Transfer flag */
#define DMA_INTSTS_ERRF3 ((uint32_t)0x00000800U) /* Channel 3 Transfer Error flag */
#define DMA_INTSTS_GLBF4 ((uint32_t)0x00001000U) /* Channel 4 Global interrupt flag */
#define DMA_INTSTS_TXCF4 ((uint32_t)0x00002000U) /* Channel 4 Transfer Complete flag */
#define DMA_INTSTS_HTXF4 ((uint32_t)0x00004000U) /* Channel 4 Half Transfer flag */
#define DMA_INTSTS_ERRF4 ((uint32_t)0x00008000U) /* Channel 4 Transfer Error flag */
#define DMA_INTSTS_GLBF5 ((uint32_t)0x00010000U) /* Channel 5 Global interrupt flag */
#define DMA_INTSTS_TXCF5 ((uint32_t)0x00020000U) /* Channel 5 Transfer Complete flag */
#define DMA_INTSTS_HTXF5 ((uint32_t)0x00040000U) /* Channel 5 Half Transfer flag */
#define DMA_INTSTS_ERRF5 ((uint32_t)0x00080000U) /* Channel 5 Transfer Error flag */

/** Bit definition for DMA_INTCLR register **/
#define DMA_INTCLR_CGLBF1 ((uint32_t)0x00000001U) /* Channel 1 Global interrupt clear */
#define DMA_INTCLR_CTXCF1 ((uint32_t)0x00000002U) /* Channel 1 Transfer Complete clear */
#define DMA_INTCLR_CHTXF1 ((uint32_t)0x00000004U) /* Channel 1 Half Transfer clear */
#define DMA_INTCLR_CERRF1 ((uint32_t)0x00000008U) /* Channel 1 Transfer Error clear */
#define DMA_INTCLR_CGLBF2 ((uint32_t)0x00000010U) /* Channel 2 Global interrupt clear */
#define DMA_INTCLR_CTXCF2 ((uint32_t)0x00000020U) /* Channel 2 Transfer Complete clear */
#define DMA_INTCLR_CHTXF2 ((uint32_t)0x00000040U) /* Channel 2 Half Transfer clear */
#define DMA_INTCLR_CERRF2 ((uint32_t)0x00000080U) /* Channel 2 Transfer Error clear */
#define DMA_INTCLR_CGLBF3 ((uint32_t)0x00000100U) /* Channel 3 Global interrupt clear */
#define DMA_INTCLR_CTXCF3 ((uint32_t)0x00000200U) /* Channel 3 Transfer Complete clear */
#define DMA_INTCLR_CHTXF3 ((uint32_t)0x00000400U) /* Channel 3 Half Transfer clear */
#define DMA_INTCLR_CERRF3 ((uint32_t)0x00000800U) /* Channel 3 Transfer Error clear */
#define DMA_INTCLR_CGLBF4 ((uint32_t)0x00001000U) /* Channel 4 Global interrupt clear */
#define DMA_INTCLR_CTXCF4 ((uint32_t)0x00002000U) /* Channel 4 Transfer Complete clear */
#define DMA_INTCLR_CHTXF4 ((uint32_t)0x00004000U) /* Channel 4 Half Transfer clear */
#define DMA_INTCLR_CERRF4 ((uint32_t)0x00008000U) /* Channel 4 Transfer Error clear */
#define DMA_INTCLR_CGLBF5 ((uint32_t)0x00010000U) /* Channel 5 Global interrupt clear */
#define DMA_INTCLR_CTXCF5 ((uint32_t)0x00020000U) /* Channel 5 Transfer Complete clear */
#define DMA_INTCLR_CHTXF5 ((uint32_t)0x00040000U) /* Channel 5 Half Transfer clear */
#define DMA_INTCLR_CERRF5 ((uint32_t)0x00080000U) /* Channel 5 Transfer Error clear */

/** Bit definition for DMA_CHCFG1 register **/
#define DMA_CHCFG1_CHEN      ((uint16_t)0x0001U) /* Channel enable */
#define DMA_CHCFG1_TXCIE     ((uint16_t)0x0002U) /* Transfer complete interrupt enable */
#define DMA_CHCFG1_HTXIE     ((uint16_t)0x0004U) /* Half Transfer interrupt enable */
#define DMA_CHCFG1_ERRIE     ((uint16_t)0x0008U) /* Transfer error interrupt enable */
#define DMA_CHCFG1_DIR       ((uint16_t)0x0010U) /* Data transfer direction */
#define DMA_CHCFG1_CIRC      ((uint16_t)0x0020U) /* Circular mode */
#define DMA_CHCFG1_PINC      ((uint16_t)0x0040U) /* Peripheral increment mode */
#define DMA_CHCFG1_MINC      ((uint16_t)0x0080U) /* Memory increment mode */

#define DMA_CHCFG1_PSIZE     ((uint16_t)0x0300U) /* PSIZE[1:0] bits (Peripheral size) */
#define DMA_CHCFG1_PSIZE_0   ((uint16_t)0x0100U) /* Bit 0 */
#define DMA_CHCFG1_PSIZE_1   ((uint16_t)0x0200U) /* Bit 1 */

#define DMA_CHCFG1_MSIZE     ((uint16_t)0x0C00U) /* MSIZE[1:0] bits (Memory size) */
#define DMA_CHCFG1_MSIZE_0   ((uint16_t)0x0400U) /* Bit 0 */
#define DMA_CHCFG1_MSIZE_1   ((uint16_t)0x0800U) /* Bit 1 */

#define DMA_CHCFG1_PRIOLVL   ((uint16_t)0x3000U) /* PRIOLVL[1:0] bits(Channel Priority level) */
#define DMA_CHCFG1_PRIOLVL_0 ((uint16_t)0x1000U) /* Bit 0 */
#define DMA_CHCFG1_PRIOLVL_1 ((uint16_t)0x2000U) /* Bit 1 */

#define DMA_CHCFG1_MEM2MEM   ((uint16_t)0x4000U) /* Memory to memory mode */

/** Bit definition for DMA_CHCFG2 register **/
#define DMA_CHCFG2_CHEN      ((uint16_t)0x0001U) /* Channel enable */
#define DMA_CHCFG2_TXCIE     ((uint16_t)0x0002U) /* Transfer complete interrupt enable */
#define DMA_CHCFG2_HTXIE     ((uint16_t)0x0004U) /* Half Transfer interrupt enable */
#define DMA_CHCFG2_ERRIE     ((uint16_t)0x0008U) /* Transfer error interrupt enable */
#define DMA_CHCFG2_DIR       ((uint16_t)0x0010U) /* Data transfer direction */
#define DMA_CHCFG2_CIRC      ((uint16_t)0x0020U) /* Circular mode */
#define DMA_CHCFG2_PINC      ((uint16_t)0x0040U) /* Peripheral increment mode */
#define DMA_CHCFG2_MINC      ((uint16_t)0x0080U) /* Memory increment mode */

#define DMA_CHCFG2_PSIZE     ((uint16_t)0x0300U) /* PSIZE[1:0] bits (Peripheral size) */
#define DMA_CHCFG2_PSIZE_0   ((uint16_t)0x0100U) /* Bit 0 */
#define DMA_CHCFG2_PSIZE_1   ((uint16_t)0x0200U) /* Bit 1 */

#define DMA_CHCFG2_MSIZE     ((uint16_t)0x0C00U) /* MSIZE[1:0] bits (Memory size) */
#define DMA_CHCFG2_MSIZE_0   ((uint16_t)0x0400U) /* Bit 0 */
#define DMA_CHCFG2_MSIZE_1   ((uint16_t)0x0800U) /* Bit 1 */

#define DMA_CHCFG2_PRIOLVL   ((uint16_t)0x3000U) /* PRIOLVL[1:0] bits (Channel Priority level) */
#define DMA_CHCFG2_PRIOLVL_0 ((uint16_t)0x1000U) /* Bit 0 */
#define DMA_CHCFG2_PRIOLVL_1 ((uint16_t)0x2000U) /* Bit 1 */

#define DMA_CHCFG2_MEM2MEM   ((uint16_t)0x4000U) /* Memory to memory mode */

/** Bit definition for DMA_CHCFG3 register **/
#define DMA_CHCFG3_CHEN      ((uint16_t)0x0001U) /* Channel enable */
#define DMA_CHCFG3_TXCIE     ((uint16_t)0x0002U) /* Transfer complete interrupt enable */
#define DMA_CHCFG3_HTXIE     ((uint16_t)0x0004U) /* Half Transfer interrupt enable */
#define DMA_CHCFG3_ERRIE     ((uint16_t)0x0008U) /* Transfer error interrupt enable */
#define DMA_CHCFG3_DIR       ((uint16_t)0x0010U) /* Data transfer direction */
#define DMA_CHCFG3_CIRC      ((uint16_t)0x0020U) /* Circular mode */
#define DMA_CHCFG3_PINC      ((uint16_t)0x0040U) /* Peripheral increment mode */
#define DMA_CHCFG3_MINC      ((uint16_t)0x0080U) /* Memory increment mode */

#define DMA_CHCFG3_PSIZE     ((uint16_t)0x0300U) /* PSIZE[1:0] bits (Peripheral size) */
#define DMA_CHCFG3_PSIZE_0   ((uint16_t)0x0100U) /* Bit 0 */
#define DMA_CHCFG3_PSIZE_1   ((uint16_t)0x0200U) /* Bit 1 */

#define DMA_CHCFG3_MSIZE     ((uint16_t)0x0C00U) /* MSIZE[1:0] bits (Memory size) */
#define DMA_CHCFG3_MSIZE_0   ((uint16_t)0x0400U) /* Bit 0 */
#define DMA_CHCFG3_MSIZE_1   ((uint16_t)0x0800U) /* Bit 1 */

#define DMA_CHCFG3_PRIOLVL   ((uint16_t)0x3000U) /* PRIOLVL[1:0] bits (Channel Priority level) */
#define DMA_CHCFG3_PRIOLVL_0 ((uint16_t)0x1000U) /* Bit 0 */
#define DMA_CHCFG3_PRIOLVL_1 ((uint16_t)0x2000U) /* Bit 1 */

#define DMA_CHCFG3_MEM2MEM   ((uint16_t)0x4000U) /* Memory to memory mode */

/** Bit definition for DMA_CHCFG4 register **/
#define DMA_CHCFG4_CHEN      ((uint16_t)0x0001U) /* Channel enable */
#define DMA_CHCFG4_TXCIE     ((uint16_t)0x0002U) /* Transfer complete interrupt enable */
#define DMA_CHCFG4_HTXIE     ((uint16_t)0x0004U) /* Half Transfer interrupt enable */
#define DMA_CHCFG4_ERRIE     ((uint16_t)0x0008U) /* Transfer error interrupt enable */
#define DMA_CHCFG4_DIR       ((uint16_t)0x0010U) /* Data transfer direction */
#define DMA_CHCFG4_CIRC      ((uint16_t)0x0020U) /* Circular mode */
#define DMA_CHCFG4_PINC      ((uint16_t)0x0040U) /* Peripheral increment mode */
#define DMA_CHCFG4_MINC      ((uint16_t)0x0080U) /* Memory increment mode */

#define DMA_CHCFG4_PSIZE     ((uint16_t)0x0300U) /* PSIZE[1:0] bits (Peripheral size) */
#define DMA_CHCFG4_PSIZE_0   ((uint16_t)0x0100U) /* Bit 0 */
#define DMA_CHCFG4_PSIZE_1   ((uint16_t)0x0200U) /* Bit 1 */

#define DMA_CHCFG4_MSIZE     ((uint16_t)0x0C00U) /* MSIZE[1:0] bits (Memory size) */
#define DMA_CHCFG4_MSIZE_0   ((uint16_t)0x0400U) /* Bit 0 */
#define DMA_CHCFG4_MSIZE_1   ((uint16_t)0x0800U) /* Bit 1 */

#define DMA_CHCFG4_PRIOLVL   ((uint16_t)0x3000U) /* PRIOLVL[1:0] bits (Channel Priority level) */
#define DMA_CHCFG4_PRIOLVL_0 ((uint16_t)0x1000U) /* Bit 0 */
#define DMA_CHCFG4_PRIOLVL_1 ((uint16_t)0x2000U) /* Bit 1 */

#define DMA_CHCFG4_MEM2MEM   ((uint16_t)0x4000U) /* Memory to memory mode */

/** Bit definition for DMA_CHCFG5 register **/
#define DMA_CHCFG5_CHEN      ((uint16_t)0x0001U) /* Channel enable */
#define DMA_CHCFG5_TXCIE     ((uint16_t)0x0002U) /* Transfer complete interrupt enable */
#define DMA_CHCFG5_HTXIE     ((uint16_t)0x0004U) /* Half Transfer interrupt enable */
#define DMA_CHCFG5_ERRIE     ((uint16_t)0x0008U) /* Transfer error interrupt enable */
#define DMA_CHCFG5_DIR       ((uint16_t)0x0010U) /* Data transfer direction */
#define DMA_CHCFG5_CIRC      ((uint16_t)0x0020U) /* Circular mode */
#define DMA_CHCFG5_PINC      ((uint16_t)0x0040U) /* Peripheral increment mode */
#define DMA_CHCFG5_MINC      ((uint16_t)0x0080U) /* Memory increment mode */

#define DMA_CHCFG5_PSIZE     ((uint16_t)0x0300U) /* PSIZE[1:0] bits (Peripheral size) */
#define DMA_CHCFG5_PSIZE_0   ((uint16_t)0x0100U) /* Bit 0 */
#define DMA_CHCFG5_PSIZE_1   ((uint16_t)0x0200U) /* Bit 1 */

#define DMA_CHCFG5_MSIZE     ((uint16_t)0x0C00U) /* MSIZE[1:0] bits (Memory size) */
#define DMA_CHCFG5_MSIZE_0   ((uint16_t)0x0400U) /* Bit 0 */
#define DMA_CHCFG5_MSIZE_1   ((uint16_t)0x0800U) /* Bit 1 */

#define DMA_CHCFG5_PRIOLVL   ((uint16_t)0x3000U) /* PRIOLVL[1:0] bits (Channel Priority level) */
#define DMA_CHCFG5_PRIOLVL_0 ((uint16_t)0x1000U) /* Bit 0 */
#define DMA_CHCFG5_PRIOLVL_1 ((uint16_t)0x2000U) /* Bit 1 */

#define DMA_CHCFG5_MEM2MEM   ((uint16_t)0x4000U) /* Memory to memory mode */

/** Bit definition for DMA_TXNUM1 register **/
#define DMA_TXNUM1_NDTX ((uint16_t)0xFFFFU) /* CH1 number of data to transfer */

/** Bit definition for DMA_TXNUM2 register **/
#define DMA_TXNUM2_NDTX ((uint16_t)0xFFFFU) /* CH2 number of data to transfer */

/** Bit definition for DMA_TXNUM3 register **/
#define DMA_TXNUM3_NDTX ((uint16_t)0xFFFFU) /* CH3 number of data to transfer */

/** Bit definition for DMA_TXNUM4 register **/
#define DMA_TXNUM4_NDTX ((uint16_t)0xFFFFU) /* CH4 number of data to transfer */

/** Bit definition for DMA_TXNUM5 register **/
#define DMA_TXNUM5_NDTX ((uint16_t)0xFFFFU) /* CH5 number of data to transfer */

/** Bit definition for DMA_PADDR1 register **/
#define DMA_PADDR1_ADDR ((uint32_t)0xFFFFFFFFU) /* Peripheral Address of CH1 */

/** Bit definition for DMA_PADDR2 register **/
#define DMA_PADDR2_ADDR ((uint32_t)0xFFFFFFFFU) /* Peripheral Address of CH2 */

/** Bit definition for DMA_PADDR3 register **/
#define DMA_PADDR3_ADDR ((uint32_t)0xFFFFFFFFU) /* Peripheral Address of CH3 */

/** Bit definition for DMA_PADDR4 register **/
#define DMA_PADDR4_ADDR ((uint32_t)0xFFFFFFFFU) /* Peripheral Address of CH4 */

/** Bit definition for DMA_PADDR5 register **/
#define DMA_PADDR5_ADDR ((uint32_t)0xFFFFFFFFU) /* Peripheral Address of CH5 */

/** Bit definition for DMA_MADDR1 register **/
#define DMA_MADDR1_ADDR ((uint32_t)0xFFFFFFFFU) /* Memory Address of CH1 */

/** Bit definition for DMA_MADDR2 register **/
#define DMA_MADDR2_ADDR ((uint32_t)0xFFFFFFFFU) /* Memory Address of CH2 */

/** Bit definition for DMA_MADDR3 register **/
#define DMA_MADDR3_ADDR ((uint32_t)0xFFFFFFFFU) /* Memory Address of CH3 */

/** Bit definition for DMA_MADDR4 register **/
#define DMA_MADDR4_ADDR ((uint32_t)0xFFFFFFFFU) /* Memory Address of CH4 */

/** Bit definition for DMA_MADDR5 register **/
#define DMA_MADDR5_ADDR ((uint32_t)0xFFFFFFFFU) /* Memory Address of CH5 */

/** Bit definition for DMA_CHSELx(x=1~5) register  ***/
#define DMA_CHSEL_CH_SEL   ((uint32_t)0x0000003FU) /* CH_SEL[5:0]: Channel request select */
#define DMA_CHSEL_CH_SEL_0 ((uint32_t)0x00000001U) /* bit0 */
#define DMA_CHSEL_CH_SEL_1 ((uint32_t)0x00000002U) /* bit1 */
#define DMA_CHSEL_CH_SEL_2 ((uint32_t)0x00000004U) /* bit2 */
#define DMA_CHSEL_CH_SEL_3 ((uint32_t)0x00000008U) /* bit3 */
#define DMA_CHSEL_CH_SEL_4 ((uint32_t)0x00000010U) /* bit4 */
#define DMA_CHSEL_CH_SEL_5 ((uint32_t)0x00000020U) /* bit5 */

//*** Analog to Digital Converter ***/

/** Bit definition for ADC_STS register **/
#define ADC_STS_AWDG                        ((uint8_t)0x01U) /* Analog watchdog flag */
#define ADC_STS_ENDC                        ((uint8_t)0x02U) /* End of conversion */
#define ADC_STS_STR                         ((uint8_t)0x04U) /* Regular channel Start flag */
#define ADC_STS_ENDCA                       ((uint8_t)0x08U) /* Regular channel any end flag */

/** Bit definition for ADC_CTRL1 register **/
#define ADC_CTRL1_AWDGCH                    ((uint32_t)0x0000001FU) /* AWDG_CH[4:0] bits (Analog watchdog channel select bits) */
#define ADC_CTRL1_AWDGCH_0                  ((uint32_t)0x00000001U) /* Bit 0 */
#define ADC_CTRL1_AWDGCH_1                  ((uint32_t)0x00000002U) /* Bit 1 */
#define ADC_CTRL1_AWDGCH_2                  ((uint32_t)0x00000004U) /* Bit 2 */
#define ADC_CTRL1_AWDGCH_3                  ((uint32_t)0x00000008U) /* Bit 3 */
#define ADC_CTRL1_AWDGCH_4                  ((uint32_t)0x00000010U) /* Bit 4 */

#define ADC_CTRL1_ENDCIEN                   ((uint32_t)0x00000020U) /* Interrupt enable for EOC */
#define ADC_CTRL1_AWDGIEN                   ((uint32_t)0x00000040U) /* Analog Watchdog interrupt enable */
#define ADC_CTRL1_AWDGSGLEN                 ((uint32_t)0x00000080U) /* Enable the watchdog on a single channel in scan mode */
#define ADC_CTRL1_AWDGERCH                  ((uint32_t)0x00000100U) /* Analog watchdog enable on regular channels */
#define ADC_CTRL1_REFSEL                  	((uint32_t)0x00000400U) /* ADC Reference Source Select */

/** Bit definition for ADC_CTRL2 register **/
#define ADC_CTRL2_ON                        ((uint32_t)0x00000001U) /* A/D Converter ON / OFF */
#define ADC_CTRL2_CTU                       ((uint32_t)0x00000002U) /* Continuous Conversion */
#define ADC_CTRL2_ALIG                      ((uint32_t)0x00000004U) /* Data Alignment */

#define ADC_CTRL2_EXTRSEL                   ((uint32_t)0x00000078U) /* EXTSEL[3:0] bits (External Event Select for regular group) */
#define ADC_CTRL2_EXTRSEL_0                 ((uint32_t)0x00000080U) /* Bit 0 */
#define ADC_CTRL2_EXTRSEL_1                 ((uint32_t)0x00000010U) /* Bit 1 */
#define ADC_CTRL2_EXTRSEL_2                 ((uint32_t)0x00080020U) /* Bit 2 */
#define ADC_CTRL2_EXTRSEL_3                 ((uint32_t)0x00080040U) /* Bit 3 */

#define ADC_CTRL2_EXTRTRIG                  ((uint32_t)0x00000080U) /* External Trigger Conversion mode for regular channels */
#define ADC_CTRL2_SWSTRRCH                  ((uint32_t)0x00000100U) /* Start Conversion of regular channels */

#define ADC_CTRL2_LEN                       ((uint32_t)0x00000E00U) /* LEN[2:0] bits (Regular Sequence length) */
#define ADC_CTRL2_LEN_0                     ((uint32_t)0x00000200U) /* Bit 0 */
#define ADC_CTRL2_LEN_1                     ((uint32_t)0x00000400U) /* Bit 1 */
#define ADC_CTRL2_LEN_2                     ((uint32_t)0x00000800U) /* Bit 2 */

#define ADC_CTRL2_SCANMD                    ((uint32_t)0x00001000U) /* Scan mode */
#define ADC_CTRL2_ENDMA                     ((uint32_t)0x00002000U) /* DMA function switch */
#define ADC_CTRL2_TEMPEN                    ((uint32_t)0x00004000U) /* Temperature sensor switch */

/** Bit definition for ADC_CTRL3 register **/
#define ADC_CTRL3_VREFEN                    ((uint16_t)0x0002U) /* ADC VREFINT_EN */
#define ADC_CTRL3_VREFRDY                   ((uint16_t)0x0004U) /* ADC VREFINT_READY */
#define ADC_CTRL3_RDY                       ((uint16_t)0x0008U) /* ADC Ready */
#define ADC_CTRL3_PDRDY                     ((uint16_t)0x0010U) /* ADC Power_down Ready */
#define ADC_CTRL3_ENDCAIEN                  ((uint16_t)0x0020U) /* Interrupt enable for any regular channels */

/** Bit definition for ADC_SAMPT register **/
#define ADC_SAMPT_SAMP                      ((uint32_t)0x00000001FU) /* SMP10[4:0] bits (Channel Sample time selection) */
#define ADC_SAMPT_SAMP_0                    ((uint32_t)0x00000001U)  /* Bit 0 */
#define ADC_SAMPT_SAMP_1                    ((uint32_t)0x00000002U)  /* Bit 1 */
#define ADC_SAMPT_SAMP_2                    ((uint32_t)0x00000004U)  /* Bit 2 */
#define ADC_SAMPT_SAMP_3                    ((uint32_t)0x00000008U)  /* Bit 3 */
#define ADC_SAMPT_SAMP_4                    ((uint32_t)0x00000010U)  /* Bit 4 */

/** Bit definition for ADC_WDGHIGH register **/
#define ADC_WDGHIGH_HTH                     ((uint16_t)0x0FFFU)  /* Analog watchdog high threshold */

/** Bit definition for ADC_WDGLOW register **/
#define ADC_WDGLOW_LTH                      ((uint16_t)0x0FFFU)  /* Analog watchdog low threshold */

/** Bit definition for ADC_DATA0 register **/
#define ADC_DAT0_DAT                        ((uint32_t)0x0000FFFFU) /* Regular data */
#define ADC_DAT0_SEQ0                       ((uint32_t)0x001F0000U) /* channel seqence of conversion */
#define ADC_DAT0_SEQ0_0                     ((uint32_t)0x00010000U) /* Bit 0 */
#define ADC_DAT0_SEQ0_1                     ((uint32_t)0x00020000U) /* Bit 1 */
#define ADC_DAT0_SEQ0_2                     ((uint32_t)0x00040000U) /* Bit 2 */
#define ADC_DAT0_SEQ0_3                     ((uint32_t)0x00080000U) /* Bit 3 */
#define ADC_DAT0_SEQ0_4                     ((uint32_t)0x00100000U) /* Bit 4 */

/** Bit definition for ADC_DATA1 register **/
#define ADC_DAT1_DAT                        ((uint32_t)0x0000FFFFU) /* Regular data */
#define ADC_DAT1_SEQ1                       ((uint32_t)0x001F0000U) /* channel seqence of conversion */
#define ADC_DAT1_SEQ1_0                     ((uint32_t)0x00010000U) /* Bit 0 */
#define ADC_DAT1_SEQ1_1                     ((uint32_t)0x00020000U) /* Bit 1 */
#define ADC_DAT1_SEQ1_2                     ((uint32_t)0x00040000U) /* Bit 2 */
#define ADC_DAT1_SEQ1_3                     ((uint32_t)0x00080000U) /* Bit 3 */
#define ADC_DAT0_SEQ1_4                     ((uint32_t)0x00100000U) /* Bit 4 */

/** Bit definition for ADC_DATA2 register **/
#define ADC_DAT2_DAT                        ((uint32_t)0x0000FFFFU) /* Regular data */
#define ADC_DAT2_SEQ2                       ((uint32_t)0x001F0000U) /* channel seqence of conversion */
#define ADC_DAT2_SEQ2_0                     ((uint32_t)0x00010000U) /* Bit 0 */
#define ADC_DAT2_SEQ2_1                     ((uint32_t)0x00020000U) /* Bit 1 */
#define ADC_DAT2_SEQ2_2                     ((uint32_t)0x00040000U) /* Bit 2 */
#define ADC_DAT2_SEQ2_3                     ((uint32_t)0x00080000U) /* Bit 3 */
#define ADC_DAT0_SEQ2_4                     ((uint32_t)0x00100000U) /* Bit 4 */

/** Bit definition for ADC_DATA3 register **/
#define ADC_DAT3_DAT                        ((uint32_t)0x0000FFFFU) /* Regular data */
#define ADC_DAT3_SEQ3                       ((uint32_t)0x001F0000U) /* channel seqence of conversion */
#define ADC_DAT3_SEQ3_0                     ((uint32_t)0x00010000U) /* Bit 0 */
#define ADC_DAT3_SEQ3_1                     ((uint32_t)0x00020000U) /* Bit 1 */
#define ADC_DAT3_SEQ3_2                     ((uint32_t)0x00040000U) /* Bit 2 */
#define ADC_DAT3_SEQ3_3                     ((uint32_t)0x00080000U) /* Bit 3 */
#define ADC_DAT3_SEQ0_4                     ((uint32_t)0x00100000U) /* Bit 4 */

/** Bit definition for ADC_DATA4 register **/
#define ADC_DAT4_DAT                        ((uint32_t)0x0000FFFFU) /* Regular data */
#define ADC_DAT4_SEQ4                       ((uint32_t)0x001F0000U) /* channel seqence of conversion */
#define ADC_DAT4_SEQ4_0                     ((uint32_t)0x00010000U) /* Bit 0 */
#define ADC_DAT4_SEQ4_1                     ((uint32_t)0x00020000U) /* Bit 1 */
#define ADC_DAT4_SEQ4_2                     ((uint32_t)0x00040000U) /* Bit 2 */
#define ADC_DAT4_SEQ4_3                     ((uint32_t)0x00080000U) /* Bit 3 */
#define ADC_DAT4_SEQ0_4                     ((uint32_t)0x00100000U) /* Bit 4 */
/***LCD Controller ***/

/** Bit definition for LCD_CTRL register **/
#define LCD_CTRL_BUFEN              ((uint32_t)0x00000100U)          /* High driving capacity buffer enable bit*/

#define LCD_CTRL_BIAS               ((uint32_t)0x00000060U)          /* Bias[1:0] bits (Bias selection) */
#define LCD_CTRL_BIAS_0             ((uint32_t)0x00000020U)          /* Bit 0 */
#define LCD_CTRL_BIAS_1             ((uint32_t)0x00000040U)          /* Bit 1 */

#define LCD_CTRL_DUTY               ((uint32_t)0x0000001CU)          /* DUTY[2:0] bits (Duty selection) */
#define LCD_CTRL_DUTY_0             ((uint32_t)0x00000004U)          /* Bit 0 */
#define LCD_CTRL_DUTY_1             ((uint32_t)0x00000008U)          /* Bit 1 */
#define LCD_CTRL_DUTY_2             ((uint32_t)0x00000010U)          /* Bit 2 */

#define LCD_CTRL_VSEL               ((uint32_t)0x00000002U)          /* LCD driver contrast control bit */
#define LCD_CTRL_EN                 ((uint32_t)0x00000001U)          /* LCD controller enable bit */

/** Bit definition for LCD_FCTRL register **/
#define LCD_FCTRL_PRES              ((uint32_t)0x07800000U)          /* 4-bit prescaler bit*/
#define LCD_FCTRL_PRES_0            ((uint32_t)0x00800000U)
#define LCD_FCTRL_PRES_1            ((uint32_t)0x01000000U)
#define LCD_FCTRL_PRES_2            ((uint32_t)0x02000000U)
#define LCD_FCTRL_PRES_3            ((uint32_t)0x04000000U)

#define LCD_FCTRL_DIV               ((uint32_t)0x00780000U)          /* DIV clock divider bit*/
#define LCD_FCTRL_DIV_0             ((uint32_t)0x00080000U)
#define LCD_FCTRL_DIV_1             ((uint32_t)0x00100000U)
#define LCD_FCTRL_DIV_2             ((uint32_t)0x00200000U)
#define LCD_FCTRL_DIV_3             ((uint32_t)0x00400000U)

#define LCD_FCTRL_BLINK             ((uint32_t)0x00060000U)          /* Blink mode selection bit*/
#define LCD_FCTRL_BLINK_0           ((uint32_t)0x00020000U)
#define LCD_FCTRL_BLINK_1           ((uint32_t)0x00040000U)

#define LCD_FCTRL_BLINKF            ((uint32_t)0x0001C000U)          /* Blink frequency selection bit*/
#define LCD_FCTRL_BLINKF_0          ((uint32_t)0x00004000U)
#define LCD_FCTRL_BLINKF_1          ((uint32_t)0x00008000U)
#define LCD_FCTRL_BLINKF_2          ((uint32_t)0x00010000U)

#define LCD_FCTRL_CONTRAST          ((uint32_t)0x00003C00U)          /* Contrast Control bit*/
#define LCD_FCTRL_CONTRAST_0        ((uint32_t)0x00000400U)
#define LCD_FCTRL_CONTRAST_1        ((uint32_t)0x00000800U)
#define LCD_FCTRL_CONTRAST_2        ((uint32_t)0x00001000U)
#define LCD_FCTRL_CONTRAST_3        ((uint32_t)0x00002000U)

#define LCD_FCTRL_DEAD              ((uint32_t)0x00000380U)          /* Dead time duration bit*/
#define LCD_FCTRL_DEAD_0            ((uint32_t)0x00000080U)
#define LCD_FCTRL_DEAD_1            ((uint32_t)0x00000100U)
#define LCD_FCTRL_DEAD_2            ((uint32_t)0x00000200U)

#define LCD_FCTRL_PULSEON           ((uint32_t)0x00000070U)          /* Pulse on duration bit*/
#define LCD_FCTRL_PULSEON_0         ((uint32_t)0x00000010U) 
#define LCD_FCTRL_PULSEON_1         ((uint32_t)0x00000020U)
#define LCD_FCTRL_PULSEON_2         ((uint32_t)0x00000040U)

#define LCD_FCTRL_UDDIE             ((uint32_t)0x00000008U)          /* Update display done interrupt enable bit*/
#define LCD_FCTRL_SOFIE             ((uint32_t)0x00000002U)          /* Start of frame interrupt enable bit */
#define LCD_FCTRL_HDEN              ((uint32_t)0x00000001U)          /* High drive enable bit */

/** Bit definition for LCD_STS register **/
#define LCD_STS_FCRSF               ((uint32_t)0x00000020U)          /* LCD Frame Control Register Synchronization flag bit*/
#define LCD_STS_RDY                 ((uint32_t)0x00000010U)          /* VLCD Ready Flag bit*/
#define LCD_STS_UDD                 ((uint32_t)0x00000008U)          /* Update Display Done bit*/
#define LCD_STS_UDR                 ((uint32_t)0x00000004U)          /* Update Display Request bit*/
#define LCD_STS_SOF                 ((uint32_t)0x00000002U)          /* Start of Frame flag*/
#define LCD_STS_ENSTS               ((uint32_t)0x00000001U)          /* LCD state bit*/

/** Bit definition for LCD_CLR register **/
#define LCD_CLR_UDDCLR              ((uint32_t)0x00000008U)          /* Update display done clear bit*/
#define LCD_CLR_SOFCLR              ((uint32_t)0x00000002U)          /* Start of frame flag clear bit*/

/** Bit definition for LCD_RAM register **/
#define LCD_RAM_SEG_DATA_RAM1_Msk           ((uint32_t)0xFFFFFFFFULU)
#define LCD_RAM_SEG_DATA_RAM2_Msk           ((uint32_t)0x0000001FULU)


/***  Comparators Peripheral Interface ***/
/** COMP1_CTRL register **/
#define COMP1_CTRL_EN        ((uint32_t)0x00000001U)     /* Comparator_1 enable */

#define COMP1_CTRL_INMSEL    ((uint32_t)0x0000001EU)     /* Inverting input select of Comparator_1 */
#define COMP1_CTRL_INMSEL_0  ((uint32_t)0x00000002U)     /* Bit 0 */
#define COMP1_CTRL_INMSEL_1  ((uint32_t)0x00000004U)     /* Bit 1 */
#define COMP1_CTRL_INMSEL_2  ((uint32_t)0x00000008U)     /* Bit 2 */
#define COMP1_CTRL_INMSEL_3  ((uint32_t)0x00000010U)     /* Bit 3 */

#define COMP1_CTRL_INPSEL    ((uint32_t)0x000000E0U)     /* Non inverting input select of Comparator_1 */
#define COMP1_CTRL_INPSEL_0  ((uint32_t)0x00000020U)     /* Bit 0 */
#define COMP1_CTRL_INPSEL_1  ((uint32_t)0x00000040U)     /* Bit 1 */
#define COMP1_CTRL_INPSEL_2  ((uint32_t)0x00000080U)     /* Bit 2 */

#define COMP1_CTRL_OUTSEL    ((uint32_t)0x00000F00U)     /* Output select of Comparator_1 */
#define COMP1_CTRL_OUTSEL_0  ((uint32_t)0x00000100U)     /* Bit 0 */
#define COMP1_CTRL_OUTSEL_1  ((uint32_t)0x00000200U)     /* Bit 1 */ 
#define COMP1_CTRL_OUTSEL_2  ((uint32_t)0x00000400U)     /* Bit 2 */ 
#define COMP1_CTRL_OUTSEL_3  ((uint32_t)0x00000800U)     /* Bit 3 */ 
 
#define COMP1_CTRL_POL       ((uint32_t)0x00001000U)     /* Output polarity select of Comparator_1 */

#define COMP1_CTRL_HYST      ((uint32_t)0x00006000U)     /* Hysteresis level select of Comparator_1 */
#define COMP1_CTRL_HYST_0    ((uint32_t)0x00002000U)     /* Bit 0 */
#define COMP1_CTRL_HYST_1    ((uint32_t)0x00004000U)     /* Bit 1 */

#define COMP1_CTRL_BLKING    ((uint32_t)0x00038000U)     /* Blanking source select of Comparator_1 */
#define COMP1_CTRL_BLKING_0  ((uint32_t)0x00008000U)     /* Bit 0 */
#define COMP1_CTRL_BLKING_1  ((uint32_t)0x00010000U)     /* Bit 1 */
#define COMP1_CTRL_BLKING_2  ((uint32_t)0x00020000U)     /* Bit 2 */

#define COMP1_CTRL_OUT       ((uint32_t)0x00040000U)     /* Output state of Comparator_1 */

#define COMP1_CTRL_FILP_OUT ((uint32_t)0x00080000U)     /* Output state of Comparator_1 Fiter */

/** COMP1_FILC register **/
#define COMP1_FILC_FILEN     ((uint32_t)0x00000001U)     /* Comparator_1 filter enable */
#define COMP1_FILC_THRESH    ((uint32_t)0x0000003EU)     /* Comparator_1 filter threshold size */
#define COMP1_FILC_SAMPW     ((uint32_t)0x000007C0U)     /* Comparator_1 filter window size */

/** COMP1_FILP register **/
#define COMP1_FILP_CLKPSC    ((uint32_t)0x0000FFFFU)     /* Comparator_1 filter sample clock prescale */

/** COMP2_CTRL register **/
#define COMP2_CTRL_EN        ((uint32_t)0x00000001U)     /* Comparator_2 enable */

#define COMP2_CTRL_INMSEL    ((uint32_t)0x0000001EU)     /* Inverting input select of Comparator_2 */
#define COMP2_CTRL_INMSEL_0  ((uint32_t)0x00000002U)     /* Bit 0 */
#define COMP2_CTRL_INMSEL_1  ((uint32_t)0x00000004U)     /* Bit 1 */
#define COMP2_CTRL_INMSEL_2  ((uint32_t)0x00000008U)     /* Bit 2 */
#define COMP2_CTRL_INMSEL_3  ((uint32_t)0x00000010U)     /* Bit 3 */

#define COMP2_CTRL_INPSEL    ((uint32_t)0x000000E0U)     /* Non inverting input select of Comparator_2 */
#define COMP2_CTRL_INPSEL_0  ((uint32_t)0x00000020U)     /* Bit 0 */
#define COMP2_CTRL_INPSEL_1  ((uint32_t)0x00000040U)     /* Bit 1 */
#define COMP2_CTRL_INPSEL_2  ((uint32_t)0x00000080U)     /* Bit 2 */

#define COMP2_CTRL_OUTSEL    ((uint32_t)0x00000F00U)     /* Output select of Comparator_2 */
#define COMP2_CTRL_OUTSEL_0  ((uint32_t)0x00000100U)     /* Bit 0 */
#define COMP2_CTRL_OUTSEL_1  ((uint32_t)0x00000200U)     /* Bit 1 */ 
#define COMP2_CTRL_OUTSEL_2  ((uint32_t)0x00000400U)     /* Bit 2 */ 
#define COMP2_CTRL_OUTSEL_3  ((uint32_t)0x00000800U)     /* Bit 3 */ 
 
#define COMP2_CTRL_POL       ((uint32_t)0x00001000U)     /* Output polarity select of Comparator_2 */

#define COMP2_CTRL_HYST      ((uint32_t)0x00006000U)     /* Hysteresis level select of Comparator_2 */
#define COMP2_CTRL_HYST_0    ((uint32_t)0x00002000U)     /* Bit 0 */
#define COMP2_CTRL_HYST_1    ((uint32_t)0x00004000U)     /* Bit 1 */

#define COMP2_CTRL_BLKING    ((uint32_t)0x00038000U)     /* Blanking source select of Comparator_2 */
#define COMP2_CTRL_BLKING_0  ((uint32_t)0x00008000U)     /* Bit 0 */
#define COMP2_CTRL_BLKING_1  ((uint32_t)0x00010000U)     /* Bit 1 */
#define COMP2_CTRL_BLKING_2  ((uint32_t)0x00020000U)     /* Bit 2 */

#define COMP2_CTRL_OUT       ((uint32_t)0x00040000U)     /* Output state of Comparator_2 */

#define COMP2_CTRL_FILP_OUT  ((uint32_t)0x00080000U)     /* Output state of Comparator_2 Fiter */

/** COMP2_FILC register **/
#define COMP2_FILC_FILEN     ((uint32_t)0x00000001U)     /* Comparator_2 filter enable */
#define COMP2_FILC_THRESH    ((uint32_t)0x0000003EU)     /* Comparator_2 filter threshold size */
#define COMP2_FILC_SAMPW     ((uint32_t)0x000007C0U)     /* Comparator_2 filter window size */

/** COMP2_FILP register **/
#define COMP2_FILP_CLKPSC    ((uint32_t)0x0000FFFFU)     /* Comparator_2 filter sample clock prescale */

/** COMP3_CTRL register **/
#define COMP3_CTRL_EN        ((uint32_t)0x00000001U)     /* Comparator_3 enable */

#define COMP3_CTRL_INMSEL    ((uint32_t)0x0000001EU)     /* Inverting input select of Comparator_3 */
#define COMP3_CTRL_INMSEL_0  ((uint32_t)0x00000002U)     /* Bit 0 */
#define COMP3_CTRL_INMSEL_1  ((uint32_t)0x00000004U)     /* Bit 1 */
#define COMP3_CTRL_INMSEL_2  ((uint32_t)0x00000008U)     /* Bit 2 */
#define COMP3_CTRL_INMSEL_3  ((uint32_t)0x00000010U)     /* Bit 3 */

#define COMP3_CTRL_INPSEL    ((uint32_t)0x000000E0U)     /* Non inverting input select of Comparator_3 */
#define COMP3_CTRL_INPSEL_0  ((uint32_t)0x00000020U)     /* Bit 0 */
#define COMP3_CTRL_INPSEL_1  ((uint32_t)0x00000040U)     /* Bit 1 */
#define COMP3_CTRL_INPSEL_2  ((uint32_t)0x00000080U)     /* Bit 2 */

#define COMP3_CTRL_OUTSEL    ((uint32_t)0x00000F00U)     /* Output select of Comparator_3 */
#define COMP3_CTRL_OUTSEL_0  ((uint32_t)0x00000100U)     /* Bit 0 */
#define COMP3_CTRL_OUTSEL_1  ((uint32_t)0x00000200U)     /* Bit 1 */ 
#define COMP3_CTRL_OUTSEL_2  ((uint32_t)0x00000400U)     /* Bit 2 */ 
#define COMP3_CTRL_OUTSEL_3  ((uint32_t)0x00000800U)     /* Bit 3 */ 
 
#define COMP3_CTRL_POL       ((uint32_t)0x00001000U)     /* Output polarity select of Comparator_3 */

#define COMP3_CTRL_HYST      ((uint32_t)0x00006000U)     /* Hysteresis level select of Comparator_3 */
#define COMP3_CTRL_HYST_0    ((uint32_t)0x00002000U)     /* Bit 0 */
#define COMP3_CTRL_HYST_1    ((uint32_t)0x00004000U)     /* Bit 1 */

#define COMP3_CTRL_BLKING    ((uint32_t)0x00038000U)     /* Blanking source select of Comparator_3 */
#define COMP3_CTRL_BLKING_0  ((uint32_t)0x00008000U)     /* Bit 0 */
#define COMP3_CTRL_BLKING_1  ((uint32_t)0x00010000U)     /* Bit 1 */
#define COMP3_CTRL_BLKING_2  ((uint32_t)0x00020000U)     /* Bit 2 */

#define COMP3_CTRL_OUT       ((uint32_t)0x00040000U)     /* Output state of Comparator_3 */

#define COMP3_CTRL_FILP_OUT  ((uint32_t)0x00080000U)     /* Output state of Comparator_3 Fiter */

/** COMP3_FILC register **/
#define COMP3_FILC_FILEN     ((uint32_t)0x00000001U)     /* Comparator_3 filter enable */
#define COMP3_FILC_THRESH    ((uint32_t)0x0000003EU)     /* Comparator_3 filter threshold size */
#define COMP3_FILC_SAMPW     ((uint32_t)0x000007C0U)     /* Comparator_3 filter window size */

/** COMP3_FILP register **/
#define COMP3_FILP_CLKPSC    ((uint32_t)0x0000FFFFU)     /* Comparator_3 filter sample clock prescale */

/** COMP4_CTRL register **/
#define COMP4_CTRL_EN        ((uint32_t)0x00000001U)     /* Comparator_4 enable */

#define COMP4_CTRL_INMSEL    ((uint32_t)0x0000001EU)     /* Inverting input select of Comparator_4 */
#define COMP4_CTRL_INMSEL_0  ((uint32_t)0x00000002U)     /* Bit 0 */
#define COMP4_CTRL_INMSEL_1  ((uint32_t)0x00000004U)     /* Bit 1 */
#define COMP4_CTRL_INMSEL_2  ((uint32_t)0x00000008U)     /* Bit 2 */
#define COMP4_CTRL_INMSEL_3  ((uint32_t)0x00000010U)     /* Bit 3 */

#define COMP4_CTRL_INPSEL    ((uint32_t)0x000000E0U)     /* Non inverting input select of Comparator_4 */
#define COMP4_CTRL_INPSEL_0  ((uint32_t)0x00000020U)     /* Bit 0 */
#define COMP4_CTRL_INPSEL_1  ((uint32_t)0x00000040U)     /* Bit 1 */
#define COMP4_CTRL_INPSEL_2  ((uint32_t)0x00000080U)     /* Bit 2 */

#define COMP4_CTRL_OUTSEL    ((uint32_t)0x00000F00U)     /* Output select of Comparator_4 */
#define COMP4_CTRL_OUTSEL_0  ((uint32_t)0x00000100U)     /* Bit 0 */
#define COMP4_CTRL_OUTSEL_1  ((uint32_t)0x00000200U)     /* Bit 1 */ 
#define COMP4_CTRL_OUTSEL_2  ((uint32_t)0x00000400U)     /* Bit 2 */ 
#define COMP4_CTRL_OUTSEL_3  ((uint32_t)0x00000800U)     /* Bit 3 */ 
 
#define COMP4_CTRL_POL       ((uint32_t)0x00001000U)     /* Output polarity select of Comparator_4 */

#define COMP4_CTRL_HYST      ((uint32_t)0x00006000U)     /* Hysteresis level select of Comparator_4 */
#define COMP4_CTRL_HYST_0    ((uint32_t)0x00002000U)     /* Bit 0 */
#define COMP4_CTRL_HYST_1    ((uint32_t)0x00004000U)     /* Bit 1 */

#define COMP4_CTRL_BLKING    ((uint32_t)0x00038000U)     /* Blanking source select of Comparator_4 */
#define COMP4_CTRL_BLKING_0  ((uint32_t)0x00008000U)     /* Bit 0 */
#define COMP4_CTRL_BLKING_1  ((uint32_t)0x00010000U)     /* Bit 1 */
#define COMP4_CTRL_BLKING_2  ((uint32_t)0x00020000U)     /* Bit 2 */

#define COMP4_CTRL_OUT       ((uint32_t)0x00040000U)     /* Output state of Comparator_4 */

#define COMP4_CTRL_FILP_OUT  ((uint32_t)0x00080000U)     /* Output state of Comparator_4 Fiter */

/** COMP4_FILC register **/
#define COMP4_FILC_FILEN     ((uint32_t)0x00000001U)    /* Comparator_4 filter enable */
#define COMP4_FILC_THRESH    ((uint32_t)0x0000003EU)    /* Comparator_4 filter threshold size */
#define COMP4_FILC_SAMPW     ((uint32_t)0x000007C0U)    /* Comparator_4 filter window size */

/** COMP4_FILP register **/
#define COMP4_FILP_CLKPSC    ((uint32_t)0x0000FFFFU)    /* Comparator_4 filter sample clock prescale */

/** COMP_OSEL register **/
#define COMP4_OSEL_CMP4XO    ((uint32_t)0x00000002U)     /* Comparator_4 XOR output */
#define COMP2_OSEL_CMP2XO    ((uint32_t)0x00000001U)     /* Comparator_2 XOR output */

/** COMP_LOCK register **/
#define COMP_LOCK            ((uint32_t)0x000FU)         /* All comparator lock enable */
#define COMP_LOCK_CMP1LK     ((uint32_t)0x0001U)         /* Comparator_1 lock enable */
#define COMP_LOCK_CMP2LK     ((uint32_t)0x0002U)         /* Comparator_2 lock enable */
#define COMP_LOCK_CMP3LK     ((uint32_t)0x0004U)         /* Comparator_3 lock enable */
#define COMP_LOCK_CMP4LK     ((uint32_t)0x0008U)         /* Comparator_4 lock enable */

/** COMP_INTEN register **/
#define COMP_INTEN           ((uint32_t)0x0000000FU)     /* Interrupt enable for all COMP */
#define COMP_INTEN_CMP1IEN   ((uint32_t)0x00000001U)     /* Interrupt enable for COMP1 */
#define COMP_INTEN_CMP2IEN   ((uint32_t)0x00000002U)     /* Interrupt enable for COMP2 */
#define COMP_INTEN_CMP3IEN   ((uint32_t)0x00000004U)     /* Interrupt enable for COMP3 */
#define COMP_INTEN_CMP4IEN   ((uint32_t)0x00000008U)     /* Interrupt enable for COMP4 */

/** COMP_INTSTS register **/
#define COMP_INTSTS          ((uint32_t)0x0000000FU)     /* Interrupt status of all Comparator */
#define COMP_INTSTS_COMP1IS  ((uint32_t)0x00000001U)     /* Interrupt status of Comparator_1 */
#define COMP_INTSTS_COMP2IS  ((uint32_t)0x00000002U)     /* Interrupt status of Comparator_2 */
#define COMP_INTSTS_COMP3IS  ((uint32_t)0x00000004U)     /* Interrupt status of Comparator_3 */
#define COMP_INTSTS_COMP4IS  ((uint32_t)0x00000008U)     /* Interrupt status of Comparator_4 */

/** COMP_VREFSCL register **/
#define COMP_VREFSCL_VV1EN   ((uint32_t)0x00000001U)     /* Low-Power internal dac1 enable */
#define COMP_VREFSCL_VV1TRM  ((uint32_t)0x0000007EU)     /* Low-Power internal dac1 output voltage size */
#define COMP_VREFSCL_VV2EN   ((uint32_t)0x00000080U)     /* Low-Power internal dac2 enable */
#define COMP_VREFSCL_VV2TRM  ((uint32_t)0x00003F00U)     /* Low-Power internal dac2 output voltage size */

/** COMP_TIM_OSEN register **/
#define COMP_TIM_EN          ((uint32_t)0x0000000FU)     /* Output to timer for all Comparator */
#define CMP1_TIM_EN          ((uint32_t)0x00000001U)     /* Comparator_1 output to timer enable */
#define CMP2_TIM_EN          ((uint32_t)0x00000002U)     /* Comparator_2 output to timer enable */
#define CMP3_TIM_EN          ((uint32_t)0x00000004U)     /* Comparator_3 output to timer enable */
#define CMP4_TIM_EN          ((uint32_t)0x00000008U)     /* Comparator_4 output to timer enable */



/*** Digital to Analog Converter ***/

/** Bit definition for DAC_CTRL register **/
#define DAC_CTRL_CHEN            ((uint32_t)0x00000001U) /* DAC channel enable */
#define DAC_CTRL_DMAEN           ((uint32_t)0x00000002U) /* DAC channel DMA enable */
#define DAC_CTRL_BEN             ((uint32_t)0x00000004U) /* DAC channel output buffer disable */
#define DAC_CTRL_TEN             ((uint32_t)0x00000008U) /* DAC channel Trigger enable */
#define DAC_CTRL_MASEL           ((uint32_t)0x000000F0U) /* MASEL[3:0] (DAC channel1 Mask/Amplitude selector) */
#define DAC_CTRL_MASEL_0         ((uint32_t)0x00000010U) /* Bit 0 */
#define DAC_CTRL_MASEL_1         ((uint32_t)0x00000020U) /* Bit 1 */
#define DAC_CTRL_MASEL_2         ((uint32_t)0x00000040U) /* Bit 2 */
#define DAC_CTRL_MASEL_3         ((uint32_t)0x00000080U) /* Bit 3 */
#define DAC_CTRL_BDASEL          ((uint32_t)0x00000100U) /* Output buffer drive ability selection */
#define DAC_CTRL_WEN             ((uint32_t)0x00000C00U) /* WEN[1:0] (DAC channel1 noise/triangle wave generation enable) */
#define DAC_CTRL_WEN_0           ((uint32_t)0x00000400U) /* Bit 0 */
#define DAC_CTRL_WEN_1           ((uint32_t)0x00000800U) /* Bit 1 */
#define DAC_CTRL_TSEL            ((uint32_t)0x00007000U) /* TSEL[2:0] (DAC channel1 Trigger selection) */
#define DAC_CTRL_TSEL_0          ((uint32_t)0x00001000U) /* Bit 0 */
#define DAC_CTRL_TSEL_1          ((uint32_t)0x00002000U) /* Bit 1 */
#define DAC_CTRL_TSEL_2          ((uint32_t)0x00004000U) /* Bit 2 */

/** Bit definition for DAC_SOTTR register **/
#define DAC_SOTTR_SWTREN         ((uint8_t)0x01U)        /* DAC channel software trigger */

/** Bit definition for DAC_DATO register **/
#define DAC_DATO_DACCHDO         ((uint16_t)0x0FFFU)     /* DAC channel data output */

/** Bit definition for DAC_DH8RA register **/
#define DAC_DH8RA_DACCHD         ((uint16_t)0x00FFU)     /* DAC channel1 8-bit right-aligned data */

/** Bit definition for DAC_DH12LA register **/
#define DAC_DH12LA_DACCHD        ((uint16_t)0xFFF0U)     /* DAC channel 12-bit left-aligned data */

/** Bit definition for DAC_DH12RA register **/
#define DAC_DH12RA_DACCHD        ((uint16_t)0x0FFFU)     /* DAC channel 12-bit right-aligned data */


/*** TIM ***/

/** Bit definition for TIM_CTRL1 register  **/

#define TIM_CTRL1_CNTEN     ((uint32_t)0x00000001U) /* Counter enable */
#define TIM_CTRL1_DIR       ((uint32_t)0x00000002U) /* Direction */

#define TIM_CTRL1_CAMSEL    ((uint32_t)0x0000000CU) /* CMS[1:0] bits (Center-aligned mode selection) */
#define TIM_CTRL1_CAMSEL_0  ((uint32_t)0x00000004U) /* Bit 0 */
#define TIM_CTRL1_CAMSEL_1  ((uint32_t)0x00000008U) /* Bit 1 */

#define TIM_CTRL1_UPRS      ((uint32_t)0x00000010U) /* Update request source */
#define TIM_CTRL1_UPDIS     ((uint32_t)0x00000020U) /* Update disable */

#define TIM_CTRL1_CLKD      ((uint32_t)0x000000C0U) /* CKD[1:0] bits (clock division) */
#define TIM_CTRL1_CLKD_0    ((uint32_t)0x00000040U) /* Bit 0 */
#define TIM_CTRL1_CLKD_1    ((uint32_t)0x00000080U) /* Bit 1 */

#define TIM_CTRL1_ONEPM     ((uint32_t)0x00000100U) /* One pulse mode */
#define TIM_CTRL1_ARPEN     ((uint32_t)0x00000200U) /* Auto-reload preload enable */
#define TIM_CTRL1_LBKPEN    ((uint32_t)0x00000400U) /* LOCKUP as bkp Enable*/
#define TIM_CTRL1_PBKPEN    ((uint32_t)0x00000800U) /* PVD as bkp Enable */
#define TIM_CTRL1_IOMBKPEN  ((uint32_t)0x00001000U) /* Break_in selection from IOM/COMP */
#define TIM_CTRL1_CLRSEL    ((uint32_t)0x00002000U) /* OCxRef selection from ETR/COMP */
#define TIM_CTRL1_COMPBKPEN ((uint32_t)0x00008000U) /* COMP as bkp Enable */
#define TIM_CTRL1_C1SEL     ((uint32_t)0x00010000U) /* Channel 1 selection from IOM/COMP/HSI */
#define TIM_CTRL1_C3SEL     ((uint32_t)0x00040000U) /* Channel 3 selection from IOM/COMP/LSI */
#define TIM_CTRL1_C4SEL     ((uint32_t)0x00080000U) /* Channel 4 selection from IOM/COMP/HSE/128 */

#define TIM_CTRL1_CMODE     ((uint32_t)0x00300000U)  /* In center-aligned mode, channel 4/7/8/9 trigger mode */
#define TIM_CTRL1_CMODE_0   ((uint32_t)0x00100000U)  /* Bit0 */
#define TIM_CTRL1_CMODE_1   ((uint32_t)0x00200000U)  /* Bit1 */

#define TIM_CTRL1_ASMMETRIC ((uint32_t)0x00800000U)  /* Asynmmetric mode enable in center-aligned */

/** Bit definition for TIM_CTRL2 register **/

#define TIM_CTRL2_OI1       ((uint32_t)0x00000001U) /* Output Idle state 1 (OC1 output) */
#define TIM_CTRL2_OI1N      ((uint32_t)0x00000002U) /* Output Idle state 1 (OC1N output) */
#define TIM_CTRL2_OI2       ((uint32_t)0x00000004U) /* Output Idle state 2 (OC2 output) */
#define TIM_CTRL2_OI2N      ((uint32_t)0x00000008U) /* Output Idle state 2 (OC2N output) */
#define TIM_CTRL2_OI3       ((uint32_t)0x00000010U) /* Output Idle state 3 (OC3 output) */
#define TIM_CTRL2_OI3N      ((uint32_t)0x00000020U) /* Output Idle state 3 (OC3N output) */
#define TIM_CTRL2_OI4       ((uint32_t)0x00000040U) /* Output Idle state 4 (OC4 output) */
#define TIM_CTRL2_OI4N      ((uint32_t)0x00000080U) /* Output Idle state 4 (OC4N output) */
#define TIM_CTRL2_OI5       ((uint32_t)0x00000100U) /* Output Idle state 5 (OC5 output) */
#define TIM_CTRL2_OI6       ((uint32_t)0x00000400U) /* Output Idle state 6 (OC6 output) */

#define TIM_CTRL2_MMSEL     ((uint32_t)0x0000f000U) /* MMS[3:0] bits (Master Mode Selection) */
#define TIM_CTRL2_MMSEL_0   ((uint32_t)0x00001000U) /* Bit 0 */
#define TIM_CTRL2_MMSEL_1   ((uint32_t)0x00002000U) /* Bit 1 */
#define TIM_CTRL2_MMSEL_2   ((uint32_t)0x00004000U) /* Bit 2 */
#define TIM_CTRL2_MMSEL_3   ((uint32_t)0x00008000U) /* Bit 3 */

#define TIM_CTRL2_CCUSEL    ((uint32_t)0x00010000U) /* Capture/Compare Control Update Selection */
#define TIM_CTRL2_CCDSEL    ((uint32_t)0x00020000U) /* Capture/Compare DMA Selection */
#define TIM_CTRL2_CCPCTL    ((uint32_t)0x00040000U) /* Capture/Compare Preloaded Control */
#define TIM_CTRL2_TI1SEL    ((uint32_t)0x00080000U) /* TI1 Selection */
#define TIM_CTRL2_TRIG4     ((uint32_t)0x00100000U) /* OC4REF trigger to ADC enable */
#define TIM_CTRL2_TRIG7     ((uint32_t)0x00200000U) /* OC7REF trigger to ADC enable */
#define TIM_CTRL2_TRIG8     ((uint32_t)0x00400000U) /* OC7REF trigger to ADC enable */
#define TIM_CTRL2_TRIG9     ((uint32_t)0x00800000U) /* OC7REF trigger to ADC enable */

/** Bit definition for TIM_STS register **/

#define TIM_STS_CC1ITF      ((uint32_t)0x00000001U) /* Capture/Compare 1 interrupt Flag */
#define TIM_STS_CC2ITF      ((uint32_t)0x00000002U) /* Capture/Compare 2 interrupt Flag */
#define TIM_STS_CC3ITF      ((uint32_t)0x00000004U) /* Capture/Compare 3 interrupt Flag */
#define TIM_STS_CC4ITF      ((uint32_t)0x00000008U) /* Capture/Compare 4 interrupt Flag */
#define TIM_STS_CC5ITF      ((uint32_t)0x00000010U) /* Capture/Compare 5 interrupt Flag */
#define TIM_STS_CC6ITF      ((uint32_t)0x00000020U) /* Capture/Compare 6 interrupt Flag */
#define TIM_STS_CC1OCF      ((uint32_t)0x00000100U) /* Capture/Compare 1 Overcapture Flag */
#define TIM_STS_CC2OCF      ((uint32_t)0x00000200U) /* Capture/Compare 2 Overcapture Flag */
#define TIM_STS_CC3OCF      ((uint32_t)0x00000400U) /* Capture/Compare 3 Overcapture Flag */
#define TIM_STS_CC4OCF      ((uint32_t)0x00000800U) /* Capture/Compare 4 Overcapture Flag */
#define TIM_STS_UDITF       ((uint32_t)0x00010000U) /* Update interrupt Flag */
#define TIM_STS_COMITF      ((uint32_t)0x00020000U) /* COM interrupt Flag */
#define TIM_STS_TITF        ((uint32_t)0x00040000U) /* Trigger interrupt Flag */
#define TIM_STS_BITF        ((uint32_t)0x00080000U) /* Break interrupt Flag */

/** Bit definition for TIM_EVTGEN register **/

#define TIM_EVTGEN_CC1GN    ((uint32_t)0x00000001U) /* Capture/Compare 1 Generation */
#define TIM_EVTGEN_CC2GN    ((uint32_t)0x00000002U) /* Capture/Compare 2 Generation */
#define TIM_EVTGEN_CC3GN    ((uint32_t)0x00000004U) /* Capture/Compare 3 Generation */
#define TIM_EVTGEN_CC4GN    ((uint32_t)0x00000008U) /* Capture/Compare 4 Generation */
#define TIM_EVTGEN_UDGN     ((uint32_t)0x00000100U) /* Update Generation */
#define TIM_EVTGEN_CCUDGN   ((uint32_t)0x00000200U) /* Capture/Compare Control Update Generation */
#define TIM_EVTGEN_TGN      ((uint32_t)0x00000400U) /* Trigger Generation */
#define TIM_EVTGEN_BGN      ((uint32_t)0x00000800U) /* Break Generation */

/** Bit definition for TIM_SMCTRL register **/

#define TIM_SMCTRL_TSEL     ((uint32_t)0x00000007U) /* TS[2:0] bits (Trigger selection) */
#define TIM_SMCTRL_TSEL_0   ((uint32_t)0x00000001U) /* Bit 0 */
#define TIM_SMCTRL_TSEL_1   ((uint32_t)0x00000002U) /* Bit 1 */
#define TIM_SMCTRL_TSEL_2   ((uint32_t)0x00000004U) /* Bit 2 */

#define TIM_SMCTRL_SMSEL    ((uint32_t)0x00000070U) /* SMS[2:0] bits (Slave mode selection) */
#define TIM_SMCTRL_SMSEL_0  ((uint32_t)0x00000010U) /* Bit 0 */
#define TIM_SMCTRL_SMSEL_1  ((uint32_t)0x00000020U) /* Bit 1 */
#define TIM_SMCTRL_SMSEL_2  ((uint32_t)0x00000040U) /* Bit 2 */

#define TIM_SMCTRL_EXTPS    ((uint32_t)0x00000300U) /* ETPS[1:0] bits (External trigger prescaler) */
#define TIM_SMCTRL_EXTPS_0  ((uint32_t)0x00000100U) /* Bit 0 */
#define TIM_SMCTRL_EXTPS_1  ((uint32_t)0x00000200U) /* Bit 1 */

#define TIM_SMCTRL_EXCEN    ((uint32_t)0x00000400U) /* External clock enable */
#define TIM_SMCTRL_EXTP     ((uint32_t)0x00000800U) /* External trigger polarity */

#define TIM_SMCTRL_EXTF     ((uint32_t)0x0000F000U) /* ETF[3:0] bits (External trigger filter) */
#define TIM_SMCTRL_EXTF_0   ((uint32_t)0x00001000U) /* Bit 0 */
#define TIM_SMCTRL_EXTF_1   ((uint32_t)0x00002000U) /* Bit 1 */
#define TIM_SMCTRL_EXTF_2   ((uint32_t)0x00004000U) /* Bit 2 */
#define TIM_SMCTRL_EXTF_3   ((uint32_t)0x00008000U) /* Bit 3 */

#define TIM_SMCTRL_MSMD     ((uint32_t)0x00010000U) /* Master/slave mode */

/** Bit definition for TIM_DINTEN register **/

#define TIM_DINTEN_CC1IEN   ((uint32_t)0x00000001U) /* Capture/Compare 1 interrupt enable */
#define TIM_DINTEN_CC2IEN   ((uint32_t)0x00000002U) /* Capture/Compare 2 interrupt enable */
#define TIM_DINTEN_CC3IEN   ((uint32_t)0x00000004U) /* Capture/Compare 3 interrupt enable */
#define TIM_DINTEN_CC4IEN   ((uint32_t)0x00000008U) /* Capture/Compare 4 interrupt enable */
#define TIM_DINTEN_CC1DEN   ((uint32_t)0x00000100U) /* Capture/Compare 1 DMA request enable */
#define TIM_DINTEN_CC2DEN   ((uint32_t)0x00000200U) /* Capture/Compare 2 DMA request enable */
#define TIM_DINTEN_CC3DEN   ((uint32_t)0x00000400U) /* Capture/Compare 3 DMA request enable */
#define TIM_DINTEN_CC4DEN   ((uint32_t)0x00000800U) /* Capture/Compare 4 DMA request enable */
#define TIM_DINTEN_UIEN     ((uint32_t)0x00010000U) /* Update interrupt enable */
#define TIM_DINTEN_TIEN     ((uint32_t)0x00020000U) /* Trigger interrupt enable */
#define TIM_DINTEN_BIEN     ((uint32_t)0x00040000U) /* Break interrupt enable */
#define TIM_DINTEN_UDEN     ((uint32_t)0x00080000U) /* Update DMA request enable */
#define TIM_DINTEN_COMDEN   ((uint32_t)0x00100000U) /* COM DMA request enable */
#define TIM_DINTEN_TDEN     ((uint32_t)0x00200000U) /* Trigger DMA request enable */
#define TIM_DINTEN_COMIEN   ((uint32_t)0x00400000U) /* COM interrupt enable */

/** Bit definition for TIM_CCMOD1 register **/

#define TIM_CCMOD1_CC1SEL       ((uint32_t)0x00000003U) /* CC1S[1:0] bits (Capture/Compare 1 Selection) */
#define TIM_CCMOD1_CC1SEL_0     ((uint32_t)0x00000001U) /* Bit 0 */
#define TIM_CCMOD1_CC1SEL_1     ((uint32_t)0x00000002U) /* Bit 1 */

#define TIM_CCMOD1_OC1PEN       ((uint32_t)0x00000004U) /* Output Compare 1 Preload enable */
#define TIM_CCMOD1_OC1FEN       ((uint32_t)0x00000008U) /* Output Compare 1 Fast enable */
#define TIM_CCMOD1_OC1CEN       ((uint32_t)0x00000010U) /* Output Compare 1Clear Enable */

#define TIM_CCMOD1_OC1MD        ((uint32_t)0x000000E0U) /* OC1M[2:0] bits (Output Compare 1 Mode) */
#define TIM_CCMOD1_OC1MD_0      ((uint32_t)0x00000020U) /* Bit 0 */
#define TIM_CCMOD1_OC1MD_1      ((uint32_t)0x00000040U) /* Bit 1 */
#define TIM_CCMOD1_OC1MD_2      ((uint32_t)0x00000080U) /* Bit 2 */

#define TIM_CCMOD1_CC2SEL       ((uint32_t)0x00000300U) /* CC2S[1:0] bits (Capture/Compare 2 Selection) */
#define TIM_CCMOD1_CC2SEL_0     ((uint32_t)0x00000100U) /* Bit 0 */
#define TIM_CCMOD1_CC2SEL_1     ((uint32_t)0x00000200U) /* Bit 1 */

#define TIM_CCMOD1_OC2PEN       ((uint32_t)0x00000400U) /* Output Compare 2 Preload enable */
#define TIM_CCMOD1_OC2FEN       ((uint32_t)0x00000800U) /* Output Compare 2 Fast enable */
#define TIM_CCMOD1_OC2CEN       ((uint32_t)0x00001000U) /* Output Compare 2 Clear Enable */

#define TIM_CCMOD1_OC2MD        ((uint32_t)0x0000E000U) /* OC2M[2:0] bits (Output Compare 2 Mode) */
#define TIM_CCMOD1_OC2MD_0      ((uint32_t)0x00002000U) /* Bit 0 */
#define TIM_CCMOD1_OC2MD_1      ((uint32_t)0x00004000U) /* Bit 1 */
#define TIM_CCMOD1_OC2MD_2      ((uint32_t)0x00008000U) /* Bit 2 */


#define TIM_CCMOD1_IC1PSC       ((uint32_t)0x0000000CU) /* IC1PSC[1:0] bits (Input Capture 1 Prescaler) */
#define TIM_CCMOD1_IC1PSC_0     ((uint32_t)0x00000004U) /* Bit 0 */
#define TIM_CCMOD1_IC1PSC_1     ((uint32_t)0x00000008U) /* Bit 1 */

#define TIM_CCMOD1_IC1F         ((uint32_t)0x000000F0U) /* IC1F[3:0] bits (Input Capture 1 Filter) */
#define TIM_CCMOD1_IC1F_0       ((uint32_t)0x00000010U) /* Bit 0 */
#define TIM_CCMOD1_IC1F_1       ((uint32_t)0x00000020U) /* Bit 1 */
#define TIM_CCMOD1_IC1F_2       ((uint32_t)0x00000040U) /* Bit 2 */
#define TIM_CCMOD1_IC1F_3       ((uint32_t)0x00000080U) /* Bit 3 */

#define TIM_CCMOD1_IC2PSC       ((uint32_t)0x00000C00U) /* IC2PSC[1:0] bits (Input Capture 2 Prescaler) */
#define TIM_CCMOD1_IC2PSC_0     ((uint32_t)0x00000400U) /* Bit 0 */
#define TIM_CCMOD1_IC2PSC_1     ((uint32_t)0x00000800U) /* Bit 1 */

#define TIM_CCMOD1_IC2F         ((uint32_t)0x0000F000U) /* IC2F[3:0] bits (Input Capture 2 Filter) */
#define TIM_CCMOD1_IC2F_0       ((uint32_t)0x00001000U) /* Bit 0 */
#define TIM_CCMOD1_IC2F_1       ((uint32_t)0x00002000U) /* Bit 1 */
#define TIM_CCMOD1_IC2F_2       ((uint32_t)0x00004000U) /* Bit 2 */
#define TIM_CCMOD1_IC2F_3       ((uint32_t)0x00008000U) /* Bit 3 */

/** Bit definition for TIM_CCMOD2 register **/

#define TIM_CCMOD2_CC3SEL       ((uint32_t)0x00000003U) /* CC3S[1:0] bits (Capture/Compare 3 Selection) */
#define TIM_CCMOD2_CC3SEL_0     ((uint32_t)0x00000001U) /* Bit 0 */
#define TIM_CCMOD2_CC3SEL_1     ((uint32_t)0x00000002U) /* Bit 1 */

#define TIM_CCMOD2_OC3PEN       ((uint32_t)0x00000004U) /* Output Compare 3 Preload enable */
#define TIM_CCMOD2_OC3FEN       ((uint32_t)0x00000008U) /* Output Compare 3 Fast enable */
#define TIM_CCMOD2_OC3CEN       ((uint32_t)0x00000010U) /* Output Compare 3 Clear Enable */

#define TIM_CCMOD2_OC3MD        ((uint32_t)0x000000E0U) /* OC3M[2:0] bits (Output Compare 3 Mode) */
#define TIM_CCMOD2_OC3MD_0      ((uint32_t)0x00000020U) /* Bit 0 */
#define TIM_CCMOD2_OC3MD_1      ((uint32_t)0x00000040U) /* Bit 1 */
#define TIM_CCMOD2_OC3MD_2      ((uint32_t)0x00000080U) /* Bit 2 */

#define TIM_CCMOD2_CC4SEL       ((uint32_t)0x00000300U) /* CC3S[1:0] bits (Capture/Compare 4 Selection) */
#define TIM_CCMOD2_CC4SEL_0     ((uint32_t)0x00000100U) /* Bit 0 */
#define TIM_CCMOD2_CC4SEL_1     ((uint32_t)0x00000200U) /* Bit 1 */

#define TIM_CCMOD2_OC4PEN       ((uint32_t)0x00000400U) /* Output Compare 4 Preload enable */
#define TIM_CCMOD2_OC4FEN       ((uint32_t)0x00000800U) /* Output Compare 4 Fast enable */
#define TIM_CCMOD2_OC4CEN       ((uint32_t)0x00001000U) /* Output Compare 4 Clear Enable */

#define TIM_CCMOD2_OC4MD        ((uint32_t)0x0000E000U) /* OC4M[2:0] bits (Output Compare 4 Mode) */
#define TIM_CCMOD2_OC4MD_0      ((uint32_t)0x00002000U) /* Bit 0 */
#define TIM_CCMOD2_OC4MD_1      ((uint32_t)0x00004000U) /* Bit 1 */
#define TIM_CCMOD2_OC4MD_2      ((uint32_t)0x00008000U) /* Bit 2 */


#define TIM_CCMOD2_IC3PSC       ((uint32_t)0x0000000CU) /* IC3PSC[1:0] bits (Input Capture 3 Prescaler) */
#define TIM_CCMOD2_IC3PSC_0     ((uint32_t)0x00000004U) /* Bit 0 */
#define TIM_CCMOD2_IC3PSC_1     ((uint32_t)0x00000008U) /* Bit 1 */

#define TIM_CCMOD2_IC3F         ((uint32_t)0x000000F0U) /* IC3F[3:0] bits (Input Capture 3 Filter) */
#define TIM_CCMOD2_IC3F_0       ((uint32_t)0x00000010U) /* Bit 0 */
#define TIM_CCMOD2_IC3F_1       ((uint32_t)0x00000020U) /* Bit 1 */
#define TIM_CCMOD2_IC3F_2       ((uint32_t)0x00000040U) /* Bit 2 */
#define TIM_CCMOD2_IC3F_3       ((uint32_t)0x00000080U) /* Bit 3 */

#define TIM_CCMOD2_IC4PSC       ((uint32_t)0x00000C00U) /* IC4PSC[1:0] bits (Input Capture 4 Prescaler) */
#define TIM_CCMOD2_IC4PSC_0     ((uint32_t)0x00000400U) /* Bit 0 */
#define TIM_CCMOD2_IC4PSC_1     ((uint32_t)0x00000800U) /* Bit 1 */

#define TIM_CCMOD2_IC4F         ((uint32_t)0x0000F000U) /* IC4F[3:0] bits (Input Capture 4 Filter) */
#define TIM_CCMOD2_IC4F_0       ((uint32_t)0x00001000U) /* Bit 0 */
#define TIM_CCMOD2_IC4F_1       ((uint32_t)0x00002000U) /* Bit 1 */
#define TIM_CCMOD2_IC4F_2       ((uint32_t)0x00004000U) /* Bit 2 */
#define TIM_CCMOD2_IC4F_3       ((uint32_t)0x00008000U) /* Bit 3 */

/** Bit definition for TIM_CCMOD3 register **/

#define TIM_CCMOD3_OC5PEN       ((uint32_t)0x00000004U) /* Output Compare 5 Preload enable */
#define TIM_CCMOD3_OC5FEN       ((uint32_t)0x00000008U) /* Output Compare 5 Fast enable */
#define TIM_CCMOD3_OC5CEN       ((uint32_t)0x00000010U) /* Output Compare 5 Clear Enable */

#define TIM_CCMOD3_OC5MD        ((uint32_t)0x000000E0U) /* OC5M[2:0] bits (Output Compare 5 Mode) */
#define TIM_CCMOD3_OC5MD_0      ((uint32_t)0x00000020U) /* Bit 0 */
#define TIM_CCMOD3_OC5MD_1      ((uint32_t)0x00000040U) /* Bit 1 */
#define TIM_CCMOD3_OC5MD_2      ((uint32_t)0x00000080U) /* Bit 2 */

#define TIM_CCMOD3_OC6PEN       ((uint32_t)0x00000400U) /* Output Compare 6 Preload enable */
#define TIM_CCMOD3_OC6FEN       ((uint32_t)0x00000800U) /* Output Compare 6 Fast enable */
#define TIM_CCMOD3_OC6CEN       ((uint32_t)0x00001000U) /* Output Compare 6 Clear Enable */

#define TIM_CCMOD3_OC6MD        ((uint32_t)0x0000E000U) /* OC6M[2:0] bits (Output Compare 6 Mode) */
#define TIM_CCMOD3_OC6MD_0      ((uint32_t)0x00002000U) /* Bit 0 */
#define TIM_CCMOD3_OC6MD_1      ((uint32_t)0x00004000U) /* Bit 1 */
#define TIM_CCMOD3_OC6MD_2      ((uint32_t)0x00008000U) /* Bit 2 */

#define TIM_CCMOD3_OC7PEN       ((uint32_t)0x00010000U) /* Output Compare 7 Preload enable */
#define TIM_CCMOD3_OC8PEN       ((uint32_t)0x00100000U) /* Output Compare 8 Preload enable */
#define TIM_CCMOD3_OC9PEN       ((uint32_t)0x01000000U) /* Output Compare 9 Preload enable */

/** Bit definition for TIM_CCEN register **/

#define TIM_CCEN_CC1NEN         ((uint32_t)0x00000001U) /* Capture/Compare 1 Complementary output enable */
#define TIM_CCEN_CC1NP          ((uint32_t)0x00000002U) /* Capture/Compare 1 Complementary output Polarity */
#define TIM_CCEN_CC1EN          ((uint32_t)0x00000004U) /* Capture/Compare 1 output enable */
#define TIM_CCEN_CC1P           ((uint32_t)0x00000008U) /* Capture/Compare 1 output Polarity */
#define TIM_CCEN_CC2NEN         ((uint32_t)0x00000010U) /* Capture/Compare 2 Complementary output enable */
#define TIM_CCEN_CC2NP          ((uint32_t)0x00000020U) /* Capture/Compare 2 Complementary output Polarity */
#define TIM_CCEN_CC2EN          ((uint32_t)0x00000040U) /* Capture/Compare 2 output enable */
#define TIM_CCEN_CC2P           ((uint32_t)0x00000080U) /* Capture/Compare 2 output Polarity */
#define TIM_CCEN_CC3NEN         ((uint32_t)0x00000100U) /* Capture/Compare 3 Complementary output enable */
#define TIM_CCEN_CC3NP          ((uint32_t)0x00000200U) /* Capture/Compare 3 Complementary output Polarity */
#define TIM_CCEN_CC3EN          ((uint32_t)0x00000400U) /* Capture/Compare 3 output enable */
#define TIM_CCEN_CC3P           ((uint32_t)0x00000800U) /* Capture/Compare 3 output Polarity */
#define TIM_CCEN_CC4NEN         ((uint32_t)0x00001000U) /* Capture/Compare 4 Complementary output enable */
#define TIM_CCEN_CC4NP          ((uint32_t)0x00002000U) /* Capture/Compare 4 Complementary output Polarity */
#define TIM_CCEN_CC4EN          ((uint32_t)0x00004000U) /* Capture/Compare 4 output enable */
#define TIM_CCEN_CC4P           ((uint32_t)0x00008000U) /* Capture/Compare 4 output Polarity */
#define TIM_CCEN_CC5EN          ((uint32_t)0x00040000U) /* Capture/Compare 5 output enable */
#define TIM_CCEN_CC5P           ((uint32_t)0x00080000U) /* Capture/Compare 5 output Polarity */
#define TIM_CCEN_CC6EN          ((uint32_t)0x00400000U) /* Capture/Compare 6 output enable */
#define TIM_CCEN_CC6P           ((uint32_t)0x00800000U) /* Capture/Compare 6 output Polarity */

/** Bit definition for TIM_CCDAT1 register **/
#define TIM_CCDAT1_CCDAT1       ((uint32_t)0x0000FFFFU)  /* Capture/Compare 1 Value */
#define TIM_CCDAT1_CCDDAT1      ((uint32_t)0xFFFF0000U)  /* Capture/Compare 1 down-counting Value */

/** Bit definition for TIM_CCDAT2 register **/
#define TIM_CCDAT2_CCDAT2       ((uint32_t)0x0000FFFFU)  /* Capture/Compare 2 Value */
#define TIM_CCDAT2_CCDDAT2      ((uint32_t)0xFFFF0000U)  /* Capture/Compare 2 down-counting Value */

/** Bit definition for TIM_CCDAT3 register **/
#define TIM_CCDAT3_CCDAT3       ((uint32_t)0x0000FFFFU)  /* Capture/Compare 3 Value */
#define TIM_CCDAT3_CCDDAT3      ((uint32_t)0xFFFF0000U)  /* Capture/Compare 3 down-counting Value */

/** Bit definition for TIM_CCDAT4 register **/
#define TIM_CCDAT4_CCDAT4       ((uint32_t)0x0000FFFFU)  /* Capture/Compare 4 Value */
#define TIM_CCDAT4_CCDDAT4      ((uint32_t)0xFFFF0000U)  /* Capture/Compare 4 down-counting Value */

/** Bit definition for TIM_CCDAT5 register **/
#define TIM_CCDAT5_CCDAT5       ((uint32_t)0x0000FFFFU)  /* Capture/Compare 5 Value */

/** Bit definition for TIM_CCDAT6 register **/
#define TIM_CCDAT6_CCDAT6       ((uint32_t)0x0000FFFFU)  /* Capture/Compare 6 Value */

/** Bit definition for TIM_PSC register **/
#define TIM_PSC_PSC             ((uint32_t)0x0000FFFFU)  /* Prescaler Value */

/** Bit definition for TIM_AR register **/
#define TIM_AR_AR               ((uint32_t)0x0000FFFFU)  /* actual auto-reload Value */

/** Bit definition for TIM_CNT register **/
#define TIM_CNT_CNT             ((uint32_t)0x0000FFFFU)  /* Counter Value */

/** Bit definition for TIM_REPCNT register **/
#define TIM_REPCNT_REPCNT       ((uint32_t)0x000000FFU) /* Repetition Counter Value */

/** Bit definition for TIM_BKDT register **/

#define TIM_BKDT_DTGN           ((uint32_t)0x000000FFU) /* DTG[0:7] bits (Dead-Time Generator set-up) */
#define TIM_BKDT_DTGN_0         ((uint32_t)0x00000001U) /* Bit 0 */
#define TIM_BKDT_DTGN_1         ((uint32_t)0x00000002U) /* Bit 1 */
#define TIM_BKDT_DTGN_2         ((uint32_t)0x00000004U) /* Bit 2 */
#define TIM_BKDT_DTGN_3         ((uint32_t)0x00000008U) /* Bit 3 */
#define TIM_BKDT_DTGN_4         ((uint32_t)0x00000010U) /* Bit 4 */
#define TIM_BKDT_DTGN_5         ((uint32_t)0x00000020U) /* Bit 5 */
#define TIM_BKDT_DTGN_6         ((uint32_t)0x00000040U) /* Bit 6 */
#define TIM_BKDT_DTGN_7         ((uint32_t)0x00000080U) /* Bit 7 */

#define TIM_BKDT_MOEN           ((uint32_t)0x00000100U) /* Main Output enable */
#define TIM_BKDT_AOEN           ((uint32_t)0x00000200U) /* Automatic Output enable */
#define TIM_BKDT_BKP            ((uint32_t)0x00000400U) /* Break Polarity */
#define TIM_BKDT_BKEN           ((uint32_t)0x00000800U) /* Break enable */
#define TIM_BKDT_OSSI           ((uint32_t)0x00001000U) /* Off-State Selection for Idle mode */
#define TIM_BKDT_OSSR           ((uint32_t)0x00002000U) /* Off-State Selection for Run mode */

#define TIM_BKDT_LCKCFG         ((uint32_t)0x0000C000U) /* LOCK[1:0] bits (Lock Configuration) */
#define TIM_BKDT_LCKCFG_0       ((uint32_t)0x00004000U) /* Bit 0 */
#define TIM_BKDT_LCKCFG_1       ((uint32_t)0x00008000U) /* Bit 1 */

/** Bit definition for TIM_CCDAT7 register **/
#define TIM_CCDAT7_CCDAT7       ((uint32_t)0x0000FFFFU)  /* Capture/Compare 7 Value */

/** Bit definition for TIM_CCDAT8 register **/
#define TIM_CCDAT8_CCDAT8       ((uint32_t)0x0000FFFFU)  /* Capture/Compare 8 Value */

/** Bit definition for TIM_CCDAT9 register **/
#define TIM_CCDAT9_CCDAT9       ((uint32_t)0x0000FFFFU)  /* Capture/Compare 9 Value */

/** Bit definition for TIM_BRK_FILT register **/
#define TIM_BRK_FILT_THRESH     ((uint32_t)0x3F000000U)
#define TIM_BRK_FILT_WSIZE      ((uint32_t)0x007E0000U)
#define TIM_BRK_FILT_FILTEN     ((uint32_t)0x00010000U)
#define TIM_BRK_FILT_PSC        ((uint32_t)0x0000FFFFU)

/** Bit definition for TIM_C1FILT register **/
#define TIM_C1FILT_THRESH       ((uint32_t)0x3F000000U)
#define TIM_C1FILT_WSIZE        ((uint32_t)0x007E0000U)
#define TIM_C1FILT_FILTEN       ((uint32_t)0x00010000U)
#define TIM_C1FILT_PSC          ((uint32_t)0x0000FFFFU)

/** Bit definition for TIM_C2FILT register **/
#define TIM_C2FILT_THRESH       ((uint32_t)0x3F000000U)
#define TIM_C2FILT_WSIZE        ((uint32_t)0x007E0000U)
#define TIM_C2FILT_FILTEN       ((uint32_t)0x00010000U)
#define TIM_C2FILT_PSC          ((uint32_t)0x0000FFFFU)

/** Bit definition for TIM_C3FILT register **/
#define TIM_C3FILT_THRESH       ((uint32_t)0x3F000000U)
#define TIM_C3FILT_WSIZE        ((uint32_t)0x007E0000U)
#define TIM_C3FILT_FILTEN       ((uint32_t)0x00010000U)
#define TIM_C3FILT_PSC          ((uint32_t)0x0000FFFFU)

/** Bit definition for TIM_C4FILT register **/
#define TIM_C4FILT_THRESH       ((uint32_t)0x3F000000U)
#define TIM_C4FILT_WSIZE        ((uint32_t)0x007E0000U)
#define TIM_C4FILT_FILTEN       ((uint32_t)0x00010000U)
#define TIM_C4FILT_PSC          ((uint32_t)0x0000FFFFU)

/** Bit definition for TIM_FILTO register **/
#define TIM_FILTO_C1FILTO       ((uint32_t)0x00000001U)
#define TIM_FILTO_C2FILTO       ((uint32_t)0x00000002U)
#define TIM_FILTO_C3FILTO       ((uint32_t)0x00000004U)
#define TIM_FILTO_C4FILTO       ((uint32_t)0x00000008U)

/** Bit definition for TIM_INSEL register **/
#define TIM_INSEL_C1SEL         ((uint32_t)0x00000001U)
#define TIM_INSEL_C2SEL         ((uint32_t)0x00000010U)
#define TIM_INSEL_C3SEL         ((uint32_t)0x00000100U)
#define TIM_INSEL_C4SEL         ((uint32_t)0x00001000U)

/** Bit definition for TIM_DCTRL register **/
#define TIM_DCTRL_DBADDR        ((uint32_t)0x00001F00U) /* DBA[4:0] bits (DMA Base Address) */
#define TIM_DCTRL_DBADDR_0      ((uint32_t)0x00000100U) /* Bit 0 */
#define TIM_DCTRL_DBADDR_1      ((uint32_t)0x00000200U) /* Bit 1 */
#define TIM_DCTRL_DBADDR_2      ((uint32_t)0x00000400U) /* Bit 2 */
#define TIM_DCTRL_DBADDR_3      ((uint32_t)0x00000800U) /* Bit 3 */
#define TIM_DCTRL_DBADDR_4      ((uint32_t)0x00001000U) /* Bit 4 */

#define TIM_DCTRL_DBLEN         ((uint32_t)0x0000001FU) /* DBL[4:0] bits (DMA Burst Length) */
#define TIM_DCTRL_DBLEN_0       ((uint32_t)0x00000001U) /* Bit 0 */
#define TIM_DCTRL_DBLEN_1       ((uint32_t)0x00000002U) /* Bit 1 */
#define TIM_DCTRL_DBLEN_2       ((uint32_t)0x00000004U) /* Bit 2 */
#define TIM_DCTRL_DBLEN_3       ((uint32_t)0x00000008U) /* Bit 3 */
#define TIM_DCTRL_DBLEN_4       ((uint32_t)0x00000010U) /* Bit 4 */

/** Bit definition for TIM_DADDR register **/
#define TIM_DADDR_BURST         ((uint32_t)0x0000FFFFU) /* DMA register for burst accesses */

/*** Real-Time Clock (RTC) ***/
/** Bits definition for RTC_INITSTS register **/
#define RTC_INITSTS_RECPF  ((uint32_t)0x00010000U)
#define RTC_INITSTS_TAM3F  ((uint32_t)0x00008000U)
#define RTC_INITSTS_TAM2F  ((uint32_t)0x00004000U)
#define RTC_INITSTS_TAM1F  ((uint32_t)0x00002000U)
#define RTC_INITSTS_TISOVF ((uint32_t)0x00001000U)
#define RTC_INITSTS_TISF   ((uint32_t)0x00000800U)
#define RTC_INITSTS_WTF    ((uint32_t)0x00000400U)
#define RTC_INITSTS_ALBF   ((uint32_t)0x00000200U)
#define RTC_INITSTS_ALAF   ((uint32_t)0x00000100U)
#define RTC_INITSTS_INITM  ((uint32_t)0x00000080U)
#define RTC_INITSTS_INITF  ((uint32_t)0x00000040U)
#define RTC_INITSTS_RSYF   ((uint32_t)0x00000020U)
#define RTC_INITSTS_INITSF ((uint32_t)0x00000010U)
#define RTC_INITSTS_SHOPF  ((uint32_t)0x00000008U)
#define RTC_INITSTS_WTWF   ((uint32_t)0x00000004U)
#define RTC_INITSTS_ALBWF  ((uint32_t)0x00000002U)
#define RTC_INITSTS_ALAWF  ((uint32_t)0x00000001U)

/** Bits definition for RTC_CTRL register **/
#define RTC_CTRL_COEN     ((uint32_t)0x00800000U)
#define RTC_CTRL_OUTSEL   ((uint32_t)0x00600000U)
#define RTC_CTRL_OUTSEL_0 ((uint32_t)0x00200000U)
#define RTC_CTRL_OUTSEL_1 ((uint32_t)0x00400000U)
#define RTC_CTRL_OPOL     ((uint32_t)0x00100000U)
#define RTC_CTRL_CALOSEL  ((uint32_t)0x00080000U)
#define RTC_CTRL_BAKP     ((uint32_t)0x00040000U)
#define RTC_CTRL_SU1H     ((uint32_t)0x00020000U)
#define RTC_CTRL_AD1H     ((uint32_t)0x00010000U)
#define RTC_CTRL_TSIEN    ((uint32_t)0x00008000U)
#define RTC_CTRL_WTIEN    ((uint32_t)0x00004000U)
#define RTC_CTRL_ALBIEN   ((uint32_t)0x00002000U)
#define RTC_CTRL_ALAIEN   ((uint32_t)0x00001000U)
#define RTC_CTRL_TSEN     ((uint32_t)0x00000800U)
#define RTC_CTRL_WTEN     ((uint32_t)0x00000400U)
#define RTC_CTRL_ALBEN    ((uint32_t)0x00000200U)
#define RTC_CTRL_ALAEN    ((uint32_t)0x00000100U)

#define RTC_CTRL_HFMT      ((uint32_t)0x00000040U)
#define RTC_CTRL_BYPS      ((uint32_t)0x00000020U)
#define RTC_CTRL_REFCLKEN  ((uint32_t)0x00000010U)
#define RTC_CTRL_TEDGE     ((uint32_t)0x00000008U)
#define RTC_CTRL_WKUPSEL   ((uint32_t)0x00000007U)
#define RTC_CTRL_WKUPSEL_0 ((uint32_t)0x00000001U)
#define RTC_CTRL_WKUPSEL_1 ((uint32_t)0x00000002U)
#define RTC_CTRL_WKUPSEL_2 ((uint32_t)0x00000004U)


/** Bits definition for RTC_TSH register **/
#define RTC_TSH_APM   ((uint32_t)0x00400000U)
#define RTC_TSH_HOT   ((uint32_t)0x00300000U)
#define RTC_TSH_HOT_0 ((uint32_t)0x00100000U)
#define RTC_TSH_HOT_1 ((uint32_t)0x00200000U)
#define RTC_TSH_HOU   ((uint32_t)0x000F0000U)
#define RTC_TSH_HOU_0 ((uint32_t)0x00010000U)
#define RTC_TSH_HOU_1 ((uint32_t)0x00020000U)
#define RTC_TSH_HOU_2 ((uint32_t)0x00040000U)
#define RTC_TSH_HOU_3 ((uint32_t)0x00080000U)
#define RTC_TSH_MIT   ((uint32_t)0x00007000U)
#define RTC_TSH_MIT_0 ((uint32_t)0x00001000U)
#define RTC_TSH_MIT_1 ((uint32_t)0x00002000U)
#define RTC_TSH_MIT_2 ((uint32_t)0x00004000U)
#define RTC_TSH_MIU   ((uint32_t)0x00000F00U)
#define RTC_TSH_MIU_0 ((uint32_t)0x00000100U)
#define RTC_TSH_MIU_1 ((uint32_t)0x00000200U)
#define RTC_TSH_MIU_2 ((uint32_t)0x00000400U)
#define RTC_TSH_MIU_3 ((uint32_t)0x00000800U)
#define RTC_TSH_SCT   ((uint32_t)0x00000070U)
#define RTC_TSH_SCT_0 ((uint32_t)0x00000010U)
#define RTC_TSH_SCT_1 ((uint32_t)0x00000020U)
#define RTC_TSH_SCT_2 ((uint32_t)0x00000040U)
#define RTC_TSH_SCU   ((uint32_t)0x0000000FU)
#define RTC_TSH_SCU_0 ((uint32_t)0x00000001U)
#define RTC_TSH_SCU_1 ((uint32_t)0x00000002U)
#define RTC_TSH_SCU_2 ((uint32_t)0x00000004U)
#define RTC_TSH_SCU_3 ((uint32_t)0x00000008U)

/** Bits definition for RTC_DATE register **/
#define RTC_DATE_YRT   ((uint32_t)0x00F00000U)
#define RTC_DATE_YRT_0 ((uint32_t)0x00100000U)
#define RTC_DATE_YRT_1 ((uint32_t)0x00200000U)
#define RTC_DATE_YRT_2 ((uint32_t)0x00400000U)
#define RTC_DATE_YRT_3 ((uint32_t)0x00800000U)
#define RTC_DATE_YRU   ((uint32_t)0x000F0000U)
#define RTC_DATE_YRU_0 ((uint32_t)0x00010000U)
#define RTC_DATE_YRU_1 ((uint32_t)0x00020000U)
#define RTC_DATE_YRU_2 ((uint32_t)0x00040000U)
#define RTC_DATE_YRU_3 ((uint32_t)0x00080000U)
#define RTC_DATE_WDU   ((uint32_t)0x0000E000U)
#define RTC_DATE_WDU_0 ((uint32_t)0x00002000U)
#define RTC_DATE_WDU_1 ((uint32_t)0x00004000U)
#define RTC_DATE_WDU_2 ((uint32_t)0x00008000U)
#define RTC_DATE_MOT   ((uint32_t)0x00001000U)
#define RTC_DATE_MOU   ((uint32_t)0x00000F00U)
#define RTC_DATE_MOU_0 ((uint32_t)0x00000100U)
#define RTC_DATE_MOU_1 ((uint32_t)0x00000200U)
#define RTC_DATE_MOU_2 ((uint32_t)0x00000400U)
#define RTC_DATE_MOU_3 ((uint32_t)0x00000800U)
#define RTC_DATE_DAT   ((uint32_t)0x00000030U)
#define RTC_DATE_DAT_0 ((uint32_t)0x00000010U)
#define RTC_DATE_DAT_1 ((uint32_t)0x00000020U)
#define RTC_DATE_DAU   ((uint32_t)0x0000000FU)
#define RTC_DATE_DAU_0 ((uint32_t)0x00000001U)
#define RTC_DATE_DAU_1 ((uint32_t)0x00000002U)
#define RTC_DATE_DAU_2 ((uint32_t)0x00000004U)
#define RTC_DATE_DAU_3 ((uint32_t)0x00000008U)

/** Bits definition for RTC_WRP register **/
#define RTC_WRP_PKEY      ((uint32_t)0x000000FFU)

/** Bits definition for RTC_SCTRL register **/
#define RTC_SCTRL_AD1S    ((uint32_t)0x80000000U)
#define RTC_SCTRL_SUBF    ((uint32_t)0x00007FFFU)

/** Bits definition for RTC_SUBS register **/
#define RTC_SUBS_SS       ((uint32_t)0x0000FFFFU)

/** Bits definition for RTC_TST register **/
#define RTC_TST_APM   ((uint32_t)0x00400000U)
#define RTC_TST_HOT   ((uint32_t)0x00300000U)
#define RTC_TST_HOT_0 ((uint32_t)0x00100000U)
#define RTC_TST_HOT_1 ((uint32_t)0x00200000U)
#define RTC_TST_HOU   ((uint32_t)0x000F0000U)
#define RTC_TST_HOU_0 ((uint32_t)0x00010000U)
#define RTC_TST_HOU_1 ((uint32_t)0x00020000U)
#define RTC_TST_HOU_2 ((uint32_t)0x00040000U)
#define RTC_TST_HOU_3 ((uint32_t)0x00080000U)
#define RTC_TST_MIT   ((uint32_t)0x00007000U)
#define RTC_TST_MIT_0 ((uint32_t)0x00001000U)
#define RTC_TST_MIT_1 ((uint32_t)0x00002000U)
#define RTC_TST_MIT_2 ((uint32_t)0x00004000U)
#define RTC_TST_MIU   ((uint32_t)0x00000F00U)
#define RTC_TST_MIU_0 ((uint32_t)0x00000100U)
#define RTC_TST_MIU_1 ((uint32_t)0x00000200U)
#define RTC_TST_MIU_2 ((uint32_t)0x00000400U)
#define RTC_TST_MIU_3 ((uint32_t)0x00000800U)
#define RTC_TST_SET   ((uint32_t)0x00000070U)
#define RTC_TST_SET_0 ((uint32_t)0x00000010U)
#define RTC_TST_SET_1 ((uint32_t)0x00000020U)
#define RTC_TST_SET_2 ((uint32_t)0x00000040U)
#define RTC_TST_SEU   ((uint32_t)0x0000000FU)
#define RTC_TST_SEU_0 ((uint32_t)0x00000001U)
#define RTC_TST_SEU_1 ((uint32_t)0x00000002U)
#define RTC_TST_SEU_2 ((uint32_t)0x00000004U)
#define RTC_TST_SEU_3 ((uint32_t)0x00000008U)

/** Bits definition for RTC_ALARMA register **/
#define RTC_ALARMA_MASK4  ((uint32_t)0x80000000U)
#define RTC_ALARMA_WKDSEL ((uint32_t)0x40000000U)
#define RTC_ALARMA_DTT    ((uint32_t)0x30000000U)
#define RTC_ALARMA_DTT_0  ((uint32_t)0x10000000U)
#define RTC_ALARMA_DTT_1  ((uint32_t)0x20000000U)
#define RTC_ALARMA_DTU    ((uint32_t)0x0F000000U)
#define RTC_ALARMA_DTU_0  ((uint32_t)0x01000000U)
#define RTC_ALARMA_DTU_1  ((uint32_t)0x02000000U)
#define RTC_ALARMA_DTU_2  ((uint32_t)0x04000000U)
#define RTC_ALARMA_DTU_3  ((uint32_t)0x08000000U)
#define RTC_ALARMA_MASK3  ((uint32_t)0x00800000U)
#define RTC_ALARMA_APM    ((uint32_t)0x00400000U)
#define RTC_ALARMA_HOT    ((uint32_t)0x00300000U)
#define RTC_ALARMA_HOT_0  ((uint32_t)0x00100000U)
#define RTC_ALARMA_HOT_1  ((uint32_t)0x00200000U)
#define RTC_ALARMA_HOU    ((uint32_t)0x000F0000U)
#define RTC_ALARMA_HOU_0  ((uint32_t)0x00010000U)
#define RTC_ALARMA_HOU_1  ((uint32_t)0x00020000U)
#define RTC_ALARMA_HOU_2  ((uint32_t)0x00040000U)
#define RTC_ALARMA_HOU_3  ((uint32_t)0x00080000U)
#define RTC_ALARMA_MASK2  ((uint32_t)0x00008000U)
#define RTC_ALARMA_MIT    ((uint32_t)0x00007000U)
#define RTC_ALARMA_MIT_0  ((uint32_t)0x00001000U)
#define RTC_ALARMA_MIT_1  ((uint32_t)0x00002000U)
#define RTC_ALARMA_MIT_2  ((uint32_t)0x00004000U)
#define RTC_ALARMA_MIU    ((uint32_t)0x00000F00U)
#define RTC_ALARMA_MIU_0  ((uint32_t)0x00000100U)
#define RTC_ALARMA_MIU_1  ((uint32_t)0x00000200U)
#define RTC_ALARMA_MIU_2  ((uint32_t)0x00000400U)
#define RTC_ALARMA_MIU_3  ((uint32_t)0x00000800U)
#define RTC_ALARMA_MASK1  ((uint32_t)0x00000080U)
#define RTC_ALARMA_SET    ((uint32_t)0x00000070U)
#define RTC_ALARMA_SET_0  ((uint32_t)0x00000010U)
#define RTC_ALARMA_SET_1  ((uint32_t)0x00000020U)
#define RTC_ALARMA_SET_2  ((uint32_t)0x00000040U)
#define RTC_ALARMA_SEU    ((uint32_t)0x0000000FU)
#define RTC_ALARMA_SEU_0  ((uint32_t)0x00000001U)
#define RTC_ALARMA_SEU_1  ((uint32_t)0x00000002U)
#define RTC_ALARMA_SEU_2  ((uint32_t)0x00000004U)
#define RTC_ALARMA_SEU_3  ((uint32_t)0x00000008U)

/** Bits definition for RTC_PRE register **/
#define RTC_PRE_DIVA      ((uint32_t)0x007F0000U)
#define RTC_PRE_DIVS      ((uint32_t)0x00007FFFU)

/** Bits definition for RTC_ALARMB register **/
#define RTC_ALARMB_MASK4  ((uint32_t)0x80000000U)
#define RTC_ALARMB_WKDSEL ((uint32_t)0x40000000U)
#define RTC_ALARMB_DTT    ((uint32_t)0x30000000U)
#define RTC_ALARMB_DTT_0  ((uint32_t)0x10000000U)
#define RTC_ALARMB_DTT_1  ((uint32_t)0x20000000U)
#define RTC_ALARMB_DTU    ((uint32_t)0x0F000000U)
#define RTC_ALARMB_DTU_0  ((uint32_t)0x01000000U)
#define RTC_ALARMB_DTU_1  ((uint32_t)0x02000000U)
#define RTC_ALARMB_DTU_2  ((uint32_t)0x04000000U)
#define RTC_ALARMB_DTU_3  ((uint32_t)0x08000000U)
#define RTC_ALARMB_MASK3  ((uint32_t)0x00800000U)
#define RTC_ALARMB_APM    ((uint32_t)0x00400000U)
#define RTC_ALARMB_HOT    ((uint32_t)0x00300000U)
#define RTC_ALARMB_HOT_0  ((uint32_t)0x00100000U)
#define RTC_ALARMB_HOT_1  ((uint32_t)0x00200000U)
#define RTC_ALARMB_HOU    ((uint32_t)0x000F0000U)
#define RTC_ALARMB_HOU_0  ((uint32_t)0x00010000U)
#define RTC_ALARMB_HOU_1  ((uint32_t)0x00020000U)
#define RTC_ALARMB_HOU_2  ((uint32_t)0x00040000U)
#define RTC_ALARMB_HOU_3  ((uint32_t)0x00080000U)
#define RTC_ALARMB_MASK2  ((uint32_t)0x00008000U)
#define RTC_ALARMB_MIT    ((uint32_t)0x00007000U)
#define RTC_ALARMB_MIT_0  ((uint32_t)0x00001000U)
#define RTC_ALARMB_MIT_1  ((uint32_t)0x00002000U)
#define RTC_ALARMB_MIT_2  ((uint32_t)0x00004000U)
#define RTC_ALARMB_MIU    ((uint32_t)0x00000F00U)
#define RTC_ALARMB_MIU_0  ((uint32_t)0x00000100U)
#define RTC_ALARMB_MIU_1  ((uint32_t)0x00000200U)
#define RTC_ALARMB_MIU_2  ((uint32_t)0x00000400U)
#define RTC_ALARMB_MIU_3  ((uint32_t)0x00000800U)
#define RTC_ALARMB_MASK1  ((uint32_t)0x00000080U)
#define RTC_ALARMB_SET    ((uint32_t)0x00000070U)
#define RTC_ALARMB_SET_0  ((uint32_t)0x00000010U)
#define RTC_ALARMB_SET_1  ((uint32_t)0x00000020U)
#define RTC_ALARMB_SET_2  ((uint32_t)0x00000040U)
#define RTC_ALARMB_SEU    ((uint32_t)0x0000000FU)
#define RTC_ALARMB_SEU_0  ((uint32_t)0x00000001U)
#define RTC_ALARMB_SEU_1  ((uint32_t)0x00000002U)
#define RTC_ALARMB_SEU_2  ((uint32_t)0x00000004U)
#define RTC_ALARMB_SEU_3  ((uint32_t)0x00000008U)

/** Bits definition for RTC_WKUPT register **/
#define RTC_WKUPT_WKUPT   ((uint32_t)0x0000FFFFU)

/** Bits definition for RTC_TMPCFG register **/
#define RTC_TMPCFG_TP3MF      ((uint32_t)0x08000000U)
#define RTC_TMPCFG_TP3INTEN   ((uint32_t)0x02000000U)
#define RTC_TMPCFG_TP2MF      ((uint32_t)0x01000000U)
#define RTC_TMPCFG_TP2INTEN   ((uint32_t)0x00400000U)
#define RTC_TMPCFG_TP1MF      ((uint32_t)0x00200000U)
#define RTC_TMPCFG_TP1INTEN   ((uint32_t)0x00080000U)

#define RTC_TMPCFG_TPPUDIS    ((uint32_t)0x00040000U)
#define RTC_TMPCFG_TPPRCH     ((uint32_t)0x00030000U)
#define RTC_TMPCFG_TPPRCH_0   ((uint32_t)0x00010000U)
#define RTC_TMPCFG_TPPRCH_1   ((uint32_t)0x00020000U)
#define RTC_TMPCFG_TPFLT      ((uint32_t)0x00003000U)
#define RTC_TMPCFG_TPFLT_0    ((uint32_t)0x00001000U)
#define RTC_TMPCFG_TPFLT_1    ((uint32_t)0x00002000U)

#define RTC_TMPCFG_TPFREQ     ((uint32_t)0x00000700U)
#define RTC_TMPCFG_TPFREQ_0   ((uint32_t)0x00000100U)
#define RTC_TMPCFG_TPFREQ_1   ((uint32_t)0x00000200U)
#define RTC_TMPCFG_TPFREQ_2   ((uint32_t)0x00000400U)
#define RTC_TMPCFG_TPTS       ((uint32_t)0x00000080U)
#define RTC_TMPCFG_TP3TRG     ((uint32_t)0x00000040U)
#define RTC_TMPCFG_TP3EN      ((uint32_t)0x00000020U)
#define RTC_TMPCFG_TP2TRG     ((uint32_t)0x00000010U)
#define RTC_TMPCFG_TP2EN      ((uint32_t)0x00000008U)
#define RTC_TMPCFG_TPINTEN    ((uint32_t)0x00000004U)
#define RTC_TMPCFG_TP1TRG     ((uint32_t)0x00000002U)
#define RTC_TMPCFG_TP1EN      ((uint32_t)0x00000001U)

/** Bits definition for RTC_ALRMASS register **/
#define RTC_ALRMASS_MASKSSB                  ((uint32_t)0x000F0000U)
#define RTC_ALRMASS_MASKSSB_0                ((uint32_t)0x00010000U)
#define RTC_ALRMASS_MASKSSB_1                ((uint32_t)0x00020000U)
#define RTC_ALRMASS_MASKSSB_2                ((uint32_t)0x00040000U)
#define RTC_ALRMASS_MASKSSB_3                ((uint32_t)0x00080000U)
#define RTC_ALRMASS_SSV                      ((uint32_t)0x00007FFFU)

/** Bits definition for RTC_OPT register **/
#define RTC_OPT_TYPE  ((uint32_t)0x00000001U)

/** Bits definition for RTC_ALRMBSS register **/
#define RTC_ALRMBSS_MASKSSB                  ((uint32_t)0x000F0000U)
#define RTC_ALRMBSS_MASKSSB_0                ((uint32_t)0x00010000U)
#define RTC_ALRMBSS_MASKSSB_1                ((uint32_t)0x00020000U)
#define RTC_ALRMBSS_MASKSSB_2                ((uint32_t)0x00040000U)
#define RTC_ALRMBSS_MASKSSB_3                ((uint32_t)0x00080000U)
#define RTC_ALRMBSS_SSV                      ((uint32_t)0x00007FFFU)

/** Bits definition for RTC_CALIB register **/
#define RTC_CALIB_CP    ((uint32_t)0x00000800U)
#define RTC_CALIB_CW8   ((uint32_t)0x00000400U)
#define RTC_CALIB_CW16  ((uint32_t)0x00000200U)
#define RTC_CALIB_CM    ((uint32_t)0x000001FFU)
#define RTC_CALIB_CM_0  ((uint32_t)0x00000001U)
#define RTC_CALIB_CM_1  ((uint32_t)0x00000002U)
#define RTC_CALIB_CM_2  ((uint32_t)0x00000004U)
#define RTC_CALIB_CM_3  ((uint32_t)0x00000008U)
#define RTC_CALIB_CM_4  ((uint32_t)0x00000010U)
#define RTC_CALIB_CM_5  ((uint32_t)0x00000020U)
#define RTC_CALIB_CM_6  ((uint32_t)0x00000040U)
#define RTC_CALIB_CM_7  ((uint32_t)0x00000080U)
#define RTC_CALIB_CM_8  ((uint32_t)0x00000100U)

/** Bits definition for RTC_TSSS register **/
#define RTC_TSSS_SSE ((uint32_t)0x0000FFFFU)

/** Bits definition for RTC_TSD register **/
#define RTC_TSD_YRT   ((uint32_t)0x00F00000U)
#define RTC_TSD_YRT_0 ((uint32_t)0x00100000U)
#define RTC_TSD_YRT_1 ((uint32_t)0x00200000U)
#define RTC_TSD_YRT_2 ((uint32_t)0x00400000U)
#define RTC_TSD_YRT_3 ((uint32_t)0x00800000U)
#define RTC_TSD_YRU   ((uint32_t)0x000F0000U)
#define RTC_TSD_YRU_0 ((uint32_t)0x00010000U)
#define RTC_TSD_YRU_1 ((uint32_t)0x00020000U)
#define RTC_TSD_YRU_2 ((uint32_t)0x00040000U)
#define RTC_TSD_YRU_3 ((uint32_t)0x00080000U)

#define RTC_TSD_MOT   ((uint32_t)0x00008000U)
#define RTC_TSD_WDU   ((uint32_t)0x00007000U)
#define RTC_TSD_WDU_0 ((uint32_t)0x00001000U)
#define RTC_TSD_WDU_1 ((uint32_t)0x00002000U)
#define RTC_TSD_WDU_2 ((uint32_t)0x00004000U)
#define RTC_TSD_MOU   ((uint32_t)0x00000F00U)
#define RTC_TSD_MOU_0 ((uint32_t)0x00000100U)
#define RTC_TSD_MOU_1 ((uint32_t)0x00000200U)
#define RTC_TSD_MOU_2 ((uint32_t)0x00000400U)
#define RTC_TSD_MOU_3 ((uint32_t)0x00000800U)
#define RTC_TSD_DAT   ((uint32_t)0x00000030U)
#define RTC_TSD_DAT_0 ((uint32_t)0x00000010U)
#define RTC_TSD_DAT_1 ((uint32_t)0x00000020U)
#define RTC_TSD_DAU   ((uint32_t)0x0000000FU)
#define RTC_TSD_DAU_0 ((uint32_t)0x00000001U)
#define RTC_TSD_DAU_1 ((uint32_t)0x00000002U)
#define RTC_TSD_DAU_2 ((uint32_t)0x00000004U)
#define RTC_TSD_DAU_3 ((uint32_t)0x00000008U)



/*** Window WATCHDOG ***/

/** Bit definition for WWDG_CTRL register **/
#define WWDG_CTRL_T      ((uint16_t)0x3FFF)     /*T[13:0] bits(14-bit counter (MSB to LSB)) */
#define WWDG_CTRL_T0     ((uint16_t)0x0001)     /* Bit 0  */
#define WWDG_CTRL_T1     ((uint16_t)0x0002)     /* Bit 1  */
#define WWDG_CTRL_T2     ((uint16_t)0x0004)     /* Bit 2  */
#define WWDG_CTRL_T3     ((uint16_t)0x0008)     /* Bit 3  */
#define WWDG_CTRL_T4     ((uint16_t)0x0010)     /* Bit 4  */
#define WWDG_CTRL_T5     ((uint16_t)0x0020)     /* Bit 5  */
#define WWDG_CTRL_T6     ((uint16_t)0x0040)     /* Bit 6  */
#define WWDG_CTRL_T7     ((uint16_t)0x0080)     /* Bit 7  */
#define WWDG_CTRL_T8     ((uint16_t)0x0100)     /* Bit 8  */
#define WWDG_CTRL_T9     ((uint16_t)0x0200)     /* Bit 9  */
#define WWDG_CTRL_T10    ((uint16_t)0x0400)     /* Bit 10 */
#define WWDG_CTRL_T11    ((uint16_t)0x0800)     /* Bit 11 */
#define WWDG_CTRL_T12    ((uint16_t)0x1000)     /* Bit 12 */
#define WWDG_CTRL_T13    ((uint16_t)0x2000)     /* Bit 13 */

#define WWDG_CTRL_ACTB   ((uint16_t)0x4000) /* Activation bit */

/**  Bit definition for WWDG_CFG register **/
#define WWDG_CFG_W       ((uint32_t)0x00003FFFU) /* W[13:0] bits (14-bit window value) */
#define WWDG_CFG_W0      ((uint32_t)0x00000001U) /* Bit 0 */
#define WWDG_CFG_W1      ((uint32_t)0x00000002U) /* Bit 1 */
#define WWDG_CFG_W2      ((uint32_t)0x00000004U) /* Bit 2 */
#define WWDG_CFG_W3      ((uint32_t)0x00000008U) /* Bit 3 */
#define WWDG_CFG_W4      ((uint32_t)0x00000010U) /* Bit 4 */
#define WWDG_CFG_W5      ((uint32_t)0x00000020U) /* Bit 5 */
#define WWDG_CFG_W6      ((uint32_t)0x00000040U) /* Bit 6 */
#define WWDG_CFG_W7      ((uint32_t)0x00000080U) /* Bit 7  */
#define WWDG_CFG_W8      ((uint32_t)0x00000100U) /* Bit 8  */
#define WWDG_CFG_W9      ((uint32_t)0x00000200U) /* Bit 9  */
#define WWDG_CFG_W10     ((uint32_t)0x00000400U) /* Bit 10 */
#define WWDG_CFG_W11     ((uint32_t)0x00000800U) /* Bit 11 */
#define WWDG_CFG_W12     ((uint32_t)0x00001000U) /* Bit 12 */
#define WWDG_CFG_W13     ((uint32_t)0x00002000U) /* Bit 13 */

#define WWDG_CFG_TIMERB  ((uint32_t)0x0000C000U) /* WDGTB[1:0] bits (Timer Base) */
#define WWDG_CFG_TIMERB0 ((uint32_t)0x00004000U) /* Bit 0 */
#define WWDG_CFG_TIMERB1 ((uint32_t)0x00008000U) /* Bit 1 */

#define WWDG_CFG_EWINT   ((uint32_t)0x00010000U) /* Early Wakeup Interrupt */

/** Bit definition for WWDG_STS register **/
#define WWDG_STS_EWINTF  ((uint8_t)0x01U)        /* Early Wakeup Interrupt Flag */



/*** Independent watchdog ***/

/** Bit definition for IWDG_KEY register **/
#define IWDG_KEY_KEYV     ((uint16_t)0xFFFFU) /* Key value (write only, read 0000h) */

/** Bit definition for IWDG_PREDIV register **/
#define IWDG_PREDIV_PD    ((uint8_t)0x07U)    /* PD[2:0] (Prescaler divider) */
#define IWDG_PREDIV_PD0   ((uint8_t)0x01U)    /* Bit 0 */
#define IWDG_PREDIV_PD1   ((uint8_t)0x02U)    /* Bit 1 */
#define IWDG_PREDIV_PD2   ((uint8_t)0x04U)    /* Bit 2 */


/** Bit definition for IWDG_RELV register **/
#define IWDG_RELV_REL     ((uint16_t)0x0FFFU) /* Watchdog counter reload value */

/** Bit definition for IWDG_STS register **/
#define IWDG_STS_PVU      ((uint8_t)0x01U)    /* Watchdog prescaler value update */
#define IWDG_STS_CRVU     ((uint8_t)0x02U)    /* Watchdog counter reload value update */
#define IWDG_STS_RUNFREF  ((uint8_t)0x04U)    /* The freeze flag of run mode */
#define IWDG_STS_LPFREF   ((uint8_t)0x08U)    /* The freeze flag of low power mode */

/** Bit definition for IWDG_FREEZE register **/
#define  IWDG_FREEZE_LPFREV ((uint32_t)0x0000FFFFU)  /* Watchdog freeze enable/disable when MCU enter low power mode */


/*** Beeper ***/

/** Bit definition for BEEPER_CTRL register **/
#define BEERPER_CTRL_BEEPEN        ((uint32_t)0x00000001U)  /* Bit[0] */

#define BEEPER_CTRL_FREQ_SEL       ((uint32_t)0x0000007EU)  /* Beeper output frequency selection */
#define BEEPER_CTRL_FREQ_SEL_0     ((uint32_t)0x00000002U)  /* Bit[1] */
#define BEEPER_CTRL_FREQ_SEL_1     ((uint32_t)0x00000004U)  /* Bit[2] */
#define BEEPER_CTRL_FREQ_SEL_2     ((uint32_t)0x00000008U)  /* Bit[3] */
#define BEEPER_CTRL_FREQ_SEL_3     ((uint32_t)0x00000010U)  /* Bit[4] */
#define BEEPER_CTRL_FREQ_SEL_4     ((uint32_t)0x00000020U)  /* Bit[5] */
#define BEEPER_CTRL_FREQ_SEL_5     ((uint32_t)0x00000040U)  /* Bit[6] */

/****       Controller Area Network     ****/
/**** CAN control and status registers ****/
/**  Bit definition for CAN_MCTRL register  ****/
#define CAN_MCTRL_INIRQ                         ((uint16_t)0x0001U) /* Initialization Request */
#define CAN_MCTRL_SLPRQ                         ((uint16_t)0x0002U) /* Sleep Mode Request */
#define CAN_MCTRL_TXFP                          ((uint16_t)0x0004U) /* Transmit DATFIFO Priority */
#define CAN_MCTRL_RFLM                          ((uint16_t)0x0008U) /* Receive DATFIFO Locked Mode */
#define CAN_MCTRL_NART                          ((uint16_t)0x0010U) /* No Automatic Retransmission */
#define CAN_MCTRL_AWKUM                         ((uint16_t)0x0020U) /* Automatic Wakeup Mode */
#define CAN_MCTRL_ABOM                          ((uint16_t)0x0040U) /* Automatic Bus-Off Management */
#define CAN_MCTRL_TTCM                          ((uint16_t)0x0080U) /* Time Triggered Communication Mode */
#define CAN_MCTRL_MRST                          ((uint16_t)0x8000U) /* CAN software master reset */
#define CAN_MCTRL_DBGF                          ((uint32_t)0x00010000U) /* CAN Debug freeze */

/**  Bit definition for CAN_MSTS register  ****/
#define CAN_MSTS_INIAK                          ((uint16_t)0x0001U) /* Initialization Acknowledge */
#define CAN_MSTS_SLPAK                          ((uint16_t)0x0002U) /* Sleep Acknowledge */
#define CAN_MSTS_ERRINT                         ((uint16_t)0x0004U) /* Error Interrupt */
#define CAN_MSTS_WKUINT                         ((uint16_t)0x0008U) /* Wakeup Interrupt */
#define CAN_MSTS_SLAKINT                        ((uint16_t)0x0010U) /* Sleep Acknowledge Interrupt */
#define CAN_MSTS_TXMD                           ((uint16_t)0x0100U) /* Transmit Mode */
#define CAN_MSTS_RXMD                           ((uint16_t)0x0200U) /* Receive Mode */
#define CAN_MSTS_LSMP                           ((uint16_t)0x0400U) /* Last Sample Point */
#define CAN_MSTS_RXS                            ((uint16_t)0x0800U) /* CAN Rx Signal */

/**  Bit definition for CAN_TSTS register  ****/
#define CAN_TSTS_RQCPM0                         ((uint32_t)0x00000001U) /* Request Completed Mailbox0 */
#define CAN_TSTS_TXOKM0                         ((uint32_t)0x00000002U) /* Transmission OK of Mailbox0 */
#define CAN_TSTS_ALSTM0                         ((uint32_t)0x00000004U) /* Arbitration Lost for Mailbox0 */
#define CAN_TSTS_TERRM0                         ((uint32_t)0x00000008U) /* Transmission Error of Mailbox0 */
#define CAN_TSTS_ABRQM0                         ((uint32_t)0x00000080U) /* Abort Request for Mailbox0 */
#define CAN_TSTS_RQCPM1                         ((uint32_t)0x00000100U) /* Request Completed Mailbox1 */
#define CAN_TSTS_TXOKM1                         ((uint32_t)0x00000200U) /* Transmission OK of Mailbox1 */
#define CAN_TSTS_ALSTM1                         ((uint32_t)0x00000400U) /* Arbitration Lost for Mailbox1 */
#define CAN_TSTS_TERRM1                         ((uint32_t)0x00000800U) /* Transmission Error of Mailbox1 */
#define CAN_TSTS_ABRQM1                         ((uint32_t)0x00008000U) /* Abort Request for Mailbox 1 */
#define CAN_TSTS_RQCPM2                         ((uint32_t)0x00010000U) /* Request Completed Mailbox2 */
#define CAN_TSTS_TXOKM2                         ((uint32_t)0x00020000U) /* Transmission OK of Mailbox 2 */
#define CAN_TSTS_ALSTM2                         ((uint32_t)0x00040000U) /* Arbitration Lost for mailbox 2 */
#define CAN_TSTS_TERRM2                         ((uint32_t)0x00080000U) /* Transmission Error of Mailbox 2 */
#define CAN_TSTS_ABRQM2                         ((uint32_t)0x00800000U) /* Abort Request for Mailbox 2 */

#define CAN_TSTS_CODE                           ((uint32_t)0x03000000U) /* Mailbox Code */
#define CAN_TSTS_CODE_0                         ((uint32_t)0x01000000U) /* Bit 0 */
#define CAN_TSTS_CODE_1                         ((uint32_t)0x02000000U) /* Bit 1 */

#define CAN_TSTS_TMEM  ((uint32_t)0x1C000000U) /* TME[2:0] bits */
#define CAN_TSTS_TMEM0 ((uint32_t)0x04000000U) /* Transmit Mailbox 0 Empty */
#define CAN_TSTS_TMEM1 ((uint32_t)0x08000000U) /* Transmit Mailbox 1 Empty */
#define CAN_TSTS_TMEM2 ((uint32_t)0x10000000U) /* Transmit Mailbox 2 Empty */

#define CAN_TSTS_LOWM  ((uint32_t)0xE0000000U) /* LOW[2:0] bits */
#define CAN_TSTS_LOWM0 ((uint32_t)0x20000000U) /* Lowest Priority Flag for Mailbox 0 */
#define CAN_TSTS_LOWM1 ((uint32_t)0x40000000U) /* Lowest Priority Flag for Mailbox 1 */
#define CAN_TSTS_LOWM2 ((uint32_t)0x80000000U) /* Lowest Priority Flag for Mailbox 2 */

/** Bit definition for CAN_RFF0 register **/
#define CAN_RFF0_FFMP0      ((uint8_t)0x03U) /* DATFIFO 0 Message Pending */
#define CAN_RFF0_FFMP0_0    ((uint8_t)0x01U) /* Bit 0 */
#define CAN_RFF0_FFMP0_1    ((uint8_t)0x02U) /* Bit 1 */

#define CAN_RFF0_FFULL0 ((uint8_t)0x08U) /* DATFIFO 0 Full */
#define CAN_RFF0_FFOVR0 ((uint8_t)0x10U) /* DATFIFO 0 Overrun */
#define CAN_RFF0_RFFOM0 ((uint8_t)0x20U) /* Release DATFIFO 0 Output Mailbox */

/** Bit definition for CAN_RFF1 register **/
#define CAN_RFF1_FFMP1      ((uint8_t)0x03U) /* DATFIFO 1 Message Pending */
#define CAN_RFF1_FFMP1_0    ((uint8_t)0x01U) /* Bit 0 */
#define CAN_RFF1_FFMP1_1    ((uint8_t)0x02U) /* Bit 1 */

#define CAN_RFF1_FFULL1     ((uint8_t)0x08U) /* DATFIFO 1 Full */
#define CAN_RFF1_FFOVR1     ((uint8_t)0x10U) /* DATFIFO 1 Overrun */
#define CAN_RFF1_RFFOM1     ((uint8_t)0x20U) /* Release DATFIFO 1 Output Mailbox */

/** Bit definition for CAN_INTE register **/
#define CAN_INTE_TMEITE  ((uint32_t)0x00000001U) /* Transmit Mailbox Empty Interrupt Enable */
#define CAN_INTE_FMPITE0 ((uint32_t)0x00000002U) /* DATFIFO Message Pending Interrupt Enable */
#define CAN_INTE_FFITE0  ((uint32_t)0x00000004U) /* DATFIFO Full Interrupt Enable */
#define CAN_INTE_FOVITE0 ((uint32_t)0x00000008U) /* DATFIFO Overrun Interrupt Enable */
#define CAN_INTE_FMPITE1 ((uint32_t)0x00000010U) /* DATFIFO Message Pending Interrupt Enable */
#define CAN_INTE_FFITE1  ((uint32_t)0x00000020U) /* DATFIFO Full Interrupt Enable */
#define CAN_INTE_FOVITE1 ((uint32_t)0x00000040U) /* DATFIFO Overrun Interrupt Enable */
#define CAN_INTE_EWGITE  ((uint32_t)0x00000100U) /* Error Warning Interrupt Enable */
#define CAN_INTE_EPVITE  ((uint32_t)0x00000200U) /* Error Passive Interrupt Enable */
#define CAN_INTE_BOFITE  ((uint32_t)0x00000400U) /* Bus-Off Interrupt Enable */
#define CAN_INTE_LECITE  ((uint32_t)0x00000800U) /* Last Error Code Interrupt Enable */
#define CAN_INTE_ERRITE  ((uint32_t)0x00008000U) /* Error Interrupt Enable */
#define CAN_INTE_WKUITE  ((uint32_t)0x00010000U) /* Wakeup Interrupt Enable */
#define CAN_INTE_SLKITE  ((uint32_t)0x00020000U) /* Sleep Interrupt Enable */

/** Bit definition for CAN_ESTS register **/
#define CAN_ESTS_EWGFL ((uint32_t)0x00000001U) /* Error Warning Flag */
#define CAN_ESTS_EPVFL ((uint32_t)0x00000002U) /* Error Passive Flag */
#define CAN_ESTS_BOFFL ((uint32_t)0x00000004U) /* Bus-Off Flag */

#define CAN_ESTS_LEC   ((uint32_t)0x00000070U) /* LEC[2:0] bits (Last Error Code) */
#define CAN_ESTS_LEC_0 ((uint32_t)0x00000010U) /* Bit 0 */
#define CAN_ESTS_LEC_1 ((uint32_t)0x00000020U) /* Bit 1 */
#define CAN_ESTS_LEC_2 ((uint32_t)0x00000040U) /* Bit 2 */

#define CAN_ESTS_TXEC  ((uint32_t)0x00FF0000U) /* Least significant byte of the 9-bit Transmit Error Counter */
#define CAN_ESTS_RXEC  ((uint32_t)0xFF000000U) /* Receive Error Counter */

/** Bit definition for CAN_BTIM register **/
#define CAN_BTIM_BRTP   ((uint32_t)0x000003FFU) /* Baud Rate Prescaler */

#define CAN_BTIM_TBS1   ((uint32_t)0x000F0000U) /* Time Segment 1 */
#define CAN_BTIM_TBS1_0 ((uint32_t)0x00010000U) /* Bit 0 */
#define CAN_BTIM_TBS1_1 ((uint32_t)0x00020000U) /* Bit 1 */
#define CAN_BTIM_TBS1_2 ((uint32_t)0x00040000U) /* Bit 2 */
#define CAN_BTIM_TBS1_3 ((uint32_t)0x00080000U) /* Bit 3 */

#define CAN_BTIM_TBS2   ((uint32_t)0x00700000U) /* Time Segment 2 */
#define CAN_BTIM_TBS2_0 ((uint32_t)0x00100000U) /* Bit 0 */
#define CAN_BTIM_TBS2_1 ((uint32_t)0x00200000U) /* Bit 1 */
#define CAN_BTIM_TBS2_2 ((uint32_t)0x00400000U) /* Bit 2 */

#define CAN_BTIM_RSJW   ((uint32_t)0x03000000U) /* Resynchronization Jump Width */
#define CAN_BTIM_RSJW_0 ((uint32_t)0x01000000U) /* Bit 0 */
#define CAN_BTIM_RSJW_1 ((uint32_t)0x02000000U) /* Bit 1 */

#define CAN_BTIM_LBM  ((uint32_t)0x40000000U) /* Loop Back Mode (Debug) */
#define CAN_BTIM_SLM  ((uint32_t)0x80000000U) /* Silent Mode */

/*** Mailbox registers ***/
/** Bit definition for CAN_TMI0 register **/
#define CAN_TMI0_TXRQ  ((uint32_t)0x00000001U) /* Transmit Mailbox Request */
#define CAN_TMI0_RTRQ  ((uint32_t)0x00000002U) /* Remote Transmission Request */
#define CAN_TMI0_IDE   ((uint32_t)0x00000004U) /* Identifier Extension */
#define CAN_TMI0_EXTID ((uint32_t)0x001FFFF8U) /* Extended Identifier */
#define CAN_TMI0_STDID ((uint32_t)0xFFE00000U) /* Standard Identifier or Extended Identifier */

/** Bit definition for CAN_TMDT0 register **/
#define CAN_TMDT0_DLC  ((uint32_t)0x0000000FU) /* Data Length Code */
#define CAN_TMDT0_TGT  ((uint32_t)0x00000100U) /* Transmit Global Time */
#define CAN_TMDT0_MTIM ((uint32_t)0xFFFF0000U) /* Message Time Stamp */

/** Bit definition for CAN_TMDL0 register **/
#define CAN_TMDL0_DATA0 ((uint32_t)0x000000FFU) /* Data byte 0 */
#define CAN_TMDL0_DATA1 ((uint32_t)0x0000FF00U) /* Data byte 1 */
#define CAN_TMDL0_DATA2 ((uint32_t)0x00FF0000U) /* Data byte 2 */
#define CAN_TMDL0_DATA3 ((uint32_t)0xFF000000U) /* Data byte 3 */

/** Bit definition for CAN_TMDH0 register **/
#define CAN_TMDH0_DATA4 ((uint32_t)0x000000FFU) /* Data byte 4 */
#define CAN_TMDH0_DATA5 ((uint32_t)0x0000FF00U) /* Data byte 5 */
#define CAN_TMDH0_DATA6 ((uint32_t)0x00FF0000U) /* Data byte 6 */
#define CAN_TMDH0_DATA7 ((uint32_t)0xFF000000U) /* Data byte 7 */

/** Bit definition for CAN_TMI1 register **/
#define CAN_TMI1_TXRQ  ((uint32_t)0x00000001U) /* Transmit Mailbox Request */
#define CAN_TMI1_RTRQ  ((uint32_t)0x00000002U) /* Remote Transmission Request */
#define CAN_TMI1_IDE   ((uint32_t)0x00000004U) /* Identifier Extension */
#define CAN_TMI1_EXTID ((uint32_t)0x001FFFF8U) /* Extended Identifier */
#define CAN_TMI1_STDID ((uint32_t)0xFFE00000U) /* Standard Identifier or Extended Identifier */

/** Bit definition for CAN_TMDT1 register **/
#define CAN_TMDT1_DLC  ((uint32_t)0x0000000FU) /* Data Length Code */
#define CAN_TMDT1_TGT  ((uint32_t)0x00000100U) /* Transmit Global Time */
#define CAN_TMDT1_MTIM ((uint32_t)0xFFFF0000U) /* Message Time Stamp */

/** Bit definition for CAN_TMDL1 register **/
#define CAN_TMDL1_DATA0 ((uint32_t)0x000000FFU) /* Data byte 0 */
#define CAN_TMDL1_DATA1 ((uint32_t)0x0000FF00U) /* Data byte 1 */
#define CAN_TMDL1_DATA2 ((uint32_t)0x00FF0000U) /* Data byte 2 */
#define CAN_TMDL1_DATA3 ((uint32_t)0xFF000000U) /* Data byte 3 */

/** Bit definition for CAN_TMDH1 register **/
#define CAN_TMDH1_DATA4 ((uint32_t)0x000000FFU) /* Data byte 4 */
#define CAN_TMDH1_DATA5 ((uint32_t)0x0000FF00U) /* Data byte 5 */
#define CAN_TMDH1_DATA6 ((uint32_t)0x00FF0000U) /* Data byte 6 */
#define CAN_TMDH1_DATA7 ((uint32_t)0xFF000000U) /* Data byte 7 */

/** Bit definition for CAN_TMI2 register **/
#define CAN_TMI2_TXRQ  ((uint32_t)0x00000001U) /* Transmit Mailbox Request */
#define CAN_TMI2_RTRQ  ((uint32_t)0x00000002U) /* Remote Transmission Request */
#define CAN_TMI2_IDE   ((uint32_t)0x00000004U) /* Identifier Extension */
#define CAN_TMI2_EXTID ((uint32_t)0x001FFFF8U) /* Extended identifier */
#define CAN_TMI2_STDID ((uint32_t)0xFFE00000U) /* Standard Identifier or Extended Identifier */

/** Bit definition for CAN_TMDT2 register **/
#define CAN_TMDT2_DLC  ((uint32_t)0x0000000FU) /* Data Length Code */
#define CAN_TMDT2_TGT  ((uint32_t)0x00000100U) /* Transmit Global Time */
#define CAN_TMDT2_MTIM ((uint32_t)0xFFFF0000U) /* Message Time Stamp */

/** Bit definition for CAN_TMDL2 register **/
#define CAN_TMDL2_DATA0 ((uint32_t)0x000000FFU) /* Data byte 0 */
#define CAN_TMDL2_DATA1 ((uint32_t)0x0000FF00U) /* Data byte 1 */
#define CAN_TMDL2_DATA2 ((uint32_t)0x00FF0000U) /* Data byte 2 */
#define CAN_TMDL2_DATA3 ((uint32_t)0xFF000000U) /* Data byte 3 */

/** Bit definition for CAN_TMDH2 register **/
#define CAN_TMDH2_DATA4 ((uint32_t)0x000000FFU) /* Data byte 4 */
#define CAN_TMDH2_DATA5 ((uint32_t)0x0000FF00U) /* Data byte 5 */
#define CAN_TMDH2_DATA6 ((uint32_t)0x00FF0000U) /* Data byte 6 */
#define CAN_TMDH2_DATA7 ((uint32_t)0xFF000000U) /* Data byte 7 */

/** Bit definition for CAN_RMI0 register **/
#define CAN_RMI0_RTRQ  ((uint32_t)0x00000002U) /* Remote Transmission Request */
#define CAN_RMI0_IDE   ((uint32_t)0x00000004U) /* Identifier Extension */
#define CAN_RMI0_EXTID ((uint32_t)0x001FFFF8U) /* Extended Identifier */
#define CAN_RMI0_STDID ((uint32_t)0xFFE00000U) /* Standard Identifier or Extended Identifier */

/** Bit definition for CAN_RMDT0 register **/
#define CAN_RMDT0_DLC  ((uint32_t)0x0000000FU) /* Data Length Code */
#define CAN_RMDT0_FMI  ((uint32_t)0x0000FF00U) /* Filter Match Index */
#define CAN_RMDT0_MTIM ((uint32_t)0xFFFF0000U) /* Message Time Stamp */

/** Bit definition for CAN_RMDL0 register **/
#define CAN_RMDL0_DATA0 ((uint32_t)0x000000FFU) /* Data byte 0 */
#define CAN_RMDL0_DATA1 ((uint32_t)0x0000FF00U) /* Data byte 1 */
#define CAN_RMDL0_DATA2 ((uint32_t)0x00FF0000U) /* Data byte 2 */
#define CAN_RMDL0_DATA3 ((uint32_t)0xFF000000U) /* Data byte 3 */

/** Bit definition for CAN_RMDH0 register **/
#define CAN_RMDH0_DATA4 ((uint32_t)0x000000FFU) /* Data byte 4 */
#define CAN_RMDH0_DATA5 ((uint32_t)0x0000FF00U) /* Data byte 5 */
#define CAN_RMDH0_DATA6 ((uint32_t)0x00FF0000U) /* Data byte 6 */
#define CAN_RMDH0_DATA7 ((uint32_t)0xFF000000U) /* Data byte 7 */

/** Bit definition for CAN_RMI1 register **/
#define CAN_RMI1_RTRQ  ((uint32_t)0x00000002U) /* Remote Transmission Request */
#define CAN_RMI1_IDE   ((uint32_t)0x00000004U) /* Identifier Extension */
#define CAN_RMI1_EXTID ((uint32_t)0x001FFFF8U) /* Extended identifier */
#define CAN_RMI1_STDID ((uint32_t)0xFFE00000U) /* Standard Identifier or Extended Identifier */

/** Bit definition for CAN_RMDT1 register **/
#define CAN_RMDT1_DLC  ((uint32_t)0x0000000FU) /* Data Length Code */
#define CAN_RMDT1_FMI  ((uint32_t)0x0000FF00U) /* Filter Match Index */
#define CAN_RMDT1_MTIM ((uint32_t)0xFFFF0000U) /* Message Time Stamp */

/** Bit definition for CAN_RMDL1 register **/
#define CAN_RMDL1_DATA0 ((uint32_t)0x000000FFU) /* Data byte 0 */
#define CAN_RMDL1_DATA1 ((uint32_t)0x0000FF00U) /* Data byte 1 */
#define CAN_RMDL1_DATA2 ((uint32_t)0x00FF0000U) /* Data byte 2 */
#define CAN_RMDL1_DATA3 ((uint32_t)0xFF000000U) /* Data byte 3 */

/** Bit definition for CAN_RMDH1 register **/
#define CAN_RMDH1_DATA4 ((uint32_t)0x000000FFU) /* Data byte 4 */
#define CAN_RMDH1_DATA5 ((uint32_t)0x0000FF00U) /* Data byte 5 */
#define CAN_RMDH1_DATA6 ((uint32_t)0x00FF0000U) /* Data byte 6 */
#define CAN_RMDH1_DATA7 ((uint32_t)0xFF000000U) /* Data byte 7 */

/*** CAN filter registers ***/
/** Bit definition for CAN_FMC register **/
#define CAN_FMC_FINITM ((uint32_t)0x01U) /* Filter Init Mode */

/**  Bit definition for CAN_FM1 register  ***/
#define CAN_FM1_FB                              ((uint16_t)0x3FFFU) /* Filter Mode */
#define CAN_FM1_FB0                             ((uint16_t)0x0001U) /* Filter Init Mode bit 0 */
#define CAN_FM1_FB1                             ((uint16_t)0x0002U) /* Filter Init Mode bit 1 */
#define CAN_FM1_FB2                             ((uint16_t)0x0004U) /* Filter Init Mode bit 2 */
#define CAN_FM1_FB3                             ((uint16_t)0x0008U) /* Filter Init Mode bit 3 */
#define CAN_FM1_FB4                             ((uint16_t)0x0010U) /* Filter Init Mode bit 4 */
#define CAN_FM1_FB5                             ((uint16_t)0x0020U) /* Filter Init Mode bit 5 */
#define CAN_FM1_FB6                             ((uint16_t)0x0040U) /* Filter Init Mode bit 6 */
#define CAN_FM1_FB7                             ((uint16_t)0x0080U) /* Filter Init Mode bit 7 */
#define CAN_FM1_FB8                             ((uint16_t)0x0100U) /* Filter Init Mode bit 8 */
#define CAN_FM1_FB9                             ((uint16_t)0x0200U) /* Filter Init Mode bit 9 */
#define CAN_FM1_FB10                            ((uint16_t)0x0400U) /* Filter Init Mode bit 10 */
#define CAN_FM1_FB11                            ((uint16_t)0x0800U) /* Filter Init Mode bit 11 */
#define CAN_FM1_FB12                            ((uint16_t)0x1000U) /* Filter Init Mode bit 12 */
#define CAN_FM1_FB13                            ((uint16_t)0x2000U) /* Filter Init Mode bit 13 */

/**  Bit definition for CAN_FS1 register  ***/
#define CAN_FS1_FSC                             ((uint16_t)0x3FFFU) /* Filter Scale Configuration */
#define CAN_FS1_FSC0                            ((uint16_t)0x0001U) /* Filter Scale Configuration bit 0 */
#define CAN_FS1_FSC1                            ((uint16_t)0x0002U) /* Filter Scale Configuration bit 1 */
#define CAN_FS1_FSC2                            ((uint16_t)0x0004U) /* Filter Scale Configuration bit 2 */
#define CAN_FS1_FSC3                            ((uint16_t)0x0008U) /* Filter Scale Configuration bit 3 */
#define CAN_FS1_FSC4                            ((uint16_t)0x0010U) /* Filter Scale Configuration bit 4 */
#define CAN_FS1_FSC5                            ((uint16_t)0x0020U) /* Filter Scale Configuration bit 5 */
#define CAN_FS1_FSC6                            ((uint16_t)0x0040U) /* Filter Scale Configuration bit 6 */
#define CAN_FS1_FSC7                            ((uint16_t)0x0080U) /* Filter Scale Configuration bit 7 */
#define CAN_FS1_FSC8                            ((uint16_t)0x0100U) /* Filter Scale Configuration bit 8 */
#define CAN_FS1_FSC9                            ((uint16_t)0x0200U) /* Filter Scale Configuration bit 9 */
#define CAN_FS1_FSC10                           ((uint16_t)0x0400U) /* Filter Scale Configuration bit 10 */
#define CAN_FS1_FSC11                           ((uint16_t)0x0800U) /* Filter Scale Configuration bit 11 */
#define CAN_FS1_FSC12                           ((uint16_t)0x1000U) /* Filter Scale Configuration bit 12 */
#define CAN_FS1_FSC13                           ((uint16_t)0x2000U) /* Filter Scale Configuration bit 13 */

/**  Bit definition for CAN_FFA1 register  ***/
#define CAN_FFA1_FAF                            ((uint16_t)0x3FFFU) /* Filter DATFIFO Assignment */
#define CAN_FFA1_FAF0                           ((uint16_t)0x0001U) /* Filter DATFIFO Assignment for Filter 0 */
#define CAN_FFA1_FAF1                           ((uint16_t)0x0002U) /* Filter DATFIFO Assignment for Filter 1 */
#define CAN_FFA1_FAF2                           ((uint16_t)0x0004U) /* Filter DATFIFO Assignment for Filter 2 */
#define CAN_FFA1_FAF3                           ((uint16_t)0x0008U) /* Filter DATFIFO Assignment for Filter 3 */
#define CAN_FFA1_FAF4                           ((uint16_t)0x0010U) /* Filter DATFIFO Assignment for Filter 4 */
#define CAN_FFA1_FAF5                           ((uint16_t)0x0020U) /* Filter DATFIFO Assignment for Filter 5 */
#define CAN_FFA1_FAF6                           ((uint16_t)0x0040U) /* Filter DATFIFO Assignment for Filter 6 */
#define CAN_FFA1_FAF7                           ((uint16_t)0x0080U) /* Filter DATFIFO Assignment for Filter 7 */
#define CAN_FFA1_FAF8                           ((uint16_t)0x0100U) /* Filter DATFIFO Assignment for Filter 8 */
#define CAN_FFA1_FAF9                           ((uint16_t)0x0200U) /* Filter DATFIFO Assignment for Filter 9 */
#define CAN_FFA1_FAF10                          ((uint16_t)0x0400U) /* Filter DATFIFO Assignment for Filter 10 */
#define CAN_FFA1_FAF11                          ((uint16_t)0x0800U) /* Filter DATFIFO Assignment for Filter 11 */
#define CAN_FFA1_FAF12                          ((uint16_t)0x1000U) /* Filter DATFIFO Assignment for Filter 12 */
#define CAN_FFA1_FAF13                          ((uint16_t)0x2000U) /* Filter DATFIFO Assignment for Filter 13 */

/**  Bit definition for CAN_FA1 register  ***/
#define CAN_FA1_FAC                             ((uint16_t)0x3FFFU) /* Filter Active */
#define CAN_FA1_FAC0                            ((uint16_t)0x0001U) /* Filter 0 Active */
#define CAN_FA1_FAC1                            ((uint16_t)0x0002U) /* Filter 1 Active */
#define CAN_FA1_FAC2                            ((uint16_t)0x0004U) /* Filter 2 Active */
#define CAN_FA1_FAC3                            ((uint16_t)0x0008U) /* Filter 3 Active */
#define CAN_FA1_FAC4                            ((uint16_t)0x0010U) /* Filter 4 Active */
#define CAN_FA1_FAC5                            ((uint16_t)0x0020U) /* Filter 5 Active */
#define CAN_FA1_FAC6                            ((uint16_t)0x0040U) /* Filter 6 Active */
#define CAN_FA1_FAC7                            ((uint16_t)0x0080U) /* Filter 7 Active */
#define CAN_FA1_FAC8                            ((uint16_t)0x0100U) /* Filter 8 Active */
#define CAN_FA1_FAC9                            ((uint16_t)0x0200U) /* Filter 9 Active */
#define CAN_FA1_FAC10                           ((uint16_t)0x0400U) /* Filter 10 Active */
#define CAN_FA1_FAC11                           ((uint16_t)0x0800U) /* Filter 11 Active */
#define CAN_FA1_FAC12                           ((uint16_t)0x1000U) /* Filter 12 Active */
#define CAN_FA1_FAC13                           ((uint16_t)0x2000U) /* Filter 13 Active */

/**  Bit definition for CAN_F0R1 register  ***/
#define CAN_F0R1_FBC0                           ((uint32_t)0x00000001U) /* Filter bit 0 */
#define CAN_F0R1_FBC1                           ((uint32_t)0x00000002U) /* Filter bit 1 */
#define CAN_F0R1_FBC2                           ((uint32_t)0x00000004U) /* Filter bit 2 */
#define CAN_F0R1_FBC3                           ((uint32_t)0x00000008U) /* Filter bit 3 */
#define CAN_F0R1_FBC4                           ((uint32_t)0x00000010U) /* Filter bit 4 */
#define CAN_F0R1_FBC5                           ((uint32_t)0x00000020U) /* Filter bit 5 */
#define CAN_F0R1_FBC6                           ((uint32_t)0x00000040U) /* Filter bit 6 */
#define CAN_F0R1_FBC7                           ((uint32_t)0x00000080U) /* Filter bit 7 */
#define CAN_F0R1_FBC8                           ((uint32_t)0x00000100U) /* Filter bit 8 */
#define CAN_F0R1_FBC9                           ((uint32_t)0x00000200U) /* Filter bit 9 */
#define CAN_F0R1_FBC10                          ((uint32_t)0x00000400U) /* Filter bit 10 */
#define CAN_F0R1_FBC11                          ((uint32_t)0x00000800U) /* Filter bit 11 */
#define CAN_F0R1_FBC12                          ((uint32_t)0x00001000U) /* Filter bit 12 */
#define CAN_F0R1_FBC13                          ((uint32_t)0x00002000U) /* Filter bit 13 */
#define CAN_F0R1_FBC14                          ((uint32_t)0x00004000U) /* Filter bit 14 */
#define CAN_F0R1_FBC15                          ((uint32_t)0x00008000U) /* Filter bit 15 */
#define CAN_F0R1_FBC16                          ((uint32_t)0x00010000U) /* Filter bit 16 */
#define CAN_F0R1_FBC17                          ((uint32_t)0x00020000U) /* Filter bit 17 */
#define CAN_F0R1_FBC18                          ((uint32_t)0x00040000U) /* Filter bit 18 */
#define CAN_F0R1_FBC19                          ((uint32_t)0x00080000U) /* Filter bit 19 */
#define CAN_F0R1_FBC20                          ((uint32_t)0x00100000U) /* Filter bit 20 */
#define CAN_F0R1_FBC21                          ((uint32_t)0x00200000U) /* Filter bit 21 */
#define CAN_F0R1_FBC22                          ((uint32_t)0x00400000U) /* Filter bit 22 */
#define CAN_F0R1_FBC23                          ((uint32_t)0x00800000U) /* Filter bit 23 */
#define CAN_F0R1_FBC24                          ((uint32_t)0x01000000U) /* Filter bit 24 */
#define CAN_F0R1_FBC25                          ((uint32_t)0x02000000U) /* Filter bit 25 */
#define CAN_F0R1_FBC26                          ((uint32_t)0x04000000U) /* Filter bit 26 */
#define CAN_F0R1_FBC27                          ((uint32_t)0x08000000U) /* Filter bit 27 */
#define CAN_F0R1_FBC28                          ((uint32_t)0x10000000U) /* Filter bit 28 */
#define CAN_F0R1_FBC29                          ((uint32_t)0x20000000U) /* Filter bit 29 */
#define CAN_F0R1_FBC30                          ((uint32_t)0x40000000U) /* Filter bit 30 */
#define CAN_F0R1_FBC31                          ((uint32_t)0x80000000U) /* Filter bit 31 */

/**  Bit definition for CAN_F1R1 register  ***/
#define CAN_F1R1_FBC0                           ((uint32_t)0x00000001U) /* Filter bit 0 */
#define CAN_F1R1_FBC1                           ((uint32_t)0x00000002U) /* Filter bit 1 */
#define CAN_F1R1_FBC2                           ((uint32_t)0x00000004U) /* Filter bit 2 */
#define CAN_F1R1_FBC3                           ((uint32_t)0x00000008U) /* Filter bit 3 */
#define CAN_F1R1_FBC4                           ((uint32_t)0x00000010U) /* Filter bit 4 */
#define CAN_F1R1_FBC5                           ((uint32_t)0x00000020U) /* Filter bit 5 */
#define CAN_F1R1_FBC6                           ((uint32_t)0x00000040U) /* Filter bit 6 */
#define CAN_F1R1_FBC7                           ((uint32_t)0x00000080U) /* Filter bit 7 */
#define CAN_F1R1_FBC8                           ((uint32_t)0x00000100U) /* Filter bit 8 */
#define CAN_F1R1_FBC9                           ((uint32_t)0x00000200U) /* Filter bit 9 */
#define CAN_F1R1_FBC10                          ((uint32_t)0x00000400U) /* Filter bit 10 */
#define CAN_F1R1_FBC11                          ((uint32_t)0x00000800U) /* Filter bit 11 */
#define CAN_F1R1_FBC12                          ((uint32_t)0x00001000U) /* Filter bit 12 */
#define CAN_F1R1_FBC13                          ((uint32_t)0x00002000U) /* Filter bit 13 */
#define CAN_F1R1_FBC14                          ((uint32_t)0x00004000U) /* Filter bit 14 */
#define CAN_F1R1_FBC15                          ((uint32_t)0x00008000U) /* Filter bit 15 */
#define CAN_F1R1_FBC16                          ((uint32_t)0x00010000U) /* Filter bit 16 */
#define CAN_F1R1_FBC17                          ((uint32_t)0x00020000U) /* Filter bit 17 */
#define CAN_F1R1_FBC18                          ((uint32_t)0x00040000U) /* Filter bit 18 */
#define CAN_F1R1_FBC19                          ((uint32_t)0x00080000U) /* Filter bit 19 */
#define CAN_F1R1_FBC20                          ((uint32_t)0x00100000U) /* Filter bit 20 */
#define CAN_F1R1_FBC21                          ((uint32_t)0x00200000U) /* Filter bit 21 */
#define CAN_F1R1_FBC22                          ((uint32_t)0x00400000U) /* Filter bit 22 */
#define CAN_F1R1_FBC23                          ((uint32_t)0x00800000U) /* Filter bit 23 */
#define CAN_F1R1_FBC24                          ((uint32_t)0x01000000U) /* Filter bit 24 */
#define CAN_F1R1_FBC25                          ((uint32_t)0x02000000U) /* Filter bit 25 */
#define CAN_F1R1_FBC26                          ((uint32_t)0x04000000U) /* Filter bit 26 */
#define CAN_F1R1_FBC27                          ((uint32_t)0x08000000U) /* Filter bit 27 */
#define CAN_F1R1_FBC28                          ((uint32_t)0x10000000U) /* Filter bit 28 */
#define CAN_F1R1_FBC29                          ((uint32_t)0x20000000U) /* Filter bit 29 */
#define CAN_F1R1_FBC30                          ((uint32_t)0x40000000U) /* Filter bit 30 */
#define CAN_F1R1_FBC31                          ((uint32_t)0x80000000U) /* Filter bit 31 */

/**  Bit definition for CAN_F2R1 register  ***/
#define CAN_F2R1_FBC0                           ((uint32_t)0x00000001U) /* Filter bit 0 */
#define CAN_F2R1_FBC1                           ((uint32_t)0x00000002U) /* Filter bit 1 */
#define CAN_F2R1_FBC2                           ((uint32_t)0x00000004U) /* Filter bit 2 */
#define CAN_F2R1_FBC3                           ((uint32_t)0x00000008U) /* Filter bit 3 */
#define CAN_F2R1_FBC4                           ((uint32_t)0x00000010U) /* Filter bit 4 */
#define CAN_F2R1_FBC5                           ((uint32_t)0x00000020U) /* Filter bit 5 */
#define CAN_F2R1_FBC6                           ((uint32_t)0x00000040U) /* Filter bit 6 */
#define CAN_F2R1_FBC7                           ((uint32_t)0x00000080U) /* Filter bit 7 */
#define CAN_F2R1_FBC8                           ((uint32_t)0x00000100U) /* Filter bit 8 */
#define CAN_F2R1_FBC9                           ((uint32_t)0x00000200U) /* Filter bit 9 */
#define CAN_F2R1_FBC10                          ((uint32_t)0x00000400U) /* Filter bit 10 */
#define CAN_F2R1_FBC11                          ((uint32_t)0x00000800U) /* Filter bit 11 */
#define CAN_F2R1_FBC12                          ((uint32_t)0x00001000U) /* Filter bit 12 */
#define CAN_F2R1_FBC13                          ((uint32_t)0x00002000U) /* Filter bit 13 */
#define CAN_F2R1_FBC14                          ((uint32_t)0x00004000U) /* Filter bit 14 */
#define CAN_F2R1_FBC15                          ((uint32_t)0x00008000U) /* Filter bit 15 */
#define CAN_F2R1_FBC16                          ((uint32_t)0x00010000U) /* Filter bit 16 */
#define CAN_F2R1_FBC17                          ((uint32_t)0x00020000U) /* Filter bit 17 */
#define CAN_F2R1_FBC18                          ((uint32_t)0x00040000U) /* Filter bit 18 */
#define CAN_F2R1_FBC19                          ((uint32_t)0x00080000U) /* Filter bit 19 */
#define CAN_F2R1_FBC20                          ((uint32_t)0x00100000U) /* Filter bit 20 */
#define CAN_F2R1_FBC21                          ((uint32_t)0x00200000U) /* Filter bit 21 */
#define CAN_F2R1_FBC22                          ((uint32_t)0x00400000U) /* Filter bit 22 */
#define CAN_F2R1_FBC23                          ((uint32_t)0x00800000U) /* Filter bit 23 */
#define CAN_F2R1_FBC24                          ((uint32_t)0x01000000U) /* Filter bit 24 */
#define CAN_F2R1_FBC25                          ((uint32_t)0x02000000U) /* Filter bit 25 */
#define CAN_F2R1_FBC26                          ((uint32_t)0x04000000U) /* Filter bit 26 */
#define CAN_F2R1_FBC27                          ((uint32_t)0x08000000U) /* Filter bit 27 */
#define CAN_F2R1_FBC28                          ((uint32_t)0x10000000U) /* Filter bit 28 */
#define CAN_F2R1_FBC29                          ((uint32_t)0x20000000U) /* Filter bit 29 */
#define CAN_F2R1_FBC30                          ((uint32_t)0x40000000U) /* Filter bit 30 */
#define CAN_F2R1_FBC31                          ((uint32_t)0x80000000U) /* Filter bit 31 */

/**  Bit definition for CAN_F3R1 register  ***/
#define CAN_F3R1_FBC0                           ((uint32_t)0x00000001U) /* Filter bit 0 */
#define CAN_F3R1_FBC1                           ((uint32_t)0x00000002U) /* Filter bit 1 */
#define CAN_F3R1_FBC2                           ((uint32_t)0x00000004U) /* Filter bit 2 */
#define CAN_F3R1_FBC3                           ((uint32_t)0x00000008U) /* Filter bit 3 */
#define CAN_F3R1_FBC4                           ((uint32_t)0x00000010U) /* Filter bit 4 */
#define CAN_F3R1_FBC5                           ((uint32_t)0x00000020U) /* Filter bit 5 */
#define CAN_F3R1_FBC6                           ((uint32_t)0x00000040U) /* Filter bit 6 */
#define CAN_F3R1_FBC7                           ((uint32_t)0x00000080U) /* Filter bit 7 */
#define CAN_F3R1_FBC8                           ((uint32_t)0x00000100U) /* Filter bit 8 */
#define CAN_F3R1_FBC9                           ((uint32_t)0x00000200U) /* Filter bit 9 */
#define CAN_F3R1_FBC10                          ((uint32_t)0x00000400U) /* Filter bit 10 */
#define CAN_F3R1_FBC11                          ((uint32_t)0x00000800U) /* Filter bit 11 */
#define CAN_F3R1_FBC12                          ((uint32_t)0x00001000U) /* Filter bit 12 */
#define CAN_F3R1_FBC13                          ((uint32_t)0x00002000U) /* Filter bit 13 */
#define CAN_F3R1_FBC14                          ((uint32_t)0x00004000U) /* Filter bit 14 */
#define CAN_F3R1_FBC15                          ((uint32_t)0x00008000U) /* Filter bit 15 */
#define CAN_F3R1_FBC16                          ((uint32_t)0x00010000U) /* Filter bit 16 */
#define CAN_F3R1_FBC17                          ((uint32_t)0x00020000U) /* Filter bit 17 */
#define CAN_F3R1_FBC18                          ((uint32_t)0x00040000U) /* Filter bit 18 */
#define CAN_F3R1_FBC19                          ((uint32_t)0x00080000U) /* Filter bit 19 */
#define CAN_F3R1_FBC20                          ((uint32_t)0x00100000U) /* Filter bit 20 */
#define CAN_F3R1_FBC21                          ((uint32_t)0x00200000U) /* Filter bit 21 */
#define CAN_F3R1_FBC22                          ((uint32_t)0x00400000U) /* Filter bit 22 */
#define CAN_F3R1_FBC23                          ((uint32_t)0x00800000U) /* Filter bit 23 */
#define CAN_F3R1_FBC24                          ((uint32_t)0x01000000U) /* Filter bit 24 */
#define CAN_F3R1_FBC25                          ((uint32_t)0x02000000U) /* Filter bit 25 */
#define CAN_F3R1_FBC26                          ((uint32_t)0x04000000U) /* Filter bit 26 */
#define CAN_F3R1_FBC27                          ((uint32_t)0x08000000U) /* Filter bit 27 */
#define CAN_F3R1_FBC28                          ((uint32_t)0x10000000U) /* Filter bit 28 */
#define CAN_F3R1_FBC29                          ((uint32_t)0x20000000U) /* Filter bit 29 */
#define CAN_F3R1_FBC30                          ((uint32_t)0x40000000U) /* Filter bit 30 */
#define CAN_F3R1_FBC31                          ((uint32_t)0x80000000U) /* Filter bit 31 */

/**  Bit definition for CAN_F4R1 register  ***/
#define CAN_F4R1_FBC0                           ((uint32_t)0x00000001U) /* Filter bit 0 */
#define CAN_F4R1_FBC1                           ((uint32_t)0x00000002U) /* Filter bit 1 */
#define CAN_F4R1_FBC2                           ((uint32_t)0x00000004U) /* Filter bit 2 */
#define CAN_F4R1_FBC3                           ((uint32_t)0x00000008U) /* Filter bit 3 */
#define CAN_F4R1_FBC4                           ((uint32_t)0x00000010U) /* Filter bit 4 */
#define CAN_F4R1_FBC5                           ((uint32_t)0x00000020U) /* Filter bit 5 */
#define CAN_F4R1_FBC6                           ((uint32_t)0x00000040U) /* Filter bit 6 */
#define CAN_F4R1_FBC7                           ((uint32_t)0x00000080U) /* Filter bit 7 */
#define CAN_F4R1_FBC8                           ((uint32_t)0x00000100U) /* Filter bit 8 */
#define CAN_F4R1_FBC9                           ((uint32_t)0x00000200U) /* Filter bit 9 */
#define CAN_F4R1_FBC10                          ((uint32_t)0x00000400U) /* Filter bit 10 */
#define CAN_F4R1_FBC11                          ((uint32_t)0x00000800U) /* Filter bit 11 */
#define CAN_F4R1_FBC12                          ((uint32_t)0x00001000U) /* Filter bit 12 */
#define CAN_F4R1_FBC13                          ((uint32_t)0x00002000U) /* Filter bit 13 */
#define CAN_F4R1_FBC14                          ((uint32_t)0x00004000U) /* Filter bit 14 */
#define CAN_F4R1_FBC15                          ((uint32_t)0x00008000U) /* Filter bit 15 */
#define CAN_F4R1_FBC16                          ((uint32_t)0x00010000U) /* Filter bit 16 */
#define CAN_F4R1_FBC17                          ((uint32_t)0x00020000U) /* Filter bit 17 */
#define CAN_F4R1_FBC18                          ((uint32_t)0x00040000U) /* Filter bit 18 */
#define CAN_F4R1_FBC19                          ((uint32_t)0x00080000U) /* Filter bit 19 */
#define CAN_F4R1_FBC20                          ((uint32_t)0x00100000U) /* Filter bit 20 */
#define CAN_F4R1_FBC21                          ((uint32_t)0x00200000U) /* Filter bit 21 */
#define CAN_F4R1_FBC22                          ((uint32_t)0x00400000U) /* Filter bit 22 */
#define CAN_F4R1_FBC23                          ((uint32_t)0x00800000U) /* Filter bit 23 */
#define CAN_F4R1_FBC24                          ((uint32_t)0x01000000U) /* Filter bit 24 */
#define CAN_F4R1_FBC25                          ((uint32_t)0x02000000U) /* Filter bit 25 */
#define CAN_F4R1_FBC26                          ((uint32_t)0x04000000U) /* Filter bit 26 */
#define CAN_F4R1_FBC27                          ((uint32_t)0x08000000U) /* Filter bit 27 */
#define CAN_F4R1_FBC28                          ((uint32_t)0x10000000U) /* Filter bit 28 */
#define CAN_F4R1_FBC29                          ((uint32_t)0x20000000U) /* Filter bit 29 */
#define CAN_F4R1_FBC30                          ((uint32_t)0x40000000U) /* Filter bit 30 */
#define CAN_F4R1_FBC31                          ((uint32_t)0x80000000U) /* Filter bit 31 */

/**  Bit definition for CAN_F5R1 register  ***/
#define CAN_F5R1_FBC0                           ((uint32_t)0x00000001U) /* Filter bit 0 */
#define CAN_F5R1_FBC1                           ((uint32_t)0x00000002U) /* Filter bit 1 */
#define CAN_F5R1_FBC2                           ((uint32_t)0x00000004U) /* Filter bit 2 */
#define CAN_F5R1_FBC3                           ((uint32_t)0x00000008U) /* Filter bit 3 */
#define CAN_F5R1_FBC4                           ((uint32_t)0x00000010U) /* Filter bit 4 */
#define CAN_F5R1_FBC5                           ((uint32_t)0x00000020U) /* Filter bit 5 */
#define CAN_F5R1_FBC6                           ((uint32_t)0x00000040U) /* Filter bit 6 */
#define CAN_F5R1_FBC7                           ((uint32_t)0x00000080U) /* Filter bit 7 */
#define CAN_F5R1_FBC8                           ((uint32_t)0x00000100U) /* Filter bit 8 */
#define CAN_F5R1_FBC9                           ((uint32_t)0x00000200U) /* Filter bit 9 */
#define CAN_F5R1_FBC10                          ((uint32_t)0x00000400U) /* Filter bit 10 */
#define CAN_F5R1_FBC11                          ((uint32_t)0x00000800U) /* Filter bit 11 */
#define CAN_F5R1_FBC12                          ((uint32_t)0x00001000U) /* Filter bit 12 */
#define CAN_F5R1_FBC13                          ((uint32_t)0x00002000U) /* Filter bit 13 */
#define CAN_F5R1_FBC14                          ((uint32_t)0x00004000U) /* Filter bit 14 */
#define CAN_F5R1_FBC15                          ((uint32_t)0x00008000U) /* Filter bit 15 */
#define CAN_F5R1_FBC16                          ((uint32_t)0x00010000U) /* Filter bit 16 */
#define CAN_F5R1_FBC17                          ((uint32_t)0x00020000U) /* Filter bit 17 */
#define CAN_F5R1_FBC18                          ((uint32_t)0x00040000U) /* Filter bit 18 */
#define CAN_F5R1_FBC19                          ((uint32_t)0x00080000U) /* Filter bit 19 */
#define CAN_F5R1_FBC20                          ((uint32_t)0x00100000U) /* Filter bit 20 */
#define CAN_F5R1_FBC21                          ((uint32_t)0x00200000U) /* Filter bit 21 */
#define CAN_F5R1_FBC22                          ((uint32_t)0x00400000U) /* Filter bit 22 */
#define CAN_F5R1_FBC23                          ((uint32_t)0x00800000U) /* Filter bit 23 */
#define CAN_F5R1_FBC24                          ((uint32_t)0x01000000U) /* Filter bit 24 */
#define CAN_F5R1_FBC25                          ((uint32_t)0x02000000U) /* Filter bit 25 */
#define CAN_F5R1_FBC26                          ((uint32_t)0x04000000U) /* Filter bit 26 */
#define CAN_F5R1_FBC27                          ((uint32_t)0x08000000U) /* Filter bit 27 */
#define CAN_F5R1_FBC28                          ((uint32_t)0x10000000U) /* Filter bit 28 */
#define CAN_F5R1_FBC29                          ((uint32_t)0x20000000U) /* Filter bit 29 */
#define CAN_F5R1_FBC30                          ((uint32_t)0x40000000U) /* Filter bit 30 */
#define CAN_F5R1_FBC31                          ((uint32_t)0x80000000U) /* Filter bit 31 */

/**  Bit definition for CAN_F6R1 register  ***/
#define CAN_F6R1_FBC0                           ((uint32_t)0x00000001U) /* Filter bit 0 */
#define CAN_F6R1_FBC1                           ((uint32_t)0x00000002U) /* Filter bit 1 */
#define CAN_F6R1_FBC2                           ((uint32_t)0x00000004U) /* Filter bit 2 */
#define CAN_F6R1_FBC3                           ((uint32_t)0x00000008U) /* Filter bit 3 */
#define CAN_F6R1_FBC4                           ((uint32_t)0x00000010U) /* Filter bit 4 */
#define CAN_F6R1_FBC5                           ((uint32_t)0x00000020U) /* Filter bit 5 */
#define CAN_F6R1_FBC6                           ((uint32_t)0x00000040U) /* Filter bit 6 */
#define CAN_F6R1_FBC7                           ((uint32_t)0x00000080U) /* Filter bit 7 */
#define CAN_F6R1_FBC8                           ((uint32_t)0x00000100U) /* Filter bit 8 */
#define CAN_F6R1_FBC9                           ((uint32_t)0x00000200U) /* Filter bit 9 */
#define CAN_F6R1_FBC10                          ((uint32_t)0x00000400U) /* Filter bit 10 */
#define CAN_F6R1_FBC11                          ((uint32_t)0x00000800U) /* Filter bit 11 */
#define CAN_F6R1_FBC12                          ((uint32_t)0x00001000U) /* Filter bit 12 */
#define CAN_F6R1_FBC13                          ((uint32_t)0x00002000U) /* Filter bit 13 */
#define CAN_F6R1_FBC14                          ((uint32_t)0x00004000U) /* Filter bit 14 */
#define CAN_F6R1_FBC15                          ((uint32_t)0x00008000U) /* Filter bit 15 */
#define CAN_F6R1_FBC16                          ((uint32_t)0x00010000U) /* Filter bit 16 */
#define CAN_F6R1_FBC17                          ((uint32_t)0x00020000U) /* Filter bit 17 */
#define CAN_F6R1_FBC18                          ((uint32_t)0x00040000U) /* Filter bit 18 */
#define CAN_F6R1_FBC19                          ((uint32_t)0x00080000U) /* Filter bit 19 */
#define CAN_F6R1_FBC20                          ((uint32_t)0x00100000U) /* Filter bit 20 */
#define CAN_F6R1_FBC21                          ((uint32_t)0x00200000U) /* Filter bit 21 */
#define CAN_F6R1_FBC22                          ((uint32_t)0x00400000U) /* Filter bit 22 */
#define CAN_F6R1_FBC23                          ((uint32_t)0x00800000U) /* Filter bit 23 */
#define CAN_F6R1_FBC24                          ((uint32_t)0x01000000U) /* Filter bit 24 */
#define CAN_F6R1_FBC25                          ((uint32_t)0x02000000U) /* Filter bit 25 */
#define CAN_F6R1_FBC26                          ((uint32_t)0x04000000U) /* Filter bit 26 */
#define CAN_F6R1_FBC27                          ((uint32_t)0x08000000U) /* Filter bit 27 */
#define CAN_F6R1_FBC28                          ((uint32_t)0x10000000U) /* Filter bit 28 */
#define CAN_F6R1_FBC29                          ((uint32_t)0x20000000U) /* Filter bit 29 */
#define CAN_F6R1_FBC30                          ((uint32_t)0x40000000U) /* Filter bit 30 */
#define CAN_F6R1_FBC31                          ((uint32_t)0x80000000U) /* Filter bit 31 */

/**  Bit definition for CAN_F7R1 register  ***/
#define CAN_F7R1_FBC0                           ((uint32_t)0x00000001U) /* Filter bit 0 */
#define CAN_F7R1_FBC1                           ((uint32_t)0x00000002U) /* Filter bit 1 */
#define CAN_F7R1_FBC2                           ((uint32_t)0x00000004U) /* Filter bit 2 */
#define CAN_F7R1_FBC3                           ((uint32_t)0x00000008U) /* Filter bit 3 */
#define CAN_F7R1_FBC4                           ((uint32_t)0x00000010U) /* Filter bit 4 */
#define CAN_F7R1_FBC5                           ((uint32_t)0x00000020U) /* Filter bit 5 */
#define CAN_F7R1_FBC6                           ((uint32_t)0x00000040U) /* Filter bit 6 */
#define CAN_F7R1_FBC7                           ((uint32_t)0x00000080U) /* Filter bit 7 */
#define CAN_F7R1_FBC8                           ((uint32_t)0x00000100U) /* Filter bit 8 */
#define CAN_F7R1_FBC9                           ((uint32_t)0x00000200U) /* Filter bit 9 */
#define CAN_F7R1_FBC10                          ((uint32_t)0x00000400U) /* Filter bit 10 */
#define CAN_F7R1_FBC11                          ((uint32_t)0x00000800U) /* Filter bit 11 */
#define CAN_F7R1_FBC12                          ((uint32_t)0x00001000U) /* Filter bit 12 */
#define CAN_F7R1_FBC13                          ((uint32_t)0x00002000U) /* Filter bit 13 */
#define CAN_F7R1_FBC14                          ((uint32_t)0x00004000U) /* Filter bit 14 */
#define CAN_F7R1_FBC15                          ((uint32_t)0x00008000U) /* Filter bit 15 */
#define CAN_F7R1_FBC16                          ((uint32_t)0x00010000U) /* Filter bit 16 */
#define CAN_F7R1_FBC17                          ((uint32_t)0x00020000U) /* Filter bit 17 */
#define CAN_F7R1_FBC18                          ((uint32_t)0x00040000U) /* Filter bit 18 */
#define CAN_F7R1_FBC19                          ((uint32_t)0x00080000U) /* Filter bit 19 */
#define CAN_F7R1_FBC20                          ((uint32_t)0x00100000U) /* Filter bit 20 */
#define CAN_F7R1_FBC21                          ((uint32_t)0x00200000U) /* Filter bit 21 */
#define CAN_F7R1_FBC22                          ((uint32_t)0x00400000U) /* Filter bit 22 */
#define CAN_F7R1_FBC23                          ((uint32_t)0x00800000U) /* Filter bit 23 */
#define CAN_F7R1_FBC24                          ((uint32_t)0x01000000U) /* Filter bit 24 */
#define CAN_F7R1_FBC25                          ((uint32_t)0x02000000U) /* Filter bit 25 */
#define CAN_F7R1_FBC26                          ((uint32_t)0x04000000U) /* Filter bit 26 */
#define CAN_F7R1_FBC27                          ((uint32_t)0x08000000U) /* Filter bit 27 */
#define CAN_F7R1_FBC28                          ((uint32_t)0x10000000U) /* Filter bit 28 */
#define CAN_F7R1_FBC29                          ((uint32_t)0x20000000U) /* Filter bit 29 */
#define CAN_F7R1_FBC30                          ((uint32_t)0x40000000U) /* Filter bit 30 */
#define CAN_F7R1_FBC31                          ((uint32_t)0x80000000U) /* Filter bit 31 */

/**  Bit definition for CAN_F8R1 register  ***/
#define CAN_F8R1_FBC0                           ((uint32_t)0x00000001U) /* Filter bit 0 */
#define CAN_F8R1_FBC1                           ((uint32_t)0x00000002U) /* Filter bit 1 */
#define CAN_F8R1_FBC2                           ((uint32_t)0x00000004U) /* Filter bit 2 */
#define CAN_F8R1_FBC3                           ((uint32_t)0x00000008U) /* Filter bit 3 */
#define CAN_F8R1_FBC4                           ((uint32_t)0x00000010U) /* Filter bit 4 */
#define CAN_F8R1_FBC5                           ((uint32_t)0x00000020U) /* Filter bit 5 */
#define CAN_F8R1_FBC6                           ((uint32_t)0x00000040U) /* Filter bit 6 */
#define CAN_F8R1_FBC7                           ((uint32_t)0x00000080U) /* Filter bit 7 */
#define CAN_F8R1_FBC8                           ((uint32_t)0x00000100U) /* Filter bit 8 */
#define CAN_F8R1_FBC9                           ((uint32_t)0x00000200U) /* Filter bit 9 */
#define CAN_F8R1_FBC10                          ((uint32_t)0x00000400U) /* Filter bit 10 */
#define CAN_F8R1_FBC11                          ((uint32_t)0x00000800U) /* Filter bit 11 */
#define CAN_F8R1_FBC12                          ((uint32_t)0x00001000U) /* Filter bit 12 */
#define CAN_F8R1_FBC13                          ((uint32_t)0x00002000U) /* Filter bit 13 */
#define CAN_F8R1_FBC14                          ((uint32_t)0x00004000U) /* Filter bit 14 */
#define CAN_F8R1_FBC15                          ((uint32_t)0x00008000U) /* Filter bit 15 */
#define CAN_F8R1_FBC16                          ((uint32_t)0x00010000U) /* Filter bit 16 */
#define CAN_F8R1_FBC17                          ((uint32_t)0x00020000U) /* Filter bit 17 */
#define CAN_F8R1_FBC18                          ((uint32_t)0x00040000U) /* Filter bit 18 */
#define CAN_F8R1_FBC19                          ((uint32_t)0x00080000U) /* Filter bit 19 */
#define CAN_F8R1_FBC20                          ((uint32_t)0x00100000U) /* Filter bit 20 */
#define CAN_F8R1_FBC21                          ((uint32_t)0x00200000U) /* Filter bit 21 */
#define CAN_F8R1_FBC22                          ((uint32_t)0x00400000U) /* Filter bit 22 */
#define CAN_F8R1_FBC23                          ((uint32_t)0x00800000U) /* Filter bit 23 */
#define CAN_F8R1_FBC24                          ((uint32_t)0x01000000U) /* Filter bit 24 */
#define CAN_F8R1_FBC25                          ((uint32_t)0x02000000U) /* Filter bit 25 */
#define CAN_F8R1_FBC26                          ((uint32_t)0x04000000U) /* Filter bit 26 */
#define CAN_F8R1_FBC27                          ((uint32_t)0x08000000U) /* Filter bit 27 */
#define CAN_F8R1_FBC28                          ((uint32_t)0x10000000U) /* Filter bit 28 */
#define CAN_F8R1_FBC29                          ((uint32_t)0x20000000U) /* Filter bit 29 */
#define CAN_F8R1_FBC30                          ((uint32_t)0x40000000U) /* Filter bit 30 */
#define CAN_F8R1_FBC31                          ((uint32_t)0x80000000U) /* Filter bit 31 */

/**  Bit definition for CAN_F9R1 register  ***/
#define CAN_F9R1_FBC0                           ((uint32_t)0x00000001U) /* Filter bit 0 */
#define CAN_F9R1_FBC1                           ((uint32_t)0x00000002U) /* Filter bit 1 */
#define CAN_F9R1_FBC2                           ((uint32_t)0x00000004U) /* Filter bit 2 */
#define CAN_F9R1_FBC3                           ((uint32_t)0x00000008U) /* Filter bit 3 */
#define CAN_F9R1_FBC4                           ((uint32_t)0x00000010U) /* Filter bit 4 */
#define CAN_F9R1_FBC5                           ((uint32_t)0x00000020U) /* Filter bit 5 */
#define CAN_F9R1_FBC6                           ((uint32_t)0x00000040U) /* Filter bit 6 */
#define CAN_F9R1_FBC7                           ((uint32_t)0x00000080U) /* Filter bit 7 */
#define CAN_F9R1_FBC8                           ((uint32_t)0x00000100U) /* Filter bit 8 */
#define CAN_F9R1_FBC9                           ((uint32_t)0x00000200U) /* Filter bit 9 */
#define CAN_F9R1_FBC10                          ((uint32_t)0x00000400U) /* Filter bit 10 */
#define CAN_F9R1_FBC11                          ((uint32_t)0x00000800U) /* Filter bit 11 */
#define CAN_F9R1_FBC12                          ((uint32_t)0x00001000U) /* Filter bit 12 */
#define CAN_F9R1_FBC13                          ((uint32_t)0x00002000U) /* Filter bit 13 */
#define CAN_F9R1_FBC14                          ((uint32_t)0x00004000U) /* Filter bit 14 */
#define CAN_F9R1_FBC15                          ((uint32_t)0x00008000U) /* Filter bit 15 */
#define CAN_F9R1_FBC16                          ((uint32_t)0x00010000U) /* Filter bit 16 */
#define CAN_F9R1_FBC17                          ((uint32_t)0x00020000U) /* Filter bit 17 */
#define CAN_F9R1_FBC18                          ((uint32_t)0x00040000U) /* Filter bit 18 */
#define CAN_F9R1_FBC19                          ((uint32_t)0x00080000U) /* Filter bit 19 */
#define CAN_F9R1_FBC20                          ((uint32_t)0x00100000U) /* Filter bit 20 */
#define CAN_F9R1_FBC21                          ((uint32_t)0x00200000U) /* Filter bit 21 */
#define CAN_F9R1_FBC22                          ((uint32_t)0x00400000U) /* Filter bit 22 */
#define CAN_F9R1_FBC23                          ((uint32_t)0x00800000U) /* Filter bit 23 */
#define CAN_F9R1_FBC24                          ((uint32_t)0x01000000U) /* Filter bit 24 */
#define CAN_F9R1_FBC25                          ((uint32_t)0x02000000U) /* Filter bit 25 */
#define CAN_F9R1_FBC26                          ((uint32_t)0x04000000U) /* Filter bit 26 */
#define CAN_F9R1_FBC27                          ((uint32_t)0x08000000U) /* Filter bit 27 */
#define CAN_F9R1_FBC28                          ((uint32_t)0x10000000U) /* Filter bit 28 */
#define CAN_F9R1_FBC29                          ((uint32_t)0x20000000U) /* Filter bit 29 */
#define CAN_F9R1_FBC30                          ((uint32_t)0x40000000U) /* Filter bit 30 */
#define CAN_F9R1_FBC31                          ((uint32_t)0x80000000U) /* Filter bit 31 */

/**  Bit definition for CAN_F10R1 register  **/
#define CAN_F10R1_FBC0                          ((uint32_t)0x00000001U) /* Filter bit 0 */
#define CAN_F10R1_FBC1                          ((uint32_t)0x00000002U) /* Filter bit 1 */
#define CAN_F10R1_FBC2                          ((uint32_t)0x00000004U) /* Filter bit 2 */
#define CAN_F10R1_FBC3                          ((uint32_t)0x00000008U) /* Filter bit 3 */
#define CAN_F10R1_FBC4                          ((uint32_t)0x00000010U) /* Filter bit 4 */
#define CAN_F10R1_FBC5                          ((uint32_t)0x00000020U) /* Filter bit 5 */
#define CAN_F10R1_FBC6                          ((uint32_t)0x00000040U) /* Filter bit 6 */
#define CAN_F10R1_FBC7                          ((uint32_t)0x00000080U) /* Filter bit 7 */
#define CAN_F10R1_FBC8                          ((uint32_t)0x00000100U) /* Filter bit 8 */
#define CAN_F10R1_FBC9                          ((uint32_t)0x00000200U) /* Filter bit 9 */
#define CAN_F10R1_FBC10                         ((uint32_t)0x00000400U) /* Filter bit 10 */
#define CAN_F10R1_FBC11                         ((uint32_t)0x00000800U) /* Filter bit 11 */
#define CAN_F10R1_FBC12                         ((uint32_t)0x00001000U) /* Filter bit 12 */
#define CAN_F10R1_FBC13                         ((uint32_t)0x00002000U) /* Filter bit 13 */
#define CAN_F10R1_FBC14                         ((uint32_t)0x00004000U) /* Filter bit 14 */
#define CAN_F10R1_FBC15                         ((uint32_t)0x00008000U) /* Filter bit 15 */
#define CAN_F10R1_FBC16                         ((uint32_t)0x00010000U) /* Filter bit 16 */
#define CAN_F10R1_FBC17                         ((uint32_t)0x00020000U) /* Filter bit 17 */
#define CAN_F10R1_FBC18                         ((uint32_t)0x00040000U) /* Filter bit 18 */
#define CAN_F10R1_FBC19                         ((uint32_t)0x00080000U) /* Filter bit 19 */
#define CAN_F10R1_FBC20                         ((uint32_t)0x00100000U) /* Filter bit 20 */
#define CAN_F10R1_FBC21                         ((uint32_t)0x00200000U) /* Filter bit 21 */
#define CAN_F10R1_FBC22                         ((uint32_t)0x00400000U) /* Filter bit 22 */
#define CAN_F10R1_FBC23                         ((uint32_t)0x00800000U) /* Filter bit 23 */
#define CAN_F10R1_FBC24                         ((uint32_t)0x01000000U) /* Filter bit 24 */
#define CAN_F10R1_FBC25                         ((uint32_t)0x02000000U) /* Filter bit 25 */
#define CAN_F10R1_FBC26                         ((uint32_t)0x04000000U) /* Filter bit 26 */
#define CAN_F10R1_FBC27                         ((uint32_t)0x08000000U) /* Filter bit 27 */
#define CAN_F10R1_FBC28                         ((uint32_t)0x10000000U) /* Filter bit 28 */
#define CAN_F10R1_FBC29                         ((uint32_t)0x20000000U) /* Filter bit 29 */
#define CAN_F10R1_FBC30                         ((uint32_t)0x40000000U) /* Filter bit 30 */
#define CAN_F10R1_FBC31                         ((uint32_t)0x80000000U) /* Filter bit 31 */

/**  Bit definition for CAN_F11R1 register  **/
#define CAN_F11R1_FBC0                          ((uint32_t)0x00000001U) /* Filter bit 0 */
#define CAN_F11R1_FBC1                          ((uint32_t)0x00000002U) /* Filter bit 1 */
#define CAN_F11R1_FBC2                          ((uint32_t)0x00000004U) /* Filter bit 2 */
#define CAN_F11R1_FBC3                          ((uint32_t)0x00000008U) /* Filter bit 3 */
#define CAN_F11R1_FBC4                          ((uint32_t)0x00000010U) /* Filter bit 4 */
#define CAN_F11R1_FBC5                          ((uint32_t)0x00000020U) /* Filter bit 5 */
#define CAN_F11R1_FBC6                          ((uint32_t)0x00000040U) /* Filter bit 6 */
#define CAN_F11R1_FBC7                          ((uint32_t)0x00000080U) /* Filter bit 7 */
#define CAN_F11R1_FBC8                          ((uint32_t)0x00000100U) /* Filter bit 8 */
#define CAN_F11R1_FBC9                          ((uint32_t)0x00000200U) /* Filter bit 9 */
#define CAN_F11R1_FBC10                         ((uint32_t)0x00000400U) /* Filter bit 10 */
#define CAN_F11R1_FBC11                         ((uint32_t)0x00000800U) /* Filter bit 11 */
#define CAN_F11R1_FBC12                         ((uint32_t)0x00001000U) /* Filter bit 12 */
#define CAN_F11R1_FBC13                         ((uint32_t)0x00002000U) /* Filter bit 13 */
#define CAN_F11R1_FBC14                         ((uint32_t)0x00004000U) /* Filter bit 14 */
#define CAN_F11R1_FBC15                         ((uint32_t)0x00008000U) /* Filter bit 15 */
#define CAN_F11R1_FBC16                         ((uint32_t)0x00010000U) /* Filter bit 16 */
#define CAN_F11R1_FBC17                         ((uint32_t)0x00020000U) /* Filter bit 17 */
#define CAN_F11R1_FBC18                         ((uint32_t)0x00040000U) /* Filter bit 18 */
#define CAN_F11R1_FBC19                         ((uint32_t)0x00080000U) /* Filter bit 19 */
#define CAN_F11R1_FBC20                         ((uint32_t)0x00100000U) /* Filter bit 20 */
#define CAN_F11R1_FBC21                         ((uint32_t)0x00200000U) /* Filter bit 21 */
#define CAN_F11R1_FBC22                         ((uint32_t)0x00400000U) /* Filter bit 22 */
#define CAN_F11R1_FBC23                         ((uint32_t)0x00800000U) /* Filter bit 23 */
#define CAN_F11R1_FBC24                         ((uint32_t)0x01000000U) /* Filter bit 24 */
#define CAN_F11R1_FBC25                         ((uint32_t)0x02000000U) /* Filter bit 25 */
#define CAN_F11R1_FBC26                         ((uint32_t)0x04000000U) /* Filter bit 26 */
#define CAN_F11R1_FBC27                         ((uint32_t)0x08000000U) /* Filter bit 27 */
#define CAN_F11R1_FBC28                         ((uint32_t)0x10000000U) /* Filter bit 28 */
#define CAN_F11R1_FBC29                         ((uint32_t)0x20000000U) /* Filter bit 29 */
#define CAN_F11R1_FBC30                         ((uint32_t)0x40000000U) /* Filter bit 30 */
#define CAN_F11R1_FBC31                         ((uint32_t)0x80000000U) /* Filter bit 31 */

/**  Bit definition for CAN_F12R1 register  **/
#define CAN_F12R1_FBC0                          ((uint32_t)0x00000001U) /* Filter bit 0 */
#define CAN_F12R1_FBC1                          ((uint32_t)0x00000002U) /* Filter bit 1 */
#define CAN_F12R1_FBC2                          ((uint32_t)0x00000004U) /* Filter bit 2 */
#define CAN_F12R1_FBC3                          ((uint32_t)0x00000008U) /* Filter bit 3 */
#define CAN_F12R1_FBC4                          ((uint32_t)0x00000010U) /* Filter bit 4 */
#define CAN_F12R1_FBC5                          ((uint32_t)0x00000020U) /* Filter bit 5 */
#define CAN_F12R1_FBC6                          ((uint32_t)0x00000040U) /* Filter bit 6 */
#define CAN_F12R1_FBC7                          ((uint32_t)0x00000080U) /* Filter bit 7 */
#define CAN_F12R1_FBC8                          ((uint32_t)0x00000100U) /* Filter bit 8 */
#define CAN_F12R1_FBC9                          ((uint32_t)0x00000200U) /* Filter bit 9 */
#define CAN_F12R1_FBC10                         ((uint32_t)0x00000400U) /* Filter bit 10 */
#define CAN_F12R1_FBC11                         ((uint32_t)0x00000800U) /* Filter bit 11 */
#define CAN_F12R1_FBC12                         ((uint32_t)0x00001000U) /* Filter bit 12 */
#define CAN_F12R1_FBC13                         ((uint32_t)0x00002000U) /* Filter bit 13 */
#define CAN_F12R1_FBC14                         ((uint32_t)0x00004000U) /* Filter bit 14 */
#define CAN_F12R1_FBC15                         ((uint32_t)0x00008000U) /* Filter bit 15 */
#define CAN_F12R1_FBC16                         ((uint32_t)0x00010000U) /* Filter bit 16 */
#define CAN_F12R1_FBC17                         ((uint32_t)0x00020000U) /* Filter bit 17 */
#define CAN_F12R1_FBC18                         ((uint32_t)0x00040000U) /* Filter bit 18 */
#define CAN_F12R1_FBC19                         ((uint32_t)0x00080000U) /* Filter bit 19 */
#define CAN_F12R1_FBC20                         ((uint32_t)0x00100000U) /* Filter bit 20 */
#define CAN_F12R1_FBC21                         ((uint32_t)0x00200000U) /* Filter bit 21 */
#define CAN_F12R1_FBC22                         ((uint32_t)0x00400000U) /* Filter bit 22 */
#define CAN_F12R1_FBC23                         ((uint32_t)0x00800000U) /* Filter bit 23 */
#define CAN_F12R1_FBC24                         ((uint32_t)0x01000000U) /* Filter bit 24 */
#define CAN_F12R1_FBC25                         ((uint32_t)0x02000000U) /* Filter bit 25 */
#define CAN_F12R1_FBC26                         ((uint32_t)0x04000000U) /* Filter bit 26 */
#define CAN_F12R1_FBC27                         ((uint32_t)0x08000000U) /* Filter bit 27 */
#define CAN_F12R1_FBC28                         ((uint32_t)0x10000000U) /* Filter bit 28 */
#define CAN_F12R1_FBC29                         ((uint32_t)0x20000000U) /* Filter bit 29 */
#define CAN_F12R1_FBC30                         ((uint32_t)0x40000000U) /* Filter bit 30 */
#define CAN_F12R1_FBC31                         ((uint32_t)0x80000000U) /* Filter bit 31 */

/**  Bit definition for CAN_F13R1 register  **/
#define CAN_F13R1_FBC0                          ((uint32_t)0x00000001U) /* Filter bit 0 */
#define CAN_F13R1_FBC1                          ((uint32_t)0x00000002U) /* Filter bit 1 */
#define CAN_F13R1_FBC2                          ((uint32_t)0x00000004U) /* Filter bit 2 */
#define CAN_F13R1_FBC3                          ((uint32_t)0x00000008U) /* Filter bit 3 */
#define CAN_F13R1_FBC4                          ((uint32_t)0x00000010U) /* Filter bit 4 */
#define CAN_F13R1_FBC5                          ((uint32_t)0x00000020U) /* Filter bit 5 */
#define CAN_F13R1_FBC6                          ((uint32_t)0x00000040U) /* Filter bit 6 */
#define CAN_F13R1_FBC7                          ((uint32_t)0x00000080U) /* Filter bit 7 */
#define CAN_F13R1_FBC8                          ((uint32_t)0x00000100U) /* Filter bit 8 */
#define CAN_F13R1_FBC9                          ((uint32_t)0x00000200U) /* Filter bit 9 */
#define CAN_F13R1_FBC10                         ((uint32_t)0x00000400U) /* Filter bit 10 */
#define CAN_F13R1_FBC11                         ((uint32_t)0x00000800U) /* Filter bit 11 */
#define CAN_F13R1_FBC12                         ((uint32_t)0x00001000U) /* Filter bit 12 */
#define CAN_F13R1_FBC13                         ((uint32_t)0x00002000U) /* Filter bit 13 */
#define CAN_F13R1_FBC14                         ((uint32_t)0x00004000U) /* Filter bit 14 */
#define CAN_F13R1_FBC15                         ((uint32_t)0x00008000U) /* Filter bit 15 */
#define CAN_F13R1_FBC16                         ((uint32_t)0x00010000U) /* Filter bit 16 */
#define CAN_F13R1_FBC17                         ((uint32_t)0x00020000U) /* Filter bit 17 */
#define CAN_F13R1_FBC18                         ((uint32_t)0x00040000U) /* Filter bit 18 */
#define CAN_F13R1_FBC19                         ((uint32_t)0x00080000U) /* Filter bit 19 */
#define CAN_F13R1_FBC20                         ((uint32_t)0x00100000U) /* Filter bit 20 */
#define CAN_F13R1_FBC21                         ((uint32_t)0x00200000U) /* Filter bit 21 */
#define CAN_F13R1_FBC22                         ((uint32_t)0x00400000U) /* Filter bit 22 */
#define CAN_F13R1_FBC23                         ((uint32_t)0x00800000U) /* Filter bit 23 */
#define CAN_F13R1_FBC24                         ((uint32_t)0x01000000U) /* Filter bit 24 */
#define CAN_F13R1_FBC25                         ((uint32_t)0x02000000U) /* Filter bit 25 */
#define CAN_F13R1_FBC26                         ((uint32_t)0x04000000U) /* Filter bit 26 */
#define CAN_F13R1_FBC27                         ((uint32_t)0x08000000U) /* Filter bit 27 */
#define CAN_F13R1_FBC28                         ((uint32_t)0x10000000U) /* Filter bit 28 */
#define CAN_F13R1_FBC29                         ((uint32_t)0x20000000U) /* Filter bit 29 */
#define CAN_F13R1_FBC30                         ((uint32_t)0x40000000U) /* Filter bit 30 */
#define CAN_F13R1_FBC31                         ((uint32_t)0x80000000U) /* Filter bit 31 */

/**  Bit definition for CAN_F0R2 register  ***/
#define CAN_F0R2_FBC0                           ((uint32_t)0x00000001U) /* Filter bit 0 */
#define CAN_F0R2_FBC1                           ((uint32_t)0x00000002U) /* Filter bit 1 */
#define CAN_F0R2_FBC2                           ((uint32_t)0x00000004U) /* Filter bit 2 */
#define CAN_F0R2_FBC3                           ((uint32_t)0x00000008U) /* Filter bit 3 */
#define CAN_F0R2_FBC4                           ((uint32_t)0x00000010U) /* Filter bit 4 */
#define CAN_F0R2_FBC5                           ((uint32_t)0x00000020U) /* Filter bit 5 */
#define CAN_F0R2_FBC6                           ((uint32_t)0x00000040U) /* Filter bit 6 */
#define CAN_F0R2_FBC7                           ((uint32_t)0x00000080U) /* Filter bit 7 */
#define CAN_F0R2_FBC8                           ((uint32_t)0x00000100U) /* Filter bit 8 */
#define CAN_F0R2_FBC9                           ((uint32_t)0x00000200U) /* Filter bit 9 */
#define CAN_F0R2_FBC10                          ((uint32_t)0x00000400U) /* Filter bit 10 */
#define CAN_F0R2_FBC11                          ((uint32_t)0x00000800U) /* Filter bit 11 */
#define CAN_F0R2_FBC12                          ((uint32_t)0x00001000U) /* Filter bit 12 */
#define CAN_F0R2_FBC13                          ((uint32_t)0x00002000U) /* Filter bit 13 */
#define CAN_F0R2_FBC14                          ((uint32_t)0x00004000U) /* Filter bit 14 */
#define CAN_F0R2_FBC15                          ((uint32_t)0x00008000U) /* Filter bit 15 */
#define CAN_F0R2_FBC16                          ((uint32_t)0x00010000U) /* Filter bit 16 */
#define CAN_F0R2_FBC17                          ((uint32_t)0x00020000U) /* Filter bit 17 */
#define CAN_F0R2_FBC18                          ((uint32_t)0x00040000U) /* Filter bit 18 */
#define CAN_F0R2_FBC19                          ((uint32_t)0x00080000U) /* Filter bit 19 */
#define CAN_F0R2_FBC20                          ((uint32_t)0x00100000U) /* Filter bit 20 */
#define CAN_F0R2_FBC21                          ((uint32_t)0x00200000U) /* Filter bit 21 */
#define CAN_F0R2_FBC22                          ((uint32_t)0x00400000U) /* Filter bit 22 */
#define CAN_F0R2_FBC23                          ((uint32_t)0x00800000U) /* Filter bit 23 */
#define CAN_F0R2_FBC24                          ((uint32_t)0x01000000U) /* Filter bit 24 */
#define CAN_F0R2_FBC25                          ((uint32_t)0x02000000U) /* Filter bit 25 */
#define CAN_F0R2_FBC26                          ((uint32_t)0x04000000U) /* Filter bit 26 */
#define CAN_F0R2_FBC27                          ((uint32_t)0x08000000U) /* Filter bit 27 */
#define CAN_F0R2_FBC28                          ((uint32_t)0x10000000U) /* Filter bit 28 */
#define CAN_F0R2_FBC29                          ((uint32_t)0x20000000U) /* Filter bit 29 */
#define CAN_F0R2_FBC30                          ((uint32_t)0x40000000U) /* Filter bit 30 */
#define CAN_F0R2_FBC31                          ((uint32_t)0x80000000U) /* Filter bit 31 */

/**  Bit definition for CAN_F1R2 register  ***/
#define CAN_F1R2_FBC0                           ((uint32_t)0x00000001U) /* Filter bit 0 */
#define CAN_F1R2_FBC1                           ((uint32_t)0x00000002U) /* Filter bit 1 */
#define CAN_F1R2_FBC2                           ((uint32_t)0x00000004U) /* Filter bit 2 */
#define CAN_F1R2_FBC3                           ((uint32_t)0x00000008U) /* Filter bit 3 */
#define CAN_F1R2_FBC4                           ((uint32_t)0x00000010U) /* Filter bit 4 */
#define CAN_F1R2_FBC5                           ((uint32_t)0x00000020U) /* Filter bit 5 */
#define CAN_F1R2_FBC6                           ((uint32_t)0x00000040U) /* Filter bit 6 */
#define CAN_F1R2_FBC7                           ((uint32_t)0x00000080U) /* Filter bit 7 */
#define CAN_F1R2_FBC8                           ((uint32_t)0x00000100U) /* Filter bit 8 */
#define CAN_F1R2_FBC9                           ((uint32_t)0x00000200U) /* Filter bit 9 */
#define CAN_F1R2_FBC10                          ((uint32_t)0x00000400U) /* Filter bit 10 */
#define CAN_F1R2_FBC11                          ((uint32_t)0x00000800U) /* Filter bit 11 */
#define CAN_F1R2_FBC12                          ((uint32_t)0x00001000U) /* Filter bit 12 */
#define CAN_F1R2_FBC13                          ((uint32_t)0x00002000U) /* Filter bit 13 */
#define CAN_F1R2_FBC14                          ((uint32_t)0x00004000U) /* Filter bit 14 */
#define CAN_F1R2_FBC15                          ((uint32_t)0x00008000U) /* Filter bit 15 */
#define CAN_F1R2_FBC16                          ((uint32_t)0x00010000U) /* Filter bit 16 */
#define CAN_F1R2_FBC17                          ((uint32_t)0x00020000U) /* Filter bit 17 */
#define CAN_F1R2_FBC18                          ((uint32_t)0x00040000U) /* Filter bit 18 */
#define CAN_F1R2_FBC19                          ((uint32_t)0x00080000U) /* Filter bit 19 */
#define CAN_F1R2_FBC20                          ((uint32_t)0x00100000U) /* Filter bit 20 */
#define CAN_F1R2_FBC21                          ((uint32_t)0x00200000U) /* Filter bit 21 */
#define CAN_F1R2_FBC22                          ((uint32_t)0x00400000U) /* Filter bit 22 */
#define CAN_F1R2_FBC23                          ((uint32_t)0x00800000U) /* Filter bit 23 */
#define CAN_F1R2_FBC24                          ((uint32_t)0x01000000U) /* Filter bit 24 */
#define CAN_F1R2_FBC25                          ((uint32_t)0x02000000U) /* Filter bit 25 */
#define CAN_F1R2_FBC26                          ((uint32_t)0x04000000U) /* Filter bit 26 */
#define CAN_F1R2_FBC27                          ((uint32_t)0x08000000U) /* Filter bit 27 */
#define CAN_F1R2_FBC28                          ((uint32_t)0x10000000U) /* Filter bit 28 */
#define CAN_F1R2_FBC29                          ((uint32_t)0x20000000U) /* Filter bit 29 */
#define CAN_F1R2_FBC30                          ((uint32_t)0x40000000U) /* Filter bit 30 */
#define CAN_F1R2_FBC31                          ((uint32_t)0x80000000U) /* Filter bit 31 */

/**  Bit definition for CAN_F2R2 register  ***/
#define CAN_F2R2_FBC0                           ((uint32_t)0x00000001U) /* Filter bit 0 */
#define CAN_F2R2_FBC1                           ((uint32_t)0x00000002U) /* Filter bit 1 */
#define CAN_F2R2_FBC2                           ((uint32_t)0x00000004U) /* Filter bit 2 */
#define CAN_F2R2_FBC3                           ((uint32_t)0x00000008U) /* Filter bit 3 */
#define CAN_F2R2_FBC4                           ((uint32_t)0x00000010U) /* Filter bit 4 */
#define CAN_F2R2_FBC5                           ((uint32_t)0x00000020U) /* Filter bit 5 */
#define CAN_F2R2_FBC6                           ((uint32_t)0x00000040U) /* Filter bit 6 */
#define CAN_F2R2_FBC7                           ((uint32_t)0x00000080U) /* Filter bit 7 */
#define CAN_F2R2_FBC8                           ((uint32_t)0x00000100U) /* Filter bit 8 */
#define CAN_F2R2_FBC9                           ((uint32_t)0x00000200U) /* Filter bit 9 */
#define CAN_F2R2_FBC10                          ((uint32_t)0x00000400U) /* Filter bit 10 */
#define CAN_F2R2_FBC11                          ((uint32_t)0x00000800U) /* Filter bit 11 */
#define CAN_F2R2_FBC12                          ((uint32_t)0x00001000U) /* Filter bit 12 */
#define CAN_F2R2_FBC13                          ((uint32_t)0x00002000U) /* Filter bit 13 */
#define CAN_F2R2_FBC14                          ((uint32_t)0x00004000U) /* Filter bit 14 */
#define CAN_F2R2_FBC15                          ((uint32_t)0x00008000U) /* Filter bit 15 */
#define CAN_F2R2_FBC16                          ((uint32_t)0x00010000U) /* Filter bit 16 */
#define CAN_F2R2_FBC17                          ((uint32_t)0x00020000U) /* Filter bit 17 */
#define CAN_F2R2_FBC18                          ((uint32_t)0x00040000U) /* Filter bit 18 */
#define CAN_F2R2_FBC19                          ((uint32_t)0x00080000U) /* Filter bit 19 */
#define CAN_F2R2_FBC20                          ((uint32_t)0x00100000U) /* Filter bit 20 */
#define CAN_F2R2_FBC21                          ((uint32_t)0x00200000U) /* Filter bit 21 */
#define CAN_F2R2_FBC22                          ((uint32_t)0x00400000U) /* Filter bit 22 */
#define CAN_F2R2_FBC23                          ((uint32_t)0x00800000U) /* Filter bit 23 */
#define CAN_F2R2_FBC24                          ((uint32_t)0x01000000U) /* Filter bit 24 */
#define CAN_F2R2_FBC25                          ((uint32_t)0x02000000U) /* Filter bit 25 */
#define CAN_F2R2_FBC26                          ((uint32_t)0x04000000U) /* Filter bit 26 */
#define CAN_F2R2_FBC27                          ((uint32_t)0x08000000U) /* Filter bit 27 */
#define CAN_F2R2_FBC28                          ((uint32_t)0x10000000U) /* Filter bit 28 */
#define CAN_F2R2_FBC29                          ((uint32_t)0x20000000U) /* Filter bit 29 */
#define CAN_F2R2_FBC30                          ((uint32_t)0x40000000U) /* Filter bit 30 */
#define CAN_F2R2_FBC31                          ((uint32_t)0x80000000U) /* Filter bit 31 */

/**  Bit definition for CAN_F3R2 register  ***/
#define CAN_F3R2_FBC0                           ((uint32_t)0x00000001U) /* Filter bit 0 */
#define CAN_F3R2_FBC1                           ((uint32_t)0x00000002U) /* Filter bit 1 */
#define CAN_F3R2_FBC2                           ((uint32_t)0x00000004U) /* Filter bit 2 */
#define CAN_F3R2_FBC3                           ((uint32_t)0x00000008U) /* Filter bit 3 */
#define CAN_F3R2_FBC4                           ((uint32_t)0x00000010U) /* Filter bit 4 */
#define CAN_F3R2_FBC5                           ((uint32_t)0x00000020U) /* Filter bit 5 */
#define CAN_F3R2_FBC6                           ((uint32_t)0x00000040U) /* Filter bit 6 */
#define CAN_F3R2_FBC7                           ((uint32_t)0x00000080U) /* Filter bit 7 */
#define CAN_F3R2_FBC8                           ((uint32_t)0x00000100U) /* Filter bit 8 */
#define CAN_F3R2_FBC9                           ((uint32_t)0x00000200U) /* Filter bit 9 */
#define CAN_F3R2_FBC10                          ((uint32_t)0x00000400U) /* Filter bit 10 */
#define CAN_F3R2_FBC11                          ((uint32_t)0x00000800U) /* Filter bit 11 */
#define CAN_F3R2_FBC12                          ((uint32_t)0x00001000U) /* Filter bit 12 */
#define CAN_F3R2_FBC13                          ((uint32_t)0x00002000U) /* Filter bit 13 */
#define CAN_F3R2_FBC14                          ((uint32_t)0x00004000U) /* Filter bit 14 */
#define CAN_F3R2_FBC15                          ((uint32_t)0x00008000U) /* Filter bit 15 */
#define CAN_F3R2_FBC16                          ((uint32_t)0x00010000U) /* Filter bit 16 */
#define CAN_F3R2_FBC17                          ((uint32_t)0x00020000U) /* Filter bit 17 */
#define CAN_F3R2_FBC18                          ((uint32_t)0x00040000U) /* Filter bit 18 */
#define CAN_F3R2_FBC19                          ((uint32_t)0x00080000U) /* Filter bit 19 */
#define CAN_F3R2_FBC20                          ((uint32_t)0x00100000U) /* Filter bit 20 */
#define CAN_F3R2_FBC21                          ((uint32_t)0x00200000U) /* Filter bit 21 */
#define CAN_F3R2_FBC22                          ((uint32_t)0x00400000U) /* Filter bit 22 */
#define CAN_F3R2_FBC23                          ((uint32_t)0x00800000U) /* Filter bit 23 */
#define CAN_F3R2_FBC24                          ((uint32_t)0x01000000U) /* Filter bit 24 */
#define CAN_F3R2_FBC25                          ((uint32_t)0x02000000U) /* Filter bit 25 */
#define CAN_F3R2_FBC26                          ((uint32_t)0x04000000U) /* Filter bit 26 */
#define CAN_F3R2_FBC27                          ((uint32_t)0x08000000U) /* Filter bit 27 */
#define CAN_F3R2_FBC28                          ((uint32_t)0x10000000U) /* Filter bit 28 */
#define CAN_F3R2_FBC29                          ((uint32_t)0x20000000U) /* Filter bit 29 */
#define CAN_F3R2_FBC30                          ((uint32_t)0x40000000U) /* Filter bit 30 */
#define CAN_F3R2_FBC31                          ((uint32_t)0x80000000U) /* Filter bit 31 */

/**  Bit definition for CAN_F4R2 register  ***/
#define CAN_F4R2_FBC0                           ((uint32_t)0x00000001U) /* Filter bit 0 */
#define CAN_F4R2_FBC1                           ((uint32_t)0x00000002U) /* Filter bit 1 */
#define CAN_F4R2_FBC2                           ((uint32_t)0x00000004U) /* Filter bit 2 */
#define CAN_F4R2_FBC3                           ((uint32_t)0x00000008U) /* Filter bit 3 */
#define CAN_F4R2_FBC4                           ((uint32_t)0x00000010U) /* Filter bit 4 */
#define CAN_F4R2_FBC5                           ((uint32_t)0x00000020U) /* Filter bit 5 */
#define CAN_F4R2_FBC6                           ((uint32_t)0x00000040U) /* Filter bit 6 */
#define CAN_F4R2_FBC7                           ((uint32_t)0x00000080U) /* Filter bit 7 */
#define CAN_F4R2_FBC8                           ((uint32_t)0x00000100U) /* Filter bit 8 */
#define CAN_F4R2_FBC9                           ((uint32_t)0x00000200U) /* Filter bit 9 */
#define CAN_F4R2_FBC10                          ((uint32_t)0x00000400U) /* Filter bit 10 */
#define CAN_F4R2_FBC11                          ((uint32_t)0x00000800U) /* Filter bit 11 */
#define CAN_F4R2_FBC12                          ((uint32_t)0x00001000U) /* Filter bit 12 */
#define CAN_F4R2_FBC13                          ((uint32_t)0x00002000U) /* Filter bit 13 */
#define CAN_F4R2_FBC14                          ((uint32_t)0x00004000U) /* Filter bit 14 */
#define CAN_F4R2_FBC15                          ((uint32_t)0x00008000U) /* Filter bit 15 */
#define CAN_F4R2_FBC16                          ((uint32_t)0x00010000U) /* Filter bit 16 */
#define CAN_F4R2_FBC17                          ((uint32_t)0x00020000U) /* Filter bit 17 */
#define CAN_F4R2_FBC18                          ((uint32_t)0x00040000U) /* Filter bit 18 */
#define CAN_F4R2_FBC19                          ((uint32_t)0x00080000U) /* Filter bit 19 */
#define CAN_F4R2_FBC20                          ((uint32_t)0x00100000U) /* Filter bit 20 */
#define CAN_F4R2_FBC21                          ((uint32_t)0x00200000U) /* Filter bit 21 */
#define CAN_F4R2_FBC22                          ((uint32_t)0x00400000U) /* Filter bit 22 */
#define CAN_F4R2_FBC23                          ((uint32_t)0x00800000U) /* Filter bit 23 */
#define CAN_F4R2_FBC24                          ((uint32_t)0x01000000U) /* Filter bit 24 */
#define CAN_F4R2_FBC25                          ((uint32_t)0x02000000U) /* Filter bit 25 */
#define CAN_F4R2_FBC26                          ((uint32_t)0x04000000U) /* Filter bit 26 */
#define CAN_F4R2_FBC27                          ((uint32_t)0x08000000U) /* Filter bit 27 */
#define CAN_F4R2_FBC28                          ((uint32_t)0x10000000U) /* Filter bit 28 */
#define CAN_F4R2_FBC29                          ((uint32_t)0x20000000U) /* Filter bit 29 */
#define CAN_F4R2_FBC30                          ((uint32_t)0x40000000U) /* Filter bit 30 */
#define CAN_F4R2_FBC31                          ((uint32_t)0x80000000U) /* Filter bit 31 */

/**  Bit definition for CAN_F5R2 register  ***/
#define CAN_F5R2_FBC0                           ((uint32_t)0x00000001U) /* Filter bit 0 */
#define CAN_F5R2_FBC1                           ((uint32_t)0x00000002U) /* Filter bit 1 */
#define CAN_F5R2_FBC2                           ((uint32_t)0x00000004U) /* Filter bit 2 */
#define CAN_F5R2_FBC3                           ((uint32_t)0x00000008U) /* Filter bit 3 */
#define CAN_F5R2_FBC4                           ((uint32_t)0x00000010U) /* Filter bit 4 */
#define CAN_F5R2_FBC5                           ((uint32_t)0x00000020U) /* Filter bit 5 */
#define CAN_F5R2_FBC6                           ((uint32_t)0x00000040U) /* Filter bit 6 */
#define CAN_F5R2_FBC7                           ((uint32_t)0x00000080U) /* Filter bit 7 */
#define CAN_F5R2_FBC8                           ((uint32_t)0x00000100U) /* Filter bit 8 */
#define CAN_F5R2_FBC9                           ((uint32_t)0x00000200U) /* Filter bit 9 */
#define CAN_F5R2_FBC10                          ((uint32_t)0x00000400U) /* Filter bit 10 */
#define CAN_F5R2_FBC11                          ((uint32_t)0x00000800U) /* Filter bit 11 */
#define CAN_F5R2_FBC12                          ((uint32_t)0x00001000U) /* Filter bit 12 */
#define CAN_F5R2_FBC13                          ((uint32_t)0x00002000U) /* Filter bit 13 */
#define CAN_F5R2_FBC14                          ((uint32_t)0x00004000U) /* Filter bit 14 */
#define CAN_F5R2_FBC15                          ((uint32_t)0x00008000U) /* Filter bit 15 */
#define CAN_F5R2_FBC16                          ((uint32_t)0x00010000U) /* Filter bit 16 */
#define CAN_F5R2_FBC17                          ((uint32_t)0x00020000U) /* Filter bit 17 */
#define CAN_F5R2_FBC18                          ((uint32_t)0x00040000U) /* Filter bit 18 */
#define CAN_F5R2_FBC19                          ((uint32_t)0x00080000U) /* Filter bit 19 */
#define CAN_F5R2_FBC20                          ((uint32_t)0x00100000U) /* Filter bit 20 */
#define CAN_F5R2_FBC21                          ((uint32_t)0x00200000U) /* Filter bit 21 */
#define CAN_F5R2_FBC22                          ((uint32_t)0x00400000U) /* Filter bit 22 */
#define CAN_F5R2_FBC23                          ((uint32_t)0x00800000U) /* Filter bit 23 */
#define CAN_F5R2_FBC24                          ((uint32_t)0x01000000U) /* Filter bit 24 */
#define CAN_F5R2_FBC25                          ((uint32_t)0x02000000U) /* Filter bit 25 */
#define CAN_F5R2_FBC26                          ((uint32_t)0x04000000U) /* Filter bit 26 */
#define CAN_F5R2_FBC27                          ((uint32_t)0x08000000U) /* Filter bit 27 */
#define CAN_F5R2_FBC28                          ((uint32_t)0x10000000U) /* Filter bit 28 */
#define CAN_F5R2_FBC29                          ((uint32_t)0x20000000U) /* Filter bit 29 */
#define CAN_F5R2_FBC30                          ((uint32_t)0x40000000U) /* Filter bit 30 */
#define CAN_F5R2_FBC31                          ((uint32_t)0x80000000U) /* Filter bit 31 */

/**  Bit definition for CAN_F6R2 register  ***/
#define CAN_F6R2_FBC0                           ((uint32_t)0x00000001U) /* Filter bit 0 */
#define CAN_F6R2_FBC1                           ((uint32_t)0x00000002U) /* Filter bit 1 */
#define CAN_F6R2_FBC2                           ((uint32_t)0x00000004U) /* Filter bit 2 */
#define CAN_F6R2_FBC3                           ((uint32_t)0x00000008U) /* Filter bit 3 */
#define CAN_F6R2_FBC4                           ((uint32_t)0x00000010U) /* Filter bit 4 */
#define CAN_F6R2_FBC5                           ((uint32_t)0x00000020U) /* Filter bit 5 */
#define CAN_F6R2_FBC6                           ((uint32_t)0x00000040U) /* Filter bit 6 */
#define CAN_F6R2_FBC7                           ((uint32_t)0x00000080U) /* Filter bit 7 */
#define CAN_F6R2_FBC8                           ((uint32_t)0x00000100U) /* Filter bit 8 */
#define CAN_F6R2_FBC9                           ((uint32_t)0x00000200U) /* Filter bit 9 */
#define CAN_F6R2_FBC10                          ((uint32_t)0x00000400U) /* Filter bit 10 */
#define CAN_F6R2_FBC11                          ((uint32_t)0x00000800U) /* Filter bit 11 */
#define CAN_F6R2_FBC12                          ((uint32_t)0x00001000U) /* Filter bit 12 */
#define CAN_F6R2_FBC13                          ((uint32_t)0x00002000U) /* Filter bit 13 */
#define CAN_F6R2_FBC14                          ((uint32_t)0x00004000U) /* Filter bit 14 */
#define CAN_F6R2_FBC15                          ((uint32_t)0x00008000U) /* Filter bit 15 */
#define CAN_F6R2_FBC16                          ((uint32_t)0x00010000U) /* Filter bit 16 */
#define CAN_F6R2_FBC17                          ((uint32_t)0x00020000U) /* Filter bit 17 */
#define CAN_F6R2_FBC18                          ((uint32_t)0x00040000U) /* Filter bit 18 */
#define CAN_F6R2_FBC19                          ((uint32_t)0x00080000U) /* Filter bit 19 */
#define CAN_F6R2_FBC20                          ((uint32_t)0x00100000U) /* Filter bit 20 */
#define CAN_F6R2_FBC21                          ((uint32_t)0x00200000U) /* Filter bit 21 */
#define CAN_F6R2_FBC22                          ((uint32_t)0x00400000U) /* Filter bit 22 */
#define CAN_F6R2_FBC23                          ((uint32_t)0x00800000U) /* Filter bit 23 */
#define CAN_F6R2_FBC24                          ((uint32_t)0x01000000U) /* Filter bit 24 */
#define CAN_F6R2_FBC25                          ((uint32_t)0x02000000U) /* Filter bit 25 */
#define CAN_F6R2_FBC26                          ((uint32_t)0x04000000U) /* Filter bit 26 */
#define CAN_F6R2_FBC27                          ((uint32_t)0x08000000U) /* Filter bit 27 */
#define CAN_F6R2_FBC28                          ((uint32_t)0x10000000U) /* Filter bit 28 */
#define CAN_F6R2_FBC29                          ((uint32_t)0x20000000U) /* Filter bit 29 */
#define CAN_F6R2_FBC30                          ((uint32_t)0x40000000U) /* Filter bit 30 */
#define CAN_F6R2_FBC31                          ((uint32_t)0x80000000U) /* Filter bit 31 */

/**  Bit definition for CAN_F7R2 register  ***/
#define CAN_F7R2_FBC0                           ((uint32_t)0x00000001U) /* Filter bit 0 */
#define CAN_F7R2_FBC1                           ((uint32_t)0x00000002U) /* Filter bit 1 */
#define CAN_F7R2_FBC2                           ((uint32_t)0x00000004U) /* Filter bit 2 */
#define CAN_F7R2_FBC3                           ((uint32_t)0x00000008U) /* Filter bit 3 */
#define CAN_F7R2_FBC4                           ((uint32_t)0x00000010U) /* Filter bit 4 */
#define CAN_F7R2_FBC5                           ((uint32_t)0x00000020U) /* Filter bit 5 */
#define CAN_F7R2_FBC6                           ((uint32_t)0x00000040U) /* Filter bit 6 */
#define CAN_F7R2_FBC7                           ((uint32_t)0x00000080U) /* Filter bit 7 */
#define CAN_F7R2_FBC8                           ((uint32_t)0x00000100U) /* Filter bit 8 */
#define CAN_F7R2_FBC9                           ((uint32_t)0x00000200U) /* Filter bit 9 */
#define CAN_F7R2_FBC10                          ((uint32_t)0x00000400U) /* Filter bit 10 */
#define CAN_F7R2_FBC11                          ((uint32_t)0x00000800U) /* Filter bit 11 */
#define CAN_F7R2_FBC12                          ((uint32_t)0x00001000U) /* Filter bit 12 */
#define CAN_F7R2_FBC13                          ((uint32_t)0x00002000U) /* Filter bit 13 */
#define CAN_F7R2_FBC14                          ((uint32_t)0x00004000U) /* Filter bit 14 */
#define CAN_F7R2_FBC15                          ((uint32_t)0x00008000U) /* Filter bit 15 */
#define CAN_F7R2_FBC16                          ((uint32_t)0x00010000U) /* Filter bit 16 */
#define CAN_F7R2_FBC17                          ((uint32_t)0x00020000U) /* Filter bit 17 */
#define CAN_F7R2_FBC18                          ((uint32_t)0x00040000U) /* Filter bit 18 */
#define CAN_F7R2_FBC19                          ((uint32_t)0x00080000U) /* Filter bit 19 */
#define CAN_F7R2_FBC20                          ((uint32_t)0x00100000U) /* Filter bit 20 */
#define CAN_F7R2_FBC21                          ((uint32_t)0x00200000U) /* Filter bit 21 */
#define CAN_F7R2_FBC22                          ((uint32_t)0x00400000U) /* Filter bit 22 */
#define CAN_F7R2_FBC23                          ((uint32_t)0x00800000U) /* Filter bit 23 */
#define CAN_F7R2_FBC24                          ((uint32_t)0x01000000U) /* Filter bit 24 */
#define CAN_F7R2_FBC25                          ((uint32_t)0x02000000U) /* Filter bit 25 */
#define CAN_F7R2_FBC26                          ((uint32_t)0x04000000U) /* Filter bit 26 */
#define CAN_F7R2_FBC27                          ((uint32_t)0x08000000U) /* Filter bit 27 */
#define CAN_F7R2_FBC28                          ((uint32_t)0x10000000U) /* Filter bit 28 */
#define CAN_F7R2_FBC29                          ((uint32_t)0x20000000U) /* Filter bit 29 */
#define CAN_F7R2_FBC30                          ((uint32_t)0x40000000U) /* Filter bit 30 */
#define CAN_F7R2_FBC31                          ((uint32_t)0x80000000U) /* Filter bit 31 */

/**  Bit definition for CAN_F8R2 register  ***/
#define CAN_F8R2_FBC0                           ((uint32_t)0x00000001U) /* Filter bit 0 */
#define CAN_F8R2_FBC1                           ((uint32_t)0x00000002U) /* Filter bit 1 */
#define CAN_F8R2_FBC2                           ((uint32_t)0x00000004U) /* Filter bit 2 */
#define CAN_F8R2_FBC3                           ((uint32_t)0x00000008U) /* Filter bit 3 */
#define CAN_F8R2_FBC4                           ((uint32_t)0x00000010U) /* Filter bit 4 */
#define CAN_F8R2_FBC5                           ((uint32_t)0x00000020U) /* Filter bit 5 */
#define CAN_F8R2_FBC6                           ((uint32_t)0x00000040U) /* Filter bit 6 */
#define CAN_F8R2_FBC7                           ((uint32_t)0x00000080U) /* Filter bit 7 */
#define CAN_F8R2_FBC8                           ((uint32_t)0x00000100U) /* Filter bit 8 */
#define CAN_F8R2_FBC9                           ((uint32_t)0x00000200U) /* Filter bit 9 */
#define CAN_F8R2_FBC10                          ((uint32_t)0x00000400U) /* Filter bit 10 */
#define CAN_F8R2_FBC11                          ((uint32_t)0x00000800U) /* Filter bit 11 */
#define CAN_F8R2_FBC12                          ((uint32_t)0x00001000U) /* Filter bit 12 */
#define CAN_F8R2_FBC13                          ((uint32_t)0x00002000U) /* Filter bit 13 */
#define CAN_F8R2_FBC14                          ((uint32_t)0x00004000U) /* Filter bit 14 */
#define CAN_F8R2_FBC15                          ((uint32_t)0x00008000U) /* Filter bit 15 */
#define CAN_F8R2_FBC16                          ((uint32_t)0x00010000U) /* Filter bit 16 */
#define CAN_F8R2_FBC17                          ((uint32_t)0x00020000U) /* Filter bit 17 */
#define CAN_F8R2_FBC18                          ((uint32_t)0x00040000U) /* Filter bit 18 */
#define CAN_F8R2_FBC19                          ((uint32_t)0x00080000U) /* Filter bit 19 */
#define CAN_F8R2_FBC20                          ((uint32_t)0x00100000U) /* Filter bit 20 */
#define CAN_F8R2_FBC21                          ((uint32_t)0x00200000U) /* Filter bit 21 */
#define CAN_F8R2_FBC22                          ((uint32_t)0x00400000U) /* Filter bit 22 */
#define CAN_F8R2_FBC23                          ((uint32_t)0x00800000U) /* Filter bit 23 */
#define CAN_F8R2_FBC24                          ((uint32_t)0x01000000U) /* Filter bit 24 */
#define CAN_F8R2_FBC25                          ((uint32_t)0x02000000U) /* Filter bit 25 */
#define CAN_F8R2_FBC26                          ((uint32_t)0x04000000U) /* Filter bit 26 */
#define CAN_F8R2_FBC27                          ((uint32_t)0x08000000U) /* Filter bit 27 */
#define CAN_F8R2_FBC28                          ((uint32_t)0x10000000U) /* Filter bit 28 */
#define CAN_F8R2_FBC29                          ((uint32_t)0x20000000U) /* Filter bit 29 */
#define CAN_F8R2_FBC30                          ((uint32_t)0x40000000U) /* Filter bit 30 */
#define CAN_F8R2_FBC31                          ((uint32_t)0x80000000U) /* Filter bit 31 */

/**  Bit definition for CAN_F9R2 register  ***/
#define CAN_F9R2_FBC0                           ((uint32_t)0x00000001U) /* Filter bit 0 */
#define CAN_F9R2_FBC1                           ((uint32_t)0x00000002U) /* Filter bit 1 */
#define CAN_F9R2_FBC2                           ((uint32_t)0x00000004U) /* Filter bit 2 */
#define CAN_F9R2_FBC3                           ((uint32_t)0x00000008U) /* Filter bit 3 */
#define CAN_F9R2_FBC4                           ((uint32_t)0x00000010U) /* Filter bit 4 */
#define CAN_F9R2_FBC5                           ((uint32_t)0x00000020U) /* Filter bit 5 */
#define CAN_F9R2_FBC6                           ((uint32_t)0x00000040U) /* Filter bit 6 */
#define CAN_F9R2_FBC7                           ((uint32_t)0x00000080U) /* Filter bit 7 */
#define CAN_F9R2_FBC8                           ((uint32_t)0x00000100U) /* Filter bit 8 */
#define CAN_F9R2_FBC9                           ((uint32_t)0x00000200U) /* Filter bit 9 */
#define CAN_F9R2_FBC10                          ((uint32_t)0x00000400U) /* Filter bit 10 */
#define CAN_F9R2_FBC11                          ((uint32_t)0x00000800U) /* Filter bit 11 */
#define CAN_F9R2_FBC12                          ((uint32_t)0x00001000U) /* Filter bit 12 */
#define CAN_F9R2_FBC13                          ((uint32_t)0x00002000U) /* Filter bit 13 */
#define CAN_F9R2_FBC14                          ((uint32_t)0x00004000U) /* Filter bit 14 */
#define CAN_F9R2_FBC15                          ((uint32_t)0x00008000U) /* Filter bit 15 */
#define CAN_F9R2_FBC16                          ((uint32_t)0x00010000U) /* Filter bit 16 */
#define CAN_F9R2_FBC17                          ((uint32_t)0x00020000U) /* Filter bit 17 */
#define CAN_F9R2_FBC18                          ((uint32_t)0x00040000U) /* Filter bit 18 */
#define CAN_F9R2_FBC19                          ((uint32_t)0x00080000U) /* Filter bit 19 */
#define CAN_F9R2_FBC20                          ((uint32_t)0x00100000U) /* Filter bit 20 */
#define CAN_F9R2_FBC21                          ((uint32_t)0x00200000U) /* Filter bit 21 */
#define CAN_F9R2_FBC22                          ((uint32_t)0x00400000U) /* Filter bit 22 */
#define CAN_F9R2_FBC23                          ((uint32_t)0x00800000U) /* Filter bit 23 */
#define CAN_F9R2_FBC24                          ((uint32_t)0x01000000U) /* Filter bit 24 */
#define CAN_F9R2_FBC25                          ((uint32_t)0x02000000U) /* Filter bit 25 */
#define CAN_F9R2_FBC26                          ((uint32_t)0x04000000U) /* Filter bit 26 */
#define CAN_F9R2_FBC27                          ((uint32_t)0x08000000U) /* Filter bit 27 */
#define CAN_F9R2_FBC28                          ((uint32_t)0x10000000U) /* Filter bit 28 */
#define CAN_F9R2_FBC29                          ((uint32_t)0x20000000U) /* Filter bit 29 */
#define CAN_F9R2_FBC30                          ((uint32_t)0x40000000U) /* Filter bit 30 */
#define CAN_F9R2_FBC31                          ((uint32_t)0x80000000U) /* Filter bit 31 */

/**  Bit definition for CAN_F10R2 register  **/
#define CAN_F10R2_FBC0                          ((uint32_t)0x00000001U) /* Filter bit 0 */
#define CAN_F10R2_FBC1                          ((uint32_t)0x00000002U) /* Filter bit 1 */
#define CAN_F10R2_FBC2                          ((uint32_t)0x00000004U) /* Filter bit 2 */
#define CAN_F10R2_FBC3                          ((uint32_t)0x00000008U) /* Filter bit 3 */
#define CAN_F10R2_FBC4                          ((uint32_t)0x00000010U) /* Filter bit 4 */
#define CAN_F10R2_FBC5                          ((uint32_t)0x00000020U) /* Filter bit 5 */
#define CAN_F10R2_FBC6                          ((uint32_t)0x00000040U) /* Filter bit 6 */
#define CAN_F10R2_FBC7                          ((uint32_t)0x00000080U) /* Filter bit 7 */
#define CAN_F10R2_FBC8                          ((uint32_t)0x00000100U) /* Filter bit 8 */
#define CAN_F10R2_FBC9                          ((uint32_t)0x00000200U) /* Filter bit 9 */
#define CAN_F10R2_FBC10                         ((uint32_t)0x00000400U) /* Filter bit 10 */
#define CAN_F10R2_FBC11                         ((uint32_t)0x00000800U) /* Filter bit 11 */
#define CAN_F10R2_FBC12                         ((uint32_t)0x00001000U) /* Filter bit 12 */
#define CAN_F10R2_FBC13                         ((uint32_t)0x00002000U) /* Filter bit 13 */
#define CAN_F10R2_FBC14                         ((uint32_t)0x00004000U) /* Filter bit 14 */
#define CAN_F10R2_FBC15                         ((uint32_t)0x00008000U) /* Filter bit 15 */
#define CAN_F10R2_FBC16                         ((uint32_t)0x00010000U) /* Filter bit 16 */
#define CAN_F10R2_FBC17                         ((uint32_t)0x00020000U) /* Filter bit 17 */
#define CAN_F10R2_FBC18                         ((uint32_t)0x00040000U) /* Filter bit 18 */
#define CAN_F10R2_FBC19                         ((uint32_t)0x00080000U) /* Filter bit 19 */
#define CAN_F10R2_FBC20                         ((uint32_t)0x00100000U) /* Filter bit 20 */
#define CAN_F10R2_FBC21                         ((uint32_t)0x00200000U) /* Filter bit 21 */
#define CAN_F10R2_FBC22                         ((uint32_t)0x00400000U) /* Filter bit 22 */
#define CAN_F10R2_FBC23                         ((uint32_t)0x00800000U) /* Filter bit 23 */
#define CAN_F10R2_FBC24                         ((uint32_t)0x01000000U) /* Filter bit 24 */
#define CAN_F10R2_FBC25                         ((uint32_t)0x02000000U) /* Filter bit 25 */
#define CAN_F10R2_FBC26                         ((uint32_t)0x04000000U) /* Filter bit 26 */
#define CAN_F10R2_FBC27                         ((uint32_t)0x08000000U) /* Filter bit 27 */
#define CAN_F10R2_FBC28                         ((uint32_t)0x10000000U) /* Filter bit 28 */
#define CAN_F10R2_FBC29                         ((uint32_t)0x20000000U) /* Filter bit 29 */
#define CAN_F10R2_FBC30                         ((uint32_t)0x40000000U) /* Filter bit 30 */
#define CAN_F10R2_FBC31                         ((uint32_t)0x80000000U) /* Filter bit 31 */

/**  Bit definition for CAN_F11R2 register  **/
#define CAN_F11R2_FBC0                          ((uint32_t)0x00000001U) /* Filter bit 0 */
#define CAN_F11R2_FBC1                          ((uint32_t)0x00000002U) /* Filter bit 1 */
#define CAN_F11R2_FBC2                          ((uint32_t)0x00000004U) /* Filter bit 2 */
#define CAN_F11R2_FBC3                          ((uint32_t)0x00000008U) /* Filter bit 3 */
#define CAN_F11R2_FBC4                          ((uint32_t)0x00000010U) /* Filter bit 4 */
#define CAN_F11R2_FBC5                          ((uint32_t)0x00000020U) /* Filter bit 5 */
#define CAN_F11R2_FBC6                          ((uint32_t)0x00000040U) /* Filter bit 6 */
#define CAN_F11R2_FBC7                          ((uint32_t)0x00000080U) /* Filter bit 7 */
#define CAN_F11R2_FBC8                          ((uint32_t)0x00000100U) /* Filter bit 8 */
#define CAN_F11R2_FBC9                          ((uint32_t)0x00000200U) /* Filter bit 9 */
#define CAN_F11R2_FBC10                         ((uint32_t)0x00000400U) /* Filter bit 10 */
#define CAN_F11R2_FBC11                         ((uint32_t)0x00000800U) /* Filter bit 11 */
#define CAN_F11R2_FBC12                         ((uint32_t)0x00001000U) /* Filter bit 12 */
#define CAN_F11R2_FBC13                         ((uint32_t)0x00002000U) /* Filter bit 13 */
#define CAN_F11R2_FBC14                         ((uint32_t)0x00004000U) /* Filter bit 14 */
#define CAN_F11R2_FBC15                         ((uint32_t)0x00008000U) /* Filter bit 15 */
#define CAN_F11R2_FBC16                         ((uint32_t)0x00010000U) /* Filter bit 16 */
#define CAN_F11R2_FBC17                         ((uint32_t)0x00020000U) /* Filter bit 17 */
#define CAN_F11R2_FBC18                         ((uint32_t)0x00040000U) /* Filter bit 18 */
#define CAN_F11R2_FBC19                         ((uint32_t)0x00080000U) /* Filter bit 19 */
#define CAN_F11R2_FBC20                         ((uint32_t)0x00100000U) /* Filter bit 20 */
#define CAN_F11R2_FBC21                         ((uint32_t)0x00200000U) /* Filter bit 21 */
#define CAN_F11R2_FBC22                         ((uint32_t)0x00400000U) /* Filter bit 22 */
#define CAN_F11R2_FBC23                         ((uint32_t)0x00800000U) /* Filter bit 23 */
#define CAN_F11R2_FBC24                         ((uint32_t)0x01000000U) /* Filter bit 24 */
#define CAN_F11R2_FBC25                         ((uint32_t)0x02000000U) /* Filter bit 25 */
#define CAN_F11R2_FBC26                         ((uint32_t)0x04000000U) /* Filter bit 26 */
#define CAN_F11R2_FBC27                         ((uint32_t)0x08000000U) /* Filter bit 27 */
#define CAN_F11R2_FBC28                         ((uint32_t)0x10000000U) /* Filter bit 28 */
#define CAN_F11R2_FBC29                         ((uint32_t)0x20000000U) /* Filter bit 29 */
#define CAN_F11R2_FBC30                         ((uint32_t)0x40000000U) /* Filter bit 30 */
#define CAN_F11R2_FBC31                         ((uint32_t)0x80000000U) /* Filter bit 31 */

/**  Bit definition for CAN_F12R2 register  **/
#define CAN_F12R2_FBC0                          ((uint32_t)0x00000001U) /* Filter bit 0 */
#define CAN_F12R2_FBC1                          ((uint32_t)0x00000002U) /* Filter bit 1 */
#define CAN_F12R2_FBC2                          ((uint32_t)0x00000004U) /* Filter bit 2 */
#define CAN_F12R2_FBC3                          ((uint32_t)0x00000008U) /* Filter bit 3 */
#define CAN_F12R2_FBC4                          ((uint32_t)0x00000010U) /* Filter bit 4 */
#define CAN_F12R2_FBC5                          ((uint32_t)0x00000020U) /* Filter bit 5 */
#define CAN_F12R2_FBC6                          ((uint32_t)0x00000040U) /* Filter bit 6 */
#define CAN_F12R2_FBC7                          ((uint32_t)0x00000080U) /* Filter bit 7 */
#define CAN_F12R2_FBC8                          ((uint32_t)0x00000100U) /* Filter bit 8 */
#define CAN_F12R2_FBC9                          ((uint32_t)0x00000200U) /* Filter bit 9 */
#define CAN_F12R2_FBC10                         ((uint32_t)0x00000400U) /* Filter bit 10 */
#define CAN_F12R2_FBC11                         ((uint32_t)0x00000800U) /* Filter bit 11 */
#define CAN_F12R2_FBC12                         ((uint32_t)0x00001000U) /* Filter bit 12 */
#define CAN_F12R2_FBC13                         ((uint32_t)0x00002000U) /* Filter bit 13 */
#define CAN_F12R2_FBC14                         ((uint32_t)0x00004000U) /* Filter bit 14 */
#define CAN_F12R2_FBC15                         ((uint32_t)0x00008000U) /* Filter bit 15 */
#define CAN_F12R2_FBC16                         ((uint32_t)0x00010000U) /* Filter bit 16 */
#define CAN_F12R2_FBC17                         ((uint32_t)0x00020000U) /* Filter bit 17 */
#define CAN_F12R2_FBC18                         ((uint32_t)0x00040000U) /* Filter bit 18 */
#define CAN_F12R2_FBC19                         ((uint32_t)0x00080000U) /* Filter bit 19 */
#define CAN_F12R2_FBC20                         ((uint32_t)0x00100000U) /* Filter bit 20 */
#define CAN_F12R2_FBC21                         ((uint32_t)0x00200000U) /* Filter bit 21 */
#define CAN_F12R2_FBC22                         ((uint32_t)0x00400000U) /* Filter bit 22 */
#define CAN_F12R2_FBC23                         ((uint32_t)0x00800000U) /* Filter bit 23 */
#define CAN_F12R2_FBC24                         ((uint32_t)0x01000000U) /* Filter bit 24 */
#define CAN_F12R2_FBC25                         ((uint32_t)0x02000000U) /* Filter bit 25 */
#define CAN_F12R2_FBC26                         ((uint32_t)0x04000000U) /* Filter bit 26 */
#define CAN_F12R2_FBC27                         ((uint32_t)0x08000000U) /* Filter bit 27 */
#define CAN_F12R2_FBC28                         ((uint32_t)0x10000000U) /* Filter bit 28 */
#define CAN_F12R2_FBC29                         ((uint32_t)0x20000000U) /* Filter bit 29 */
#define CAN_F12R2_FBC30                         ((uint32_t)0x40000000U) /* Filter bit 30 */
#define CAN_F12R2_FBC31                         ((uint32_t)0x80000000U) /* Filter bit 31 */

/**  Bit definition for CAN_F13R2 register  **/
#define CAN_F13R2_FBC0                          ((uint32_t)0x00000001U) /* Filter bit 0 */
#define CAN_F13R2_FBC1                          ((uint32_t)0x00000002U) /* Filter bit 1 */
#define CAN_F13R2_FBC2                          ((uint32_t)0x00000004U) /* Filter bit 2 */
#define CAN_F13R2_FBC3                          ((uint32_t)0x00000008U) /* Filter bit 3 */
#define CAN_F13R2_FBC4                          ((uint32_t)0x00000010U) /* Filter bit 4 */
#define CAN_F13R2_FBC5                          ((uint32_t)0x00000020U) /* Filter bit 5 */
#define CAN_F13R2_FBC6                          ((uint32_t)0x00000040U) /* Filter bit 6 */
#define CAN_F13R2_FBC7                          ((uint32_t)0x00000080U) /* Filter bit 7 */
#define CAN_F13R2_FBC8                          ((uint32_t)0x00000100U) /* Filter bit 8 */
#define CAN_F13R2_FBC9                          ((uint32_t)0x00000200U) /* Filter bit 9 */
#define CAN_F13R2_FBC10                         ((uint32_t)0x00000400U) /* Filter bit 10 */
#define CAN_F13R2_FBC11                         ((uint32_t)0x00000800U) /* Filter bit 11 */
#define CAN_F13R2_FBC12                         ((uint32_t)0x00001000U) /* Filter bit 12 */
#define CAN_F13R2_FBC13                         ((uint32_t)0x00002000U) /* Filter bit 13 */
#define CAN_F13R2_FBC14                         ((uint32_t)0x00004000U) /* Filter bit 14 */
#define CAN_F13R2_FBC15                         ((uint32_t)0x00008000U) /* Filter bit 15 */
#define CAN_F13R2_FBC16                         ((uint32_t)0x00010000U) /* Filter bit 16 */
#define CAN_F13R2_FBC17                         ((uint32_t)0x00020000U) /* Filter bit 17 */
#define CAN_F13R2_FBC18                         ((uint32_t)0x00040000U) /* Filter bit 18 */
#define CAN_F13R2_FBC19                         ((uint32_t)0x00080000U) /* Filter bit 19 */
#define CAN_F13R2_FBC20                         ((uint32_t)0x00100000U) /* Filter bit 20 */
#define CAN_F13R2_FBC21                         ((uint32_t)0x00200000U) /* Filter bit 21 */
#define CAN_F13R2_FBC22                         ((uint32_t)0x00400000U) /* Filter bit 22 */
#define CAN_F13R2_FBC23                         ((uint32_t)0x00800000U) /* Filter bit 23 */
#define CAN_F13R2_FBC24                         ((uint32_t)0x01000000U) /* Filter bit 24 */
#define CAN_F13R2_FBC25                         ((uint32_t)0x02000000U) /* Filter bit 25 */
#define CAN_F13R2_FBC26                         ((uint32_t)0x04000000U) /* Filter bit 26 */
#define CAN_F13R2_FBC27                         ((uint32_t)0x08000000U) /* Filter bit 27 */
#define CAN_F13R2_FBC28                         ((uint32_t)0x10000000U) /* Filter bit 28 */
#define CAN_F13R2_FBC29                         ((uint32_t)0x20000000U) /* Filter bit 29 */
#define CAN_F13R2_FBC30                         ((uint32_t)0x40000000U) /* Filter bit 30 */
#define CAN_F13R2_FBC31                         ((uint32_t)0x80000000U) /* Filter bit 31 */


/*** Serial Peripheral Interface ***/

/** Bit definition for SPI_CTRL1 register **/
#define SPI_CTRL1_BR        ((uint16_t)0x0007U)      /* BR[2:0] bits (Baud Rate Control) */
#define SPI_CTRL1_BR0       ((uint16_t)0x0001U)      /* Bit 0 */
#define SPI_CTRL1_BR1       ((uint16_t)0x0002U)      /* Bit 1 */
#define SPI_CTRL1_BR2       ((uint16_t)0x0004U)      /* Bit 2 */
#define SPI_CTRL1_CLKPOL    ((uint16_t)0x0010U)      /* Clock Polarity */
#define SPI_CTRL1_CLKPHA    ((uint16_t)0x0020U)      /* Clock Phase */
#define SPI_CTRL1_MSEL      ((uint16_t)0x0040U)      /* Master Selection */
#define SPI_CTRL1_LSBFF     ((uint16_t)0x0080U)      /* Frame Format */
#define SPI_CTRL1_DATFF     ((uint16_t)0x0100U)      /* Data Frame Format */
#define SPI_CTRL1_CRCNEXT   ((uint16_t)0x0200U)      /* Transmit CRC next */
#define SPI_CTRL1_SSOEN     ((uint16_t)0x0400U)      /* SS Output Enable */
#define SPI_CTRL1_SSEL      ((uint16_t)0x0800U)      /* Internal slave select */
#define SPI_CTRL1_SSMEN     ((uint16_t)0x1000U)      /* Software slave management */
#define SPI_CTRL1_RONLY     ((uint16_t)0x2000U)      /* Receive only */
#define SPI_CTRL1_BIDIROEN  ((uint16_t)0x4000U)      /* Output enable in bidirectional mode */
#define SPI_CTRL1_BIDIRMODE ((uint16_t)0x8000U)      /* Bidirectional data mode enable */

/** Bit definition for SPI_CTRL2 register **/ 
#define SPI_CTRL2_SPIEN     ((uint16_t)0x0001U)      /* SPI Enable */
#define SPI_CTRL2_RDMAEN    ((uint16_t)0x0002U)      /* Rx buffer DMA enable */
#define SPI_CTRL2_TDMAEN    ((uint16_t)0x0004U)      /* Tx buffer DMA enable */
#define SPI_CTRL2_CRCEN     ((uint16_t)0x0008U)      /* Hardware CRC calculation enable */
#define SPI_CTRL2_TEINTEN   ((uint16_t)0x0010U)      /* Tx buffer Empty Interrupt Enable */
#define SPI_CTRL2_RNEINTEN  ((uint16_t)0x0020U)      /* RX buffer Not Empty Interrupt Enable */
#define SPI_CTRL2_ERRINTEN  ((uint16_t)0x0040U)      /* Error Interrupt Enable */
#define SPI_CTRL2_NSSPOL    ((uint16_t)0x0080U)      /* NSS polarity */
#define SPI_CTRL2_CRCSTP    ((uint16_t)0x2000U)      /* CRC stop calculation control */

/** Bit definition for SPI_STS register **/
#define SPI_STS_TE          ((uint16_t)0x0001U)      /* Transmit buffer Empty */
#define SPI_STS_RNE         ((uint16_t)0x0002U)      /* Receive buffer Not Empty */
#define SPI_STS_BUSY        ((uint16_t)0x0004U)      /* Busy flag */
#define SPI_STS_CRCERR      ((uint16_t)0x0008U)      /* CRC fault */
#define SPI_STS_MODERR      ((uint16_t)0x0010U)      /* Mode fault */
#define SPI_STS_OVER        ((uint16_t)0x0020U)      /* Overrun flag */

/** Bit definition for SPI_DAT register **/
#define SPI_DAT_DAT         ((uint16_t)0xFFFFU)      /* Data Register */

/** Bit definition for SPI_CRCTDAT register **/
#define SPI_CRCTDAT_DAT     ((uint16_t)0xFFFFU)      /* The CRC result value to send */

/** Bit definition for SPI_CRCRDAT register **/
#define SPI_CRCRDAT_DAT     ((uint16_t)0xFFFFU)      /* The received CRC result value */

/** Bit definition for SPI_CRCPOLY register **/
#define SPI_CRCPOLY_DAT     ((uint16_t)0xFFFFU)      /* CRC polynomial */

/** Bit definition for SPI_CTRL3 register **/
#define SPI_CTRL3_DELAYTIME ((uint16_t)0x000FU)      /* SPI Host Clock Delay Time Configuration */


/*** Inter-integrated Circuit Interface ***/

/** Bit definition for I2C_CTRL1 register **/
#define I2C_CTRL1_EN       ((uint32_t)0x00000001U) /* Peripheral Enable */
#define I2C_CTRL1_SMBMODE  ((uint32_t)0x00000002U) /* SMBus Mode */
#define I2C_CTRL1_SMBTYPE  ((uint32_t)0x00000004U) /* SMBus Type */
#define I2C_CTRL1_ARPEN    ((uint32_t)0x00000008U) /* ARP Enable */
#define I2C_CTRL1_PECEN    ((uint32_t)0x00000010U) /* PEC Enable */
#define I2C_CTRL1_GCEN     ((uint32_t)0x00000020U) /* General Call Enable */
#define I2C_CTRL1_NOEXTEND ((uint32_t)0x00000040U) /* Clock Stretching Disable (Slave mode) */
#define I2C_CTRL1_STARTGEN ((uint32_t)0x00000080U) /* Start Generation */
#define I2C_CTRL1_STOPGEN  ((uint32_t)0x00000100U) /* Stop Generation */
#define I2C_CTRL1_ACKEN    ((uint32_t)0x00000200U) /* Acknowledge Enable */
#define I2C_CTRL1_ACKPOS   ((uint32_t)0x00000400U) /* Acknowledge/PEC Position (for data reception) */
#define I2C_CTRL1_PEC      ((uint32_t)0x00000800U) /* Packet Error Checking */
#define I2C_CTRL1_SMBALERT ((uint32_t)0x00001000U) /* SMBus Alert */
#define I2C_CTRL1_SWRESET  ((uint32_t)0x00002000U) /* Software Reset */

#define I2C_CTRL1_HTOSEL   ((uint32_t)0x18000000U) /* high timeout threshold selection */
#define I2C_CTRL1_HTOSEL_0 ((uint32_t)0x08000000U) /* Bit 0 */
#define I2C_CTRL1_HTOSEL_1 ((uint32_t)0x10000000U) /* Bit 1 */

#define I2C_CTRL1_LTOSEL   ((uint32_t)0x60000000U) /* low timeout threshold selection */
#define I2C_CTRL1_LTOSEL_0 ((uint32_t)0x20000000U) /* Bit 0 */
#define I2C_CTRL1_LTOSEL_1 ((uint32_t)0x40000000U) /* Bit 1 */

/** Bit definition for I2C_CTRL2 register **/
#define I2C_CTRL2_CLKFREQ   ((uint32_t)0x0000007FU) /* FREQ[6:0] bits (Peripheral Clock Frequency) */
#define I2C_CTRL2_CLKFREQ_0 ((uint32_t)0x00000001U) /* Bit 0 */
#define I2C_CTRL2_CLKFREQ_1 ((uint32_t)0x00000002U) /* Bit 1 */
#define I2C_CTRL2_CLKFREQ_2 ((uint32_t)0x00000004U) /* Bit 2 */
#define I2C_CTRL2_CLKFREQ_3 ((uint32_t)0x00000008U) /* Bit 3 */
#define I2C_CTRL2_CLKFREQ_4 ((uint32_t)0x00000010U) /* Bit 4 */
#define I2C_CTRL2_CLKFREQ_5 ((uint32_t)0x00000020U) /* Bit 5 */
#define I2C_CTRL2_CLKFREQ_6 ((uint32_t)0x00000040U) /* Bit 6 */

#define I2C_CTRL2_DMALAST  ((uint32_t)0x00000100U) /* DMA Last Transfer */
#define I2C_CTRL2_BUFINTEN ((uint32_t)0x00001000U) /* Buffer Interrupt Enable */
#define I2C_CTRL2_EVTINTEN ((uint32_t)0x00002000U) /* Event Interrupt Enable */
#define I2C_CTRL2_ERRINTEN ((uint32_t)0x00004000U) /* Error Interrupt Enable */
#define I2C_CTRL2_DMAEN    ((uint32_t)0x00008000U) /* DMA Requests Enable */

#define I2C_CTRL2_SDALTOINTEN    ((uint32_t)0x04000000U) /* SDA low timeout error interrupt enable */
#define I2C_CTRL2_SCLHTOINTEN    ((uint32_t)0x08000000U) /* SCL high timeout error interrupt enable */
#define I2C_CTRL2_SCLLTOINTEN    ((uint32_t)0x10000000U) /* SCL low timeout error interrupt enable */
#define I2C_CTRL2_HTOEN          ((uint32_t)0x20000000U) /* high timeout function enable */
#define I2C_CTRL2_LTOEN          ((uint32_t)0x40000000U) /* low timeout function enable */

/** Bit definition for I2C_OADDR1 register **/
#define I2C_OADDR1_ADDR1_7 ((uint16_t)0x00FEU) /* Interface Address */
#define I2C_OADDR1_ADDR8_9 ((uint16_t)0x0300U) /* Interface Address */

#define I2C_OADDR1_ADDR0 ((uint16_t)0x0001U) /* Bit 0 */
#define I2C_OADDR1_ADDR1 ((uint16_t)0x0002U) /* Bit 1 */
#define I2C_OADDR1_ADDR2 ((uint16_t)0x0004U) /* Bit 2 */
#define I2C_OADDR1_ADDR3 ((uint16_t)0x0008U) /* Bit 3 */
#define I2C_OADDR1_ADDR4 ((uint16_t)0x0010U) /* Bit 4 */
#define I2C_OADDR1_ADDR5 ((uint16_t)0x0020U) /* Bit 5 */
#define I2C_OADDR1_ADDR6 ((uint16_t)0x0040U) /* Bit 6 */
#define I2C_OADDR1_ADDR7 ((uint16_t)0x0080U) /* Bit 7 */
#define I2C_OADDR1_ADDR8 ((uint16_t)0x0100U) /* Bit 8 */
#define I2C_OADDR1_ADDR9 ((uint16_t)0x0200U) /* Bit 9 */

#define I2C_OADDR1_ADDRMODE ((uint16_t)0x8000U) /* Addressing Mode (Slave mode) */

/** Bit definition for I2C_OADDR2 register **/
#define I2C_OADDR2_DUALEN ((uint8_t)0x01U) /* Dual addressing mode enable */
#define I2C_OADDR2_ADDR2  ((uint8_t)0xFEU) /* Interface address */

/** Bit definition for I2C_DAT register **/
#define I2C_DAT_DATA ((uint8_t)0xFFU) /* 8-bit Data Register */

/** Bit definition for I2C_STS1 register **/
#define I2C_STS1_STARTBF  ((uint16_t)0x0001U) /* Start Bit (Master mode) */
#define I2C_STS1_ADDRF    ((uint16_t)0x0002U) /* Address sent (master mode)/matched (slave mode) */
#define I2C_STS1_BSF      ((uint16_t)0x0004U) /* Byte Transfer Finished */
#define I2C_STS1_STOPF    ((uint16_t)0x0008U) /* Stop detection (Slave mode) */
#define I2C_STS1_RXDATNE  ((uint16_t)0x0010U) /* Data Register not Empty (receivers) */
#define I2C_STS1_TXDATE   ((uint16_t)0x0020U) /* Data Register Empty (transmitters) */
#define I2C_STS1_ADDR10F  ((uint16_t)0x0040U) /* 10-bit header sent (Master mode) */

#define I2C_STS1_ACKFAIL  ((uint16_t)0x0100U) /* Acknowledge Failure */
#define I2C_STS1_ARLOST   ((uint16_t)0x0200U) /* Arbitration Lost (master mode) */
#define I2C_STS1_BUSERR   ((uint16_t)0x0400U) /* Bus Error */
#define I2C_STS1_OVERRUN  ((uint16_t)0x0800U) /* Overrun/Underrun */
#define I2C_STS1_PECERR   ((uint16_t)0x1000U) /* PEC Error in reception */
#define I2C_STS1_SMBALERT ((uint16_t)0x4000U) /* SMBus Alert */

#define I2C_STS1_SDALTO   ((uint32_t)0x00800000U) /* SDA low timeout error */
#define I2C_STS1_SCLHTO   ((uint32_t)0x01000000U) /* SCL high timeout error */
#define I2C_STS1_SCLLTO   ((uint32_t)0x02000000U) /* SCL low timeout error */

/** Bit definition for I2C_STS2 register **/

#define I2C_STS2_BUSY      ((uint16_t)0x0001U) /* Bus Busy */
#define I2C_STS2_MSMODE    ((uint16_t)0x0002U) /* Master/Slave */
#define I2C_STS2_TRF       ((uint16_t)0x0004U) /* Transmitter/Receiver */

#define I2C_STS2_GCALLADDR ((uint16_t)0x0010U) /* General Call Address (Slave mode) */
#define I2C_STS2_DUALFLAG  ((uint16_t)0x0020U) /* Dual Flag (Slave mode) */
#define I2C_STS2_SMBDADDR  ((uint16_t)0x0040U) /* SMBus Device Default Address (Slave mode) */
#define I2C_STS2_SMBHADDR  ((uint16_t)0x0080U) /* SMBus Host Header (Slave mode) */

#define I2C_STS2_PECVAL    ((uint16_t)0xFF00U) /* Packet Error Checking Register */

/** Bit definition for I2C_CLKCTRL register **/
#define I2C_CLKCTRL_CLKCTRL ((uint16_t)0x0FFFU) /* Clock Control Register in Fast/Standard mode (Master mode) */
#define I2C_CLKCTRL_FSMODE  ((uint16_t)0x4000U) /* I2C Master Mode Selection */
#define I2C_CLKCTRL_DUTY    ((uint16_t)0x8000U) /* Fast Mode Duty Cycle */

/**  Bit definition for I2C_TMRISE register  ***/
#define  I2C_TMRISE_TMRISE   ((uint8_t)0x3FU)               /* Maximum Rise Time in Fast/Standard mode (Master mode) */

/**  Bit definition for I2C_BYTENUM register  ***/
#define  I2C_BYTENUM_BYTENUM       ((uint16_t)0x3FFFU)     /* Master receives bytes configuration */
#define  I2C_BYTENUM_RXFSEL        ((uint16_t)0x4000U)     /* Receive end send condition selection */
#define  I2C_BYTENUM_BYTENUMEN     ((uint16_t)0x8000U)     /* Master receive byte control enable */

/**  Bit definition for I2C_GFLTRCTRL register  ***/
#define  I2C_GFLTRCTRL_SDADFW   ((uint16_t)0x000FU) /* SDA digital gfilter width selection */
#define  I2C_GFLTRCTRL_SCLDFW   ((uint16_t)0x00F0U) /* SCL digital gfilter width selection */

#define  I2C_GFLTRCTRL_SDAAFW   ((uint16_t)0x0300U) /* SDA analog gfilter width selection */
#define  I2C_GFLTRCTRL_SDAAFW_0 ((uint16_t)0x0100U) /* Bit 0 */
#define  I2C_GFLTRCTRL_SDAAFW_1 ((uint16_t)0x0200U) /* Bit 1 */

#define  I2C_GFLTRCTRL_SDAAFENN ((uint16_t)0x0800U) /* SDA analog gfilter enable */

#define  I2C_GFLTRCTRL_SCLAFW   ((uint16_t)0x3000U) /* SCL analog gfilter width selection */
#define  I2C_GFLTRCTRL_SCLAFW_0 ((uint16_t)0x1000U) /* Bit 0 */
#define  I2C_GFLTRCTRL_SCLAFW_1 ((uint16_t)0x2000U) /* Bit 1 */

#define  I2C_GFLTRCTRL_SCLAFENN ((uint16_t)0x8000U) /* SCL analog gfilter enable */


/*** Universal Asynchronous Receiver Transmitter ***/

/** Bit definition for UART_CTRL1 register **/
#define UART_CTRL1_UEN      ((uint32_t)0x00000001U) /* UART Enable */
#define UART_CTRL1_RXEN     ((uint32_t)0x00000002U) /* Receiver Enable */
#define UART_CTRL1_TXEN     ((uint32_t)0x00000004U) /* Transmitter Enable */
#define UART_CTRL1_PSEL     ((uint32_t)0x00000008U) /* Parity Selection */
#define UART_CTRL1_PCEN     ((uint32_t)0x00000010U) /* Parity Control Enable */
#define UART_CTRL1_WL       ((uint32_t)0x00000020U) /* Word length */
#define UART_CTRL1_RCVWU    ((uint32_t)0x00000040U) /* Receiver wakeup */
#define UART_CTRL1_WUM      ((uint32_t)0x00000080U) /* Wakeup method */
#define UART_CTRL1_IDLEIEN  ((uint32_t)0x00000100U) /* IDLE Interrupt Enable */
#define UART_CTRL1_RXDNEIEN ((uint32_t)0x00000200U) /* RXNE Interrupt Enable */
#define UART_CTRL1_TXDEIEN  ((uint32_t)0x00000400U) /* TXE Interrupt Enable */
#define UART_CTRL1_TXCIEN   ((uint32_t)0x00000800U) /* Transmission Complete Interrupt Enable */
#define UART_CTRL1_PEIEN    ((uint32_t)0x00001000U) /* PE Interrupt Enable */
#define UART_CTRL1_SDBRK    ((uint32_t)0x00002000U) /* Send Break */

/** Bit definition for UART_CTRL2 register **/
#define UART_CTRL2_ADDR     ((uint32_t)0x0000000FU) /* Address of the UART node */
#define UART_CTRL2_STPB     ((uint32_t)0x00000060U) /* STOP[1:0] bits (STOP bits) */
#define UART_CTRL2_STPB_0   ((uint32_t)0x00000020U) /* Bit 0 */
#define UART_CTRL2_STPB_1   ((uint32_t)0x00000040U) /* Bit 1 */

#define UART_CTRL2_LINMEN   ((uint32_t)0x00001000U) /* LIN mode enable */
#define UART_CTRL2_LINBDIEN ((uint32_t)0x00002000U) /* LIN Break Detection Interrupt Enable */
#define UART_CTRL2_LINBDL   ((uint32_t)0x00004000U) /* LIN Break Detection Length */

/** Bit definition for UART_CTRL3 register **/
#define UART_CTRL3_HDMEN    ((uint32_t)0x00000008U) /* Half-Duplex Selection */
#define UART_CTRL3_DMATXEN  ((uint32_t)0x00000010U) /* DMA Enable Transmitter */
#define UART_CTRL3_DMARXEN  ((uint32_t)0x00000020U) /* DMA Enable Receiver */
#define UART_CTRL3_ERRIEN   ((uint32_t)0x00000040U) /* Error Interrupt Enable */
#define UART_CTRL3_IRDAMEN  ((uint32_t)0x00000080U) /* IrDA mode Enable */
#define UART_CTRL3_IRDALP   ((uint32_t)0x00000100U) /* IrDA Low-Power */

/** Bit definition for UART_STS register **/
#define UART_STS_IDLEF      ((uint32_t)0x00000040U) /* IDLE line detected */
#define UART_STS_TXDE       ((uint32_t)0x00000080U) /* Transmit Data Register Empty */
#define UART_STS_TXC        ((uint32_t)0x00000100U) /* Transmission Complete */
#define UART_STS_RXDNE      ((uint32_t)0x00000200U) /* Read Data Register Not Empty */
#define UART_STS_LINBDF     ((uint32_t)0x00000800U) /* LIN Break Detection Flag */
#define UART_STS_PEF        ((uint32_t)0x00001000U) /* Parity Error */
#define UART_STS_OREF       ((uint32_t)0x00002000U) /* OverRun Error */
#define UART_STS_NEF        ((uint32_t)0x00004000U) /* Noise Error Flag */
#define UART_STS_FEF        ((uint32_t)0x00008000U) /* Framing Error */

/** Bit definition for UART_DAT register **/
#define UART_DAT_DATV       ((uint32_t)0x000001FFU) /* Data value */

/** Bit definition for UART_BRCF register **/
#define UART_BRCF_DIVD      ((uint32_t)0x0000000FU) /* Decimal of UARTDIV */
#define UART_BRCF_DIVI      ((uint32_t)0x0000FFF0U) /* Integer of UARTDIV */

/** Bit definition for UART_GTP register **/
#define UART_GTP_PSCV       ((uint32_t)0x000000FFU) /* Prescaler value  */

/*** FLASH Registers ***/

/**  Bit definition for FLASH_AC register  **/
#define  FLASH_AC_LATENCY                   ((uint8_t)0x03U)               /* LATENCY[1:0] bits (Latency) */
#define  FLASH_AC_LATENCY_0                 ((uint8_t)0x00U)               /* Bit 0 = 0 */
#define  FLASH_AC_LATENCY_1                 ((uint8_t)0x01U)               /* Bit 0 = 1 */
#define  FLASH_AC_LATENCY_2                 ((uint8_t)0x02U)               /* Bit 1 = 1 */

#define  FLASH_AC_PRFTBFEN                  ((uint8_t)0x10U)               /* Prefetch Buffer Enable */
#define  FLASH_AC_PRFTBFSTS                 ((uint8_t)0x20U)               /* Prefetch Buffer Status */

/**  Bit definition for FLASH_KEY register  **/
#define  FLASH_KEY_FKEY                    ((uint32_t)0xFFFFFFFFU)        /* FLASH Key */

/**  Bit definition for FLASH_OPTKEY register  **/
#define  FLASH_OPTKEY_OPTKEY              ((uint32_t)0xFFFFFFFFU)         /* Option Byte Key */

/**  Bit definition for FLASH_STS register  **/
#define  FLASH_STS_BUSY                       ((uint16_t)0x0001U)               /* Busy */
#define  FLASH_STS_PGERR                      ((uint16_t)0x0004U)               /* Programming Error */
#define  FLASH_STS_WRPERR                     ((uint16_t)0x0010U)               /* Write Protection Error */
#define  FLASH_STS_EOP                        ((uint16_t)0x0020U)               /* End of operation */
#define  FLASH_STS_ECCERR                     ((uint16_t)0x0080U)               /* ECC Error */

/**  Bit definition for FLASH_CTRL register  **/
#define  FLASH_CTRL_PG                         ((uint16_t)0x0001U)            /* Programming */
#define  FLASH_CTRL_PER                        ((uint16_t)0x0002U)            /* Page Erase */
#define  FLASH_CTRL_MER                        ((uint16_t)0x0004U)            /* Mass Erase */
#define  FLASH_CTRL_OPTPG                      ((uint16_t)0x0010U)            /* Option Byte Programming */
#define  FLASH_CTRL_OPTER                      ((uint16_t)0x0020U)            /* Option Byte Erase */
#define  FLASH_CTRL_START                      ((uint16_t)0x0040U)            /* Start */
#define  FLASH_CTRL_LOCK                       ((uint16_t)0x0080U)            /* Lock */
#define  FLASH_CTRL_OPTWE                      ((uint16_t)0x0200U)            /* Option Bytes Write Enable */
#define  FLASH_CTRL_ERRITE                     ((uint16_t)0x0400U)            /* Error Interrupt Enable */
#define  FLASH_CTRL_EOPITE                     ((uint16_t)0x1000U)            /* End of operation interrupt enable */
#define  FLASH_CTRL_ECERRITE                   ((uint16_t)0x2000U)            /* ECC Error interrupt enable */

/**  Bit definition for FLASH_ADD register  **/
#define  FLASH_ADD_FADD                        ((uint32_t)0xFFFFFFFFU)        /* Flash Address */

/**  Bit definition for FLASH_OB register  **/
#define  FLASH_OB_OBERR                        ((uint16_t)0x0001U)            /* Option Byte Error */
#define  FLASH_OB_RDPRT1                       ((uint16_t)0x0002U)            /* Read protection */

#define  FLASH_OB_USER                         ((uint16_t)0x01FCU)            /* User Option Bytes */
#define  FLASH_OB_IWDG_SW                      ((uint16_t)0x0004U)            /* IWDG_SW */
#define  FLASH_OB_nRST_STOP                    ((uint16_t)0x0008U)            /* nRST_STOP */
#define  FLASH_OB_nRST_PD                      ((uint16_t)0x0010U)            /* nRST_STDBY */

#define  FLASH_OB_nBOOT0                       ((uint16_t)0x0020U)            /* nBOOT0 */
#define  FLASH_OB_nBOOT1                       ((uint16_t)0x0040U)            /* nBOOT1 */
#define  FLASH_OB_nSWBOOT0                     ((uint16_t)0x0080U)            /* nSWBOOT0 */

#define  FLASH_OB_BOOT0_CFG                    ((uint16_t)0x0100U)            /* BOOT0_CFG */

#define FLASH_OB_DATA0                          ((uint32_t)0x0003FC00U) /* Data0[7:0]  */
#define FLASH_OB_DATA0_0                        ((uint32_t)0x00000400U) /* bit 0 */ 
#define FLASH_OB_DATA0_1                        ((uint32_t)0x00000800U) /* bit 1 */
#define FLASH_OB_DATA0_2                        ((uint32_t)0x00001000U) /* bit 2 */
#define FLASH_OB_DATA0_3                        ((uint32_t)0x00002000U) /* bit 3 */
#define FLASH_OB_DATA0_4                        ((uint32_t)0x00004000U) /* bit 4 */
#define FLASH_OB_DATA0_5                        ((uint32_t)0x00008000U) /* bit 5 */
#define FLASH_OB_DATA0_6                        ((uint32_t)0x00010000U) /* bit 6 */
#define FLASH_OB_DATA0_7                        ((uint32_t)0x00020000U) /* bit 7 */

#define FLASH_OB_DATA1                          ((uint32_t)0x03FC0000U) /* Data1[7:0] */
#define FLASH_OB_DATA1_0                        ((uint32_t)0x00040000U) /* bit 0 */ 
#define FLASH_OB_DATA1_1                        ((uint32_t)0x00080000U) /* bit 1 */
#define FLASH_OB_DATA1_2                        ((uint32_t)0x00100000U) /* bit 2 */
#define FLASH_OB_DATA1_3                        ((uint32_t)0x00200000U) /* bit 3 */
#define FLASH_OB_DATA1_4                        ((uint32_t)0x00400000U) /* bit 4 */
#define FLASH_OB_DATA1_5                        ((uint32_t)0x00800000U) /* bit 5 */
#define FLASH_OB_DATA1_6                        ((uint32_t)0x01000000U) /* bit 6 */
#define FLASH_OB_DATA1_7                        ((uint32_t)0x02000000U) /* bit 7 */

#define  FLASH_OB_BOOT_SEL                      ((uint32_t)0x0C000000U)        /* boot pin select */
#define  FLASH_OB_RDPRT2                        ((uint32_t)0x80000000U)        /* Read protection level 2 */

/** Bit definition for FLASH_WRP register **/
#define FLASH_WRP_WRPT                          ((uint32_t)0xFFFFFFFFU) /* Write Protect */
#define FLASH_WRP_WRPT_0                        ((uint32_t)0x00000001U) /* bit 0  */
#define FLASH_WRP_WRPT_1                        ((uint32_t)0x00000002U) /* bit 1  */
#define FLASH_WRP_WRPT_2                        ((uint32_t)0x00000004U) /* bit 2  */
#define FLASH_WRP_WRPT_3                        ((uint32_t)0x00000008U) /* bit 3  */
#define FLASH_WRP_WRPT_4                        ((uint32_t)0x00000010U) /* bit 4  */
#define FLASH_WRP_WRPT_5                        ((uint32_t)0x00000020U) /* bit 5  */
#define FLASH_WRP_WRPT_6                        ((uint32_t)0x00000040U) /* bit 6  */
#define FLASH_WRP_WRPT_7                        ((uint32_t)0x00000080U) /* bit 7  */
#define FLASH_WRP_WRPT_8                        ((uint32_t)0x00000100U) /* bit 8  */
#define FLASH_WRP_WRPT_9                        ((uint32_t)0x00000200U) /* bit 9  */
#define FLASH_WRP_WRPT_10                       ((uint32_t)0x00000400U) /* bit 10 */
#define FLASH_WRP_WRPT_11                       ((uint32_t)0x00000800U) /* bit 11 */
#define FLASH_WRP_WRPT_12                       ((uint32_t)0x00001000U) /* bit 12 */
#define FLASH_WRP_WRPT_13                       ((uint32_t)0x00002000U) /* bit 13 */
#define FLASH_WRP_WRPT_14                       ((uint32_t)0x00004000U) /* bit 14 */
#define FLASH_WRP_WRPT_15                       ((uint32_t)0x00008000U) /* bit 15 */
#define FLASH_WRP_WRPT_16                       ((uint32_t)0x00010000U) /* bit 16 */
#define FLASH_WRP_WRPT_17                       ((uint32_t)0x00020000U) /* bit 17 */
#define FLASH_WRP_WRPT_18                       ((uint32_t)0x00040000U) /* bit 18 */
#define FLASH_WRP_WRPT_19                       ((uint32_t)0x00080000U) /* bit 19 */
#define FLASH_WRP_WRPT_20                       ((uint32_t)0x00100000U) /* bit 20 */
#define FLASH_WRP_WRPT_21                       ((uint32_t)0x00200000U) /* bit 21 */
#define FLASH_WRP_WRPT_22                       ((uint32_t)0x00400000U) /* bit 22 */
#define FLASH_WRP_WRPT_23                       ((uint32_t)0x00800000U) /* bit 23 */
#define FLASH_WRP_WRPT_24                       ((uint32_t)0x01000000U) /* bit 24 */
#define FLASH_WRP_WRPT_25                       ((uint32_t)0x02000000U) /* bit 25 */
#define FLASH_WRP_WRPT_26                       ((uint32_t)0x04000000U) /* bit 26 */
#define FLASH_WRP_WRPT_27                       ((uint32_t)0x08000000U) /* bit 27 */
#define FLASH_WRP_WRPT_28                       ((uint32_t)0x10000000U) /* bit 28 */
#define FLASH_WRP_WRPT_29                       ((uint32_t)0x20000000U) /* bit 29 */
#define FLASH_WRP_WRPT_30                       ((uint32_t)0x40000000U) /* bit 30 */
#define FLASH_WRP_WRPT_31                       ((uint32_t)0x80000000U) /* bit 31 */

/** Bit definition for FLASH_ECC register **/
#define FLASH_WRP_ECCLW                      ((uint32_t)0x000000FFU)        /* ecc result of low word data[31:0] in flash */

/**  Bit definition for FLASH_USER register  **/
#define  FLASH_USER_LVRLS                   ((uint32_t)0x0000000FU)       /* LVR gear selection */
#define  FLASH_USER_LVREN                   ((uint32_t)0x00000010U)       /* LVR enable */
#define  FLASH_USER_LVRRST                  ((uint32_t)0x00000020U)       /* LVR reset enable control */
#define  FLASH_USER_LVRFILEN                ((uint32_t)0x00000040U)       /* LVR filter enable */
#define  FLASH_USER_LVRCNT                  ((uint32_t)0x0000FF00U)       /* LVR filter control count value */
#define  FLASH_USER_POR_DELAY               ((uint32_t)0x00FF0000U)       /* Delay time of CPU reset after POR is triggered */

/**  Bit definition for FLASH_START_ADD register  **/
#define  FLASH_START_ADD_MASK               ((uint32_t)0x000000FFU)       /* FLASH boot address mask */

/**  Bit definition for FLASH_VTOR register  **/
#define  FLASH_VTOR_EN                      ((uint32_t)0x80000000U)       /* VTOR enalbe */
#define  FLASH_VTOR_VALUE                   ((uint32_t)0x7FFFFFFFU)       /* VTOR address value */


/*** Option Bytes register ***/

/**  Bit definition for FLASH_RDP register  **/
#define  FLASH_RDP_RDP1                      ((uint32_t)0x000000FFU)        /* Read protection option byte */
#define  FLASH_RDP_nRDP1                     ((uint32_t)0x0000FF00U)        /* Read protection complemented option byte */

/**  Bit definition for FLASH_USER1 register  **/
#define  FLASH_USER_USER1                    ((uint32_t)0x000000FFU)        /* User option byte */
#define  FLASH_USER_nUSER1                   ((uint32_t)0x0000FF00U)        /* User complemented option byte */

/**  Bit definition for FLASH_USER2 register  **/
#define  FLASH_USER_USER2                    ((uint32_t)0x000000FFU)        /* User option byte */
#define  FLASH_USER_nUSER2                   ((uint32_t)0x0000FF00U)        /* User complemented option byte */

/**  Bit definition for FLASH_USER3 register  **/
#define  FLASH_USER_USER3                    ((uint32_t)0x000000FFU)        /* User option byte */
#define  FLASH_USER_nUSER3                   ((uint32_t)0x0000FF00U)        /* User complemented option byte */

/**  Bit definition for FLASH_USER4 register  **/
#define  FLASH_USER_USER4                    ((uint32_t)0x000000FFU)        /* User option byte */
#define  FLASH_USER_nUSER4                   ((uint32_t)0x0000FF00U)        /* User complemented option byte */

/**  Bit definition for FLASH_USER5 register  **/
#define  FLASH_USER_USER5                    ((uint32_t)0x000000FFU)        /* User option byte */
#define  FLASH_USER_nUSER5                   ((uint32_t)0x0000FF00U)        /* User complemented option byte */

/**  Bit definition for FLASH_USER6 register  **/
#define  FLASH_USER_USER6                    ((uint32_t)0x000000FFU)        /* User option byte */
#define  FLASH_USER_nUSER6                   ((uint32_t)0x0000FF00U)        /* User complemented option byte */

/**  Bit definition for FLASH_Data0 register  **/
#define  FLASH_Data0_Data0                   ((uint32_t)0x000000FFU)        /* User data storage option byte */
#define  FLASH_Data0_nData0                  ((uint32_t)0x0000FF00U)        /* User data storage complemented option byte */

/**  Bit definition for FLASH_Data1 register  **/
#define  FLASH_Data1_Data1                   ((uint32_t)0x000000FFU)        /* User data storage option byte */
#define  FLASH_Data1_nData1                  ((uint32_t)0x0000FF00U)        /* User data storage complemented option byte */

/**  Bit definition for OptionByte WRP0  **/
#define FLASH_WRP0_WRP0                      ((uint32_t)0x000000FFU)        /* Flash memory write protection option bytes */
#define FLASH_WRP0_NWRP0                     ((uint32_t)0x0000FF00U)        /* Flash memory write protection complemented option bytes */

/**  Bit definition for OptionByte WRP1  **/
#define FLASH_WRP1_WRP1                      ((uint32_t)0x000000FFU)        /* Flash memory write protection option bytes */
#define FLASH_WRP1_NWRP1                     ((uint32_t)0x0000FF00U)        /* Flash memory write protection complemented option bytes */

/**  Bit definition for OptionByte WRP2  **/
#define FLASH_WRP2_WRP2                      ((uint32_t)0x000000FFU)        /* Flash memory write protection option bytes */
#define FLASH_WRP2_NWRP2                     ((uint32_t)0x0000FF00U)        /* Flash memory write protection complemented option bytes */

/**  Bit definition for OptionByte WRP3  **/
#define FLASH_WRP3_WRP3                      ((uint32_t)0x000000FFU)        /* Flash memory write protection option bytes */
#define FLASH_WRP3_NWRP3                     ((uint32_t)0x0000FF00U)        /* Flash memory write protection complemented option bytes */

/**  Bit definition for FLASH_RDP2 register  **/
#define  FLASH_RDP_RDP2                      ((uint32_t)0x000000FFU)        /* Read protection level 2 option byte */
#define  FLASH_RDP_nRDP2                     ((uint32_t)0x0000FF00U)        /* Read protection level 2 complemented option byte */


/** Bit Offset register **/
#define REG_BIT1_OFFSET    ((uint32_t)0x00000001U)
#define REG_BIT2_OFFSET    ((uint32_t)0x00000002U)
#define REG_BIT3_OFFSET    ((uint32_t)0x00000003U)
#define REG_BIT4_OFFSET    ((uint32_t)0x00000004U)
#define REG_BIT5_OFFSET    ((uint32_t)0x00000005U)
#define REG_BIT6_OFFSET    ((uint32_t)0x00000006U)
#define REG_BIT7_OFFSET    ((uint32_t)0x00000007U)
#define REG_BIT8_OFFSET    ((uint32_t)0x00000008U)
#define REG_BIT9_OFFSET    ((uint32_t)0x00000009U)
#define REG_BIT10_OFFSET   ((uint32_t)0x0000000AU)
#define REG_BIT11_OFFSET   ((uint32_t)0x0000000BU)
#define REG_BIT12_OFFSET   ((uint32_t)0x0000000CU)
#define REG_BIT13_OFFSET   ((uint32_t)0x0000000DU)
#define REG_BIT14_OFFSET   ((uint32_t)0x0000000EU)
#define REG_BIT15_OFFSET   ((uint32_t)0x0000000FU)
#define REG_BIT16_OFFSET   ((uint32_t)0x00000010U)
#define REG_BIT17_OFFSET   ((uint32_t)0x00000011U)
#define REG_BIT18_OFFSET   ((uint32_t)0x00000012U)
#define REG_BIT19_OFFSET   ((uint32_t)0x00000013U)
#define REG_BIT20_OFFSET   ((uint32_t)0x00000014U)
#define REG_BIT21_OFFSET   ((uint32_t)0x00000015U)
#define REG_BIT22_OFFSET   ((uint32_t)0x00000016U)
#define REG_BIT23_OFFSET   ((uint32_t)0x00000017U)
#define REG_BIT24_OFFSET   ((uint32_t)0x00000018U)
#define REG_BIT25_OFFSET   ((uint32_t)0x00000019U)
#define REG_BIT26_OFFSET   ((uint32_t)0x0000001AU)
#define REG_BIT27_OFFSET   ((uint32_t)0x0000001BU)
#define REG_BIT28_OFFSET   ((uint32_t)0x0000001CU)
#define REG_BIT29_OFFSET   ((uint32_t)0x0000001DU)
#define REG_BIT30_OFFSET   ((uint32_t)0x0000001EU)
#define REG_BIT31_OFFSET   ((uint32_t)0x0000001FU)
#define REG_BIT32_OFFSET   ((uint32_t)0x00000020U)


/*** Exported_macro ***/

#define SET_BIT(REG, BIT)     ((REG) |= (BIT))

#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))

#define READ_BIT(REG, BIT)    ((REG) & (BIT))

#define CLEAR_REG(REG)        ((REG) = (0x0))

#define WRITE_REG(REG, VAL)   ((REG) = (VAL))

#define READ_REG(REG)         ((REG))

#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))


#ifdef __cplusplus
}
#endif

#endif /* __n32A052_H */




