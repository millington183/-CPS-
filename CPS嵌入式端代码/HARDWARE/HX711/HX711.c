#include "HX711.h"
#include "delay.h"
long HX711_Buffer = 0;
long Weight_Maopi = 0,Weight_Shiwu = 0;

#define GapValue 430
#define HIGH 1
#define LOW  0
#define HX711_GROUP GPIOB
      

void digitalWrite(GPIO_TypeDef * GPIO,int pin,int value)
{
	if(value==HIGH)//set 1
	{
		GPIO_SetBits(GPIO,pin);
	}
	if(value==LOW)//reset 0
	{
		GPIO_ResetBits(GPIO,pin);
	}
}

int digitalRead(GPIO_TypeDef * GPIO,int pin)
{
	return GPIO_ReadInputDataBit(GPIO,pin);
}

//****************************************************
//初始化HX711
//****************************************************
void Init_Hx711()
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	GPIO_InitTypeDef  GPIO_InitStructure1;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

  //SCK
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_Init(GPIOB, &GPIO_InitStructure);



  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

  //DOUT
  GPIO_InitStructure1.GPIO_Pin = GPIO_Pin_1 ;
  GPIO_InitStructure1.GPIO_Mode = GPIO_Mode_IN;
  //GPIO_InitStructure1.GPIO_OType = GPIO_OType_OD; 
  GPIO_InitStructure1.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure1.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure1);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

}


//****************************************************
//获取毛皮重量
//****************************************************
void Get_Maopi()
{
	Weight_Maopi = HX711_Read();		
} 

//****************************************************
//称重
//****************************************************
long Get_Weight()
{
	HX711_Buffer = HX711_Read();
	Weight_Shiwu = HX711_Buffer;
	Weight_Shiwu = Weight_Shiwu - Weight_Maopi;				//获取实物的AD采样数值。
	//printf("Weight_shiwu==%ld\r\n",Weight_Shiwu);
	Weight_Shiwu = (long)(Weight_Shiwu/GapValue); 
	//printf("Weight_Shiwu/GapValue=%f\r\n",(float)Weight_Shiwu/GapValue);
	return Weight_Shiwu;
}

//****************************************************
//读取HX711
//****************************************************
unsigned long HX711_Read(void)	//增益128
{
		unsigned long val = 0; 
	unsigned char i = 0; 

	//判断模块是否准备好
	while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1));
	delay_us(1);   
	//sck 拉低
	GPIO_ResetBits(GPIOB,GPIO_Pin_0);
	//再次判断是否准备好
	while(!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1));
  
	for(i=0;i<24;i++) 
	{ 
		delay_us(100); 
		GPIO_SetBits(GPIOB,GPIO_Pin_0);	   
		val=val<<1; 
		delay_us(1);  
		GPIO_ResetBits(GPIOB,GPIO_Pin_0);	   
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1))  
		val++; 
		delay_us(1); 
	} 
	GPIO_SetBits(GPIOB,GPIO_Pin_0); 
	val = val^0x800000; 
	delay_us(1); 
	GPIO_ResetBits(GPIOB,GPIO_Pin_0); 
	delay_us(1);  
	return val; 
}
