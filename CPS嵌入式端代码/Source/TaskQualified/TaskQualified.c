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
#include "hx711.h"
#include "delay.h"
#include "hmi_driver.h"
/************************************************************************************/
// 常量及全局变量定义
/************************************************************************************/
/************************************************************************************/


/***********************************************************************************
* Function: Qualified_Task;
*
* Description: 产品合格任务;
*              
* Input:  none;
*
* Return: none;
*
* Note:   本函数负责控制多久没有对产品进行判断默认合格时间
*
************************************************************************************/
void Qualified_Task(void *p_arg)
{

	INT8U QualifiedERR;																	//产品结果信号量

	while(1)
	{
//			OSSemPend(QualifiedSem,0,&QualifiedERR);				//等待产品合格的信号量
//			if(QualifiedERR == OS_ERR_NONE)
//			{
//				printf("按键任务接收到产品的信号量\r\n");
//				OSTimeDlyHMSM(0,2,0,0);												//挂起1分钟
//				SetTextValue(1,9,ProductResult);
//				ProductResultFlag=1;													//默认合格也添加历史记录
//				OSSemPost(ResultSem);													//释放产品结果信号量
//				printf("释放结果信号量\r\n");
//			}	
//		OSTimeDlyHMSM(0,0,15,0);	
	}
}



		
