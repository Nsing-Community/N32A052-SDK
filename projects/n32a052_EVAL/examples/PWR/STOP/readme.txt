﻿﻿1、功能说明
1、STOP进入和唤醒退出示例。


2、使用环境

    /* 软件开发环境：当前工程使用的软件工具名称及版本号 */
    IDE工具：KEIL MDK-ARM 5.34.0.0
                 IAR EWARM 8.50.1
      
    /* 硬件环境：工程对应的开发硬件平台 */
     N32A052系列：
            基于评估板N32A052KBQ7_STB V1.0开发
     


3、使用说明

    系统配置；
        1、时钟源：HSI+PLL
        2、时钟频率：64M
        3、唤醒引脚：PA0
        4、打印：PA9-115200

    使用方法：
        在KEIL下编译后烧录到评估板，上电输出打印“PWR_STOP INIT”。过了一会输出打印“STOP ENTRY”，表明进入STOP了。
        按下WAKEUP按键后，串口又输出“STOP EXIT”，表明MCU被唤醒了.从停止的位置执行。


4、注意事项
    STOP模式下时钟关闭，若开启NRST滤波会导致引脚复位失效，因此需要在进STOP前关闭NRST滤波，退出STOP后再开启NRST滤波。


1. Function description
    1. Example of STOP entry and wake-up exit.


2. Use environment

    /* Software development environment: the name and version number of the software tool used in the current project */
    IDE tool: KEIL MDK-ARM 5.34.0.0
                 IAR EWARM 8.50.1
      
    /* Hardware environment: the development hardware platform corresponding to the project */
     N32A052 series:
            Developed based on the evaluation board N32A052KBQ7_STB V1.0


3. Instructions for use

    System Configuration;
        1. Clock source: HSI+PLL
        2. Clock frequency: 64M
        3. Wakeup pin: PA0
        4. Log: PA9-115200

    Instructions:
        After compiling under KEIL and burning it to the evaluation board, the output prints "PWR_STOP INIT" after power-on. After a while, the output prints "STOP ENTRY", indicating that it has entered STOP.
        After pressing the WAKEUP button, the serial port outputs "STOP EXIT" again, indicating that the MCU is awakened. Execute from the stopped position.


4. Matters needing attention
    The clock is off in STOP mode, and turning on the NRST filter will cause the pin reset to fail, so you need to turn off the NRST filter before going into STOP, and then turn on the NRST filter after exiting STOP.