#ifndef LIGHTS_H
#define LIGHTS_H

#include <Arduino.h>

enum LightPattern {
    LIGHT_PATTERN_NONE = 0,
    LIGHT_PATTERN_LEFT,
    LIGHT_PATTERN_RIGHT,
    LIGHT_PATTERN_LEFT_U,
    LIGHT_PATTERN_RIGHT_U,
    LIGHT_PATTERN_BRAKE
};

void lightsInit();
void lightsTask();

void startLightPattern(LightPattern pattern);
bool lightPatternActive();

void brakeLights();
void allLightsOff();

// Legacy wrappers kept for compatibility.
void leftTurnSignal();
void rightTurnSignal();
void leftUTurnSignal();
void rightUTurnSignal();

#endif
