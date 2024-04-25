#ifndef __LCD_FONTS_H
#define __LCD_FONTS_H
#include "stm32f10x.h"
/* From lcd_st7576p library */
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
#endif /* __LCD_FONTS_H */