#include <Arduino.h>
#include "Sensor.h"
#include "BalanceController.h"
#include "Motor.h"

Sensor sensor;

BalanceController controller(1.0, 0.0, 0.0);

unsigned long lastLoopTime = 0;

Motor leftMotor(25, 26, 27, 34, 35);
Motor rightMotor(14, 32, 33, 36, 39);



void setup() {
    Serial.begin(115200);
    
    sensor.begin();
    sensor.calibrate();

    controller.setTargetAngle(166.0);
    lastLoopTime = micros();
    leftMotor.begin();
    rightMotor.begin();
}

void loop() {
    sensor.update();
    unsigned long now = micros();

    float dt = (now - lastLoopTime) / 1000000.0 ;//convert to seconds

    lastLoopTime = now;
    float tilt = sensor.getTiltAngle();
    float control = controller.update(tilt,dt);

    leftMotor.setTargetRPM(control);
    rightMotor.setTargetRPM(control);

    Serial.print("Tilt: ");
    Serial.print(tilt);

    Serial.print("Control: ");
    Serial.println(control);

    Serial.print("left RPM: ");
    Serial.println (leftMotor.getRPM());

    Serial.print("Right RPM: ");
    Serial.println(rightMotor.getRPM());

    delay(100);

}