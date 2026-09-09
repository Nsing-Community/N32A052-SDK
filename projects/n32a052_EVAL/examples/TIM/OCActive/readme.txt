1、功能说明
    1、TIM3 CH1 CH2 CH3 CH4 达到CC值后，输出ACTIVE电平
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
        2、端口配置：
                    PC6选择为TIM3 CH1输出
                    PC7选择为TIM3 CH2输出
                    PD5选择为TIM3 CH3输出
                    PD12选择为TIM3 CH4输出
                    PA3选择为IO 输出
    使用方法：
        1、编译后打开调试模式，用示波器或者逻辑分析仪观察TIM3 CH1 CH2 CH3 CH4的波形
        2、定时器运行到CC1 CC2 CC3 CC4之后，对应通道的输出变为Active
4、注意事项
    无
	
	
	
1. Function description
     1. After TIM3 CH1 CH2 CH3 CH4 reaches the CC value, it outputs ACTIVE level
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
        2. Port configuration:
                     PC6 is selected as TIM3 CH1 output
                     PC7 is selected as TIM3 CH2 output
                     PD5 is selected as TIM3 CH3 output
                     PD12 is selected as TIM3 CH4 output
                     PA3 is selected as IO output
     Instructions:
         1. After compiling, turn on the debug mode, use an oscilloscope or logic analyzer to observe the waveform of TIM3 CH1 CH2 CH3 CH4
         2. After the timer runs to CC1 CC2 CC3 CC4, the output of the corresponding channel becomes Active
4. Matters needing attention
     without