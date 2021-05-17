#ifndef E3_WATCHDOG_H
#define E3_WATCHDOG_H
#include "common.h"

IWDG_HandleTypeDef WD_Handle;

E3_Status_t WD_Init(void)
{
  E3_Status_t ret = E3_OK;

  WD_Handle.Instance = IWDG;
  // watchdog timeout 2.0s
  // prescaler = 32
  // reload = 2048 = 0.5s / (32 / 32768)
  WD_Handle.Init.Prescaler = IWDG_PRESCALER_32;
  WD_Handle.Init.Reload = 512U;  // 0.5sec
  if (HAL_IWDG_Init(&WD_Handle) != HAL_OK) {
    ret = E3_ERR;
  }

  return ret;
}

void WD_Refresh(void) { HAL_IWDG_Refresh(&WD_Handle); }

#endif
