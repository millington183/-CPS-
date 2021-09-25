#include "RS485.h"
#include "PIONEER_Config.h"
#include "delay.h"
#include "UserVars.h"
#include "stdio.h"
#include "string.h"



void RS485_DirPin_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//使能GPIOC时钟
	//PC8推挽输出，485模式控制  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; //GPIOC8
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOE,&GPIO_InitStructure); //初始化PC8
	RS485_TX_EN = 0;
	
}


//RS485发送len个字节.
//buf:发送区首地址
//len:发送的字节数(为了和本代码的接收匹配,这里建议不要超过UART2_RXBUF_SIZE个字节)
void RS485_Send_Data(u8 *buf,u8 len)
{
	u8 t;
	RS485_TX_EN=1;			//设置为发送模式
  	for(t=0;t<len;t++)		//循环发送数据
	{
	  while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET); //等待发送结束		
	  USART_SendData(USART2,buf[t]); //发送数据
	}	 
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET); //等待发送结束		
	UART2_RX_STA=0;	  
	RS485_TX_EN=0;				//设置为接收模式	
}
//RS485查询接收到的数据
//buf:接收缓存首地址
//len:读到的数据长度
void RS485_Receive_Data(u8 *buf,u8 *len)
{
	u8 rxlen=UART2_RX_STA;
	u8 i=0;
	*len=0;				//默认为0
	delay_ms(10);		//等待10ms,连续超过10ms没有接收到一个数据,则认为接收结束
	if(rxlen==UART2_RX_STA&&rxlen)//接收到了数据,且接收完成了
	{
		for(i=0;i<rxlen;i++)
		{
			buf[i]=UART2_RX_BUF[i];	
		}		
		*len=UART2_RX_STA;	//记录本次数据长度
		UART2_RX_STA=0;		//清零
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

