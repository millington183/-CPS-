#include "key.h"
#include "delay.h" 
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

//按键初始化函数
void KEY_Init(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStructure;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOE,ENABLE);//使能GPIOD,B,E时钟
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7; //KEY0 KEY1 KEY2 KEY3 KEY4对应引脚 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//下拉
  GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化GPIOD3,4,5,6,7
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_14|GPIO_Pin_15;//KEY5 KEY6对应引脚
	GPIO_Init(GPIOB,&GPIO_InitStructure);//初始化GPIOB14,15
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;//KEY7 KEY8 KEY9对应引脚
	GPIO_Init(GPIOE,&GPIO_InitStructure);//初始化GPIOE0,1,2
	
} 
//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//0，没有任何按键按下
// 1，KEY0按下
// 2，KEY1按下
// 3，KEY2按下 
// 4，KEY3按下 
// 5，KEY4按下 
// 6，KEY5按下 
// 7，KEY6按下
// 8，KEY7按下
// 9，KEY8按下 
//10，KEY9按下 
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&(KEY0==1||KEY1==1||KEY2==1|KEY3==1|KEY4==1
	|KEY5==1|KEY6==1|KEY7==1|KEY8==1|KEY9==1))
	
	{
		delay_ms(10);//去抖动 
		key_up=0;
		if(KEY0==1)return KEY0_PRES;
		else if(KEY1==1)return KEY1_PRES;
		else if(KEY2==1)return KEY2_PRES;
		else if(KEY3==1)return KEY3_PRES;
		else if(KEY4==1)return KEY4_PRES;
		else if(KEY5==1)return KEY5_PRES;
		else if(KEY6==1)return KEY6_PRES;
		else if(KEY7==1)return KEY7_PRES;
		else if(KEY8==1)return KEY8_PRES;
		else if(KEY9==1)return KEY9_PRES;
	}
	else if(KEY0==0&&KEY1==0&&KEY2==0&&KEY3==0
	&&KEY4==0&&KEY5==0&&KEY6==0&&KEY7==0&&KEY8==0&&KEY9==0)key_up=1; 	    
 	
	return 0;// 无按键按下
}




















