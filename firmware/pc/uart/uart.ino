void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    String receivedData = Serial.readString();
    Serial.println("ECHO: " + receivedData);
  }
}