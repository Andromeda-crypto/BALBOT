#include <Arduino.h>
#include "Sensor.h"
#include "BalanceController.h"

Sensor sensor;

BalanceController controller(1.0, 0.0, 0.0);

unsigned long lastLoopTime = 0;


void setup() {
    Serial.begin(115200);
    
    sensor.begin();
    sensor.calibrate();

    controller.setTargetAngle(166.0);
    lastLoopTime = micros();
}

void loop() {
    sensor.update();
    unsigned long now = micros();

    float dt = (now - lastLoopTime) / 1000000.0 ;//convert to seconds

    lastLoopTime = now;
    float tilt = sensor.getTiltAngle();
    float control = controller.update(tilt,dt);

    Serial.print("Tilt: ");
    Serial.print(tilt);

    Serial.print("Control: ");
    Serial.println(control);

    delay(100);

}