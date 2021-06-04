
#include"tm4c123gh6pm.h"
#include "stdint.h"
#include "stdio.h"
void SystemInit(){}

char str[3];
float dis=100;
	
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
