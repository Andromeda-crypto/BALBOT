#include <Arduino.h>
#include <math.h>
#include "BalanceController.h"

BalanceController::BalanceController(float Kp, float Ki, float Kd) : targetAngle(0), Kp(Kp), Ki(Ki), Kd(Kd), integral(0), lastError(0), outputMin(-255), outputMax(255), 
    integralMin(-100.0), integralMax(100.0) {}

void BalanceController::setTargetAngle(float targetAngle) {
    this->targetAngle = targetAngle;
}

void BalanceController::setGains(float Kp, float Ki, float Kd) {
    this->Kp = Kp;
    this->Ki = Ki;
    this->Kd = Kd;
}

void BalanceController::setOutputLimits(float minOutput, float maxOutput){
    this->outputMin = minOutput;
    this->outputMax = maxOutput;
}
float BalanceController::update(float currentTiltAngle, float dt) {

    if (dt <=0) return 0; // prevent division by zero
    float error = targetAngle - currentTiltAngle;
    integral += error * dt;
    if (integral > integralMax) integral = integralMax;
    if (integral < integralMin) integral = integralMin;
    float derivative = (error - lastError) / dt;
    lastError = error;

    float output = Kp*error + Ki*integral + Kd*derivative;
    // Constrain output to limits
    if (output > outputMax) {
        output = outputMax;
    }
    if (output < outputMin) {
        output = outputMin;
    }
    return output;
} 
