#ifndef __UART_H__
#define __UART_H__

#include "stdint.h"
#include "C:/Keil/EE319Kware/inc/tm4c123gh6pm.h"

//proto types for the functions

void UART0_Init(void);
uint8_t UART0_Available(void);
uint8_t UART0_Read(void);
void uart0_write(uint8_t data);




#endif //__UART_H__
