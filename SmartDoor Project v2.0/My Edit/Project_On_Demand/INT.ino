//////////////////////////////FINGERPRINT/////////////////////////////////

int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  
  // found a match!
  Serial.print("Found ID #"); 
  Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); 
  Serial.println(finger.confidence);
  return finger.fingerID; 
}


////////////////////////////////ULTRASONIC//////////////////////////////////////
int calc_distance(){ 
  
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pulseTime = pulseIn(echoPin, HIGH);
  distance = (pulseTime*0.034)/2;    // measure distance and convert to centimetres (Left Sensor)
  return distance;
}
int calc_distance2(){ 
  
  digitalWrite(trigPin2, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  pulseTime2 = pulseIn(echoPin2, HIGH);
  distance2 = (pulseTime2*0.034)/2;    // measure distance and convert to centimetres (Right Sensor)
  return distance2;
}
