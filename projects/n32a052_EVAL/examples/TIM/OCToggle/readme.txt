1、功能说明
    1、TIM3 CH1 CH2 CH3 CH4 达到CC值后输出翻转，并且比较值累加
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
                    TIM3 比较中断打开
        3、端口配置：
                    PC6选择为TIM3的CH1输出
                    PC7选择为TIM3的CH2输出
                    PD5选择为TIM3的CH3输出
                    PD12选择为TIM3的CH4输出
        4、TIM：
                    TIM3 配置好CH1 CH2 CH3 CH4的比较值输出翻转，并打开比较中断
    使用方法：
        1、编译后打开调试模式，用示波器或者逻辑分析仪观察TIM3 的CH1 CH2 CH3 CH4的波形
        2、每当达到比较值时，输出翻转，并且再增加同样的比较值，波形占空比为50%
4、注意事项
    无
	
	
	
1. Function description
    1. When TIM3 CH1 CH2 CH3 CH4 reaches the CC value, the output is reversed, and the comparison value is accumulated
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
                    TIM3 compare interrupt is turned on
        3. Port configuration:
                    PC6 is selected as the CH1 output of TIM3
                    PC7 is selected as the CH2 output of TIM3
                    PD5 is selected as the CH3 output of TIM3
                    PD12 is selected as the CH4 output of TIM3
        4. TIM:
                    TIM3 configures the comparison value output of CH1, CH2, CH3, CH4, and turns on the comparison interrupt
    Instructions:
        1. After compiling, turn on the debug mode and use an oscilloscope or logic analyzer to observe the waveform of CH1 CH2 CH3 CH4 of TIM3
        2. Whenever the comparison value is reached, the output is reversed, and the same comparison value is increased again, and the waveform duty cycle is 50%
4. Matters needing attention
    without