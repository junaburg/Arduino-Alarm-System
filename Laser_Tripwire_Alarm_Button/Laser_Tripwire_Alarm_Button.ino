
/* This code is for a LASER Tripwire Alarm based on a light sensor, LASER module and a push button
 * The LASER is constantly sending beams to the sensor, when someone passes the light is not detected
 * and the alarm goes off, and will not stop until you press the button
 * Refer to www.surtrtech.com for more details
 */
#include <IRremote.hpp>
 
#define Rec 0      //Light sensor output
#define Laser 2    //Laser module 
#define Button 3   //Push button input
#define Buzzer 13
#define Reciever 7
bool detection;

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(Reciever); // start the receiver
  pinMode(Laser, OUTPUT);
  pinMode(Buzzer,OUTPUT); 
  digitalWrite(Laser, HIGH); //Turning on the laser
  delay(2000);
}

void loop() {
//Serial.println(analogRead(Rec));
 short Detect = analogRead(Rec);            //Constanly reading the module value
 bool  Button_state = digitalRead(Button);  //And the button value (1-0)
 
   if(IrReceiver.decode())
  {
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX); //prints the value of a button press
    IrReceiver.resume();               // Receive the next value
    Serial.println("*****************");
  } 
 
 if(Detect < 200)              //The Max value is 760, if someone passes it goes below that (every value lower than 700 can do the work)
    detection = true;          //The detection is triggered
 if(Detect > 200)
    detection = false;
 if(detection==true)
    {
       tone(Buzzer,2000);        //Alarm sequence will go on as long as the detection is true
       delay(1000);            //This alarm has two sounds 2kHz nd 1Khz delayed by 50ms
       tone(Buzzer,1000);
       delay(50);
    }

 if(Button_state == LOW)  //If the button is pressed the buzzer is turned off and the detection too
    {
      detection = false;
      noTone(Buzzer);
    }

  
}
