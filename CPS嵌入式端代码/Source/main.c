/************************************************************************************/
// 引用外部头文件
#include "PIONEER_Config.h"
#include <includes.h>
#include "STM32F4_Head.h"
#include "UserVars.h"
#include "APP_Init.h"
#include "OSVars.h"
#include "const.h"
#include "MC_Print_inc.h"
/************************************************************************************/

/************************************************************************************/
// 常量及全局变量定义
/************************************************************************************/
static  void  App_TaskCreate       (void);
static  void  App_TaskStart        (void *p_arg);

//#define ASK_LEN 8
#define VALIDDATA_LEN 8

unsigned char buf[8]={0X01,0X03,0X00,0X00,0X00,0X01,0X84,0X0A};

//#define RS485BUFF_LEN 8

//LED0任务
//设置任务优先级
#define LED0_TASK_PRIO       			22
//设置任务堆栈大小
#define LED0_STK_SIZE  		    		64
//任务堆栈	
OS_STK LED0_TASK_STK[LED0_STK_SIZE];
//任务函数
void led0_task(void *pdata);


////LED1任务
////设置任务优先级
//#define LED1_TASK_PRIO       			23 
////设置任务堆栈大小
//#define LED1_STK_SIZE  					64
////任务堆栈
//OS_STK LED1_TASK_STK[LED1_STK_SIZE];
////任务函数
//void led1_task(void *pdata);
/*
*********************************************************************************************************
*                                                main()
*
* Description : This is the standard entry point for C code.  It is assumed that your code will call
*               main() once you have performed all necessary initialization.
*
* Argument(s) : none.
*
* Return(s)   : none.
*********************************************************************************************************
*/



int  main (void)
{
	CPU_INT08U  os_err;
	OS_CPU_SR cpu_sr=0;
	API_Init();             // 应用功能初始化
	
  delay_ms(10);  
	CPU_IntDis();	        // 清除所有中断
	OSInit();               // Initialize "uC/OS-II, The Real-Time Kernel".         

    // 创建App_TaskStart任务
	os_err = OSTaskCreate((void (*)(void *)) App_TaskStart,     // Create the start task.
                          (void          * ) 0,
                          (OS_STK        * )&App_TaskStartStk[APP_TASK_START_STK_SIZE - 1],
                          (INT8U           ) APP_TASK_START_PRIO
                         );
    // 设置任务名字
    //OSTaskNameSet(APP_TASK_START_PRIO, (CPU_INT08U *)"Start Task", &os_err);  

	//OSFlagSys = OSFlagCreate(0, (INT8U *)&os_err); // 创建标志变量

                          
                          
	OSTimeSet(0);  // 初始化系统时钟
                          
    #if (IWDG_EN > 0)         // 看门狗使能             
			IWDG_Feed();   // 清除看门狗
    #endif
    OSStart();                    // 启动操作系统运行, 让操作系统接管软件运行 
                                  // Start multitasking (i.e. give control to uC/OS-II). 

    return (0);                   // 永远不会运行到这里
}

/*
*********************************************************************************************************
*                                          App_TaskStart()
*
* Description : The startup task.  The uC/OS-II ticker should only be initialize once multitasking starts.
*
* Argument(s) : p_arg       Argument passed to 'App_TaskStart()' by 'OSTaskCreate()'.
*
* Return(s)   : none.
*
* Caller(s)   : This is a task.
*
* Note(s)     : none.
*********************************************************************************************************/
static  void  App_TaskStart (void *p_arg)
{
	INT32U  TaskCount;
//	INT16U  TaskFlag;
	
	(void)p_arg;    
    
	#if (IWDG_EN > 0) 
	IWDG_Feed();
	#endif	

    UserVars.Flag |= OS_START_FLAG;      // 设置操作系统启动标志
	#if (OS_TASK_STAT_EN > 0)
    OSStatInit();                        // Determine CPU capacity.                              
	#endif
	
 	App_TaskCreate();
	TaskCount = 0;
	UserVars.TaskRunStatus = 0; 
	UserVars.TimerCount = 0;
    while (1) 
	{                                                           // Task body, always written as an infinite loop.       
		OSTimeDly(10);
		#if (IWDG_EN > 0) 
			IWDG_Feed();                               // 硬件喂狗  
		#endif
        
		TaskCount++;
		if ((TaskCount%10)==0)
		{
			UserVars.TimerCount++;
		}
		if (TaskCount>6000) // 大于1分钟		 
		{
				
		   TaskCount = 0;  
		   if (UserVars.TaskRunStatus == TASK_FLAG)	 // 判断任务运行状态
		   {
			    UserVars.TaskRunStatus = 0;           // 清除任务运行标志 
		   }		 
		   else
		   {
				#if (DEBUG_APP_EN == 1)		  
			    printf("TaskMain：任务出错，出错代码：%x\r\n\r\n",UserVars.TaskRunStatus);	
				#endif			
//			    for (;;);  // 等待看门狗复位
		   }
	    } 
	}
}

/*
*********************************************************************************************************
*                                            App_TaskCreate()
*
* Description : Create the application tasks.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : App_TaskStart().
*
* Note(s)     : none.
*********************************************************************************************************
*/ 
static  void  App_TaskCreate (void)
{
  CPU_INT08U  os_err;
	INT8U err;
	INT8U OS_Err;
	
		os_err = OSTaskCreate((void (*)(void *)) led0_task,
                          (void          * ) 0,
                          (OS_STK        * )&LED0_TASK_STK[LED0_STK_SIZE - 1],
                          (INT8U           ) LED0_TASK_PRIO
                          );
													
	#if (TASK_IO_EN == 1)
   	os_err = OSTaskCreate((void (*)(void *)) App_TaskIO,
                          (void          * ) 0,
                          (OS_STK        * )&App_TaskIOStk[APP_TASK_IO_STK_SIZE - 1],
                          (INT8U           ) APP_TASK_IO_PRIO
                          );
		if(OS_ERR_NONE == os_err)
		{
			#if (DEBUG_APP_EN == 1)
				printf("TaskCreate：Creat App_TaskIO Success!\r\n");
			#endif
		}
		else
		{
		#if (DEBUG_APP_EN == 1)
				printf("TaskCreate：Creat App_TaskIO Error!\r\n");
			#endif
		}
		
	#endif
	
	
	#if (TASK_TEST_EN == 1)
   	os_err = OSTaskCreate((void (*)(void *)) App_TaskTest,
                          (void          * ) 0,
                          (OS_STK        * )&App_TaskTestStk[APP_TASK_TEST_STK_SIZE - 1],
                          (INT8U           ) APP_TASK_TEST_PRIO
                          );

	if(OS_ERR_NONE == os_err)
		{
			#if (DEBUG_APP_EN == 1)
				printf("TaskCreate：Creat App_TaskTest Success!\r\n");
			#endif
		}
		else
		{
		#if (DEBUG_APP_EN == 1)
				printf("TaskCreate：Creat App_TaskTest Error!\r\n");
			#endif
		}
	#endif
	
	#if (TASK_NB_EN == 1)												
		#if (NBTX_TASK_EN == 1)
			os_err = OSTaskCreate((void (*)(void *)) NB_TxTask,
														(void          * ) 0,
														(OS_STK        * )&NBTX_TASK_STK[NBTX_TASK_STK_SIZE - 1],
														(INT8U           ) NBTX_TASK_PRIO
														);
			if(OS_ERR_NONE == os_err)
			{
				#if (DEBUG_APP_EN == 1)
					printf("TaskCreate：Creat NB_TxTask Success!\r\n");
				#endif
			}
			else
			{
			#if (DEBUG_APP_EN == 1)
					printf("TaskCreate：Creat NB_TxTask Error!\r\n");
				#endif
			}
			#endif
		
		#if (NBRV_TASK_EN == 1)
			os_err = OSTaskCreate((void (*)(void *)) NB_RvTask,
														(void          * ) 0,
														(OS_STK        * )&NBRV_TASK_STK[NBRV_TASK_STK_SIZE - 1],
														(INT8U           ) NBRX_TASK_PRIO
														);
			if(OS_ERR_NONE == os_err)
			{
				#if (DEBUG_APP_EN == 1)
					printf("TaskCreate：Creat NB_RvTask Success!\r\n");
				#endif
			}
			else
			{
			#if (DEBUG_APP_EN == 1)
					printf("TaskCreate：Creat NB_RvTask Error!\r\n");
				#endif
			}
		#endif
		
		#if (UPDATE_TASK_EN == 1)
			os_err = OSTaskCreate((void (*)(void *)) NB_UpdateTask,
														(void          * ) 0,
														(OS_STK        * )&UPDATE_TASK_STK[UPDATE_TASK_STK_SIZE - 1],
														(INT8U           ) UPDATE_TASK_PRIO
														);
			if(OS_ERR_NONE == os_err)
			{
				#if (DEBUG_APP_EN == 1)
					printf("TaskCreate：Creat NB_UpdateTask Success!\r\n");
				#endif
			}
			else
			{
			#if (DEBUG_APP_EN == 1)
					printf("TaskCreate：Creat NB_UpdateTask Error!\r\n");
				#endif
			}
		#endif
														
	#endif												
													
	#if (TASK_UART_EN == 1)
   	os_err = OSTaskCreate((void (*)(void *))TaskUart,
                          (void          * ) 0,
                          (OS_STK        * )&TaskUartStk[TASK_UART_STK_SIZE - 1],
                          (INT8U           ) TASK_UART_PRIO
                          );
		#if (DEBUG_APP_EN == 1)
			printf("TaskCreate：Creat App_TaskUart!\r\n");
		#endif
	#endif

													
	
		#if (TASK_FLASH_EN == 1)													
		os_err = OSTaskCreate(
													(void(*)(void *))Flash_Task,
													(void          *)0,
													(OS_STK        *)&FlashTaskStk[FLASH_TASK_STK_SIZE-1],
													(INT8U          )FLASH_TASK_PRIO
													
													);
		#if (DEBUG_APP_EN == 1)
			printf("TaskCreate：Creat Flash_Task Success!\r\n");
		#endif
	#endif			
													
	#if (TASK_DISPLAY_EN == 1)													
		os_err = OSTaskCreate(
													(void(*)(void *))Display_Task,
													(void          *)0,
													(OS_STK        *)&DisplayTaskStk[DISPLAY_TASK_STK_SIZE-1],
													(INT8U          )DISPLAY_TASK_PRIO
													
													);
		#if (DEBUG_APP_EN == 1)
			printf("TaskCreate：Creat Display_Task Success!\r\n");
		#endif
	#endif
											
	#if (TASK_ENVIRONMENT_EN == 1)													
		os_err = OSTaskCreate(
													(void(*)(void *))Environment_Task,
													(void          *)0,
													(OS_STK        *)&EnvironmentTaskStk[ENVIRONMENT_TASK_STK_SIZE-1],
													(INT8U          )ENVIRONMENT_TASK_PRIO
													
													);
		#if (DEBUG_APP_EN == 1)
			printf("TaskCreate：Creat Environment_Task Success!\r\n");
		#endif
	#endif

	#if (TASK_NUMBER_EN == 1)													
		os_err = OSTaskCreate(
													(void(*)(void *))Number_Task,
													(void          *)0,
													(OS_STK        *)&NumberTaskStk[NUMBER_TASK_STK_SIZE-1],
													(INT8U          )NUMBER_TASK_PRIO
													
													);
		#if (DEBUG_APP_EN == 1)
			printf("TaskCreate：Creat Number_Task Success!\r\n");
		#endif
	#endif
													
	#if (TASK_PRESSURE_EN == 1)													
		os_err = OSTaskCreate(
													(void(*)(void *))Pressure_Task,
													(void          *)0,
													(OS_STK        *)&PressureTaskStk[PRESSURE_TASK_STK_SIZE-1],
													(INT8U          )PRESSURE_TASK_PRIO
													
													);
		#if (DEBUG_APP_EN == 1)
			printf("TaskCreate：Creat Pressure_Task Success!\r\n");
		#endif
	#endif	

	#if (TASK_PLC_EN == 1)													
		os_err = OSTaskCreate(
													(void(*)(void *))PLC_Task,
													(void          *)0,
													(OS_STK        *)&PLCTaskStk[PLC_TASK_STK_SIZE-1],
													(INT8U          )PLC_TASK_PRIO
													
													);
		#if (DEBUG_APP_EN == 1)
			printf("TaskCreate：Creat PLC_Task Success!\r\n");
		#endif
	#endif																								

	#if (TASK_SCAN_EN == 1)													
		os_err = OSTaskCreate(
													(void(*)(void *))Scan_Task,
													(void          *)0,
													(OS_STK        *)&ScanTaskStk[SCAN_TASK_STK_SIZE-1],
													(INT8U          )SCAN_TASK_PRIO
													
													);
		#if (DEBUG_APP_EN == 1)
			printf("TaskCreate：Creat ScanTask Success!\r\n");
		#endif
	#endif

													
													
													
	#if (TASK_QUALIFIED_EN == 1)													
		os_err = OSTaskCreate(
													(void(*)(void *))Qualified_Task,
													(void          *)0,
													(OS_STK        *)&QualifiedTaskStk[QUALIFIED_TASK_STK_SIZE-1],
													(INT8U          )QUALIFIED_TASK_PRIO
													
													);
		#if (DEBUG_APP_EN == 1)
			printf("TaskCreate：Creat Qualified_Task Success!\r\n");
		#endif
	#endif

	#if (TASK_PROCESSING_EN == 1)													
		os_err = OSTaskCreate(
													(void(*)(void *))Processing_Task,
													(void          *)0,
													(OS_STK        *)&ProcessingTaskStk[PROCESSING_TASK_STK_SIZE-1],
													(INT8U          )PROCESSING_PRIO
													
													);
		#if (DEBUG_APP_EN == 1)
			printf("TaskCreate：Creat Processing_Task Success!\r\n");
		#endif
	#endif
			


		//创建通信方式:
	ProductSem=OSSemCreate(0);												//产品个数信号量											
	UART5Mutex=OSMutexCreate(1,&err);									//串口5互斥信号量			
	PLCSem=OSSemCreate(0);
	UART3Sem=OSSemCreate(0);                          //串口3信号量
	MaintainMbox=OSMboxCreate((void *)0);							//保养信息消息邮箱
	PLCMbox=OSMboxCreate((void *)0);									//PLC数据消息邮箱
	ResultSem=OSSemCreate(0);													//产品结果信号量
	QualifiedSem=OSSemCreate(0);											//合格信号量
	CameraSem=OSSemCreate(0);													//摄像头信号量												
	

	

	NBUartRdy   = OSSemCreate(0);								// 创建通知UART5接收数据完成（NB）的信号量
	NBDataQ     = OSQCreate(NBData, 32);					// 创建NB接收数据的消息队列
	NBDataMem   = OSMemCreate((void*)NBMemData,16,256,&err);		// 创建存放采集PLC所获得数据的存储分区
	
	RTDataMem   = OSMemCreate((void*)RTMemData,16,256,&err);
	
	NBStateSem  = OSSemCreate(0);							// 创建用于通知OneNet返回的命令相应数据
	NBUpdateSem = OSSemCreate(0);							// 创建用于NB更新生存期计时完成的信号量
	NBUartMutex = OSMutexCreate(4,&OS_Err);		// 创建用户保证NB所使用串口互斥使用的互斥信号量
	
	Uart6Mutex = OSMutexCreate(5,&OS_Err);
	
	FReadMBox   = OSMboxCreate((void*)0);							// Flsah数据读取邮箱创建
	FSaveMBox   = OSMboxCreate((void*)0);							// Flash数据存储邮箱创建
	ComSem      = OSSemCreate(0);              //通信任务数据接收结束信号量
	

}

//LED0任务
void led0_task(void *pdata)
{	 	
	while(1)
	{
		//printf("123");
		LED0=0;
		delay_ms(5000);
		LED0=1;
		OSTimeDlyHMSM(0,0,1,0);
	};
}

//LED1任务
void led1_task(void *pdata)
{	  
	while(1)
	{
		LED1=0;
		delay_ms(300);
		LED1=1;
		delay_ms(300);
	};
}
/***********************************************************************************/
// 文件结束
/***********************************************************************************/


