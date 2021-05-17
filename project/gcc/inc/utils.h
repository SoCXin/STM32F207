#ifndef E3_UTILS_H
#define E3_UTILS_H
#include "common.h"
#include "uart.h"

#define LED_ERROR LED3

void Handle_Error(E3_Status_t err)
{
  if (err != E3_OK) {
    Led_On(LED_ERROR);
  }

  while (1)
    ;
}

#endif
