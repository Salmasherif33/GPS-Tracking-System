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
 #ifndef LCD_H_
#define LCD_H_
#include"tm4c123gh6pm.h"
#include "stdint.h"
#include "stdio.h"
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/ 
 
void LCD_init(void);
void LCD_displayString(const char *Str);
void LCD_sendCommand(uint8_t command);
