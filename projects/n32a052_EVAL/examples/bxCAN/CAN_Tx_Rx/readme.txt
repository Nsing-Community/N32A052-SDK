1、功能说明

    /* 简单描述工程功能 */
        这个例程配置并演示CAN在正常模式下收发CAN报文情况


2、使用环境

    软件开发环境：KEIL MDK-ARM V5.34.0.0
                 IAR EWARM 8.50.1
    硬件开发环境： 
        N32A052系列：
            基于评估板N32A052KBQX_STB V1.0开发


3、使用说明
    
    /* 描述相关模块配置方法；例如:时钟，I/O等 */
        SystemClock：64MHz
        CAN: RX-PA3, TX-PB3，波特率500K，正常模式

    /* 描述Demo的测试步骤和现象 */
        1.编译后下载程序复位运行；
        2.CAN初始化对外发送一帧消息
        3.然后在收到其他设备发来的消息后，会再对外发送一帧消息。


4、注意事项

1. Function description
    1. The reference program for CAN sending and receiving.


2. Use environment

	Software development environment: KEIL MDK-ARM V5.34.0.0
                                      IAR EWARM 8.50.1
    Hardware development environment:
         N32A052 series:
            Developed based on the evaluation board N32A052KBQX_STB V1.0


3. Instructions for use
    
    System Configuration;
    /* Describe the configuration method of related modules; for example: clock, I/O, etc. */
    SystemClock: 64MHz
    CAN: RX-PA3, TX-PB3, baud rate 500K, normal mode

    /* Describe the test steps and phenomena of Demo */
    1. After compiling, download the program to reset and run;
    2. CAN initialization sends a frame of message externally
    3. After receiving messages from other devices, another frame of message will be sent to the outside world.
                     
                 
4. Matters needing attention
     without

