#ifndef OLED_H
#define OLED_H

#include <Arduino.h>

void oledInit();
void oledSetMessage(const char* line);
void oledTask();
void oledShowLine(const char* line);

#endif
