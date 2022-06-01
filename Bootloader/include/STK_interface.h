/*******************************************************/
/* Auther    : Mohamed Salem                           */
/* Date      : 25 APRIL 2021                           */ 
/* Version   : V01                                     */
/*******************************************************/

#ifndef _STK_INTERFACE_H
#define _STK_INTERFACE_H



#define MSTK_TICKINT_DIS			0		/* Counting down to zero does not assert the STK exception request 	*/
#define MSTK_TICKINT_EN				1		/* Counting down to zero to asserts the STK exception request 		*/

#define MSTK_COUNTER_DIS			0		/* Counter disabled */
#define MSTK_COUNTER_EN				1	    /* Counter enabled  */



void MSTK_voidInit               ( void                                                           );

void MSTK_voidSetBusyWait        ( u32 Copy_u32Ticks                         );

void MSTK_voidSetIntervalSingle  (u32 Copy_u32Ticks  , void (*Copy_ptr)(void));

void MSTK_voidSetIntervalPeriodic(u32 Copy_u32Ticks  , void (*Copy_ptr)(void));

void MSTK_voidStopInterval       ( void                                                           );
 
u32 MSTK_u32GetElapsedTime       ( void                                            );
 
u32 MSTK_u32GetReminingTime      ( void                                            );


#endif
