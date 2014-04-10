#include <avr/io.h>
#include <avr/delay.h>

int main()
{
	DDRA=0b11111111; //Sätter utgångar
	DDRC=0b11000001;
	 
	 PORTA=0b00110000; 
	 PORTC=0b00000000;
	 _delay_ms(20);
	 PORTA=0b00110000; 
	 PORTC=0b10000000;
	 PORTC=0b00000000;
	 _delay_ms(5);
	 PORTA=0b00110000; 
	 PORTC=0b10000000;
	 PORTC=0b00000000;
	 _delay_us(110);
	 
	//Startar initiering
	PORTA=0b00111100; // 2-line mode ; 5x8 Dots
	PORTC=0b10000000;
	PORTC=0b00000000;
	_delay_us(400);
	PORTA=0b00001111; // Display on ; Cursor on ; Blink on
	PORTC=0b10000000;
	PORTC=0b00000000;
	_delay_us(400);
	PORTA=0b00000001; // Clear display
	PORTC=0b10000000;
	PORTC=0b00000000;
	_delay_ms(20);
	PORTA=0b00000111; //Increment mode ; Entire shift on
	PORTC=0b10000000;
	_delay_ms(20);
	//Initiering klar
	_delay_ms(4000);
	
	
	
	DDRB=0x00;
	
	//DDRC=0b11000001;
	DDRD=0b11100000;
	TCCR1A=0b10010001; //setup, phase correct PWM
	TCCR1B=0b00000010; //sätter hastigheten på klockan
	TCCR2A=0b10010001;
	TCCR2B=0b00000010;
	
	int Auto=1; 
	
	while(1)
	{
		int knapptryck=PINB;
		int fjarrstyrt = (PIND & 0x01);
		
		if(fjarrstyrt==1)
		{
			if(Auto==1)
			{
				PORTA=0b00000001; // Clear display
				PORTC=0b10000000;
				PORTC=0b00000000;
				_delay_ms(20);
				Auto=0;
			}
			
			switch(knapptryck)
			{
				case (0x01)://Kör framåt, W
				PORTC = 0x01; //sätter båda DIR till 1
				PORTD = 0x40;
				OCR2A = 250; //PWM vänster
				OCR1A = 250; //PWM höger
				writechar(0b01010111); //W
				break;
				case (0x04): //Backa, S
				PORTC = 0x0; //sätter båda DIR till 0
				PORTD = 0x0;
				OCR2A = 250;
				OCR1A = 250;
				writechar(0b01010011); //S
				break;
				case (0x06): //Rotera vänster, Q
				PORTC = 0x00; //DIR vänster till 0
				PORTD = 0x40; //DIR höger till 1
				OCR2A = 250;
				OCR1A = 250;
				writechar(0b01010001); //Q
				break;
				case (0x05): //Rotera höger, E
				PORTC = 0x01;
				PORTD = 0x00;
				OCR2A = 250;
				OCR1A = 250;
				writechar(0b01000101); //E
				break;
				case (0x03): //Sväng vänster, A
				PORTC = 0x01;
				PORTD = 0x40;
				OCR2A = 100;
				OCR1A = 250;
				writechar(0b01000001); //A
				break;
				case (0x02): //Sväng höger, D
				PORTC = 0x01;
				PORTD = 0x40;
				OCR2A = 250;
				OCR1A = 100;
				writechar(0b01000100); //D
				break;
				default:
				OCR2A = 0;
				OCR1A = 0;
			}
		}
		else
		{
			OCR2A = 0;
			OCR1A = 0;
			if (Auto==0)
			{
				writechar(0b01000001); //A
				writechar(0b01110101); //u
				writechar(0b01110100); //t
				writechar(0b01101111); //o
				Auto=1;
			}
		}
	}
	return 0;
}



void writechar(unsigned char data)
{
	PORTA=data;
	(PORTC |= 0b11000000);
	(PORTC &= 0b01000001);
	_delay_ms(30);
}
