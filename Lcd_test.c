
#include"tm4c123gh6pm.h"
#include "stdint.h"
#include "stdio.h"
#include "Lcd.h"
void SystemInit(){}

char str[3];
float dis=100;
	
int main()
{
	int i = 0;
	SysTick_Init(); //initiate systick for delays
	LCD_init();  //initiate lcd 
	sprintf(str,"%f",dis);   //convert float to string 
	LCD_sendCommand(1); /* clear display */
        LCD_sendCommand(0x80); /* LCD cursor location */
		
	while(str[i] != '\0')// loop to diplay characters
	{
		LCD_displayCharacter(str[i]);//diplay character
		i++;
	}
		SysTick_Wait1ms(500);//delay 500ms
while(1)
{

}
}
