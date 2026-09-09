1、功能说明

    1、SPI 全双工软件 NSS 模式发送接收数据

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
            MISO  -->  PD5
            MOSI  -->  PD4
    
    4、SPI2 配置：
            SCK   -->  PC5
            MISO  -->  PC7
            MOSI  -->  PC6
            
    4、使用方法：
        /* 描述Demo的测试步骤和现象 */
        1.编译后下载程序复位运行；
        2.SPI1 初始化位主机，发送数据，SPI2 初始化位丛机，接收数据 ，传输完成后，检查数据，查看 TransferStatus1 和 TransferStatus2 状态为 PASSED，
          SPI2 初始化位主机，发送数据，SPI1 初始化位丛机，接收数据 ，传输完成后，检查数据，查看 TransferStatus3 和 TransferStatus4 状态为 PASSED；

4、注意事项
    1. 需根据主机时钟空闲电平来配置主机CLK引脚的上/下拉，CLKPOL为1配置为上拉，CLKPOL为0配置为下拉.



1. Function description

    1. SPI full-duplex software NSS mode to send and receive data

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
        MISO  -->  PD5
        MOSI  -->  PD4

    4. SPI2 Configuration:
        SCK   -->  PC5
        MISO  -->  PC7
        MOSI  -->  PC6

    /* Describe the test steps and phenomena of the Demo */
    1. After compiling, download the program to reset and run;
    2. SPI1 initializes the bit host, sends data, SPI2 initializes the bit cluster machine, receives data, after the transmission is completed, 
        check the data, check that the status of TransferStatus1 and TransferStatus2 is PASSED,
        SPI2 initializes the bit host, sends data, SPI1 initializes the bit cluster machine, receives data, and after the transmission is completed,
        check the data, and check that the status of TransferStatus3 and TransferStatus4 is PASSED;

4. Matters needing attention
    1. The pull-up/down of the host CLK pin should be configured according to the idle level of the host clock，
        when CLKPOL is set to 1, it is configured as pull-up; when CLKPOL is set to 0, it is configured as pull-down.