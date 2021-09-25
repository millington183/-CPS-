/************************************************************************************
*  Copyright (c), 2019, ��������ѧ
*            All rights reserved.
*
* http:  www.jxust.edu.cn
* Email: 
*
* File name: NB-IoT.c
* Project  : NB-IoT�ײ㺯��
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  
* Version: 0.01
* Date:    2019.08.15			
* Email:   
* 
* Description: ���ļ������������֡��ͨ��NB-IoTģ�鷢�����ݵ�OneNet
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
#include "includes.h"
#include "NB_IoT.h"
#include "STM32F4_Head.h"
#include "UserVars.h"
#include "OSVars.h"
#include "string.h"
#include "stdio.h"


/************************************************************************************/
// ������ȫ�ֱ�������
/************************************************************************************/
#define RV_BUF_LEN	256

//extern INT8U NBRvDelay;
//extern INT8U HaveOk;			// ���ڵ��յ���NB�������ݰ�����OK���͡�+MIPLWRITE��ʱ��ʾ���������Ok��

INT8U RvBuf[RV_BUF_LEN] = {0};																							// �ݴ�Ӵ���5�յ�������																									// ���ڱ���NB�豸�������
char testtmp=0x30;

INT8U Close_Date[]={"AT+MIPLCLOSE=0\r\n"};																// ȡ���豸��OneNetƽ̨��ע���ATָ��
INT8U Create_Date[]={"AT+MIPLCREATE=49,130031F10003F2002304001100000000000000123138332E3233302E34302E34303A35363833000131F30008C000000000,0,49,0\r\n"};
INT8U AddObj_Date[]={"AT+MIPLADDOBJ=0,3200,1,\"1\",1,0\r\n"};							// ����object�����󣩵�ATָ��
INT8U DiscoverRsp_Date[]={"AT+MIPLDISCOVERRSP=0,3200,1,4,\"5750\"\r\n"};	// ģ����ӦOneNetƽ̨��Discover�����ATָ��
INT8U Open_Date[]={"AT+MIPLOPEN=0,3000,30\r\n"};													// �豸ע�ᵽOneNetƽ̨ATָ��
INT8U Del_Data[]={"AT+MIPLDELETE=0\r\n"};																	// ɾ���豸ʵ�壨��ɾ���Ѷ��ĵ�Object��instance��resource)
INT8U Query_Data[]={"AT+MIPLOPEN?\r\n"};																	// ��ѯ��¼״��
INT8U NRB_Data[]={"AT+NRB\r\n"};
INT8U Update_Data[]={"AT+MIPLUPDATE=0,0,0\r\n"};												// ������ʱ���������,����ǰһ�εĴ����ʱ��

/***********************************************************************************
* Function: nbiot_Create;
*
* Description: �����豸ʵ��;
*              
* Input:  none;
*
* Return: 1���ɹ�
*					0��ʧ��
*
* Note:   none;
************************************************************************************/
INT8U nbiot_Create(void)
{
	INT16U i,j;
	INT8U result;
	INT8U OS_Err;
	
	OSMutexPend(NBUartMutex, 0, &OS_Err);			// ����NB���ڻ����ź���
	
	NBRvDelay = 0;
	
	Uart_Write(UART5_ID,Create_Date,sizeof(Create_Date));	// ��������
	
	#if (NBRV_TASK_EN==1)
	OSSemPend(NBStateSem, 500, &OS_Err );			// ������ר�ŵ�NB���ڽ�������ͨ�����������ȷ��മ������
	#else
	OSSemPend(NBUartRdy, 500, &OS_Err);				// δ������ר�ŵ�NB���ڽ�������
	#endif
	
	for(i=0; i<RV_BUF_LEN; i++)
	{
		RvBuf[i] = 0;													// ��մ洢����	
	}
	if((UART5_RX_STA&0x8000))
	{
		for(j=0; j<(UART5_RX_STA&0X3FFF); j++)
		{
			RvBuf[j] = UART5_RX_BUF[j];					// ��ȡ����1����
			UART5_RX_BUF[j] = 0;								// �������1���ջ�����������
		}
		UART5_RX_STA=0;
		
		OSMutexPost(NBUartMutex);							// �ͷ�NB���ڻ����ź���
		
		#if (DEBUG_APP_EN == 1)
			printf("Create�յ���������%s\r\n", RvBuf);
		#endif
		
		if((RvBuf[19] == 'O') && (RvBuf[20] == 'K'))
		{
			printf("�����豸ʵ��ɹ�\r\n");
			result = 1;
		}
		else
		{
			#if (DEBUG_APP_EN == 1)
				printf("�����豸ʵ��ʧ��\r\n");
			#endif
			result = 0;
		}
	}
	
	return result;
}

/***********************************************************************************
* Function: nbiot_AddObj;
*
* Description: ����OBJ������
*              
* Input:  none;
*
* Return: 1���ɹ�
*					0��ʧ��
*
* Note:   none;
************************************************************************************/
INT8U nbiot_AddObj(void)
{
	INT16U i,j;
	INT8U result;
	INT8U OS_Err;
	
	OSMutexPend(NBUartMutex, 0, &OS_Err);			// ����NB���ڻ����ź���
	
	NBRvDelay = 0;
	Uart_Write(UART5_ID,AddObj_Date,sizeof(AddObj_Date));
	
	#if (NBRV_TASK_EN == 1)
	OSSemPend(NBStateSem, 500, &OS_Err );			// ������ר�ŵ�NB���ڽ�������ͨ�����������ȷ��മ������
	#else
	OSSemPend(NBUartRdy, 500, &OS_Err);				// δ������ר�ŵ�NB���ڽ�������
	#endif
	
	if((UART5_RX_STA&0x8000))
	{
		for(i=0; i<RV_BUF_LEN; i++)
		{
			RvBuf[i] = 0;													// ��մ洢����	
		}
		for(j=0; j<(UART5_RX_STA&0X3FFF); j++)
		{
			RvBuf[j] = UART5_RX_BUF[j];					// ��ȡ����1����
			UART5_RX_BUF[j] = 0;								// �������1���ջ�����������
		}
		UART5_RX_STA=0;
		
		OSMutexPost(NBUartMutex);							// �ͷ�NB���ڻ����ź���
		
		#if (DEBUG_APP_EN == 1)
			printf("Addobj�յ���������%s\r\n", RvBuf);
		#endif
		
		if((RvBuf[2] == 'O') && (RvBuf[3] == 'K'))
		{
			printf("����OBJ�����óɹ�\r\n");
			result = 1;
		}
		else
		{
			#if (DEBUG_APP_EN == 1)
				printf("����OBJ������ʧ��\r\n");
			#endif
			result = 0;
		}
	}
	
	return result;
}

/***********************************************************************************
* Function: nbiot_DiscoverRsp;
*
* Description: ����Resource��������
*              
* Input:  none;
*
* Return: 1���ɹ�
*					0��ʧ��
*
* Note:   none;
************************************************************************************/
INT8U nbiot_DiscoverRsp(void)
{
	INT16U i,j;
	INT8U result;
	INT8U OS_Err;
	
	OSMutexPend(NBUartMutex, 0, &OS_Err);			// ����NB���ڻ����ź���
	
	NBRvDelay = 0;
	
	Uart_Write(UART5_ID,DiscoverRsp_Date,sizeof(DiscoverRsp_Date));
	
	#if (NBRV_TASK_EN == 1)
	OSSemPend(NBStateSem, 500, &OS_Err );			// ������ר�ŵ�NB���ڽ�������ͨ�����������ȷ��മ������
	#else
	OSSemPend(NBUartRdy, 500, &OS_Err);				// δ������ר�ŵ�NB���ڽ�������
	#endif
	
	if((UART5_RX_STA&0x8000))
	{
		for(i=0; i<RV_BUF_LEN; i++)
		{
			RvBuf[i] = 0;													// ��մ洢����	
		}
		for(j=0; j<(UART5_RX_STA&0X3FFF); j++)
		{
			RvBuf[j] = UART5_RX_BUF[j];					// ��ȡ����1����
			UART5_RX_BUF[j] = 0;								// �������1���ջ�����������
		}
		UART5_RX_STA=0;
		
		OSMutexPost(NBUartMutex);							// �ͷ�NB���ڻ����ź���
		
		#if (DEBUG_APP_EN == 1)
			printf("DiscoverRsp�յ���������%s\r\n", RvBuf);
		#endif
		
		if((RvBuf[2] == 'O') && (RvBuf[3] == 'K'))
		{
			#if (DEBUG_APP_EN == 1)
				printf("����Resource�������óɹ�\r\n");
			#endif
			//++NB_OK;
			result = 1;
		}
		else
		{
			#if (DEBUG_APP_EN == 1)
				printf("����Resource��������ʧ��\r\n");
			#endif
			result = 0;
		}
	}
	
	return result;
}

/***********************************************************************************
* Function: nbiot_Connect;
*
* Description: ��ƽ̨ע���¼;
*              
* Input:  none;
*
* Return: 1��NB-IoTע��ɹ�
*					0��NB-IoTע��ʧ��
*
* Note:   none;
************************************************************************************/
INT8U nbiot_Connect(void)
{
	INT16U i,j;
	INT8U result;
	INT8U OS_Err;
	
	OSMutexPend(NBUartMutex, 0, &OS_Err);			// ����NB���ڻ����ź���
	
	NBRvDelay = 1;
	Uart_Write(UART5_ID,Open_Date,sizeof(Open_Date));
	
	#if (NBRV_TASK_EN == 1)
	OSSemPend(NBStateSem, 500, &OS_Err );			// ������ר�ŵ�NB���ڽ�������ͨ�����������ȷ��മ������
	#else
	OSSemPend(NBUartRdy, 500, &OS_Err);				// δ������ר�ŵ�NB���ڽ�������
	#endif
	
	if((UART5_RX_STA&0x8000))
	{
		for(i=0; i<RV_BUF_LEN; i++)
		{
			RvBuf[i] = 0;													// ��մ洢����	
		}
		for(j=0; j<(UART5_RX_STA&0X3FFF); j++)
		{
			RvBuf[j] = UART5_RX_BUF[j];					// ��ȡ����1����
			UART5_RX_BUF[j] = 0;								// �������1���ջ�����������
		}
		UART5_RX_STA=0;
		
		OSMutexPost(NBUartMutex);							// �ͷ�NB���ڻ����ź���
		
		#if (DEBUG_APP_EN == 1)
			printf("Connect�յ���������%s\r\n", RvBuf);
		#endif
		
		for(i=0; i<RV_BUF_LEN; i++)
		{
			if(RvBuf[i] == 0x36)
			{
				#if (DEBUG_APP_EN == 1)
					printf("��ƽ̨ע���¼�ɹ�\r\n");
				#endif
				result = 1;
				break;																	// �յ��˵�¼�ɹ��ı�־��6���������ַ�����
			}
		}
		
		if(i >= RV_BUF_LEN)
		{
			#if (DEBUG_APP_EN == 1)
				printf("��ƽ̨ע���¼ʧ��\r\n");
			#endif
			result = 0;
		}
	}	
	return result;
}

/***********************************************************************************
* Function: nbiot_Query;
*
* Description:  ��ѯ��¼״̬����
*              
* Input:  none;
*
* Return: 1��NB-IoT�Ѿ���¼
*					0��NB-IoTδ��¼
*
* Note:   none;
************************************************************************************/
INT8U nbiot_Query(void)							// ��ѯ��¼״̬����
{
	INT16U i,j;
	INT8U result;
	INT8U OS_Err;
	
	OSMutexPend(NBUartMutex, 0, &OS_Err);			// ����NB���ڻ����ź���
	
	NBRvDelay = 1;
	
	Uart_Write(UART5_ID,Query_Data,sizeof(Query_Data));
	
	#if (NBRV_TASK_EN == 1)
	OSSemPend(NBStateSem, 500, &OS_Err );			// ������ר�ŵ�NB���ڽ�������ͨ�����������ȷ��മ������
	#else
	OSSemPend(NBUartRdy, 500, &OS_Err);				// δ������ר�ŵ�NB���ڽ�������
	#endif
	
	if((UART5_RX_STA&0x8000))
	{
		for(i=0; i<RV_BUF_LEN; i++)
		{
			RvBuf[i] = 0;													// ��մ洢����	
		}
		for(j=0; j<(UART5_RX_STA&0X3FFF); j++)
		{
			RvBuf[j] = UART5_RX_BUF[j];					// ��ȡ����1����
			UART5_RX_BUF[j] = 0;								// �������1���ջ�����������
		}
		UART5_RX_STA=0;
		
		OSMutexPost(NBUartMutex);							// �ͷ�NB���ڻ����ź���
		
		#if (DEBUG_APP_EN == 1)
			printf("Query�յ���������%s\r\n", RvBuf);
		#endif
		
		for(i=0; i<RV_BUF_LEN; i++)
		{
			if(RvBuf[i] == 0x36)
			{
				#if (DEBUG_APP_EN == 1)
						printf("ģ���ѵ�¼OneNet\r\n");
				#endif
				result = 1;
				break;																	// �յ��˵�¼�ɹ��ı�־��6���������ַ�����
			}
		}
			
		if(i >= RV_BUF_LEN)
		{
			#if (DEBUG_APP_EN == 1)
				printf("ģ��δ��¼OneNet\r\n");
			#endif
			result = 0;
		}
	}
	
	return result;
}

/***********************************************************************************
* Function: nbiot_Update;
*
* Description: ���´��ʱ��;
*              
* Input:  none;
*
* Return: 1���ɹ�
*					0��ʧ��
*
* Note:   none;
************************************************************************************/
INT8U nbiot_Update(void)
{
	INT16U i,j;
	INT8U result;
	INT8U OS_Err;
	
	OSMutexPend(NBUartMutex, 0, &OS_Err);			// ����NB���ڻ����ź���
	
	NBRvDelay = 1;
	Uart_Write(UART5_ID,Update_Data,sizeof(Update_Data));
	
	#if (NBRV_TASK_EN == 1)
	OSSemPend(NBStateSem, 500, &OS_Err );			// ������ר�ŵ�NB���ڽ�������ͨ�����������ȷ��മ������
	#else
	OSSemPend(NBUartRdy, 500, &OS_Err);				// δ������ר�ŵ�NB���ڽ�������
	#endif
	
	if((UART5_RX_STA&0x8000))
	{
		for(i=0; i<RV_BUF_LEN; i++)
		{
			RvBuf[i] = 0;													// ��մ洢����	
		}
		for(j=0; j<(UART5_RX_STA&0X3FFF); j++)
		{
			RvBuf[j] = UART5_RX_BUF[j];					// ��ȡ����1����
			UART5_RX_BUF[j] = 0;								// �������1���ջ�����������
		}
		UART5_RX_STA=0;
		
		OSMutexPost(NBUartMutex);							// �ͷ�NB���ڻ����ź���
		
		#if (DEBUG_APP_EN == 1)
			printf("nbiot_Update��������%s\r\n", RvBuf);
		#endif
		
		for(i=0; i<RV_BUF_LEN-1; i++)
		{
			if((RvBuf[i] == 0x31) && (RvBuf[i+1] == 0x31))
			{
				#if (DEBUG_APP_EN == 1)
						printf("���ʱ����³ɹ�\r\n");
				#endif
				result = 1;
				break;																	// �յ��˵�¼�ɹ��ı�־��6���������ַ�����
			}
		}
			
		if(i >= RV_BUF_LEN)
		{
			#if (DEBUG_APP_EN == 1)
				printf("���ʱ�����ʧ��\r\n");
			#endif
			result = 0;
		}
	}
	
	return result;
}


/***********************************************************************************
* Function: nbiot_Nofity;
*
* Description: �������ݵ�ƽ̨;
*              
* Input:  ��Ҫ���͵��ַ���ָ��;
*
* Return: 1���������ݳɹ�
*					0����������ʧ��
*
* Note:   none;
************************************************************************************/
INT8U nbiot_Nofity(INT8U *NBBuff)
{
	INT8U flag=0;
	INT16U i,j;
	INT8U OS_Err;	
	
	INT8U Notify_Date[128]={0};
	
	sprintf((char*)Notify_Date,"AT+MIPLNOTIFY=0,0,3200,0,5750,1,%d,\"%s\",0,0\r\n",strlen((char*)NBBuff),NBBuff);
	
	OSMutexPend(NBUartMutex, 0, &OS_Err);			// ����NB���ڻ����ź���
	
	NBRvDelay = 0;
	Uart_Write(UART5_ID,Notify_Date,sizeof(Notify_Date));// �ϴ�����				
	
	#if (NBRV_TASK_EN == 1)
	OSSemPend(NBStateSem, 500, &OS_Err );			// ������ר�ŵ�NB���ڽ�������ͨ�����������ȷ��മ������
	#else
	OSSemPend(NBUartRdy, 500, &OS_Err);				// δ������ר�ŵ�NB���ڽ�������
	#endif
	
	if(0 == HaveOk)
	{
		if((UART5_RX_STA&0x8000))
		{
			for(i=0; i<RV_BUF_LEN; i++)
			{
				RvBuf[i] = 0;													// ��մ洢����	
			}
			for(j=0; j<(UART5_RX_STA&0X3FFF); j++)
			{
				RvBuf[j] = UART5_RX_BUF[j];					// ��ȡ����1����
				UART5_RX_BUF[j] = 0;								// �������1���ջ�����������
			}
			UART5_RX_STA=0;
			
			OSMutexPost(NBUartMutex);							// �ͷ�NB���ڻ����ź���
			
			#if (DEBUG_APP_EN == 1)
				printf("Nofity�յ���������%s\r\n", RvBuf);
			#endif
			
			if((RvBuf[2] == 'O') && (RvBuf[3] == 'K'))
			{
				#if (DEBUG_APP_EN == 1)
					printf("�ϴ����ݳɹ�\r\n");
				#endif
				flag = 1;
			}
			else
			{
				#if (DEBUG_APP_EN == 1)
					printf("�ϴ�����ʧ��\r\n");
				#endif
				flag = 0;
			}
		}
	}
	else		// HaveOK=1
	{
		#if (DEBUG_APP_EN == 1)
			printf("�ϴ����ݳɹ�\r\n");
		#endif
		
		HaveOk = 0;
		
		OSMutexPost(NBUartMutex);												// �ͷ�NB���ڻ����ź���
		
		flag = 1;
	}
		
	return flag;
}

/***********************************************************************************
* Function: nbiot_Del;
*
* Description:  ɾ���豸ʵ��
*              
* Input:  none;
*
* Return: 1��ɾ���豸ʵ��ɹ�
*					0��ɾ���豸ʵ��ʧ��
*
* Note:   none;
************************************************************************************/
INT8U nbiot_Del(void)								// ɾ���豸ʵ��
{
	INT16U i,j;
	INT8U result;
	INT8U OS_Err;
	
	OSMutexPend(NBUartMutex, 0, &OS_Err);			// ����NB���ڻ����ź���
	
	NBRvDelay = 0;
	Uart_Write(UART5_ID,Del_Data,sizeof(Del_Data));
	
	#if (NBRV_TASK_EN == 1)
	OSSemPend(NBStateSem, 500, &OS_Err);			// ������ר�ŵ�NB���ڽ�������ͨ�����������ȷ��മ������
	#else
	OSSemPend(NBUartRdy, 500, &OS_Err);				// δ������ר�ŵ�NB���ڽ�������
	#endif
	
	if((UART5_RX_STA&0x8000))
	{
		for(i=0; i<RV_BUF_LEN; i++)
		{
			RvBuf[i] = 0;													// ��մ洢����	
		}
		for(j=0; j<(UART5_RX_STA&0X3FFF); j++)
		{
			RvBuf[j] = UART5_RX_BUF[j];					// ��ȡ����1����
			UART5_RX_BUF[j] = 0;								// �������1���ջ�����������
		}
		UART5_RX_STA=0;
		
		OSMutexPost(NBUartMutex);							// �ͷ�NB���ڻ����ź���
		
		#if (DEBUG_APP_EN == 1)
			printf("Del�յ���������%s\r\n", RvBuf);
		#endif
		
		if((RvBuf[2] == 'O') && (RvBuf[3] == 'K'))
		{
			#if (DEBUG_APP_EN == 1)
				printf("ɾ���豸ʵ��ɹ�\r\n");
			#endif
			result = 1;
		}
		else
		{
			#if (DEBUG_APP_EN == 1)
				printf("ɾ���豸ʵ��ʧ��\r\n");
			#endif
			result = 0;
		}
	}
	
	return result;
}


/***********************************************************************************
* Function: nbiot_Reset;
*
* Description:  ��λģ��;
*              
* Input:  none;
*
* Return: 1����λNB-IoT�ɹ�
*					0����λNB-IoTʧ��
*
* Note:   none;
************************************************************************************/
INT8U nbiot_Reset(void)
{
	INT16U i,j;
	INT8U result;
	INT8U OS_Err;
	
	OSMutexPend(NBUartMutex, 0, &OS_Err);			// ����NB���ڻ����ź���
	
	NBRvDelay = 0;
	Uart_Write(UART5_ID,NRB_Data,sizeof(NRB_Data));
	
	#if (NBRV_TASK_EN == 1)
	OSSemPend(NBStateSem, 500, &OS_Err );			// ������ר�ŵ�NB���ڽ�������ͨ�����������ȷ��മ������
	#else
	OSSemPend(NBUartRdy, 500, &OS_Err);				// δ������ר�ŵ�NB���ڽ�������
	#endif
	
	if((UART5_RX_STA&0x8000))
	{
		for(i=0; i<RV_BUF_LEN; i++)
		{
			RvBuf[i] = 0;													// ��մ洢����	
		}
		for(j=0; j<(UART5_RX_STA&0X3FFF); j++)
		{
			RvBuf[j] = UART5_RX_BUF[j];					// ��ȡ����1����
			UART5_RX_BUF[j] = 0;								// �������1���ջ�����������
		}
		UART5_RX_STA=0;
		
		OSMutexPost(NBUartMutex);							// �ͷ�NB���ڻ����ź���
		
		#if (DEBUG_APP_EN == 1)
			printf("Reset�յ���������%s\r\n", RvBuf);
		#endif
		
		if((RvBuf[2] == 'R') && (RvBuf[3] == 'E'))
		{
			#if (DEBUG_APP_EN == 1)
				printf("NBģ�鸴λ�ɹ�\r\n");
			#endif
			result = 1;
		}
		else
		{
			#if (DEBUG_APP_EN == 1)
				printf("NBģ�鸴λʧ��\r\n");
			#endif
			result = 0;
		}
	}
	
	return result;
}

/***********************************************************************************/
// �ļ�����
/***********************************************************************************/
