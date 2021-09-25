/************************************************************************************
*  Copyright (c), 2019, ��������ѧ
*            All rights reserved.
*
* http:  www.jxust.edu.cn
* Email: 
*
* File name: const.h
* Project  : STM32F4XXϵ��ģ�����
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  �ǻ۹����о���
* Version: 1.0
* Date:    2019.12.12				
* Email:  
* 
* Description: ���ļ������������ȫ�ֳ�������, �û����ɸ���;
*
* Others: ���ļ��ĵ��κζ��嶼�����޸�,�������!
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
//  �����������Ͷ���, ���¶�����Բ����޸�
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
//  �������Ͷ���, ���¶�����Բ����޸�
/*************************************************************************************/
typedef unsigned char  INT8U;      // 8λ�޷�����                          
typedef signed   char  INT8S;      // 8λ�з�����                         
typedef unsigned short INT16U;     // 16λ�޷�����                            
typedef signed   short INT16S;     // 16λ�з�����                          
typedef unsigned int   INT32U;     // 32λ�޷�����                            
typedef signed   int   INT32S;     // 32λ�з����� 
typedef unsigned long long INT64U; // 64λ�޷�����                            
typedef long long      INT64S;     // 64λ�з�����                        
typedef float          FP32;       // �����ȸ�����                    
typedef double         FP64;       // ˫���ȸ����� 

typedef  void  (*FUNCTION_VOID)(void);  

// 32λ����Ͻṹ
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

    unsigned int d;         // �޷���32λ
	int          s;         // �з���32λ
}INT32_TypeDef;

// 16λ����Ͻṹ
typedef union  
{
    struct 
    {
        unsigned char c0;   // LSB
		unsigned char c1;   // MSB 
    } chars;   
    unsigned short d;       // �޷���16λ
    short          s;       // �з���16λ
}INT16_TypeDef;

#define EXRAM __attribute__ ((section ("RW_RAM1")))	   //��EXRAM���������嵽�ⲿRAM��, ֻ���ں���ģ��STM32F103ZE��ʹ��
#define CCRAM __attribute__ ((section ("CCM_IRAM")))   //��CCRAM���������嵽�ⲿRAM��, ֻ���ں���ģ��STM32F407VE��ʹ��  

/*************************************************************************************/
//  ������붨��, ���¶�����Բ����޸�
/*************************************************************************************/
#define  ERR_OK   	 0	  // ��ȷ
#define  ERR_TRUE    0	  // �ɹ�
#define  ERR_FALSE   1	  // ʧ��
#define  ERR_TIMEOUT 2	  // ��ʱ����
#define  ERR_PARA	 3	  // ������������
#define  ERR_CRC     4	  // CRCУ�����
#define  ERR_HWID    5    // Ӳ��ʶ�����
#define  ERR_NOINIT  6    // ���Ӳ��δ��ʼ��
#define  ERR_NOFIND  7    // û�з���


#endif

/***********************************************************************************/
// �ļ�����
/***********************************************************************************/
