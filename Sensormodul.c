
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

void send_front()
{
    //skicka f�rst 1;
}

void send_fight_front()
{
    //skicka f�rst 2;
}

void send_right_back()
{
    //skicka f�rst 3;
}

void send_left_front()
{
    //skicka f�rst 4;
}

void send_left_back()
{
    //skicka f�rst 5;
}

void send_dist()
{
    //skicka f�rst 6;
}

void send_gyro()
{
    //skicka f�rst 7;
}

void send_RFID()
{
    //skicka f�rst 8;
}

void convert_front()
{
}

void convert_fight_front()
{
}

void convert_right_back()
{
}

void convert_left_front()
{
}

void convert_left_back()
{
}

void convert_dist()
{
}

void convert_gyro()
{
}





ISR(INT0_vect) //knapp
{
    ADCSRA = 0b11001011;
}

ISR(ADC_vect)
{
    PORTB = ADC >> 2;
}
