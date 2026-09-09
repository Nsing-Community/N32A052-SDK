﻿1、功能说明
    1、ADC采样内部温度传感器的模拟电压，并转换为温度值 
2、使用环境
		/* 软件开发环境：当前工程使用的软件工具名称及版本号 */
        IDE工具：KEIL MDK-ARM 5.34.0.0
                 IAR EWARM 8.50.1

        /* 硬件环境：工程对应的开发硬件平台 */
        开发板：N32A052CL-STB V1.0
3、使用说明
    系统配置；
        1、时钟源：
                    HSI=8M,AHB=64M,APB1=32M,APB2=64M,ADC CLK=64M/16,ADC 1M CLK=HSI/8
        2、DMA：
                    DMA_CH1通道循环模式搬运一个半字的ADC转换结果到ADCConvertedValue变量
        3、ADC：
                    ADC连续转换、软件触发、12位数据右对齐，转换通道16即内部温度传感器的模拟电压数据
        4、端口配置：
                    PA9选择为USART1的TX引脚
                    PA10选择为USART1的RX引脚
        5、USART：
                    USART1 115200波特率、8位数据位、1位停止位、无奇偶校验位、无硬件流控、发送和接收使能
        6、功能函数：
                    TempValue = TempCal(ADCConvertedValue)函数将温度ADC原始格式数据转为度的单位的格式
    使用方法：
        1、编译后打开调试模式，将变量ADCConvertedValue,TempValue添加到watch窗口观察
        2、将串口工具连接到PA9引脚，并打开串口接收工具
        3、全速运行，可以看到温度变量的数值在常温下接近25度左右，同时串口工具显示实时芯片内的温度值

4、注意事项
    无


1. Function description
    1. ADC samples and converts the analog voltage of the internal temperature sensor and converts it to a temperature value

2. Use environment
    /* Software development environment: the name and version number of the software tool used in the current project */
    Software development environment: KEIL MDK-ARM 5.21.1.0
                                      IAR EWARM 8.50.1
    /* Hardware environment: the development hardware platform corresponding to the project */
    Hardware Environment: 
        Developed based on N32A052CL-STB V1.0

3. Instructions for use
    System Configuration;
        1. Clock source:
                    HSI=8M,AHB=64M,APB1=32M,APB2=64M,ADC CLK=64M/16,ADC 1M CLK=HSI/8
        2. DMA:
                    DMA1_CH1 channel is configuered as circular mode, carries a half-word ADC conversion result to ADCConvertedValue variable
        3. ADC:
                    ADC configuration: continuous conversion, software trigger, 12-bit data right-aligned, conversion channel 16 is the analog voltage data of the internal temperature sensor
        4. Port configuration:
                    PA9 is selected as the TX pin of USART1
                    PA10 is selected as the RX pin of USART1
    Instructions:
        1. Open the debug mode after compiling, add the variables ADCConvertedValue, TempValue to the watch window for observation
        2. Connect the serial port tool to the PA9 pin and open the serial port receiving tool
        3. Running at full speed, you can see that the value of the temperature variable is close to about 25 degrees at room temperature, and the serial port tool displays the temperature value in the real-time chip

4. Matters needing attention
    None