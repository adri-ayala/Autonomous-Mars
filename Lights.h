#ifndef LIGHTS_H
#define LIGHTS_H

#include <Arduino.h>

void lightsInit();

void leftTurnSignal();
void rightTurnSignal();
void leftUTurnSignal();
void rightUTurnSignal();
void brakeLights();
void allLightsOff();

#endif