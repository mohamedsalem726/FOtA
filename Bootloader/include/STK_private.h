/*******************************************************/
/* Auther    : Mohamed Salem                           */
/* Date      : 25 APRIL 2021                           */ 
/* Version   : V01                                     */
/*******************************************************/

#ifndef _STK_PRIVATE_H_
#define _STK_PRIVATE_H_

typedef struct{

	volatile u32 CTRL ;
	volatile u32 LOAD ;
	volatile u32 VAL  ;
	volatile u32 CALIB;

}SYSTICK;


#define MSTK ((volatile SYSTICK*)0xE000E010)

#define MSTK_SRC_AHB     0
#define MSTK_SRC_AHB_8   1

#define MSTK_SINGLE_INTERVAL  0
#define MSTK_PERIOD_INTERVAL  1

#define MSTK_COUNTFLAG_BIT 			16		/* Returns 1 if timer counted to 0 since last time this was read */
#define MSTK_CLKSOURCE_BIT			2		/* Clock source selection */
#define MSTK_TICKINT_BIT			1		/* STK exception request enable */
#define MSTK_COUNTER_EN_BIT			0		/* Counter enable */


#endif
