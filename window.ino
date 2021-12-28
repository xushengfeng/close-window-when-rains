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

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <ESP32Servo.h>

#define LED_BUILTIN 2   // Set the GPIO pin where you connected your test LED or comment this line out if your dev board has a built-in LED

// Set these to your desired credentials.
const char *ssid = "AUTO-WINDOW";
const char *password = "";

WiFiServer server(80);


Servo myservo;  // 定义Servo对象来控制
int pos = 0;    // 角度存储变量
int o_or_c = HIGH;


void setup() {
  // 舵机
  myservo.attach(14);
  // 雨滴
  pinMode(35, INPUT);
  // LED
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");

  // WIFI AP
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();

  Serial.println("Server started");
}

void loop() {
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("<head><meta charset='utf-8'><meta http-equiv='refresh' content='2;url=/'><title></title></head>");
            client.print("<style>.main {display: flex;height: 100%;flex-direction: column;justify-content: center;align-items: center;}p{font-size: 3rem;}.b_f {display: flex;justify-content: center;align-items: center;}a {text-decoration: none;color: #000}.b {margin: 16px;padding: 16px;background-color: #ddd;border-radius: 8px;font-size: 2rem;}</style>");
            client.print("<div class='main'><p>现在外面 <span id='rain'>");
            if (digitalRead(35) == HIGH) {
              client.print("有");
            } else {
              client.print("无");
            }
            client.print("</span>雨</p><div class='b_f'><a href='/H'><div class='b'>开窗</div></a><a href='/L'><div class='b'>关窗</div></a></div></div>");


            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H")) {
          open_window();
        }
        if (currentLine.endsWith("GET /L")) {
          close_window();
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }

  if (digitalRead(35) != o_or_c ) {
    o_or_c = digitalRead(35) ;
    if (digitalRead(35) == HIGH) { // 有水
      close_window();
    }
    else { // 无水
      open_window();
    }
    delay(100); // Delay a little bit to improve simulation performance
  }
}


void open_window() {
  if (myservo.read() != 125) {
    digitalWrite(LED_BUILTIN, HIGH);
    for (pos = 10; pos <= 125; pos ++) {
      myservo.write(pos);
      delay(5);
    }
  }
}

void close_window() {
  if (myservo.read() != 10) {
    digitalWrite(LED_BUILTIN, LOW);
    for (pos = 120; pos >= 10; pos --) {
      myservo.write(pos);
      delay(5);
    }
  }
}
