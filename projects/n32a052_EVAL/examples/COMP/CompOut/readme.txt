1、功能说明
    1、COMP1的输出PB8受输入INP PA3和INM PA2的影响
    
2、使用环境

    软件开发环境：KEIL MDK-ARM V5.34.0.0
                 IAR EWARM 8.50.1
    硬件开发环境： 
        N32A052系列：
            基于评估板N32A052KBQX_STB V1.0开发

3、使用说明
    系统配置；
        1、时钟源：
            HSI=8M,AHB=64M,APB1=32M, COMP_CLK=32M ,COMP_FILCLK=64M
        2、端口配置：
            PA3选择为模拟功能COMP INP
            PA2选择为模拟功能COMP INM
            PB8选择为模拟功能COMP OUT
            PB3选择为IO输出
            PB4选择为IO输出
        3、COMP：
            COMP1输入PA3，PA2，输出PB8
    使用方法：
        1、编译后打开调试模式，将PB3连接到PA3，PB4连接到PA2，利用示波器或者逻辑分析仪观察PB8输出波形
        2、当软件输出PB3电平大于PB4时，PB8输出高电平，相反时，输出低电平
4、注意事项
        1.PB8和PC10引脚为组合引脚，只能同时使用其中一个IO的功能，且在同一个Pin上的其他IO必须配置成模拟模式，以免影响正在使用的IO


1. Function description
    1. COMP1 output PB8 is affected by INP PA3 and INM PA2

2. Use environment
    Software development environment: KEIL MDK-ARM V5.34.0.0
                                      IAR EWARM 8.50.1
    Hardware development environment:
         N32A052 series:
            Developed based on the evaluation board N32A052KBQX_STB V1.0

3. Instructions for use
    System Configuration;
        1. Clock source:
            HSI=8M,AHB=64M,APB1=32M, COMP_CLK=32M ,COMP_FILCLK=64M
        2. Port Configuration:
            PA3 is selected as the analog function COMP INP
            PA2 is selected as the simulation function COMP INM
            PB8 is selected as emulation feature COMP OUT
            PB3 Select IO output
            PB4 select IO output
        3. COMP：
            COMP1 inputs PA3, PA2, and outputs PB8
    Usage:
        1. After compiling, open the debugging mode, connect PB3 to PA3 and PB4 to PA2, 
          and observe the output waveform of PB8 using oscilloscope or logic analyzer.
        2. When the software outputs PB3 level greater than PB4, PB68outputs high level; otherwise, PB8 outputs low level 
        
4. Matters needing attention
        1.Pins PB8 and PC10 are combined pins; only the function of one IO can be used at a time, and all other IOs on the same pin must be configured to analog mode to avoid interfering with the IO in use.
