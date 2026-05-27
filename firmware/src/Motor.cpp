#include <Arduino.h>
#include "Motor.h"

Motor::Motor(int pwmPin,
             int in1Pin,
             int in2Pin,
             int encoderPinA,
             int encoderPinB)
    : pwmPin(pwmPin),
      in1Pin(in1Pin),
      in2Pin(in2Pin),
      encoderPinA(encoderPinA),
      encoderPinB(encoderPinB),
      encoderCount(0),
      targetRPM(0.0),
      currentRPM(0.0),
      kp(0.0),
      ki(0.0),
      kd(0.0),
      integral(0.0),
      lastError(0.0),
      currentPWM(0),
      outputMin(-255),
      outputMax(255)
{
}

void Motor::begin() {
    pinMode(in1Pin, OUTPUT);
    pinMode(in2Pin, OUTPUT);
    pinMode(pwmPin, OUTPUT);

    pinMode(encoderPinA, INPUT_PULLUP);
    pinMode(encoderPinB, INPUT_PULLUP);

    stop();
}

void Motor::setTargetRPM(float rpm) {
    targetRPM = rpm;
}

void Motor::setGains(float kp, float ki, float kd) {
    this->kp = kp;
    this->ki = ki;
    this->kd = kd;
}

void Motor::update(float dt) {
    if (dt <= 0.0) {
        return;
    }

    float error = targetRPM - currentRPM;
    integral += error * dt;

    float derivative = (error - lastError) / dt;
    lastError = error;

    float output = kp * error + ki * integral + kd * derivative;

    if (output > outputMax) output = outputMax;
    if (output < outputMin) output = outputMin;

    setPWM((int)output);
}

float Motor::getRPM() const {
    return currentRPM;
}

float Motor::getTargetRPM() const {
    return targetRPM;
}

int Motor::getPWM() const {
    return currentPWM;
}

long Motor::getEncoderCount() const {
    return encoderCount;
}

void Motor::setPWM(int pwm) {
    if (pwm > outputMax) pwm = outputMax;
    if (pwm < outputMin) pwm = outputMin;

    currentPWM = pwm;

    if (pwm > 0) {
        digitalWrite(in1Pin, HIGH);
        digitalWrite(in2Pin, LOW);
        analogWrite(pwmPin, pwm);
    }
    else if (pwm < 0) {
        digitalWrite(in1Pin, LOW);
        digitalWrite(in2Pin, HIGH);
        analogWrite(pwmPin, -pwm);
    }
    else {
        stop();
    }
}

void Motor::stop() {
    digitalWrite(in1Pin, LOW);
    digitalWrite(in2Pin, LOW);
    analogWrite(pwmPin, 0);

    currentPWM = 0;
}