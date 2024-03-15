#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32vldiscovery.h"

void delay(vu32 nCount);

void pulseClk(void);
void pulseOw(void);
void setNumber(uint8_t number);

int main(void)
{

   /* Structure declaration */
   GPIO_InitTypeDef GPIO_InitStructure;
   GPIO_StructInit(&GPIO_InitStructure);

   /* enable IO port C */
   // RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

   // PC6 SR_Dat, PC7 SR_Ow, PC8 SR_Clk, PC9 LD3 [Green]
   GPIO_InitStructure.GPIO_Pin =
       GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
   GPIO_Init(GPIOC, &GPIO_InitStructure);

   while (1) {
      uint8_t i;
      for (i = 0; i < 100; ++i) {
         setNumber(i);
         delay(500000);
      }
   }
}

void pulseClk(void)
{
   GPIO_SetBits(GPIOC, GPIO_Pin_8);
   delay(100);
   GPIO_ResetBits(GPIOC, GPIO_Pin_8);
}

void pulseOw(void)
{
   GPIO_SetBits(GPIOC, GPIO_Pin_7);
   delay(100);
   GPIO_ResetBits(GPIOC, GPIO_Pin_7);
}

void setNumber(uint8_t number)
{
   uint8_t hex1 = number / 10;
   uint8_t hex0 = number % 10;

   uint8_t numbers[10][8] = {{1, 1, 1, 1, 1, 1, 0, 0},  // 0
                             {0, 1, 1, 0, 0, 0, 0, 0},  // 1
                             {1, 1, 0, 1, 1, 0, 1, 0},  // 2
                             {1, 1, 1, 1, 0, 0, 1, 0},  // 3
                             {0, 1, 1, 0, 0, 1, 1, 0},  // 4
                             {1, 0, 1, 1, 0, 1, 1, 0},  // 5
                             {1, 0, 1, 1, 1, 1, 1, 0},  // 6
                             {1, 1, 1, 0, 0, 0, 0, 0},  // 7
                             {1, 1, 1, 1, 1, 1, 1, 0},  // 8
                             {1, 1, 1, 1, 0, 1, 1, 0}}; // 9
   uint8_t i;
   for (i = 0; i < 8; ++i) {
      if (!numbers[hex0][i])
         GPIO_SetBits(GPIOC, GPIO_Pin_6);
      else
         GPIO_ResetBits(GPIOC, GPIO_Pin_6);
      delay(100);
      pulseClk();
      delay(100);
   }
   for (i = 0; i < 8; ++i) {
      if (!numbers[hex1][i])
         GPIO_SetBits(GPIOC, GPIO_Pin_6);
      else
         GPIO_ResetBits(GPIOC, GPIO_Pin_6);
      delay(100);
      pulseClk();
      delay(100);
   }
   pulseOw();
}

void delay(vu32 nCount)
{
   for (; nCount != 0; nCount--)
      ;
}
