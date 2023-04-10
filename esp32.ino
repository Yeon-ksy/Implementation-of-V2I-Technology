#include "BluetoothSerial.h"
#define SIGNAL_PIN 33
#define LEFT_PIN 32
#define RIGHT_PIN 25
//
String device_name = "a15c151d";
// String device_name = "63bf2f34";

String serial_input;
char input_signal;

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial SerialBT;

void setup() {
  pinMode(SIGNAL_PIN, OUTPUT);
  pinMode(LEFT_PIN, OUTPUT);
  pinMode(RIGHT_PIN, OUTPUT);

  digitalWrite(SIGNAL_PIN, HIGH);
  digitalWrite(LEFT_PIN, HIGH);
  digitalWrite(RIGHT_PIN, HIGH);

  Serial.begin(115200);
  SerialBT.begin(device_name);  
}

void loop() {
  
  if (SerialBT.available()) {

    serial_input = SerialBT.readString();
    
    if (serial_input.length() > 0) {
      input_signal = serial_input[0];
    }
    Serial.println(input_signal);
    if (input_signal == 'R' || input_signal == 'Y') {
      digitalWrite(SIGNAL_PIN, LOW);
      digitalWrite(LEFT_PIN, HIGH);
      digitalWrite(RIGHT_PIN, HIGH);

    } else if (input_signal == 'G') {
      digitalWrite(SIGNAL_PIN, HIGH);
      digitalWrite(LEFT_PIN, HIGH);
      digitalWrite(RIGHT_PIN, HIGH);

    } else if (input_signal == 'L') {
      digitalWrite(SIGNAL_PIN, HIGH);
      digitalWrite(LEFT_PIN, LOW);  
      digitalWrite(RIGHT_PIN, HIGH);
      Serial.println("L");
      delay(200);
      Serial.println("End");
      digitalWrite(LEFT_PIN, HIGH);
      input_signal = 'X';
    } else if (input_signal == 'r') {
      
      digitalWrite(SIGNAL_PIN, HIGH);
      digitalWrite(LEFT_PIN, HIGH);
      digitalWrite(RIGHT_PIN, LOW);
      Serial.println("R");

      delay(200);
      digitalWrite(RIGHT_PIN, HIGH);

      input_signal = 'X';
      Serial.println("End");

    }
  }
}