#include <LiquidCrystal.h>
#include <Wire.h>
#include "RTClib.h"
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RTC_DS1307 RTC;
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

int speakerPin = 8;
int hours=0;
int minutes=0;
int tones[] = {261, 277, 294, 311, 330, 349, 370, 392, 415, 440};
const uint64_t ch1 = 1;  
byte smth[]={'s'} ;

#define hr  A0
#define mi  A1
#define Show_Alarm A2
#define CE_PIN 9
#define CSN_PIN 10
RF24 radio(CE_PIN,CSN_PIN);

void setup () {
   Serial.begin(9600);
   Wire.begin();
   lcd.begin(16, 2);
   RTC.begin();
   if (! RTC.isrunning()) {
      Serial.println("RTC is NOT running!");
      RTC.adjust(DateTime(__DATE__, __TIME__));
  }
  radio.begin();
  radio.openWritingPipe(ch1);
  radio.write( smth, sizeof(smth) );
  pinMode(hr,OUTPUT);
  pinMode(mi,OUTPUT);  
}
  
void adjust_alarm(){
  if (analogRead(hr) > 700){ 
    if ( hours == 23)
      {hours=0;}
    else 
      {hours++;}
     }
  if (analogRead(mi) > 700){ 
    if (minutes== 59)
    {minutes=0;}
    else 
    {minutes++;}
    } 
}
void loop () {
    DateTime now = RTC.now(); 
    adjust_alarm();
    
    if ( ( ( String( now.hour() ) ) == String(hours) )&&(( String( now.minute() ) ) == String(minutes) ) )
    {
        for (int i = 0; i < 10; i++)
      {
          tone(speakerPin, tones[i]);
          delay(500);
      }
        noTone(speakerPin);    
        radio.write( smth, sizeof(smth) );
        Serial.println("Switch on the light"); 
        delay(50);
     }    
     
    lcd.setCursor(0, 0);
    lcd.print(String(now.year())+"/"+String(now.month())+"/"+String(now.day())+"  ");
    Serial.println(now.year());
    lcd.setCursor(0, 1);
    lcd.print(String(now.hour())+"/"+String(now.minute())+"/"+String(now.second())+"  ");
    
    lcd.setCursor(11, 0);
    lcd.print("Alarm");
    lcd.setCursor(11, 1);
    lcd.print(String(hours)+":"+String(minutes));
    
    delay(10);
}
