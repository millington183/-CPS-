#ifndef __TIMER_
#define __TIMER_
#include "sys.h"
#include "stm32f4xx_conf.h"
#include "PIONEER_Config.h"

/***********************************************************************************
* Function: Timerx_Init;
*
* Description: TIMER初始化函数;
* 
* Input:  none;
*
* Output: none;
*          		
* Return:none;
*
* Note:   none;
************************************************************************************/

/***********************************************************************************
* Function: TIM_Init;
*
* Description: Tiner2~Timer7初始化函数;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/

void TIM2_Init(void);
void TIM3_Init(void);
void TIM4_Init(void);
void TIM5_Init(void);
void TIM6_Init(void);
void TIM7_Init(void);





#endif



