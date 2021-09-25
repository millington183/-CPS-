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
* Description: 本文件负责操作系统各个任务优先级和堆栈配置;
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
#ifndef  __APP_CFG_H__
#define  __APP_CFG_H__

/*
*********************************************************************************************************
*                                       MODULE ENABLE / DISABLE
*********************************************************************************************************
*/


/**********************************************************************************************************
*                         操作系统任务优先级定义
**********************************************************************************************************/	
#define  APP_TASK_START_PRIO          2

#define  APP_TASK_IO_PRIO             4
//#define  APP_TASK_TEST_PRIO						5      
//NB
#define  NBTX_TASK_PRIO               6
#define  NBRX_TASK_PRIO               7
#define  UPDATE_TASK_PRIO             8

#define  	TASK_UART_PRIO							18
#define  	FLASH_TASK_PRIO          		4        	// TaskFlash Flash任务优先级
#define 	DISPLAY_TASK_PRIO						12				// TaskDisplay 串口屏任务优先级
#define 	ENVIRONMENT_TASK_PRIO      	16				// TaskEnvironment 环境任务优先级
#define  	NUMBER_TASK_PRIO    				9					// TaskNumber 产品个数任务优先级
#define  	PRESSURE_TASK_PRIO          19        	// TaskPressure 压力传感器任务优先级
#define  	PLC_TASK_PRIO          			10        // TaskPLC 压机设备数据任务优先级
#define  	SCAN_TASK_PRIO    					11				// TaskScan 扫码枪任务优先级
#define  	QUALIFIED_TASK_PRIO    			14				// TaskQualified 合格产品任务优先级
#define  	PROCESSING_PRIO           	13        // TaskProcessing 数据处理任务优先级




/*
*********************************************************************************************************
*                                            TASK STACK SIZES
*                             Size of the task stacks (# of OS_STK entries)
*********************************************************************************************************
*/
#define  APP_TASK_START_STK_SIZE           128             // 启动任务任务栈大小定义
#define  APP_TASK_IO_STK_SIZE				    	 256
#define  APP_TASK_TEST_STK_SIZE				     160
#define  APP_TASK_UART_STK_SIZE				     160

//NB   // TaskNB任务栈大小定义 
#define  NBTX_TASK_STK_SIZE				         256 
#define  NBRV_TASK_STK_SIZE				         256
#define  UPDATE_TASK_STK_SIZE				       256
      
#define  FLASH_TASK_STK_SIZE           		1024            // TaskFlash任务栈大小定义
#define  DISPLAY_TASK_STK_SIZE         		 512            // 串口屏任务栈大小定义
#define  ENVIRONMENT_TASK_STK_SIZE				 128				  	// 环境任务栈大小定义
#define  NUMBER_TASK_STK_SIZE			         128					  // 产品个数任务栈大小定义
#define  PRESSURE_TASK_STK_SIZE            128            // 压力任务栈大小定义
#define  PLC_TASK_STK_SIZE           	     512            // 压机设备任务栈大小定义
#define  SCAN_TASK_STK_SIZE                256            // 扫码枪任务栈大小定义
#define  QUALIFIED_TASK_STK_SIZE           128            // 合格产品任务栈大小定义
#define  PROCESSING_TASK_STK_SIZE          256            // 数据处理任务栈大小定义




/*
*********************************************************************************************************
*                                                  LIB
*********************************************************************************************************
*/
#define  uC_CFG_OPTIMIZE_ASM_EN                 DEF_ENABLED
#define  LIB_STR_CFG_FP_EN                      DEF_DISABLED

#endif
