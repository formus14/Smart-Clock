// Connect your buzz signal pin to digital pin 8
int buzzer=8;
int flag=0; 
void setup()
{
  pinMode(buzzer,OUTPUT);
}

void loop()
{
  int i;
  if ( flag== 0){
    for(i=0;i<255;i++) // output sound of one frequency
    {
      digitalWrite(buzzer,HIGH);// Buzz sound
      delay(1);//delay 1ms
      digitalWrite(buzzer,LOW);// silent
      delay(1);//delay 1ms
    }
    flag=1;
    digitalWrite(buzzer,LOW);// silent
  }
}
