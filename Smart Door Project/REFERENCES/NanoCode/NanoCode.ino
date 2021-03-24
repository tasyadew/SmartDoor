// FOR NANO, HC-05 (MASTER), SERVO
// RECEIVE  : RFID, PIR, FINGERPRINT (To Servo)
// TRANSFER : BUTTON 3 (To buzzer)
#include <Servo.h>

//BUTTON DEFINE:-
#define buttonPin3 7
#define buttonPin4 8

//SERVO DEFINE:-
#define SERVO_PIN 6
Servo myservo;


int door = 0;
int open = 0;

int state = 0;    // Logic for data transmit


void setup() {
  Serial.begin(9600);
//BUTTON USAGE:-
  pinMode(buttonPin3, INPUT);
  pinMode(buttonPin4, INPUT);
  
//SERVO
  myservo.attach(SERVO_PIN);
  myservo.write( 70 );
  delay(1500);
  myservo.write( 0 );
  
  
}
void loop() {
 if(Serial.available() > 0){    // For receiving data
    state = Serial.read();      
 }
    
door = digitalRead(buttonPin3);
open = digitalRead(buttonPin4);
myservo.write(0);

/////////////////////////////TRANSMIT/////////////////////////////////
if ( door == LOW || open == HIGH){
  
  Serial.println("1");
  myservo.write(90);
  delay(30);
}  

else if( door == HIGH || open == LOW){
  myservo.write(0);
  Serial.println("0");
  delay(30);
}


  
else{
///////////////////////////////RECEIVE///////////////////////////////

//PART 1
 if(state == '1'){
  Serial.println("1");
   myservo.write( 90 );
 delay(20);
  myservo.write( 0 );
  state = 0;
  } 
  
 else if(state == '0'){
  Serial.println("0");
  myservo.write( 0 );
  state = 0;
  }
 }
 
}
