# Motor Architecture — BALBOT

## Purpose

The Motor subsystem is responsible for converting high-level wheel speed commands into low-level PWM motor signals.

It acts as the actuation layer between the balance controller and the physical motors.

```text
BalanceController
    ↓ target RPM
Motor inner PID loop
    ↓ PWM duty cycle
L298N motor driver
    ↓
DC motors
```

The subsystem is designed to support:
- raw PWM testing
- encoder feedback
- closed-loop wheel velocity control
- future telemetry/dashboard integration

---

# Current Status

## Implemented
- `Motor.h` interface
- `Motor.cpp` initial implementation
- PWM abstraction
- target RPM abstraction
- encoder interrupt support
- RPM estimation from encoder count deltas
- velocity PID enable gate
- output saturation support

## Not Yet Implemented
- physical motor testing
- hardware PWM output validation
- inner-loop PID tuning

---

# Responsibilities

The `Motor` class owns:
- PWM pin
- direction pins
- encoder pins
- encoder count
- target RPM
- measured RPM
- PID state
- current PWM output

External systems should interact only through the public interface.

The class internally manages:
- control state
- actuation state
- encoder tracking
- future velocity control

---

# Control Hierarchy

The overall balancing architecture is designed as:

```text
Sensor subsystem
    ↓ filtered tilt angle

BalanceController (outer loop)
    ↓ target wheel RPM

Motor subsystem (inner loop)
    ↓ PWM command

L298N driver
    ↓ motor torque

Physical robot motion
    ↓ updated tilt

Sensor subsystem
```

This forms the complete future closed-loop balancing system.

---

# Public Interface

## `begin()`

Initializes all motor-related pins.

Planned responsibilities:
- configure PWM pin as output
- configure direction pins as output
- configure encoder pins as input
- attach encoder interrupt on encoder channel A
- stop motor safely on startup

---

## `setTargetRPM(float rpm)`

Stores desired wheel speed.

Future inner PID loop will attempt to achieve this target RPM using encoder feedback.

Sign convention:
- positive RPM = one wheel direction
- negative RPM = opposite direction

Final convention will be validated during physical testing.

---

## `update(float dt)`

Runs the motor update loop.

Current role:
- update measured RPM from encoder count deltas
- run inner velocity PID only when explicitly enabled

Future responsibilities:
- validate encoder counts-per-revolution on hardware
- tune PID correction
- clamp output
- apply PWM command
- update motor state

Planned update frequency:
- approximately 200Hz

---

## `getRPM()`

Returns measured wheel RPM.

Currently:
- computed from encoder tick deltas in `update(dt)`

Future:
- refine counts-per-revolution and sign convention after hardware validation

---

## `getTargetRPM()`

Returns currently requested wheel speed.

Useful for:
- telemetry
- debugging
- dashboard graphs

---

## `getPWM()`

Returns currently applied PWM value.

Useful for:
- telemetry
- tuning
- debugging saturation behavior

---

## `getEncoderCount()`

Returns raw encoder tick count.

Useful for:
- debugging encoder ISR logic
- validating direction tracking
- low-level diagnostics

---

## `setPWM(int pwm)`

Raw PWM fallback interface.

Bypasses future velocity PID and directly commands motor output.

Purpose:
- initial hardware bringup
- direction testing
- debugging
- emergency fallback

Expected range:

```text
-255 to +255
```

Sign determines direction.

Magnitude determines duty cycle.

---

## `stop()`

Immediately disables motor motion.

Expected behavior:
- both direction pins LOW
- PWM = 0
- motor torque removed

Used for:
- startup safety
- emergency stop
- debugging

---

## `setGains(float kp, float ki, float kd)`

Future interface for tuning inner velocity PID loop.

Controls:
- responsiveness
- stability
- overshoot
- RPM tracking accuracy

---

# Internal State

## Pin Configuration

```cpp
int pwmPin;
int in1Pin;
int in2Pin;

int encoderPinA;
int encoderPinB;
```

---

## Encoder State

```cpp
volatile long encoderCount;
```

Marked `volatile` because:
- ISR modifies encoder count asynchronously
- main loop reads encoder count

---

## Velocity State

```cpp
float targetRPM;
float currentRPM;
```

Represents:
- desired wheel speed
- measured wheel speed

---

## PID State

```cpp
float kp;
float ki;
float kd;

float integral;
float lastError;
```

Used for future closed-loop wheel velocity control.

---

## Output State

```cpp
int currentPWM;

int outputMin;
int outputMax;
```

Tracks:
- applied PWM command
- actuator saturation limits

Expected default limits:

```text
-255 to +255
```

---

# Encoder Plan

Encoder interrupts:
- count wheel ticks
- determine wheel direction
- compute RPM
- feed inner PID loop

Architecture:

```text
Encoder ISR
    ↓ tick accumulation

Motor::update()
    ↓ RPM calculation

Inner PID
    ↓ PWM correction
```

---

# Planned Inner Velocity PID

Future inner-loop control structure:

```text
targetRPM - currentRPM
        ↓
    velocity PID
        ↓
      PWM
```

Purpose:
- accurate wheel speed tracking
- disturbance rejection
- stable balancing response

Current safety rule:
- velocity PID is disabled by default
- raw PWM, direction, stop behavior, encoder counts, and RPM telemetry must pass before enabling it

---

# Future Telemetry Integration

Motor subsystem will eventually expose:
- RPM
- target RPM
- PWM output
- encoder counts
- PID terms

for:
- WebSocket telemetry
- dashboard graphs
- tuning
- logging


