/*********
  Modified from the examples of the Arduino LoRa library
  More resources: https://randomnerdtutorials.com
*********/

#include <SPI.h>
#include <LoRa.h>

//define the pins used by the transceiver module
#define ss 5
#define rst 14
#define dio0 2

#define PIN_RED    25 // 
#define PIN_GREEN  26 // 
#define PIN_BLUE   27 //

void setup() {
  //initialize Serial Monitor
  Serial.begin(115200);
  pinMode(PIN_RED,   OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE,  OUTPUT); 
  while (!Serial);
  Serial.println("LoRa Receiver");

  //setup LoRa transceiver module
  LoRa.setPins(ss, rst, dio0);
  
  //replace the LoRa.begin(---E-) argument with your location's frequency 
  //433E6 for Asia
  //866E6 for Europe
  //915E6 for North America
  while (!LoRa.begin(915E6)) {
    Serial.println(".");
    delay(500);
  }
   // Change sync word (0xF3) to match the receiver
  // The sync word assures you don't get LoRa messages from other LoRa transceivers
  // ranges from 0-0xFF
  LoRa.setSyncWord(0xF3);
  Serial.println("LoRa Initializing OK!");
}

void loop() {
    analogWrite(PIN_RED,   255);
    analogWrite(PIN_GREEN, 0);
    analogWrite(PIN_BLUE,  0);
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    analogWrite(PIN_RED,   0);
    analogWrite(PIN_GREEN, 255);
    analogWrite(PIN_BLUE,  255);
    // received a packet
    Serial.print("Received packet '");
    delay(1000);
    // read packet
    while (LoRa.available()) {
      String LoRaData = LoRa.readString();
      Serial.print(LoRaData); 
    }

    // print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
  }
}