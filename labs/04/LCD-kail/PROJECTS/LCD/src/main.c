/**
 ******************************************************************************
 * @file    main.c
 * @author  MCD Application Team
 * @version V1.1.0
 * @date    07-October-2011
 * @brief   Main program body
 ******************************************************************************
 * @attention
 *
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *
 * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "serial_driver.h"
#include "stm32_eval.h"
#include <stdio.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define ENCODER_COUNTER_ZERO (0xFFFF / 2)
#define ENCODER_PULSES_PER_ROTATION 96
#define ENCODER_COUNTER_RANGE (0xFFFF / 2)
#define ENCODER_POSITION (int)(TIM4->CNT - ENCODER_COUNTER_ZERO) / 4

#define LCD_CENTER_X (LCD_PIXEL_WIDTH / 2)
#define LCD_CENTER_Y (LCD_PIXEL_HEIGHT / 2)

#define CMD_DISPLAY_OFF 0xAE
#define CMD_DISPLAY_ON 0xAF

#define CMD_SET_DISP_START_LINE 0x40
#define CMD_SET_PAGE 0xB0

#define CMD_SET_COLUMN_UPPER 0x10
#define CMD_SET_COLUMN_LOWER 0x00

#define CMD_SET_ADC_NORMAL 0xA0
#define CMD_SET_ADC_REVERSE 0xA1

#define CMD_SET_DISP_NORMAL 0xA6
#define CMD_SET_DISP_REVERSE 0xA7

#define CMD_SET_ALLPTS_NORMAL 0xA4
#define CMD_SET_ALLPTS_ON 0xA5
#define CMD_SET_BIAS_9 0xA2
#define CMD_SET_BIAS_7 0xA3

#define CMD_RMW 0xE0
#define CMD_RMW_CLEAR 0xEE
#define CMD_INTERNAL_RESET 0xE2
#define CMD_SET_COM_NORMAL 0xC0
#define CMD_SET_COM_REVERSE 0xC8
#define CMD_SET_POWER_CONTROL 0x28
#define CMD_SET_RESISTOR_RATIO 0x20
#define CMD_SET_VOLUME_FIRST 0x81
#define CMD_SET_VOLUME_SECOND 0
#define CMD_SET_STATIC_OFF 0xAC
#define CMD_SET_STATIC_ON 0xAD
#define CMD_SET_STATIC_REG 0x0
#define CMD_SET_BOOSTER_FIRST 0xF8
#define CMD_SET_BOOSTER_234 0
#define CMD_SET_BOOSTER_5 1
#define CMD_SET_BOOSTER_6 3
#define CMD_NOP 0xE3
#define CMD_TEST 0xF0
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

// Stolen from lcd_st7576p library
static uint8_t font5x8[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, // 0x00
    0x3E, 0x5B, 0x4F, 0x5B, 0x3E, // 0x01 :(
    0x3E, 0x6B, 0x4F, 0x6B, 0x3E, // 0x02 :)
    0x1C, 0x3E, 0x7C, 0x3E, 0x1C, // 0x03 srdce
    0x18, 0x3C, 0x7E, 0x3C, 0x18, // 0x04 kary
    0x1C, 0x57, 0x7D, 0x57, 0x1C, // 0x05 krize
    0x1C, 0x5E, 0x7F, 0x5E, 0x1C, // 0x06 piky
    0x00, 0x18, 0x3C, 0x18, 0x00, // 0x07 tecka
    0xFF, 0xE7, 0xC3, 0xE7, 0xFF, // 0x08 inv tecka
    0x00, 0x18, 0x24, 0x18, 0x00, // 0x09 kolecko
    0xFF, 0xE7, 0xDB, 0xE7, 0xFF, // 0x0A inv kolecko
    0x30, 0x48, 0x3A, 0x06, 0x0E, // 0x0B samec
    0x26, 0x29, 0x79, 0x29, 0x26, // 0x0C samice
    0x40, 0x7F, 0x05, 0x05, 0x07, // 0x0D nota
    0x40, 0x7F, 0x05, 0x25, 0x3F, // 0x0E dve noty
    0x5A, 0x3C, 0xE7, 0x3C, 0x5A, // 0x0F slunce
    0x7F, 0x3E, 0x1C, 0x1C, 0x08, // 0x10 sipka <-
    0x08, 0x1C, 0x1C, 0x3E, 0x7F, // 0x11 sipka ->
    0x14, 0x22, 0x7F, 0x22, 0x14, // 0x12 sipka nahoru/dolu
    0x5F, 0x5F, 0x00, 0x5F, 0x5F, // 0x13 dvojty vykricnik
    0x06, 0x09, 0x7F, 0x01, 0x7F, // 0x14 velke Pi
    0x00, 0x66, 0x89, 0x95, 0x6A, // 0x15 paragraf
    0x60, 0x60, 0x60, 0x60, 0x60, // 0x16 _
    0x94, 0xA2, 0xFF, 0xA2, 0x94, // 0x17 sipka nahoru/dolu od zeme
    0x08, 0x04, 0x7E, 0x04, 0x08, // 0x18 nahoru
    0x10, 0x20, 0x7E, 0x20, 0x10, // 0x19 dolu
    0x08, 0x08, 0x2A, 0x1C, 0x08, // 0x1A vpravo
    0x08, 0x1C, 0x2A, 0x08, 0x08, // 0x1B vlevo
    0x1E, 0x10, 0x10, 0x10, 0x10, // 0x1C |_
    0x0C, 0x1E, 0x0C, 0x1E, 0x0C, // 0x1D polozena #
    0x30, 0x38, 0x3E, 0x38, 0x30, // 0x1E domecek nahoru
    0x06, 0x0E, 0x3E, 0x0E, 0x06, // 0x1F domecek dolu
    0x00, 0x00, 0x00, 0x00, 0x00, // ' '
    0x00, 0x00, 0x5F, 0x00, 0x00, // '!'
    0x00, 0x07, 0x00, 0x07, 0x00, // '"'
    0x14, 0x7F, 0x14, 0x7F, 0x14, // '#'
    0x24, 0x2A, 0x7F, 0x2A, 0x12, // '$'
    0x23, 0x13, 0x08, 0x64, 0x62, // '%'
    0x36, 0x49, 0x56, 0x20, 0x50, // '&'
    0x00, 0x08, 0x07, 0x03, 0x00, // '''
    0x00, 0x1C, 0x22, 0x41, 0x00, // '('
    0x00, 0x41, 0x22, 0x1C, 0x00, // ')'
    0x2A, 0x1C, 0x7F, 0x1C, 0x2A, // '*'
    0x08, 0x08, 0x3E, 0x08, 0x08, // '+'
    0x00, 0x80, 0x70, 0x30, 0x00, // ','
    0x08, 0x08, 0x08, 0x08, 0x08, // '-'
    0x00, 0x00, 0x60, 0x60, 0x00, // '.'
    0x20, 0x10, 0x08, 0x04, 0x02, // '/'
    0x3E, 0x51, 0x49, 0x45, 0x3E, // '0'
    0x00, 0x42, 0x7F, 0x40, 0x00, // '1'
    0x72, 0x49, 0x49, 0x49, 0x46, // '2'
    0x21, 0x41, 0x49, 0x4D, 0x33, // '3'
    0x18, 0x14, 0x12, 0x7F, 0x10, // '4'
    0x27, 0x45, 0x45, 0x45, 0x39, // '5'
    0x3C, 0x4A, 0x49, 0x49, 0x31, // '6'
    0x41, 0x21, 0x11, 0x09, 0x07, // '7'
    0x36, 0x49, 0x49, 0x49, 0x36, // '8'
    0x46, 0x49, 0x49, 0x29, 0x1E, // '9'
    0x00, 0x00, 0x14, 0x00, 0x00, // ':'
    0x00, 0x40, 0x34, 0x00, 0x00, // ';'
    0x00, 0x08, 0x14, 0x22, 0x41, // '<'
    0x14, 0x14, 0x14, 0x14, 0x14, // '='
    0x00, 0x41, 0x22, 0x14, 0x08, // '>'
    0x02, 0x01, 0x59, 0x09, 0x06, // '?'
    0x3E, 0x41, 0x5D, 0x59, 0x4E, // '@'
    0x7C, 0x12, 0x11, 0x12, 0x7C, // 'A'
    0x7F, 0x49, 0x49, 0x49, 0x36, // 'B'
    0x3E, 0x41, 0x41, 0x41, 0x22, // 'C'
    0x7F, 0x41, 0x41, 0x41, 0x3E, // 'D'
    0x7F, 0x49, 0x49, 0x49, 0x41, // 'E'
    0x7F, 0x09, 0x09, 0x09, 0x01, // 'F'
    0x3E, 0x41, 0x41, 0x51, 0x73, // 'G'
    0x7F, 0x08, 0x08, 0x08, 0x7F, // 'H'
    0x00, 0x41, 0x7F, 0x41, 0x00, // 'I'
    0x20, 0x40, 0x41, 0x3F, 0x01, // 'J'
    0x7F, 0x08, 0x14, 0x22, 0x41, // 'K'
    0x7F, 0x40, 0x40, 0x40, 0x40, // 'L'
    0x7F, 0x02, 0x1C, 0x02, 0x7F, // 'M'
    0x7F, 0x04, 0x08, 0x10, 0x7F, // 'N'
    0x3E, 0x41, 0x41, 0x41, 0x3E, // 'O'
    0x7F, 0x09, 0x09, 0x09, 0x06, // 'P'
    0x3E, 0x41, 0x51, 0x21, 0x5E, // 'Q'
    0x7F, 0x09, 0x19, 0x29, 0x46, // 'R'
    0x26, 0x49, 0x49, 0x49, 0x32, // 'S'
    0x03, 0x01, 0x7F, 0x01, 0x03, // 'T'
    0x3F, 0x40, 0x40, 0x40, 0x3F, // 'U'
    0x1F, 0x20, 0x40, 0x20, 0x1F, // 'V'
    0x3F, 0x40, 0x38, 0x40, 0x3F, // 'W'
    0x63, 0x14, 0x08, 0x14, 0x63, // 'X'
    0x03, 0x04, 0x78, 0x04, 0x03, // 'Y'
    0x61, 0x59, 0x49, 0x4D, 0x43, // 'Z'
    0x00, 0x7F, 0x41, 0x41, 0x41, // '['
    0x02, 0x04, 0x08, 0x10, 0x20, // '\'
    0x00, 0x41, 0x41, 0x41, 0x7F, // ']'
    0x04, 0x02, 0x01, 0x02, 0x04, // '^'
    0x40, 0x40, 0x40, 0x40, 0x40, // '_'
    0x00, 0x03, 0x07, 0x08, 0x00, // '`'
    0x20, 0x54, 0x54, 0x78, 0x40, // 'a'
    0x7F, 0x28, 0x44, 0x44, 0x38, // 'b'
    0x38, 0x44, 0x44, 0x44, 0x28, // 'c'
    0x38, 0x44, 0x44, 0x28, 0x7F, // 'd'
    0x38, 0x54, 0x54, 0x54, 0x18, // 'e'
    0x00, 0x08, 0x7E, 0x09, 0x02, // 'f'
    0x18, 0xA4, 0xA4, 0x9C, 0x78, // 'g'
    0x7F, 0x08, 0x04, 0x04, 0x78, // 'h'
    0x00, 0x44, 0x7D, 0x40, 0x00, // 'i'
    0x20, 0x40, 0x40, 0x3D, 0x00, // 'j'
    0x7F, 0x10, 0x28, 0x44, 0x00, // 'k'
    0x00, 0x41, 0x7F, 0x40, 0x00, // 'l'
    0x7C, 0x04, 0x78, 0x04, 0x78, // 'm'
    0x7C, 0x08, 0x04, 0x04, 0x78, // 'n'
    0x38, 0x44, 0x44, 0x44, 0x38, // 'o'
    0xFC, 0x18, 0x24, 0x24, 0x18, // 'p'
    0x18, 0x24, 0x24, 0x18, 0xFC, // 'q'
    0x7C, 0x08, 0x04, 0x04, 0x08, // 'r'
    0x48, 0x54, 0x54, 0x54, 0x24, // 's'
    0x04, 0x04, 0x3F, 0x44, 0x24, // 't'
    0x3C, 0x40, 0x40, 0x20, 0x7C, // 'u'
    0x1C, 0x20, 0x40, 0x20, 0x1C, // 'v'
    0x3C, 0x40, 0x30, 0x40, 0x3C, // 'w'
    0x44, 0x28, 0x10, 0x28, 0x44, // 'x'
    0x4C, 0x90, 0x90, 0x90, 0x7C, // 'y'
    0x44, 0x64, 0x54, 0x4C, 0x44, // 'z'
    0x00, 0x08, 0x36, 0x41, 0x00, // '{'
    0x00, 0x00, 0x77, 0x00, 0x00, // '|'
    0x00, 0x41, 0x36, 0x08, 0x00, // '}'
    0x02, 0x01, 0x02, 0x04, 0x02, // '~'
    0x3C, 0x26, 0x23, 0x26, 0x3C, // 0x7F prazdny domecek
    0x1E, 0xA1, 0xA1, 0x61, 0x12, // 0x80 nektere znaky podobne codepage 437
    0x3A, 0x40, 0x40, 0x20, 0x7A, // 0x81
    0x38, 0x54, 0x54, 0x55, 0x59, // 0x82
    0x21, 0x55, 0x55, 0x79, 0x41, // 0x83
    0x21, 0x54, 0x54, 0x78, 0x41, // 0x84
    0x21, 0x55, 0x54, 0x78, 0x40, // 0x85
    0x20, 0x54, 0x55, 0x79, 0x40, // 0x86
    0x0C, 0x1E, 0x52, 0x72, 0x12, // 0x87
    0x39, 0x55, 0x55, 0x55, 0x59, // 0x88
    0x39, 0x54, 0x54, 0x54, 0x59, // 0x89
    0x39, 0x55, 0x54, 0x54, 0x58, // 0x8A
    0x00, 0x00, 0x45, 0x7C, 0x41, // 0x8B
    0x00, 0x02, 0x45, 0x7D, 0x42, // 0x8C
    0x00, 0x01, 0x45, 0x7C, 0x40, // 0x8D
    0xF0, 0x29, 0x24, 0x29, 0xF0, // 0x8E
    0xF0, 0x28, 0x25, 0x28, 0xF0, // 0x8F
    0x7C, 0x54, 0x55, 0x45, 0x00, // 0x90
    0x20, 0x54, 0x54, 0x7C, 0x54, // 0x91
    0x7C, 0x0A, 0x09, 0x7F, 0x49, // 0x92
    0x32, 0x49, 0x49, 0x49, 0x32, // 0x93
    0x32, 0x48, 0x48, 0x48, 0x32, // 0x94
    0x32, 0x4A, 0x48, 0x48, 0x30, // 0x95
    0x3A, 0x41, 0x41, 0x21, 0x7A, // 0x96
    0x3A, 0x42, 0x40, 0x20, 0x78, // 0x97
    0x00, 0x9D, 0xA0, 0xA0, 0x7D, // 0x98
    0x39, 0x44, 0x44, 0x44, 0x39, // 0x99
    0x3D, 0x40, 0x40, 0x40, 0x3D, // 0x9A
    0x3C, 0x24, 0xFF, 0x24, 0x24, // 0x9B
    0x48, 0x7E, 0x49, 0x43, 0x66, // 0x9C
    0x2B, 0x2F, 0xFC, 0x2F, 0x2B, // 0x9D
    0xFF, 0x09, 0x29, 0xF6, 0x20, // 0x9E
    0xC0, 0x88, 0x7E, 0x09, 0x03, // 0x9F
    0x20, 0x54, 0x54, 0x79, 0x41, // 0xA0
    0x00, 0x00, 0x44, 0x7D, 0x41, // 0xA1
    0x30, 0x48, 0x48, 0x4A, 0x32, // 0xA2
    0x38, 0x40, 0x40, 0x22, 0x7A, // 0xA3
    0x00, 0x7A, 0x0A, 0x0A, 0x72, // 0xA4
    0x7D, 0x0D, 0x19, 0x31, 0x7D, // 0xA5
    0x26, 0x29, 0x29, 0x2F, 0x28, // 0xA6
    0x26, 0x29, 0x29, 0x29, 0x26, // 0xA7
    0x30, 0x48, 0x4D, 0x40, 0x20, // 0xA8
    0x38, 0x08, 0x08, 0x08, 0x08, // 0xA9
    0x08, 0x08, 0x08, 0x08, 0x38, // 0xAA
    0x2F, 0x10, 0xC8, 0xAC, 0xBA, // 0xAB
    0x2F, 0x10, 0x28, 0x34, 0xFA, // 0xAC
    0x00, 0x00, 0x7B, 0x00, 0x00, // 0xAD
    0x08, 0x14, 0x2A, 0x14, 0x22, // 0xAE
    0x22, 0x14, 0x2A, 0x14, 0x08, // 0xAF
    0xAA, 0x00, 0x55, 0x00, 0xAA, // 0xB0
    0xAA, 0x55, 0xAA, 0x55, 0xAA, // 0xB1
    0x55, 0xAA, 0x55, 0xAA, 0x55, // 0xB2
    0x00, 0x00, 0x00, 0xFF, 0x00, // 0xB3
    0x10, 0x10, 0x10, 0xFF, 0x00, // 0xB4
    0x14, 0x14, 0x14, 0xFF, 0x00, // 0xB5
    0x10, 0x10, 0xFF, 0x00, 0xFF, // 0xB6
    0x10, 0x10, 0xF0, 0x10, 0xF0, // 0xB7
    0x14, 0x14, 0x14, 0xFC, 0x00, // 0xB8
    0x14, 0x14, 0xF7, 0x00, 0xFF, // 0xB9
    0x00, 0x00, 0xFF, 0x00, 0xFF, // 0xBA
    0x14, 0x14, 0xF4, 0x04, 0xFC, // 0xBB
    0x14, 0x14, 0x17, 0x10, 0x1F, // 0xBC
    0x10, 0x10, 0x1F, 0x10, 0x1F, // 0xBD
    0x14, 0x14, 0x14, 0x1F, 0x00, // 0xBE
    0x10, 0x10, 0x10, 0xF0, 0x00, // 0xBF
    0x00, 0x00, 0x00, 0x1F, 0x10, // 0xC0
    0x10, 0x10, 0x10, 0x1F, 0x10, // 0xC1
    0x10, 0x10, 0x10, 0xF0, 0x10, // 0xC2
    0x00, 0x00, 0x00, 0xFF, 0x10, // 0xC3
    0x10, 0x10, 0x10, 0x10, 0x10, // 0xC4
    0x10, 0x10, 0x10, 0xFF, 0x10, // 0xC5
    0x00, 0x00, 0x00, 0xFF, 0x14, // 0xC6
    0x00, 0x00, 0xFF, 0x00, 0xFF, // 0xC7
    0x00, 0x00, 0x1F, 0x10, 0x17, // 0xC8
    0x00, 0x00, 0xFC, 0x04, 0xF4, // 0xC9
    0x14, 0x14, 0x17, 0x10, 0x17, // 0xCA
    0x14, 0x14, 0xF4, 0x04, 0xF4, // 0xCB
    0x00, 0x00, 0xFF, 0x00, 0xF7, // 0xCC
    0x14, 0x14, 0x14, 0x14, 0x14, // 0xCD
    0x14, 0x14, 0xF7, 0x00, 0xF7, // 0xCE
    0x14, 0x14, 0x14, 0x17, 0x14, // 0xCF
    0x10, 0x10, 0x1F, 0x10, 0x1F, // 0xD0
    0x14, 0x14, 0x14, 0xF4, 0x14, // 0xD1
    0x10, 0x10, 0xF0, 0x10, 0xF0, // 0xD2
    0x00, 0x00, 0x1F, 0x10, 0x1F, // 0xD3
    0x00, 0x00, 0x00, 0x1F, 0x14, // 0xD4
    0x00, 0x00, 0x00, 0xFC, 0x14, // 0xD5
    0x00, 0x00, 0xF0, 0x10, 0xF0, // 0xD6
    0x10, 0x10, 0xFF, 0x10, 0xFF, // 0xD7
    0x14, 0x14, 0x14, 0xFF, 0x14, // 0xD8
    0x10, 0x10, 0x10, 0x1F, 0x00, // 0xD9
    0x00, 0x00, 0x00, 0xF0, 0x10, // 0xDA
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 0xDB
    0xF0, 0xF0, 0xF0, 0xF0, 0xF0, // 0xDC
    0xFF, 0xFF, 0xFF, 0x00, 0x00, // 0xDD
    0x00, 0x00, 0x00, 0xFF, 0xFF, // 0xDE
    0x0F, 0x0F, 0x0F, 0x0F, 0x0F, // 0xDF
    0x38, 0x44, 0x44, 0x38, 0x44, // 0xE0
    0x7C, 0x2A, 0x2A, 0x3E, 0x14, // 0xE1
    0x7E, 0x02, 0x02, 0x06, 0x06, // 0xE2
    0x02, 0x7E, 0x02, 0x7E, 0x02, // 0xE3
    0x63, 0x55, 0x49, 0x41, 0x63, // 0xE4
    0x38, 0x44, 0x44, 0x3C, 0x04, // 0xE5
    0x40, 0x7E, 0x20, 0x1E, 0x20, // 0xE6
    0x06, 0x02, 0x7E, 0x02, 0x02, // 0xE7
    0x99, 0xA5, 0xE7, 0xA5, 0x99, // 0xE8
    0x1C, 0x2A, 0x49, 0x2A, 0x1C, // 0xE9
    0x4C, 0x72, 0x01, 0x72, 0x4C, // 0xEA
    0x30, 0x4A, 0x4D, 0x4D, 0x30, // 0xEB
    0x30, 0x48, 0x78, 0x48, 0x30, // 0xEC
    0xBC, 0x62, 0x5A, 0x46, 0x3D, // 0xED
    0x3E, 0x49, 0x49, 0x49, 0x00, // 0xEE
    0x7E, 0x01, 0x01, 0x01, 0x7E, // 0xEF
    0x2A, 0x2A, 0x2A, 0x2A, 0x2A, // 0xF0
    0x44, 0x44, 0x5F, 0x44, 0x44, // 0xF1
    0x40, 0x51, 0x4A, 0x44, 0x40, // 0xF2
    0x40, 0x44, 0x4A, 0x51, 0x40, // 0xF3
    0x00, 0x00, 0xFF, 0x01, 0x03, // 0xF4
    0xE0, 0x80, 0xFF, 0x00, 0x00, // 0xF5
    0x08, 0x08, 0x6B, 0x6B, 0x08, // 0xF6
    0x36, 0x12, 0x36, 0x24, 0x36, // 0xF7
    0x06, 0x0F, 0x09, 0x0F, 0x06, // 0xF8
    0x00, 0x00, 0x18, 0x18, 0x00, // 0xF9
    0x00, 0x00, 0x10, 0x10, 0x00, // 0xFA
    0x30, 0x40, 0xFF, 0x01, 0x01, // 0xFB
    0x00, 0x1F, 0x01, 0x01, 0x1E, // 0xFC
    0x00, 0x19, 0x1D, 0x17, 0x12, // 0xFD
    0x00, 0x3C, 0x3C, 0x3C, 0x3C, // 0xFE
};

/* Private function prototypes -----------------------------------------------*/
void delay(vu32 nCount);
void LED_Init(void);
void init_encoder_timer();
void init_button();

void init_LCD();
void setup_LCD();
// void LCD_SendByte(uint8_t byte);
void LCD_SendData(uint8_t data);
void LCD_SendCommand(uint8_t cmd);
void LCD_DrawRectWithDiagonals(uint8_t x, uint8_t line);
void LCD_DrawMyRectWithDiagonals(uint8_t x, uint8_t line);
void LCD_MyDisplayChar(uint8_t Line, uint16_t Column, uint8_t Ascii);
void LCD_MyDisplayStr(uint8_t x, uint16_t Line, char *str);
void LCD_DrawCentreRectangleDiag();
void LCD_DrawOrnament(uint8_t x, uint8_t line, uint8_t length);
void LCD_DrawVLine(uint8_t x, uint8_t y, uint8_t length);
void LCD_DrawHLine(uint8_t x, uint8_t y, uint8_t length);
void LCD_DrawRectangleDiag(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
void LCD_ClearDisplay();
/* Private functions ---------------------------------------------------------*/

/**
 * Main program.
 * @return Nothing.
 */
int main(void)
{

   /* Initialize all LEDs */
   LED_Init();
   init_button();

   /* Initialize COM2 == USART3 (USB <==> Serial Port) */
   ComPort_Init(COM2);

   /* Configure COM2 as stdin, stdout and stderr */
   ComPort_ConfigStdio(COM2, COM2, COM2);

   init_LCD();
   setup_LCD();
   LCD_ClearDisplay();
   //    LCD_DrawRectWithDiagonals(8, 2);
   // LCD_DrawVLine(64,32,15);
   //    LCD_DrawVLine(63,32,1);
   //    LCD_DrawVLine(62,32,6);
   //    LCD_DrawVLine(61,32,4);
   //    LCD_DrawVLine(60,32,3);
   //    LCD_DrawVLine(50,32,2);
   //    LCD_DrawVLine(50,32,2);
   //    LCD_DrawVLine(64,32,15);

   //    LCD_DrawHLine(64,32,15);

   /* INITIALIZE ECODER */
   init_encoder_timer();
   /* It is not that hard, no help today. */
   /* Look into SCKit schematics for the encoder connection */
   /* Read STM32F207 datasheet and reference manual */
   /* Do not forget to configure the encoder pins */
   /* Do not forget to configure clock for a counter */
   // LCD_DrawMyRectWithDiagonals(50,1);

   LCD_MyDisplayChar(80, 4, 'a');
   LCD_MyDisplayStr(123, 0, "horisontal");
   LCD_DrawHLine(1, 3, 50);
   LCD_MyDisplayStr(123, 1, "vertical");
   LCD_DrawVLine(25, 10, 20);
   LCD_MyDisplayStr(123, 4, "ornament");
   LCD_DrawOrnament(1, 4, 50);
   LCD_MyDisplayStr(123, 5, "rectangle");
   LCD_DrawMyRectWithDiagonals(50, 5);
   LCD_MyDisplayStr(123, 7, "For encoder press BT2");

   char trigger = 0;
   char change = 0;
   char x = 63;
   int last_val = ENCODER_POSITION;
   while (1) {
      if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_15) == 0) {
         change = 1;
         trigger = 1;
      }
      if (trigger == 1 && change == 1) {
         change = 0;
         char buff[30];
         sprintf(buff, "Encoder: %d", ENCODER_POSITION);
         LCD_ClearDisplay();
         LCD_MyDisplayStr(123, 0, buff);
         if (last_val > ENCODER_POSITION) {
            x++;
         } else {
            x--;
         }
         LCD_DrawMyRectWithDiagonals(x, 4);
         last_val = ENCODER_POSITION;
      }
      if (last_val != ENCODER_POSITION) {
         change = 1;
      }
   }
   //    iprintf("\nRun.");
   //    while (1) {
   //        // STM_EVAL_LEDToggle(LED1);
   //        // iprintf(".");
   //        iprintf("%d\n", ENCODER_POSITION);
   //
   //        if (GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_15) == 0){
   //            TIM4->CNT = ENCODER_COUNTER_ZERO;
   //            while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_15) == 0){
   //                continue;
   //            }
   //        }
   //        delay(0x0FFFFF);
   //        LCD_ClearDisplay();
   //
   //    }
}

/**
 * Initialize all LEDs
 */
void LED_Init(void)
{
   Led_TypeDef led;

   for (led = LED1; led < (LED1 + LEDn); led++) {
      /* Initialize SCKit's LEDs */
      STM_EVAL_LEDInit(led);
      /* Set LEDs off */
      STM_EVAL_LEDOff(led);
   }
}

/**
 * Delay function
 * @param nCount = Number of cycles to delay.
 */
void delay(vu32 nCount)
{
   for (; nCount != 0; nCount--)
      ;
}
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
void init_button()
{
   GPIO_InitTypeDef GPIO_InitStructure;

   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
   GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void init_encoder_timer()
{
   /* Initialize the corresponding input pins */
   GPIO_InitTypeDef GPIO_InitStructure;
   /* Enable clock to GPIOD */
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
   GPIO_StructInit(&GPIO_InitStructure);
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOD, &GPIO_InitStructure);
   GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);
   GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4);

   /* Initialize the timer */
   /* Enable clock to TIM4 */
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

   TIM_TimeBaseInitTypeDef TIM_InitStructure;
   TIM_TimeBaseStructInit(&TIM_InitStructure);
   TIM_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
   TIM_InitStructure.TIM_Period = 0xFFFF;
   TIM_InitStructure.TIM_Prescaler = 0;
   TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
   TIM_TimeBaseInit(TIM4, &TIM_InitStructure);

   /* Set the timer up for quadrature decoding */
   TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising,
                              TIM_ICPolarity_Rising);
   TIM4->CNT = ENCODER_COUNTER_ZERO;
   TIM_Cmd(TIM4, ENABLE);
}

// Sets the whole LCD RAM to 0
void LCD_ClearDisplay()
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

// Sets LCD cursor position
void LCD_SetPos(uint8_t line, uint8_t column)
{
   LCD_SendCommand(CMD_SET_PAGE | (line & 0x0F));
   LCD_SendCommand(CMD_SET_COLUMN_LOWER | ((column) & 0xf));
   LCD_SendCommand(CMD_SET_COLUMN_UPPER | (((column) >> 4) & 0x0F));
   LCD_SendCommand(CMD_RMW);
}

// Draws a small square with diagonals
void LCD_DrawRectWithDiagonals(uint8_t x, uint8_t line)
{
   uint8_t x_width = 8;

   LCD_SetPos(line, x);
   while (x_width--) {
      if (x_width == 7) // Prvni vertikalni cara
         LCD_SendData(0xFF);
      else if (x_width == 0) // Druha vertikalni cara
         LCD_SendData(0xFF);
      else
         LCD_SendData(1 << 0 |                 // horni horizontalni cara
                      1 << 7 |                 // spodni horizontalni cara
                      1 << (x_width % 8) |     // jedna uhlopricka
                      1 << (7 - (x_width % 8)) // druha uhlopricka
         );
   }
}

// Draws a small square with diagonals
void LCD_DrawMyRectWithDiagonals(uint8_t x, uint8_t line)
{
   uint16_t fill = 2;
   uint8_t initial_x = x;

   LCD_SetPos(line, x);
   LCD_SendData(0xff);
   LCD_SetPos(line + 1, x);
   LCD_SendData(0xff);
   x++;

   while (fill < 0xff) {
      LCD_SetPos(line, x);
      LCD_SendData(fill + 1);
      LCD_SetPos(line + 1, x + 7);
      LCD_SendData((fill >> 1) | 0x80);
      fill = fill << 1;
      x++;
   }
   fill = fill >> 1;
   while (fill > 0x1) {
      LCD_SetPos(line, x);
      LCD_SendData(fill + 1);
      LCD_SetPos(line + 1, x - 7);
      LCD_SendData((fill >> 1) | 0x80);
      fill = fill >> 1;
      x++;
   }
   LCD_SetPos(line, x);
   LCD_SendData(0xff);
   LCD_SetPos(line + 1, x);
   LCD_SendData(0xff);
}

// Draws a sawtooth line (with changing width from 1 to 8)
void LCD_DrawOrnament(uint8_t x, uint8_t line, uint8_t length)
{
   LCD_SetPos(line, x);
   while (length--) {
      LCD_SendData(0xFF >> (length % 8));
   }
}

void LCD_MyDisplayStr(uint8_t x, uint16_t Line, char *str)
{
   int i = 0;
   char current_char = str[i++];
   uint16_t current_x = x;
   while (current_char != '\0') {
      LCD_MyDisplayChar(current_x, Line, current_char);
      current_char = str[i++];
      current_x -= 6;
   }
}

void LCD_MyDisplayChar(uint8_t x, uint16_t Line, uint8_t Ascii)
{
   int i;
   for (i = 0; i < 5; i++) {
      LCD_SetPos(Line, x++);
      LCD_SendData(font5x8[(Ascii * 5) + 5 - i - 1]);
   }
}

// Draws a vertical line
void LCD_DrawVLine(uint8_t x, uint8_t y, uint8_t length)
{
   uint8_t cur_line = y / 8;
   uint8_t column = x;
   uint8_t n_lines = length / 8 + 1;
   uint8_t data;
   uint8_t col_start = y % 8;

   //    if (length < 8) {
   //        unsigned bin_number = col_start;
   //        int i;
   //        for (i = 0; i<length; i++){
   //            bin_number = (bin_number << 1) | 1;
   //        }
   //        LCD_SetPos(cur_line++, column);
   //        LCD_SendData(bin_number);
   //    } else {

   data = ((0xff) << (col_start));

   while (n_lines--) {
      LCD_SetPos(cur_line++, column);
      LCD_SendData(data);
      if (n_lines == 1) // Set data for the next iteration
         data = (0xff >> (8 - ((col_start + length) % 8)));
      else
         data = 0xff;
      //        }
   }
}

// Draws a horizontal line
void LCD_DrawHLine(uint8_t x, uint8_t y, uint8_t length)
{
   uint8_t start_line = y / 8;
   uint8_t start_column = x;
   uint8_t data;
   uint8_t col_pos = y % 8;
   data = (1 << col_pos);

   LCD_SetPos(start_line, start_column);
   for (; length; length--)
      LCD_SendData(data);
}
// Must not be on span of one line
void LCD_DrawRectangleDiag(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
   unsigned a = abs(x1 - x2);
   unsigned b = abs(y1 - y2);

   LCD_DrawHLine(x1, y1, a);
   LCD_DrawHLine(x1, y2, a);
   LCD_DrawVLine(x1, y1, b + 1);
   LCD_DrawVLine(x2, y1, b + 1);

   unsigned D = 2 * b - a;
   unsigned y = y1;

   int x;
   for (x = x1; x < x2; x++) {
      LCD_DrawVLine(x, y, 1);
      if (D > 0) {
         y = y + 1;
         D = D - 2 * a;
      }
      D = D + 2 * b;
   }
}

void LCD_DrawCentreRectangleDiag()
{
   uint8_t x0 = 32, y0 = 16, x1 = 96, y1 = 48;
   unsigned a = abs(x1 - x0);
   unsigned b = abs(y1 - y0);

   LCD_DrawHLine(x0, y0, a);
   LCD_DrawHLine(x0, y1, a);
   LCD_DrawVLine(x0, y0, b + 1);
   LCD_DrawVLine(x1, y0, b + 1);
}

void LCD_SendByte(uint8_t byte)
{
   /*!< Loop while DR register in not emplty */
   while (SPI_I2S_GetFlagStatus(LCD_SPI, SPI_I2S_FLAG_TXE) == RESET)
      ;

   /*!< Send byte through the SPI1 peripheral */
   SPI_I2S_SendData(LCD_SPI, byte);

   /*!< Wait to receive a byte */
   while (SPI_I2S_GetFlagStatus(LCD_SPI, SPI_I2S_FLAG_RXNE) == RESET)
      ;

   /*!< Return the byte read from the SPI bus */
   SPI_I2S_ReceiveData(LCD_SPI);
}

void LCD_SendData(uint8_t data)
{
   GPIO_SetBits(GPIOD, GPIO_Pin_14); // Set A0 to HIGH to indicate data
   LCD_SendByte(data);
}

void LCD_SendCommand(uint8_t cmd)
{
   GPIO_ResetBits(GPIOD, GPIO_Pin_14); // Set A0 to LOW to indicate command
   LCD_SendByte(cmd);
}

// Sets up the LCD parameters
void setup_LCD()
{
   /* reset sequence for the LCD */
   GPIO_ResetBits(GPIOD,
                  GPIO_Pin_11); // Set LCD_RESET to LOW to reset the device
   delay(50);
   GPIO_SetBits(GPIOD,
                GPIO_Pin_11); // Set LCD_RESET to HIGH to start normal function
   delay(50);

   LCD_SendCommand(CMD_SET_BIAS_7);
   LCD_SendCommand(CMD_SET_ADC_NORMAL);
   LCD_SendCommand(CMD_SET_COM_NORMAL);
   LCD_SendCommand(CMD_SET_DISP_START_LINE);
   LCD_SendCommand(CMD_SET_POWER_CONTROL | 0x4); // VC=1, VR =0, VF = 0
   delay(50);
   LCD_SendCommand(CMD_SET_POWER_CONTROL | 0x6); // VC=1, VR =1, VF = 0
   delay(50);
   LCD_SendCommand(CMD_SET_POWER_CONTROL | 0x7); // VC=1, VR =1, VF = 1
   delay(50);
   LCD_SendCommand(CMD_SET_RESISTOR_RATIO |
                   0x6); // regulator resistor, ref. voltage resistor
   delay(50);
   LCD_SendCommand(CMD_DISPLAY_ON);
   LCD_SendCommand(CMD_SET_VOLUME_FIRST);
   LCD_SendCommand(CMD_SET_VOLUME_SECOND | (0x10 & 0x3f));
}

// Initializes the SPI and GPIO HW for communication with the LCD
void init_LCD()
{
   /* Initialize the corresponding pins */
   GPIO_InitTypeDef GPIO_InitStructure;
   /* Enable clock to GPIOB, C and D */
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
   GPIO_StructInit(&GPIO_InitStructure);
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_14 | GPIO_Pin_15;
   GPIO_Init(GPIOD, &GPIO_InitStructure);

   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
   GPIO_Init(GPIOB, &GPIO_InitStructure);
   GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_SPI2);

   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
   GPIO_Init(GPIOC, &GPIO_InitStructure);
   GPIO_PinAFConfig(GPIOC, GPIO_PinSource2, GPIO_AF_SPI2);
   GPIO_PinAFConfig(GPIOC, GPIO_PinSource3, GPIO_AF_SPI2);

   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
   GPIO_Init(GPIOC, &GPIO_InitStructure);

   RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
   /*!< SPI configuration */
   SPI_InitTypeDef SPI_InitStructure;
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
   SPI_Init(LCD_SPI, &SPI_InitStructure);

   /*!< Enable the LCD_SPI */
   SPI_Cmd(LCD_SPI, ENABLE);

   GPIO_ResetBits(GPIOD,
                  GPIO_Pin_15); // Set CS to LOW to activate SPI communication
   GPIO_SetBits(GPIOC,
                GPIO_Pin_7); // Set BACKLIGHT pin to HIGH to activate backlight
}