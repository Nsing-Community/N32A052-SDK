; *********************************************************************************************************
;     Copyright (c) 2023, Nations Technologies Inc.
; 
;     All rights reserved.
;
;     This software is the exclusive property of Nations Technologies Inc. (Hereinafter 
; referred to as NATIONS). This software, and the product of NATIONS described herein 
; (Hereinafter referred to as the Product) are owned by NATIONS under the laws and treaties
; of the People's Republic of China and other applicable jurisdictions worldwide.
;
;     NATIONS does not grant any license under its patents, copyrights, trademarks, or other 
; intellectual property rights. Names and brands of third party may be mentioned or referred 
; thereto (if any) for identification purposes only.
;
;     NATIONS reserves the right to make changes, corrections, enhancements, modifications, and 
; improvements to this software at any time without notice. Please contact NATIONS and obtain 
; the latest version of this software before placing orders.

;     Although NATIONS has attempted to provide accurate and reliable information, NATIONS assumes 
; no responsibility for the accuracy and reliability of this software.
; 
;     It is the responsibility of the user of this software to properly design, program, and test 
; the functionality and safety of any application made of this information and any resulting product. 
; In no event shall NATIONS be liable for any direct, indirect, incidental, special,exemplary, or 
; consequential damages arising in any way out of the use of this software or the Product.
;
;     NATIONS Products are neither intended nor warranted for usage in systems or equipment, any
; malfunction or failure of which may cause loss of human life, bodily injury or severe property 
; damage. Such applications are deemed, "Insecure Usage".
;
;     All Insecure Usage shall be made at user's risk. User shall indemnify NATIONS and hold NATIONS 
; harmless from and against all claims, costs, damages, and other liabilities, arising from or related 
; to any customer's Insecure Usage.

;     Any express or implied warranty with regard to this software or the Product, including,but not 
; limited to, the warranties of merchantability, fitness for a particular purpose and non-infringement
; are disclaimed to the fullest extent permitted by law.

;     Unless otherwise explicitly permitted by NATIONS, anyone may not duplicate, modify, transcribe
; or otherwise distribute this software for any purposes, in whole or in part.
;
;     NATIONS products and technologies shall not be used for or incorporated into any products or systems
; whose manufacture, use, or sale is prohibited under any applicable domestic or foreign laws or regulations. 
; User shall comply with any applicable export control laws and regulations promulgated and administered by 
; the governments of any countries asserting jurisdiction over the parties or transactions.
; ************************************************************************************************************

; Amount of memory (in bytes) allocated for Stack
; Tailor this value to your application needs
; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000500

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000200

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit

                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset
                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp                   ; Top of Stack
                DCD     Reset_Handler                  ; Reset Handler
                DCD     NMI_Handler                    ; NMI Handler
                DCD     HardFault_Handler              ; Hard Fault Handler
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     SVC_Handler                    ; SVCall Handler
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     PendSV_Handler                 ; PendSV Handler
                DCD     SysTick_Handler                ; SysTick Handler

                ; External Interrupts
                DCD     WWDG_IRQHandler                      ; WWDG
		DCD     PVD_IRQHandler                       ; PVD&LVR through EXTI Line16 detect
                DCD     RTC_IRQHandler                       ; RTC through EXTI Line17/18/19 detect
                DCD     MMU_RAMC_ERR_IRQHandler              ; MMU&RAM
                DCD     FLASH_IRQHandler                     ; FLASH
                DCD     RCC_IRQHandler                       ; RCC
                DCD     EXTI0_1_IRQHandler                   ; EXTI Line 0 and 1
                DCD     EXTI2_3_IRQHandler                   ; EXTI Line 2 and 3
                DCD     EXTI4_15_IRQHandler                  ; EXTI Line 4 to 15
                DCD     SAC_IRQHandler                       ; SAC
                DCD     DMA_CH1_2_IRQHandler                 ; DMA Channle 1 and 2
                DCD     DMA_CH3_4_5_IRQHandler               ; DMA Channle 3 and 4 and 5
                DCD     TIM4_IRQHandler                      ; TIM4
                DCD     TIM1_BRK_UP_TRG_COM_IRQHandler       ; TIM1 Break, Update, Trigger and Commutation
                DCD     TIM1_CC_IRQHandler                   ; UART2
                DCD     CAN_IRQHandler                       ; CAN          
                DCD     TIM3_IRQHandler                      ; TIM3     
                DCD     UART3_4_IRQHandler                   ; UART3 and UART4     
                DCD     TIM5_IRQHandler                      ; TIM5    
                DCD     TIM6_IRQHandler                      ; TIM6 through EXTI Line20 detect    
                DCD     TIM2_IRQHandler                      ; TIM2     
                DCD     ADC_IRQHandler                       ; ADC     
                DCD     SPI2_IRQHandler                      ; SPI2     
                DCD     I2C1_IRQHandler                      ; I2C1     
                DCD     I2C2_IRQHandler                      ; I2C2    
                DCD     SPI1_IRQHandler                      ; SPI1     
                DCD     UART1_IRQHandler                     ; UART1     
                DCD     SPI3_IRQHandler                      ; SPI3  
                DCD     UART5_IRQHandler                     ; UART5
                DCD     LCD_IRQHandler                       ; LCD
                DCD     UART2_IRQHandler                     ; UART2
                DCD     COMP1_2_3_4_IRQHandler               ; COMP1 2 3 4 					
__Vectors_End

__Vectors_Size  EQU  __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY

; Reset handler routine
Reset_Handler    PROC
                 EXPORT  Reset_Handler                 [WEAK]
		 IMPORT  __main
		 IMPORT  SystemInit  
                 LDR     R0, =SystemInit
                 BLX     R0
                 LDR     R0, =__main
                 BX      R0
                 ENDP

; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler                    [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler              [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler                    [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler                 [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler                [WEAK]
                B       .
                ENDP

Default_Handler PROC
	
						     	EXPORT     WWDG_IRQHandler                      [WEAK]
				                EXPORT     PVD_IRQHandler                       [WEAK]
                                EXPORT     RTC_IRQHandler                       [WEAK]
                                EXPORT     MMU_RAMC_ERR_IRQHandler              [WEAK]
                                EXPORT     FLASH_IRQHandler                     [WEAK]
                                EXPORT     RCC_IRQHandler                       [WEAK]
                                EXPORT     EXTI0_1_IRQHandler                   [WEAK]
                                EXPORT     EXTI2_3_IRQHandler                   [WEAK]
                                EXPORT     EXTI4_15_IRQHandler                  [WEAK]
                                EXPORT     SAC_IRQHandler                       [WEAK]
                                EXPORT     DMA_CH1_2_IRQHandler                 [WEAK]
                                EXPORT     DMA_CH3_4_5_IRQHandler               [WEAK]
                                EXPORT     TIM4_IRQHandler                      [WEAK]
                                EXPORT     TIM1_BRK_UP_TRG_COM_IRQHandler       [WEAK]
                                EXPORT     TIM1_CC_IRQHandler                   [WEAK]
                                EXPORT     CAN_IRQHandler                       [WEAK]        
                                EXPORT     TIM3_IRQHandler                      [WEAK]    
                                EXPORT     UART3_4_IRQHandler                   [WEAK]    
                                EXPORT     TIM5_IRQHandler                      [WEAK]   
                                EXPORT     TIM6_IRQHandler                      [WEAK]     
                                EXPORT     TIM2_IRQHandler                      [WEAK]   
                                EXPORT     ADC_IRQHandler                       [WEAK]
                                EXPORT     SPI2_IRQHandler                      [WEAK]  
                                EXPORT     I2C1_IRQHandler                      [WEAK]    
                                EXPORT     I2C2_IRQHandler                      [WEAK]
                                EXPORT     SPI1_IRQHandler                      [WEAK]
                                EXPORT     UART1_IRQHandler                     [WEAK]
                                EXPORT     SPI3_IRQHandler                      [WEAK]
                                EXPORT     UART5_IRQHandler                     [WEAK]
                                EXPORT     LCD_IRQHandler                       [WEAK]
                                EXPORT     UART2_IRQHandler                     [WEAK]
                                EXPORT     COMP1_2_3_4_IRQHandler               [WEAK]

WWDG_IRQHandler                      
PVD_IRQHandler                       
RTC_IRQHandler                       
MMU_RAMC_ERR_IRQHandler              
FLASH_IRQHandler                     
RCC_IRQHandler                       
EXTI0_1_IRQHandler                   
EXTI2_3_IRQHandler                   
EXTI4_15_IRQHandler                  
SAC_IRQHandler                       
DMA_CH1_2_IRQHandler                 
DMA_CH3_4_5_IRQHandler                 
TIM4_IRQHandler                      
TIM1_BRK_UP_TRG_COM_IRQHandler       
TIM1_CC_IRQHandler                   
CAN_IRQHandler                               
TIM3_IRQHandler                          
UART3_4_IRQHandler                       
TIM5_IRQHandler                         
TIM6_IRQHandler                           
TIM2_IRQHandler                         
ADC_IRQHandler                       
SPI2_IRQHandler                        
I2C1_IRQHandler                      
I2C2_IRQHandler                  
SPI1_IRQHandler                      
UART1_IRQHandler                     
SPI3_IRQHandler                      
UART5_IRQHandler                     
LCD_IRQHandler                       
UART2_IRQHandler                   
COMP1_2_3_4_IRQHandler                   

                B       .

                ENDP

                ALIGN

;*******************************************************************************
; User Stack and Heap initialization
;*******************************************************************************
                 IF      :DEF:__MICROLIB
                
                 EXPORT  __initial_sp
                 EXPORT  __heap_base
                 EXPORT  __heap_limit
                
                 ELSE
                
                 IMPORT  __use_two_region_memory
                 EXPORT  __user_initial_stackheap
                 
__user_initial_stackheap

                 LDR     R0, =  Heap_Mem
                 LDR     R1, =(Stack_Mem + Stack_Size)
                 LDR     R2, = (Heap_Mem +  Heap_Size)
                 LDR     R3, = Stack_Mem
                 BX      LR

                 ALIGN

                 ENDIF

                 END

