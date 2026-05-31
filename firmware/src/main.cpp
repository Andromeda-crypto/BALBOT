#include <Arduino.h>


const int IN1 = 25;
const int IN2 = 26;

void setup() {
    Serial.begin(115200);

    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);   

    Serial.println("L298N one-motor test started");
}

void loop() {
    Serial.println("Forward");
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    delay(2000);

    Serial.println("Stop");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    delay(2000);


    Serial.println("Reverse");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    delay(2000);

    Serial.println("Stop");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    delay(2000);


}