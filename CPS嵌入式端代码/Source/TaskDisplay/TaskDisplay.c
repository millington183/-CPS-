/************************************************************************************
*  Copyright (c), 2019, 江西理工大学
*            All rights reserved.
*
* http:  www.jxust.edu.cn
* Email: 
*
* File name: TaskDisplay.c
* Project  : 智能分拣系统串口屏任务模块
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  
* Version: 1.00
* Date:    2020.01.14			
* Email:   
* 
* Description: 本文件负责基于串口实现处理器与串口屏的通信; 
*
* Others: none;
*
* Function List:
*		
* History:
*   1. Author:			  
*	   Version: 	 		0.01
*	   Date:        	2020.01.14
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
#include "PIONEER_Config.h"
#include "STM32F4_Head.h"
#include "OSVars.h"
#include "UserVars.h"

#include "hmi_driver.h"
#include "hmi_user_uart.h"
#include "cmd_queue.h"
#include "cmd_process.h"
#include "stdio.h"

#include "ulitity.h"
#include "string.h"
#include "delay.h"
#include "stm32f4xx.h"

#include "APP_Init.h"


#define TIME_100MS 10                                                                //100毫秒(10个单位)
#define MaintainID         3																												 //保养信息ID


/************************************************************************************/

/************************************************************************************/
// 常量及全局变量定义
/************************************************************************************/
INT8U OS_Err;
INT8U SendBuf[12];
INT8U InfoHead;
INT8U RTCFlag1;


u8 NBMaintainIDData[128];																														//整合保养数据

volatile uint32  timer_tick_count = 0;                                               //定时器节拍

uint8  cmd_buffer[CMD_MAX_SIZE];                                                     //指令缓存
static uint16 current_screen_id = 0;                                                 //当前画面ID
static int32 progress_value = 0;                                                     //进度条测试值
static int32 test_value = 0;                                                         //测试值
static uint8 update_en = 0;                                                          //更新标记
static int32 meter_flag = 0;                                                         //仪表指针往返标志位
static int32 num = 0;                                                              //曲线采样点计数
static int sec = 1;                                                                  //时间秒
static int32 curves_type = 0;                                                        //曲线标志位  0为正弦波，1为锯齿波                  
static int32 second_flag=0;                                                          //时间标志位
static int32 icon_flag = 0;                                                          //图标标志位
static int years,months,weeks,days,hours,minutes; 
static uint8 Select_H ;                                                              //滑动选择小时
static uint8 Select_M ;                                                              //滑动选择分钟 
static uint8 Last_H ;                                                                //上一个选择小时
static uint8 Last_M;                                                                 //上一个选择分钟 
static int32 Progress_Value = 0;                                                     //进度条的值 

void UpdateUI(void);                                                                 //更新UI数据

/***********************************************************************************
* Function: Display_Task;
*
* Description: Display任务;
*              
* Input:  none;
*
* Return: none;
*
* Note:   本函数负责进行串口屏接收的数据进行处理
*
************************************************************************************/
void Display_Task(void *p_arg)		
{	 
		INT8U RTCERR;
		static int32 test_value = 0;                                                     //测试值
    uint32 timer_tick_last_update = 0;                                               //上一次更新的时间
    qsize  size = 0;
		Maintain.MaintainNum=0;                                                          
    //配置时钟
    //Set_System(); 
		SystemInit();
    //配置串口中断                                                                
    //Interrupts_Config();                                                            
    //配置时钟节拍                                                                
    systicket_init();                                                               
    //串口初始化                                              
    //UartInit(9600);                                                               

    //清空串口接收缓冲区                                                          
    queue_reset();                                                                  

    //延时等待串口屏初始化完毕,必须等待300ms                                      
    delay_ms(300); 

		SetControlVisiable(1,9,0);		//隐藏人工识别的文本框
		SetControlVisiable(1,21,0);		//隐藏人工识别的下拉菜单
    while(1)                                                                        
    {      
        size = queue_find_cmd(cmd_buffer,CMD_MAX_SIZE); 			//从缓冲区中获取一条指令         
			if(size>0)                                      
        {            
            ProcessMessage((PCTRL_MSG)cmd_buffer, size);                             //指令处理  
        } 
        //    特别注意
        //    MCU不要频繁向串口屏发送数据，否则串口屏的内部缓存区会满，从而导致数据丢失(缓冲区大小：标准型8K，基本型4.7K)
        //    1) 一般情况下，控制MCU向串口屏发送数据的周期大于100ms，就可以避免数据丢失的问题；
        //    2) 如果仍然有数据丢失的问题，请判断串口屏的BUSY引脚，为高时不能发送数据给串口屏。

        //    TODO: 添加用户代码
        //    数据有更新时标志位发生改变，定时100毫秒刷新屏幕
        if(update_en&&timer_tick_count-timer_tick_last_update>=TIME_100MS)
        {
            update_en = 0;
            timer_tick_last_update = timer_tick_count;   

            UpdateUI();
        }
  
        //这里为了演示方便，每20毫秒自动更新一次
        //进一次中断10ms，timer_tick_count值+1,100*timer_tick_count = 1s
        if(timer_tick_count%2==0)
        {   
            UpdateUI(); 
        }
				
				if(ProductResultFlag == 1)														//通过外部按键判断从而去增加记录
				{
						GetControlValue(1,9);														//获取结果通过菜单录入的值
						ProductResultFlag=0;
				}
				
				if(CameraFlag == 1)																		//通过摄像头判断的方式去增加记录
				{
					GetControlValue(1,27);														//获取机器视觉的值
					CameraFlag=0;
				}
				
				delay_ms(10);
    }  
}

/*! 
*  \brief  消息处理流程
*  \param msg 待处理消息
*  \param size 消息长度
*/
void ProcessMessage( PCTRL_MSG msg, uint16 size )
{
	
    uint8 cmd_type = msg->cmd_type;                                                  //指令类型
    uint8 ctrl_msg = msg->ctrl_msg;                                                  //消息的类型
    uint8 control_type = msg->control_type;                                          //控件类型
    uint16 screen_id = PTR2U16(&msg->screen_id);                                     //画面ID
    uint16 control_id = PTR2U16(&msg->control_id);                                   //控件ID
    uint32 value = PTR2U32(msg->param);                                              //数值
		//printf("解析");
    switch(cmd_type)
    {  
    case NOTIFY_TOUCH_PRESS:                                                        //触摸屏按下
    case NOTIFY_TOUCH_RELEASE:                                                      //触摸屏松开
        NotifyTouchXY(cmd_buffer[1],PTR2U16(cmd_buffer+2),PTR2U16(cmd_buffer+4)); 
        break;                                                                    
    case NOTIFY_WRITE_FLASH_OK:                                                     //写FLASH成功
        NotifyWriteFlash(1);                                                      
        break;                                                                    
    case NOTIFY_WRITE_FLASH_FAILD:                                                  //写FLASH失败
        NotifyWriteFlash(0);                                                      
        break;                                                                    
    case NOTIFY_READ_FLASH_OK:                                                      //读取FLASH成功
        NotifyReadFlash(1,cmd_buffer+2,size-6);                                     //去除帧头帧尾
        break;                                                                    
    case NOTIFY_READ_FLASH_FAILD:                                                   //读取FLASH失败
        NotifyReadFlash(0,0,0);                                                   
        break;                                                                    
    case NOTIFY_READ_RTC:                                                           //读取RTC时间
        NotifyReadRTC(cmd_buffer[2],cmd_buffer[3],cmd_buffer[4],cmd_buffer[5],cmd_buffer[6],cmd_buffer[7],cmd_buffer[8]);
        break;
    case NOTIFY_CONTROL:
        {
            if(ctrl_msg==MSG_GET_CURRENT_SCREEN)                                    //画面ID变化通知
            {
                NotifyScreen(screen_id);                                            //画面切换调动的函数
            }
            else
            {
                switch(control_type)
                {
                case kCtrlButton:                                                   //按钮控件
                    NotifyButton(screen_id,control_id,msg->param[1]);                  
                    break;                                                             
                case kCtrlText:                                                     //文本控件
                    NotifyText(screen_id,control_id,msg->param);                       
                    break;                                                             
                case kCtrlProgress:                                                 //进度条控件
                    NotifyProgress(screen_id,control_id,value);                        
                    break;                                                             
                case kCtrlSlider:                                                   //滑动条控件
                    NotifySlider(screen_id,control_id,value);                          
                    break;                                                             
                case kCtrlMeter:                                                    //仪表控件
                    NotifyMeter(screen_id,control_id,value);                           
                    break;                                                             
                case kCtrlMenu:                                                     //菜单控件
                    NotifyMenu(screen_id,control_id,msg->param[0],msg->param[1]);      
                    break;                                                              
                case kCtrlSelector:                                                 //选择控件
                    NotifySelector(screen_id,control_id,msg->param[0]);                
                    break;                                                              
                case kCtrlRTC:                                                      //倒计时控件
                    NotifyTimer(screen_id,control_id);
                    break;
                default:
                    break;
                }
            } 
            break;  
        } 
    case NOTIFY_HandShake:                                                          //握手通知                                                     
        NOTIFYHandShake();
        break;
    default:
        break;
    }
}

/*! 
*  \brief  握手通知
*/
void NOTIFYHandShake()
{
   SetButtonValue(3,2,1);
}


/*! 
*  \brief  画面切换通知
*  \details  当前画面改变时(或调用GetScreen)，执行此函数
*  \param screen_id 当前画面ID
*/
void NotifyScreen(uint16 screen_id)
{
    //TODO: 添加用户代码
    current_screen_id = screen_id;                                                   //在工程配置中开启画面切换通知，记录当前画面ID

}

/*! 
*  \brief  触摸坐标事件响应
*  \param press 1按下触摸屏，3松开触摸屏
*  \param x x坐标
*  \param y y坐标
*/
void NotifyTouchXY(uint8 press,uint16 x,uint16 y)
{ 
    //TODO: 添加用户代码
}


/*! 
*  \brief  更新数据
*/ 
void UpdateUI()
{
		INT8U RTCSemERR;
    //实时曲线，正弦波数组。  定时20ms更新数据
//    if(current_screen_id == 8)      
//    { 
//           //正弦数组
//				printf("串口屏更新数据%s",Facility.BriquettingPressure);
//				//GraphChannelDataAdd(8,1,0,(uint8 *)&BriquettingPressure[num],1);  			//添加数据到曲线  一次两个数据
//					num+=1;
//			if(num>=6)
//			{
//				num=0;
//				printf("数组");
//			}
//     }   

		if(current_screen_id==2)													//保养界面
			{
				if(Maintain.MaintainNum>=5)										//当记录数大于5时
					{
						Record_DelData(2,8,5);										//删除第5条记录
						//printf("画面二");
						Maintain.MaintainNum=4;										//保养记录数为4
					}
			}
			
			if(current_screen_id==9)												//压型数据记录界面
			{
				if(Facility.Count>=10)												//当压型数据记录大于10
					{
						Record_DelData(9,1,10);										//删除第10条记录
						Facility.Count=9;												//压型数据记录数为9
					}
			}
			
}

/*! 
*  \brief  按钮控件通知
*  \details  当按钮状态改变(或调用GetControlValue)时，执行此函数
*  \param screen_id 画面ID
*  \param control_id 控件ID
*  \param state 按钮状态：0弹起，1按下
*/
void NotifyButton(uint16 screen_id, uint16 control_id, uint8  state)
{ 
	
	switch(screen_id)
	{
		case 1:																								
		{
			if(control_id == 16)																					 //主页的扫码按钮
			{
				if(state == 1)
				{
					ScanFlag=1;
				}
			}
		}
		case 2:
		{
			if(control_id == 2)																								//保养界面上传按钮
			{
				GetControlValue(2,3);																					//获取上传时间的文本值
				
			}
			if(control_id==10)																							//保养界面保存按钮
			{
				printf("保存键按下");
				
				ClearTextValue(2,5);																					//清除文本时间
				ClearTextValue(2,6);																					//清除文本人员
				ClearTextValue(2,7);																					//清除文本内容
				
				sprintf((char *)Maintain.MaintainData,"%s;%s;%s;",Maintain.Time,Maintain.Name,Maintain.Data);//将保养信息整合
				
				//sprintf((char *)NBMaintainIDData,"%d,%s,%s,%s",MaintainID,Maintain.Time,Maintain.Name,Maintain.Data);//将数据整合到NB数组
				
				printf("%s",Maintain.MaintainData);
			}
			if(control_id==11)																							//保养界面清除按钮
			{
				Record_Clear(2,8);																						//清除按键删除所有历史记录
				Maintain.MaintainNum=0;													
			}
			if(control_id==12)																							//保养界面时间按钮
			{
				ReadRTC();
				
				printf("years=%4d months=%d days=%d hours=%d minutes=%d sec=%d",years,months,days,hours,minutes,sec);//保养界面时间按钮
				
				sprintf((char *)Maintain.Time,"%d-%d-%d %d:%d:%d",years,months,days,hours,minutes,sec);	//获取时间
				
				SetTextValue(2,5,(uchar*)Maintain.Time);											//显示时间
			}
			break;
		}
		
		case 3:
		{
			if(control_id==4)																					//返回键
			{
				ScanFlag=0;																							//扫码标志为0
			}
			if(control_id==5)																					//压型人员编号
			{
				ClearTextValue(3,1);
			}
			if(control_id==7)
			{
				ClearTextValue(3,2);
			}
			if(control_id==8)																					//原料编号的保存键
			{
				SetTextValue(1,2,(u8 *)SerialNumber.Mark);							//设置原料编号到工作界面
				ClearTextValue(3,3);
			}	
			
			if(control_id==9)																					//设备编号的保存键
			{
				SetTextValue(1,1,(u8 *)SerialNumber.Facility);					//设置设备编号到工作界面
				ClearTextValue(3,6);
			}
			
			break;
		}
		
		case 5:
		{
			if(control_id==2)																						//保存按钮中是否保存弹窗的是
			{
				if(state==1)
				{		
					Record_Insertion(2,8,0,(uchar *)Maintain.MaintainData);	//添加一条保养记录信息			
					
					//OSQPost(NBDataQ,NBMaintainIDData);											//上传数据到OneNet
					
					memset(NBMaintainIDData,0,sizeof(NBMaintainIDData));		//清空保养信息上传数组
					
					Maintain.MaintainNum++;																	//保养记录数加一
					
					printf("MaintainNum==%d",Maintain.MaintainNum);
				}
			}
			
			break;
		}
		
		case 9:
		{
			if(control_id==4)																						//工作记录的清除按钮
			{
				Record_Clear(9,1);																				//清除历史记录
			}
			break;
		}
		
		case 10:
		{
			if(control_id==2)																						//是否上传弹窗的是
			{
				if(state==1)
				{
					
					OSQPost(NBDataQ,NBMaintainIDData);											//上传数据到OneNet
					
					ClearTextValue(2,3);
					memset(NBMaintainIDData,0,sizeof(NBMaintainIDData));		//清空保养信息上传数组
				}
			}
			break;
		}
		
		case 16://设置界面
		{
			if(control_id==3)
			{
				if(state==1)
				{
					
					DetectionMode=0;							//检测模式为机器视觉
					SetControlVisiable(1,9,0);		//隐藏人工识别的文本框
					SetControlVisiable(1,21,0);		//隐藏人工识别的下拉菜单
					
				}
			}
			if(control_id==4)
			{
				if(state==1)
				{
					DetectionMode=1;							//检测模式为人工检测
					SetControlVisiable(1,9,1);		//显示人工识别的文本框
					SetControlVisiable(1,21,1);		//显示人工识别的下拉菜单
				}
			}
		}
		
		default :;
	}
}

/*! 
*  \brief  文本控件通知
*  \details  当文本通过键盘更新(或调用GetControlValue)时，执行此函数
*  \details  文本控件的内容以字符串形式下发到MCU，如果文本控件内容是浮点值，
*  \details  则需要在此函数中将下发字符串重新转回浮点值。
*  \param screen_id 画面ID
*  \param control_id 控件ID
*  \param str 文本控件内容
*/
void NotifyText(uint16 screen_id, uint16 control_id, uint8 *str)
{
	switch(screen_id)
	{
		case 1:
		{
			if(control_id==9)																										//获取结果的值	
			{
					
				ReadRTC();																											//发送产品结果产生时间的信号量

				//printf("%s",str);
				sprintf((char *)GainData.ResultData,"%s",str);										//整合为获取的结果数据
				
				sprintf((char *)Facility.Time,"%d-%d-%d %d:%d:%d",years,months,days,hours,minutes,sec);	//获取时间
				
				sprintf((char *)Facility.FacilityRecord,"%s;%s;%s;%s;%s;%s;%s;",Facility.Time,					//整合压型数据记录
									SerialNumber.Mark,Facility.BriquettingPressure,Facility.TonnageMolding,
				Facility.MagnetizingA,Facility.DemagnetizmA,GainData.ResultData);
				
				//printf("压型数据记录%s",Facility.FacilityRecord);
				
				Record_Insertion(9,1,0,(u8 *)Facility.FacilityRecord);						//在第0行增加一条数据记录
			}
			
//			if(control_id==11)																										//模具文本控件
//			{
//				printf("%s",str);
//				sprintf((char *)GainData.MouldData,"%s",str);												//获取模具的值
//			}
			
//			if(control_id==12)																										//粒度文本控件
//			{
//				printf("%s",str);
//				sprintf((char *)GainData.MouldData,"%s",str);												//获取粒度的值
//			}
			
			if(control_id == 27)
			{
				ReadRTC();																											//发送产品结果产生时间的信号量

				sprintf((char *)GainData.ResultData,"%s",str);										//整合为获取的结果数据
				
				sprintf((char *)Facility.Time,"%d-%d-%d %d:%d:%d",years,months,days,hours,minutes,sec);	//获取时间
				
				sprintf((char *)Facility.FacilityRecord,"%s;%s;%s;%s;%s;%s;%s;",Facility.Time,					//整合压型数据记录
									SerialNumber.Mark,Facility.BriquettingPressure,Facility.TonnageMolding,
				Facility.MagnetizingA,Facility.DemagnetizmA,GainData.ResultData);
	
				Record_Insertion(9,1,0,(u8 *)Facility.FacilityRecord);						//在第0行增加一条数据记录
			}
			break;
		}
		
		case 2:
		{
			if(control_id==3)																										//保养界面的下次保养时间
			{
				sprintf((char *)Maintain.NextTime,"%s",str);											//获取下次保养的时间
				
				sprintf((char *)NBMaintainIDData,"%d,%s,%s,%s,%s,%s",MaintainID,SerialNumber.Facility,Maintain.
				Name,Maintain.Time,Maintain.DataNumber,Maintain.NextTime);//将数据整合到NB数组
			
			}
			if(control_id==6)																										//保养界面的人员
			{
				sprintf((char *)Maintain.Name,"%s",str);													//整合人员输入的数据
				printf("%s",Maintain.Name);
			}
			
			if(control_id==7)																										//保养界面的保养内容
			{
				sprintf((char *)Maintain.Data,"%s",str);													//整合保养界面的保养内容
				printf("%s",Maintain.Data);																				
			}
			
			break;
		}
		
		default:;
	}
}	                                                                             

/*!                                                                              
*  \brief  进度条控件通知                                                       
*  \details  调用GetControlValue时，执行此函数                                  
*  \param screen_id 画面ID                                                      
*  \param control_id 控件ID                                                     
*  \param value 值                                                              
*/                                                                              
void NotifyProgress(uint16 screen_id, uint16 control_id, uint32 value)           
{  
    //TODO: 添加用户代码   
}                                                                                

/*!                                                                              
*  \brief  滑动条控件通知                                                       
*  \details  当滑动条改变(或调用GetControlValue)时，执行此函数                  
*  \param screen_id 画面ID                                                      
*  \param control_id 控件ID                                                     
*  \param value 值                                                              
*/                                                                              
void NotifySlider(uint16 screen_id, uint16 control_id, uint32 value)             
{                                                             
 
}

/*! 
*  \brief  仪表控件通知
*  \details  调用GetControlValue时，执行此函数
*  \param screen_id 画面ID
*  \param control_id 控件ID
*  \param value 值
*/
void NotifyMeter(uint16 screen_id, uint16 control_id, uint32 value)
{
    //TODO: 添加用户代码
}

/*! 
*  \brief  菜单控件通知
*  \details  当菜单项按下或松开时，执行此函数
*  \param screen_id 画面ID
*  \param control_id 控件ID
*  \param item 菜单项索引
*  \param state 按钮状态：0松开，1按下
*/
void NotifyMenu(uint16 screen_id, uint16 control_id, uint8 item, uint8 state)
{
    //TODO: 添加用户代码
	INT8U err;
		switch(screen_id)
	{
		case 1:
		{
			if(control_id==22)								//模具下拉菜单
			{
				printf("模具");
				if(item == 0)										//模具索引号
				{
					printf("块状");
					
					sprintf((char *)GainNumber.MouldData,"%d",1);
					
					printf("模具的索引号是%s\n",GainNumber.MouldData);
				}
				if(item == 1)									//模具索引号
				{
					printf("圆柱");			
					
					sprintf((char *)GainNumber.MouldData,"%d",2);
					
					printf("模具的索引号是%s\n",GainNumber.MouldData);
				}
//				if(state==1)
//				{
//					GetControlValue(1,11);				//获取模具通过菜单录入的值
//				}
			}
			
			if(control_id==21)								//人工检测下拉菜单
			{
			
				if(item == 0)											//人工检测索引号
				{
					if(state == 0)
					{
					printf("圆柱-缺角-磕碰\r\n");			

					sprintf((char *)GainNumber.ResultData,"%d",1);
					ProcessingFlag=1;																//产品合格标志为1
					printf("产品结果的索引号是%s\r\n",GainNumber.ResultData);
					OSSemPost(ResultSem);
					}
				}
				if(item == 1)											//人工检测索引号
				{
					if(state == 0)
					{
					printf("圆柱-缺角-软边\r\n");			
					
					sprintf((char *)GainNumber.ResultData,"%d",2);
					ProcessingFlag=1;																//产品合格标志为1
					printf("产品结果的索引号是%s\r\n",GainNumber.ResultData);
					OSSemPost(ResultSem);
					}
				}
				if(item == 2)											//人工检测索引号
				{
					if(state == 0)
					{
					printf("圆柱-偏位不良\r\n");			
					
					sprintf((char *)GainNumber.ResultData,"%d",3);
					ProcessingFlag=1;																//产品合格标志为1
					printf("产品结果的索引号是%s\r\n",GainNumber.ResultData);
					OSSemPost(ResultSem);
					}
				}
				if(item == 3)											//人工检测索引号
				{
					if(state == 0)
					{
					printf("圆柱-裂痕\r\n");			
					
					sprintf((char *)GainNumber.ResultData,"%d",4);
					ProcessingFlag=1;																//产品合格标志为1
					printf("产品结果的索引号是%s\r\n",GainNumber.ResultData);
					OSSemPost(ResultSem);
					}
				}
				if(item == 4)											//人工检测索引号
				{
					if(state == 0)
					{
					printf("块状-缺角-磕碰\r\n");			
					
					sprintf((char *)GainNumber.ResultData,"%d",5);
					ProcessingFlag=1;																//产品合格标志为1
					printf("产品结果的索引号是%s\r\n",GainNumber.ResultData);
					OSSemPost(ResultSem);
					}
					
				}
				if(item == 5)											//人工检测索引号
				{
					if(state == 0)
					{
					printf("块状-缺角-拿捏不当\r\n");			
					
					sprintf((char *)GainNumber.ResultData,"%d",6);
					ProcessingFlag=1;																//产品合格标志为1
					printf("产品结果的索引号是%s\r\n",GainNumber.ResultData);
					OSSemPost(ResultSem);
					}
				}
				if(item == 6)											//人工检测索引号
				{
					if(state == 0)
					{
					printf("块状-缺角-模具不良\r\n");			
					
					sprintf((char *)GainNumber.ResultData,"%d",7);
					ProcessingFlag=1;																//产品合格标志为1
					printf("产品结果的索引号是%s\r\n",GainNumber.ResultData);
					OSSemPost(ResultSem);
					}
				}
				if(item == 7)											//人工检测索引号
				{
					if(state == 0)
					{
					printf("块状-斜横\r\n");			
					
					sprintf((char *)GainNumber.ResultData,"%d",8);
					ProcessingFlag=1;																//产品合格标志为1
					printf("产品结果的索引号是%s\r\n",GainNumber.ResultData);
					OSSemPost(ResultSem);
					}
					
				}
			}
			
			if(control_id==29)								//粒度下拉菜单
			{
				if(item == 0)
				{
					printf("小粒\r\n");
					
					sprintf((char *)GainNumber.Granularity,"%d",0);
																					//产品合格标志为1
					printf("产品结果的索引号是%s\r\n",GainNumber.Granularity);
					
				}
				if(item == 1)
				{
					printf("大粒\r\n");
					
					sprintf((char *)GainNumber.Granularity,"%d",1);
					
					printf("产品结果的索引号是%s\r\n",GainNumber.Granularity);
				}
			}
				
//				if(state==1)
//				{
//					GetControlValue(1,12);				//获取粒度通过菜单录入的值
//				}
			}
			break;
			
		case 2:
		{
			if(control_id==17)
			{
				if(state==1)
				{
					GetControlValue(2,7);				 //获取保养内容从菜单录入的值
				}
				if(item == 0)											//人工检测索引号
				{
					printf("清洁、润滑\r\n");			

					sprintf((char *)Maintain.DataNumber,"%d",1);
					
					printf("产品结果的索引号是%s\r\n",Maintain.DataNumber);
				}
				if(item == 1)
				{
					printf("调整\r\n");
					
					sprintf((char *)Maintain.DataNumber,"%d",2);
					
					printf("产品结果的索引号是%s\r\n",Maintain.DataNumber);
				}
				if(item == 2)
				{
					printf("防腐\r\n");
					
					sprintf((char *)Maintain.DataNumber,"%d",3);
					
					printf("产品结果的索引号是%s\r\n",Maintain.DataNumber);
				}
				if(item == 3)
				{
					printf("检测排故\r\n");
					
					sprintf((char *)Maintain.DataNumber,"%d",4);
					
					printf("产品结果的索引号是%s\r\n",Maintain.DataNumber);
				}
			}
			break;	
		}
		
		default :;
	
	}
	
}

/*! 
*  \brief  选择控件通知
*  \details  当选择控件变化时，执行此函数
*  \param screen_id 画面ID
*  \param control_id 控件ID
*  \param item 当前选项
*/
void NotifySelector(uint16 screen_id, uint16 control_id, uint8  item)
{
    if(screen_id == 13&&control_id == 1)                                               //获取当前选择控件的值
    {
        Select_H =  item;
    } 
    if(screen_id == 13&&control_id == 2)                                               //获取当前选择控件的值
    {
        Select_M =  item;
    } 

}

/*! 
*  \brief  定时器超时通知处理
*  \param screen_id 画面ID
*  \param control_id 控件ID
*/
void NotifyTimer(uint16 screen_id, uint16 control_id)
{
    if(screen_id==8&&control_id == 7)
    {
        SetBuzzer(100);
    } 
}

/*! 
*  \brief  读取用户FLASH状态返回
*  \param status 0失败，1成功
*  \param _data 返回数据
*  \param length 数据长度
*/
void NotifyReadFlash(uint8 status,uint8 *_data,uint16 length)
{
    //TODO: 添加用户代码
}

/*! 
*  \brief  写用户FLASH状态返回
*  \param status 0失败，1成功
*/
void NotifyWriteFlash(uint8 status)
{
    //TODO: 添加用户代码
}

/*! 
*  \brief  读取RTC时间，注意返回的是BCD码
*  \param year 年（BCD）
*  \param month 月（BCD）
*  \param week 星期（BCD）
*  \param day 日（BCD）
*  \param hour 时（BCD）
*  \param minute 分（BCD）
*  \param second 秒（BCD）
*/
void NotifyReadRTC(uint8 year,uint8 month,uint8 week,uint8 day,uint8 hour,uint8 minute,uint8 second)
{      
    sec    =(0xff & (second>>4))*10 +(0xf & second);                                    //BCD码转十进制
    years   =(0xff & (year>>4))*10 +(0xf & year);                                      
    months  =(0xff & (month>>4))*10 +(0xf & month);                                     
    weeks   =(0xff & (week>>4))*10 +(0xf & week);                                      
    days    =(0xff & (day>>4))*10 +(0xf & day);                                      
    hours   =(0xff & (hour>>4))*10 +(0xf & hour);                                       
    minutes =(0xff & (minute>>4))*10 +(0xf & minute);                                                                                                                  
}


