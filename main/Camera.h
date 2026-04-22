#ifndef CAMERA_H
#define CAMERA_H

#include <Arduino.h>

void cameraInit();
bool cameraTask();
void cameraActionTask();
bool cameraActionActive();
void cameraReset();

#endif
