#include "stm8l15x.h"
#include "1621.h"
unsigned int tmp;
unsigned int n1, n2, n3, n4;
unsigned char DispTab[]={0xEB,0x0A,0xAD,0x8F,0x4E,0xC7,0xE7,0x8A,0xEF,0xCF,0x85,0xEE, 0x67, 0xE1,0x2F,0xE5,0xE4};
//基础操作定义
void Ht1621_CS_0() { GPIO_Init(Ht1621_CS_PORT, Ht1621_CS_PIN, GPIO_Mode_Out_PP_Low_Fast);}  // 
void Ht1621_CS_1() { GPIO_Init(Ht1621_CS_PORT, Ht1621_CS_PIN, GPIO_Mode_Out_PP_High_Fast);}

void Ht1621_WR_0() { GPIO_Init(Ht1621_WR_PORT, Ht1621_WR_PIN, GPIO_Mode_Out_PP_Low_Fast);}  // 
void Ht1621_WR_1() { GPIO_Init(Ht1621_WR_PORT, Ht1621_WR_PIN, GPIO_Mode_Out_PP_High_Fast);}

void Ht1621_DAT_0() { GPIO_Init(Ht1621_DAT_PORT, Ht1621_DAT_PIN, GPIO_Mode_Out_PP_Low_Fast);}  // 
void Ht1621_DAT_1() { GPIO_Init(Ht1621_DAT_PORT, Ht1621_DAT_PIN, GPIO_Mode_Out_PP_High_Fast);}

void Ht1621_GND_0() { GPIO_Init(Ht1621_GND_PORT, Ht1621_GND_PIN, GPIO_Mode_Out_PP_Low_Slow);}  //
void Ht1621_GND_1() { GPIO_Init(Ht1621_GND_PORT, Ht1621_GND_PIN, GPIO_Mode_Out_PP_High_Fast);}

void Ht1621_VCC_0() { GPIO_Init(Ht1621_VCC_PORT, Ht1621_VCC_PIN, GPIO_Mode_Out_PP_Low_Fast);}  //
void Ht1621_VCC_1() { GPIO_Init(Ht1621_VCC_PORT, Ht1621_VCC_PIN, GPIO_Mode_Out_PP_High_Slow);}

/*******************************************************************************
****函数名称:
****函数功能:1621写数据函数
****版本:V1.0
****日期:14-2-2014
****入口参数:Data-要发送的数据  cnt-要发送的数据位数
****出口参数:
****说明:
********************************************************************************/
void Ht1621Wr_Data(unsigned char Data,unsigned char cnt) 
{ 
  unsigned char i; 
  for (i=0;i<cnt;i++) 
   {   
     Ht1621_WR_0(); 
     if((Data & 0x80)==0x80) 
        {Ht1621_DAT_1();}
     else 
        {Ht1621_DAT_0();}
     Ht1621_WR_1(); 
     Data<<=1; 
   } 
} 
/*******************************************************************************
****函数名称:
****函数功能:1621写指令函数
****版本:V1.0
****日期:14-2-2014
****入口参数:Cmd 命令
****出口参数:
****说明:
********************************************************************************/
void Ht1621WrCmd(unsigned char Cmd) 
{ 
   Ht1621_CS_0(); 
   Ht1621Wr_Data(0x80,4);          //写入命令标志100 
   Ht1621Wr_Data(Cmd,8);           //写入命令数据 
   Ht1621_CS_1(); 
} 
/*******************************************************************************
****函数名称:
****函数功能:1621写一个数据函数
****版本:V1.0
****日期:14-2-2014
****入口参数:Addr--地址 Data--数据
****出口参数:
****说明:
********************************************************************************/
void Ht1621WrOneData(unsigned char Addr,unsigned char Data)
{
  Ht1621_CS_0();
  Ht1621Wr_Data(0xa0,3);  //写入数据标志101
  Ht1621Wr_Data(Addr<<2,6); //写入地址数据
  Ht1621Wr_Data(Data,4); //写入数据的前四位 7  6  5  4
  Ht1621_CS_1();
}
/*******************************************************************************
****函数名称:
****函数功能:1621写整屏数据函数
****版本:V1.0
****日期:14-2-2014
****入口参数:Addr--地址 p--数据  cnt数据个数
****出口参数:
****说明:
********************************************************************************/
void Ht1621WrAllData(unsigned char Addr,unsigned char *p,unsigned char cnt)
{
  unsigned char i;
  Ht1621_CS_0();
  Ht1621Wr_Data(0xa0,3); //写入数据标志101
  Ht1621Wr_Data(Addr<<2,6); //写入地址数据
  for (i=0;i<cnt;i++)
   {
    Ht1621Wr_Data(*p,8); //写入数据
    p++;
   }
  Ht1621_CS_1();
}
/*******************************************************************************
****函数名称:
****函数功能:1621初始化函数
****版本:V1.0
****日期:14-2-2014
****入口参数:
****出口参数:
****说明:
********************************************************************************/
void Ht1621_Init(void) 
{ 
    Ht1621_GND_0();       //HT1621 power on
    Ht1621_VCC_1();
   Ht1621WrCmd(BIAS); 
   Ht1621WrCmd(RC256);             //使用内部振荡器 
   //Ht1621WrCmd(XTAL);             //使用外部振荡器 
   Ht1621WrCmd(SYSDIS); 
   Ht1621WrCmd(WDTDIS1); 
   Ht1621WrCmd(SYSEN); 
   Ht1621WrCmd(LCDON); 
} 
/*******************************************************************************
****函数名称:
****函数功能:1621显示函数
****版本:V1.0
****日期:14-2-2014
****入口参数:
****出口参数:
****说明:
********************************************************************************/
void Display(void) 
{ 
 
   Ht1621WrOneData(0 , DispTab[n4]);
   Ht1621WrOneData(1 , DispTab[n4]<<4);

   Ht1621WrOneData(2 , DispTab[n3]);
   Ht1621WrOneData(3 , DispTab[n3]<<4);
   
   Ht1621WrOneData(4 , DispTab[n2]);
   Ht1621WrOneData(5 , DispTab[n2]<<4);
  
   Ht1621WrOneData(6 , DispTab[n1]); 
   Ht1621WrOneData(7 , DispTab[n1]<<4); 
   
}
/*******************************************************************************
****函数名称:
****函数功能:显示符号函数
****版本:V1.0
****日期:14-2-2014
****入口参数:Addr--地址 Data--数据
****出口参数:
****说明:
********************************************************************************/
void Display_lcd_dot(void) 
{ 
  //Ht1621WrOneData(0 , DispTab[n4]|0x10);//P1
   Ht1621WrOneData(2 , DispTab[n3]|0x10);    //2P
   //Ht1621WrOneData(4 , DispTab[n2]|0x10);    //3P
   //Ht1621WrOneData(6 , DispTab[n1]|0x10);    //4P
}
/*******************************************************************************
****函数名称:
****函数功能:数据转换函数
****版本:V1.0
****日期:14-2-2014
****入口参数:adc_value-需要转换的数值
****出口参数:
****说明:
********************************************************************************/
void data_convertor(unsigned long adc_value) 
{  
    tmp=adc_value;         //adc 
    n4=tmp/1000;
    tmp=tmp%1000;
    n3=tmp/100;
    tmp=tmp%100;	
    n2=tmp/10;
    tmp=tmp%10;		
    n1=tmp; 
 }
