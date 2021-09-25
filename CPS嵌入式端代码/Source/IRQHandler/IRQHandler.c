/************************************************************************************
*  Copyright (c), 2019, ��������ѧ
*            All rights reserved.
*
* http:  www.jxust.edu.cn
* Email: 
*
* File name: UserVars.c
* Project  : STM32F4XXϵ��ģ�����
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  �ǻ۹����о���
* Version: 1.00
* Date:    2019.12.11			
* Email:   
* 
* Description: ���ļ���������ϵͳ�жϴ�����;
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
// �����ⲿͷ�ļ�
/************************************************************************************/

#include "sys.h"
#include "STM32F4_Head.h"
#include "PIONEER_Config.h"
#include "const.h"
#include "includes.h"					//ucos ʹ��	  
#include "UserVars.h"	
#include "OSVars.h"
#include "cmd_queue.h"
#include "hmi_user_uart.h"

/************************************************************************************/
/************************************************************************************
// ������ȫ�ֱ�������
*************************************************************************************/



/***********************************************************************************
* Function: EXTI0_ISRHook, EXTI1_ISRHook, EXTI2_ISRHook, EXTI3_ISRHook;
*           EXTI4_ISRHook, EXTI5_ISRHook, EXTI6_ISRHook, EXTI7_ISRHook,
*           EXTI8_ISRHook, EXTI9_ISRHook, EXTI10_ISRHook, EXTI11_ISRHook,
*           EXTI12_ISRHook, EXTI13_ISRHook, EXTI14_ISRHook, EXTI15_ISRHook,
*
* Description: ���º������ⲿIO 16���жϺ���;
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

//�ⲿ�ж�0�������
void EXTI0_IRQHandler(void)
{
	#if UCOS_II_EN  //ʹ��UCOS����ϵͳ
		OSIntEnter();    
	#endif

	delay_ms(10);	//����
	if(EXTI_GetITStatus(EXTI_Line0) != RESET)	 
	{
		// ���±�д�Լ����жϴ������
		if(KEY7 == 1)
		{
			printf("PE0����\r\n");
			sprintf((char *)GainNumber.ResultData,"%d",8);	//���ñ��Ϊ8
			ProcessingFlag=1;																//��Ʒ�ϸ��־Ϊ1
			SetTextValue(1,9,ProductResult8);								//������ڴ�������	
			OSSemPost(ResultSem);
		}
		
    #if (DEBUG_APP_EN > 0)
			printf("EXTI0�����ж�\r\n");
    #endif
		
	}		 
	 EXTI_ClearITPendingBit(EXTI_Line0); //���LINE0�ϵ��жϱ�־λ 
	#if UCOS_II_EN  
		OSIntExit();    	//�˳��ж�
	#endif
}	
//�ⲿ�ж�1�������
void EXTI1_IRQHandler(void)
{
	#if UCOS_II_EN  //ʹ��UCOS����ϵͳ
		OSIntEnter();    
	#endif

	delay_ms(10);	//����
	if(EXTI_GetITStatus(EXTI_Line1) != RESET)	 
	{
		// ���±�д�Լ����жϴ������
		if(KEY8 == 1)
		{
			printf("PE1����\r\n");
		}
		
    #if (DEBUG_APP_EN > 0)
			printf("EXTI1�����ж�\r\n");
    #endif
		
	}		 
	 EXTI_ClearITPendingBit(EXTI_Line1); //���LINE0�ϵ��жϱ�־λ 
	#if UCOS_II_EN  
		OSIntExit();    	//�˳��ж�
	#endif
}	

//�ⲿ�ж�2�������
void EXTI2_IRQHandler(void)
{
	#if UCOS_II_EN  //ʹ��UCOS����ϵͳ
		OSIntEnter();    
	#endif
	delay_ms(10);	//����
	if(EXTI_GetITStatus(EXTI_Line2) != RESET)	 
	{
		// ���±�д�Լ����жϴ������
		if(KEY9 == 1)
		{
			printf("PE2����\r\n");
		}
		
    #if (DEBUG_APP_EN > 0)
			printf("EXTI2�����ж�\r\n");
    #endif
		
	}		 
	 EXTI_ClearITPendingBit(EXTI_Line2);//���LINE2�ϵ��жϱ�־λ 
	#if UCOS_II_EN  
		OSIntExit();    	//�˳��ж�
	#endif
}
//�ⲿ�ж�3�������
void EXTI3_IRQHandler(void)
{
	#if UCOS_II_EN  //ʹ��UCOS����ϵͳ
		OSIntEnter();    
	#endif
	delay_ms(10);	//����
	if(EXTI_GetITStatus(EXTI_Line3) != RESET)	 
	{
		// ���±�д�Լ����жϴ������
		if(KEY0==1)
		{
			printf("PD3����");
			sprintf((char *)GainNumber.ResultData,"%d",1);	//���ñ��Ϊ1
			SetTextValue(1,9,ProductResult1);								//������ڴ�������	
			ProcessingFlag=1;																//��Ʒ�ϸ��־Ϊ1
			OSSemPost(ResultSem);														//�ͷŲ�Ʒ����Ļ����ź���
			ProductResultFlag=1;														//��Ʒ�����Ӽ�¼�ı�־
		}
		
    #if (DEBUG_APP_EN > 0)
			printf("EXTI3�����ж�\r\n");
    #endif
		
	}		 
	 EXTI_ClearITPendingBit(EXTI_Line3);  //���LINE3�ϵ��жϱ�־λ  
	#if UCOS_II_EN  
		OSIntExit();    	//�˳��ж�
	#endif
}
//�ⲿ�ж�4�������
void EXTI4_IRQHandler(void)
{
	#if UCOS_II_EN  //ʹ��UCOS����ϵͳ
		OSIntEnter();    
	#endif
	delay_ms(10);	//����
	if(EXTI_GetITStatus(EXTI_Line4) != RESET)	 
	{
		// ���±�д�Լ����жϴ������
		if(KEY1 == 1)
		{
			printf("PD4����\r\n");
			sprintf((char *)GainNumber.ResultData,"%d",2);	//���ñ��Ϊ2
			SetTextValue(1,9,ProductResult2);								//������ڴ�������
			ProcessingFlag=1;																//��Ʒ�ϸ��־Ϊ1			
			OSSemPost(ResultSem);														//�ͷŲ�Ʒ����Ļ����ź���
			ProductResultFlag=1;														//��Ʒ�����Ӽ�¼�ı�־
		}
		
    #if (DEBUG_APP_EN > 0)
			printf("EXTI4�����ж�\r\n");
    #endif
		
	}		 
	 EXTI_ClearITPendingBit(EXTI_Line4);//���LINE4�ϵ��жϱ�־λ  
	#if UCOS_II_EN  
		OSIntExit();    	//�˳��ж�
	#endif
}
//�ⲿ�ж�5~9������
void EXTI9_5_IRQHandler(void)
{
	#if UCOS_II_EN  //ʹ��UCOS����ϵͳ
		OSIntEnter();    
	#endif

	
	delay_ms(10);   //����
	
	//�ⲿ�ж�5����
	if(EXTI_GetITStatus(EXTI_Line5) != RESET)	 
	{
		// ���±�д�Լ����жϴ������
			if(KEY2==1)
			{
				printf("PD5����");
				sprintf((char *)GainNumber.ResultData,"%d",3);	//���ñ��Ϊ3
				SetTextValue(1,9,ProductResult3);								//������ڴ�������	
				ProcessingFlag=1;																//��Ʒ�ϸ��־Ϊ1
				OSSemPost(ResultSem);														//�ͷŲ�Ʒ����Ļ����ź���
				ProductResultFlag=1;														//��Ʒ�����Ӽ�¼�ı�־
			}
		
		
    #if (DEBUG_APP_EN > 0)
			printf("EXTI5�����ж�\r\n");
    #endif
		EXTI_ClearITPendingBit(EXTI_Line5);//���LINE5�ϵ��жϱ�־λ
	}	
	//�ⲿ�ж�6����
	if(EXTI_GetITStatus(EXTI_Line6) != RESET)	 
	{
		// ���±�д�Լ����жϴ������
		if(KEY3 == 1)
		{
			printf("PD6����\r\n");
			sprintf((char *)GainNumber.ResultData,"%d",4);	//���ñ��Ϊ4
			SetTextValue(1,9,ProductResult4);								//������ڴ�������	
			ProcessingFlag=1;																//��Ʒ�ϸ��־Ϊ1
			OSSemPost(ResultSem);														//�ͷŲ�Ʒ����Ļ����ź���
			ProductResultFlag=1;														//��Ʒ�����Ӽ�¼�ı�־
		}
		
		
    #if (DEBUG_APP_EN > 0)
			printf("EXTI6�����ж�\r\n");
    #endif
		EXTI_ClearITPendingBit(EXTI_Line6);//���LINE6�ϵ��жϱ�־λ
	}	
	//�ⲿ�ж�7����
	if(EXTI_GetITStatus(EXTI_Line7) != RESET)	 
	{
		// ���±�д�Լ����жϴ������
		if(KEY4 == 1)
		{
			printf("PD7����\r\n");
			sprintf((char *)GainNumber.ResultData,"%d",5);	//���ñ��Ϊ5
			SetTextValue(1,9,ProductResult5);								//������ڴ�������	
			ProcessingFlag=1;																//��Ʒ�ϸ��־Ϊ1
			OSSemPost(ResultSem);														//�ͷŲ�Ʒ����Ļ����ź���
			ProductResultFlag=1;														//��Ʒ�����Ӽ�¼�ı�־
		}
		
		
    #if (DEBUG_APP_EN > 0)
			printf("EXTI7�����ж�\r\n");
    #endif
		EXTI_ClearITPendingBit(EXTI_Line7);//���LINE5�ϵ��жϱ�־λ
	}	
	//�ⲿ�ж�8����
	if(EXTI_GetITStatus(EXTI_Line8) != RESET)	 
	{
		// ���±�д�Լ����жϴ������

		
		
    #if (DEBUG_APP_EN > 0)
			printf("EXTI8�����ж�\r\n");
    #endif
		EXTI_ClearITPendingBit(EXTI_Line8);//���LINE8�ϵ��жϱ�־λ
	}	
	//�ⲿ�ж�9����
	if(EXTI_GetITStatus(EXTI_Line9) != RESET)	 
	{
		// ���±�д�Լ����жϴ������

		
		
    #if (DEBUG_APP_EN > 0)
			printf("EXTI9�����ж�\r\n");
    #endif
		EXTI_ClearITPendingBit(EXTI_Line9);//���LINE9�ϵ��жϱ�־λ
	}
	#if UCOS_II_EN  
		OSIntExit();    	//�˳��ж�
	#endif	
}

//�ⲿ�ж�10~15������
void EXTI15_10_IRQHandler(void)
{
	#if UCOS_II_EN  //ʹ��UCOS����ϵͳ
		OSIntEnter();    
	#endif

	
	delay_ms(10);   //����
	
	//�ⲿ�ж�10����
	if(EXTI_GetITStatus(EXTI_Line10) != RESET)	 
	{
		// ���±�д�Լ����жϴ������

		
		
    #if (DEBUG_APP_EN > 0)
			printf("EXTI10�����ж�\r\n");
    #endif
		EXTI_ClearITPendingBit(EXTI_Line10);//���LINE10�ϵ��жϱ�־λ
	}	
	//�ⲿ�ж�11����
	if(EXTI_GetITStatus(EXTI_Line11) != RESET)	 
	{
		// ���±�д�Լ����жϴ������

		
		
    #if (DEBUG_APP_EN > 0)
			printf("EXTI11�����ж�\r\n");
    #endif
		EXTI_ClearITPendingBit(EXTI_Line11);//���LINE11�ϵ��жϱ�־λ
	}	
	//�ⲿ�ж�12����
	if(EXTI_GetITStatus(EXTI_Line12) != RESET)	 
	{
		// ���±�д�Լ����жϴ������

		
		
    #if (DEBUG_APP_EN > 0)
			printf("EXTI12�����ж�\r\n");
    #endif
		EXTI_ClearITPendingBit(EXTI_Line12);//���LINE12�ϵ��жϱ�־λ
	}	
	//�ⲿ�ж�13����
	if(EXTI_GetITStatus(EXTI_Line13) != RESET)	 
	{
		// ���±�д�Լ����жϴ������

		
		
    #if (DEBUG_APP_EN > 0)
			printf("EXTI13�����ж�\r\n");
    #endif
		EXTI_ClearITPendingBit(EXTI_Line13);//���LINE13�ϵ��жϱ�־λ
	}	
	//�ⲿ�ж�14����
	if(EXTI_GetITStatus(EXTI_Line14) != RESET)	 
	{
		// ���±�д�Լ����жϴ������
		if(KEY5 == 1)
		{
			printf("PB14����\r\n");
			sprintf((char *)GainNumber.ResultData,"%d",6);	//���ñ��Ϊ6
			SetTextValue(1,9,ProductResult6);								//������ڴ�������	
			ProcessingFlag=1;																//��Ʒ�ϸ��־Ϊ1
			OSSemPost(ResultSem);														//�ͷŲ�Ʒ����Ļ����ź���
			ProductResultFlag=1;														//��Ʒ�����Ӽ�¼�ı�־
		}
		
		
    #if (DEBUG_APP_EN > 0)
			printf("EXTI14�����ж�\r\n");
    #endif
		EXTI_ClearITPendingBit(EXTI_Line14);//���LINE9�ϵ��жϱ�־λ
	}	
		//�ⲿ�ж�15����
	if(EXTI_GetITStatus(EXTI_Line15) != RESET)	 
	{
		// ���±�д�Լ����жϴ������
		if(KEY6 == 1)
			{
				printf("PB15����\r\n");
				sprintf((char *)GainNumber.ResultData,"%d",7);	//���ñ��Ϊ7
				SetTextValue(1,9,ProductResult7);								//������ڴ�������	
				ProcessingFlag=1;																//��Ʒ�ϸ��־Ϊ1
				OSSemPost(ResultSem);														//�ͷŲ�Ʒ����Ļ����ź���
				ProductResultFlag=1;														//��Ʒ�����Ӽ�¼�ı�־
			}
		
		
    #if (DEBUG_APP_EN > 0)
			printf("EXTI15�����ж�\r\n");
    #endif
		EXTI_ClearITPendingBit(EXTI_Line15);//���LINE15�ϵ��жϱ�־λ
	}	
	
	#if UCOS_II_EN  
		OSIntExit();    	//�˳��ж�
	#endif
	
}

/***********************************************************************************
* Function: TIM2_IRQHandler, TIM3_IRQHandler, TIM4_IRQHandler,TIM5_IRQHandler, 
*			TIM6_IRQHandler, TIM7_IRQHandler
*
* Description: ��������TIM1��TIM8�жϹ��Ӻ���;
*           
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/

//��ʱ��2�жϷ�����
void TIM2_IRQHandler(void)
{
	#if UCOS_II_EN  //ʹ��UCOS����ϵͳ
		OSIntEnter();    
	#endif
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET) //����ж�
	{
		#if (UART1_EN>0 && UART1_RX_MODE==0) 
			UART1_RX_STA|=1<<15;	//��ǽ������
			TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  //���TIM2�����жϱ�־    
			TIM_Cmd(TIM2, DISABLE);  //�ر�TIM2
		#else
		// ���±�д�Լ����жϴ������
			//GPIO_SetBits(GPIOE,GPIO_Pin_2);   //BEEP�������ߣ� ��ͬBEEP=1;
			//delay_ms(300); 
			//GPIO_ResetBits(GPIOE,GPIO_Pin_2); //BEEP�������ͣ� ��ͬBEEP=0;
			//delay_ms(300);                    //��ʱ300ms

		
			TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  //���TIM2�����жϱ�־ 
		#endif
	}
	#if UCOS_II_EN  
		OSIntExit();    	//�˳��ж�
	#endif
}

//��ʱ��3�жϷ�����
void TIM3_IRQHandler(void)
{
	#if UCOS_II_EN  //ʹ��UCOS����ϵͳ
		OSIntEnter();    
	#endif
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //����ж�
	{
		#if (UART2_EN>0 && UART2_RX_MODE==0) 
			UART2_RX_STA|=1<<15;	//��ǽ������

			TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  //���TIM3�����жϱ�־    
			TIM_Cmd(TIM3, DISABLE);  //�ر�TIM3 
		#else
		// ���±�д�Լ����жϴ������
		NBUpdateCnt++;
		if(NBUpdateCnt >= UPDATE_TIME_DATA*60)
		{
			TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  // ���TIM3�����жϱ�־  
			TIM_Cmd(TIM3, DISABLE);  											// �ر�TIM3
			OSSemPost(NBUpdateSem);												// ���ͼ�ʱ��������ź���
		}
		
		
			TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  //���TIM3�����жϱ�־ 
		#endif
	}
	#if UCOS_II_EN  
		OSIntExit();    	//�˳��ж�
	#endif
}

void TIM4_IRQHandler(void)
{
	#if UCOS_II_EN  //ʹ��UCOS����ϵͳ
		OSIntEnter();    
	#endif
	if(TIM_GetITStatus(TIM4,TIM_IT_Update)==SET) //����ж�
	{
		#if (UART3_EN>0 && UART3_RX_MODE==0) 
			UART3_RX_STA|=1<<15;	//��ǽ������
			OSSemPost(UART3Sem);
			TIM_ClearITPendingBit(TIM4, TIM_IT_Update);  //���TIM3�����жϱ�־    
			TIM_Cmd(TIM4, DISABLE);  //�ر�TIM3 
		#else
		// ���±�д�Լ����жϴ������
		NBUpdateCnt++;
		if(NBUpdateCnt >= UPDATE_TIME_DATA*60)
		{
			TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );  // ���TIM3�����жϱ�־  
			TIM_Cmd(TIM4, DISABLE);  											// �ر�TIM3
			OSSemPost(NBUpdateSem);												// ���ͼ�ʱ��������ź���
		}
		
		
			TIM_ClearITPendingBit(TIM4, TIM_IT_Update);  //���TIM3�����жϱ�־ 
		#endif
	}
	#if UCOS_II_EN  
		OSIntExit();    	//�˳��ж�
	#endif
}

/*
void TIM4_IRQHandler(void)
{
	#if UCOS_II_EN  //ʹ��UCOS����ϵͳ
	OSIntEnter();    
	#endif
	if((TIM4CH1_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
	{	  
		if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
		 
		{	    
			if(TIM4CH1_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
			{
				if((TIM4CH1_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
				{
					TIM4CH1_CAPTURE_STA|=0X80;//��ǳɹ�������һ��
					TIM4CH1_CAPTURE_VAL=0XFFFF;
				}else TIM4CH1_CAPTURE_STA++;
			}	 
		}
		if(TIM_GetITStatus(TIM4, TIM_IT_CC1) != RESET)//����1���������¼�
		{	
			if(TIM4CH1_CAPTURE_STA&0X40)		//����һ���½��� 		
			{	  			
				TIM4CH1_CAPTURE_STA|=0X80;		//��ǳɹ�����һ��������
				TIM4CH1_CAPTURE_VAL=TIM_GetCapture1(TIM4);
		   	TIM_OC1PolarityConfig(TIM4,TIM_ICPolarity_Rising); //CC1P=0 ����Ϊ�����ز���
			}else  								//��δ��ʼ,��һ�β���������
			{
				TIM4CH1_CAPTURE_STA=0;			//���
				TIM4CH1_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM4,0);
			
				TIM4CH1_CAPTURE_STA|=0X40;		//��ǲ�����������
				TIM_OC1PolarityConfig(TIM4,TIM_ICPolarity_Falling);		//CC1P=1 ����Ϊ�½��ز���
			}		    
		}
 	}
 
    TIM_ClearITPendingBit(TIM4, TIM_IT_CC1|TIM_IT_Update); //����жϱ�־λ		
	
	#if UCOS_II_EN  
		OSIntExit();    	//�˳��ж�
	#endif	
}
*/


/*
//��ʱ��4�жϷ�����
void TIM4_IRQHandler(void)
{
	#if UCOS_II_EN  //ʹ��UCOS����ϵͳ
		OSIntEnter();    
	#endif
	if(TIM_GetITStatus(TIM4,TIM_IT_Update)==SET) //����ж�
	{
		#if (UART3_EN>0 && UART3_RX_MODE==0) 
			UART3_RX_STA|=1<<15;	//��ǽ������
			TIM_ClearITPendingBit(TIM4, TIM_IT_Update);  //���TIM4�����жϱ�־    
			TIM_Cmd(TIM4, DISABLE);  //�ر�TIM4 
		#else
		// ���±�д�Լ����жϴ������
			//GPIO_SetBits(GPIOE,GPIO_Pin_2);   //BEEP�������ߣ� ��ͬBEEP=1;
			//delay_ms(500); 
			//GPIO_ResetBits(GPIOE,GPIO_Pin_2); //BEEP�������ͣ� ��ͬBEEP=0;
			//delay_ms(500);  
		
		
			TIM_ClearITPendingBit(TIM4, TIM_IT_Update);  //���TIM4�����жϱ�־ 
		#endif
	}
	#if UCOS_II_EN  
		OSIntExit();    	//�˳��ж�
	#endif
}
*/

//��ʱ��5�жϷ�����
void TIM5_IRQHandler(void)
{
	#if UCOS_II_EN  //ʹ��UCOS����ϵͳ
		OSIntEnter();    
	#endif
	if(TIM_GetITStatus(TIM5,TIM_IT_Update)==SET) //����ж�
	{
		#if (UART5_EN>0 && UART5_RX_MODE==0) 
		if(0 == NBRvDelay)
		{
			UART5_RX_STA|=1<<15;	//��ǽ������
		  OSSemPost(NBUartRdy);														// ͨ���ź���֪ͨNB���������յ��˴�������
		  //OSSemPost(RS485UartRdy);		
			//OSSemPost(WaterRdy);
			//OSSemPost(FurnaceRdy);
			//OSSemPost(ConduRdy);
			TIM_ClearITPendingBit(TIM5, TIM_IT_Update);  //���TIM6�����жϱ�־    
			TIM_Cmd(TIM5, DISABLE);  //�ر�TIM6
		}
		else if (NBRvDelay >= 10)
		{
			TIM_ClearITPendingBit(TIM5, TIM_IT_Update);  //���TIM6�����жϱ�־
			NBRvDelay = 0;
		}
		else 
		{
			TIM_ClearITPendingBit(TIM5, TIM_IT_Update);  //���TIM6�����жϱ�־
			NBRvDelay++;
		}
			
		#else
		// ���±�д�Լ����жϴ������
		
		
		
			TIM_ClearITPendingBit(TIM5, TIM_IT_Update);  //���TIM6�����жϱ�־ 
		#endif
	}
	#if UCOS_II_EN  
		OSIntExit();    	//�˳��ж�
	#endif
	
	/*#if UCOS_II_EN  //ʹ��UCOS����ϵͳ
		OSIntEnter();    
	#endif
	if(TIM_GetITStatus(TIM5,TIM_IT_Update)==SET) //����ж�
	{
		#if (UART4_EN>0 && UART4_RX_MODE==0) 
			UART4_RX_STA|=1<<15;	//��ǽ������
	  	OSSemPost(ComSem);												// ���ͼ�ʱ��������ź���
			TIM_ClearITPendingBit(TIM5, TIM_IT_Update);  //���TIM5�����жϱ�־    
			TIM_Cmd(TIM5, DISABLE);  //�ر�TIM5 
		#else
		// ���±�д�Լ����жϴ������
		 
		
		
		
			TIM_ClearITPendingBit(TIM5, TIM_IT_Update);  //���TIM5�����жϱ�־ 
		#endif
	}
	#if UCOS_II_EN  
		OSIntExit();    	//�˳��ж�
	#endif*/
}






//��ʱ��6�жϷ�����
void TIM6_IRQHandler(void)
{
	#if UCOS_II_EN  //ʹ��UCOS����ϵͳ
		OSIntEnter();    
	#endif
	if(TIM_GetITStatus(TIM6,TIM_IT_Update)==SET) //����ж�
	{
		#if (UART5_EN>0 && UART5_RX_MODE==0) 
		if(0 == NBRvDelay)
		{
			UART5_RX_STA|=1<<15;	//��ǽ������
		  OSSemPost(NBUartRdy);														// ͨ���ź���֪ͨNB���������յ��˴�������
			TIM_ClearITPendingBit(TIM6, TIM_IT_Update);  //���TIM6�����жϱ�־    
			TIM_Cmd(TIM6, DISABLE);  //�ر�TIM6
		}
		else if (NBRvDelay >= 10)
		{
			TIM_ClearITPendingBit(TIM6, TIM_IT_Update);  //���TIM6�����жϱ�־
			NBRvDelay = 0;
		}
		else 
		{
			TIM_ClearITPendingBit(TIM6, TIM_IT_Update);  //���TIM6�����жϱ�־
			NBRvDelay++;
		}
			
		#else
		// ���±�д�Լ����жϴ������
		
		
		
			TIM_ClearITPendingBit(TIM6, TIM_IT_Update);  //���TIM6�����жϱ�־ 
		#endif
	}
	#if UCOS_II_EN  
		OSIntExit();    	//�˳��ж�
	#endif
}

//��ʱ��7�жϷ�����
void TIM7_IRQHandler(void)
{
	#if UCOS_II_EN  //ʹ��UCOS����ϵͳ
		OSIntEnter();    
	#endif
	if(TIM_GetITStatus(TIM7,TIM_IT_Update)==SET) //����ж�
	{
		#if (UART6_EN>0 && UART6_RX_MODE==0) 
			UART6_RX_STA|=1<<15;	//��ǽ������
			TIM_ClearITPendingBit(TIM7, TIM_IT_Update);  //���TIM7�����жϱ�־    
			TIM_Cmd(TIM7, DISABLE);  //�ر�TIM7 
		#else
		// ���±�д�Լ����жϴ������
	
			TIM_ClearITPendingBit(TIM7, TIM_IT_Update);  //���TIM7�����жϱ�־ 
			TIM_Cmd(TIM7, DISABLE);  //�ر�TIM7
		
		#endif
	}
	#if UCOS_II_EN  
		OSIntExit();    	//�˳��ж�
	#endif
	
}


/***********************************************************************************
* Function: RTC_Alarm_IRQHandler,RTC_WKUP_IRQHandler;
*
* Description: ���º�����RTC���Ӻͻ����жϵĹ��Ӻ���;
*           
* Input:
*
* Output: none;
*          		
* Return: none;
*
* Note:   ���ж�ֻ����STM32F10Xģ���ϴ���;
************************************************************************************/

//RTC�����жϷ�����
void RTC_Alarm_IRQHandler(void)
{    
	if(RTC_GetFlagStatus(RTC_FLAG_ALRAF)==SET)//ALARM A�ж�?
	{
		RTC_ClearFlag(RTC_FLAG_ALRAF);//����жϱ�־
		// ���±�д�Լ����жϴ������
		
		
		
		
		
		#if (DEBUG_APP_EN == 1)
			printf("RTC�������ӱ����ж�\r\n");  
		#endif
	}   
	EXTI_ClearITPendingBit(EXTI_Line17);	//����ж���17���жϱ�־ 											 
}

//RTC WAKE UP�жϷ�����
void RTC_WKUP_IRQHandler(void)
{    
	if(RTC_GetFlagStatus(RTC_FLAG_WUTF)==SET)//WK_UP�ж�
	{ 
		RTC_ClearFlag(RTC_FLAG_WUTF);	//����жϱ�־
		// ���±�д�Լ����жϴ������
		
		
		
		
		
		#if (DEBUG_APP_EN == 1)
			printf("RTC���������ж�\r\n");  
		#endif
		
		
		
	}   
	EXTI_ClearITPendingBit(EXTI_Line22);//����ж���22���жϱ�־ 								
}


/***********************************************************************************
* Function: USART1_IRQHandler,USART2_IRQHandler,USART3_IRQHandler,USART4_IRQHandler,
*           USART5_IRQHandler,USART6_IRQHandler;
*
* Description: ���º�����Uart1,Uart2,Uart3,Uart4,Uart5,Uart6�жϼ��������ݵĹ��Ӻ���;
*           
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   ������ֻ�ܸ��ݴ���״̬UartSR��д�������ݳ���, �����������ڲ��ж�ʵ��;
*         ��������д��3�ֽ���Э�� ������ PIONEER_Config.h�ļ����޸�  UART1_RX_MODE
************************************************************************************/



void USART1_IRQHandler(void)                	//����1�жϷ������
{
	u8 Res;
	#if UCOS_II_EN  //ʹ��UCOS����ϵͳ
		OSIntEnter();    
	#endif
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�
	{		
		Res =USART_ReceiveData(USART1);//(USART1->DR);	//��ȡ���յ�������
		#if (UART1_RX_MODE == 1)         //(���յ������ݱ�����0x0d 0x0a��β)
			if((UART1_RX_STA&0x8000)==0)//����δ���
			{
				if(UART1_RX_STA&0x4000)//���յ���0x0d
				{
					if(Res!=0x0a)
						UART1_RX_STA=0;//���մ���,���¿�ʼ
					else 
						UART1_RX_STA|=0x8000;	//��������� 
				}
				else //��û�յ�0X0D
				{	
					if(Res==0x0d)
						UART1_RX_STA|=0x4000;
					else
					{
						UART1_RX_BUF[UART1_RX_STA&0X3FFF]=Res ;
						UART1_RX_STA++;
						if(UART1_RX_STA>(UART1_RXBUF_SIZE-1))
							UART1_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
					}		 
				}
			}
			
		#elif (UART1_RX_MODE == 2)        //RS485����ģʽ
		
			if(UART1_RX_STA<UART1_RXBUF_SIZE)
			{
				UART1_RX_BUF[UART1_RX_STA]=Res;		//��¼���յ���ֵ
				UART1_RX_STA++;						//������������1 
			} 
			
			
		#else   //��ʱ���жϽ���
						//ͨ���жϽ�������2���ַ�֮���ʱ������100ms�������ǲ���һ������������.
						//���2���ַ����ռ������100ms,����Ϊ����1����������.Ҳ���ǳ���100msû�н��յ�
						//�κ�����,���ʾ�˴ν������.
						//���յ�������״̬
						//[15]:0,û�н��յ�����;1,���յ���һ������.
						//[14:0]:���յ������ݳ���
		
			if((UART1_RX_STA&(1<<15))==0)//�������һ������,��û�б�����,���ٽ�����������
			{ 
				if(UART1_RX_STA<UART1_RXBUF_SIZE)		//�����Խ�������
				{
					TIM_SetCounter(TIM2,0);//���������        				 
					if(UART1_RX_STA==0)
					{
						TIM_Cmd(TIM2, ENABLE);  //ʹ�ܶ�ʱ��2
					}
						 
					UART1_RX_BUF[UART1_RX_STA++]=Res;		//��¼���յ���ֵ	 
				}
				else 
				{
					UART1_RX_STA|=1<<15;					//ǿ�Ʊ�ǽ������
				} 
			}  	

		
		#endif
	} 
	
	#if UCOS_II_EN  
		OSIntExit();    	//�˳��ж�
	#endif
} 


void USART2_IRQHandler(void)                	//����2�жϷ������
{
	u8 Res;
#if UCOS_II_EN  //ʹ��UCOS����ϵͳ
	OSIntEnter();    
#endif
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //�����ж�
	{		
		Res =USART_ReceiveData(USART2);//(USART2->DR);	//��ȡ���յ�������
		#if (UART2_RX_MODE == 1)          //(���յ������ݱ�����0x0d 0x0a��β)
			if((UART2_RX_STA&0x8000)==0)//����δ���
			{
				if(UART2_RX_STA&0x4000)//���յ���0x0d
				{
					if(Res!=0x0a)
						UART2_RX_STA=0;//���մ���,���¿�ʼ
					else 
						UART2_RX_STA|=0x8000;	//��������� 
				}
				else //��û�յ�0X0D
				{	
					if(Res==0x0d)
						UART2_RX_STA|=0x4000;
					else
					{
						UART2_RX_BUF[UART2_RX_STA&0X3FFF]=Res ;
						UART2_RX_STA++;
						if(UART2_RX_STA>(UART2_RXBUF_SIZE-1))
							UART2_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
					}		 
				}
			}
		/*if(UART2_RX_STA<64)
		{
			
			UART2_RX_BUF[UART2_RX_STA]=Res;		//��¼���յ���ֵ
			
			UART2_RX_STA++;						//������������1 
		}*/
			
		#elif (UART2_RX_MODE == 2)        //RS485����ģʽ
		
			if(UART2_RX_STA<UART2_RXBUF_SIZE)
			{
				UART2_RX_BUF[UART2_RX_STA]=Res;		//��¼���յ���ֵ
				UART2_RX_STA++;						//������������1 
			} 
			
		#else   //��ʱ���жϽ���
						//ͨ���жϽ�������2���ַ�֮���ʱ������100ms�������ǲ���һ������������.
						//���2���ַ����ռ������100ms,����Ϊ����1����������.Ҳ���ǳ���100msû�н��յ�
						//�κ�����,���ʾ�˴ν������.
						//���յ�������״̬
						//[15]:0,û�н��յ�����;1,���յ���һ������.
						//[14:0]:���յ������ݳ���
		
			if((UART2_RX_STA&(1<<15))==0)//�������һ������,��û�б�����,���ٽ�����������
			{ 
				if(UART2_RX_STA<UART2_RXBUF_SIZE)		//�����Խ�������
				{
					TIM_SetCounter(TIM3,0);//���������        				 
					if(UART2_RX_STA==0)
					{
						TIM_Cmd(TIM3, ENABLE);  //ʹ�ܶ�ʱ��3
					}
						 
					UART2_RX_BUF[UART2_RX_STA++]=Res;		//��¼���յ���ֵ	 
				}
				else 
				{
					UART2_RX_STA|=1<<15;					//ǿ�Ʊ�ǽ������
				} 
			}  	

		
		#endif
	} 
	
 #if UCOS_II_EN  
	OSIntExit();    	//�˳��ж�
	#endif
} 


void USART3_IRQHandler(void)                	//����3�жϷ������
{
	u8 Res;
#if UCOS_II_EN  //ʹ��UCOS����ϵͳ
	OSIntEnter();    
#endif
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //�����ж�
	{		
		Res =USART_ReceiveData(USART3);//(USART3->DR);	//��ȡ���յ�������
		#if (UART3_RX_MODE == 1)          //(���յ������ݱ�����0x0d 0x0a��β)
			if((UART3_RX_STA&0x8000)==0)//����δ���
			{
				if(UART3_RX_STA&0x4000)//���յ���0x0d
				{
					if(Res!=0x0a)
						UART3_RX_STA=0;//���մ���,���¿�ʼ
					else 
						UART3_RX_STA|=0x8000;	//��������� 
				}
				else //��û�յ�0X0D
				{	
					if(Res==0x0d)
						UART3_RX_STA|=0x4000;
					else
					{
						UART3_RX_BUF[UART3_RX_STA&0X3FFF]=Res ;
						UART3_RX_STA++;
						if(UART3_RX_STA>(UART3_RXBUF_SIZE-1))
							UART3_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
					}		 
				}
			}
			
		#elif (UART3_RX_MODE == 2)        //RS485����ģʽ
		
			if(UART3_RX_STA<UART3_RXBUF_SIZE)
			{
				UART3_RX_BUF[UART3_RX_STA]=Res;		//��¼���յ���ֵ
				UART3_RX_STA++;						//������������1 
			} 
			
		#else   //��ʱ���жϽ���
						//ͨ���жϽ�������2���ַ�֮���ʱ������100ms�������ǲ���һ������������.
						//���2���ַ����ռ������100ms,����Ϊ����1����������.Ҳ���ǳ���100msû�н��յ�
						//�κ�����,���ʾ�˴ν������.
						//���յ�������״̬
						//[15]:0,û�н��յ�����;1,���յ���һ������.
						//[14:0]:���յ������ݳ���
		
			if((UART3_RX_STA&(1<<15))==0)//�������һ������,��û�б�����,���ٽ�����������
			{ 
				if(UART3_RX_STA<UART3_RXBUF_SIZE)		//�����Խ�������
				{
					TIM_SetCounter(TIM4,0);//���������        				 
					if(UART3_RX_STA==0)
					{
						TIM_Cmd(TIM4, ENABLE);  //ʹ�ܶ�ʱ��4
					}
						 
					UART3_RX_BUF[UART3_RX_STA++]=Res;		//��¼���յ���ֵ	 
				}
				else 
				{
					UART3_RX_STA|=1<<15;					//ǿ�Ʊ�ǽ������
				} 
			}  	

		
		#endif
	} 
	
 #if UCOS_II_EN  
	OSIntExit();    	//�˳��ж�
	#endif
} 


void UART4_IRQHandler(void)                	//����4�жϷ������
{
	u8 Res;
#if UCOS_II_EN  //ʹ��UCOS����ϵͳ
	OSIntEnter();    
#endif
	if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)  //�����ж�
	{		
		Res =USART_ReceiveData(UART4);//(USART1->DR);	//��ȡ���յ�������
		#if (UART4_RX_MODE == 1)          //(���յ������ݱ�����0x0d 0x0a��β)
			if((UART4_RX_STA&0x8000)==0)//����δ���
			{
				if(UART4_RX_STA&0x4000)//���յ���0x0d
				{
					if(Res!=0x0a)
						UART4_RX_STA=0;//���մ���,���¿�ʼ
					else 
						UART4_RX_STA|=0x8000;	//��������� 
				}
				else //��û�յ�0X0D
				{	
					if(Res==0x0d)
						UART4_RX_STA|=0x4000;
					else
					{
						UART4_RX_BUF[UART4_RX_STA&0X3FFF]=Res ;
						UART4_RX_STA++;
						queue_push(Res);
						if(UART4_RX_STA>(UART4_RXBUF_SIZE-1))
							UART4_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
					}		 
				}
			}
		
		#elif (UART4_RX_MODE == 2)        //RS485����ģʽ
	
			if(UART4_RX_STA<UART4_RXBUF_SIZE)
			{
				UART4_RX_BUF[UART4_RX_STA]=Res;		//��¼���յ���ֵ
				UART4_RX_STA++;						//������������1 
			} 
			
		#else   //��ʱ���жϽ���
						//ͨ���жϽ�������2���ַ�֮���ʱ������100ms�������ǲ���һ������������.
						//���2���ַ����ռ������100ms,����Ϊ����1����������.Ҳ���ǳ���100msû�н��յ�
						//�κ�����,���ʾ�˴ν������.
						//���յ�������״̬
						//[15]:0,û�н��յ�����;1,���յ���һ������.
						//[14:0]:���յ������ݳ���
		
			if((UART4_RX_STA&(1<<15))==0)//�������һ������,��û�б�����,���ٽ�����������
			{ 
				if(UART4_RX_STA<UART4_RXBUF_SIZE)		//�����Խ�������
				{
					TIM_SetCounter(TIM5,0);//���������        				 
					if(UART4_RX_STA==0)
					{
						TIM_Cmd(TIM5, ENABLE);  //ʹ�ܶ�ʱ��5
					}
						 
					UART4_RX_BUF[UART4_RX_STA++]=Res;		//��¼���յ���ֵ	 
				}
				else 
				{
					UART4_RX_STA|=1<<15;					//ǿ�Ʊ�ǽ������
					
				} 
			}  	

		
		#endif
	} 
	
 #if UCOS_II_EN  
	OSIntExit();    	//�˳��ж�
	#endif
} 


void UART5_IRQHandler(void)                	//����5�жϷ������
{
	u8 Res;
#if UCOS_II_EN  //ʹ��UCOS����ϵͳ
	OSIntEnter();    
#endif
	if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)  //�����ж�
	{		
		Res =USART_ReceiveData(UART5);//(USART1->DR);	//��ȡ���յ�������
		#if (UART5_RX_MODE == 1)          //(���յ������ݱ�����0x0d 0x0a��β)
			if((UART5_RX_STA&0x8000)==0)//����δ���
			{
				if(UART5_RX_STA&0x4000)//���յ���0x0d
				{
					if(Res!=0x0a)
						UART5_RX_STA=0;//���մ���,���¿�ʼ
					else 
						UART5_RX_STA|=0x8000;	//��������� 
						
						
				}
				else //��û�յ�0X0D
				{	
					if(Res==0x0d)
						UART5_RX_STA|=0x4000;
					else
					{
						UART5_RX_BUF[UART5_RX_STA&0X3FFF]=Res ;
						UART5_RX_STA++;
						if(UART5_RX_STA>(UART5_RXBUF_SIZE-1))
							UART5_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
					}		 
				}
			}
			
		#elif (UART5_RX_MODE == 2)        //RS485����ģʽ
	
			if(UART5_RX_STA<UART5_RXBUF_SIZE)
			{
				UART5_RX_BUF[UART5_RX_STA]=Res;		//��¼���յ���ֵ
				UART5_RX_STA++;						//������������1 
			} 
			
		#else   //��ʱ���жϽ���
						//ͨ���жϽ�������2���ַ�֮���ʱ������100ms�������ǲ���һ������������.
						//���2���ַ����ռ������100ms,����Ϊ����1����������.Ҳ���ǳ���100msû�н��յ�
						//�κ�����,���ʾ�˴ν������.
						//���յ�������״̬
						//[15]:0,û�н��յ�����;1,���յ���һ������.
						//[14:0]:���յ������ݳ���
		
			if((UART5_RX_STA&(1<<15))==0)//�������һ������,��û�б�����,���ٽ�����������
			{ 
				if(UART5_RX_STA<UART5_RXBUF_SIZE)		//�����Խ�������
				{
					TIM_SetCounter(TIM5,0);//���������        				 
					if(UART5_RX_STA==0)
					{
						TIM_Cmd(TIM5, ENABLE);  //ʹ�ܶ�ʱ��6
					}
						 
					UART5_RX_BUF[UART5_RX_STA++]=Res;		//��¼���յ���ֵ	 
				}
				else 
				{
					UART5_RX_STA|=1<<15;					//ǿ�Ʊ�ǽ������
				} 
			}  	

		
		#endif
	} 
	
 #if UCOS_II_EN  
	OSIntExit();    	//�˳��ж�
	#endif
} 


void USART6_IRQHandler(void)                	//����6�жϷ������
{
	u8 Res;
#if UCOS_II_EN  //ʹ��UCOS����ϵͳ
	OSIntEnter();    
#endif

	if(USART_GetITStatus(USART6, USART_IT_RXNE) != RESET)  //�����ж�
	{		
		Res =USART_ReceiveData(USART6);//(USART6->DR);	//��ȡ���յ�������
		
		if(UART6_RX_STA<64)
		{
			UART6_RX_BUF[UART6_RX_STA]=Res;		//��¼���յ���ֵ		
			UART6_RX_STA++;						//������������1 
		} 
		
		
		
	/*	#if (UART6_RX_MODE == 1)          //(���յ������ݱ�����0x0d 0x0a��β)
			if((UART6_RX_STA&0x8000)==0)//����δ���
			{
				if(UART6_RX_STA&0x4000)//���յ���0x0d
				{
					if(Res!=0x0a)
						UART6_RX_STA=0;//���մ���,���¿�ʼ
					else 
						UART6_RX_STA|=0x8000;	//��������� 
				}
				else //��û�յ�0X0D
				{	
					if(Res==0x0d)
						UART6_RX_STA|=0x4000;
					else
					{
						UART6_RX_BUF[UART6_RX_STA&0X3FFF]=Res ;
						UART6_RX_STA++;
						if(UART6_RX_STA>(UART6_RXBUF_SIZE-1))
							UART6_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
					}		 
				}
			}
			
		#elif (UART6_RX_MODE == 2)        //RS485����ģʽ
	
			if(UART6_RX_STA<UART6_RXBUF_SIZE)
			{
				UART6_RX_BUF[UART6_RX_STA]=Res;		//��¼���յ���ֵ
				UART6_RX_STA++;						//������������1 
			} 
			
		#else   //��ʱ���жϽ���
						//ͨ���жϽ�������2���ַ�֮���ʱ������100ms�������ǲ���һ������������.
						//���2���ַ����ռ������100ms,����Ϊ����1����������.Ҳ���ǳ���100msû�н��յ�
						//�κ�����,���ʾ�˴ν������.
						//���յ�������״̬
						//[15]:0,û�н��յ�����;1,���յ���һ������.
						//[14:0]:���յ������ݳ���
		
			if((UART6_RX_STA&(1<<15))==0)//�������һ������,��û�б�����,���ٽ�����������
			{ 
				if(UART6_RX_STA<UART6_RXBUF_SIZE)		//�����Խ�������
				{
					TIM_SetCounter(TIM7,0);//���������        				 
					if(UART6_RX_STA==0)
					{
						TIM_Cmd(TIM7, ENABLE);  //ʹ�ܶ�ʱ��7
					}
						 
					UART6_RX_BUF[UART6_RX_STA++]=Res;		//��¼���յ���ֵ	 
				}
				else 
				{
					UART6_RX_STA|=1<<15;					//ǿ�Ʊ�ǽ������
				} 
			}  	

		
		#endif     */
	} 
	
 #if UCOS_II_EN  
	OSIntExit();    	//�˳��ж�
	#endif
} 
