/************************************************************************************
*  Copyright (c), 2019, ��������ѧ
*            All rights reserved.
*
* http:  www.jxust.edu.cn
* Email: 
*
* File name: TaskDisplay.c
* Project  : ���ּܷ�ϵͳ����������ģ��
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  
* Version: 1.00
* Date:    2020.01.14			
* Email:   
* 
* Description: ���ļ�������ڴ���ʵ�ִ������봮������ͨ��; 
*
* Others: none;
*
* Function List:
*		
* History:
*   1. Author:			  
*	   Version: 	 		0.01
*	   Date:        	2020.01.14
*    Modification: 	none
*
*************************************************************************************/

/************************************************************************************/
// ����˵��
/************************************************************************************/
/*

*/
/************************************************************************************/
// �����ⲿͷ�ļ�  
#include "PIONEER_Config.h"
#include "STM32F4_Head.h"
#include "OSVars.h"
#include "UserVars.h"

#include "hmi_driver.h"
#include "hmi_user_uart.h"
#include "cmd_queue.h"
#include "cmd_process.h"
#include "stdio.h"

#include "ulitity.h"
#include "string.h"
#include "delay.h"
#include "stm32f4xx.h"

#include "APP_Init.h"


#define TIME_100MS 10                                                                //100����(10����λ)
#define MaintainID         3																												 //������ϢID


/************************************************************************************/

/************************************************************************************/
// ������ȫ�ֱ�������
/************************************************************************************/
INT8U OS_Err;
INT8U SendBuf[12];
INT8U InfoHead;
INT8U RTCFlag1;


u8 NBMaintainIDData[128];																														//���ϱ�������

volatile uint32  timer_tick_count = 0;                                               //��ʱ������

uint8  cmd_buffer[CMD_MAX_SIZE];                                                     //ָ���
static uint16 current_screen_id = 0;                                                 //��ǰ����ID
static int32 progress_value = 0;                                                     //����������ֵ
static int32 test_value = 0;                                                         //����ֵ
static uint8 update_en = 0;                                                          //���±��
static int32 meter_flag = 0;                                                         //�Ǳ�ָ��������־λ
static int32 num = 0;                                                              //���߲��������
static int sec = 1;                                                                  //ʱ����
static int32 curves_type = 0;                                                        //���߱�־λ  0Ϊ���Ҳ���1Ϊ��ݲ�                  
static int32 second_flag=0;                                                          //ʱ���־λ
static int32 icon_flag = 0;                                                          //ͼ���־λ
static int years,months,weeks,days,hours,minutes; 
static uint8 Select_H ;                                                              //����ѡ��Сʱ
static uint8 Select_M ;                                                              //����ѡ����� 
static uint8 Last_H ;                                                                //��һ��ѡ��Сʱ
static uint8 Last_M;                                                                 //��һ��ѡ����� 
static int32 Progress_Value = 0;                                                     //��������ֵ 

void UpdateUI(void);                                                                 //����UI����

/***********************************************************************************
* Function: Display_Task;
*
* Description: Display����;
*              
* Input:  none;
*
* Return: none;
*
* Note:   ������������д��������յ����ݽ��д���
*
************************************************************************************/
void Display_Task(void *p_arg)		
{	 
		INT8U RTCERR;
		static int32 test_value = 0;                                                     //����ֵ
    uint32 timer_tick_last_update = 0;                                               //��һ�θ��µ�ʱ��
    qsize  size = 0;
		Maintain.MaintainNum=0;                                                          
    //����ʱ��
    //Set_System(); 
		SystemInit();
    //���ô����ж�                                                                
    //Interrupts_Config();                                                            
    //����ʱ�ӽ���                                                                
    systicket_init();                                                               
    //���ڳ�ʼ��                                              
    //UartInit(9600);                                                               

    //��մ��ڽ��ջ�����                                                          
    queue_reset();                                                                  

    //��ʱ�ȴ���������ʼ�����,����ȴ�300ms                                      
    delay_ms(300); 

		SetControlVisiable(1,9,0);		//�����˹�ʶ����ı���
		SetControlVisiable(1,21,0);		//�����˹�ʶ��������˵�
    while(1)                                                                        
    {      
        size = queue_find_cmd(cmd_buffer,CMD_MAX_SIZE); 			//�ӻ������л�ȡһ��ָ��         
			if(size>0)                                      
        {            
            ProcessMessage((PCTRL_MSG)cmd_buffer, size);                             //ָ���  
        } 
        //    �ر�ע��
        //    MCU��ҪƵ���򴮿����������ݣ����򴮿������ڲ��������������Ӷ��������ݶ�ʧ(��������С����׼��8K��������4.7K)
        //    1) һ������£�����MCU�򴮿����������ݵ����ڴ���100ms���Ϳ��Ա������ݶ�ʧ�����⣻
        //    2) �����Ȼ�����ݶ�ʧ�����⣬���жϴ�������BUSY���ţ�Ϊ��ʱ���ܷ������ݸ���������

        //    TODO: ����û�����
        //    �����и���ʱ��־λ�����ı䣬��ʱ100����ˢ����Ļ
        if(update_en&&timer_tick_count-timer_tick_last_update>=TIME_100MS)
        {
            update_en = 0;
            timer_tick_last_update = timer_tick_count;   

            UpdateUI();
        }
  
        //����Ϊ����ʾ���㣬ÿ20�����Զ�����һ��
        //��һ���ж�10ms��timer_tick_countֵ+1,100*timer_tick_count = 1s
        if(timer_tick_count%2==0)
        {   
            UpdateUI(); 
        }
				
				if(ProductResultFlag == 1)														//ͨ���ⲿ�����жϴӶ�ȥ���Ӽ�¼
				{
						GetControlValue(1,9);														//��ȡ���ͨ���˵�¼���ֵ
						ProductResultFlag=0;
				}
				
				if(CameraFlag == 1)																		//ͨ������ͷ�жϵķ�ʽȥ���Ӽ�¼
				{
					GetControlValue(1,27);														//��ȡ�����Ӿ���ֵ
					CameraFlag=0;
				}
				
				delay_ms(10);
    }  
}

/*! 
*  \brief  ��Ϣ��������
*  \param msg ��������Ϣ
*  \param size ��Ϣ����
*/
void ProcessMessage( PCTRL_MSG msg, uint16 size )
{
	
    uint8 cmd_type = msg->cmd_type;                                                  //ָ������
    uint8 ctrl_msg = msg->ctrl_msg;                                                  //��Ϣ������
    uint8 control_type = msg->control_type;                                          //�ؼ�����
    uint16 screen_id = PTR2U16(&msg->screen_id);                                     //����ID
    uint16 control_id = PTR2U16(&msg->control_id);                                   //�ؼ�ID
    uint32 value = PTR2U32(msg->param);                                              //��ֵ
		//printf("����");
    switch(cmd_type)
    {  
    case NOTIFY_TOUCH_PRESS:                                                        //����������
    case NOTIFY_TOUCH_RELEASE:                                                      //�������ɿ�
        NotifyTouchXY(cmd_buffer[1],PTR2U16(cmd_buffer+2),PTR2U16(cmd_buffer+4)); 
        break;                                                                    
    case NOTIFY_WRITE_FLASH_OK:                                                     //дFLASH�ɹ�
        NotifyWriteFlash(1);                                                      
        break;                                                                    
    case NOTIFY_WRITE_FLASH_FAILD:                                                  //дFLASHʧ��
        NotifyWriteFlash(0);                                                      
        break;                                                                    
    case NOTIFY_READ_FLASH_OK:                                                      //��ȡFLASH�ɹ�
        NotifyReadFlash(1,cmd_buffer+2,size-6);                                     //ȥ��֡ͷ֡β
        break;                                                                    
    case NOTIFY_READ_FLASH_FAILD:                                                   //��ȡFLASHʧ��
        NotifyReadFlash(0,0,0);                                                   
        break;                                                                    
    case NOTIFY_READ_RTC:                                                           //��ȡRTCʱ��
        NotifyReadRTC(cmd_buffer[2],cmd_buffer[3],cmd_buffer[4],cmd_buffer[5],cmd_buffer[6],cmd_buffer[7],cmd_buffer[8]);
        break;
    case NOTIFY_CONTROL:
        {
            if(ctrl_msg==MSG_GET_CURRENT_SCREEN)                                    //����ID�仯֪ͨ
            {
                NotifyScreen(screen_id);                                            //�����л������ĺ���
            }
            else
            {
                switch(control_type)
                {
                case kCtrlButton:                                                   //��ť�ؼ�
                    NotifyButton(screen_id,control_id,msg->param[1]);                  
                    break;                                                             
                case kCtrlText:                                                     //�ı��ؼ�
                    NotifyText(screen_id,control_id,msg->param);                       
                    break;                                                             
                case kCtrlProgress:                                                 //�������ؼ�
                    NotifyProgress(screen_id,control_id,value);                        
                    break;                                                             
                case kCtrlSlider:                                                   //�������ؼ�
                    NotifySlider(screen_id,control_id,value);                          
                    break;                                                             
                case kCtrlMeter:                                                    //�Ǳ�ؼ�
                    NotifyMeter(screen_id,control_id,value);                           
                    break;                                                             
                case kCtrlMenu:                                                     //�˵��ؼ�
                    NotifyMenu(screen_id,control_id,msg->param[0],msg->param[1]);      
                    break;                                                              
                case kCtrlSelector:                                                 //ѡ��ؼ�
                    NotifySelector(screen_id,control_id,msg->param[0]);                
                    break;                                                              
                case kCtrlRTC:                                                      //����ʱ�ؼ�
                    NotifyTimer(screen_id,control_id);
                    break;
                default:
                    break;
                }
            } 
            break;  
        } 
    case NOTIFY_HandShake:                                                          //����֪ͨ                                                     
        NOTIFYHandShake();
        break;
    default:
        break;
    }
}

/*! 
*  \brief  ����֪ͨ
*/
void NOTIFYHandShake()
{
   SetButtonValue(3,2,1);
}


/*! 
*  \brief  �����л�֪ͨ
*  \details  ��ǰ����ı�ʱ(�����GetScreen)��ִ�д˺���
*  \param screen_id ��ǰ����ID
*/
void NotifyScreen(uint16 screen_id)
{
    //TODO: ����û�����
    current_screen_id = screen_id;                                                   //�ڹ��������п��������л�֪ͨ����¼��ǰ����ID

}

/*! 
*  \brief  ���������¼���Ӧ
*  \param press 1���´�������3�ɿ�������
*  \param x x����
*  \param y y����
*/
void NotifyTouchXY(uint8 press,uint16 x,uint16 y)
{ 
    //TODO: ����û�����
}


/*! 
*  \brief  ��������
*/ 
void UpdateUI()
{
		INT8U RTCSemERR;
    //ʵʱ���ߣ����Ҳ����顣  ��ʱ20ms��������
//    if(current_screen_id == 8)      
//    { 
//           //��������
//				printf("��������������%s",Facility.BriquettingPressure);
//				//GraphChannelDataAdd(8,1,0,(uint8 *)&BriquettingPressure[num],1);  			//������ݵ�����  һ����������
//					num+=1;
//			if(num>=6)
//			{
//				num=0;
//				printf("����");
//			}
//     }   

		if(current_screen_id==2)													//��������
			{
				if(Maintain.MaintainNum>=5)										//����¼������5ʱ
					{
						Record_DelData(2,8,5);										//ɾ����5����¼
						//printf("�����");
						Maintain.MaintainNum=4;										//������¼��Ϊ4
					}
			}
			
			if(current_screen_id==9)												//ѹ�����ݼ�¼����
			{
				if(Facility.Count>=10)												//��ѹ�����ݼ�¼����10
					{
						Record_DelData(9,1,10);										//ɾ����10����¼
						Facility.Count=9;												//ѹ�����ݼ�¼��Ϊ9
					}
			}
			
}

/*! 
*  \brief  ��ť�ؼ�֪ͨ
*  \details  ����ť״̬�ı�(�����GetControlValue)ʱ��ִ�д˺���
*  \param screen_id ����ID
*  \param control_id �ؼ�ID
*  \param state ��ť״̬��0����1����
*/
void NotifyButton(uint16 screen_id, uint16 control_id, uint8  state)
{ 
	
	switch(screen_id)
	{
		case 1:																								
		{
			if(control_id == 16)																					 //��ҳ��ɨ�밴ť
			{
				if(state == 1)
				{
					ScanFlag=1;
				}
			}
		}
		case 2:
		{
			if(control_id == 2)																								//���������ϴ���ť
			{
				GetControlValue(2,3);																					//��ȡ�ϴ�ʱ����ı�ֵ
				
			}
			if(control_id==10)																							//�������汣�水ť
			{
				printf("���������");
				
				ClearTextValue(2,5);																					//����ı�ʱ��
				ClearTextValue(2,6);																					//����ı���Ա
				ClearTextValue(2,7);																					//����ı�����
				
				sprintf((char *)Maintain.MaintainData,"%s;%s;%s;",Maintain.Time,Maintain.Name,Maintain.Data);//��������Ϣ����
				
				//sprintf((char *)NBMaintainIDData,"%d,%s,%s,%s",MaintainID,Maintain.Time,Maintain.Name,Maintain.Data);//���������ϵ�NB����
				
				printf("%s",Maintain.MaintainData);
			}
			if(control_id==11)																							//�������������ť
			{
				Record_Clear(2,8);																						//�������ɾ��������ʷ��¼
				Maintain.MaintainNum=0;													
			}
			if(control_id==12)																							//��������ʱ�䰴ť
			{
				ReadRTC();
				
				printf("years=%4d months=%d days=%d hours=%d minutes=%d sec=%d",years,months,days,hours,minutes,sec);//��������ʱ�䰴ť
				
				sprintf((char *)Maintain.Time,"%d-%d-%d %d:%d:%d",years,months,days,hours,minutes,sec);	//��ȡʱ��
				
				SetTextValue(2,5,(uchar*)Maintain.Time);											//��ʾʱ��
			}
			break;
		}
		
		case 3:
		{
			if(control_id==4)																					//���ؼ�
			{
				ScanFlag=0;																							//ɨ���־Ϊ0
			}
			if(control_id==5)																					//ѹ����Ա���
			{
				ClearTextValue(3,1);
			}
			if(control_id==7)
			{
				ClearTextValue(3,2);
			}
			if(control_id==8)																					//ԭ�ϱ�ŵı����
			{
				SetTextValue(1,2,(u8 *)SerialNumber.Mark);							//����ԭ�ϱ�ŵ���������
				ClearTextValue(3,3);
			}	
			
			if(control_id==9)																					//�豸��ŵı����
			{
				SetTextValue(1,1,(u8 *)SerialNumber.Facility);					//�����豸��ŵ���������
				ClearTextValue(3,6);
			}
			
			break;
		}
		
		case 5:
		{
			if(control_id==2)																						//���水ť���Ƿ񱣴浯������
			{
				if(state==1)
				{		
					Record_Insertion(2,8,0,(uchar *)Maintain.MaintainData);	//���һ��������¼��Ϣ			
					
					//OSQPost(NBDataQ,NBMaintainIDData);											//�ϴ����ݵ�OneNet
					
					memset(NBMaintainIDData,0,sizeof(NBMaintainIDData));		//��ձ�����Ϣ�ϴ�����
					
					Maintain.MaintainNum++;																	//������¼����һ
					
					printf("MaintainNum==%d",Maintain.MaintainNum);
				}
			}
			
			break;
		}
		
		case 9:
		{
			if(control_id==4)																						//������¼�������ť
			{
				Record_Clear(9,1);																				//�����ʷ��¼
			}
			break;
		}
		
		case 10:
		{
			if(control_id==2)																						//�Ƿ��ϴ���������
			{
				if(state==1)
				{
					
					OSQPost(NBDataQ,NBMaintainIDData);											//�ϴ����ݵ�OneNet
					
					ClearTextValue(2,3);
					memset(NBMaintainIDData,0,sizeof(NBMaintainIDData));		//��ձ�����Ϣ�ϴ�����
				}
			}
			break;
		}
		
		case 16://���ý���
		{
			if(control_id==3)
			{
				if(state==1)
				{
					
					DetectionMode=0;							//���ģʽΪ�����Ӿ�
					SetControlVisiable(1,9,0);		//�����˹�ʶ����ı���
					SetControlVisiable(1,21,0);		//�����˹�ʶ��������˵�
					
				}
			}
			if(control_id==4)
			{
				if(state==1)
				{
					DetectionMode=1;							//���ģʽΪ�˹����
					SetControlVisiable(1,9,1);		//��ʾ�˹�ʶ����ı���
					SetControlVisiable(1,21,1);		//��ʾ�˹�ʶ��������˵�
				}
			}
		}
		
		default :;
	}
}

/*! 
*  \brief  �ı��ؼ�֪ͨ
*  \details  ���ı�ͨ�����̸���(�����GetControlValue)ʱ��ִ�д˺���
*  \details  �ı��ؼ����������ַ�����ʽ�·���MCU������ı��ؼ������Ǹ���ֵ��
*  \details  ����Ҫ�ڴ˺����н��·��ַ�������ת�ظ���ֵ��
*  \param screen_id ����ID
*  \param control_id �ؼ�ID
*  \param str �ı��ؼ�����
*/
void NotifyText(uint16 screen_id, uint16 control_id, uint8 *str)
{
	switch(screen_id)
	{
		case 1:
		{
			if(control_id==9)																										//��ȡ�����ֵ	
			{
					
				ReadRTC();																											//���Ͳ�Ʒ�������ʱ����ź���

				//printf("%s",str);
				sprintf((char *)GainData.ResultData,"%s",str);										//����Ϊ��ȡ�Ľ������
				
				sprintf((char *)Facility.Time,"%d-%d-%d %d:%d:%d",years,months,days,hours,minutes,sec);	//��ȡʱ��
				
				sprintf((char *)Facility.FacilityRecord,"%s;%s;%s;%s;%s;%s;%s;",Facility.Time,					//����ѹ�����ݼ�¼
									SerialNumber.Mark,Facility.BriquettingPressure,Facility.TonnageMolding,
				Facility.MagnetizingA,Facility.DemagnetizmA,GainData.ResultData);
				
				//printf("ѹ�����ݼ�¼%s",Facility.FacilityRecord);
				
				Record_Insertion(9,1,0,(u8 *)Facility.FacilityRecord);						//�ڵ�0������һ�����ݼ�¼
			}
			
//			if(control_id==11)																										//ģ���ı��ؼ�
//			{
//				printf("%s",str);
//				sprintf((char *)GainData.MouldData,"%s",str);												//��ȡģ�ߵ�ֵ
//			}
			
//			if(control_id==12)																										//�����ı��ؼ�
//			{
//				printf("%s",str);
//				sprintf((char *)GainData.MouldData,"%s",str);												//��ȡ���ȵ�ֵ
//			}
			
			if(control_id == 27)
			{
				ReadRTC();																											//���Ͳ�Ʒ�������ʱ����ź���

				sprintf((char *)GainData.ResultData,"%s",str);										//����Ϊ��ȡ�Ľ������
				
				sprintf((char *)Facility.Time,"%d-%d-%d %d:%d:%d",years,months,days,hours,minutes,sec);	//��ȡʱ��
				
				sprintf((char *)Facility.FacilityRecord,"%s;%s;%s;%s;%s;%s;%s;",Facility.Time,					//����ѹ�����ݼ�¼
									SerialNumber.Mark,Facility.BriquettingPressure,Facility.TonnageMolding,
				Facility.MagnetizingA,Facility.DemagnetizmA,GainData.ResultData);
	
				Record_Insertion(9,1,0,(u8 *)Facility.FacilityRecord);						//�ڵ�0������һ�����ݼ�¼
			}
			break;
		}
		
		case 2:
		{
			if(control_id==3)																										//����������´α���ʱ��
			{
				sprintf((char *)Maintain.NextTime,"%s",str);											//��ȡ�´α�����ʱ��
				
				sprintf((char *)NBMaintainIDData,"%d,%s,%s,%s,%s,%s",MaintainID,SerialNumber.Facility,Maintain.
				Name,Maintain.Time,Maintain.DataNumber,Maintain.NextTime);//���������ϵ�NB����
			
			}
			if(control_id==6)																										//�����������Ա
			{
				sprintf((char *)Maintain.Name,"%s",str);													//������Ա���������
				printf("%s",Maintain.Name);
			}
			
			if(control_id==7)																										//��������ı�������
			{
				sprintf((char *)Maintain.Data,"%s",str);													//���ϱ�������ı�������
				printf("%s",Maintain.Data);																				
			}
			
			break;
		}
		
		default:;
	}
}	                                                                             

/*!                                                                              
*  \brief  �������ؼ�֪ͨ                                                       
*  \details  ����GetControlValueʱ��ִ�д˺���                                  
*  \param screen_id ����ID                                                      
*  \param control_id �ؼ�ID                                                     
*  \param value ֵ                                                              
*/                                                                              
void NotifyProgress(uint16 screen_id, uint16 control_id, uint32 value)           
{  
    //TODO: ����û�����   
}                                                                                

/*!                                                                              
*  \brief  �������ؼ�֪ͨ                                                       
*  \details  ���������ı�(�����GetControlValue)ʱ��ִ�д˺���                  
*  \param screen_id ����ID                                                      
*  \param control_id �ؼ�ID                                                     
*  \param value ֵ                                                              
*/                                                                              
void NotifySlider(uint16 screen_id, uint16 control_id, uint32 value)             
{                                                             
 
}

/*! 
*  \brief  �Ǳ�ؼ�֪ͨ
*  \details  ����GetControlValueʱ��ִ�д˺���
*  \param screen_id ����ID
*  \param control_id �ؼ�ID
*  \param value ֵ
*/
void NotifyMeter(uint16 screen_id, uint16 control_id, uint32 value)
{
    //TODO: ����û�����
}

/*! 
*  \brief  �˵��ؼ�֪ͨ
*  \details  ���˵���»��ɿ�ʱ��ִ�д˺���
*  \param screen_id ����ID
*  \param control_id �ؼ�ID
*  \param item �˵�������
*  \param state ��ť״̬��0�ɿ���1����
*/
void NotifyMenu(uint16 screen_id, uint16 control_id, uint8 item, uint8 state)
{
    //TODO: ����û�����
	INT8U err;
		switch(screen_id)
	{
		case 1:
		{
			if(control_id==22)								//ģ�������˵�
			{
				printf("ģ��");
				if(item == 0)										//ģ��������
				{
					printf("��״");
					
					sprintf((char *)GainNumber.MouldData,"%d",1);
					
					printf("ģ�ߵ���������%s\n",GainNumber.MouldData);
				}
				if(item == 1)									//ģ��������
				{
					printf("Բ��");			
					
					sprintf((char *)GainNumber.MouldData,"%d",2);
					
					printf("ģ�ߵ���������%s\n",GainNumber.MouldData);
				}
//				if(state==1)
//				{
//					GetControlValue(1,11);				//��ȡģ��ͨ���˵�¼���ֵ
//				}
			}
			
			if(control_id==21)								//�˹���������˵�
			{
			
				if(item == 0)											//�˹����������
				{
					if(state == 0)
					{
					printf("Բ��-ȱ��-����\r\n");			

					sprintf((char *)GainNumber.ResultData,"%d",1);
					ProcessingFlag=1;																//��Ʒ�ϸ��־Ϊ1
					printf("��Ʒ�������������%s\r\n",GainNumber.ResultData);
					OSSemPost(ResultSem);
					}
				}
				if(item == 1)											//�˹����������
				{
					if(state == 0)
					{
					printf("Բ��-ȱ��-���\r\n");			
					
					sprintf((char *)GainNumber.ResultData,"%d",2);
					ProcessingFlag=1;																//��Ʒ�ϸ��־Ϊ1
					printf("��Ʒ�������������%s\r\n",GainNumber.ResultData);
					OSSemPost(ResultSem);
					}
				}
				if(item == 2)											//�˹����������
				{
					if(state == 0)
					{
					printf("Բ��-ƫλ����\r\n");			
					
					sprintf((char *)GainNumber.ResultData,"%d",3);
					ProcessingFlag=1;																//��Ʒ�ϸ��־Ϊ1
					printf("��Ʒ�������������%s\r\n",GainNumber.ResultData);
					OSSemPost(ResultSem);
					}
				}
				if(item == 3)											//�˹����������
				{
					if(state == 0)
					{
					printf("Բ��-�Ѻ�\r\n");			
					
					sprintf((char *)GainNumber.ResultData,"%d",4);
					ProcessingFlag=1;																//��Ʒ�ϸ��־Ϊ1
					printf("��Ʒ�������������%s\r\n",GainNumber.ResultData);
					OSSemPost(ResultSem);
					}
				}
				if(item == 4)											//�˹����������
				{
					if(state == 0)
					{
					printf("��״-ȱ��-����\r\n");			
					
					sprintf((char *)GainNumber.ResultData,"%d",5);
					ProcessingFlag=1;																//��Ʒ�ϸ��־Ϊ1
					printf("��Ʒ�������������%s\r\n",GainNumber.ResultData);
					OSSemPost(ResultSem);
					}
					
				}
				if(item == 5)											//�˹����������
				{
					if(state == 0)
					{
					printf("��״-ȱ��-���󲻵�\r\n");			
					
					sprintf((char *)GainNumber.ResultData,"%d",6);
					ProcessingFlag=1;																//��Ʒ�ϸ��־Ϊ1
					printf("��Ʒ�������������%s\r\n",GainNumber.ResultData);
					OSSemPost(ResultSem);
					}
				}
				if(item == 6)											//�˹����������
				{
					if(state == 0)
					{
					printf("��״-ȱ��-ģ�߲���\r\n");			
					
					sprintf((char *)GainNumber.ResultData,"%d",7);
					ProcessingFlag=1;																//��Ʒ�ϸ��־Ϊ1
					printf("��Ʒ�������������%s\r\n",GainNumber.ResultData);
					OSSemPost(ResultSem);
					}
				}
				if(item == 7)											//�˹����������
				{
					if(state == 0)
					{
					printf("��״-б��\r\n");			
					
					sprintf((char *)GainNumber.ResultData,"%d",8);
					ProcessingFlag=1;																//��Ʒ�ϸ��־Ϊ1
					printf("��Ʒ�������������%s\r\n",GainNumber.ResultData);
					OSSemPost(ResultSem);
					}
					
				}
			}
			
			if(control_id==29)								//���������˵�
			{
				if(item == 0)
				{
					printf("С��\r\n");
					
					sprintf((char *)GainNumber.Granularity,"%d",0);
																					//��Ʒ�ϸ��־Ϊ1
					printf("��Ʒ�������������%s\r\n",GainNumber.Granularity);
					
				}
				if(item == 1)
				{
					printf("����\r\n");
					
					sprintf((char *)GainNumber.Granularity,"%d",1);
					
					printf("��Ʒ�������������%s\r\n",GainNumber.Granularity);
				}
			}
				
//				if(state==1)
//				{
//					GetControlValue(1,12);				//��ȡ����ͨ���˵�¼���ֵ
//				}
			}
			break;
			
		case 2:
		{
			if(control_id==17)
			{
				if(state==1)
				{
					GetControlValue(2,7);				 //��ȡ�������ݴӲ˵�¼���ֵ
				}
				if(item == 0)											//�˹����������
				{
					printf("��ࡢ��\r\n");			

					sprintf((char *)Maintain.DataNumber,"%d",1);
					
					printf("��Ʒ�������������%s\r\n",Maintain.DataNumber);
				}
				if(item == 1)
				{
					printf("����\r\n");
					
					sprintf((char *)Maintain.DataNumber,"%d",2);
					
					printf("��Ʒ�������������%s\r\n",Maintain.DataNumber);
				}
				if(item == 2)
				{
					printf("����\r\n");
					
					sprintf((char *)Maintain.DataNumber,"%d",3);
					
					printf("��Ʒ�������������%s\r\n",Maintain.DataNumber);
				}
				if(item == 3)
				{
					printf("����Ź�\r\n");
					
					sprintf((char *)Maintain.DataNumber,"%d",4);
					
					printf("��Ʒ�������������%s\r\n",Maintain.DataNumber);
				}
			}
			break;	
		}
		
		default :;
	
	}
	
}

/*! 
*  \brief  ѡ��ؼ�֪ͨ
*  \details  ��ѡ��ؼ��仯ʱ��ִ�д˺���
*  \param screen_id ����ID
*  \param control_id �ؼ�ID
*  \param item ��ǰѡ��
*/
void NotifySelector(uint16 screen_id, uint16 control_id, uint8  item)
{
    if(screen_id == 13&&control_id == 1)                                               //��ȡ��ǰѡ��ؼ���ֵ
    {
        Select_H =  item;
    } 
    if(screen_id == 13&&control_id == 2)                                               //��ȡ��ǰѡ��ؼ���ֵ
    {
        Select_M =  item;
    } 

}

/*! 
*  \brief  ��ʱ����ʱ֪ͨ����
*  \param screen_id ����ID
*  \param control_id �ؼ�ID
*/
void NotifyTimer(uint16 screen_id, uint16 control_id)
{
    if(screen_id==8&&control_id == 7)
    {
        SetBuzzer(100);
    } 
}

/*! 
*  \brief  ��ȡ�û�FLASH״̬����
*  \param status 0ʧ�ܣ�1�ɹ�
*  \param _data ��������
*  \param length ���ݳ���
*/
void NotifyReadFlash(uint8 status,uint8 *_data,uint16 length)
{
    //TODO: ����û�����
}

/*! 
*  \brief  д�û�FLASH״̬����
*  \param status 0ʧ�ܣ�1�ɹ�
*/
void NotifyWriteFlash(uint8 status)
{
    //TODO: ����û�����
}

/*! 
*  \brief  ��ȡRTCʱ�䣬ע�ⷵ�ص���BCD��
*  \param year �꣨BCD��
*  \param month �£�BCD��
*  \param week ���ڣ�BCD��
*  \param day �գ�BCD��
*  \param hour ʱ��BCD��
*  \param minute �֣�BCD��
*  \param second �루BCD��
*/
void NotifyReadRTC(uint8 year,uint8 month,uint8 week,uint8 day,uint8 hour,uint8 minute,uint8 second)
{      
    sec    =(0xff & (second>>4))*10 +(0xf & second);                                    //BCD��תʮ����
    years   =(0xff & (year>>4))*10 +(0xf & year);                                      
    months  =(0xff & (month>>4))*10 +(0xf & month);                                     
    weeks   =(0xff & (week>>4))*10 +(0xf & week);                                      
    days    =(0xff & (day>>4))*10 +(0xf & day);                                      
    hours   =(0xff & (hour>>4))*10 +(0xf & hour);                                       
    minutes =(0xff & (minute>>4))*10 +(0xf & minute);                                                                                                                  
}


