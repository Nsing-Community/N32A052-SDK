1、功能说明
    1、COMP1的输出刹车TIM1的互补信号，COMP OUT变低后恢复TIM1波形
    
2、使用环境

    软件开发环境：KEIL MDK-ARM V5.34.0.0
                 IAR EWARM 8.50.1
    硬件开发环境： 
        N32A052系列：
            基于评估板N32A052KBQX_STB V1.0开发
            
3、使用说明
    系统配置；
        1、时钟源：
            HSE=8M,PLL=64M,AHB=64M,APB1=32M,APB2=64M,COMP CLK=32M,TIM1 CLK=64VM
        2、端口配置：
            PA3选择为模拟功能COMP INP
            PA2选择为模拟功能COMP INM
            PB8选择为模拟功能COMP OUT
            PB3选择为IO输出
            PB4选择为IO输出
            PA4选择为TIM1 CH1输出
            PA9选择为TIM1 CH2输出
            PA11选择为TIM1 CH3输出
        3、COMP：
            TIM1开启CH1 CH2 CH3 输出,COMP作为刹车输入
    使用方法：
        1、编译后打开调试模式，将PB3连接到PA3，PB4连接到PA2，利用示波器或者逻辑分析仪观察TIM1输出波形
        2、当软件输出PB3电平大于PB4时，TIM波形消失，相反时，波形正常输出
4、注意事项
    PB8和PC10、PA4和PA6、PA11和PC15为组合引脚，使用其中一个引脚时，另一个引脚要配置成模拟模式，否则会影响功能正常使用


1. Function description
    1. The output of COMP1 brakes the complementary signal of TIM1, and the waveform of TIM1 is restored after COMP OUT goes low.

2. Use environment

    Software development environment: KEIL MDK-ARM V5.34.0.0
                                      IAR EWARM 8.50.1
    Hardware development environment:
         N32A052 series:
            Developed based on the evaluation board N32A052KBQX_STB V1.0

3. Instructions for use
    System Configuration;
        1. Clock source:
            HSE=8M,PLL=64M,AHB=64M,APB1=32M,APB2=64M,COMP CLK=32M,TIM1 CLK=64VM 
        2. Port Configuration:
            PA3 is selected as the analog function COMP INP
            PA2 is selected as the simulation function COMP INM
            PB8 is selected as emulation feature COMP OUT
            PB3 Select IO output
            PB4 select IO output
            PA4 is selected as TIM1 CH1 output
            PA9 is selected as TIM1 CH2 output
            PA11 is selected as TIM1 CH3 output
        3. COMP：
            TIM1 turns on CH1 CH2 CH3 output, COMP is used as brake input
    Usage:
        1. After compiling, turn on the debug mode,connect PB3 to PA3 and PB4 to PA2, use an oscilloscope or logic analyzer to observe the output waveforms of TIM1 
        2. When the software output PB3 level greater than PB4, the TIM waveform disappears, on the contrary, the waveform is output normally
        
4. Matters needing attention
    PB8 & PC10, PA4 & PA6, and PA11 & PC15 are combined pin pairs. When one pin of a pair is in use, the other must be configured to analog mode; otherwise, the normal functionality will be impaired.