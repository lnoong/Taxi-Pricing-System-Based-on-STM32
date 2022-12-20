#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "rtc.h"
#include "usmart.h"
#include "key.h"
#include "pwm.h"
#include "sensor.h"
//ALIENTEK Mini STM32开发板范例代码11
//TFTLCD显示实验   
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司 


 int main(void)
 { int a=0;
	 int b=0;
	 int c=0;
	double dis=0.00;
	double n=1.00;
	double pri0=0.0,pri1=0.0,pri=0.0;
	long int waittime;
	u8 x=0;
	u8 len;
	u8 t;	

	u8 sdis[10];
	u8 spri[10];
	delay_init();	    	 //延时函数初始化	  
	uart_init(9600);	 	//串口初始化为9600
	LED_Init();		  		//初始化与LED连接的硬件接口
	KEY_Init();          	//初始化与按键连接的硬件接口
	Sensor_Init();
	TIM4_PWM_Init(7199,0);
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	RTC_Init();
	LCD_Init();

	 
	LCD_Clear(WHITE);

	POINT_COLOR=RED;	
	LCD_ShowString(10,70,50,24,24,"TIME:");	
	LCD_ShowString(80,70,110,24,24,"  :  :  ");	 
	LCD_ShowString(10,40,50,24,24,"DATE:");
	LCD_ShowString(80,40,110,24,24,"    /  /  ");		 
	RTC_Set(2022,05,29,calendar.hour,calendar.min,calendar.sec);  //	
	//LED0=0;
	LCD_ShowString(10,250,50,24,24,"MODE:");	
	LCD_ShowString(80,250,110,24,24,"DAY");
	PA11 = 0;
	PA12 = 1;
  	while(1) 
	{		 
		POINT_COLOR=RED;
		if(USART_RX_STA&0x8000)
		{					   
			len=USART_RX_STA&0x3fff;//得到此次接收到的数据长度
			for(t=0;t<len;t++)
			{
				USART1->DR=USART_RX_BUF[t];
				while((USART1->SR&0X40)==0);//等待发送结束
			}
			if(USART_RX_BUF[0]=='0')
			{
				waittime=RTC_GetCounter();
				c=1;
			}	
			else	if(USART_RX_BUF[0]=='1')
			{
				PA11 = 0;
				PA12 = 1;
				c=2;
			}
			USART_RX_STA=0;
		}
		if(c==1)
		{
			PA11 = 0;
			PA12 = 0;
			LCD_ShowNum(80,130,RTC_GetCounter()-waittime,4,24);
			pri0=(double)(RTC_GetCounter()-waittime)/60;
		}
			if(SENSOR0==0)
			{
				n++;
				dis=n/10;
			}
			
			sprintf((char*)sdis,"%.2lf",dis);//将LCD ID打印到lcd_id数组。
			///////////time
			LCD_ShowNum(80,70,calendar.hour,2,24);									  
			LCD_ShowNum(115,70,calendar.min,2,24);									  
			LCD_ShowNum(150,70,calendar.sec,2,24);
			
			///////////date
			LCD_ShowNum(80,40,calendar.w_year,4,24);									  
			LCD_ShowNum(140,40,calendar.w_month ,2,24);									  
			LCD_ShowNum(175,40,calendar.w_date ,2,24);
			
			t=KEY_Scan(0);		//得到键值
			
			if(t==WKUP_PRES)////判断wakeup键功能
				a++;
			
			if(a==0)////黑白切换
			{
				
				if(t==KEY1_PRES)
				{
					b++;
				}
				if(b%2==0)////白天模式
				{
					LCD_ShowString(10,250,50,24,24,"MODE:");	
					LCD_ShowString(80,250,110,24,24,"DAY  ");
					if(dis<2.7)//33
						pri1=33;
					else if(dis>=2.7&&dis<=19)//21
						pri1=21*(dis-2.7)+33;
					else
						pri1=21*(19-2.7)+33+3*(dis-19);
							
					LED0=0;
					LED1=1;
				}
				else//黑天模式
				{
				
					LCD_ShowString(10,250,50,24,24,"MODE:");	
					LCD_ShowString(80,250,110,24,24,"NIGHT");
					
					
					if(dis<2.7)//33
						pri1=33*1.3;
					else if(dis>=2.7&&dis<=19)//21
						pri1=1.7*21*(dis-2.7)+33*1.3;
					else
						pri1=1.7*21*(19-2.7)+1.7*21*(dis-2.7)+33*1.3;
					LED1=0;
					LED0=1;
				}
			}	
			pri=pri1+pri0;
			sprintf((char*)spri,"%.1lf",pri);//将LCD ID打印到lcd_id数组。
			switch(a)////修改时间
			{
				case 1:
				if(t==KEY1_PRES)
				{
				calendar.hour++;
				RTC_Set(2022,05,27,calendar.hour,calendar.min,calendar.sec);
				}
				else if(t==KEY0_PRES)
				{
				calendar.hour--;
				RTC_Set(2022,05,27,calendar.hour,calendar.min,calendar.sec);
				}
				break;
				case 2:
				if(t==KEY1_PRES)
				{
				calendar.min++;
				RTC_Set(2022,05,27,calendar.hour,calendar.min,calendar.sec);
				}
				else if(t==KEY0_PRES)
				{
				calendar.min--;
				RTC_Set(2022,05,27,calendar.hour,calendar.min,calendar.sec);
				}
				break;
				case 3:
				if(t==KEY1_PRES)
				{
				calendar.sec++;
				RTC_Set(2022,05,27,calendar.hour,calendar.min,calendar.sec);
				}
				else if(t==KEY0_PRES)
				{
				calendar.sec--;
				RTC_Set(2022,05,27,calendar.hour,calendar.min,calendar.sec);
				}
				break;
				default:
					a=0;
					break ;
			}
		
		////////循环显示信息
		{
			
			
		LCD_ShowString(10,10,50,24,24,"NUM :");
		LCD_ShowString(80,10,200,24,24,"2100970233");
			
		LCD_ShowString(10,100,50,24,24,"DIS :");	
		LCD_ShowString(80,100,110,24,24,sdis);

		LCD_ShowString(10,130,50,24,24,"WAIT:");	
		
		LCD_ShowString(10,160,50,24,24,"PRI :");	
		LCD_ShowString(80,160,110,24,24,spri);
		

		}
	
		
	}	
		   					
	
}
