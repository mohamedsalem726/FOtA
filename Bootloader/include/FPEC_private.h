/********************************************************/
/* Auther    : Mohamed Salem                            */
/* Date      : 03 SEPT 2021                             */ 
/* Version   : V01                                      */
/********************************************************/

#ifndef _FPEC_PRIVATE_H
#define _FPEC_PRIVATE_H


typedef struct
{
	volatile u32 ACR;
	volatile u32 KEYR;
	volatile u32 OPTKEYR;
	volatile u32 SR;
	volatile u32 CR;
	volatile u32 AR;
	volatile u32 RESERVED;
	volatile u32 OBR;
	volatile u32 WRPR;
}FPEC_Reg;

#define MFPEC ((FPEC_Reg*)0x40022000)


#endif
