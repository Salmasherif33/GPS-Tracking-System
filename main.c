
#include "uart.h"
#include "uart2.h"
#include "GPIO.h"
#include "distance.h"
#include "Lcd.h"
#include "systick.h"
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
	volatile float dist=0;//variable to save distance after calling function that calculate distance between two points
	int deg;
	float lat_arr[1000];/*array to save latitude */
	float lang_arr[1000];/*array to save langtude*/
        int counter=0;/*variable used as acounter to increased every time  */
	float lat;
	float lang;
	float lat1;
	float lang1;
	int x;
	
	SysTick_Init();/*to intialize systick for delays*/
	LCD_init();/*function to initalize lcd */
	UART0_Init();/*function to initialize uart0*/
	UART2_Init();/*function to initialize uart1*/
	init();/*/*function to initialize led*/
	
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
