#include "LineSensing.h"

// =======================
// SENSOR PINS
// =======================
#define LS 8    // Left sensor
#define RS 6    // Right sensor

// HIGH = on black line — flip to LOW if your sensor is inverted
#define ON_LINE HIGH

// =======================
void lineSensorInit() {
    pinMode(LS, INPUT);
    pinMode(RS, INPUT);
}

bool leftOnLine() {
    return digitalRead(LS) == ON_LINE;
}

bool rightOnLine() {
    return digitalRead(RS) == ON_LINE;
}