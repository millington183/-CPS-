/************************************************************************************
*  Copyright (c), 2019, 江西理工大学
*            All rights reserved.
*
* http:  www.jxust.edu.cn
* Email: 
*
* File name: TaskUart.c
* Project  : STM32F4XX系列模块软件
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  
* Version: 0.01
* Date:    2021.6.11			
* Email:   
* 
* Description: 本文件负责对数据进行处理。
*
* Others: none;
*
* Function List:
*		
*   1. Author:			  
*	   Version: 	 		0.02
*	   Date:         	2021.6.11
*    Modification: 	none
*	   
*
*************************************************************************************/
#include "PIONEER_Config.h"
#include "STM32F4_Head.h"
#include "UserVars.h"
#include "OSVars.h"
#include "string.h"
#include "stdio.h"
#include "hmi_driver.h"
/************************************************************************************/
// 常量及全局变量定义
/************************************************************************************/

INT8U CameraData[20];	
/***********************************************************************************
* Function: Processing_Task;
*
* Description: 摄像头处理任务;
*              
* Input:  none;
*
* Return: none;
*
* Note:   本函数负责接收摄像头数据并对其进行处理
*
************************************************************************************/
void Processing_Task(void *p_arg)
{
	u16 len;
	u8 i;
	INT8U CameraERR;
	INT8U QualifiedERR;
	while(1)
	{
		
			if(DetectionMode==0)							//检测方式为摄像头检测时
			{
				if((UART1_RX_STA & 0X8000) && (CameraRedFlag ==1))			//接收到数据并且红外对管检测到产品
				{
			
					printf("接收到数据\r\n");
					CameraRedFlag=0;
					len=UART1_RX_STA&0X7FFF;
					for(i=0;i<len;i++)
					{
						CameraData[i]=UART1_RX_BUF[i];
						UART1_RX_BUF[i]=0;
					}
					UART1_RX_STA=0;
					
					if(CameraData[0]=='0')
					{
						OSTimeDlyHMSM(0,0,0,500);	
						SetTextValue(1,27,ProductResult);
						strcpy((char *)GainNumber.ResultData,"0");//将结果的编号设置为0
						//sprintf((char *)GainData.ResultData,"%s",ProductResult);			//整合为获取的结果数据
						CameraFlag=1;															//通过摄像头检测去增加一条记录
						OSTimeDlyHMSM(0,0,0,1500);
						OSSemPost(ResultSem);											//释放产品结果信号量
						//UploadingFlag=1;
					}
					
					if(CameraData[0]=='2')
					{
						OSTimeDlyHMSM(0,0,0,500);
						SetTextValue(1,27,ProductResult2);
						strcpy((char *)GainNumber.ResultData,"2");//将结果的编号设置为2
						//sprintf((char *)GainData.ResultData,"%s",ProductResult2);			//整合为获取的结果数据
						CameraFlag=1;															//通过摄像头检测去增加一条记录
						OSTimeDlyHMSM(0,0,0,1500);
						OSSemPost(ResultSem);							//释放产品结果信号量
						//UploadingFlag=1;
					}
					
					if(CameraData[0]=='5')
					{
						OSTimeDlyHMSM(0,0,0,500);
						SetTextValue(1,27,ProductResult5);
						strcpy((char *)GainNumber.ResultData,"5");//将结果的编号设置为0
						//sprintf((char *)GainData.ResultData,"%s",ProductResult5);			//整合为获取的结果数据
						CameraFlag=1;															//通过摄像头检测去增加一条记录
						OSTimeDlyHMSM(0,0,0,1500);
						OSSemPost(ResultSem);							//释放产品结果信号量
						//UploadingFlag=1;
					}
				}
			}
			
			else if(DetectionMode==1)//为人工检测时
		{
				EXTI_APPInit();               // 外部中断初始化
//			OSSemPend(QualifiedSem,0,&QualifiedERR);				//等待产品合格的信号量
//			if(QualifiedERR == OS_ERR_NONE)
//			{
			if(ProcessingFlag==0)
			{
				printf("按键任务接收到产品的信号量\r\n");
				OSTimeDlyHMSM(0,0,20,0);												//挂起1分钟
				SetTextValue(1,9,ProductResult);
				ProductResultFlag=1;													//默认合格也添加历史记录
				OSSemPost(ResultSem);													//释放产品结果信号量
				printf("释放结果信号量\r\n");
			}
			//}	
		}
		
		OSTimeDlyHMSM(0,0,1,0);
	}
}
