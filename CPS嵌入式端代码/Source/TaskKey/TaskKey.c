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
#define ProductID          1		//��Ʒ��������ID


u8 NBProduct[512]={"1,1,2,08090118312,08090118304,1,1,5,4.6,6.2,460.7,24.1,39.8,188.4,50H,2"};
u8 NBEnvironment[64]={"2,16,22.12,80.21"};
u8 NBProductEX[512]={0};
u8 MainSF[128]={"3,1,08090118312,2021-06-12 15:46,1,2021-06-13 15:00"};
u8 NBDataSF[256];

	
/************************************************************************************/

/***********************************************************************************
* Function: Processing_Task;
*
* Description: ���ݴ�������;
*              
* Input:  none;
*
* Return: none;
*
* Note:   ����������������ݲ�������д���
*
************************************************************************************/
/*
	ģ�����ͱ��
	��״      1
	Բ״      2
	
	���ȱ��
	С��      0
	����      1
	
	��Ʒ��Ϣ����
	1���豸�ţ���Ʒ��ţ�ѹ����Ա����װ��Ա��ģ�߱�ţ����ȱ�ţ��Ʒۼ�ʱ
	����ѹ�������Ͷ�λ���������ߴ磬�˴ŵ�������ŵ��������ϱ��,������(Ĭ��Ϊ0)
	
	��Ʒ���
	0 �ϸ�
	1 Բ��-ȱ��-����
	2 Բ��-ȱ��-���
	3 Բ��-ƫλ����
	4 Բ��-�Ѻ�
	5 ��״-ȱ��-����
	6 ��״-ȱ��-���󲻵�
	7 ��״-ȱ��-ģ�߲���
	8 ��״-б��
	
	
*/

void Qualified_Task(void *pdata)
{

	INT8U ProductERR;//��Ʒ����ź���

	pdata=pdata;
	 
	while(1)
	{
			OSSemPend(ProductSem,0,&ProductERR);
			if(ProductERR == OS_ERR_NONE)
			{
				printf("����������յ���Ʒ���ź���\r\n");
				OSTimeDlyHMSM(0,0,30,0);						//����1����
				OSSemPost(ResultSem);							//�ͷŲ�Ʒ����ź���
				SetTextValue(1,9,ProductResult);
				ProductResultFlag=1;
				printf("�ͷŽ���ź���\r\n");
			}	
		OSTimeDlyHMSM(0,0,15,0);
		
	}
}



		
