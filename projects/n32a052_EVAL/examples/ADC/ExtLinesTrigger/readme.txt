1、功能说明
    1、ADC规则通道采样PA0、PA1引脚的模拟电压
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
            ADC规则转换结果完成进入中断，中断优先级0
            中断处理接收转换结果到ADCConvertedValue[5]数组，并翻转PA6电平
        3、端口配置：
            PA0选择为模拟功能
            PA1选择为模拟功能
            PC7选择为外部EXTI事件上升沿触发
            PA6选择为通用IO输出
            PB3选择为通用IO输出
        4、ADC：
            ADC规则通道扫描模式、EXTI7触发、12位数据右对齐，转换通道PA0和PA1的模拟电压数据
    使用方法：
        1、编译后打开调试模式，将变量ADCConvertedValue[5]添加到watch窗口观察
        2、PC7连接PB3,通过示波器可观察，PC7上升沿可以触发规则通道数据采样;
    
4、注意事项
    无


1. Function description
    1. The ADC regular channel samples the analog voltage of the PA0 and PA1 pins.
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
            ADC regular conversion result completion will enter interrupt function, interrupt priority level set to 0.
            In the interrupt function,the regular result is read into the ADCConvertedValue[5] array, and flips PA6 level.
        3. Port configuration:
            PA0 is selected as the analog function
            PA1 is selected as the analog function
            PC7 is selected as external EXTI event rising edge trigger
            PA6 is selected as general IO output
            PB3 is selected as general IO output
        4. ADC:
            ADC regular channel scan mode, EXTI7 trigger, 12-bit data right-aligned, conversion of analog voltage data of channels PA0 and PA1
    Instructions:
        1. Open the debug mode after compiling, add the variables ADCConvertedValue[5] to the watch window for observation
        2. PC7 connects to PB3, through the oscilloscope can be observed, the rising edge of PC7 can be triggered by the regular channel data sampling.


4. Matters needing attention
    None
