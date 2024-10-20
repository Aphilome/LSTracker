#include "LoRa_E220.h"
 
SoftwareSerial mySerial(4, 5);
LoRa_E220 e220ttl(&mySerial, 3, 7, 6); // AUX M0 M1

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

void setup() {
  Serial.begin(9600);
  delay(500);
 
  Serial.println("Pc lora ready to receive");
  // Startup all pins and UARTD
  e220ttl.begin();
}
 
void loop() {
  if (e220ttl.available() > 1) {
      // read the String message
    ResponseStructContainer rsc = e220ttl.receiveMessage(sizeof(dronInfo));
    dronInfo dron = *(dronInfo*) rsc.data;

    Serial.print("uwbLat: ");
    Serial.println(dron.uwbLat);
    Serial.print("uwbLon: ");
    Serial.println(dron.uwbLon);
    Serial.print("uwbAlt: ");
    Serial.println(dron.uwbAlt);
    
    Serial.println();
  }
}