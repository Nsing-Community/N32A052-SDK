1、功能说明

    该测例演示了UARTy与UARTz间通过查询检测标识实现的基础通信。
    首先，UARTy发送TxBuffer1数据至UARTz，UARTz接收数据存至RxBuffer2。比较接收数据与发送数据，比较结果存入TransferStatus1变量。
    随后，UARTz发送TxBuffer2数据至UARTy，UARTy接收数据存至RxBuffer1。比较接收数据与发送数据，比较结果存入TransferStatus2变量。
    UARTy和UARTz可以是UART1和UART4。


2、使用环境

    软件开发环境：KEIL MDK-ARM V5.34.0.0
                 IAR EWARM 8.50.1

    硬件环境：最小系统板 N32A052KBL7-STB_V1.0


3、使用说明
	
    系统时钟配置如下：
    - 系统时钟 = 64MHz
    
    USART配置如下：
    - 波特率 = 115200 baud
    - 字长 = 8数据位
    - 1停止位
    - 校验控制禁用
    - 接收器和发送器使能
    
    UART引脚连接如下：    
    - UART1_Tx.PA2   <------->   UART4_Rx.PD11
    - UART1_Rx.PA3   <------->   UART4_Tx.PD5

    
    测试步骤与现象：
    - Demo在KEIL环境下编译后，下载至MCU
    - 复位运行，依次查看变量TransferStatus1和TransferStatus2，其中，
      PASSED为测试通过，FAILED为测试异常


4、注意事项

    需先将开发板NS-LINK的MCU_TX和MCU_RX跳线帽断开

1. Function description

    This test case demonstrates the basic communication between UARTy and UARTz by querying the detection identification.
    First, UARTy sends TxBuffer1 data to UARTz, and UARTz receives data and stores it in RxBuffer2.
Compare the received data with the sent data, and the comparison result is stored in the TransferStatus1 variable.
    Subsequently, UARTz sends TxBuffer2 data to UARTy, and UARTy receives data to RxBuffer1.
Compare the received data with the sent data, and the result of the comparison is stored in the TransferStatus2 variable.
    UARTy and UARTz can be UART1 and UART4.

2. Use environment

    Software development environment: KEIL MDK-ARM V5.34.0.0
                                      IAR EWARM 8.50.1

    Hardware environment: minimum system board N32A052KBL7-STB_V1.0

3. Instructions for use

    The system clock configuration is as follows:
    -System clock = 64MHz
    
    The USART configuration is as follows:
    -Baud rate = 115200 baud
    -Word length = 8 data bits
    -1 stop bit
    -Verification control disabled
    -Receiver and transmitter enable
    
    The UART pin connections are as follows:
    - UART1_Tx.PA2   <------->   UART4_Rx.PD11
    - UART1_Rx.PA3   <------->   UART4_Tx.PD5

    
    Test steps and phenomena:
    -After the Demo is compiled in the KEIL environment, download it to the MCU
    -Reset operation, check the variables TransferStatus1 and TransferStatus2 in turn, among them,
      PASSED means the test passed, FAILED means the test is abnormal


4. Matters needing attention

    the MCU_TX and MCU_RX jumper cap of the development board NS-LINK needs to be disconnected first