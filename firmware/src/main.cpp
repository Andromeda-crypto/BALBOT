#include <Arduino.h>

#include "Sensor.h"
#include "BalanceController.h"
#include "Motor.h"

// System Objects

Sensor sensor;

// keep Ki, Kd 0 for intial software gain
BalanceController controller(1.0,0.0,0.0);

// placehoider pins, update and verify before wiring and testing motors
Motor leftMotor(25,26,27,34,35);
Motor rightMotor(14,32,33,36,39);

unsigned long lastLoopTime = 0;

// Safety Setting
const float TARGET_ANGLE = 90.0;
const float SAFE_ANGLE_RANGE = 20.0; 

void setup() {
    Serial.begin(115200);
    sensor.begin();
    sensor.calibrate(); 

    controller.setTargetAngle(TARGET_ANGLE);

    leftMotor.begin();
    rightMotor.begin();

    lastLoopTime = micros();
    Serial.println("Setup complete, entering main loop.");
}

void loop() {
    sensor.update();

    unsigned long now = micros();
    float dt = (now - lastLoopTime) / 1e6; 
    lastLoopTime = now;

    float tiltAngle = sensor.getTiltAngle();

    float angleError = abs(tiltAngle - TARGET_ANGLE);

    if (angleError > SAFE_ANGLE_RANGE) {
        controller.reset();

        leftMotor.setTargetRPM(0.0);
        rightMotor.setTargetRPM(0.0);

        leftMotor.stop();
        rightMotor.stop();

        Serial.println("Unsafe angle\nMotors stopped, waiting for reset...");
        
        delay(100);
        return;}

    // Control pipeline

    float controlOutput = controller.update(tiltAngle, dt);
    leftMotor.setTargetRPM(controlOutput);
    rightMotor.setTargetRPM(controlOutput);

    leftMotor.update(dt);
    rightMotor.update(dt);

    // Telemetry
    Serial.print("Tilt: ");
    Serial.print(tiltAngle);

    Serial.print(" | Control: ");
    Serial.print(controlOutput);

    Serial.print(" | Left TargetRPM: ");
    Serial.print(leftMotor.getTargetRPM());

    Serial.print(" | Right TargetRPM: ");
    Serial.print(rightMotor.getTargetRPM());

    Serial.print(" | Left PWM: ");
    Serial.print(leftMotor.getPWM());

    Serial.print(" | Right PWM: ");
    Serial.println(rightMotor.getPWM());

    delay(100);
    }
