1、功能说明

    SPI 读、写、擦除 GD25Q16。

2、使用环境

    软件开发环境：KEIL MDK-ARM V5.34.0.0
                 IAR EWARM 8.50.1
    硬件开发环境： 
        N32A052系列：
            基于评估板N32A052KBQX_STB V1.0开发
    片外FLASH：GD25Q16

3、使用说明

    1、时钟源：HSE+PLL
    2、主时钟：64MHz
    3、SPI1 配置：
            SCK   -->  PC5
            MISO  -->  PC7
            MOSI  -->  PC6
            CS    -->  PD0
            全双工
            主模式
            8bit传输
            极性：起始为低/第二个边沿
            软件片选
            大端在前MSB

    4、使用方法：
          1、编译后下载程序复位运行；
           2、通过 SPI1 读取 GD25Q16 的 ID，然后写数据，再读出来，比较读写数据，查看 TransferStatus1 状态为 PASSED，然后擦除块，检查擦除块正常。

4、注意事项
    1. 需根据主机时钟空闲电平来配置主机CLK引脚的上/下拉，CLKPOL为1配置为上拉，CLKPOL为0配置为下拉.
    2. 由于PD0引脚同时兼作BOOT引脚，本示例需先在调试模式下运行程序，进main函数后打断点暂停，再连接SPI闪存模块进行测试


1. Function description
    SPI read, write, erase GD25Q16.

    
2. Use environment
    Software development environment: KEIL MDK-ARM V5.34.0.0
                                      IAR EWARM 8.50.1
    Hardware development environment:
         N32A052 series:
            Developed based on the evaluation board N32A052KBQX_STB V1.0
    Off-chip FLASH: GD25Q16
    
3. Instructions for use

    /* Describe related module configuration methods; for example: clock, I/O, etc. */
    1. SystemClock: 64MHz
    2. clock source:HSE+PLL

    3. SPI1 configuration:
        SCK   -->  PC5
        MISO  -->  PC7
        MOSI  -->  PC6
        CS    -->  PD0
        Full duplex
        Main mode
        8 bit transmission
        Polarity: start at low/second edge
        Piece of software to choose
        Big end in front MSB

    4.Instructions:
        1. After compiling, download the program to reset and run;
        2. Read the ID of GD25Q16 through SPI1, then write the data, then read it out, compare the read and write data, check the status of TransferStatus1 as PASSED, 
            then erase the block, and check the erase block is normal;

4. Precautions
    1. The pull-up/down of the host CLK pin should be configured according to the idle level of the host clock，
        when CLKPOL is set to 1, it is configured as pull-up; when CLKPOL is set to 0, it is configured as pull-down.
    2. Since PD0 also functions as the BOOT pin, this example requires running the program in debug mode first. After entering the main function, set a breakpoint to pause execution, then connect the SPI flash module for testing.