

byte rows[8] = {B100,B110,B111,B101,B011,B000,B010,B001};
byte cols[8] = {B100,B110,B111,B101,B010,B001,B000,B011};
char colsV[8] = {'a','b','c','d','e','f','g','h'};
int k;
byte sensorSelected;
// the setup function runs once when you press reset or power the board

byte LEDrows[8] = {B101,B111,B110,B100,B011,B000,B001,B010};
byte LEDcols[8] = {B010,B100,B000,B110,B001,B011,B111,B101};


int row;
int col;
byte squarey;

// Interrupt is called once a millisecond, 
SIGNAL(TIMER0_COMPA_vect) 
{
  k++;
  if(k==8)
  k=0;
  bitWrite(PORTB,5,bitRead(rows[k],2)); // S2
  bitWrite(PORTB,4,bitRead(rows[k],1)); // S1
  bitWrite(PORTB,3,bitRead(rows[k],0)); // S0
  for(int i;i<8;i++)
  {
    bitWrite(PORTB,0,bitRead(cols[i],2)); // S2
    bitWrite(PORTD,7,bitRead(cols[i],1)); // S1
    bitWrite(PORTD,6,bitRead(cols[i],0)); // S0
    delayMicroseconds(10);
    if(bitRead(PINB,1)==1)
    {
      if (sensorSelected!=(i + 8*k))
      {
      sensorSelected = i + 8*k;
      Serial.write(sensorSelected);
      squarey=sensorSelected;
      }
    }
  }
}




void setup() {
DDRC=B111;
DDRB=B11111101;
DDRD=B11110000;

bitWrite(PORTB,2,1); // LED COL1
bitWrite(PORTD,5,0); // LED ROW9

pinMode(1,OUTPUT);
digitalWrite(1,LOW);

Serial.begin(38400);

  // Timer0 is already used for millis() - we'll just interrupt somewhere
  // in the middle and call the "Compare A" function below
  OCR0A = 0xAF;
  TIMSK0 |= _BV(OCIE0A);
}

// the loop function runs over and over again forever
void loop()
{
    
    row = squarey/8+1;
    col = squarey%8+1;

      if(row != 8)
      {
        bitWrite(PORTD,5,0); // LED ROW9
        bitWrite(PORTD,4,bitRead(LEDrows[row-1],2)); // S2
        bitWrite(PORTB,6,bitRead(LEDrows[row-1],1)); // S1
        bitWrite(PORTB,7,bitRead(LEDrows[row-1],0)); // S0
      }
      else
      {
        bitWrite(PORTD,5,1); // LED ROW9
      }
      if(col != 1)
      {
        bitWrite(PORTB,2,1); // LED COL1
        PORTC = LEDcols[col-2];
      }
      else
      {
        bitWrite(PORTB,2,0); // LED COL1
        PORTC = LEDcols[col-1];
      }
      delay(1);

      
      if(row != 8)
      {
        bitWrite(PORTD,5,0); // LED ROW9
        bitWrite(PORTD,4,bitRead(LEDrows[row-1],2)); // S2
        bitWrite(PORTB,6,bitRead(LEDrows[row-1],1)); // S1
        bitWrite(PORTB,7,bitRead(LEDrows[row-1],0)); // S0
      }
      else
      {
        bitWrite(PORTD,5,1); // LED ROW9
      }
      if(col != 1)
      {
        bitWrite(PORTB,2,1); // LED COL1
        PORTC = LEDcols[col-1];
      }
      else
      {
        bitWrite(PORTB,2,0); // LED COL1
        //PORTC = LEDcols[col];
      }
      delay(1);

      
      if(row != 8)
      {
        bitWrite(PORTD,5,0); // LED ROW9
        bitWrite(PORTD,4,bitRead(LEDrows[row],2)); // S2
        bitWrite(PORTB,6,bitRead(LEDrows[row],1)); // S1
        bitWrite(PORTB,7,bitRead(LEDrows[row],0)); // S0
      }
      else
      {
        bitWrite(PORTD,5,1); // LED ROW9
        bitWrite(PORTD,4,bitRead(LEDrows[row-1],2)); // S2
        bitWrite(PORTB,6,bitRead(LEDrows[row-1],1)); // S1
        bitWrite(PORTB,7,bitRead(LEDrows[row-1],0)); // S0
      }
      if(col != 1)
      {
        bitWrite(PORTB,2,1); // LED COL1
        PORTC = LEDcols[col-2];
      }
      else
      {
        if(row==8)
          bitWrite(PORTB,2,1); // LED COL1
        else
          bitWrite(PORTB,2,0); // LED COL1
        PORTC = LEDcols[col-1];
      }
      delay(1);

      
      if(row != 8)
      {
        bitWrite(PORTD,5,0); // LED ROW9
        bitWrite(PORTD,4,bitRead(LEDrows[row],2)); // S2
        bitWrite(PORTB,6,bitRead(LEDrows[row],1)); // S1
        bitWrite(PORTB,7,bitRead(LEDrows[row],0)); // S0
      }
      else
      {
        bitWrite(PORTD,5,1); // LED ROW9
        bitWrite(PORTD,4,bitRead(LEDrows[row-1],2)); // S2
        bitWrite(PORTB,6,bitRead(LEDrows[row-1],1)); // S1
        bitWrite(PORTB,7,bitRead(LEDrows[row-1],0)); // S0
      }
      if(col != 1)
      {
        bitWrite(PORTB,2,1); // LED COL1
        PORTC = LEDcols[col-1];
      }
      else
      {
        if(row==8)
          bitWrite(PORTB,2,1); // LED COL1
        else
          bitWrite(PORTB,2,0); // LED COL1
        //PORTC = LEDcols[col];
      }
      delay(1);

while (Serial.available()) {
    byte inByte = Serial.read();
    if(inByte-100 == sensorSelected)
      Serial.write(0x01);
    else if (inByte >= 100)
      Serial.write(0x00);
    if(inByte >= 0 && inByte <= 63)
      squarey=inByte;
  }
}
