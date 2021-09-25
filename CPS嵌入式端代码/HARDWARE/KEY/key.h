#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//按键输入驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/3
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 

/*下面的方式是通过直接操作库函数方式读取IO*/

/*下面方式是通过位带操作方式读取IO*/

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



void KEY_Init(void);	//IO初始化
u8 KEY_Scan(u8);  		//按键扫描函数	

#endif
