#ifndef DEBUG_UART_H_1V2039076V__
#define DEBUG_UART_H_1V2039076V__

#ifndef dbg_setup_uart
#define dbg_setup_uart dbg_setup_uart_default
#endif

#define PUTCHAR_PROTOTYPE int putchar (int c)
#define GETCHAR_PROTOTYPE int getchar (void)

void
dbg_setup_uart();

#endif /* DEBUG_UART_H_1V2039076V__ */
