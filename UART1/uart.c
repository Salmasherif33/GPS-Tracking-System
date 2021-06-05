
//---------------------------------------------------------------------UART------------------------------------------------------------------------


#include "uart.h"


void INIT_UART( )
{

	//clock to uart1 at port B
	
	SYSCTL_RCGCUART_R |= 0x0002;
	
	//clock to port B
	
	SYSCTL_RCGCGPIO_R |= 0x0002;
	
	//clear enable (disable) uart1
	
	UART1_CTL_R&=~0x0001;
	
	// divider = 80000000/(16*9600) =520.8333
	// 0.8333*64+0.5 = 53
	
	UART1_IBRD_R = 520;
	UART1_FBRD_R = 53;
	
	//fifo enable(16 element) , 8 bit data
	
	UART1_LCRH_R = 0x0070;
	
	//enable uart1,TX,RX
	
	UART1_CTL_R = 0x301;
	
	//select UART instead of GPIO
	
	GPIO_PORTB_AFSEL_R |= 0x03;	
	
	// select uart alternate function
	
	GPIO_PORTB_PCTL_R = ( GPIO_PORTB_PCTL_R  & 0xffffff00 ) + 0x00000011;
	
	//digital enable
	
	GPIO_PORTB_DEN_R |= 0x03;
	
	//analog disable
	
	GPIO_PORTB_AMSEL_R &= ~0x03;	
	
}


// to read data from UART ( latitude and longitude )s
float UART_READ( )
{

	//if the reciever is empty busy waiting
	
	while ( ( UART1_FR_R & 0x0010 )  != 0) { } ;
	
	//we only need first 8 bits
	
	return ( ( float ) ( UART1_DR_R & 0x00ff ) ) ; 
	
}




//---------------------------------------------------------------------------------------------------------------------------------------------------

