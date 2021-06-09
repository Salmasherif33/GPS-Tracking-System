
#include "uart.h"
#include "uart2.h"
#include "GPIO.h"
#include "distance.h"
#include "Lcd.h"
#incude "systick.h"
#include "GPScutting.h"
#include <stdlib.h>
#include <string.h>

#define RED 0x02
#define BLUE 0x04
#define GREEN 0x08

//store in theses arrays after cuuting the string of GPS module
char latitude[11] = {'0','0','0','0','0','0','0','0','0','0','\0'};
char langitude[11] = {'0','0','0','0','0','0','0','0','0','0','\0'};

void SystemInit(){}

/*Theses arrays were dummy data for testing*/	
//volatile float lat[9]={48.85837,48.85836,48.85836,48.85836,48.85839,48.85827,48.85821,48.85827,48.85832};
//volatile float lang[9]={2.29448,2.29452,2.29457,2.29464,2.29463,2.29474,2.29440,2.29491,2.29490};
int main(void){
	int deg;
	float lat;
	float lang;
	
	SysTick_Init();
	LCD_init();
	UART0_Init();
	UART2_Init();
	init();
	
	while(1){
		//if there is a correct data comes from GPS
		if(GPSModule(latitude,langitude)){
			//convert from GPS NMEA coordinates, to Google Maps coordinates
			lat = atof(latitude);
			deg =(lat/100);
			lat = deg + ( lat - (float)(deg*100)) / 60.00;
			
			lang = atof(langitude);
			deg =(lang/100);
			lang = deg + ( lang - (float)(deg*100)) / 60.00;
		}
		

	}	

	return 0;	
}
