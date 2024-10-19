#include <SPI.h>

// DWM3000 Chip Select pin
#define DWM3000_CS_PIN 10
#define DWM3000_IRQ_PIN 2 // Digital pin for IRQ

void setup() {
  Serial.begin(115200);

  // Initialize SPI
  SPI.begin();
  pinMode(DWM3000_CS_PIN, OUTPUT);
  digitalWrite(DWM3000_CS_PIN, HIGH); // DWM3000 chip select high

  pinMode(DWM3000_IRQ_PIN, INPUT);

  // Optionally, you can perform a reset or initialization sequence here
}

// Function to write a register in DWM3000
void dwm3000WriteRegister(uint16_t address, uint32_t value) {
  digitalWrite(DWM3000_CS_PIN, LOW); // Select DWM3000
  SPI.transfer((address >> 8) & 0xFF); // Send high byte of register address
  SPI.transfer(address & 0xFF);        // Send low byte of register address
  SPI.transfer((value >> 24) & 0xFF); // Send high byte of value
  SPI.transfer((value >> 16) & 0xFF); // Send byte of value
  SPI.transfer((value >> 8) & 0xFF);  // Send byte of value
  SPI.transfer(value & 0xFF);         // Send low byte of value
  digitalWrite(DWM3000_CS_PIN, HIGH); // Deselect DWM3000
}

// Function to read a register from DWM3000
uint32_t dwm3000ReadRegister(uint16_t address) {
  digitalWrite(DWM3000_CS_PIN, LOW); // Select DWM3000
  SPI.transfer((address >> 8) & 0xFF | 0x80); // Read operation
  SPI.transfer(address & 0xFF);        // Send low byte of register address
  uint32_t value = 0;
  for (int i = 3; i >= 0; i--) {       // Read 4 bytes
    value |= (SPI.transfer(0x00) << (i * 8));
  }
  digitalWrite(DWM3000_CS_PIN, HIGH); // Deselect DWM3000
  return value;
}


void loop() {
  // Example: Writing and reading a register
  uint16_t registerAddress = 0x0000; // Replace with actual register address
  uint32_t registerValue = 0x12345678; // Example value to write

  dwm3000WriteRegister(registerAddress, registerValue);
  uint32_t readValue = dwm3000ReadRegister(registerAddress);

  Serial.print("Read Value: 0x");
  Serial.println(readValue, HEX);

  delay(1000); // Delay for demonstration
}