# Pinout - BALBOT

## I2C
- MPU6050 SDA: GPIO21
- MPU6050 SCL: GPIO22

## Motor Driver - L298N

### Left Motor
- ENA / PWM: GPIO25
- IN1: GPIO26
- IN2: GPIO27
- Encoder A: GPIO34
- Encoder B: GPIO35

### Right Motor
- ENB / PWM: GPIO14
- IN3: GPIO32
- IN4: GPIO33
- Encoder A: GPIO18
- Encoder B: GPIO19

## UART
- TF-Luna TX -> ESP32 RX2 GPIO16
- TF-Luna RX -> ESP32 TX2 GPIO17

## Debug / Safety
- Buzzer: TBD
- Status LED: TBD

## Notes
- GPIO34 and GPIO35 are input-only and require external pullups if the encoder outputs are open-drain/open-collector.
- Current firmware assumes 20 encoder counts per wheel revolution during bringup; update `ENCODER_COUNTS_PER_REVOLUTION` after confirming the motor/encoder specification.
- Motor driver grounds and ESP32 ground must be common.
- Direction convention must be confirmed during raw PWM forward/reverse tests before enabling closed-loop control.
