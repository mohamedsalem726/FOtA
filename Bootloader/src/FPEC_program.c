/********************************************************/
/* Auther    : Mohamed Salem                            */
/* Date      : 03 SEPT 2021                             */ 
/* Version   : V01                                      */
/********************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "FPEC_interface.h"
#include "FPEC_private.h"
#include "FPEC_config.h"

void MFPEC_voidEraseAppArea(void)
{
	u8 i;
	
	for (i=18;i<64;i++)
	{
		MFPEC_voidFlashPageErase(i);
	}
}

void MFPEC_voidFlashPageErase(u8 Copy_u8PageNumber)
{
	/* Wait Busy Flag */
	while (GET_BIT(MFPEC->SR,0) == 1);

	/* Check if FPEC is locked or not */
	if ( GET_BIT(MFPEC->CR,7) == 1)
	{
		MFPEC -> KEYR = 0x45670123;
		MFPEC -> KEYR = 0xCDEF89AB;
	}
	
	/* Page Erase Operation */
	SET_BIT(MFPEC->CR,1);

	/* Write Page address */
	MFPEC->AR = (u32)(Copy_u8PageNumber * 1024) + 0x08000000 ;

	/* Start operation */
	SET_BIT(MFPEC->CR,6);

	/* Wait Busy Flag */
	while (GET_BIT(MFPEC->SR,0) == 1);

	/* EOP */
	SET_BIT(MFPEC->SR,5);
	CLR_BIT(MFPEC->CR,1);
}

void MFPEC_voidFlashWrite(u32 Copy_u32Address, u16* Copy_u16Data, u8 Copy_u8Length)
{
	u8 i;
	volatile u16 Temp;

	/* Wait Busy Flag */
	while (GET_BIT(MFPEC->SR,0) == 1);

	/* Check if FPEC is locked or not */
	if ( GET_BIT(MFPEC->CR,7) == 1 )
	{
		MFPEC -> KEYR = 0x45670123;
		MFPEC -> KEYR = 0xCDEF89AB;
	}
	
	
	for (i = 0; i< Copy_u8Length; i++)
	{
		/* Write Flash Programming */
		SET_BIT(MFPEC->CR,0);

		/* Half word operation */

		Temp = Copy_u16Data[i];
		*((volatile u16*)Copy_u32Address) = Copy_u16Data[i];
		Copy_u32Address += 2 ;

		/* Wait Busy Flag */
		while (GET_BIT(MFPEC->SR,0) == 1);
	
		/* EOP */
		SET_BIT(MFPEC->SR,5);
		CLR_BIT(MFPEC->CR,0);
	}
}
