#ifndef __uart_H__
#define __uart_H__

#include "stdint.h"
#include "tm4c123gh6pm.h"

//proto types for the functions

void UART0_Init(void);
uint8_t UART0_Available(void);
uint8_t UART0_Read(void);
void uart0_write(uint8_t data);




#endif 
