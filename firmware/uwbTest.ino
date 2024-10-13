#include "Decawave.h"

Decawave dw(D2, D3, D4);

void setup() {
  Serial.begin(115200);
  dw.begin();
}

void loop() {
  if (dw.update()) {
    Serial.print("Distance: ");
    Serial.print(dw.getDistance());
    Serial.println(" cm");
  }
  delay(1000);
}
