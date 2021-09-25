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
* Description: 本文件负责对外接按钮按下的处理。
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
#include "delay.h"
#include "hmi_driver.h"
#include "string.h"
/************************************************************************************/
// 常量及全局变量定义
/************************************************************************************/
/************************************************************************************/
u8 ID_Data[128];
/***********************************************************************************
* Function:Flash_Task;
*
* Description: FLASH任务;
*              
* Input:  none;
*
* Return: none;
*
* Note:   本函数负责掉电保护
*
************************************************************************************/
void Flash_Task(void *p_arg)
{
	
	while(1)
	{
		
		OSTimeDly(100);
	}
}

		
