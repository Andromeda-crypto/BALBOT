
#include <Arduino.h>
#include <math.h>
#include "sensor.h"
#include "Wire.h"


Sensor::Sensor(){
    angle = 0.0;
    lastUpdateTime = 0;
    gyroBiasX = 0.0;
    filterInitialized = false;
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
    lastUpdateTime = micros();
    Serial.println("Sensor begin: MPU initialized");
}

void Sensor::calibrate(){
   Serial.println("Caibrating gyro .....  Keep sensor still.");
   long sum = 0;
   for (int i=0; i < 500;i++){
        Wire.beginTransmission(MPU_ADDR);
        Wire.write(0x43);
        Wire.endTransmission(false);

        Wire.requestFrom(MPU_ADDR, 2);

        if (Wire.available() == 2) {
            int16_t rawGyroX = Wire.read() << 8 | Wire.read();
            sum+= rawGyroX;
        }

        delay(3);
   }

   gyroBiasX = sum / 500.0;
   angle = 0.0;
   lastUpdateTime = micros();
   Serial.print("Gyro bias X: ");
   Serial.println(gyroBiasX);
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

        unsigned long now = micros();
        float dt = (now - lastUpdateTime) / 1000000.0;
        lastUpdateTime = now;

        accelX = rawAccelX / 16384.0;
        accelY = rawAccelY / 16384.0;
        accelZ = rawAccelZ / 16384.0;

        float accelAngle = atan2(accelX, accelZ) * 180.0 / PI;

        gyroX = (rawGyroX - gyroBiasX) / 131.0;
        gyroY = rawGyroY / 131.0;
        gyroZ = rawGyroZ / 131.0;

        if (!filterInitialized) {
            angle = accelAngle;
            filterInitialized = true;
            lastUpdateTime = micros();
            return;
        }

        angle = 0.98 * (angle + gyroX * dt) + 0.02 * accelAngle;
    }
}

float Sensor::getAngle(){
    return angle;
}

