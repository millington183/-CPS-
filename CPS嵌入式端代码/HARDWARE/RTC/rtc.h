#ifndef __RTC_H
#define __RTC_H	 
#include "sys.h" 
#include "stm32f4xx_conf.h"
#include "PIONEER_Config.h"

	
	
/*************************************************************************************/
//  ����ʱ�����ݽṹ����, ���¶�����Բ����޸�
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
   INT8U  flag;   // ������־λ
}RTC_TIME;
	
	
	
u8 RTCInit(void);						//RTC��ʼ��
//ErrorStatus RTC_Set_Time(u8 hour,u8 min,u8 sec,u8 ampm);			//RTCʱ������
//ErrorStatus RTC_Set_Date(u8 year,u8 month,u8 date,u8 week); 		//RTC��������
void RTC_Set_Alarm(u16 RTC_Alarm,u8 week,u8 hour,u8 min,u8 sec);		//��������ʱ��(����������,24Сʱ��)
void RTC_Set_WakeUp(u32 wksel,u16 cnt);					//�����Ի��Ѷ�ʱ������

#endif

















