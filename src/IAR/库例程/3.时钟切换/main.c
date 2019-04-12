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
/*******************************************************************************
****入口参数：无
****出口参数：无
****函数备注：不精确延时函数
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
****函数备注：系统上电默认时钟为HSI/8=2M，根据LED闪烁频率来判断时钟源切换是否成功
              采用方法的是手动切换时钟源
****版权信息：蓝旗嵌入式系统
*******************************************************************************/
int main( void )
{
    uint8_t i;  
   
    GPIO_Init(LED_GPIO_PORT, LED_GPIO_PINS, GPIO_Mode_Out_PP_Low_Slow);//初始化LED端口
    
    //系统时钟为HSI 16M
    CLK_HSICmd(ENABLE);//开始内部高频RC，16M
    CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSI);//HSI为系统时钟
    CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);//不分频,16M 
    for(i=0;i<10;i++)
    {
       GPIO_ToggleBits(LED_GPIO_PORT, (GPIO_Pin_TypeDef)LED_GPIO_PINS);//翻转LED状态
       Delay(0xFFFF);
    }
    //系统时钟为HSI/8=2M
    CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_8);//8分频，16M/8=2M
    for(i=0;i<10;i++)
    {
       GPIO_ToggleBits(LED_GPIO_PORT, (GPIO_Pin_TypeDef)LED_GPIO_PINS);//翻转LED状态
       Delay(0xFFFF);
    }
    
    //以下为HSE为系统时钟    16M
    CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSE);//系统主时钟为HSE
    
    while(CLK_GetFlagStatus(CLK_FLAG_HSERDY)==RESET);//等待HSE准备就绪
    CLK_SYSCLKSourceSwitchCmd(ENABLE);//使能切换
    
    if(CLK_GetSYSCLKSource()==CLK_SYSCLKSource_HSE)//如果切换成功
    {
       CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_2);//2分频,8M
       for(i=0;i<10;i++)
       {
          GPIO_ToggleBits(LED_GPIO_PORT, LED_GPIO_PINS);
          Delay(0xFFFF);
        }
    }
    
    //以下为LSE为系统时钟    32768
    CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_LSE);//系统主时钟为LSE
    
    while(CLK_GetFlagStatus(CLK_FLAG_LSERDY)==RESET);//等待LSE准备就绪
    CLK_SYSCLKSourceSwitchCmd(ENABLE);//使能切换
    
    if(CLK_GetSYSCLKSource()==CLK_SYSCLKSource_LSE)//如果切换成功
    {
       CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);//
       for(i=0;i<2;i++)
       {
          GPIO_ToggleBits(LED_GPIO_PORT, LED_GPIO_PINS);
          Delay(0x0FFF);
        }
    }
    
    
    //以下为LSI为系统时钟 32K
    while(1)
    {
        CLK_LSICmd (ENABLE);    //使能LSI
        CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_LSI);//LSI为系统时钟
        while(CLK_GetFlagStatus(CLK_FLAG_LSIRDY)==RESET);//等待LSI准备就绪
        CLK_SYSCLKSourceSwitchCmd (ENABLE);//使能切换
        if(CLK_GetSYSCLKSource()==CLK_SYSCLKSource_LSI)//如果切换成功
       {
          
          CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);//不分频  
          for(i=0;i<2;i++)
          {
             GPIO_ToggleBits(LED_GPIO_PORT, (GPIO_Pin_TypeDef)LED_GPIO_PINS);
             Delay(0x0FFF);
          }  
       }  
    }
}

/*******************************************************************************
*******************************蓝旗嵌入式系统***********************************
*************************http://lenchimcu.taobao.com****************************
*******************************************************************************/
