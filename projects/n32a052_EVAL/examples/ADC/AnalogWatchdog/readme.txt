1、功能说明
    1、ADC采样转换PA0引脚的模拟电压，如果超过模拟看门狗定义的阈值范围，则跳入中断程序
    
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
            ADC连续转换、软件触发、12位数据右对齐
        3、端口配置：
            PA0选择为模拟功能
        4、中断：
            ADC模拟看门狗中断打开，优先级0
    使用方法：
        1、编译后打开调试模式，将变量gCntAwdg添加到watch窗口观察
        2、改变PA0引脚电压值，当电压值超出模拟看门狗定义的0x300（即0.6V）到0xB00（即2.26V）范围外，则进入一次中断，变量做累加操作.
4、注意事项
    无


1. Function description
    1.ADC samples and converts the analog voltage of the PA0 pin. If it exceeds the threshold range defined by the analog watchdog, then jump into the interrupt program

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
            ADC configuration: continuous conversion, software trigger, 12-bit data right-aligned.
        3. Port configuration:
            PA0 is selected as analog function
        4. Interrupt:
            ADC analog watchdog interrupt is turned on, priority 0
    Instructions:
        1. Open the debug mode after compiling and add the variable gCntAwdg to the watch window for observation
        2. Change the voltage value of the PA0 pin. When the voltage value exceeds the range defined by the analog watchdog from 0x300 (ie 0.6V) to 0xB00 (ie 2.26V), 
           an interrupt is entered, and the variable is accumulated.

4. Matters needing attention
    None
