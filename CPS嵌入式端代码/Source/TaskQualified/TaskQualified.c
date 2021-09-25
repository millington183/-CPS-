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
#include "hx711.h"
#include "delay.h"
#include "hmi_driver.h"
/************************************************************************************/
// ������ȫ�ֱ�������
/************************************************************************************/
/************************************************************************************/


/***********************************************************************************
* Function: Qualified_Task;
*
* Description: ��Ʒ�ϸ�����;
*              
* Input:  none;
*
* Return: none;
*
* Note:   ������������ƶ��û�жԲ�Ʒ�����ж�Ĭ�Ϻϸ�ʱ��
*
************************************************************************************/
void Qualified_Task(void *p_arg)
{

	INT8U QualifiedERR;																	//��Ʒ����ź���

	while(1)
	{
//			OSSemPend(QualifiedSem,0,&QualifiedERR);				//�ȴ���Ʒ�ϸ���ź���
//			if(QualifiedERR == OS_ERR_NONE)
//			{
//				printf("����������յ���Ʒ���ź���\r\n");
//				OSTimeDlyHMSM(0,2,0,0);												//����1����
//				SetTextValue(1,9,ProductResult);
//				ProductResultFlag=1;													//Ĭ�Ϻϸ�Ҳ�����ʷ��¼
//				OSSemPost(ResultSem);													//�ͷŲ�Ʒ����ź���
//				printf("�ͷŽ���ź���\r\n");
//			}	
//		OSTimeDlyHMSM(0,0,15,0);	
	}
}



		
