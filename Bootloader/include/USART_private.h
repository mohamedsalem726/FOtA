
/*******************************************************/
/* Auther    : Mohamed Salem                           */
/* Date      : 01 MAY 2021                             */ 
/* Version   : V01                                     */
/*******************************************************/

#ifndef _UART_PRIVATE_H
#define _UART_PRIVATE_H

typedef struct{
	volatile u32 SR;
	volatile u32 DR;
	volatile u32 BRR;
	volatile u32 CR[3];
	volatile u32 GTPR;
}USART_Register;

#define MUSART1    ((volatile USART_Register*)0x40013800)


#endif

