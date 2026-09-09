1、功能说明

    1、此例程展示 IO 控制 LED 闪烁


2、使用环境

    软件开发环境：KEIL MDK-ARM V5.34.0.0
                 IAR EWARM 8.50.1
    硬件开发环境： 
        N32A052系列：
            基于评估板N32A052KBQX_STB V1.0开发

3、使用说明

    /* 描述相关模块配置方法；例如:时钟，I/O等 */
          1、 SystemClock：64MHz
          2、 GPIO：PB0、PB4、PD11 控制 LED(D1、D2、D3) 闪烁

    /* 描述Demo的测试步骤和现象 */
        1.编译后下载程序复位运行；
        2. LED(D1、D2、D3) 闪烁；

4、注意事项
    无


1. Function description

    1. This routine shows the IO control LED blinking
	
2. Use environment

	Software development environment: KEIL MDK-ARM V5.34.0.0
                                      IAR EWARM 8.50.1
    Hardware development environment:
         N32A052 series:
            Developed based on the evaluation board N32A052KBQX_STB V1.0
			
3. Instructions for use

    System Configuration;
        1. SystemClock：64MHz
        2. GPIO: PB0, PB4, PD11 control LED (D1, D2, D3) to blink
    Instructions:
        1. After compiling, download the program to reset and run
        2. LED (D1, D2, D3) to blinking
		
4. Matters needing attention
    No