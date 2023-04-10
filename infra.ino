#include <stdlib.h>
#include <SPI.h>
#include <MFRC522.h>
#include "BluetoothSerial.h"
#include <ESP32Servo.h>

#define LEFT_SIGN_PIN 4
#define STOP_SIGN_PIN 22
#define RIGHT_SIGN_PIN 21

#define RST 34
#define MISO 22
#define MOSI 23
#define SCK 18
#define SS 5

#define TRIG_PIN 32
#define ECHO_PIN 33
#define FREQ 400
#define DISTANCE 10.0

Servo Left_Sign;
Servo Stop_Sign;
Servo Right_Sign;

int tsignal = 0;
char singals[2]{ 'L', 'r' };
// char singals[2]{ 'r', 'L' };

// char singals[2]{ 'r', 'r' };

int threshold = 1000;
int count = 0;

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial SerialBT;

byte nuidPICC[4] = { 0, 0, 0, 0 };

MFRC522 rfid(SS, RST);
MFRC522::MIFARE_Key key;

String slaveName = "slave";  // Change this to reflect the real name of your slave BT device
String myName = "master";

float getDistance() {
  float duration, distance;
  digitalWrite(TRIG_PIN, HIGH);
  delay(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  distance = ((float)(340 * duration) / 1000 / 10) / 2;
  Serial.print("distance : ");
  Serial.print(distance);
  Serial.println("cm");
  return distance;
}

void signalOn(int count) {
  if (count % FREQ == 0) {
    tsignal = (tsignal + 1) % 2;

    Left_Sign.write(0);
    Right_Sign.write(0);

    if (tsignal == 0) {
      Right_Sign.write(90);
    } else if (tsignal == 1) {
      Left_Sign.write(90);
    }
  }
}

void tryConnect(String carId) {
  if (SerialBT.connect(carId)) { 
    Serial.println("Connected Successfully!");
    delay(1000);
    Stop_Sign.write(20);
  }
}

void setup() {
  Serial.begin(115200);
  SerialBT.begin(myName, true);
  SPI.begin();
  rfid.PCD_Init();

  Left_Sign.attach(LEFT_SIGN_PIN);
  Stop_Sign.attach(STOP_SIGN_PIN);
  Right_Sign.attach(RIGHT_SIGN_PIN);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

    Stop_Sign.write(110);

  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
  // rfid.PCD_DumpVersionToSerial();

  delay(10);
}

void loop() {
  signalOn(count);
  if (SerialBT.connected() && getDistance() < DISTANCE) {
    SerialBT.write(singals[tsignal]);
      Serial.print(singals[tsignal]);
    delay(50);

    SerialBT.disconnect();
    Serial.println("Disconnected Successfully!");

    for (byte i = 0; i < 4; i++) {
      nuidPICC[i] = 0;
    }
    Stop_Sign.write(110);
  }

  count++;
  count %= FREQ;

  if (!rfid.PICC_IsNewCardPresent())
    return;
  // Verify if the NUID has been readed
  if (!rfid.PICC_ReadCardSerial())
    return;

  if (rfid.uid.uidByte[0] != nuidPICC[0] || rfid.uid.uidByte[1] != nuidPICC[1] || rfid.uid.uidByte[2] != nuidPICC[2] || rfid.uid.uidByte[3] != nuidPICC[3]) {
    String rfid_;

    for (byte i = 0; i < 4; i++) {
      nuidPICC[i] = rfid.uid.uidByte[i];
      rfid_ += String(rfid.uid.uidByte[i], HEX);
    }

  Serial.println(rfid_);
  tryConnect(rfid_);
  } else Serial.println(F("Card read previously."));

  rfid.PICC_HaltA();
}
