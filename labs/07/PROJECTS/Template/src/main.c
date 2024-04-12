#include "stm32f10x.h"
#include "stm32vldiscovery.h"

void delay(vu32 nCount);

int main(void)
{
   int pom;
   /* enable IO port C */
   RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;

   /* configure GPIOC (PC9: output, 2MHz, push-pull) */
   GPIOC->CRH = 0x44444424;
   GPIOC->BSRR = GPIO_BSRR_BR9;

   /* program loop */
   STM32vldiscovery_LEDInit(LED4);
   STM32vldiscovery_PBInit(Button_USER, BUTTON_MODE_GPIO);

   while (1) {
      GPIOC->BSRR = GPIO_BSRR_BR9;
      delay(0x0FFFFF);

      GPIOC->BSRR = GPIO_BSRR_BS9;
      delay(0x0FFFFF);

      pom = STM32vldiscovery_PBGetState(Button_USER);

      if (pom == 1)
         STM32vldiscovery_LEDOn(LED4);
      else
         STM32vldiscovery_LEDOff(LED4);
   }
}

void delay(vu32 nCount)
{
   for (; nCount != 0; nCount--)
      ;
}
