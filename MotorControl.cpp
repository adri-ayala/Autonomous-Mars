#include "MotorControl.h"

// =======================
// MOTOR PINS (FROM YOUR TABLE)
// =======================
#define MotorPWM_A 4
#define INA1A 32
#define INA2A 34

#define MotorPWM_B 5
#define INA1B 30
#define INA2B 36

int turnPWM = 130;

// =======================
void motorInit() {
    pinMode(INA1A, OUTPUT);
    pinMode(INA2A, OUTPUT);
    pinMode(INA1B, OUTPUT);
    pinMode(INA2B, OUTPUT);

    pinMode(MotorPWM_A, OUTPUT);
    pinMode(MotorPWM_B, OUTPUT);

    stopMotors();
}

// =======================
void moveForward() {
    digitalWrite(INA1A, HIGH);
    digitalWrite(INA2A, LOW);

    digitalWrite(INA1B, HIGH);
    digitalWrite(INA2B, LOW);

    analogWrite(MotorPWM_A, 150);
    analogWrite(MotorPWM_B, 150);
}

// =======================
void stopMotors() {
    digitalWrite(INA1A, LOW);
    digitalWrite(INA2A, LOW);
    digitalWrite(INA1B, LOW);
    digitalWrite(INA2B, LOW);
}

// =======================
void turnLeft90() {
    digitalWrite(INA1A, LOW);
    digitalWrite(INA2A, HIGH);

    digitalWrite(INA1B, HIGH);
    digitalWrite(INA2B, LOW);

    analogWrite(MotorPWM_A, turnPWM);
    analogWrite(MotorPWM_B, turnPWM);

    delay(550);
    stopMotors();
}

// =======================
void turnRight90() {
    digitalWrite(INA1A, HIGH);
    digitalWrite(INA2A, LOW);

    digitalWrite(INA1B, LOW);
    digitalWrite(INA2B, HIGH);

    analogWrite(MotorPWM_A, turnPWM);
    analogWrite(MotorPWM_B, turnPWM);

    delay(550);
    stopMotors();
}

// =======================
void uTurnLeft() {
    turnLeft90();
    delay(200);
    turnLeft90();
}

// =======================
void uTurnRight() {
    turnRight90();
    delay(200);
    turnRight90();
}