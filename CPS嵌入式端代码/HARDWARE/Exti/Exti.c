#include "Exti.h"


void EXTIX_Init(EXTI_PARA *pPara)
{
	
	
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ��SYSCFGʱ��
	
 
	SYSCFG_EXTILineConfig(pPara->Port, pPara->id);//���ӵ��ж���
	
		
	switch(pPara->id)
	{
		case EXTI0_ID:
			  /* ����EXTI_Line0 */
			EXTI_InitStructure.EXTI_Line = EXTI_Line0;//LINE0
			EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
			EXTI_InitStructure.EXTI_Trigger = (EXTITrigger_TypeDef)pPara->Mode; //���ô�����ʽ
			EXTI_InitStructure.EXTI_LineCmd = ENABLE;//ʹ��LINE
			EXTI_Init(&EXTI_InitStructure);//����
					 
			NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;//�ⲿ�ж�0
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//��ռ���ȼ�
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;//�����ȼ�
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
			NVIC_Init(&NVIC_InitStructure);//����
		break;
		
		case EXTI1_ID:
			  /* ����EXTI_Line1 */
			EXTI_InitStructure.EXTI_Line = EXTI_Line1;//LINE1
			EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
			EXTI_InitStructure.EXTI_Trigger = (EXTITrigger_TypeDef)pPara->Mode; //���ô�����ʽ
			EXTI_InitStructure.EXTI_LineCmd = ENABLE;//ʹ��LINE
			EXTI_Init(&EXTI_InitStructure);//����
			
		 
			NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;//�ⲿ�ж�1
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//��ռ���ȼ�
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;//�����ȼ�
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
			NVIC_Init(&NVIC_InitStructure);//����
		break;
			
		case EXTI2_ID:
			  /* ����EXTI_Line2 */
			EXTI_InitStructure.EXTI_Line = EXTI_Line2;//LINE2
			EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
			EXTI_InitStructure.EXTI_Trigger = (EXTITrigger_TypeDef)pPara->Mode; //���ô�����ʽ
			EXTI_InitStructure.EXTI_LineCmd = ENABLE;//ʹ��LINE
			EXTI_Init(&EXTI_InitStructure);//����
			
		 
			NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;//�ⲿ�ж�2
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//��ռ���ȼ�
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;//�����ȼ�
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
			NVIC_Init(&NVIC_InitStructure);//����
		break;
			
		case EXTI3_ID:
			  /* ����EXTI_Line3 */
			EXTI_InitStructure.EXTI_Line = EXTI_Line3;//LIN3
			EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
			EXTI_InitStructure.EXTI_Trigger = (EXTITrigger_TypeDef)pPara->Mode; //���ô�����ʽ
			EXTI_InitStructure.EXTI_LineCmd = ENABLE;//ʹ��LINE3
			EXTI_Init(&EXTI_InitStructure);//����
			
		 
			NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;//�ⲿ�ж�3
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//��ռ���ȼ�
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;//�����ȼ�
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
			NVIC_Init(&NVIC_InitStructure);//����
		break;
		
		case EXTI4_ID:
			  /* ����EXTI_Line0 */
			EXTI_InitStructure.EXTI_Line = EXTI_Line4;//LINE4
			EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
			EXTI_InitStructure.EXTI_Trigger = (EXTITrigger_TypeDef)pPara->Mode; //���ô�����ʽ
			EXTI_InitStructure.EXTI_LineCmd = ENABLE;//ʹ��LINE4
			EXTI_Init(&EXTI_InitStructure);//����
			
		 
			NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;//�ⲿ�ж�4
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//��ռ���ȼ�
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;//�����ȼ�
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
			NVIC_Init(&NVIC_InitStructure);//����
		break;
		
		case EXTI5_ID:
			  /* ����EXTI_Line5*/
			EXTI_InitStructure.EXTI_Line = EXTI_Line5;//LINE5
			EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
			EXTI_InitStructure.EXTI_Trigger = (EXTITrigger_TypeDef)pPara->Mode; //���ô�����ʽ
			EXTI_InitStructure.EXTI_LineCmd = ENABLE;//ʹ��LINE5
			EXTI_Init(&EXTI_InitStructure);//����
			
		 
			NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//�ⲿ�ж�5~9
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//��ռ���ȼ�
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;//�����ȼ�
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
			NVIC_Init(&NVIC_InitStructure);//����
		break;
		
		case EXTI6_ID:
			  /* ����EXTI_Line6 */
			EXTI_InitStructure.EXTI_Line = EXTI_Line6;//LINE6
			EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
			EXTI_InitStructure.EXTI_Trigger = (EXTITrigger_TypeDef)pPara->Mode; //���ô�����ʽ
			EXTI_InitStructure.EXTI_LineCmd = ENABLE;//ʹ��LINE6
			EXTI_Init(&EXTI_InitStructure);//����
			
		 
			NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//�ⲿ�ж�5~9
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//��ռ���ȼ�
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;//�����ȼ�
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
			NVIC_Init(&NVIC_InitStructure);//����
		break;
		
		case EXTI7_ID:
			  /* ����EXTI_Line7 */
			EXTI_InitStructure.EXTI_Line = EXTI_Line7;//LINE7
			EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
			EXTI_InitStructure.EXTI_Trigger = (EXTITrigger_TypeDef)pPara->Mode; //���ô�����ʽ
			EXTI_InitStructure.EXTI_LineCmd = ENABLE;//ʹ��LINE7
			EXTI_Init(&EXTI_InitStructure);//����
			
		 
			NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//�ⲿ�ж�5~9
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//��ռ���ȼ�
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;//�����ȼ�
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
			NVIC_Init(&NVIC_InitStructure);//����
		break;
		
		case EXTI8_ID:
			  /* ����EXTI_Line8 */
			EXTI_InitStructure.EXTI_Line = EXTI_Line8;//LINE8
			EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
			EXTI_InitStructure.EXTI_Trigger = (EXTITrigger_TypeDef)pPara->Mode; //���ô�����ʽ
			EXTI_InitStructure.EXTI_LineCmd = ENABLE;//ʹ��LINE8
			EXTI_Init(&EXTI_InitStructure);//����
			
		 
			NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//�ⲿ�ж�5~9
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//��ռ���ȼ�
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;//�����ȼ�
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
			NVIC_Init(&NVIC_InitStructure);//����
		break;
		
		case EXTI9_ID:
			  /* ����EXTI_Line9 */
			EXTI_InitStructure.EXTI_Line = EXTI_Line9;//LINE9
			EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
			EXTI_InitStructure.EXTI_Trigger = (EXTITrigger_TypeDef)pPara->Mode; //���ô�����ʽ
			EXTI_InitStructure.EXTI_LineCmd = ENABLE;//ʹ��LINE9
			EXTI_Init(&EXTI_InitStructure);//����
			
		 
			NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//�ⲿ�ж�5~9
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//��ռ���ȼ�
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;//�����ȼ�
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
			NVIC_Init(&NVIC_InitStructure);//����
		break;
		
		case EXTI10_ID:
			  /* ����EXTI_Lin10 */
			EXTI_InitStructure.EXTI_Line = EXTI_Line10;//LINE10
			EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
			EXTI_InitStructure.EXTI_Trigger = (EXTITrigger_TypeDef)pPara->Mode; //���ô�����ʽ
			EXTI_InitStructure.EXTI_LineCmd = ENABLE;//ʹ��LINE10
			EXTI_Init(&EXTI_InitStructure);//����
			
		 
			NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//�ⲿ�ж�15~10
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//��ռ���ȼ�
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//�����ȼ�
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
			NVIC_Init(&NVIC_InitStructure);//����
		break;
		
		case EXTI11_ID:
			  /* ����EXTI_Lin11 */
			EXTI_InitStructure.EXTI_Line = EXTI_Line11;//LINE11
			EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
			EXTI_InitStructure.EXTI_Trigger = (EXTITrigger_TypeDef)pPara->Mode; //���ô�����ʽ
			EXTI_InitStructure.EXTI_LineCmd = ENABLE;//ʹ��LINE11
			EXTI_Init(&EXTI_InitStructure);//����
			
		 
			NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//�ⲿ�ж�15~10
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//��ռ���ȼ�
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//�����ȼ�
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
			NVIC_Init(&NVIC_InitStructure);//����
		break;
		
		case EXTI12_ID:
			  /* ����EXTI_Lin12 */
			EXTI_InitStructure.EXTI_Line = EXTI_Line12;//LINE12
			EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
			EXTI_InitStructure.EXTI_Trigger = (EXTITrigger_TypeDef)pPara->Mode; //���ô�����ʽ
			EXTI_InitStructure.EXTI_LineCmd = ENABLE;//ʹ��LINE2
			EXTI_Init(&EXTI_InitStructure);//����
			
		 
			NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//�ⲿ�ж�15~10
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//��ռ���ȼ�
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//�����ȼ�
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
			NVIC_Init(&NVIC_InitStructure);//����
		break;
		
		case EXTI13_ID:
			  /* ����EXTI_Lin13 */
			EXTI_InitStructure.EXTI_Line = EXTI_Line13;//LINE13
			EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
			EXTI_InitStructure.EXTI_Trigger = (EXTITrigger_TypeDef)pPara->Mode; //���ô�����ʽ
			EXTI_InitStructure.EXTI_LineCmd = ENABLE;//ʹ��LINE13
			EXTI_Init(&EXTI_InitStructure);//����
			
		 
			NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//�ⲿ�ж�15~10
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//��ռ���ȼ�
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//�����ȼ�
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
			NVIC_Init(&NVIC_InitStructure);//����
		break;
		
		case EXTI14_ID:
			  /* ����EXTI_Lin14 */
			EXTI_InitStructure.EXTI_Line = EXTI_Line14;//LINE14
			EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
			EXTI_InitStructure.EXTI_Trigger = (EXTITrigger_TypeDef)pPara->Mode; //���ô�����ʽ
			EXTI_InitStructure.EXTI_LineCmd = ENABLE;//ʹ��LINE14
			EXTI_Init(&EXTI_InitStructure);//����
			
		 
			NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//�ⲿ�ж�15~10
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//��ռ���ȼ�
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//�����ȼ�
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
			NVIC_Init(&NVIC_InitStructure);//����
		break;
		
		case EXTI15_ID:
			  /* ����EXTI_Lin15 */
			EXTI_InitStructure.EXTI_Line = EXTI_Line15;//LINE15
			EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
			EXTI_InitStructure.EXTI_Trigger = (EXTITrigger_TypeDef)pPara->Mode; //���ô�����ʽ
			EXTI_InitStructure.EXTI_LineCmd = ENABLE;//ʹ��LINE15
			EXTI_Init(&EXTI_InitStructure);//����
			
		 
			NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//�ⲿ�ж�15~10
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//��ռ���ȼ�
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//�����ȼ�
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
			NVIC_Init(&NVIC_InitStructure);//����
		break;
		
		
		default: ;
			
	}
	
	   
}
