// FOR NANO, HC-05 (MASTER), SERVO

#include <Servo.h>
Servo myServo;
int state = 0;
int angle = 20; //default angle for the servo

void setup() {
  Serial.begin(9600);
  myServo.attach(6);
  
}
void loop() {
 if(Serial.available() > 0){    // For receiving data
    state = Serial.read();      // can read from slave
 }
    
  if (state == '1') {
    myServo.write(150); 
    state = 0;
 }
  else if (state == '0') {
    myServo.write(20); 
    state = 0;
  }

 }
