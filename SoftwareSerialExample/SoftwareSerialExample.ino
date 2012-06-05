#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3);

const int flexiForcePin = 0; // Analog pin0 connected to sensor
int motorPin = 9;    // LED connected to digital pin 9

int isSending;

void setup()  
{
  
  isSending=1;
  Serial.begin(57600);
  Serial.println("Force unit.");
  
}



void loop() // run over and over
{
  if (mySerial.available())
    Serial.write(mySerial.read());
  
  int value = analogRead(flexiForcePin);
  
  if( isSending == 1)
  {  
    Serial.print("Value is: ");
    Serial.println(value);
  }
  
  int d= 10;
  int motorForce = map(value, 0, 1023, 0, 255);
  
  analogWrite(motorPin,motorForce);         
    // wait for 30 milliseconds to see the dimming effect    
  delay(d);       
    
  //delay(1000);
  //if (Serial.available())
    //mySerial.write(Serial.read());
}
