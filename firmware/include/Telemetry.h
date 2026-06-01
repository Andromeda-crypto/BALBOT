#ifndef TELEMETRY_H
#define TELEMETRY_H

enum RobotMode{
    MODE_STARTUP,
    MODE_SAFE,
    MODE_ACTIVE,
    MODE_FAULT
};


struct TelemetryData {
    unsigned long timeMs;
    
    float tiltAngle;
    float targetAngle;
    float angleError;

    float controlOutput;

    float leftTargetRPM;
    float rightTargetRPM;

    float leftRPM;
    float rightRPM;

    int leftPWM;
    int rightPWM;

    RobotMode mode;    
};

class Telemetry {
    public:
    void print(const TelemetryData& data);

    private:
    const char* modeToString(RobotMode mode);
};

#endif


