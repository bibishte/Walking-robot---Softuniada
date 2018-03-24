#include <SPI.h>
const int M11 = A3;
const int M12 = 4;
const int M22 = 6;
const int M21 = 7;
const int speed1 = 3;
//const int sl = 2;
    //const int s = 2;
//const int sr = A2;
char DM;
int r, f, l;


char buff [100];
volatile byte index;
volatile bool receivedone;  /* use reception complete flag */

//void turn()
//{
//  analogWrite(speed1, 60); // Set rotating motor speed
//      digitalWrite(M11, LOW);
//      digitalWrite(M12, HIGH);
//      digitalWrite(M22, LOW);
//      digitalWrite(M21, LOW);
//}

void setup() {
   pinMode(M11, OUTPUT);
   pinMode(M12, OUTPUT);
   pinMode(M22, OUTPUT);
   pinMode(M21, OUTPUT);
   pinMode(speed1, OUTPUT);

   
   //pinMode(sl, INPUT);
   pinMode(2, INPUT);
   //pinMode(sr, INPUT);
   


   SPCR |= bit(SPE);         /* Enable SPI */
   pinMode(MISO, OUTPUT);    /* Make MISO pin as OUTPUT */
   index = 0;
   receivedone = false;
   SPI.attachInterrupt();    /* Attach SPI interrupt */
   attachInterrupt(PD2, turn, FALLING);
   Serial.begin(115200);      // open the serial port at 115200 bps:
   


}

void loop() {
  if (receivedone)          /* Check and print received buffer if any */
  {
    buff[index] = 0;
    //Serial.println(buff);
    index = 0;
    receivedone = false;
    
  }
   
  /*if((digitalRead(s)==LOW) || (digitalRead(sl)==LOW) || (digitalRead(sr)==LOW))
   //if(digitalRead(sl)==LOW)
    {
      analogWrite(speed1, 60); // Set rotating motor speed
      digitalWrite(M11, LOW);
      digitalWrite(M12, HIGH);
      digitalWrite(M22, LOW);
      digitalWrite(M21, LOW);
      //delay(1000);
      return;
    }else
    {
      digitalWrite(M11, LOW);
      digitalWrite(M12, LOW);
      digitalWrite(M22, LOW);
      digitalWrite(M21, LOW);
      return;
    }*/
  
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
    if(c=='B' )
    {
      digitalWrite(M11, LOW);
      digitalWrite(M12, LOW);
      digitalWrite(M22, HIGH);
      digitalWrite(M21, LOW);
      receivedone = true;
    }
    if(c=='L'){
      analogWrite(speed1, 60); // Set rotating motor speed
      digitalWrite(M11, LOW);
      digitalWrite(M12, HIGH);
      digitalWrite(M22, LOW);
      digitalWrite(M21, LOW);
      receivedone = true;
    }
    if(c=='Q'){
      analogWrite(speed1, 160); // Set rotating motor speed
      digitalWrite(M11, LOW);
      digitalWrite(M12, HIGH);
      digitalWrite(M22, LOW);
      digitalWrite(M21, LOW);
      receivedone = true;
    }
    if(c=='R'){
      analogWrite(speed1, 60); // Set rotating motor speed
      digitalWrite(M11, HIGH);
      digitalWrite(M12, LOW);
      digitalWrite(M22, LOW);
      digitalWrite(M21, LOW);
      receivedone = true;
    }
    if(c=='W'){
      analogWrite(speed1, 160); // Set rotating motor speed
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

void turn()
{
  analogWrite(speed1, 60); // Set rotating motor speed
      digitalWrite(M11, LOW);
      digitalWrite(M12, HIGH);
      digitalWrite(M22, LOW);
      digitalWrite(M21, LOW);
      Serial.println("ennn");
}
