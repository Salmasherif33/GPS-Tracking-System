#include "tm4c123gh6pm.h"

#include "UART.h"
#include "GPIO.h"
#include "distance.h"
#include "systick.h"

//#include "systic.h"
#define RED 0x02
#define BLUE 0x04
#define GREEN 0x08

void SystemInit(){}
	
volatile float lat[9]={48.85837,48.85836,48.85836,48.85836,48.85839,48.85827,48.85821,48.85827,48.85832};
volatile float lang[9]={2.29448,2.29452,2.29457,2.29464,2.29463,2.29474,2.29440,2.29491,2.29490};
int main(){
	volatile float dist=0;

	
	UART0_Init();
	init();
	while(1){
		
		volatile float dist=0;
		int i;
		for( i=0;i<8;i++)
		{dist+=calc_dist_bet_2_points (lat[i], lat[i+1], lang[i], lang[i+1]);
	if (dist >=100)
	{LED_ON(RED);
	break;}

	}	
}
	}
