// Controlling a servo position using a potentiometer (variable resistor) 
// by Michal Rinott <http://people.interaction-ivrea.it/m.rinott> 

#include <Servo.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3);
Servo myservo;  // create servo object to control a servo 
 
unsigned long time;
unsigned long time_old;
unsigned long dt;

int flexpin1 = 1;  // analog pin used to connect the potentiometer
int flexpin0 = 0;  // analog pin used to connect the potentiometer
int pospin = 2;  // analog pin used to connect the potentiometer
int val1;    // variable to read the value from the analog pin 
int val0;    // variable to read the value from the analog pin 

int isSending;
int counter;
const float k = 0;//-25.28;
const float c = 40.26;

int setPoint; // = 40;
float servoforce;
int pos;
int pos_in_min;
int pos_in_max;
int pos_in;
int pos_out_min;
int pos_out_max;
int pos_set;

void setup() 
{ 
  time = millis();
  pos_set = 30;
  pos_in = 0;
  pos_in_min = 1000;
  pos_in_max = -1000;
  //pos = analogRead(pospin);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  counter = 0;
  isSending=1;
  Serial.begin(9600);
  Serial.println("Start, go to min pos");
  myservo.write(pos_set);
  delay(1500);
  pos_in = analogRead(pospin);
  while( pos_in < pos_in_min )
  {
     pos_in_min = pos_in;
     pos_set = pos_set - 1; //
     myservo.write(pos_set);
     delay(200);
     pos_in = analogRead(pospin);
     //Serial.print("Pos min is: ");
     //Serial.println(pos_min);
  }
  pos_out_min = pos_set;
  Serial.print("Pos out min is: ");
  Serial.println(pos_out_min);
  Serial.println("Go to max pos");
  
  pos_set = 160;
  myservo.write(pos_set);
  delay(1500);
  
  pos_in = analogRead(pospin);
  while( pos_in > pos_in_max )
  {
     pos_in_max = pos_in;
     pos_set = pos_set + 1; //
     myservo.write(pos_set);
     delay(200);
     pos_in = analogRead(pospin);
     //Serial.print("Pos max is: ");
     //Serial.println(pos_max);
  }
  pos_out_max = pos_set;
  Serial.print("Pos out max is: ");
  Serial.println(pos_out_max);
  
  int val=(pos_in_max-pos_in_min)/2+pos_in_min;
  pos_set = map(val,pos_in_min,pos_in_max,pos_out_min,pos_out_max);
  Serial.print("Pos_set is: ");
  Serial.println(pos_set);
  myservo.write(pos_set);
  delay(1500);
  Serial.println("Ready");
  
  /*
  val1 = analogRead(flexpin1);            // reads the value of the potentiometer (value between 0 and 1023) 
  //if (val1 < setPoint )
  while( val1 < 25 )
  {
    servoforce = servoforce + 0.1;
    myservo.write((int)servoforce);                  // sets the servo position according to the scaled value 
    Serial.print("Pos is: ");
       Serial.println(servoforce);
    delay(15);
    val1 = analogRead(flexpin1);
  }
  setPoint = (int)servoforce + 1;
  servoforce = 0;
  myservo.write((int)servoforce);                  // sets the servo position according to the scaled value 
  delay(15);*/
} 
 
void loop() 
{ 
  
  time_old = time;
  int pos_old = pos_in;
  pos_in = analogRead(pospin);
  
  time = millis();
  dt = time - time_old;
  
  
  int tau_des = analogRead(flexpin0);
  int tau = analogRead(flexpin1);
  int e_tau = tau_des-tau;
  
  float q_dot = (float)(pos_old - pos_in)/(float)dt;
  float k_d = 1;
  float k_p = 0.01;
  float e_tau_f = (float)e_tau;
  float u = 3.3*k_p*e_tau_f-k_d*q_dot;
  
  pos_set = pos_set + (int)u;
  myservo.write(pos_set);
  delay(15);

  /*
  Serial.print("tau_des is: ");
  Serial.print(tau_des);
  Serial.print("  tau is: ");
  Serial.print(tau);
  Serial.print("  e_tau is: ");
  Serial.print(e_tau);
  
  Serial.print("  pos_old is: ");
  Serial.print(pos_old);
  Serial.print("  pos_in is: ");
  Serial.print(pos_in);
  Serial.print("  q_dot is: ");
  Serial.print(q_dot);*/
  
  /*
  Serial.print("pos_in is: ");
  Serial.print(pos_in);
  Serial.print("  u is: ");
  Serial.println(u);*/

  
  
  /*
  myservo.write(50);
  delay(1500);
  myservo.write(150);
  delay(1500);
  */
  /*
  int value;
  if (mySerial.available())
    Serial.write(mySerial.read());
    
  val0 = analogRead(flexpin0);            // reads the value of the potentiometer (value between 0 and 1023)
  val1 = analogRead(flexpin1);            // reads the value of the potentiometer (value between 0 and 1023)
  pos = analogRead(pospin);            // reads the value of the potentiometer (value between 0 and 1023) 

  if (val1 < setPoint )
    servoforce = servoforce + 0.1;
  if (servoforce > 70 )
    servoforce = 0;
  //value = map(val1, 0, 1023, 0, 179);     // scale it to use it with the servo (value between 0 and 180) 
  myservo.write((int)servoforce);                  // sets the servo position according to the scaled value 
  delay(15);                           // waits for the servo to get there 
  
  if( isSending == 1)
  {  
    if (counter == 9)
    {
       /*float acc =0;
       for( int i=0; i<=9;i++)
       {
         acc = acc + (float) val[i];
       }
       float mean = acc/10;
       float newton = (mean-k)/c;*/
       /*
       Serial.print("Force is: ");
       Serial.print(val1);
       Serial.print("    Position is: ");
       Serial.println(pos);
    }
  }
  if (counter < 9)
    counter++;
   else
    counter = 0; 
  //Serial.println(counter);
  */
} 
