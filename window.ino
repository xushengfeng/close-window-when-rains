// C++ code
//
void setup()
{
//  pinMode(LED_BUILTIN, OUTPUT);/
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
}

void loop()
{
  if (digitalRead(2) == HIGH) { // 有水
    if (digitalRead(3) == LOW) {
//      digitalWrite(LED_BUILTIN, HIGH);/
      digitalWrite(6, HIGH);
      digitalWrite(7, LOW);
    } else { // 3HIGH关到底
//      digitalWrite(LED_BUILTIN, LOW);/
      digitalWrite(6, LOW);
      digitalWrite(7, LOW);
    }
  }
  else { // 无水
    if (digitalRead(4) == LOW) {
//      analogWrite(LED_BUILTIN, 64);/
      digitalWrite(6, HIGH);
      digitalWrite(7, LOW);
    } else { // 4HIGH开到底
//      digitalWrite(LED_BUILTIN, LOW);/
      digitalWrite(6, LOW);
      digitalWrite(7, LOW);
    }
  }

  delay(100); // Delay a little bit to improve simulation performance
}
