#include <Servo.h>

Servo myServo;
#define SERVO_PIN 13;

setup():
myServo.attach(SERVO_PIN);
myServo.write(90);  // Start centered


void servoLeft() {
  myServo.write(0);
}

void servoRight() {
  myServo.write(180);
}

void servoCenter() {
  myServo.write(90);
}


servoLeft();    // Turn servo left
delay(500);
servoCenter();  // Return to center
delay(500);
servoRight();   // Turn servo right