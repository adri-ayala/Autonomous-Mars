#ifndef OLED_H
#define OLED_H

#include <Arduino.h>

void oledInit();
void oledShowMusic(const char* song, int speed);
void oledTask();

#endif