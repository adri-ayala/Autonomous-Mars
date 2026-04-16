#include "OLED.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <string.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// READY SCREEN
void oledShowReady() {
    display.clearDisplay();

    display.setTextSize(3);
    display.setTextColor(SSD1306_WHITE);

    display.setCursor(10, 20);
    display.print("READY");

    display.display();
}

// SIMPLE DISPLAY
void oledShowLine(const char* line) {
    display.clearDisplay();

    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);

    display.setCursor(0, 20);
    display.print(line);

    display.display();
}

// INIT
void oledInit() {
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        for (;;);
    }

    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);

    // SHOW READY
    display.setTextSize(3);
    display.setCursor(10, 20);
    display.print("READY");
    display.display();

    delay(800);

    display.clearDisplay();
    display.display();
}