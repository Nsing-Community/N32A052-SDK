﻿﻿1、功能说明

    此例程展示了作为从机使用I2C中断收发数据。   

2、使用环境

   软件开发环境：
    IDE工具：KEIL MDK-ARM 5.34.0.0
                 IAR EWARM 8.50.1
    
    硬件环境：
     N32A052系列：
            基于评估板N32A052KBQ7_STB V1.0开发


3、使用说明
	
    1、主时钟：64MHz
    2、I2C1 配置：
            SCL   -->  PD12          
            SDA   -->  PD13         
            CLOCK:100KHz
            
    3、USART1配置：
            TX  -->  PA9   
            RX  -->  PA10           
            波特率：115200
        

    4、测试步骤与现象
        a，跳线连接主机I2C1
        b，编译下载代码复位运行
        c，从串口看打印信息，验证结果

4、注意事项
    1.SCL及SDA必须接上拉
    2.I2C从机地址不要使用0xF0

1. Function description

     This example demonstrates the use of I2C interrupts to send and receive data as a slave.

2. Use environment

    Software development environment:
    IDE tool: KEIL MDK-ARM 5.34.0.0
                 IAR EWARM 8.50.1
    
     Hardware environment:
     N32A052 series:
            Developed based on the evaluation board N32A052KBQ7_STB V1.0


3. Instructions for use

     1. Main clock: 64MHz
     2. I2C1 configuration:
             SCL --> PD12
             SDA --> PD13
             CLOCK: 100KHz
            
     3. USART1 configuration:
             TX --> PA9
	     RX --> PA10
             Baud rate: 115200
        

     4. Test steps and phenomena
         a, the jumper wire connects the master I2C1
         b, compile and download the code, reset and run
         c, view the print information from the serial port and verify the result

4. Matters needing attention
     1.SCL and SDA must be pulled up
     2. Do not use 0xF0 for I2C slave addresses