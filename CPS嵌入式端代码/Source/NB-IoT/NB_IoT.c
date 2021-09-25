/************************************************************************************
*  Copyright (c), 2019, 江西理工大学
*            All rights reserved.
*
* http:  www.jxust.edu.cn
* Email: 
*
* File name: NB-IoT.c
* Project  : NB-IoT底层函数
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
/************************************************************************************/
// 测试说明
/************************************************************************************/
/*

*/

/************************************************************************************/
// 引用外部头文件
/************************************************************************************/
#include "includes.h"
#include "NB_IoT.h"
#include "STM32F4_Head.h"
#include "UserVars.h"
#include "OSVars.h"
#include "string.h"
#include "stdio.h"


/************************************************************************************/
// 常量及全局变量定义
/************************************************************************************/
#define RV_BUF_LEN	256

//extern INT8U NBRvDelay;
//extern INT8U HaveOk;			// 用于当收到的NB串口数据包含“OK”和“+MIPLWRITE”时表示里面包含“Ok”

INT8U RvBuf[RV_BUF_LEN] = {0};																							// 暂存从串口5收到的数据																									// 用于保存NB设备创建结果
char testtmp=0x30;

INT8U Close_Date[]={"AT+MIPLCLOSE=0\r\n"};																// 取消设备在OneNet平台的注册的AT指令
INT8U Create_Date[]={"AT+MIPLCREATE=49,130031F10003F2002304001100000000000000123138332E3233302E34302E34303A35363833000131F30008C000000000,0,49,0\r\n"};
INT8U AddObj_Date[]={"AT+MIPLADDOBJ=0,3200,1,\"1\",1,0\r\n"};							// 创建object（对象）的AT指令
INT8U DiscoverRsp_Date[]={"AT+MIPLDISCOVERRSP=0,3200,1,4,\"5750\"\r\n"};	// 模组响应OneNet平台的Discover请求的AT指令
INT8U Open_Date[]={"AT+MIPLOPEN=0,3000,30\r\n"};													// 设备注册到OneNet平台AT指令
INT8U Del_Data[]={"AT+MIPLDELETE=0\r\n"};																	// 删除设备实体（将删除已订阅的Object、instance、resource)
INT8U Query_Data[]={"AT+MIPLOPEN?\r\n"};																	// 查询登录状况
INT8U NRB_Data[]={"AT+NRB\r\n"};
INT8U Update_Data[]={"AT+MIPLUPDATE=0,0,0\r\n"};												// 发起存活时间更新请求,延续前一次的存活期时长

/***********************************************************************************
* Function: nbiot_Create;
*
* Description: 创建设备实体;
*              
* Input:  none;
*
* Return: 1：成功
*					0：失败
*
* Note:   none;
************************************************************************************/
INT8U nbiot_Create(void)
{
	INT16U i,j;
	INT8U result;
	INT8U OS_Err;
	
	OSMutexPend(NBUartMutex, 0, &OS_Err);			// 申请NB串口互斥信号量
	
	NBRvDelay = 0;
	
	Uart_Write(UART5_ID,Create_Date,sizeof(Create_Date));	// 发送数据
	
	#if (NBRV_TASK_EN==1)
	OSSemPend(NBStateSem, 500, &OS_Err );			// 创建了专门的NB串口接收任务，通过该任务首先分类串口内容
	#else
	OSSemPend(NBUartRdy, 500, &OS_Err);				// 未创建了专门的NB串口接收任务
	#endif
	
	for(i=0; i<RV_BUF_LEN; i++)
	{
		RvBuf[i] = 0;													// 清空存储区域	
	}
	if((UART5_RX_STA&0x8000))
	{
		for(j=0; j<(UART5_RX_STA&0X3FFF); j++)
		{
			RvBuf[j] = UART5_RX_BUF[j];					// 读取串口1数据
			UART5_RX_BUF[j] = 0;								// 清除串口1接收缓冲区的数据
		}
		UART5_RX_STA=0;
		
		OSMutexPost(NBUartMutex);							// 释放NB串口互斥信号量
		
		#if (DEBUG_APP_EN == 1)
			printf("Create收到的数据是%s\r\n", RvBuf);
		#endif
		
		if((RvBuf[19] == 'O') && (RvBuf[20] == 'K'))
		{
			printf("创建设备实体成功\r\n");
			result = 1;
		}
		else
		{
			#if (DEBUG_APP_EN == 1)
				printf("创建设备实体失败\r\n");
			#endif
			result = 0;
		}
	}
	
	return result;
}

/***********************************************************************************
* Function: nbiot_AddObj;
*
* Description: 订阅OBJ组配置
*              
* Input:  none;
*
* Return: 1：成功
*					0：失败
*
* Note:   none;
************************************************************************************/
INT8U nbiot_AddObj(void)
{
	INT16U i,j;
	INT8U result;
	INT8U OS_Err;
	
	OSMutexPend(NBUartMutex, 0, &OS_Err);			// 申请NB串口互斥信号量
	
	NBRvDelay = 0;
	Uart_Write(UART5_ID,AddObj_Date,sizeof(AddObj_Date));
	
	#if (NBRV_TASK_EN == 1)
	OSSemPend(NBStateSem, 500, &OS_Err );			// 创建了专门的NB串口接收任务，通过该任务首先分类串口内容
	#else
	OSSemPend(NBUartRdy, 500, &OS_Err);				// 未创建了专门的NB串口接收任务
	#endif
	
	if((UART5_RX_STA&0x8000))
	{
		for(i=0; i<RV_BUF_LEN; i++)
		{
			RvBuf[i] = 0;													// 清空存储区域	
		}
		for(j=0; j<(UART5_RX_STA&0X3FFF); j++)
		{
			RvBuf[j] = UART5_RX_BUF[j];					// 读取串口1数据
			UART5_RX_BUF[j] = 0;								// 清除串口1接收缓冲区的数据
		}
		UART5_RX_STA=0;
		
		OSMutexPost(NBUartMutex);							// 释放NB串口互斥信号量
		
		#if (DEBUG_APP_EN == 1)
			printf("Addobj收到的数据是%s\r\n", RvBuf);
		#endif
		
		if((RvBuf[2] == 'O') && (RvBuf[3] == 'K'))
		{
			printf("订阅OBJ组配置成功\r\n");
			result = 1;
		}
		else
		{
			#if (DEBUG_APP_EN == 1)
				printf("订阅OBJ组配置失败\r\n");
			#endif
			result = 0;
		}
	}
	
	return result;
}

/***********************************************************************************
* Function: nbiot_DiscoverRsp;
*
* Description: 订阅Resource参数配置
*              
* Input:  none;
*
* Return: 1：成功
*					0：失败
*
* Note:   none;
************************************************************************************/
INT8U nbiot_DiscoverRsp(void)
{
	INT16U i,j;
	INT8U result;
	INT8U OS_Err;
	
	OSMutexPend(NBUartMutex, 0, &OS_Err);			// 申请NB串口互斥信号量
	
	NBRvDelay = 0;
	
	Uart_Write(UART5_ID,DiscoverRsp_Date,sizeof(DiscoverRsp_Date));
	
	#if (NBRV_TASK_EN == 1)
	OSSemPend(NBStateSem, 500, &OS_Err );			// 创建了专门的NB串口接收任务，通过该任务首先分类串口内容
	#else
	OSSemPend(NBUartRdy, 500, &OS_Err);				// 未创建了专门的NB串口接收任务
	#endif
	
	if((UART5_RX_STA&0x8000))
	{
		for(i=0; i<RV_BUF_LEN; i++)
		{
			RvBuf[i] = 0;													// 清空存储区域	
		}
		for(j=0; j<(UART5_RX_STA&0X3FFF); j++)
		{
			RvBuf[j] = UART5_RX_BUF[j];					// 读取串口1数据
			UART5_RX_BUF[j] = 0;								// 清除串口1接收缓冲区的数据
		}
		UART5_RX_STA=0;
		
		OSMutexPost(NBUartMutex);							// 释放NB串口互斥信号量
		
		#if (DEBUG_APP_EN == 1)
			printf("DiscoverRsp收到的数据是%s\r\n", RvBuf);
		#endif
		
		if((RvBuf[2] == 'O') && (RvBuf[3] == 'K'))
		{
			#if (DEBUG_APP_EN == 1)
				printf("订阅Resource参数配置成功\r\n");
			#endif
			//++NB_OK;
			result = 1;
		}
		else
		{
			#if (DEBUG_APP_EN == 1)
				printf("订阅Resource参数配置失败\r\n");
			#endif
			result = 0;
		}
	}
	
	return result;
}

/***********************************************************************************
* Function: nbiot_Connect;
*
* Description: 向平台注册登录;
*              
* Input:  none;
*
* Return: 1：NB-IoT注册成功
*					0：NB-IoT注册失败
*
* Note:   none;
************************************************************************************/
INT8U nbiot_Connect(void)
{
	INT16U i,j;
	INT8U result;
	INT8U OS_Err;
	
	OSMutexPend(NBUartMutex, 0, &OS_Err);			// 申请NB串口互斥信号量
	
	NBRvDelay = 1;
	Uart_Write(UART5_ID,Open_Date,sizeof(Open_Date));
	
	#if (NBRV_TASK_EN == 1)
	OSSemPend(NBStateSem, 500, &OS_Err );			// 创建了专门的NB串口接收任务，通过该任务首先分类串口内容
	#else
	OSSemPend(NBUartRdy, 500, &OS_Err);				// 未创建了专门的NB串口接收任务
	#endif
	
	if((UART5_RX_STA&0x8000))
	{
		for(i=0; i<RV_BUF_LEN; i++)
		{
			RvBuf[i] = 0;													// 清空存储区域	
		}
		for(j=0; j<(UART5_RX_STA&0X3FFF); j++)
		{
			RvBuf[j] = UART5_RX_BUF[j];					// 读取串口1数据
			UART5_RX_BUF[j] = 0;								// 清除串口1接收缓冲区的数据
		}
		UART5_RX_STA=0;
		
		OSMutexPost(NBUartMutex);							// 释放NB串口互斥信号量
		
		#if (DEBUG_APP_EN == 1)
			printf("Connect收到的数据是%s\r\n", RvBuf);
		#endif
		
		for(i=0; i<RV_BUF_LEN; i++)
		{
			if(RvBuf[i] == 0x36)
			{
				#if (DEBUG_APP_EN == 1)
					printf("向平台注册登录成功\r\n");
				#endif
				result = 1;
				break;																	// 收到了登录成功的标志“6”，跳出字符搜索
			}
		}
		
		if(i >= RV_BUF_LEN)
		{
			#if (DEBUG_APP_EN == 1)
				printf("向平台注册登录失败\r\n");
			#endif
			result = 0;
		}
	}	
	return result;
}

/***********************************************************************************
* Function: nbiot_Query;
*
* Description:  查询登录状态函数
*              
* Input:  none;
*
* Return: 1：NB-IoT已经登录
*					0：NB-IoT未登录
*
* Note:   none;
************************************************************************************/
INT8U nbiot_Query(void)							// 查询登录状态函数
{
	INT16U i,j;
	INT8U result;
	INT8U OS_Err;
	
	OSMutexPend(NBUartMutex, 0, &OS_Err);			// 申请NB串口互斥信号量
	
	NBRvDelay = 1;
	
	Uart_Write(UART5_ID,Query_Data,sizeof(Query_Data));
	
	#if (NBRV_TASK_EN == 1)
	OSSemPend(NBStateSem, 500, &OS_Err );			// 创建了专门的NB串口接收任务，通过该任务首先分类串口内容
	#else
	OSSemPend(NBUartRdy, 500, &OS_Err);				// 未创建了专门的NB串口接收任务
	#endif
	
	if((UART5_RX_STA&0x8000))
	{
		for(i=0; i<RV_BUF_LEN; i++)
		{
			RvBuf[i] = 0;													// 清空存储区域	
		}
		for(j=0; j<(UART5_RX_STA&0X3FFF); j++)
		{
			RvBuf[j] = UART5_RX_BUF[j];					// 读取串口1数据
			UART5_RX_BUF[j] = 0;								// 清除串口1接收缓冲区的数据
		}
		UART5_RX_STA=0;
		
		OSMutexPost(NBUartMutex);							// 释放NB串口互斥信号量
		
		#if (DEBUG_APP_EN == 1)
			printf("Query收到的数据是%s\r\n", RvBuf);
		#endif
		
		for(i=0; i<RV_BUF_LEN; i++)
		{
			if(RvBuf[i] == 0x36)
			{
				#if (DEBUG_APP_EN == 1)
						printf("模组已登录OneNet\r\n");
				#endif
				result = 1;
				break;																	// 收到了登录成功的标志“6”，跳出字符搜索
			}
		}
			
		if(i >= RV_BUF_LEN)
		{
			#if (DEBUG_APP_EN == 1)
				printf("模组未登录OneNet\r\n");
			#endif
			result = 0;
		}
	}
	
	return result;
}

/***********************************************************************************
* Function: nbiot_Update;
*
* Description: 更新存活时间;
*              
* Input:  none;
*
* Return: 1：成功
*					0：失败
*
* Note:   none;
************************************************************************************/
INT8U nbiot_Update(void)
{
	INT16U i,j;
	INT8U result;
	INT8U OS_Err;
	
	OSMutexPend(NBUartMutex, 0, &OS_Err);			// 申请NB串口互斥信号量
	
	NBRvDelay = 1;
	Uart_Write(UART5_ID,Update_Data,sizeof(Update_Data));
	
	#if (NBRV_TASK_EN == 1)
	OSSemPend(NBStateSem, 500, &OS_Err );			// 创建了专门的NB串口接收任务，通过该任务首先分类串口内容
	#else
	OSSemPend(NBUartRdy, 500, &OS_Err);				// 未创建了专门的NB串口接收任务
	#endif
	
	if((UART5_RX_STA&0x8000))
	{
		for(i=0; i<RV_BUF_LEN; i++)
		{
			RvBuf[i] = 0;													// 清空存储区域	
		}
		for(j=0; j<(UART5_RX_STA&0X3FFF); j++)
		{
			RvBuf[j] = UART5_RX_BUF[j];					// 读取串口1数据
			UART5_RX_BUF[j] = 0;								// 清除串口1接收缓冲区的数据
		}
		UART5_RX_STA=0;
		
		OSMutexPost(NBUartMutex);							// 释放NB串口互斥信号量
		
		#if (DEBUG_APP_EN == 1)
			printf("nbiot_Update的数据是%s\r\n", RvBuf);
		#endif
		
		for(i=0; i<RV_BUF_LEN-1; i++)
		{
			if((RvBuf[i] == 0x31) && (RvBuf[i+1] == 0x31))
			{
				#if (DEBUG_APP_EN == 1)
						printf("存活时间更新成功\r\n");
				#endif
				result = 1;
				break;																	// 收到了登录成功的标志“6”，跳出字符搜索
			}
		}
			
		if(i >= RV_BUF_LEN)
		{
			#if (DEBUG_APP_EN == 1)
				printf("存活时间更新失败\r\n");
			#endif
			result = 0;
		}
	}
	
	return result;
}


/***********************************************************************************
* Function: nbiot_Nofity;
*
* Description: 发送数据到平台;
*              
* Input:  需要发送的字符串指针;
*
* Return: 1：发送数据成果
*					0：发送数据失败
*
* Note:   none;
************************************************************************************/
INT8U nbiot_Nofity(INT8U *NBBuff)
{
	INT8U flag=0;
	INT16U i,j;
	INT8U OS_Err;	
	
	INT8U Notify_Date[128]={0};
	
	sprintf((char*)Notify_Date,"AT+MIPLNOTIFY=0,0,3200,0,5750,1,%d,\"%s\",0,0\r\n",strlen((char*)NBBuff),NBBuff);
	
	OSMutexPend(NBUartMutex, 0, &OS_Err);			// 申请NB串口互斥信号量
	
	NBRvDelay = 0;
	Uart_Write(UART5_ID,Notify_Date,sizeof(Notify_Date));// 上传数据				
	
	#if (NBRV_TASK_EN == 1)
	OSSemPend(NBStateSem, 500, &OS_Err );			// 创建了专门的NB串口接收任务，通过该任务首先分类串口内容
	#else
	OSSemPend(NBUartRdy, 500, &OS_Err);				// 未创建了专门的NB串口接收任务
	#endif
	
	if(0 == HaveOk)
	{
		if((UART5_RX_STA&0x8000))
		{
			for(i=0; i<RV_BUF_LEN; i++)
			{
				RvBuf[i] = 0;													// 清空存储区域	
			}
			for(j=0; j<(UART5_RX_STA&0X3FFF); j++)
			{
				RvBuf[j] = UART5_RX_BUF[j];					// 读取串口1数据
				UART5_RX_BUF[j] = 0;								// 清除串口1接收缓冲区的数据
			}
			UART5_RX_STA=0;
			
			OSMutexPost(NBUartMutex);							// 释放NB串口互斥信号量
			
			#if (DEBUG_APP_EN == 1)
				printf("Nofity收到的数据是%s\r\n", RvBuf);
			#endif
			
			if((RvBuf[2] == 'O') && (RvBuf[3] == 'K'))
			{
				#if (DEBUG_APP_EN == 1)
					printf("上传数据成功\r\n");
				#endif
				flag = 1;
			}
			else
			{
				#if (DEBUG_APP_EN == 1)
					printf("上传数据失败\r\n");
				#endif
				flag = 0;
			}
		}
	}
	else		// HaveOK=1
	{
		#if (DEBUG_APP_EN == 1)
			printf("上传数据成功\r\n");
		#endif
		
		HaveOk = 0;
		
		OSMutexPost(NBUartMutex);												// 释放NB串口互斥信号量
		
		flag = 1;
	}
		
	return flag;
}

/***********************************************************************************
* Function: nbiot_Del;
*
* Description:  删除设备实体
*              
* Input:  none;
*
* Return: 1：删除设备实体成功
*					0：删除设备实体失败
*
* Note:   none;
************************************************************************************/
INT8U nbiot_Del(void)								// 删除设备实体
{
	INT16U i,j;
	INT8U result;
	INT8U OS_Err;
	
	OSMutexPend(NBUartMutex, 0, &OS_Err);			// 申请NB串口互斥信号量
	
	NBRvDelay = 0;
	Uart_Write(UART5_ID,Del_Data,sizeof(Del_Data));
	
	#if (NBRV_TASK_EN == 1)
	OSSemPend(NBStateSem, 500, &OS_Err);			// 创建了专门的NB串口接收任务，通过该任务首先分类串口内容
	#else
	OSSemPend(NBUartRdy, 500, &OS_Err);				// 未创建了专门的NB串口接收任务
	#endif
	
	if((UART5_RX_STA&0x8000))
	{
		for(i=0; i<RV_BUF_LEN; i++)
		{
			RvBuf[i] = 0;													// 清空存储区域	
		}
		for(j=0; j<(UART5_RX_STA&0X3FFF); j++)
		{
			RvBuf[j] = UART5_RX_BUF[j];					// 读取串口1数据
			UART5_RX_BUF[j] = 0;								// 清除串口1接收缓冲区的数据
		}
		UART5_RX_STA=0;
		
		OSMutexPost(NBUartMutex);							// 释放NB串口互斥信号量
		
		#if (DEBUG_APP_EN == 1)
			printf("Del收到的数据是%s\r\n", RvBuf);
		#endif
		
		if((RvBuf[2] == 'O') && (RvBuf[3] == 'K'))
		{
			#if (DEBUG_APP_EN == 1)
				printf("删除设备实体成功\r\n");
			#endif
			result = 1;
		}
		else
		{
			#if (DEBUG_APP_EN == 1)
				printf("删除设备实体失败\r\n");
			#endif
			result = 0;
		}
	}
	
	return result;
}


/***********************************************************************************
* Function: nbiot_Reset;
*
* Description:  复位模块;
*              
* Input:  none;
*
* Return: 1：复位NB-IoT成功
*					0：复位NB-IoT失败
*
* Note:   none;
************************************************************************************/
INT8U nbiot_Reset(void)
{
	INT16U i,j;
	INT8U result;
	INT8U OS_Err;
	
	OSMutexPend(NBUartMutex, 0, &OS_Err);			// 申请NB串口互斥信号量
	
	NBRvDelay = 0;
	Uart_Write(UART5_ID,NRB_Data,sizeof(NRB_Data));
	
	#if (NBRV_TASK_EN == 1)
	OSSemPend(NBStateSem, 500, &OS_Err );			// 创建了专门的NB串口接收任务，通过该任务首先分类串口内容
	#else
	OSSemPend(NBUartRdy, 500, &OS_Err);				// 未创建了专门的NB串口接收任务
	#endif
	
	if((UART5_RX_STA&0x8000))
	{
		for(i=0; i<RV_BUF_LEN; i++)
		{
			RvBuf[i] = 0;													// 清空存储区域	
		}
		for(j=0; j<(UART5_RX_STA&0X3FFF); j++)
		{
			RvBuf[j] = UART5_RX_BUF[j];					// 读取串口1数据
			UART5_RX_BUF[j] = 0;								// 清除串口1接收缓冲区的数据
		}
		UART5_RX_STA=0;
		
		OSMutexPost(NBUartMutex);							// 释放NB串口互斥信号量
		
		#if (DEBUG_APP_EN == 1)
			printf("Reset收到的数据是%s\r\n", RvBuf);
		#endif
		
		if((RvBuf[2] == 'R') && (RvBuf[3] == 'E'))
		{
			#if (DEBUG_APP_EN == 1)
				printf("NB模组复位成功\r\n");
			#endif
			result = 1;
		}
		else
		{
			#if (DEBUG_APP_EN == 1)
				printf("NB模组复位失败\r\n");
			#endif
			result = 0;
		}
	}
	
	return result;
}

/***********************************************************************************/
// 文件结束
/***********************************************************************************/
