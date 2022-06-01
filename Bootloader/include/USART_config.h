/*******************************************************/
/* Auther    : Mohamed Salem                           */
/* Date      : 01 MAY 2021                             */ 
/* Version   : V01                                     */
/*******************************************************/

#ifndef _UART_CONFIG_H
#define _UART_CONFIG_H

/* System Clock */

#define F_CPU                    8000000UL

/* USART1_Configuration */

#define MUSART1_STATUS            MUSART1_ENABLE


#define MUSART1_WORD_LENGTH       _8BIT_WORD_LENGTH
#define MUSART1_PARITY            PARITY_DISABLE
#define MUSART1_INTERRUPT         INT_DISABLE

#define MUSART1_TRANSMITTER       TRANSMITTER_ENABLE
#define MUSART1_RECEIVER          RECEIVER_ENABLE

#define MUSART1_STOP_BITS         ONE_STOP_BIT




#endif

