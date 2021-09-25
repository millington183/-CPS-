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
* Description: ���ļ�����PLC��ȡ�������ݽ��д���
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
#include "string.h"
#include "hmi_driver.h"
/************************************************************************************/
// ������ȫ�ֱ�������
/************************************************************************************/
static u8 rs485buf[4]={0x02,0x00,0x01,0x14};																								//��ȡPLC����ָ��
u8 ProductDataPLC[256];
u8 NBProductData[256];				//������������
/************************************************************************************/

/************************************************************************************/
/***********************************************************************************
* Function: PLC_Task;
*
* Description: PLC����;
*              
* Input:  none;
*
* Return: none;
*
* Note:   �����������ȡPLC�������������ݽ��д���
*
************************************************************************************/
void PLC_Task(void *p_arg)
{
			u8 ReceivingArray[25];																							//PLC���������ַ�������
			u8 i,j=0;																														//����PLC��������ı���
			u8 len;																															//����PLC����ĳ���
			
			INT8U ERRMutex;																											//����5�����ź���������
			INT8U ERRSem;																												//��Ʒ�����ź���������
			INT8U ResultERR;
		while(1)
			 {
						printf("PLC����");
						OSSemPend(ProductSem,0,&ERRSem);
					 if(ERRSem==OS_ERR_NONE)
					 {
								OSMutexPend(UART5Mutex,0,&ERRMutex);																//�ȴ���Ʒ�ۻ��������ź���
							 	RS485_Send_Data((u8 *)rs485buf,4);													//ͨ��485����ָ���PLC		
								delay_ms(800);
								RS485_Receive_Data((u8 *)ReceivingArray,&len);							//����PLC������
								delay_ms(500);
								
							 printf("���յ�PLC������%d\r\n",len);
					
						if(len>0)																											//���ճɹ�
							{	
									printf("���յ�PLC����");
								for(i=0;i<25;i++)
									{
										if(i==3|i==6|i==11|i==15|i==19|i==24)
										{
											j=0;
										}
										if(i<3)
										{
											Facility.BriquettingPressure[i]=ReceivingArray[i];
										}
										if(i>2&&i<6)
										{
											
											Facility.TonnageMolding[j++]=ReceivingArray[i];
										}
										
										if(i>5&&i<11)
										{
											Facility.MagnetizingA[j++]=ReceivingArray[i];
										}
										if(i>10&&i<15)
										{
											Facility.DemagnetizmA[j++]=ReceivingArray[i];
										}
										if(i>14&&i<19)
										{
											Facility.Size[j++]=ReceivingArray[i];
										}
										if(i>18&&i<24)
										{
											Facility.Weight[j++]=ReceivingArray[i];
										}
										if(i==24)
										{
											Facility.PowderTime[0]=ReceivingArray[i];
										}
									}
									Facility.BriquettingPressure[3]='\0';
									Facility.TonnageMolding[3]='\0';
									Facility.MagnetizingA[5]='\0';
									Facility.DemagnetizmA[4]='\0';
									Facility.Size[4]='\0';
									Facility.Weight[5]='\0';
									Facility.PowderTime[1]='\0';
									printf("ת�����\r\n");
									printf("%s\r\n",Facility.BriquettingPressure);							//����ѹ��
									printf("%s\r\n",Facility.TonnageMolding);										//���Ͷ�λ
									printf("%s\r\n",Facility.MagnetizingA);											//��ŵ���
									printf("%s\r\n",Facility.DemagnetizmA);											//�˴ŵ���
									printf("%s\r\n",Facility.Size);															//�ߴ�
									printf("%s\r\n",Facility.Weight);														//����
									printf("%s\r\n",Facility.PowderTime);												//�Ʒۼ�ʱ
								
									
									SetTextValue(1,8,	(u8 *)Facility.BriquettingPressure);			//��������ʾ����ѹ��
									SetTextValue(1,7,	(u8 *)Facility.TonnageMolding);						//��������ʾ���Ͷ�λ
									SetTextValue(1,5,	(u8 *)Facility.MagnetizingA);							//��������ʾ��ŵ���
									SetTextValue(1,3,	(u8 *)Facility.DemagnetizmA);							//��������ʾ�˴ŵ���
									SetTextValue(1,10,(u8 *)Facility.Size);											//��������ʾ�ߴ�
									SetTextValue(1,4, (u8 *)Facility.Weight);										//��������ʾ����
									SetTextValue(1,6, (u8 *)Facility.PowderTime);								//��������ʾ�Ʒۼ�ʱ

									
							 	sprintf((char *)ProductDataPLC,"%d,%s,%d,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s",1,SerialNumber.Facility,Facility.Number,
								SerialNumber.Pack_ID,SerialNumber.Profiling_ID,GainNumber.MouldData,GainNumber.Granularity,
								Facility.PowderTime,Facility.BriquettingPressure,Facility.TonnageMolding,Facility.Weight,Facility.Size,
								Facility.DemagnetizmA,Facility.MagnetizingA,SerialNumber.Mark);							
									
								printf("PLC����%s\r\n",ProductDataPLC);
							}
						
							OSMutexPost(UART5Mutex);																				//�ͷŻ����ź���			
							
							OSSemPend(ResultSem,0,&ResultERR);															//�����ź���
							if(ResultERR==OS_ERR_NONE)
							{
								sprintf((char *)NBProductData,"%s,%s",ProductDataPLC,GainNumber.ResultData);//�������ɵ�����
								
								OSQPost(NBDataQ,(void *)NBProductData);	//�ϴ���Ʒ���������ݵ�OneNet
								strcpy((char *)GainNumber.ResultData,"0");//������ı������Ϊ0
								
								printf("��Ʒ����ϴ�NB���ݳɹ�\r\n");
																						
							}	
						}
					 OSTimeDlyHMSM(0,0,0,100);
				}										
}
