#include "sensor.h"

/*
参考来源：
老师PPT
*/	  

//初始化PB12、PB13、PB14为红外循迹传感器输入口.并使能这四个端口的时钟   
//Sensor IO初始化

void Sensor_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //使能PB端口时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;		 //SENSOR0-->PB.12 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 	 //下拉输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //IO口速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);		 //根据设定参数初始化GPIOB.12



}

