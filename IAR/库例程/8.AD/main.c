/*******************************************************************************
*******************************蓝旗嵌入式系统***********************************
*************************http://lenchimcu.taobao.com****************************
********************************************************************************
****例程简介:STM8L151K4库例程工程Demo
*******************************************************************************/
#include "stm8l15x.h"
//定义LED与按键接口
#define LED_GPIO_PORT  GPIOA
#define LED_GPIO_PINS  GPIO_Pin_6
#define KEY_GPIO_PORT  GPIOB
#define KEY_GPIO_PINS  GPIO_Pin_4

uint8_t HexTable[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
/*******************************************************************************
****入口参数：需要发送的字符串
****出口参数：无
****函数备注：USART发送函数
****版权信息：蓝旗嵌入式系统
*******************************************************************************/
void USART1_SendStr(unsigned char *Str) 
{
        while(*Str!=0)//不为结束
        {
            USART_SendData8(USART1,*Str);     //发送数据 
            while(!USART_GetFlagStatus (USART1,USART_FLAG_TXE));//等待发送完毕
            Str++;//下一个数据
        }
}
/*******************************************************************************
****入口参数：需要发送的16进制数
****出口参数：无
****函数备注：USART发送16进制函数
****版权信息：蓝旗嵌入式系统
*******************************************************************************/
void USART1_SendHex(unsigned char dat)
{
      USART_SendData8(USART1,'0');
      while(!USART_GetFlagStatus (USART1,USART_FLAG_TXE));//等待发送完毕
      USART_SendData8(USART1,'x');
      while(!USART_GetFlagStatus (USART1,USART_FLAG_TXE));//等待发送完毕
      USART_SendData8(USART1,HexTable[dat>>4]);
      while(!USART_GetFlagStatus (USART1,USART_FLAG_TXE));//等待发送完毕
      USART_SendData8(USART1,HexTable[dat&0x0f]);
      while(!USART_GetFlagStatus (USART1,USART_FLAG_TXE));//等待发送完毕
      USART_SendData8(USART1,' ');
      while(!USART_GetFlagStatus (USART1,USART_FLAG_TXE));//等待发送完毕
}
/*******************************************************************************
****入口参数：无
****出口参数：无
****函数备注：开发板上RXD-UT TXD-UR跳线帽短接，通过USB线连接计算机与开发板，打开
              计算机的串口调试助手软件，设置参数，可以接收到开发板发送的ADC处理后的
              数据。使用前计算机需先安装CH340驱动。
****版权信息：蓝旗嵌入式系统
*******************************************************************************/
int main( void )
{
     u16 u16_adc1_value;  
     CLK_PeripheralClockConfig (CLK_Peripheral_USART1,ENABLE);//开启ADC/USART时钟
     CLK_PeripheralClockConfig (CLK_Peripheral_ADC1,ENABLE);//开启ADC/USART时钟
     USART_Init(USART1,9600,USART_WordLength_8b,USART_StopBits_1,USART_Parity_No,USART_Mode_Tx);//USART初始化，9600，8N1
     USART_Cmd (USART1,ENABLE);//使能USART
     
     ADC_Init (ADC1,ADC_ConversionMode_Single,ADC_Resolution_12Bit,ADC_Prescaler_1);//单次转换，12位，转换时钟1分频
     ADC_Cmd(ADC1,ENABLE);//ADC使能
     ADC_ChannelCmd (ADC1,ADC_Channel_11,ENABLE);//使能通道11
     
     while(1)
     {
         ADC_SoftwareStartConv (ADC1);//开启软件转换
         
         USART1_SendStr("ADC转换结果为: ");
         while(!ADC_GetFlagStatus (ADC1,ADC_FLAG_EOC));//等待转换结束
         ADC_ClearFlag (ADC1,ADC_FLAG_EOC);//清除对应标志
         u16_adc1_value=ADC_GetConversionValue (ADC1);//获取转换值
         
         USART1_SendHex((u16_adc1_value>>8)); 
         USART1_SendHex((u16_adc1_value&0xff));
         
         USART1_SendStr("\r\n");//换行
     }
}

/*******************************************************************************
*******************************蓝旗嵌入式系统***********************************
*************************http://lenchimcu.taobao.com****************************
*******************************************************************************/
