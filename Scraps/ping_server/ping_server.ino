#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>



void setup(){
  Serial.begin(9600);

  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();

  Mirf.setRADDR((byte *)"clie1");

  Mirf.payload = 32;

  Mirf.config();

  Serial.println("Beginning ... "); 
  
  Mirf.setTADDR((byte *)"serv1");

  Mirf.send((byte *)"Testing for mr madge");


  while(Mirf.isSending()){
  }
  Serial.println("Finished sending");
}


void loop(){



  //delay(10);
}


