#ifndef SENSOR_H
#define SENSOR_H

#define MPU_ADDR 0x68

class Sensor {
private:
    float angle;
    unsigned long lastUpdateTime;
    float gyroBiasX;
    float accelX;
    float accelY;
    float accelZ;

    float gyroX;
    float gyroY;
    float gyroZ;

    bool filterInitialized;

public:
    Sensor();

    void begin();
    void calibrate();
    void update();

    float getAngle();
};

#endif