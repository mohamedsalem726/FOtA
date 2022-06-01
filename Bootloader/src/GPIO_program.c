/*****************************************************/
/* Auther    : Mohamed Salem                         */
/* Date      : 01 MAY 2021                           */ 
/* Version   : V02                                   */
/*****************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "GPIO_private.h"


void MGPIO_voidSetPinDirection(u8 copy_u8Port , u8 copy_u8Pin , u8 copy_u8Mode)
{
	switch(copy_u8Port){
	case GPIOA :
	
	    if(copy_u8Pin <= 7){//Low
		
		    MGPIOA->CRL &= ~ ((0b1111) << (copy_u8Pin * 4));
		    MGPIOA->CRL |=   ((copy_u8Mode) << (copy_u8Pin * 4));
			
		}else if(copy_u8Pin <= 15){//High
			
			copy_u8Pin = copy_u8Pin - 8;
			MGPIOA->CRH &= ~ ((0b1111) << (copy_u8Pin * 4)); 
			MGPIOA->CRH |=   ((copy_u8Mode) << (copy_u8Pin * 4));
			
	    }
		
		break;
		
	case GPIOB :
	
	    if(copy_u8Pin <= 7){//Low
		
		    MGPIOB->CRL &= ~ ((0b1111) << (copy_u8Pin * 4));
		    MGPIOB->CRL |=   ((copy_u8Mode) << (copy_u8Pin * 4));
			
		}else if(copy_u8Pin <= 15){//High
			
			copy_u8Pin = copy_u8Pin - 8;
			MGPIOB->CRH &= ~ ((0b1111) << (copy_u8Pin * 4)); 
			MGPIOB->CRH |=   ((copy_u8Mode) << (copy_u8Pin * 4));
			
	    }
		
		break;
		
	case GPIOC :
	
		if(copy_u8Pin <= 7){//Low
		
			MGPIOC->CRL &= ~ ((0b1111) << (copy_u8Pin * 4));
			MGPIOC->CRL |=   ((copy_u8Mode) << (copy_u8Pin * 4));
			
		}else if(copy_u8Pin <= 15){//High
		
			copy_u8Pin = copy_u8Pin - 8;
			MGPIOC->CRH &= ~ ((0b1111) << (copy_u8Pin * 4)); 
		    MGPIOC->CRH |=   ((copy_u8Mode) << (copy_u8Pin * 4));
			
		}
		
		break;
		
	default : break;
	}
}

void MGPIO_voidSetPinValue(u8 copy_u8Port , u8 copy_u8Pin , u8 copy_u8Value)
{
	switch(copy_u8Port){
	case GPIOA :
	
	    if(copy_u8Value == GPIO_HIGH){
			
			SET_BIT(MGPIOA->ODR , copy_u8Pin);
			
		}else if(copy_u8Value == GPIO_LOW){
			
			CLR_BIT(MGPIOA->ODR , copy_u8Pin);
			
		}
		
		break;
		
	case GPIOB :
	    
		if(copy_u8Value == GPIO_HIGH){
	    	
	    	SET_BIT(MGPIOB->ODR , copy_u8Pin);
	    	
	    }else if(copy_u8Value == GPIO_LOW){
	    	
	    	CLR_BIT(MGPIOB->ODR , copy_u8Pin);
	    	
	    }
       
        break;
		
	case GPIOC :
	    
		if(copy_u8Value == GPIO_HIGH){
			
			SET_BIT(MGPIOC->ODR , copy_u8Pin);
			
		}else if(copy_u8Value == GPIO_LOW){
			
			CLR_BIT(MGPIOC->ODR , copy_u8Pin);
			
		}
		
		break;
		
	default : break;
	}
}
u8 MGPIO_u8GetPinValue(u8 copy_u8Port , u8 Copy_u8Pin)
{
	u8  LOC_u8Result = 0;
	
	switch(copy_u8Port){
	case GPIOA :
		
		LOC_u8Result = GET_BIT(MGPIOA->IDR , Copy_u8Pin);
		
		break;
		
	case GPIOB :
	    
		LOC_u8Result = GET_BIT(MGPIOB->IDR , Copy_u8Pin);
		
        break;	
		
	case GPIOC :
	
	    LOC_u8Result = GET_BIT(MGPIOC->IDR , Copy_u8Pin);
		
		break;
		
	default : break;
	}
	
	return LOC_u8Result ;
	
}

void MGPIO_voidSetPortDirection(u8 Copy_u8Port , u8 Copy_u8Position , u8 Copy_u8Mode)
{

	switch(Copy_u8Port){

	case GPIOA:

		if      (Copy_u8Position == GPIO_LOW ) {MGPIOA->CRL = (0x11111111 * Copy_u8Mode); }
		else if (Copy_u8Position == GPIO_HIGH) {MGPIOA->CRH = (0x11111111 * Copy_u8Mode); }

		break;
	case GPIOB:

		if      (Copy_u8Position == GPIO_LOW ) {MGPIOB->CRL = (0x11111111 * Copy_u8Mode); }
		else if (Copy_u8Position == GPIO_HIGH) {MGPIOB->CRH = (0x11111111 * Copy_u8Mode); }

		break;
	case GPIOC:

		if      (Copy_u8Position == GPIO_LOW  ) {MGPIOC->CRL = (0x11111111 * Copy_u8Mode); }
		else if (Copy_u8Position == GPIO_HIGH ) {MGPIOC->CRH = (0x11111111 * Copy_u8Mode); }

		break;

	}

}

void MGPIO_voidSetPortValue(u8 Copy_u8Port , u8 Copy_u8Position , u16 Copy_u8Value)
{

	switch(Copy_u8Port){

	case GPIOA:

		if      (Copy_u8Position == GPIO_LOW ){MGPIOA->ODR = (MGPIOA->ODR & 0xFF00) | ((u8)Copy_u8Value); }
		else if (Copy_u8Position == GPIO_HIGH){MGPIOA->ODR = (MGPIOA->ODR & 0x00FF) | (Copy_u8Value); }

		break;
	case GPIOB:

		if      ( Copy_u8Position == GPIO_LOW  ){ MGPIOB->ODR = (MGPIOB->ODR & 0xFF00 ) | ((u8)Copy_u8Value); }
		else if ( Copy_u8Position == GPIO_HIGH ){ MGPIOB->ODR = (MGPIOB->ODR & 0x00FF ) | (Copy_u8Value ); }

		break;
	case GPIOC:

		if      ( Copy_u8Position == GPIO_LOW  ){ MGPIOC->ODR = (MGPIOC->ODR & 0xFF00 ) | ((u8)Copy_u8Value); }
		else if ( Copy_u8Position == GPIO_HIGH ){ MGPIOC->ODR = (MGPIOC->ODR & 0x00FF ) | (Copy_u8Value); }

		break;

	}

}

u16 MGPIO_u16GetPortValue(u8 Copy_u8Port , u8 Copy_u8Position)
{

	u16 LOC_u16Result = 0;

	switch(Copy_u8Port){

	case GPIOA:

		LOC_u16Result = MGPIOA->IDR;
		if      (Copy_u8Position == GPIO_LOW){LOC_u16Result &= 0x00FF;}
		else if (Copy_u8Position == GPIO_HIGH){LOC_u16Result &= 0xFF00;}

		break;
	case GPIOB:

		LOC_u16Result = MGPIOB->IDR;
		if      (Copy_u8Position == GPIO_LOW ){LOC_u16Result &= 0x00FF; }
		else if (Copy_u8Position == GPIO_HIGH){LOC_u16Result &= 0xFF00; }

		break;
	case GPIOC:

		LOC_u16Result = MGPIOC->IDR;
		if      (Copy_u8Position == GPIO_LOW ){LOC_u16Result &= 0x00FF; }
		else if (Copy_u8Position == GPIO_HIGH){LOC_u16Result &= 0xFF00; }

		break;

	}

	return LOC_u16Result ;

}

