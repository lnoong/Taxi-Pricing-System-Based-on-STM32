# 基于STM32 的出租车计价系统设计

​		**系统以STＭ32F103RCT6为核心，用A3144霍尔传感器来统计车轮转过的圈数，从而得到出租车行驶的距离进行计价。对于时间及日期的计算，该系统采用STM32开发板上的RTC定时器处理，该模块拥有一组连续计数的计数器，能够通过算法实现整个系统的时间计算。在显示方面，该系统采用正点原子的TFT LCD显示屏，显示效果好，使用方便。整个系统由7.4V干电池供电，辅以AMS1117-5.0进行稳压处理。**

​		**该系统内部设定起步价，开机后检测按键是否按下，判断按下了什么按键，并进行下一步操作。通过PWM输出控制电机转动，霍尔传感器检测车轮上的磁铁来计算圈数，且可以通过串口发送的信号来判断车速是否为零，最终将圈数可以化为公里数，得出车费。**

- 模块功能示意图
- ![](功能模块.png)
- 软件流程图

![](软件流程.png)

- 效果展示

![](效果展示.jpg)
