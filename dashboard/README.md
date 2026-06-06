# BALBOT Dashboard

This directory contains the source and deployment assets for the BALBOT browser dashboard.

The dashboard is intended to provide real-time visibility into the robot's sensing, control, actuation, and safety state during bring-up and tuning. The final deployed version will be served by the ESP32 from SPIFFS and accessed through the robot's local WiFi access point.

## Deployment Target

Final operating model:

```text
ESP32 access point: 192.168.4.1
Dashboard route:    http://192.168.4.1
WebSocket route:    ws://192.168.4.1/ws
Update rate:        approximately 20Hz
Runtime network:    offline, local to BALBOT
```

The deployed dashboard must not depend on external servers, CDN assets, or an internet connection.

## Functional Scope

The dashboard is responsible for:
- displaying live telemetry from the ESP32
- showing current control and safety state
- supporting PID gain updates during tuning
- exposing arm, disarm, reset, and emergency stop commands
- providing enough diagnostic information to evaluate balance behavior

The dashboard is not a remote driving interface. It should not provide direct manual motor control except for explicitly defined test or safety workflows.

## Development Phases

Dashboard work should remain separated into three phases:

1. UI development with simulated telemetry.
2. WebSocket integration with ESP32 firmware.
3. Static build deployment to ESP32 SPIFFS.

The development implementation may use React, Vite, and TypeScript. The firmware deployment artifact is static HTML, CSS, and JavaScript.

## Telemetry Inputs

The ESP32 should publish a compact JSON telemetry packet containing, at minimum:
- tilt angle
- target angle
- balance PID output
- left and right motor RPM
- left and right PWM command
- encoder counts
- active PID gains
- armed/balancing/safety state
- battery voltage, when available

Telemetry field names and units should be documented before hardware tuning begins.

## Commands

Dashboard-originated commands should be explicit and limited in scope:
- set balance PID gains
- set motor PID gains
- set target angle offset
- reset controller state
- arm balancing
- disarm balancing
- emergency stop

Command handling in firmware should validate input ranges and reject unsupported commands.

## Interface Requirements

The interface should prioritize operational clarity:
- readable on a phone or laptop near the robot
- usable without internet access
- high contrast under typical indoor lighting
- connection and safety state visible at all times
- emergency stop available without navigation
- charts focused on control behavior and saturation

The dashboard should support both tuning sessions and demonstrations without changing the underlying telemetry protocol.
