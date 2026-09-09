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


#define TEST_BUFFER_SIZE  100
#define I2CT_FLAG_TIMEOUT ((uint32_t)0x1000)
#define I2CT_LONG_TIMEOUT ((uint32_t)(10 * I2CT_FLAG_TIMEOUT))
#define I2C_SLAVE_ADDR    0x10

#define I2C1_TEST
#define I2Cx I2C1
#define I2Cx_SCL_PIN GPIO_PIN_12
#define I2Cx_SDA_PIN GPIO_PIN_13
#define GPIOx        GPIOD
#define GPIO_AF_I2C GPIO_AF6_I2C1
uint8_t data_buf[TEST_BUFFER_SIZE] = {0};
static __IO uint32_t I2CTimeout;
uint8_t flag_slave_recv_finish         = 0;
uint8_t flag_slave_send_finish         = 0;
static uint8_t rxDataNum = 0;

void CommTimeOut_CallBack(ErrCode_t errcode);



/**
*\*\name    NVIC_ConfigurationSlave.
*\*\fun     NVIC Configuration.
*\*\param   ch
*\*\return  result 
**/
void NVIC_ConfigurationSlave(uint8_t ch)
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
*\*\name    i2c_slave_init.
*\*\fun     slave gpio/rcc/i2c/nvic initializes.
*\*\param   none
*\*\return  result 
**/
int i2c_slave_init(void)
{
    I2C_InitType i2c1_slave;
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
    GPIO_InitPeripheral(GPIOx, &i2c1_gpio);

    I2C_DeInit(I2Cx);
    I2C_InitStruct(&i2c1_slave);
    i2c1_slave.BusMode     = I2C_BUSMODE_I2C;
    i2c1_slave.FmDutyCycle = I2C_FMDUTYCYCLE_2;
    i2c1_slave.OwnAddr1    = I2C_SLAVE_ADDR;
    i2c1_slave.AckEnable   = I2C_ACKEN;
    i2c1_slave.AddrMode    = I2C_ADDR_MODE_7BIT;
    i2c1_slave.ClkSpeed    = 100000; // 100000 100K

    I2C_Init(I2Cx, &i2c1_slave);
    I2C_EnableTimeoutDetect(I2Cx, I2C_TIMEOUT_LOW, DISABLE);
    // int enable
    I2C_ConfigInt(I2Cx, I2C_INT_EVENT | I2C_INT_BUF | I2C_INT_ERR, ENABLE);
    NVIC_ConfigurationSlave((uint8_t)1);
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
    log_init();
    log_info("this is a i2c slave int demo\r\n");

    /* Initialize the I2C slave driver ----------------------------------------*/
    i2c_slave_init();
    
    I2CTimeout = I2CT_LONG_TIMEOUT * 1000;
    // recive data
    while (flag_slave_recv_finish == 0) // wait for recv data finish
    {
        if ((I2CTimeout--) == 0)
            CommTimeOut_CallBack(SLAVE_UNKNOW);
    }
        
    log_info("recv finish,recv len = %d\r\n", rxDataNum);
    flag_slave_recv_finish = 0;

    I2CTimeout = I2CT_LONG_TIMEOUT * 1000;
    // send data
    while (flag_slave_send_finish == 0) // wait for send data finish
    {
        if ((I2CTimeout--) == 0)
            CommTimeOut_CallBack(SLAVE_UNKNOW);
    }
        
    log_info("tx finish,tx len = %d\r\n", rxDataNum);
    flag_slave_send_finish = 0;
        
    while (1)
    {;}
}


/**
*\*\name    I2C1_IRQHandler.
*\*\fun     i2c Interrupt service function.
*\*\param   none
*\*\return  none 
**/
void I2C1_IRQHandler(void)
{
    uint8_t timeout_flag = 0;
    uint32_t last_event = 0;
    
    last_event = I2C_GetLastEvent(I2C1);
    if ((last_event & I2C_ROLE_MASTER) != I2C_ROLE_MASTER) // MSMODE = 0:I2C slave mode
    {
        switch (last_event)
        {
        case I2C_EVT_SLAVE_RECV_ADDR_MATCHED: //EV1 Rx addr matched
            
            // clear flag,ready to receive data
            rxDataNum = 0;
            break;
        
        case I2C_EVT_SLAVE_SEND_ADDR_MATCHED: //EV1 Tx addr matched
            
            rxDataNum = 0;
            I2C1->DAT = data_buf[rxDataNum++];// Send first data
            break;
        
        // SlaveTransmitter	
        case I2C_EVT_SLAVE_DATA_SENDING:  //EV3 Sending data
           
            break;
            
        case I2C_EVT_SLAVE_DATA_SENDED:
            I2C1->DAT = data_buf[rxDataNum++];
            break;
        
        // SlaveReceiver
        case I2C_EVT_SLAVE_DATA_RECVD: //EV2 one byte recved
            data_buf[rxDataNum++] = I2C1->DAT;
            break;
       
        
        case I2C_EVT_SLAVE_STOP_RECVD: // EV4
            I2C_Enable(I2C1, ENABLE);   
            if(rxDataNum != 0)
            {
                flag_slave_recv_finish = 1; // The STOPF bit is not set after a NACK reception
            }
            break;
        
        default:
            I2C_Enable(I2C1, ENABLE);
            timeout_flag = 1;
            break;
        }
    }
    
    if (timeout_flag)
    {
        if ((I2CTimeout--) == 0)
        {
            CommTimeOut_CallBack(SLAVE_UNKNOW);
        }
    }
    else
    {
        I2CTimeout = I2CT_LONG_TIMEOUT;
    }
    if(last_event == I2C_EVT_SLAVE_ACK_MISS)   
    {   
        I2C_ClrFlag(I2C1, I2C_FLAG_ACKFAIL);
        if(rxDataNum != 0)  //slave send the last data and recv NACK 
        {
            flag_slave_send_finish = 1;
        }
        else //not the last data recv nack, send fail
        {
        }
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
    
    i2c_slave_init();
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

