#include "MotorControl.h"

#include "LineSensor.h"

namespace {

constexpr uint8_t MOTOR_PWM_A = 4;
constexpr uint8_t MOTOR_PWM_B = 5;
constexpr uint8_t INA1A = 32;
constexpr uint8_t INA2A = 34;
constexpr uint8_t INA1B = 30;
constexpr uint8_t INA2B = 36;

constexpr int PWM_TURNING = 250;
constexpr int PWM_STRAIGHT = 50;
constexpr int PWM_TURNING_LIGHTLY = 0;
constexpr int TURN_PWM = 130;

constexpr unsigned long TURN_90_MS = 550;
constexpr unsigned long UTURN_PAUSE_MS = 200;

MotorAction currentAction = MOTOR_ACTION_NONE;
unsigned long actionStepStartedAtMs = 0;
uint8_t actionPhase = 0;

void driveForward(int leftPwm, int rightPwm) {
    analogWrite(MOTOR_PWM_A, leftPwm);
    analogWrite(MOTOR_PWM_B, rightPwm);
    digitalWrite(INA1A, HIGH);
    digitalWrite(INA2A, LOW);
    digitalWrite(INA1B, HIGH);
    digitalWrite(INA2B, LOW);
}

void driveTurnLeft() {
    digitalWrite(INA1A, LOW);
    digitalWrite(INA2A, HIGH);
    digitalWrite(INA1B, HIGH);
    digitalWrite(INA2B, LOW);
    analogWrite(MOTOR_PWM_A, TURN_PWM);
    analogWrite(MOTOR_PWM_B, TURN_PWM);
}

void driveTurnRight() {
    digitalWrite(INA1A, HIGH);
    digitalWrite(INA2A, LOW);
    digitalWrite(INA1B, LOW);
    digitalWrite(INA2B, HIGH);
    analogWrite(MOTOR_PWM_A, TURN_PWM);
    analogWrite(MOTOR_PWM_B, TURN_PWM);
}

void finishMotorAction() {
    stopMotors();
    currentAction = MOTOR_ACTION_NONE;
    actionPhase = 0;
    actionStepStartedAtMs = 0;
}

}  // namespace

void motorInit() {
    pinMode(MOTOR_PWM_A, OUTPUT);
    pinMode(MOTOR_PWM_B, OUTPUT);
    pinMode(INA1A, OUTPUT);
    pinMode(INA2A, OUTPUT);
    pinMode(INA1B, OUTPUT);
    pinMode(INA2B, OUTPUT);

    stopMotors();
}

void motorTask() {
    if (currentAction == MOTOR_ACTION_NONE) {
        return;
    }

    const unsigned long now = millis();

    switch (currentAction) {
        case MOTOR_ACTION_LEFT_90:
            if (actionPhase == 0) {
                driveTurnLeft();
                actionPhase = 1;
                actionStepStartedAtMs = now;
            } else if (now - actionStepStartedAtMs >= TURN_90_MS) {
                finishMotorAction();
            }
            break;

        case MOTOR_ACTION_RIGHT_90:
            if (actionPhase == 0) {
                driveTurnRight();
                actionPhase = 1;
                actionStepStartedAtMs = now;
            } else if (now - actionStepStartedAtMs >= TURN_90_MS) {
                finishMotorAction();
            }
            break;

        case MOTOR_ACTION_U_LEFT:
            if (actionPhase == 0) {
                driveTurnLeft();
                actionPhase = 1;
                actionStepStartedAtMs = now;
            } else if (actionPhase == 1 &&
                       now - actionStepStartedAtMs >= TURN_90_MS) {
                stopMotors();
                actionPhase = 2;
                actionStepStartedAtMs = now;
            } else if (actionPhase == 2 &&
                       now - actionStepStartedAtMs >= UTURN_PAUSE_MS) {
                driveTurnLeft();
                actionPhase = 3;
                actionStepStartedAtMs = now;
            } else if (actionPhase == 3 &&
                       now - actionStepStartedAtMs >= TURN_90_MS) {
                finishMotorAction();
            }
            break;

        case MOTOR_ACTION_U_RIGHT:
            if (actionPhase == 0) {
                driveTurnRight();
                actionPhase = 1;
                actionStepStartedAtMs = now;
            } else if (actionPhase == 1 &&
                       now - actionStepStartedAtMs >= TURN_90_MS) {
                stopMotors();
                actionPhase = 2;
                actionStepStartedAtMs = now;
            } else if (actionPhase == 2 &&
                       now - actionStepStartedAtMs >= UTURN_PAUSE_MS) {
                driveTurnRight();
                actionPhase = 3;
                actionStepStartedAtMs = now;
            } else if (actionPhase == 3 &&
                       now - actionStepStartedAtMs >= TURN_90_MS) {
                finishMotorAction();
            }
            break;

        case MOTOR_ACTION_NONE:
            break;
    }
}

void followLine() {
    const bool left = leftOnLine();
    const bool right = rightOnLine();

    if (!left && !right) {
        moveForward();
    } else if (left && !right) {
        turnRightCorrection();
    } else if (!left && right) {
        turnLeftCorrection();
    } else {
        stopMotors();
    }
}

void moveForward() {
    driveForward(PWM_STRAIGHT, PWM_STRAIGHT);
}

void turnRightCorrection() {
    driveForward(PWM_TURNING_LIGHTLY, PWM_TURNING);
}

void turnLeftCorrection() {
    driveForward(PWM_TURNING, PWM_TURNING_LIGHTLY);
}

void stopMotors() {
    digitalWrite(INA1A, LOW);
    digitalWrite(INA2A, LOW);
    digitalWrite(INA1B, LOW);
    digitalWrite(INA2B, LOW);
    analogWrite(MOTOR_PWM_A, 0);
    analogWrite(MOTOR_PWM_B, 0);
}

void startMotorAction(MotorAction action) {
    currentAction = action;
    actionPhase = 0;
    actionStepStartedAtMs = millis();
}

bool motorActionActive() {
    return currentAction != MOTOR_ACTION_NONE;
}

void turnLeft90() {
    startMotorAction(MOTOR_ACTION_LEFT_90);
}

void turnRight90() {
    startMotorAction(MOTOR_ACTION_RIGHT_90);
}

void uTurnLeft() {
    startMotorAction(MOTOR_ACTION_U_LEFT);
}

void uTurnRight() {
    startMotorAction(MOTOR_ACTION_U_RIGHT);
}
