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
#include <includes.h>
#include "const.h"
#include "PIONEER_Config.h"
/************************************************************************************
// ������ȫ�ֱ�������
*************************************************************************************/
#define OSFLAG_FSMC_BANK1	0x00000001	 // BANK1�жϱ�־
#define OSFLAG_FSMC_BANK2	0x00000002	 // BANK2�жϱ�־
#define OSFLAG_FSMC_BANK3	0x00000004	 // BANK3�жϱ�־
#define OSFLAG_FSMC_BANK4	0x00000008	 // BANK4�жϱ�־
#define OSFLAG_NET_RXINT	0x00000010	 // DM9000�����жϱ�־

/************************************************************************************
*
*       ϵͳ״̬��־����
*
*************************************************************************************/
extern OS_EVENT *ProductSem;                   			 //��Ʒ�����ź���
extern OS_EVENT *UART5Mutex;                    		 //����5�����ź���
extern OS_EVENT *UART3Sem;                           //����3�ź���
extern OS_EVENT *MaintainMbox;                       //������Ϣ��Ϣ����
extern OS_EVENT *PLCSem;														 //PLC�ź���	
extern OS_EVENT *PLCMbox;														 //PLC������Ϣ����
extern OS_EVENT *ResultSem;													 //����ϴ�OneNet
extern OS_EVENT *QualifiedSem;											 //�ϸ�ʱ���ź���
extern OS_EVENT *CameraSem;													 //����ͷ�ź���

extern OS_FLAG_GRP *OSFlagSys;

extern OS_EVENT *DisplayQ;					 // ��������ʾ�����¼���־ָ�붨��
extern OS_EVENT 	*RS485UartRdy;						// RS485�������ݽ�����ɱ�־�ź���ָ��




extern OS_EVENT 	*NBUartRdy;								// NB��ʹ�ô������ݽ�����ɱ�־�ź���ָ��
extern void 			*NBData[32];							// ���ڴ洢��NB���͵�����ָ������


extern OS_EVENT 	*NBDataQ;									// NB����������ݵ���Ϣ����ָ��
extern INT8U 		NBMemData[16][256];				// ���ڴ����洢��������Ҫ������

extern INT8U 		RTMemData[16][256];	

extern OS_MEM   *DisplayMem;				 // ���ڴ洢���ڴ�������ʾ���ݵĴ洢��������
extern OS_MEM 		*NBDataMem;								// �����ݴ���Ҫ��NB�����͵����ݵĴ洢����

extern OS_MEM   *RTDataMem;

extern OS_EVENT	*NBStateSem;							// ����֪ͨNB�����������������ź���ָ��
extern OS_EVENT	*NBUpdateSem;							// ����NB���������ڼ�ʱ��ɵ��ź���ָ��
extern OS_EVENT  *NBUartMutex;							// ʵ��NB��ʹ�ô��ڵĶ�ռʹ�õĻ����ź���

extern OS_EVENT  *Uart6Mutex;

extern OS_EVENT *FReadMBox;				   // Flsah���ݶ�ȡ�����¼���־ָ�붨��
extern OS_EVENT *FSaveMBox;				   // Flash���ݴ洢�����¼���־ָ�붨��
extern OS_EVENT *ComSem;            //����֪ͨͨ��������յ�������




/************************************************************************************
*
*   ���������ڴ����뼰��Ϣ���ж��� 
*
*************************************************************************************/
// �����������
//#define OSQ_WRITE_CMD_SIZE  512
//extern  OS_EVENT *OSQWriteCmd;
//extern  void *OSQWriteCmdTbl[OSQ_WRITE_CMD_SIZE];
//
//
//#define OSQ_OUT_DATA_SIZE  32
//extern  OS_EVENT *OSQOutData;
//extern  void *OSQOutDataTbl[OSQ_OUT_DATA_SIZE];
/************************************************************************************
*   UCOS-ii �����ջ����
*************************************************************************************/
extern  OS_STK   App_TaskStartStk[APP_TASK_START_STK_SIZE];

#if (TASK_IO_EN == 1)
	extern  OS_STK   App_TaskIOStk[APP_TASK_IO_STK_SIZE];
#endif

#if (TASK_TEST_EN == 1)
	extern  OS_STK   App_TaskTestStk[APP_TASK_TEST_STK_SIZE];   
#endif


#if (TASK_UART_EN == 1)
	extern  OS_STK   App_TaskUartStk[APP_TASK_UART_STK_SIZE];
#endif


#if (TASK_FLASH_EN == 1)
	extern OS_STK   FlashTaskStk[FLASH_TASK_STK_SIZE];
#endif

#if (TASK_DISPLAY_EN == 1)
	extern  OS_STK   DisplayTaskStk[DISPLAY_TASK_STK_SIZE];
#endif

#if (TASK_ENVIRONMENT_EN == 1)
	extern  OS_STK   EnvironmentTaskStk[ENVIRONMENT_TASK_STK_SIZE];
#endif

#if (TASK_NUMBER_EN == 1)
	extern  OS_STK   NumberTaskStk[NUMBER_TASK_STK_SIZE];
#endif

#if (TASK_PRESSURE_EN == 1)
  extern  OS_STK   PressureTaskStk[PRESSURE_TASK_STK_SIZE];
#endif

#if (TASK_PLC_EN == 1)
  extern  OS_STK   PLCTaskStk[PLC_TASK_STK_SIZE];
#endif

#if (TASK_SCAN_EN == 1)
	extern  OS_STK   ScanTaskStk[SCAN_TASK_STK_SIZE];
#endif

#if (TASK_QUALIFIED_EN == 1)
	extern  OS_STK   QualifiedTaskStk[QUALIFIED_TASK_STK_SIZE];
#endif

#if (TASK_PROCESSING_EN == 1)
	extern  OS_STK   ProcessingTaskStk[PROCESSING_TASK_STK_SIZE];
#endif




#if (TASK_CONDUCTIVITY_EN == 1)
	extern  OS_STK  App_TaskConductivityStk[APP_TASK_CONDUCTIVITY_STK_SIZE];
#endif

#if (TASK_RT_EN == 1)
	extern  OS_STK  App_TaskRTStk[APP_TASK_RT_STK_SIZE];
#endif

#if (TASK_NRT_EN == 1)
	extern  OS_STK  App_TaskNRTStk[APP_TASK_NRT_STK_SIZE];
#endif




//NB
#if (NBTX_TASK_EN == 1)
	extern OS_STK   NBTX_TASK_STK[NBTX_TASK_STK_SIZE];
#endif

#if (NBRV_TASK_EN == 1)
	extern OS_STK   NBRV_TASK_STK[NBRV_TASK_STK_SIZE];
#endif

#if (UPDATE_TASK_EN == 1)
	extern OS_STK   UPDATE_TASK_STK[UPDATE_TASK_STK_SIZE];
#endif


/************************************************************************************
*
*   ���������� 
*
*************************************************************************************/
extern  void  App_TaskIO               (void *p_arg);
extern  void  App_TaskTest             (void *p_arg);
extern  void  App_TaskUart             (void *p_arg);

extern  void  Flash_Task        		   (void *p_arg);
extern  void  Display_Task        		 (void *p_arg);
extern  void  Environment_Task				 (void *p_arg);
extern  void  Number_Task					     (void *p_arg);
extern  void  PLC_Task                 (void *p_arg);
extern  void  Pressure_Task					 	 (void *p_arg);
extern  void  Scan_Task				 				 (void *p_arg);
extern  void  Qualified_Task           (void *pdata);
extern  void  Processing_Task					 (void *p_arg);



extern  void  NB_TxTask      				 (void *p_arg);     // ����NB�����������
extern  void  NB_RvTask      				 (void *p_arg);
extern  void  NB_UpdateTask  				 (void *p_arg);
/***********************************************************************************/
// �ļ�����
/***********************************************************************************/
