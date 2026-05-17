#include <Arduino.h>
#include "sensor.h"

Sensor sensor;

void setup() {
    Serial.begin(115200);
    delay(1000);

    sensor.begin();
    sensor.calibrate();
}

void loop() {
    sensor.update();

    float tiltAngle = sensor.getTiltAngle();
    Serial.print("Current Angle: ");
    Serial.println(tiltAngle);

    delay(100);
}