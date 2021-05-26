 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.h
 *
 * Description: Header file for the LCD driver
 *
 *
 *******************************************************************************/

#include "tm4c123gh6pm.h"
#include "stdint.h"
#include "stdio.h"
#include <math.h>
void SystemInit(){} //must in each file
/*define useful symbolic names for LCD commands */
#define clear_display     0x01
#define returnHome        0x02
#define moveCursorRight   0x06
#define moveCursorLeft    0x08
#define shiftDisplayRight 0x1C
#define shiftDisplayLeft  0x18
#define cursorBlink       0x0F
#define cursorOff         0x0C
#define cursorOn          0x0E
#define Function_set_4bit 0x28
#define Function_set_8bit 0x38
#define Entry_mode        0x06
#define Function_8_bit    0x32
#define Set5x7FontSize    0x20
#define FirstRow          0x80
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
 void LCD_init(void);
void LCD_sendCommand(uint8_t command);
void LCD_Data(uint8_t data); 
void LCD_displayCharacter(uint8_t data);
void LCD_displayString(const char *Str);
void LCD_intgerToString(int data);
