/*******************************************************************************
*******************************蓝旗嵌入式系统***********************************
*************************http://lenchimcu.taobao.com****************************
********************************************************************************
****例程简介:STM8L151K4库例程工程Demo
*******************************************************************************/
#include "stm8l15x.h"
//定义LED和按键接口
#define LED_GPIO_PORT  GPIOA
#define LED_GPIO_PINS  GPIO_Pin_6
#define KEY_GPIO_PORT  GPIOB
#define KEY_GPIO_PINS  GPIO_Pin_4
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
****函数备注：时钟配置函数函数
****版权信息：蓝旗嵌入式系统
*******************************************************************************/
void CLK_Config(void)
{
  
  /* Select HSE as system clock source */
  CLK_SYSCLKSourceSwitchCmd(ENABLE);//使能时钟切换
  CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_LSI);//选择外部低速时钟作为时钟源
  /* system clock prescaler: 1*/
  CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);//设置系统时钟分频
  while (CLK_GetSYSCLKSource() != CLK_SYSCLKSource_LSI)//等待时钟稳定
  {}
}
/*******************************************************************************
****入口参数：无
****出口参数：无
****函数备注：等待模式有两种WFI/WFE，分别指等待中断/等待事件，等待模式CPU停止，但是
              外设和中断控制器会继续工作；进入等待模式后，中断总开关自动打开；
              时钟尽量频率低；GPIO尽量输出低电平；
              实测电流大约200ua左右
              WFE等待的事件如果是中断，则不会进入中断响应函数
****版权信息：蓝旗嵌入式系统
*******************************************************************************/
int main( void )
{
    CLK_Config();//切换LSI为主时钟
    
    //不使用的IO全部设置为输出低电平
    GPIO_Init(GPIOA, GPIO_Pin_All, GPIO_Mode_Out_PP_Low_Slow);
    GPIO_Init(GPIOB, GPIO_Pin_All, GPIO_Mode_Out_PP_Low_Slow);
    GPIO_Init(GPIOC, GPIO_Pin_All, GPIO_Mode_Out_PP_Low_Slow);
    GPIO_Init(GPIOD, GPIO_Pin_All, GPIO_Mode_Out_PP_Low_Slow);
  
    GPIO_Init(LED_GPIO_PORT, LED_GPIO_PINS, GPIO_Mode_Out_PP_Low_Slow);//GPIO初始化
    GPIO_Init(KEY_GPIO_PORT, KEY_GPIO_PINS, GPIO_Mode_In_PU_IT);//初始化按键，GPB4上拉输入
      
    WFE_DeInit ();
    WFE_WakeUpSourceEventCmd (WFE_Source_EXTI_EV4,ENABLE);//指定外部中断4为等待的事件
    
    while(1)
    {
         
        EXTI_ClearITPendingBit (EXTI_IT_Pin4);//清中断标志
        GPIO_ToggleBits(LED_GPIO_PORT, (GPIO_Pin_TypeDef)LED_GPIO_PINS);//翻转LED端口电平
        Delay(0x00FF);
        
        wfe();
    }
}

/*******************************************************************************
*******************************蓝旗嵌入式系统***********************************
*************************http://lenchimcu.taobao.com****************************
*******************************************************************************/
