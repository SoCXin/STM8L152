/*******************************************************************************
*******************************蓝旗嵌入式系统***********************************
*************************http://lenchimcu.taobao.com****************************
********************************************************************************
****例程简介:STM8L151K4库例程RTC例程
*******************************************************************************/
#include "stm8l15x.h"
#include "1621.h"


typedef uint8_t* string;
unsigned char Ht1621Tab[]={0x00,0x00,0x00,0x00};
//定义RTC
RTC_InitTypeDef   RTC_InitStr;
RTC_TimeTypeDef   RTC_TimeStr;
RTC_DateTypeDef   RTC_DateStr;
RTC_AlarmTypeDef  RTC_AlarmStr;
/* Days names definition */
CONST string WeekDayNames[7] =
  {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT" };

/* Months names definition */
CONST   uint8_t MonthNames[] = {'J', 'A', 'N', 'F', 'E', 'B', 'M', 'A', 'R', 'A', 'P', 'R',
                                  'M', 'A', 'Y', 'J', 'U', 'N', 'J', 'U', 'L', 'A', 'U', 'G',
                                  'S', 'E', 'P', 'O', 'C', 'T', 'N', 'O', 'V', 'D', 'E', 'C'};
/*******************************************************************************
****函数名称:
****函数功能:不精确延时函数
****版本:V1.0
****日期:14-2-2014
****入口参数:需要延时的数目
****出口参数:无
****说明:
********************************************************************************/
void Delay(uint16_t nCount)
{
  while (nCount != 0)
  {   
    nCount--;
  }
}
/*******************************************************************************
****入口参数：无
****出口参数：无
****函数备注：RTC初始化函数
****版权信息：蓝旗嵌入式系统
*******************************************************************************/
void Calendar_Init(void)
{
  RTC_InitStr.RTC_HourFormat = RTC_HourFormat_24;
  RTC_InitStr.RTC_AsynchPrediv = 0x7F;
  RTC_InitStr.RTC_SynchPrediv = 0x00FF;
  RTC_Init(&RTC_InitStr);

  RTC_DateStructInit(&RTC_DateStr);
  RTC_DateStr.RTC_WeekDay = RTC_Weekday_Friday;
  RTC_DateStr.RTC_Date = 13;
  RTC_DateStr.RTC_Month = RTC_Month_May;
  RTC_DateStr.RTC_Year = 11;
  RTC_SetDate(RTC_Format_BIN, &RTC_DateStr);

  RTC_TimeStructInit(&RTC_TimeStr);
  RTC_TimeStr.RTC_Hours   = 01;
  RTC_TimeStr.RTC_Minutes = 00;
  RTC_TimeStr.RTC_Seconds = 00;
  RTC_SetTime(RTC_Format_BIN, &RTC_TimeStr);


  RTC_AlarmStructInit(&RTC_AlarmStr);
  RTC_AlarmStr.RTC_AlarmTime.RTC_Hours   = 01;
  RTC_AlarmStr.RTC_AlarmTime.RTC_Minutes = 01;
  RTC_AlarmStr.RTC_AlarmTime.RTC_Seconds = 00;
  RTC_AlarmStr.RTC_AlarmMask = RTC_AlarmMask_DateWeekDay;
  RTC_SetAlarm(RTC_Format_BIN, &RTC_AlarmStr);

  RTC_ITConfig(RTC_IT_ALRA, ENABLE);
  RTC_AlarmCmd(ENABLE);
}

/*******************************************************************************
****入口参数：无
****出口参数：无
****函数备注：RTC测试程序，时间在液晶屏幕显示
****版权信息：蓝旗嵌入式系统
*******************************************************************************/
int main( void )
{
    unsigned short temp1,temp2;
    
    CLK_RTCClockConfig(CLK_RTCCLKSource_LSE, CLK_RTCCLKDiv_1);//RTC时钟源
    CLK_PeripheralClockConfig (CLK_Peripheral_RTC,ENABLE);//开启RTC时钟
    
    RTC_DeInit( ); //RTC相关设置复位到默认状态
    Calendar_Init();//RTC初始化
       
    Delay(100);           //延时一段时间 
    Ht1621_Init();        //上电初始化LCD 
    Delay(100);           //延时一段时间 
    Ht1621WrAllData(0,Ht1621Tab,16);// 清屏
  
    while (1)
    {
        RTC_GetTime(RTC_Format_BIN, &RTC_TimeStr);//获取RTC当前时间
        temp1 = RTC_TimeStr.RTC_Seconds;//秒
        temp2=RTC_TimeStr.RTC_Minutes;  //分
        data_convertor(temp2*100+temp1);//转换为显示值
        Display();                      //显示时间
        Display_lcd_dot();              //显示符号
       
    }

}

/*******************************************************************************
*******************************蓝旗嵌入式系统***********************************
*************************http://lenchimcu.taobao.com****************************
*******************************************************************************/
