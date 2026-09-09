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
*\*\file n32a052_gpio.h
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/

#ifndef __N32A052_GPIO_H__
#define __N32A052_GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32a052.h"


/** GPIO Init Structure Definition **/
typedef struct
{
    uint32_t         Pin;            /* Specifies the GPIO pins to be configured. */

    uint32_t         GPIO_Mode;      /* Specifies the operating mode for the selected pins. */

    uint32_t         GPIO_Pull;      /* Specifies the Pull-up or Pull-Down activation for the selected pins. */

    uint32_t         GPIO_Slew_Rate; /* Specify the reverse speed for the selected pins. */

    uint32_t         GPIO_Current;   /* Driving drive capability of the select pins. */

    uint32_t         GPIO_Alternate; /* Peripheral to be connected to the selected pins. */ 
}GPIO_InitType;

/** Bit_SET and Bit_RESET enumeration **/
typedef enum
{
    Bit_RESET = 0,
    Bit_SET
}Bit_OperateType;


#define GPIO_AF_MODE                    ((uint32_t)GPIO_PMODE0_2)
#define GPIO_PU_MODE                    ((uint32_t)GPIO_PUPD0_1)
#define GPIO_PD_MODE                    ((uint32_t)GPIO_PUPD0_2)

#define GPIO_GET_INDEX(PERIPH)          (((PERIPH) == (GPIOA))? 0 :\
                                         ((PERIPH) == (GPIOB))? 1 :\
                                         ((PERIPH) == (GPIOC))? 2 :3)

#define GPIO_GET_PERIPH(INDEX)          (((INDEX)==((uint8_t)0x00))? GPIOA :\
                                         ((INDEX)==((uint8_t)0x01))? GPIOB :\
                                         ((INDEX)==((uint8_t)0x02))? GPIOC : GPIOD )

/** GPIO_pins_define **/
#define GPIO_PIN_0           ((uint16_t)0x0001U) /* Pin 0 selected    */
#define GPIO_PIN_1           ((uint16_t)0x0002U) /* Pin 1 selected    */
#define GPIO_PIN_2           ((uint16_t)0x0004U) /* Pin 2 selected    */
#define GPIO_PIN_3           ((uint16_t)0x0008U) /* Pin 3 selected    */
#define GPIO_PIN_4           ((uint16_t)0x0010U) /* Pin 4 selected    */
#define GPIO_PIN_5           ((uint16_t)0x0020U) /* Pin 5 selected    */
#define GPIO_PIN_6           ((uint16_t)0x0040U) /* Pin 6 selected    */
#define GPIO_PIN_7           ((uint16_t)0x0080U) /* Pin 7 selected    */
#define GPIO_PIN_8           ((uint16_t)0x0100U) /* Pin 8 selected    */
#define GPIO_PIN_9           ((uint16_t)0x0200U) /* Pin 9 selected    */
#define GPIO_PIN_10          ((uint16_t)0x0400U) /* Pin 10 selected   */
#define GPIO_PIN_11          ((uint16_t)0x0800U) /* Pin 11 selected   */
#define GPIO_PIN_12          ((uint16_t)0x1000U) /* Pin 12 selected   */
#define GPIO_PIN_13          ((uint16_t)0x2000U) /* Pin 13 selected   */
#define GPIO_PIN_14          ((uint16_t)0x4000U) /* Pin 14 selected   */
#define GPIO_PIN_15          ((uint16_t)0x8000U) /* Pin 15 selected   */
#define GPIO_PIN_ALL         ((uint16_t)0xFFFFU) /* All pins selected */

#define GPIOA_PIN_AVAILABLE  GPIO_PIN_ALL
#define GPIOB_PIN_AVAILABLE  GPIO_PIN_ALL
#define GPIOC_PIN_AVAILABLE  GPIO_PIN_ALL
#define GPIOD_PIN_AVAILABLE  (GPIO_PIN_0 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 |\
                              GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15)


/** GPIO_mode_define **/
#define GPIO_MODE_INPUT         ((uint32_t)0x00000000U)  /* Input Floating Mode */
#define GPIO_MODE_OUTPUT_PP     ((uint32_t)0x00000001U)  /* Output Push Pull Mode */
#define GPIO_MODE_OUTPUT_OD     ((uint32_t)0x00000011U)  /* Output Open Drain Mode */
#define GPIO_MODE_AF_PP         ((uint32_t)0x00000002U)  /* Alternate Function Push Pull Mode  */
#define GPIO_MODE_AF_OD         ((uint32_t)0x00000012U)  /* Alternate Function Open Drain Mode */
#define GPIO_MODE_ANALOG        ((uint32_t)0x00000003U)  /* Analog Mode */

/** GPIO Pull-Up or Pull-Down Activation **/
#define GPIO_NO_PULL         ((uint32_t)GPIO_PUPD0_0) /* No Pull-up or Pull-down activation */
#define GPIO_PULL_UP         ((uint32_t)GPIO_PUPD0_1) /* Pull-up activation */
#define GPIO_PULL_DOWN       ((uint32_t)GPIO_PUPD0_2) /* Pull-down activation */

/** slew rate config **/
#define GPIO_SLEW_RATE_FAST  ((uint32_t)0x00000000U)
#define GPIO_SLEW_RATE_SLOW  ((uint32_t)0x00000001U)

/** driver strength config **/
#define GPIO_HIGH_DREIVE     ((uint32_t)0x00000000U)
#define GPIO_LOW_DREIVE      ((uint32_t)0x00000001U)



/** GPIO Port Sources **/
#define GPIOA_PORT_SOURCE    ((uint8_t)0x00)
#define GPIOB_PORT_SOURCE    ((uint8_t)0x01)
#define GPIOC_PORT_SOURCE    ((uint8_t)0x02)
#define GPIOD_PORT_SOURCE    ((uint8_t)0x03)

/** GPIO Pin Sources **/
#define GPIO_PIN_SOURCE0     ((uint8_t)0x00)
#define GPIO_PIN_SOURCE1     ((uint8_t)0x01)
#define GPIO_PIN_SOURCE2     ((uint8_t)0x02)
#define GPIO_PIN_SOURCE3     ((uint8_t)0x03)
#define GPIO_PIN_SOURCE4     ((uint8_t)0x04)
#define GPIO_PIN_SOURCE5     ((uint8_t)0x05)
#define GPIO_PIN_SOURCE6     ((uint8_t)0x06)
#define GPIO_PIN_SOURCE7     ((uint8_t)0x07)
#define GPIO_PIN_SOURCE8     ((uint8_t)0x08)
#define GPIO_PIN_SOURCE9     ((uint8_t)0x09)
#define GPIO_PIN_SOURCE10    ((uint8_t)0x0A)
#define GPIO_PIN_SOURCE11    ((uint8_t)0x0B)
#define GPIO_PIN_SOURCE12    ((uint8_t)0x0C)
#define GPIO_PIN_SOURCE13    ((uint8_t)0x0D)
#define GPIO_PIN_SOURCE14    ((uint8_t)0x0E)
#define GPIO_PIN_SOURCE15    ((uint8_t)0x0F)

typedef enum
{
    AFIO_ADC_TRIG_EXTI_0 = 0x00U,
    AFIO_ADC_TRIG_EXTI_1 = 0x01U,
    AFIO_ADC_TRIG_EXTI_2,
    AFIO_ADC_TRIG_EXTI_3,
    AFIO_ADC_TRIG_EXTI_4,
    AFIO_ADC_TRIG_EXTI_5,
    AFIO_ADC_TRIG_EXTI_6,
    AFIO_ADC_TRIG_EXTI_7,
    AFIO_ADC_TRIG_EXTI_8,
    AFIO_ADC_TRIG_EXTI_9,
    AFIO_ADC_TRIG_EXTI_10,
    AFIO_ADC_TRIG_EXTI_11,
    AFIO_ADC_TRIG_EXTI_12,
    AFIO_ADC_TRIG_EXTI_13,
    AFIO_ADC_TRIG_EXTI_14,
    AFIO_ADC_TRIG_EXTI_15,
}AFIO_ADC_Trig_RemapType;

/** EXTI line sources **/
#define EXTI_LINE_SOURCE0    ((uint8_t)0x00) /* EXTI_line_0  */
#define EXTI_LINE_SOURCE1    ((uint8_t)0x01) /* EXTI_line_1  */
#define EXTI_LINE_SOURCE2    ((uint8_t)0x02) /* EXTI_line_2  */
#define EXTI_LINE_SOURCE3    ((uint8_t)0x03) /* EXTI_line_3  */
#define EXTI_LINE_SOURCE4    ((uint8_t)0x04) /* EXTI_line_4  */
#define EXTI_LINE_SOURCE5    ((uint8_t)0x05) /* EXTI_line_5  */
#define EXTI_LINE_SOURCE6    ((uint8_t)0x06) /* EXTI_line_6  */
#define EXTI_LINE_SOURCE7    ((uint8_t)0x07) /* EXTI_line_7  */
#define EXTI_LINE_SOURCE8    ((uint8_t)0x08) /* EXTI_line_8  */
#define EXTI_LINE_SOURCE9    ((uint8_t)0x09) /* EXTI_line_9  */
#define EXTI_LINE_SOURCE10   ((uint8_t)0x0A) /* EXTI_line_10 */
#define EXTI_LINE_SOURCE11   ((uint8_t)0x0B) /* EXTI_line_11 */
#define EXTI_LINE_SOURCE12   ((uint8_t)0x0C) /* EXTI_line_12 */
#define EXTI_LINE_SOURCE13   ((uint8_t)0x0D) /* EXTI_line_13 */
#define EXTI_LINE_SOURCE14   ((uint8_t)0x0E) /* EXTI_line_14 */
#define EXTI_LINE_SOURCE15   ((uint8_t)0x0F) /* EXTI_line_15 */

/** GPIOx_Alternate_function_selection Alternate function selection **/

/** Alternate function AF0 **/
#define ALTERNATE_FUN_0      ((uint8_t)0x00U)
#define GPIO_AF0_SWDIO       (ALTERNATE_FUN_0) /* SWDIO Alternate Function mapping    */
#define GPIO_AF0_SWCLK       (ALTERNATE_FUN_0) /* SWCLK Alternate Function mapping    */
#define GPIO_AF0_TIM3        (ALTERNATE_FUN_0) /* TIM3 Alternate Function mapping     */
#define GPIO_AF0_SPI1        (ALTERNATE_FUN_0) /* SPI1 Alternate Function mapping     */
#define GPIO_AF0_SPI2        (ALTERNATE_FUN_0) /* SPI2 Alternate Function mapping     */
#define GPIO_AF0_SPI3        (ALTERNATE_FUN_0) /* SPI3 Alternate Function mapping     */
#define GPIO_AF0_I2C2        (ALTERNATE_FUN_0) /* I2C2 Alternate Function mapping     */

/** Alternate function AF1 **/
#define ALTERNATE_FUN_1      ((uint8_t)0x01U)
#define GPIO_AF1_TIM1        (ALTERNATE_FUN_1) /* TIM1 Alternate Function mapping     */
#define GPIO_AF1_TIM2        (ALTERNATE_FUN_1) /* TIM2 Alternate Function mapping     */
#define GPIO_AF1_TIM3        (ALTERNATE_FUN_1) /* TIM3 Alternate Function mapping     */
#define GPIO_AF1_TIM4        (ALTERNATE_FUN_1) /* TIM4 Alternate Function mapping     */
#define GPIO_AF1_TIM5        (ALTERNATE_FUN_1) /* TIM5 Alternate Function mapping     */
#define GPIO_AF1_I2C1        (ALTERNATE_FUN_1) /* I2C1 Alternate Function mapping     */
#define GPIO_AF1_SPI1        (ALTERNATE_FUN_1) /* SPI1 Alternate Function mapping     */
#define GPIO_AF1_SPI2        (ALTERNATE_FUN_1) /* SPI2 Alternate Function mapping     */

/** Alternate function AF2 **/
#define ALTERNATE_FUN_2      ((uint8_t)0x02U)
#define GPIO_AF2_UART1       (ALTERNATE_FUN_2) /* UART1 Alternate Function mapping    */
#define GPIO_AF2_UART2       (ALTERNATE_FUN_2) /* UART2 Alternate Function mapping    */
#define GPIO_AF2_TIM1        (ALTERNATE_FUN_2) /* TIM1 Alternate Function mapping     */
#define GPIO_AF2_TIM2        (ALTERNATE_FUN_2) /* TIM2 Alternate Function mapping     */
#define GPIO_AF2_TIM3        (ALTERNATE_FUN_2) /* TIM3 Alternate Function mapping     */
#define GPIO_AF2_TIM4        (ALTERNATE_FUN_2) /* TIM4 Alternate Function mapping     */
#define GPIO_AF2_TIM5        (ALTERNATE_FUN_2) /* TIM5 Alternate Function mapping     */
#define GPIO_AF2_I2C2        (ALTERNATE_FUN_2) /* I2C2 Alternate Function mapping     */

/** Alternate function AF3 **/
#define ALTERNATE_FUN_3      ((uint8_t)0x03U)
#define GPIO_AF3_EVENTOUT    (ALTERNATE_FUN_3) /* EVENTOUT Alternate Function mapping */
#define GPIO_AF3_TIM1        (ALTERNATE_FUN_3) /* TIM1 Alternate Function mapping     */
#define GPIO_AF3_TIM4        (ALTERNATE_FUN_3) /* TIM4 Alternate Function mapping     */
#define GPIO_AF3_TIM5        (ALTERNATE_FUN_3) /* TIM5 Alternate Function mapping     */
#define GPIO_AF3_SPI3        (ALTERNATE_FUN_3) /* SPI3 Alternate Function mapping     */
#define GPIO_AF3_I2C2        (ALTERNATE_FUN_3) /* I2C2 Alternate Function mapping     */
#define GPIO_AF3_RTC         (ALTERNATE_FUN_3) /* RTC  Alternate Function mapping     */
#define GPIO_AF3_UART2       (ALTERNATE_FUN_3) /* UART2 Alternate Function mapping    */

/** Alternate function AF4 **/
#define ALTERNATE_FUN_4      ((uint8_t)0x04U)
#define GPIO_AF4_TIM1        (ALTERNATE_FUN_4) /* TIM1 Alternate Function mapping     */
#define GPIO_AF4_TIM2        (ALTERNATE_FUN_4) /* TIM2 Alternate Function mapping     */
#define GPIO_AF4_TIM3        (ALTERNATE_FUN_4) /* TIM3 Alternate Function mapping     */
#define GPIO_AF4_TIM4        (ALTERNATE_FUN_4) /* TIM4 Alternate Function mapping     */
#define GPIO_AF4_TIM5        (ALTERNATE_FUN_4) /* TIM5 Alternate Function mapping     */
#define GPIO_AF4_SPI2        (ALTERNATE_FUN_4) /* SPI2 Alternate Function mapping     */
#define GPIO_AF4_SPI3        (ALTERNATE_FUN_4) /* SPI3 Alternate Function mapping     */
#define GPIO_AF4_UART1       (ALTERNATE_FUN_4) /* UART1 Alternate Function mapping    */
#define GPIO_AF4_UART2       (ALTERNATE_FUN_4) /* UART2 Alternate Function mapping    */
#define GPIO_AF4_UART3       (ALTERNATE_FUN_4) /* UART3 Alternate Function mapping    */
#define GPIO_AF4_UART4       (ALTERNATE_FUN_4) /* UART4 Alternate Function mapping    */
#define GPIO_AF4_UART5       (ALTERNATE_FUN_4) /* UART5 Alternate Function mapping    */
#define GPIO_AF4_I2C2        (ALTERNATE_FUN_4) /* I2C2 Alternate Function mapping     */
#define GPIO_AF4_CAN         (ALTERNATE_FUN_4) /* CAN  Alternate Function mapping     */
#define GPIO_AF4_COMP4       (ALTERNATE_FUN_4) /* COMP4 Alternate Function mapping    */
#define GPIO_AF4_RTC         (ALTERNATE_FUN_4) /* RTC Alternate Function mapping      */
#define GPIO_AF4_EVENTOUT    (ALTERNATE_FUN_4) /* EVENTOUT Alternate Function mapping */

/** Alternate function AF5 **/
#define ALTERNATE_FUN_5      ((uint8_t)0x05U)
#define GPIO_AF5_UART1       (ALTERNATE_FUN_5) /* UART1 Alternate Function mapping    */
#define GPIO_AF5_UART3       (ALTERNATE_FUN_5) /* UART3 Alternate Function mapping    */
#define GPIO_AF5_UART4       (ALTERNATE_FUN_5) /* UART4 Alternate Function mapping    */
#define GPIO_AF5_UART5       (ALTERNATE_FUN_5) /* UART5 Alternate Function mapping    */
#define GPIO_AF5_TIM1        (ALTERNATE_FUN_5) /* TIM1 Alternate Function mapping     */
#define GPIO_AF5_TIM5        (ALTERNATE_FUN_5) /* TIM5 Alternate Function mapping     */
#define GPIO_AF5_SPI1        (ALTERNATE_FUN_5) /* SPI1 Alternate Function mapping     */
#define GPIO_AF5_SPI2        (ALTERNATE_FUN_5) /* SPI2 Alternate Function mapping     */
#define GPIO_AF5_SPI3        (ALTERNATE_FUN_5) /* SPI3 Alternate Function mapping     */
#define GPIO_AF5_COMP1       (ALTERNATE_FUN_5) /* COMP1 Alternate Function mapping    */
#define GPIO_AF5_COMP3       (ALTERNATE_FUN_5) /* COMP3 Alternate Function mapping    */
#define GPIO_AF5_COMP4       (ALTERNATE_FUN_5) /* COMP4 Alternate Function mapping    */
#define GPIO_AF5_I2C2        (ALTERNATE_FUN_5) /* I2C2  Alternate Function mapping    */
#define GPIO_AF5_LED         (ALTERNATE_FUN_5) /* LED  Alternate Function mapping     */


/** Alternate function AF6 **/
#define ALTERNATE_FUN_6      ((uint8_t)0x06U)
#define GPIO_AF6_I2C1        (ALTERNATE_FUN_6) /* I2C1 Alternate Function mapping     */
#define GPIO_AF6_I2C2        (ALTERNATE_FUN_6) /* I2C2 Alternate Function mapping     */
#define GPIO_AF6_UART2       (ALTERNATE_FUN_6) /* UART2 Alternate Function mapping    */
#define GPIO_AF6_UART3       (ALTERNATE_FUN_6) /* UART3 Alternate Function mapping    */
#define GPIO_AF6_UART5       (ALTERNATE_FUN_6) /* UART5 Alternate Function mapping    */
#define GPIO_AF6_MCO         (ALTERNATE_FUN_6) /* MCO Alternate Function mapping      */
#define GPIO_AF6_SPI3        (ALTERNATE_FUN_6) /* SPI3  Alternate Function mapping    */
#define GPIO_AF6_COMP2       (ALTERNATE_FUN_6) /* COMP2 Alternate Function mapping    */
#define GPIO_AF6_BEEPER      (ALTERNATE_FUN_6) /* BEEPER Alternate Function mapping   */

/** Alternate function AF7 **/
#define ALTERNATE_FUN_7      ((uint8_t)0x07U)
#define GPIO_AF7_BEEPER      (ALTERNATE_FUN_7) /* BEEPER Alternate Function mapping   */
#define GPIO_AF7_I2C1        (ALTERNATE_FUN_7) /* I2C1 Alternate Function mapping     */
#define GPIO_AF7_I2C2        (ALTERNATE_FUN_7) /* I2C2 Alternate Function mapping     */
#define GPIO_AF7_UART4       (ALTERNATE_FUN_7) /* UART4 Alternate Function mapping    */
#define GPIO_AF7_RTC         (ALTERNATE_FUN_7) /* RTC  Alternate Function mapping     */
#define GPIO_AF7_CAN         (ALTERNATE_FUN_7) /* CAN  Alternate Function mapping     */
#define GPIO_AF7_TIM1        (ALTERNATE_FUN_7) /* TIM1 Alternate Function mapping     */
#define GPIO_AF7_LCD         (ALTERNATE_FUN_7) /* LCD Alternate Function mapping      */


/** Alternate function AF8 **/
#define ALTERNATE_FUN_8      ((uint8_t)0x08U)
#define GPIO_AF8_SPI3        (ALTERNATE_FUN_8) /* SPI3 Alternate Function mapping     */
#define GPIO_AF8_I2C1        (ALTERNATE_FUN_8) /* I2C1 Alternate Function mapping     */
#define GPIO_AF8_UART4       (ALTERNATE_FUN_8) /* UART4 Alternate Function mapping    */
#define GPIO_AF8_UART5       (ALTERNATE_FUN_8) /* UART5 Alternate Function mapping    */
#define GPIO_AF8_CAN         (ALTERNATE_FUN_8) /* CAN   Alternate Function mapping    */
#define GPIO_AF8_COMP1       (ALTERNATE_FUN_8) /* COMP1 Alternate Function mapping    */
#define GPIO_AF8_LCD         (ALTERNATE_FUN_8) /* LCD Alternate Function mapping      */


/** Alternate function AF9 **/
#define ALTERNATE_FUN_9      ((uint8_t)0x09U)
#define GPIO_AF9_COMP2       (ALTERNATE_FUN_9) /* COMP2 Alternate Function mapping    */
#define GPIO_AF9_COMP3       (ALTERNATE_FUN_9) /* COMP3 Alternate Function mapping    */
#define GPIO_AF9_LCD         (ALTERNATE_FUN_9) /* LCD Alternate Function mapping      */

/** Alternate function AF10 **/
#define ALTERNATE_FUN_10     ((uint8_t)0x0AU)
#define GPIO_AF10_LCD        (ALTERNATE_FUN_10) /* LCD Alternate Function mapping      */

/** Alternate function AF15 **/
#define ALTERNATE_FUN_15     ((uint8_t)0x0FU)  /* NON Alternate Function mapping      */

#define GPIO_NO_AF           (ALTERNATE_FUN_15)

/** SPI mode definition in AFIO register  **/
#define AFIO_SPI1_NSS        ((uint32_t)AFIO_RMP_CFG_SPI1_NSS)
#define AFIO_SPI2_NSS        ((uint32_t)AFIO_RMP_CFG_SPI2_NSS)
#define AFIO_SPI3_NSS        ((uint32_t)AFIO_RMP_CFG_SPI3_NSS)

#define AFIO_SPI_NSS_HIGH_IMPEDANCE  (0x0UL)
#define AFIO_SPI_NSS_High_LEVEL      (0x1UL)

/** TIM3_CH2 internal remap definition in AFIO register  **/
#define AFIO_TIM3CH2_MAP     ((uint32_t)AFIO_RMP_CFG_TIM3CH2)

#define TIM3CH2_TO_PORT      (0x0UL)
#define TIM3CH2_TO_LSI       (0x1UL)

/** GPIO_Exported_Functions **/
void GPIO_DeInit(GPIO_Module* GPIOx);
void GPIO_DeInitPin(GPIO_Module* GPIOx, uint32_t Pin);
void GPIO_AFIOInitDefault(void);

void GPIO_InitPeripheral(GPIO_Module* GPIOx, GPIO_InitType * GPIO_InitStruct);
void GPIO_InitStruct(GPIO_InitType* GPIO_InitStructer);

uint8_t GPIO_ReadInputDataBit(GPIO_Module* GPIOx, uint16_t Pin);
uint16_t GPIO_ReadInputData(GPIO_Module* GPIOx);
uint8_t GPIO_ReadOutputDataBit(GPIO_Module* GPIOx, uint16_t Pin);
uint16_t GPIO_ReadOutputData(GPIO_Module* GPIOx);

void GPIO_SetBits(GPIO_Module* GPIOx, uint16_t Pin);
void GPIO_ResetBits(GPIO_Module* GPIOx, uint16_t Pin);
void GPIO_WriteBit(GPIO_Module* GPIOx, uint16_t Pin, Bit_OperateType BitCmd);
void GPIO_Write(GPIO_Module* GPIOx, uint16_t data_value);
void GPIO_TogglePin(GPIO_Module *GPIOx, uint16_t Pin);

void GPIO_ConfigPinLock(GPIO_Module* GPIOx, uint16_t Pin);
void GPIO_ConfigEXTILine(uint8_t PortSource, uint8_t PinSource);
void GPIO_ClearEXTILine( uint8_t PinSource);
void GPIO_ConfigPinRemap(uint8_t PortSource, uint8_t PinSource, uint32_t AlternateFunction);

void AFIO_ConfigADCExternalTrigRemap(AFIO_ADC_Trig_RemapType ADC_trigger);
void AFIO_ConfigSPINSSMode(uint32_t AFIO_SPIx_NSS, uint32_t SpiNssMode);
void AFIO_ConfigIOFlitNum(uint8_t Flit_Num);
void AFIO_DIGEFTEnable(uint8_t PortSource, uint16_t Pin, FunctionalState Cmd);

#ifdef __cplusplus
}
#endif

#endif /* __N32A052_GPIO_H__ */

