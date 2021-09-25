/************************************************************************************
*  Copyright (c), 2019, 江西理工大学
*            All rights reserved.
*
* http:  www.jxust.edu.cn
* Email: 
*
* File name: const.h
* Project  : STM32F4XX系列模块软件
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  智慧工厂研究所
* Version: 1.0
* Date:    2019.12.12				
* Email:  
* 
* Description: 本文件负责整个软件全局常量定义, 用户不可更改;
*
* Others: 本文件的的任何定义都不可修改,否则出错!
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
#ifndef __CONST_H 
#define __CONST_H 


/*************************************************************************************/
//  常用数据类型定义, 以下定义绝对不能修改
/*************************************************************************************/
#define  null    0
#define  NULL    0
#define  false   0
#define  true    1
#define  OFF     0
#define  ON      1
#define  CLOSE   0
#define  OPEN    1
#define  RSP_OK	 0xff

/*************************************************************************************/
//  数据类型定义, 以下定义绝对不能修改
/*************************************************************************************/
typedef unsigned char  INT8U;      // 8位无符号数                          
typedef signed   char  INT8S;      // 8位有符号数                         
typedef unsigned short INT16U;     // 16位无符号数                            
typedef signed   short INT16S;     // 16位有符号数                          
typedef unsigned int   INT32U;     // 32位无符号数                            
typedef signed   int   INT32S;     // 32位有符号数 
typedef unsigned long long INT64U; // 64位无符号数                            
typedef long long      INT64S;     // 64位有符号数                        
typedef float          FP32;       // 单精度浮点数                    
typedef double         FP64;       // 双精度浮点数 

typedef  void  (*FUNCTION_VOID)(void);  

// 32位数组合结构
typedef union 
{
    struct 
    {
        unsigned char c0;   // LSB
        unsigned char c1;   
        unsigned char c2;   
        unsigned char c3;   // MSB
    }chars;

    struct
    {
        unsigned short w0;  // LSW 
        unsigned short w1;  // MSW
    }ints;

    unsigned int d;         // 无符号32位
	int          s;         // 有符号32位
}INT32_TypeDef;

// 16位数组合结构
typedef union  
{
    struct 
    {
        unsigned char c0;   // LSB
		unsigned char c1;   // MSB 
    } chars;   
    unsigned short d;       // 无符号16位
    short          s;       // 有符号16位
}INT16_TypeDef;

#define EXRAM __attribute__ ((section ("RW_RAM1")))	   //用EXRAM将变量定义到外部RAM中, 只有在核心模块STM32F103ZE中使用
#define CCRAM __attribute__ ((section ("CCM_IRAM")))   //用CCRAM将变量定义到外部RAM中, 只有在核心模块STM32F407VE中使用  

/*************************************************************************************/
//  出错代码定义, 以下定义绝对不能修改
/*************************************************************************************/
#define  ERR_OK   	 0	  // 正确
#define  ERR_TRUE    0	  // 成功
#define  ERR_FALSE   1	  // 失败
#define  ERR_TIMEOUT 2	  // 超时错误
#define  ERR_PARA	 3	  // 函数参数错误
#define  ERR_CRC     4	  // CRC校验错误
#define  ERR_HWID    5    // 硬件识别错误
#define  ERR_NOINIT  6    // 相关硬件未初始化
#define  ERR_NOFIND  7    // 没有发现


#endif

/***********************************************************************************/
// 文件结束
/***********************************************************************************/
