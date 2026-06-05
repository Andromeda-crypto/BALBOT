// Telemetry.cpp

#include "Telemetry.h"
#include <Arduino.h>

const char* Telemetry::modeToString(RobotMode mode) {
    switch(mode) {
        case MODE_STARTUP: return "STARTUP";
        case MODE_SAFE: return "SAFE";
        case MODE_ACTIVE: return "ACTIVE";
        case MODE_FAULT: return "FAULT";
        default: return "UNKNOWN";
    }
}

void Telemetry::print(const TelemetryData& data) {
    Serial.print("Time: ");
    Serial.print(data.timeMs);
    
    Serial.print("Mode: ");
    Serial.print(modeToString(data.mode));

    Serial.print(" Tilt: ");
    Serial.print(data.tiltAngle, 2);

    Serial.print(" Target: ");
    Serial.print(data.targetAngle, 2);

    Serial.print(" Error: ");
    Serial.print(data.angleError, 2);

    Serial.print(" Control: ");
    Serial.print(data.controlOutput, 2);

    Serial.print(" Left Target RPM:");
    Serial.print(data.leftTargetRPM, 2);

    Serial.print(" Right Target RPM: ");
    Serial.print(data.rightTargetRPM, 2);

    Serial.print(" Left RPM: ");
    Serial.print(data.leftRPM, 2);

    Serial.print("Right RPM:");
    Serial.print(data.rightRPM, 2);

    Serial.print(" Left PWM: ");
    Serial.print(data.leftPWM);

    Serial.print(" Right PWM: ");
    Serial.println(data.rightPWM);
    
}

