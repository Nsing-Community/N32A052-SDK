1、功能说明
     1、TIM1 CH2门控TIM1 CH1和TIM3 CH1 TIM3门控TIM4 CH1
2、使用环境
    软件开发环境：KEIL MDK-ARM V5.34.0.0
                 IAR EWARM 8.50.1
    硬件开发环境： 
        N32A052系列：
            基于评估板N32A052KBQX_STB V1.0开发
3、使用说明
    系统配置:
        1、时钟源：
                    HSI=8M,SYS CLK=64M,TIM1 CLK=64M,TIM3 CLK=64M,TIM4 CLK=64M
        2、端口配置：
                    PA9选择为TIM1 CH1输出
                    PA6选择为TIM1 CH2输入
                    PC6选择为TIM3 CH1输出
                    PA10选择为TIM4 CH1输出
        3、TIM：
                    TIM1 CH2 门控TIM1 CH1，门控TIM3 CH1, TIM3门控TIM4 CH1
    使用方法：
        1、编译后打开调试模式，用示波器或者逻辑分析仪观察TIM1 CH1,TIM3 CH1,TIM4 CH1的波形
        2、TIM1 CH2高电平定时器开始计数，低电平停止
4、注意事项
       开发板默认PA9,PA10跳帽接到NSLINK的虚拟串口，若工程中PA9，PA10不作串口，用作其他用途，须拔掉串口跳帽。
	
	
	
1. Function description
     1. TIM1 CH2 gated TIM1 CH1 and TIM3 CH1,TIM3 gated TIM4 CH1
2. Use environment
	Software development environment: KEIL MDK-ARM V5.34.0.0
                                      IAR EWARM 8.50.1
    Hardware development environment:
         N32A052 series:
            Developed based on the evaluation board N32A052KBQX_STB V1.0
3. Instructions for use
    System Configuration;
        1. Clock source:
                    HSI=8M,SYS CLK=64M,TIM1 CLK=64M,TIM3 CLK=64M,TIM4 CLK=64M
        2. Port configuration:
                    PA9 is selected as TIM1 CH1 output
                    PA6 is selected as TIM1 CH2 output
                    PC6 is selected as TIM3 CH1 output
                    PA10 is selected as TIM4 CH1 output
         3. TIM:
                    TIM1 CH2 gated TIM1 CH1, gated TIM3 CH1.TIM3 gated TIM4 CH1
     Instructions:
         1. After compiling, turn on the debug mode, use an oscilloscope or logic analyzer to observe the waveforms of TIM1 CH1, TIM3 CH1, TIM4 CH1
         2. TIM1 CH2 high level timer starts counting, low level stops
4. Matters needing attention
        By default, the PA9 and PA10 jumper caps of the development board are connected to the virtual serial port of NSLINK. If PA9 and PA10 are not used as serial ports in the project, and are used for other purposes, the serial port jumper caps must be unplugged.
	
