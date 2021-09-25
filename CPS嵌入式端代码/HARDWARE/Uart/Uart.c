#include "Uart.h"
#include "sys.h"

#include "string.h"
#include "MC_Print_inc.h"
////////////////////////////////////////////////////////////////////////////////// 	 
//���ʹ��ucos,����������ͷ�ļ�����.
#if UCOS_II_EN
#include "includes.h"					//ucos ʹ��	  
#endif
//////////////////////////////////////////////////////////////////////////////////	 

 //ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���  	


#if DEBUG_EN > 0
	#pragma import(__use_no_semihosting)             
	//��׼����Ҫ��֧�ֺ���                 
	struct __FILE 
	{ 
		int handle; 
	}; 

	FILE __stdout;       
	//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
	void _sys_exit(int x) 
	{ 
		x = x; 
	} 
	//�ض���fputc���� 
	int fputc(int ch, FILE *f)
	{
		switch(DEBUG_UART)
		{
			case UART1_ID:
				while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
				USART1->DR = (u8) ch;
				break;
			case UART2_ID:
				while((USART2->SR&0X40)==0);//ѭ������,ֱ���������   
				USART2->DR = (u8) ch;
				break;
			case UART3_ID:
				while((USART3->SR&0X40)==0);//ѭ������,ֱ���������   
				USART3->DR = (u8) ch;
				break;
			case UART4_ID:
				while((UART4->SR&0X40)==0);//ѭ������,ֱ���������   
				UART4->DR = (u8) ch;
				break;
			case UART5_ID:
				while((UART5->SR&0X40)==0);//ѭ������,ֱ���������   
				UART5->DR = (u8) ch;
				break;
			case UART6_ID:
				while((USART6->SR&0X40)==0);//ѭ������,ֱ���������   
				USART6->DR = (u8) ch;
				break;
			
			 default: ;
		}
		     
		return ch;
	}
#endif

/***********************************************************************************
* Function: Uart_Write;
*
* Description: ����һ�����ݿ鵽���ͻ�����;
*           
* Input:  id,  UART������ʶ(UART1_ID~UART6_ID);
*         *p,  �������ݿ�ָ��; 
*         len, �������ݿ鳤��;
*      		
* Return: none ;
*
* Note:   �ú���ֻ�ǽ����ݷ��ͻ�����,UART�����������������ݣ�����������ʱ������ζ��
*         �����Ѿ�������ɣ�
************************************************************************************/
void Uart_Write(INT8U id, INT8U *buf, INT16U len)
{
	INT8U t;
	switch(id)
	{
		case UART1_ID:
			for(t=0;t<len;t++)		//ѭ����������
			{
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET); //�ȴ����ͽ���		
				USART_SendData(USART1,buf[t]); //��������
			}	 
			while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET); //�ȴ����ͽ���	
			break;
		case UART2_ID:
			for(t=0;t<len;t++)		//ѭ����������
			{
				while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET); //�ȴ����ͽ���		
				USART_SendData(USART2,buf[t]); //��������
			}	 
			while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET); //�ȴ����ͽ���	
			break;
		case UART3_ID:
			for(t=0;t<len;t++)		//ѭ����������
			{
				while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET); //�ȴ����ͽ���		
				USART_SendData(USART3,buf[t]); //��������
			}	 
			while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET); //�ȴ����ͽ���	
			break;
		case UART4_ID:
			for(t=0;t<len;t++)		//ѭ����������
			{
				while(USART_GetFlagStatus(UART4,USART_FLAG_TC)==RESET); //�ȴ����ͽ���		
				USART_SendData(UART4,buf[t]); //��������
			}	 
			while(USART_GetFlagStatus(UART4,USART_FLAG_TC)==RESET); //�ȴ����ͽ���	
			break;
		case UART5_ID:
			for(t=0;t<len;t++)		//ѭ����������
			{
				while(USART_GetFlagStatus(UART5,USART_FLAG_TC)==RESET); //�ȴ����ͽ���		
				USART_SendData(UART5,buf[t]); //��������
			}	 
			while(USART_GetFlagStatus(UART5,USART_FLAG_TC)==RESET); //�ȴ����ͽ���	
			break;
		case UART6_ID:
			for(t=0;t<len;t++)		//ѭ����������
			{
				while(USART_GetFlagStatus(USART6,USART_FLAG_TC)==RESET); //�ȴ����ͽ���		
				USART_SendData(USART6,buf[t]); //��������
			}	 
			while(USART_GetFlagStatus(USART6,USART_FLAG_TC)==RESET); //�ȴ����ͽ���	
			break;			
			
		default: ;
	}
			
}








//��ʼ��IO ����1 
void Uart1_Init(void)
{
   //GPIO�˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //ʹ��GPIOAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//ʹ��USART1ʱ��
 
	//����1��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1); //GPIOA9����ΪUSART1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); //GPIOA10����ΪUSART1
	
	//USART1�˿�����
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; //GPIOA9��GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOA,&GPIO_InitStructure); //��ʼ��PA9��PA10

   //USART1 ��ʼ������
	USART_InitStructure.USART_BaudRate = UART1_BAUD;//����������
	USART_InitStructure.USART_WordLength = UART1_WORD_LENGTH;//���ݸ�ʽ
	USART_InitStructure.USART_StopBits = UART1_STOP_BITS;//ֹͣλ
	USART_InitStructure.USART_Parity = UART1_PARITY;//��żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
	USART_Init(USART1, &USART_InitStructure); //��ʼ������1
	
	USART_Cmd(USART1, ENABLE);  //ʹ�ܴ���1 
	
	USART_ClearFlag(USART1, USART_FLAG_TC);
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//��������ж�

	//Usart1 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;		//��Ӧ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����


	
}

//��ʼ��IO ����2 
void Uart2_Init(void)
{
   //GPIO�˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //ʹ��GPIOAʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//ʹ��USART2ʱ��
 
	//����2��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2); //GPIOA2����ΪUSART2
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2); //GPIOA3����ΪUSART2
	
	//USART2�˿�����
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3; //GPIOA2��GPIOA3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOA,&GPIO_InitStructure); //��ʼ��PA2��PA3

   //USART2 ��ʼ������
	USART_InitStructure.USART_BaudRate = UART2_BAUD;//����������
	USART_InitStructure.USART_WordLength = UART2_WORD_LENGTH;//���ݸ�ʽ
	USART_InitStructure.USART_StopBits = UART2_STOP_BITS;//ֹͣλ
	USART_InitStructure.USART_Parity = UART2_PARITY;//��żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
	USART_Init(USART2, &USART_InitStructure); //��ʼ������2
	
	USART_Cmd(USART2, ENABLE);  //ʹ�ܴ���2 
	
	USART_ClearFlag(USART2, USART_FLAG_TC);
		
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//��������ж�

	//Usart2 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;//����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;		//��Ӧ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����


	
}

//��ʼ��IO ����3 
void Uart3_Init(void)
{
   //GPIO�˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE); //ʹ��GPIOBʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);//ʹ��USART3ʱ��
 
	//����1��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3); //GPIOB10����ΪUSART3
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3); //GPIOB11����ΪUSART3
	
	//USART3�˿�����
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; //GPIOB10��GPIOB11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOB,&GPIO_InitStructure); //��ʼ��PB10��PB11

   //USART3 ��ʼ������
	USART_InitStructure.USART_BaudRate = UART3_BAUD;//����������
	USART_InitStructure.USART_WordLength = UART3_WORD_LENGTH;//���ݸ�ʽ
	USART_InitStructure.USART_StopBits = UART3_STOP_BITS;//ֹͣλ
	USART_InitStructure.USART_Parity = UART3_PARITY;//��żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
	USART_Init(USART3, &USART_InitStructure); //��ʼ������3
	
	USART_Cmd(USART3, ENABLE);  //ʹ�ܴ���3 
	
	USART_ClearFlag(USART3, USART_FLAG_TC);
		
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//��������ж�

	//Usart3 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;//����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;		//��Ӧ���ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����

	
}

//��ʼ��IO ����4
void Uart4_Init(void)
{
   //GPIO�˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE); //ʹ��GPIOCʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);//ʹ��UART4ʱ��
 
	//����4��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource10,GPIO_AF_UART4); //GPIOC10����ΪUART4
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource11,GPIO_AF_UART4); //GPIOC11����ΪUART4
	
	//USART4�˿�����
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; //GPIOC10��GPIOC11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOC,&GPIO_InitStructure); //��ʼ��PC19��PC11

   //UART4 ��ʼ������
	USART_InitStructure.USART_BaudRate = UART4_BAUD;//����������
	USART_InitStructure.USART_WordLength = UART4_WORD_LENGTH;//���ݸ�ʽ
	USART_InitStructure.USART_StopBits = UART4_STOP_BITS;//ֹͣλ
	USART_InitStructure.USART_Parity = UART4_PARITY;//��żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
	USART_Init(UART4, &USART_InitStructure); 	
//��ʼ������4
	
	USART_Cmd(UART4, ENABLE);  //ʹ�ܴ���4 
	
	USART_ClearFlag(UART4, USART_FLAG_TC);
		
	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);//��������ж�

	//Usart4 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;//����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//��Ӧ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����

	
}

//��ʼ��IO ����5
void Uart5_Init(void)
{
   //GPIO�˿�����
	GPIO_InitTypeDef GPIOC_InitStructure;
	GPIO_InitTypeDef GPIOD_InitStructure;
	
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE); //ʹ��GPIOCʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE); //ʹ��GPIODʱ��
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);//ʹ��UART5ʱ��
 
	//����1��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource12,GPIO_AF_UART5); //GPIOC12����ΪUART5
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource2 ,GPIO_AF_UART5); //GPIOD2����ΪUART5
	
	//UART5�˿�����
	GPIOC_InitStructure.GPIO_Pin = GPIO_Pin_12; //GPIOC12
	GPIOC_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIOC_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIOC_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIOC_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOC,&GPIOC_InitStructure); //��ʼ��PC12
	
	GPIOD_InitStructure.GPIO_Pin = GPIO_Pin_2; //GPIOD2
	GPIOD_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIOD_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIOD_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIOD_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOD,&GPIOD_InitStructure); //��ʼ��PD2


   //UART5 ��ʼ������
	USART_InitStructure.USART_BaudRate = UART5_BAUD;//����������
	USART_InitStructure.USART_WordLength = UART5_WORD_LENGTH;//���ݸ�ʽ
	USART_InitStructure.USART_StopBits = UART5_STOP_BITS;//ֹͣλ
	USART_InitStructure.USART_Parity = UART5_PARITY;//��żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
	USART_Init(UART5, &USART_InitStructure); //��ʼ������5
	
	USART_Cmd(UART5, ENABLE);  //ʹ�ܴ���5
	
	USART_ClearFlag(UART5, USART_FLAG_TC);
		
	USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);//��������ж�

	//Usart5 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;//����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//��Ӧ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����

	
}

//��ʼ��IO ����6 
void Uart6_Init(void)
{
   //GPIO�˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE); //ʹ��GPIOCʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6,ENABLE);//ʹ��USART6ʱ��
 
	//����6��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_USART6); //GPIOC6����ΪUSART6
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_USART6); //GPIOC7����ΪUSART6
	
	//USART6�˿�����
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; //GPIOC6��GPIOC7
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOC,&GPIO_InitStructure); //��ʼ��PC6��PC7

   //USART6 ��ʼ������
	USART_InitStructure.USART_BaudRate = UART6_BAUD;//����������
	USART_InitStructure.USART_WordLength = UART6_WORD_LENGTH;//���ݸ�ʽ
	USART_InitStructure.USART_StopBits = UART6_STOP_BITS;//ֹͣλ
	USART_InitStructure.USART_Parity = UART6_PARITY;//��żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
	USART_Init(USART6, &USART_InitStructure); //��ʼ������1
	
	USART_Cmd(USART6, ENABLE);  //ʹ�ܴ���6 
	
	USART_ClearFlag(USART6, USART_FLAG_TC);
		
	USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);//��������ж�

	//Usart6 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn;//����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;		//��Ӧ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����

	
}


/*void UART_SendByte(unsigned char Send_Dat)
{
	USART_SendData(USART2,Send_Dat);         //�򴮿�1��������
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
}

unsigned char UART_RecByte(void)
{
	u8 Res;
	Res =USART_ReceiveData(USART2);
	return Res;
}*/


void UART_SendByte(unsigned char Send_Dat)
{
	USART_SendData(USART2,Send_Dat);         //�򴮿�1��������
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
}

/*unsigned char UART_RecByte(void)
{
	u8 Res;
	Res =USART_ReceiveData(USART2);
	return Res;
}*/


