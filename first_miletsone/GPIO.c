

#include "tm4c123gh6pm.h"
#include "GPIO.h"
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