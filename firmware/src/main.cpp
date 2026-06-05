#include <Arduino.h>

const int encoderA = 18;
const int encoderB = 19;

void setup() {
    Serial.begin(115200);
    pinMode(encoderA, INPUT_PULLUP);
    pinMode(encoderB, INPUT_PULLUP);

    Serial.println("Encoder Test Started.");
}

void loop() {
    Serial.print("Encoder A: ");
    Serial.print(digitalRead(encoderA));

    Serial.print("   Encoder B: ");
    Serial.println(digitalRead(encoderB));

    delay(50);
}