#ifndef MOTOR_H
#define MOTOR_H

class Motor {
public:
    Motor(int pwmPin,
          int in1Pin,
          int in2Pin,
          int encoderPinA,
          int encoderPinB);

    void begin();

    // Closed-loop velocity command
    void setTargetRPM(float rpm);

    // Runs motor control update, eventually inner PID
    void update(float dt);

    // Telemetry
    float getRPM() const;
    float getTargetRPM() const;
    int getPWM() const;
    long getEncoderCount() const;

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
};

#endif