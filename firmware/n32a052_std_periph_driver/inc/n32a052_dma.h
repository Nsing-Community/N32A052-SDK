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
*\*\file n32a052_dma.h
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/
 
#ifndef __N32A052_DMA_H__
#define __N32A052_DMA_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32a052.h"

/*** DMA Structure Definition Start ***/

/** DMA Init structure definition **/
typedef struct
{
    uint32_t PeriphAddr;     /* Specifies the peripheral base address for DMAy Channelx. */

    uint32_t MemAddr;        /* Specifies the memory base address for DMAy Channelx. */

    uint32_t Direction;      /* Specifies if the peripheral is the source or destination. */

    uint32_t BufSize;        /* Specifies the buffer size, in data unit, of the specified Channel.
                                The data unit is equal to the configuration set in PeriphDataSize
                                or MemDataSize members depending in the transfer direction. */

    uint32_t PeriphInc;      /* Specifies whether the Peripheral address register is incremented or not. */

    uint32_t DMA_MemoryInc;      /* Specifies whether the memory address register is incremented or not. */

    uint32_t PeriphDataSize; /* Specifies the Peripheral data width. */

    uint32_t MemDataSize;    /* Specifies the Memory data width. */

    uint32_t CircularMode;   /* Specifies the operation mode of the DMAy Channelx.
                                *\*\note: The circular buffer mode cannot be used if the memory-to-memory
                                data transfer is configured on the selected Channel. */

    uint32_t Priority;       /* Specifies the software priority for the DMAy Channelx. */

    uint32_t Mem2Mem;        /* Specifies if the DMAy Channelx will be used in memory-to-memory transfer. */
} DMA_InitType;

/*** DMA Structure Definition End ***/


/*** DMA Macro Definition Start ***/

/** DMA register bit field mask definition **/
#define DMA_REG_BIT_FIELD_MASK          ((uint32_t)0x00000000U)

/* DMA CHCFGx registers Masks, MEM2MEM, PL, MSIZE, PSIZE, MINC, PINC, CIRC and DIR bits */
#define CCR_CLEAR_Mask ((uint32_t)0xFFFF800FU)

/** DMA data transfer direction definition **/
#define DMA_DIR_PERIPH_MASK             (~((uint32_t)DMA_CHCFG1_DIR))
#define DMA_DIR_PERIPH_DST              ((uint32_t)DMA_CHCFG1_DIR)
#define DMA_DIR_PERIPH_SRC              ((uint32_t)DMA_REG_BIT_FIELD_MASK)

/** DMA peripheral incremented mode definition **/
#define DMA_PERIPH_INC_MODE_MASK        (~((uint32_t)DMA_CHCFG1_PINC))
#define DMA_PERIPH_INC_ENABLE           ((uint32_t)DMA_CHCFG1_PINC)
#define DMA_PERIPH_INC_DISABLE          ((uint32_t)DMA_REG_BIT_FIELD_MASK)

/** DMA memory incremented mode definition **/
#define DMA_MEM_INC_MODE_MASK           (~((uint32_t)DMA_CHCFG1_MINC))
#define DMA_MEM_INC_ENABLE              ((uint32_t)DMA_CHCFG1_MINC)
#define DMA_MEM_INC_DISABLE             ((uint32_t)DMA_REG_BIT_FIELD_MASK)

/** DMA peripheral data width definition **/
#define DMA_PERIPH_DATA_WIDTH_MASK      (~((uint32_t)DMA_CHCFG1_PSIZE))
#define DMA_PERIPH_DATA_SIZE_BYTE       ((uint32_t)(DMA_CHCFG1_PSIZE_0 \
                                                  & DMA_CHCFG1_PSIZE_1))
#define DMA_PERIPH_DATA_SIZE_HALFWORD   ((uint32_t)(DMA_CHCFG1_PSIZE_0))
#define DMA_PERIPH_DATA_SIZE_WORD       ((uint32_t)(DMA_CHCFG1_PSIZE_1))

/** DMA memory data width definition **/
#define DMA_MEM_DATA_WIDTH_MASK         (~((uint32_t)DMA_CHCFG1_MSIZE))
#define DMA_MemoryDataSize_Byte         ((uint32_t)(DMA_CHCFG1_MSIZE_0 \
                                                  & DMA_CHCFG1_MSIZE_1))
#define DMA_MemoryDataSize_HalfWord     ((uint32_t)(DMA_CHCFG1_MSIZE_0))
#define DMA_MemoryDataSize_Word         ((uint32_t)(DMA_CHCFG1_MSIZE_1))

/** DMA circulation mode definition **/
#define DMA_CIRCULAR_MODE_MASK          (~((uint32_t)DMA_CHCFG1_CIRC))
#define DMA_MODE_CIRCULAR               ((uint32_t)DMA_CHCFG1_CIRC)
#define DMA_MODE_NORMAL                 ((uint32_t)DMA_REG_BIT_FIELD_MASK)

/** DMA channel priority level definition **/
#define DMA_CH_PRIORITY_MASK            (~((uint32_t)DMA_CHCFG1_PRIOLVL))
#define DMA_PRIORITY_VERY_HIGH          ((uint32_t)(DMA_CHCFG1_PRIOLVL_0 \
                                                  | DMA_CHCFG1_PRIOLVL_1))
#define DMA_PRIORITY_HIGH               ((uint32_t)(DMA_CHCFG1_PRIOLVL_1))
#define DMA_PRIORITY_MEDIUM             ((uint32_t)(DMA_CHCFG1_PRIOLVL_0))
#define DMA_PRIORITY_LOW                ((uint32_t)(DMA_CHCFG1_PRIOLVL_0 \
                                                  & DMA_CHCFG1_PRIOLVL_1))

/** DMA memory to memory mode definition **/
#define DMA_MEM2MEM_MASK                (~((uint32_t)DMA_CHCFG1_MEM2MEM))
#define DMA_M2M_ENABLE                  ((uint32_t)DMA_CHCFG1_MEM2MEM)
#define DMA_M2M_DISABLE                 ((uint32_t)DMA_REG_BIT_FIELD_MASK)

/** DMA channel enable definition **/
#define DMA_CHANNEL_ENABLE              ((uint32_t)DMA_CHCFG1_CHEN)
#define DMA_CHANNEL_DISABLE             (~((uint32_t)DMA_CHCFG1_CHEN))

/** DMA interrupts definition **/
#define DMA_INT_TXC     ((uint32_t)DMA_CHCFG1_TXCIE) /* Transfer complete interrupt */
#define DMA_INT_HTX     ((uint32_t)DMA_CHCFG1_HTXIE) /* Half transfer interrupt */
#define DMA_INT_ERR     ((uint32_t)DMA_CHCFG1_ERRIE) /* Transfer error interrupt */

#define DMA_INT_GLB1 ((uint32_t)DMA_INTSTS_GLBF1) /* DMA channel1 global interrupt */
#define DMA_INT_TXC1 ((uint32_t)DMA_INTSTS_TXCF1) /* DMA channel1 transfer complete interrupt */
#define DMA_INT_HTX1 ((uint32_t)DMA_INTSTS_HTXF1) /* DMA channel1 half transfer interrupt */
#define DMA_INT_ERR1 ((uint32_t)DMA_INTSTS_ERRF1) /* DMA channel1 transfer error interrupt */
#define DMA_INT_GLB2 ((uint32_t)DMA_INTSTS_GLBF2) /* DMA channel2 global interrupt */
#define DMA_INT_TXC2 ((uint32_t)DMA_INTSTS_TXCF2) /* DMA channel2 transfer complete interrupt */
#define DMA_INT_HTX2 ((uint32_t)DMA_INTSTS_HTXF2) /* DMA channel2 half transfer interrupt */
#define DMA_INT_ERR2 ((uint32_t)DMA_INTSTS_ERRF2) /* DMA channel2 transfer error interrupt */
#define DMA_INT_GLB3 ((uint32_t)DMA_INTSTS_GLBF3) /* DMA channel3 global interrupt */
#define DMA_INT_TXC3 ((uint32_t)DMA_INTSTS_TXCF3) /* DMA channel3 transfer complete interrupt */
#define DMA_INT_HTX3 ((uint32_t)DMA_INTSTS_HTXF3) /* DMA channel3 half transfer interrupt */
#define DMA_INT_ERR3 ((uint32_t)DMA_INTSTS_ERRF3) /* DMA channel3 transfer error interrupt */
#define DMA_INT_GLB4 ((uint32_t)DMA_INTSTS_GLBF4) /* DMA channel4 global interrupt */
#define DMA_INT_TXC4 ((uint32_t)DMA_INTSTS_TXCF4) /* DMA channel4 transfer complete interrupt */
#define DMA_INT_HTX4 ((uint32_t)DMA_INTSTS_HTXF4) /* DMA channel4 half transfer interrupt */
#define DMA_INT_ERR4 ((uint32_t)DMA_INTSTS_ERRF4) /* DMA channel4 transfer error interrupt */
#define DMA_INT_GLB5 ((uint32_t)DMA_INTSTS_GLBF5) /* DMA channel5 global interrupt */
#define DMA_INT_TXC5 ((uint32_t)DMA_INTSTS_TXCF5) /* DMA channel5 transfer complete interrupt */
#define DMA_INT_HTX5 ((uint32_t)DMA_INTSTS_HTXF5) /* DMA channel5 half transfer interrupt */
#define DMA_INT_ERR5 ((uint32_t)DMA_INTSTS_ERRF5) /* DMA channel5 transfer error interrupt */

/** DMA flags definition **/
#define DMA_FLAG_GL1    ((uint32_t)DMA_INTSTS_GLBF1) /* DMA Channel1 global flag */
#define DMA_FLAG_TC1    ((uint32_t)DMA_INTSTS_TXCF1) /* DMA Channel1 transfer complete flag */
#define DMA_FLAG_HT1    ((uint32_t)DMA_INTSTS_HTXF1) /* DMA Channel1 half transfer flag */
#define DMA_FLAG_TE1    ((uint32_t)DMA_INTSTS_ERRF1) /* DMA Channel1 transfer error flag */
#define DMA_FLAG_GL2    ((uint32_t)DMA_INTSTS_GLBF2) /* DMA Channel2 global flag */
#define DMA_FLAG_TC2    ((uint32_t)DMA_INTSTS_TXCF2) /* DMA Channel2 transfer complete flag */
#define DMA_FLAG_HT2    ((uint32_t)DMA_INTSTS_HTXF2) /* DMA Channel2 half transfer flag */
#define DMA_FLAG_TE2    ((uint32_t)DMA_INTSTS_ERRF2) /* DMA Channel2 transfer error flag */
#define DMA_FLAG_GL3    ((uint32_t)DMA_INTSTS_GLBF3) /* DMA Channel3 global flag */
#define DMA_FLAG_TC3    ((uint32_t)DMA_INTSTS_TXCF3) /* DMA Channel3 transfer complete flag */
#define DMA_FLAG_HT3    ((uint32_t)DMA_INTSTS_HTXF3) /* DMA Channel3 half transfer flag */
#define DMA_FLAG_TE3    ((uint32_t)DMA_INTSTS_ERRF3) /* DMA Channel3 transfer error flag */
#define DMA_FLAG_GL4    ((uint32_t)DMA_INTSTS_GLBF4) /* DMA Channel4 global flag */
#define DMA_FLAG_TC4    ((uint32_t)DMA_INTSTS_TXCF4) /* DMA Channel4 transfer complete flag */
#define DMA_FLAG_HT4    ((uint32_t)DMA_INTSTS_HTXF4) /* DMA Channel4 half transfer flag */
#define DMA_FLAG_TE4    ((uint32_t)DMA_INTSTS_ERRF4) /* DMA Channel4 transfer error flag */
#define DMA_FLAG_GL5    ((uint32_t)DMA_INTSTS_GLBF5) /* DMA Channel5 global flag */
#define DMA_FLAG_TC5    ((uint32_t)DMA_INTSTS_TXCF5) /* DMA Channel5 transfer complete flag */
#define DMA_FLAG_HT5    ((uint32_t)DMA_INTSTS_HTXF5) /* DMA Channel5 half transfer flag */
#define DMA_FLAG_TE5    ((uint32_t)DMA_INTSTS_ERRF5) /* DMA Channel5 transfer error flag */

/** DMA remap channel request definition **/
#define DMA_REMAP_ADC       ((uint32_t)(DMA_CHSEL_CH_SEL_0 \
                                      & DMA_CHSEL_CH_SEL_1 \
                                      & DMA_CHSEL_CH_SEL_2 \
                                      & DMA_CHSEL_CH_SEL_3 \
                                      & DMA_CHSEL_CH_SEL_4 \
                                      & DMA_CHSEL_CH_SEL_5)) /* DMA Request For ADC */
#define DMA_REMAP_UART1_TX  ((uint32_t)(DMA_CHSEL_CH_SEL_0)) /* DMA Request For UART1_TX */
#define DMA_REMAP_UART1_RX  ((uint32_t)(DMA_CHSEL_CH_SEL_1)) /* DMA Request For UART1_RX */
#define DMA_REMAP_UART2_TX  ((uint32_t)(DMA_CHSEL_CH_SEL_0 \
                                      | DMA_CHSEL_CH_SEL_1)) /* DMA Request For UART2_TX */
#define DMA_REMAP_UART2_RX  ((uint32_t)(DMA_CHSEL_CH_SEL_2)) /* DMA Request For UART2_RX */
#define DMA_REMAP_UART3_TX  ((uint32_t)(DMA_CHSEL_CH_SEL_0 \
                                      | DMA_CHSEL_CH_SEL_2)) /* DMA Request For UART3_TX */
#define DMA_REMAP_UART3_RX  ((uint32_t)(DMA_CHSEL_CH_SEL_1 \
                                      | DMA_CHSEL_CH_SEL_2)) /* DMA Request For UART3_RX */
#define DMA_REMAP_UART4_TX  ((uint32_t)(DMA_CHSEL_CH_SEL_0 \
                                      | DMA_CHSEL_CH_SEL_1 \
                                      | DMA_CHSEL_CH_SEL_2)) /* DMA Request For UART4_TX */
#define DMA_REMAP_UART4_RX  ((uint32_t)(DMA_CHSEL_CH_SEL_3)) /* DMA Request For UART4_RX */
#define DMA_REMAP_UART5_TX  ((uint32_t)(DMA_CHSEL_CH_SEL_0 \
                                      | DMA_CHSEL_CH_SEL_3)) /* DMA Request For UART5_TX */
#define DMA_REMAP_UART5_RX  ((uint32_t)(DMA_CHSEL_CH_SEL_1 \
                                      | DMA_CHSEL_CH_SEL_3)) /* DMA Request For UART5_RX */
#define DMA_REMAP_SPI1_TX   ((uint32_t)(DMA_CHSEL_CH_SEL_0 \
                                      | DMA_CHSEL_CH_SEL_1 \
                                      | DMA_CHSEL_CH_SEL_3)) /* DMA Request For SPI1_TX */
#define DMA_REMAP_SPI1_RX   ((uint32_t)(DMA_CHSEL_CH_SEL_2 \
                                      | DMA_CHSEL_CH_SEL_3)) /* DMA Request For SPI1_RX */
#define DMA_REMAP_SPI2_TX   ((uint32_t)(DMA_CHSEL_CH_SEL_0 \
                                      | DMA_CHSEL_CH_SEL_2 \
                                      | DMA_CHSEL_CH_SEL_3)) /* DMA Request For SPI2_TX */
#define DMA_REMAP_SPI2_RX   ((uint32_t)(DMA_CHSEL_CH_SEL_1 \
                                      | DMA_CHSEL_CH_SEL_2 \
                                      | DMA_CHSEL_CH_SEL_3)) /* DMA Request For SPI2_RX */
#define DMA_REMAP_SPI3_TX   ((uint32_t)(DMA_CHSEL_CH_SEL_0 \
                                      | DMA_CHSEL_CH_SEL_1 \
                                      | DMA_CHSEL_CH_SEL_2 \
                                      | DMA_CHSEL_CH_SEL_3)) /* DMA Request For SPI3_TX */
#define DMA_REMAP_SPI3_RX   ((uint32_t)(DMA_CHSEL_CH_SEL_4)) /* DMA Request For SPI3_RX */
#define DMA_REMAP_I2C1_TX   ((uint32_t)(DMA_CHSEL_CH_SEL_0 \
                                      | DMA_CHSEL_CH_SEL_4)) /* DMA Request For I2C1_TX */
#define DMA_REMAP_I2C1_RX   ((uint32_t)(DMA_CHSEL_CH_SEL_1 \
                                      | DMA_CHSEL_CH_SEL_4)) /* DMA Request For I2C1_RX */
#define DMA_REMAP_I2C2_TX   ((uint32_t)(DMA_CHSEL_CH_SEL_0 \
                                      | DMA_CHSEL_CH_SEL_1 \
                                      | DMA_CHSEL_CH_SEL_4)) /* DMA Request For I2C2_TX */
#define DMA_REMAP_I2C2_RX   ((uint32_t)(DMA_CHSEL_CH_SEL_2 \
                                      | DMA_CHSEL_CH_SEL_4)) /* DMA Request For I2C2_RX */
#define DMA_REMAP_TIM1_CH1  ((uint32_t)(DMA_CHSEL_CH_SEL_0 \
                                      | DMA_CHSEL_CH_SEL_2 \
                                      | DMA_CHSEL_CH_SEL_4)) /* DMA Request For TIM1_CH1 */
#define DMA_REMAP_TIM1_CH2  ((uint32_t)(DMA_CHSEL_CH_SEL_1 \
                                      | DMA_CHSEL_CH_SEL_2 \
                                      | DMA_CHSEL_CH_SEL_4)) /* DMA Request For TIM1_CH2 */
#define DMA_REMAP_TIM1_CH3  ((uint32_t)(DMA_CHSEL_CH_SEL_0 \
                                      | DMA_CHSEL_CH_SEL_1 \
                                      | DMA_CHSEL_CH_SEL_2 \
                                      | DMA_CHSEL_CH_SEL_4)) /* DMA Request For TIM1_CH3 */
#define DMA_REMAP_TIM1_CH4  ((uint32_t)(DMA_CHSEL_CH_SEL_3 \
                                      | DMA_CHSEL_CH_SEL_4)) /* DMA Request For TIM1_CH4 */
#define DMA_REMAP_TIM1_COM  ((uint32_t)(DMA_CHSEL_CH_SEL_0 \
                                      | DMA_CHSEL_CH_SEL_3 \
                                      | DMA_CHSEL_CH_SEL_4)) /* DMA Request For TIM1_COM */
#define DMA_REMAP_TIM1_UP   ((uint32_t)(DMA_CHSEL_CH_SEL_1 \
                                      | DMA_CHSEL_CH_SEL_3 \
                                      | DMA_CHSEL_CH_SEL_4)) /* DMA Request For TIM1_UP */
#define DMA_REMAP_TIM1_TRIG ((uint32_t)(DMA_CHSEL_CH_SEL_0 \
                                      | DMA_CHSEL_CH_SEL_1 \
                                      | DMA_CHSEL_CH_SEL_3 \
                                      | DMA_CHSEL_CH_SEL_4)) /* DMA Request For TIM1_TRIG */
#define DMA_REMAP_TIM2_CH1  ((uint32_t)(DMA_CHSEL_CH_SEL_2 \
                                      | DMA_CHSEL_CH_SEL_3 \
                                      | DMA_CHSEL_CH_SEL_4)) /* DMA Request For TIM2_CH1 */
#define DMA_REMAP_TIM2_CH2  ((uint32_t)(DMA_CHSEL_CH_SEL_0 \
                                      | DMA_CHSEL_CH_SEL_2 \
                                      | DMA_CHSEL_CH_SEL_3 \
                                      | DMA_CHSEL_CH_SEL_4)) /* DMA Request For TIM2_CH2 */
#define DMA_REMAP_TIM2_CH3  ((uint32_t)(DMA_CHSEL_CH_SEL_1 \
                                      | DMA_CHSEL_CH_SEL_2 \
                                      | DMA_CHSEL_CH_SEL_3 \
                                      | DMA_CHSEL_CH_SEL_4)) /* DMA Request For TIM2_CH3 */
#define DMA_REMAP_TIM2_CH4  ((uint32_t)(DMA_CHSEL_CH_SEL_0 \
                                      | DMA_CHSEL_CH_SEL_1 \
                                      | DMA_CHSEL_CH_SEL_2 \
                                      | DMA_CHSEL_CH_SEL_3 \
                                      | DMA_CHSEL_CH_SEL_4)) /* DMA Request For TIM2_CH4 */
#define DMA_REMAP_TIM2_UP   ((uint32_t)(DMA_CHSEL_CH_SEL_5)) /* DMA Request For TIM2_UP */
#define DMA_REMAP_TIM2_TRIG ((uint32_t)(DMA_CHSEL_CH_SEL_0 \
                                      | DMA_CHSEL_CH_SEL_5)) /* DMA Request For TIM2_TRIG */
#define DMA_REMAP_TIM3_CH1  ((uint32_t)(DMA_CHSEL_CH_SEL_1 \
                                      | DMA_CHSEL_CH_SEL_5)) /* DMA Request For TIM3_CH1 */
#define DMA_REMAP_TIM3_CH2  ((uint32_t)(DMA_CHSEL_CH_SEL_0 \
                                      | DMA_CHSEL_CH_SEL_1 \
                                      | DMA_CHSEL_CH_SEL_5)) /* DMA Request For TIM3_CH2 */
#define DMA_REMAP_TIM3_CH3  ((uint32_t)(DMA_CHSEL_CH_SEL_2 \
                                      | DMA_CHSEL_CH_SEL_5)) /* DMA Request For TIM3_CH3 */
#define DMA_REMAP_TIM3_CH4  ((uint32_t)(DMA_CHSEL_CH_SEL_0 \
                                      | DMA_CHSEL_CH_SEL_2 \
                                      | DMA_CHSEL_CH_SEL_5)) /* DMA Request For TIM3_CH4 */
#define DMA_REMAP_TIM3_UP   ((uint32_t)(DMA_CHSEL_CH_SEL_1 \
                                      | DMA_CHSEL_CH_SEL_2 \
                                      | DMA_CHSEL_CH_SEL_5)) /* DMA Request For TIM3_UP */
#define DMA_REMAP_TIM3_TRIG ((uint32_t)(DMA_CHSEL_CH_SEL_0 \
                                      | DMA_CHSEL_CH_SEL_1 \
                                      | DMA_CHSEL_CH_SEL_2 \
                                      | DMA_CHSEL_CH_SEL_5)) /* DMA Request For TIM3_TRIG */
#define DMA_REMAP_TIM4_CH1  ((uint32_t)(DMA_CHSEL_CH_SEL_3 \
                                      | DMA_CHSEL_CH_SEL_5)) /* DMA Request For TIM4_CH1 */
#define DMA_REMAP_TIM4_CH2  ((uint32_t)(DMA_CHSEL_CH_SEL_0 \
                                      | DMA_CHSEL_CH_SEL_3 \
                                      | DMA_CHSEL_CH_SEL_5)) /* DMA Request For TIM4_CH2 */
#define DMA_REMAP_TIM4_CH3  ((uint32_t)(DMA_CHSEL_CH_SEL_1 \
                                      | DMA_CHSEL_CH_SEL_3 \
                                      | DMA_CHSEL_CH_SEL_5)) /* DMA Request For TIM4_CH3 */
#define DMA_REMAP_TIM4_CH4  ((uint32_t)(DMA_CHSEL_CH_SEL_0 \
                                      | DMA_CHSEL_CH_SEL_1 \
                                      | DMA_CHSEL_CH_SEL_3 \
                                      | DMA_CHSEL_CH_SEL_5)) /* DMA Request For TIM4_CH4 */
#define DMA_REMAP_TIM4_UP   ((uint32_t)(DMA_CHSEL_CH_SEL_2 \
                                      | DMA_CHSEL_CH_SEL_3 \
                                      | DMA_CHSEL_CH_SEL_5)) /* DMA Request For TIM4_UP */
#define DMA_REMAP_TIM4_TRIG ((uint32_t)(DMA_CHSEL_CH_SEL_0 \
                                      | DMA_CHSEL_CH_SEL_2 \
                                      | DMA_CHSEL_CH_SEL_3 \
                                      | DMA_CHSEL_CH_SEL_5)) /* DMA Request For TIM4_TRIG */
#define DMA_REMAP_TIM5_CH1  ((uint32_t)(DMA_CHSEL_CH_SEL_1 \
                                      | DMA_CHSEL_CH_SEL_2 \
                                      | DMA_CHSEL_CH_SEL_3 \
                                      | DMA_CHSEL_CH_SEL_5)) /* DMA Request For TIM5_CH1 */
#define DMA_REMAP_TIM5_CH2  ((uint32_t)(DMA_CHSEL_CH_SEL_0 \
                                      | DMA_CHSEL_CH_SEL_1 \
                                      | DMA_CHSEL_CH_SEL_2 \
                                      | DMA_CHSEL_CH_SEL_3 \
                                      | DMA_CHSEL_CH_SEL_5)) /* DMA Request For TIM5_CH2 */
#define DMA_REMAP_TIM5_CH3  ((uint32_t)(DMA_CHSEL_CH_SEL_4 \
                                      | DMA_CHSEL_CH_SEL_5)) /* DMA Request For TIM5_CH3 */
#define DMA_REMAP_TIM5_CH4  ((uint32_t)(DMA_CHSEL_CH_SEL_0 \
                                      | DMA_CHSEL_CH_SEL_4 \
                                      | DMA_CHSEL_CH_SEL_5)) /* DMA Request For TIM5_CH4 */
#define DMA_REMAP_TIM5_UP   ((uint32_t)(DMA_CHSEL_CH_SEL_1 \
                                      | DMA_CHSEL_CH_SEL_4 \
                                      | DMA_CHSEL_CH_SEL_5)) /* DMA Request For TIM5_UP */
#define DMA_REMAP_TIM5_TRIG ((uint32_t)(DMA_CHSEL_CH_SEL_0 \
                                      | DMA_CHSEL_CH_SEL_1 \
                                      | DMA_CHSEL_CH_SEL_4 \
                                      | DMA_CHSEL_CH_SEL_5)) /* DMA Request For TIM5_TRIG */
#define DMA_REMAP_TIM6_UP   ((uint32_t)(DMA_CHSEL_CH_SEL_2 \
                                      | DMA_CHSEL_CH_SEL_4 \
                                      | DMA_CHSEL_CH_SEL_5)) /* DMA Request For TIM6_UP */
#define DMA_REMAP_DAC       ((uint32_t)(DMA_CHSEL_CH_SEL_0 \
                                      | DMA_CHSEL_CH_SEL_2 \
                                      | DMA_CHSEL_CH_SEL_4 \
                                      | DMA_CHSEL_CH_SEL_5)) /* DMA Request For DAC */
#define DMA_REMAP_GCLK_TRIG ((uint32_t)(DMA_CHSEL_CH_SEL_1 \
                                      | DMA_CHSEL_CH_SEL_2 \
                                      | DMA_CHSEL_CH_SEL_4 \
                                      | DMA_CHSEL_CH_SEL_5)) /* DMA Request For GCLK_TRIG */
#define DMA_REMAP_RESERVED  ((uint32_t)0x0000003FU)           /* DMA Request reserved value */

/** DMA Channelx interrupt pending bit masks definition **/
#define DMA_CH1_INT_MASK ((uint32_t)(DMA_INTSTS_GLBF1 | DMA_INTSTS_TXCF1 | DMA_INTSTS_HTXF1 | DMA_INTSTS_ERRF1))
#define DMA_CH2_INT_MASK ((uint32_t)(DMA_INTSTS_GLBF2 | DMA_INTSTS_TXCF2 | DMA_INTSTS_HTXF2 | DMA_INTSTS_ERRF2))
#define DMA_CH3_INT_MASK ((uint32_t)(DMA_INTSTS_GLBF3 | DMA_INTSTS_TXCF3 | DMA_INTSTS_HTXF3 | DMA_INTSTS_ERRF3))
#define DMA_CH4_INT_MASK ((uint32_t)(DMA_INTSTS_GLBF4 | DMA_INTSTS_TXCF4 | DMA_INTSTS_HTXF4 | DMA_INTSTS_ERRF4))
#define DMA_CH5_INT_MASK ((uint32_t)(DMA_INTSTS_GLBF5 | DMA_INTSTS_TXCF5 | DMA_INTSTS_HTXF5 | DMA_INTSTS_ERRF5))

/*** DMA Macro Definition End ***/


/*** DMA Driving Functions Declaration ***/
void DMA_DeInit(DMA_ChannelType* DMAChx);
void DMA_Init(DMA_ChannelType* DMAChx, DMA_InitType* DMA_InitParam);
void DMA_StructInit(DMA_InitType* DMA_InitParam);
void DMA_EnableChannel(DMA_ChannelType* DMAChx, FunctionalState Cmd);
void DMA_ConfigInt(DMA_ChannelType* DMAChx, uint32_t DMAInt, FunctionalState Cmd);
void DMA_SetCurrDataCounter(DMA_ChannelType* DMAChx, uint16_t DataNumber);
uint16_t DMA_GetCurrDataCounter(const DMA_ChannelType* DMAChx);
FlagStatus DMA_GetFlagStatus(uint32_t DMAFlag, const DMA_Module* DMAy);
void DMA_ClearFlag(uint32_t DMAFlag, DMA_Module* DMAy);
INTStatus DMA_GetIntStatus(uint32_t DMA_IT, const DMA_Module* DMAy);
void DMA_ClrIntPendingBit(uint32_t DMA_IT, DMA_Module* DMAy);
void DMA_RequestRemap(uint32_t DMA_REMAP, const DMA_Module* DMAy, DMA_ChannelType* DMAChx, FunctionalState Cmd);


#ifdef __cplusplus
}
#endif

#endif /*__N32A052_DMA_H__ */

