1、功能说明
    1、TIM4 CH2上升沿触发CH1输出一个单脉冲
2、使用环境
    软件开发环境：KEIL MDK-ARM V5.34.0.0
                 IAR EWARM 8.50.1
    硬件开发环境： 
        N32A052系列：
            基于评估板N32A052KBQX_STB V1.0开发
3、使用说明
    系统配置:
        1、时钟源：
                    HSI=8M,SYS CLK=64M,TIM4 CLK=64M
        2、端口配置：
                    PD11选择为TIM4的CH1输出
                    PA10选择为TIM4的CH2输入
                    PA3选择为IO输出
        3、TIM：
                    TIM4 配置CH2上升沿触发CH1输出一个单脉冲
    使用方法：
        1、编译后打开调试模式，PA3连接PA10，用示波器或者逻辑分析仪观察TIM4 的CH1 的波形
        2、通过调试窗口配置gSendTrigEn=1，程序发送PA3的上升沿，TIM4 CH1输出一个单脉冲
4、注意事项
       开发板默认PA9,PA10跳帽接到NSLINK的虚拟串口，若工程中PA9，PA10不作串口，用作其他用途，须拔掉串口跳帽。
	
	
	
1. Function description
     1. The rising edge of TIM4 CH2 triggers CH1 to output a single pulse
2. Use environment
	Software development environment: KEIL MDK-ARM V5.34.0.0
                                      IAR EWARM 8.50.1
    Hardware development environment:
         N32A052 series:
            Developed based on the evaluation board N32A052KBQX_STB V1.0
3. Instructions for use
    System Configuration;
        1. Clock source:
                    HSI=8M,SYS CLK=64M,TIM4 CLK=64M
         2. Port configuration:
                     PD11 is selected as the CH1 output of TIM4
                     PA10 is selected as the CH2 input of TIM4
                     PA3 is selected as IO output
         3. TIM:
                     TIM4 configures the rising edge of CH2 to trigger CH1 to output a single pulse
     Instructions:
         1. After compiling, turn on the debug mode, connect PA3 to PA10, and use an oscilloscope or logic analyzer to observe the waveform of CH1 of TIM4
         2. Configure gSendTrigEn=1 in the debug window,the program sends the rising edge of PA3, and TIM4 CH1 outputs a single pulse
4. Matters needing attention
        By default, the PA9 and PA10 jumper caps of the development board are connected to the virtual serial port of NSLINK. If PA9 and PA10 are not used as serial ports in the project, and are used for other purposes, the serial port jumper caps must be unplugged.