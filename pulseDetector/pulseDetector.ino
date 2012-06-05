

#include <SoftwareSerial.h>

int outPin =  0;      // the number of the out pin

void setup()
{
pinMode(7,INPUT);
pinMode(outPin,OUTPUT);
digitalWrite(outPin, LOW);
Serial.begin(9600);
//ACSR = B01011010; // comparator interrupt enabled and tripped on falling edge.
ACSR = B01011010; // comparator interrupt enabled and tripped on rising edge.

/*ACSR = 
 (0<<ACD) |   // Analog Comparator: Enabled
 (0<<ACBG) |   // Analog Comparator Bandgap Select: AIN0 is applied to the positive input
 (0<<ACO) |   // Analog Comparator Output: Off
 (1<<ACI) |   // Analog Comparator Interrupt Flag: Clear Pending Interrupt
 (1<<ACIE) |   // Analog Comparator Interrupt: Enabled
 (0<<ACIC) |   // Analog Comparator Input Capture: Disabled
 (1<<ACIS1) | (1<ACIS0);   // Analog Comparator Interrupt Mode: Comparator Interrupt on Rising Output Edge
*/

}

void loop()
{
}

ISR(ANALOG_COMP_vect)
{
  digitalWrite(outPin, HIGH);
  delay(1);
  digitalWrite(outPin, LOW);
  
  Serial.println("5");


}
