// clang-format off
#include "stm32f2xx.h"

#include "common.h"
#include "clock.h"
#include "interrupts.h"
#include "led.h"
#include "uart.h"
#include "utils.h"
#include "watchdog.h"
// clang-format on

void Board_Init(void)
{
  HAL_Init();

  // Set clocks to 120MHz
  Clocks_Init();
  Leds_Init();

  // Watchdog
  if (WD_Init() != E3_OK)
  {
    Handle_Error(E3_ERR);
  }

  // UART
  if (Uart_Init() != E3_OK) {
    Handle_Error(E3_ERR);
  }

  // printf w/o buffering
  setvbuf(stdout, NULL, _IONBF, 0);
}

int main(void)
{
  // init phase
  Board_Init();

  // runtime phase
  printf("Board initialized with clock freq %lu.\r\n", SystemCoreClock / 1000000U);

  uint32_t u32_lastTickMs = HAL_GetTick();
  while (1) {
    WD_Refresh();

    Led_On(LED0);
    HAL_Delay(200);

    Led_Off(LED0);
    HAL_Delay(200);

    uint32_t u32_nowTickMs = HAL_GetTick();
    uint32_t u32_loopTimeMs = (u32_nowTickMs - u32_lastTickMs);
    u32_lastTickMs = u32_nowTickMs;

    // printf takes ~20ms
    printf("Loop took %lums \r\n", (u32_loopTimeMs));
  }

  return 0;
}
