/************************************************************************************
*  Copyright (c), 2019, 江西理工大学
*            All rights reserved.
*
* http:  www.jxust.edu.cn
* Email: 
*
* File name: UserVars.c
* Project  : STM32F4XX系列模块软件
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  智慧工厂研究所
* Version: 1.00
* Date:    2019.11.25			
* Email:   
* 
* Description: 本文件负责用户应用程序公共全局变量, 客户可以把应用的全局变量设置到这里;
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
#include "UserVars.h"	
USER_VARS UserVars;	     																							// 用户变量

Number SerialNumber={"0","0","0","0"};     														//编号变量定义
Record Maintain={"0","0","0","0",0,"0","0"};				 									//保养记录编号定义
Gain GainData={"0","0","0","0"};           														//获取的信息变量定义
Gain GainNumber={"0","0","0","0"};																		//获取的信息编号变量定义
Press Facility={"0","0","0","0","0","0","0","0","0",0,0};							//压机设备数据结构体
Environment	EnvironmentData={"0","0","0"};														//环境数据结构体变量
NBAccept Maintenance={0,"0",0,0};																			//距离保养设备的时间结构体变量


u32 FLASH_SIZE=128*1024*1024;	//开始写入的FLash地址	

u32 FLASH_SIZE_Count;					//所用的FLASH地址

u8 DetectionMode;							//检测方式
u8 CameraFlag;								//通过摄像头检测的标志
u8 ScanFlag;									//扫码标志
u8 UploadingFlag;							//数据上传NB标志
u8 ProductResultFlag=0;				//通过外部按键按下时产品历史记录
u8 CameraRedFlag;							//红外对管检测到的标志
u8 ProcessingFlag;						//产品合格标志

u8 ProductResult[]="合格";
u8 ProductResult1[]="圆柱-缺角-磕碰";
u8 ProductResult2[]="圆柱-缺角-软边";
u8 ProductResult3[]="圆柱-偏位不良";
u8 ProductResult4[]="圆柱-裂痕";
u8 ProductResult5[]="块状-缺角-磕碰";
u8 ProductResult6[]="块状-缺角-拿捏不当";
u8 ProductResult7[]="块状-缺角-模具不良";
u8 ProductResult8[]="块状-斜横";



void *DisplayQMsg[32];		// 定义消息队列DisaplayQ的指针数组
INT8U DisMemData[32][64]; // 定义串口屏显示内容存放存储区所需的空间（50块每块64字节）



INT8U UART1_RX_BUF[UART1_RXBUF_SIZE];     //接收缓冲,最大UART1_RXBUF_SIZE个字节.
INT8U UART2_RX_BUF[UART2_RXBUF_SIZE];
INT8U UART3_RX_BUF[UART3_RXBUF_SIZE];
INT8U UART4_RX_BUF[UART4_RXBUF_SIZE];
INT8U UART5_RX_BUF[UART5_RXBUF_SIZE];
INT8U UART6_RX_BUF[UART6_RXBUF_SIZE];
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
INT16U UART1_RX_STA=0;       //接收状态标记	.
INT16U UART2_RX_STA=0;
INT16U UART3_RX_STA=0;
INT16U UART4_RX_STA=0;
INT16U UART5_RX_STA=0;
INT16U UART6_RX_STA=0;


INT8U  TIM4CH1_CAPTURE_STA=0;	//输入捕获状态		    				
INT32U	TIM4CH1_CAPTURE_VAL;	//输入捕获值


//全局变量

//NB变量
INT8U ConnectStatus=0;															// 用于保存网络连接状态  =0：未连接	=1：已连接
INT8U DelCnt=0;
INT8U NBRvDelay=0;																	// 用于在NB模块接收某些命令的返回结果时，延时接收多条数据
INT16U NBUpdateCnt;																		// 	用于计更新生存期的时间
INT8U SendIntervalSecond=3;													// 用于存放数据发送间隔的秒数
INT16U SendIntervalMilli=0;													// 用于存放数据发送间隔的毫秒数
INT8U ReadSIData[6];
INT8U HaveOk=0;	




/***********************************************************************************/
// 文件结束
/***********************************************************************************/
