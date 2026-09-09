﻿1、功能说明
    1、LVR配置电压产生对应的复位。


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
        3、打印：PA9-115200

    使用方法：
        在KEIL下编译后烧录到评估板，把电压调低到LVR设置电压以下，再调到设置电压以上，此时芯片复位，打印"LVR reset occurs!"。


4、注意事项
    无


1. Function description
    1. The LVR configuration voltage generates a corresponding reset


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
        3. Log: PA9-115200

    Instructions:
        After compiling under KEIL and burning to the evaluation board, lower the voltage to below the LVR setting voltage, 
        and then adjust to above the setting voltage, then the chip reset, print "LVR reset occurs!".


4. Matters needing attention
    none