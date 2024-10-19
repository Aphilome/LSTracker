#ifndef DWM3000EVM_H
#define DWM3000EVM_H

#include <SPI.h>
#include "DW1000.h"

#define ANCHOR_ID 0x01  // Define anchor ID
#define TAG_ID 0x02     // Define tag ID

class DWM3000EVM {
public:
    DWM3000EVM();
    void begin(bool isTag = false);
    void sendPing();
    bool available();
    float getDistance();

private:
    void initialize();
    void waitForResponse();
    float calculateDistance(uint8_t *timeData);

    static const int SS_PIN = 10; // Chip select pin
    static const int RST_PIN = 9;  // Reset pin
    DW1000Class dwm;
};

#endif