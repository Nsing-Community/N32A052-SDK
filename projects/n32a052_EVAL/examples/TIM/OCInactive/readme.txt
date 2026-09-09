1、功能说明
    1、TIM2 CH1 CH2 CH3 CH4 达到CC值后，对应拉低PC6 PC7 PD5 PD12的IO电平
2、使用环境
    软件开发环境：KEIL MDK-ARM V5.34.0.0
                 IAR EWARM 8.50.1
    硬件开发环境： 
        N32A052系列：
            基于评估板N32A052KBQX_STB V1.0开发
3、使用说明
    系统配置:
        1、时钟源：
                    HSI=8M,SYS CLK=64M,TIM3 CLK=32M
        2、中断：
                    TIM2 比较中断打开
        3、端口配置：
                    PC6选择为IO 输出
                    PC7选择为IO 输出
                    PD5选择为IO 输出
                    PD12选择为IO 输出
        4、TIM：
                    TIM2 配置好CH1 CH2 CH3 CH4的比较值，并打开比较中断
    使用方法：
        1、编译后打开调试模式，用示波器或者逻辑分析仪观察PC6 PC7 PD5 PD12的波形
        2、定时器运进入CC1 CC2 CC3 CC4中断后,对应拉低PC6 PC7 PD5 PD12的IO
4、注意事项
    无
	
	
	
1. Function description
    1. After TIM2 CH1 CH2 CH3 CH4 reaches the CC value, correspondingly pull down the IO level of PC6, PC7, PD5, and PD12
2. Use environment
	Software development environment: KEIL MDK-ARM V5.34.0.0
                                      IAR EWARM 8.50.1
    Hardware development environment:
         N32A052 series:
            Developed based on the evaluation board N32A052KBQX_STB V1.0
3. Instructions for use
    System Configuration;
        1. Clock source:
                    HSI=8M,SYS CLK=64M,TIM3 CLK=32M
        2. Interruption:
                    TIM2 compare interrupt is turned on
        3. Port configuration:
                    PC6 is selected as IO output
                    PC7 is selected as IO output
                    PD5 is selected as IO output
                    PD12 is selected as IO output
        4. TIM:
                    TIM2 configures the comparison value of CH1, CH2, CH3, CH4, and turns on the comparison interrupt
    Instructions:
        1. After compiling, turn on the debug mode, and use an oscilloscope or logic analyzer to observe the waveforms of PC6, PC7, PD5, and PD12
        2. After the timer enters the CC1 CC2 CC3 CC4 interrupt, it will correspondingly pull down the IO of PC6 PC7 PD5 PD12
4. Matters needing attention
    without