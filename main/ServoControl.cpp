#include "ServoControl.h"
#include <Servo.h>

Servo myServo;

#define SERVO_PIN 13

// =======================
void servoInit() {
    myServo.attach(SERVO_PIN);
    myServo.write(90);
}

// =======================
void servoLeft() {
    myServo.write(0);
}

// =======================
void servoRight() {
    myServo.write(180);
}

// =======================
void servoCenter() {
    myServo.write(90);
}