1、功能说明

    此例程展示通过外部触发中断，控制 LED 闪烁


2、使用环境

    软件开发环境：KEIL MDK-ARM V5.34.0.0
                 IAR EWARM 8.50.1
    硬件开发环境： 
        N32A052系列：
            基于评估板N32A052KBQX_STB V1.0开发   

3、使用说明

    /* 描述相关模块配置方法；例如:时钟，I/O等 */
    SystemClock：64MHz
    GPIO：PA1 选择作为外部中断入口，PB4 控制 LED 闪烁


    /* 描述Demo的测试步骤和现象 */
    1.编译后下载程序复位运行；
    2.按下松开 KEY1 按键，LED 闪烁；


4、注意事项
    无

1. Function description

    This example shows how to control LED blinking by externally triggering an interrupt.
    

2. Use environment

	Software development environment: KEIL MDK-ARM V5.34.0.0
                                      IAR EWARM 8.50.1
    Hardware development environment:
         N32A052 series:
            Developed based on the evaluation board N32A052KBQX_STB V1.0


3. Instructions for use

     //Describe related module configuration methods; for example, clock, I/O, etc.
     1. SystemClock: 64MHz
     2. GPIO：PA1 is selected as the external interrupt entry, PB4 controls the LED to flash.

     //Describe the test steps and phenomena of the Demo
     1. Compile and download the code to reset and run.
     2. Press and release the KEY1 button,then the LED will flash.

4. Matters needing attention
     None