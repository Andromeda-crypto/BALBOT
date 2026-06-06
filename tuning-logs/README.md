# BALBOT Tuning Logs

This directory contains the tuning and validation record for BALBOT's physical control system.

BALBOT is being developed through staged hardware bring-up: sensor validation, motor actuation, encoder feedback, velocity control, and full balance control. The files in this directory document that progression through test notes, tuning sessions, telemetry exports, and observed behavior during physical trials.

## Role in the Project

Tuning logs provide traceability between the robot's mechanical configuration, firmware revision, control parameters, and physical behavior.

For a self-balancing robot, the final PID values are only part of the result. The tuning process also depends on chassis geometry, sensor placement, battery voltage, motor response, encoder direction, and safety limits. Recording these sessions makes it possible to understand why specific changes were made and how the system responded.

## Expected Contents

This directory may include:
- actuation bring-up notes
- motor direction and stop validation
- encoder count and RPM validation
- motor velocity PID tuning sessions
- balance PID tuning sessions
- safety cutoff tests
- chassis revision notes
- battery and power observations
- exported dashboard telemetry
- failure analysis and corrective actions

Markdown files are used for session notes and engineering observations. CSV or JSON files may be used for exported telemetry from the dashboard.

## Current Project Context

At the current stage, BALBOT is moving from software validation into physical actuation bring-up. The first logs in this directory are expected to focus on:
- verifying motor wiring and direction
- confirming stop behavior
- validating encoder counts
- validating RPM estimation
- recording early motor PID behavior

Balance PID tuning will follow after the motor subsystem has been validated independently.

## Relationship to Other Documentation

General design documentation is maintained in `docs/`.

This directory is reserved for test evidence and tuning history. It is intended to capture what happened during physical sessions, including both successful and failed attempts.

The dashboard, once implemented, will provide live telemetry and may export session data into this directory for later review.
