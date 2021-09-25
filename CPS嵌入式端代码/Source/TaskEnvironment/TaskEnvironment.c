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
* Description: 本文件负责获取温湿度及粉尘浓度传感器的值并进行处理。
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
#include "hmi_driver.h"
/************************************************************************************/
// 常量及全局变量定义
/************************************************************************************/
	#define EnvironmentID      2															//环境数据ID
	u8 Send485buf[]={0x01,0x03,0x00,0x00,0x00,0x0a,0xc5,0xcd};//读取环境数据指令
	u8 num;																										//接收数据的个数
	u8 NBEnvironmentData[64];																	//整合环境数据
/************************************************************************************/

/***********************************************************************************
* Function: Environment_Task;
*
* Description: Environment任务;
*              
* Input:  none;
*
* Return: none;
*
* Note:   本函数负责读取工作环境的温度
*
************************************************************************************/
void Environment_Task(void *p_arg)
{	
	INT8U MutexERR;							//互斥信号量出错码
	INT8U SemERR;
	u8 Recive48buf[20]={0};			//环境任务的接收数组
	INT8U ENVIRCount=0;						//环境任务的执行次数

	while(1)
	{
		
			printf("读取环境任务\r\n");
	
			OSMutexPend(UART5Mutex,0,&MutexERR);
			
			RS485_Send_Data(Send485buf,8);//发送5个字节 									   
		
			delay_ms(500);
			
			RS485_Receive_Data(Recive48buf,&num);
		
			delay_ms(1000);
	
			if(num>0)
			{
				printf("环境任务数据");
				TempData(Recive48buf,(char *)EnvironmentData.Temperature);									//将环境温度转为字符串
				HumiDityData(Recive48buf,EnvironmentData.Humidity);													//将环境湿度转为字符串
				PMData(Recive48buf,(char *)EnvironmentData.PM);                            //将粉尘浓度转为字符串
				
				EnvironmentData.Temperature[5]='\0';
				
				EnvironmentData.Humidity[4]='\0';
				
				SetTextValue(1,13,EnvironmentData.PM);																			//串口屏上显示粉尘浓度
				SetTextValue(1,14,EnvironmentData.Temperature);															//串口屏上显示温度
				SetTextValue(1,15,EnvironmentData.Humidity);																//串口屏上显示湿度
				
				sprintf((char *)NBEnvironmentData,"%d,%s,%s,%s",EnvironmentID,EnvironmentData.PM,EnvironmentData.Temperature,EnvironmentData.Humidity);//整合环境数据
				
				OSQPost(NBDataQ,NBEnvironmentData);//上传数据到OneNet
				
			}
	
			OSMutexPost(UART5Mutex);						//释放互斥信号量
			
		OSTimeDlyHMSM(0,1,0,0);			
				
		}	
	} 

