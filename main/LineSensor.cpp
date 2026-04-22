#include "LineSensor.h"

#include <Arduino.h>

namespace {

constexpr uint8_t RIGHT_SENSOR_PIN = 8;
constexpr uint8_t LEFT_SENSOR_PIN = 6;

}

void lineSensorInit() {
    pinMode(LEFT_SENSOR_PIN, INPUT);
    pinMode(RIGHT_SENSOR_PIN, INPUT);
}

bool leftOnLine() {
    return digitalRead(LEFT_SENSOR_PIN) == LINE_SENSOR_ACTIVE_STATE;
}

bool rightOnLine() {
    return digitalRead(RIGHT_SENSOR_PIN) == LINE_SENSOR_ACTIVE_STATE;
}
