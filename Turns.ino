// ===========================================
// Turn Functions for Robot Car
// Based on Project1_V5_WIP.ino
// ===========================================
// 
// --------------------
// 90-Degree Turns
// --------------------

// Turn Left 90 degrees 
void turnLeft90() {
  noInterrupts();
  leftCount = 0;
  rightCount = 0;
  interrupts();

  // Left motor backward, right motor forward
  digitalWrite(INA1A, LOW);
  digitalWrite(INA2A, HIGH);
  digitalWrite(INA1B, HIGH);
  digitalWrite(INA2B, LOW);
  
  analogWrite(MotorPWM_A, turnPWM);
  analogWrite(MotorPWM_B, turnPWM);

  // Stop a bit early for momentum
  while ((leftCount + rightCount) / 2 < turnCounts - 20) {}
  
  // Slow down for precision
  analogWrite(MotorPWM_A, 60);
  analogWrite(MotorPWM_B, 60);
  
  while ((leftCount + rightCount) / 2 < turnCounts) {}

  stopMotors();
  delay(200);
  
  Serial2.print("Left 90 done. L=");
  Serial2.print(leftCount);
  Serial2.print(" R=");
  Serial2.println(rightCount);
}

// Turn Right 90 degrees (pivot in place)
void turnRight90() {
  noInterrupts();
  leftCount = 0;
  rightCount = 0;
  interrupts();

  // Left motor forward, right motor backward
  digitalWrite(INA1A, HIGH);
  digitalWrite(INA2A, LOW);
  digitalWrite(INA1B, LOW);
  digitalWrite(INA2B, HIGH);
  
  analogWrite(MotorPWM_A, turnPWM);
  analogWrite(MotorPWM_B, turnPWM);

  // Stop a bit early for momentum
  while ((leftCount + rightCount) / 2 < turnCounts - 20) {}
  
  // Slow down for precision
  analogWrite(MotorPWM_A, 60);
  analogWrite(MotorPWM_B, 60);
  
  while ((leftCount + rightCount) / 2 < turnCounts) {}

  stopMotors();
  delay(200);
  
  Serial2.print("Right 90 done. L=");
  Serial2.print(leftCount);
  Serial2.print(" R=");
  Serial2.println(rightCount);
}

// --------------------
// U-Turns (180 degrees)
// --------------------

// U-Turn counts (approximately double the 90-degree turn)
long uTurnCounts = 240;  // Adjust as needed (turnCounts * 2)

// Left U-Turn (180 degrees, pivot in place)
void uTurnLeft() {
  noInterrupts();
  leftCount = 0;
  rightCount = 0;
  interrupts();

  // Left motor backward, right motor forward
  digitalWrite(INA1A, LOW);
  digitalWrite(INA2A, HIGH);
  digitalWrite(INA1B, HIGH);
  digitalWrite(INA2B, LOW);
  
  analogWrite(MotorPWM_A, turnPWM);
  analogWrite(MotorPWM_B, turnPWM);

  // Stop a bit early for momentum
  while ((leftCount + rightCount) / 2 < uTurnCounts - 30) {}
  
  // Slow down for precision
  analogWrite(MotorPWM_A, 60);
  analogWrite(MotorPWM_B, 60);
  
  while ((leftCount + rightCount) / 2 < uTurnCounts) {}

  stopMotors();
  delay(200);
  
  Serial2.print("Left U-Turn done. L=");
  Serial2.print(leftCount);
  Serial2.print(" R=");
  Serial2.println(rightCount);
}

// Right U-Turn (180 degrees, pivot in place)
void uTurnRight() {
  noInterrupts();
  leftCount = 0;
  rightCount = 0;
  interrupts();

  // Left motor forward, right motor backward
  digitalWrite(INA1A, HIGH);
  digitalWrite(INA2A, LOW);
  digitalWrite(INA1B, LOW);
  digitalWrite(INA2B, HIGH);
  
  analogWrite(MotorPWM_A, turnPWM);
  analogWrite(MotorPWM_B, turnPWM);

  // Stop a bit early for momentum
  while ((leftCount + rightCount) / 2 < uTurnCounts - 30) {}
  
  // Slow down for precision
  analogWrite(MotorPWM_A, 60);
  analogWrite(MotorPWM_B, 60);
  
  while ((leftCount + rightCount) / 2 < uTurnCounts) {}

  stopMotors();
  delay(200);
  
  Serial2.print("Right U-Turn done. L=");
  Serial2.print(leftCount);
  Serial2.print(" R=");
  Serial2.println(rightCount);
}

// --------------------
// Wrapper functions with LED signals
// --------------------

// Right turn with turn signal
void rightTurn() {
  RightTurnLight();
  turnRight90();
  allLightsOff();
}

// Left turn with turn signal
void leftTurn() {
  LeftTurnLight();
  turnLeft90();
  allLightsOff();
}

// Right U-turn with turn signal
void rightUTurn() {
  RightTurnLight();
  uTurnRight();
  allLightsOff();
}

// Left U-turn with turn signal
void leftUTurn() {
  LeftTurnLight();
  uTurnLeft();
  allLightsOff();
}
