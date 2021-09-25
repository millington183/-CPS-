/************************************************************************************
*  Copyright (c), 2019, 江西理工大学
*            All rights reserved.
*
* http:  www.jxust.edu.cn
* Email: 
*
* File name: TaskUart.c
* Project  : STM32F4XX系列模块软件
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  
* Version: 0.01
* Date:    2021.6.11			
* Email:   
* 
* Description: 本文件负责将压力传感器读取到的数据进行处理
*
* Others: none;
*
* Function List:
*		
*   1. Author:			  
*	   Version: 	 		0.02
*	   Date:         	2021.6.11
*    Modification: 	none
*	   
*
*************************************************************************************/
#include "PIONEER_Config.h"
#include "STM32F4_Head.h"
#include "UserVars.h"
#include "OSVars.h"
#include "sys.h"
#include "Uart.h"
#include "led.h"
#include "hx711.h"
#include "delay.h"
#include "hmi_driver.h"
/************************************************************************************/
// 常量及全局变量定义
/************************************************************************************/
u32 Pressure = 0;
INT8U PressureData[5];
/***********************************************************************************
* Function: Pressure_Task;
*
* Description: Pressure任务;
*              
* Input:  none;
*
* Return: none;
*
* Note:   本函数负责读取压力传感器的值
*
************************************************************************************/
void Pressure_Task(void *p_arg)
{ 
	Init_Hx711();
	delay_ms(2000);
	Get_Maopi();
	delay_ms(100);
	while(1)
	{
		printf("压力传感器运行\r\n");
		Pressure = -Get_Weight();
		sprintf((char *)PressureData,"%d.%03d",Pressure/1000,Pressure%1000);//将整数转为字符串的小数
		//Weight = Weight///1000.0f;	
		printf("%dg\r\n",Pressure);	//串口显示重量
		printf("%skg\r\n",PressureData);
		printf("PressureData[2]=%c\r\n",PressureData[2]);
			if(Pressure/1000<=1&&Pressure%1000>=0)
		{
			SetTextValue(1,8,PressureData);//串口屏成型压力显示
		}
		OSTimeDlyHMSM(0,0,0,1000);
	}
}






