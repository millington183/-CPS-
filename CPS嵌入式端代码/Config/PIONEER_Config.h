/************************************************************************************
*  Copyright (c), 2019, 江西理工大学
*            All rights reserved.
*
* http:  www.jxust.edu.cn
* Email: 
*
* File name: PIONEER_Config.h
* Project  : STM32F4XX系列模块软件
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  智慧工厂研究所
* Version: 1.00
* Date:    2019.12.12				
* Email:   
* 
* Description: 本文件是PIONEER工控板配置软件, 客户可根据模块实际应用进行更改;
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
#ifndef __PIONEER_CONFIG_H 
#define __PIONEER_CONFIG_H 
/************************************************************************************/
// 端口定义说明
/************************************************************************************/
/*
|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| 产品型号 | 端口标号、类型及说明         |  1脚  |  2脚  |  3脚  |  4脚  |  5脚  |  6脚  |  7脚  |  8脚  |  9脚  |  10脚  |     备注                                                      |
|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
|          | J11 : DI1-DI8, 光电隔离输入  |  COM  |  DI1  |  DI2  |  DI3  |  DI4  |  DI5  |  DI6  |  DI7  |  DI8  |   -    | 由MCU IO口直接驱动                                            |
|          |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
|  PIONEER | JP13: DO1-DO8 , 光电隔离输出 |  +OPT |  DO1  |  DO2  |  DO3  |  DO4  |  DO5  |  DO6  |  DO7  |  DO7  |   GND  | 由MCU IO口直接驱动入                                     |
|          |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
|          |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
|          | JP7: 4路RS232/TTL接口        |  GND  |  TX1  |  RX1  |  TX2  |  RX2  |  TX3  |  RX3  |  TX4  |  RX4   |   -    |TX1/2: RS232发送端口;RX1/2表示: RS232接收端口                 |
|          |                              |   地  | UART1转RS232  | UART2转RS232  | UART3转RS232  | UART4转RS232   |                                                               |
|          |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
|          | JP16: UART6接口 RS232/TTL电平| GND   |  RX5  |  TX5  |   -   |   -   |   -   |   -   |   -   |   -   |   -    | TX6: UART6发送端口; RX5: UART6接收端口                     |
|          |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
|          | JP10: 1路RS485接口,带光电隔离 |  A+   |   B-  |  GND  |   -   |   -   |   -   |   -   |   -   |    -  |   -    |UART6转RS485; GND,一般不接; RK1:断开                           |
|          |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
|          | JP14: 电源接口, 9-26V输入    |  VDD  |  GND  |   -                                                            |                                        |
|          |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
|          | JP26:NB-IoT                  |  UART6接口                                                                     |                                        |
|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
*/
/************************************************************************************/
// 引用外部头文件
/************************************************************************************/
#include "sys.h"
#include "const.h"
//#include "STM32F4_Head.h"
#include "exti.h"

/************************************************************************************/
// 板子常用信息定义, 用户可根据实际情况自行修改定义  
/************************************************************************************/
#define PRODUCT_MODEL  "PIONEER"             // 产品型号, 用户可根据实际需要修改这这个型号
#define PRODUCT_NAME   "PIONEER工业控制板"   // 产品名字, 用户可根据实际需要修改这这个产品名称

#define HW_VERSION     110          // 硬件版本V1.10

#define SW_VERSION     110          // 软件版本V1.10
#define SW_DATE        "2019.11.12"   // 软件版本生成日期

/************************************************************************************/
// UCOS-II 使能定义 
// 在有UCOS-II下, 请设置成1; 在无UCOS-II下, 请设置成0; 
/************************************************************************************/
#define UCOS_II_EN          1	    // 1:使能UCOS-II; 0：不使用UCOS-II;

#define  MODULE_CLASS STM32F407XX       

/************************************************************************************/
// 系统任务运行选择 
// 用户可以在以下选项中设定1，使能该任务运行，或设定0，关闭该任务运行
/************************************************************************************/
#if (UCOS_II_EN > 0)
#define TASK_IO_EN      	       0	    // IO测试任务：       0, 关闭; 1, 使能运行;
#define TASK_TEST_EN             0     // 测试任务  ：       0, 关闭; 1, 使能运行;
#define TASK_UART_EN             0	    // Uart测试任务：     0, 关闭; 1, 使能运行;

#define TASK_FLASH_EN						 0
#define TASK_DISPLAY_EN          1 
#define TASK_ENVIRONMENT_EN      1
#define TASK_NUMBER_EN           1
#define TASK_PRESSURE_EN         0
#define TASK_PLC_EN              1
#define TASK_SCAN_EN             1
#define TASK_QUALIFIED_EN        0
#define TASK_PROCESSING_EN       1



//NB 
#define TASK_NB_EN        		   1   // NB任务：        0, 关闭; 1, 使能运行;
#define NBTX_TASK_EN             1	    
#define NBRV_TASK_EN             1
#define UPDATE_TASK_EN           1



#endif

/************************************************************************************/
//  系统时钟定义、系统定时器定义  
/************************************************************************************/
//#define SYSCLK_HSE    50000000           // 高速外部时钟源，可根据硬件配置在3~25MHZ
//#define SYSCLK        SYSCLK_168MHZ      //SYSCLK_72MHz       // SYSCLK_25MHz //       	   // 系统时钟

//#define SYS_TICK_EN   1      // 系统定时器使能: 1：打开使能， 0：关闭
//#define SYS_TICK_T    10     //单位ms, 当系统时钟是72MHZ时, 最大是230ms;
                             //注意:   系统定时器定时时间, 注意应用操作系统时,这个时间固定为10ms
/************************************************************************************/
// DEBUG输出及串口配置
// 用户可以在以下选项中设定1，使能该部分调试打印信息输出，或设定0，关闭调试信息输出
/************************************************************************************/
#define DEBUG_EN 	       1         // DEBUG输出使能, 1：打开使能， 0：关闭
#define DEBUG_UART	     UART1_ID  // 选择DEBUG串口输出

#define DEBUG_APP_EN     1	     // 应用程序调试信息输出
/************************************************************************************/
// 内部独立看门狗参数配置 
//时间计算(大概):Tout=((4*2^prer)*rlr)/32 (ms).(默认为1S)
/************************************************************************************/
#define IWDG_EN        1         // 内部看门狗使能, 1：打开使能， 0：关闭
#define IWDG_PRER      4       //IWDG_PRER:分频数:0~7(只有低3位有效!)分频因子=4*2^prer.但最大值只能是256!
#define IWDG_RLR       500     //IWDG_RLR:自动重装载值,0~0XFFF.重装载寄存器值:低11位有效.
/************************************************************************************/
// EXTI0~EXTI19 输入中断配置
/************************************************************************************/
// EXTI0中断配置
#define EXTI0_EN        1		 // 中断或事件使能: 0,关闭中断和事件; 1, 打开中断; 2, 打开事件请求
#define EXTI0_PORT      E  // 在A, B, C, D, E, F, G, H, I中选择一个总线作为中断输入口; 
#define EXTI0_MODE      EXTI_Trigger_Rising		 //中断模式定义: EXTI_Trigger_Rising （上升沿触发）, EXTI_Trigger_Falling （下降沿触发）, EXTI_Trigger_Rising_Falling （任意电平触发）
// EXTI1中断配置
#define EXTI1_EN        1		 // 中断或事件使能: 0,关闭中断和事件; 1, 打开中断; 2, 打开事件请求
#define EXTI1_PORT      E  // 在A, B, C, D, E, F, G, H, I中选择一个总线作为中断输入口;
#define EXTI1_MODE      EXTI_Trigger_Rising		 //中断模式定义: EXTI_Trigger_Rising （上升沿触发）, EXTI_Trigger_Falling （下降沿触发）, EXTI_Trigger_Rising_Falling （任意电平触发）

// EXTI2中断配置
#define EXTI2_EN        1		 // 中断或事件使能: 0,关闭中断和事件; 1, 打开中断; 2, 打开事件请求
#define EXTI2_PORT      E  // 在A, B, C, D, E, F, G, H, I中选择一个总线作为中断输入口; 
#define EXTI2_MODE      EXTI_Trigger_Rising		 //中断模式定义: EXTI_Trigger_Rising （上升沿触发）, EXTI_Trigger_Falling （下降沿触发）, EXTI_Trigger_Rising_Falling （任意电平触发）

// EXTI3中断配置
#define EXTI3_EN        1		 // 中断或事件使能: 0,关闭中断和事件; 1, 打开中断; 2, 打开事件请求
#define EXTI3_PORT      D  // 在A, B, C, D, E, F, G, H, I中选择一个总线作为中断输入口;
#define EXTI3_MODE      EXTI_Trigger_Rising		 //中断模式定义: EXTI_Trigger_Rising （上升沿触发）, EXTI_Trigger_Falling （下降沿触发）, EXTI_Trigger_Rising_Falling （任意电平触发）

// EXTI4中断配置
#define EXTI4_EN        1		 // 中断或事件使能: 0,关闭中断和事件; 1, 打开中断; 2, 打开事件请求
#define EXTI4_PORT      D  // 在A, B, C, D, E, F, G, H, I中选择一个总线作为中断输入口;
#define EXTI4_MODE      EXTI_Trigger_Rising		 //中断模式定义: EXTI_Trigger_Rising （上升沿触发）, EXTI_Trigger_Falling （下降沿触发）, EXTI_Trigger_Rising_Falling （任意电平触发）

// EXTI5中断配置
#define EXTI5_EN        1		 // 中断或事件使能: 0,关闭中断和事件; 1, 打开中断; 2, 打开事件请求
#define EXTI5_PORT      D  // 在A, B, C, D, E, F, G, H, I中选择一个总线作为中断输入口;
#define EXTI5_MODE      EXTI_Trigger_Rising		 //中断模式定义: EXTI_Trigger_Rising （上升沿触发）, EXTI_Trigger_Falling （下降沿触发）, EXTI_Trigger_Rising_Falling （任意电平触发）

// EXTI6中断配置
#define EXTI6_EN        1		 // 中断或事件使能: 0,关闭中断和事件; 1, 打开中断; 2, 打开事件请求
#define EXTI6_PORT      D  // 在A, B, C, D, E, F, G, H, I中选择一个总线作为中断输入口;
#define EXTI6_MODE      EXTI_Trigger_Rising		 //中断模式定义: EXTI_Trigger_Rising （上升沿触发）, EXTI_Trigger_Falling （下降沿触发）, EXTI_Trigger_Rising_Falling （任意电平触发）

// EXTI7中断配置
#define EXTI7_EN        1		 // 中断或事件使能: 0,关闭中断和事件; 1, 打开中断; 2, 打开事件请求
#define EXTI7_PORT      D      // 在A, B, C, D, E, F, G, H, I中选择一个总线作为中断输入口;
#define EXTI7_MODE      EXTI_Trigger_Rising		 //中断模式定义: EXTI_Trigger_Rising （上升沿触发）, EXTI_Trigger_Falling （下降沿触发）, EXTI_Trigger_Rising_Falling （任意电平触发）

// EXTI8中断配置
#define EXTI8_EN        0		 // 中断或事件使能: 0,关闭中断和事件; 1, 打开中断; 2, 打开事件请求
#define EXTI8_PORT      D      // 在A, B, C, D, E, F, G, H, I中选择一个总线作为中断输入口; 
#define EXTI8_MODE      EXTI_Trigger_Rising		 //中断模式定义: EXTI_Trigger_Rising （上升沿触发）, EXTI_Trigger_Falling （下降沿触发）, EXTI_Trigger_Rising_Falling （任意电平触发）

// EXTI9中断配置
#define EXTI9_EN        0		 // 中断或事件使能: 0,关闭中断和事件; 1, 打开中断; 2, 打开事件请求
#define EXTI9_PORT      D  // 在A, B, C, D, E, F, G, H, I中选择一个总线作为中断输入口; 
#define EXTI9_MODE      EXTI_Trigger_Rising		 //中断模式定义: EXTI_Trigger_Rising （上升沿触发）, EXTI_Trigger_Falling （下降沿触发）, EXTI_Trigger_Rising_Falling （任意电平触发）

// EXTI10中断配置
#define EXTI10_EN       0 		 // 中断或事件使能: 0,关闭中断和事件; 1, 打开中断; 2, 打开事件请求
#define EXTI10_PORT     D     // 在PA10, PB10, PC10, PD10, PE10, PF10, PG10, PH10, PI10 中选择一个IO作为中断输入口; 
#define EXTI10_MODE     EXTI_Trigger_Rising		 //中断模式定义: EXTI_Trigger_Rising （上升沿触发）, EXTI_Trigger_Falling （下降沿触发）, EXTI_Trigger_Rising_Falling （任意电平触发）

// EXTI11中断配置
#define EXTI11_EN       0		 // 中断或事件使能: 0,关闭中断和事件; 1, 打开中断; 2, 打开事件请求
#define EXTI11_PORT     D     // 在A, B, C, D, E, F, G, H, I中选择一个总线作为中断输入口; 
#define EXTI11_MODE     EXTI_Trigger_Rising		 //中断模式定义: EXTI_Trigger_Rising （上升沿触发）, EXTI_Trigger_Falling （下降沿触发）, EXTI_Trigger_Rising_Falling （任意电平触发）

// EXTI12中断配置
#define EXTI12_EN       0		 // 中断或事件使能: 0,关闭中断和事件; 1, 打开中断; 2, 打开事件请求
#define EXTI12_PORT     D     // 在A, B, C, D, E, F, G, H, I中选择一个总线作为中断输入口; 
#define EXTI12_MODE     EXTI_Trigger_Rising		 //中断模式定义: EXTI_Trigger_Rising （上升沿触发）, EXTI_Trigger_Falling （下降沿触发）, EXTI_Trigger_Rising_Falling （任意电平触发）

// EXTI13中断配置
#define EXTI13_EN       0		 // 中断或事件使能: 0,关闭中断和事件; 1, 打开中断; 2, 打开事件请求
#define EXTI13_PORT     D     // 在A, B, C, D, E, F, G, H, I中选择一个总线作为中断输入口;
#define EXTI13_MODE     EXTI_Trigger_Rising		 //中断模式定义: EXTI_Trigger_Rising （上升沿触发）, EXTI_Trigger_Falling （下降沿触发）, EXTI_Trigger_Rising_Falling （任意电平触发）

// EXTI14中断配置
#define EXTI14_EN       1		 // 中断或事件使能: 0,关闭中断和事件; 1, 打开中断; 2, 打开事件请求
#define EXTI14_PORT     B     // 在A, B, C, D, E, F, G, H, I中选择一个总线作为中断输入口;
#define EXTI14_MODE     EXTI_Trigger_Rising		 //中断模式定义: EXTI_Trigger_Rising （上升沿触发）, EXTI_Trigger_Falling （下降沿触发）, EXTI_Trigger_Rising_Falling （任意电平触发）

// EXTI15中断配置
#define EXTI15_EN       1		 // 中断或事件使能: 0,关闭中断和事件; 1, 打开中断; 2, 打开事件请求
#define EXTI15_PORT     B     // 在A, B, C, D, E, F, G, H, I中选择一个总线作为中断输入口; 
#define EXTI15_MODE     EXTI_Trigger_Rising		 //中断模式定义: EXTI_Trigger_Rising （上升沿触发）, EXTI_Trigger_Falling （下降沿触发）, EXTI_Trigger_Rising_Falling （任意电平触发）


/************************************************************************************/
// UART1 参数配置
// 注意：如果定义了奇偶检验位，请将字长设置成9bit，最后一个bit是奇偶检验位
/************************************************************************************/
#define UART1_EN          1       // UART1使能, 1：打开使能， 0：关闭

#define UART1_RX_MODE     0       //选择串口接收模式 0：定时器查询接收  1：接收到的数据必须是0x0d 0x0a结尾  2：RS485模式
#define UART1_BAUD        19200  // 定义波特率，可以设置：1200，2400，4800，9600，19200，38400，57600，115200
#define UART1_WORD_LENGTH USART_WordLength_8b       // 定义数据字长,   USART_WordLength_8b: 8bit;   USART_WordLength_9b: 9bit;
#define UART1_STOP_BITS   USART_StopBits_1       // 定义停止位,     USART_StopBits_1: 1bit;   USART_StopBits_2: 2bit;    USART_StopBits_0_5: 0.5bit;  USART_StopBits_1_5 : 1.5bit;
#define UART1_PARITY      USART_Parity_No       // 定义奇偶检验位, USART_Parity_No: 无校验; USART_Parity_Even: 偶校验;  USART_Parity_Odd : 奇校验;

#define UART1_RXBUF_SIZE  256     // 定义接收缓存长度, 范围大于0, 根据自己实际需要设置, 不可以太大; 
#define UART1_TXBUF_SIZE  1024     // 定义发送缓存长度, 范围大于0, 根据自己实际需要设置, 不可以太大; 

/************************************************************************************/
// UART2 参数配置 
/************************************************************************************/
#define UART2_EN          1       // UART2使能, 1：打开使能， 0：关闭

#define UART2_RX_MODE     2       //选择串口接收模式   0：定时器查询接收  1：接收到的数据必须是0x0d 0x0a结尾  2：RS485模式
#define UART2_BAUD        9600  // 定义波特率，可以设置：1200，2400，4800，9600，19200，38400，57600，115200
#define UART2_WORD_LENGTH USART_WordLength_8b       // 定义数据字长,   USART_WordLength_8b: 8bit;   USART_WordLength_9b: 9bit;
#define UART2_STOP_BITS   USART_StopBits_1       // 定义停止位,     USART_StopBits_1: 1bit;   USART_StopBits_2: 2bit;    USART_StopBits_0_5: 0.5bit;  USART_StopBits_1_5 : 1.5bit;
#define UART2_PARITY      USART_Parity_No       // 定义奇偶检验位, USART_Parity_No: 无校验; USART_Parity_Even: 偶校验;  USART_Parity_Odd : 奇校验;

#define UART2_RXBUF_SIZE  256     // 定义接收缓存长度,范围大于0, 根据自己实际需要设置, 不可以太大; 
#define UART2_TXBUF_SIZE  256     // 定义发送缓存长度,范围大于0, 根据自己实际需要设置, 不可以太大; 

/************************************************************************************/
// UART3 参数配置 
// 注意：如果定义了奇偶检验位，请将字长设置成9bit，最后一个bit是奇偶检验位
/************************************************************************************/
#define UART3_EN          1       // UART3使能, 1：打开使能， 0：关闭

#define UART3_RX_MODE     0       //选择串口接收模式   0：定时器查询接收  1：接收到的数据必须是0x0d 0x0a结尾  2：RS485模式
#define UART3_BAUD        9600  // 定义波特率，可以设置：1200，2400，4800，9600，19200，38400，57600，115200
#define UART3_WORD_LENGTH USART_WordLength_8b       // 定义数据字长,   USART_WordLength_8b: 8bit;   USART_WordLength_9b: 9bit;
#define UART3_STOP_BITS   USART_StopBits_1       // 定义停止位,     USART_StopBits_1: 1bit;   USART_StopBits_2: 2bit;    USART_StopBits_0_5: 0.5bit;  USART_StopBits_1_5 : 1.5bit;
#define UART3_PARITY      USART_Parity_No       // 定义奇偶检验位, USART_Parity_No: 无校验; USART_Parity_Even: 偶校验;  USART_Parity_Odd : 奇校验;

#define UART3_RXBUF_SIZE  256     // 定义接收缓存长度, 范围大于0, 根据自己实际需要设置, 不可以太大; 
#define UART3_TXBUF_SIZE  256     // 定义发送缓存长度, 范围大于0, 根据自己实际需要设置, 不可以太大; 

/************************************************************************************/
// UART4 参数配置
// 注意：如果定义了奇偶检验位，请将字长设置成9bit，最后一个bit是奇偶检验位
/************************************************************************************/
#define UART4_EN          1       // UART4使能, 1：打开使能， 0：关闭

#define UART4_RX_MODE     1       //选择串口接收模式   0：定时器查询接收  1：接收到的数据必须是0x0d 0x0a结尾  2：RS485模式
#define UART4_BAUD        9600  // 定义波特率，可以设置：1200，2400，4800，9600，19200，38400，57600，115200
#define UART4_WORD_LENGTH USART_WordLength_8b       // 定义数据字长,   USART_WordLength_8b: 8bit;   USART_WordLength_9b: 9bit;
#define UART4_STOP_BITS   USART_StopBits_1       // 定义停止位,     USART_StopBits_1: 1bit;   USART_StopBits_2: 2bit;    USART_StopBits_0_5: 0.5bit;  USART_StopBits_1_5 : 1.5bit;
#define UART4_PARITY      USART_Parity_No       // 定义奇偶检验位, USART_Parity_No: 无校验; USART_Parity_Even: 偶校验;  USART_Parity_Odd : 奇校验;

#define UART4_RXBUF_SIZE  256     // 定义接收缓存长度, 范围大于0, 根据自己实际需要设置, 不可以太大; 
#define UART4_TXBUF_SIZE  256     // 定义发送缓存长度, 范围大于0, 根据自己实际需要设置, 不可以太大;  

/************************************************************************************/
// UART5 参数配置 （NB-IoT）
// 注意：如果定义了奇偶检验位，请将字长设置成9bit，最后一个bit是奇偶检验位
/************************************************************************************/
#define UART5_EN          1      // UART5使能, 1：打开使能， 0：关闭

#define UART5_RX_MODE     0       //选择串口接收模式   0：定时器查询接收  1：接收到的数据必须是0x0d 0x0a结尾  2：RS485模式
#define UART5_BAUD        9600  // 定义波特率，可以设置：1200，2400，4800，9600，19200，38400，57600，115200
#define UART5_WORD_LENGTH USART_WordLength_8b       // 定义数据字长,   USART_WordLength_8b: 8bit;   USART_WordLength_9b: 9bit;
#define UART5_STOP_BITS   USART_StopBits_1       // 定义停止位,     USART_StopBits_1: 1bit;   USART_StopBits_2: 2bit;    USART_StopBits_0_5: 0.5bit;  USART_StopBits_1_5 : 1.5bit;
#define UART5_PARITY      USART_Parity_No       // 定义奇偶检验位, USART_Parity_No: 无校验; USART_Parity_Even: 偶校验;  USART_Parity_Odd : 奇校验;

#define UART5_RXBUF_SIZE  256     // 定义接收缓存长度, 范围大于0, 根据自己实际需要设置, 不可以太大; 
#define UART5_TXBUF_SIZE  256     // 定义发送缓存长度, 范围大于0, 根据自己实际需要设置, 不可以太大; 

//NB参数设置
#define SEND_INTERVAL_SECOND      4									// 发送数据的时间间隔（秒）
#define SEND_INTERVAL_MILLISECOND 0									// 发送数据的时间间隔（毫秒）
#define UPDATE_TIME_DATA          40								// 设定存活期更新的时间的数据量（分钟）
#define ONLINE_SET_EN             1								  // 网络在线更新参数开关




/************************************************************************************/
// UART6 参数配置     RS485通讯口
// 注意：如果定义了奇偶检验位，请将字长设置成9bit，最后一个bit是奇偶检验位
/************************************************************************************/
#define UART6_EN          1      // UART6使能, 1：打开使能， 0：关闭

#define UART6_RX_MODE     2       //选择串口接收模式   0：定时器查询接收  1：接收到的数据必须是0x0d 0x0a结尾  2：RS485模式
#define UART6_BAUD        9600  // 定义波特率，可以设置：1200，2400，4800，9600，19200，38400，57600，115200
#define UART6_WORD_LENGTH USART_WordLength_8b       // 定义数据字长,   USART_WordLength_8b: 8bit;   USART_WordLength_9b: 9bit;
#define UART6_STOP_BITS   USART_StopBits_1       // 定义停止位,     USART_StopBits_1: 1bit;   USART_StopBits_2: 2bit;    USART_StopBits_0_5: 0.5bit;  USART_StopBits_1_5 : 1.5bit;
#define UART6_PARITY      USART_Parity_No       // 定义奇偶检验位, USART_Parity_No: 无校验; USART_Parity_Even: 偶校验;  USART_Parity_Odd : 奇校验;

#define UART6_RXBUF_SIZE  256     // 定义接收缓存长度, 范围大于0, 根据自己实际需要设置, 不可以太大; 
#define UART6_TXBUF_SIZE  256     // 定义发送缓存长度, 范围大于0, 根据自己实际需要设置, 不可以太大; 


/************************************************************************************/
//  定时器1配置 （高级控制定时器）
/************************************************************************************/
#define TIM1_EN       0		  // TIM1使能, 1：打开使能， 0：关闭


#define TIM2_PSC      8400                  //分频系数     （1~65536）
#define TIM2_ARR      100                  //自动重装载值  （1~65536）	
/************************************************************************************/

//因为系统初始化SystemInit函数里面已经初始化APB1的时钟为4分频，
//所以APB1的时钟为42M，而从STM32F4的内部时钟树图
//得知：当APB1的时钟分频数为1的时候，TIM2~7以及TIM12~14的时钟
//为APB1的时钟，而如果APB1的时钟分频数不为1，那么TIM2~7以及
//TIM12~14的时钟频率将为APB1时钟的两倍。因此，TIM3的时钟为84M，
//再根据我们设计的arr和psc的值，就可以计算中断时间了。

//通用定时器中断初始化
//arr：自动重装值。
//psc：时钟预分频数
//定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=定时器工作频率,单位:Mhz
//分频系数介于 1 到 65536 之间

//  定时器2配置   （通用定时器）
/************************************************************************************/
#define TIM2_EN       1		  // TIM2使能, 1：打开使能， 0：关闭

#if (UART1_EN>0 && UART1_RX_MODE==0)     //用于串口的定时查询  10ms中断一次
   //切勿修改内部参数
	#define TIM2_PSC      8400                  //分频系数     （1~65536）
	#define TIM2_ARR      100                  //自动重装载值  （1~65536）
#else 

	#define TIM2_PSC      8400                  //分频系数     （1~65536）
	#define TIM2_ARR      100                 //自动重装载值  （1~65536）	
#endif

/************************************************************************************/
//  定时器3配置     （通用定时器）
/************************************************************************************/
#define TIM3_EN       1	  // TIM3使能, 1：打开使能， 0：关闭


#if (UART2_EN>0 && UART2_RX_MODE==0)     //用于串口的定时查询  10ms中断一次
   //切勿修改内部参数
	#define TIM3_PSC      8400                  //分频系数     （1~65536）
	#define TIM3_ARR      5000                 //自动重装载值  （1~65536）
#else 

	#define TIM3_PSC      8400                  //分频系数     （1~65536）
	#define TIM3_ARR      5000                  //自动重装载值  （1~65536）	
#endif

/************************************************************************************/
//  定时器4配置 
/************************************************************************************/
#define TIM4_EN       1		  // TIM4使能, 1：打开使能， 0：关闭

#if (UART3_EN>0 && UART3_RX_MODE==0)     //用于串口的定时查询  10ms中断一次
   //切勿修改内部参数
	#define TIM4_PSC      8400                  //分频系数     （1~65536）
	#define TIM4_ARR      5000                  //自动重装载值  （1~65536）
#else 

	#define TIM4_PSC      8400                  //分频系数     （1~65536）
	#define TIM4_ARR      5000                  //自动重装载值  （1~65536）	
#endif

/************************************************************************************/
//  定时器5配置 
/************************************************************************************/
#define TIM5_EN       1		  // TIM5使能, 1：打开使能， 0：关闭


#if (UART4_EN>0 && UART4_RX_MODE==0)     //用于串口的定时查询  10ms中断一次
   //切勿修改内部参数
	#define TIM5_PSC      8400/*8400*/                  //分频系数     （1~65536）
	#define TIM5_ARR      1000/*3400*/                  //自动重装载值  （1~65536）
#else 

	#define TIM5_PSC      8400/*8400*/                  //分频系数     （1~65536）
	#define TIM5_ARR      1000/*3400*/                  //自动重装载值  （1~65536）	
#endif
                                  
/************************************************************************************/
//  定时器6配置 
/************************************************************************************/
#define TIM6_EN       1		  // TIM5使能, 1：打开使能， 0：关闭


#if (UART5_EN>0 && UART5_RX_MODE==0)     //用于串口的定时查询  10ms中断一次
   //切勿修改内部参数
	#define TIM6_PSC      8400                  //分频系数     （1~65536）
	#define TIM6_ARR      100                  //自动重装载值  （1~65536）
#else 

	#define TIM6_PSC      8400                  //分频系数     （1~65536）
	#define TIM6_ARR      100                  //自动重装载值  （1~65536）	
#endif
/************************************************************************************/
//  定时器7配置 
/************************************************************************************/
#define TIM7_EN       1		  // TIM5使能, 1：打开使能， 0：关闭


#if (UART6_EN>0 && UART6_RX_MODE==0)     //用于串口的定时查询  10ms中断一次
   //切勿修改内部参数
	#define TIM7_PSC      8400/*8400*/                  //分频系数     （1~65536）
	#define TIM7_ARR      3400/*100*/                  //自动重装载值  （1~65536）
#else 

	#define TIM7_PSC      8400/*8400*/                  //分频系数     （1~65536）
	#define TIM7_ARR      3400/*100*/                  //自动重装载值  （1~65536）	
#endif

/************************************************************************************/
//  定时器8配置 （高级控制定时器）
/************************************************************************************/
#define TIM8_EN       0		  // TIM8使能, 1：打开使能， 0：关闭


#define TIM8_PSC      8400                  //分频系数     （1~65536）
#define TIM8_ARR      100                  //自动重装载值  （1~65536）	
/************************************************************************************/
//  定时器9配置 
/************************************************************************************/
#define TIM9_EN       0		  // TIM9使能, 1：打开使能， 0：关闭


#define TIM9_PSC      8400                  //分频系数     （1~65536）
#define TIM9_ARR      100                  //自动重装载值  （1~65536）	

/************************************************************************************/
//  定时器10配置 
/************************************************************************************/
#define TIM10_EN       0		  // TIM10使能, 1：打开使能， 0：关闭


#define TIM10_PSC      8400                  //分频系数     （1~65536）
#define TIM10_ARR      100                  //自动重装载值  （1~65536）	

/************************************************************************************/
//  定时器11配置 
/************************************************************************************/
#define TIM11_EN       0		  // TIM11使能, 1：打开使能， 0：关闭


#define TIM11_PSC      8400                  //分频系数     （1~65536）
#define TIM11_ARR      100                  //自动重装载值  （1~65536）	

/************************************************************************************/
//  定时器12配置 
/************************************************************************************/
#define TIM12_EN       0		  // TIM12使能, 1：打开使能， 0：关闭


#define TIM12_PSC      8400                  //分频系数     （1~65536）
#define TIM12_ARR      100                  //自动重装载值  （1~65536）	

/************************************************************************************/
//  定时器13配置 
/************************************************************************************/
#define TIM13_EN       0		  // TIM13使能, 1：打开使能， 0：关闭


#define TIM13_PSC      8400                  //分频系数     （1~65536）
#define TIM13_ARR      100                  //自动重装载值  （1~65536）	
                                         

/************************************************************************************/
//  定时器14配置 
/************************************************************************************/
#define TIM14_EN       0		  // TIM14使能, 1：打开使能， 0：关闭

#define TIM14_PSC      8400                  //分频系数     （1~65536）
#define TIM14_ARR      100                  //自动重装载值  （1~65536）	
                                         

/************************************************************************************/
// MODBUS 主机通信配置
// 注意：ASCII模式暂时不支持
/************************************************************************************/
#define MODBUS_EN         0           // MODBUS通信使能：1, 使能;  0, 关闭;

#define MODBUS_MODE       0           // MODBUS通信模式：0, RTU;  1, ASCII码; 
#define MODBUS_CH         UART3_ID    // MODBUS通信通道：0: UART1_ID, 1: UART2_ID, 2: UART3_ID, 3: UART4_ID, 4: UART5_ID; 
#define MODBUS_ID         1           // MODBUS操作设备的通信地址ID, 默认1 

#define MODBUS_TIMEOUT    1000        // MODBUS通信超时时间, 单位ms;

/************************************************************************************/
// MODBUS 从机通信配置
// 注意：ASCII模式暂时不支持
/************************************************************************************/
#define MODBUS_SLAVE_EN        0           // MODBUS从机通信使能：1, 使能;  0, 关闭;

#define MODBUS_SLAVE_MODE      0           // MODBUS从机通信模式：0, RTU;  1, ASCII码; 
#define MODBUS_SLAVE_CH        UART4_ID    // MODBUS从机通信通道：0: UART1_ID, 1: UART2_ID, 2: UART3_ID, 3: UART4_ID, 4: UART5_ID; 
#define MODBUS_SLAVE_ID        1           // MODBUS从机通信地址码, 范围：1~255;

#define MODBUS_COILS_BASEADDR 	  10000        // 线圈寄存器基地址;
#define MODBUS_DISINPUT_BASEADDR  10000        // 离散输入量寄存器基地址;
#define MODBUS_HOLDREG_BASEADDR   10000        // 保持寄存器基地址;
#define MODBUS_INPUTREG_BASEADDR  10000        // 输入寄存器基地址;

#define MODBUS_MAX_COILS       32          // MODBUS从机最大线圈数量(读写,可用功能码:1,5,15);
#define MODBUS_MAX_DISINPUT    32          // MODBUS从机最大离散输入量(只读,可用功能码:2);
#define MODBUS_MAX_HOLDREG     16          // MODBUS从机最大保持寄存器(读写,可用功能码:3,6,16,23)数量;	 
#define MODBUS_MAX_INPUTREG    16          // MODBUS从机最大输入寄存器(只读,可用功能码:4)数量;

/************************************************************************************/
// SD卡配置
/************************************************************************************/
//#define SDCARD_EN              0          // SD卡使能：1, 使能;  0, 关闭;
/************************************************************************************/
// EEPROM 参数配置
/************************************************************************************/
#define EEPROM_EN          1          // EEPROM使能, 1：打开使能， 0：关闭

#define EEPROM_DEVICE      AT24C64    // 定义器件型号	
//#define EEPROM_FREQ        100000     // 读写时钟频率
/************************************************************************************/
// SPI1参数配置
/************************************************************************************/
#define SPI1_EN            1             // SPI使能,      1：打开使能， 0：关闭
#define SPI1_CKMODE        SPI_CKMODE3   // 时钟相位模式,  
#define SPI1_DIVCLK        SPI_DIVCLK_8  // SPI时钟分频系数

/************************************************************************************/
// RTC 参数配置 
/************************************************************************************/
#define RTC_EN           1          // RTC使能, 1：打开使能， 0：关闭

#define RTC_WKUPIT_EN    0         // RTC唤醒中断使能, 1：打开使能， 0：关闭	
#define RTC_ALRAIT_EN    0         // RTC闹钟A中断使能, 1：打开使能， 0：关闭	
#define RTC_ALRBIT_EN    0         // RTC闹钟B中断使能, 1：打开使能， 0：关闭	

/************************************************************************************/
// BKP 参数配置 
/************************************************************************************/
//#define BKP_EN          0          // BKP使能, 1：打开使能， 0：关闭


/************************************************************************************/
// SPI FLASH(W25QXX系列)配置
/************************************************************************************/
#define SPIFLASH_EN            1        // SPI FLASH使能：1, 使能;  0, 关闭;

#define SPIFLASH_MODE          0        // SPI FLASH操作方式：1, 利用FATFS文件系统进行读写;  0, 用SPI FLASH读写函数进行操作;
                                        // 注意:2种操作方式只能选择一种    

#define SPIFLASH_TYPE          W25QXX   // SPI FLASH类型定义: 只能定义W25QXX


#if (SPIFLASH_TYPE == W25QXX)
// 注意: 因为W25QXX是按扇区擦除, 所以建立文件系统就按扇区计算
#define W25QXX_MODEL           W25Q128   // SPI FLASH型号：W25Q80~W25Q128

#define W25QXX_SECTOR_SIZE	   4096      // W25QXX扇区大小 	

#define W25QXX_SECTOR_NUM	     2048      // SPI FLASH总扇区数
#define W25QXX_FATFS_SECTORNUM (2048-60) // 用于建立文件系统的扇区数(范围：0~W25QXX_SECTOR_NUM-1) 	

#define W25QXX_ZDY_STARTSECTOR W25QXX_FATFS_SECTORNUM                        // 用于自定义扇区起始扇区 
#define W25QXX_ZDY_SECTORNUM   (W25QXX_SECTOR_NUM - W25QXX_FATFS_SECTORNUM)	 // 用于自定义扇区数(范围：W25QXX_ZDY_STARTSECTOR ~ W25QXX_SECTOR_NUM-1) 	

#define W25QXX_PAGE_SIZE	   256      // W25QXX读写页大小 	

#endif

/************************************************************************************/
// 配置出错定义
/************************************************************************************/
#if ((UART1_EN == 1)&&(UART1_RX_MODE == 0)&&(TIM2_EN == 0))
  #error "ERROR: 使用UART1定时器接收模式必须使能TIM2_EN"
#endif

#if ((UART2_EN == 1)&&(UART2_RX_MODE == 0)&&(TIM3_EN == 0))
  #error "ERROR: 使用UART2定时器接收模式必须使能TIM3_EN"
#endif

#if ((UART3_EN == 1)&&(UART3_RX_MODE == 0)&&(TIM4_EN == 0))
  #error "ERROR: 使用UART3定时器接收模式必须使能TIM4_EN"
#endif

#if ((UART4_EN == 1)&&(UART4_RX_MODE == 0)&&(TIM5_EN == 0))
  #error "ERROR: 使用UART4定时器接收模式必须使能TIM5_EN"
#endif

#if ((UART5_EN == 1)&&(UART5_RX_MODE == 0)&&(TIM6_EN == 0))
  #error "ERROR: 使用UART5定时器接收模式必须使能TIM6_EN"
#endif

#if ((UART6_EN == 1)&&(UART6_RX_MODE == 0)&&(TIM7_EN == 0))
  #error "ERROR: 使用UART6定时器接收模式必须使能TIM7_EN"
#endif

#if ((SPIFLASH_EN == 1)&&(SPI1_EN == 0))
  #error "ERROR: 使用SPIFLASH必须使能SPI1_EN"
#endif






#endif
/***********************************************************************************/
// 文件结束
/***********************************************************************************/
