1、功能说明
    1、TIM2 周期门控TIM3 TIM4
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
                    PA10选择为TIM2的CH1输出
                    PC6选择为TIM3的CH1输出
                    PD11选择为TIM4的CH1输出
        3、TIM：
                    TIM2 周期触发门控TIM3 TIM4的CH1,即TIM3为10倍周期TIM2，即TIM4为5倍周期TIM2
    使用方法：
        1、编译后打开调试模式，用示波器或者逻辑分析仪观察TIM2 CH1、TIM3 CH1、TIM4 CH1的波形
        2、TIM4周期5倍于TIM2，TIM3周期10倍于TIM2
4、注意事项
       开发板默认PA9,PA10跳帽接到NSLINK的虚拟串口，若工程中PA9，PA10不作串口，用作其他用途，须拔掉串口跳帽。
	
	
	
1. Function description
     1. TIM2 cycle gated TIM3 TIM4
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
                     PA10 is selected as CH1 output of TIM2
                     PC6 is selected as the CH1 output of TIM3
                     PD11 is selected as the CH1 output of TIM4
         3. TIM:
                     TIM2 cycle triggers CH1 of gating TIM3 TIM4, that is, TIM3 is 10 times period TIM2, that is, TIM4 is 5 times period TIM2
     Instructions:
         1. After compiling, turn on the debug mode and use an oscilloscope or logic analyzer to observe the waveforms of TIM2 CH1, TIM3 CH1, and TIM4 CH1
         2. The cycle of TIM4 is 5 times that of TIM2, and the cycle of TIM3 is 10 times that of TIM2.
4. Matters needing attention
        By default, the PA9 and PA10 jumper caps of the development board are connected to the virtual serial port of NSLINK. If PA9 and PA10 are not used as serial ports in the project, and are used for other purposes, the serial port jumper caps must be unplugged.