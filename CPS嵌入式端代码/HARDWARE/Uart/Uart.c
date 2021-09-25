#include "Uart.h"
#include "sys.h"

#include "string.h"
#include "MC_Print_inc.h"
////////////////////////////////////////////////////////////////////////////////// 	 
//如果使用ucos,则包括下面的头文件即可.
#if UCOS_II_EN
#include "includes.h"					//ucos 使用	  
#endif
//////////////////////////////////////////////////////////////////////////////////	 

 //注意,读取USARTx->SR能避免莫名其妙的错误  	


#if DEBUG_EN > 0
	#pragma import(__use_no_semihosting)             
	//标准库需要的支持函数                 
	struct __FILE 
	{ 
		int handle; 
	}; 

	FILE __stdout;       
	//定义_sys_exit()以避免使用半主机模式    
	void _sys_exit(int x) 
	{ 
		x = x; 
	} 
	//重定义fputc函数 
	int fputc(int ch, FILE *f)
	{
		switch(DEBUG_UART)
		{
			case UART1_ID:
				while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
				USART1->DR = (u8) ch;
				break;
			case UART2_ID:
				while((USART2->SR&0X40)==0);//循环发送,直到发送完毕   
				USART2->DR = (u8) ch;
				break;
			case UART3_ID:
				while((USART3->SR&0X40)==0);//循环发送,直到发送完毕   
				USART3->DR = (u8) ch;
				break;
			case UART4_ID:
				while((UART4->SR&0X40)==0);//循环发送,直到发送完毕   
				UART4->DR = (u8) ch;
				break;
			case UART5_ID:
				while((UART5->SR&0X40)==0);//循环发送,直到发送完毕   
				UART5->DR = (u8) ch;
				break;
			case UART6_ID:
				while((USART6->SR&0X40)==0);//循环发送,直到发送完毕   
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
* Description: 发送一个数据块到发送缓存中;
*           
* Input:  id,  UART索引标识(UART1_ID~UART6_ID);
*         *p,  发送数据块指针; 
*         len, 发送数据块长度;
*      		
* Return: none ;
*
* Note:   该函数只是将数据发送缓存中,UART会立即启动发送数据，但函数返回时并不意味着
*         数据已经发送完成；
************************************************************************************/
void Uart_Write(INT8U id, INT8U *buf, INT16U len)
{
	INT8U t;
	switch(id)
	{
		case UART1_ID:
			for(t=0;t<len;t++)		//循环发送数据
			{
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET); //等待发送结束		
				USART_SendData(USART1,buf[t]); //发送数据
			}	 
			while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET); //等待发送结束	
			break;
		case UART2_ID:
			for(t=0;t<len;t++)		//循环发送数据
			{
				while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET); //等待发送结束		
				USART_SendData(USART2,buf[t]); //发送数据
			}	 
			while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET); //等待发送结束	
			break;
		case UART3_ID:
			for(t=0;t<len;t++)		//循环发送数据
			{
				while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET); //等待发送结束		
				USART_SendData(USART3,buf[t]); //发送数据
			}	 
			while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET); //等待发送结束	
			break;
		case UART4_ID:
			for(t=0;t<len;t++)		//循环发送数据
			{
				while(USART_GetFlagStatus(UART4,USART_FLAG_TC)==RESET); //等待发送结束		
				USART_SendData(UART4,buf[t]); //发送数据
			}	 
			while(USART_GetFlagStatus(UART4,USART_FLAG_TC)==RESET); //等待发送结束	
			break;
		case UART5_ID:
			for(t=0;t<len;t++)		//循环发送数据
			{
				while(USART_GetFlagStatus(UART5,USART_FLAG_TC)==RESET); //等待发送结束		
				USART_SendData(UART5,buf[t]); //发送数据
			}	 
			while(USART_GetFlagStatus(UART5,USART_FLAG_TC)==RESET); //等待发送结束	
			break;
		case UART6_ID:
			for(t=0;t<len;t++)		//循环发送数据
			{
				while(USART_GetFlagStatus(USART6,USART_FLAG_TC)==RESET); //等待发送结束		
				USART_SendData(USART6,buf[t]); //发送数据
			}	 
			while(USART_GetFlagStatus(USART6,USART_FLAG_TC)==RESET); //等待发送结束	
			break;			
			
		default: ;
	}
			
}








//初始化IO 串口1 
void Uart1_Init(void)
{
   //GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //使能GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//使能USART1时钟
 
	//串口1对应引脚复用映射
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1); //GPIOA9复用为USART1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); //GPIOA10复用为USART1
	
	//USART1端口配置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; //GPIOA9与GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化PA9，PA10

   //USART1 初始化设置
	USART_InitStructure.USART_BaudRate = UART1_BAUD;//波特率设置
	USART_InitStructure.USART_WordLength = UART1_WORD_LENGTH;//数据格式
	USART_InitStructure.USART_StopBits = UART1_STOP_BITS;//停止位
	USART_InitStructure.USART_Parity = UART1_PARITY;//奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
	USART_Init(USART1, &USART_InitStructure); //初始化串口1
	
	USART_Cmd(USART1, ENABLE);  //使能串口1 
	
	USART_ClearFlag(USART1, USART_FLAG_TC);
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启相关中断

	//Usart1 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;		//响应优先级0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、


	
}

//初始化IO 串口2 
void Uart2_Init(void)
{
   //GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //使能GPIOA时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//使能USART2时钟
 
	//串口2对应引脚复用映射
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2); //GPIOA2复用为USART2
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2); //GPIOA3复用为USART2
	
	//USART2端口配置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3; //GPIOA2与GPIOA3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化PA2，PA3

   //USART2 初始化设置
	USART_InitStructure.USART_BaudRate = UART2_BAUD;//波特率设置
	USART_InitStructure.USART_WordLength = UART2_WORD_LENGTH;//数据格式
	USART_InitStructure.USART_StopBits = UART2_STOP_BITS;//停止位
	USART_InitStructure.USART_Parity = UART2_PARITY;//奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
	USART_Init(USART2, &USART_InitStructure); //初始化串口2
	
	USART_Cmd(USART2, ENABLE);  //使能串口2 
	
	USART_ClearFlag(USART2, USART_FLAG_TC);
		
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启相关中断

	//Usart2 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;//串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;		//响应优先级1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、


	
}

//初始化IO 串口3 
void Uart3_Init(void)
{
   //GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE); //使能GPIOB时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);//使能USART3时钟
 
	//串口1对应引脚复用映射
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3); //GPIOB10复用为USART3
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3); //GPIOB11复用为USART3
	
	//USART3端口配置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; //GPIOB10与GPIOB11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOB,&GPIO_InitStructure); //初始化PB10，PB11

   //USART3 初始化设置
	USART_InitStructure.USART_BaudRate = UART3_BAUD;//波特率设置
	USART_InitStructure.USART_WordLength = UART3_WORD_LENGTH;//数据格式
	USART_InitStructure.USART_StopBits = UART3_STOP_BITS;//停止位
	USART_InitStructure.USART_Parity = UART3_PARITY;//奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
	USART_Init(USART3, &USART_InitStructure); //初始化串口3
	
	USART_Cmd(USART3, ENABLE);  //使能串口3 
	
	USART_ClearFlag(USART3, USART_FLAG_TC);
		
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启相关中断

	//Usart3 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;//串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;		//响应优先级2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、

	
}

//初始化IO 串口4
void Uart4_Init(void)
{
   //GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE); //使能GPIOC时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);//使能UART4时钟
 
	//串口4对应引脚复用映射
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource10,GPIO_AF_UART4); //GPIOC10复用为UART4
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource11,GPIO_AF_UART4); //GPIOC11复用为UART4
	
	//USART4端口配置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; //GPIOC10与GPIOC11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOC,&GPIO_InitStructure); //初始化PC19，PC11

   //UART4 初始化设置
	USART_InitStructure.USART_BaudRate = UART4_BAUD;//波特率设置
	USART_InitStructure.USART_WordLength = UART4_WORD_LENGTH;//数据格式
	USART_InitStructure.USART_StopBits = UART4_STOP_BITS;//停止位
	USART_InitStructure.USART_Parity = UART4_PARITY;//奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
	USART_Init(UART4, &USART_InitStructure); 	
//初始化串口4
	
	USART_Cmd(UART4, ENABLE);  //使能串口4 
	
	USART_ClearFlag(UART4, USART_FLAG_TC);
		
	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);//开启相关中断

	//Usart4 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;//串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//响应优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、

	
}

//初始化IO 串口5
void Uart5_Init(void)
{
   //GPIO端口设置
	GPIO_InitTypeDef GPIOC_InitStructure;
	GPIO_InitTypeDef GPIOD_InitStructure;
	
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE); //使能GPIOC时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE); //使能GPIOD时钟
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);//使能UART5时钟
 
	//串口1对应引脚复用映射
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource12,GPIO_AF_UART5); //GPIOC12复用为UART5
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource2 ,GPIO_AF_UART5); //GPIOD2复用为UART5
	
	//UART5端口配置
	GPIOC_InitStructure.GPIO_Pin = GPIO_Pin_12; //GPIOC12
	GPIOC_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIOC_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIOC_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIOC_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOC,&GPIOC_InitStructure); //初始化PC12
	
	GPIOD_InitStructure.GPIO_Pin = GPIO_Pin_2; //GPIOD2
	GPIOD_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIOD_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIOD_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIOD_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOD,&GPIOD_InitStructure); //初始化PD2


   //UART5 初始化设置
	USART_InitStructure.USART_BaudRate = UART5_BAUD;//波特率设置
	USART_InitStructure.USART_WordLength = UART5_WORD_LENGTH;//数据格式
	USART_InitStructure.USART_StopBits = UART5_STOP_BITS;//停止位
	USART_InitStructure.USART_Parity = UART5_PARITY;//奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
	USART_Init(UART5, &USART_InitStructure); //初始化串口5
	
	USART_Cmd(UART5, ENABLE);  //使能串口5
	
	USART_ClearFlag(UART5, USART_FLAG_TC);
		
	USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);//开启相关中断

	//Usart5 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;//串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//响应优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、

	
}

//初始化IO 串口6 
void Uart6_Init(void)
{
   //GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE); //使能GPIOC时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6,ENABLE);//使能USART6时钟
 
	//串口6对应引脚复用映射
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_USART6); //GPIOC6复用为USART6
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_USART6); //GPIOC7复用为USART6
	
	//USART6端口配置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; //GPIOC6与GPIOC7
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOC,&GPIO_InitStructure); //初始化PC6，PC7

   //USART6 初始化设置
	USART_InitStructure.USART_BaudRate = UART6_BAUD;//波特率设置
	USART_InitStructure.USART_WordLength = UART6_WORD_LENGTH;//数据格式
	USART_InitStructure.USART_StopBits = UART6_STOP_BITS;//停止位
	USART_InitStructure.USART_Parity = UART6_PARITY;//奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
	USART_Init(USART6, &USART_InitStructure); //初始化串口1
	
	USART_Cmd(USART6, ENABLE);  //使能串口6 
	
	USART_ClearFlag(USART6, USART_FLAG_TC);
		
	USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);//开启相关中断

	//Usart6 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn;//串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;		//响应优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、

	
}


/*void UART_SendByte(unsigned char Send_Dat)
{
	USART_SendData(USART2,Send_Dat);         //向串口1发送数据
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//等待发送结束
}

unsigned char UART_RecByte(void)
{
	u8 Res;
	Res =USART_ReceiveData(USART2);
	return Res;
}*/


void UART_SendByte(unsigned char Send_Dat)
{
	USART_SendData(USART2,Send_Dat);         //向串口1发送数据
	while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//等待发送结束
}

/*unsigned char UART_RecByte(void)
{
	u8 Res;
	Res =USART_ReceiveData(USART2);
	return Res;
}*/


