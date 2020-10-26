#include "stm8l15x.h"
#include "debug-uart.h"
#include "clock.h"
#include "sys/process.h"
#include "sys/procinit.h"
#include "etimer.h"
#include "sys/autostart.h"

void led_init();
unsigned int idle_count  = 0;

PROCESS(blink_process, "blink");
AUTOSTART_PROCESSES(&blink_process);

PROCESS_THREAD(blink_process, ev, data)
{
    PROCESS_BEGIN();
    while(1)
    {
        static struct etimer et;
        etimer_set(&et, CLOCK_SECOND);
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
        // open LED
        GPIO_ResetBits(GPIOF, GPIO_Pin_0);
        printf("LED ON\r\n");
        etimer_set(&et, CLOCK_SECOND);
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
        // close LED
        GPIO_SetBits(GPIOF, GPIO_Pin_0);
        printf("LED OFF\r\n");
    }
    PROCESS_END();
}

void  main( void )
{
    sysOscillatorInit();
    dbg_setup_uart();
    led_init();
    printf("Initialising\r\n");
    clock_init();
    process_init();
    process_start(&etimer_process, NULL);
    autostart_start(autostart_processes);
    printf("Processes running\r\n");
    enableInterrupts();
    while(1)
    {
        do{

        }
        while(process_run() > 0);
        idle_count++;
    }
}

void led_init()
{
    GPIO_Init(GPIOB, GPIO_Pin_0, GPIO_Mode_Out_PP_High_Slow);
    GPIO_Init(GPIOF, GPIO_Pin_0, GPIO_Mode_Out_PP_High_Slow);
    GPIO_ResetBits(GPIOB, GPIO_Pin_0);
    GPIO_ResetBits(GPIOF, GPIO_Pin_0);
}
