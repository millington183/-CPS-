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
* Description: ���ļ��������ϵͳ�����������ȼ��Ͷ�ջ����;
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
*                         ����ϵͳ�������ȼ�����
**********************************************************************************************************/	
#define  APP_TASK_START_PRIO          2

#define  APP_TASK_IO_PRIO             4
//#define  APP_TASK_TEST_PRIO						5      
//NB
#define  NBTX_TASK_PRIO               6
#define  NBRX_TASK_PRIO               7
#define  UPDATE_TASK_PRIO             8

#define  	TASK_UART_PRIO							18
#define  	FLASH_TASK_PRIO          		4        	// TaskFlash Flash�������ȼ�
#define 	DISPLAY_TASK_PRIO						12				// TaskDisplay �������������ȼ�
#define 	ENVIRONMENT_TASK_PRIO      	16				// TaskEnvironment �����������ȼ�
#define  	NUMBER_TASK_PRIO    				9					// TaskNumber ��Ʒ�����������ȼ�
#define  	PRESSURE_TASK_PRIO          19        	// TaskPressure ѹ���������������ȼ�
#define  	PLC_TASK_PRIO          			10        // TaskPLC ѹ���豸�����������ȼ�
#define  	SCAN_TASK_PRIO    					11				// TaskScan ɨ��ǹ�������ȼ�
#define  	QUALIFIED_TASK_PRIO    			14				// TaskQualified �ϸ��Ʒ�������ȼ�
#define  	PROCESSING_PRIO           	13        // TaskProcessing ���ݴ����������ȼ�




/*
*********************************************************************************************************
*                                            TASK STACK SIZES
*                             Size of the task stacks (# of OS_STK entries)
*********************************************************************************************************
*/
#define  APP_TASK_START_STK_SIZE           128             // ������������ջ��С����
#define  APP_TASK_IO_STK_SIZE				    	 256
#define  APP_TASK_TEST_STK_SIZE				     160
#define  APP_TASK_UART_STK_SIZE				     160

//NB   // TaskNB����ջ��С���� 
#define  NBTX_TASK_STK_SIZE				         256 
#define  NBRV_TASK_STK_SIZE				         256
#define  UPDATE_TASK_STK_SIZE				       256
      
#define  FLASH_TASK_STK_SIZE           		1024            // TaskFlash����ջ��С����
#define  DISPLAY_TASK_STK_SIZE         		 512            // ����������ջ��С����
#define  ENVIRONMENT_TASK_STK_SIZE				 128				  	// ��������ջ��С����
#define  NUMBER_TASK_STK_SIZE			         128					  // ��Ʒ��������ջ��С����
#define  PRESSURE_TASK_STK_SIZE            128            // ѹ������ջ��С����
#define  PLC_TASK_STK_SIZE           	     512            // ѹ���豸����ջ��С����
#define  SCAN_TASK_STK_SIZE                256            // ɨ��ǹ����ջ��С����
#define  QUALIFIED_TASK_STK_SIZE           128            // �ϸ��Ʒ����ջ��С����
#define  PROCESSING_TASK_STK_SIZE          256            // ���ݴ�������ջ��С����




/*
*********************************************************************************************************
*                                                  LIB
*********************************************************************************************************
*/
#define  uC_CFG_OPTIMIZE_ASM_EN                 DEF_ENABLED
#define  LIB_STR_CFG_FP_EN                      DEF_DISABLED

#endif
