#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32vldiscovery.h"

void delay(vu32 nCount);

int main(void)
{

   /* Structure declaration */
   GPIO_InitTypeDef GPIOB_InitStructure;
   GPIO_InitTypeDef GPIOC_InitStructure;

   /* Enable clocks */
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

   /* Define B peripherals */
   /* PB9 (I2C1 SDA) a PB8 (I2C1 CLK) */
   GPIO_StructInit(&GPIOB_InitStructure);
   GPIOB_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_8;
   GPIOB_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
   GPIOB_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
   GPIO_Init(GPIOB, &GPIOB_InitStructure);

   /* Define C peripherals */
   /* PC8 LD4 [Blue], PC9 LD3 [Green] */
   GPIO_StructInit(&GPIOC_InitStructure);
   GPIOC_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
   GPIOC_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
   GPIOC_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
   GPIO_Init(GPIOC, &GPIOC_InitStructure);

   while (1) {
      GPIO_SetBits(GPIOC, GPIO_Pin_8);
      GPIO_ResetBits(GPIOC, GPIO_Pin_9);
      delay(5000000);
      GPIO_ResetBits(GPIOC, GPIO_Pin_8);
      GPIO_SetBits(GPIOC, GPIO_Pin_9);
      delay(5000000);
   }
}

void delay(vu32 nCount)
{
   for (; nCount != 0; nCount--)
      ;
}
