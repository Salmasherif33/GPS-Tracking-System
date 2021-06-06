
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
/*4bitmode
*Rs----->PB0
*R/W---->PB1
*Enable->PB2
*DATA-->PB4-PB5-PB6-PB7
*/
/*
*Function Description:used to intialize lcd and portB
*/
 void LCD_init(void)
 {SYSCTL_RCGCGPIO_R |= 0x02; /* activate Port B */
  while((SYSCTL_PRGPIO_R&=0x00000002) == 0){};/*waite to activate*/ 
  GPIO_PORTB_AMSEL_R &= 0;         /* Disable Analog on PORTB*/
  GPIO_PORTB_PCTL_R   &= 0x00000000;   /* Clear PMCx bits for  PORTB to use it as GPIO pin */
  GPIO_PORTB_DIR_R    |= 0xFF;         /* Configure PORTB as output pin */
  GPIO_PORTB_AFSEL_R &= 0x0;         /* Disable alternative function on PORTB */
  GPIO_PORTB_DEN_R   |= 0xFF;         /* Enable Digital I/O onPORTB */
  GPIO_PORTB_DATA_R   &= 0x0;         /* Clear data in PORT B */
  SysTick_Wait1ms(20);//delay 20ms
LCD_sendCommand(0X30);//wakeup
SysTick_Wait1ms(5);//DELAY 5mS
LCD_sendCommand(0X30);//wakeup
SysTick_Wait1us(100);//DELAY 40uS
LCD_sendCommand(0X30);//wakeup
SysTick_Wait1us(40);//DELAY 40uS
LCD_sendCommand(0x20); /* use 4-bit data mode */
SysTick_Wait1us(40);//DELAY 40uS
 LCD_sendCommand(0X28); /* Select 4-bit Mode of LCD */
 LCD_sendCommand(0X06); /* clear whatever is written on display */
 LCD_sendCommand(0X01); /* shift cursor right */
 LCD_sendCommand(0X0F);  /* Enable Display and cursor blinking */
 }
 // send command to LCD
 void LCD_sendCommand(uint8_t command)
 {
GPIO_PORTB_DATA_R &=0xFC;    /*Instruction Mode RS=0 /write data to LCD so RW=0 */
/* out the highest 4 bits of the required command to the data bus D4 --> D7 */
GPIO_PORTB_DATA_R = ((GPIO_PORTB_DATA_R & 0x0F) | (command & 0xF0));
GPIO_PORTB_DATA_R |=0X04;/*enable=1*/
SysTick_Wait1us(40);//delay 40us 
GPIO_PORTB_DATA_R &=0xFB;/*enable =0*/
/* out the lowest 4 bits of the required command to the data bus D4 --> D7 */
 GPIO_PORTB_DATA_R = ((	GPIO_PORTB_DATA_R & 0x0F) | ((command<< 4)&0xF0));/*write data*/
GPIO_PORTB_DATA_R |=0X04;/*enable=1*/
 SysTick_Wait1us(40);
GPIO_PORTB_DATA_R &=0xFB;/*enable =0*/
if(command<4)
SysTick_Wait1ms(2);//delay 2ms	 
else 
SysTick_Wait1us(40);//delay 40us
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
 GPIO_PORTB_DATA_R |=0x01; /* Instruction Mode RS=1 /write data to LCD so RW=0/ENABLE=0 */
GPIO_PORTB_DATA_R = ( GPIO_PORTB_DATA_R & 0x0F) | (data& 0xF0);
GPIO_PORTB_DATA_R |=0X04;/*enable=1*/
SysTick_Wait1us(40); 	 
GPIO_PORTB_DATA_R &=0xFB;/*enable =0*/
GPIO_PORTB_DATA_R = ((	GPIO_PORTB_DATA_R & 0x0F) | ((data<< 4)&0xF0));/*write data*/
GPIO_PORTB_DATA_R |=0X04;/*enable=1*/
SysTick_Wait1us(40); 	
GPIO_PORTB_DATA_R &=0xFB;/*enable =0*/
SysTick_Wait1us(40); 	 
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

void LCD_goToRowColumn(uint8 row,uint8 col)
{
	uint8 Address;
	
	/* first of all calculate the required address */
	switch(row)
	{
		case 0:
				Address=col;
				break;
		case 1:
				Address=col+0x40;
				break;
		case 2:
				Address=col+0x10;
				break;
		case 3:
				Address=col+0x50;
				break;
	}					
	/* to write to a specific address in the LCD 
	 * we need to apply the corresponding command 0b10000000+Address */
	LCD_sendCommand(Address | SET_CURSOR_LOCATION); 
}

	void LCD_displayfloat(float data){
		char str[7];
		int i;
		i=0;
	sprintf(str,"%f",data);
	LCD_sendCommand(1); /* clear display */
LCD_sendCommand(0x80); /* LCD cursor location */
		
	while(str[i] != '\0')
	{
		LCD_displayCharacter(str[i]);
		i++;
	}
		SysTick_Wait1ms(500);
	}

