/*
  WiFiAccessPoint.ino creates a WiFi access point and provides a web server on it.

  Steps:
  1. Connect to the access point "yourAp"
  2. Point your web browser to http://192.168.4.1/H to turn the LED on or http://192.168.4.1/L to turn it off
     OR
     Run raw TCP "GET /H" and "GET /L" on PuTTY terminal with 192.168.4.1 as IP address and 80 as port

  Created for arduino-esp32 on 04 July, 2018
  by Elochukwu Ifediora (fedy0)
*/

#include <ESP32Servo.h>

#define LED_BUILTIN 2   // Set the GPIO pin where you connected your test LED or comment this line out if your dev board has a built-in LED



Servo myservo;  // 定义Servo对象来控制
int pos = 0;    // 角度存储变量
int o_or_c = HIGH;


void setup() {
  myservo.attach(14);  // 控制线连接数字9
  pinMode(35, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");

  // You can remove the password parameter if you want the AP to be open.
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();

  Serial.println("Server started");
}

void loop() {
  

  if (digitalRead(35) != o_or_c ) {
    o_or_c = digitalRead(35) ;
    if (digitalRead(35) == HIGH) { // 有水
      close_window();
    Serial.println("有水");

    }
    else { // 无水
      open_window();
    Serial.println("无水");
    }
    delay(100); // Delay a little bit to improve simulation performance
  }
}


void open_window() {
  digitalWrite(LED_BUILTIN, HIGH);
  for (pos = 10; pos <= 125; pos ++) {
    myservo.write(pos);
    delay(5);
  }
}

void close_window() {
  digitalWrite(LED_BUILTIN, LOW);
  for (pos = 120; pos >= 10; pos --) {
    myservo.write(pos);
    delay(5);
  }
}
