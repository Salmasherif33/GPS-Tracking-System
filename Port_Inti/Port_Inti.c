#include "stdint.h"
#include "tm4c123gh6pm.h"
#define GPIO_PA10_M 0x03

void Init_port_F(void)
{
GPIO_PORTF_AMSEL_REG &= 0xF1; /* Disable Analog on PF1, PF2 and PF3 */
GPIO_PORTF_PCTL_REG &= 0xFFFF000F; /* Clear PMCx bits for PF1, PF2 and PF3 to use it as GPIO pin */
GPIO_PORTF_DIR_REG |= 0x0E; /* Configure PF1, PF2 and PF3 as output pin */
GPIO_PORTF_AFSEL_REG &= 0xF1; /* Disable alternative function on PF1, PF2 and PF3 */
GPIO_PORTF_DEN_REG |= 0x0E; /* Enable Digital I/O on PF1, PF2 and PF3 */
GPIO_PORTF_DATA_REG &= 0xF1; /* Clear bit 0, 1 and 2 in Data regsiter to turn off the leds */
}

void Init_Port_B(void)
 {SYSCTL_RCGCGPIO_R |= 0x02; /* activate Port B */
  while((SYSCTL_PRGPIO_R&=0x00000002) == 0){};/*waite to activate*/ 
  GPIO_PORTB_AMSEL_R &= 0;         /* Disable Analog on PORTB*/
  GPIO_PORTB_PCTL_R   &= 0x00000000;   /* Clear PMCx bits for  PORTB to use it as GPIO pin */
  GPIO_PORTB_DIR_R    |= 0xFF;         /* Configure PORTB as output pin */
  GPIO_PORTB_AFSEL_R &= 0x0;         /* Disable alternative function on PORTB */
  GPIO_PORTB_DEN_R   |= 0xFF;         /* Enable Digital I/O onPORTB */
  GPIO_PORTB_DATA_R   &= 0x0;         /* Clear data in PORT B */
}
	
void UART0_Init()
{
	//clock to uart0 at port A
	
	SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R0;
	
	//clock to port A
	
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0;
  while((SYSCTL_PRGPIO_R&0x01) == 0){};
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
