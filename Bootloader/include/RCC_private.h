/************************************************/
/* Auther   : Mohamed Salem                     */
/* Date     : 17 APRIL 2021                     */ 
/* Version  : V01                               */
/************************************************/
#ifndef RCC_PRIVATE_H
#define RCC_PRIVATE_H


/* Register Definitions */
typedef struct{
	volatile u32 CR;
	volatile u32 CFGR;
	volatile u32 CIR;
	volatile u32 APB2RSTR;
	volatile u32 APB1RSTR;
	volatile u32 AHBENR;
	volatile u32 APB2ENR;
	volatile u32 APB1ENR;
	volatile u32 BDCR;
	volatile u32 CSR;
}RCC_Register;

#define MRCC ((volatile RCC_Register*)0x40021000)


#endif