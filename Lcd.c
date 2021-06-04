
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
 // send command to LCD
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
 //send data as string
void LCD_displayString(const char *Str)
{
	uint8_t i = 0;
	while(Str[i] != '\0')
	{
		LCD_displayCharacter(Str[i]);
		i++;
	}
}

//send data as char
void LCD_displayCharacter(uint8_t data)

 {

   GPIO_PORTD_DATA_R |=0xf1; /* Instruction Mode RS=1 /write data to LCD so RW=0/ENABLE=0 */

	 GPIO_PORTD_DATA_R =(data>>4)&0xf0;/*write data*/

	 GPIO_PORTD_DATA_R |=0X04;/*enable=1*/

	 GPIO_PORTD_DATA_R &=0xFB;/*enable =0*/

	 GPIO_PORTD_DATA_R =data&0xf0;/*write data*/

	 GPIO_PORTD_DATA_R |=0X04;/*enable=1*/

	 GPIO_PORTD_DATA_R &=0xFb;/*enable =0*/

	 /*delay*/

SysTick_Wait(270000);

}
// convert integer to string

void LCD_intgerToString(int data)

{

    int i, rem, len = 0, n;

   unsigned char numberArray[10];

    n = data;

    while (n != 0)

    {

        len++;

        n /= 10;

    }

    for (i = 0; i < len; i++)

    {

        rem = data % 10;

        data= data/ 10;

        numberArray[len - (i + 1)] = rem + '0';

    }

    numberArray[len] = '\0';

		LCD_displayString(numberArray);

}
// clear the lcd values to write new one

 void LCD_Clear()

{

   LCD_sendCommand(clear_display ); // clear the screen

   SysTick_Wait(32000);// for the problem of missing first charachter 

}	

