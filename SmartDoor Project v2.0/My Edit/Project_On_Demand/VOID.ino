////////////////////////////////LCD////////////////////////////////////
void LcdSetup(){
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

void LcdMaster(){
   lcd.clear();
      lcd.print(" WELCOME MASTER ");
      lcd.setCursor(0, 1);
      lcd.print("            ");
      
}

void LcdUnknown(){
  lcd.clear();
      lcd.print("WELCOME UNKNOWN");
}


void LcdUser1(){
  lcd.clear();
      lcd.print("WELCOME SIR");
      lcd.setCursor(0, 1);
      lcd.print("  FENDY");
      

}

void LcdAccess(){
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

void LcdDenied(){
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

void LcdOpen(){
  lcd.clear();
      lcd.print("PLEASE CLOSE THE");
      lcd.setCursor(0, 1);
      lcd.print("DAMN DOOR IDIOT!");
      Serial.println(open);
      myservo.write(0);
      digitalWrite(red, LOW);
      digitalWrite(green, HIGH);
      tone1();
      delay(150);
      tone1();
      delay(150);
      tone1();
      delay(1150);
    

}

/////////////////////////////////LED&SERVO&TONE////////////////////////////////
void Welcome(){
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
      
}

//////////////////////////////////RFID///////////////////////////////////////////
void control_id() {
  if (content.substring(1) == "E1 EC 18 1E") {
    digitalWrite(red, LOW);
    digitalWrite(green, HIGH);
    lcd.clear();
    lcd.print(" ADMINISTRATOR");
    lcd.setCursor(0, 1);
    lcd.print("     ACCESS");
    delay(2000);
    lcd.clear();
    lcd.print("ADD NEW ID ?");
    lcd.setCursor(0, 1);
    lcd.print("DEL CURRENT ID ?");
    
    if (buttonCommand_1 == 1) {
      lcd.clear();
      lcd.print("SCAN CARD TO ADD");
      lcd.setCursor(0, 1);
      lcd.print(" AS NEW ID USER");

      //scanning the id card.
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

      lcd.clear();
      lcd.print(" THE CARD ID IS");
      lcd.setCursor(0, 1);
      lcd.print("   REGISTERED");
      digitalWrite(red, LOW);
      digitalWrite(green, HIGH);
      delay(200);
      digitalWrite(green, LOW);
      delay(200);
      digitalWrite(green, HIGH);
      delay(200);
      digitalWrite(green, LOW);
      delay(2000);
      tone2();
      delay(150);
    }

    if (buttonCommand_2 == 1) {
      lcd.clear();
      lcd.print("SCAN CARD TO DEL");
      lcd.setCursor(0, 1);
      lcd.print("CURRENT ID USER");

      //scanning the id card.
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

      lcd.clear();
      lcd.print(" THE CARD ID IS");
      lcd.setCursor(0, 1);
      lcd.print("   DELETED");
      digitalWrite(green, LOW);
      digitalWrite(red, HIGH);
      delay(200);
      digitalWrite(red, LOW);
      delay(200);
      digitalWrite(red, HIGH);
      delay(200);
      digitalWrite(red, LOW);
      delay(2000);
      tone2();
      delay(150);
    }
  }
}
