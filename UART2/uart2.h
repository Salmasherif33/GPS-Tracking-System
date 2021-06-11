#ifndef __uart2_H__
#define __uart2_H__


#include "stdint.h"
#include "tm4c123gh6pm.h"


//proto types for the functions


void UART2_Init(void);   //initializing uart2
uint8_t UART2_Available(void);  //if the gps is sending data or not 
uint8_t UART2_Read(void);  // to read data from UART latitude and longitude





#endif

