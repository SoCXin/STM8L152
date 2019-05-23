#include "stm8l15x.h"
#include "stm8l15x_it.h"
#include <sys/clock.h>
#include <sys/cc.h>
#include <sys/etimer.h>
#include <debug-uart.h>

static volatile clock_time_t current_clock = 0;
static volatile unsigned long current_seconds = 0;
static unsigned int second_countdown = CLOCK_SECOND;

void
SysTick_handler(void)
{
  current_clock++;
  if(etimer_pending() && etimer_next_expiration_time() <= current_clock) {
    etimer_request_poll();
    /* printf("%d,%d\n", clock_time(),etimer_next_expiration_time  	()); */

  }
  if (--second_countdown == 0) {
    current_seconds++;
    second_countdown = CLOCK_SECOND;
  }
}

void sysOscillatorInit(void)
{
    uint16_t i = 10000;    
    CLK_HSICmd(ENABLE);
    
    while(i--);
    //Wait for HIE mode oscillator ready
    while(!CLK_GetFlagStatus(CLK_FLAG_HSIRDY));
    
    //Configures the system clock (SYSCLK) - HSI mode
    CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSI);
    
    //Configures the System clock (SYSCLK) dividers - CLK_SYSCLKDiv_1
    CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_2);
    
    //Enables or disables the clock switch execution
    //If enabled, the clock switch to the source defined in thd CLK_SWR register.
    CLK_SYSCLKSourceSwitchCmd(ENABLE);
}

void
clock_init()
{
    CLK_RTCClockConfig(CLK_RTCCLKSource_LSE, CLK_RTCCLKDiv_1);
    
    //Wait for LSE mode oscillator ready
    while (CLK_GetFlagStatus(CLK_FLAG_LSERDY) == RESET);
    CLK_PeripheralClockConfig(CLK_Peripheral_RTC, ENABLE);
    
    //Configures the RTC wakeup timer_step = RTCCLK/16 = LSE/16 =  32768/16 = 2048
    RTC_WakeUpClockConfig(RTC_WakeUpClock_RTCCLK_Div16);

    //Enable wake up unit Interrupt
    RTC_ITConfig(RTC_IT_WUT, ENABLE);    
    // RTC wake-up event every 10 ms (timer_step x (20+ 1) )
    RTC_SetWakeUpCounter(20);    
    RTC_WakeUpCmd(ENABLE);
}

clock_time_t
clock_time(void)
{
  return current_clock;
}

#if 0
/* The inner loop takes 4 cycles. The outer 5+SPIN_COUNT*4. */

#define SPIN_TIME 2 /* us */
#define SPIN_COUNT (((MCK*SPIN_TIME/1000000)-5)/4)

#ifndef __MAKING_DEPS__

void
clock_delay(unsigned int t)
{
#ifdef __THUMBEL__ 
  asm volatile("1: mov r1,%2\n2:\tsub r1,#1\n\tbne 2b\n\tsub %0,#1\n\tbne 1b\n":"=l"(t):"0"(t),"l"(SPIN_COUNT));
#else
#error Must be compiled in thumb mode
#endif
}
#endif
#endif /* __MAKING_DEPS__ */

unsigned long
clock_seconds(void)
{
  return current_seconds;
}

INTERRUPT_HANDLER(RTC_CSSLSE_IRQHandler, 4)
{
    SysTick_handler();
    //Clear the periodic wakeup unit flag 
    RTC_ClearITPendingBit(RTC_IT_WUT);
}