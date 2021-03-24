
//LIBRARY USED:-
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

//PIR MOTION SENSOR CALIBRATE USAGE:-
//the time we give the sensor to calibrate (10-60 secs according to the datasheet)
int calibrationTime = 10;       
 
//the time when the sensor outputs a low impulse
long unsigned int lowIn;        
 
//the amount of milliseconds the sensor has to be low
//before we assume all motion has stopped
long unsigned int pause = 250; 
 
boolean lockLow = true;
boolean takeLowTime; 

int pirPin = 4;    //the digital pin connected to the PIR sensor's output

//BUZZER PIN:-
#define buzzer 8

//LED PIN DEFINE:-
#define red 5
#define green 7
#define yellow 6

//SERVO DEFINE:-
#define SERVO_PIN 3
Servo myservo;

//RFID DEFINE:-
#define SS_PIN 10
#define RST_PIN 9


#define ACCESS_DELAY 2000
#define DENIED_DELAY 1000
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

//BUTTON SENSOR DEFINE:-
#define buttonPin1 A1
#define buttonPin2 A2
#define buttonPin3 A3
#define buttonPin4 A4

int program1 = 0;
int program2 = 0;
int door = 0;
int open = 0;

void setup() {
  Serial.begin(9600);   // Initiate a serial communication 

//BUTTON USAGE:-
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(buttonPin4, INPUT);

//BUZZER USAGE:-
  pinMode(buzzer, OUTPUT);//buzzer

//PIR USAGE:-
  pinMode(pirPin, INPUT);
  pinMode(yellow, OUTPUT);
  digitalWrite(pirPin, LOW);
 
  //give the sensor some time to calibrate
  Serial.print("calibrating sensor ");
    for(int i = 0; i < calibrationTime; i++){
      Serial.print(".");
      delay(500);
      }
    Serial.println(" done");
    Serial.println("SENSOR ACTIVE");
    delay(50);

 //RFID USAGE:-
  SPI.begin();          // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522

  myservo.attach(SERVO_PIN);
  myservo.write( 70 );
  delay(1500);
  myservo.write( 0 );
  Serial.println("Put your card to the reader...");
  Serial.println();  

   tone3();
   delay(200);
   tone1();
   delay(200);

}

void loop() {

program1 = digitalRead(buttonPin1);
program2 = digitalRead(buttonPin2);
door = digitalRead(buttonPin3);
open = digitalRead(buttonPin4);
myservo.write(0);

pinMode(green, LOW);
pinMode(red, HIGH);
pinMode(yellow, LOW);

if (open == LOW){
  pinMode(red, LOW);
  pinMode(green, HIGH);
  myservo.write(50);
  Serial.println("DOOR IS OPEN");
  delay(3000);
}  

else if(door == HIGH){
  pinMode(red, LOW);
  pinMode(green, HIGH);
  myservo.write(50);
  Serial.println("DOOR IS OPEN");
  delay(3000);
}


else{
  
if(program1 == HIGH && program2 == LOW) {
//do{
/*  //PIR USAGE:-
  pinMode(pirPin, INPUT);
  pinMode(yellow, OUTPUT);
  digitalWrite(pirPin, LOW);
 
  //give the sensor some time to calibrate
  Serial.print("calibrating sensor ");
    for(int i = 0; i < calibrationTime; i++){
      Serial.print(".");
      delay(1000);
      }
    Serial.println(" done");
    Serial.println("SENSOR ACTIVE");
    delay(50);

 //RFID USAGE:-
  SPI.begin();          // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522

  myservo.attach(SERVO_PIN);
  myservo.write( 70 );
  delay(1500);
  myservo.write( 0 );
  Serial.println("Put your card to the reader...");
  Serial.println();   
*/
 if(digitalRead(pirPin) == HIGH){
  
/*      digitalWrite(yellow, LOW);   //the led visualizes the sensors output pin state
       if(lockLow){ 
         //makes sure we wait for a transition to LOW before any further output is made:
         lockLow = false;           
         Serial.println("---");
         Serial.print("motion detected at ");
         Serial.print(millis()/1000);
         Serial.println(" sec");
         }        
         takeLowTime = true;
*/
  pinMode(green, LOW);
  pinMode(red, HIGH);
  pinMode(yellow, HIGH);
  // Look for new cards
  
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;

  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "3B 38 47 0D") //change here the UID of the card
  {
    Serial.println("Authorized access");
    Serial.println();
    pinMode(green, HIGH);
    pinMode(red, LOW);
    tone2();
    delay(150);
    tone1();
   myservo.write( 50 );
 delay(2000);
  myservo.write( 0 );

  } 
  
   else if (content.substring(1) == "E1 EC 18 1E") //change here the UID of the card
  {
    Serial.println("Authorized access");
    Serial.println("WELCOME ADMIN");
    Serial.println();
    pinMode(green, HIGH);
    pinMode(red, LOW);
    tone2();
    delay(150);
    tone1();
   myservo.write( 50 );
 delay(2000);
  myservo.write( 0 );

  }

  else if (content.substring(1) == "28 48 E5 49") //change here the UID of the card
  {
    Serial.println("Authorized access");
    Serial.println("WELCOME ADMIN");
    Serial.println();
    pinMode(green, HIGH);
    pinMode(red, LOW);
    tone2();
    delay(150);
    tone1();
   myservo.write( 50 );
 delay(2000);
  myservo.write( 0 );

  }

  else if (content.substring(1) == "58 E4 9E 5C") //change here the UID of the card
  {
    Serial.println("Authorized access");
    Serial.println();
    pinMode(green, HIGH);
    pinMode(red, LOW);
    tone2();
    delay(150);
    tone1();
   myservo.write( 50 );
 delay(2000);
  myservo.write( 0 );

  }
 
 else   {
    Serial.println(" GET LOST!!!");
    pinMode(red, HIGH);
    pinMode(green,LOW);
    tone3();
    delay(200);
    tone3();
    delay(200);
    tone3();
    delay(200);

    delay(DENIED_DELAY);

 
  }
 }
 
 if(digitalRead(pirPin) == LOW){ 
       digitalWrite(red, HIGH); 
       digitalWrite(green, LOW);
       digitalWrite(yellow, LOW);  //the led visualizes the sensors output pin state

/*      if(takeLowTime){
        lowIn = millis();          //save the time of the transition from high to LOW
        takeLowTime = false;       //make sure this is only done at the start of a LOW phase
        }
       //if the sensor is low for more than the given pause,
       //we assume that no more motion is going to happen
       
       if(!lockLow && millis() - lowIn > pause){ 
           //makes sure this block of code is only executed again after
           //a new motion sequence has been detected
           lockLow = true;                       
           Serial.print("motion ended at ");      //output
           Serial.print((millis() - pause)/1000);
           Serial.println(" sec");
           }
     */      
       }
  }

else if (program2 == HIGH && program1 == LOW){
  pinMode(green, LOW);
  pinMode(red, HIGH);
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;

  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "3B 38 47 0D") //change here the UID of the card
  {
    Serial.println("Authorized access");
    Serial.println();
    pinMode(green, HIGH);
    pinMode(red, LOW);
    tone2();
    delay(150);
    tone1();
   myservo.write( 70 );
 delay(2000);
  myservo.write( 0 );

  } 
  
   else if (content.substring(1) == "E1 EC 18 1E") //change here the UID of the card
  {
    Serial.println("Authorized access");
    Serial.println("WELCOME ADMIN");
    Serial.println();
    pinMode(green, HIGH);
    pinMode(red, LOW);
    tone2();
    delay(150);
    tone1();
   myservo.write( 70 );
 delay(2000);
  myservo.write( 0 );

  }

  else if (content.substring(1) == "28 48 E5 49") //change here the UID of the card
  {
    Serial.println("Authorized access");
    Serial.println("WELCOME ADMIN");
    Serial.println();
    pinMode(green, HIGH);
    pinMode(red, LOW);
    tone2();
    delay(150);
    tone1();
   myservo.write( 70 );
 delay(2000);
  myservo.write( 0 );

  }

  else if (content.substring(1) == "58 E4 9E 5C") //change here the UID of the card
  {
    Serial.println("Authorized access");
    Serial.println();
    pinMode(green, HIGH);
    pinMode(red, LOW);
    tone2();
    delay(150);
    tone1();
   myservo.write( 70 );
 delay(2000);
  myservo.write( 0 );

  }
 
 else   {
    Serial.println(" GET LOST!!!");
    pinMode(red, HIGH);
    pinMode(green,LOW);
    tone3();
    delay(200);
    tone3();
    delay(200);
    tone3();
    delay(200);

    delay(DENIED_DELAY);

 
  }
}

else{
  myservo.write(50);
  pinMode(red, LOW);
  pinMode(green, HIGH);
  Serial.print("DOOR CLOSED");
  delay(3000);
}
//while(program1 == HIGH);
}


}
