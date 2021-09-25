/************************************************************************************
*  Copyright (c), 2019, 江西理工大学
*            All rights reserved.
*
* http:  www.jxust.edu.cn
* Email: 
*
* File name: TaskNB.c
* Project  : STM32F4XX系列模块软件
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  
* Version: 0.01
* Date:    2019.12.20			
* Email:   
* 
* Description: 本文件负责接收数据帧，通过NB-IoT模块发送数据到OneNet
*
* Others: none;
*
* Function List:
*		
*   1. Author:			  
*	   Version: 	 		0.02
*	   Date:         	2019.12.12
*    Modification: 	none
*	   
*
*************************************************************************************/
#include "PIONEER_Config.h"
#if (TASK_NB_EN == 1)
#include "STM32F4_Head.h"
#include "UserVars.h"
#include "OSVars.h"
#include "NB_IoT.h"
#include "stdio.h"
#include "string.h"
#include "hmi_driver.h"
#include "hmi_user_uart.h"
#include "cmd_queue.h"
#include "cmd_process.h"

/************************************************************************************/
// 常量及全局变量定义
/************************************************************************************/

#define RS485BUFF_LEN 46
#define VALIDDATA_LEN 150



//char RS485_buff[RS485BUFF_LEN];											// 存储从RS485读取的数据
// 当向设备读取数据出错时，将该信息上传到OneNet
INT8U ReadErrInfo[]="ERR01";
/************************************************************************************/




/***********************************************************************************
* Function: NB_TxTask;
*
* Description: NBIoT数据发送任务;
*              
* Input:  none;
*
* Return: none;
*
* Note:   本函数利用消息队列接收设备发来的数据，然后通过NB网络发送到OneNet，但要注意对NB
*					连接服务器的状态维护
*
************************************************************************************/
#if (NBTX_TASK_EN == 1)
void NB_TxTask(void *pdata)
{
	INT8U *Msg,*MemPtr;																 			// 消息指针及消息存放的存储块指针
	INT8U OS_Err;
	INT16U i;
	INT8U GetData[VALIDDATA_LEN];														// 存储消息队列收到的数据
	INT8U NB_flag,send_flag;
	INT8U Create_flag,Obj_flag,Rsp_flag,connect_flag;
	//INT8U DataNB[]="登录NB";
	for(i=0; i<VALIDDATA_LEN; i++)
	{
		GetData[i] = 0;
	}
	ConnectStatus = 0;																					// 初始化NB登录状态为登录
	//OSQPost(NBDataQ,DataNB);
	while(1)
	{
		UserVars.TaskRunStatus |= NBTX_TASK_FLAG;    // 设置本任务运行状态标志
		Msg = (INT8U*)OSQPend(NBDataQ,0,&OS_Err);									// 等待接收各任务发来的显示内容
		
		if(OS_ERR_NONE == OS_Err)
		{
			memset(GetData,0,VALIDDATA_LEN);
			if(*Msg != 'E')
			{
				MemPtr = Msg;																						// 保持存储块起始地址，以便后面进行释放
				for(i=0; i<VALIDDATA_LEN; i++)													// 从存储块中读取接收到的消息到GetData数组
				{
					GetData[i] = *Msg;
					Msg++;
				}
				OSMemPut(NBDataMem,(void*)MemPtr);											// 释放存储块
			}
			else
			{
				MemPtr = Msg;																						// 保持存储块起始地址，以便后面进行释放
				for(i=0; i<strlen((char *)ReadErrInfo); i++)																			// 从存储块中读取接收到的消息到GetData数组
				{
					GetData[i] = *Msg;
					Msg++;
				}
				OSMemPut(NBDataMem,(void*)MemPtr);											// 释放存储块
			}
			
			// 通过NB-IoT模块，将数据帧发送给服务器
			NB_flag = 0;																						// NB发送是否成功的总标志
			send_flag = 0;																					// 数据发送是否成功的标志
			DelCnt = 0;
			
			while(!NB_flag)
			{
				if(1 == ConnectStatus)																// 如已经登录，则可以进行数据发送
				{
					send_flag = nbiot_Nofity((INT8U*)GetData);						
					if(1 == send_flag)
					{
						NB_flag = 1;																			// 表示本条数据已经发送完成，可以不再进入发送数据循环数清零
						DelCnt = 0;																				// 删除设备实体次数清零
						break;
					}		
					else
					{
						nbiot_Del();																			// 删除设备实体
						ConnectStatus = 0;																// 设置未登录
						NB_flag = 0;																			// NB发送是否成功的总标志
						DelCnt++;																					// 删除设备实体次数加1					
					}
				}
				
				if(0 == ConnectStatus)																// 若查询登录状态，发现未登录，则进行登录流程
				{
					
					Create_flag = 0;
					Obj_flag = 0;
					connect_flag = 0;
					Rsp_flag = 0;
					
					if(nbiot_Query())																		// 查询是否登录
					{
						printf("C\r\n");
						ConnectStatus = 1;
					}
					else
					{
						if(nbiot_Create())																	// 尝试创建设备实体
						{
							Create_flag = 1;
						}
						
						if(Create_flag == 1)
						{
							
							if(nbiot_AddObj())																// 尝试订阅Object资源
							{
								Obj_flag = 1;
							}
						}
						
						if((Create_flag == 1) &&(Obj_flag == 1))
						{
							if(nbiot_DiscoverRsp())														// 尝试订阅Resource资源
							{
								Rsp_flag = 1;
							}
						}
						
						if((Create_flag == 1) && (Obj_flag ==1) && (Rsp_flag == 1))
						{
							if(nbiot_Connect())															// 尝试登录OneNet
							{
								connect_flag = 1;
								ConnectStatus = 1;
							}
						}
						if((Create_flag == 0) || (Obj_flag == 0) || (connect_flag == 0) || (Rsp_flag == 0))
						{
							nbiot_Del();																	// 删除设备实体
							ConnectStatus = 0;														// 设置未登录
							DelCnt++;																			// 删除设备实体次数加1
						}
						if(DelCnt >= 3)				 // 如删除设备实体3以上，复位NB模组并复位系统
						{			
							nbiot_Reset();
							OSTaskSuspend(APP_TASK_START_PRIO);
							OSTaskSuspend(NBTX_TASK_PRIO);								// 挂起两个任务，等待看门狗过期后复位
						}
					}	// 结束：if(nbiot_Query())				
				}// 结束：if(0 == ConnectStatus)
			}// 结束：while(!NB_flag)
		}// 结束：if(OS_ERR_NONE == OS_Err)
		
		//OSTimeDlyHMSM(0,0,0,300);	
	}
}
#endif

/***********************************************************************************
* Function: NB_RvTask;
*
* Description: NBIoT数据接收任务;
*              
* Input:  none;
*
* Return: none;
*
* Note:   本函数用于接收UART1来自OneNet的数据，对于参数配置命令进行解析，对于反馈信息，则
*					直接通过消息邮箱，发送给NB数据发送任务的相关函数。
*					处理是分为4种情况：
*					1、所接收的数据不包含“+”
*					2、所接收的数据包含“+”，但不是“+MIPLWRITE”
*					3、所接收的数据包含“+MIPLWRITE”，但同时包含“OK”
*					4、所接收的数据仅包含“+MIPLWRITE”相关内容
*					本程序主要应处理好两个问题，一个是接收到的数据中既有发送数据返回的“OK”，又有
*					OneNet下发的写命令，首先需要辨别出来；二是对这个情况发生时，Nb串口发送和接收
*					任务必须互斥地使用串口，且要设置NB串口接收任务的优先级更高，优先将回应数据帧
*					发送给OneNet平台，然后才进行常规的数据上传。
************************************************************************************/
#if (NBRV_TASK_EN == 1)
#define SIDataAdress 0
void NB_RvTask(void *pdata)
{
	INT8U OS_Err,i,len,Num;
	INT8U NBRvData[150];																// 存放接收到的写命令原始数据
	INT8U ResposeData[32];															// 存放生成的写操作反馈帧
	INT8U msgid[10]={0};																// 存放提取出来的msgid号
	INT8U StartNum;																			// 存放,7有效数据的起始位置
	INT8U StartNum1;																		// 存放,8有效数据的起始位置
	INT8U StartFlag;																		// 开始的标志位
	INT8U DataLen;																			// 存放有效数据的字节长度
	INT8U SIData[100];																	// 存放发送间隔时间数据      存储在EEPROM中地址为：1000
	INT8U RunCnt;																				// 运行控制变量
	INT8U nbnbnb[100];
	INT8U PlusPosi;
	
	
	while(1)
	{
		UserVars.TaskRunStatus |= NBRV_TASK_FLAG;    // 设置本任务运行状态标志
		OSSemPend(NBUartRdy, 0, &OS_Err);									// 等待NB数据接收完成的信号量
		
		len = (UART5_RX_STA&0X3FFF);
		for(i=0; i<len; i++)
		{
			if(UART5_RX_BUF[i] == '+')
			{
				PlusPosi = i;
				break;
			}
		}
		if(i >= len)
		{
			// 第1种情况，收到的数据不包含“+”，则说明与OneNet“写”操作无关，直接通知其他任务
			OSSemPost(NBStateSem);
		}
		else
		{
			// 判断是否是“+MIPLWRITE”
			if((UART5_RX_BUF[PlusPosi] == '+') && (UART5_RX_BUF[PlusPosi+5] == 'W')
				 && (UART5_RX_BUF[PlusPosi+6] == 'R') && (UART5_RX_BUF[PlusPosi+7] == 'I'))
			{
				//OSMutexPend(NBUartMutex, 0, &OS_Err);			// 申请NB串口互斥信号量
				
				// 扫描所收到的数据，看是否包含“OK“
				HaveOk = 0;
				for(i=0; i<len-1; i++)
				{
					if((UART5_RX_BUF[i] == 'O') &&(UART5_RX_BUF[i+1] == 'K'))
					{
						HaveOk = 1;
						OSSemPost(NBStateSem);										// 第3种情况,向NB发送任务发送信号量
						break;
					}
				}
				
				OSMutexPend(NBUartMutex, 0, &OS_Err);					// 申请NB串口互斥信号量，等待NB发送任务释放互斥信号量
			
				// 第3、4种情况，针对“+MIPLWRITE”的处理
				// 读取从串口接收到的数据
				if((UART5_RX_STA&0x8000))
				{
					printf("%s",UART5_RX_BUF);              //打印出串口5接收来自onenet的写命令
					for(i=0; i<len; i++)
					{
						NBRvData[i] = UART5_RX_BUF[i];				// 读取串口5数据
						UART5_RX_BUF[i] = 0;									// 清除串口5接收缓冲区的数据
					}
					UART5_RX_STA=0;
				}
				  
				printf("%s",NBRvData);                //打印出串口5接收来自onenet的写命令
				
				// 提取msgid		
				for(i=0; i<10; i++)
				{
					msgid[i] = 0;
				}
				i= 0;
				PlusPosi = PlusPosi + 13;								// 调整指针到有效数据的起始位置
				while(NBRvData[PlusPosi] != ',')					
				{
					msgid[i] = NBRvData[PlusPosi];
					PlusPosi++;
					i++;
				}
				
				// 向OneNet发送写操作反馈帧
				for(i=0; i<32; i++)
				{
					ResposeData[i] = 0;
				}
				sprintf((char*)ResposeData,"AT+MIPLWRITERSP=0,%s,2\r\n",msgid);
				
				RunCnt=0;
				Num=0;
				
				while((0 == RunCnt) && (Num < 3))										// 多次尝试发送响应数据帧，直到收到“OK”或超过3次
				{
					Uart_Write(UART5_ID,ResposeData,sizeof(ResposeData));											// 发送写响应数据帧
					Num++;
					OSSemPend(NBUartRdy, 0, &OS_Err);									// 等待OneNet回复“OK”
					if((UART5_RX_STA&0x8000))
					{
						if((UART5_RX_BUF[2] == 'O') && (UART5_RX_BUF[3] == 'K'))
						{
							RunCnt = 1;
						}			
						else
						{
							RunCnt = 0;
						}
						UART5_RX_STA=0;
					}
				}
		
				OSMutexPost(NBUartMutex);							// 释放NB串口互斥信号量
				

				for(i=0;i<len; i++)
				{		
						if(NBRvData[i-1] == ','&&NBRvData[i] == 'M')
					{
							StartNum=i;      	//记录有效数据开始的位置
							break;
					}
				}
		
				if(NBRvData[i-2] == '7')
				{

						for(i=StartNum;i<len; i++)
					{	
						if((NBRvData[i] == 'M')&&(NBRvData[i+1] == ','))
						{
							Maintenance.Facility=NBRvData[i+2];
							printf("%d\r\n",Maintenance.Facility-'0');
							
						}
						if((NBRvData[i] == ',')&&(NBRvData[i+1] == 'D'))
						{
							Maintenance.NBTimeNum=NBRvData[i-1];						//需要保养剩余的天数
							printf("接收到的整数%d\r\n",Maintenance.NBTimeNum-'0');
							SetScreen(11);//设置当前画面为天
							//SetScreen(11);
							SetTextInt32(11,3,Maintenance.NBTimeNum-'0',0,1);
							
							printf("接收到天的\r\n");
						}
						if((NBRvData[i] == ',')&&(NBRvData[i+1] == 'H'))
						{
							Maintenance.NBTimeNum=NBRvData[i-1];						//需要保养剩余的小时数
							printf("接收到的整数%d\r\n",Maintenance.NBTimeNum-'0');
							SetScreen(12);//设置当前画面为时
							//SetScreen(12);
							SetTextInt32(12,3,Maintenance.NBTimeNum-'0',0,1);
							
							printf("接收到时的\r\n");
						}
						if((NBRvData[i] == ',')&&(NBRvData[i+1] == 'M')&&(NBRvData[i+2] == ',')&&(NBRvData[i+3] == '0'))
						{
							Maintenance.NBTimeNum=NBRvData[i-1];						//需要保养剩余的分钟数
							printf("接收到的整数%d\r\n",Maintenance.NBTimeNum-'0');
							
							SetScreen(13);//设置当前画面为分
							//SetScreen(13);
							printf("接收到分的\r\n");
							SetTextInt32(13,3,Maintenance.NBTimeNum-'0',0,1);
							
							printf("接收到分的\r\n");
						}
						if((NBRvData[i] == ',')&&(NBRvData[i+1] == 'S'))
						{
							Maintenance.NBTimeNum=NBRvData[i-1];						//需要保养剩余的秒数
							printf("接收到的整数%d\r\n",Maintenance.NBTimeNum-'0');
							
							SetScreen(14);//设置当前画面为天
							
							SetTextInt32(14,3,Maintenance.NBTimeNum-'0',0,1);
							printf("接收到秒的\r\n");
						}
						if((NBRvData[i] == ',')&&(NBRvData[i+1] == 'N'))
						{
							
							SetScreen(15);//设置当前画面为天												//已经超时需要立刻保养
							printf("需要立刻保养\r\n");
						}
						if(NBRvData[i] == ',' && NBRvData[i + 1] == '0')
								DataLen= i- StartNum;       //记录有效数据长度   
						
					}
				}
				
				
				if(NBRvData[i-2] == '8')
				{
					printf("接收到8的\r\n");
						for(i=StartNum;i<len; i++)
					{	
						if((NBRvData[i] == 'M')&&(NBRvData[i+1] == ','))
						{
							Maintenance.Facility=NBRvData[i+2];
							printf("%d\r\n",Maintenance.Facility-'0');
							
						}
						if((NBRvData[i] == ',')&&(NBRvData[i+1] == 'D'))
						{
							Maintenance.NBTimeNum=NBRvData[i-1];						//需要保养剩余的天数
							printf("接收到的整数%d\r\n",Maintenance.NBTimeNum-'0');
							SetScreen(11);//设置当前画面为天
							SetScreen(11);
							SetTextInt32(11,3,Maintenance.NBTimeNum-'0',0,1);
							
							printf("接收到天的\r\n");
						}
						if((NBRvData[i] == ',')&&(NBRvData[i+1] == 'H'))
						{
							sprintf((char *)Maintenance.TimeNum,"%d%d",NBRvData[i-2]-'0',NBRvData[i-1]-'0');//需要保养剩余的小时数
							//printf("接收到的整数%d\r\n",NBRvData[i-2]-'0');
							//printf("接收到的整数%d\r\n",NBRvData[i-1]-'0');
							SetScreen(12);//设置当前画面为时
							SetScreen(12);//设置当前画面为时
							SetTextValue(12,3,Maintenance.TimeNum);//在串口屏上显示剩余多少小时
							printf("接收到时的\r\n");
						}
						if((NBRvData[i] == ',')&&(NBRvData[i+1] == 'M')&&(NBRvData[i+2] == ',')&&(NBRvData[i+3] == '0'))
						{
			
							sprintf((char *)Maintenance.TimeNum,"%d%d",NBRvData[i-2]-'0',NBRvData[i-1]-'0');//需要保养剩余的分钟数
							printf("接收到的整数%d\r\n",NBRvData[i-2]-'0');
							printf("接收到的整数%d\r\n",NBRvData[i-1]-'0');
							SetScreen(13);//设置当前画面为分
							SetScreen(13);
							SetTextValue(13,3,Maintenance.TimeNum);//在串口屏上显示剩余多少分钟
							printf("接收到分的\r\n");
						}
						if((NBRvData[i] == ',')&&(NBRvData[i+1] == 'S'))
						{
							sprintf((char *)Maintenance.TimeNum,"%d%d",NBRvData[i-2]-'0',NBRvData[i-1]-'0');//需要保养剩余的分钟数
							printf("接收到的整数%d\r\n",NBRvData[i-2]-'0');
							printf("接收到的整数%d\r\n",NBRvData[i-1]-'0');
							SetScreen(14);//设置当前画面为秒
							SetScreen(14);
							SetTextValue(14,3,Maintenance.TimeNum);//在串口屏上显示剩余多少秒钟
							printf("接收到秒的\r\n");
						}
//						if((NBRvData[i] == ',')&&(NBRvData[i+1] == 'N'))
//						{
//							SetScreen(15);
//							SetScreen(15);
//							printf("需要立刻保养\r\n");
//						}
						if(NBRvData[i] == ',' && NBRvData[i + 1] == '0')
								DataLen= i- StartNum;       //记录有效数据长度   
					}
				}
			
				memcpy(SIData, &NBRvData[StartNum], DataLen);
				//printf("%d\r\n",DataLen);
		  	printf("有效数据%s\r\n",SIData);         //打印有效数据
				
						// 提取数据发送间隔的秒数
	  //					SendIntervalSecond =  (NBRvData[j+3]-0x30)*10 +(NBRvData[j+4]-0x30);
						
						// 提取数据发送间隔的毫秒数
		//				SendIntervalMilli = (NBRvData[j+5]-0x30)*100 + (NBRvData[j+6]-0x30)*10 + (NBRvData[j+7]-0x30);		// 提取数据发送间隔的毫秒数
					
						// 将参数存入EEPROM
//						EEPROM_Write(SIDataAdress,SIData,sizeof(SIData));
//					  delay_ms(50);
//				    EEPROM_Read(SIDataAdress,nbnbnb,sizeof(SIData));
				//	  printf("EEPROM：%s\r\n",nbnbnb);
					if((NBRvData[StartNum] == 'R') && (NBRvData[StartNum+1] == 'S'))
					{
						nbiot_Reset();
						nbiot_Del();																	// 删除设备实体
						OSTaskSuspend(APP_TASK_START_PRIO);
						OSTaskSuspend(NBTX_TASK_PRIO);								// 挂起两个任务，等待看门狗过期后复位
					}
					
					// 提取其他数据对，可按照上面的if语句进行
					
			//	}
			}
			else
			{
				// 第2种情况，收到的数据包含“+”，但并不是“+MIPLWRITE”
				OSSemPost(NBStateSem);
			}
		}
		
		//OSTimeDlyHMSM(0,0,0,50);
	}
}
#endif

/***********************************************************************************
* Function: NB_UpdateTask;
*
* Description: NBIoT更新存活期任务;
*              
* Input:  none;
*
* Return: none;
*
* Note:   本函数用于隔若干时间更新NB-IoT登录OneNet的存活期
*
************************************************************************************/
#if (UPDATE_TASK_EN == 1)
void NB_UpdateTask(void *pdata)
{		
	u8 OS_Err;
	
//	TIM5_Int_Init(1000-1,7200-1);										// 定时周期100ms
	
	while(1)
	{
		UserVars.TaskRunStatus |= UPDATE_TASK_FLAG;    // 设置本任务运行状态标志
		if(1 == ConnectStatus)
		{
			NBUpdateCnt = 0;														// 计时变量清零
			TIM_Cmd(TIM3,ENABLE);												// 开启定时器3
			
			OSSemPend(NBUpdateSem, 0, &OS_Err );				// 等待计时完成后，收到信号量
			
			if(!nbiot_Update())													// 进行更新存活时间操作
			{
				if(nbiot_Query())													// 查询是否登录
				{
					if(!nbiot_Update())
					{
						ConnectStatus = 0;
					}
				}
				else
				{
					ConnectStatus = 0;
				}
			}			
		}
		else
		{
			delay_ms(1000);
		}	
	}
}
#endif


#endif


