1、功能说明

    该测例演示了如何使用UART多处理器模式。UARTy和UARTz可以是UART1和UART4。
    首先，分别设置UARTy和UARTz的地址为0x1和0x2。UARTy连续给UARTz发送字符0x33。UARTz收到0x33，便翻转LED1引脚。
    一旦KEY1_INT_EXTI_LINE线检测到上升沿，则产生EXTI中断，在EXTI0_1_IRQHandler中断处理函数中(the ControlFlag = 0)，
    UARTz进入静默模式，在静默模式中，LED引脚停止翻转，直到KEY1_INT_EXTI_LINE线检测到上升沿(the ControlFlag = 1)。
    在EXTI0_1_IRQHandler中断处理函数中，UARTy发送地址0x102唤醒UARTz。LED引脚重新启动翻转。


2、使用环境

    软件开发环境：KEIL MDK-ARM V5.34.0.0
                 IAR EWARM 8.50.1
    硬件开发环境： 
        N32A052系列：
            基于评估板N32A052KBQX_STB V1.0开发


3、使用说明
	
    系统时钟配置如下：
    - 系统时钟 = 64MHz
    
    UARTy配置如下：
    - 波特率 = 115200 baud
    - 字长 = 9数据位
    - 1停止位
    - 校验控制禁用
    - 接收器和发送器使能  
    
    
    UART引脚连接如下：    
    - UART1_Tx.PA2   <------->   UART4_Rx.PD11
    - UART1_Rx.PA3   <------->   UART4_Tx.PD5
    
    KEY1_INT_EXTI_LINE.PA1    <------->   KEY1
    
    LED1    <------->   PB0

    
    测试步骤与现象：
    - Demo在KEIL环境下编译后，下载至MCU
    - 复位运行，观察LED1是否处于闪烁状态
    - 按按键KEY，观察LED1是否停止闪烁
    - 再次按按键KEY，观察LED1是否恢复闪烁


4、注意事项


1. Function description

    This test example demonstrates how to use the UART multiprocessor mode. UARTy and UARTz can be UART1 and UART4.
    First, set the addresses of UARTy and UARTz to 0x1 and 0x2 respectively. UARTy continuously sends the character 0x33 to UARTz. UARTz receives 0x33 and flips the pins of LED1.
    Once the KEY1_INT_EXTI_LINE line detects the rising edge, the EXTI0 interrupt is generated. In the EXTI0_1_IRQHandler interrupt processing function (the ControlFlag = 0), 
    the UARTz enters the silent mode. In the silent mode, the LED pin stops toggling until the KEY1_INT_EXTI_LINE line detects the rising edge ( the ControlFlag = 1). 
    In the EXTI0_1_IRQHandler interrupt processing function, UARTy sends address 0x102 to wake up UARTz. The LED pin restarts toggling.


2. Use environment

	Software development environment: KEIL MDK-ARM V5.34.0.0
                                      IAR EWARM 8.50.1
    Hardware development environment:
         N32A052 series:
            Developed based on the evaluation board N32A052KBQX_STB V1.0


3. Instructions for use

    The system clock configuration is as follows:
    -System clock = 64MHz
    
    The UARTy configuration is as follows:
    -Baud rate = 115200 baud
    -Word length = 9 data bits
    -1 stop bit
    -Verification control disabled
    -Receiver and transmitter enable
    
    
    The UART pin connections are as follows:
    - UART1_Tx.PA2   <------->   UART4_Rx.PD11
    - UART1_Rx.PA3   <------->   UART4_Tx.PD5
    
    KEY1_INT_EXTI_LINE.PA1    <------->   KEY1
    
    LED1    <------->   PB0

    
    Test steps and phenomena:
    -After the Demo is compiled in the KEIL environment, download it to the MCU
    -Reset operation, observe whether LED1 are blinking
    -Press the KEY button and observe if LED1 stop flashing
    -Press the KEY button again and observe whether LED1 resume flashing


4. Matters needing attention