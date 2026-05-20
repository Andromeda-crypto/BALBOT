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
      outputMax(255)  {}

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

void Motor::setGains(float Kp, float Ki, float Kd) {
    this->kp = Kp;
    this->ki = Ki;
    this->kd = Kd;
}

void Motor::update(float dt) {
    /*
    Current placeholder for future encoder RPM calculation
    currentRPM will later come from encoder counts
    */

    float error =  targetRPM - currentRPM;
    integral += error * dt;

    float derivative = 0.0;

    if (dt > 0) {
        derivative = (error - lastError) / dt;
    }

    lastError = error;
    float output = kp * error + ki * integral + kd * derivative;

    // Clamp output
    if (output > outputMax) {
        output = outputMax;
    }

    if (output < outputMin) {
        output = outputMin;
    }
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
    // forward
    if (pwm > 0) {
        digitalWrite(in1Pin, HIGH);
        digitalWrite(in2Pin, LOW);

        digitalWrite(pwmPin, pwm);
    }

    // reverse
    else if (pwm < 0) {
        digitalWrite(in1Pin, LOW);
        digitalWrite(in2Pin, HIGH);

        digitalWrite(pwmPin, -pwm);
    }

    // stop
    else {
        stop();
    }
}

void Motor::stop() {
    digitalWrite(in1Pin, LOW);
    digitalWrite(in2Pin, LOW);
    digitalWrite(pwmPin, LOW);
}


    