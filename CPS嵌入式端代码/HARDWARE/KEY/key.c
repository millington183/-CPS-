#include "key.h"
#include "delay.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//����������������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 

//������ʼ������
void KEY_Init(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStructure;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOE,ENABLE);//ʹ��GPIOD,B,Eʱ��
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7; //KEY0 KEY1 KEY2 KEY3 KEY4��Ӧ���� 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//����
  GPIO_Init(GPIOD, &GPIO_InitStructure);//��ʼ��GPIOD3,4,5,6,7
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_14|GPIO_Pin_15;//KEY5 KEY6��Ӧ����
	GPIO_Init(GPIOB,&GPIO_InitStructure);//��ʼ��GPIOB14,15
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;//KEY7 KEY8 KEY9��Ӧ����
	GPIO_Init(GPIOE,&GPIO_InitStructure);//��ʼ��GPIOE0,1,2
	
} 
//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//0��û���κΰ�������
// 1��KEY0����
// 2��KEY1����
// 3��KEY2���� 
// 4��KEY3���� 
// 5��KEY4���� 
// 6��KEY5���� 
// 7��KEY6����
// 8��KEY7����
// 9��KEY8���� 
//10��KEY9���� 
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//�������ɿ���־
	if(mode)key_up=1;  //֧������		  
	if(key_up&&(KEY0==1||KEY1==1||KEY2==1|KEY3==1|KEY4==1
	|KEY5==1|KEY6==1|KEY7==1|KEY8==1|KEY9==1))
	
	{
		delay_ms(10);//ȥ���� 
		key_up=0;
		if(KEY0==1)return KEY0_PRES;
		else if(KEY1==1)return KEY1_PRES;
		else if(KEY2==1)return KEY2_PRES;
		else if(KEY3==1)return KEY3_PRES;
		else if(KEY4==1)return KEY4_PRES;
		else if(KEY5==1)return KEY5_PRES;
		else if(KEY6==1)return KEY6_PRES;
		else if(KEY7==1)return KEY7_PRES;
		else if(KEY8==1)return KEY8_PRES;
		else if(KEY9==1)return KEY9_PRES;
	}
	else if(KEY0==0&&KEY1==0&&KEY2==0&&KEY3==0
	&&KEY4==0&&KEY5==0&&KEY6==0&&KEY7==0&&KEY8==0&&KEY9==0)key_up=1; 	    
 	
	return 0;// �ް�������
}




















