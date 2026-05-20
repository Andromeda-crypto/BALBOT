# Pinout — BALBOT

## I2C
- MPU6050 SDA: GPIO21
- MPU6050 SCL: GPIO22

## Motor Driver — L298N

### Left Motor
- ENA / PWM: TBD
- IN1: TBD
- IN2: TBD
- Encoder A: TBD
- Encoder B: TBD

### Right Motor
- ENB / PWM: TBD
- IN3: TBD
- IN4: TBD
- Encoder A: TBD
- Encoder B: TBD

## UART
- TF-Luna TX -> ESP32 RX2 GPIO16
- TF-Luna RX -> ESP32 TX2 GPIO17

## Debug / Safety
- Buzzer: TBD
- Status LED: TBD

## Notes
- GPIO34–39 are input-only and good candidates for encoder input
- Motor driver grounds and ESP32 ground must be common
- Final pin choices must be confirmed before wiring motors