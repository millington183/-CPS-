/************************************************************************************
*  Copyright (c), 2019, ��������ѧ
*            All rights reserved.
*
* http:  www.jxust.edu.cn
* Email: 
*
* File name: APP_Init.c
* Project  : STM32F4XXϵ��ģ�����
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  �ǻ۹����о���
* Version: 1.00
* Date:    2019.11.25			
* Email:   
* 
* Description: ���ļ���Ӧ�ó���������ĳ�ʼ������, ����PIONEER_Conifg.h������ý��г�ʼ��
*
* Others: none;
*
* Function List:
*		
* History:
*   1. Author:			wangzl  
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

#include "APP_Init.h"



/***********************************************************************************
* Function: TIMER_APPInit;
*
* Description: TIM2-TIM7Ӧ�ó�ʼ��;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
void TIM_Init(void)
{
	
	
	#if (TIM2_EN > 0)	
		TIM2_Init();
		TIM_Cmd(TIM2, DISABLE); //�رն�ʱ��
	  UART1_RX_STA=0;				//����
	#endif
	
	#if (TIM3_EN > 0)	
		TIM3_Init();
	  TIM_Cmd(TIM3, DISABLE); //�رն�ʱ��
	  UART2_RX_STA=0;				//����
	#endif
	
	#if (TIM4_EN > 0)	
		TIM4_Init();
  	TIM_Cmd(TIM4, DISABLE); //�رն�ʱ��
	  UART3_RX_STA=0;				//����
	#endif
	
	#if (TIM5_EN > 0)	
		TIM5_Init();
		TIM_Cmd(TIM5, DISABLE); //�رն�ʱ��
	  UART4_RX_STA=0;				//����
	#endif
	
	#if (TIM6_EN > 0)	
		TIM6_Init();
		TIM_Cmd(TIM6, DISABLE); //�رն�ʱ��
	  UART5_RX_STA=0;				//����
	#endif
	
	#if (TIM7_EN > 0)	
		TIM7_Init();
		TIM_Cmd(TIM7, DISABLE); //�رն�ʱ��
	  UART6_RX_STA=0;				//����
	#endif

}





/***********************************************************************************
* Function: Uart_Init;
*
* Description: UART1-UART6Ӧ�ó�ʼ������,RS485���ƹܽų�ʼ������
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/

void Uart_Init(void)
{
	
	#if (UART1_EN > 0)	
		Uart1_Init();
	#endif
	
	#if (UART2_EN > 0)	
		Uart2_Init();
	#endif
	
	#if (UART3_EN > 0)	
		Uart3_Init();
	#endif
	
	#if (UART4_EN > 0)	
		Uart4_Init();
	#endif
	
	#if (UART5_EN > 0)	
		Uart5_Init();
	#endif
	
	#if (UART6_EN > 0)	
		Uart6_Init();
	#endif
	#if ((UART1_RX_MODE == 2)||(UART2_RX_MODE == 2)||(UART3_RX_MODE == 2)||(UART4_RX_MODE == 2)||(UART5_RX_MODE == 2)||(UART6_RX_MODE == 2))	
		RS485_DirPin_Init();
	#endif
	
}

void IO_Init(void)
{
	 //IN_Init();
	 //OUT_Init();
	 //LED_Init();
	 //BEEP_Init();

}

/***********************************************************************************
* Function: RTC_APPInit;
*
* Description: RTCӦ�ó�ʼ������;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
#if (RTC_EN > 0)

	#define RTC_PWROFF_FLAG  0x5050    // RTC�ϵ��־
		
	void RTC_APPInit(void)
	{
		RTC_TimeTypeDef RTC_Time;
		RTC_DateTypeDef RTC_Date;
		
		INT8U flag;
		flag = RTCInit();    // RTC��ʼ��
		if (flag == ERR_TRUE)
		{
				#if (DEBUG_APP_EN == 1)   
				printf("RTC��ʼ��: OK\r\n");  
				#endif 
		}
		else
		{
				#if (DEBUG_APP_EN == 1)
				printf("RTC��ʼ��: ERROR\r\n");  
				#endif
		} 
		if(RTC_ReadBackupRegister(RTC_BKP_DR0)!=RTC_PWROFF_FLAG)		//�Ƿ��һ������?
		{
			
			RTC_Date.RTC_Year    = 20; //��
			RTC_Date.RTC_Month   = 1;  //��
			RTC_Date.RTC_Date    = 15; //��
			RTC_Date.RTC_WeekDay = 3;  //����
			
			RTC_Time.RTC_H12     = RTC_H12_AM;  //AM/PM����   �����õ�ʱ����24Сʱ��ʽ ��Ĭ�� RTC_H12_AM �Ϳ���
			RTC_Time.RTC_Hours   = 15;
			RTC_Time.RTC_Minutes = 28;
			RTC_Time.RTC_Seconds = 56;
			//��ʼ��ʱ��
			RTC_SetDate(RTC_Format_BIN,&RTC_Date);//��������   ��ע:����1��ѡ��RTC_Format_BIN��RTC_Format_BCD
			RTC_SetTime(RTC_Format_BIN,&RTC_Time);//����ʱ��		
		 
			RTC_WriteBackupRegister(RTC_BKP_DR0,RTC_PWROFF_FLAG);	//����Ѿ���ʼ������
		}
		
		#if (RTC_ALRAIT_EN > 0)
			//��������ʱ��(����������,24Сʱ��)
			//week:���ڼ�(1~7) @ref  RTC_Alarm_Definitions
			//hour,min,sec:Сʱ,����,����
			RTC_Set_Alarm(RTC_Alarm_A,2,5,30,0);		//		week,hour,min,sec;
		#endif
		#if (RTC_ALRBIT_EN > 0)
			//��������ʱ��(����������,24Сʱ��)
			//week:���ڼ�(1~7) @ref  RTC_Alarm_Definitions
			//hour,min,sec:Сʱ,����,����
			RTC_Set_Alarm(RTC_Alarm_B,2,5,30,0); //		week,hour,min,sec;
		#endif
		#if (RTC_WKUPIT_EN > 0)
			RTC_Set_WakeUp(RTC_WakeUpClock_CK_SPRE_16bits,1);		//����WAKE UP�ж�,1�����ж�һ��		
		#endif
		
	}
	
#endif
/***********************************************************************************
* Function: EXTI_APPInit;
*
* Description: �ⲿ�жϺ��¼�Ӧ�ó�ʼ������;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   ����������EXTI1~EXTI15 �����ж����ó�ʼ��;
************************************************************************************/
void EXTI_APPInit(void)    
{
    EXTI_PARA Para;

    #if (EXTI0_EN > 0)
    Para.id   = EXTI0_ID;
    Para.Mode = EXTI0_MODE;
    Para.Port  = EXTI0_PORT;
    EXTIX_Init((EXTI_PARA *)&Para);            // ��ʼ��EXTI0
    #endif
    
    #if (EXTI1_EN > 0)
    Para.id   = EXTI1_ID;
    Para.Mode = EXTI1_MODE;
    Para.Port  = EXTI1_PORT;
    EXTIX_Init((EXTI_PARA *)&Para);            // ��ʼ��EXTI1
    #endif
    
    #if (EXTI2_EN > 0)
    Para.id   = EXTI2_ID;
    Para.Mode = EXTI2_MODE;
    Para.Port  = EXTI2_PORT;
    EXTIX_Init((EXTI_PARA *)&Para);            // ��ʼ��EXTI2
    #endif
    
    #if (EXTI3_EN > 0)
    Para.id   = EXTI3_ID;
    Para.Mode = EXTI3_MODE;
    Para.Port  = EXTI3_PORT;
    EXTIX_Init((EXTI_PARA *)&Para);            // ��ʼ��EXTI3
    #endif
    
    #if (EXTI4_EN > 0)
    Para.id   = EXTI4_ID;
    Para.Mode = EXTI4_MODE;
    Para.Port  = EXTI4_PORT;
    EXTIX_Init((EXTI_PARA *)&Para);            // ��ʼ��EXTI4
    #endif
    
    #if (EXTI5_EN > 0)
    Para.id   = EXTI5_ID;
    Para.Mode = EXTI5_MODE;
    Para.Port  = EXTI5_PORT;
    EXTIX_Init((EXTI_PARA *)&Para);            // ��ʼ��EXTI5
    #endif
    
    #if (EXTI6_EN > 0)
    Para.id   = EXTI6_ID;
    Para.Mode = EXTI6_MODE;
    Para.Port  = EXTI6_PORT;
    EXTIX_Init((EXTI_PARA *)&Para);            // ��ʼ��EXTI6
    #endif
    #if (EXTI7_EN > 0)
    Para.id   = EXTI7_ID;
    Para.Mode = EXTI7_MODE;
    Para.Port  = EXTI7_PORT;
    EXTIX_Init((EXTI_PARA *)&Para);            // ��ʼ��EXTI7
    #endif
    
    #if (EXTI8_EN > 0)
    Para.id   = EXTI8_ID;
    Para.Mode = EXTI8_MODE;
    Para.Port  = EXTI8_PORT;
    EXTIX_Init((EXTI_PARA *)&Para);            // ��ʼ��EXTI8
    #endif
    
    #if (EXTI9_EN > 0)
    Para.id   = EXTI9_ID;
    Para.Mode = EXTI9_MODE;
    Para.Port  = EXTI9_PORT;
    EXTIX_Init((EXTI_PARA *)&Para);            // ��ʼ��EXTI9
    #endif
    
    #if (EXTI10_EN > 0)
    Para.id   = EXTI10_ID;
    Para.Mode = EXTI10_MODE;
    Para.Port  = EXTI10_PORT;
    EXTIX_Init((EXTI_PARA *)&Para);            // ��ʼ��EXTI10
    #endif
    
    #if (EXTI11_EN > 0)
    Para.id   = EXTI11_ID;
    Para.Mode = EXTI11_MODE;
    Para.Port  = EXTI11_PORT;
    EXTIX_Init((EXTI_PARA *)&Para);            // ��ʼ��EXTI11
    #endif
    
    #if (EXTI12_EN > 0)
    Para.id   = EXTI12_ID;
    Para.Mode = EXTI12_MODE;
    Para.Port  = EXTI12_PORT;
    EXTIX_Init((EXTI_PARA *)&Para);            // ��ʼ��EXTI12
    #endif
    
    #if (EXTI13_EN > 0)
    Para.id   = EXTI13_ID;
    Para.Mode = EXTI13_MODE;
    Para.Port  = EXTI13_PORT;
    EXTIX_Init((EXTI_PARA *)&Para);            // ��ʼ��EXTI13
    #endif
    
    #if (EXTI14_EN > 0)
    Para.id   = EXTI14_ID;
    Para.Mode = EXTI14_MODE;
    Para.Port  = EXTI14_PORT;
    EXTIX_Init((EXTI_PARA *)&Para);            // ��ʼ��EXTI14
    #endif
    
    #if (EXTI15_EN > 0)
    Para.id   = EXTI15_ID;
    Para.Mode = EXTI15_MODE;
    Para.Port  = EXTI15_PORT;
    EXTIX_Init((EXTI_PARA *)&Para);            // ��ʼ��EXTI15
    #endif    

    
    #if (DEBUG_APP_EN == 1)   
			printf("EXTI��ʼ��: OK\r\n");  
    #endif         
}





void Logo_Out(void)
{
    
	#if (DEBUG_APP_EN == 1)
		printf("\r\n\r\n******************************************************\r\n");
		printf("* Copyright (c), 2019, ��������ѧ\r\n");
		printf("*            All rights reserved.\r\n");
		printf("*\r\n");
		printf("* �����Ա: �ǻ۹����о���\r\n"); 
		printf("* ��Ʒ����: %s\r\n", PRODUCT_NAME);        
		printf("* ��Ʒ�ͺ�: %s\r\n", PRODUCT_MODEL);
		printf("* Ӳ���汾: %d.%d%d\r\n", HW_VERSION/100, (HW_VERSION%100)/10, HW_VERSION%10);
		printf("* ����汾: %d.%d%d\r\n", SW_VERSION/100, (SW_VERSION%100)/10, SW_VERSION%10);
		printf("* ��������: %s\r\n", SW_DATE);

		#if (UCOS_II_EN > 0)
			printf("*\r\n* ����ϵͳ: UCOS-II V2.86\r\n");
		#else
			printf("*\r\n* ����ϵͳ: ��\r\n");
		#endif
	
		printf("*\r\n* ��˾����:xiaoyunxie@126.com\r\n");
		printf("* ��˾��ַ:www.jxust.edu.cn\r\n");
		printf("*****************************************************\r\n");
	#endif    
}



/***********************************************************************************
* Function: API_Init;
*
* Description: �������ʼ������;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
void  API_Init(void)
{
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	Adc_Init();
	delay_init(168);
	#if (IWDG_EN > 0)           // IWDG����ʹ��
    IWDG_Init();              //IWDG��ʼ��
		IWDG_Feed();              //ι��
	#endif
	
	LED_Init();
	IO_Init();                  
	
	#if ((UART1_EN > 0)||(UART2_EN > 0)||(UART3_EN > 0)||(UART4_EN > 0)||(UART5_EN > 0)||(UART6_EN > 0)) // UART1-UART6����ʹ��
    Uart_Init();              // UART1-UART6Ӧ�ó�ʼ������;	
	#endif 
	
	#if ((TIM2_EN > 0)||(TIM3_EN > 0)||(TIM4_EN > 0)||(TIM5_EN > 0)||(TIM6_EN > 0)||(TIM7_EN > 0)) //TIM1-TIM14����ʹ��
    TIM_Init();              // ��ʱ��Ӧ�ó�ʼ��
	#endif
	
	//EXTI_APPInit();               // �ⲿ�жϳ�ʼ��
	Logo_Out();                  // ���logo��ӡ���
	
	#if (EEPROM_EN > 0 )
		EEPROM_Init();
		EEPROM_Check();
		if(EEPROM_Check()==1)
		{
			#if (DEBUG_APP_EN == 1)
				printf("EEPROM err");
			#endif
			
		}
		else
		{
			#if (DEBUG_APP_EN == 1)
				printf("EEPROM ok");
			#endif
		}
	#endif
	
	#if (SPI1_EN > 0 )
		SPI1_Init();
	#endif
	
	#if (SPIFLASH_EN > 0 )
		W25QXX_Init();
	#endif
	
	#if (RTC_EN > 0)
		RTC_APPInit();
	#endif
}


