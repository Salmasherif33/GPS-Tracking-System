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
 
void LCD_init(void); /*function used to initialize lcd*/
void LCD_displayString(const char *Str);/*function used to display string*/
void LCD_sendCommand(uint8_t command);/*function used to send command to lcd*/
void LCD_displayCharacter(uint8_t data);/*function used to diplay character*/
void LCD_intgerToString(int data);/*function used to convert integer to string*/
void LCD_Clear();/*function used to clear what is  wriiten on  lcd*/
