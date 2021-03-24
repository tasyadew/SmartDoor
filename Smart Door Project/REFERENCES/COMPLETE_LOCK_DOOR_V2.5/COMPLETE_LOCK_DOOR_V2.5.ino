
//LIBRARY USED:-
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

int x;
int state = 0;    //Loggic for data transmit

// LCD USAGE:-
LiquidCrystal lcd(23, 24, 25, 26, 27, 28);

//PIR MOTION SENSOR CALIBRATE USAGE:-
//the time we give the sensor to calibrate (10-60 secs according to the datasheet)
int calibrationTime = 10;
 
//the time when the sensor outputs a low impulse
long unsigned int lowIn;        
 
//the amount of milliseconds the sensor has to be low
//before we assume all motion has stopped
long unsigned int pause = 200; 
 
boolean lockLow = true;
boolean takeLowTime; 

int pirPin = 4;    //the digital pin connected to the PIR sensor's output

//BUZZER PIN:-
#define buzzer 8

//LED PIN DEFINE:-
#define red 5
#define green 6
#define blue 7

//RFID DEFINE:-
#define SS_PIN 10
#define RST_PIN 9


#define ACCESS_DELAY 2000
#define DENIED_DELAY 1000
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

//FINGERPRINT DEFINE:-
SoftwareSerial mySerial(2, 3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
int fingerprintID = 0;
String IDname;

void setup() {
  Serial.begin(9600);   // Initiate a serial communication
  analogWrite (22,20);
  lcd.begin(16, 2);
  
//RGB USAGE:-
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);

//BUZZER USAGE:-
  pinMode(buzzer, OUTPUT);//buzzer

//PIR USAGE:-
  pinMode(pirPin, INPUT);
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

 //FINGERPRINT USAGE:-
  finger.begin(57600);  //Initiate fingerprint communication 
  
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } 
  else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) { delay(1); }
  }

 //RFID USAGE:-
  SPI.begin();          // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522

//PROGRAME BEGIN:-
  lcd.clear();
  delay(1500);
  Serial.write( '0' );
  Serial.println("Put your card to the reader...");
  Serial.println();  
  lcd.print(" SYSYTEM IS NOW ");
  lcd.setCursor(0,1);
  lcd.print("   INITIATING   "); 

   tone3();
   delay(200);
   tone1();
   delay(200);

}

void loop() {

  if (Serial.available() > 0 ){
    state = Serial.read();
  }
 Serial.write('1');                  //closed

 digitalWrite(red, HIGH); 
 digitalWrite(green, LOW);
 digitalWrite(blue, LOW);

lcd.clear();

  //PIR USAGE:-
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

  Serial.write('1');
  Serial.println("Put your card to the reader...");
  Serial.println();   


//PART 1 - LOCK THE DOOR, INTRUDER APPROACHING
 if(digitalRead(pirPin) == HIGH){
  
     digitalWrite(blue, LOW);   //the led visualizes the sensors output pin state
       if(lockLow){ 
         //makes sure we wait for a transition to LOW before any further output is made:
         lockLow = false;           
         Serial.println("---");
         Serial.print("motion detected at ");
         Serial.print(millis()/1000);
         Serial.println(" sec");
         }        
         takeLowTime = true;


  pinMode(green, LOW);
  pinMode(red, HIGH);
  pinMode(blue, LOW);

 //Look for fingerprint
  fingerprintID = getFingerprintIDez();
  delay(50);
  if(fingerprintID == 1 || fingerprintID == 2){
    lcd.clear();
    lcd.print(" WELCOME MASTER ");
    lcd.setCursor(0,1);
    lcd.print("      DECI      ");
    tone2();
    Serial.write('1');
    tone1();
    digitalWrite(red, HIGH);
    delay(200);
    digitalWrite(red, LOW);
    delay(200);
    digitalWrite(red, HIGH);
    delay(200);
    digitalWrite(red, LOW);
    delay(200);
    fingerprintID = 0;       
  }  
  else if(fingerprintID == 3){
    lcd.clear();
    lcd.print("WELCOME UNKNOWN ");
    lcd.setCursor(0,1);
    lcd.print("    PERSON    ");
    tone2();
    Serial.write('1');
    delay(150);
    tone1();
    digitalWrite(red, HIGH);
    delay(200);
    digitalWrite(red, LOW);
    delay(200);
    digitalWrite(red, HIGH);
    delay(200);
    digitalWrite(red, LOW);
    delay(200);
    fingerprintID = 0;  
  }

///////////////////////////////////CARDS////////////////////////////////////
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

////////////////////////END CARD/////////////////////////////////////////


  if (content.substring(1) == "3B 38 47 0D") //change here the UID of the card
  {
    lcd.clear();
    Serial.println("Authorized access");
    Serial.println();
    lcd.print("WELCOME UNKNOWN");
    Serial.write('1');
    digitalWrite(green, HIGH);
    digitalWrite(red, LOW);
    digitalWrite(blue, LOW);
    tone2();
    delay(150);
    tone1();
   delay(2000);

  } 
  
   else if (content.substring(1) == "E1 EC 18 1E") //change here the UID of the card
  {
    lcd.clear();
    Serial.println("Authorized access");
    Serial.println("WELCOME ADMIN");
    Serial.println();
    lcd.print(" WELCOME MASTER ");
    lcd.setCursor(0,1);
    lcd.print("      DECI      ");
    Serial.write('1');
    digitalWrite(green, HIGH);
    digitalWrite(red, LOW);
    digitalWrite(blue, LOW);
    tone2();
    delay(150);
    tone1();
   delay(2000);

  }

  else if (content.substring(1) == "28 48 E5 49") //change here the UID of the card
  {
    lcd.clear();
    Serial.println("Authorized access");
    Serial.println();
    lcd.print("WELCOME UNKNOWN");
    Serial.write('1');
    digitalWrite(green, HIGH);
    digitalWrite(red, LOW);
    digitalWrite(blue, LOW);
    tone2();
    delay(150);
    tone1();
   delay(2000);

  }

  else if (content.substring(1) == "58 E4 9E 5C") //change here the UID of the card
  {
    lcd.clear();
    Serial.println("Authorized access");
    Serial.println();
    lcd.print("WELCOME UNKNOWN");
    Serial.write('1');
    digitalWrite(green, HIGH);
    digitalWrite(red, LOW);
    digitalWrite(blue, LOW);
    tone2();
    delay(150);
    tone1();
   delay(2000);

  }
 
 else   {
    lcd.clear();
    Serial.println(" GET LOST!!!");
    lcd.print("  GET LOST !!!  ");
    digitalWrite(red, HIGH);
    digitalWrite(green, LOW);
    digitalWrite(blue, LOW);
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
 /*      digitalWrite(red, HIGH); 
       digitalWrite(green, LOW);
       digitalWrite(blue, LOW);  //the led visualizes the sensors output pin state
*/
      if(takeLowTime){
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
          disco();
       }

else{
  Serial.write('0');
  pinMode(red, LOW);
  pinMode(green, HIGH);
  Serial.print("DOOR CLOSED");
  delay(3000);
}


}
