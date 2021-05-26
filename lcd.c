
 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.c
 *
 * Description: Source file for the LCD driver
 *******************************************************************************/
#include "lcd.h"
#include "delay.h"


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

 /*4pit*//*rs bit 4  rw bit 5 enable bit 6*/
 void LCD_init(void)
 {SYSCTL_RCGCGPIO_R |= 0x00000001; // activate Port A
  while((SYSCTL_PRGPIO_R&=0x00000001) == 0){};
	GPIO_PORTA_AMSEL_R &= 0x80;         /* Disable Analog on PORTA */
  GPIO_PORTA_PCTL_R   &= 0x10000000;   /* Clear PMCx bits for  PORTA to use it as GPIO pin */
  GPIO_PORTA_DIR_R    |= 0x7F;         /* Configure PORTA as output pin */
  GPIO_PORTA_AFSEL_R &= 0x80;         /* Disable alternative function on PORTA */
  GPIO_PORTA_DEN_R   |= 0x7F;         /* Enable Digital I/O onPORTA */
  GPIO_PORTA_DATA_R   &= 0x80;         /* Clear bit PORTA in Data regsiter to turn off the leds */
	
 LCD_sendCommand(Function_set_4bit); /* Select 4-bit Mode of LCD */
 LCD_sendCommand(clear_display); /* clear whatever is written on display */
 LCD_sendCommand(moveCursorRight); /* shift cursor right */
 LCD_sendCommand(cursorBlink);  /* Enable Display and cursor blinking */
	
 }
 

 void LCD_sendCommand(uint8_t command)
 {    GPIO_PORTA_DATA_R &=0x8f;    /*Instruction Mode RS=0 /write data to LCD so RW=0/ENABLE=0 */
	 /* out the highest 4 bits of the required command to the data bus D4 --> D7 */
    GPIO_PORTA_DATA_R =(command>>4)&0x0f;/*write data*/
	 GPIO_PORTF_DATA_R |=0X40;/*enable=1*/
	 GPIO_PORTF_DATA_R &=0xbf;/*enable =0*/
	 /* out the lowest 4 bits of the required command to the data bus D4 --> D7 */
	  GPIO_PORTA_DATA_R =command&0x0f;/*write data*/
	 	 GPIO_PORTA_DATA_R |=0X40;/*enable=1*/
	 GPIO_PORTA_DATA_R &=0xbf;/*enable =0*/
/*delay*/
	 SysTick_Init();
 }
 void LCD_displayCharacter(uint8_t data)
 {
  GPIO_PORTA_DATA_R |=0x1f; /* Instruction Mode RS=1 /write data to LCD so RW=0/ENABLE=0 */
	 GPIO_PORTA_DATA_R =(data>>4)&0x0f;/*write data*/
	 	 GPIO_PORTF_DATA_R |=0X40;/*enable=1*/
	 GPIO_PORTF_DATA_R &=0xbf;/*enable =0*/
	 GPIO_PORTA_DATA_R =data&0x0f;/*write data*/
	 	GPIO_PORTA_DATA_R |=0X40;/*enable=1*/
	 GPIO_PORTA_DATA_R &=0xbf;/*enable =0*/
	 /*delay*/
SysTick_Init();
}
 
 
 
void LCD_displayString(const char *Str)
{
	uint8_t i = 0;
	while(Str[i] != '\0')
	{
		LCD_displayCharacter(Str[i]);
		i++;
	}}

	void LCD_intgerToString(int data)
{
   char buff[16]; /* String to hold the ascii result */
   itoa(data,buff,10); /* 10 for decimal */
   LCD_displayString(buff);
	/*
	   int c = 0;
    unsigned int n = number;

    while (n != 0)
    {
        n /= 10;
        c++;
    }

    unsigned char numberArray[20];

    //c = 0;
    n = number;
    numberArray[c] = '\0';
    c-- ;
    while (n != 0)
    {
        numberArray[c] =( n % 10 ) + 48 ;
        n /= 10;
        c--;
    }
    numberArray[c] = '\0';

    lcdWriteString(numberArray);
	
	*/
}
	
	
