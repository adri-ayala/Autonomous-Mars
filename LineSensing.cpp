#include "LineSensing.h"

void lineSensorInit() {
  pinMode(MotorPWM_A, OUTPUT);
  pinMode(MotorPWM_B, OUTPUT);
  pinMode(INA1A, OUTPUT);
  pinMode(INA2A, OUTPUT);
  pinMode(INA1B, OUTPUT);
  pinMode(INA2B, OUTPUT);

  pinMode(LS, INPUT);
  pinMode(RS, INPUT);
}

void followLine() {
  bool L = digitalRead(LS);
  bool R = digitalRead(RS);

  Serial.print("LEFT: "); Serial.print(L);
  Serial.print("  |  RIGHT: "); Serial.println(R);

  if (!L && !R) {
    Serial.println(">> Forward");
    Forward();

  } else if (L && !R) {
    Serial.println(">> Correct Right");
    TurnRight();

  } else if (!L && R) {
    Serial.println(">> Correct Left");
    TurnLeft();

  } else {
    Serial.println(">> Stop");
    Stop();
  }

  delay(5);
}

void Forward() {
  analogWrite(MotorPWM_A, PWM_straight);
  analogWrite(MotorPWM_B, PWM_straight);
  digitalWrite(INA1A, 1);
  digitalWrite(INA2A, 0);
  digitalWrite(INA1B, 1);
  digitalWrite(INA2B, 0);
}

void TurnRight() {
  analogWrite(MotorPWM_A, PWM_turninglightly);  // slow left motor
  analogWrite(MotorPWM_B, PWM_turning);          // full right motor
  digitalWrite(INA1A, 1);
  digitalWrite(INA2A, 0);
  digitalWrite(INA1B, 1);
  digitalWrite(INA2B, 0);
}

void TurnLeft() {
  analogWrite(MotorPWM_A, PWM_turning);          // full left motor
  analogWrite(MotorPWM_B, PWM_turninglightly);  // slow right motor
  digitalWrite(INA1A, 1);
  digitalWrite(INA2A, 0);
  digitalWrite(INA1B, 1);
  digitalWrite(INA2B, 0);
}

void Stop() {
  digitalWrite(INA1A, 0);
  digitalWrite(INA2A, 0);
  digitalWrite(INA1B, 0);
  digitalWrite(INA2B, 0);
}
