// Basic Bluetooth sketch HC-05_03_AT_MODE_Controlled
// Connect the HC-05 module and communicate using the serial monitor
//
// The HC-05 defaults to communication mode when first powered on.
// The default baud rate for communication mode is 9600. Your module may have a different speed.
// This sketch allows the user to enter AT mode on the HC-05
//
//
// Pins
// D2 (RX) to HC-05 TX
// D3 (TX) to voltage divider and then HC-05 RX
// D4 to voltage divider and then to pin 34
// HC-05 vcc to 5v
// HC-05 GND to common GND
//

#include <SoftwareSerial.h>
SoftwareSerial BTserial(2, 3); // RX | TX
// Connect the HC-05 TX to Arduino pin 2 RX.
// Connect the HC-05 RX to Arduino pin 3 TX through a voltage divider.

char c = ' ';
byte ATmodePin=4;

void setup()
{
 // set up the pin used to turn on AT mode
 pinMode(ATmodePin, OUTPUT);
 digitalWrite(ATmodePin, LOW); 
// Start the serial monitor
 Serial.begin(9600);
 Serial.println("Arduino is ready");

 // HC-05 default serial speed for communication mode is 9600
 BTserial.begin(9600);
 Serial.println("BTserial started at 9600");
 Serial.println("Type # to enter AT mode");
}

void loop()
{

 // Keep reading from HC-05 and send to Arduino Serial Monitor
 if (BTserial.available())
 {
 c = BTserial.read();
 Serial.write(c);
 }

 // Keep reading from Arduino Serial Monitor and send to HC-05
 if (Serial.available())
 {
 c = Serial.read();

 if (c=='#') // enter AT mode
 {
  digitalWrite(ATmodePin, HIGH);
 Serial.print("Entered AT mode. Type $ to exit");
 }

 else if (c=='$') // exit AT mode by reseting the HC-05
 {
 digitalWrite(ATmodePin, LOW);
 BTserial.print("AT+RESET\n\r");
 Serial.print("AT+RESET\n\r");
 }

 else
 {
 // Copy the serial data back to to the serial monitor.
 // This makes it easy to follow the commands and replies
 Serial.write(c);
 BTserial.write(c);
 }

 }

}
