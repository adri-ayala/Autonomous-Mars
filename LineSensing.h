#ifndef LINESENSING_H
#define LINESENSING_H

#include <Arduino.h>

// =======================
// MOTOR PINS
// =======================
#define MotorPWM_A 4
#define MotorPWM_B 5
#define INA1A 32
#define INA2A 34
#define INA1B 30
#define INA2B 36

// =======================
// SENSOR PINS
// =======================
#define RS 8
#define LS 6

// =======================
// PWM SPEEDS
// =======================
#define PWM_turning        250
#define PWM_straight        50
#define PWM_turninglightly   0

void lineSensorInit();
void followLine();
void Forward();
void TurnRight();
void TurnLeft();
void Stop();

#endif
