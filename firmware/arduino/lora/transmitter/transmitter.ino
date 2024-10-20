#include "LoRa_E220.h"
 
SoftwareSerial mySerial(4, 5);
LoRa_E220 e220ttl(&mySerial, 3, 7, 6); // AUX M0 M1

struct loraPc {
   int chan;
   char addH;
   char addL;
};
loraPc client = { 18, 0x21, 0x21 };

struct dronInfo {
  int uwbLat;
  int uwbLon;
  int uwbAlt;

  int gpsLat;
  int gpsLon;
  int gpsAlt;

  int gpsLatR1;
  int gpsLonR1;
  int gpsAltR1;

  int gpsLatR2;
  int gpsLonR2;
  int gpsAltR2;

  int gpsLatR3;
  int gpsLonR3;
  int gpsAltR3;
};
dronInfo currentDron = { 0,0,0, 0,0,0, 0,0,0, 0,0,0, 0,0,0 };
 
void setup() {
  Serial.begin(9600);
  delay(500);
 
  Serial.println("Dron lora ready to send");
  Serial.println(sizeof(currentDron));
 
  // Startup all pins and UARTD
  e220ttl.begin();
 
  // Send message
  //ResponseStatus rs = e220ttl.sendFixedMessage(client.addH, client.addL, client.chan, "Lora dron started");

  // Check if there is some problem of successfully send
  Serial.println(rs.getResponseDescription());
}
 
void loop() {
  static unsigned long lastSend = millis(); 
  if(millis() - lastSend > 5000){
      currentDron.uwbLat = 1;
      currentDron.uwbLon = 2;
      currentDron.uwbAlt = 3; 
      ResponseStatus rs = e220ttl.sendFixedMessage(client.addH, client.addL, client.chan, &currentDron, sizeof(currentDron));
      Serial.println(rs.getResponseDescription());
      lastSend = millis();
  }
}