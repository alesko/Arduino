
#include <SoftwareSerial.h>

//const int switchPin = 2;    // switch input
//const int motor1Pin = 3;    // H-bridge leg 1 (pin 2, 1A)
const int motor2Pin = 4;    // H-bridge leg 2 (pin 7, 2A)
const int enablePin = 9;    // H-bridge enable pin
  
const int flexiForcePin = 0; // Analog pin0 connected to sensor
const int motor1Pin = 3; // 
  
  
void setup() {
    // set the switch as an input:
    //pinMode(switchPin, INPUT); 

    // set all the other pins you're using as outputs:
    pinMode(motor1Pin, OUTPUT); 
    pinMode(motor2Pin, OUTPUT); 
    pinMode(enablePin, OUTPUT);
    //pinMode(ledPin, OUTPUT);

    // set enablePin high so that motor can turn on:
    digitalWrite(enablePin, HIGH);
    //pinMode(motorPin, OUTPUT); 
    
    Serial.begin(9600);
}
  
  
void loop() {

    int value = analogRead(flexiForcePin);
    analogWrite(3,value);
    
    // if the switch is high, motor will turn on one direction:
    //if (digitalRead(switchPin) == HIGH) {
      //digitalWrite(motor1Pin, LOW);   // set leg 1 of the H-bridge low
      //digitalWrite(motor2Pin, LOW);  // set leg 2 of the H-bridge high
    //} 
    // if the switch is low, motor will turn in the other direction:
    //else {
      digitalWrite(motor1Pin, HIGH);  // set leg 1 of the H-bridge high
      digitalWrite(motor2Pin, HIGH);   // set leg 2 of the H-bridge low
    //}
  }
