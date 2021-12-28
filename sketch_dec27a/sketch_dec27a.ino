// C++ code
//
#include <ESP32Servo.h>

Servo myservo;  // 定义Servo对象来控制
int pos = 0;    // 角度存储变量
int o_or_c = HIGH;

void setup()
{
  //  pinMode(LED_BUILTIN, OUTPUT);/
  myservo.attach(14);  // 控制线连接数字9
  pinMode(35, INPUT);
  pinMode(2, OUTPUT);
}

void loop()
{
  if (digitalRead(35) != o_or_c ) {
    o_or_c = digitalRead(35) ;
    if (digitalRead(35) == HIGH) { // 有水
      digitalWrite(2, HIGH);
      close_window();

    }
    else { // 无水
      digitalWrite(2, LOW);
      open_window();
    }
    delay(100); // Delay a little bit to improve simulation performance
  }
}

void open_window() {
  for (pos = 10; pos <= 125; pos ++) {
    // in steps of 1 degree
    myservo.write(pos);
    delay(5);
  }
}

void close_window() {
  for (pos = 120; pos >= 10; pos --) {
    myservo.write(pos);
    delay(5);
  }
}
