#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <Arduino.h>

enum MotorAction {
    MOTOR_ACTION_NONE = 0,
    MOTOR_ACTION_LEFT_90,
    MOTOR_ACTION_RIGHT_90,
    MOTOR_ACTION_U_LEFT,
    MOTOR_ACTION_U_RIGHT
};

void motorInit();
void motorTask();

void followLine();
void moveForward();
void turnRightCorrection();
void turnLeftCorrection();
void stopMotors();

void startMotorAction(MotorAction action);
bool motorActionActive();

// Legacy wrappers kept for compatibility.
void turnLeft90();
void turnRight90();
void uTurnLeft();
void uTurnRight();

#endif
