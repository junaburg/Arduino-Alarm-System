#include <NewPing.h>
#include <Bridge.h>
#include <BridgeClient.h>
#include <BridgeServer.h>
#include <BridgeSSLClient.h>
#include <BridgeUdp.h>
#include <Console.h>
#include <FileIO.h>
#include <HttpClient.h>
#include <Mailbox.h>
#include <Process.h>
#include <IRremote.h>

// Select which PWM-capable pins are to be used.
int RED_PIN =  9;
#define BLUE_PIN 22
#define GREEN_PIN 24
#define BUZZER 1
#define LASER 0
#define LIGHT 4 5 7
#define TRIGGER_PIN  X  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     X  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 100 // Maximum distance we want to ping for (in centimeters).
#define ALARM 3
#define REMOTE 
int RECIEVER = 7;
  
float sinVal;
int toneVal;
boolean triggered;
short code[4]{'1','2','3','4'};
IRrecv irrecv(RECIEVER);
decode_results results;    

// Convenience typedef: uint = unsigned int
typedef unsigned int uint;

void setup() {

//set pinModes for RGB
//pinMode(RED_PIN, OUTPUT);
//pinMode(BLUE_PIN, OUTPUT);
//pinMode(GREEN_PIN, OUTPUT);

//set IR Remote
Serial.begin(19200); // Open serial monitor at 115200 baud to see ping results. 
irrecv.enableIRIn();

// set Buzzer
pinMode(BUZZER,OUTPUT);

//reset lights
//analogWrite(RED_PIN, 0);
//analogWrite(BLUE_PIN, 0);
//analogWrite(RED_PIN, 0);

//Passcode for remote control
delay(5000);

triggered = false; 
}

void loop() {
  digitalWrite(LED_BUILTIN,HIGH);
  
  if(irrecv.decode())
  {
    int value = results.value;
      
    Serial.println(value);
      
    Serial.println(" "); 

    Serial.print("Code: "); 

    Serial.println(results.value); //prints the value a a button press 

    Serial.println(" "); 

    irrecv.resume();    //recieve next input
  } 

//  if (triggered == true) 
//  {
//    digitalWrite(LED_BUILTIN,HIGH);
//    color(255,0,0);
//    alarm();
//  }
//  else
//  {
//    color(0,255,0);
//    delay(50);// Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
//    //unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
//    uint distance = 100; //uS / US_ROUNDTRIP_CM;
//    Serial.println(distance);
//    if (distance < 100) 
//    {
//      triggered = true;
//    }
}

void alarm(){
  //flashes colors
   color(255,0,0); //red
   delay(100);
   color(255,255,0); //yelow
   delay(100);
}

//void Getpass(){
//  tone(13,2000);
//  for(short i=0 ; i&lt;4 ; i++)
//            {
//              
//           char keypressed = myKeypad.waitForKey();
//              if (keypressed==code[i])
//              a++;
//            }
//}


//helper function enabling us to send a colour in one command
void color (unsigned char red, unsigned char green, unsigned char blue)     // the color generating function
{     
    analogWrite(RED_PIN, red);     
    analogWrite(BLUE_PIN, blue);
    analogWrite(GREEN_PIN, green);
}
