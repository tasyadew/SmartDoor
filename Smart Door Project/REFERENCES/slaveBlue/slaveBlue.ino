// FOR UNO, HC-06 (SLAVE), BUTTON

int button = 9;  
int buttonState = 0;
int state = 0;  // unnecessary. but, oh well..

void setup() {
  pinMode (button,INPUT);
  Serial.begin(9600);
  
}

void loop() {
  if(Serial.available() > 0){    // this part is unnecessary. 
    state = Serial.read();       // for receiveng data. but this test is only to transfer
  }
  buttonState = digitalRead (button);
 if (buttonState == HIGH){
     Serial.write('1');
  }
   else {
     Serial.write('0'); 
  }

}
