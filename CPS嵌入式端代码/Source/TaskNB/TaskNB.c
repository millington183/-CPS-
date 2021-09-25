/************************************************************************************
*  Copyright (c), 2019, ��������ѧ
*            All rights reserved.
*
* http:  www.jxust.edu.cn
* Email: 
*
* File name: TaskNB.c
* Project  : STM32F4XXϵ��ģ�����
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  
* Version: 0.01
* Date:    2019.12.20			
* Email:   
* 
* Description: ���ļ������������֡��ͨ��NB-IoTģ�鷢�����ݵ�OneNet
*
* Others: none;
*
* Function List:
*		
*   1. Author:			  
*	   Version: 	 		0.02
*	   Date:         	2019.12.12
*    Modification: 	none
*	   
*
*************************************************************************************/
#include "PIONEER_Config.h"
#if (TASK_NB_EN == 1)
#include "STM32F4_Head.h"
#include "UserVars.h"
#include "OSVars.h"
#include "NB_IoT.h"
#include "stdio.h"
#include "string.h"
#include "hmi_driver.h"
#include "hmi_user_uart.h"
#include "cmd_queue.h"
#include "cmd_process.h"

/************************************************************************************/
// ������ȫ�ֱ�������
/************************************************************************************/

#define RS485BUFF_LEN 46
#define VALIDDATA_LEN 150



//char RS485_buff[RS485BUFF_LEN];											// �洢��RS485��ȡ������
// �����豸��ȡ���ݳ���ʱ��������Ϣ�ϴ���OneNet
INT8U ReadErrInfo[]="ERR01";
/************************************************************************************/




/***********************************************************************************
* Function: NB_TxTask;
*
* Description: NBIoT���ݷ�������;
*              
* Input:  none;
*
* Return: none;
*
* Note:   ������������Ϣ���н����豸���������ݣ�Ȼ��ͨ��NB���緢�͵�OneNet����Ҫע���NB
*					���ӷ�������״̬ά��
*
************************************************************************************/
#if (NBTX_TASK_EN == 1)
void NB_TxTask(void *pdata)
{
	INT8U *Msg,*MemPtr;																 			// ��Ϣָ�뼰��Ϣ��ŵĴ洢��ָ��
	INT8U OS_Err;
	INT16U i;
	INT8U GetData[VALIDDATA_LEN];														// �洢��Ϣ�����յ�������
	INT8U NB_flag,send_flag;
	INT8U Create_flag,Obj_flag,Rsp_flag,connect_flag;
	//INT8U DataNB[]="��¼NB";
	for(i=0; i<VALIDDATA_LEN; i++)
	{
		GetData[i] = 0;
	}
	ConnectStatus = 0;																					// ��ʼ��NB��¼״̬Ϊ��¼
	//OSQPost(NBDataQ,DataNB);
	while(1)
	{
		UserVars.TaskRunStatus |= NBTX_TASK_FLAG;    // ���ñ���������״̬��־
		Msg = (INT8U*)OSQPend(NBDataQ,0,&OS_Err);									// �ȴ����ո�����������ʾ����
		
		if(OS_ERR_NONE == OS_Err)
		{
			memset(GetData,0,VALIDDATA_LEN);
			if(*Msg != 'E')
			{
				MemPtr = Msg;																						// ���ִ洢����ʼ��ַ���Ա��������ͷ�
				for(i=0; i<VALIDDATA_LEN; i++)													// �Ӵ洢���ж�ȡ���յ�����Ϣ��GetData����
				{
					GetData[i] = *Msg;
					Msg++;
				}
				OSMemPut(NBDataMem,(void*)MemPtr);											// �ͷŴ洢��
			}
			else
			{
				MemPtr = Msg;																						// ���ִ洢����ʼ��ַ���Ա��������ͷ�
				for(i=0; i<strlen((char *)ReadErrInfo); i++)																			// �Ӵ洢���ж�ȡ���յ�����Ϣ��GetData����
				{
					GetData[i] = *Msg;
					Msg++;
				}
				OSMemPut(NBDataMem,(void*)MemPtr);											// �ͷŴ洢��
			}
			
			// ͨ��NB-IoTģ�飬������֡���͸�������
			NB_flag = 0;																						// NB�����Ƿ�ɹ����ܱ�־
			send_flag = 0;																					// ���ݷ����Ƿ�ɹ��ı�־
			DelCnt = 0;
			
			while(!NB_flag)
			{
				if(1 == ConnectStatus)																// ���Ѿ���¼������Խ������ݷ���
				{
					send_flag = nbiot_Nofity((INT8U*)GetData);						
					if(1 == send_flag)
					{
						NB_flag = 1;																			// ��ʾ���������Ѿ�������ɣ����Բ��ٽ��뷢������ѭ��������
						DelCnt = 0;																				// ɾ���豸ʵ���������
						break;
					}		
					else
					{
						nbiot_Del();																			// ɾ���豸ʵ��
						ConnectStatus = 0;																// ����δ��¼
						NB_flag = 0;																			// NB�����Ƿ�ɹ����ܱ�־
						DelCnt++;																					// ɾ���豸ʵ�������1					
					}
				}
				
				if(0 == ConnectStatus)																// ����ѯ��¼״̬������δ��¼������е�¼����
				{
					
					Create_flag = 0;
					Obj_flag = 0;
					connect_flag = 0;
					Rsp_flag = 0;
					
					if(nbiot_Query())																		// ��ѯ�Ƿ��¼
					{
						printf("C\r\n");
						ConnectStatus = 1;
					}
					else
					{
						if(nbiot_Create())																	// ���Դ����豸ʵ��
						{
							Create_flag = 1;
						}
						
						if(Create_flag == 1)
						{
							
							if(nbiot_AddObj())																// ���Զ���Object��Դ
							{
								Obj_flag = 1;
							}
						}
						
						if((Create_flag == 1) &&(Obj_flag == 1))
						{
							if(nbiot_DiscoverRsp())														// ���Զ���Resource��Դ
							{
								Rsp_flag = 1;
							}
						}
						
						if((Create_flag == 1) && (Obj_flag ==1) && (Rsp_flag == 1))
						{
							if(nbiot_Connect())															// ���Ե�¼OneNet
							{
								connect_flag = 1;
								ConnectStatus = 1;
							}
						}
						if((Create_flag == 0) || (Obj_flag == 0) || (connect_flag == 0) || (Rsp_flag == 0))
						{
							nbiot_Del();																	// ɾ���豸ʵ��
							ConnectStatus = 0;														// ����δ��¼
							DelCnt++;																			// ɾ���豸ʵ�������1
						}
						if(DelCnt >= 3)				 // ��ɾ���豸ʵ��3���ϣ���λNBģ�鲢��λϵͳ
						{			
							nbiot_Reset();
							OSTaskSuspend(APP_TASK_START_PRIO);
							OSTaskSuspend(NBTX_TASK_PRIO);								// �����������񣬵ȴ����Ź����ں�λ
						}
					}	// ������if(nbiot_Query())				
				}// ������if(0 == ConnectStatus)
			}// ������while(!NB_flag)
		}// ������if(OS_ERR_NONE == OS_Err)
		
		//OSTimeDlyHMSM(0,0,0,300);	
	}
}
#endif

/***********************************************************************************
* Function: NB_RvTask;
*
* Description: NBIoT���ݽ�������;
*              
* Input:  none;
*
* Return: none;
*
* Note:   ���������ڽ���UART1����OneNet�����ݣ����ڲ�������������н��������ڷ�����Ϣ����
*					ֱ��ͨ����Ϣ���䣬���͸�NB���ݷ����������غ�����
*					�����Ƿ�Ϊ4�������
*					1�������յ����ݲ�������+��
*					2�������յ����ݰ�����+���������ǡ�+MIPLWRITE��
*					3�������յ����ݰ�����+MIPLWRITE������ͬʱ������OK��
*					4�������յ����ݽ�������+MIPLWRITE���������
*					��������ҪӦ������������⣬һ���ǽ��յ��������м��з������ݷ��صġ�OK��������
*					OneNet�·���д���������Ҫ�����������Ƕ�����������ʱ��Nb���ڷ��ͺͽ���
*					������뻥���ʹ�ô��ڣ���Ҫ����NB���ڽ�����������ȼ����ߣ����Ƚ���Ӧ����֡
*					���͸�OneNetƽ̨��Ȼ��Ž��г���������ϴ���
************************************************************************************/
#if (NBRV_TASK_EN == 1)
#define SIDataAdress 0
void NB_RvTask(void *pdata)
{
	INT8U OS_Err,i,len,Num;
	INT8U NBRvData[150];																// ��Ž��յ���д����ԭʼ����
	INT8U ResposeData[32];															// ������ɵ�д��������֡
	INT8U msgid[10]={0};																// �����ȡ������msgid��
	INT8U StartNum;																			// ���,7��Ч���ݵ���ʼλ��
	INT8U StartNum1;																		// ���,8��Ч���ݵ���ʼλ��
	INT8U StartFlag;																		// ��ʼ�ı�־λ
	INT8U DataLen;																			// �����Ч���ݵ��ֽڳ���
	INT8U SIData[100];																	// ��ŷ��ͼ��ʱ������      �洢��EEPROM�е�ַΪ��1000
	INT8U RunCnt;																				// ���п��Ʊ���
	INT8U nbnbnb[100];
	INT8U PlusPosi;
	
	
	while(1)
	{
		UserVars.TaskRunStatus |= NBRV_TASK_FLAG;    // ���ñ���������״̬��־
		OSSemPend(NBUartRdy, 0, &OS_Err);									// �ȴ�NB���ݽ�����ɵ��ź���
		
		len = (UART5_RX_STA&0X3FFF);
		for(i=0; i<len; i++)
		{
			if(UART5_RX_BUF[i] == '+')
			{
				PlusPosi = i;
				break;
			}
		}
		if(i >= len)
		{
			// ��1��������յ������ݲ�������+������˵����OneNet��д�������޹أ�ֱ��֪ͨ��������
			OSSemPost(NBStateSem);
		}
		else
		{
			// �ж��Ƿ��ǡ�+MIPLWRITE��
			if((UART5_RX_BUF[PlusPosi] == '+') && (UART5_RX_BUF[PlusPosi+5] == 'W')
				 && (UART5_RX_BUF[PlusPosi+6] == 'R') && (UART5_RX_BUF[PlusPosi+7] == 'I'))
			{
				//OSMutexPend(NBUartMutex, 0, &OS_Err);			// ����NB���ڻ����ź���
				
				// ɨ�����յ������ݣ����Ƿ������OK��
				HaveOk = 0;
				for(i=0; i<len-1; i++)
				{
					if((UART5_RX_BUF[i] == 'O') &&(UART5_RX_BUF[i+1] == 'K'))
					{
						HaveOk = 1;
						OSSemPost(NBStateSem);										// ��3�����,��NB�����������ź���
						break;
					}
				}
				
				OSMutexPend(NBUartMutex, 0, &OS_Err);					// ����NB���ڻ����ź������ȴ�NB���������ͷŻ����ź���
			
				// ��3��4���������ԡ�+MIPLWRITE���Ĵ���
				// ��ȡ�Ӵ��ڽ��յ�������
				if((UART5_RX_STA&0x8000))
				{
					printf("%s",UART5_RX_BUF);              //��ӡ������5��������onenet��д����
					for(i=0; i<len; i++)
					{
						NBRvData[i] = UART5_RX_BUF[i];				// ��ȡ����5����
						UART5_RX_BUF[i] = 0;									// �������5���ջ�����������
					}
					UART5_RX_STA=0;
				}
				  
				printf("%s",NBRvData);                //��ӡ������5��������onenet��д����
				
				// ��ȡmsgid		
				for(i=0; i<10; i++)
				{
					msgid[i] = 0;
				}
				i= 0;
				PlusPosi = PlusPosi + 13;								// ����ָ�뵽��Ч���ݵ���ʼλ��
				while(NBRvData[PlusPosi] != ',')					
				{
					msgid[i] = NBRvData[PlusPosi];
					PlusPosi++;
					i++;
				}
				
				// ��OneNet����д��������֡
				for(i=0; i<32; i++)
				{
					ResposeData[i] = 0;
				}
				sprintf((char*)ResposeData,"AT+MIPLWRITERSP=0,%s,2\r\n",msgid);
				
				RunCnt=0;
				Num=0;
				
				while((0 == RunCnt) && (Num < 3))										// ��γ��Է�����Ӧ����֡��ֱ���յ���OK���򳬹�3��
				{
					Uart_Write(UART5_ID,ResposeData,sizeof(ResposeData));											// ����д��Ӧ����֡
					Num++;
					OSSemPend(NBUartRdy, 0, &OS_Err);									// �ȴ�OneNet�ظ���OK��
					if((UART5_RX_STA&0x8000))
					{
						if((UART5_RX_BUF[2] == 'O') && (UART5_RX_BUF[3] == 'K'))
						{
							RunCnt = 1;
						}			
						else
						{
							RunCnt = 0;
						}
						UART5_RX_STA=0;
					}
				}
		
				OSMutexPost(NBUartMutex);							// �ͷ�NB���ڻ����ź���
				

				for(i=0;i<len; i++)
				{		
						if(NBRvData[i-1] == ','&&NBRvData[i] == 'M')
					{
							StartNum=i;      	//��¼��Ч���ݿ�ʼ��λ��
							break;
					}
				}
		
				if(NBRvData[i-2] == '7')
				{

						for(i=StartNum;i<len; i++)
					{	
						if((NBRvData[i] == 'M')&&(NBRvData[i+1] == ','))
						{
							Maintenance.Facility=NBRvData[i+2];
							printf("%d\r\n",Maintenance.Facility-'0');
							
						}
						if((NBRvData[i] == ',')&&(NBRvData[i+1] == 'D'))
						{
							Maintenance.NBTimeNum=NBRvData[i-1];						//��Ҫ����ʣ�������
							printf("���յ�������%d\r\n",Maintenance.NBTimeNum-'0');
							SetScreen(11);//���õ�ǰ����Ϊ��
							//SetScreen(11);
							SetTextInt32(11,3,Maintenance.NBTimeNum-'0',0,1);
							
							printf("���յ����\r\n");
						}
						if((NBRvData[i] == ',')&&(NBRvData[i+1] == 'H'))
						{
							Maintenance.NBTimeNum=NBRvData[i-1];						//��Ҫ����ʣ���Сʱ��
							printf("���յ�������%d\r\n",Maintenance.NBTimeNum-'0');
							SetScreen(12);//���õ�ǰ����Ϊʱ
							//SetScreen(12);
							SetTextInt32(12,3,Maintenance.NBTimeNum-'0',0,1);
							
							printf("���յ�ʱ��\r\n");
						}
						if((NBRvData[i] == ',')&&(NBRvData[i+1] == 'M')&&(NBRvData[i+2] == ',')&&(NBRvData[i+3] == '0'))
						{
							Maintenance.NBTimeNum=NBRvData[i-1];						//��Ҫ����ʣ��ķ�����
							printf("���յ�������%d\r\n",Maintenance.NBTimeNum-'0');
							
							SetScreen(13);//���õ�ǰ����Ϊ��
							//SetScreen(13);
							printf("���յ��ֵ�\r\n");
							SetTextInt32(13,3,Maintenance.NBTimeNum-'0',0,1);
							
							printf("���յ��ֵ�\r\n");
						}
						if((NBRvData[i] == ',')&&(NBRvData[i+1] == 'S'))
						{
							Maintenance.NBTimeNum=NBRvData[i-1];						//��Ҫ����ʣ�������
							printf("���յ�������%d\r\n",Maintenance.NBTimeNum-'0');
							
							SetScreen(14);//���õ�ǰ����Ϊ��
							
							SetTextInt32(14,3,Maintenance.NBTimeNum-'0',0,1);
							printf("���յ����\r\n");
						}
						if((NBRvData[i] == ',')&&(NBRvData[i+1] == 'N'))
						{
							
							SetScreen(15);//���õ�ǰ����Ϊ��												//�Ѿ���ʱ��Ҫ���̱���
							printf("��Ҫ���̱���\r\n");
						}
						if(NBRvData[i] == ',' && NBRvData[i + 1] == '0')
								DataLen= i- StartNum;       //��¼��Ч���ݳ���   
						
					}
				}
				
				
				if(NBRvData[i-2] == '8')
				{
					printf("���յ�8��\r\n");
						for(i=StartNum;i<len; i++)
					{	
						if((NBRvData[i] == 'M')&&(NBRvData[i+1] == ','))
						{
							Maintenance.Facility=NBRvData[i+2];
							printf("%d\r\n",Maintenance.Facility-'0');
							
						}
						if((NBRvData[i] == ',')&&(NBRvData[i+1] == 'D'))
						{
							Maintenance.NBTimeNum=NBRvData[i-1];						//��Ҫ����ʣ�������
							printf("���յ�������%d\r\n",Maintenance.NBTimeNum-'0');
							SetScreen(11);//���õ�ǰ����Ϊ��
							SetScreen(11);
							SetTextInt32(11,3,Maintenance.NBTimeNum-'0',0,1);
							
							printf("���յ����\r\n");
						}
						if((NBRvData[i] == ',')&&(NBRvData[i+1] == 'H'))
						{
							sprintf((char *)Maintenance.TimeNum,"%d%d",NBRvData[i-2]-'0',NBRvData[i-1]-'0');//��Ҫ����ʣ���Сʱ��
							//printf("���յ�������%d\r\n",NBRvData[i-2]-'0');
							//printf("���յ�������%d\r\n",NBRvData[i-1]-'0');
							SetScreen(12);//���õ�ǰ����Ϊʱ
							SetScreen(12);//���õ�ǰ����Ϊʱ
							SetTextValue(12,3,Maintenance.TimeNum);//�ڴ���������ʾʣ�����Сʱ
							printf("���յ�ʱ��\r\n");
						}
						if((NBRvData[i] == ',')&&(NBRvData[i+1] == 'M')&&(NBRvData[i+2] == ',')&&(NBRvData[i+3] == '0'))
						{
			
							sprintf((char *)Maintenance.TimeNum,"%d%d",NBRvData[i-2]-'0',NBRvData[i-1]-'0');//��Ҫ����ʣ��ķ�����
							printf("���յ�������%d\r\n",NBRvData[i-2]-'0');
							printf("���յ�������%d\r\n",NBRvData[i-1]-'0');
							SetScreen(13);//���õ�ǰ����Ϊ��
							SetScreen(13);
							SetTextValue(13,3,Maintenance.TimeNum);//�ڴ���������ʾʣ����ٷ���
							printf("���յ��ֵ�\r\n");
						}
						if((NBRvData[i] == ',')&&(NBRvData[i+1] == 'S'))
						{
							sprintf((char *)Maintenance.TimeNum,"%d%d",NBRvData[i-2]-'0',NBRvData[i-1]-'0');//��Ҫ����ʣ��ķ�����
							printf("���յ�������%d\r\n",NBRvData[i-2]-'0');
							printf("���յ�������%d\r\n",NBRvData[i-1]-'0');
							SetScreen(14);//���õ�ǰ����Ϊ��
							SetScreen(14);
							SetTextValue(14,3,Maintenance.TimeNum);//�ڴ���������ʾʣ���������
							printf("���յ����\r\n");
						}
//						if((NBRvData[i] == ',')&&(NBRvData[i+1] == 'N'))
//						{
//							SetScreen(15);
//							SetScreen(15);
//							printf("��Ҫ���̱���\r\n");
//						}
						if(NBRvData[i] == ',' && NBRvData[i + 1] == '0')
								DataLen= i- StartNum;       //��¼��Ч���ݳ���   
					}
				}
			
				memcpy(SIData, &NBRvData[StartNum], DataLen);
				//printf("%d\r\n",DataLen);
		  	printf("��Ч����%s\r\n",SIData);         //��ӡ��Ч����
				
						// ��ȡ���ݷ��ͼ��������
	  //					SendIntervalSecond =  (NBRvData[j+3]-0x30)*10 +(NBRvData[j+4]-0x30);
						
						// ��ȡ���ݷ��ͼ���ĺ�����
		//				SendIntervalMilli = (NBRvData[j+5]-0x30)*100 + (NBRvData[j+6]-0x30)*10 + (NBRvData[j+7]-0x30);		// ��ȡ���ݷ��ͼ���ĺ�����
					
						// ����������EEPROM
//						EEPROM_Write(SIDataAdress,SIData,sizeof(SIData));
//					  delay_ms(50);
//				    EEPROM_Read(SIDataAdress,nbnbnb,sizeof(SIData));
				//	  printf("EEPROM��%s\r\n",nbnbnb);
					if((NBRvData[StartNum] == 'R') && (NBRvData[StartNum+1] == 'S'))
					{
						nbiot_Reset();
						nbiot_Del();																	// ɾ���豸ʵ��
						OSTaskSuspend(APP_TASK_START_PRIO);
						OSTaskSuspend(NBTX_TASK_PRIO);								// �����������񣬵ȴ����Ź����ں�λ
					}
					
					// ��ȡ�������ݶԣ��ɰ��������if������
					
			//	}
			}
			else
			{
				// ��2��������յ������ݰ�����+�����������ǡ�+MIPLWRITE��
				OSSemPost(NBStateSem);
			}
		}
		
		//OSTimeDlyHMSM(0,0,0,50);
	}
}
#endif

/***********************************************************************************
* Function: NB_UpdateTask;
*
* Description: NBIoT���´��������;
*              
* Input:  none;
*
* Return: none;
*
* Note:   ���������ڸ�����ʱ�����NB-IoT��¼OneNet�Ĵ����
*
************************************************************************************/
#if (UPDATE_TASK_EN == 1)
void NB_UpdateTask(void *pdata)
{		
	u8 OS_Err;
	
//	TIM5_Int_Init(1000-1,7200-1);										// ��ʱ����100ms
	
	while(1)
	{
		UserVars.TaskRunStatus |= UPDATE_TASK_FLAG;    // ���ñ���������״̬��־
		if(1 == ConnectStatus)
		{
			NBUpdateCnt = 0;														// ��ʱ��������
			TIM_Cmd(TIM3,ENABLE);												// ������ʱ��3
			
			OSSemPend(NBUpdateSem, 0, &OS_Err );				// �ȴ���ʱ��ɺ��յ��ź���
			
			if(!nbiot_Update())													// ���и��´��ʱ�����
			{
				if(nbiot_Query())													// ��ѯ�Ƿ��¼
				{
					if(!nbiot_Update())
					{
						ConnectStatus = 0;
					}
				}
				else
				{
					ConnectStatus = 0;
				}
			}			
		}
		else
		{
			delay_ms(1000);
		}	
	}
}
#endif


#endif


