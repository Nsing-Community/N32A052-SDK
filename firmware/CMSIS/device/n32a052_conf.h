/*****************************************************************************
 * Copyright (c) 2023, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/
 
/**
*\*\file n32a052_conf.h
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/ 

#ifndef __N32A052_CONF_H__
#define __N32A052_CONF_H__

/* Uncomment/Comment the line below to enable/disable peripheral header file inclusion */

#include "n32a052_adc.h"
#include "n32a052_beeper.h"
#include "n32a052_can.h"
#include "n32a052_comp.h"
#include "n32a052_crc.h"
#include "n32a052_dac.h"
#include "n32a052_dma.h"
#include "n32a052_exti.h"
#include "n32a052_flash.h"
#include "n32a052_gpio.h"
#include "n32a052_i2c.h"
#include "n32a052_iwdg.h"
#include "n32a052_lcd.h"
#include "n32a052_pwr.h"
#include "n32a052_rcc.h"
#include "n32a052_rtc.h"
#include "n32a052_spi.h"
#include "n32a052_tim.h"
#include "n32a052_uart.h"
#include "n32a052_wwdg.h"


#include "misc.h" /* High level functions for NVIC and SysTick (add-on to CMSIS functions) */

/* Uncomment the line below to expanse the "assert_param" macro in the
   Standard Peripheral Library drivers code */
/* #define USE_FULL_ASSERT    1  */

#endif /* __N32A052_CONF_H___CONF_H */
