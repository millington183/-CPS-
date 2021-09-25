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
* Description: 本文件负责对产品的个数进行计算。
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
u16 adcx;						//ADC通道获取到的值
u8 ADC_Fall = 1;				//ADC通道的值下降
u8 ADC_Rise;				//ADC通道的值上升
u8 Detection_Flag;	//检测到物品
/************************************************************************************/

/***********************************************************************************
* Function: Number_Task;
*
* Description: 产品个数任务;
*              
* Input:  none;
*
* Return: none;
*
* Note:   本函数负责读取产品个数
*
************************************************************************************/
void Number_Task(void *p_arg)
{
	u16 adcx;

	Facility.Number=0;
	
	while(1)
	{
		
		adcx = Get_Adc_Average(ADC_Channel_15,20);		//获取通道15的转换值，20次取平均
		
		//printf("ADC实验adcx=%d\r\n",adcx);
		
		if(adcx<1100 && ADC_Fall==1)//检测到物品，控制检测一次
		{
			
			printf("检测到物品\r\n");
			Detection_Flag = 1;				//检测到物品
			
			ADC_Fall=0;					      //控制当物品持续放着的时候只检测一次
			ADC_Rise=1;					       //下次检测上升
		}
		
		if(adcx>1100 && ADC_Rise==1)//物品拿走，控制检测一次
		{
			
			ADC_Rise=0;								//控制只检测一次
			ADC_Fall=1;								//下次检测下降
			
			ClearTextValue(1,9);
			ClearTextValue(1,8);			//串口屏显示成型压力
			ClearTextValue(1,7);			//串口屏显示成型吨位
			ClearTextValue(1,5);			//串口屏显示充磁电流
			ClearTextValue(1,3);			//串口屏显示退磁电流
			ClearTextValue(1,10);			//串口屏显示尺寸
			ClearTextValue(1,4);			//串口屏显示重量
			ClearTextValue(1,6);  		//串口屏显示称粉记时
			ClearTextValue(1,27);																						//清除机器检测的结果				
		
		}
		
		if(Detection_Flag==1) //有物品放着
		{
			
			Detection_Flag = 0;							//控制只触发一次
			Facility.Number++;							//产品个数加一
			OSSemPost(ProductSem);					//发送产品信号量接收数据
			
			printf("发送信号量给PLC\r\n");
			OSTimeDlyHMSM(0,0,0,1000);
			
			CameraRedFlag = 1;							//红外对管检测到产品，通过摄像头进行判断
			
			ProcessingFlag=0;								//产品合格检测的标志
			
			
		}
		
		OSTimeDlyHMSM(0,0,0,100);
	}
}
