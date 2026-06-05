#ifndef MOTOR_H
#define MOTOR_H

class Motor {
public:
    Motor(int pwmPin,
          int in1Pin,
          int in2Pin,
          int encoderPinA,
          int encoderPinB,
          float encoderCountsPerRevolution = 20.0);

    void begin();

    // Closed-loop velocity command
    void setTargetRPM(float rpm);

    // Runs encoder/RPM update and optional inner PID
    void update(float dt);
    void setVelocityPIDEnabled(bool enabled);
    bool isVelocityPIDEnabled() const;

    // Telemetry
    float getRPM() const;
    float getTargetRPM() const;
    int getPWM() const;
    long getEncoderCount() const;
    void resetEncoderCount();

    // Raw motor control fallback
    void setPWM(int pwm);
    void stop();

    // Future inner-loop PID tuning
    void setGains(float kp, float ki, float kd);

private:
    int pwmPin;
    int in1Pin;
    int in2Pin;

    int encoderPinA;
    int encoderPinB;

    volatile long encoderCount;
    long lastEncoderCount;
    float encoderCountsPerRevolution;

    float targetRPM;
    float currentRPM;

    float kp;
    float ki;
    float kd;

    float integral;
    float lastError;

    int currentPWM;

    int outputMin;
    int outputMax;
    bool velocityPIDEnabled;

    void handleEncoderTick();
    static void handleEncoderInterrupt(void* arg);
};

#endif
