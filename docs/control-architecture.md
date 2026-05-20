# Control Architecture — BALBOT

## Purpose

This document describes the real-time control pipeline used in BALBOT.

The system is designed as a layered robotics architecture where:
- sensing
- state estimation
- control
- actuation

are separated into independent subsystems.

This separation improves:
- modularity
- debugging
- scalability
- testing
- future expansion

---

# High-Level Runtime Flow

```text
MPU6050
    ↓ raw accel/gyro

Sensor subsystem
    ↓ complementary filter

Filtered tilt angle
    ↓

BalanceController
    ↓ PID output

Target wheel RPM
    ↓

Motor subsystem
    ↓ inner motor control

PWM command
    ↓

L298N motor driver
    ↓

DC motors
    ↓

Robot motion
    ↓

Updated tilt angle
```

This forms the complete closed-loop balancing system.

---

# Subsystem Breakdown

---

# 1. Sensor Subsystem

## Responsibilities

The Sensor subsystem is responsible for:
- reading MPU6050 data
- filtering noisy measurements
- estimating robot tilt angle
- compensating for gyro drift

## Implemented Features

### I2C MPU6050 Communication
ESP32 communicates with MPU6050 using:
- SDA → GPIO21
- SCL → GPIO22

### Accelerometer Angle Estimation

Using:

```text
atan2(accelX, accelZ)
```

to estimate tilt angle.

### Gyroscope Integration

Using:
```text
θ = θ + ωΔt
```

with real-time `micros()` timing.

### Gyro Bias Calibration

At boot:
- 500 gyro samples averaged
- gyro bias estimated
- bias subtracted during runtime

### Complementary Filter

Using:

```text
θ = 0.98(θ + ωΔt) + 0.02θ_acc
```

Purpose:
- gyro handles short-term motion
- accelerometer corrects long-term drift

## Current Status

Validated:
- stationary stability
- slow tilt response
- rapid disturbance response
- long-duration runtime stability

---

# 2. BalanceController Subsystem

## Purpose

The BalanceController converts tilt error into corrective wheel commands.

This is the outer control loop.

---

## PID Equation

Using:

```text
u = Kp*error + Ki*integral + Kd*derivative
```

where:

```text
error = targetAngle - currentTilt
```

---

## Current Features

### Configurable Gains
Supports:
- Kp
- Ki
- Kd

### Target Angle Support
Controller attempts to maintain:
```text
targetAngle
```

### Output Saturation
Controller output constrained to:

```text
-255 to +255
```

to match future motor PWM limits.

### Anti-Windup
Integral term clamped to prevent:
```text
integral windup
```

during actuator saturation.

### Timing-Aware Derivative
Derivative uses:
```text
dt
```

computed from real runtime timing.

---

## Current Testing

Validated using:
- manual tilt tests
- simulated control outputs
- sign verification
- proportional response checks

Observed:
- larger tilt errors produce larger outputs
- opposite tilt directions produce opposite outputs
- outputs approach zero near target angle

---

# 3. Motor Subsystem

## Purpose

The Motor subsystem converts:
```text
target RPM
```

into:
```text
PWM motor commands
```

This is the inner actuation/control layer.

---

## Current Features

Implemented:
- Motor class architecture
- PWM abstraction
- target RPM interface
- PID placeholders
- encoder placeholders
- output tracking

Not yet implemented:
- encoder interrupts
- RPM calculation
- physical motor control
- inner-loop PID tuning

---

# 4. Current Runtime Pipeline

Current software test flow:

```text
MPU6050
    ↓
Sensor::update()
    ↓
getTiltAngle()
    ↓
BalanceController::update()
    ↓
control output
    ↓
Motor::setTargetRPM()
```

This validates:
- subsystem integration
- control signal propagation
- software architecture correctness

before physical motors arrive.

---

# Current Testing Results

## Sensor Validation
PASS:
- stationary drift
- slow tilt response
- rapid disturbance response
- long-duration stability

## PID Validation
PASS:
- correct sign response
- proportional output scaling
- output saturation
- anti-windup behavior

## Pipeline Validation
PASS:
- tilt changes produce control output
- control output propagates into motor commands
- subsystem integration functioning correctly

---

# Design Philosophy

BALBOT is intentionally designed as:
```text
a layered robotics control system
```

not as:
```text
a monolithic Arduino sketch
```

Each subsystem owns its own:
- state
- timing
- logic
- responsibilities

This allows:
- isolated debugging
- incremental testing
- scalable development
- future dashboard integration
- easier control experimentation

---

# Current Project Status

## Completed
- sensor estimation subsystem
- complementary filtering
- gyro calibration
- PID control subsystem
- motor subsystem architecture
- software control pipeline integration

## Remaining Major Work
- physical motor bringup
- encoder ISR implementation
- RPM calculation
- inner-loop velocity PID
- balancing on hardware
- WiFi dashboard
- TF-Luna obstacle layer

---

# Next Major Phase

```text
Actuation Bringup
```

This includes:
- motor wiring
- PWM testing
- direction testing
- encoder interrupts
- RPM validation
- electrical noise debugging
- power stability testing

Only after successful actuation validation:
```text
full balancing tests
```