#include <stdlib.h>
#include <SPI.h>
#include <MFRC522.h>
#include "BluetoothSerial.h"

#define LED_R 25
#define LED_G 26
#define LED_Y 27
#define LED_CONNECT 32
#define RST 34
#define MISO 19
#define MOSI 23
#define SCK 18
#define SDA 5
#define FREQ 200

int tsignal = 2;
char singals[3] {'R', 'G', 'Y'};

int count = 0;
bool isfirst = false;

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial SerialBT;
MFRC522 rfid(SS, RST);
MFRC522::MIFARE_Key key; 
byte nuidPICC[4];

String slaveName = "slave"; // Change this to reflect the real name of your slave BT device
String myName = "master";

void signalOn(int count) {
  if(count%FREQ == 0) {
    tsignal = (tsignal+1)%3;
    for (int pin=25; pin<28; pin++) {
      digitalWrite(pin, LOW);
    }
    digitalWrite(25+tsignal, HIGH);

    SerialBT.write(singals[tsignal]);
  }
  
}

void tryConnect() {
  if(SerialBT.connect(slaveName)) {
    Serial.println("Connected Successfully!");
    isfirst = true;
    digitalWrite(LED_CONNECT, HIGH);
    SerialBT.write(singals[tsignal]);
    // SerialBT.write('R');
  }
}

void setup() {
  for (int pin=25; pin<28; pin++) {
    pinMode(pin, OUTPUT);
  }
  pinMode(LED_CONNECT, OUTPUT);
  Serial.begin(115200);
  SerialBT.begin(myName, true);
  SPI.begin();
  rfid.PCD_Init();
  delay(10);
}

void loop() {
  signalOn(count);
  if(rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial() && (rfid.uid.uidByte[0] != nuidPICC[0] || rfid.uid.uidByte[1] != nuidPICC[1] || rfid.uid.uidByte[2] != nuidPICC[2] || rfid.uid.uidByte[3] != nuidPICC[3] )) {
    String uidStr = "";
    for (byte i = 0; i < 4; i++) {
      uidStr += String(rfid.uid.uidByte[i], HEX);
    }
    slaveName = uidStr;    
    Serial.println(slaveName);
    tryConnect();  
    for (byte i = 0; i < 4; i++) {
      nuidPICC[i] = rfid.uid.uidByte[i];
    }
  }
 
  if(SerialBT.connected()) {
    if(isfirst==true) {
      delay(120);
      isfirst = false;
    }
    if (singals[tsignal]=='G') {
      SerialBT.write(singals[tsignal]);
      isfirst = true;
      SerialBT.disconnect();
      Serial.println("Disconnected Successfully!");
    }
    for (byte i = 0; i < 4; i++) {
      nuidPICC[i] = 0;
    }
    digitalWrite(LED_CONNECT, LOW);
  }
  count++;
  count %= FREQ;
  delay(10);
}