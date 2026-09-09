1、功能说明
    1、TIM3 CH1 CH2 CH3 CH4输出频率相同占空比不同的PWM
2、使用环境
    软件开发环境：KEIL MDK-ARM V5.34.0.0
                 IAR EWARM 8.50.1
    硬件开发环境： 
        N32A052系列：
            基于评估板N32A052KBQX_STB V1.0开发
3、使用说明
    系统配置:
        1、时钟源：
                    HSI=8M,SYS CLK=64M,TIM2 CLK=64M
        2、端口配置：
                    PC6选择为TIM3的CH1输出
                    PC7选择为TIM3的CH2输出
                    PD5选择为TIM3的CH3输出
                    PD12选择为TIM3的CH4输出
        3、TIM：
                    TIM3 CH1 CH2 CH3 CH4周期相等，占空比不等
    使用方法：
        1、编译后打开调试模式，用示波器或者逻辑分析仪观察TIM3 CH1、CH2、CH3、CH4的波形
        2、程序运行后，产生4路周期相等占空比不同的PWM信号
4、注意事项
    无
	
	
	
1. Function description
    1. TIM3 uses the CH1 CH2 CH3 CH4 CC value to generate a timing interrupt and flip the IO level
2. Use environment
	Software development environment: KEIL MDK-ARM V5.34.0.0
                                      IAR EWARM 8.50.1
    Hardware development environment:
         N32A052 series:
            Developed based on the evaluation board N32A052KBQX_STB V1.0
3. Instructions for use
    System Configuration;
        1. Clock source:
                    HSI=8M,SYS CLK=64M,TIM2 CLK=64M
        2. Port configuration:
                    PC6 is selected as the CH1 output of TIM3
                    PC7 is selected as the CH2 output of TIM3
                    PD5 is selected as the CH3 output of TIM3
                    PD12 is selected as the CH4 output of TIM3
        3. TIM:
                     TIM3 CH1 CH2 CH3 CH4 has the same period, and the duty cycle is not equal
    Instructions:
         1. After compiling, turn on the debug mode, use an oscilloscope or logic analyzer to observe the waveforms of TIM3 CH1, CH2, CH3, CH4
         2. After the program runs, 4 PWM signals with equal period and different duty cycle are generated
4. Matters needing attention
    without