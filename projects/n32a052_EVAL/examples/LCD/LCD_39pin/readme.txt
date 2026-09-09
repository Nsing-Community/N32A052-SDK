1、功能说明
    LCD功能演示

2、使用环境
    软件开发环境：KEIL MDK-ARM V5.34.0.0
                 IAR EWARM 8.50.1
    硬件开发环境： 
        N32A052系列：
            基于评估板N32A052KBQX_STB V1.0开发

3、使用说明
    
    系统配置；
        1、时钟源：HSE+PLL
        2、系统时钟：64MHz
        3、LCD端口： 

            SEG:
            PB0:SEG0      PB12:SEG5     PD0:SEG6      PA14:SEG7
            PA13:SEG8    PB4:SEG13     PB8:SEG16     PC5:SEG23
            PC6:SEG24    PC7:SEG25        
            
            COM:
            PD4:COM0    PD5:COM1    PD8:COM4    PD11:COM7

            PWM:PA6

    使用方法：
        1、在KEIL下编译后烧录到开发板，通电，通过示波器观察相对应的COM端和SEG端电压差是否为最大，当某一区段电压差最大时，该区段会被点亮，反之不会。
        2、LCD全亮
        3、COM0-SEG0段点亮
        4、COM0-SEG5段点亮
        5、LCD全灭
        
4、注意事项
    此demo会导致SWD引脚被复用，可以在LCD_GPIO_Init中屏蔽PA13/PA14的复用

1. Function description
	LCD function demonstration
2. Use environment
	Software development environment: KEIL MDK-ARM V5.34.0.0
                                      IAR EWARM 8.50.1
    Hardware development environment:
         N32A052 series:
            Developed based on the evaluation board N32A052KBQX_STB V1.0

3. Instructions for use  
	System configuration;
	1. Clock source: HSE+PLL
	2. System clock: 64MHz
	3. LCD port:
	
            SEG:
            PB0:SEG0      PB12:SEG5     PD0:SEG6      PA14:SEG7
            PA13:SEG8    PB4:SEG13     PB8:SEG16     PC5:SEG23
            PC6:SEG24    PC7:SEG25        
            
            COM:
            PD4:COM0    PD5:COM1    PD8:COM4    PD11:COM7

            PWM:PA6
     
	Usage:
	1.Compile the code in KEIL, then download and program it into the development board. Power on the board, and use an oscilloscope to check whether the voltage difference between the corresponding COM and SEG terminals is at its maximum. When the voltage difference of a certain segment reaches its maximum, the segment will light up; otherwise, it will not.
	2.All LCD segments on
	3.COM0-SEG0 segment lit
	4.COM0-SEG5 segment lit
	5.All LCD segments off
        
4. Matters needing attention
	This demo causes the SWD pin to be multiplexed, you can block PA13/PA14 multiplexing in LCD_GPIO_Init