1、功能说明
    1、ADC采样内部通道Vrefint
    
2、使用环境

    软件开发环境：KEIL MDK-ARM V5.34.0.0
                  IAR EWARM 8.50.1
    硬件开发环境： 
        N32A052系列：
            基于评估板N32A052KBQX_STB V1.0开发

3、使用说明
    系统配置；
        1、时钟源：
            HSI=8M,AHB=64M,APB1=32M,APB2=64M,ADC CLK=64M/16,ADC 1M CLK=HSI/8
        2、ADC：
            ADC连续转换、软件触发、12位数据右对齐，ADC通道16即内部参考电压数据
            
    使用方法：
        1、编译后打开调试模式，将变量ADCConvertedValue,添加到watch窗口观察，这个值就是Vrefint的采样值，换算后约为1.2V.
        
4、注意事项
    无



1. Function description
    1. ADC samples the internal channel Vrefint

2. Use environment

    Software development environment: KEIL MDK-ARM V5.34.0.0
                                      IAR EWARM 8.50.1
    Hardware development environment:
         N32A052 series:
            Developed based on the evaluation board N32A052KBQX_STB V1.0

3. Instructions for use
    System Configuration;
        1. Clock source:
           HSI=8M,AHB=64M,APB1=32M,APB2=64M,ADC CLK=64M/16,ADC 1M CLK=HSI/8
        2. ADC:
           ADC configuration: continuous conversion, software trigger, 12-bit data right-aligned, ADC channel 16 is the analog voltage data of the internal reference voltage.
    Instructions:
        1. Open the debug mode after compiling, add the variables ADCConvertedValue to the watch window for observation，This value is the Vrefint sample value. 
           It is about 1.2V after conversion 
           
4. Matters needing attention
    None

