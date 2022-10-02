/*
 * 	FileName  : main.c
 *  Created on: 30/1/2020
 *  Author    : ABDULRAHMAN OSAMA 
 */

#include"STD_TYPES.h"
#include"BIT_MATH.h"

#include"DIO_interface.h"
#include"LCD_int.h"
#include"ADC_int.h"
#include"util/delay.h"


void ISR (void)
{
	volatile u32 analog_value;
	volatile u32 digital_value;
	volatile u32 Temperature;
	volatile u32 Light_Intensity;

	digital_value = ADC_Get_Value();
	analog_value = (( digital_value * 5000UL)/1024);
	Temperature = (analog_value /10);
	
	 if(Temperature<=9)
	{
		LCD_CLEAR_DISPLAY();
		LCD_voidWriteString((u8 *)" sleep ");
	}
	else
	{
		LCD_CLEAR_DISPLAY();
		LCD_voidWriteString((u8 *)" wake up ");
	}

	ADC_StartConversion() ;
	_delay_ms(1000);

}

int main()
{
	
	LCD_8voidInit();
	LCD_CLEAR_DISPLAY();
	CALLback_ADC(ISR);
	ADC_SingleEnded_void_initialize(ADC0 , AVCC ,INTERRUPT,R_ADJ,SINGLE);
	while(1);
	
	return 0 ;
}


