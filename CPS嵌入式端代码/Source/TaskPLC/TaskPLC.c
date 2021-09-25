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
* Description: 本文件负责将PLC读取到的数据进行处理
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
#include "delay.h"
#include "string.h"
#include "hmi_driver.h"
/************************************************************************************/
// 常量及全局变量定义
/************************************************************************************/
static u8 rs485buf[4]={0x02,0x00,0x01,0x14};																								//读取PLC数据指令
u8 ProductDataPLC[256];
u8 NBProductData[256];				//整合生产数据
/************************************************************************************/

/************************************************************************************/
/***********************************************************************************
* Function: PLC_Task;
*
* Description: PLC任务;
*              
* Input:  none;
*
* Return: none;
*
* Note:   本函数负责读取PLC产生的生产数据进行处理
*
************************************************************************************/
void PLC_Task(void *p_arg)
{
			u8 ReceivingArray[25];																							//PLC接收数据字符串数组
			u8 i,j=0;																														//接收PLC变量数组的变量
			u8 len;																															//接收PLC数组的长度
			
			INT8U ERRMutex;																											//串口5互斥信号量错误码
			INT8U ERRSem;																												//产品个数信号量错误码
			INT8U ResultERR;
		while(1)
			 {
						printf("PLC任务");
						OSSemPend(ProductSem,0,&ERRSem);
					 if(ERRSem==OS_ERR_NONE)
					 {
								OSMutexPend(UART5Mutex,0,&ERRMutex);																//等待产品累积个数的信号量
							 	RS485_Send_Data((u8 *)rs485buf,4);													//通过485发送指令给PLC		
								delay_ms(800);
								RS485_Receive_Data((u8 *)ReceivingArray,&len);							//接收PLC的数据
								delay_ms(500);
								
							 printf("接收的PLC数据是%d\r\n",len);
					
						if(len>0)																											//接收成功
							{	
									printf("接收到PLC数据");
								for(i=0;i<25;i++)
									{
										if(i==3|i==6|i==11|i==15|i==19|i==24)
										{
											j=0;
										}
										if(i<3)
										{
											Facility.BriquettingPressure[i]=ReceivingArray[i];
										}
										if(i>2&&i<6)
										{
											
											Facility.TonnageMolding[j++]=ReceivingArray[i];
										}
										
										if(i>5&&i<11)
										{
											Facility.MagnetizingA[j++]=ReceivingArray[i];
										}
										if(i>10&&i<15)
										{
											Facility.DemagnetizmA[j++]=ReceivingArray[i];
										}
										if(i>14&&i<19)
										{
											Facility.Size[j++]=ReceivingArray[i];
										}
										if(i>18&&i<24)
										{
											Facility.Weight[j++]=ReceivingArray[i];
										}
										if(i==24)
										{
											Facility.PowderTime[0]=ReceivingArray[i];
										}
									}
									Facility.BriquettingPressure[3]='\0';
									Facility.TonnageMolding[3]='\0';
									Facility.MagnetizingA[5]='\0';
									Facility.DemagnetizmA[4]='\0';
									Facility.Size[4]='\0';
									Facility.Weight[5]='\0';
									Facility.PowderTime[1]='\0';
									printf("转换完成\r\n");
									printf("%s\r\n",Facility.BriquettingPressure);							//成型压力
									printf("%s\r\n",Facility.TonnageMolding);										//成型吨位
									printf("%s\r\n",Facility.MagnetizingA);											//充磁电流
									printf("%s\r\n",Facility.DemagnetizmA);											//退磁电流
									printf("%s\r\n",Facility.Size);															//尺寸
									printf("%s\r\n",Facility.Weight);														//重量
									printf("%s\r\n",Facility.PowderTime);												//称粉记时
								
									
									SetTextValue(1,8,	(u8 *)Facility.BriquettingPressure);			//串口屏显示成型压力
									SetTextValue(1,7,	(u8 *)Facility.TonnageMolding);						//串口屏显示成型吨位
									SetTextValue(1,5,	(u8 *)Facility.MagnetizingA);							//串口屏显示充磁电流
									SetTextValue(1,3,	(u8 *)Facility.DemagnetizmA);							//串口屏显示退磁电流
									SetTextValue(1,10,(u8 *)Facility.Size);											//串口屏显示尺寸
									SetTextValue(1,4, (u8 *)Facility.Weight);										//串口屏显示重量
									SetTextValue(1,6, (u8 *)Facility.PowderTime);								//串口屏显示称粉记时

									
							 	sprintf((char *)ProductDataPLC,"%d,%s,%d,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s",1,SerialNumber.Facility,Facility.Number,
								SerialNumber.Pack_ID,SerialNumber.Profiling_ID,GainNumber.MouldData,GainNumber.Granularity,
								Facility.PowderTime,Facility.BriquettingPressure,Facility.TonnageMolding,Facility.Weight,Facility.Size,
								Facility.DemagnetizmA,Facility.MagnetizingA,SerialNumber.Mark);							
									
								printf("PLC任务%s\r\n",ProductDataPLC);
							}
						
							OSMutexPost(UART5Mutex);																				//释放互斥信号量			
							
							OSSemPend(ResultSem,0,&ResultERR);															//接收信号量
							if(ResultERR==OS_ERR_NONE)
							{
								sprintf((char *)NBProductData,"%s,%s",ProductDataPLC,GainNumber.ResultData);//整合生成的数据
								
								OSQPost(NBDataQ,(void *)NBProductData);	//上传产品产生的数据到OneNet
								strcpy((char *)GainNumber.ResultData,"0");//将结果的编号设置为0
								
								printf("产品结果上传NB数据成功\r\n");
																						
							}	
						}
					 OSTimeDlyHMSM(0,0,0,100);
				}										
}
