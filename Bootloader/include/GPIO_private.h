/*****************************************************/
/* Auther    : Mohamed Salem                         */
/* Date      : 12 FEB 2021                           */ 
/* Version   : V01                                   */
/*****************************************************/
#ifndef _GPIO_PRIVAT_H
#define _GPIO_PRIVAT_H


typedef struct{
	volatile u32 CRL  ;//0x00
	volatile u32 CRH  ;//0x04
    volatile u32 IDR  ;//0x08
    volatile u32 ODR  ;//0x0C
    volatile u32 BSRR ;//0x10
    volatile u32 BRR  ;//0x14
    volatile u32 LCKR ;//0x18
}GPIO;

#define MGPIOA ((volatile GPIO*)0x40010800) 	 
#define MGPIOB ((volatile GPIO*)0x40010C00)
#define MGPIOC ((volatile GPIO*)0x40011000)





#endif