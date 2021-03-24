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
