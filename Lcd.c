
 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.c
 *
 * Description: Source file for the LCD driver

 *******************************************************************************/
 #include "Lcd.h"
 /*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*4bit*//*rs bit PD0  rw bit PD1 enable bit PD2 AND DATA PC7 PC6 PC5 PC4*/
 void LCD_init(void)
 {SysTick_Wait(800000);//wait 50ms 
	 SYSCTL_RCGCGPIO_R |= 0x00000002; // activate  PORTB
  while((SYSCTL_PRGPIO_R&=0x00000002) == 0){};
	GPIO_PORTB_AMSEL_R &= 0x08;         /* Disable Analog on  */
	GPIO_PORTB_PCTL_R   &= 0x0000F000;   /* Clear PMCx bits for PB7 PB6 PB5 PB4 to use it as GPIO pin */
	GPIO_PORTB_DIR_R    |= 0xF7;         /* Configure PB7 PB6 PB5 PB4 as output pin */
	GPIO_PORTB_AFSEL_R &= 0x08;         /* Disable alternative function on  PB7 PB6 PB5 PB4 */
	GPIO_PORTB_DEN_R   |= 0xF7;         /* Enable Digital I/O on  PB7 PB6 PB5 PB4*/
	GPIO_PORTB_DATA_R   &= 0x08;         /* Clear bit PB7 PB6 PB5 PB4 in Data regsiter to turn off the leds */
		LCD_sendCommand(0x28); /* Select 4-bit Mode of LCD */
		SysTick_Wait(16000);
	LCD_sendCommand(0x0E);
			SysTick_Wait(16000);//delay 1ms
	LCD_sendCommand(0X01); /* clear whatever is written on display */
			SysTick_Wait(32000);
			LCD_sendCommand(0X06);
		SysTick_Wait(32000);
		}
 
 void LCD_sendCommand(uint8_t command)
 {    GPIO_PORTB_DATA_R &=0xFC;    /*Instruction Mode RS=0 PD0 /write data to LCD so RW=0 PD1/ENABLE=0 PD2 */
	 /* out the highest 4 bits of the required command to the data bus D4 --> D7 */
    GPIO_PORTB_DATA_R =( GPIO_PORTB_DATA_R& 0x0F) | (command & 0xF0);/*write data*/
	 GPIO_PORTB_DATA_R |=0X04;/*enable=1 PD2*/
	SysTick_Wait(32000);//delay 2ms
	 GPIO_PORTB_DATA_R &=0xFB;/*enable =0 PD2*/
	 /* out the lowest 4 bits of the required command to the data bus D4 --> D7 */
	  GPIO_PORTB_DATA_R =( GPIO_PORTB_DATA_R & 0x0F) | ((command & 0x0F) << 4);/*write data*/
	 	 GPIO_PORTB_DATA_R |=0X04;/*enable=1*/
	   SysTick_Wait(32000);//delay2ms
	 GPIO_PORTB_DATA_R &=0xFB;/*enable =0*/
  
 }
void LCD_displayString(const char *Str)
{
	uint8_t i = 0;
	while(Str[i] != '\0')
	{
		LCD_displayCharacter(Str[i]);
		i++;
	}}

