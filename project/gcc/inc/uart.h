#ifndef E3_UART_H
#define E3_UART_H
#include "common.h"
#include "syscalls.h"

UART_HandleTypeDef Uart_Handle;

// UART3 TX->PC11 RC->PC10
E3_Status_t Uart_Init(void)
{
  E3_Status_t ret = E3_OK;

  GPIO_InitTypeDef GPIO_InitStruct;

  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_UART4_CLK_ENABLE();

  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

  /* UART TX GPIO pin configuration  */
  GPIO_InitStruct.Pin = GPIO_PIN_11;
  GPIO_InitStruct.Alternate = GPIO_AF8_UART4;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* UART RX GPIO pin configuration  */
  GPIO_InitStruct.Pin = GPIO_PIN_10;
  GPIO_InitStruct.Alternate = GPIO_AF8_UART4;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  Uart_Handle.Instance = UART4;
  Uart_Handle.Init.BaudRate = 9600;
  Uart_Handle.Init.WordLength = UART_WORDLENGTH_8B;
  Uart_Handle.Init.StopBits = UART_STOPBITS_1;
  Uart_Handle.Init.Parity = UART_PARITY_NONE;
  Uart_Handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  Uart_Handle.Init.Mode = UART_MODE_TX_RX;

  if (HAL_UART_Init(&Uart_Handle) != HAL_OK) {
    ret = E3_ERR;
  }
  return ret;
}

#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

PUTCHAR_PROTOTYPE
{
#ifdef DEBUG_UART
  HAL_UART_Transmit(&Uart_Handle, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
#endif
  return ch;
}

#endif
