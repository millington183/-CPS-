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
* Description: ���ļ������ȡ��ʪ�ȼ��۳�Ũ�ȴ�������ֵ�����д���
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
#include "string.h"
#include "hmi_driver.h"
/************************************************************************************/
// ������ȫ�ֱ�������
/************************************************************************************/
	#define EnvironmentID      2															//��������ID
	u8 Send485buf[]={0x01,0x03,0x00,0x00,0x00,0x0a,0xc5,0xcd};//��ȡ��������ָ��
	u8 num;																										//�������ݵĸ���
	u8 NBEnvironmentData[64];																	//���ϻ�������
/************************************************************************************/

/***********************************************************************************
* Function: Environment_Task;
*
* Description: Environment����;
*              
* Input:  none;
*
* Return: none;
*
* Note:   �����������ȡ�����������¶�
*
************************************************************************************/
void Environment_Task(void *p_arg)
{	
	INT8U MutexERR;							//�����ź���������
	INT8U SemERR;
	u8 Recive48buf[20]={0};			//��������Ľ�������
	INT8U ENVIRCount=0;						//���������ִ�д���

	while(1)
	{
		
			printf("��ȡ��������\r\n");
	
			OSMutexPend(UART5Mutex,0,&MutexERR);
			
			RS485_Send_Data(Send485buf,8);//����5���ֽ� 									   
		
			delay_ms(500);
			
			RS485_Receive_Data(Recive48buf,&num);
		
			delay_ms(1000);
	
			if(num>0)
			{
				printf("������������");
				TempData(Recive48buf,(char *)EnvironmentData.Temperature);									//�������¶�תΪ�ַ���
				HumiDityData(Recive48buf,EnvironmentData.Humidity);													//������ʪ��תΪ�ַ���
				PMData(Recive48buf,(char *)EnvironmentData.PM);                            //���۳�Ũ��תΪ�ַ���
				
				EnvironmentData.Temperature[5]='\0';
				
				EnvironmentData.Humidity[4]='\0';
				
				SetTextValue(1,13,EnvironmentData.PM);																			//����������ʾ�۳�Ũ��
				SetTextValue(1,14,EnvironmentData.Temperature);															//����������ʾ�¶�
				SetTextValue(1,15,EnvironmentData.Humidity);																//����������ʾʪ��
				
				sprintf((char *)NBEnvironmentData,"%d,%s,%s,%s",EnvironmentID,EnvironmentData.PM,EnvironmentData.Temperature,EnvironmentData.Humidity);//���ϻ�������
				
				OSQPost(NBDataQ,NBEnvironmentData);//�ϴ����ݵ�OneNet
				
			}
	
			OSMutexPost(UART5Mutex);						//�ͷŻ����ź���
			
		OSTimeDlyHMSM(0,1,0,0);			
				
		}	
	} 

