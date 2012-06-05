

int outPin =  13;      // the number of the out pin
void setup() 
{
  pinMode(outPin, OUTPUT);
  
  digitalWrite(outPin, LOW);
  
}

void loop() 
{
  int d = 100; 
  delay(10000-d);
  
  digitalWrite(outPin, HIGH);
  delay(d);
  digitalWrite(outPin, LOW);
  
}
