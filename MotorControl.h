#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <Arduino.h>

void motorInit();

void moveForward();
void stopMotors();

void turnLeft90();
void turnRight90();

void uTurnLeft();
void uTurnRight();

#endif