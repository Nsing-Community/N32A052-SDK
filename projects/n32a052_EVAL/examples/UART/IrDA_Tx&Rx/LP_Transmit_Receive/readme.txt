1、功能说明

    该测例演示了UARTy与UARTz间实现串行IrDA低功耗模式红外解码功能的基础通信。
    首先，UARTy发送TxBuffer1数据至UARTz，UARTz通过中断接收数据存至RxBuffer1。
    随后，比较接收数据与发送数据，比较结果存入TransferStatus变量。


2、使用环境

    软件开发环境：KEIL MDK-ARM V5.34.0.0
                 IAR EWARM 8.50.1
    硬件开发环境： 
        N32A052系列：
            基于评估板N32A052KBQX_STB V1.0开发


3、使用说明

    系统时钟配置如下：
    - 时钟源 = HSE
    - 系统时钟 = 8MHz
    
    UART配置如下：
    - 波特率 = 600 baud
    - 字长 = 8数据位
    - 1停止位
    - 校验控制禁用
    - 硬件流控制禁用（RTS和CTS信号）
    - 接收器和发送器使能
    - IrDA模式使能
    
    UART引脚连接如下：
    - UART1_Tx.PA2    <------->   IrDA Transmitter
    - UART4_Rx.PD11    <------->   IrDA Receiver
    
    - GPIO.PB0         <------->   38kHz carrier

    
    测试步骤与现象：
    - 复位运行MCU，查看变量TransferStatus，其中，PASSED为测试通过，FAILED为测试异常


4、注意事项

1. Function description

    This test example demonstrates the basic communication between UARTy and UARTz to realize the infrared 
    decoding function of serial IrDA low power consumption mode.
    First, UARTy sends TxBuffer1 data to UARTz, and UARTz receives data through interrupt and stores it in RxBuffer1.
    Subsequently, compare the received data with the sent data, and the result of the comparison is stored in the 
    TransferStatus variable.


2. Use environment

	Software development environment: KEIL MDK-ARM V5.34.0.0
                                      IAR EWARM 8.50.1
    Hardware development environment:
         N32A052 series:
            Developed based on the evaluation board N32A052KBQX_STB V1.0


3. Instructions for use

    The system clock configuration is as follows:
    -Clock source = HSE
    -System clock = 8MHz
    
    The UART configuration is as follows:
    -Baud rate = 600 baud
    -Word length = 8 data bits
    -1 stop bit
    -Verification control disabled
    -Hardware flow control disabled (RTS and CTS signals)
    -Receiver and transmitter enable
    -IrDA mode enable
    
    The UART pin connections are as follows:
    - UART1_Tx.PA2    <------->   IrDA Transmitter
    - UART4_Rx.PD11    <------->   IrDA Receiver
    
    - GPIO.PB0         <------->   38kHz carrier

    
    Test steps and phenomena:
-Reset and run the MCU, check the variable TransferStatus, where PASSED means the test passed and FAILED means the test is abnormal


4. Matters needing attention