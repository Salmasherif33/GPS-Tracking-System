#include "uart.h"

#define GPIO_PA10_M 0x03

void UART0_Init()
{
//clock to port A
SYSCTL_RCGCUART_R |= 0x01;
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0;

	//clock to uart0 at port A
	

	

	
	//clear enable (disable) uart0
	
	UART0_CTL_R &= ~UART_CTL_UARTEN;
	
	// divider = 16000000/(16*9600) =104.16666
	// 0.16666*64+0.5 = 11
	
	UART0_IBRD_R = 104;
	UART0_FBRD_R = 11;
	
	//fifo enable(16 element) , 8 bit data
	
	UART0_LCRH_R = (UART_LCRH_WLEN_8 | UART_LCRH_FEN);
	
	//enable uart0,TX,RX
	
	UART0_CTL_R |= (UART_CTL_RXE | UART_CTL_TXE | UART_CTL_UARTEN);
	
	//select UART instead of GPIO
	
	GPIO_PORTA_AFSEL_R |= GPIO_PA10_M;	
	
	// select uart alternate function
	
	GPIO_PORTA_PCTL_R = ( GPIO_PORTA_PCTL_R  & 0xFFFFFF00 ) |  (GPIO_PCTL_PA1_U0TX | GPIO_PCTL_PA0_U0RX);
	
	//digital enable
	
	GPIO_PORTA_DEN_R |= GPIO_PA10_M;
	
	//analog disable
	
	//GPIO_PORTA_AMSEL_R &= ~0x03;	
	
}

uint8_t UART0_Available(void){
	return ((UART0_FR_R&UART_FR_RXFE) == UART_FR_RXFE) ? 0 : 1;
}

// to read data from UART ( latitude and longitude )s
uint8_t UART0_Read(void)
{

	//if the reciever is empty busy waiting
	
	while ( UART0_Available() != 1) ;
	
	//we only need first 8 bits
	
	return ( uint8_t ) ( UART0_DR_R & 0xFF ) ; 
	
}


void uart0_write(uint8_t data){
	while ((UART0_FR_R & UART_FR_TXFF) != 0 );
	UART0_DR_R = data;

}

