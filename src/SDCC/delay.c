#include "STM8L15.h"
#include <stdint.h>

#define TIM4_SR1_UIF	((uint8_t)0x01) /* Update Interrupt Flag Mask */
#define TIM4_SR1_TIF	((uint8_t)0x40) /* Trigger Interrupt Flag Mask */
#define TIM4_CR1_CEN	((uint8_t)0x01) /* Counter Enable Mask. */
#define TIM4_CR1_UDIS	((uint8_t)0x02) /* Update Disable Mask. */

void delay_ms(int ms)
{
    /* Init Timer 4 */
    //CLK_PeripheralClockConfig(CLK_Peripheral_TIM4, ENABLE);

    CLK_PCKENR1 |= 0x04;    //enable clock for TIM4, input clock = 16MHz???

    TIM4_PSCR = 0x06;       /* prescaler: (2^6) = 64 */

    TIM4_ARR = 250;         /* Preload= 250 decimal */

    /*Counter value: 2, to compensate the initialization of TIMER */
    TIM4_CNTR = 2;

    TIM4_SR1 &= ~TIM4_SR1_UIF;   /* clear update flag */

    TIM4_CR1 |= TIM4_CR1_CEN;   /* Enable counter */

    while(ms--) {
        while((TIM4_SR1 & TIM4_SR1_UIF) == 0) ;
        TIM4_SR1 &= ~TIM4_SR1_UIF;
    }

    TIM4_CR1 &= ~TIM4_CR1_CEN;   /* Disable counter */
}
