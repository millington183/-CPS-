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
* Date:    2019.12.11			
* Email:   
* 
* Description: 本文件负责整个系统中断处理函数;
* Others: none;
*
* Function List: 
*		
* History:
* 1. Author:			  wangzl  
*	   Version: 	 		0.02
*	   Date:         	2019.12.12
*    Modification: 	none
*
*************************************************************************************/

/************************************************************************************/
// 引用外部头文件
/************************************************************************************/

#include "sys.h"
#include "STM32F4_Head.h"
#include "PIONEER_Config.h"
#include "const.h"
#include "includes.h"					//ucos 使用	  
#include "UserVars.h"	
#include "OSVars.h"
#include "cmd_queue.h"
#include "hmi_user_uart.h"

/************************************************************************************/
/************************************************************************************
// 常量及全局变量定义
*************************************************************************************/



/***********************************************************************************
* Function: EXTI0_ISRHook, EXTI1_ISRHook, EXTI2_ISRHook, EXTI3_ISRHook;
*           EXTI4_ISRHook, EXTI5_ISRHook, EXTI6_ISRHook, EXTI7_ISRHook,
*           EXTI8_ISRHook, EXTI9_ISRHook, EXTI10_ISRHook, EXTI11_ISRHook,
*           EXTI12_ISRHook, EXTI13_ISRHook, EXTI14_ISRHook, EXTI15_ISRHook,
*
* Description: 以下函数是外部IO 16个中断函数;
*
*           
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/

//外部中断0服务程序
void EXTI0_IRQHandler(void)
{
	#if UCOS_II_EN  //使用UCOS操作系统
		OSIntEnter();    
	#endif

	delay_ms(10);	//消抖
	if(EXTI_GetITStatus(EXTI_Line0) != RESET)	 
	{
		// 以下编写自己的中断处理程序
		if(KEY7 == 1)
		{
			printf("PE0按下\r\n");
			sprintf((char *)GainNumber.ResultData,"%d",8);	//设置编号为8
			ProcessingFlag=1;																//产品合格标志为1
			SetTextValue(1,9,ProductResult8);								//将结果在串口屏上	
			OSSemPost(ResultSem);
		}
		
    #if (DEBUG_APP_EN > 0)
			printf("EXTI0产生中断\r\n");
    #endif
		
	}		 
	 EXTI_ClearITPendingBit(EXTI_Line0); //清除LINE0上的中断标志位 
	#if UCOS_II_EN  
		OSIntExit();    	//退出中断
	#endif
}	
//外部中断1服务程序
void EXTI1_IRQHandler(void)
{
	#if UCOS_II_EN  //使用UCOS操作系统
		OSIntEnter();    
	#endif

	delay_ms(10);	//消抖
	if(EXTI_GetITStatus(EXTI_Line1) != RESET)	 
	{
		// 以下编写自己的中断处理程序
		if(KEY8 == 1)
		{
			printf("PE1按下\r\n");
		}
		
    #if (DEBUG_APP_EN > 0)
			printf("EXTI1产生中断\r\n");
    #endif
		
	}		 
	 EXTI_ClearITPendingBit(EXTI_Line1); //清除LINE0上的中断标志位 
	#if UCOS_II_EN  
		OSIntExit();    	//退出中断
	#endif
}	

//外部中断2服务程序
void EXTI2_IRQHandler(void)
{
	#if UCOS_II_EN  //使用UCOS操作系统
		OSIntEnter();    
	#endif
	delay_ms(10);	//消抖
	if(EXTI_GetITStatus(EXTI_Line2) != RESET)	 
	{
		// 以下编写自己的中断处理程序
		if(KEY9 == 1)
		{
			printf("PE2按下\r\n");
		}
		
    #if (DEBUG_APP_EN > 0)
			printf("EXTI2产生中断\r\n");
    #endif
		
	}		 
	 EXTI_ClearITPendingBit(EXTI_Line2);//清除LINE2上的中断标志位 
	#if UCOS_II_EN  
		OSIntExit();    	//退出中断
	#endif
}
//外部中断3服务程序
void EXTI3_IRQHandler(void)
{
	#if UCOS_II_EN  //使用UCOS操作系统
		OSIntEnter();    
	#endif
	delay_ms(10);	//消抖
	if(EXTI_GetITStatus(EXTI_Line3) != RESET)	 
	{
		// 以下编写自己的中断处理程序
		if(KEY0==1)
		{
			printf("PD3按下");
			sprintf((char *)GainNumber.ResultData,"%d",1);	//设置编号为1
			SetTextValue(1,9,ProductResult1);								//将结果在串口屏上	
			ProcessingFlag=1;																//产品合格标志为1
			OSSemPost(ResultSem);														//释放产品结果的互斥信号量
			ProductResultFlag=1;														//产品结果添加记录的标志
		}
		
    #if (DEBUG_APP_EN > 0)
			printf("EXTI3产生中断\r\n");
    #endif
		
	}		 
	 EXTI_ClearITPendingBit(EXTI_Line3);  //清除LINE3上的中断标志位  
	#if UCOS_II_EN  
		OSIntExit();    	//退出中断
	#endif
}
//外部中断4服务程序
void EXTI4_IRQHandler(void)
{
	#if UCOS_II_EN  //使用UCOS操作系统
		OSIntEnter();    
	#endif
	delay_ms(10);	//消抖
	if(EXTI_GetITStatus(EXTI_Line4) != RESET)	 
	{
		// 以下编写自己的中断处理程序
		if(KEY1 == 1)
		{
			printf("PD4按下\r\n");
			sprintf((char *)GainNumber.ResultData,"%d",2);	//设置编号为2
			SetTextValue(1,9,ProductResult2);								//将结果在串口屏上
			ProcessingFlag=1;																//产品合格标志为1			
			OSSemPost(ResultSem);														//释放产品结果的互斥信号量
			ProductResultFlag=1;														//产品结果添加记录的标志
		}
		
    #if (DEBUG_APP_EN > 0)
			printf("EXTI4产生中断\r\n");
    #endif
		
	}		 
	 EXTI_ClearITPendingBit(EXTI_Line4);//清除LINE4上的中断标志位  
	#if UCOS_II_EN  
		OSIntExit();    	//退出中断
	#endif
}
//外部中断5~9服务函数
void EXTI9_5_IRQHandler(void)
{
	#if UCOS_II_EN  //使用UCOS操作系统
		OSIntEnter();    
	#endif

	
	delay_ms(10);   //消抖
	
	//外部中断5函数
	if(EXTI_GetITStatus(EXTI_Line5) != RESET)	 
	{
		// 以下编写自己的中断处理程序
			if(KEY2==1)
			{
				printf("PD5按下");
				sprintf((char *)GainNumber.ResultData,"%d",3);	//设置编号为3
				SetTextValue(1,9,ProductResult3);								//将结果在串口屏上	
				ProcessingFlag=1;																//产品合格标志为1
				OSSemPost(ResultSem);														//释放产品结果的互斥信号量
				ProductResultFlag=1;														//产品结果添加记录的标志
			}
		
		
    #if (DEBUG_APP_EN > 0)
			printf("EXTI5产生中断\r\n");
    #endif
		EXTI_ClearITPendingBit(EXTI_Line5);//清除LINE5上的中断标志位
	}	
	//外部中断6函数
	if(EXTI_GetITStatus(EXTI_Line6) != RESET)	 
	{
		// 以下编写自己的中断处理程序
		if(KEY3 == 1)
		{
			printf("PD6按下\r\n");
			sprintf((char *)GainNumber.ResultData,"%d",4);	//设置编号为4
			SetTextValue(1,9,ProductResult4);								//将结果在串口屏上	
			ProcessingFlag=1;																//产品合格标志为1
			OSSemPost(ResultSem);														//释放产品结果的互斥信号量
			ProductResultFlag=1;														//产品结果添加记录的标志
		}
		
		
    #if (DEBUG_APP_EN > 0)
			printf("EXTI6产生中断\r\n");
    #endif
		EXTI_ClearITPendingBit(EXTI_Line6);//清除LINE6上的中断标志位
	}	
	//外部中断7函数
	if(EXTI_GetITStatus(EXTI_Line7) != RESET)	 
	{
		// 以下编写自己的中断处理程序
		if(KEY4 == 1)
		{
			printf("PD7按下\r\n");
			sprintf((char *)GainNumber.ResultData,"%d",5);	//设置编号为5
			SetTextValue(1,9,ProductResult5);								//将结果在串口屏上	
			ProcessingFlag=1;																//产品合格标志为1
			OSSemPost(ResultSem);														//释放产品结果的互斥信号量
			ProductResultFlag=1;														//产品结果添加记录的标志
		}
		
		
    #if (DEBUG_APP_EN > 0)
			printf("EXTI7产生中断\r\n");
    #endif
		EXTI_ClearITPendingBit(EXTI_Line7);//清除LINE5上的中断标志位
	}	
	//外部中断8函数
	if(EXTI_GetITStatus(EXTI_Line8) != RESET)	 
	{
		// 以下编写自己的中断处理程序

		
		
    #if (DEBUG_APP_EN > 0)
			printf("EXTI8产生中断\r\n");
    #endif
		EXTI_ClearITPendingBit(EXTI_Line8);//清除LINE8上的中断标志位
	}	
	//外部中断9函数
	if(EXTI_GetITStatus(EXTI_Line9) != RESET)	 
	{
		// 以下编写自己的中断处理程序

		
		
    #if (DEBUG_APP_EN > 0)
			printf("EXTI9产生中断\r\n");
    #endif
		EXTI_ClearITPendingBit(EXTI_Line9);//清除LINE9上的中断标志位
	}
	#if UCOS_II_EN  
		OSIntExit();    	//退出中断
	#endif	
}

//外部中断10~15服务函数
void EXTI15_10_IRQHandler(void)
{
	#if UCOS_II_EN  //使用UCOS操作系统
		OSIntEnter();    
	#endif

	
	delay_ms(10);   //消抖
	
	//外部中断10函数
	if(EXTI_GetITStatus(EXTI_Line10) != RESET)	 
	{
		// 以下编写自己的中断处理程序

		
		
    #if (DEBUG_APP_EN > 0)
			printf("EXTI10产生中断\r\n");
    #endif
		EXTI_ClearITPendingBit(EXTI_Line10);//清除LINE10上的中断标志位
	}	
	//外部中断11函数
	if(EXTI_GetITStatus(EXTI_Line11) != RESET)	 
	{
		// 以下编写自己的中断处理程序

		
		
    #if (DEBUG_APP_EN > 0)
			printf("EXTI11产生中断\r\n");
    #endif
		EXTI_ClearITPendingBit(EXTI_Line11);//清除LINE11上的中断标志位
	}	
	//外部中断12函数
	if(EXTI_GetITStatus(EXTI_Line12) != RESET)	 
	{
		// 以下编写自己的中断处理程序

		
		
    #if (DEBUG_APP_EN > 0)
			printf("EXTI12产生中断\r\n");
    #endif
		EXTI_ClearITPendingBit(EXTI_Line12);//清除LINE12上的中断标志位
	}	
	//外部中断13函数
	if(EXTI_GetITStatus(EXTI_Line13) != RESET)	 
	{
		// 以下编写自己的中断处理程序

		
		
    #if (DEBUG_APP_EN > 0)
			printf("EXTI13产生中断\r\n");
    #endif
		EXTI_ClearITPendingBit(EXTI_Line13);//清除LINE13上的中断标志位
	}	
	//外部中断14函数
	if(EXTI_GetITStatus(EXTI_Line14) != RESET)	 
	{
		// 以下编写自己的中断处理程序
		if(KEY5 == 1)
		{
			printf("PB14按下\r\n");
			sprintf((char *)GainNumber.ResultData,"%d",6);	//设置编号为6
			SetTextValue(1,9,ProductResult6);								//将结果在串口屏上	
			ProcessingFlag=1;																//产品合格标志为1
			OSSemPost(ResultSem);														//释放产品结果的互斥信号量
			ProductResultFlag=1;														//产品结果添加记录的标志
		}
		
		
    #if (DEBUG_APP_EN > 0)
			printf("EXTI14产生中断\r\n");
    #endif
		EXTI_ClearITPendingBit(EXTI_Line14);//清除LINE9上的中断标志位
	}	
		//外部中断15函数
	if(EXTI_GetITStatus(EXTI_Line15) != RESET)	 
	{
		// 以下编写自己的中断处理程序
		if(KEY6 == 1)
			{
				printf("PB15按下\r\n");
				sprintf((char *)GainNumber.ResultData,"%d",7);	//设置编号为7
				SetTextValue(1,9,ProductResult7);								//将结果在串口屏上	
				ProcessingFlag=1;																//产品合格标志为1
				OSSemPost(ResultSem);														//释放产品结果的互斥信号量
				ProductResultFlag=1;														//产品结果添加记录的标志
			}
		
		
    #if (DEBUG_APP_EN > 0)
			printf("EXTI15产生中断\r\n");
    #endif
		EXTI_ClearITPendingBit(EXTI_Line15);//清除LINE15上的中断标志位
	}	
	
	#if UCOS_II_EN  
		OSIntExit();    	//退出中断
	#endif
	
}

/***********************************************************************************
* Function: TIM2_IRQHandler, TIM3_IRQHandler, TIM4_IRQHandler,TIM5_IRQHandler, 
*			TIM6_IRQHandler, TIM7_IRQHandler
*
* Description: 本函数是TIM1、TIM8中断钩子函数;
*           
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/

//定时器2中断服务函数
void TIM2_IRQHandler(void)
{
	#if UCOS_II_EN  //使用UCOS操作系统
		OSIntEnter();    
	#endif
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET) //溢出中断
	{
		#if (UART1_EN>0 && UART1_RX_MODE==0) 
			UART1_RX_STA|=1<<15;	//标记接收完成
			TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  //清除TIM2更新中断标志    
			TIM_Cmd(TIM2, DISABLE);  //关闭TIM2
		#else
		// 以下编写自己的中断处理程序
			//GPIO_SetBits(GPIOE,GPIO_Pin_2);   //BEEP引脚拉高， 等同BEEP=1;
			//delay_ms(300); 
			//GPIO_ResetBits(GPIOE,GPIO_Pin_2); //BEEP引脚拉低， 等同BEEP=0;
			//delay_ms(300);                    //延时300ms

		
			TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  //清除TIM2更新中断标志 
		#endif
	}
	#if UCOS_II_EN  
		OSIntExit();    	//退出中断
	#endif
}

//定时器3中断服务函数
void TIM3_IRQHandler(void)
{
	#if UCOS_II_EN  //使用UCOS操作系统
		OSIntEnter();    
	#endif
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //溢出中断
	{
		#if (UART2_EN>0 && UART2_RX_MODE==0) 
			UART2_RX_STA|=1<<15;	//标记接收完成

			TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  //清除TIM3更新中断标志    
			TIM_Cmd(TIM3, DISABLE);  //关闭TIM3 
		#else
		// 以下编写自己的中断处理程序
		NBUpdateCnt++;
		if(NBUpdateCnt >= UPDATE_TIME_DATA*60)
		{
			TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  // 清除TIM3更新中断标志  
			TIM_Cmd(TIM3, DISABLE);  											// 关闭TIM3
			OSSemPost(NBUpdateSem);												// 发送计时结束完成信号了
		}
		
		
			TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  //清除TIM3更新中断标志 
		#endif
	}
	#if UCOS_II_EN  
		OSIntExit();    	//退出中断
	#endif
}

void TIM4_IRQHandler(void)
{
	#if UCOS_II_EN  //使用UCOS操作系统
		OSIntEnter();    
	#endif
	if(TIM_GetITStatus(TIM4,TIM_IT_Update)==SET) //溢出中断
	{
		#if (UART3_EN>0 && UART3_RX_MODE==0) 
			UART3_RX_STA|=1<<15;	//标记接收完成
			OSSemPost(UART3Sem);
			TIM_ClearITPendingBit(TIM4, TIM_IT_Update);  //清除TIM3更新中断标志    
			TIM_Cmd(TIM4, DISABLE);  //关闭TIM3 
		#else
		// 以下编写自己的中断处理程序
		NBUpdateCnt++;
		if(NBUpdateCnt >= UPDATE_TIME_DATA*60)
		{
			TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );  // 清除TIM3更新中断标志  
			TIM_Cmd(TIM4, DISABLE);  											// 关闭TIM3
			OSSemPost(NBUpdateSem);												// 发送计时结束完成信号了
		}
		
		
			TIM_ClearITPendingBit(TIM4, TIM_IT_Update);  //清除TIM3更新中断标志 
		#endif
	}
	#if UCOS_II_EN  
		OSIntExit();    	//退出中断
	#endif
}

/*
void TIM4_IRQHandler(void)
{
	#if UCOS_II_EN  //使用UCOS操作系统
	OSIntEnter();    
	#endif
	if((TIM4CH1_CAPTURE_STA&0X80)==0)//还未成功捕获	
	{	  
		if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
		 
		{	    
			if(TIM4CH1_CAPTURE_STA&0X40)//已经捕获到高电平了
			{
				if((TIM4CH1_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
				{
					TIM4CH1_CAPTURE_STA|=0X80;//标记成功捕获了一次
					TIM4CH1_CAPTURE_VAL=0XFFFF;
				}else TIM4CH1_CAPTURE_STA++;
			}	 
		}
		if(TIM_GetITStatus(TIM4, TIM_IT_CC1) != RESET)//捕获1发生捕获事件
		{	
			if(TIM4CH1_CAPTURE_STA&0X40)		//捕获到一个下降沿 		
			{	  			
				TIM4CH1_CAPTURE_STA|=0X80;		//标记成功捕获到一次上升沿
				TIM4CH1_CAPTURE_VAL=TIM_GetCapture1(TIM4);
		   	TIM_OC1PolarityConfig(TIM4,TIM_ICPolarity_Rising); //CC1P=0 设置为上升沿捕获
			}else  								//还未开始,第一次捕获上升沿
			{
				TIM4CH1_CAPTURE_STA=0;			//清空
				TIM4CH1_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM4,0);
			
				TIM4CH1_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
				TIM_OC1PolarityConfig(TIM4,TIM_ICPolarity_Falling);		//CC1P=1 设置为下降沿捕获
			}		    
		}
 	}
 
    TIM_ClearITPendingBit(TIM4, TIM_IT_CC1|TIM_IT_Update); //清除中断标志位		
	
	#if UCOS_II_EN  
		OSIntExit();    	//退出中断
	#endif	
}
*/


/*
//定时器4中断服务函数
void TIM4_IRQHandler(void)
{
	#if UCOS_II_EN  //使用UCOS操作系统
		OSIntEnter();    
	#endif
	if(TIM_GetITStatus(TIM4,TIM_IT_Update)==SET) //溢出中断
	{
		#if (UART3_EN>0 && UART3_RX_MODE==0) 
			UART3_RX_STA|=1<<15;	//标记接收完成
			TIM_ClearITPendingBit(TIM4, TIM_IT_Update);  //清除TIM4更新中断标志    
			TIM_Cmd(TIM4, DISABLE);  //关闭TIM4 
		#else
		// 以下编写自己的中断处理程序
			//GPIO_SetBits(GPIOE,GPIO_Pin_2);   //BEEP引脚拉高， 等同BEEP=1;
			//delay_ms(500); 
			//GPIO_ResetBits(GPIOE,GPIO_Pin_2); //BEEP引脚拉低， 等同BEEP=0;
			//delay_ms(500);  
		
		
			TIM_ClearITPendingBit(TIM4, TIM_IT_Update);  //清除TIM4更新中断标志 
		#endif
	}
	#if UCOS_II_EN  
		OSIntExit();    	//退出中断
	#endif
}
*/

//定时器5中断服务函数
void TIM5_IRQHandler(void)
{
	#if UCOS_II_EN  //使用UCOS操作系统
		OSIntEnter();    
	#endif
	if(TIM_GetITStatus(TIM5,TIM_IT_Update)==SET) //溢出中断
	{
		#if (UART5_EN>0 && UART5_RX_MODE==0) 
		if(0 == NBRvDelay)
		{
			UART5_RX_STA|=1<<15;	//标记接收完成
		  OSSemPost(NBUartRdy);														// 通过信号量通知NB接收任务收到了串口数据
		  //OSSemPost(RS485UartRdy);		
			//OSSemPost(WaterRdy);
			//OSSemPost(FurnaceRdy);
			//OSSemPost(ConduRdy);
			TIM_ClearITPendingBit(TIM5, TIM_IT_Update);  //清除TIM6更新中断标志    
			TIM_Cmd(TIM5, DISABLE);  //关闭TIM6
		}
		else if (NBRvDelay >= 10)
		{
			TIM_ClearITPendingBit(TIM5, TIM_IT_Update);  //清除TIM6更新中断标志
			NBRvDelay = 0;
		}
		else 
		{
			TIM_ClearITPendingBit(TIM5, TIM_IT_Update);  //清除TIM6更新中断标志
			NBRvDelay++;
		}
			
		#else
		// 以下编写自己的中断处理程序
		
		
		
			TIM_ClearITPendingBit(TIM5, TIM_IT_Update);  //清除TIM6更新中断标志 
		#endif
	}
	#if UCOS_II_EN  
		OSIntExit();    	//退出中断
	#endif
	
	/*#if UCOS_II_EN  //使用UCOS操作系统
		OSIntEnter();    
	#endif
	if(TIM_GetITStatus(TIM5,TIM_IT_Update)==SET) //溢出中断
	{
		#if (UART4_EN>0 && UART4_RX_MODE==0) 
			UART4_RX_STA|=1<<15;	//标记接收完成
	  	OSSemPost(ComSem);												// 发送计时结束完成信号了
			TIM_ClearITPendingBit(TIM5, TIM_IT_Update);  //清除TIM5更新中断标志    
			TIM_Cmd(TIM5, DISABLE);  //关闭TIM5 
		#else
		// 以下编写自己的中断处理程序
		 
		
		
		
			TIM_ClearITPendingBit(TIM5, TIM_IT_Update);  //清除TIM5更新中断标志 
		#endif
	}
	#if UCOS_II_EN  
		OSIntExit();    	//退出中断
	#endif*/
}






//定时器6中断服务函数
void TIM6_IRQHandler(void)
{
	#if UCOS_II_EN  //使用UCOS操作系统
		OSIntEnter();    
	#endif
	if(TIM_GetITStatus(TIM6,TIM_IT_Update)==SET) //溢出中断
	{
		#if (UART5_EN>0 && UART5_RX_MODE==0) 
		if(0 == NBRvDelay)
		{
			UART5_RX_STA|=1<<15;	//标记接收完成
		  OSSemPost(NBUartRdy);														// 通过信号量通知NB接收任务收到了串口数据
			TIM_ClearITPendingBit(TIM6, TIM_IT_Update);  //清除TIM6更新中断标志    
			TIM_Cmd(TIM6, DISABLE);  //关闭TIM6
		}
		else if (NBRvDelay >= 10)
		{
			TIM_ClearITPendingBit(TIM6, TIM_IT_Update);  //清除TIM6更新中断标志
			NBRvDelay = 0;
		}
		else 
		{
			TIM_ClearITPendingBit(TIM6, TIM_IT_Update);  //清除TIM6更新中断标志
			NBRvDelay++;
		}
			
		#else
		// 以下编写自己的中断处理程序
		
		
		
			TIM_ClearITPendingBit(TIM6, TIM_IT_Update);  //清除TIM6更新中断标志 
		#endif
	}
	#if UCOS_II_EN  
		OSIntExit();    	//退出中断
	#endif
}

//定时器7中断服务函数
void TIM7_IRQHandler(void)
{
	#if UCOS_II_EN  //使用UCOS操作系统
		OSIntEnter();    
	#endif
	if(TIM_GetITStatus(TIM7,TIM_IT_Update)==SET) //溢出中断
	{
		#if (UART6_EN>0 && UART6_RX_MODE==0) 
			UART6_RX_STA|=1<<15;	//标记接收完成
			TIM_ClearITPendingBit(TIM7, TIM_IT_Update);  //清除TIM7更新中断标志    
			TIM_Cmd(TIM7, DISABLE);  //关闭TIM7 
		#else
		// 以下编写自己的中断处理程序
	
			TIM_ClearITPendingBit(TIM7, TIM_IT_Update);  //清除TIM7更新中断标志 
			TIM_Cmd(TIM7, DISABLE);  //关闭TIM7
		
		#endif
	}
	#if UCOS_II_EN  
		OSIntExit();    	//退出中断
	#endif
	
}


/***********************************************************************************
* Function: RTC_Alarm_IRQHandler,RTC_WKUP_IRQHandler;
*
* Description: 以下函数是RTC闹钟和唤醒中断的钩子函数;
*           
* Input:
*
* Output: none;
*          		
* Return: none;
*
* Note:   此中断只有在STM32F10X模块上存在;
************************************************************************************/

//RTC闹钟中断服务函数
void RTC_Alarm_IRQHandler(void)
{    
	if(RTC_GetFlagStatus(RTC_FLAG_ALRAF)==SET)//ALARM A中断?
	{
		RTC_ClearFlag(RTC_FLAG_ALRAF);//清除中断标志
		// 以下编写自己的中断处理程序
		
		
		
		
		
		#if (DEBUG_APP_EN == 1)
			printf("RTC产生闹钟报警中断\r\n");  
		#endif
	}   
	EXTI_ClearITPendingBit(EXTI_Line17);	//清除中断线17的中断标志 											 
}

//RTC WAKE UP中断服务函数
void RTC_WKUP_IRQHandler(void)
{    
	if(RTC_GetFlagStatus(RTC_FLAG_WUTF)==SET)//WK_UP中断
	{ 
		RTC_ClearFlag(RTC_FLAG_WUTF);	//清除中断标志
		// 以下编写自己的中断处理程序
		
		
		
		
		
		#if (DEBUG_APP_EN == 1)
			printf("RTC产生唤醒中断\r\n");  
		#endif
		
		
		
	}   
	EXTI_ClearITPendingBit(EXTI_Line22);//清除中断线22的中断标志 								
}


/***********************************************************************************
* Function: USART1_IRQHandler,USART2_IRQHandler,USART3_IRQHandler,USART4_IRQHandler,
*           USART5_IRQHandler,USART6_IRQHandler;
*
* Description: 以下函数是Uart1,Uart2,Uart3,Uart4,Uart5,Uart6中断及接收数据的钩子函数;
*           
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   本函数只能根据串口状态UartSR编写接收数据程序, 发送数据由内部中断实现;
*         本函数编写了3种接收协议 可以在 PIONEER_Config.h文件中修改  UART1_RX_MODE
************************************************************************************/



void USART1_IRQHandler(void)                	//串口1中断服务程序
{
	u8 Res;
	#if UCOS_II_EN  //使用UCOS操作系统
		OSIntEnter();    
	#endif
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断
	{		
		Res =USART_ReceiveData(USART1);//(USART1->DR);	//读取接收到的数据
		#if (UART1_RX_MODE == 1)         //(接收到的数据必须是0x0d 0x0a结尾)
			if((UART1_RX_STA&0x8000)==0)//接收未完成
			{
				if(UART1_RX_STA&0x4000)//接收到了0x0d
				{
					if(Res!=0x0a)
						UART1_RX_STA=0;//接收错误,重新开始
					else 
						UART1_RX_STA|=0x8000;	//接收完成了 
				}
				else //还没收到0X0D
				{	
					if(Res==0x0d)
						UART1_RX_STA|=0x4000;
					else
					{
						UART1_RX_BUF[UART1_RX_STA&0X3FFF]=Res ;
						UART1_RX_STA++;
						if(UART1_RX_STA>(UART1_RXBUF_SIZE-1))
							UART1_RX_STA=0;//接收数据错误,重新开始接收	  
					}		 
				}
			}
			
		#elif (UART1_RX_MODE == 2)        //RS485接收模式
		
			if(UART1_RX_STA<UART1_RXBUF_SIZE)
			{
				UART1_RX_BUF[UART1_RX_STA]=Res;		//记录接收到的值
				UART1_RX_STA++;						//接收数据增加1 
			} 
			
			
		#else   //定时器中断接收
						//通过判断接收连续2个字符之间的时间差不大于100ms来决定是不是一次连续的数据.
						//如果2个字符接收间隔超过100ms,则认为不是1次连续数据.也就是超过100ms没有接收到
						//任何数据,则表示此次接收完毕.
						//接收到的数据状态
						//[15]:0,没有接收到数据;1,接收到了一批数据.
						//[14:0]:接收到的数据长度
		
			if((UART1_RX_STA&(1<<15))==0)//接收完的一批数据,还没有被处理,则不再接收其他数据
			{ 
				if(UART1_RX_STA<UART1_RXBUF_SIZE)		//还可以接收数据
				{
					TIM_SetCounter(TIM2,0);//计数器清空        				 
					if(UART1_RX_STA==0)
					{
						TIM_Cmd(TIM2, ENABLE);  //使能定时器2
					}
						 
					UART1_RX_BUF[UART1_RX_STA++]=Res;		//记录接收到的值	 
				}
				else 
				{
					UART1_RX_STA|=1<<15;					//强制标记接收完成
				} 
			}  	

		
		#endif
	} 
	
	#if UCOS_II_EN  
		OSIntExit();    	//退出中断
	#endif
} 


void USART2_IRQHandler(void)                	//串口2中断服务程序
{
	u8 Res;
#if UCOS_II_EN  //使用UCOS操作系统
	OSIntEnter();    
#endif
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //接收中断
	{		
		Res =USART_ReceiveData(USART2);//(USART2->DR);	//读取接收到的数据
		#if (UART2_RX_MODE == 1)          //(接收到的数据必须是0x0d 0x0a结尾)
			if((UART2_RX_STA&0x8000)==0)//接收未完成
			{
				if(UART2_RX_STA&0x4000)//接收到了0x0d
				{
					if(Res!=0x0a)
						UART2_RX_STA=0;//接收错误,重新开始
					else 
						UART2_RX_STA|=0x8000;	//接收完成了 
				}
				else //还没收到0X0D
				{	
					if(Res==0x0d)
						UART2_RX_STA|=0x4000;
					else
					{
						UART2_RX_BUF[UART2_RX_STA&0X3FFF]=Res ;
						UART2_RX_STA++;
						if(UART2_RX_STA>(UART2_RXBUF_SIZE-1))
							UART2_RX_STA=0;//接收数据错误,重新开始接收	  
					}		 
				}
			}
		/*if(UART2_RX_STA<64)
		{
			
			UART2_RX_BUF[UART2_RX_STA]=Res;		//记录接收到的值
			
			UART2_RX_STA++;						//接收数据增加1 
		}*/
			
		#elif (UART2_RX_MODE == 2)        //RS485接收模式
		
			if(UART2_RX_STA<UART2_RXBUF_SIZE)
			{
				UART2_RX_BUF[UART2_RX_STA]=Res;		//记录接收到的值
				UART2_RX_STA++;						//接收数据增加1 
			} 
			
		#else   //定时器中断接收
						//通过判断接收连续2个字符之间的时间差不大于100ms来决定是不是一次连续的数据.
						//如果2个字符接收间隔超过100ms,则认为不是1次连续数据.也就是超过100ms没有接收到
						//任何数据,则表示此次接收完毕.
						//接收到的数据状态
						//[15]:0,没有接收到数据;1,接收到了一批数据.
						//[14:0]:接收到的数据长度
		
			if((UART2_RX_STA&(1<<15))==0)//接收完的一批数据,还没有被处理,则不再接收其他数据
			{ 
				if(UART2_RX_STA<UART2_RXBUF_SIZE)		//还可以接收数据
				{
					TIM_SetCounter(TIM3,0);//计数器清空        				 
					if(UART2_RX_STA==0)
					{
						TIM_Cmd(TIM3, ENABLE);  //使能定时器3
					}
						 
					UART2_RX_BUF[UART2_RX_STA++]=Res;		//记录接收到的值	 
				}
				else 
				{
					UART2_RX_STA|=1<<15;					//强制标记接收完成
				} 
			}  	

		
		#endif
	} 
	
 #if UCOS_II_EN  
	OSIntExit();    	//退出中断
	#endif
} 


void USART3_IRQHandler(void)                	//串口3中断服务程序
{
	u8 Res;
#if UCOS_II_EN  //使用UCOS操作系统
	OSIntEnter();    
#endif
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //接收中断
	{		
		Res =USART_ReceiveData(USART3);//(USART3->DR);	//读取接收到的数据
		#if (UART3_RX_MODE == 1)          //(接收到的数据必须是0x0d 0x0a结尾)
			if((UART3_RX_STA&0x8000)==0)//接收未完成
			{
				if(UART3_RX_STA&0x4000)//接收到了0x0d
				{
					if(Res!=0x0a)
						UART3_RX_STA=0;//接收错误,重新开始
					else 
						UART3_RX_STA|=0x8000;	//接收完成了 
				}
				else //还没收到0X0D
				{	
					if(Res==0x0d)
						UART3_RX_STA|=0x4000;
					else
					{
						UART3_RX_BUF[UART3_RX_STA&0X3FFF]=Res ;
						UART3_RX_STA++;
						if(UART3_RX_STA>(UART3_RXBUF_SIZE-1))
							UART3_RX_STA=0;//接收数据错误,重新开始接收	  
					}		 
				}
			}
			
		#elif (UART3_RX_MODE == 2)        //RS485接收模式
		
			if(UART3_RX_STA<UART3_RXBUF_SIZE)
			{
				UART3_RX_BUF[UART3_RX_STA]=Res;		//记录接收到的值
				UART3_RX_STA++;						//接收数据增加1 
			} 
			
		#else   //定时器中断接收
						//通过判断接收连续2个字符之间的时间差不大于100ms来决定是不是一次连续的数据.
						//如果2个字符接收间隔超过100ms,则认为不是1次连续数据.也就是超过100ms没有接收到
						//任何数据,则表示此次接收完毕.
						//接收到的数据状态
						//[15]:0,没有接收到数据;1,接收到了一批数据.
						//[14:0]:接收到的数据长度
		
			if((UART3_RX_STA&(1<<15))==0)//接收完的一批数据,还没有被处理,则不再接收其他数据
			{ 
				if(UART3_RX_STA<UART3_RXBUF_SIZE)		//还可以接收数据
				{
					TIM_SetCounter(TIM4,0);//计数器清空        				 
					if(UART3_RX_STA==0)
					{
						TIM_Cmd(TIM4, ENABLE);  //使能定时器4
					}
						 
					UART3_RX_BUF[UART3_RX_STA++]=Res;		//记录接收到的值	 
				}
				else 
				{
					UART3_RX_STA|=1<<15;					//强制标记接收完成
				} 
			}  	

		
		#endif
	} 
	
 #if UCOS_II_EN  
	OSIntExit();    	//退出中断
	#endif
} 


void UART4_IRQHandler(void)                	//串口4中断服务程序
{
	u8 Res;
#if UCOS_II_EN  //使用UCOS操作系统
	OSIntEnter();    
#endif
	if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)  //接收中断
	{		
		Res =USART_ReceiveData(UART4);//(USART1->DR);	//读取接收到的数据
		#if (UART4_RX_MODE == 1)          //(接收到的数据必须是0x0d 0x0a结尾)
			if((UART4_RX_STA&0x8000)==0)//接收未完成
			{
				if(UART4_RX_STA&0x4000)//接收到了0x0d
				{
					if(Res!=0x0a)
						UART4_RX_STA=0;//接收错误,重新开始
					else 
						UART4_RX_STA|=0x8000;	//接收完成了 
				}
				else //还没收到0X0D
				{	
					if(Res==0x0d)
						UART4_RX_STA|=0x4000;
					else
					{
						UART4_RX_BUF[UART4_RX_STA&0X3FFF]=Res ;
						UART4_RX_STA++;
						queue_push(Res);
						if(UART4_RX_STA>(UART4_RXBUF_SIZE-1))
							UART4_RX_STA=0;//接收数据错误,重新开始接收	  
					}		 
				}
			}
		
		#elif (UART4_RX_MODE == 2)        //RS485接收模式
	
			if(UART4_RX_STA<UART4_RXBUF_SIZE)
			{
				UART4_RX_BUF[UART4_RX_STA]=Res;		//记录接收到的值
				UART4_RX_STA++;						//接收数据增加1 
			} 
			
		#else   //定时器中断接收
						//通过判断接收连续2个字符之间的时间差不大于100ms来决定是不是一次连续的数据.
						//如果2个字符接收间隔超过100ms,则认为不是1次连续数据.也就是超过100ms没有接收到
						//任何数据,则表示此次接收完毕.
						//接收到的数据状态
						//[15]:0,没有接收到数据;1,接收到了一批数据.
						//[14:0]:接收到的数据长度
		
			if((UART4_RX_STA&(1<<15))==0)//接收完的一批数据,还没有被处理,则不再接收其他数据
			{ 
				if(UART4_RX_STA<UART4_RXBUF_SIZE)		//还可以接收数据
				{
					TIM_SetCounter(TIM5,0);//计数器清空        				 
					if(UART4_RX_STA==0)
					{
						TIM_Cmd(TIM5, ENABLE);  //使能定时器5
					}
						 
					UART4_RX_BUF[UART4_RX_STA++]=Res;		//记录接收到的值	 
				}
				else 
				{
					UART4_RX_STA|=1<<15;					//强制标记接收完成
					
				} 
			}  	

		
		#endif
	} 
	
 #if UCOS_II_EN  
	OSIntExit();    	//退出中断
	#endif
} 


void UART5_IRQHandler(void)                	//串口5中断服务程序
{
	u8 Res;
#if UCOS_II_EN  //使用UCOS操作系统
	OSIntEnter();    
#endif
	if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)  //接收中断
	{		
		Res =USART_ReceiveData(UART5);//(USART1->DR);	//读取接收到的数据
		#if (UART5_RX_MODE == 1)          //(接收到的数据必须是0x0d 0x0a结尾)
			if((UART5_RX_STA&0x8000)==0)//接收未完成
			{
				if(UART5_RX_STA&0x4000)//接收到了0x0d
				{
					if(Res!=0x0a)
						UART5_RX_STA=0;//接收错误,重新开始
					else 
						UART5_RX_STA|=0x8000;	//接收完成了 
						
						
				}
				else //还没收到0X0D
				{	
					if(Res==0x0d)
						UART5_RX_STA|=0x4000;
					else
					{
						UART5_RX_BUF[UART5_RX_STA&0X3FFF]=Res ;
						UART5_RX_STA++;
						if(UART5_RX_STA>(UART5_RXBUF_SIZE-1))
							UART5_RX_STA=0;//接收数据错误,重新开始接收	  
					}		 
				}
			}
			
		#elif (UART5_RX_MODE == 2)        //RS485接收模式
	
			if(UART5_RX_STA<UART5_RXBUF_SIZE)
			{
				UART5_RX_BUF[UART5_RX_STA]=Res;		//记录接收到的值
				UART5_RX_STA++;						//接收数据增加1 
			} 
			
		#else   //定时器中断接收
						//通过判断接收连续2个字符之间的时间差不大于100ms来决定是不是一次连续的数据.
						//如果2个字符接收间隔超过100ms,则认为不是1次连续数据.也就是超过100ms没有接收到
						//任何数据,则表示此次接收完毕.
						//接收到的数据状态
						//[15]:0,没有接收到数据;1,接收到了一批数据.
						//[14:0]:接收到的数据长度
		
			if((UART5_RX_STA&(1<<15))==0)//接收完的一批数据,还没有被处理,则不再接收其他数据
			{ 
				if(UART5_RX_STA<UART5_RXBUF_SIZE)		//还可以接收数据
				{
					TIM_SetCounter(TIM5,0);//计数器清空        				 
					if(UART5_RX_STA==0)
					{
						TIM_Cmd(TIM5, ENABLE);  //使能定时器6
					}
						 
					UART5_RX_BUF[UART5_RX_STA++]=Res;		//记录接收到的值	 
				}
				else 
				{
					UART5_RX_STA|=1<<15;					//强制标记接收完成
				} 
			}  	

		
		#endif
	} 
	
 #if UCOS_II_EN  
	OSIntExit();    	//退出中断
	#endif
} 


void USART6_IRQHandler(void)                	//串口6中断服务程序
{
	u8 Res;
#if UCOS_II_EN  //使用UCOS操作系统
	OSIntEnter();    
#endif

	if(USART_GetITStatus(USART6, USART_IT_RXNE) != RESET)  //接收中断
	{		
		Res =USART_ReceiveData(USART6);//(USART6->DR);	//读取接收到的数据
		
		if(UART6_RX_STA<64)
		{
			UART6_RX_BUF[UART6_RX_STA]=Res;		//记录接收到的值		
			UART6_RX_STA++;						//接收数据增加1 
		} 
		
		
		
	/*	#if (UART6_RX_MODE == 1)          //(接收到的数据必须是0x0d 0x0a结尾)
			if((UART6_RX_STA&0x8000)==0)//接收未完成
			{
				if(UART6_RX_STA&0x4000)//接收到了0x0d
				{
					if(Res!=0x0a)
						UART6_RX_STA=0;//接收错误,重新开始
					else 
						UART6_RX_STA|=0x8000;	//接收完成了 
				}
				else //还没收到0X0D
				{	
					if(Res==0x0d)
						UART6_RX_STA|=0x4000;
					else
					{
						UART6_RX_BUF[UART6_RX_STA&0X3FFF]=Res ;
						UART6_RX_STA++;
						if(UART6_RX_STA>(UART6_RXBUF_SIZE-1))
							UART6_RX_STA=0;//接收数据错误,重新开始接收	  
					}		 
				}
			}
			
		#elif (UART6_RX_MODE == 2)        //RS485接收模式
	
			if(UART6_RX_STA<UART6_RXBUF_SIZE)
			{
				UART6_RX_BUF[UART6_RX_STA]=Res;		//记录接收到的值
				UART6_RX_STA++;						//接收数据增加1 
			} 
			
		#else   //定时器中断接收
						//通过判断接收连续2个字符之间的时间差不大于100ms来决定是不是一次连续的数据.
						//如果2个字符接收间隔超过100ms,则认为不是1次连续数据.也就是超过100ms没有接收到
						//任何数据,则表示此次接收完毕.
						//接收到的数据状态
						//[15]:0,没有接收到数据;1,接收到了一批数据.
						//[14:0]:接收到的数据长度
		
			if((UART6_RX_STA&(1<<15))==0)//接收完的一批数据,还没有被处理,则不再接收其他数据
			{ 
				if(UART6_RX_STA<UART6_RXBUF_SIZE)		//还可以接收数据
				{
					TIM_SetCounter(TIM7,0);//计数器清空        				 
					if(UART6_RX_STA==0)
					{
						TIM_Cmd(TIM7, ENABLE);  //使能定时器7
					}
						 
					UART6_RX_BUF[UART6_RX_STA++]=Res;		//记录接收到的值	 
				}
				else 
				{
					UART6_RX_STA|=1<<15;					//强制标记接收完成
				} 
			}  	

		
		#endif     */
	} 
	
 #if UCOS_II_EN  
	OSIntExit();    	//退出中断
	#endif
} 
