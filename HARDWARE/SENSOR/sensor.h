#ifndef __SENSOR_H
#define __SENSOR_H	 
#include "sys.h"

//用SENSOR0读取红外循迹传感器0的输入值
#define SENSOR0 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)


void Sensor_Init(void);//声明Sensor初始化函数
		 				    
#endif

