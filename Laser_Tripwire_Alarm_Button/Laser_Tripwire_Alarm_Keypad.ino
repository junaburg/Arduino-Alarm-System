/* This code is for a LASER Tripwire Alarm based on a light sensor, LASER module and keypad
 * The LASER is constantly sending beams to the sensor, when someone passes the light is not detected
 * and the alarm goes off, and will not stop until you press '*' and enter the correct code
 * Refer to www.surtrtech.com for more details
 */

#include <Keypad.h>

#define Rec 0
#define Laser 2
#define Button 3

bool detection;
short a=0;
short code[4]={'1','3','6','6'};  //pass code stored in a array you can make it longer or shorter
                                  //by changing '4' and add/remove values

const byte numRows= 4;            //Rows and columns of the keypad
const byte numCols= 4;
 
char keymap[numRows][numCols]=    //Keypad map
          {
          {'1', '2', '3', 'A'}, 
          {'4', '5', '6', 'B'}, 
          {'7', '8', '9', 'C'},
          {'*', '0', '#', 'D'}
          };

byte rowPins[numRows] = {11,10,9,8}; //Keypad 8 pins
byte colPins[numCols]= {7,6,5,4}; 

Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);

void setup() {
  
  pinMode(Laser, OUTPUT);
  digitalWrite(Laser, HIGH);
  delay(2000);
}

void loop() {

 short Detect = analogRead(Rec);                 //Constantly reading the sensor value, to detect if someone passes


    if(Detect < 500)
        detection = true;

    if(detection==true) 
        {                                       //Alarm sequence and constantly waiting for '*' to be pressed
         tone(13,1000);
         delay(50);
         tone(13,200);
         delay(50);
         char keypressed = myKeypad.getKey();
         if (keypressed == '*')                   //if '*' is pressed go to Getpass function
         Getpass();
          }
    
     if(a==4){                                   //if a==4 means the code is correct, the alarm is off
         noTone(13);
         a=0;                                   //setting the a to 0, otherwise the alarm will turn off automatically
         detection=false;
         }
 
  
}

void Getpass(){               //Getting passcode function
  tone(13,2000);              //Constant frequency sound while entring the code
  for(short i=0 ; i<4 ; i++)
            {
              
           char keypressed = myKeypad.waitForKey();
              if (keypressed==code[i])   //If the sequence is correct the a increases (4) means all values are right
              a++;
            }
}



