/************************************************************************************
*  Copyright (c), 2019, ��������ѧ
*            All rights reserved.
*
* http:  www.jxust.edu.cn
* Email: 
*
* File name: UserVars.h
* Project  : STM32F4XXϵ��ģ�����
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  �ǻ۹����о���
* Version: 1.00
* Date:    2019.11.25			
* Email:   
* 
* Description: ���ļ������û�Ӧ�ó��򹫹�ȫ�ֱ�������ͷ�ļ�, �ͻ����԰�Ӧ�õ�ȫ�ֱ������õ�����;
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
#ifndef __USER_VARS_H 
#define __USER_VARS_H 

/************************************************************************************/
// �����ⲿͷ�ļ�
/************************************************************************************/
#include "const.h"	
//#include "config.h"	
#include "PIONEER_Config.h"

#include "timer.h"	
/************************************************************************************
*
*       ϵͳ״̬��־����
*
*************************************************************************************/

#define CONFIG_PARA_LEN	 sizeof(CONFIG_PARA)
	
#define TASK_IO_FLAG		    0x00000001
#define TASK_TEST_FLAG      0x00000002 
#define NBTX_TASK_FLAG	    0x00000004 
#define NBRV_TASK_FLAG	    0x00000008 
#define UPDATE_TASK_FLAG	  0x00000010 

#define TASK_UART_FLAG	    0x00000020 


#define TASK_FLAG   (TASK_TEST_FLAG*TASK_TEST_EN + TASK_IO_FLAG*TASK_IO_EN + NBTX_TASK_FLAG*NBTX_TASK_EN +      \
                     NBRV_TASK_FLAG*NBRV_TASK_EN + UPDATE_TASK_FLAG*UPDATE_TASK_EN + TASK_UART_FLAG*TASK_UART_EN \
										)



// Flag���ֱ�־λ����
#define  RTC_SECIT_FLAG         0x00000001  // RTC���жϱ�־
#define  RTC_ALRIT_FLAG         0x00000002  // RTC�����жϱ�־
#define  SPIFLASH_WK_FLAG       0x00000004  // SPI FLASH���ڹ����б�־, �������־
#define  SD_WK_FLAG             0x00000008  // SD�����ڹ����б�־
#define  OS_START_FLAG          0x00000020  // ����ϵͳ�������б�־

// OKFlag ���Ӹ����ܲ��Գɹ���־
#define  SPIFLASH_OK_FLAG       0x00000001  // SPI FLASH���Գɹ���־
#define  NFLASH_OK_FLAG         0x00000002  // NAND FLASH���Գɹ���־
#define  EEPROM_OK_FLAG         0x00000004  // EEPROM���Գɹ���־
#define  SRAM_OK_FLAG           0x00000008  // ��չSRAM���Գɹ���־
#define  SD_OK_FLAG             0x00000010  // SD�����Գɹ���־


#define  DATABUF_SIZE   512

#pragma pack (1)


typedef struct
{ 
    INT32U   Flag;          // ���ֱ�־λ
    INT32U   TaskRunStatus; // ����ϵͳ��������״̬ 
    
    INT32U   OKFlag;        // ���Ӹ����ܲ��Գɹ���־
    INT32U   DI;	        // DI����ֵ: DI1=bit0, DI2=bit1; �Դ�����DI32=bit31; 
    INT32U   DO;	        // DO���ֵ: DO1=bit0, DO2=bit1; �Դ�����DO32=bit31; 
	
		INT32U   TimerCount;
    INT8U    buf[DATABUF_SIZE+1];  // ����������
    INT16U   UartData;      // Uart��������
    
}USER_VARS;	 
#pragma pack() 
extern USER_VARS UserVars;	     // �û�����

extern u8 ProcessingFlag;						//��Ʒ�ϸ��־
extern u8 DetectionMode;							//��ⷽʽ
extern u32 FLASH_SIZE;				   //FLASH ��СΪ16�ֽ�		
extern u8 ProductResultFlag;		 //ͨ���ⲿ��������ʱ��Ʒ��ʷ��¼
extern u8 CameraFlag;						 //ͨ������ͷ���ı�־
extern u8 ScanFlag;							 //ɨ���־
extern u8 UploadingFlag;				 //�����ϴ�NB��־
extern u8 CameraRedFlag;				 //����Թܼ�⵽�ı�־
extern INT8U UART1_RX_BUF[UART1_RXBUF_SIZE];     //���ջ���,���UART1_RXBUF_SIZE���ֽ�.
extern INT8U UART2_RX_BUF[UART2_RXBUF_SIZE];
extern INT8U UART3_RX_BUF[UART3_RXBUF_SIZE];
extern INT8U UART4_RX_BUF[UART4_RXBUF_SIZE];
extern INT8U UART5_RX_BUF[UART5_RXBUF_SIZE];
extern INT8U UART6_RX_BUF[UART6_RXBUF_SIZE];
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
extern INT16U UART1_RX_STA;       //����״̬���	.
extern INT16U UART2_RX_STA;
extern INT16U UART3_RX_STA;
extern INT16U UART4_RX_STA;
extern INT16U UART5_RX_STA;
extern INT16U UART6_RX_STA;


extern INT8U  TIM4CH1_CAPTURE_STA;	//���벶��״̬		    				
extern INT32U	TIM4CH1_CAPTURE_VAL;	//���벶��ֵ


//NB����

extern INT8U ConnectStatus;															// ���ڱ�����������״̬  =0��δ����	=1��������
extern INT8U DelCnt;
extern INT8U NBRvDelay;																	// ������NBģ�����ĳЩ����ķ��ؽ��ʱ����ʱ���ն�������
extern INT16U NBUpdateCnt;																		// 	���ڼƸ��������ڵ�ʱ��
extern INT8U SendIntervalSecond;													// ���ڴ�����ݷ��ͼ��������
extern INT16U SendIntervalMilli;													// ���ڴ�����ݷ��ͼ���ĺ�����
extern INT8U ReadSIData[6];
extern INT8U HaveOk;	


typedef struct
{
	u8 BriquettingPressure[4];															//����ѹ��
	u8 TonnageMolding[4];																		//���Ͷ�λ
	u8 MagnetizingA[6];																			//��ŵ���
	u8 DemagnetizmA[5];																			//�˴ŵ���
	u8 Size[5];																							//�ߴ�
	u8 Weight[6];																						//����
	u8 PowderTime[2];																				//�Ʒۼ�ʱ
	u8 FacilityRecord[128];																	//ѹ���������ݼ�¼
	u8 Time[32];																						//���������ʱ��
	u8 Number;																							//��Ʒ�ĸ���
	u8 Count;																								//��Ʒ��ʷ���ݼ�¼��
}Press;																										//ѹ���豸�ṹ��
extern Press Facility;


typedef struct 
{
	u8 Pack_ID[16];																					//��װԱ��ID
	u8 Profiling_ID[16];																		//ѹ��Ա��ID
	u8 Mark[16];																						//ԭ�ϱ��
	u8 Facility[16];																				//�豸���
}Number;																									//��Žṹ��			
extern Number SerialNumber;



typedef struct																						//���ڴ�ű�����¼
{		
	
	u8 Time[32];																					  //ʱ��
	u8 Name[16];																						//����
	u8 Data[32];																						//��������	
	u8 DataNumber[8];																				//�������ݱ��
	u8 MaintainNum;																				  //������¼��
	u8 MaintainData[128];																		//������Ϣ����
	u8 NextTime[16];																				//�´α�����ʱ��
}Record;
extern Record Maintain;																		//������¼�Ľṹ�����

typedef struct
{
		u8 Facility;																					//�豸��
		u8 TimeNum[8];																				//�����ʱ����
	  u8 HourlyBasis;																				//ʱ�䵥λ
		u8 NBTimeNum;																					//NB�յ��ľ���ʱ����
}NBAccept;
extern NBAccept Maintenance;															//���뱣���豸��ʱ��ṹ�����

typedef struct
{
	u8  MouldData[64];																			//ģ��
	u8  ResultData[64];																			//���
	u8  Granularity[64];																		//����
	u8 	Time[16];																						//���������ʱ��
}Gain;													
extern Gain GainData; 																		//��ȡ����Ϣ���ݱ�������
extern Gain GainNumber;																		//��ȡ����Ϣ��ű�������

extern u8 ProductResult[];																//��Ʒ�ϸ�����
extern u8 ProductResult1[];																//��Ʒ�������1
extern u8 ProductResult1[];																//��Ʒ�������2
extern u8 ProductResult2[];																//��Ʒ�������3
extern u8 ProductResult3[];																//��Ʒ�������4
extern u8 ProductResult4[];																//��Ʒ�������5
extern u8 ProductResult5[];																//��Ʒ�������6
extern u8 ProductResult6[];																//��Ʒ�������7
extern u8 ProductResult7[];																//��Ʒ�������8
extern u8 ProductResult8[];																//��Ʒ�������9

typedef struct
{
	u8  Temperature[16];																			//�¶�
	u8  Humidity[16];																					//ʪ��
	u8  PM[16];																								//PM2.5
}Environment;																								//

extern Environment	EnvironmentData;												//�������ݽṹ�����
#endif
/***********************************************************************************/
// �ļ�����
/***********************************************************************************/
