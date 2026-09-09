1、功能说明
    1、TIM1 CH3 CH3N互补信号每6个周期改变一次占空比
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
                    PA11选择为TIM1 CH3输出
                    PA4选择为TIM1 CH3N输出
        3、TIM：
                    TIM1 CH3 CH3N互补输出，每6个周期触发一次DMA传输
        4、DMA：
                    DMA1_CH5通道循环环模式搬运3个半字SRC_Buffer[3]变量到TIM1 CCDAT3寄存器
    使用方法：
        1、编译后打开调试模式，用示波器或者逻辑分析仪观察TIM1 CH3 CH3N的波形
        2、TIM1的6个周期改变一次CH3 CH3N的占空比，循环改变
4、注意事项
    无
	
	
	
1. Function description
    1. TIM1 CH3 CH3N complementary signal changes duty cycle every 6 cycles
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
            PA11 selected as TIM1 CH3 Output
            PA4 selected as TIM1 CH3N Output
        3. TIM:
            TIM1 CH3 CH3N complementary output triggers DMA transmission every 6 cycles
        4. DMA:
            DMA1_ CH5 Channel circular mode handling 3 half-Word SRC_ Buffer[3] variable to TIM1 CCDAT3 register
     Instructions:
         1. After compiling, turn on the debug mode, use an oscilloscope or logic analyzer to observe the waveform of TIM1 CH3 CH3N
         2. Change the duty cycle of CH3 and CH3N once in 6 cycles of TIM1, and change cyclically
4. Matters needing attention
    None
