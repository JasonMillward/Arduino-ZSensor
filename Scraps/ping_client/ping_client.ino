#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(8,11,9,4,5,6,7);

void setup(){
  Serial.begin(9600);
  lcd.begin(16, 2);
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();

  Mirf.setRADDR((byte *)"serv1");

  Mirf.payload = 32;

  Mirf.config();

  Serial.println("Beginning ... "); 
}
void loop(){
  byte data[32];
  if(Mirf.dataReady()){
    do{
      Serial.println("Got packet");
      Mirf.getData(data);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.write((char *)data);
    }
    while(!Mirf.rxFifoEmpty());
  }
}




