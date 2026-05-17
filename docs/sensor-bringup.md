# Sensor Bringup — MPU6050

## Wiring
- SDA -> GPIO21
- SCL -> GPIO22
- VCC -> 3.3V
- GND -> GND
- AD0 -> GND

---

## Current Status
- ESP32 successfully communicating with MPU6050 over I2C
- Device initialization confirmed
- Raw accelerometer and gyroscope values readable
- Accelerometer-only angle estimation implemented and tested
- Gyroscope integration implemented using `micros()` timing
- Boot-time gyro bias calibration implemented
- Complementary filter implemented successfully
- Stable real-time orientation estimation achieved
- Serial telemetry pipeline operational

---

## Sensor Fusion Pipeline

### Accelerometer Angle
Using:

atan2(accelX, accelZ) * 180 / PI

Provides:
- long-term orientation reference
- stable absolute tilt estimate
- noisy readings during motion

### Gyroscope Integration

θ = θ + ωΔt

Using:
- `micros()` for precise timing
- gyro bias compensation during runtime

Provides:
- smooth short-term motion tracking
- responsive tilt estimation
- drift accumulation without correction

### Complementary Filter

θ = 0.98(θ + ωΔt) + 0.02θ_acc

Purpose:
- gyro handles short-term motion
- accelerometer corrects long-term drift

Current alpha:
- gyro weight: 0.98
- accel weight: 0.02

---

## Calibration
Boot-time gyro calibration implemented.

Process:
- averages 500 gyro samples while sensor remains stationary
- computes gyro X-axis bias
- subtracts bias continuously during runtime

Observed gyro bias:
- approximately -337 raw units

Result:
- stationary drift reduced dramatically

---

## Observations
- Accelerometer-only estimation was stable but noisy during movement
- Gyro-only estimation tracked motion smoothly but drifted significantly over time
- Complementary filter combines both successfully
- Current orientation estimate stable within approximately ±0.2°
- Sensor orientation relative to final robot chassis not finalized yet
- Current resting angle approximately 166° due to temporary sensor orientation

---

## Remaining Work
- Controlled rapid-tilt stress testing
- Define final robot pitch axis
- Define upright reference orientation
- Normalize upright robot posture to 0°
- Long-duration drift testing
- Vibration sensitivity testing
- Transition toward control-loop integration

---

## Stationary Drift Test — Complementary Filter

Test setup:
- MPU6050 placed stationary on table
- Serial output sampled during stationary run
- Complementary filter alpha = 0.98
- Gyro bias calibration ran at boot

Observed:
- Initial angle started around 171.84°
- Angle gradually settled near 170°
- After settling, readings stayed approximately between 169.6° and 170.2°
- Stable variation after settling was roughly ±0.3°

Result:
- Stationary stability after settling: PASS
- Initial boot settling behavior observed and should be considered before PID use

---

## Slow Tilt Response Test

Test: 
- Sensor slowly tilted forward/backward by hand
- Sensor returned to original orientation after each motion

Observed: 
- Angle changed smoothly during motion
- No random spikes or instabilitgy observed
- Angle returned close to original settled value
- No noticeable runaway drif after motion

Result:
PASS

---

## Rapid Tilt / Disturbance Test

Test:
- Sensor was allowed to settle first
- Sensor was sharply tilted in one direction
- Motion was stopped abruptly
- Test repeated multiple times within safe movement limits due to jumper-wire connections

Observed:
- Angle responded quickly to sharp motion
- No random jumps or unstable spikes observed
- After abrupt stops, the filter took a short time to settle
- Angle returned near the original settled value after each attempt
- No runaway drift observed after repeated disturbances

Result:
PASS

Notes:
- Movement range was limited because the MPU6050 is still connected with jumper wires
- A more aggressive vibration/disturbance test should be repeated after the sensor is mounted securely on the chassis