#include "OLED.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// DISPLAY CONFIG
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// STATE
String currentSong = "No Song";
int currentSpeed = 0;

// INIT
void oledInit() {
    Serial.println("Initializing OLED...");

    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println("OLED failed!");
        for (;;);
    }

    display.clearDisplay();
    display.display();
}

// SHOW MUSIC DASHBOARD 
void oledShowMusic(const char* song, int speed) {
    currentSong = song;
    currentSpeed = speed;

    display.clearDisplay();

    // Title
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("Now Playing:");

    // Song name
    display.setTextSize(2);
    display.setCursor(0, 14);
    display.println(currentSong);

    // Speed
    display.setTextSize(1);
    display.setCursor(0, 42);
    display.print("Speed: ");
    display.print(currentSpeed);
    display.println(" mph");

    display.display();
}
/*void oledTask() {
}*/