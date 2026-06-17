#include <Arduino.h>
#include "Motor.h"

constexpr int PWM_PIN = 33;
constexpr int IN1_PIN = 25;
constexpr int IN2_PIN = 26;

constexpr int ENC_A = 34;
constexpr int ENC_B = 35;

Motor testMotor(
    PWM_PIN,
    IN1_PIN,
    IN2_PIN,
    ENC_A,
    ENC_B,
    20.0f
);

unsigned long lastPrint = 0;

void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.println("Single Motor Bringup");

    testMotor.begin();
    testMotor.setVelocityPIDEnabled(false);

    Serial.println("Starting motor...");
    testMotor.setPWM(90);
}

void loop() {

    testMotor.update(0.01f);

    if (millis() - lastPrint > 500) {

        lastPrint = millis();

        Serial.print("PWM=");
        Serial.print(testMotor.getPWM());

        Serial.print(" Count=");
        Serial.print(testMotor.getEncoderCount());

        Serial.print(" RPM=");
        Serial.println(testMotor.getRPM(), 2);
    }
}