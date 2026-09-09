1、功能说明
    1、ADC采样转换PB0 PB12引脚的模拟电压
    2、采用软件触发一次，采集一次的方式
    
2、使用环境

    软件开发环境：KEIL MDK-ARM V5.34.0.0
                 IAR EWARM 8.50.1
    硬件开发环境： 
        N32A052系列：
            基于评估板N32A052KBQX_STB V1.0开发

3、使用说明
    系统配置；
        1、时钟源：
            HSI=8M,AHB=64M,APB2=64M,APB1=32M,ADC CLK=64M/16,ADC 1M CLK=HSI/8 
        2、端口配置：
            PB0选择为模拟功能ADC转换通道0
            PB12选择为模拟功能ADC转换通道1
        3、ADC：
            ADC软件触发转换、12位数据右对齐，转换PB0 PB12的模拟电压数据
    使用方法：
        1、编译后打开调试模式，将变量ADCConvertedValue添加到watch窗口观察
        2、通过改变PB0 PB12引脚的电压，可以看到转换结果变量同步改变
4、注意事项
    无



1. Function description
    1. ADC samples and converts the analog voltage of PB0 PB12 pin
    2. Use software to trigger once and collect once

2. Use environment
    Software development environment: KEIL MDK-ARM V5.34.0.0
                                      IAR EWARM 8.50.1
    Hardware development environment:
         N32A052 series:
            Developed based on the evaluation board N32A052KBQX_STB V1.0

3. Instructions for use
    System Configuration;
        1. Clock source:
            HSI=8M,AHB=64M,APB1=32M,APB2=64M,ADC CLK=64M/16,ADC 1M CLK=HSI/24
        2. Port configuration:
            PB0 is selected as analog function, ADC conversion channel 0
            PB12 is selected as analog function, ADC conversion channel 1
        3. ADC:
            ADC configuration: software trigger, 12-bit data is right-aligned, and converts the analog voltage data of PB0 PB12 
    Instructions:
        1. Open the debug mode after compiling and add the variable ADCConvertedValue to the watch window for observation
        2. By changing the voltage of the PB0 PB12 pin, you can see that the conversion result variable changes synchronously

4. Matters needing attention
    None