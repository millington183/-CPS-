/************************************版权申明********************************************
**                             广州大彩光电科技有限公司
**                             http://www.gz-dc.com
**-----------------------------------文件信息--------------------------------------------
** 文件名称:   ulitity.c
** 修改时间:   2018-05-18
** 文件说明:   用户MCU串口驱动函数库
** 技术支持：  Tel: 020-82186683  Email: hmi@gz-dc.com Web:www.gz-dc.com
--------------------------------------------------------------------------------------*/
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

#include "lcdscreen.h"

#define TIME_100MS 10                                                                //100毫秒(10个单位)

int value[8];                                                                       //各模块数据
uint8 level[10]={0xff,0xe0,0xc4,0xa8,0x8c,0x70,0x54,0x38,0x1c,0x00};                 //亮度等级
int Model_Number;                                                                    //批号记录值
uint16 Record_Number;                                                                   //批号数量
int Record_Flag=0;                                                                   //记录控件读取标志位
int Down5_1=0;																																				//按键按下标志位
int Down12_4=0;
uint8 *username=(uint8*)"root";                                                             //用户名
uint8 password[8];                                                         //用户密码
int PassWord_OK=0,UserName_OK=0;                                                            //登录输入的账号密码标志位
int OldPassWord=0,ResetPassWord=0;                                                          //修改密码标志位
uint8 SetPassWord[8];                                                                         //临时存新密码

volatile uint32  timer_tick_count = 0;                                               //定时器节拍

uint8  cmd_buffer[CMD_MAX_SIZE];                                                     //指令缓存
static uint16 current_screen_id = 0;                                                 //当前画面ID
//static int32 progress_value = 0;                                                     //进度条测试值
//static int32 test_value = 0;                                                         //测试值
static uint8 update_en = 0;                                                          //更新标记
//static int32 meter_flag = 0;                                                         //仪表指针往返标志位
//static int32 num = 0;                                                                //曲线采样点计数
//static int sec = 1;                                                                  //时间秒
//static int32 curves_type = 0;                                                        //曲线标志位  0为正弦波，1为锯齿波                  
//static int32 second_flag=0;                                                          //时间标志位
//static int32 icon_flag = 0;                                                          //图标标志位
//static uint8 Select_H ;                                                              //滑动选择小时
//static uint8 Select_M ;                                                              //滑动选择分钟 
//static uint8 Last_H ;                                                                //上一个选择小时
//static uint8 Last_M;                                                                 //上一个选择分钟 
static int32 Progress_Value = 0;                                                     //进度条的值 

void UpdateUI(void);                                                                 //更新UI数据


/*!                                                                                 
*  \brief  程序入口
*/                                                                                  
void LcdScreen()
{                                                                              

    uint32 timer_tick_last_update = 0;                                               //上一次更新的时间
    qsize  size = 0;
    //配置时钟
    SystemInit();                                                                   
    //配置串口中断                                                                
    //Interrupts_Config();                                                            
    //配置时钟节拍                                                                
    systicket_init();                                                               
    //串口初始化                                              
    //UartInit(19200);                                                               

    //清空串口接收缓冲区                                                          
    queue_reset();                                                                  

    //延时等待串口屏初始化完毕,必须等待300ms                                      
    delay_ms(300);                                                                  

    while(1)                                                                        
    {                                                                               
        size = queue_find_cmd(cmd_buffer,CMD_MAX_SIZE);                              //从缓冲区中获取一条指令         

        if(size>0&&cmd_buffer[1]!=0x07)                                              //接收到指令 ，及判断是否为开机提示
        {                                                                     
            ProcessMessage((PCTRL_MSG)cmd_buffer, size);                             //指令处理  
        }
        else if(size>0&&cmd_buffer[1]==0x07)                                         //如果为指令0x07就软重置STM32  
        {                                                                           
            __disable_fault_irq();                                                   
            NVIC_SystemReset();                                                                                                                                          
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
						else if(ctrl_msg==0x55)
							NotifyRecord_Num(screen_id,control_id,msg->param[1]);
						else if(ctrl_msg==0x56)
							NotifyRecord(screen_id,control_id,msg->param);
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
		//hfl:代码

		if(screen_id == 4)
		{
			GetControlValue(5,2);									//获取压力最小值
			GetControlValue(5,3);									//获取压力最大值
			GetControlValue(5,20);									//获取直径最小值
			GetControlValue(5,23);									//获取直径最大值
			GetControlValue(5,21);									//获取电导率最大值
			GetControlValue(5,24);									//获取电导率最大值
			GetControlValue(5,22);									//获取延展率最大值
			GetControlValue(5,25);									//获取延展率最大值
		}

		if(screen_id==7)
		{
			GetControlValue(5,2);									//获取压力最小值
			GetControlValue(5,3);									//获取压力最大值
		}
		
		if(screen_id==8)
		{
			GetControlValue(5,20);									//获取直径最小值
			GetControlValue(5,23);									//获取直径最大值
		}
		
		if(screen_id==9)
		{
			GetControlValue(5,21);									//获取电导率最大值
			GetControlValue(5,24);									//获取电导率最大值
		}
		
		if(screen_id==10)
		{
			GetControlValue(5,22);									//获取延展率最大值
			GetControlValue(5,25);									//获取延展率最大值
		}
		
    //进入画面5读flash存的值


    //进到二维码页面生成二维码
    if(current_screen_id==3)
    {
        //二维码控件显示中文字符时，需要转换为UTF8编码，
        //通过“指令助手”，转换“www.gz-dc.com” ，得到字符串编码如下
        uint8 dat[] = {0xE9,0xBB,0x84,0xE9,0xA3,0x9E,0xE9,0xBE,0x99};
        SetTextValue(3,1,dat);                                                      //发送二维码字符编码                     
    }
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

    //实时曲线，正弦波数组。  定时20ms更新数据
    /*if(current_screen_id == 11)      
    { 
        if(curves_type == 0)
        {
            //正弦数组
            uint8 sin[256] = {1,1,1,1,1,2,3,4,6,8,10,13,15,
                19,22,25,29,33,38,42,47,52,57,62,68,73,79,85,91,97,103,109,115,121,127,134,
                140,146,152,158,164,170,176,182,187,193,198,203,208,213,217,222,226,230,233,
                236,240,242,245,247,249,251,252,253,254,254,254,254,254,253,252,251,249,247,
                245,242,240,236,233,230,226,222,217,213,208,203,198,193,187,182,176,170,164,
                158,152,146,140,134,128,121,115,109,103,97,91,85,79,73,68,62,57,52,47,42,38,
                33,29,25,22,19,15,13,10,8,6,4,3,2,1,1,1,1,1,2,3,4,6,8,10,13,15,
                19,22,25,29,33,38,42,47,52,57,62,68,73,79,85,91,97,103,109,115,121,127,134,
                140,146,152,158,164,170,176,182,187,193,198,203,208,213,217,222,226,230,233,
                236,240,242,245,247,249,251,252,253,254,254,254,254,254,253,252,251,249,247,
                245,242,240,236,233,230,226,222,217,213,208,203,198,193,187,182,176,170,164,
                158,152,146,140,134,128,121,115,109,103,97,91,85,79,73,68,62,57,52,47,42,38,
                33,29,25,22,19,15,13,10,8,6,4,3,2};

            GraphChannelDataAdd(11,1,0,&sin[num],2);                                    //添加数据到曲线  一次两个数据

            num += 2;                                                                        
            if(num >= 255)                                                                
            {                                                                             
                num =0;                                                                  
            }
        } 
        else if(curves_type == 1)
        {
            //锯齿波数组
            uint8 sawtooth[180] = {0,9,18,27,36,45,54,63,72,81,90,99,108,117,126,135,144,153,162,171,180,189,198,207,216,225,234,243,252,
                0,9,18,27,36,45,54,63,72,81,90,99,108,117,126,135,144,153,162,171,180,189,198,207,216,225,234,243,252,
                0,9,18,27,36,45,54,63,72,81,90,99,108,117,126,135,144,153,162,171,180,189,198,207,216,225,234,243,252,
                0,9,18,27,36,45,54,63,72,81,90,99,108,117,126,135,144,153,162,171,180,189,198,207,216,225,234,243,252,
                0,9,18,27,36,45,54,63,72,81,90,99,108,117,126,135,144,153,162,171,180,189,198,207,216,225,234,243,252,
                0,9,18,27,36,45,54,63,72,81,90,99,108,117,126,135,144,153,162,171,180,189,198,207,216,225,234,243,252};


            GraphChannelDataAdd(11,1,0,&sawtooth[num],2);                              //添加数据到曲线  一次两个数据
            num +=2 ;                                                                        
            if(num >= 180)                                                                
            {                                                                             
                num =0;                                                                  
            }
        }          
    }                                                                              

    //历时曲线，正弦波数组                                                         
    if(current_screen_id == 16 && timer_tick_count %100 == 0)                           //历史曲线控件采样周期1s一个点。//一次添加五个数据                                                    
    {   
        if(curves_type == 0)
        {        
            //正弦数组
            uint8 sin[256] = {1,1,1,1,1,2,3,4,6,8,10,13,15,
                19,22,25,29,33,38,42,47,52,57,62,68,73,79,85,91,97,103,109,115,121,127,134,
                140,146,152,158,164,170,176,182,187,193,198,203,208,213,217,222,226,230,233,
                236,240,242,245,247,249,251,252,253,254,254,254,254,254,253,252,251,249,247,
                245,242,240,236,233,230,226,222,217,213,208,203,198,193,187,182,176,170,164,
                158,152,146,140,134,128,121,115,109,103,97,91,85,79,73,68,62,57,52,47,42,38,
                33,29,25,22,19,15,13,10,8,6,4,3,2,1,1,1,1,1,2,3,4,6,8,10,13,15,
                19,22,25,29,33,38,42,47,52,57,62,68,73,79,85,91,97,103,109,115,121,127,134,
                140,146,152,158,164,170,176,182,187,193,198,203,208,213,217,222,226,230,233,
                236,240,242,245,247,249,251,252,253,254,254,254,254,254,253,252,251,249,247,
                245,242,240,236,233,230,226,222,217,213,208,203,198,193,187,182,176,170,164,
                158,152,146,140,134,128,121,115,109,103,97,91,85,79,73,68,62,57,52,47,42,38,
                33,29,25,22,19,15,13,10,8,6,4,3,2}; 

            HistoryGraph_SetValueInt8(16,1,&sin[num],1);                               //添加历史曲线数据         
            num++;
            if(num >= 255)
            {
                num =0;
            }
        } 
        else if(curves_type == 1)
        {          
            //锯齿波数组
            uint8 sawtooth[180] = {0,9,18,27,36,45,54,63,72,81,90,99,108,117,126,135,144,153,162,171,180,189,198,207,216,225,234,243,252,
                0,9,18,27,36,45,54,63,72,81,90,99,108,117,126,135,144,153,162,171,180,189,198,207,216,225,234,243,252,
                0,9,18,27,36,45,54,63,72,81,90,99,108,117,126,135,144,153,162,171,180,189,198,207,216,225,234,243,252,
                0,9,18,27,36,45,54,63,72,81,90,99,108,117,126,135,144,153,162,171,180,189,198,207,216,225,234,243,252,
                0,9,18,27,36,45,54,63,72,81,90,99,108,117,126,135,144,153,162,171,180,189,198,207,216,225,234,243,252,
                0,9,18,27,36,45,54,63,72,81,90,99,108,117,126,135,144,153,162,171,180,189,198,207,216,225,234,243,252};

            HistoryGraph_SetValueInt8(16,1,&sawtooth[num],1);                          //添加历史曲线数据        
            num++;
            if(num >= 90)
            {
                num =0;
            }
        } 


    }*/

}


/*
by  hfl

读取记录控件返回的批号数量
*/
void NotifyRecord_Num(uint16 screen_id,uint16 control_id,uint8 num)
{
			uint16 i=0,j=0;
			u8 data[18];
			Record_Number=(uint16)num;
			for(;i<(int)num;i++)
			{
					j=1;
					Record_GetData(12,1,num-1-i);
			}
			if(Record_Number==0&&j==0)
			{
				if(Down12_4!=1)                    //防止删除键创建数据记录
				{
					sprintf((char*)data,"%d;%d;%d;%d;%d;%d;%d;%d;%d;",Model_Number,value[0],value[1],value[2],value[3],value[4],value[5],value[6],value[7]);
					Record_Add(12,1,data);
				}
				else
				{
					Down12_4=0;
				}
			}
}

/*
by hfl

读取记录控件返回的一行数据

*/
void NotifyRecord(uint16 screen_id,uint16 control_id,uint8 *msg)
{
			uint8 data[18];
			int i,k=0;
			uint16 j[8]={2,3,20,23,21,24,22,25};
			Record_Number=Record_Number-1;
			if(msg[1]==0x3b)
			{
				if(Model_Number==(int)msg[0]-48)
				{
					if(Down5_1==1)
					{
						Down5_1=0;
						sprintf((char*)data,"%d;%d;%d;%d;%d;%d;%d;%d;%d;",Model_Number,value[0],value[1],value[2],value[3],value[4],value[5],value[6],value[7]);
						Record_ModifyData(12,1,Record_Number,data);
					}
					else if(Down12_4==1)
					{
						Down12_4=0;
						Record_DelData(12,1,(uint16)Record_Number);
					}
					else
					{
						for(i=2;i<strlen((const char*)msg);i++)
						{
							if(msg[i+1]!=0x3b)
							{
								if(msg[i+2]!=0x3b)
								{
									SetTextInt32(5,j[k],(msg[i]-48)*100+(msg[i+1]-48)*10+msg[i+2]-48,1,3);
									i+=3;k++;
								}
								else
								{
									SetTextInt32(5,j[k],(msg[i]-48)*10+msg[i+1]-48,1,3);
									i+=2;k++;
								}
							}
							else
							{
								SetTextInt32(5,j[k],msg[i]-48,1,3);
								i++;k++;
							}
						}
					}
					Record_Flag=1;
				}
			}
			else
			{
				if(Model_Number==((int)msg[0]-48)*10+(int)msg[1]-48)
				{
					if(Down5_1==1)
					{
						Down5_1=0;
						sprintf((char*)data,"%d;%d;%d;%d;%d;%d;%d;%d;%d;",Model_Number,value[0],value[1],value[2],value[3],value[4],value[5],value[6],value[7]);
						Record_ModifyData(12,1,Record_Number,data);
					}
					else if(Down12_4==1)
					{
						Down12_4=0;
						Record_DelData(12,1,(uint16)Record_Number);
					}
					else
					{
						for(i=3;i<strlen((const char*)msg);i++)
						{
							if(msg[i+1]!=0x3b)
							{
								if(msg[i+2]!=0x3b)
								{
									SetTextInt32(5,j[k],(msg[i]-48)*100+(msg[i+1]-48)*10+msg[i+2]-48,1,3);
									i+=3;k++;
								}
								else
								{
									SetTextInt32(5,j[k],(msg[i]-48)*10+msg[i+1]-48,1,3);
									i+=2;k++;
								}
							}
							else
							{
								
								SetTextInt32(5,j[k],msg[i]-48,1,3);
								i++;k++;
							}
						}
					}
					Record_Flag=1;
				}
			}
			if(Record_Number==0)
			{
				if(Record_Flag!=1)
				{
					if(Down12_4!=1)
					{
						sprintf((char*)data,"%d;%d;%d;%d;%d;%d;%d;%d;%d;",Model_Number,value[0],value[1],value[2],value[3],value[4],value[5],value[6],value[7]);
						Record_Add(12,1,data);
					}
					else
					{
						Down12_4=0;
					}
				}
				else
					Record_Flag=0;
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
    //控制背光亮度
    if(screen_id == 6)
    {
        if(control_id==1 || control_id==2)
        {
            GetControlValue(6,4);                                                                
        } 
    }
    if(screen_id == 5 && control_id==1)
    {
			if(state==0)
			{
				GetControlValue(5,26);
				Down5_1=1;
			}
    }
		if(screen_id == 5 && control_id==5)
    {
			if(state==0)
			{
				GetControlValue(5,26);
				Down5_1=1;
			}
    }
		if(screen_id == 6 && control_id==7)
    {
			if(state==0)
			{
				Record_Clear(12,1);
			}
    }
		if(screen_id == 1 && control_id==4)
		{
			if(state==0)
			{
				GetControlValue(5,26);
			}
		}
		if(screen_id == 12 && control_id==4)
		{
			if(state==1)
			{
				GetControlValue(12,3);
				Down12_4=1;
			}
		}
		if(screen_id == 0 && control_id==6)
		{
			if(state==0)
			{
     			if(PassWord_OK==1&&UserName_OK==1)
					{
						SetScreen(1);
						SetTextValue(0,3,(uint8*)"");
					}
					else if(UserName_OK==0)
						SetScreen(13);
					else
						SetScreen(14);
					PassWord_OK=0;
					UserName_OK=0;
			}
		}
		if(screen_id == 15 && control_id==4)
		{
			if(state==0)
			{
					if(OldPassWord==0||ResetPassWord==0)
					{
						SetScreen(17);
						SetTextValue(15,1,(uint8*)"");
					}
					else
					{
						strcpy((char*)password,(const char*)SetPassWord);
						WriteUserFlash(0,8,password);
						SetScreen(16);
						SetTextValue(15,1,(uint8*)"");
						SetTextValue(15,2,(uint8*)"");
						SetTextValue(15,3,(uint8*)"");
					}
					OldPassWord=0;
					ResetPassWord=0;
			}
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
		uchar *err=(uchar*)"数据错误";
		uchar *truedata=(uchar*)"数据合格";
		int i;
    if(screen_id==5)                                                                 
    {
			switch(control_id)
			{
				case 2:
					sscanf((const char*)str,"%d",&value[0]);
					if(current_screen_id==4)
					{
						SetTextInt32(4,10,value[0],1,3);
					}
					if(current_screen_id==7)
					{
						SetTextInt32(7,4,value[0],1,3);
					}
					break;
				case 3:
					sscanf((const char*)str,"%d",&value[1]);
					if(current_screen_id==4)
					{
						SetTextInt32(4,6,110,1,3);
						SetTextInt32(4,11,value[1],1,3);
						if(value[0]>110||value[1]<110)
						{
							SetTextValue(4,2,err);
							SetControlForeColor(4,6,60);
						}
						else
						{
							SetTextValue(4,2,truedata);
							SetControlForeColor(4,6,0);
						}
					}
					if(current_screen_id==7)
					{
						SetTextInt32(7,3,110,1,3);
						SetTextInt32(7,5,value[1],1,3);
						if(value[0]>110||value[1]<110)
						{
							SetTextValue(7,1,err);
							SetControlForeColor(7,3,60);
						}
						else
						{
							SetTextValue(7,1,truedata);
							SetControlForeColor(7,3,0);
						}
					}
					break;
				case 20:
					sscanf((const char*)str,"%d",&value[2]);
					if(current_screen_id==4)
					{
						SetTextInt32(4,14,value[2],1,3);
					}
					if(current_screen_id==8)
					{
						SetTextInt32(8,4,value[2],1,3);
					}
					break;
				case 23:
					sscanf((const char*)str,"%d",&value[3]);
					if(current_screen_id==4)
					{
						SetTextInt32(4,7,30,1,3);
						SetTextInt32(4,15,value[3],1,3);
						if(value[2]>30||value[3]<30)
						{
							SetTextValue(4,4,err);
							SetControlForeColor(4,7,60);
						}
						else
						{
							SetTextValue(4,4,truedata);
							SetControlForeColor(4,7,0);
						}
					}
					if(current_screen_id==8)
					{
						SetTextInt32(8,3,30,1,3);
						SetTextInt32(8,5,value[3],1,3);
						if(value[2]>30||value[3]<30)
						{
							SetTextValue(8,1,err);
							SetControlForeColor(8,3,60);
						}
						else
						{
							SetTextValue(8,1,truedata);
							SetControlForeColor(8,3,0);
						}
					}
					break;
				case 21:
					sscanf((const char*)str,"%d",&value[4]);
					if(current_screen_id==4)
					{
						SetTextInt32(4,16,value[4],1,3);
					}
					if(current_screen_id==9)
					{
						SetTextInt32(9,4,value[4],1,3);
					}
					break;
				case 24:
					sscanf((const char*)str,"%d",&value[5]);
					if(current_screen_id==4)
					{
						SetTextInt32(4,9,40,1,3);
						SetTextInt32(4,17,value[5],1,3);
						if(value[4]>40||value[5]<40)
						{
							SetTextValue(4,5,err);
							SetControlForeColor(4,9,60);
						}
						else
						{
							SetTextValue(4,5,truedata);
							SetControlForeColor(4,9,0);
						}
					}
					if(current_screen_id==9)
					{
						SetTextInt32(9,3,40,1,3);
						SetTextInt32(9,5,value[5],1,3);
						if(value[4]>40||value[5]<30)
						{
							SetTextValue(9,1,err);
							SetControlForeColor(9,3,60);
						}
						else
						{
							SetTextValue(9,1,truedata);
							SetControlForeColor(9,3,0);
						}
					}
					break;
				case 22:
					sscanf((const char*)str,"%d",&value[6]);
					if(current_screen_id==4)
					{
						SetTextInt32(4,12,value[6],1,3);
					}
					if(current_screen_id==10)
					{
						SetTextInt32(10,4,value[6],1,3);
					}
					break;
				case 25:
					sscanf((const char*)str,"%d",&value[7]);
					if(current_screen_id==4)
					{
						SetTextInt32(4,8,50,1,3);
						SetTextInt32(4,13,value[7],1,3);
						if(value[6]>50||value[7]<50)
						{
							SetTextValue(4,3,err);
							SetControlForeColor(4,8,60);
						}
						else
						{
							SetTextValue(4,3,truedata);
							SetControlForeColor(4,8,0);
						}
					}
					if(current_screen_id==10)
					{
						SetTextInt32(10,3,50,1,3);
						SetTextInt32(10,5,value[7],1,3);
						if(value[6]>50||value[7]<50)
						{
							SetTextValue(10,1,err);
							SetControlForeColor(10,3,60);
						}
						else
						{
							SetTextValue(10,1,truedata);
							SetControlForeColor(10,3,0);
						}
					}
					break;
				case 26:
					sscanf((const char*)str,"%d",&Model_Number);
					GetControlValue(5,2);									//获取压力最小值
					GetControlValue(5,3);									//获取压力最大值
					GetControlValue(5,20);									//获取直径最小值
					GetControlValue(5,23);									//获取直径最大值
					GetControlValue(5,21);									//获取电导率最大值
					GetControlValue(5,24);									//获取电导率最大值
					GetControlValue(5,22);									//获取延展率最大值
					GetControlValue(5,25);									//获取延展率最大值
					if(current_screen_id==5)
					{
						Record_GetCount(12,1);
					}
					break;
			}
    }
		if(screen_id==6)
		{
			if(control_id==4)
			{
				i=(int)*str;
				SetPowerLevel(level[i-1]);
			}
		}
		if(screen_id==12)
		{
			if(control_id==3)
			{
				if(Down12_4==1)
				{
					sscanf((const char*)str,"%d",&Model_Number);
					Record_GetCount(12,1);
				}
			}
		}
		if(screen_id==0)
		{	
			if(control_id==3)
			{
					ReadUserFlash(0,8);
					if(!strcmp((const char*)str,(const char*)password))
						PassWord_OK=1;
			}
			if(control_id==4)
			{
					if(!strcmp((const char*)str,(const char*)username))
						UserName_OK=1;
			}
		}
		if(screen_id==15)
		{
			if(control_id==1)
			{
					if(strcmp((const char*)str,(const char*)password)==0)
						OldPassWord=1;
					else
						OldPassWord=0;
			}
			if(control_id==2)
			{			
					if(strlen((const char*)str)<=8)
					{
						strcpy((char*)SetPassWord,(const char*)str);
					}
					else
						SetTextValue(15,6,(u8*)"密码不能超过8位");
			}
			if(control_id==3)
			{
					if(strcmp((char*)SetPassWord,(const char*)str)==0)
						ResetPassWord=1;
					else
						ResetPassWord=0;
			}
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
    if(screen_id == 5)
    {
        Progress_Value = value;                                  
        SetTextInt32(5,2,Progress_Value,0,1);                                        //设置文本框的值     
    }    
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
		int i=0;
		u8 j[8]="12345678";
    if(status==1)
		{
			for(;i<8;i++)
			{
				if(_data[0]!=0x00)
					password[i]=_data[i];
				else
					password[i]=j[i];
			}
		}
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

}
