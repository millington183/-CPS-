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
* Description: ���ļ���������ݽ��д���
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
#include "stdio.h"
#include "hmi_driver.h"
/************************************************************************************/
// ������ȫ�ֱ�������
/************************************************************************************/

INT8U CameraData[20];	
/***********************************************************************************
* Function: Processing_Task;
*
* Description: ����ͷ��������;
*              
* Input:  none;
*
* Return: none;
*
* Note:   �����������������ͷ���ݲ�������д���
*
************************************************************************************/
void Processing_Task(void *p_arg)
{
	u16 len;
	u8 i;
	INT8U CameraERR;
	INT8U QualifiedERR;
	while(1)
	{
		
			if(DetectionMode==0)							//��ⷽʽΪ����ͷ���ʱ
			{
				if((UART1_RX_STA & 0X8000) && (CameraRedFlag ==1))			//���յ����ݲ��Һ���Թܼ�⵽��Ʒ
				{
			
					printf("���յ�����\r\n");
					CameraRedFlag=0;
					len=UART1_RX_STA&0X7FFF;
					for(i=0;i<len;i++)
					{
						CameraData[i]=UART1_RX_BUF[i];
						UART1_RX_BUF[i]=0;
					}
					UART1_RX_STA=0;
					
					if(CameraData[0]=='0')
					{
						OSTimeDlyHMSM(0,0,0,500);	
						SetTextValue(1,27,ProductResult);
						strcpy((char *)GainNumber.ResultData,"0");//������ı������Ϊ0
						//sprintf((char *)GainData.ResultData,"%s",ProductResult);			//����Ϊ��ȡ�Ľ������
						CameraFlag=1;															//ͨ������ͷ���ȥ����һ����¼
						OSTimeDlyHMSM(0,0,0,1500);
						OSSemPost(ResultSem);											//�ͷŲ�Ʒ����ź���
						//UploadingFlag=1;
					}
					
					if(CameraData[0]=='2')
					{
						OSTimeDlyHMSM(0,0,0,500);
						SetTextValue(1,27,ProductResult2);
						strcpy((char *)GainNumber.ResultData,"2");//������ı������Ϊ2
						//sprintf((char *)GainData.ResultData,"%s",ProductResult2);			//����Ϊ��ȡ�Ľ������
						CameraFlag=1;															//ͨ������ͷ���ȥ����һ����¼
						OSTimeDlyHMSM(0,0,0,1500);
						OSSemPost(ResultSem);							//�ͷŲ�Ʒ����ź���
						//UploadingFlag=1;
					}
					
					if(CameraData[0]=='5')
					{
						OSTimeDlyHMSM(0,0,0,500);
						SetTextValue(1,27,ProductResult5);
						strcpy((char *)GainNumber.ResultData,"5");//������ı������Ϊ0
						//sprintf((char *)GainData.ResultData,"%s",ProductResult5);			//����Ϊ��ȡ�Ľ������
						CameraFlag=1;															//ͨ������ͷ���ȥ����һ����¼
						OSTimeDlyHMSM(0,0,0,1500);
						OSSemPost(ResultSem);							//�ͷŲ�Ʒ����ź���
						//UploadingFlag=1;
					}
				}
			}
			
			else if(DetectionMode==1)//Ϊ�˹����ʱ
		{
				EXTI_APPInit();               // �ⲿ�жϳ�ʼ��
//			OSSemPend(QualifiedSem,0,&QualifiedERR);				//�ȴ���Ʒ�ϸ���ź���
//			if(QualifiedERR == OS_ERR_NONE)
//			{
			if(ProcessingFlag==0)
			{
				printf("����������յ���Ʒ���ź���\r\n");
				OSTimeDlyHMSM(0,0,20,0);												//����1����
				SetTextValue(1,9,ProductResult);
				ProductResultFlag=1;													//Ĭ�Ϻϸ�Ҳ�����ʷ��¼
				OSSemPost(ResultSem);													//�ͷŲ�Ʒ����ź���
				printf("�ͷŽ���ź���\r\n");
			}
			//}	
		}
		
		OSTimeDlyHMSM(0,0,1,0);
	}
}
