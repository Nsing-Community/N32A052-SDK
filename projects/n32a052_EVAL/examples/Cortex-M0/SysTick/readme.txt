1. 功能描述

	/* 简要描述项目功能 */
         该例程配置并演示如何使用 SysTick


2. 使用环境

	软件开发环境： KEIL MDK-ARM V5.34.0.0
                IAR EWARM 8.50.1
    硬件开发环境：
         N32A052 系列：
            基于评估板 N32A052KBQX_STB V1.0 开发


3. 使用说明

	/* 说明相关模块的配置方法；例如：时钟、I/O 等。*/
         系统时钟：64MHz
         UART：TX - PA9，RX - PA10，波特率 115200
         SysTick：10ms中断

	/* 描述演示程序的测试步骤和现象 */
         1. 编译后，下载程序重置并运行；
         2. 触发 SysTick 中断后开始计数，计数为偶数时打印信息；


4. 注意事项



1. Function description

	/* Briefly describe the project function */
         This routine configures and demonstrates how to use SysTick


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
         SysTick: 10ms interrupt

	/* Describe the test steps and phenomena of the Demo */
         1. After compiling, download the program to reset and run;
         2. Start counting after the SysTick interrupt is triggered, and print information when the count is even;


4. Matters needing attention

