/************************************************************************************
*  Copyright (c), 2019, 江西理工大学
*            All rights reserved.
*
* http:  www.jxust.edu.cn
* Email: 
*
* File name: UserVars.h
* Project  : STM32F4XX系列模块软件
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  智慧工厂研究所
* Version: 1.00
* Date:    2019.11.25			
* Email:   
* 
* Description: 本文件负责用户应用程序公共全局变量引用头文件, 客户可以把应用的全局变量设置到这里;
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
#ifndef __USER_VARS_H 
#define __USER_VARS_H 

/************************************************************************************/
// 引用外部头文件
/************************************************************************************/
#include "const.h"	
//#include "config.h"	
#include "PIONEER_Config.h"

#include "timer.h"	
/************************************************************************************
*
*       系统状态标志定义
*
*************************************************************************************/

#define CONFIG_PARA_LEN	 sizeof(CONFIG_PARA)
	
#define TASK_IO_FLAG		    0x00000001
#define TASK_TEST_FLAG      0x00000002 
#define NBTX_TASK_FLAG	    0x00000004 
#define NBRV_TASK_FLAG	    0x00000008 
#define UPDATE_TASK_FLAG	  0x00000010 

#define TASK_UART_FLAG	    0x00000020 


#define TASK_FLAG   (TASK_TEST_FLAG*TASK_TEST_EN + TASK_IO_FLAG*TASK_IO_EN + NBTX_TASK_FLAG*NBTX_TASK_EN +      \
                     NBRV_TASK_FLAG*NBRV_TASK_EN + UPDATE_TASK_FLAG*UPDATE_TASK_EN + TASK_UART_FLAG*TASK_UART_EN \
										)



// Flag各种标志位定义
#define  RTC_SECIT_FLAG         0x00000001  // RTC秒中断标志
#define  RTC_ALRIT_FLAG         0x00000002  // RTC闹钟中断标志
#define  SPIFLASH_WK_FLAG       0x00000004  // SPI FLASH正在工作中标志, 用这个标志
#define  SD_WK_FLAG             0x00000008  // SD卡正在工作中标志
#define  OS_START_FLAG          0x00000020  // 操作系统启动运行标志

// OKFlag 板子各功能测试成功标志
#define  SPIFLASH_OK_FLAG       0x00000001  // SPI FLASH测试成功标志
#define  NFLASH_OK_FLAG         0x00000002  // NAND FLASH测试成功标志
#define  EEPROM_OK_FLAG         0x00000004  // EEPROM测试成功标志
#define  SRAM_OK_FLAG           0x00000008  // 扩展SRAM测试成功标志
#define  SD_OK_FLAG             0x00000010  // SD卡测试成功标志


#define  DATABUF_SIZE   512

#pragma pack (1)


typedef struct
{ 
    INT32U   Flag;          // 各种标志位
    INT32U   TaskRunStatus; // 操作系统任务运行状态 
    
    INT32U   OKFlag;        // 板子各功能测试成功标志
    INT32U   DI;	        // DI输入值: DI1=bit0, DI2=bit1; 以此类推DI32=bit31; 
    INT32U   DO;	        // DO输出值: DO1=bit0, DO2=bit1; 以此类推DO32=bit31; 
	
		INT32U   TimerCount;
    INT8U    buf[DATABUF_SIZE+1];  // 测试用数组
    INT16U   UartData;      // Uart接收数据
    
}USER_VARS;	 
#pragma pack() 
extern USER_VARS UserVars;	     // 用户变量

extern u8 ProcessingFlag;						//产品合格标志
extern u8 DetectionMode;							//检测方式
extern u32 FLASH_SIZE;				   //FLASH 大小为16字节		
extern u8 ProductResultFlag;		 //通过外部按键按下时产品历史记录
extern u8 CameraFlag;						 //通过摄像头检测的标志
extern u8 ScanFlag;							 //扫码标志
extern u8 UploadingFlag;				 //数据上传NB标志
extern u8 CameraRedFlag;				 //红外对管检测到的标志
extern INT8U UART1_RX_BUF[UART1_RXBUF_SIZE];     //接收缓冲,最大UART1_RXBUF_SIZE个字节.
extern INT8U UART2_RX_BUF[UART2_RXBUF_SIZE];
extern INT8U UART3_RX_BUF[UART3_RXBUF_SIZE];
extern INT8U UART4_RX_BUF[UART4_RXBUF_SIZE];
extern INT8U UART5_RX_BUF[UART5_RXBUF_SIZE];
extern INT8U UART6_RX_BUF[UART6_RXBUF_SIZE];
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
extern INT16U UART1_RX_STA;       //接收状态标记	.
extern INT16U UART2_RX_STA;
extern INT16U UART3_RX_STA;
extern INT16U UART4_RX_STA;
extern INT16U UART5_RX_STA;
extern INT16U UART6_RX_STA;


extern INT8U  TIM4CH1_CAPTURE_STA;	//输入捕获状态		    				
extern INT32U	TIM4CH1_CAPTURE_VAL;	//输入捕获值


//NB变量

extern INT8U ConnectStatus;															// 用于保存网络连接状态  =0：未连接	=1：已连接
extern INT8U DelCnt;
extern INT8U NBRvDelay;																	// 用于在NB模块接收某些命令的返回结果时，延时接收多条数据
extern INT16U NBUpdateCnt;																		// 	用于计更新生存期的时间
extern INT8U SendIntervalSecond;													// 用于存放数据发送间隔的秒数
extern INT16U SendIntervalMilli;													// 用于存放数据发送间隔的毫秒数
extern INT8U ReadSIData[6];
extern INT8U HaveOk;	


typedef struct
{
	u8 BriquettingPressure[4];															//成型压力
	u8 TonnageMolding[4];																		//成型吨位
	u8 MagnetizingA[6];																			//充磁电流
	u8 DemagnetizmA[5];																			//退磁电流
	u8 Size[5];																							//尺寸
	u8 Weight[6];																						//重量
	u8 PowderTime[2];																				//称粉记时
	u8 FacilityRecord[128];																	//压机成型数据记录
	u8 Time[32];																						//结果产生的时间
	u8 Number;																							//产品的个数
	u8 Count;																								//产品历史数据记录数
}Press;																										//压机设备结构体
extern Press Facility;


typedef struct 
{
	u8 Pack_ID[16];																					//包装员工ID
	u8 Profiling_ID[16];																		//压型员工ID
	u8 Mark[16];																						//原料编号
	u8 Facility[16];																				//设备编号
}Number;																									//编号结构体			
extern Number SerialNumber;



typedef struct																						//用于存放保养记录
{		
	
	u8 Time[32];																					  //时间
	u8 Name[16];																						//名字
	u8 Data[32];																						//保养内容	
	u8 DataNumber[8];																				//保养内容编号
	u8 MaintainNum;																				  //保养记录数
	u8 MaintainData[128];																		//保养信息整合
	u8 NextTime[16];																				//下次保养的时间
}Record;
extern Record Maintain;																		//保养记录的结构体变量

typedef struct
{
		u8 Facility;																					//设备号
		u8 TimeNum[8];																				//距离的时间数
	  u8 HourlyBasis;																				//时间单位
		u8 NBTimeNum;																					//NB收到的距离时间数
}NBAccept;
extern NBAccept Maintenance;															//距离保养设备的时间结构体变量

typedef struct
{
	u8  MouldData[64];																			//模具
	u8  ResultData[64];																			//结果
	u8  Granularity[64];																		//粒度
	u8 	Time[16];																						//产生结果的时间
}Gain;													
extern Gain GainData; 																		//获取的信息数据变量定义
extern Gain GainNumber;																		//获取的信息编号变量定义

extern u8 ProductResult[];																//产品合格数组
extern u8 ProductResult1[];																//产品结果数组1
extern u8 ProductResult1[];																//产品结果数组2
extern u8 ProductResult2[];																//产品结果数组3
extern u8 ProductResult3[];																//产品结果数组4
extern u8 ProductResult4[];																//产品结果数组5
extern u8 ProductResult5[];																//产品结果数组6
extern u8 ProductResult6[];																//产品结果数组7
extern u8 ProductResult7[];																//产品结果数组8
extern u8 ProductResult8[];																//产品结果数组9

typedef struct
{
	u8  Temperature[16];																			//温度
	u8  Humidity[16];																					//湿度
	u8  PM[16];																								//PM2.5
}Environment;																								//

extern Environment	EnvironmentData;												//环境数据结构体变量
#endif
/***********************************************************************************/
// 文件结束
/***********************************************************************************/
