1、功能说明
    1、TIM3 CH2捕获引脚通过CH1下降沿和CH2上升沿计算占空比和频率
2、使用环境
    软件开发环境：KEIL MDK-ARM V5.34.0.0
                 IAR EWARM 8.50.1
    硬件开发环境： 
        N32A052系列：
            基于评估板N32A052KBQX_STB V1.0开发
3、使用说明
    系统配置:
        1、时钟源：
                    HSI=8M,SYS CLK=64M,TIM3 CLK=64M
        2、中断：
                    TIM3 CC2比较中断打开
        3、端口配置：
                    PC7选择为TIM3 CH2输入
                    PA3选择为IO 输出
        4、TIM：
                    TIM3 CH1下降沿捕获CH2信号，CH2上升沿捕获CH2信号
    使用方法：
        1、编译后打开调试模式，连接PA3与PC7，将Frequency、DutyCycle添加到watch窗口
        2、程序运行后，PA3发送的脉冲数据可以被捕获到占空比和频率到变量
4、注意事项
       本例程可捕获的最大间隔时间为65536*TIM3_CLK
	
	
	
1. Function description
     1. TIM3 CH2 capture pin calculates the duty cycle and frequency through the falling edge of CH1 and the rising edge of CH2
2. Use environment
	Software development environment: KEIL MDK-ARM V5.34.0.0
                                      IAR EWARM 8.50.1
    Hardware development environment:
         N32A052 series:
            Developed based on the evaluation board N32A052KBQX_STB V1.0
3. Instructions for use
    System Configuration;
        1. Clock source:
                    HSI=8M,SYS CLK=64M,TIM3 CLK=64M
         2. Interruption:
                     TIM3 CC2 compare interrupt is turned on
         3. Port configuration:
                     PC7 is selected as TIM3 CH2 input
                     PA3 is selected as IO output
         4. TIM:
                     TIM3 CH1 falling edge captures CH2 signal, CH2 rising edge captures CH2 signal
     Instructions:
         1. After compiling, open the debug mode, connect PA3 and PC7, and add Frequency and DutyCycle to the watch window
         2. After the program runs, the pulse data sent by PA3 can be captured to the duty cycle and frequency to the variable
4. Matters needing attention
     The maximum interval time that can be captured by this demo is 65536*TIM3_CLK