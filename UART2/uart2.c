#include "uart2.h"

#define GPIO_PD10_M 0x0C0

void UART2_Init()
{
//clock to port D
	
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R3;
  while((SYSCTL_PRGPIO_R & 0x00000008) == 0){};
	//clock to uart2 at port D
	
	SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R2;
	GPIO_PORTD_LOCK_R=GPIO_LOCK_KEY;

	
	//clear enable (disable) uart0
	
	UART2_CTL_R &= ~UART_CTL_UARTEN;
	
	// divider = 16000000/(16*9600) =104.16666
	// 0.16666*64+0.5 = 11
	
	UART2_IBRD_R = 104;
	UART2_FBRD_R = 11;
	
	//fifo enable(16 element) , 8 bit data
	
	UART2_LCRH_R = (UART_LCRH_WLEN_8 | UART_LCRH_FEN);
	
	//enable uart1,TX,RX
	
	UART2_CTL_R |= (UART_CTL_RXE | UART_CTL_TXE | UART_CTL_UARTEN);
	
	GPIO_PORTD_CR_R = 0xFF;
	//select UART instead of GPIO
	
	GPIO_PORTD_AFSEL_R = GPIO_PD10_M;	//011000000
	
	// select uart alternate function
	
	GPIO_PORTD_PCTL_R = ( GPIO_PORTD_PCTL_R  & 0x00FFFFFF ) |  (GPIO_PCTL_PD7_U2TX | GPIO_PCTL_PD6_U2RX);
	
	//digital enable
	
	GPIO_PORTD_DEN_R = GPIO_PD10_M;
	
	//analog disable
	
	//GPIO_PORTA_AMSEL_R &= ~0x03;	
	
}

uint8_t UART2_Available(void){
	return ((UART2_FR_R&UART_FR_RXFE) == UART_FR_RXFE) ? 0 : 1;
}

// to read data from UART ( latitude and longitude )s
uint8_t UART2_Read(void)
{

	//if the reciever is empty busy waiting
	
	while ( UART2_Available() != 1) ;
	
	//we only need first 8 bits
	
	return ( uint8_t ) ( UART2_DR_R & 0xFF ) ; 
	
}


