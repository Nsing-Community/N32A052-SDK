1、功能说明
    1、通过设定闹钟时间来触发闹钟中断。

2、使用环境

    软件开发环境：KEIL MDK-ARM V5.34.0.0
                 IAR EWARM 8.50.1
    硬件开发环境： 
        N32A052系列：
            基于评估板N32A052KBQX_STB V1.0开发

3、使用说明

    系统配置；
        1、RTC时钟源：LSI
        2、串口配置：
                    - 串口为UART1（TX：PA9  RX：PA10）:
                    - 数据位：8
                    - 停止位：1
                    - 奇偶校验：无
                    - 波特率： 115200 


    使用方法：
        编译后烧录到评估板，上电，串口按照闹钟设定时间进行打印输出。

4、注意事项
    无


1. Function description
    1. Trigger the alarm interrupt by setting the alarm time.

2. Use environment

    Software development environment: KEIL MDK-ARM V5.34.0.0
                                      IAR EWARM 8.50.1
    Hardware development environment:
         N32A052 series:
            Developed based on the evaluation board N32A052KBQX_STB V1.0


3. Instructions for use

    System Configuration;
        1. RTC clock source: LSI
        2. Serial port configuration:
                    - Serial port is UART1 (TX: PA9 RX: PA10):
                    - Data bits: 8
                    - Stop bit: 1
                    - Parity: none
                    - Baud rate: 115200


    Instructions:
        After compiling, burn it to the evaluation board, power on, and the serial port will print out the time set by the alarm clock.

4. Matters needing attention
    none