#ifndef __EEPROM_H
#define __EEPROM_H
#include "sys.h"
#include "PIONEER_Config.h"

#define AT24C01		127
#define AT24C02		255
#define AT24C04		511
#define AT24C08		1023
#define AT24C16		2047
#define AT24C32		4095
#define AT24C64	  8191
#define AT24C128	16383
#define AT24C256	32767  



//#define EE_TYPE AT24C64
					  
u8 EEPROM_ReadOneByte(u16 ReadAddr);							//指定地址读取一个字节
void EEPROM_WriteOneByte(u16 WriteAddr,u8 DataToWrite);		//指定地址写入一个字节
void EEPROM_WriteLenByte(u16 WriteAddr,u32 DataToWrite,u8 Len);//指定地址开始写入指定长度的数据
u32 EEPROM_ReadLenByte(u16 ReadAddr,u8 Len);					//指定地址开始读取指定长度数据
void EEPROM_Write(u16 WriteAddr,u8 *pBuffer,u16 NumToWrite);	//从指定地址开始写入指定长度的数据
void EEPROM_Read(u16 ReadAddr,u8 *pBuffer,u16 NumToRead);   	//从指定地址开始读出指定长度的数据

u8 EEPROM_Check(void);  //检查器件

void EEPROM_Init(void); //初始化IIC




#endif



