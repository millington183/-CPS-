/************************************************************************************
*  Copyright (c), 2019, 江西理工大学
*            All rights reserved.
*
* http:  www.jxust.edu.cn
* Email: 
*
* File name: NB-IoT.h
* Project  : NB-IoT底层函数的头文件
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  
* Version: 0.01
* Date:    2019.08.15			
* Email:   
* 
* Description: 本文件负责接收数据帧，通过NB-IoT模块发送数据到OneNet
*
* Others: none;
*
* Function List:
*		
* History:
*   1. Author:			  
*	   Version: 	 		0.02
*	   Date:         	2019.11.08
*    Modification: 	none
*
*************************************************************************************/
#ifndef _NB_IOT_H_
#define _NB_IOT_H_

#include "PIONEER_Config.h"

INT8U nbiot_Create(void);						// 创建设备实体;
INT8U nbiot_AddObj(void);						// 订阅OBJ组配置
INT8U nbiot_DiscoverRsp(void);				// 订阅Resource参数配置
INT8U nbiot_Connect(void);						// 向平台注册登录;
INT8U nbiot_Query(void);							// 查询登录状态函数
INT8U nbiot_Nofity(INT8U *NBBuff);		// 发送数据到平台;
INT8U nbiot_Del(void);								// 删除设备实体
INT8U nbiot_Reset(void);							// 复位模块;
INT8U nbiot_Update(void);						// 更新存活时间

#endif


