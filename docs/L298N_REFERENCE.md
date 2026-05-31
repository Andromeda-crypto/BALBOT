# L298N Motor Driver Reference

## Overview

The L298N controls DC motor direction using two digital inputs and motor speed using a PWM signal.

For Motor A:

* ENA = Speed control (PWM)
* IN1 = Direction control
* IN2 = Direction control

For Motor B:

* ENB = Speed control (PWM)
* IN3 = Direction control
* IN4 = Direction control

---

# Motor Direction Truth Table

| IN1  | IN2  | Motor State  |
| ---- | ---- | ------------ |
| HIGH | LOW  | Forward      |
| LOW  | HIGH | Reverse      |
| LOW  | LOW  | Coast / Stop |
| HIGH | HIGH | Brake        |

---

# Speed Control

Motor speed is controlled using PWM on ENA.

Example values:

| PWM Value | Approximate Speed |
| --------- | ----------------- |
| 0         | Stopped           |
| 64        | Slow              |
| 128       | Medium            |
| 192       | Fast              |
| 255       | Maximum           |

---

# Example Control Logic

Forward:

```cpp
digitalWrite(IN1, HIGH);
digitalWrite(IN2, LOW);
analogWrite(ENA, 150);
```

Reverse:

```cpp
digitalWrite(IN1, LOW);
digitalWrite(IN2, HIGH);
analogWrite(ENA, 150);
```

Stop:

```cpp
digitalWrite(IN1, LOW);
digitalWrite(IN2, LOW);
analogWrite(ENA, 0);
```

Brake:

```cpp
digitalWrite(IN1, HIGH);
digitalWrite(IN2, HIGH);
analogWrite(ENA, 0);
```

---

# BALBOT Notes

Motor bringup sequence:

1. Verify battery power to L298N.
2. Verify ESP32 control signals reach IN1/IN2.
3. Test forward rotation.
4. Test reverse rotation.
5. Test stop behavior.
6. Integrate encoder feedback.
7. Implement RPM measurement.
8. Integrate Motor PID.
9. Integrate Balance Controller.

Do not tune PID gains until forward/reverse/stop behavior is verified.
