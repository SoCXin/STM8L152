#include <stdio.h>
#include <stdint.h>
#include "STM8L15.h"
#include "delay.h"

#define EXTI_PIN1   9
void EXTI_init(void);

void GPIO_init(void)
{
    PE_DDR = 0x80;  /* Config PE port direction register PE7 output */
    PE_CR1 = 0x80;  /* Set PE7 as pull-push output */

}

#if 1
void EXTI_init(void)
{
//    PC_DDR = 0x0;     /* Set PortC as input */
 //   PC_CR1 = 0x02;  /* Set PC1 as input with pull-up */
    PC_DDR &= ~(0x02);
    PC_CR1 &= ~(0x02);
    PC_CR2 = 0x02;  /* Enable PC1 external interrupt */
//    CFG_GCR = (1<<1); /* Interrupt only activation mode */
}
#endif

int main()
{
    __asm__("sim");     /* Disable interrupt */
    CLK_DIVR = 0x00; /* Set Clock to 16MHz */

    GPIO_init();
    EXTI_init();
    __asm__("rim");     /* Enable interrupt */


    while(1) {
#if 0
        if(PC_IDR & 0x02)
            PE_ODR = 0x80;
        else
            PE_ODR = 0x00;
#endif
    }
}

void exti_pin1_isr(void) __interrupt(EXTI_PIN1)
{
    if(PC_IDR & (1<<1)) {
        PE_ODR &= ~(0x80);
    }
    else {
        PE_ODR |= 0x80;
    }
}
