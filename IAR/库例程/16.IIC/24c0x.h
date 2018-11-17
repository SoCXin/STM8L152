#ifndef _iic_h_
#define _iic_h_
/*******************************************************************************
****蓝旗嵌入式系统 STM8S105 EasyKit
****LENCHIMCU.TAOBAO.COM
****版本:V1.0
****日期:14-2-2014
****说明:主芯片STM8S105C4T6
********************************************************************************/
#define IICSPEED 100000       //100K速度，时钟速度至少1M，400K速度，时钟速度至少4M
#define I2C1_SLAVE_ADDRESS7    0xA0
#define EEPROM_BASE_ADDRESS    0x02
#define EEPROM_Page_Byte_Size  8   /*EEPROM 每页最多写8Byte*/
#define EEPROM_ADDRESS         0xA0
extern void InitIIC(void);
extern void EEPROM_WriteData(unsigned char *buffer,unsigned char addr,unsigned char num);
extern void EEPROM_ReadData(unsigned char *buffer,unsigned char addr,unsigned char num);

#endif