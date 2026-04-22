#ifndef LINE_SENSOR_H
#define LINE_SENSOR_H

#include <Arduino.h>

#ifndef LINE_SENSOR_ACTIVE_STATE
#define LINE_SENSOR_ACTIVE_STATE LOW
#endif

void lineSensorInit();
bool leftOnLine();
bool rightOnLine();

#endif
