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
* Description: ���ļ�����Բ�Ʒ�ĸ������м��㡣
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
u16 adcx;						//ADCͨ����ȡ����ֵ
u8 ADC_Fall = 1;				//ADCͨ����ֵ�½�
u8 ADC_Rise;				//ADCͨ����ֵ����
u8 Detection_Flag;	//��⵽��Ʒ
/************************************************************************************/

/***********************************************************************************
* Function: Number_Task;
*
* Description: ��Ʒ��������;
*              
* Input:  none;
*
* Return: none;
*
* Note:   �����������ȡ��Ʒ����
*
************************************************************************************/
void Number_Task(void *p_arg)
{
	u16 adcx;

	Facility.Number=0;
	
	while(1)
	{
		
		adcx = Get_Adc_Average(ADC_Channel_15,20);		//��ȡͨ��15��ת��ֵ��20��ȡƽ��
		
		//printf("ADCʵ��adcx=%d\r\n",adcx);
		
		if(adcx<1100 && ADC_Fall==1)//��⵽��Ʒ�����Ƽ��һ��
		{
			
			printf("��⵽��Ʒ\r\n");
			Detection_Flag = 1;				//��⵽��Ʒ
			
			ADC_Fall=0;					      //���Ƶ���Ʒ�������ŵ�ʱ��ֻ���һ��
			ADC_Rise=1;					       //�´μ������
		}
		
		if(adcx>1100 && ADC_Rise==1)//��Ʒ���ߣ����Ƽ��һ��
		{
			
			ADC_Rise=0;								//����ֻ���һ��
			ADC_Fall=1;								//�´μ���½�
			
			ClearTextValue(1,9);
			ClearTextValue(1,8);			//��������ʾ����ѹ��
			ClearTextValue(1,7);			//��������ʾ���Ͷ�λ
			ClearTextValue(1,5);			//��������ʾ��ŵ���
			ClearTextValue(1,3);			//��������ʾ�˴ŵ���
			ClearTextValue(1,10);			//��������ʾ�ߴ�
			ClearTextValue(1,4);			//��������ʾ����
			ClearTextValue(1,6);  		//��������ʾ�Ʒۼ�ʱ
			ClearTextValue(1,27);																						//����������Ľ��				
		
		}
		
		if(Detection_Flag==1) //����Ʒ����
		{
			
			Detection_Flag = 0;							//����ֻ����һ��
			Facility.Number++;							//��Ʒ������һ
			OSSemPost(ProductSem);					//���Ͳ�Ʒ�ź�����������
			
			printf("�����ź�����PLC\r\n");
			OSTimeDlyHMSM(0,0,0,1000);
			
			CameraRedFlag = 1;							//����Թܼ�⵽��Ʒ��ͨ������ͷ�����ж�
			
			ProcessingFlag=0;								//��Ʒ�ϸ���ı�־
			
			
		}
		
		OSTimeDlyHMSM(0,0,0,100);
	}
}
