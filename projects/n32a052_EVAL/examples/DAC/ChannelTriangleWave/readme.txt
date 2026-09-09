1、功能说明
    1、TIM4周期触发DAC 输出三角波数据，在PB13输出三角波形
    
2、使用环境

    软件开发环境：KEIL MDK-ARM V5.34.0.0
                 IAR EWARM 8.50.1
    硬件开发环境： 
        N32A052系列：
            基于评估板N32A052KBQX_STB V1.0开发

3、使用说明
    系统配置；
        1、时钟源：
            HSI=8M,AHB=64M,APB1=32M DAC_CLK = 32M
       2、端口配置：
            PB13选择为模拟功能DAC OUT
        3、TIM：
            TIM4 更新事件作为触发输出给DAC
        4、DAC：
            DAC选择TIM4 TRGO信号触发，使能三角波幅度2048，基值0x000
    使用方法：
        1、编译后打开调试模式，利用示波器观察PB13输出波形
        2、全速运行时，TIM4的每个周期触发PB13的一个数据，形成三角波
4、注意事项
    无


1. Function description
    1. TIM4 periodically triggers DAC to output triangular wave data, and outputs triangular waveform in PB13

2. Use environment

    Software development environment: KEIL MDK-ARM V5.34.0.0
                                      IAR EWARM 8.50.1
    Hardware development environment:
         N32A052 series:
            Developed based on the evaluation board N32A052KBQX_STB V1.0


3. Instructions for use
    System Configuration;
        1. Clock source:
             HSI=8M,AHB=64M,APB1=32M DAC_CLK = 32M
        2. Port configuration:
             PB13 is selected as analog function, DAC OUT
        3. TIM:
             TIM4 update event as trigger output to DAC
        4. DAC:
             DAC selects TIM4 TRGO signal trigger, enables triangle wave amplitude 2048, base value 0x000
    Instructions:
        1. Open the debug mode after compiling, and use the oscilloscope to observe the output waveform of the PB13
        2. When running at full speed, each cycle of TIM4 triggers a data of PB13 to form a triangular wave

4. Matters needing attention
    none
