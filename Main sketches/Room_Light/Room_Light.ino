#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h> 
 
int servoPin = 7;
Servo servo;  
int angle = 0;   // servo position in degrees 
 
#define CE_PIN 9
#define CSN_PIN 10

const uint64_t ch1 = 1; 
RF24 radio(CE_PIN,CSN_PIN);

byte rec[1];
void setup() {
  Serial.begin(115200); 
  radio.begin();
  radio.openReadingPipe(1,ch1);
  radio.startListening();
  servo.attach(servoPin); 

}

void loop() {
  if ( radio.available() != 0)
  {
      radio.read( (rec), (sizeof(rec)) );
      if(rec[0]=='s'){
          for(angle = 0; angle < 100; angle++)  
        {                                  
          servo.write(angle);               
          delay(15);                   
        } 
        
      }
  }

}
