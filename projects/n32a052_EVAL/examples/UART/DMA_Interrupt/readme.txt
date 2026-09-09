1、功能说明

    该测例演示了UARTy与UARTz间通过DMA(中断)实现的基础通信。
    首先，DMA传输TxBuffer1数据至UARTy发送数据寄存器，传输完成产生
DMA中断，随后数据发送至UARTz。UARTz在接收中断中接收数据，数据存储
至RxBuffer2，完成后关闭中断。
    同时，DMA传输TxBuffer2数据至UARTz发送数据寄存器，传输完成产生
DMA中断，随后数据发送至UARTy。UARTy通过查询标志位的形式将数据存储
至RxBuffer1。
    最后，分别比较两组收、发数据，比较结果存入TransferStatus1变量
和TransferStatus2变量。


2、使用环境

    软件开发环境：KEIL MDK-ARM V5.34.0.0
                 IAR EWARM 8.50.1
    硬件开发环境： 
        N32A052系列：
            基于评估板N32A052KBQX_STB V1.0开发


3、使用说明
	
    系统时钟配置如下：
    - 系统时钟 = 64MHz
    
    UART配置如下：
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

    This test example demonstrates basic communication between UARTy and UARTz via DMA. 

   First, the DMA transfers the TxBuffer1 data to the UARTy transmit data register, and then the 
   data is sent to the UARTz. UARTz uses the interrupt to receive data and store it in RxBuffer2. 

   At the same time, the DMA transfers the TxBuffer2 data to the UARTz transmit data register,
   and then the data is sent to the UARTy. UARTy receives data by querying the check flag and 
   stores it in RxBuffer1. 

2. Use environment

	Software development environment: KEIL MDK-ARM V5.34.0.0
                                      IAR EWARM 8.50.1
    Hardware development environment:
         N32A052 series:
            Developed based on the evaluation board N32A052KBQX_STB V1.0

3. Instructions for use

    The system clock configuration is as follows:
    -System clock = 64MHz
    
    The UART configuration is as follows:
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