#include "RS485.h"
#include "PIONEER_Config.h"
#include "delay.h"
#include "UserVars.h"
#include "stdio.h"
#include "string.h"



void RS485_DirPin_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//ʹ��GPIOCʱ��
	//PC8���������485ģʽ����  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; //GPIOC8
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //�������
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOE,&GPIO_InitStructure); //��ʼ��PC8
	RS485_TX_EN = 0;
	
}


//RS485����len���ֽ�.
//buf:�������׵�ַ
//len:���͵��ֽ���(Ϊ�˺ͱ�����Ľ���ƥ��,���ｨ�鲻Ҫ����UART2_RXBUF_SIZE���ֽ�)
void RS485_Send_Data(u8 *buf,u8 len)
{
	u8 t;
	RS485_TX_EN=1;			//����Ϊ����ģʽ
  	for(t=0;t<len;t++)		//ѭ����������
	{
	  while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET); //�ȴ����ͽ���		
	  USART_SendData(USART2,buf[t]); //��������
	}	 
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET); //�ȴ����ͽ���		
	UART2_RX_STA=0;	  
	RS485_TX_EN=0;				//����Ϊ����ģʽ	
}
//RS485��ѯ���յ�������
//buf:���ջ����׵�ַ
//len:���������ݳ���
void RS485_Receive_Data(u8 *buf,u8 *len)
{
	u8 rxlen=UART2_RX_STA;
	u8 i=0;
	*len=0;				//Ĭ��Ϊ0
	delay_ms(10);		//�ȴ�10ms,��������10msû�н��յ�һ������,����Ϊ���ս���
	if(rxlen==UART2_RX_STA&&rxlen)//���յ�������,�ҽ��������
	{
		for(i=0;i<rxlen;i++)
		{
			buf[i]=UART2_RX_BUF[i];	
		}		
		*len=UART2_RX_STA;	//��¼�������ݳ���
		UART2_RX_STA=0;		//����
	}
}

void TempData(u8 *data, char *TData)
{
	u32 t=0;
	u32  s,x;
	
	t=((data[5]<<8)+data[6]);									
	s=t/10;
	x=t%100;
	sprintf(TData,"%d.%d",s,x);
	
	printf("temp%s",TData);
}

void HumiDityData(u8 *data, u8 *TData)
{
	u32 t=0;
	u32  s,x;
	
	t=((data[3]<<8)+data[4]);
	s=t/10;
	x=t%100;
	sprintf((char *)TData,"%d.%d%%",s,x);
	
	printf("humi%s",TData);
}


void PMData(u8 *data, char *TData)
{
	u32 t=0;
	
	t=((data[11]<<8)+data[12]);
	sprintf(TData,"%d",t);
	printf("%d",t);
}

