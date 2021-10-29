#include <avr/io.h>
#include <util/delay.h>

#define  NUM PORTD// this bits for light led
#define SEG PORTB  // this bits for select segment with leds

unsigned int dig_numbers[10] = {
	0x3f,	// 0
	0x6,	// 1
	0x5b,	// 2
	0x4f,	// 3
	0x66,	// 4
	0x6d,	// 5
	0x7d,	// 6
	0x7,	// 7
	0x7f,	// 8
	0x6f	// 9
};


void seg_show(int numb_for_encode) {
	if (numb_for_encode / 10 > 0) {
		NUM = dig_numbers[numb_for_encode %100 / 10];
		SEG = 0b00000010;
		_delay_ms(300);
	}
	NUM = dig_numbers[numb_for_encode % 10];
	SEG = 0b00000001;
	_delay_ms(300);		
}


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
	DDRD = 0b11111111; // all on output for gain leds
	DDRB = 0b00001111;
	
	// test light
	NUM = dig_numbers[0];
	SEG = 0b00000001;
	
	//DDRB |= (1 << 0); // output for led
	//PORTB &= ~(1 << 0); //
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
				seg_show(15);
			}
			
			else {
				PORTB &= ~(1 << 0);
			}
			ADCSRA |= (1<<4);
		}
	}
}

