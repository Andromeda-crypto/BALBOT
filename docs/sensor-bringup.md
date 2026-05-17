# Sensor Bringup — MPU6050

## Wiring
- SDA -> GPIO21
- SCL -> GPIO22
- VCC -> 3.3V
- GND -> GND
- AD0 -> GND

## Current Status
- ESP32 successfully communicating with MPU6050 over I2C
- Device detected and initialized correctly
- Raw accelerometer and gyroscope values readable
- Accelerometer-only angle computation implemented
- Serial monitor output stable

## Angle Formula
Currently using:

atan2(accelX, accelZ) * 180 / PI

## Observations
- Large angle swings observed during aggressive physical movement
- Stable readings observed when sensor stationary
- Sensor orientation relative to future robot chassis not finalized yet
- No complementary filter implemented yet

## Next Steps
- Controlled axis testing
- Define robot pitch axis
- Define upright reference orientation
- Implement gyro integration
- Implement complementary filter