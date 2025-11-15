#include "sys.h"
#include "delay.h" 
#include "led.h"  
#include "usart.h"
#include "mpu.h"   
#include "lcd.h" 
#include "w25qxx.h"
#include "sdram.h"
#include "component_data_struct.h"

#include "FreeRTOS.h"
#include "task.h"

#include "lvgl.h"
#include "lv_init.h"
#include "lv_port_disp_template.h"
#include "lv_port_indev_template.h"
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
#define UART_TASK_PRIO		2
//任务堆栈大小	
#define UART_STK_SIZE 		128  
//任务句柄
TaskHandle_t Uart_Task_Handler;
//开始任务函数
void uart_task(void *pvParameters);

//任务优先级
#define LVGL_TASK_PRIO		1
//任务堆栈大小	
#define LVGL_STK_SIZE 		2128
//任务句柄
TaskHandle_t Lvgl_Task_Handler;
//开始任务函数
void lvgl_task(void *pvParameters);
//******************************************
// 1
int i=0;
int main(void)
{ 
	Stm32_Clock_Init(160,5,2,4);	//设置时钟,400Mhz
  delay_init(400);				//延时初始化  
	uart_init(100,115200);			//串口初始化为115200  
	W25QXX_Init();					//W25QXX初始化
	
	Init_component_db(&component_classifier); //数据库初始化
	Test_add_categoties(&component_classifier); //测试添加新类别函数
	SDRAM_Init();
	LCD_Display_Dir(1);								//设置横屏
	lv_init();
	lv_port_disp_init();
	lv_port_indev_init();
	
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
		//创建开始任务
		xTaskCreate((TaskFunction_t )lvgl_task,            //任务函数
                (const char*    )"lvgl_task",          //任务名称
                (uint16_t       )LVGL_STK_SIZE,        //任务堆栈大小
                (void*          )NULL,                  //传递给任务函数的参数
                (UBaseType_t    )LVGL_TASK_PRIO,       //任务优先级
                (TaskHandle_t*  )&Lvgl_Task_Handler);   //任务句柄 
								
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
void lvgl_task(void *pvParameters)//O0
{
	u32 count=0;
	
	lv_obj_t* label=NULL; //标签
	label=lv_label_create(lv_scr_act());   //标签事件
	lv_obj_set_style_text_font(label,&lv_font_montserrat_14,LV_STATE_DEFAULT);  //字体大小
	lv_obj_set_style_text_color(label,lv_color_hex(0x5084db),LV_STATE_DEFAULT);  //标签颜色
	lv_label_set_text(label,"speed = #ff0000 %d#");
	lv_obj_align(label,LV_ALIGN_CENTER,0,-lcddev.height/3);
	
	lv_obj_t* btn=NULL;  //按钮
	btn=lv_btn_create(lv_scr_act());
	lv_obj_set_size(btn,lcddev.width/12,lcddev.height/6);
	lv_obj_align(btn,LV_ALIGN_CENTER,lcddev.width/3,0);
	lv_obj_set_style_bg_color(btn,lv_color_hex(0xffe1d4),LV_STATE_PRESSED);  
	lv_obj_add_flag(btn,LV_OBJ_FLAG_CHECKABLE);
	while(1)
	{
		TickType_t count = xTaskGetTickCount();
		vTaskDelay(100);
		lv_timer_handler();
		lv_label_set_text_fmt(label,"speed %d  %d \r\n",count,i);
		printf("lvgl移植测试 %d  %d \r\n",count,i);
	}
}
void vApplicationTickHook(void)
{
	i++;
	lv_tick_inc(1); // 1ms
}








