# BALBOT

A layered self-balancing robot built on the ESP32 platform using real-time sensor fusion, cascaded PID control, encoder-based wheel feedback, and a dual-core software architecture.

---

# Overview

BALBOT is a two-wheel self-balancing robot designed from first principles with a strong emphasis on:

- real-time control systems
- modular robotics architecture
- embedded systems engineering
- subsystem isolation
- telemetry and tuning infrastructure

The project is being developed incrementally:
1. Sensor estimation
2. Control architecture
3. Actuation
4. Closed-loop balancing
5. Telemetry/dashboard integration
6. Obstacle awareness

Rather than building a monolithic Arduino sketch, BALBOT is structured as a layered robotics control system with clean subsystem boundaries.

---

# System Architecture

```text
MPU6050
    ↓
Sensor Fusion
    ↓
Filtered Tilt Angle
    ↓
BalanceController (Outer PID)
    ↓
Target Wheel RPM
    ↓
Motor Controller (Inner PID)
    ↓
PWM Commands
    ↓
L298N Driver
    ↓
DC Motors
    ↓
Robot Motion
    ↓
Updated Tilt Angle
```

---

# Hardware Stack

## Core Electronics

- ESP32 DevKit V1
- MPU6050 IMU
- Dual N20 6V DC motors with magnetic encoders
- L298N dual H-bridge motor driver
- TF-Luna LiDAR
- 2S 18650 battery pack
- MP1584 buck converter
- Breadboard + jumper prototyping

---

# Software Architecture

BALBOT uses a layered software design with subsystem separation.

## Layer 1 — Sensor Subsystem

Responsibilities:
- MPU6050 communication over I2C
- accelerometer angle estimation
- gyroscope integration
- gyro bias calibration
- complementary filtering

Current status:
- fully operational
- validated against drift and disturbance testing

---

## Layer 2 — BalanceController

Outer-loop balancing controller.

Responsibilities:
- maintain target robot angle
- compute corrective wheel commands
- generate target RPM outputs

Features:
- configurable PID gains
- anti-windup protection
- output saturation
- timing-aware derivative computation

---

## Layer 3 — Motor Subsystem

Inner-loop actuation layer.

Responsibilities:
- encoder processing
- RPM calculation
- wheel velocity PID
- PWM motor output

Current status:
- architecture complete
- physical implementation pending motor arrival

---

## Layer 4 — Networking & Dashboard

Planned:
- ESPAsyncWebServer
- WebSocket telemetry
- browser-based tuning dashboard
- live graphs
- runtime PID updates

---

# Current Progress

## Completed

### Sensor Bringup
- MPU6050 communication
- stable tilt estimation
- complementary filter implementation
- gyro calibration
- disturbance testing
- long-duration drift testing

### Control Pipeline
- PID controller implementation
- output saturation
- anti-windup
- subsystem integration
- Sensor → Controller → Motor software pipeline

### Software Architecture
- modular subsystem structure
- clean class separation
- motor abstraction layer
- documentation infrastructure

---

# Repository Structure

```text
BALBOT/
│
├── firmware/
│   ├── include/
│   │   ├── Sensor.h
│   │   ├── BalanceController.h
│   │   └── Motor.h
│   │
│   ├── src/
│   │   ├── Sensor.cpp
│   │   ├── BalanceController.cpp
│   │   ├── Motor.cpp
│   │   └── main.cpp
│   │
│   └── platformio.ini
│
├── docs/
│   ├── control-architecture.md
│   ├── motor-architecture.md
│   ├── sensor-bringup.md
│   └── pinout.md
│
├── tuning-logs/
│
└── README.md
```

---

# Control Strategy

BALBOT uses cascaded control loops.

## Outer Loop — Balance PID

Controls:
- robot tilt angle

Outputs:
- target wheel RPM

---

## Inner Loop — Velocity PID

Controls:
- wheel speed

Outputs:
- PWM motor command

This separation improves:
- stability
- responsiveness
- tuning clarity

---

# Sensor Fusion

The MPU6050 uses a complementary filter:

```text
θ = 0.98(θ + ωΔt) + 0.02θ_acc
```

where:
- gyroscope provides short-term motion tracking
- accelerometer corrects long-term drift

This allows:
- stable tilt estimation
- smooth dynamic response
- low computational overhead

---

# Planned Features

## Core Robotics
- encoder-based wheel RPM estimation
- real-time balancing
- disturbance recovery
- runtime gain tuning

## Dashboard
- live telemetry
- PID sliders
- connection monitoring
- tuning logs
- mobile-friendly UI

## Obstacle Awareness
- TF-Luna LiDAR integration
- forward obstacle detection
- dashboard visualization
- buzzer warnings

---

# Development Philosophy

BALBOT is intentionally built:
- incrementally
- subsystem-first
- test-driven
- from first principles

Each layer is validated independently before integrating the next.

This minimizes:
- debugging complexity
- hidden coupling
- uncontrolled failure modes

---

# Current Status

## Software
- strong architectural foundation complete

## Hardware
- sensor subsystem validated
- motor subsystem awaiting physical bringup

## Next Phase
```text
Actuation Bringup
```

Including:
- motor wiring
- PWM validation
- encoder interrupts
- RPM estimation
- velocity PID testing

---

# Author

Om Anand

Computer Science + Mathematics student focused on:
- robotics
- control systems
- embedded systems
- autonomous systems
- real-time software architecture

# Time Spent
[![wakatime](https://wakatime.com/badge/github/Andromeda-crypto/BALBOT.svg)](https://wakatime.com/badge/github/Andromeda-crypto/BALBOT)
