1、功能说明
    1、systick 100ms触发TIM1输出6步换相波形
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
                    TIM1 COM事件中断打开，优先级1
                    Systick 100ms中断，优先级0
        3、端口配置：
                    PD4选择为TIM1 CH1输出
                    PA9选择为TIM1 CH2输出
                    PA10选择为TIM1 CH4输出
                    PB13选择为TIM1 CH1N输出
                    PA6选择为TIM1 CH2N输出
                    PB12选择为TIM1 CH4N输出
        4、TIM：
                    TIM1 6路(3对)互补冻结输出模式，无刹车，开COM中断
    使用方法：
        1、编译后打开调试模式，用示波器或者逻辑分析仪观察TIM1的输出波形
        2、每隔100ms systick触发COM中断，在TIM的COM中断里面输出AB AC BC BA CA CB的6步换相波形
4、注意事项
       开发板默认PA9,PA10跳帽接到NSLINK的虚拟串口，若工程中PA9，PA10不作串口，用作其他用途，须拔掉串口跳帽。
	
	
	
1. Function description
    1. systick triggers TIM1 for 100ms to output 6-step commutation waveform
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
        2. Interrupt:
                    TIM1 COM event interrupt on, priority 1
                    Systick 100ms interrupt, priority 0
        3. Port configuration:
                    PD4 is selected as TIM1 CH1 output
                    PA9 is selected as TIM1 CH2 output
                    PA10 is selected as TIM1 CH4 output
                    PB13 is selected as TIM1 CH1N output
                    PA6 is selected as TIM1 CH2N output
                    PB12 is selected as TIM1 CH4N output
        4. TIM:
                    TIM1 6-output complementary PWM (3 pairs), freeze output mode, no brake, open COM interrupt
    Instructions:
        1. Open the debug mode after compiling, and observe the output waveform of TIM1 with an oscilloscope or logic analyzer
        2. The systick triggers the COM interrupt every 100ms, and outputs the 6-step commutation waveform of AB AC BC BA CA CB in the COM interrupt of the TIM
4. Matters needing attention
        By default, the PA9 and PA10 jumper caps of the development board are connected to the virtual serial port of NSLINK. If PA9 and PA10 are not used as serial ports in the project, and are used for other purposes, the serial port jumper caps must be unplugged.

