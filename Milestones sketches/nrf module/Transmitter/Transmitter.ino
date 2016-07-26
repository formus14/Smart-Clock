#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN 9
#define CSN_PIN 10

const uint64_t ch1 = 1;  
byte smth[]={'s'} ;

RF24 radio(CE_PIN,CSN_PIN);

void setup() {
  // put your setup code here, to run once:
radio.begin();
radio.openWritingPipe(ch1);
radio.write( smth, sizeof(smth) );
}

void loop() {
  // put your main code here, to run repeatedly:
radio.write( smth, sizeof(smth) );
      Serial.println(smth[0]); 

}
