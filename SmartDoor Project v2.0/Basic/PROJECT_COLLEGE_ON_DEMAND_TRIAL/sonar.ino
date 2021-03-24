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
