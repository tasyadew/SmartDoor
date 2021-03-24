#include <LiquidCrystal.h>
LiquidCrystal lcd(1, 2, 4, 5, 6, 7);

#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>


#define SS_PIN 10
#define RST_PIN 9

#define SERVO_PIN 3
Servo myservo;

#define CCESS_ADELAY 2000
#define DENIED_DELAY 1000
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

#define buzzer 8
#define red 5
#define green 7

#define echoPin2   25
#define trigPin2   24
#define echoPin   22
#define trigPin   23

unsigned long pulseTime = 0;
unsigned long distance = 0;
unsigned long pulseTime2 = 0;
unsigned long distance2 = 0;

#define buttonPin1 A1
#define buttonPin2 A2
int open = 0;
int door = 0;

void setup()
{
  Serial.begin(9600);   // Initiate a serial communication
  lcd.begin(16, 2);
  SPI.begin();          // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522

  pinMode(buttonPin1, INPUT);

  pinMode(buzzer, OUTPUT);//buzzer
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);

  myservo.attach(SERVO_PIN);
  myservo.write( 0 );
  delay(5000);
  myservo.write( 70 );
  tone1();
  pinMode(red, HIGH);
  delay(250);
  pinMode(red, LOW);
  pinMode(green, HIGH);
  delay(250);
  pinMode(red, HIGH);
  pinMode(green, LOW);

  lcd.clear();
  lcd.print("  SYSTEM CHECK");
  lcd.blink();
  delay(3000);
  lcd.clear();
  lcd.print(" SYSTEM READY!");
  delay(1500);
  Serial.println("Put your card to the reader...");
  Serial.println();

}
void loop()
{
  open = digitalRead(buttonPin1);
  door = digitalRead(buttonPin2);
  int distance = calc_distance();
  int distance2 = calc_distance2();

  if (distance <= 100 || distance2 <= 100) {

    if (door == 1) {
      lcd.clear();
      lcd.print("   DOOR CLOSE");
      digitalWrite(green, HIGH);
      digitalWrite(red, LOW);
      myservo.write(0);
      delay(4000);
    }

    else if (open == 0) {
      lcd.clear();
      lcd.print(" SCAN YOUR CARD");
      Serial.println(open);
      myservo.write( 70 );
      digitalWrite(green, LOW);
      digitalWrite(red, HIGH);
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
      String content = "";
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
        lcd.clear();
        lcd.print(" ACCESS GRANTED");
        Serial.println("Authorized access");
        Serial.println();
        pinMode(green, HIGH);
        pinMode(red, LOW);
        tone2();
        delay(150);
        tone1();
        myservo.write( 0 );
        delay(3000);

      }

      else if (content.substring(1) == "E1 EC 18 1E") //change here the UID of the card
      {
        lcd.clear();
        lcd.print(" ACCESS GRANTED");
        Serial.println("Authorized access");
        Serial.println("WELCOME ADMIN");
        Serial.println();
        pinMode(green, HIGH);
        pinMode(red, LOW);
        tone2();
        delay(150);
        tone1();
        myservo.write( 0 );
        delay(3000);

      }

      else if (content.substring(1) == "28 48 E5 49") //change here the UID of the card
      {
        lcd.clear();
        lcd.print(" ACCESS GRANTED");
        Serial.println("Authorized access");
        Serial.println("WELCOME ADMIN");
        Serial.println();
        pinMode(green, HIGH);
        pinMode(red, LOW);
        tone2();
        delay(150);
        tone1();
        myservo.write( 0 );
        delay(3000);

      }

      else if (content.substring(1) == "4F F9 39 EE") //change here the UID of the card
      {
        lcd.clear();
        lcd.print(" ACCESS GRANTED");
        Serial.println("Authorized access");
        Serial.println();
        pinMode(green, HIGH);
        pinMode(red, LOW);
        tone2();
        delay(150);
        tone1();
        myservo.write( 0 );
        delay(3000);

      }

      else if (content.substring(1) == "58 E4 9E 5C") //change here the UID of the card
      {
        lcd.clear();
        lcd.print(" ACCESS GRANTED");
        Serial.println("Authorized access");
        Serial.println();
        pinMode(green, HIGH);
        pinMode(red, LOW);
        tone2();
        delay(150);
        tone1();
        myservo.write( 0 );
        delay(3000);

      }

      else   {
        lcd.clear();
        lcd.print("  GET LOST!!!");
        Serial.println(" GET LOST!!!");
        pinMode(red, HIGH);
        pinMode(green, LOW);
        tone3();
        delay(200);
        tone3();
        delay(200);
        tone3();
        delay(200);

        delay(DENIED_DELAY);

      }

    }

    else if (door == 1 || open == 1) {
      lcd.clear();
      lcd.print("PLEASE CLOSE THE");
      lcd.setCursor(0, 1);
      lcd.print("DAMN DOOR IDIOT!");
      Serial.println(open);
      myservo.write(0);
      pinMode(red, LOW);
      pinMode(green, HIGH);
      tone1();
      delay(150);
      tone1();
      delay(150);
      tone1();
      delay(150);
      delay(1000);
    }
  }

  else {
    digitalWrite(red, LOW);
    digitalWrite(green, HIGH);
    lcd.clear();
    lcd.print(" NO ONE IS HERE");
    myservo.write(0);

    if (door == 1 || open == 1) {
      lcd.clear();
      lcd.print("PLEASE CLOSE THE");
      lcd.setCursor(0, 1);
      lcd.print("DAMN DOOR IDIOT!");
      Serial.println(open);
      myservo.write(0);
      pinMode(red, LOW);
      pinMode(green, HIGH);
      tone1();
      delay(150);
      tone1();
      delay(150);
      tone1();
      delay(150);
      delay(1000);
    }
  }
}
