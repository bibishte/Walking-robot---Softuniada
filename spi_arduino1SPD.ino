#include <SPI.h>

const int M11 = 2;
const int M12 = 4;
const int M22 = 5;
const int M21 = 1;
const int speed1 = 3;
const  int speed2 = 6;
const int sl = 0;
const int s = 8;
const int sr = 9;
char DM;
int r, f, l;


char buff [100];
volatile byte index;
volatile bool receivedone;  /* use reception complete flag */

void setup() {
   pinMode(M11, OUTPUT);
   pinMode(M12, OUTPUT);
   pinMode(M22, OUTPUT);
   pinMode(M21, OUTPUT);
   pinMode(speed1, OUTPUT);
   pinMode(speed2, OUTPUT);
   
   pinMode(sl, INPUT);
   pinMode(s, INPUT);
   pinMode(sr, INPUT);
   


   SPCR |= bit(SPE);         /* Enable SPI */
   pinMode(MISO, OUTPUT);    /* Make MISO pin as OUTPUT */
   index = 0;
   receivedone = false;
   SPI.attachInterrupt();    /* Attach SPI interrupt */
   Serial.begin(115200);      // open the serial port at 115200 bps:

   analogWrite(speed1, 120);
   analogWrite(speed2, 120);
   


}

void loop() {
  if (receivedone)          /* Check and print received buffer if any */
  {
    buff[index] = 0;
    //Serial.println(buff);
    index = 0;
    receivedone = false;
  }
  
}



ISR (SPI_STC_vect)
{
  uint8_t oldsrg = SREG;
  cli();
  char c = SPDR;
  if (index <sizeof buff)
  {
    buff [index++] = c;
    //if (c == '\n'){     /* Check for newline character as end of msg */
    // receivedone = true;
    //}
    if(c=='F')
    {
      
      digitalWrite(M11, LOW);
      digitalWrite(M12, LOW);
      digitalWrite(M22, LOW);
      digitalWrite(M21, HIGH);
      receivedone = true; 
    }
    if(c=='B')
    {
      
      digitalWrite(M11, LOW);
      digitalWrite(M12, LOW);
      digitalWrite(M22, HIGH);
      digitalWrite(M21, LOW);
      receivedone = true;
    }
    
    if(c=='L'){
      
      digitalWrite(M11, LOW);
      digitalWrite(M12, HIGH);
      digitalWrite(M22, LOW);
      digitalWrite(M21, LOW);
      receivedone = true;
    }
    
    if(c=='R'){
      
      digitalWrite(M11, HIGH);
      digitalWrite(M12, LOW);
      digitalWrite(M22, LOW);
      digitalWrite(M21, LOW);
      receivedone = true;
    }
    
    if(c=='S'){
      
      digitalWrite(M11, LOW);
      digitalWrite(M12, LOW);
      digitalWrite(M22, LOW);
      digitalWrite(M21, LOW);
      receivedone = true;
    }
    delay(100);
  }
  SREG = oldsrg;
}
