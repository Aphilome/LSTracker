#include "DWM3000EVM.h"

DWM3000EVM dwm;

void setup() {
    Serial.begin(115200);
    dwm.begin();
    Serial.println("Anchor Ready");
}

void loop() {
    if (dwm.available()) {
        float distance = dwm.getDistance();
        Serial.print("Distance: ");
        Serial.print(distance);
        Serial.println(" meters");
    }
    delay(500);
}