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

    float angle = sensor.getAngle();

    Serial.print("Current Angle: ");
    Serial.println(angle);

    delay(100);
}