1、功能说明

	/* 简单描述工程功能 */
        这个例程配置并演示如何配置选项字节


2、使用环境

    软件开发环境：KEIL MDK-ARM V5.34.0.0
                 IAR EWARM 8.50.1
    硬件开发环境： 
        N32A052系列：
            基于评估板N32A052KBQX_STB V1.0开发
        

3、使用说明
	
	/* 描述相关模块配置方法；例如:时钟，I/O等 */
        SystemClock：64MHz
        UART：TX - PA9，RX - PA10，波特率115200

	/* 描述Demo的测试步骤和现象 */
        1.编译后下载程序复位运行；
        2.对选项字节进行编程，编程OK，打印信息为测试通过；


4、注意事项
    选项字节需要MCU复位后生效


/***   For English user   ***/
1. Function description

	/* Briefly describe the project function */
         This routine configures and demonstrates how to configure option bytes


2. Use environment

	Software development environment: KEIL MDK-ARM V5.34.0.0
                                      IAR EWARM 8.50.1
    Hardware development environment:
         N32A052 series:
            Developed based on the evaluation board N32A052KBQX_STB V1.0
        

3. Instructions for use

	/* Describe related module configuration methods; for example: clock, I/O, etc. */
         SystemClock: 64MHz
         UART: TX - PA9, RX - PA10, baud rate 115200

	/* Describe the test steps and phenomena of the Demo */
         1. After compiling, download the program to reset and run;
         2. Programming the option byte, programming OK, the print information is the test passed;


4. Matters needing attention
    Option bytes require an MCU reset to take effect