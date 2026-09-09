1、功能说明
    1、TIM1 利用更新中断，产生定时翻转IO
2、使用环境
    软件开发环境：KEIL MDK-ARM V5.34.0.0
                 IAR EWARM 8.50.1
    硬件开发环境： 
        N32A052系列：
            基于评估板N32A052KBQX_STB V1.0开发
3、使用说明
    系统配置:
        1、时钟源：
                    HSI=8M,SYS CLK=64M,TIM1 CLK=64M
        2、中断：
            TIM1 更新中断打开
        3、端口配置：
            PC6选择为IO输出
        4、TIM：
            TIM1使能周期中断
    使用方法：
        1、编译后打开调试模式，用示波器或者逻辑分析仪观察PC6的波形
        2、程序运行后，TIM1的周期中断来临翻转PC6电平
4、注意事项
    无
	
	
	
	
	
1. Function description
     1. TIM1 uses the update interrupt to generate timing rollover IO
2. Use environment
	Software development environment: KEIL MDK-ARM V5.34.0.0
                                      IAR EWARM 8.50.1
    Hardware development environment:
         N32A052 series:
            Developed based on the evaluation board N32A052KBQX_STB V1.0
3. Instructions for use
    System Configuration;
         1. Clock source:
             HSI=8M,SYS CLK=64M,TIM1 CLK=64M
         2. Interruption:
             TIM1 update interrupt is turned on
         3. Port configuration:
             PC6 is selected as IO output
         4. TIM:
             TIM1 enables periodic interrupts
     Instructions:
         1. After compiling, turn on the debug mode and observe the waveform of PC6 with an oscilloscope or logic analyzer
         2. After the program runs, the periodic interrupt of TIM1 comes to flip the PC6 level
4. Matters needing attention
     without