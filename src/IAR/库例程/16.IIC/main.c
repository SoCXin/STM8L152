/*******************************************************************************
*******************************蓝旗嵌入式系统***********************************
*************************http://lenchimcu.taobao.com****************************
********************************************************************************
****例程简介:STM8L151K4库例程GPIO例程
*******************************************************************************/
#include "stm8l15x.h"
#include "24c0x.h"
//定义LED与按键接口
#define LED1_GPIO_PORT  GPIOD
#define LED1_GPIO_PINS  GPIO_Pin_2
#define LED2_GPIO_PORT  GPIOB
#define LED2_GPIO_PINS  GPIO_Pin_0
#define LED3_GPIO_PORT  GPIOC
#define LED3_GPIO_PINS  GPIO_Pin_4

unsigned char WBuf[]={"STM8S IIC读写24C0X!\r\n"};
#define BufferSize  30
unsigned char RBuf[BufferSize];
/*******************************************************************************
****入口参数：无
****出口参数：无
****函数备注：延时函数
****版权信息：蓝旗嵌入式系统
*******************************************************************************/
void Delay(__IO uint16_t nCount)
{
    /* Decrement nCount value */
    while (nCount != 0)
    {
        nCount--;
    }
}

/*******************************************************************************
****入口参数：无
****出口参数：无
****函数备注：
****版权信息：蓝旗嵌入式系统
*******************************************************************************/
int main( void )
{
    GPIO_Init(LED1_GPIO_PORT, LED1_GPIO_PINS, GPIO_Mode_Out_PP_Low_Slow);//初始化LED1接口
    CLK_PeripheralClockConfig (CLK_Peripheral_I2C1,ENABLE);//开启IIC1时钟
    
     //UART_Init();  
  //Send_Str("STM8S IIC读写测试:\r\n");
  
  InitIIC();
  EEPROM_WriteData(WBuf,EEPROM_BASE_ADDRESS,BufferSize);
  EEPROM_ReadData(RBuf,EEPROM_BASE_ADDRESS,BufferSize);
 
  //Send_Str(RBuf);
    while(1)
    {
        GPIO_ToggleBits(LED1_GPIO_PORT, LED1_GPIO_PINS);//翻转LED1接口电平，实现LED1闪烁
        Delay(0xFFFF);//延时，便于观察实验现象
    }

}

/*******************************************************************************
*******************************蓝旗嵌入式系统***********************************
*************************http://lenchimcu.taobao.com****************************
*******************************************************************************/
