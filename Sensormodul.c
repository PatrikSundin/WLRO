
//B�rjar med att klistra in fr�n AVR-labben
int main(void)
{
    MCUCR = 0b00000011;
    GICR = 0b01000000;
    ADMUX = 0;
    DDRB = 0xFF;
    ADCSRA = 0b10001011;

    sei();
    while(1) {}

    //Pseudokod typ fast inte
    /*Start
    Setup
    while (styr vill ha data)
    {
    if RFID
	minns rfid
    adomvandla sensorv�rden
    omvandla till r�tt enhet
    skicka till styr
    }*/

}

ISR(INT0_vect) //knapp
{
    ADCSRA = 0b11001011;
}

ISR(ADC_vect)
{
    PORTB = ADC >> 2;
}
