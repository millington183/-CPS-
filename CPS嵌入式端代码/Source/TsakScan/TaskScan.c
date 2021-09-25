/************************************************************************************
*  Copyright (c), 2019, 江西理工大学
*            All rights reserved.
*
* http:  www.jxust.edu.cn
* Email: 
*
* File name: TaskScan.c
* Project  : STM32F1XX/4XX扫码任务
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  
* Version: 0.01
* Date:    2021.06.11			
* Email:   
* 
* Description: 本文件负责接收扫码得到的数据及处理函数
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
#include "PIONEER_Config.h"
#include "STM32F4_Head.h"
#include "UserVars.h"
#include "OSVars.h"
#include "string.h"
#include "hmi_driver.h"
/************************************************************************************/
// 常量及全局变量定义
/************************************************************************************/
//设备编号1/2
//物料编号50H开头
//人员编号08开头
//081是包装员工
//082是压型员工
u8  StaffFlag=0;							//检测编号的类型
static char CacheData[256];		//缓存数组
	u8 datmp[25];
/***********************************************************************************
* Function: Scan（）
*
* Description: Scan函数;
*              
* Input:  none;
*
* Return: none;
*
* Note:   本函数用于读取二维码的原始信息
*
************************************************************************************/
void Scan(void )
{
	char ScanData[256];//扫描数组
	INT8U i;
	INT8U len=0;
	INT8U OS_Err;
	  
		OSSemPend(UART3Sem,0,&OS_Err);					  									 //等待串口3发送的信号量	
			
			if(OS_Err == OS_ERR_NONE)							 										 //如果接受到信号量，且正确
			{		
				
				if(UART3_RX_STA&0x8000 )
				{				
						//printf("接收成功");
						len = UART3_RX_STA&0x7FFF;     											 //得到此次接收到的数据长度							
						memset(ScanData,0,sizeof(ScanData));								 //将扫码数组数据清零
						
						for(i=0; i<len-1; i++)					  									 //len-1：用于删除扫码枪自动返回的回车键
						{
							ScanData[i] = UART3_RX_BUF[i];	    							 // 读取串口3数据	
							//printf("%c",ScanData[i]);
							UART3_RX_BUF[i] = 0;             								 	 // 清除串口3接收缓冲区的数据							
						}
						UART3_RX_BUF[i+1] = 0;														   // 清除串口3接收缓冲区的len+1数据						 
						UART3_RX_STA=0;																			 // 接收UART3状态标记
					
						if(ScanData[0]=='0'&&ScanData[1]=='8')
					{
						StaffFlag=1;																				 //包装员工
						memset(CacheData,0,sizeof(CacheData));							 //将缓存数组清空
						for(i=0;i<len-1;i++)
						{
							CacheData[i]=ScanData[i];													 //接收扫描数组的数据
							//printf("Scan%c",CacheData[i]);
						}
					}
					
					else if(ScanData[0]=='0'&&ScanData[1]=='0')											
					{																																
						StaffFlag=2;																				 //压型员工
						memset(CacheData,0,sizeof(CacheData));							 //将缓存数组清空
						for(i=0;i<len-1;i++)
						{
							CacheData[i]=ScanData[i];													 //接收扫描数组的数据
							//printf("%c",CacheData[i]);
						}
					}
					
					else if(ScanData[0]=='3'&&ScanData[1]=='3'&&ScanData[2]=='A')
					{
						StaffFlag=3;																				 //原料编号
						memset(CacheData,0,sizeof(CacheData));							 //将缓存数组清空
						for(i=0;i<len-1;i++)
						{
							CacheData[i]=ScanData[i];													 //接收扫描数组的数据
							//printf("%c",CacheData[i]);
						}
					}
					
					else
					{
						StaffFlag=4;																				 //设备编号
						memset(CacheData,0,sizeof(CacheData));							 //将缓存数组清空
						for(i=0;i<len-1;i++)
						{
							CacheData[i]=ScanData[i];													 //接收扫描数组的数据
							//printf("%c",CacheData[i]);
						}
					}
					
					memset(ScanData,0,sizeof(ScanData));									//清空扫描数据的数据
				
				}			
			}
}

/***********************************************************************************
* Function: Scan_Task;
*
* Description: Scan任务;
*              
* Input:  none;
*
* Return: none;
*
* Note:   本函数负责读取样品二维码的原始信息
*
************************************************************************************/
void Scan_Task(void *p_arg)
{
	u8 i=0;

	while(1)
	{
			printf("扫码枪任务运行\r\n");
			
			Scan();																		 		 					//本函数用于读取二维码的原始信息	
			
			switch(StaffFlag)
			{
				
				case 1:																			
				{
					if(ScanFlag == 1)
					{
						strncpy((char *)SerialNumber.Pack_ID,CacheData,13);  				//从缓存数组中复制包装员工ID
						for(i=0;i<13;i++)
						{
							printf("%c",SerialNumber.Pack_ID[i]);
						}
						SetTextValue(3,2,(u8 *)SerialNumber.Pack_ID);				//串口屏上显示包装员工ID
					
						printf("包装员工的字节=%d\r\n",strlen((const char*)SerialNumber.Pack_ID));
					
					break;
					}
				
				}
				
				case 2:
				{
					if(ScanFlag == 1)
					{
						strncpy((char *)SerialNumber.Profiling_ID,CacheData,13);  	//从缓存数组中复制压型员工ID
						for(i=0;i<13;i++)
						{
							printf("%c",SerialNumber.Profiling_ID[i]);
						}					
						SetTextValue(3,1,(u8 *)SerialNumber.Profiling_ID);	//串口屏上显示压型员工ID
					}
					break;
				}
			
				case 3:
				{
					if(ScanFlag == 1)
					{
						strncpy((char *)SerialNumber.Mark,CacheData,14); 						//从缓存数组中复制原料编号
						for(i=0;i<14;i++)
						{
							printf("%c",SerialNumber.Mark[i]);
						}							
						SetTextValue(3,3,(u8 *)SerialNumber.Mark);					//串口屏上显示原料编号
					}
					
					break;
				}
			
				case 4:
				{
					if(ScanFlag == 1)
					{
						strncpy((char *)SerialNumber.Facility,CacheData,14); 				//从缓存数组中复制设备编号
						for(i=0;i<14;i++)
						{
						printf("%c",SerialNumber.Facility[i]);
						}							
					SetTextValue(3,6,(u8 *)SerialNumber.Facility);					//串口屏上显示设备编号
					}
					
					break;
				}
				
				default :;
			
			} 

			OSTimeDly(10);	
    }

}

