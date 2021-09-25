#ifndef __IO_
#define __IO_

#include "sys.h"

//DIN端口定义
#define DI_NUM 8     // 定义DI输入数量

#define DI1 PDin(8)		 
#define DI2 PDin(9)
#define DI3 PDin(10)
#define DI4 PDin(11)
#define DI5 PDin(12)
#define DI6 PDin(13)
#define DI7 PDin(14)
#define DI8 PDin(15)

//OUT端口定义
#define DO_NUM 8       // 定义DO输出端口数量 

#define DO1 PEout(8)		 
#define DO2 PEout(9)
#define DO3 PEout(10)
#define DO4 PEout(11)
#define DO5 PEout(12)
#define DO6 PEout(13)
#define DO7 PEout(14)
#define DO8 PEout(15)

//LED端口定义
#define LED1 PAout(4)	
#define LED2 PAout(5)	 


//BEEP端口定义
#define BEEP PEout(2)

void IN_Init(void);
void OUT_Init(void);
void LED_Init(void);
void BEEP_Init(void);







#endif


