#ifndef BALANCE_CONTROLLER_H
#define BALANCE_CONTROLLER_H

class BalanceController {
private:
    float Kp;   // proportional gain
    float Ki;   // integral gain
    float Kd;   // derivative gain
    float integral;
    float lastError;
    float targetAngle;
    float outputMin;
    float outputMax;
    float integralMin;
    float integralMax;

public:
    BalanceController(float Kp, float Ki, float Kd);

    void setTargetAngle(float targetAngle);
    void setGains(float Kp, float Ki, float Kd);
    void setOutputLimits(float minOutput, float maxOutput);

    float update(float currentTiltAngle, float dt);
};

#endif

