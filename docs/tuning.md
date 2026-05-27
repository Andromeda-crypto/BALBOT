# BALBOT Tuning Log

## Purpose

This file tracks tuning decisions, gain changes, observed behavior, failure modes, and final values for BALBOT.

---

# Sensor Filter Settings

## Complementary Filter

Current filter:

```text
angle = 0.98 * (angle + gyroRate * dt) + 0.02 * accelAngle
```

## Notes

- Gyro bias calibration runs at boot
- Sensor must remain still during calibration
- Current sensor estimation validated with:
  - stationary tests
  - slow tilt tests
  - rapid disturbance tests
  - long-duration runtime tests

---

# Balance PID Tuning

## Current Status

Not physically tested yet.

## Initial Software Validation

- Kp = 1.0
- Ki = 0.0
- Kd = 0.0
- Output limits implemented
- Anti-windup implemented
- Derivative-on-measurement implemented
- Manual tilt tests completed successfully

Observed behavior:
- larger tilt errors produced larger outputs
- opposite tilt directions produced opposite outputs
- outputs approached zero near target angle
- subsystem integration functioning correctly

---

## Balance PID Test Log

| Attempt | Kp | Ki | Kd | Observation | Result |
|---|---:|---:|---:|---|---|
| 1 | 1.0 | 0.0 | 0.0 | Software-only manual tilt validation | PASS |

---

# Motor PID Tuning

## Current Status

Not physically tested yet.

The Motor subsystem currently exists as:
- architecture
- interfaces
- placeholder PID
- PWM abstraction
- encoder placeholders

Physical validation pending motor arrival.

---

## Motor PID Test Log

| Attempt | Kp | Ki | Kd | Target RPM | Observation | Result |
|---|---:|---:|---:|---:|---|---|

---

# Safety System

## Startup Safety Gate

Before enabling balancing control:

```text
abs(currentTilt - targetAngle) < 20°
```

If outside safe range:
- controller reset triggered
- target RPM forced to zero
- motors stopped
- balancing disabled

Purpose:
- prevent violent startup behavior
- avoid uncontrolled launch conditions
- improve debugging safety

---

# Failure Modes

| Date | Failure | Suspected Cause | Fix | Result |
|---|---|---|---|---|
| TBD | TBD | TBD | TBD | TBD |

---

# Runtime Architecture Notes

Current software pipeline:

```text
MPU6050
    ↓
Sensor::update()
    ↓
Filtered tilt angle
    ↓
BalanceController::update()
    ↓
Control output
    ↓
Motor::setTargetRPM()
```

Validated:
- subsystem communication
- timing flow
- PID response
- software integration

---

# Planned Future Tuning

## Balance Controller
Future tuning goals:
- fast disturbance rejection
- minimal oscillation
- stable upright hold
- controlled recovery behavior

---

## Motor Controller
Future tuning goals:
- accurate RPM tracking
- low overshoot
- fast wheel response
- stable velocity estimation

---

# Final Gains

## Sensor

| Parameter | Value |
|---|---|
| Complementary Filter Alpha | 0.98 |

---

## Balance Controller

| Parameter | Value |
|---|---|
| Kp | TBD |
| Ki | TBD |
| Kd | TBD |

---

## Motor Controller

| Parameter | Value |
|---|---|
| Kp | TBD |
| Ki | TBD |
| Kd | TBD |

---

# Notes

BALBOT is being developed incrementally.

Each subsystem is:
1. implemented
2. isolated
3. tested
4. validated
5. integrated

before moving to the next layer.

This minimizes:
- debugging complexity
- hidden coupling
- unstable integrations
- uncontrolled hardware behavior