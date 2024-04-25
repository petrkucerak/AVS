#include "lcd_graph_commands.h"
#include "lcd_symbols.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_spi.h"
#include "stm32vldiscovery.h"

#define SMALL_DELAY 50

void delay(vu32 nCount);
static void LCD_SendByte(uint8_t byte);
static void LCD_SendCommand(uint8_t byte);
static void LCD_SendData(uint8_t byte);
static void LCD_ClearDisplay(void);
static void LCD_SetPos(uint8_t line, uint8_t column);
static void LCD_DisplayChar(uint8_t column, uint16_t line, uint8_t ascii);

int main(void)
{

   /* Structure declaration */
   GPIO_InitTypeDef GPIOA_InitStructure;
   GPIO_InitTypeDef GPIOB_InitStructure;
   GPIO_InitTypeDef GPIOC_InitStructure;
   GPIO_InitTypeDef GPIOD_InitStructure;
   SPI_InitTypeDef SPI_InitStructure;

   /* Enable clocks */
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

   /* Define A peripherals */
   /* PA5[SPI1_SCK], PA7[SPI1_MOSI] as alternative function */
   /* Confugure SCK and MOSI pins as Alternate Function Push Pull */
   GPIO_StructInit(&GPIOA_InitStructure);
   GPIOA_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
   GPIOA_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIOA_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
   GPIO_Init(GPIOA, &GPIOA_InitStructure);

   /* PB5 [DSP_CS (also known as CS too)] */
   GPIO_StructInit(&GPIOB_InitStructure);
   GPIOB_InitStructure.GPIO_Pin = GPIO_Pin_4;
   GPIOB_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
   GPIOB_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
   GPIO_Init(GPIOA, &GPIOB_InitStructure);

   /* Define C peripherals */
   /* PC8 LD4 [Blue], PC9 LD3 [Green] */
   GPIO_StructInit(&GPIOC_InitStructure);
   GPIOC_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
   GPIOC_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
   GPIOC_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
   GPIO_Init(GPIOC, &GPIOC_InitStructure);

   /* Define D peripherals */
   /* PD2 [DSP_A0/Rs (switch command/data)] */
   GPIO_StructInit(&GPIOD_InitStructure);
   GPIOD_InitStructure.GPIO_Pin = GPIO_Pin_2;
   GPIOD_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
   GPIOD_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
   GPIO_Init(GPIOA, &GPIOD_InitStructure);

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
   /* Set CS to LOW to activate SPI communication */
   GPIO_ResetBits(GPIOB, GPIO_Pin_5);
   delay(SMALL_DELAY);

   /* Init LCD */
   LCD_SendCommand(CMD_SET_BIAS_7);
   LCD_SendCommand(CMD_SET_ADC_NORMAL);
   LCD_SendCommand(CMD_SET_COM_NORMAL);
   LCD_SendCommand(CMD_SET_DISP_START_LINE);

   /* Config LCD power supply */
   LCD_SendCommand(CMD_SET_POWER_CONTROL | 0x4); // VC=1, VR =0, VF = 0
   LCD_SendCommand(CMD_SET_POWER_CONTROL | 0x6); // VC=1, VR =1, VF = 0
   LCD_SendCommand(CMD_SET_POWER_CONTROL | 0x7); // VC=1, VR =1, VF = 1
   LCD_SendCommand(CMD_SET_RESISTOR_RATIO |
                   0x6); // regulator resistor, ref. voltage R
   LCD_SendCommand(CMD_SET_VOLUME_FIRST);
   LCD_SendCommand(CMD_SET_VOLUME_SECOND |
                   (0x10 & 0x3f)); // contrast settings - usable range 0x05-0x20
   LCD_SendCommand(CMD_DISPLAY_ON); // turn on the display

   /* Clear display */
   LCD_ClearDisplay();

   LCD_DisplayChar(80, 4, 'a');
   LCD_DisplayChar(20, 24, 'b');
   LCD_DisplayChar(8, 40, 'f');

   while (1) {
      delay(10000);
   }
}

void delay(vu32 nCount)
{
   for (; nCount != 0; nCount--)
      ;
}

static void LCD_SendByte(uint8_t byte)
{
   /* Loop while DR register in not emplty */
   while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET)
      ;

   /* Send byte through the SPI1 peripheral */
   SPI_I2S_SendData(SPI1, byte);

   /* Wait to receive a byte */
   while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET)
      ;

   /* Return the byte read from the SPI bus */
   SPI_I2S_ReceiveData(SPI1);
}

static void LCD_SendCommand(uint8_t byte)
{
   /* Set A0 to LOW to indicate command */
   GPIO_ResetBits(GPIOD, GPIO_Pin_2);
   delay(SMALL_DELAY);
   LCD_SendByte(byte);
}
static void LCD_SendData(uint8_t byte)
{
   /* Set A0 to HIGH to indicate data */
   GPIO_SetBits(GPIOD, GPIO_Pin_2);
   delay(SMALL_DELAY);
   LCD_SendByte(byte);
}

/**
 * @brief Sets the whole LCD RAM to 0
 *
 */
static void LCD_ClearDisplay(void)
{
   uint8_t line = LCD_PIXEL_HEIGHT / 8, column;
   while (line--) {
      LCD_SendCommand(CMD_SET_PAGE | (line));
      LCD_SendCommand(CMD_SET_COLUMN_LOWER | 0);
      LCD_SendCommand(CMD_SET_COLUMN_UPPER | 0);
      LCD_SendCommand(CMD_RMW);
      column = LCD_PIXEL_WIDTH;
      while (column--) {
         LCD_SendData(0x00);
      }
   }
}

/**
 * @brief Sets LCD cursor position
 *
 * @param line
 * @param column
 */
static void LCD_SetPos(uint8_t line, uint8_t column)
{
   LCD_SendCommand(CMD_SET_PAGE | (line & 0x0F));
   LCD_SendCommand(CMD_SET_COLUMN_LOWER | ((column) & 0xf));
   LCD_SendCommand(CMD_SET_COLUMN_UPPER | (((column) >> 4) & 0x0F));
   LCD_SendCommand(CMD_RMW);
}

/**
 * @brief Display char
 *
 * @param column
 * @param line
 * @param ascii
 */
static void LCD_DisplayChar(uint8_t column, uint16_t line, uint8_t ascii)
{
   int i;
   for (i = 0; i < 5; i++) {
      LCD_SetPos(line, column++);
      LCD_SendData(font5x8[(ascii * 5) + 5 - i - 1]);
   }
}