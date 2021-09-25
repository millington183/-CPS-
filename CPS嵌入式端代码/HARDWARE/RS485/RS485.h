#ifndef __RS485_
#define __RS485_
#include "sys.h"

#define RS485_TX_EN		PEout(6)	//485模式控制.0,接收;1,发送.
//如果想串口中断接收，设置EN_USART6_RX为1，否则设置为0


/***********************************************************************************
* Function: RS485_DirPin_Init;
*
* Description: RS485控制引脚初始化函数;
*              
* Input:  none;
*
* Output: none;
*
* Return: none;
*
* Note:   none;
************************************************************************************/

void RS485_DirPin_Init(void);

/***********************************************************************************
* Function: RS485_Send_Data;
*
* Description: RS485发送len个字节;
*           
* Input:  buf:发送区首地址; 
*         len:发送的字节数(为了和本代码的接收匹配,这里建议不要超过UART5_RXBUF_SIZE个字节);
*      		
* Return: none ;
*
* Note:   
*       
************************************************************************************/

void RS485_Send_Data(u8 *buf,u8 len);

/***********************************************************************************
* Function: RS485_Send_Data;
*
* Description: RS485查询接收到的数据;
*           
* Input:  buf:接收缓存首地址;
*         len:读到的数据长度;
*      		
* Return: none ;
*
* Note:   
*       
************************************************************************************/

void RS485_Receive_Data(u8 *buf,u8 *len);

/***********************************************************************************
* Function: TempData;
*
* Description: RS485接收到的数据转换为显示的数据;
*           
* Input:  data:接收缓存首地址;
*         Tdata:数据转换后存放的数组;
*      		
* Return: none ;
*
* Note:   
*       
************************************************************************************/

void TempData(u8 *data, char *TData);


/***********************************************************************************
* Function: HumiDityData;
*
* Description: RS485接收到的数据转换为显示的数据;
*           
* Input:  data:接收缓存首地址;
*         Tdata:数据转换后存放的数组;
*      		
* Return: none ;
*
* Note:   
*       
************************************************************************************/


void HumiDityData(u8 *data, u8 *TData);
/***********************************************************************************
* Function: PMData;
*
* Description: RS485接收到的数据转换为显示的数据;
*           
* Input:  data:接收缓存首地址;
*         Tdata:数据转换后存放的数组;
*      		
* Return: none ;
*
* Note:   
*       
************************************************************************************/

void PMData(u8 *data, char *TData);

#endif


