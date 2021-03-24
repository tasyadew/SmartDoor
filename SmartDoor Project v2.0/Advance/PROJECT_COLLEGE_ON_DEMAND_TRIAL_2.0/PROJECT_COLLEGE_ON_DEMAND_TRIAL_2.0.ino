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

  //Unnecessary startup countdown #just_want_to_look_cool ^_^!
  lcd.clear();
  lcd.noBlink();
  lcd.print("CHECKING SENSORS");
  lcd.setCursor(8, 1);
  lcd.blink();
  delay(3000);
  lcd.clear();
  lcd.noBlink();
  lcd.print("ALL SENSORS ARE");
  lcd.setCursor(0, 1);
  lcd.print("     READY");
  delay(3000);
  lcd.clear();
  lcd.print("SYSTEM START IN");
  lcd.setCursor(0, 1);
  lcd.print(" 5");
  delay(1000);
  lcd.print("  4");
  delay(1000);
  lcd.print("  3");
  delay(1000);
  lcd.print("  2");
  delay(1000);
  lcd.print("  1");
  delay(1000);
  lcd.clear();
  lcd.print("WELCOME TO KMKPH");
  delay(2000);
  lcd.clear();
}

void loop() {
  digitalWrite(red, HIGH);
  digitalWrite(green, LOW);
  lcd.clear();
  lcd.print("  SCAN CARD OR  ");
  lcd.setCursor(0, 1);
  lcd.print("  FINGERPRINT  ");
  // displayMainScreen();
  fingerprintID = getFingerprintIDez();
  delay(50);

  int distance = calc_distance();
  int distance2 = calc_distance2();

  if (distance <= 100 || distance2 <= 100) {

    if (fingerprintID == 1 ) {
      lcd.clear();
      lcd.print(" WELCOME MASTER ");
      lcd.setCursor(0, 1);
      lcd.print("            ");
      tone2();
      delay(150);
      tone1();
      digitalWrite(red, LOW);
      digitalWrite(green, HIGH);
      delay(200);
      digitalWrite(green, LOW);
      delay(200);
      digitalWrite(green, HIGH);
      delay(200);
      digitalWrite(green, LOW);
      myservo.write( 0 );
      delay(3000);

      /*   IDname = "Sara";
         displayUserGreeting(IDname);  */
    }
    else if (fingerprintID == 2) {
      lcd.clear();
      lcd.print("WELCOME UNKNOWN");
      tone2();
      delay(150);
      tone1();
      digitalWrite(red, LOW);
      digitalWrite(green, HIGH);
      delay(200);
      digitalWrite(green, LOW);
      delay(200);
      digitalWrite(green, HIGH);
      delay(200);
      digitalWrite(green, LOW);
      myservo.write( 0 );
      delay(3000);

      /*   IDname = "Rui";
         displayUserGreeting(IDname);   */
    }
    else if (fingerprintID == 5) {
      lcd.clear();
      lcd.print("WELCOME SIR");
      lcd.setCursor(0, 1);
      lcd.print("  FENDY");
      tone2();
      delay(150);
      tone1();
      digitalWrite(red, LOW);
      digitalWrite(green, HIGH);
      delay(200);
      digitalWrite(green, LOW);
      delay(200);
      digitalWrite(green, HIGH);
      delay(200);
      digitalWrite(green, LOW);
      myservo.write( 0 );
      delay(3000);

      /*   IDname = "Rui";
         displayUserGreeting(IDname);   */
    }
    if ( ! mfrc522.PICC_IsNewCardPresent())
    {
      return;
    }
    // Select one of the cards
    if ( ! mfrc522.PICC_ReadCardSerial())
    {
      return;
    }
    String content = "";
    byte letter;
    for (byte i = 0; i < mfrc522.uid.size; i++)
    {
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522.uid.uidByte[i], HEX);
      content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
      content.concat(String(mfrc522.uid.uidByte[i], HEX));
    }


    content.toUpperCase();
    if (content.substring(1) == "29 C4 A4 6E") //change here the UID of the card
    {
      lcd.clear();
        lcd.print(" ACCESS GRANTED");
        Serial.println("Authorized access");
        Serial.println();
        digitalWrite(green, HIGH);
        digitalWrite(red, LOW);
        tone2();
        delay(150);
        tone1();
        myservo.write( 0 );
        delay(3000);

    }

    else if (content.substring(1) == "49 81 F4 6E") //change here the UID of the card
    {
      lcd.clear();
        lcd.print(" ACCESS GRANTED");
        Serial.println("Authorized access");
        Serial.println();
        digitalWrite(green, HIGH);
        digitalWrite(red, LOW);
        tone2();
        delay(150);
        tone1();
        myservo.write( 0 );
        delay(3000);

    }

    else if (content.substring(1) == "E1 EC 18 1E") //change here the UID of the card
    {
      lcd.clear();
      Serial.println("Authorized access");
      Serial.println("WELCOME ADMIN");
      Serial.println();
      lcd.print(" WELCOME MASTER ");
      lcd.setCursor(0, 1);
      lcd.print("      DECI      ");
      digitalWrite(green, HIGH);
      digitalWrite(red, LOW);
      tone2();
      delay(150);
      tone1();
      myservo.write( 0 );
      delay(3000);

    }

    else   {
      lcd.clear();
      Serial.println("ACCES DENIED");
      lcd.print("  ACCES DENIED  ");
      digitalWrite(red, HIGH);
      digitalWrite(green, LOW);
      tone3();
      delay(200);
      tone3();
      delay(200);
      tone3();
      delay(200);

      delay(DENIED_DELAY);

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
