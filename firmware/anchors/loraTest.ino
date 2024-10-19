// With FIXED SENDER configuration
#define DESTINATION_ADDL 3
#define ROOM "Kitchen"
 
// With FIXED RECEIVER configuration
//#define DESTINATION_ADDL 2
//#define ROOM "Bath"
 
// If you want use RSSI uncomment //#define ENABLE_RSSI true
// and use relative configuration with RSSI enabled
// #define ENABLE_RSSI true
 
#include "Arduino.h"
#include "LoRa_E220.h"
 
// ---------- esp8266 pins --------------
//LoRa_E220 e220ttl(RX, TX, AUX, M0, M1);  // Arduino RX <-- e220 TX, Arduino TX --> e220 RX
//LoRa_E220 e220ttl(D3, D4, D5, D7, D6); // Arduino RX <-- e220 TX, Arduino TX --> e220 RX AUX M0 M1
//LoRa_E220 e220ttl(D2, D3); // Config without connect AUX and M0 M1
 
//#include <SoftwareSerial.h>
//SoftwareSerial mySerial(D2, D3); // Arduino RX <-- e220 TX, Arduino TX --> e220 RX
//LoRa_E220 e220ttl(&mySerial, D5, D7, D6); // AUX M0 M1
// -------------------------------------
 
// ---------- Arduino pins --------------
//LoRa_E220 e220ttl(4, 5, 3, 7, 6); // Arduino RX <-- e220 TX, Arduino TX --> e220 RX AUX M0 M1
//LoRa_E220 e220ttl(4, 5); // Config without connect AUX and M0 M1
 
//#include <SoftwareSerial.h>
//SoftwareSerial mySerial(4, 5); // Arduino RX <-- e220 TX, Arduino TX --> e220 RX
//LoRa_E220 e220ttl(&mySerial, 3, 7, 6); // AUX M0 M1
// -------------------------------------
 
// ------------- Arduino Nano 33 IoT -------------
// LoRa_E220 e220ttl(&Serial1, 2, 4, 6); //  RX AUX M0 M1
// -------------------------------------------------
 
// ------------- Arduino MKR WiFi 1010 -------------
// LoRa_E220 e220ttl(&Serial1, 0, 2, 4); //  RX AUX M0 M1
// -------------------------------------------------
 
// ---------- esp32 pins --------------
 LoRa_E220 e220ttl(&Serial2, 15, 21, 19); //  RX AUX M0 M1
 
//LoRa_E220 e220ttl(&Serial2, 22, 4, 18, 21, 19, UART_BPS_RATE_9600); //  esp32 RX <-- e220 TX, esp32 TX --> e220 RX AUX M0 M1
// -------------------------------------
 
struct Message {
    char type[5];
    char message[8];
    float temperature;
};
 
void setup() {
  Serial.begin(9600);
  delay(500);
 
  // Startup all pins and UART
  e220ttl.begin();
 
  Serial.println("Hi, I'm going to send message!");
 
  struct    Message message = {"TEMP", ROOM, 19.2};
 
  // Send message
  ResponseStatus rs = e220ttl.sendFixedMessage(0, DESTINATION_ADDL, 23, &message, sizeof(Message));
  // Check If there is some problem of succesfully send
  Serial.println(rs.getResponseDescription());
}
 
void loop() {
    // If something available
  if (e220ttl.available()>1) {
      // read the String message
#ifdef ENABLE_RSSI
        ResponseStructContainer rsc = e220ttl.receiveMessageRSSI(sizeof(Message));
#else
        ResponseStructContainer rsc = e220ttl.receiveMessage(sizeof(Message));
#endif
 
    // Is something goes wrong print error
    if (rsc.status.code!=1){
        Serial.println(rsc.status.getResponseDescription());
    }else{
        // Print the data received
        Serial.println(rsc.status.getResponseDescription());
        struct Message message = *(Message*) rsc.data;
        Serial.println(message.type);
        Serial.println(message.message);
        Serial.println(message.temperature);
 
#ifdef ENABLE_RSSI
        Serial.print("RSSI: "); Serial.println(rsc.rssi, DEC);
#endif
    }
  }
  if (Serial.available()) {
      struct Message message = { "TEMP", ROOM, 0 };
      message.temperature = Serial.parseFloat();
 
      // Send message
      ResponseStatus rs = e220ttl.sendFixedMessage(0, DESTINATION_ADDL, 23, &message, sizeof(Message));
      // Check If there is some problem of succesfully send
      Serial.println(rs.getResponseDescription());
  }
}
