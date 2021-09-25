#include "Exti.h"


void EXTIX_Init(EXTI_PARA *pPara)
{
	
	
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//使能SYSCFG时钟
	
 
	SYSCFG_EXTILineConfig(pPara->Port, pPara->id);//连接到中断线
	
		
	switch(pPara->id)
	{
		case EXTI0_ID:
			  /* 配置EXTI_Line0 */
			EXTI_InitStructure.EXTI_Line = EXTI_Line0;//LINE0
			EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
			EXTI_InitStructure.EXTI_Trigger = (EXTITrigger_TypeDef)pPara->Mode; //设置触发方式
			EXTI_InitStructure.EXTI_LineCmd = ENABLE;//使能LINE
			EXTI_Init(&EXTI_InitStructure);//配置
					 
			NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;//外部中断0
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//抢占优先级
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;//子优先级
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
			NVIC_Init(&NVIC_InitStructure);//配置
		break;
		
		case EXTI1_ID:
			  /* 配置EXTI_Line1 */
			EXTI_InitStructure.EXTI_Line = EXTI_Line1;//LINE1
			EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
			EXTI_InitStructure.EXTI_Trigger = (EXTITrigger_TypeDef)pPara->Mode; //设置触发方式
			EXTI_InitStructure.EXTI_LineCmd = ENABLE;//使能LINE
			EXTI_Init(&EXTI_InitStructure);//配置
			
		 
			NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;//外部中断1
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//抢占优先级
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;//子优先级
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
			NVIC_Init(&NVIC_InitStructure);//配置
		break;
			
		case EXTI2_ID:
			  /* 配置EXTI_Line2 */
			EXTI_InitStructure.EXTI_Line = EXTI_Line2;//LINE2
			EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
			EXTI_InitStructure.EXTI_Trigger = (EXTITrigger_TypeDef)pPara->Mode; //设置触发方式
			EXTI_InitStructure.EXTI_LineCmd = ENABLE;//使能LINE
			EXTI_Init(&EXTI_InitStructure);//配置
			
		 
			NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;//外部中断2
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//抢占优先级
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;//子优先级
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
			NVIC_Init(&NVIC_InitStructure);//配置
		break;
			
		case EXTI3_ID:
			  /* 配置EXTI_Line3 */
			EXTI_InitStructure.EXTI_Line = EXTI_Line3;//LIN3
			EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
			EXTI_InitStructure.EXTI_Trigger = (EXTITrigger_TypeDef)pPara->Mode; //设置触发方式
			EXTI_InitStructure.EXTI_LineCmd = ENABLE;//使能LINE3
			EXTI_Init(&EXTI_InitStructure);//配置
			
		 
			NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;//外部中断3
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//抢占优先级
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;//子优先级
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
			NVIC_Init(&NVIC_InitStructure);//配置
		break;
		
		case EXTI4_ID:
			  /* 配置EXTI_Line0 */
			EXTI_InitStructure.EXTI_Line = EXTI_Line4;//LINE4
			EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
			EXTI_InitStructure.EXTI_Trigger = (EXTITrigger_TypeDef)pPara->Mode; //设置触发方式
			EXTI_InitStructure.EXTI_LineCmd = ENABLE;//使能LINE4
			EXTI_Init(&EXTI_InitStructure);//配置
			
		 
			NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;//外部中断4
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//抢占优先级
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;//子优先级
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
			NVIC_Init(&NVIC_InitStructure);//配置
		break;
		
		case EXTI5_ID:
			  /* 配置EXTI_Line5*/
			EXTI_InitStructure.EXTI_Line = EXTI_Line5;//LINE5
			EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
			EXTI_InitStructure.EXTI_Trigger = (EXTITrigger_TypeDef)pPara->Mode; //设置触发方式
			EXTI_InitStructure.EXTI_LineCmd = ENABLE;//使能LINE5
			EXTI_Init(&EXTI_InitStructure);//配置
			
		 
			NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//外部中断5~9
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//抢占优先级
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;//子优先级
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
			NVIC_Init(&NVIC_InitStructure);//配置
		break;
		
		case EXTI6_ID:
			  /* 配置EXTI_Line6 */
			EXTI_InitStructure.EXTI_Line = EXTI_Line6;//LINE6
			EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
			EXTI_InitStructure.EXTI_Trigger = (EXTITrigger_TypeDef)pPara->Mode; //设置触发方式
			EXTI_InitStructure.EXTI_LineCmd = ENABLE;//使能LINE6
			EXTI_Init(&EXTI_InitStructure);//配置
			
		 
			NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//外部中断5~9
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//抢占优先级
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;//子优先级
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
			NVIC_Init(&NVIC_InitStructure);//配置
		break;
		
		case EXTI7_ID:
			  /* 配置EXTI_Line7 */
			EXTI_InitStructure.EXTI_Line = EXTI_Line7;//LINE7
			EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
			EXTI_InitStructure.EXTI_Trigger = (EXTITrigger_TypeDef)pPara->Mode; //设置触发方式
			EXTI_InitStructure.EXTI_LineCmd = ENABLE;//使能LINE7
			EXTI_Init(&EXTI_InitStructure);//配置
			
		 
			NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//外部中断5~9
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//抢占优先级
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;//子优先级
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
			NVIC_Init(&NVIC_InitStructure);//配置
		break;
		
		case EXTI8_ID:
			  /* 配置EXTI_Line8 */
			EXTI_InitStructure.EXTI_Line = EXTI_Line8;//LINE8
			EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
			EXTI_InitStructure.EXTI_Trigger = (EXTITrigger_TypeDef)pPara->Mode; //设置触发方式
			EXTI_InitStructure.EXTI_LineCmd = ENABLE;//使能LINE8
			EXTI_Init(&EXTI_InitStructure);//配置
			
		 
			NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//外部中断5~9
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//抢占优先级
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;//子优先级
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
			NVIC_Init(&NVIC_InitStructure);//配置
		break;
		
		case EXTI9_ID:
			  /* 配置EXTI_Line9 */
			EXTI_InitStructure.EXTI_Line = EXTI_Line9;//LINE9
			EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
			EXTI_InitStructure.EXTI_Trigger = (EXTITrigger_TypeDef)pPara->Mode; //设置触发方式
			EXTI_InitStructure.EXTI_LineCmd = ENABLE;//使能LINE9
			EXTI_Init(&EXTI_InitStructure);//配置
			
		 
			NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//外部中断5~9
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//抢占优先级
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;//子优先级
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
			NVIC_Init(&NVIC_InitStructure);//配置
		break;
		
		case EXTI10_ID:
			  /* 配置EXTI_Lin10 */
			EXTI_InitStructure.EXTI_Line = EXTI_Line10;//LINE10
			EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
			EXTI_InitStructure.EXTI_Trigger = (EXTITrigger_TypeDef)pPara->Mode; //设置触发方式
			EXTI_InitStructure.EXTI_LineCmd = ENABLE;//使能LINE10
			EXTI_Init(&EXTI_InitStructure);//配置
			
		 
			NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//外部中断15~10
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//抢占优先级
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//子优先级
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
			NVIC_Init(&NVIC_InitStructure);//配置
		break;
		
		case EXTI11_ID:
			  /* 配置EXTI_Lin11 */
			EXTI_InitStructure.EXTI_Line = EXTI_Line11;//LINE11
			EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
			EXTI_InitStructure.EXTI_Trigger = (EXTITrigger_TypeDef)pPara->Mode; //设置触发方式
			EXTI_InitStructure.EXTI_LineCmd = ENABLE;//使能LINE11
			EXTI_Init(&EXTI_InitStructure);//配置
			
		 
			NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//外部中断15~10
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//抢占优先级
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//子优先级
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
			NVIC_Init(&NVIC_InitStructure);//配置
		break;
		
		case EXTI12_ID:
			  /* 配置EXTI_Lin12 */
			EXTI_InitStructure.EXTI_Line = EXTI_Line12;//LINE12
			EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
			EXTI_InitStructure.EXTI_Trigger = (EXTITrigger_TypeDef)pPara->Mode; //设置触发方式
			EXTI_InitStructure.EXTI_LineCmd = ENABLE;//使能LINE2
			EXTI_Init(&EXTI_InitStructure);//配置
			
		 
			NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//外部中断15~10
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//抢占优先级
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//子优先级
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
			NVIC_Init(&NVIC_InitStructure);//配置
		break;
		
		case EXTI13_ID:
			  /* 配置EXTI_Lin13 */
			EXTI_InitStructure.EXTI_Line = EXTI_Line13;//LINE13
			EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
			EXTI_InitStructure.EXTI_Trigger = (EXTITrigger_TypeDef)pPara->Mode; //设置触发方式
			EXTI_InitStructure.EXTI_LineCmd = ENABLE;//使能LINE13
			EXTI_Init(&EXTI_InitStructure);//配置
			
		 
			NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//外部中断15~10
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//抢占优先级
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//子优先级
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
			NVIC_Init(&NVIC_InitStructure);//配置
		break;
		
		case EXTI14_ID:
			  /* 配置EXTI_Lin14 */
			EXTI_InitStructure.EXTI_Line = EXTI_Line14;//LINE14
			EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
			EXTI_InitStructure.EXTI_Trigger = (EXTITrigger_TypeDef)pPara->Mode; //设置触发方式
			EXTI_InitStructure.EXTI_LineCmd = ENABLE;//使能LINE14
			EXTI_Init(&EXTI_InitStructure);//配置
			
		 
			NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//外部中断15~10
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//抢占优先级
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//子优先级
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
			NVIC_Init(&NVIC_InitStructure);//配置
		break;
		
		case EXTI15_ID:
			  /* 配置EXTI_Lin15 */
			EXTI_InitStructure.EXTI_Line = EXTI_Line15;//LINE15
			EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
			EXTI_InitStructure.EXTI_Trigger = (EXTITrigger_TypeDef)pPara->Mode; //设置触发方式
			EXTI_InitStructure.EXTI_LineCmd = ENABLE;//使能LINE15
			EXTI_Init(&EXTI_InitStructure);//配置
			
		 
			NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//外部中断15~10
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//抢占优先级
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//子优先级
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
			NVIC_Init(&NVIC_InitStructure);//配置
		break;
		
		
		default: ;
			
	}
	
	   
}
