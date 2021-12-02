
/* This code is for a LASER Tripwire Alarm based on a light sensor, LASER module and an IR Remote
 * The LASER is constantly sending beams to the sensor, when someone passes the light is not detected
 * and the alarm goes off, and will not stop until you input the set password to turn it off
 */
#include <IRremote.hpp>
//#include <LiquidCrystal.h> this project includes alot of lcd display code I dont know if it works 
#define Light 0      //Light sensor output
#define Laser 2    //Laser module 
#define Button 3   //Push button input
#define Buzzer 13
#define Reciever 7
bool detection = false;   //the bool for the tripwire
bool locked = true;  //determines if the password system is locked
bool set = false; //determines if there is a userpassword set or not

String defaultpass = "1234"; //this password never changes
String userpass = "";  //this password is set by the user
String inputPass = ""; //this password is the current inputed pass
String tail = ""; //this is what holds the number that is pressed

//long btn1 =  0xF30CFF00; //IRremote button HEX codes
//long btn2 = 0xE718FF00;
//long btn3 = 0xA15EFF00;
//long btn4 = 0xF708FF00;
//long btn5 = 0xE31CFF00;
//long btn6 = 0xA55AFF00;
//long btn7 = 0xBD42FF00;
//long btn8 = 0xAD52FF00;
//long btn9 = 0xB54AFF00;
//long btn0 = 0xE916FF00;
//long btnPOWER = 0xBA45FF00;
//long btnFUNC = 0xB847FF00;

//String btn1 =  "F30CFF00"; //IRremote button HEX codes
//String btn2 = "E718FF00";
//String btn3 = "A15EFF00";
//String btn4 = "F708FF00";
//String btn5 = "E31CFF00";
//String btn6 = "A55AFF00";
//String btn7 = "BD42FF00";
//String btn8 = "AD52FF00";
//String btn9 = "B54AFF00";
//String btn0 = "E916FF00";
//String btnPOWER = "BA45FF00";
//String btnFUNC = "B847FF00";

String btn1 =  "f30cff00"; //IRremote button HEX codes
String btn2 = "e718ff00";
String btn3 = "a15eff00";
String btn4 = "f708ff00";
String btn5 = "e31cff00";
String btn6 = "a55aff00";
String btn7 = "bd42ff00";
String btn8 = "ad52ff00";
String btn9 = "b54aff00";
String btn0 = "e916ff00";
String btnPOWER = "ba45ff00";
String btnFUNC = "b847ff00";


void setup() {
  IrReceiver.begin(Reciever); // start the receiver
  
  
  pinMode(Laser, OUTPUT);  
  pinMode(Buzzer,OUTPUT);
   
  
  Serial.begin(9600);  //begin serial monitor at 9600 baud
  digitalWrite(Laser, HIGH); //Turning on the laser
  delay(2000);
}

void loop() {
 //Serial.println(analogRead(Light));         //for reading light sensor values
 short Detect = analogRead(Light);            //Constanly reading the module value
 bool  Button_state = digitalRead(Button);    //And the button value (1-0) im not using the button anymore I'm using the Remote at this stage


 
   if(IrReceiver.decode())
  {
    long keypad = IrReceiver.decodedIRData.decodedRawData;

    //prints the value of a button press
    Serial.println(String(keypad,HEX));
    Serial.println("*****************");

  
    ////////////////////////////////////////////////////////////////////////////
     if (String(keypad,HEX) == btn1) {
        Serial.println("1");
         tail ="1";
         updatePass(tail);
      }
      else if (String(keypad,HEX) == btn2) {
        Serial.println("2");
         tail ="2";
         updatePass(tail);
      }
      else if (String(keypad,HEX) == btn3) {
        Serial.println("3");
         tail ="3";
         updatePass(tail);
      }
      else if (String(keypad,HEX) == btn4) {
        Serial.println("4");
         tail = "4";
         updatePass(tail);
      }
      else if (String(keypad,HEX) == btn5) {
        Serial.println("5");
         tail = "5";
         updatePass(tail);
      }
      else if (String(keypad,HEX) == btn6) {
        Serial.println("6");
         tail = "6";
         updatePass(tail);
      }
      else if (String(keypad,HEX) == btn7) {
        Serial.println("7");
         tail = "7";
         updatePass(tail);
      }
      else if (String(keypad,HEX) == btn8) {
        Serial.println("8");
         tail = "8";
         updatePass(tail);
      }
      else if (String(keypad,HEX) == btn9) {
        Serial.println("9");
         tail = "9";
         updatePass(tail);
      }
      else if (String(keypad,HEX) == btn0) {
        Serial.println("0");
         tail = "0";
         updatePass(tail);
      }
      
      else if(String(keypad,HEX) == btnPOWER){
        resetPass();
      }
      
      else if(String(keypad,HEX) == btnFUNC){
        if(set == true){
          if(inputPass != ""){
             set = false;
             Serial.println("\nPassword changing...");
             delay(10);
             setnewpass();
          }
          else{
            //lcd.setCursor(0,1);
            //lcd.print("Enter Userpass 6");
            Serial.println("\nPlease enter password");
          }
        }
              
            else if(set == false){
                          //lcd.clear();
                          //lcd.setCursor(0,0);
                          //lcd.print("Change Password");
                          Serial.println("\nChange Password...");
                          setpass();
                       }
            else if(locked == true){
            //lcd.clear();
            //lcd.setCursor(0,0);
            //lcd.print("Plz login Root");
                       }
      }
      
    IrReceiver.resume(); //recieve the next value
  }
  
//////////////////////////////////////////////////////////////////////////////
/* this is for detecting the light sensor if it falls below a certain value the buzzer will sound
 * and the system should lock requiring a password
 */
 if(Detect < 200) {         //The Max value is ~860, if someone passes it goes below that (every value lower than 700 can do the work)
    detection = true;          //The detection is triggered
    //Serial.println("Alarm triggered");
}
   
 if(detection == true)
    {
       tone(Buzzer,2000);       //Alarm sequence will go on as long as the detection is true
       delay(1000);            //This alarm has two sounds 2kHz nd 1Khz delayed by 50ms
       tone(Buzzer,1000);
       delay(50);
    }
  if(detection == false){
    noTone(Buzzer);
  }
////////////////////////////////////////////////////////////////////////////////
//
// if(Button_state == LOW)  //If the button is pressed the buzzer is turned off and the detection too
//    {
//      detection = false;
//      noTone(Buzzer);
//    }
  
}


void resetPass() {
  inputPass = "";
  detection = false;
  noTone(Buzzer);
  Serial.println("Resetting...");
}

bool updatePass(String character) {
  if (locked == false)    //redudancy
    return false;
    
  beep();  //haha beep
  //lcd.print("*");
    inputPass += character; //receiving inputs to the input pass string
    if (inputPass.length() < defaultpass.length()) {
     //do nothing
    }
    else {
      if(set == false){
      if (defaultpass == inputPass || userpass == inputPass ) {//both passwords can login
        locked = false;
        detection = false;
        Serial.println("\nUNLOCKED");
          delay(60);
          digitalWrite(Buzzer, HIGH);
          delay(150);
          digitalWrite(Buzzer, LOW);
          delay(100);
          digitalWrite(Buzzer, HIGH);
          delay(200);
          digitalWrite(Buzzer, LOW);
        
        }
      
      else {
        Serial.println(inputPass);
        inputPass = "";
        digitalWrite(Buzzer, HIGH);
        delay(800);
        digitalWrite(Buzzer, LOW);
        //lcd.setCursor(0,1);
        //lcd.print("Wrong Password!");
        delay(1100);
        //lcd.clear();
        //lcd.print("IR control device");
        Serial.println("\nWRONG PASSWORD!");
        Serial.println("default pass: ");
        Serial.print(defaultpass);
        }
        
     }
     
    }
}
void setpass(){
    if(defaultpass == inputPass){//just root password can change user password
      set = true;
      locked = true;
      inputPass = "";
      //lcd.setCursor(0,1);
      //lcd.print("Enter Userpass 6");
      delay(1300);
      //lcd.clear();
      //lcd.print("Change Password");
      Serial.println("\nEnter New password 6 numbers");
    }
  else{
      //lcd.setCursor(0,1);
      //lcd.print("Enter Rootpass");
      delay(1300);
      //lcd.clear();
      //lcd.print("Change Password");
      Serial.println("\nEnter Root password");
  }
}

void setnewpass(){
  userpass = inputPass;
  //lcd.setCursor(0,1);
  //lcd.print("UserPass update");
  delay(1300);
  //lcd.clear();
  //lcd.print("IR control device");
  Serial.println("\nThe password has been updated to ");
  Serial.print(userpass);
}
void beep() {
    digitalWrite(Buzzer, HIGH);
    delay(60);
    digitalWrite(Buzzer, LOW);
}
