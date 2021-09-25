/************************************************************************************
*  Copyright (c), 2019, ��������ѧ
*            All rights reserved.
*
* http:  www.jxust.edu.cn
* Email: 
*
* File name: UserVars.c
* Project  : STM32F4XXϵ��ģ�����
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  �ǻ۹����о���
* Version: 1.00
* Date:    2019.11.25			
* Email:   
* 
* Description: ���ļ������û�Ӧ�ó��򹫹�ȫ�ֱ���, �ͻ����԰�Ӧ�õ�ȫ�ֱ������õ�����;
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
#include "UserVars.h"	
USER_VARS UserVars;	     																							// �û�����

Number SerialNumber={"0","0","0","0"};     														//��ű�������
Record Maintain={"0","0","0","0",0,"0","0"};				 									//������¼��Ŷ���
Gain GainData={"0","0","0","0"};           														//��ȡ����Ϣ��������
Gain GainNumber={"0","0","0","0"};																		//��ȡ����Ϣ��ű�������
Press Facility={"0","0","0","0","0","0","0","0","0",0,0};							//ѹ���豸���ݽṹ��
Environment	EnvironmentData={"0","0","0"};														//�������ݽṹ�����
NBAccept Maintenance={0,"0",0,0};																			//���뱣���豸��ʱ��ṹ�����


u32 FLASH_SIZE=128*1024*1024;	//��ʼд���FLash��ַ	

u32 FLASH_SIZE_Count;					//���õ�FLASH��ַ

u8 DetectionMode;							//��ⷽʽ
u8 CameraFlag;								//ͨ������ͷ���ı�־
u8 ScanFlag;									//ɨ���־
u8 UploadingFlag;							//�����ϴ�NB��־
u8 ProductResultFlag=0;				//ͨ���ⲿ��������ʱ��Ʒ��ʷ��¼
u8 CameraRedFlag;							//����Թܼ�⵽�ı�־
u8 ProcessingFlag;						//��Ʒ�ϸ��־

u8 ProductResult[]="�ϸ�";
u8 ProductResult1[]="Բ��-ȱ��-����";
u8 ProductResult2[]="Բ��-ȱ��-���";
u8 ProductResult3[]="Բ��-ƫλ����";
u8 ProductResult4[]="Բ��-�Ѻ�";
u8 ProductResult5[]="��״-ȱ��-����";
u8 ProductResult6[]="��״-ȱ��-���󲻵�";
u8 ProductResult7[]="��״-ȱ��-ģ�߲���";
u8 ProductResult8[]="��״-б��";



void *DisplayQMsg[32];		// ������Ϣ����DisaplayQ��ָ������
INT8U DisMemData[32][64]; // ���崮������ʾ���ݴ�Ŵ洢������Ŀռ䣨50��ÿ��64�ֽڣ�



INT8U UART1_RX_BUF[UART1_RXBUF_SIZE];     //���ջ���,���UART1_RXBUF_SIZE���ֽ�.
INT8U UART2_RX_BUF[UART2_RXBUF_SIZE];
INT8U UART3_RX_BUF[UART3_RXBUF_SIZE];
INT8U UART4_RX_BUF[UART4_RXBUF_SIZE];
INT8U UART5_RX_BUF[UART5_RXBUF_SIZE];
INT8U UART6_RX_BUF[UART6_RXBUF_SIZE];
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
INT16U UART1_RX_STA=0;       //����״̬���	.
INT16U UART2_RX_STA=0;
INT16U UART3_RX_STA=0;
INT16U UART4_RX_STA=0;
INT16U UART5_RX_STA=0;
INT16U UART6_RX_STA=0;


INT8U  TIM4CH1_CAPTURE_STA=0;	//���벶��״̬		    				
INT32U	TIM4CH1_CAPTURE_VAL;	//���벶��ֵ


//ȫ�ֱ���

//NB����
INT8U ConnectStatus=0;															// ���ڱ�����������״̬  =0��δ����	=1��������
INT8U DelCnt=0;
INT8U NBRvDelay=0;																	// ������NBģ�����ĳЩ����ķ��ؽ��ʱ����ʱ���ն�������
INT16U NBUpdateCnt;																		// 	���ڼƸ��������ڵ�ʱ��
INT8U SendIntervalSecond=3;													// ���ڴ�����ݷ��ͼ��������
INT16U SendIntervalMilli=0;													// ���ڴ�����ݷ��ͼ���ĺ�����
INT8U ReadSIData[6];
INT8U HaveOk=0;	




/***********************************************************************************/
// �ļ�����
/***********************************************************************************/
