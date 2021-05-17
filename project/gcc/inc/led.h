#ifndef E3_LED_H
#define E3_LED_H

#define LEDn 4

typedef enum {
  LED0 = 0,
  LED1,
  LED2,
  LED3,
} Led_t;

const uint32_t LED_ON_STATE[LEDn] = {GPIO_BSRR_BS0, GPIO_BSRR_BS1,
                                     GPIO_BSRR_BS2, GPIO_BSRR_BS3};
const uint32_t LED_OFF_STATE[LEDn] = {GPIO_BSRR_BR0, GPIO_BSRR_BR1,
                                      GPIO_BSRR_BR2, GPIO_BSRR_BR3};

void Leds_Init(void)
{
  // Turn on the GPIOB peripheral
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

  // Put pin 0-3 in general purpose output mode
  // clang-format off
  GPIOB->MODER |= GPIO_MODER_MODE0_0 |
                  GPIO_MODER_MODE1_0 |
                  GPIO_MODER_MODE2_0 |
                  GPIO_MODER_MODE3_0;
  // clang-format off
}

void Led_On(Led_t led)
{
  if (led < LEDn)
  {
    GPIOB->BSRR |= LED_ON_STATE[led];
  }
}

void Led_Off(Led_t led)
{
  if (led < LEDn)
  {
    GPIOB->BSRR |= LED_OFF_STATE[led];
  }
}
#endif
