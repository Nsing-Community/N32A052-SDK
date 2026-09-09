1、功能说明
    1、TIM3 CH2上升沿计算频率
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
                    TIM3 CH2上升沿中断打开
        3、端口配置：
                    PC7选择为TIM3 CH2输入
                    PA3选择为IO 输出
        4、TIM：
                    TIM3 CH2 上升沿捕获中断打开
    使用方法：
        1、编译后打开调试模式，连接PA3与PC7，将变量TIM3Freq添加到watch窗口
        2、通过调试窗口修改gOnePulsEn为1，PA3会有电平翻转
        3、程序控制PA3电平翻转后，查看TIM3Freq计算的频率值
4、注意事项
        本例程可捕获的上升沿间隔时间最大为65536*TIM3_CLK
	
	
	
1. Function description
     1. TIM3 CH2 rising edge calculation frequency
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
                     TIM3 CH2 rising edge interrupt is turned on
         3. Port configuration:
                     PC7 is selected as TIM3 CH2 input
                     PA3 is selected as IO output
         4. TIM:
                     TIM3 CH2 rising edge capture interrupt is turned on
     Instructions:
         1. After compiling, open the debug mode, connect PA3 and PC7, and add the variable TIM3Freq to the watch window
         2. Modify gOnePulsEn to 1 in the debug mode and flip the PA3 pin level
         3. After the program controls the level of PA3 to flip, check the frequency value calculated by TIM3Freq
4. Matters needing attention
     The maximum time between rising edges that can be captured by this demo is 65536 * TIM3_CLK