#ifndef __EXTI_H
#define __EXTI_H	 
#include "sys.h"  	
#include "const.h"


// EXTI_Init() 初始化参数数据结构
typedef struct
{   
    INT8U  id;             // 中断id选择,EXTI0_ID~EXTI15_ID, 
    INT8U  Mode;           // 中断模式定义: EXTI_Trigger_Rising（上升沿触发）, EXTI_Trigger_Falling（下降沿触发）, EXTI_Trigger_Rising_Falling （任意电平触发）
    INT8U  Port;            // 选择IO端口: A,B,C,D,E,F,G,H,I;
}EXTI_PARA;


// IO中断0 ~ 15索引
#define EXTI0_ID  EXTI_PinSource0       
#define EXTI1_ID  EXTI_PinSource1
#define EXTI2_ID  EXTI_PinSource2
#define EXTI3_ID  EXTI_PinSource3
#define EXTI4_ID  EXTI_PinSource4
#define EXTI5_ID  EXTI_PinSource5
#define EXTI6_ID  EXTI_PinSource6
#define EXTI7_ID  EXTI_PinSource7
#define EXTI8_ID  EXTI_PinSource8
#define EXTI9_ID  EXTI_PinSource9
#define EXTI10_ID EXTI_PinSource10
#define EXTI11_ID EXTI_PinSource11
#define EXTI12_ID EXTI_PinSource12
#define EXTI13_ID EXTI_PinSource13
#define EXTI14_ID EXTI_PinSource14
#define EXTI15_ID EXTI_PinSource15

//端口组
#define A         EXTI_PortSourceGPIOA
#define B         EXTI_PortSourceGPIOB
#define C         EXTI_PortSourceGPIOC
#define D         EXTI_PortSourceGPIOD
#define E         EXTI_PortSourceGPIOE
#define F         EXTI_PortSourceGPIOF
#define G         EXTI_PortSourceGPIOG
#define H         EXTI_PortSourceGPIOH
#define I         EXTI_PortSourceGPIOI
#define PORT_NONE       0xff







void EXTIX_Init(EXTI_PARA *pPara);	//外部中断初始化	



#endif


