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
*\*\file main.c
*\*\author Nations 
*\*\version v1.0.0 
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/
#include "main.h"
#include "log.h"


#define I2C_MASTER_LOW_LEVEL
#define TEST_BUFFER_SIZE  100
#define I2CT_FLAG_TIMEOUT ((uint32_t)0x1000)
#define I2CT_LONG_TIMEOUT ((uint32_t)(10 * I2CT_FLAG_TIMEOUT))
#define I2C_MASTER_ADDR   0x30

/* When the MCU is sent as a host and in 7-bit address mode, the slave address cannot be configured as 0xF0, 0xF2, 0xF4, or 0xF6. */
#define I2C_SLAVE_ADDR    0x10

#define I2C1_TEST
#define I2Cx I2C1
#define I2Cx_SCL_PIN GPIO_PIN_12
#define I2Cx_SDA_PIN GPIO_PIN_13
#define GPIOx        GPIOD
#define GPIO_AF_I2C GPIO_AF6_I2C1

static uint8_t tx_buf[TEST_BUFFER_SIZE] = {0};
static uint8_t rx_buf[TEST_BUFFER_SIZE] = {0};
volatile Status test_status      = FAILED;
static __IO uint32_t I2CTimeout;
static CommCtrl_t Comm_Flag = C_READY; // Avoid star flag and stop flag set 1 at the same time


static uint8_t rx_num = 0;
static uint8_t tx_num = 0;
uint8_t flag_master_recv_finish = 0;
uint8_t flag_master_send_finish = 0;
uint8_t flag_trans_direct       = 0; // write

Status Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);
void Memset(void* s, uint8_t c, uint32_t count);
void CommTimeOut_CallBack(ErrCode_t errcode);
    
/**
*\*\name    Delay.
*\*\fun     system ms delay function.
*\*\param   nCount
*\*\return  none 
**/
void Delay(__IO uint32_t nCount)
{
    __IO uint32_t tcnt;
    while (nCount--)
    {
        tcnt = 64000 / 5;
        while (tcnt--){;}
    }
}
/**
*\*\name    Delay_us.
*\*\fun     system us delay function.
*\*\param   nCount
*\*\return  none 
**/
void Delay_us(__IO uint32_t nCount)
{
    __IO uint32_t tcnt;
    while (nCount--)
    {
        tcnt = 64 / 5;
        while (tcnt--){;}
    }
}


/**
*\*\name    NVIC_ConfigurationMaster.
*\*\fun     NVIC enable.
*\*\param   ch I2C channel
*\*\return  result 
**/
void NVIC_ConfigurationMaster(uint8_t ch)
{
    NVIC_InitType NVIC_InitStructure;
    if (ch == 1)
    {
        NVIC_InitStructure.NVIC_IRQChannel = I2C1_IRQn;
    }
    if (ch == 2)
    {
        NVIC_InitStructure.NVIC_IRQChannel = I2C2_IRQn;
    }

    NVIC_InitStructure.NVIC_IRQChannelPriority           = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


/**
*\*\name    NVIC_ConfigurationMaster.
*\*\fun     NVIC disable.
*\*\param   ch I2C channel
*\*\return  result 
**/
void NVIC_ConfigurationMasterDis(void)
{
    NVIC_InitType NVIC_InitStructure;

    NVIC_InitStructure.NVIC_IRQChannel                   = I2C1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority           = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = DISABLE;
    NVIC_Init(&NVIC_InitStructure);
}


/**
*\*\name    i2c_master_init.
*\*\fun     master gpio/rcc/i2c/nvic initializes.
*\*\param   none
*\*\return  result 
**/
int i2c_master_init(void)
{
    I2C_InitType i2c1_master;
    GPIO_InitType i2c1_gpio;
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_I2C1, ENABLE);
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOD, ENABLE);
    GPIOx->POD |= (I2Cx_SCL_PIN | I2Cx_SDA_PIN);//pull up pin

    GPIO_InitStruct(&i2c1_gpio);
    /*PD12 -- SCL; PD13 -- SDA*/
    i2c1_gpio.Pin        = I2Cx_SCL_PIN | I2Cx_SDA_PIN;
    i2c1_gpio.GPIO_Slew_Rate = GPIO_SLEW_RATE_FAST; 
    i2c1_gpio.GPIO_Mode  = GPIO_MODE_AF_OD;
    i2c1_gpio.GPIO_Alternate = GPIO_AF_I2C;
    i2c1_gpio.GPIO_Pull = GPIO_PULL_UP;	  
    GPIO_InitPeripheral(GPIOx, &i2c1_gpio);

    I2C_DeInit(I2Cx);
    I2C_InitStruct(&i2c1_master);
    i2c1_master.BusMode     = I2C_BUSMODE_I2C;
    i2c1_master.FmDutyCycle = I2C_FMDUTYCYCLE_2;
    i2c1_master.OwnAddr1    = I2C_MASTER_ADDR;
    i2c1_master.AckEnable   = I2C_ACKEN;
    i2c1_master.AddrMode    = I2C_ADDR_MODE_7BIT;
    i2c1_master.ClkSpeed    = 100000; // 100000 100K

    I2C_Init(I2Cx, &i2c1_master);
    I2C_EnableTimeoutDetect(I2Cx, I2C_TIMEOUT_LOW, DISABLE);
    // int enable
    I2C_ConfigInt(I2Cx, I2C_INT_EVENT | I2C_INT_BUF | I2C_INT_ERR, ENABLE);
    NVIC_ConfigurationMaster(1);
    I2C_Enable(I2Cx, ENABLE);
    return 0;
}

/**
*\*\name    main.
*\*\fun     main function.
*\*\param   none
*\*\return  none 
**/
int main(void)
{
    uint16_t i = 0;
    // USART_Config();
    log_init();
    log_info("\n\rthis is a i2c master int demo\r\n");

    i2c_master_init();

    /* Fill the buffer to send */
    for (i = 0; i < TEST_BUFFER_SIZE; i++)
    {
        tx_buf[i] = i;
    }
    /* First write in the memory followed by a read of the written data --------*/
    /* Write data*/
    flag_trans_direct = 0;
    if (Comm_Flag == C_READY)
    {
        Comm_Flag = C_START_BIT;
        I2C_GenerateStart(I2C1, ENABLE);
    }
    
    I2CTimeout = I2CT_LONG_TIMEOUT * 1000;
    while (flag_master_send_finish == 0)
    {
        if ((I2CTimeout--) == 0)
        {
            CommTimeOut_CallBack(MASTER_UNKNOW);
        }
    }
    
    /* master send finish */
    flag_master_send_finish = 0;
    I2CTimeout = I2CT_LONG_TIMEOUT;
    while (I2C_GetFlag(I2C1, I2C_FLAG_BUSY))
    {
        if ((I2CTimeout--) == 0)
        {
            CommTimeOut_CallBack(MASTER_BUSY);
        }
    }
    Comm_Flag = C_READY;

    I2C_ConfigAck(I2C1, ENABLE);
    /* read data */
    flag_trans_direct = 1;
    if (Comm_Flag == C_READY)
    {
        Comm_Flag = C_START_BIT;
        I2C_GenerateStart(I2C1, ENABLE);
    }
    
    I2CTimeout = I2CT_LONG_TIMEOUT * 1000;
    while (flag_master_recv_finish == 0)
    {
        if ((I2CTimeout--) == 0)
        {
            CommTimeOut_CallBack(MASTER_UNKNOW);
        }
    }
        
    /* master recv finish */
    flag_master_recv_finish = 0;
    I2CTimeout = I2CT_LONG_TIMEOUT;
    while (I2C_GetFlag(I2C1, I2C_FLAG_BUSY))
    {
        if ((I2CTimeout--) == 0)
        {
            CommTimeOut_CallBack(MASTER_BUSY);
        }
    }
    Comm_Flag = C_READY;

    /* Check if the data written to the memory is read correctly */
    test_status = Buffercmp(tx_buf, rx_buf, TEST_BUFFER_SIZE);
    if (test_status == PASSED) /* test_status = PASSED, if the write and read dataare the same  */
    {
        log_info("the write and read data the same, i2c master int test pass\r\n");
    }
    else /* test_status = FAILED, if the write and read dataare different */
    {
        log_info("the write and read data are different, i2c master int test fail\r\n");
    }

    while (1)
    {
    }
}
/**
*\*\name    I2C1_IRQHandler.
*\*\fun     i2c Interrupt service function.
*\*\param   none
*\*\return  none 
**/
void I2C1_IRQHandler(void)
{
    uint32_t last_event = 0;

    last_event = I2C_GetLastEvent(I2C1);
    if ((last_event & I2C_ROLE_MASTER) == I2C_ROLE_MASTER) // master mode
    {
        switch (last_event)
        {
        case I2C_EVT_MASTER_MODE_FLAG: // EV5 Send addr
            
            if(flag_trans_direct)     // read
            {
                Memset(rx_buf, 0, TEST_BUFFER_SIZE); // clear recv buf, ready to recv data
                I2C_SendAddr7bit(I2C1, I2C_SLAVE_ADDR, I2C_DIRECTION_RECV);
                rx_num = 0;
            }
            else // write
            {
                I2C_SendAddr7bit(I2C1, I2C_SLAVE_ADDR, I2C_DIRECTION_SEND);
                tx_num = 0;
            }
            break;

           // MasterTransmitter	
        case I2C_EVT_MASTER_TXMODE_FLAG: // EV6 Send first data
            Comm_Flag = C_READY;
            I2C_SendData(I2C1, tx_buf[tx_num++]);
            break;

        case I2C_EVT_MASTER_DATA_SENDING: // EV8 Sending data
            
            if (tx_num < TEST_BUFFER_SIZE)
            {
                I2C_SendData(I2C1, tx_buf[tx_num++]);
            }
            break;
            
        case I2C_EVT_MASTER_DATA_SENDED: // EV8_2 Send finish
            
            if (tx_num == TEST_BUFFER_SIZE)
            {
                if (Comm_Flag == C_READY)
                {
                    Comm_Flag = C_STOP_BIT;
                    I2C_GenerateStop(I2C1, ENABLE);
                    flag_master_send_finish = 1;
                }
            }
            break;
            
            // MasterReceiver
        case I2C_EVT_MASTER_RXMODE_FLAG: // EV6
            Comm_Flag = C_READY;
            if (TEST_BUFFER_SIZE == 1)
            {
                I2C_ConfigAck(I2C1, DISABLE);
                if (Comm_Flag == C_READY)
                {
                    Comm_Flag = C_STOP_BIT;
                    I2C_GenerateStop(I2C1, ENABLE);
                }
            }
            else if (TEST_BUFFER_SIZE == 2)
            {
                I2C1->CTRL1 |= I2C_NACK_POS_NEXT; /// set ACKPOS
                I2C_ConfigAck(I2C1, DISABLE);
            }
            break;

        case I2C_EVT_MASTER_DATA_RECVD_FLAG: // EV7.one byte recved 
        case I2C_EVT_MASTER_DATA_RECVD_BSF_FLAG: // EV7.When the I2C communication rate is too high, BSF = 1
            
            rx_buf[rx_num++] = I2C_RecvData(I2C1);
            if (rx_num == (TEST_BUFFER_SIZE - 1))
            { 
                I2C_ConfigAck(I2C1, DISABLE);   // Disable I2C1 acknowledgement.
                if (Comm_Flag == C_READY)
                {
                    Comm_Flag = C_STOP_BIT;
                    I2C_GenerateStop(I2C1, ENABLE); // Send I2C1 STOP Condition.
                }
            }
            else if (rx_num == TEST_BUFFER_SIZE)
            {
                flag_master_recv_finish = 1;
            }
            break;
        case 0x00030201: // Arbitration lost
        case 0x00030101: // Acknowledge failure
        case 0x00030501: // Acknowledge failure and Bus error
            I2C_Enable(I2C1, DISABLE);
            I2C_Enable(I2C1, ENABLE);
            break;

        default:
            log_info("I2C error status:0x%x\r\n", last_event);
            break;
        }
    }
}



/**
*\*\name   Buffercmp.
*\*\fun    Compares two buffers.
*\*\param  pBuffer, pBuffer1: buffers to be compared.
*\*\param  BufferLength: buffer's length
*\*\return PASSED: pBuffer identical to pBuffer1
*\*\       FAILED: pBuffer differs from pBuffer1
**/
Status Buffercmp(uint8_t* pBuffer, uint8_t* pBuffer1, uint16_t BufferLength)
{
    while (BufferLength--)
    {
        if (*pBuffer != *pBuffer1)
        {
            return FAILED;
        }

        pBuffer++;
        pBuffer1++;
    }

    return PASSED;
}


/**
*\*\name   Memset.
*\*\fun    memery set a value
*\*\param  s source.
*\*\param  c value
*\*\param  count number
*\*\return pointer of the memery
**/
void Memset(void* s, uint8_t c, uint32_t count)
{
    char* xs = (char*)s;

    while (count--) // clear 17byte buffer
    {
        *xs++ = c;
    }

    return;
}

/**
*\*\name    IIC_RestoreSlaveByClock.
*\*\fun     Emulate 9 clock recovery slave by GPIO.
*\*\param   none
*\*\return  none 
**/
void IIC_RestoreSlaveByClock(void)
{
    uint8_t i;
    GPIO_InitType i2cx_gpio;
    
    GPIOx->POD |= (I2Cx_SCL_PIN | I2Cx_SDA_PIN);//pull up pin
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOD, ENABLE);
    GPIOx->POD |= (I2Cx_SCL_PIN | I2Cx_SDA_PIN);//pull up pin
    
    GPIO_InitStruct(&i2cx_gpio);
    i2cx_gpio.Pin        = I2Cx_SCL_PIN;
    i2cx_gpio.GPIO_Slew_Rate = GPIO_SLEW_RATE_FAST; 
    i2cx_gpio.GPIO_Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitPeripheral(GPIOx, &i2cx_gpio);
    
    for (i = 0; i < 9; i++)
    {
        GPIO_SetBits(GPIOx, I2Cx_SCL_PIN);
        Delay_us(5);
        GPIO_ResetBits(GPIOx, I2Cx_SCL_PIN);
        Delay_us(5);
    }
}

/**
*\*\name    SystemNVICReset.
*\*\fun     System software reset.
*\*\param   none
*\*\return  none 
**/
void SystemNVICReset(void)
{
    
    __disable_irq();
    log_info("***** NVIC system reset! *****\r\n");
    NVIC_SystemReset();
}

/**
*\*\name    IIC_RCCReset.
*\*\fun     RCC clock reset.
*\*\param   none
*\*\return  none 
**/
void IIC_RCCReset(void)
{
    RCC_EnableAPB1PeriphReset(RCC_APB1_PERIPH_I2C1);
    
    IIC_RestoreSlaveByClock();
    
    i2c_master_init();
    log_info("***** IIC module by RCC reset! *****\r\n");
    
}

/**
*\*\name    IIC_SWReset.
*\*\fun     I2c software reset.
*\*\param   none
*\*\return  none 
**/
void IIC_SWReset(void)
{
    GPIO_InitType i2cx_gpio;
    
    GPIO_InitStruct(&i2cx_gpio);
    i2cx_gpio.Pin        = I2Cx_SCL_PIN | I2Cx_SDA_PIN;
    i2cx_gpio.GPIO_Slew_Rate = GPIO_SLEW_RATE_FAST; 
    i2cx_gpio.GPIO_Mode  = GPIO_MODE_INPUT;
    GPIO_InitPeripheral(GPIOx, &i2cx_gpio);
    
    I2CTimeout = I2CT_LONG_TIMEOUT;
    for (;;)
    {
        if ((I2Cx_SCL_PIN | I2Cx_SDA_PIN) == (GPIOx->PID & (I2Cx_SCL_PIN | I2Cx_SDA_PIN)))
        {
            I2C_EnableSoftwareReset(I2Cx,ENABLE);
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            I2C_EnableSoftwareReset(I2Cx,DISABLE);
            
            log_info("***** IIC module self reset! *****\r\n");
            break;
        }
        else
        {
            if ((I2CTimeout--) == 0)
            {
                IIC_RCCReset();
            }
        }
    }
}

/**
*\*\name    CommTimeOut_CallBack.
*\*\fun     Callback function.
*\*\param   none
*\*\return  none 
**/
void CommTimeOut_CallBack(ErrCode_t errcode)
{
    log_info("...ErrCode:%d\r\n", errcode);
    
#if (COMM_RECOVER_MODE == MODULE_SELF_RESET)
    IIC_SWReset();
#elif (COMM_RECOVER_MODE == MODULE_RCC_RESET)
    IIC_RCCReset();
#elif (COMM_RECOVER_MODE == SYSTEM_NVIC_RESET)
    SystemNVICReset();
#endif
}

