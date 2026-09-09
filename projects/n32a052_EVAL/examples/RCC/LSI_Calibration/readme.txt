1、功能说明
    1、TIM2 CH3上升沿计算LSI频率，通过LSI Trim校准LSI时钟，可用于LSI纠偏


2、使用环境
    软件开发环境： KEIL MDK-ARM 5.34.0.0
                 IAR EWARM 8.50.1
    硬件环境：      
     N32A052系列：
            基于评估板N32A052KBQ7_STB V1.0开发

3、使用说明
    系统配置:
        1、时钟源：
                    HSI=8M,PLL=64M,AHB=64M,APB1=32M,APB2=64M,TIM2 CLK=64M
        2、中断：
                    TIM2 CH3上升沿中断打开
        3、端口配置：
                    LSI配置为为TIM2 CH3输入
                    PB3选择为MCO 输出
        4、TIM：
                    TIM2 CH3 上升沿捕获中断打开
    使用方法：   
        1、编译后下载进芯片，通过示波器抓取PB3引脚波形，观察频率

4、注意事项
	无
	
	
	
1. Function description
     1. TIM2 CH3 rising edge calculates LSI frequency, calibrates LSI clock through LSI Trim, available for LSI deskew.

2. Use environment
    Software development environment: KEIL MDK-ARM 5.34.0.0
                                      IAR EWARM 8.50.1
    Hardware environment: 
     N32A052 series:
            Developed based on the evaluation board N32A052KBQ7_STB V1.0

3. Instructions for use
    System Configuration;
        1. Clock source:
                    HSI=8M,PLL=64M,AHB=64M,APB1=32M,APB2=64M,TIM2 CLK=64M
         2. Interruption:
                     TIM2 CH3 rising edge interrupt is turned on
         3. Port configuration:
                     LSI is configured as a TIM2 CH3 input
                     PB3 is selected as MCO output
         4. TIM:
                     TIM2 CH3 rising edge capture interrupt is turned on
     Instructions:
         1. After compiling and downloading into the chip, grab the PB3 pin waveform through an oscilloscope and observe the frequency

4. Matters needing attention
     without
	
