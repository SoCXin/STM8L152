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
****函数备注：非精确延时函数
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
****函数备注：RTC配置函数
****版权信息：蓝旗嵌入式系统
*******************************************************************************/
void RTC_Config(void)
{
        CLK_LSEConfig(CLK_LSE_ON);//RTC时钟源选择
        CLK_RTCClockConfig(CLK_RTCCLKSource_LSE, CLK_RTCCLKDiv_1);//RTC时钟分频
        while (CLK_GetFlagStatus(CLK_FLAG_LSERDY) == RESET);//等待时钟源就绪
        
        RTC_WakeUpCmd(DISABLE);//关闭RTC唤醒
        CLK_PeripheralClockConfig(CLK_Peripheral_RTC, ENABLE);//RTC时钟门控使能
        RTC_WakeUpClockConfig(RTC_WakeUpClock_RTCCLK_Div16);//RTC唤醒时钟分频
        RTC_ITConfig(RTC_IT_WUT, ENABLE);//RTC唤醒中断使能
        RTC_SetWakeUpCounter(2047);

        ITC_SetSoftwarePriority(RTC_IRQn, ITC_PriorityLevel_3);//优先级
        
        enableInterrupts();//使能中断
}
/*******************************************************************************
****入口参数：无
****出口参数：无
****函数备注：要实现最低功耗CPU的IO口要输出确定的电平；例程除了按键与LED接口其他IO全部输出低；
              还需要使用超低功耗指令；
                            
              实测此例程
              ACTIVE-HALT：主振荡器/CPU/大多数外设停止；LSI/LSE运行；BEEP/IWDG/RTC/LCD的一个或多个
              使能，即可通过HALT指令进入ACTIVD-HALT模式；
              
              休眠时实测电流大约1.4ua
              RTC中断唤醒，LED以一定频率闪烁
              具体请参阅AN3147
****版权信息：蓝旗嵌入式系统
*******************************************************************************/
int main( void )
{
     PWR_FastWakeUpCmd(ENABLE);  //快速唤醒使能
     RTC_Config();
     //所有IO输出低电平
    GPIO_Init(GPIOA, GPIO_Pin_All, GPIO_Mode_Out_PP_Low_Slow);
    GPIO_Init(GPIOB, GPIO_Pin_All, GPIO_Mode_Out_PP_Low_Slow);
    GPIO_Init(GPIOC, GPIO_Pin_All, GPIO_Mode_Out_PP_Low_Slow);
    GPIO_Init(GPIOD, GPIO_Pin_All, GPIO_Mode_Out_PP_Low_Slow);
       
    PWR_UltraLowPowerCmd(ENABLE);//超低功耗
    
    RTC_ITConfig(RTC_IT_WUT, ENABLE);//唤醒定时器中断使能
    RTC_WakeUpCmd(ENABLE);//RTC唤醒使能
    
    while(1)
    {
        halt();
    }
}

/*******************************************************************************
*******************************蓝旗嵌入式系统***********************************
*************************http://lenchimcu.taobao.com****************************
*******************************************************************************/
