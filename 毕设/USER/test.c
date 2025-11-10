#include "sys.h"
#include "delay.h" 
#include "led.h"  
#include "usart.h"
#include "mpu.h"   
#include "lcd.h" 
#include "w25qxx.h"

#include "component_data_struct.h"

// 1
int main(void)
{ 
	Stm32_Clock_Init(160,5,2,4);	//设置时钟,400Mhz
  delay_init(400);				//延时初始化  
	uart_init(100,115200);			//串口初始化为115200  
	LCD_Init();							//初始化LCD
	W25QXX_Init();					//W25QXX初始化
	
	Init_component_db(&component_classifier); //数据库初始化
	Test_add_categoties(&component_classifier); //测试添加新类别函数
	
	POINT_COLOR=RED;
//	LCD_ShowString(30,50,200,16,16,"Apollo STM32F4/F7/H7"); 
	while(1)
	{
		
	}
}













