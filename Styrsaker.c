void fjarrstyrt()
{
	DDRB=0x00;
	
	DDRC=0b00000001;
	DDRD=0b11100000;
	TCCR1A=0b10010001; //setup, phase correct PWM
	TCCR1B=0b00000010; //sätter hastigheten på klockan
	TCCR2A=0b10010001;
	TCCR2B=0b00000010;
	
    while(1)
    {	
	int knapptryck=PINB;

      switch(knapptryck)
      {
	      case (0x01)://Kör framåt, W
	      PORTC = 0x01; //sätter båda DIR till 1
	      PORTD = 0x40;
	      OCR2A = 250; //PWM vänster
	      OCR1A = 250; //PWM höger
		  
	      break;
	      case (0x04): //Backa, S
	      PORTC = 0x0; //sätter båda DIR till 0
	      PORTD = 0x0;
	      OCR2A = 250;
	      OCR1A = 250;
	      break;
	      case (0x06): //Rotera vänster, Q
	      PORTC = 0x00; //DIR vänster till 0
	      PORTD = 0x40; //DIR höger till 1
	      OCR2A = 250;
	      OCR1A = 250;
	      break;
	      case (0x05): //Rotera höger, E
	      PORTC = 0x01;
	      PORTD = 0x00;
	      OCR2A = 250;
	      OCR1A = 250;
	      break;
	      case (0x03): //Sväng vänster, A
	      PORTC = 0x01;
	      PORTD = 0x40;
	      OCR2A = 100;
	      OCR1A = 250;
	      break;
	      case (0x02): //Sväng höger, D
	      PORTC = 0x01;
	      PORTD = 0x40;
	      OCR2A = 250;
	      OCR1A = 100;
	      break;
		  default:
		  OCR2A = 0;
		  OCR1A = 0;
      }

    }
}


void rotate90right()
{
	DDRC=0b00000001; //Sätter utgångar
	DDRD=0b11100000;
	TCCR1A=0b10010001; //setup, phase correct PWM
	TCCR1B=0b00000010; //sätter hastigheten på klockan
	TCCR2A=0b10010001;
	TCCR2B=0b00000010;
	
	PORTC = 0x01; // Vänster framåt
	PORTB = 0x00; // Höger bakåt
	
	int degrees=0;
		
	while(degrees<90)
	{
		OCR2A = 150;
		OCR1A = 150;
		degrees+=gyrodata;
	}
	OCR2A = 0;
	OCR1A = 0;
	
	if(mydirection=1)  // mydirection: 1=x+, 2=y+. 3=x-, 4=y-
	{
		mydirection=4,
	}
	else
	{
		mydirection-=1;
	}
}


void rotate90left()
 {
	 DDRC=0b00000001; //Sätter utgångar
	 DDRD=0b11100000;
	 TCCR1A=0b10010001; //setup, phase correct PWM
	 TCCR1B=0b00000010; //sätter hastigheten på klockan
	 TCCR2A=0b10010001;
	 TCCR2B=0b00000010;
	 
	 PORTC = 0x00; // vänster bakåt
	 PORTB = 0x40; // Höger framåt
	 
	 int degrees=0;
	 
	 while(degrees<90)
	 {
		 OCR2A = 150;
		 OCR1A = 150;
		 degrees+=gyrodata;
	 }
	 OCR2A = 0;
	 OCR1A = 0;
	 
	 if(mydirection=4)
	 {
		 mydirection=1,
	 }
	 else
	 {
		 mydirection+=1;
	 }
 }


void regleringright()
{
	DDRC=0b00000001;
	DDRD=0b11100000;
	TCCR1A=0b10010001; //setup, phase correct PWM
	TCCR1B=0b00000010; //sätter hastigheten på klockan
	TCCR2A=0b10010001;
	TCCR2B=0b00000010;
	PORTC = 0x01; //sätter båda DIR till 1
	PORTD = 0x40;
	int K = 5; //Bestämmer hur snabbt roboten ska reagera på skillnader mellan önskat avstånd till väggen(10cm) och uppmätt avstånd

	while(regleramotvagg==1)
	{
		int sensordiffr = sensor1r-sensor2r;
		int sensormeanr = (sensor1r+sensor2r)/2;
		
		if (sensorfront>10)
		{
			if(sensordiff<20) //Byt plats på höger och vänster för att reglera mot vänster vägg
			{
				OCR1A = 180+K*(9-sensormeanr); //PWM höger
				OCR2A = 180-K*(9-sensormeanr); //PWM vänster
			}
			else //sensordiff>20 innebär att ett hörn kommer
			{
				while(traveled<20)
				{
					OCR2A = 180;
					OCR1A = 180;	
				}
				rotate90right();	
				while(traveled<20)
				{
					OCR2A = 180;
					OCR1A = 180;
				}		
			}
		}
		else
		rotate90left();
	}
}


void regleringleft()
{
	DDRC=0b00000001;
	DDRD=0b11100000;
	TCCR1A=0b10010001; //setup, phase correct PWM
	TCCR1B=0b00000010; //sätter hastigheten på klockan
	TCCR2A=0b10010001;
	TCCR2B=0b00000010;
	PORTC = 0x01; //sätter båda DIR till 1
	PORTD = 0x40;
	int K = 5; //Bestämmer hur snabbt roboten ska reagera på skillnader mellan önskat avstånd till väggen(10cm) och uppmätt avstånd

	while(regleramotvagg==1)
	{
		int sensordiffr = sensor1l-sensor2l;
		int sensormeanr = (sensor1l+sensor2l)/2;
		
		if (sensorfront>10)
		{
			if(sensordiff<20) 
			{
				OCR1A = 180-K*(9-sensormeanr); //PWM höger
				OCR2A = 180+K*(9-sensormeanr); //PWM vänster
			}
			else //sensordiff>20 innebär att ett hörn kommer
			{
				while(traveled<20)
				{
					OCR2A = 180;
					OCR1A = 180;	
				}
				rotate90left();	
				while(traveled<20)
				{
					OCR2A = 180;
					OCR1A = 180;
				}		
			}
		}
		else
		rotate90right();
	}
}


void returntostart()
{
	int mydirection; //Robotens riktning
	int myposX; //Rpbotens position i X-led
	int starposX; //Starpositionens värde i X-led
	
	if(mydirection=4) //4=negativ y-led. x+,y+,x-,y- = 1,2,3,4
	{
		while(sensorfram>10) 
		{
			//Kör rakt fram
			PORTC = 0x01;
			PORTD = 0x40;
			OCR2A = 180;
			OCR1A = 180;	
		}
		if(myposX<startposX) //Om ingången är till höger om roboten
		{
			while(myposX<startposX)
			{
				regleringright();
			}
		}
		else 
		{
			while(myposX>startposX) //Om ingången är till vänster om roboten
			{
				regleringleft();
			}
		}
	}
	else
	{
		while(mydirection!=4)
		{
		rotate90left();  //Rotera 90 grader om vi står i fel riktning
		}
	}
}


int map1[17][31]={{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,}, //1 är avsökt
	 	  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};
						
					

void setmypos(mypos) //sätter nuvarande position till en tvåa
{
	map1[myposY][myposX]=2;
}

void setwall(int x,int y)
{
	map1[y][x]=1;
}

int findfirstzero()
{
	int i; //X
	int j; //Y
	int firstzero[2]={0,0};
	
	for(int j=0;j<=17;j++)
	{
		for(int i=0;i<=31;i++)
		{
			if(map1[j][i]==0)
			{
				firstzero[0]=i;
				firstzero[1]=j;
			}
		}
	}
return firstzero;					
}

void prutt()
{
	int leftturn;
	if(myposX>0)
	{
		leftturn=0;
	}	
	else
	{
		leftturn=1;
	}
	
	while(1)
	{
		if(sensorfront>50)
		{
			PORTC = 0x01;
			PORTB = 0x04;
			OCR2A = speed;
			OCR0A = speed;
		}
		else if(leftturn==1)
		{
			rotate90left2();
			int distance=0;
			while(distance<40)
			{
				PORTC = 0x01;
				PORTB = 0x04;
				OCR2A = speed;
				OCR0A = speed;
			}
			rotate90left2();
		}
		else
		{
			rotate90right2();
			int distance=0;
			while(distance<40)
			{
				PORTC = 0x01;
				PORTB = 0x04;
				OCR2A = speed;
				OCR0A = speed;
			}
			rotate90right2();
		}
	}		
}

void rotate90right2()
{
	int degrees=0;
	
	if(degrees<89)
	{
		PORTC = 0x00;
		PORTB = 0x40;
		OCR2A = 150;
		OCR1A = 150;
		degrees+=gyro
	}
	else if (degrees>91)
	{
		PORTC = 0x01;
		PORTB = 0x00;
		OCR2A = 100;
		OCR1A = 100;
		degrees-=gyro;
	}
	else
	{
		OCR2A = speed;
		OCR1A = speed;
	}
}

void rotate90left2()
{
	int degrees=0;
	
	if(degrees<89)
	{
		PORTC = 0x01;
		PORTB = 0x00;
		OCR2A = 150;
		OCR1A = 150;
		degrees+=gyro
	}
	else if (degrees>91)
	{
		PORTC = 0x00;
		PORTB = 0x40;
		OCR2A = 100;
		OCR1A = 100;
		degrees-=gyro
	}
	else
	{
		OCR2A = 0;
		OCR1A = 0;
	}
}

void driveto(int x, int y)
{
	if(myposX!=x)
	{
		if(x>myposX)
		{
			switch(mydirection)  //mydirection: 1=x+, 2=y+. 3=x-, 4=y-
			{
				case(1):
				PORTC = 0x01;
				PORTB = 0x04;
				OCR2A = speed;
				OCR0A = speed;
				case(2):
				rotate90right2();
				case(3):
				rotate90right2();
				rotate90right2();
				case(4):
				rotate90left2();
			}
		}
		else
		{
			switch(mydirection)
			{
				case(3):
				PORTC = 0x01;
				PORTB = 0x04;
				OCR2A = speed;
				OCR0A = speed;
				case(4):
				rotate90left2();
				case(1):
				rotate90right2();
				rotate90right2();
				case(2):
				rotate90right2();
			}
		}
		
	}
	else if (myposY!=y)
	{
		if(y>myposY)
		{
			switch(mydirection)
			{
				case(2):
				PORTC = 0x01;
				PORTB = 0x04;
				OCR2A = speed;
				OCR0A = speed;
				case(3):
				rotate90right2();
				case(4):
				rotate90right2();
				rotate90right2();
				case(1):
				rotate90left2();
			}
		}
		else
		{
			switch(mydirection)
			{
				case(4):
				PORTC = 0x01;
				PORTB = 0x04;
				OCR2A = speed;
				OCR0A = speed;
				case(1):
				rotate90left2();
				case(2):
				rotate90right2();
				rotate90right2();
				case(3):
				rotate90right2();
			}
		}
	}
}
