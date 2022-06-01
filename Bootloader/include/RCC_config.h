/**********************************************/
/* Auther   : Mohamed Salem                   */
/* Date     : 01 MAY 2021                     */ 
/* Version  : V02                             */
/**********************************************/

#ifndef RCC_CONFIG_H
#define RCC_CONFIG_H


/*******************************************************************/
/*                                                                 */
/*                       ClockType Maybe :                         */
/*                       1-HSI                                     */
/*                       2-HSE                                     */
/*                       3-PLL                                     */
/*                          *PLL_Source                            */
/*                               3.1-PLL_HSI_DIVIDED_BY_2          */
/*                               3.2-PLL_HSE                       */
/*                               3.3-PLL_HSE_DIVIDED_BY_2          */
/*                       4-HSE_BYPASS                              */
/*                                                                 */
/*******************************************************************/


#define CLOCK_TYPE       HSI

#if CLOCK_TYPE == PLL
#define PLL_SOURCE       PLL_HSE_DIVIDED_BY_2
#endif

/********************************************************************************************/
/*                              ClockFactor For PLL  Maybe :                                */
/*                              0-NO_CLOCK_FACTOR                                           */
/*                              1-PLL_Clock_MULTIPLE_BY_2                                   */
/*                              2-PLL_Clock_MULTIPLE_BY_3                                   */
/*                              3-PLL_Clock_MULTIPLE_BY_4                                   */
/*                              4-PLL_Clock_MULTIPLE_BY_5                                   */
/*                              5-PLL_Clock_MULTIPLE_BY_6                                   */
/*                              6-PLL_Clock_MULTIPLE_BY_7                                   */
/*                              7-PLL_Clock_MULTIPLE_BY_8                                   */
/*                              8-PLL_Clock_MULTIPLE_BY_9                                   */
/*                              9-PLL_Clock_MULTIPLE_BY_10                                  */
/*                              10-PLL_Clock_MULTIPLE_BY_11                                 */
/*                              11-PLL_Clock_MULTIPLE_BY_12                                 */
/*                              12-PLL_Clock_MULTIPLE_BY_13                                 */
/*                              13-PLL_Clock_MULTIPLE_BY_14                                 */
/*                              14-PLL_Clock_MULTIPLE_BY_15                                 */
/*                              15-PLL_Clock_MULTIPLE_BY_16                                 */
/********************************************************************************************/

#if RCC_CLOCK_TYPE == PLL
#define CLOCK_FACTOR     PLL_CLOCK_MULTIPLE_BY_16
#endif
/**********************************************************************/
/*                                                                    */
/*                 Clock Security System May be                       */
/*                 1-Enable:                                          */
/* 				  	-To Set HSI By H.W When There are Failure In HSE  */
/* 				    -To Set HSI By H.W When Leaving Stop Or Standby   */
/* 				   2-Disable                                          */
/* 				   The Previouse Feature Does not Happen              */
/*                                                                    */
/**********************************************************************/

#define CLOCK_SECURITY_SYSTEM     DISABLE_CLOCK_SECURITY_SYSTEM


#endif
