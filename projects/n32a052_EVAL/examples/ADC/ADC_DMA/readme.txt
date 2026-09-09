1、功能说明
    1、ADC采样转换PA0 PA1 PA2 PA3 PA4引脚的模拟电压
    2、其中ADC转换结果通过DMA_CH1通道读取到变量ADCConvertedValue
    
2、使用环境

    软件开发环境：KEIL MDK-ARM V5.34.0.0
                 IAR EWARM 8.50.1
    硬件开发环境： 
        N32A052系列：
            基于评估板N32A052KBQX_STB V1.0开发

3、使用说明
    系统配置；
        1、时钟源：
            HSI=8M,AHB=64M,APB1=32M,APB2=64M,TIM =64M,DMA =64M, ADC CLK=64M/16,ADC 1M CLK=HSI/8
        2、端口配置：
            PA0选择为模拟功能ADC转换通道0
            PA1选择为模拟功能ADC转换通道1
            PA2选择为模拟功能ADC转换通道2
            PA3选择为模拟功能ADC转换通道3
            PA4选择为模拟功能ADC转换通道4
        3、ADC：
            TIM1_CC1事件触发转换、12位数据右对齐，转换PA0 PA1 PA2 PA3 PA4的模拟电压数据
        4、DMA：
            DMA_CH1通道正常模式搬运5个字的ADC转换结果到ADCConvertedValue[5]变量,该变量低半字有效。
    使用方法：
        1、编译后打开调试模式，将变量ADCConvertedValue添加到watch窗口观察
        2、通过改变PA0 PA1 PA2 PA3 PA4引脚的电压，可以看到转换结果变量同步改变
4、注意事项
    无


1. Function description
    1. ADC samples and converts the analog voltage of PA0 PA1 PA2 PA3 PA4 pin
    2. ADC conversion result is read to variable ADCConvertedValue through DMA_CH1 channel

2. Use environment
    Software development environment: KEIL MDK-ARM V5.34.0.0
                                      IAR EWARM 8.50.1
    Hardware development environment:
         N32A052 series:
            Developed based on the evaluation board N32A052KBQX_STB V1.0

3. Instructions for use
    System Configuration;
        1. Clock source:
            HSI=8M,AHB=64M,APB1=32M,APB2=64M,TIM =64M,DMA =64M, ADC CLK=64M/16,ADC 1M CLK=HSI/8
        2. Port configuration:
            PA0 is selected as analog function, ADC conversion channel 0
            PA1 is selected as analog function, ADC conversion channel 1
            PA2 is selected as analog function, ADC conversion channel 2
            PA3 is selected as analog function, ADC conversion channel 3
            PA4 is selected as analog function, ADC conversion channel 4
        3. ADC:
            ADC configuration: TIM1_CC1 event trigger, 12-bit data is right-aligned, and converts the analog voltage data of PA0 PA1 PA2 PA3 PA4
        4. DMA:
            DMA_CH1 channel is configuered as normal mode, carries 5 words of ADC conversion result to the ADCConvertedValue[5] variable.
            The variable is valid in the lower half of the word.
    Instructions:
        1. Open the debug mode after compiling and add the variable ADCConvertedValue[5] to the watch window for observation
        2. By changing the voltage of the PA0 PA1 PA2 PA3 PA4 pin, you can see that the conversion result variable changes synchronously

4. Matters needing attention
    none