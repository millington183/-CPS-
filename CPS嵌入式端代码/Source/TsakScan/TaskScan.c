/************************************************************************************
*  Copyright (c), 2019, ��������ѧ
*            All rights reserved.
*
* http:  www.jxust.edu.cn
* Email: 
*
* File name: TaskScan.c
* Project  : STM32F1XX/4XXɨ������
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  
* Version: 0.01
* Date:    2021.06.11			
* Email:   
* 
* Description: ���ļ��������ɨ��õ������ݼ�������
*
* Others: none;
*
* Function List:
*		
* History:
*   1. Author:			  
*	   Version: 	 		0.02
*	   Date:         	2019.11.08
*    Modification: 	none
*
*************************************************************************************/
/************************************************************************************/
// ����˵��
/************************************************************************************/
/*

*/

/************************************************************************************/
// �����ⲿͷ�ļ�
/************************************************************************************/
#include "PIONEER_Config.h"
#include "STM32F4_Head.h"
#include "UserVars.h"
#include "OSVars.h"
#include "string.h"
#include "hmi_driver.h"
/************************************************************************************/
// ������ȫ�ֱ�������
/************************************************************************************/
//�豸���1/2
//���ϱ��50H��ͷ
//��Ա���08��ͷ
//081�ǰ�װԱ��
//082��ѹ��Ա��
u8  StaffFlag=0;							//����ŵ�����
static char CacheData[256];		//��������
	u8 datmp[25];
/***********************************************************************************
* Function: Scan����
*
* Description: Scan����;
*              
* Input:  none;
*
* Return: none;
*
* Note:   ���������ڶ�ȡ��ά���ԭʼ��Ϣ
*
************************************************************************************/
void Scan(void )
{
	char ScanData[256];//ɨ������
	INT8U i;
	INT8U len=0;
	INT8U OS_Err;
	  
		OSSemPend(UART3Sem,0,&OS_Err);					  									 //�ȴ�����3���͵��ź���	
			
			if(OS_Err == OS_ERR_NONE)							 										 //������ܵ��ź���������ȷ
			{		
				
				if(UART3_RX_STA&0x8000 )
				{				
						//printf("���ճɹ�");
						len = UART3_RX_STA&0x7FFF;     											 //�õ��˴ν��յ������ݳ���							
						memset(ScanData,0,sizeof(ScanData));								 //��ɨ��������������
						
						for(i=0; i<len-1; i++)					  									 //len-1������ɾ��ɨ��ǹ�Զ����صĻس���
						{
							ScanData[i] = UART3_RX_BUF[i];	    							 // ��ȡ����3����	
							//printf("%c",ScanData[i]);
							UART3_RX_BUF[i] = 0;             								 	 // �������3���ջ�����������							
						}
						UART3_RX_BUF[i+1] = 0;														   // �������3���ջ�������len+1����						 
						UART3_RX_STA=0;																			 // ����UART3״̬���
					
						if(ScanData[0]=='0'&&ScanData[1]=='8')
					{
						StaffFlag=1;																				 //��װԱ��
						memset(CacheData,0,sizeof(CacheData));							 //�������������
						for(i=0;i<len-1;i++)
						{
							CacheData[i]=ScanData[i];													 //����ɨ�����������
							//printf("Scan%c",CacheData[i]);
						}
					}
					
					else if(ScanData[0]=='0'&&ScanData[1]=='0')											
					{																																
						StaffFlag=2;																				 //ѹ��Ա��
						memset(CacheData,0,sizeof(CacheData));							 //�������������
						for(i=0;i<len-1;i++)
						{
							CacheData[i]=ScanData[i];													 //����ɨ�����������
							//printf("%c",CacheData[i]);
						}
					}
					
					else if(ScanData[0]=='3'&&ScanData[1]=='3'&&ScanData[2]=='A')
					{
						StaffFlag=3;																				 //ԭ�ϱ��
						memset(CacheData,0,sizeof(CacheData));							 //�������������
						for(i=0;i<len-1;i++)
						{
							CacheData[i]=ScanData[i];													 //����ɨ�����������
							//printf("%c",CacheData[i]);
						}
					}
					
					else
					{
						StaffFlag=4;																				 //�豸���
						memset(CacheData,0,sizeof(CacheData));							 //�������������
						for(i=0;i<len-1;i++)
						{
							CacheData[i]=ScanData[i];													 //����ɨ�����������
							//printf("%c",CacheData[i]);
						}
					}
					
					memset(ScanData,0,sizeof(ScanData));									//���ɨ�����ݵ�����
				
				}			
			}
}

/***********************************************************************************
* Function: Scan_Task;
*
* Description: Scan����;
*              
* Input:  none;
*
* Return: none;
*
* Note:   �����������ȡ��Ʒ��ά���ԭʼ��Ϣ
*
************************************************************************************/
void Scan_Task(void *p_arg)
{
	u8 i=0;

	while(1)
	{
			printf("ɨ��ǹ��������\r\n");
			
			Scan();																		 		 					//���������ڶ�ȡ��ά���ԭʼ��Ϣ	
			
			switch(StaffFlag)
			{
				
				case 1:																			
				{
					if(ScanFlag == 1)
					{
						strncpy((char *)SerialNumber.Pack_ID,CacheData,13);  				//�ӻ��������и��ư�װԱ��ID
						for(i=0;i<13;i++)
						{
							printf("%c",SerialNumber.Pack_ID[i]);
						}
						SetTextValue(3,2,(u8 *)SerialNumber.Pack_ID);				//����������ʾ��װԱ��ID
					
						printf("��װԱ�����ֽ�=%d\r\n",strlen((const char*)SerialNumber.Pack_ID));
					
					break;
					}
				
				}
				
				case 2:
				{
					if(ScanFlag == 1)
					{
						strncpy((char *)SerialNumber.Profiling_ID,CacheData,13);  	//�ӻ��������и���ѹ��Ա��ID
						for(i=0;i<13;i++)
						{
							printf("%c",SerialNumber.Profiling_ID[i]);
						}					
						SetTextValue(3,1,(u8 *)SerialNumber.Profiling_ID);	//����������ʾѹ��Ա��ID
					}
					break;
				}
			
				case 3:
				{
					if(ScanFlag == 1)
					{
						strncpy((char *)SerialNumber.Mark,CacheData,14); 						//�ӻ��������и���ԭ�ϱ��
						for(i=0;i<14;i++)
						{
							printf("%c",SerialNumber.Mark[i]);
						}							
						SetTextValue(3,3,(u8 *)SerialNumber.Mark);					//����������ʾԭ�ϱ��
					}
					
					break;
				}
			
				case 4:
				{
					if(ScanFlag == 1)
					{
						strncpy((char *)SerialNumber.Facility,CacheData,14); 				//�ӻ��������и����豸���
						for(i=0;i<14;i++)
						{
						printf("%c",SerialNumber.Facility[i]);
						}							
					SetTextValue(3,6,(u8 *)SerialNumber.Facility);					//����������ʾ�豸���
					}
					
					break;
				}
				
				default :;
			
			} 

			OSTimeDly(10);	
    }

}

