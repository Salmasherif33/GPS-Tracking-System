#include "stdint.h"
#include "E:/3rd_computer2/keil v_4/keil/EE319Kware/inc/tm4c123gh6pm.h"
#define GPIO_PA10_M 0x03

void init(){
	
	//to check the port connection to the clock
	//set port f        00100000
  SYSCTL_RCGCGPIO_R |=0x20;
  while((SYSCTL_PRGPIO_R&0x020) == 0){};
	GPIO_PORTF_LOCK_R=0x4C4F434B;
	//commit reg
	GPIO_PORTF_CR_R=0x1F;
	// i will use GPIO only
	GPIO_PORTF_AFSEL_R=0;
	GPIO_PORTF_PCTL_R=0;
	//i will use digital only
	GPIO_PORTF_AMSEL_R=0;
	// pin1,2,3  output      00001110
	GPIO_PORTF_DIR_R=0x0E;
	// pin 1,2,3,4,5 are digital
	GPIO_PORTF_DEN_R=0x1F;
	// for input       00010001
	GPIO_PORTF_PUR_R=0x11;
	GPIO_PORTF_DATA_R=0;
}
void LED_ON(uint8_t led){
	GPIO_PORTF_DATA_R  = (GPIO_PORTF_DATA_R & 0xF1) | led; /* Turn on the Red LED and disbale the others */
	
	
}
void Port_B(void)
 {SYSCTL_RCGCGPIO_R |= 0x02; /* activate Port B */
  while((SYSCTL_PRGPIO_R&=0x00000002) == 0){};/*waite to activate*/ 
  GPIO_PORTB_AMSEL_R &= 0;         /* Disable Analog on PORTB*/
  GPIO_PORTB_PCTL_R   &= 0x00000000;   /* Clear PMCx bits for  PORTB to use it as GPIO pin */
  GPIO_PORTB_DIR_R    |= 0xFF;         /* Configure PORTB as output pin */
  GPIO_PORTB_AFSEL_R &= 0x0;         /* Disable alternative function on PORTB */
  GPIO_PORTB_DEN_R   |= 0xFF;         /* Enable Digital I/O onPORTB */
  GPIO_PORTB_DATA_R   &= 0x0;         /* Clear data in PORT B */
	}
	
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