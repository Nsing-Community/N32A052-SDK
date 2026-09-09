1、功能说明

    此例程提供了一种DMA用法，用于在I2C外设与RAM之间传输数据。  

2、使用环境

    软件开发环境：KEIL MDK-ARM V5.34.0.0
                 IAR EWARM 8.50.1
    硬件开发环境： 
        N32A052系列：
            基于评估板N32A052KBQX_STB V1.0开发


3、使用说明

    1、时钟源：HSE+PLL
    2、主时钟：64MHz
    3、DMA通道：DMA_CH5，DMA_CH1
    4、I2C1 配置：
            SCL   -->  PA4
            SDA   -->  PA3
            ADDR：0x30(7bit)
            CLOCK：100K
    
    5、I2C2 配置：
            SCL   -->  PD12
            SDA   -->  PD13
            ADDR：0x30(7bit)
            CLOCK：100K
    
    6、UART1配置：
            TX  -->  PA9
            波特率：115200
            数据位：8bit
            停止位：1bit
            无校验

    7、测试步骤与现象
        a, 开发板连接:PA4连接PD12, PA3连接PD13
        b，编译下载代码复位运行
        c，从串口看打印信息，验证结果

4、注意事项
    无


1. Function description
    This routine provides a DMA usage for transferring data between I2C peripheral and RAM.

2. Use environment
    Software development environment: KEIL MDK-ARM V5.34.0.0
                                      IAR EWARM 8.50.1
    Hardware development environment:
         N32A052 series:
            Developed based on the evaluation board N32A052KBQX_STB V1.0

3. Instructions for use
    1.Clock source: HSE+PLL
    2.Master clock: 64MHz
    3.DMA channels: DMA_CH5, DMA_CH1
    4.I2C1 configuration:
        SCL   -->  PA4
        SDA   -->  PA3
        ADDR：0x30(7bit)
        CLOCK：100K
    5.I2C2 configuration:
        SCL   -->  PD12
        SDA   -->  PD13
        ADDR：0x30(7bit)
        CLOCK：100K
    6.UART1 configuration:
        TX  -->  PA9
        Baud rate: 115200
        Data bit: 8 bits
        Stop bit: 1bit
        No check
    7.Test steps and phenomena
    A. Development board connection: PA4 connected to PD12, PA3 connected to PD13
    B. Compile download code reset run
    C. View the printed information from the serial port and verify the result

4. Precautions
    None

