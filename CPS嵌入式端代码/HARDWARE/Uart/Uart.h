#ifndef __UART_
#define __UART_

#include "sys.h"
#include "stdio.h"
#include "stdarg.h"
#include "stm32f4xx_conf.h"
#include "PIONEER_Config.h"
//#include "UserVars.h"



//extern u8  UART1_RX_BUF[UART1_RXBUF_SIZE]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
//extern u8  UART2_RX_BUF[UART2_RXBUF_SIZE];
//extern u8  UART3_RX_BUF[UART3_RXBUF_SIZE];
//extern u8  UART4_RX_BUF[UART4_RXBUF_SIZE];
//extern u8  UART5_RX_BUF[UART5_RXBUF_SIZE];
//extern u8  UART6_RX_BUF[UART6_RXBUF_SIZE];

//extern u16 UART1_RX_STA;         		//接收状态标记	
//extern u16 UART2_RX_STA; 
//extern u16 UART3_RX_STA; 
//extern u16 UART4_RX_STA; 
//extern u16 UART5_RX_STA; 
//extern u16 UART6_RX_STA; 

/***********************************************************************************
* Function: Uartx_Init;
*
* Description: Uart初始化函数;
*              
* Input:  none;
*
* Output: none;
*
* Return: none;
*
* Note:   none;
************************************************************************************/

void Uart1_Init(void);
void Uart2_Init(void);
void Uart3_Init(void);
void Uart4_Init(void);
void Uart5_Init(void);
void Uart6_Init(void);



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
void Uart_Write(INT8U id, INT8U *buf, INT16U len);

void UART_SendByte(unsigned char Send_Dat);
unsigned char UART_RecByte(void);



     //串口接收示例
//if(UART4_RX_STA&0x8000)
//{					   
//	len=UART4_RX_STA&0x3fff;//得到此次接收到的数据长度
    //用户函数



//	UART4_RX_STA=0;  //在此位置必须将计数变量初始化为零 
//}



#endif

