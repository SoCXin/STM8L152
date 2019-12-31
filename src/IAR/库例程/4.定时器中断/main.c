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
****函数备注：大约1SLED会翻转一次，具体原理请见代码注释；
****版权信息：蓝旗嵌入式系统
*******************************************************************************/
int main( void )
{
    GPIO_Init(LED_GPIO_PORT, LED_GPIO_PINS, GPIO_Mode_Out_PP_Low_Slow);//初始化LED，GPD4低速推挽输出
    CLK_PeripheralClockConfig (CLK_Peripheral_TIM4,ENABLE); //使能外设时钟，STM8L默认所有外设时钟初始时关闭，使用前徐开启
       
    TIM4_TimeBaseInit(TIM4_Prescaler_128, 0xff);//16M/8/128=15.625K，0xff=255,255*（1/15.625）=0.01632S，大约61次中断是1S
    TIM4_ITConfig(TIM4_IT_Update, ENABLE);//向上溢出中断，中断函数向量号为25
    TIM4_Cmd(ENABLE);//使能
    enableInterrupts();
    while(1)
    {
      
    }
    
    
}
