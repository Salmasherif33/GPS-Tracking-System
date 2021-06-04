
#include"tm4c123gh6pm.h"
#include "stdint.h"
#include "stdio.h"
void SystemInit(){}

char str[3];
float dis=100;
	
//send data
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
	
int main()
{
	int i = 0;
	SysTick_Init();
	LCD_init();
	sprintf(str,"%f",dis);
	LCD_sendCommand(1); /* clear display */
  LCD_sendCommand(0x80); /* LCD cursor location */
		
	while(str[i] != '\0')
	{
		LCD_displayCharacter(str[i]);
		i++;
	}
		SysTick_Wait1ms(500);
while(1)
{

}
}
