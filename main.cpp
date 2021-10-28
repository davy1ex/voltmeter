#include <avr/io.h>


void adc_setup() {
	ADCSRA |= (1 << ADEN); // enable adc
	ADCSRA |= (1 << ADFR); // mode: free running select
		
	ADCSRA &= ~(1 << ADPS2); // XTAL frequency 125kHz
	ADCSRA |= (1 << ADPS1) | (1 << ADPS0);
	
	ADMUX |= (1 << REFS1) | (1 << REFS0); // internal voltage source	
	ADMUX &= ~(1 << ADLAR); // orientation read data
	ADMUX |=  (1 << MUX0);
	ADMUX &= ~((1 << MUX3) | (1 << MUX2) | (1 << MUX1)); // PC0 as adc port (ADC0)	
	
	ADCSRA |= (1 << ADSC); // adc start conversion
}


void ports_setup() {
	DDRB |= (1 << 0); // output for led
	PORTB &= ~(1 << 0); // 
	DDRC &= ~(1 << 1);
	
	
	adc_setup();
}



int main(void)
{
	ports_setup();
    /* Replace with your application code */
    while (1) 
    {
		if (ADCSRA & (1 << 4)) 
		{
			if (ADC >= 600) 
			{
				PORTB |= (1 << 0);
				PORTB &= ~(1 << 1);
				PORTB &= ~(1 << 2);
			}	
			
			else {
				PORTB &= ~(1 << 0);
			}
			ADCSRA |= (1<<4);
		}
	}
}

