#include <Arduino.h>
#include <math.h>
#include "BalanceController.h"

BalanceController::BalanceController(float Kp, float Ki, float Kd)
    : targetAngle(0),
      Kp(Kp), Ki(Ki), Kd(Kd),
      integral(0), lastAngle(0),
      outputMin(-255), outputMax(255),
      integralMin(-100.0), integralMax(100.0) {}

void BalanceController::setTargetAngle(float angle) {
    this->targetAngle = angle;
}

void BalanceController::setGains(float Kp, float Ki, float Kd) {
    this->Kp = Kp;
    this->Ki = Ki;
    this->Kd = Kd;
}

void BalanceController::setOutputLimits(float minOutput, float maxOutput) {
    this->outputMin = minOutput;
    this->outputMax = maxOutput;
}

void BalanceController::reset() {
    integral = 0;
    lastAngle = 0;
}

float BalanceController::update(float currentTiltAngle, float dt) {
    if (dt <= 0) return 0;

    float error = targetAngle - currentTiltAngle;

    // Derivative on measurement (not error) — avoids derivative spike on setpoint change
    float derivative = -(currentTiltAngle - lastAngle) / dt;
    lastAngle = currentTiltAngle;

    // Compute raw output before integrating (for anti-windup check)
    float rawOutput = Kp * error + Ki * integral + Kd * derivative;

    // Anti-windup: only accumulate integral when output is not saturated
    bool saturated = (rawOutput >= outputMax || rawOutput <= outputMin);
    if (!saturated) {
        integral += error * dt;
        if (integral > integralMax) integral = integralMax;
        if (integral < integralMin) integral = integralMin;
    }

    // Recompute with (possibly updated) integral
    float output = Kp * error + Ki * integral + Kd * derivative;

    // Clamp final output
    if (output > outputMax) output = outputMax;
    if (output < outputMin) output = outputMin;

    return output;
}