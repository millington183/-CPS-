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
* Description: 本文件负责对外接按钮按下的处理。
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
#include "sys.h"
#include "Uart.h"
#include "led.h"
#include "hx711.h"
#include "delay.h"
#include "hmi_driver.h"
/************************************************************************************/
// 常量及全局变量定义
/************************************************************************************/
#define ProductID          1		//产品生产数据ID


u8 NBProduct[512]={"1,1,2,08090118312,08090118304,1,1,5,4.6,6.2,460.7,24.1,39.8,188.4,50H,2"};
u8 NBEnvironment[64]={"2,16,22.12,80.21"};
u8 NBProductEX[512]={0};
u8 MainSF[128]={"3,1,08090118312,2021-06-12 15:46,1,2021-06-13 15:00"};
u8 NBDataSF[256];

	
/************************************************************************************/

/***********************************************************************************
* Function: Processing_Task;
*
* Description: 数据处理任务;
*              
* Input:  none;
*
* Return: none;
*
* Note:   本函数负责接收数据并对其进行处理
*
************************************************************************************/
/*
	模具类型编号
	块状      1
	圆状      2
	
	粒度编号
	小粒      0
	大粒      1
	
	产品信息数据
	1，设备号，产品编号，压型人员，包装人员，模具编号，粒度编号，称粉记时
	成型压力，成型吨位，重量，尺寸，退磁电流，充磁电流，物料编号,结果编号(默认为0)
	
	产品结果
	0 合格
	1 圆柱-缺角-磕碰
	2 圆柱-缺角-软边
	3 圆柱-偏位不良
	4 圆柱-裂痕
	5 块状-缺角-磕碰
	6 块状-缺角-拿捏不当
	7 块状-缺角-模具不良
	8 块状-斜横
	
	
*/

void Qualified_Task(void *pdata)
{

	INT8U ProductERR;//产品结果信号量

	pdata=pdata;
	 
	while(1)
	{
			OSSemPend(ProductSem,0,&ProductERR);
			if(ProductERR == OS_ERR_NONE)
			{
				printf("按键任务接收到产品的信号量\r\n");
				OSTimeDlyHMSM(0,0,30,0);						//挂起1分钟
				OSSemPost(ResultSem);							//释放产品结果信号量
				SetTextValue(1,9,ProductResult);
				ProductResultFlag=1;
				printf("释放结果信号量\r\n");
			}	
		OSTimeDlyHMSM(0,0,15,0);
		
	}
}



		
