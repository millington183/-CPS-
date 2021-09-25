/************************************************************************************
*  Copyright (c), 2004-2013, ������Ƕ���Ƶ������޹�˾
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: ucos-ii.c
* Project  : STM32F1XX/4XXϵ��ģ�����
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.00
* Date:    2013.3.1			
* Email:   EmbedARM@126.com
* 
* Description: ���ļ���UCOS-II����ϵͳ��Դ�ļ�;
*
* Others: none;
*
* Function List:
*		
*
* History:
*   1. Author:       EmbedARM  
*	   Version: 	 0.90
*	   Date:         2012.1.1
*      Modification: none
*
*************************************************************************************/


/************************************************************************************/
// �����ⲿͷ�ļ�
//#include "config.h"
#include "PIONEER_Config.h"
#if (UCOS_II_EN == 1)

// uC-CPU
#if (MODULE_CLASS == STM32F407XX) 
#include "../uCOS-II/uC-CPU/ARM-Cortex-M4/cpu_c.c"
#include "../uCOS-II/uC-CPU/ARM-Cortex-M4/cpu_core.c"
#else
#include "../uCOS-II/uC-CPU/ARM-Cortex-M3/cpu_c.c"
#endif


// source
#include "os_core.c"
#include "os_flag.c"
#include "os_mbox.c"
#include "os_mem.c"
#include "os_mutex.c"
#include "os_q.c"
#include "os_sem.c"
#include "os_task.c"
#include "os_time.c"
#include "os_tmr.c"



// port
#if (MODULE_CLASS == STM32F407XX) 
#include "../uCOS-II/Ports/ARM-Cortex-M4/os_cpu_c.c"
#include "../uCOS-II/Ports/ARM-Cortex-M4/os_dbg.c"
#else
#include "../uCOS-II/Ports/ARM-Cortex-M3/os_cpu_c.c"
#include "../uCOS-II/Ports/ARM-Cortex-M3/os_dbg.c"
#endif


// uc-lib
#include "lib_mem.c"
#include "lib_str.c"

#if (MODULE_CLASS == STM32F407XX) 
#include "lib_ascii.c"
#include "lib_math.c"
#endif


#endif
/***********************************************************************************/
// �ļ�����
/***********************************************************************************/

