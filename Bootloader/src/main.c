/*
 * main.c
 *
 *  Created on: Sep 3, 2021
 *      Author: Mohamed Salem
 */



#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ERROR_STATUS.h"

#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "STK_interface.h"
#include "USART_interface.h"
#include "FPEC_interface.h"


void Parser_voidParseRecord(u8* Copy_u8BufData);

volatile u8 u8RecBuffer[100]    ;
volatile u8 u8RecCounter     = 0;
volatile u8 u8TimeOutFlag    = 0;
volatile u16 u16TimerCounter = 0;
volatile u8 u8LWriteReq      = 1;
typedef void (*Function_t)(void);
Function_t  addr_to_call = 0;

void GoToApp(void)
{
#define SCB_VTOR  *((volatile u32*)0xE000ED08)

	SCB_VTOR = 0x08004800;

	addr_to_call = *(Function_t*)(0x08004804);
	addr_to_call();
}

void main(void)
{
	u8 Local_u8RecStatus;

	u8 Local_u8Arr='k';

	MRCC_voidInit();                                     /* Enable HSI */
	MRCC_voidEnablePeripheralClock(RCC_APB2,USART1_RCC); /* USART1     */
	MRCC_voidEnablePeripheralClock(RCC_APB2,GPIOA_RCC);  /* PortA      */
	MRCC_voidEnablePeripheralClock(RCC_AHB,FPEC_RCC);    /* FPEC       */

	MGPIO_voidSetPinDirection(GPIOA,PIN9,OUTPUT_SPEED_2MHZ_AFPP); /* TX AFPP */
	MGPIO_voidSetPinDirection(GPIOA,PIN10,INPUT_FLOATING);        /* RX Input Floating */

	MGPIO_voidSetPinDirection(GPIOA,PIN0,OUTPUT_SPEED_2MHZ_PP);

	MUSART1_voidInit(); /* Baud Rate 9600 - Enable RX and TX */

	MSTK_voidInit();

	MSTK_voidSetIntervalSingle(50000000, GoToApp);


	while(u8TimeOutFlag == 0)
	{
		Local_u8RecStatus = MUSART1_u8Recieve( &(u8RecBuffer[u8RecCounter]));


		if(Local_u8RecStatus == 1)
		{
			MSTK_voidStopInterval();

			if(u8RecBuffer[u8RecCounter] == '\n')
			{
				if(u8LWriteReq == 1)
				{
					MFPEC_voidEraseAppArea();
					u8LWriteReq = 0;
				}

				/* Parse */
				Parser_voidParseRecord(u8RecBuffer);

				MUSART1_voidSendChar(Local_u8Arr);
				u8RecCounter = 0;
			}
			else
			{
				u8RecCounter++;
			}

			MSTK_voidSetIntervalSingle(50000000, GoToApp);

		}
	else
		{
			/* Nothing to Receive */
		}
	}
}

