//LIBRARY USED:-
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(1, 2, 4, 5, 6, 7);

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
  lcd.begin(16, 2);
  //Serial.begin(9600);
  
  lcd.clear();
  lcd.print(" OUR INSTAGRAM:- ");
  lcd.setCursor(0,1);
  lcd.print("{danial_x_deci}");
  delay(2250);
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("{   _hfyim    }");
  delay(2250);
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("{tasyanazrain}");
  delay(2250);
  lcd.clear();

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
  lcd.print("PUT YOUR CARD TO");
  lcd.setCursor(0,1);
  lcd.print("   THE READER   ");
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

lcd.clear();

if (open == LOW){
  lcd.clear();
  pinMode(red, LOW);
  pinMode(green, HIGH);
  myservo.write(50);
  lcd.print("  DOOR IS OPEN  ");
  Serial.println("DOOR IS OPEN");
  delay(3000);
}  

else if(door == HIGH){
  lcd.clear();
  pinMode(red, LOW);
  pinMode(green, HIGH);
  myservo.write(50);
  lcd.print("  DOOR IS OPEN  ");
  Serial.println("DOOR IS OPEN");
  delay(3000);
}


else{
  
if(program1 == HIGH && program2 == LOW) {
//do{

 if(digitalRead(pirPin) == HIGH){
  lcd.clear();
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
  lcd.clear();
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
  lcd.clear();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "3B 38 47 0D") //change here the UID of the card
  {
    lcd.print("ACCESS GRANTED :");
    Serial.println("Authorized access");
    lcd.setCursor(0,1);
    lcd.print(" WELCOME SYAFIQ ");
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
    lcd.print("ACCESS GRANTED :");
    Serial.println("Authorized access");
    lcd.setCursor(0,1);
    lcd.print(" WELCOME MASTER ");
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
    lcd.print("ACCESS GRANTED :");
    Serial.println("Authorized access");
    lcd.setCursor(0,1);
    lcd.print(" WELCOME MASTER ");
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
    lcd.print("ACCESS GRANTED :");
    Serial.println("Authorized access");
    lcd.setCursor(0,1);
    lcd.print("  WELCOME MOFARO ");
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
    lcd.print("   GET LOST !!! ");
    Serial.println(" GET LOST!!!");
    lcd.setCursor(0,1);
    lcd.print("   YOU THIEF   ");
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
       lcd.clear();
       lcd.print("   NO MOTION :  ");
       lcd.print(" DOOR UNLOCKED  ");
       digitalWrite(red, HIGH); 
       digitalWrite(green, LOW);
       digitalWrite(yellow, LOW);  //the led visualizes the sensors output pin state

       }
  }

//BREAK//
else if (program2 == HIGH && program1 == LOW){
  lcd.clear();
  lcd.print("  SAVE & QUIET  ");
  lcd.setCursor(0,1);
  lcd.print("      MODE");
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

//BREAK 2
else{
  lcd.clear();
  lcd.print("   DOOR CLOSED  ");
  myservo.write(50);
  pinMode(red, LOW);
  pinMode(green, HIGH);
  Serial.print("DOOR CLOSED");
  delay(2500);
}

}


}
