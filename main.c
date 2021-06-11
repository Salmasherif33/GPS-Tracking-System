/*
 * main.c
 *Gps_Tracking System the led will turn on after 100meter
 *and the lcd will display the value then break  
 */ 

#include "uart.h"
#include "uart2.h"
#include "GPIO.h"
#include "distance.h"
#include "Lcd.h"
#include "systick.h"
#include "GPScutting.h"
#include <stdlib.h>
#include <string.h>

#define RED 0x02 /* red led*/
#define BLUE 0x04 /*blude red*/
#define GREEN 0x08/*green led*/

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
	
	
	
	SysTick_Init();/*to intialize systick for delays*/
	LCD_init();/*function to initalize lcd */
	UART0_Init();/*function to initialize uart0*/
	UART2_Init();/*function to initialize uart1*/
	init();/*function to initialize led*/
	
	while(1){
		//if there is a correct data comes from GPS
		if(GPSModule(latitude,langitude))
		{
			//convert from GPS NMEA coordinates, to Google Maps coordinates
			lat = atof(latitude);
			deg =(lat/100);
			lat = deg + ( lat - (float)(deg*100)) / 60.00;
			
			lang = atof(langitude);
			deg =(lang/100);
			lang = deg + ( lang - (float)(deg*100)) / 60.00;
			lat_arr[counter]=lat;/*store in the array of altitude*/
	                lang_arr[counter]=lang;/*store in the array of longitude*/
			if(counter!=0)
			{
				 dist+=calc_dist_bet_2_points(lat_arr[counter-1],lat_arr[counter],lang_arr[counter-1],lang_arr[counter]);
				
				if(dist>=100)
				{ 
			            LED_ON(RED);/*turn on red led when distance ==100*/
				    LCD_Clear();/*clear screen*/
				    LCD_displayfloat(dist);/*display distance on lcd*/
				    break;/*break from the while(1)after 100 meter*/
			        }
		         }
				counter++;/*increase counter by 1*/
				SysTick_Wait1ms(1000);//delay 1 sec
              }	
	}

	return 0;	
}
