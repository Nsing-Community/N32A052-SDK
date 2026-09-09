1、功能说明

    1、SPI 单线中断发送和接收数据

2、使用环境

    软件开发环境：KEIL MDK-ARM V5.34.0.0
                 IAR EWARM 8.50.1
    硬件开发环境： 
        N32A052系列：
            基于评估板N32A052KBQX_STB V1.0开发


3、使用说明

    1、时钟源：HSE+PLL
    2、主时钟：64MHz
    3、SPI1 配置：
            SCK   -->  PB12
            MOSI  -->  PD4
            单线模式
            主模式
            8bit传输
            极性：起始为低/第二个边沿
            软件片选
            大端在前MSB
    
    4、SPI2 配置：
            SCK   -->  PC5
            MISO  -->  PC7
            单线模式
            从模式
            8bit传输
            极性：起始为低/第二个边沿
            软件片选
            大端在前MSB

    5、中断：SPI1 中断入口函数 SPI1_IRQHandler，SPI2 中断入口函数 SPI2_IRQHandler
    6、使用方法：
        /* 描述Demo的测试步骤和现象 */
        1.编译后下载程序复位运行；
        2.SPI1 有数据需要发送时进入 SPI1_IRQHandler 中断函数发送，SPI2 有数据需要接收时进入 SPI2_IRQHandler中断函数接收，数据传输完成后，查看 TransferStatus 状态为 PASSED；

4、注意事项
    1. “单线”数据线在主设备端为MOSI引脚，在从设备端为MISO引脚
    2. 单线模式下，需根据主机时钟空闲电平来配置主机CLK引脚的上/下拉



1. Function description

    1. SPI single-wire interrupt sending and receiving data

2. Use environment
    Software development environment: KEIL MDK-ARM V5.34.0.0
                                      IAR EWARM 8.50.1
    Hardware development environment:
         N32A052 series:
            Developed based on the evaluation board N32A052KBQX_STB V1.0

3. Instructions for use

    /* Describe related module configuration methods; for example: clock, I/O, etc. */
    1. SystemClock: 64MHz
    2. clock source:HSE+PLL

    3. SPI1 configuration:
        SCK   -->  PB12
        MOSI  -->  PD4
        single-line
        Master mode
        8 bit transmission
        Polarity: start at low/second edge
        Piece of software to choose
        Big end in front MSB

    4. SPI2 Configuration:
        SCK   -->  PC5
        MISO  -->  PC7
        single-line
        Slave mode
        8 bit transmission
        Polarity: start at low/second edge
        Piece of software to choose
        Big end in front MSB
    5. Interrupt: SPI1 interrupt entry function SPI1_IRQHandler, SPI2 interrupt entry function SPI2_IRQHandler

    /* Describe the test steps and phenomena of the Demo */
    1. After compiling, download the program to reset and run;
    2. Enter the SPI1_IRQHandler interrupt function to send when SPI1 has data to send, 
        and enter the SPI2_IRQHandler interrupt function to receive when SPI2 has data to receive. 
        After the data transmission is completed, check the TransferStatus status as PASSED;

4. Matters needing attention
    1. The "single wire" data lines are MOSI pins on the master side and MISO pins on the slave side.
    2. In single-wire mode, the pull-up/down of the host CLK pin should be configured according to the idle level of the host clock.