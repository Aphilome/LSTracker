#include "DWM3000EVM.h"

DWM3000EVM::DWM3000EVM() {}

void DWM3000EVM::begin(bool isTag) {
    pinMode(SS_PIN, OUTPUT);
    pinMode(RST_PIN, OUTPUT);
    digitalWrite(RST_PIN, LOW);
    delay(10);
    digitalWrite(RST_PIN, HIGH);
    delay(10);

    dwm.setup(SS_PIN); // Set up SPI communication
    initialize();

    if (!isTag) {
        dwm.setRole(DW1000::ANCHOR);
    } else {
        dwm.setRole(DW1000::TAG);
    }
}

void DWM3000EVM::initialize() {
    dwm.start();
}

void DWM3000EVM::sendPing() {
    dwm.sendPing(ANCHOR_ID);
}

bool DWM3000EVM::available() {
    return dwm.hasReceivedData();
}

float DWM3000EVM::getDistance() {
    uint8_t timeData[8];
    dwm.getResponse(timeData);
    return calculateDistance(timeData);
}

float DWM3000EVM::calculateDistance(uint8_t *timeData) {
    // Convert raw time data to distance
    // Placeholder calculation - implement actual time to distance conversion logic
    return (float)(*(uint32_t *)timeData) * 0.001; // Example conversion
}