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
****函数备注：要实现最低功耗CPU的IO口要输出确定的电平；例程除了按键与LED接口其他IO全部输出低；
              还需要使用超低功耗指令；
              
              程序运行效果-LED被点亮后被HALT挂起，按键中断会唤醒，唤醒时LED被熄灭；中断结束，
              LED重新被电量，重新HALT，
              
              实测此例程
              HALT：唤醒源-中断和RESET，CPU停止，外设停止，最低功耗大约350na左右
              具体请参阅AN3147
****版权信息：蓝旗嵌入式系统
*******************************************************************************/
int main( void )
{
     PWR_FastWakeUpCmd(ENABLE);  //快速唤醒使能
     //所有IO输出低电平
    GPIO_Init(GPIOA, GPIO_Pin_All, GPIO_Mode_Out_PP_Low_Slow);
    GPIO_Init(GPIOB, GPIO_Pin_All, GPIO_Mode_Out_PP_Low_Slow);
    GPIO_Init(GPIOC, GPIO_Pin_All, GPIO_Mode_Out_PP_Low_Slow);
    GPIO_Init(GPIOD, GPIO_Pin_All, GPIO_Mode_Out_PP_Low_Slow);
    
    
    GPIO_Init(LED_GPIO_PORT, LED_GPIO_PINS, GPIO_Mode_Out_PP_Low_Slow);//GPIO初始化
    GPIO_Init(KEY_GPIO_PORT, KEY_GPIO_PINS, GPIO_Mode_In_PU_IT);//初始化按键，GPB4带上拉带中断输入
    
    
    
    EXTI_DeInit (); //恢复中断的所有设置 
    EXTI_SetPinSensitivity (EXTI_Pin_4,EXTI_Trigger_Falling);//外部中断4，下降沿触发，向量号12
    enableInterrupts();//使能中断
    
    PWR_UltraLowPowerCmd(ENABLE);//超低功耗
    while(1)
    {
        Delay(0xFFFF);
        GPIO_ResetBits (GPIOA,GPIO_Pin_6);
        halt();
    }
}

/*******************************************************************************
*******************************蓝旗嵌入式系统***********************************
*************************http://lenchimcu.taobao.com****************************
*******************************************************************************/
