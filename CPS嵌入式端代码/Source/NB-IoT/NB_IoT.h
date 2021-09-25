/************************************************************************************
*  Copyright (c), 2019, ��������ѧ
*            All rights reserved.
*
* http:  www.jxust.edu.cn
* Email: 
*
* File name: NB-IoT.h
* Project  : NB-IoT�ײ㺯����ͷ�ļ�
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  
* Version: 0.01
* Date:    2019.08.15			
* Email:   
* 
* Description: ���ļ������������֡��ͨ��NB-IoTģ�鷢�����ݵ�OneNet
*
* Others: none;
*
* Function List:
*		
* History:
*   1. Author:			  
*	   Version: 	 		0.02
*	   Date:         	2019.11.08
*    Modification: 	none
*
*************************************************************************************/
#ifndef _NB_IOT_H_
#define _NB_IOT_H_

#include "PIONEER_Config.h"

INT8U nbiot_Create(void);						// �����豸ʵ��;
INT8U nbiot_AddObj(void);						// ����OBJ������
INT8U nbiot_DiscoverRsp(void);				// ����Resource��������
INT8U nbiot_Connect(void);						// ��ƽ̨ע���¼;
INT8U nbiot_Query(void);							// ��ѯ��¼״̬����
INT8U nbiot_Nofity(INT8U *NBBuff);		// �������ݵ�ƽ̨;
INT8U nbiot_Del(void);								// ɾ���豸ʵ��
INT8U nbiot_Reset(void);							// ��λģ��;
INT8U nbiot_Update(void);						// ���´��ʱ��

#endif


