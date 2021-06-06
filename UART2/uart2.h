
#ifndef __uart_gps_H__
#define __uart_gps_H__

#include "stdint.h"
#include "tm4c123gh6pm.h"


void UART2_Init(void);
uint8_t UART2_Available(void);
uint8_t UART2_Read(void);


#endif

