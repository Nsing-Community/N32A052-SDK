1、功能说明

    此例程提供了一种DMA MemtoMem模式用法，用于在FLASH与RAM之间传输数据。  

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
            全双工
            主模式
            8bit传输
            极性：起始为低/第二个边沿
            软件片选
            大端在前MSB
    
    4、SPI2 配置：
            SCK   -->  PC5
            MISO  -->  PC7
            MOSI  -->  PC6
            全双工
            从模式
            8bit传输
            极性：起始为低/第二个边沿
            软件片选
            大端在前MSB

    5、使用方法：
          1、编译后下载程序复位运行；
          2、SPI1、SPI2 同时收发数据，传输完成后，发送 CRC 数据，检查数据和 CRC 值，
               查看 TransferStatus1 和 TransferStatus2 状态为 PASSED，再查看 CRC 值；

4、注意事项
    1. 需根据主机时钟空闲电平来配置主机CLK引脚的上/下拉，CLKPOL为1配置为上拉，CLKPOL为0配置为下拉.


1. Function description
    This routine provides a DMA MemtoMem mode usage for transferring data between FLASH and RAM.

    
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
        Full duplex
        Main mode
        8 bit transmission
        Polarity: start at low/second edge
        Piece of software to choose
        Big end in front MSB

    4. SPI2 Configuration:
        SCK   -->  PC5
        MISO  -->  PC7
        MOSI  -->  PC6
        Full duplex
        From the pattern
        8 bit transmission
        Polarity: start at low/second edge
        Piece of software to choose
        Big end in front MSB

    5.Instructions:
        1. After compiling, download the program to reset and run;
        2. SPI1, SPI2 send and receive data at the same time, after the transmission is completed, send CRC data, check the data and CRC value,
           Check that the status of TransferStatus1 and TransferStatus2 is PASSED, and then check the CRC value;

4. Precautions
    1. The pull-up/down of the host CLK pin should be configured according to the idle level of the host clock，
        when CLKPOL is set to 1, it is configured as pull-up; when CLKPOL is set to 0, it is configured as pull-down.