#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>
#include <LiquidCrystal.h>

int latchPin = 4;
int clockPin = 3;
int dataPin  = 5;

int pPins[] = {
  1,2,4,8,4,2,1,2,4,8,4,2,1,0,0,0,0,0,15,15,15,15,15,0,0,0,0,0,15,15,15,15,15,0,0,0,0,0};

int counter = 0;


void setup(){
  Serial.begin(9600);
  pinMode(latchPin, OUTPUT);
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR((byte *)"serv1");
  Mirf.payload = 32;
  Mirf.config();
  Serial.println("Beginning ... "); 
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, 0); 
  delay(1000);
  int pSize = sizeof(pPins) / sizeof(int);
  for (int i = 0; i < pSize; i++) {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, pPins[i]);  
    digitalWrite(latchPin, HIGH);
    delay(50);
  }
}


void loop(){
  byte data[32];
  if(Mirf.dataReady()){
    do{
      Serial.println("Got packet");
      Mirf.getData(data);
      Serial.println((char *)data);

      char *numstr = (char *)data;
      int val = atoi(numstr); 
      if ( val >= 1) {
        counter += val;
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, MSBFIRST, counter);  
        digitalWrite(latchPin, HIGH);
      }
    }
    while(!Mirf.rxFifoEmpty());
  }
}



void shiftOut(int myDataPin, int myClockPin, byte myDataOut) {
  int i=0;
  int pinState;
  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin, OUTPUT);
  digitalWrite(myDataPin, 0);
  digitalWrite(myClockPin, 0);
  for (i=7; i>=0; i--)  {
    digitalWrite(myClockPin, 0);
    if ( myDataOut & (1<<i) ) {
      pinState= 1;
    }
    else {      
      pinState= 0;
    }
    digitalWrite(myDataPin, pinState);
    digitalWrite(myClockPin, 1);
    digitalWrite(myDataPin, 0);
  }
  digitalWrite(myClockPin, 0);
}













