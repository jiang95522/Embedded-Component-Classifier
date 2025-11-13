#include "sys.h"
#include "delay.h" 
#include "led.h"  
#include "usart.h"
#include "mpu.h"   
#include "lcd.h" 
#include "w25qxx.h"

#include "component_data_struct.h"

#include "FreeRTOS.h"
#include "task.h"
//************************************************
//任务优先级
#define START_TASK_PRIO		1
//任务堆栈大小	
#define START_STK_SIZE 		128  
//任务句柄
TaskHandle_t StartTask_Handler;
//开始任务函数
void start_task(void *pvParameters);

//任务优先级
#define UART_TASK_PRIO		1
//任务堆栈大小	
#define UART_STK_SIZE 		128  
//任务句柄
TaskHandle_t Uart_Task_Handler;
//开始任务函数
void uart_task(void *pvParameters);
//******************************************
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
	
    //创建开始任务
    xTaskCreate((TaskFunction_t )start_task,            //任务函数
                (const char*    )"start_task",          //任务名称
                (uint16_t       )START_STK_SIZE,        //任务堆栈大小
                (void*          )NULL,                  //传递给任务函数的参数
                (UBaseType_t    )START_TASK_PRIO,       //任务优先级
                (TaskHandle_t*  )&StartTask_Handler);   //任务句柄 
	printf("开始任务 \r\n");
    //创建								
    vTaskStartScheduler();          //开启任务调度
}

//开始任务任务函数
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //进入临界区		
    //创建开始任务
    xTaskCreate((TaskFunction_t )uart_task,            //任务函数
                (const char*    )"uart_task",          //任务名称
                (uint16_t       )UART_STK_SIZE,        //任务堆栈大小
                (void*          )NULL,                  //传递给任务函数的参数
                (UBaseType_t    )UART_TASK_PRIO,       //任务优先级
                (TaskHandle_t*  )&Uart_Task_Handler);   //任务句柄 
    vTaskDelete(StartTask_Handler); //删除开始任务
    taskEXIT_CRITICAL();            //退出临界区
		printf("串口任务 \r\n");
}
void uart_task(void *pvParameters)
{
	while(1)
	{
		TickType_t last_tick = xTaskGetTickCount();
		vTaskDelay(1000);
		 printf("rtos移植测试，距离上次打印经过了 %d 个tick\r\n", last_tick);
		printf("rtos移植测试 \r\n");
	}
}









