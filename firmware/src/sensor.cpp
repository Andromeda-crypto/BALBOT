
#include <Arduino.h>
#include <math.h>
#include "sensor.h"
#include "Wire.h"


Sensor::Sensor(){
    angle = 0.0;

}

/*
Implement:

I2C
MPU reads
filter logic

*/

void Sensor::begin(){
    Wire.begin(21,22);
    Wire.beginTransmission(MPU_ADDR); // MPU address
    Wire.write(0x6B); // Power management register
    Wire.write(0x00); // Waking up MPU 
    Wire.endTransmission();
    Serial.println("Sensor begin: MPU initialized");
}

void Sensor::calibrate(){
    Serial.println("Sensor calibrate: placeholder");
}

void Sensor::update() {
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x3B);
    Wire.endTransmission(false);

    Wire.requestFrom(MPU_ADDR, 14);

    if (Wire.available() == 14) {
        int16_t rawAccelX = Wire.read() << 8 | Wire.read();
        int16_t rawAccelY = Wire.read() << 8 | Wire.read();
        int16_t rawAccelZ = Wire.read() << 8 | Wire.read();

        Wire.read();
        Wire.read();

        int16_t rawGyroX = Wire.read() << 8 | Wire.read();
        int16_t rawGyroY = Wire.read() << 8 | Wire.read();
        int16_t rawGyroZ = Wire.read() << 8 | Wire.read();

        float accelX = rawAccelX / 16384.0;
        float accelZ = rawAccelZ / 16384.0;

        float accelAngle = atan2(accelX, accelZ) * 180.0 / PI;

        angle = accelAngle;
    }
}

float Sensor::getAngle(){
    return angle;
}

