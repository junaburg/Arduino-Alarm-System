
/* This code is for a LASER Tripwire Alarm based on a light sensor, LASER module and an IR remote
 * The LASER is constantly sending beams to the sensor, when someone passes the light is not detected
 * and the alarm goes off, and will not stop until you input the code you set on the IR remote
 * https://github.com/junaburg/Arduino-Alarm-System
 */
#include <IRremote.hpp>
#include <Password.h>
 
#define Rec 0      //Light sensor output
#define Laser 2    //Laser module 
#define Button 3   //Push button input
#define Buzzer 13  //Buzzer/speaker
#define Reciever 7 //IR receiver module
bool detection;
unsigned int keypad = IrReceiver.decodedIRData.decodedRawData;
Password password = Password("1234");


void setup() {
  Serial.begin(9600);  //begin reading on serial monitor on baud9600
  IrReceiver.begin(Reciever); // start the IR receiver
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
     
  if(keypad == 0xBA45FF00){ //If POWER is pressed erase the password
        password.reset();
  }
  if(keypad == 0x3734F2){  //If FUNC/STOP is pressed on the IRremote you can set a password for the buzzer 
    switch(keypad){
      case 0xE916FF00: //0
        password.append(keypad);
        break;
      case 0xF30CFF00: //1
        password.append(keypad);
        break;
      case 0xE718FF00: //2
        password.append(keypad);
        break;
      case 0xC19E983F: //3
        password.append(keypad);
        break;
      case 0xF708FF00: //4
        password.append(keypad);
        break;
      case 0xE31CFF00: //5
        password.append(keypad);
        break;
      case 0xA55AFF00: //6
        password.append(keypad);
        break;
      case 0xBD42FF00: //7
        password.append(keypad);
        break;
      case 0xAD52FF00: //8
        password.append(keypad);
        break;
      case 0xB53AFF00: //9
        password.append(keypad);
        break;
        IrReceiver.resume();
      }
    }
  }
  IrReceiver.resume();
 
 if(Detect < 200)              //The Max value is 760, if someone passes it goes below that (every value lower than 700 can do the work)
    detection = true;          //The detection is triggered
 if(Detect > 200)
    detection = false;
 if(detection==true)
    {
       tone(Buzzer,2000);        //Alarm sequence will go on as long as the detection is true
       delay(1000);            //This alarm has two sounds 2kHz nd 1Khz delayed by 50ms
       tone(Buzzer,1000);
       delay(200);
    }
for(int i;
 if(Button_state == LOW)  //If the button is pressed the buzzer is turned off and the detection too
    {
      detection = false;
      noTone(Buzzer);
    }

  
}
