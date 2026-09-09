1、功能说明
    此例程展示蜂鸣器模块的用法。
    
2、使用环境

    软件开发环境：KEIL MDK-ARM V5.34.0.0
                 IAR EWARM 8.50.1
    硬件开发环境： 
        N32A052系列：
            基于评估板N32A052KBQX_STB V1.0开发


3、使用说明
    1、时钟源：HSE+PLL
    2、主时钟：64MHz
    3、输出端口：
            BEEPR_OUT: PA13

    4、测试步骤与现象
       a，编译下载代码复位运行
       b，用示波器查看波形，查看输出波形频率

4、注意事项
     1、由于BEEPER输出时钟源为LSI，所以输出波形频率会有一点偏差。
     2、BEEPER输出复用了调试接口PA13，Load时需复位。

1. Function description
    This example shows the usage of the buzzer module.
    
2. Use environment

	Software development environment: KEIL MDK-ARM V5.34.0.0
                                      IAR EWARM 8.50.1
    Hardware development environment:
         N32A052 series:
            Developed based on the evaluation board N32A052KBQX_STB V1.0

3. Instructions for use
     1. Clock source: HSE+PLL
     2. Main clock: 64MHz
     3. Output port：
                BEEPR_OUT: PA13

     4. Test steps and phenomenon
        a. Compile and download the code to reset and run.
        b. Use the oscilloscope to view the waveform and check the output waveform frequency

4. Matters needing attention
    1.Since the BEEPER output clock source is LSI, the output waveform frequency will be slightly deviated.
    2.The BEEPER output reuses the debug interface PA13 and requires a reset during Load.