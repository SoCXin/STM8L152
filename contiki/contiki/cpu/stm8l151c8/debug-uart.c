#include <debug-uart.h>
#include <string.h>
#include "stm8l15x.h"
#ifndef DBG_UART
#define DBG_UART USART3
#endif

void
dbg_setup_uart_default()
{
    /* Enable USART clock */
    CLK_PeripheralClockConfig(CLK_Peripheral_USART3, ENABLE);

    /* Configure USART Tx as alternate function push-pull  (software pull up)*/
    GPIO_ExternalPullUpConfig(GPIOE, GPIO_Pin_6, ENABLE);

    /* Configure USART Rx as alternate function push-pull  (software pull up)*/
    GPIO_ExternalPullUpConfig(GPIOE, GPIO_Pin_7, ENABLE);

    /* USART configuration */
    USART_Init(DBG_UART, (uint32_t)115200,
               USART_WordLength_8b,
               USART_StopBits_1,
               USART_Parity_No,
               (USART_Mode_TypeDef)(USART_Mode_Tx | USART_Mode_Rx));
}

/**
  * @brief Retargets the C library printf function to the USART.
  * @param[in] c Character to send
  * @retval char Character sent
  * @par Required preconditions:
  * - None
  */
PUTCHAR_PROTOTYPE
{
  /* Write a character to the USART */
  USART_SendData8(USART3, c);
  /* Loop until the end of transmission */
  while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);

  return (c);
}
/**
  * @brief Retargets the C library scanf function to the USART.
  * @param[in] None
  * @retval char Character to Read
  * @par Required preconditions:
  * - None
  */
GETCHAR_PROTOTYPE
{
  int c = 0;
  /* Loop until the Read data register flag is SET */
  while (USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET);
  c = USART_ReceiveData8(USART3);
  return (c);
}
