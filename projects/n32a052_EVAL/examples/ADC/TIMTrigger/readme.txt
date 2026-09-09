1、功能说明
    1、ADC规则采样PA0,PA1引脚的模拟电压，在TIM1 CC1事件下触发采样;
    2、在转换完成中断中读取转换结果
    
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
        2、中断：
            ADC规则通道转换结果完成会进入中断，中断优先级设置为0。
            中断函数中将规则通道的结果读取到ADCConvertedValue[5]数组，并翻转PA6电平
        3、端口配置：
            PA0选择为模拟功能
            PA1选择为模拟功能
            PA6选择为通用IO输出
            PA9选择为TIM1 CH1 PWM输出

        4、ADC：
            ADC TIM1 CC1触发、12位数据右对齐，规则转换通道PA0,PA1的模拟电压数据
        6、TIM：
            TIM1开启CH1输出，CH1用作触发ADC转换 
    使用方法：
        1、编译后打开调试模式，将变量ADCConvertedValue[5]添加到watch窗口观察
        2、通过改变PA0,PA1引脚的电压，在每个CC1事件发生时转换一次规则通道，变量储存在对应数组中, 同时在PA9 可以看到TIM1 CH1的 PWM 波形
    
4、注意事项
    无

1. Function description
    1. The ADC regularly samples the analog voltage of the PA0,PA1 pin, and triggers sampling under the TIM1 CC1 event;
    2. Read the conversion result in the conversion completion interrupt.

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
        2. Interrupt:
            ADC regular conversion result complete will enter interrupt function, interrupt priority level set to 0.
            In the interrupt function, the regular result is read into the ADCConvertedValue[5] array, and the PA6 level is flipped
        3. Port configuration:
            PA0 is selected as the analog function
            PA1 is selected as the analog function
            PA6 is selected as general IO output
            PA9 is selected as TIM1 CH1 PWM output
        5. ADC:
            ADC configuration: TIM1 CC1 trigger, 12-bit data right-aligned, analog voltage data of regular conversion channel PA0,PA1 Pin
        6. TIM:
            TIM1 turns on CH1 output, and CH1 is used to trigger ADC conversion 
    Instructions:
        1. Open the debug mode after compiling and add the variables ADCConvertedValue[5] to the watch window for observation
        2. By changing the voltage of the PA0,PA1 pin,regular channel are converted once every CC1 event occurs, 
            and the variables are stored in the corresponding array.At the same time, you can see the PWM waveform of TIM1 CH1 on PA9

4. Matters needing attention
    None
