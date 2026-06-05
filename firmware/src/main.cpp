        case BringupStage::LeftForward:
        case BringupStage::LeftReverse:
        case BringupStage::RightForward:
        case BringupStage::RightReverse:
            return 4000;
        case BringupStage::LeftStop:
        case BringupStage::RightStop:
            return 2000;
        case BringupStage::FinalStop:
            return 0;
    }

    return 0;
}

BringupStage nextStage(BringupStage currentStage) {
    switch (currentStage) {
        case BringupStage::StartupStop:
            return BringupStage::LeftForward;
        case BringupStage::LeftForward:
            return BringupStage::LeftStop;
        case BringupStage::LeftStop:
            return BringupStage::LeftReverse;
        case BringupStage::LeftReverse:
            return BringupStage::RightForward;
        case BringupStage::RightForward:
            return BringupStage::RightStop;
        case BringupStage::RightStop:
            return BringupStage::RightReverse;
        case BringupStage::RightReverse:
        case BringupStage::FinalStop:
            return BringupStage::FinalStop;
    }

    return BringupStage::FinalStop;
}

void stopBothMotors() {
    leftMotor.stop();
    rightMotor.stop();
}

void applyStageOutputs(BringupStage currentStage) {
    stopBothMotors();

    switch (currentStage) {
        case BringupStage::LeftForward:
            leftMotor.setPWM(BRINGUP_PWM);
            break;
        case BringupStage::LeftReverse:
            leftMotor.setPWM(-BRINGUP_PWM);
            break;
        case BringupStage::RightForward:
            rightMotor.setPWM(BRINGUP_PWM);
            break;
        case BringupStage::RightReverse:
            rightMotor.setPWM(-BRINGUP_PWM);
            break;
        case BringupStage::StartupStop:
        case BringupStage::LeftStop:
        case BringupStage::RightStop:
        case BringupStage::FinalStop:
            break;
    }
}

void enterStage(BringupStage next) {
    stage = next;
    stageStartedAt = millis();
    leftMotor.resetEncoderCount();
    rightMotor.resetEncoderCount();
    applyStageOutputs(stage);

    Serial.println();
    Serial.print("Stage: ");
    Serial.println(stageName(stage));
}

void printMotorTelemetry(const char* label, const Motor& motor) {
    Serial.print(label);
    Serial.print(" PWM=");
    Serial.print(motor.getPWM());
    Serial.print(" Count=");
    Serial.print(motor.getEncoderCount());
    Serial.print(" RPM=");
    Serial.print(motor.getRPM(), 2);
    Serial.print(" TargetRPM=");
    Serial.print(motor.getTargetRPM(), 2);
    Serial.print(" PID=");
    Serial.print(motor.isVelocityPIDEnabled() ? "ON" : "OFF");
}

void printTelemetry() {
    Serial.print("t=");
    Serial.print(millis());
    Serial.print(" stage=");
    Serial.print(stageName(stage));
    Serial.print(" | ");
    printMotorTelemetry("L", leftMotor);
    Serial.print(" | ");
    printMotorTelemetry("R", rightMotor);
    Serial.println();
}
}

void setup() {
    Serial.begin(115200);
    delay(500);

    Serial.println("BALBOT Actuation Bringup");
    Serial.println("Raw PWM tests run one motor at a time. Keep the robot lifted and ready to cut power.");
    Serial.print("Encoder counts per revolution assumption: ");
    Serial.println(ENCODER_COUNTS_PER_REVOLUTION);

    leftMotor.begin();
    rightMotor.begin();

    leftMotor.setVelocityPIDEnabled(false);
    rightMotor.setVelocityPIDEnabled(false);

    lastUpdateAt = micros();
    enterStage(BringupStage::StartupStop);
}

void loop() {
    unsigned long nowMicros = micros();
    if (nowMicros - lastUpdateAt >= MOTOR_UPDATE_INTERVAL_US) {
        float dt = (nowMicros - lastUpdateAt) / 1000000.0;
        lastUpdateAt = nowMicros;

        leftMotor.update(dt);
        rightMotor.update(dt);
    }

    unsigned long nowMillis = millis();
    if (nowMillis - lastTelemetryAt >= TELEMETRY_INTERVAL_MS) {
        lastTelemetryAt = nowMillis;
        printTelemetry();
    }

    unsigned long duration = stageDurationMs(stage);
    if (duration > 0 && nowMillis - stageStartedAt >= duration) {
        enterStage(nextStage(stage));
    }
}