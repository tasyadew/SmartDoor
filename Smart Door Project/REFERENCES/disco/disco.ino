void disco() {
    for(x=0; x<=341; x++) {
      Serial.println(x);
      analogWrite(red, map(x, 0, 341, 0, 255));
      analogWrite(green, map(x, 0, 341, 255, 0));
      analogWrite(blue, 255);
    }
    for(x=342; x<=682; x++) {
      Serial.println(x);
      analogWrite(green, map(x, 342, 682, 0, 255));
      analogWrite(blue, map(x, 342, 682, 255, 0));
      analogWrite(red, 255);
    }
    for(x=683; x<=1023; x++) {
      Serial.println(x);
      analogWrite(blue, map(x, 683, 1023, 0, 255));
      analogWrite(red, map(x, 683, 1023, 255, 0));
      analogWrite(green, 255);
    }
    x=0;
}
