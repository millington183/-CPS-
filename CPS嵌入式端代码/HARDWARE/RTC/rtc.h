#ifndef __RTC_H
#define __RTC_H	 
#include "sys.h" 
#include "stm32f4xx_conf.h"
#include "PIONEER_Config.h"

	
	
/*************************************************************************************/
//  日期时间数据结构定义, 以下定义绝对不能修改
/*************************************************************************************/
typedef struct
{
	INT8U  year;
	INT8U  month;
	INT8U  day;
	INT8U  hour;
	INT8U  minute;
	INT8U  second;
	INT8U  week;
   INT8U  flag;   // 新增标志位
}RTC_TIME;
	
	
	
u8 RTCInit(void);						//RTC初始化
//ErrorStatus RTC_Set_Time(u8 hour,u8 min,u8 sec,u8 ampm);			//RTC时间设置
//ErrorStatus RTC_Set_Date(u8 year,u8 month,u8 date,u8 week); 		//RTC日期设置
void RTC_Set_Alarm(u16 RTC_Alarm,u8 week,u8 hour,u8 min,u8 sec);		//设置闹钟时间(按星期闹铃,24小时制)
void RTC_Set_WakeUp(u32 wksel,u16 cnt);					//周期性唤醒定时器设置

#endif

















