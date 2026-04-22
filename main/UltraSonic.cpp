#include "UltraSonic.h"

namespace {

constexpr unsigned long ECHO_TIMEOUT_US = 30000UL;

}

void ultraSonicInit() {
    pinMode(ULTRASONIC_TRIG_PIN, OUTPUT);
    pinMode(ULTRASONIC_ECHO_PIN, INPUT);
    digitalWrite(ULTRASONIC_TRIG_PIN, LOW);
}

float readDistanceCm() {
    digitalWrite(ULTRASONIC_TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(ULTRASONIC_TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(ULTRASONIC_TRIG_PIN, LOW);

    const unsigned long duration =
        pulseIn(ULTRASONIC_ECHO_PIN, HIGH, ECHO_TIMEOUT_US);

    if (duration == 0) {
        return -1.0f;
    }

    return static_cast<float>(duration) * 0.0343f / 2.0f;
}

bool ultrasonicObjectDetected() {
    const float distanceCm = readDistanceCm();
    return distanceCm > 0.0f &&
           distanceCm <= ULTRASONIC_OBJECT_DISTANCE_CM;
}
