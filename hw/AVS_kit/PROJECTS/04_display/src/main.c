#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_spi.h"
#include "stm32vldiscovery.h"

void delay(vu32 nCount);

int main(void)
{

   /* Structure declaration */
   GPIO_InitTypeDef GPIOA_InitStructure;
   GPIO_InitTypeDef GPIOC_InitStructure;
   SPI_InitTypeDef SPI_InitStructure;

   /* Enable clocks */
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

   /* Define A peripherals */
   /* PA5[SPI1_SCK], PA6[SPI1_MISO], PA7[SPI1_MOSI] as alternative function */
   GPIO_StructInit(&GPIOA_InitStructure);
   GPIOA_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
   GPIOA_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIOA_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
   GPIO_Init(GPIOA, &GPIOA_InitStructure);
   /* PA4 [SPI_NSS (known as CS too)] as alternative function */
   GPIO_StructInit(&GPIOA_InitStructure);
   GPIOA_InitStructure.GPIO_Pin = GPIO_Pin_4;
   GPIOA_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIOA_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
   GPIO_Init(GPIOA, &GPIOA_InitStructure);

   /* Define C peripherals */
   /* PC8 LD4 [Blue], PC9 LD3 [Green] */
   GPIO_StructInit(&GPIOC_InitStructure);
   GPIOC_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
   GPIOC_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
   GPIOC_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
   GPIO_Init(GPIOC, &GPIOC_InitStructure);

   /* SPI1 configuration */
   SPI_StructInit(&SPI_InitStructure);
   SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
   SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
   SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
   SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
   SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
   SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
   SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
   SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
   SPI_InitStructure.SPI_CRCPolynomial = 7;
   SPI_Init(SPI1, &SPI_InitStructure);

   /* Enable the SPI1  */
   SPI_Cmd(SPI1, ENABLE);

   while (1) {
      GPIO_SetBits(GPIOC, GPIO_Pin_8);
      GPIO_ResetBits(GPIOC, GPIO_Pin_9);
      delay(1000000);
      GPIO_ResetBits(GPIOC, GPIO_Pin_8);
      GPIO_SetBits(GPIOC, GPIO_Pin_9);
      delay(1000000);
   }
}

void delay(vu32 nCount)
{
   for (; nCount != 0; nCount--)
      ;
}
