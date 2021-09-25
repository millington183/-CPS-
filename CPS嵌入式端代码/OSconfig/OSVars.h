/************************************************************************************
*  Copyright (c), 2019, 江西理工大学
*            All rights reserved.
*
* http:  www.jxust.edu.cn
* Email: 
*
* File name: TaskIO.h
* Project  : STM32F4XX系列模块软件
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  智慧工厂研究所
* Version: 0.01
* Date:    2019.12.12			
* Email:   
* 
* Description: 本文件是操作系统任务全局变量定义, 客户可以把和操作系统相关的全局变量设置到这里;
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
// 引用外部头文件
/************************************************************************************/
#include <includes.h>
#include "const.h"
#include "PIONEER_Config.h"
/************************************************************************************
// 常量及全局变量定义
*************************************************************************************/
#define OSFLAG_FSMC_BANK1	0x00000001	 // BANK1中断标志
#define OSFLAG_FSMC_BANK2	0x00000002	 // BANK2中断标志
#define OSFLAG_FSMC_BANK3	0x00000004	 // BANK3中断标志
#define OSFLAG_FSMC_BANK4	0x00000008	 // BANK4中断标志
#define OSFLAG_NET_RXINT	0x00000010	 // DM9000接收中断标志

/************************************************************************************
*
*       系统状态标志定义
*
*************************************************************************************/
extern OS_EVENT *ProductSem;                   			 //产品个数信号量
extern OS_EVENT *UART5Mutex;                    		 //串口5互斥信号量
extern OS_EVENT *UART3Sem;                           //串口3信号量
extern OS_EVENT *MaintainMbox;                       //保养信息消息邮箱
extern OS_EVENT *PLCSem;														 //PLC信号量	
extern OS_EVENT *PLCMbox;														 //PLC数据消息邮箱
extern OS_EVENT *ResultSem;													 //结果上传OneNet
extern OS_EVENT *QualifiedSem;											 //合格时间信号量
extern OS_EVENT *CameraSem;													 //摄像头信号量

extern OS_FLAG_GRP *OSFlagSys;

extern OS_EVENT *DisplayQ;					 // 串口屏显示队列事件标志指针定义
extern OS_EVENT 	*RS485UartRdy;						// RS485串口数据接收完成标志信号量指针




extern OS_EVENT 	*NBUartRdy;								// NB所使用串口数据接收完成标志信号量指针
extern void 			*NBData[32];							// 用于存储待NB发送的数据指针数组


extern OS_EVENT 	*NBDataQ;									// NB任务接收数据的消息队列指针
extern INT8U 		NBMemData[16][256];				// 用于创建存储分区所需要的数组

extern INT8U 		RTMemData[16][256];	

extern OS_MEM   *DisplayMem;				 // 用于存储需在串口屏显示内容的存储分区定义
extern OS_MEM 		*NBDataMem;								// 用于暂存需要有NB任务发送的数据的存储分区

extern OS_MEM   *RTDataMem;

extern OS_EVENT	*NBStateSem;							// 用于通知NB服务器反馈的数据信号量指针
extern OS_EVENT	*NBUpdateSem;							// 用于NB更新生存期计时完成的信号量指针
extern OS_EVENT  *NBUartMutex;							// 实现NB所使用串口的独占使用的互斥信号量

extern OS_EVENT  *Uart6Mutex;

extern OS_EVENT *FReadMBox;				   // Flsah数据读取邮箱事件标志指针定义
extern OS_EVENT *FSaveMBox;				   // Flash数据存储邮箱事件标志指针定义
extern OS_EVENT *ComSem;            //用于通知通信任务接收到的数据




/************************************************************************************
*
*   发送命令内存申请及消息队列定义 
*
*************************************************************************************/
// 发送命令队列
//#define OSQ_WRITE_CMD_SIZE  512
//extern  OS_EVENT *OSQWriteCmd;
//extern  void *OSQWriteCmdTbl[OSQ_WRITE_CMD_SIZE];
//
//
//#define OSQ_OUT_DATA_SIZE  32
//extern  OS_EVENT *OSQOutData;
//extern  void *OSQOutDataTbl[OSQ_OUT_DATA_SIZE];
/************************************************************************************
*   UCOS-ii 任务堆栈定义
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
*   任务函数定义 
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



extern  void  NB_TxTask      				 (void *p_arg);     // 声明NB任务的任务函数
extern  void  NB_RvTask      				 (void *p_arg);
extern  void  NB_UpdateTask  				 (void *p_arg);
/***********************************************************************************/
// 文件结束
/***********************************************************************************/
