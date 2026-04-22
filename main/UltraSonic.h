#ifndef ULTRASONIC_H
#define ULTRASONIC_H
#include <Arduino.h>

#ifndef ULTRASONIC_TRIG_PIN
#define ULTRASONIC_TRIG_PIN 11
#endif

#ifndef ULTRASONIC_ECHO_PIN
#define ULTRASONIC_ECHO_PIN 12
#endif

#ifndef ULTRASONIC_OBJECT_DISTANCE_CM
#define ULTRASONIC_OBJECT_DISTANCE_CM 20.0f
#endif

void ultraSonicInit();
float readDistanceCm();
bool ultrasonicObjectDetected();

#endif
