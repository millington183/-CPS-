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
* Description: ���ļ�����ѹ����������ȡ�������ݽ��д���
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
u32 Pressure = 0;
INT8U PressureData[5];
/***********************************************************************************
* Function: Pressure_Task;
*
* Description: Pressure����;
*              
* Input:  none;
*
* Return: none;
*
* Note:   �����������ȡѹ����������ֵ
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
		printf("ѹ������������\r\n");
		Pressure = -Get_Weight();
		sprintf((char *)PressureData,"%d.%03d",Pressure/1000,Pressure%1000);//������תΪ�ַ�����С��
		//Weight = Weight///1000.0f;	
		printf("%dg\r\n",Pressure);	//������ʾ����
		printf("%skg\r\n",PressureData);
		printf("PressureData[2]=%c\r\n",PressureData[2]);
			if(Pressure/1000<=1&&Pressure%1000>=0)
		{
			SetTextValue(1,8,PressureData);//����������ѹ����ʾ
		}
		OSTimeDlyHMSM(0,0,0,1000);
	}
}






