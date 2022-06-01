/*******************************************************/
/* Auther    : Mohamed Salem                           */
/* Date      : 01 MAY 2021                             */ 
/* Version   : V01                                     */
/*******************************************************/




#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "USART_interface.h"
#include "USART_private.h"
#include "USART_config.h"

#define THRESHOLD_VALUE           9000000UL
#define MUSART1_BAUD_RATE         (u32)9600

void MUSART1_voidInit(void)
{
	u32 LOC_u32Mantissa = ( F_CPU ) / ( 16 * MUSART1_BAUD_RATE) ;

	u32 LOC_u32Fraction = ( ( ( F_CPU * 100 ) / ( 16 * MUSART1_BAUD_RATE )  ) % 100 ) * 16 ;

	if( LOC_u32Fraction > 1500 ){ LOC_u32Mantissa += 1 ; LOC_u32Fraction  = 0 ; }

		#if MUSART1_STATUS == MUSART1_ENABLE

		MUSART1 -> SR = 0 ;

		#if MUSART1_WORD_LENGTH == _8BIT_WORD_LENGTH

					CLR_BIT( MUSART1 -> CR[0] , 12 );

		#elif MUSART1_WORD_LENGTH == _9BIT_WORD_LENGTH

					SET_BIT( MUSART1 -> CR[0] , 12 );

		#endif

		#if   MUSART1_PARITY == PARITY_DISABLE

					CLR_BIT( MUSART1 -> CR[0] , 10 );

		#elif MUSART1_PARITY == EVEN_PARITY

					SET_BIT( MUSART1 -> CR[0] , 10 );
					CLR_BIT( MUSART1 -> CR[0] , 11 );

		#elif MUSART1_PARITY == ODD_PARITY

					SET_BIT( MUSART1 -> CR[0] , 10 );
					SET_BIT( MUSART1 -> CR[0] , 11 );

		#endif

		#if  MUSART1_INTERRUPT == INT_DISABLE

					CLR_BIT( MUSART1 -> CR[0] , 5 );
					CLR_BIT( MUSART1 -> CR[0] , 6 );
					CLR_BIT( MUSART1 -> CR[0] , 7 );

		#elif MUSART1_INTERRUPT == TXE_INT_ENABLE

					SET_BIT( MUSART1 -> CR[0] , 7 );

		#elif MUSART1_INTERRUPT == TCE_INT_ENABLE

					SET_BIT( MUSART1 -> CR[0] , 6 );

		#elif MUSART1_INTERRUPT == RXNE_INT_ENABLE

					SET_BIT( MUSART1 -> CR[0] , 5 );

		#endif

		#if   MUSART1_TRANSMITTER == TRANSMITTER_ENABLE

					SET_BIT( MUSART1 -> CR[0] , 3 );

		#elif MUSART1_TRANSMITTER == TRANSMITTER_DISABLE

					CLR_BIT( MUSART1 -> CR[0] , 3 );

		#endif

		#if   MUSART1_RECEIVER == RECEIVER_ENABLE

					SET_BIT( MUSART1 -> CR[0] , 2 );

		#elif MUSART1_RECEIVER == RECEIVER_DISBLE

					CLR_BIT( MUSART1 -> CR[0] , 2 );

		#endif

		#if   MUSART1_STOP_BITS == ONE_STOP_BIT

					CLR_BIT( MUSART1 -> CR[1] , 12 ); CLR_BIT( MUSART1 -> CR[1], 13 );

		#elif MUSART1_STOP_BITS == HALF_STOP_BIT

					SET_BIT( MUSART1 -> CR[1] , 12 ); CLR_BIT( MUSART1 -> CR[1] , 13 );

		#elif MUSART1_STOP_BITS == TWO_STOP_BIT

					CLR_BIT( MUSART1 -> CR[1] , 12 ); SET_BIT( MUSART1 -> CR[1] , 13 );

		#elif MUSART1_STOP_BITS == ONE_AND_HALF_STOP_BIT

					SET_BIT( MUSART1 -> CR[1] , 12 ); SET_BIT( MUSART1 -> CR[1] , 13 );


		#endif

		MUSART1 -> BRR = ( LOC_u32Mantissa << 4  ) | ( LOC_u32Fraction / 100 ) ;
		SET_BIT( MUSART1 -> CR[0] , 13 );

	#elif MUSART1_STATUS == USART1_DISABLE
		CLR_BIT( MUSART1 -> CR[0] , 0 );

	#endif
}

void MUSART1_voidSendChar(u8 Copy_u8Char)
{

	MUSART1 -> DR = Copy_u8Char ;

	while( GET_BIT( MUSART1 -> SR , 6 ) == 0 );

	CLR_BIT( MUSART1 -> SR , 6 );

}


void MUSART1_voidSendString(u8 *Copy_ptrString)
{

	u8 LOC_u8Iterator = 0 ;

	while ( Copy_ptrString[ LOC_u8Iterator ] != '\0' )
	{

		MUSART1_voidSendChar(Copy_ptrString[ LOC_u8Iterator ]);
		LOC_u8Iterator++ ;

	}

}


u8 MUSART1_u8Recieve(u8* Copy_u8Data)
{
	u8 Local_u8Result = 1;

	if( (GET_BIT(MUSART1 -> SR , 5)) == 1 )
	{
		*Copy_u8Data = MUSART1 -> DR ;
	}
	else
	{
		Local_u8Result = 0;
	}

	return Local_u8Result;
}



