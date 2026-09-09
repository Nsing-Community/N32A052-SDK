1、功能说明
    通过PA0来检测入侵。


2、使用环境

    软件开发环境：KEIL MDK-ARM V5.34.0.0
                 IAR EWARM 8.50.1
    硬件开发环境： 
        N32A052系列：
            基于评估板N32A052KBQX_STB V1.0开发



3、使用说明

    系统配置；
        1、时钟：LSI
        2、检测口：PA0
        3、串口配置：
                    - 串口为USART1（TX：PA9  RX：PA10）:
                    - 数据位：8
                    - 停止位：1
                    - 奇偶校验：无
                    - 波特率： 115200 


    使用方法：
        1、编译后烧录到评估板，上电后，按按键WKUP(PA0)，串口打印输出Tamper2 interrupt。
                
                

4、注意事项
    无



1. Function description
    Intrusion is detected by PA0.



2. Use environment

	Software development environment: KEIL MDK-ARM V5.34.0.0
                                      IAR EWARM 8.50.1
    Hardware development environment:
         N32A052 series:
            Developed based on the evaluation board N32A052KBQX_STB V1.0



3. Instructions for use

    System Configuration;
        1. Clock: LSI
        2. Detection port: PA0
        3. Serial port configuration:
                    - Serial port is USART1 (TX: PA9 RX: PA10):
                    - Data bits: 8
                    - Stop bit: 1
                    - Parity: none
                    - Baud rate: 115200


    Instructions:
        1. After compiling, burn it to the evaluation board. After power-on, Press the button WKUP(PA0) and the serial port will print out Tamper2 interrupt.
                               

4. Matters needing attention
    None