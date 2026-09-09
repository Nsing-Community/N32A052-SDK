1、功能说明

    此例程提供了一种DMA用法，用于在外设到RAM之间传输数据。
    

2、使用环境

    软件开发环境：KEIL MDK-ARM V5.34.0.0
                 IAR EWARM 8.50.1
    硬件开发环境： 
        N32A052系列：
            基于评估板N32A052KBQX_STB V1.0开发


3、使用说明

    1、时钟源：HSE+PLL
    2、主时钟：64MHz
    3、DMA通道：DMA_CH2，DMA_CH3，DMA_CH4，DMA_CH5
    4、SPI1 配置：
            SCK   -->  PB12
            MISO  -->  PD5
            MOSI  -->  PD4
            全双工
            主模式
            8bit传输
            极性：起始为低/第二个边沿
            软件片选
            大端在前MSB
    
    5、SPI2 配置：
            SCK   -->  PC5
            MISO  -->  PC7
            MOSI  -->  PC6
            全双工
            从模式
            8bit传输
            极性：起始为低/第二个边沿
            软件片选
            大端在前MSB
    
    6、USART1配置：
            TX  -->  PA9
            波特率：115200
            数据位：8bit
            停止位：1bit
            无校验

    7、测试步骤与现象
        a，引脚连接：PB12连接PC5，PD5连接PC7，PD4连接PC6
        b，编译下载代码复位运行
        c，从串口看打印信息，验证结果
        
4、注意事项
    1. 需根据主机时钟空闲电平来配置主机CLK引脚的上/下拉，CLKPOL为1配置为上拉，CLKPOL为0配置为下拉.


1. Function description
    This routine provides a DMA usage for transferring data between peripherals and RAM.

2. Use environment
    Software development environment: KEIL MDK-ARM V5.34.0.0
                                      IAR EWARM 8.50.1
    Hardware development environment:
         N32A052 series:
            Developed based on the evaluation board N32A052KBQX_STB V1.0

3. Instructions for use
    1. Clock source: HSE+PLL
    2. Master clock: 64MHz
    3. DMA channels: DMA_CH2, DMA_CH3, DMA_CH4, DMA_CH5
4. SPI1 configuration:
        SCK   -->  PB12
        MISO  -->  PD5
        MOSI  -->  PD4
        Full duplex
        Main mode
        8 bit transmission
        Polarity: start at low/second edge
        Piece of software to choose
        Big end in front MSB

5. SPI2 Configuration:
        SCK   -->  PC5
        MISO  -->  PC7
        MOSI  -->  PC6
        Full duplex
        From the pattern
        8 bit transmission
        Polarity: start at low/second edge
        Piece of software to choose
        Big end in front MSB

6. USART1 configuration:
        TX  -->  PA9
        Baud rate: 115200
        Data bit: 8 bits
        Stop bit: 1bit
        No check

    7. Test steps and phenomena
        A. Pin connection: PB12 connects to PC5, PD5 connects to PC7, PD4 connects to PC6
        B. Compile download code reset run
        C. View the printed information from the serial port and verify the result
        
4. Precautions
    1. The pull-up/down of the host CLK pin should be configured according to the idle level of the host clock，
        when CLKPOL is set to 1, it is configured as pull-up; when CLKPOL is set to 0, it is configured as pull-down.

