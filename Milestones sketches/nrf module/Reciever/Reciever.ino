#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN 9
#define CSN_PIN 10

const uint64_t ch1 = 1; 
RF24 radio(CE_PIN,CSN_PIN);

byte rec[1];
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  radio.begin();
  radio.openReadingPipe(1,ch1);
  radio.startListening();
}

void loop() {
  // put your main code here, to run repeatedly:
  if ( radio.available() != 0)
  {
      radio.read( (rec), (sizeof(rec)) );
      Serial.println(rec[0]); 
  }else {       Serial.println("NOPE"); }

}
