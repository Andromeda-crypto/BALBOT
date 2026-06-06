# BALBOT Tuning Logs

This directory stores hardware tuning notes, session logs, exported dashboard data, and test observations for BALBOT.

Tuning logs are part of the engineering record. They connect firmware changes, PID gain values, chassis configuration, hardware conditions, and observed robot behavior. This prevents tuning from becoming guesswork and makes the project easier to debug, reproduce, and present.

## Purpose

BALBOT is a physical control system. Small changes in chassis geometry, motor response, battery voltage, sensor mounting, encoder direction, or PID gains can significantly affect stability.

This directory should capture:
- actuation bring-up results
- encoder and RPM validation notes
- motor velocity PID tuning attempts
- balance PID tuning attempts
- safety cutoff behavior
- chassis revisions
- battery and power observations
- dashboard-exported telemetry sessions
- failures, suspected causes, fixes, and results

The goal is to preserve not only final values, but the reasoning path that led to them.


```md
# Session Title

## Setup
- Date:
- Chassis:
- Battery:
- Firmware commit:
- Test location:
- Sensor mount:
- Motor driver:
- Notes:

## Goal
- What this session is trying to validate or improve.

## Starting Values
- Balance Kp:
- Balance Ki:
- Balance Kd:
- Motor Kp:
- Motor Ki:
- Motor Kd:
- Target angle:

## Observations
- What the robot did.
- Whether it oscillated, drifted, saturated, fell, recovered, or behaved asymmetrically.
- Any visible mechanical or electrical issues.

## Changes Made
| Attempt | Parameter Change | Observation | Result |
|---|---|---|---|
| 1 |  |  |  |

## Outcome
- Pass/fail result.
- Best values from the session.
- What should be tested next.

## Follow-Up
- Hardware fixes:
- Firmware fixes:
- Dashboard/logging fixes:
```

## Logging Guidelines

Use precise language when recording behavior:
- "Falls forward after 1-2 seconds" is better than "unstable."
- "PID output saturated at +255 during recovery" is better than "too much output."
- "Left RPM reads negative during forward command" is better than "encoder wrong."

Record failed attempts. Failed tests are valuable because they explain why final tuning choices were made.

## Dashboard Exports

When the dashboard supports exporting telemetry, save CSV or JSON files here.

Useful exported fields:
- timestamp
- angle
- target angle
- PID output
- left RPM
- right RPM
- left PWM
- right PWM
- active gains
- armed/safety state
- battery voltage, if available

Dashboard exports should be paired with a short Markdown note explaining what physical test was being performed.

