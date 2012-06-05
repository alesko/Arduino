/********************************************************
 * PID Basic Example
 * Reading analog input 0 to control analog PWM output 3
 ********************************************************/

#include <PID_v1.h>

//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &Setpoint,2,5,1, DIRECT);

void setup()
{
  //initialize the variables we're linked to
  Input = analogRead(0);
  Setpoint = analogRead(1);
  
  //turn the PID on
  myPID.SetMode(AUTOMATIC);
}

void loop()
{
  Input = analogRead(0);
  Setpoint = analogRead(1);
  myPID.Compute();
  analogWrite(9,Output);
  //analogWrite(13,125);
}


