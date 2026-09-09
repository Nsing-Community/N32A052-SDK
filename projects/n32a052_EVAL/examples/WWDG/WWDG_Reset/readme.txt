1、功能说明
    1、WWDG复位功能。


2、使用环境

    软件开发环境：KEIL MDK-ARM V5.34.0.0
                 IAR EWARM 8.50.1
    硬件开发环境： 
        N32A052系列：
            基于评估板N32A052KBQX_STB V1.0开发


3、使用说明

    系统配置；
        1、WWDG时钟源：PCLK1 32MHz
        2、窗口值：48.128ms < n < 65.536ms
        3、指示灯：PB0(LED1)   PD11(LED3)
             
    测试步骤与现象：
        1、在KEIL下编译后烧录到评估板，上电后，指示灯LED2不停的闪烁。说明窗口值刷新正常，代码正常运行。
        2、当把SysTick_Delay_Ms(57)函数参数改成小于48或者大于65时，整个系统将一直处于复位状态。LED1亮。


4、注意事项
    1、当窗口值很小时，系统处于频繁的复位状态，此时，容易引起程序无法正常下载。本例程中在开启WWDG前加了1秒延时来避免这个现象。当然也可以不用延时，直接将BOOT0引脚拉高即可正常下载。 



1. Function description

    WWDG reset function.
    

2. Use environment

	Software development environment: KEIL MDK-ARM V5.34.0.0
                                      IAR EWARM 8.50.1
    Hardware development environment:
         N32A052 series:
            Developed based on the evaluation board N32A052KBQX_STB V1.0


3. Instructions for use

    System Configuration:
       1. IWDG clock source: PCLK1 32MHz
       2. Window value: 48.128ms < n < 65.536ms
       3. light Indicator: PB0(LED1)   PD11(LED3)

    Test steps and phenomenon：
       1. Compile and download the code to reset and run, the indicator LED2 keeps flashing.
          It means that the window value is refreshed normally and the code is running normally.
       2. When the parameter of the SysTick_Delay_Ms() function is changed from 57 to less than 48 or greater than 65, 
          the entire system will always be in the reset state. LED1 is on.

4. Matters needing attention
    1. When the window value is very small, the system is in a frequent reset state, and at this time, it is easy to 
       cause the program to fail to download normally. In this routine, 1s delay is added before WWDG is 
       turned on to avoid this phenomenon. Of course, without delay, you can directly pull up the BOOT0 pin to download normally.