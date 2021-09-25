/************************************************************************************
*  Copyright (c), 2019, ��������ѧ
*            All rights reserved.
*
* http:  www.jxust.edu.cn
* Email: 
*
* File name: TaskUart.c
* Project  : STM32F4XXϵ��ģ�����
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  
* Version: 0.01
* Date:    2021.6.11			
* Email:   
* 
* Description: ���ļ��������Ӱ�ť���µĴ���
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
// ������ȫ�ֱ�������
/************************************************************************************/
/************************************************************************************/
u8 ID_Data[128];
/***********************************************************************************
* Function:Flash_Task;
*
* Description: FLASH����;
*              
* Input:  none;
*
* Return: none;
*
* Note:   ������������籣��
*
************************************************************************************/
void Flash_Task(void *p_arg)
{
	
	while(1)
	{
		
		OSTimeDly(100);
	}
}

		
