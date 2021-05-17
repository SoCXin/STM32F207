#ifndef E3_INTERRUPTS_H
#define E3_INTERRUPTS_H

void SysTick_Handler(void)
{
  HAL_IncTick();
}

#endif
