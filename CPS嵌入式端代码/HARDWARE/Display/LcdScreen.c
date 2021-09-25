/************************************��Ȩ����********************************************
**                             ���ݴ�ʹ��Ƽ����޹�˾
**                             http://www.gz-dc.com
**-----------------------------------�ļ���Ϣ--------------------------------------------
** �ļ�����:   ulitity.c
** �޸�ʱ��:   2018-05-18
** �ļ�˵��:   �û�MCU��������������
** ����֧�֣�  Tel: 020-82186683  Email: hmi@gz-dc.com Web:www.gz-dc.com
--------------------------------------------------------------------------------------*/
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

#include "lcdscreen.h"

#define TIME_100MS 10                                                                //100����(10����λ)

int value[8];                                                                       //��ģ������
uint8 level[10]={0xff,0xe0,0xc4,0xa8,0x8c,0x70,0x54,0x38,0x1c,0x00};                 //���ȵȼ�
int Model_Number;                                                                    //���ż�¼ֵ
uint16 Record_Number;                                                                   //��������
int Record_Flag=0;                                                                   //��¼�ؼ���ȡ��־λ
int Down5_1=0;																																				//�������±�־λ
int Down12_4=0;
uint8 *username=(uint8*)"root";                                                             //�û���
uint8 password[8];                                                         //�û�����
int PassWord_OK=0,UserName_OK=0;                                                            //��¼������˺������־λ
int OldPassWord=0,ResetPassWord=0;                                                          //�޸������־λ
uint8 SetPassWord[8];                                                                         //��ʱ��������

volatile uint32  timer_tick_count = 0;                                               //��ʱ������

uint8  cmd_buffer[CMD_MAX_SIZE];                                                     //ָ���
static uint16 current_screen_id = 0;                                                 //��ǰ����ID
//static int32 progress_value = 0;                                                     //����������ֵ
//static int32 test_value = 0;                                                         //����ֵ
static uint8 update_en = 0;                                                          //���±��
//static int32 meter_flag = 0;                                                         //�Ǳ�ָ��������־λ
//static int32 num = 0;                                                                //���߲��������
//static int sec = 1;                                                                  //ʱ����
//static int32 curves_type = 0;                                                        //���߱�־λ  0Ϊ���Ҳ���1Ϊ��ݲ�                  
//static int32 second_flag=0;                                                          //ʱ���־λ
//static int32 icon_flag = 0;                                                          //ͼ���־λ
//static uint8 Select_H ;                                                              //����ѡ��Сʱ
//static uint8 Select_M ;                                                              //����ѡ����� 
//static uint8 Last_H ;                                                                //��һ��ѡ��Сʱ
//static uint8 Last_M;                                                                 //��һ��ѡ����� 
static int32 Progress_Value = 0;                                                     //��������ֵ 

void UpdateUI(void);                                                                 //����UI����


/*!                                                                                 
*  \brief  �������
*/                                                                                  
void LcdScreen()
{                                                                              

    uint32 timer_tick_last_update = 0;                                               //��һ�θ��µ�ʱ��
    qsize  size = 0;
    //����ʱ��
    SystemInit();                                                                   
    //���ô����ж�                                                                
    //Interrupts_Config();                                                            
    //����ʱ�ӽ���                                                                
    systicket_init();                                                               
    //���ڳ�ʼ��                                              
    //UartInit(19200);                                                               

    //��մ��ڽ��ջ�����                                                          
    queue_reset();                                                                  

    //��ʱ�ȴ���������ʼ�����,����ȴ�300ms                                      
    delay_ms(300);                                                                  

    while(1)                                                                        
    {                                                                               
        size = queue_find_cmd(cmd_buffer,CMD_MAX_SIZE);                              //�ӻ������л�ȡһ��ָ��         

        if(size>0&&cmd_buffer[1]!=0x07)                                              //���յ�ָ�� �����ж��Ƿ�Ϊ������ʾ
        {                                                                     
            ProcessMessage((PCTRL_MSG)cmd_buffer, size);                             //ָ���  
        }
        else if(size>0&&cmd_buffer[1]==0x07)                                         //���Ϊָ��0x07��������STM32  
        {                                                                           
            __disable_fault_irq();                                                   
            NVIC_SystemReset();                                                                                                                                          
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
						else if(ctrl_msg==0x55)
							NotifyRecord_Num(screen_id,control_id,msg->param[1]);
						else if(ctrl_msg==0x56)
							NotifyRecord(screen_id,control_id,msg->param);
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
		//hfl:����

		if(screen_id == 4)
		{
			GetControlValue(5,2);									//��ȡѹ����Сֵ
			GetControlValue(5,3);									//��ȡѹ�����ֵ
			GetControlValue(5,20);									//��ȡֱ����Сֵ
			GetControlValue(5,23);									//��ȡֱ�����ֵ
			GetControlValue(5,21);									//��ȡ�絼�����ֵ
			GetControlValue(5,24);									//��ȡ�絼�����ֵ
			GetControlValue(5,22);									//��ȡ��չ�����ֵ
			GetControlValue(5,25);									//��ȡ��չ�����ֵ
		}

		if(screen_id==7)
		{
			GetControlValue(5,2);									//��ȡѹ����Сֵ
			GetControlValue(5,3);									//��ȡѹ�����ֵ
		}
		
		if(screen_id==8)
		{
			GetControlValue(5,20);									//��ȡֱ����Сֵ
			GetControlValue(5,23);									//��ȡֱ�����ֵ
		}
		
		if(screen_id==9)
		{
			GetControlValue(5,21);									//��ȡ�絼�����ֵ
			GetControlValue(5,24);									//��ȡ�絼�����ֵ
		}
		
		if(screen_id==10)
		{
			GetControlValue(5,22);									//��ȡ��չ�����ֵ
			GetControlValue(5,25);									//��ȡ��չ�����ֵ
		}
		
    //���뻭��5��flash���ֵ


    //������ά��ҳ�����ɶ�ά��
    if(current_screen_id==3)
    {
        //��ά��ؼ���ʾ�����ַ�ʱ����Ҫת��ΪUTF8���룬
        //ͨ����ָ�����֡���ת����www.gz-dc.com�� ���õ��ַ�����������
        uint8 dat[] = {0xE9,0xBB,0x84,0xE9,0xA3,0x9E,0xE9,0xBE,0x99};
        SetTextValue(3,1,dat);                                                      //���Ͷ�ά���ַ�����                     
    }
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

    //ʵʱ���ߣ����Ҳ����顣  ��ʱ20ms��������
    /*if(current_screen_id == 11)      
    { 
        if(curves_type == 0)
        {
            //��������
            uint8 sin[256] = {1,1,1,1,1,2,3,4,6,8,10,13,15,
                19,22,25,29,33,38,42,47,52,57,62,68,73,79,85,91,97,103,109,115,121,127,134,
                140,146,152,158,164,170,176,182,187,193,198,203,208,213,217,222,226,230,233,
                236,240,242,245,247,249,251,252,253,254,254,254,254,254,253,252,251,249,247,
                245,242,240,236,233,230,226,222,217,213,208,203,198,193,187,182,176,170,164,
                158,152,146,140,134,128,121,115,109,103,97,91,85,79,73,68,62,57,52,47,42,38,
                33,29,25,22,19,15,13,10,8,6,4,3,2,1,1,1,1,1,2,3,4,6,8,10,13,15,
                19,22,25,29,33,38,42,47,52,57,62,68,73,79,85,91,97,103,109,115,121,127,134,
                140,146,152,158,164,170,176,182,187,193,198,203,208,213,217,222,226,230,233,
                236,240,242,245,247,249,251,252,253,254,254,254,254,254,253,252,251,249,247,
                245,242,240,236,233,230,226,222,217,213,208,203,198,193,187,182,176,170,164,
                158,152,146,140,134,128,121,115,109,103,97,91,85,79,73,68,62,57,52,47,42,38,
                33,29,25,22,19,15,13,10,8,6,4,3,2};

            GraphChannelDataAdd(11,1,0,&sin[num],2);                                    //������ݵ�����  һ����������

            num += 2;                                                                        
            if(num >= 255)                                                                
            {                                                                             
                num =0;                                                                  
            }
        } 
        else if(curves_type == 1)
        {
            //��ݲ�����
            uint8 sawtooth[180] = {0,9,18,27,36,45,54,63,72,81,90,99,108,117,126,135,144,153,162,171,180,189,198,207,216,225,234,243,252,
                0,9,18,27,36,45,54,63,72,81,90,99,108,117,126,135,144,153,162,171,180,189,198,207,216,225,234,243,252,
                0,9,18,27,36,45,54,63,72,81,90,99,108,117,126,135,144,153,162,171,180,189,198,207,216,225,234,243,252,
                0,9,18,27,36,45,54,63,72,81,90,99,108,117,126,135,144,153,162,171,180,189,198,207,216,225,234,243,252,
                0,9,18,27,36,45,54,63,72,81,90,99,108,117,126,135,144,153,162,171,180,189,198,207,216,225,234,243,252,
                0,9,18,27,36,45,54,63,72,81,90,99,108,117,126,135,144,153,162,171,180,189,198,207,216,225,234,243,252};


            GraphChannelDataAdd(11,1,0,&sawtooth[num],2);                              //������ݵ�����  һ����������
            num +=2 ;                                                                        
            if(num >= 180)                                                                
            {                                                                             
                num =0;                                                                  
            }
        }          
    }                                                                              

    //��ʱ���ߣ����Ҳ�����                                                         
    if(current_screen_id == 16 && timer_tick_count %100 == 0)                           //��ʷ���߿ؼ���������1sһ���㡣//һ������������                                                    
    {   
        if(curves_type == 0)
        {        
            //��������
            uint8 sin[256] = {1,1,1,1,1,2,3,4,6,8,10,13,15,
                19,22,25,29,33,38,42,47,52,57,62,68,73,79,85,91,97,103,109,115,121,127,134,
                140,146,152,158,164,170,176,182,187,193,198,203,208,213,217,222,226,230,233,
                236,240,242,245,247,249,251,252,253,254,254,254,254,254,253,252,251,249,247,
                245,242,240,236,233,230,226,222,217,213,208,203,198,193,187,182,176,170,164,
                158,152,146,140,134,128,121,115,109,103,97,91,85,79,73,68,62,57,52,47,42,38,
                33,29,25,22,19,15,13,10,8,6,4,3,2,1,1,1,1,1,2,3,4,6,8,10,13,15,
                19,22,25,29,33,38,42,47,52,57,62,68,73,79,85,91,97,103,109,115,121,127,134,
                140,146,152,158,164,170,176,182,187,193,198,203,208,213,217,222,226,230,233,
                236,240,242,245,247,249,251,252,253,254,254,254,254,254,253,252,251,249,247,
                245,242,240,236,233,230,226,222,217,213,208,203,198,193,187,182,176,170,164,
                158,152,146,140,134,128,121,115,109,103,97,91,85,79,73,68,62,57,52,47,42,38,
                33,29,25,22,19,15,13,10,8,6,4,3,2}; 

            HistoryGraph_SetValueInt8(16,1,&sin[num],1);                               //�����ʷ��������         
            num++;
            if(num >= 255)
            {
                num =0;
            }
        } 
        else if(curves_type == 1)
        {          
            //��ݲ�����
            uint8 sawtooth[180] = {0,9,18,27,36,45,54,63,72,81,90,99,108,117,126,135,144,153,162,171,180,189,198,207,216,225,234,243,252,
                0,9,18,27,36,45,54,63,72,81,90,99,108,117,126,135,144,153,162,171,180,189,198,207,216,225,234,243,252,
                0,9,18,27,36,45,54,63,72,81,90,99,108,117,126,135,144,153,162,171,180,189,198,207,216,225,234,243,252,
                0,9,18,27,36,45,54,63,72,81,90,99,108,117,126,135,144,153,162,171,180,189,198,207,216,225,234,243,252,
                0,9,18,27,36,45,54,63,72,81,90,99,108,117,126,135,144,153,162,171,180,189,198,207,216,225,234,243,252,
                0,9,18,27,36,45,54,63,72,81,90,99,108,117,126,135,144,153,162,171,180,189,198,207,216,225,234,243,252};

            HistoryGraph_SetValueInt8(16,1,&sawtooth[num],1);                          //�����ʷ��������        
            num++;
            if(num >= 90)
            {
                num =0;
            }
        } 


    }*/

}


/*
by  hfl

��ȡ��¼�ؼ����ص���������
*/
void NotifyRecord_Num(uint16 screen_id,uint16 control_id,uint8 num)
{
			uint16 i=0,j=0;
			u8 data[18];
			Record_Number=(uint16)num;
			for(;i<(int)num;i++)
			{
					j=1;
					Record_GetData(12,1,num-1-i);
			}
			if(Record_Number==0&&j==0)
			{
				if(Down12_4!=1)                    //��ֹɾ�����������ݼ�¼
				{
					sprintf((char*)data,"%d;%d;%d;%d;%d;%d;%d;%d;%d;",Model_Number,value[0],value[1],value[2],value[3],value[4],value[5],value[6],value[7]);
					Record_Add(12,1,data);
				}
				else
				{
					Down12_4=0;
				}
			}
}

/*
by hfl

��ȡ��¼�ؼ����ص�һ������

*/
void NotifyRecord(uint16 screen_id,uint16 control_id,uint8 *msg)
{
			uint8 data[18];
			int i,k=0;
			uint16 j[8]={2,3,20,23,21,24,22,25};
			Record_Number=Record_Number-1;
			if(msg[1]==0x3b)
			{
				if(Model_Number==(int)msg[0]-48)
				{
					if(Down5_1==1)
					{
						Down5_1=0;
						sprintf((char*)data,"%d;%d;%d;%d;%d;%d;%d;%d;%d;",Model_Number,value[0],value[1],value[2],value[3],value[4],value[5],value[6],value[7]);
						Record_ModifyData(12,1,Record_Number,data);
					}
					else if(Down12_4==1)
					{
						Down12_4=0;
						Record_DelData(12,1,(uint16)Record_Number);
					}
					else
					{
						for(i=2;i<strlen((const char*)msg);i++)
						{
							if(msg[i+1]!=0x3b)
							{
								if(msg[i+2]!=0x3b)
								{
									SetTextInt32(5,j[k],(msg[i]-48)*100+(msg[i+1]-48)*10+msg[i+2]-48,1,3);
									i+=3;k++;
								}
								else
								{
									SetTextInt32(5,j[k],(msg[i]-48)*10+msg[i+1]-48,1,3);
									i+=2;k++;
								}
							}
							else
							{
								SetTextInt32(5,j[k],msg[i]-48,1,3);
								i++;k++;
							}
						}
					}
					Record_Flag=1;
				}
			}
			else
			{
				if(Model_Number==((int)msg[0]-48)*10+(int)msg[1]-48)
				{
					if(Down5_1==1)
					{
						Down5_1=0;
						sprintf((char*)data,"%d;%d;%d;%d;%d;%d;%d;%d;%d;",Model_Number,value[0],value[1],value[2],value[3],value[4],value[5],value[6],value[7]);
						Record_ModifyData(12,1,Record_Number,data);
					}
					else if(Down12_4==1)
					{
						Down12_4=0;
						Record_DelData(12,1,(uint16)Record_Number);
					}
					else
					{
						for(i=3;i<strlen((const char*)msg);i++)
						{
							if(msg[i+1]!=0x3b)
							{
								if(msg[i+2]!=0x3b)
								{
									SetTextInt32(5,j[k],(msg[i]-48)*100+(msg[i+1]-48)*10+msg[i+2]-48,1,3);
									i+=3;k++;
								}
								else
								{
									SetTextInt32(5,j[k],(msg[i]-48)*10+msg[i+1]-48,1,3);
									i+=2;k++;
								}
							}
							else
							{
								
								SetTextInt32(5,j[k],msg[i]-48,1,3);
								i++;k++;
							}
						}
					}
					Record_Flag=1;
				}
			}
			if(Record_Number==0)
			{
				if(Record_Flag!=1)
				{
					if(Down12_4!=1)
					{
						sprintf((char*)data,"%d;%d;%d;%d;%d;%d;%d;%d;%d;",Model_Number,value[0],value[1],value[2],value[3],value[4],value[5],value[6],value[7]);
						Record_Add(12,1,data);
					}
					else
					{
						Down12_4=0;
					}
				}
				else
					Record_Flag=0;
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
    //���Ʊ�������
    if(screen_id == 6)
    {
        if(control_id==1 || control_id==2)
        {
            GetControlValue(6,4);                                                                
        } 
    }
    if(screen_id == 5 && control_id==1)
    {
			if(state==0)
			{
				GetControlValue(5,26);
				Down5_1=1;
			}
    }
		if(screen_id == 5 && control_id==5)
    {
			if(state==0)
			{
				GetControlValue(5,26);
				Down5_1=1;
			}
    }
		if(screen_id == 6 && control_id==7)
    {
			if(state==0)
			{
				Record_Clear(12,1);
			}
    }
		if(screen_id == 1 && control_id==4)
		{
			if(state==0)
			{
				GetControlValue(5,26);
			}
		}
		if(screen_id == 12 && control_id==4)
		{
			if(state==1)
			{
				GetControlValue(12,3);
				Down12_4=1;
			}
		}
		if(screen_id == 0 && control_id==6)
		{
			if(state==0)
			{
     			if(PassWord_OK==1&&UserName_OK==1)
					{
						SetScreen(1);
						SetTextValue(0,3,(uint8*)"");
					}
					else if(UserName_OK==0)
						SetScreen(13);
					else
						SetScreen(14);
					PassWord_OK=0;
					UserName_OK=0;
			}
		}
		if(screen_id == 15 && control_id==4)
		{
			if(state==0)
			{
					if(OldPassWord==0||ResetPassWord==0)
					{
						SetScreen(17);
						SetTextValue(15,1,(uint8*)"");
					}
					else
					{
						strcpy((char*)password,(const char*)SetPassWord);
						WriteUserFlash(0,8,password);
						SetScreen(16);
						SetTextValue(15,1,(uint8*)"");
						SetTextValue(15,2,(uint8*)"");
						SetTextValue(15,3,(uint8*)"");
					}
					OldPassWord=0;
					ResetPassWord=0;
			}
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
		uchar *err=(uchar*)"���ݴ���";
		uchar *truedata=(uchar*)"���ݺϸ�";
		int i;
    if(screen_id==5)                                                                 
    {
			switch(control_id)
			{
				case 2:
					sscanf((const char*)str,"%d",&value[0]);
					if(current_screen_id==4)
					{
						SetTextInt32(4,10,value[0],1,3);
					}
					if(current_screen_id==7)
					{
						SetTextInt32(7,4,value[0],1,3);
					}
					break;
				case 3:
					sscanf((const char*)str,"%d",&value[1]);
					if(current_screen_id==4)
					{
						SetTextInt32(4,6,110,1,3);
						SetTextInt32(4,11,value[1],1,3);
						if(value[0]>110||value[1]<110)
						{
							SetTextValue(4,2,err);
							SetControlForeColor(4,6,60);
						}
						else
						{
							SetTextValue(4,2,truedata);
							SetControlForeColor(4,6,0);
						}
					}
					if(current_screen_id==7)
					{
						SetTextInt32(7,3,110,1,3);
						SetTextInt32(7,5,value[1],1,3);
						if(value[0]>110||value[1]<110)
						{
							SetTextValue(7,1,err);
							SetControlForeColor(7,3,60);
						}
						else
						{
							SetTextValue(7,1,truedata);
							SetControlForeColor(7,3,0);
						}
					}
					break;
				case 20:
					sscanf((const char*)str,"%d",&value[2]);
					if(current_screen_id==4)
					{
						SetTextInt32(4,14,value[2],1,3);
					}
					if(current_screen_id==8)
					{
						SetTextInt32(8,4,value[2],1,3);
					}
					break;
				case 23:
					sscanf((const char*)str,"%d",&value[3]);
					if(current_screen_id==4)
					{
						SetTextInt32(4,7,30,1,3);
						SetTextInt32(4,15,value[3],1,3);
						if(value[2]>30||value[3]<30)
						{
							SetTextValue(4,4,err);
							SetControlForeColor(4,7,60);
						}
						else
						{
							SetTextValue(4,4,truedata);
							SetControlForeColor(4,7,0);
						}
					}
					if(current_screen_id==8)
					{
						SetTextInt32(8,3,30,1,3);
						SetTextInt32(8,5,value[3],1,3);
						if(value[2]>30||value[3]<30)
						{
							SetTextValue(8,1,err);
							SetControlForeColor(8,3,60);
						}
						else
						{
							SetTextValue(8,1,truedata);
							SetControlForeColor(8,3,0);
						}
					}
					break;
				case 21:
					sscanf((const char*)str,"%d",&value[4]);
					if(current_screen_id==4)
					{
						SetTextInt32(4,16,value[4],1,3);
					}
					if(current_screen_id==9)
					{
						SetTextInt32(9,4,value[4],1,3);
					}
					break;
				case 24:
					sscanf((const char*)str,"%d",&value[5]);
					if(current_screen_id==4)
					{
						SetTextInt32(4,9,40,1,3);
						SetTextInt32(4,17,value[5],1,3);
						if(value[4]>40||value[5]<40)
						{
							SetTextValue(4,5,err);
							SetControlForeColor(4,9,60);
						}
						else
						{
							SetTextValue(4,5,truedata);
							SetControlForeColor(4,9,0);
						}
					}
					if(current_screen_id==9)
					{
						SetTextInt32(9,3,40,1,3);
						SetTextInt32(9,5,value[5],1,3);
						if(value[4]>40||value[5]<30)
						{
							SetTextValue(9,1,err);
							SetControlForeColor(9,3,60);
						}
						else
						{
							SetTextValue(9,1,truedata);
							SetControlForeColor(9,3,0);
						}
					}
					break;
				case 22:
					sscanf((const char*)str,"%d",&value[6]);
					if(current_screen_id==4)
					{
						SetTextInt32(4,12,value[6],1,3);
					}
					if(current_screen_id==10)
					{
						SetTextInt32(10,4,value[6],1,3);
					}
					break;
				case 25:
					sscanf((const char*)str,"%d",&value[7]);
					if(current_screen_id==4)
					{
						SetTextInt32(4,8,50,1,3);
						SetTextInt32(4,13,value[7],1,3);
						if(value[6]>50||value[7]<50)
						{
							SetTextValue(4,3,err);
							SetControlForeColor(4,8,60);
						}
						else
						{
							SetTextValue(4,3,truedata);
							SetControlForeColor(4,8,0);
						}
					}
					if(current_screen_id==10)
					{
						SetTextInt32(10,3,50,1,3);
						SetTextInt32(10,5,value[7],1,3);
						if(value[6]>50||value[7]<50)
						{
							SetTextValue(10,1,err);
							SetControlForeColor(10,3,60);
						}
						else
						{
							SetTextValue(10,1,truedata);
							SetControlForeColor(10,3,0);
						}
					}
					break;
				case 26:
					sscanf((const char*)str,"%d",&Model_Number);
					GetControlValue(5,2);									//��ȡѹ����Сֵ
					GetControlValue(5,3);									//��ȡѹ�����ֵ
					GetControlValue(5,20);									//��ȡֱ����Сֵ
					GetControlValue(5,23);									//��ȡֱ�����ֵ
					GetControlValue(5,21);									//��ȡ�絼�����ֵ
					GetControlValue(5,24);									//��ȡ�絼�����ֵ
					GetControlValue(5,22);									//��ȡ��չ�����ֵ
					GetControlValue(5,25);									//��ȡ��չ�����ֵ
					if(current_screen_id==5)
					{
						Record_GetCount(12,1);
					}
					break;
			}
    }
		if(screen_id==6)
		{
			if(control_id==4)
			{
				i=(int)*str;
				SetPowerLevel(level[i-1]);
			}
		}
		if(screen_id==12)
		{
			if(control_id==3)
			{
				if(Down12_4==1)
				{
					sscanf((const char*)str,"%d",&Model_Number);
					Record_GetCount(12,1);
				}
			}
		}
		if(screen_id==0)
		{	
			if(control_id==3)
			{
					ReadUserFlash(0,8);
					if(!strcmp((const char*)str,(const char*)password))
						PassWord_OK=1;
			}
			if(control_id==4)
			{
					if(!strcmp((const char*)str,(const char*)username))
						UserName_OK=1;
			}
		}
		if(screen_id==15)
		{
			if(control_id==1)
			{
					if(strcmp((const char*)str,(const char*)password)==0)
						OldPassWord=1;
					else
						OldPassWord=0;
			}
			if(control_id==2)
			{			
					if(strlen((const char*)str)<=8)
					{
						strcpy((char*)SetPassWord,(const char*)str);
					}
					else
						SetTextValue(15,6,(u8*)"���벻�ܳ���8λ");
			}
			if(control_id==3)
			{
					if(strcmp((char*)SetPassWord,(const char*)str)==0)
						ResetPassWord=1;
					else
						ResetPassWord=0;
			}
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
    if(screen_id == 5)
    {
        Progress_Value = value;                                  
        SetTextInt32(5,2,Progress_Value,0,1);                                        //�����ı����ֵ     
    }    
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
		int i=0;
		u8 j[8]="12345678";
    if(status==1)
		{
			for(;i<8;i++)
			{
				if(_data[0]!=0x00)
					password[i]=_data[i];
				else
					password[i]=j[i];
			}
		}
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

}
