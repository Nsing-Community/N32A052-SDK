﻿﻿1、功能说明

    /* 简单描述工程功能 */
    这个例程配置并演示系统时钟源为HSE和PLL时，当HSE失效时的恢复处理


2、使用环境

    /* 软件开发环境：当前工程使用的软件工具名称及版本号 */
    IDE工具：KEIL MDK-ARM 5.34.0.0
                 IAR EWARM 8.50.1
      
    /* 硬件环境：工程对应的开发硬件平台 */
     N32A052系列：
            基于评估板N32A052KBQ7_STB V1.0开发
     

3、使用说明

    /* 描述相关模块配置方法；例如:时钟，I/O等 */
    USART：TX - PA9，波特率115200

    /* 描述Demo的测试步骤和现象 */
    1.编译后下载程序复位运行；
    2.系统时钟配置为HSE及PLL，此时重复打印"Running!"，将晶振引脚接地后HSE失效后系统复位，使用HSI+PLL作为系统时钟正常打印工作；


4、注意事项
    

1. Function description

     /* Briefly describe the engineering function */
     This example configures and demonstrates the recovery handling when the HSE fails when the system clock source is the HSE and PLL.


2. Use environment

    /* Software development environment: the name and version number of the software tool used in the current project */
    IDE tool: KEIL MDK-ARM 5.34.0.0
                 IAR EWARM 8.50.1
      
    /* Hardware environment: the development hardware platform corresponding to the project */
     N32A052 series:
            Developed based on the evaluation board N32A052KBQ7_STB V1.0

3. Instructions for use

     /* Describe the configuration method of related modules; for example: clock, I/O, etc. */
     USART: TX-PA9, baud rate 115200

     /* Describe the test steps and phenomena of Demo */
     1. After compiling, download the program to reset and run;
     2. The system clock is configured as HSE and PLL. At this time, repeatedly print "Running!". 
        After grounding the crystal oscillator pin, if HSE fails, the system will reset. Use HSI+PLL as the system clock to print normally;


4. Attention