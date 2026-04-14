#include <Arduino.h>
#include "Buzzer.h"
#include "Camera.h"

// =======================
// BLUETOOTH
// =======================
String receivedWord = "";
unsigned long lastReceiveTime = 0;
const unsigned long WORD_TIMEOUT = 120;

// =======================

void setup() {
  Serial.begin(9600);
  Serial2.begin(38400);

  Serial.println("System Ready!");
  cameraInit();
  Serial.println("Buzzer Commands: play, stop, switch");
}

// =======================

void loop() {
  readBluetooth();

  buzzerTask("");// keeps music running
  cameraTask();//Cam always scanning
}

// =======================
// BLUETOOTH
// =======================

void readBluetooth() {
  while (Serial2.available()) {
    char c = Serial2.read();
    lastReceiveTime = millis();

    if (c == '\n' || c == '\r') {
      if (receivedWord.length() > 0) {
        processCommand(receivedWord);
        receivedWord = "";
      }
    } else {
      receivedWord += c;
    }
  }

  if (receivedWord.length() > 0 && millis() - lastReceiveTime > WORD_TIMEOUT) {
    processCommand(receivedWord);
    receivedWord = "";
  }
}

// =======================

void processCommand(String word) {
  word.toLowerCase();
  word.trim();

  Serial.print("Command: ");
  Serial.println(word);

  buzzerTask(word);
}