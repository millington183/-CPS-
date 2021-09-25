/************************************************************************************
*  Copyright (c), 2019, ��������ѧ
*            All rights reserved.
*
* http:  www.jxust.edu.cn
* Email: 
*
* File name: TaskIO.h
* Project  : STM32F4XXϵ��ģ�����
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  �ǻ۹����о���
* Version: 0.01
* Date:    2019.12.12			
* Email:   
* 
* Description: ���ļ��ǲ���ϵͳ����ȫ�ֱ�������, �ͻ����԰ѺͲ���ϵͳ��ص�ȫ�ֱ������õ�����;
*
* Others: none;
*
* Function List:
*		
* History:
*   1. Author:			wangzl  
*	   Version: 	 		0.02
*	   Date:         	2019.12.12
*    Modification: 	none
*
*************************************************************************************/
/************************************************************************************/
// �����ⲿͷ�ļ�
/************************************************************************************/
#include "OSVars.h"

/************************************************************************************
// ������ȫ�ֱ�������
*************************************************************************************/
OS_EVENT *ProductSem;                   			 //��Ʒ�����ź���
OS_EVENT *UART5Mutex;                    			 //����5�����ź���
OS_EVENT *UART3Sem;                            //����3�ź���
OS_EVENT *MaintainMbox;                        //������Ϣ��Ϣ����
OS_EVENT *PLCSem;															 //PLC�ź���
OS_EVENT *PLCMbox;														 //PLC������Ϣ����
OS_EVENT *ResultSem;													 //����ϴ�OneNet
OS_EVENT *QualifiedSem;												 //�ϸ�ʱ���ź���
OS_EVENT *CameraSem;													 //����ͷ�ź���

OS_FLAG_GRP *OSFlagSys;

OS_EVENT *OSMboxADC;         // ADCת���������

OS_EVENT *DisplayQ;					 // ��������ʾ�����¼���־ָ�붨��
OS_EVENT 	*RS485UartRdy;						// RS485�������ݽ�����ɱ�־�ź���ָ��



OS_EVENT 	*NBUartRdy;								// NB��ʹ�ô������ݽ�����ɱ�־�ź���ָ��
void 			*NBData[32];							// ���ڴ洢��NB���͵�����ָ������


OS_EVENT 	*NBDataQ;									// NB����������ݵ���Ϣ����ָ��
INT8U 		NBMemData[16][256];				// ���ڴ����洢��������Ҫ������

INT8U 		RTMemData[16][256];	

OS_MEM 		*NBDataMem;								// �����ݴ���Ҫ��NB�����͵����ݵĴ洢����

OS_MEM    *RTDataMem;

OS_MEM   *DisplayMem;				 // ���ڴ洢���ڴ�������ʾ���ݵĴ洢��������
OS_EVENT	*NBStateSem;							// ����֪ͨNB�����������������ź���ָ��
OS_EVENT	*NBUpdateSem;							// ����NB���������ڼ�ʱ��ɵ��ź���ָ��
OS_EVENT  *NBUartMutex;							// ʵ��NB��ʹ�ô��ڵĶ�ռʹ�õĻ����ź���

OS_EVENT  *Uart6Mutex;

OS_EVENT *FReadMBox;				 // Flsah���ݶ�ȡ�����¼���־ָ�붨��
OS_EVENT *FSaveMBox;				 // Flash���ݴ洢�����¼���־ָ�붨��

OS_EVENT *ComSem;            //����֪ͨͨ��������յ�������



/************************************************************************************
*   UCOS-ii �����ջ����
*************************************************************************************/
__align(8) OS_STK   App_TaskStartStk[APP_TASK_START_STK_SIZE];

#if (TASK_IO_EN == 1)
__align(8) OS_STK   App_TaskIOStk[APP_TASK_IO_STK_SIZE];
#endif

#if (TASK_TEST_EN == 1)
__align(8) OS_STK   App_TaskTestStk[APP_TASK_TEST_STK_SIZE];  
#endif


#if (TASK_UART_EN == 1)
__align(8) OS_STK   TaskUartStk[APP_TASK_UART_STK_SIZE];
#endif


#if (TASK_FLASH_EN == 1)
__align(8) OS_STK   FlashTaskStk[FLASH_TASK_STK_SIZE];
#endif

#if (TASK_DISPLAY_EN == 1)
__align(8) OS_STK   DisplayTaskStk[DISPLAY_TASK_STK_SIZE];
#endif

#if (TASK_ENVIRONMENT_EN == 1)
__align(8) OS_STK   EnvironmentTaskStk[ENVIRONMENT_TASK_STK_SIZE];
#endif

#if (TASK_NUMBER_EN == 1)
__align(8) OS_STK   NumberTaskStk[NUMBER_TASK_STK_SIZE];
#endif

#if (TASK_PRESSURE_EN == 1)
__align(8) OS_STK   PressureTaskStk[PRESSURE_TASK_STK_SIZE];
#endif

#if (TASK_PLC_EN == 1)
__align(8) OS_STK   PLCTaskStk[PLC_TASK_STK_SIZE];
#endif

#if (TASK_SCAN_EN == 1)
__align(8) OS_STK  ScanTaskStk[SCAN_TASK_STK_SIZE];
#endif

#if (TASK_QUALIFIED_EN == 1)
__align(8) OS_STK  	QualifiedTaskStk[QUALIFIED_TASK_STK_SIZE];
#endif


#if (TASK_PROCESSING_EN == 1)
__align(8) OS_STK  ProcessingTaskStk[PROCESSING_TASK_STK_SIZE];
#endif


//NB       // ����NB���������ջ
#if (NBTX_TASK_EN == 1)
__align(8) OS_STK   NBTX_TASK_STK[NBTX_TASK_STK_SIZE];
#endif

#if (NBRV_TASK_EN == 1)
__align(8) OS_STK   NBRV_TASK_STK[NBRV_TASK_STK_SIZE];
#endif

#if (UPDATE_TASK_EN == 1)
__align(8) OS_STK   UPDATE_TASK_STK[UPDATE_TASK_STK_SIZE];              
#endif



/***********************************************************************************/
// �ļ�����
/***********************************************************************************/



