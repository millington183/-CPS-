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
#include "OSVars.h"

/************************************************************************************
// 常量及全局变量定义
*************************************************************************************/
OS_EVENT *ProductSem;                   			 //产品个数信号量
OS_EVENT *UART5Mutex;                    			 //串口5互斥信号量
OS_EVENT *UART3Sem;                            //串口3信号量
OS_EVENT *MaintainMbox;                        //保养信息消息邮箱
OS_EVENT *PLCSem;															 //PLC信号量
OS_EVENT *PLCMbox;														 //PLC数据消息邮箱
OS_EVENT *ResultSem;													 //结果上传OneNet
OS_EVENT *QualifiedSem;												 //合格时间信号量
OS_EVENT *CameraSem;													 //摄像头信号量

OS_FLAG_GRP *OSFlagSys;

OS_EVENT *OSMboxADC;         // ADC转换完成邮箱

OS_EVENT *DisplayQ;					 // 串口屏显示队列事件标志指针定义
OS_EVENT 	*RS485UartRdy;						// RS485串口数据接收完成标志信号量指针



OS_EVENT 	*NBUartRdy;								// NB所使用串口数据接收完成标志信号量指针
void 			*NBData[32];							// 用于存储待NB发送的数据指针数组


OS_EVENT 	*NBDataQ;									// NB任务接收数据的消息队列指针
INT8U 		NBMemData[16][256];				// 用于创建存储分区所需要的数组

INT8U 		RTMemData[16][256];	

OS_MEM 		*NBDataMem;								// 用于暂存需要有NB任务发送的数据的存储分区

OS_MEM    *RTDataMem;

OS_MEM   *DisplayMem;				 // 用于存储需在串口屏显示内容的存储分区定义
OS_EVENT	*NBStateSem;							// 用于通知NB服务器反馈的数据信号量指针
OS_EVENT	*NBUpdateSem;							// 用于NB更新生存期计时完成的信号量指针
OS_EVENT  *NBUartMutex;							// 实现NB所使用串口的独占使用的互斥信号量

OS_EVENT  *Uart6Mutex;

OS_EVENT *FReadMBox;				 // Flsah数据读取邮箱事件标志指针定义
OS_EVENT *FSaveMBox;				 // Flash数据存储邮箱事件标志指针定义

OS_EVENT *ComSem;            //用于通知通信任务接收到的数据



/************************************************************************************
*   UCOS-ii 任务堆栈定义
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


//NB       // 定义NB任务的任务栈
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
// 文件结束
/***********************************************************************************/



