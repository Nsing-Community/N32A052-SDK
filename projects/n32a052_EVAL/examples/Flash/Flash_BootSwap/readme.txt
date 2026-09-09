1、功能说明

	/* 简单描述工程功能 */
        本demo将演示如何更改main flash的启动地址


2、使用环境

    软件开发环境：KEIL MDK-ARM V5.34.0.0
                 IAR EWARM 8.50.1
    硬件开发环境： 
        N32A052系列：
            基于评估板N32A052KBQX_STB V1.0开发
        

3、使用说明
	
	/* 描述相关模块配置方法；例如:时钟，I/O等 */
        SystemClock：64MHz
        USART：TX - PA9，RX - PA10，波特率115200

	/* 描述Demo的测试步骤和现象 */
        1.分别编译N32A052_BOOT0工程和N32A052_BOOT1工程并下载；下载完程序后复位运行；
        2.查看串口打印信息，刚上电时从0x8000000启动运行代码；
        3.通过串口下发0x55指令，系统复位并从从0x8010000启动运行代码；
        4.通过串口下发0xAA指令，系统复位并从从0x8000000启动运行代码。


4、注意事项
    N32A052_BOOT0工程和N32A052_BOOT1工程分别编译下载前，可以将前一个工程clean后再rebulid。


1. Function description

	/* Briefly describe the project function */
         This demo demonstrates how to change the boot address of the main flash


2. Use environment

	Software development environment: KEIL MDK-ARM V5.34.0.0
                                      IAR EWARM 8.50.1
    Hardware development environment:
         N32A052 series:
            Developed based on the evaluation board N32A052KBQX_STB V1.0
        

3. Instructions for use

	/* Describe related module configuration methods; for example: clock, I/O, etc. */
         SystemClock: 64MHz
         USART: TX - PA9, RX - PA10, baud rate 115200

	/* Describe the test steps and phenomena of the Demo */
         1. Compile N32A052_BOOT0 project and N32A052_BOOT1 project respectively and download them; reset and run them after downloading the program;
         2. Check the serial port print information, just power on from 0x8000000 start running code;
         3. Send 0x55 instruction through the serial port, the system reset and start running code from 0x8010000;
         4. Send 0xAA instruction through the serial port, the system reset and start running code from 0x8000000.

4. Matters needing attention
    Before compiling and downloading N32A052_BOOT0 and N32A052_BOOT1 respectively, you can clean the previous project and then rebulid it.