#ifndef __UART_
#define __UART_

#include "sys.h"
#include "stdio.h"
#include "stdarg.h"
#include "stm32f4xx_conf.h"
#include "PIONEER_Config.h"
//#include "UserVars.h"



//extern u8  UART1_RX_BUF[UART1_RXBUF_SIZE]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
//extern u8  UART2_RX_BUF[UART2_RXBUF_SIZE];
//extern u8  UART3_RX_BUF[UART3_RXBUF_SIZE];
//extern u8  UART4_RX_BUF[UART4_RXBUF_SIZE];
//extern u8  UART5_RX_BUF[UART5_RXBUF_SIZE];
//extern u8  UART6_RX_BUF[UART6_RXBUF_SIZE];

//extern u16 UART1_RX_STA;         		//����״̬���	
//extern u16 UART2_RX_STA; 
//extern u16 UART3_RX_STA; 
//extern u16 UART4_RX_STA; 
//extern u16 UART5_RX_STA; 
//extern u16 UART6_RX_STA; 

/***********************************************************************************
* Function: Uartx_Init;
*
* Description: Uart��ʼ������;
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
void Uart_Write(INT8U id, INT8U *buf, INT16U len);

void UART_SendByte(unsigned char Send_Dat);
unsigned char UART_RecByte(void);



     //���ڽ���ʾ��
//if(UART4_RX_STA&0x8000)
//{					   
//	len=UART4_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
    //�û�����



//	UART4_RX_STA=0;  //�ڴ�λ�ñ��뽫����������ʼ��Ϊ�� 
//}



#endif

