#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//����������������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 

/*����ķ�ʽ��ͨ��ֱ�Ӳ����⺯����ʽ��ȡIO*/

/*���淽ʽ��ͨ��λ��������ʽ��ȡIO*/

#define KEY0 		PDin(3)   		//PD3
#define KEY1 		PDin(4)				//PD4 
#define KEY2 		PDin(5)				//PD5
#define KEY3    PDin(6)				//PD6
#define KEY4    PDin(7)				//PD7
#define KEY5    PBin(14)			//PB14
#define KEY6		PBin(15)			//PB15
#define KEY7		PEin(0)				//PE0
#define KEY8		PEin(1)				//PE1
#define KEY9		PEin(2)				//PE2


#define KEY0_PRES 	1
#define KEY1_PRES		2
#define KEY2_PRES		3
#define KEY3_PRES   4
#define KEY4_PRES   5
#define KEY5_PRES   6
#define KEY6_PRES   7
#define KEY7_PRES   8
#define KEY8_PRES   9
#define KEY9_PRES   10



void KEY_Init(void);	//IO��ʼ��
u8 KEY_Scan(u8);  		//����ɨ�躯��	

#endif
