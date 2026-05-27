#pragma once

class BalanceController {
public:
    BalanceController(float Kp, float Ki, float Kd);

    void setTargetAngle(float angle);
    void setGains(float Kp, float Ki, float Kd);
    void setOutputLimits(float minOutput, float maxOutput);
    void reset();

    float update(float currentTiltAngle, float dt);

private:
    float targetAngle;

    float Kp, Ki, Kd;

    float integral;
    float lastAngle;        // used for derivative on measurement

    float outputMin, outputMax;
    float integralMin, integralMax;
};