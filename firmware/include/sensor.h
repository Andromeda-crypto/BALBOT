#ifndef SENSOR_H
#define SENSOR_H

#define MPU_ADDR 0x68

class Sensor {
private:
    float angle;
    unsigned long lastUpdateTime;
    float gyroBiasx;

public:
    Sensor();

    void begin();
    void calibrate();
    void update();

    float getAngle();
};

#endif