#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
SoftwareSerial mySerial(2, 3);

#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define SS_PIN 10
#define RST_PIN 9
#define CCESS_ADELAY 2000
#define DENIED_DELAY 1000
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.


#define echoPin2   ?
#define trigPin2   ?
#define echoPin   ?
#define trigPin   ?
#define buzzer A0
#define red 7
#define green 1
#define buttonCommand_1 ?
#define buttonCommand_2 ?
#define SERVO_PIN 6
Servo myservo;

unsigned long pulseTime = 0;
unsigned long distance = 0;
unsigned long pulseTime2 = 0;
unsigned long distance2 = 0;

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
int fingerprintID = 0;
String IDname;
const int rs = A0, en = A1, d4 = A2, d5 = A3, d6 = A4, d7 = A5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


/////////////////////////////////////////////////////////////////////////////
void setup() {
  myservo.write(120);
  lcd.begin(16, 2);

  //Hardware define
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);

  //Fingerprint sensor module setup
  Serial.begin(9600);
  SPI.begin();          // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  // set the data rate for the sensor serial port
  finger.begin(57600);
  lcd.print("   SMART A.D.   ");
  delay(2000);
  digitalWrite(red, HIGH);
  digitalWrite(green, LOW);

}


////////////////////////////////////////////////////////////////////////////
void loop() {
  // put your main code here, to run repeatedly:

}
