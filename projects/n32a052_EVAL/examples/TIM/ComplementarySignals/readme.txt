1、功能说明
    1、TIM1输出3对互补波形
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
        2、端口配置：
                    PD4选择为TIM1 CH1输出
                    PA9选择为TIM1 CH2输出
                    PA10选择为TIM1 CH4输出
                    PB13选择为TIM1 CH1N输出
                    PA6选择为TIM1 CH2N输出
                    PB12选择为TIM1 CH4N输出
                    PA1选择为刹车输入
        3、TIM：
                    TIM1 6路(3对)互补输出，带死区，PA1刹车
    使用方法：
        1、编译后打开调试模式，用示波器或者逻辑分析仪观察TIM1的波形
        2、PA1拉低可观察到4对互补PWM，PA1拉高PWM消失
4、注意事项
       开发板默认PA9,PA10跳帽接到NSLINK的虚拟串口，若工程中PA9，PA10不作串口，用作其他用途，须拔掉串口跳帽。
	
	
	
1. Function description
     1. TIM1 outputs 3 complementary waveforms
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
        2. Port configuration:
                    PD4 is selected as TIM1 CH1 output
                    PA9 is selected as TIM1 CH2 output
                    PA10 is selected as TIM1 CH4 output
                    PB13 is selected as TIM1 CH1N output
                    PA6 is selected as TIM1 CH2N output
                    PB12 is selected as TIM1 CH4N output
                    PA1 is selected as break input
         3. TIM:
                     TIM1 6-output complementary PWM (3 pairs) with dead zone, PA1 is brake input
     Instructions:
         1. After compiling, turn on the debug mode, and use an oscilloscope or logic analyzer to observe the waveform of TIM1
         2. When PA1 is low, 3 complementary PWM can be observed, and when PA1 is high, PWM disappears
4. Matters needing attention
        By default, the PA9 and PA10 jumper caps of the development board are connected to the virtual serial port of NSLINK. If PA9 and PA10 are not used as serial ports in the project, and are used for other purposes, the serial port jumper caps must be unplugged.
	
