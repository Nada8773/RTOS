#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_register.h"
#include "DIO_interface.h"


void DIO_SetPinMode(u8 Port,u8 Pin ,u8 Mode)
{
	switch(Port)
	{
		case 'A':
			if(Pin<=7)
			{
				/* Clear 4 bits */
				PORTA_CRL &= ~(0b1111 << (Pin * 4));
				/* Set mode in 4 bits */
				PORTA_CRL |=  (Mode   << (Pin * 4));
			}
			else if (Pin<=15)
			{
				Pin = Pin-8;
				/* Clear 4 bits */
				PORTA_CRH &= ~(0b1111 << (Pin * 4));
				/* Set mode in 4 bits */
				PORTA_CRH |=  (Mode   <<(Pin * 4));
			}
			break;
			
		case 'B':
			if(Pin<=7)
			{
				/* Clear 4 bits */
				PORTB_CRL &= ~(0b1111 << (Pin * 4));
				/* Set mode in 4 bits */
				PORTB_CRL |=  (Mode   << (Pin * 4));
			}
			else if (Pin<=15)
			{
				Pin = Pin-8;
				/* Clear 4 bits */
				PORTB_CRH &= ~(0b1111 << (Pin * 4));
				/* Set mode in 4 bits */
				PORTB_CRH |=  (Mode   <<(Pin * 4));
			}
			break;
		case 'C':
		    if((Pin>=13) && (Pin <=15))
			{
				Pin = Pin-8;
				/* Clear 4 bits */
				PORTC_CRH &= ~(0b1111 << (Pin * 4));
				/* Set mode in 4 bits */
				PORTC_CRH |=  (Mode   << (Pin * 4));
			}
			break;
	}

}


   


void SetPinVal(u8 Port,u8 Pin ,u8 Val)
{
	switch(Port)
	{
		case 'A':
			if(Val == 1)
			{		
				SET_BIT(PORTA_ODR,Pin);
			}
			else
			{
				CLR_BIT(PORTA_ODR,Pin);
			}
			break;
		case 'B':
			if(Val == 1)
			{		
				SET_BIT(PORTB_ODR,Pin);
			}
			else
			{
				CLR_BIT(PORTB_ODR,Pin);
			}
			break;
		case 'C':
		    if(Val == 1)
			{		
				SET_BIT(PORTC_ODR,Pin);
			}
			else
			{
				CLR_BIT(PORTC_ODR,Pin);
			}
		
	}

}


u8 DIO_GetPinVal(u8 Port,u8 Pin)
{
	u8 Result;
	switch(Port)
	{
		case 'A':
			Result=GET_BIT(PORTA_IDR,Pin);
			break;
		case 'B':
			Result=GET_BIT(PORTB_IDR,Pin);
			break;
		case 'C':
			Result=GET_BIT(PORTC_IDR,Pin);
			break;
	}
	return Result;

}






















