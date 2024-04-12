#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32vldiscovery.h"

void delay(vu32 nCount);

int main(void)
{

   /* Structure declaration */
   GPIO_InitTypeDef GPIO_InitStructure;
   GPIO_StructInit(&GPIO_InitStructure);

   /* enable IO port C */
   // RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE)

   // PC6 SR_Dat, PC7 SR_Ow, PC8 SR_Clk, PC9 LD3 [Green]
   GPIO_InitStructure.GPIO_Pin =
       GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
   GPIO_Init(GPIOC, &GPIO_InitStructure);

   while (1) {
      delay(500000);
   }
}

void delay(vu32 nCount)
{
   for (; nCount != 0; nCount--)
      ;
}
