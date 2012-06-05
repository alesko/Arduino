#if ARDUINO > 18
#include <SPI.h>
#endif

#include <Ethernet.h>
#include "TextFinder.h"


// assign a MAC address for the ethernet controller.
// fill in your address here:
byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
// assign an IP address for the controller:
//IPAddress ip(130,229,40,206);
//IPAddress gateway(130,229,40,255);	
//IPAddress subnet(255, 255, 255, 0);

// Initialize the Ethernet server library
// with the IP address and port you want to use 
// (port 80 is default for HTTP):
EthernetServer server(80);
EthernetClient client;

char buffer[8];


const int flexiForcePin = 0; // Analog pin0 connected to sensor
int motorPin = 9;    // LED connected to digital pin 9

void setup() {
  // start the SPI library:
  SPI.begin();
  Serial.begin(9600);
  
  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    for(;;)
      ;
  }
  // print your local IP address:
  Serial.print("My IP address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print("."); 
  }
  Serial.println();
  
  
  // start the Ethernet connection and the server:
  server.begin();

  // give the sensor and Ethernet shield time to set up:
  delay(1000);

}


void sendHeader(EthernetClient client, char* title)
{
  client.println("HTTP/1.1 200 OK");  
  client.println("Content-Type: text/html");
  client.println();
  client.println("<html><head><title>");
  client.print(title);
  client.println("</title><body>");
}

int motorToForce[255];

void doAct1()
{
  Serial.println("doAct1");
  int d= 100;
  
  //if (mySerial.available())
  //  Serial.write(mySerial.read());
  
  int value = analogRead(flexiForcePin);
  //int motorForce = map(value, 0, 1023, 0, 255);
  int i=0;
  for(i = 0; i<255; i++)
  {
     analogWrite(motorPin,i);
     
     motorToForce[i] = analogRead(flexiForcePin);
     Serial.print("Int ");
     Serial.print(i);
     Serial.print(" ");
     Serial.println(motorToForce[i]);
     delay(d);
  } 
  for(i = 255; i>=0; i--)
  {
     analogWrite(motorPin,i);
     
     motorToForce[i] = (motorToForce[i] + analogRead(flexiForcePin))/2;
     Serial.print("Int ");
     Serial.print(i);
     Serial.print(" ");
     Serial.println(motorToForce[i]);
     delay(d);
  } 
  
  //analogWrite(motorPin,motorForce);
  
  
}

void doAct2()
{
  Serial.println("Calibrate");
  int i=0;
  int d= 100;
  int force = 0;
  while( force < 300 )
  {    
    analogWrite(motorPin,i);
    delay(d);
    force = analogRead(flexiForcePin);
    motorToForce[i] = force;
    Serial.println(motorToForce[i]);
    i++; 
  }
  i--;
  Serial.print("Int ");
     Serial.print(i);
     Serial.print(" ");
     Serial.println(motorToForce[i]);
  analogWrite(motorPin,0);
  
}

void doAct3()
{
  Serial.print("Sense ");
  int i=0;
  int d= 50;
  int force = 0;
  int accuForce = 0;
  //while( force < 800 )
  for(i=0;i<100;i++)
  {    
    //analogWrite(motorPin,i);
   // delay(d);
    force = analogRead(flexiForcePin);
    accuForce = accuForce + force;
    //motorToForce[i] = force;
    //Serial.println(force);
  }
  Serial.println((accuForce/100));
}

void doAct4(int duty)
{
  Serial.print("Run motor ");
  Serial.print(duty);
  Serial.println(" percent");
  int i=0;
  int d= 50;
  int force = 0;
  analogWrite(motorPin,duty);
  Serial.println("Done");
 
  
}


void listenForEthernetClients() 
{
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client){
    //Serial.println("Got a client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    TextFinder finder(client);
    int type = 0;
    while (client.connected() ){
      if (client.available() ){
        
        sendHeader(client,"Post Example");
        client.println("<h2>Click buttons to turn pin 8 on or off</h2>");
        client.print("<form action='/' method='GET' ><p><input type='hidden' name='pinD8' ");
        client.println(" value='0'><input type='submit' value='Off' /></form>");
        client.print("<form action='/' method='GET' ><p><input type='hidden' name='pinD8' ");
        client.println(" value='1'><input type='submit' value='On' /></form>");
        client.print("<form action='/' method='GET' ><p><input type='hidden' name='act' ");
        client.println(" value='1'><input type='submit' value='Act1' /></form>");
        client.print("<form action='/' method='GET' ><p><input type='hidden' name='act' ");
        client.println(" value='2'><input type='submit' value='Act2' /></form>");
        client.print("<form action='/' method='GET' ><p><input type='hidden' name='act' ");
        client.println(" value='3'><input type='submit' value='Act3' /></form>");
        
        client.print("<form action='/' method='GET' ><p><input type='hidden' name='act' ");
        client.println(" value='0'><input type='submit' value='Stop' /></form>");
        client.print("<form action='/' method='GET' ><p><input type='hidden' name='act' ");
        client.println(" value='25'><input type='submit' value='25%' /></form>");
        client.print("<form action='/' method='GET' ><p><input type='hidden' name='act' ");
        client.println(" value='50'><input type='submit' value='50%' /></form>");
        client.print("<form action='/' method='GET' ><p><input type='hidden' name='act' ");
        client.println(" value='60'><input type='submit' value='60%' /></form>");
        client.print("<form action='/' method='GET' ><p><input type='hidden' name='act' ");
        client.println(" value='70'><input type='submit' value='70%' /></form>");
        client.print("<form action='/' method='GET' ><p><input type='hidden' name='act' ");
        client.println(" value='80'><input type='submit' value='80%' /></form>");
        client.print("<form action='/' method='GET' ><p><input type='hidden' name='act' ");
        client.println(" value='90'><input type='submit' value='90%' /></form>");
        client.print("<form action='/' method='GET' ><p><input type='hidden' name='act' ");
        client.println(" value='100'><input type='submit' value='100%' /></form>");
        
        
        if(finder.find("GET /" )){
          //Serial.println("Found something");  
          while(finder.findUntil("act","\n\r")){
            //Serial.println("Found act");
            int act = finder.getValue();
            switch(act)
            {
              case 1:
                doAct1();
                break;
              case 2:
                doAct2();
                break;
              case 3:
                doAct3();
                break;
              case 0:
                doAct4(0);
                break;
              case 25:
                doAct4(64);
                break;
              case 50:
                doAct4(128);
                break;
              case 60:
                doAct4(153);
                break;
              case 70:
                doAct4(179);
                break;
              case 80:
                doAct4(204);
                break;
              case 90:
                doAct4(230);
                break;
              case 100:
                doAct4(255);
                break;
               
            }
          }
        }
        client.println("</body></html>");
      }
      break;      
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
  }
}


void loop() { 
  // check for a reading no more than once a second.
/*  if (millis() - lastReadingTime > 1000){
    // if there's a reading ready, read it:
    // don't do anything until the data ready pin is high:
    if (digitalRead(dataReadyPin) == HIGH) {
      getData();
      // timestamp the last time you got a reading:
      lastReadingTime = millis();
    }
  }
*/
  // listen for incoming Ethernet connections:
  listenForEthernetClients();
}
