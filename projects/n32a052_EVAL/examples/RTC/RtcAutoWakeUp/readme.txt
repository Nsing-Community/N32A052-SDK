1、功能说明
    1、通过设定唤醒时间触发中断。


2、使用环境

    软件开发环境：KEIL MDK-ARM V5.34.0.0
                 IAR EWARM 8.50.1
    硬件开发环境： 
        N32A052系列：
            基于评估板N32A052KBQX_STB V1.0开发  

3、使用说明

    系统配置；
        1、周期性唤醒时钟源：RTCCLK（1HZ）
        2、串口配置：
                    - 串口为UART1（TX：PA9  RX：PA10）:
                    - 数据位：8
                    - 停止位：1
                    - 奇偶校验：无
                    - 波特率： 115200 


    使用方法：
        1、编译后烧录到评估板，上电后，串口每隔4s会打印I am in rtc_wkup。
            
4、注意事项
    无


1. Function description
    1. Trigger the interrupt by setting the wake-up time.


2. Use environment

	Software development environment: KEIL MDK-ARM V5.34.0.0
                                      IAR EWARM 8.50.1
    Hardware development environment:
         N32A052 series:
            Developed based on the evaluation board N32A052KBQX_STB V1.0



3. Instructions for use

    System Configuration;
        1. Periodic wake-up clock source: RTCCLK (1HZ)
        2. Serial port configuration:
                    - Serial port is UART1 (TX: PA9 RX: PA10):
                    - Data bits: 8
                    - Stop bit: 1
                    - Parity: none
                    - Baud rate: 115200


    Instructions:
        1. After compiling, burn it to the evaluation board. After power-on, the serial port will print I am in rtc_wkup every 4s.
            
4. Matters needing attention
    none